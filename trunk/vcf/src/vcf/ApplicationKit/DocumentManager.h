#ifndef _VCF_DOCUMENTMANAGER_H__
#define _VCF_DOCUMENTMANAGER_H__
//DocumentManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class APPLICATIONKIT_API DocManagerEvent : public Event {
public:
	DocManagerEvent( Object* source, ulong32 type ): Event( source, type ),
			allowFileOp_(true), fileOperationStatus_(false) {

	}

	bool allowFileOperation() {
		return allowFileOp_;
	}

	void setAllowFileOperation( const bool& val ) {
		allowFileOp_ = val;
	}

	bool getFileOperationStatus() {
		return fileOperationStatus_;
	}

	/**
	Programs that handle file saving themselves
	without relying on the base behaviour should call this
	method on the event. It will dictate what the
	DocumentManager::saveFile() wil return.
	@param bool if allowFileOperation() is false it indicates that the
	event handler handled the file operation and DocumentManager::saveFile()
	will the value of val, or getFileOperationStatus().
	*/
	void setFileOperationStatus( const bool& val ) {
		fileOperationStatus_ = val;
	}
protected:
	bool allowFileOp_;
	bool fileOperationStatus_;
};




class APPLICATIONKIT_API DocumentInfo {
public:
	String classID;
	String className;
	String view;
	String window;
	String fileTypes;
	String mimetype;
	String description;
};


/**
<p>
The DocumentManager manages the interaction between the application (and any other
UI classes) a collection of one or more documents, and the DocInterfacePolicy
(which manages the collection of one or more documents).
The DocumentManager allows only a single instance, which you can get at by calling the
static method DocumentManager::getDocumentManager().
</p>

@delegates
	@del DocumentManager::SaveFile
	@del DocumentManager::OpenFile
	@del DocumentManager::DocumentInitialized
	@del DocumentManager::DocumentClosed
	@del DocumentManager::CurrentDocumentChanged
*/
class APPLICATIONKIT_API DocumentManager {
public:
	DocumentManager();

	virtual ~DocumentManager();

	enum {
		dmSaveDocument = 1000,
		dmOpenDocument,
		dmNewDocument,
		dmCloseDocument,
		dmDocumentInitialized,
		dmCurrentDocumentChanged,
	};


	enum ActionTag {
		atFileNew = 1,
		atFileOpen,
		atFileClose,
		atFileSave,
		atFileSaveAs,
		atEditUndo = 100,
		atEditRedo,
		atEditCut,
		atEditCopy,
		atEditPaste,
		atEditPreferences
	};

	/**
	@delegate SaveFile this is called when the document manager's saveFile()
	method is called.
	@event DocManagerEvent
	@eventtype DocumentManager::dmSaveDocument
	@see saveFile()
	*/
	DELEGATE(SaveFile);

	/**
	@delegate OpenFile this is called when the document manager's
	openFile() method is called.
	@event DocManagerEvent
	@eventtype  DocumentManager::dmOpenDocument
	*/
	DELEGATE(OpenFile);

	/**
	@delegate DocumentInitialized this is called after a newly created document has
	been fully initialized by the document manager. At this point the document should
	be connected to it's views (at least as many of them as the document manager knows
	about), as well as having a window set for it.
	@event DocManagerEvent
	@eventtype DocumentManager::dmDocumentInitialized
	@see Document::setWindow
	*/
	DELEGATE(DocumentInitialized)

	/**
	@delegate DocumentClosed this is called when the document is closed by
	the DocInterfacePolicy. It is up to the implementer to call fire the
	event to the delegate.
	@event DocManagerEvent
	*/
	DELEGATE(DocumentClosed)

	/**
	@delegate CurrentDocumentChanged this is fired whenever the
	currentDocumentChanged() method is called. It is the responsibility of
	the DocInterfacePolicy to call the currentDocumentChanged() method
	when appropriate.
	@event DocManagerEvent
	@eventtype DocumentManager::dmCurrentDocumentChanged
	*/
	DELEGATE(CurrentDocumentChanged)


	virtual void init();

	virtual void terminate();

	UndoRedoStack& getUndoRedoStack( Document* doc );

	Menu* getStandardMenu() {
		return standardMenu_;
	}

	virtual void cutFromDocument( Document* doc );

	virtual void copyFromDocument( Document* doc );

	virtual void pasteToDocument( Document* doc );

	virtual void undoForDocument( Document* doc );

	virtual void redoForDocument( Document* doc );

	virtual void editPreferences(){};

	virtual bool saveFile( Document* document ){
		return false;
	}

	virtual void openFile(){};

	virtual void closeCurrentDocument(){};

	void currentDocumentChanged() {
		DocManagerEvent event( getCurrentDocument(), DocumentManager::dmCurrentDocumentChanged );
		CurrentDocumentChanged.fireEvent( &event );
	}

	virtual Document* openFromFileName( const String& fileName );

	virtual void newDocument(){
		newDefaultDocument();
	}

	virtual Document* newDefaultDocument( const String& mimetype="" ){
		return NULL;
	};


	virtual Document* createDocumentFromType( const DocumentInfo& info ){
		return NULL;
	};

	virtual Document* getCurrentDocument() {
		return NULL;
	}

	virtual void setCurrentDocument( Document* newCurrentDocument ) {

	}

	virtual void createMenus(){};

	static DocumentManager* getDocumentManager();

	String getMimeTypeFromFileExtension( const String& fileName );

	DocumentInfo getDocumentInfo( const String& mimeType );

	virtual Window* getWindowForNewDocument( Document* document, const DocumentInfo& info ) {
		return NULL;
	}

	virtual void initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info  ) {}

	void addDocumentInfo( const VCF::String& mimeType, const DocumentInfo& info );

	bool saveDocument( Document* doc );

	virtual void setNewView( DocumentInfo info, View* view, Window* window, Document* newDocument ) {
		view->setViewControl( window );
		window->setView( view );
		newDocument->addView( window );
	}


	Enumerator<DocumentInfo>* getRegisteredDocumentInfo();

	bool getShouldCreateUI() {
		return shouldCreateUI_;
	}

	void setShouldCreateUI( bool val ) {
		shouldCreateUI_ = val;
	}

	virtual void attachUIToDocument( const String& mimeType, Document* document ) {};

	Action* getAction( ActionTag tag );

	Enumerator<Document*>* getOpenedDocuments();
protected:
	virtual void prepareOpenDialog( CommonFileOpen* openDialog );

	virtual void openDialogFinished( CommonFileOpen* openDialog ){};

	virtual void prepareSaveDialog( CommonFileSave* saveDialog, Document* doc );

	virtual void saveDialogFinished( CommonFileSave* saveDialog ){};

	DocumentInfo* getDocumentInfo( Document* doc );

	void updatePaste( ActionEvent* event, Document* doc );

	void updateCut( ActionEvent* event, Document* doc );

	void updateCopy( ActionEvent* event, Document* doc );

	void updateUndo( ActionEvent* event, Document* doc );

	void updateRedo( ActionEvent* event, Document* doc );

	void removeUndoRedoStackForDocument( Document* doc );

	UIToolkit::ModalReturnType saveChanges( Document* document );

	void addAction( ActionTag tag, Action* action );

	void addDocument( Document* document );
	void removeDocument( Document* document );

	typedef std::map<String,DocumentInfo> DocumentInfoMap;
	typedef std::map<Document*,UndoRedoStack*> DocumentUndoRedoMap;

	typedef std::map<ulong32,Action*> ActionMap;

	DocumentInfoMap docInfo_;

	EnumeratorMapContainer<DocumentInfoMap,DocumentInfo> docInfoContainer_;

	static DocumentManager* docManagerInstance;

	DocumentUndoRedoMap undoRedoStack_;
	Menu* standardMenu_;
	bool shouldCreateUI_;

	ActionMap actionsMap_;
	std::vector<Document*> openDocuments_;
	EnumeratorContainer<std::vector<Document*>,Document*> openDocContainer_;
};


/**
class DocumentManagerImpl documentation
*/
template < typename AppClass,
			typename DocInterfacePolicy >
class DocumentManagerImpl : public DocumentManager, public DocInterfacePolicy {
public:
	DocumentManagerImpl(): app_(NULL), closingDocument_(false), documentClosedOK_(false) {}




	virtual void init();

	virtual bool saveFile( Document* document );

	virtual void openFile();

	virtual void closeCurrentDocument();

	virtual Document* newDefaultDocument( const String& mimetype="" );


	virtual Document* createDocumentFromType( const DocumentInfo& info );

	virtual void createMenus();

	virtual Document* getCurrentDocument() {
		return DocInterfacePolicy::getCurrentDocument();
	}

	virtual void setCurrentDocument( Document* newCurrentDocument ) {

		DocInterfacePolicy::setCurrentDocument(newCurrentDocument);

		VCF::DocumentManager::getDocumentManager()->currentDocumentChanged();
	}

	virtual Window* getWindowForNewDocument( Document* document, const DocumentInfo& info );

	virtual void initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info  );

	virtual void attachUIToDocument( const String& mimeType, Document* document );
protected:

	AppClass* app_;
	bool closingDocument_;
	bool documentClosedOK_;

	void onNew( Event* e ) {
		newDocument();
	}

	void onSave( Event* e ) {
		saveFile( DocInterfacePolicy::getCurrentDocument() );
	}

	void onSaveAs( Event* e ) {
		Document* doc = DocInterfacePolicy::getCurrentDocument();
		doc->setFileName( "" );
		doc->setModified(true);
		saveFile( doc );
	}

	void onOpen( Event* e ) {
		openFile();
	}

	void onClose( Event* e ) {
		closeCurrentDocument();
	}

	void onUndo( Event* e ) {
		undoForDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	void onUpdateUndo( ActionEvent* e ) {

		updateUndo( e, DocInterfacePolicy::getCurrentDocument() );
	}

	void onRedo( Event* e ) {
		redoForDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	void onUpdateRedo( ActionEvent* e ) {

		updateRedo( e, DocInterfacePolicy::getCurrentDocument() );
	}

	void onCut( Event* e ) {
		cutFromDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	void onUpdateCut( ActionEvent* e ) {


		updateCut( e, DocInterfacePolicy::getCurrentDocument() );
	}

	void onCopy( Event* e ) {
		copyFromDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	void onUpdateCopy( ActionEvent* e ) {

		updateCopy( e, DocInterfacePolicy::getCurrentDocument() );
	}

	void onPaste( Event* e ) {
		pasteToDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	void onUpdatePaste( ActionEvent* e ) {

		updatePaste( e, DocInterfacePolicy::getCurrentDocument() );
	}

	void onPreferences( Event* e ) {
		editPreferences();
	}

	void onUpdatePreferences( ActionEvent* e ) {

	}

	void onDocWindowClosing( FrameEvent* e ) {

		if ( !DocInterfacePolicy::closeDocumentWindow( (Window*)e->getSource() ) ) {
			e->setOkToClose( false );
		}

	}

	void onDocWindowActive( WindowEvent* e ) {
		Window* window = (Window*)e->getSource();

		if ( window->isActive() ) {
			DocInterfacePolicy::documentWindowActivated( window );
		}
	}

	void onDocModified( ModelEvent* e ) {
		Document* doc = (Document*)e->getSource();
		String caption = DocInterfacePolicy::getDocumentWindowCaption();

		if ( caption != doc->getWindow()->getCaption() ) {
			doc->getWindow()->setCaption( caption );
		}
	}

	void attachUI( const DocumentInfo& info, Document* document );

	void initActions();
};







template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::init()
{
	app_ = reinterpret_cast<AppClass*>( Application::getRunningInstance() );

	DocumentManager::init();

	initActions();
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::initActions()
{
	Action* action = new Action();
	action->setName("FileNew");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onNew,
													"onNew" );
	addAction( DocumentManager::atFileNew, action );

	action = new Action();
	action->setName("FileOpen");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onOpen,
													"onOpen" );
	addAction( DocumentManager::atFileOpen, action );

	action = new Action();
	action->setName("FileSave");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onSave,
													"onSave" );
	addAction( DocumentManager::atFileSave, action );

	action = new Action();
	action->setName("FileSaveAs");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onSaveAs,
													"onSaveAs" );
	addAction( DocumentManager::atFileSaveAs, action );

	action = new Action();
	action->setName("FileClose");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onClose,
													"onClose" );
	addAction( DocumentManager::atFileClose, action );

	action = new Action();
	action->setName("EditUndo");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUndo,
													"onUndo" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateUndo,
													"onUpdateUndo" );

	addAction( DocumentManager::atEditUndo, action );

	action = new Action();
	action->setName("EditRedo");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onRedo,
													"onRedo" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateRedo,
													"onUpdateRedo" );

	addAction( DocumentManager::atEditRedo, action );


	action = new Action();
	action->setName("EditCut");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onCut,
													"onCut" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateCut,
													"onUpdateCut" );

	addAction( DocumentManager::atEditCut, action );

	action = new Action();
	action->setName("EditCopy");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onCopy,
													"onCopy" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateCopy,
													"onUpdateCopy" );

	addAction( DocumentManager::atEditCopy, action );


	action = new Action();
	action->setName("EditPaste");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onPaste,
													"onPaste" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdatePaste,
													"onUpdatePaste" );

	addAction( DocumentManager::atEditPaste, action );


	action = new Action();
	action->setName("EditPreferences");
	action->Performed += new GenericEventHandler< AppClass >( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onPreferences,
													"onPreferences" );
	action->Update +=
			new EventHandlerInstance<AppClass,ActionEvent>( app_,
													&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdatePreferences,
													"onUpdatePreferences" );

	addAction( DocumentManager::atEditPreferences, action );

}


template < typename AppClass, typename DocInterfacePolicy >
bool DocumentManagerImpl<AppClass,DocInterfacePolicy>::saveFile( Document* doc ) {
	bool result = false;

	if ( NULL == doc ) {

		return false;
	}

	if ( doc->isModified() ) {

		DocManagerEvent event( doc, DocumentManager::dmSaveDocument );
		SaveFile.fireEvent( &event );
		if ( !event.allowFileOperation() ) {
			return event.getFileOperationStatus();
		}

		String fileType;
		String fileTypes;

		DocumentInfo* info = getDocumentInfo( doc );
		if ( NULL != info ) {
			fileType = info->mimetype;
			fileTypes = info->fileTypes;
		}

		FilePath tmpName;
		FilePath fp = doc->getFileName();
		if ( !File::exists( fp ) ) {
			String currentDir = System::getCurrentWorkingDirectory();
			CommonFileSave saveDialog( doc->getWindow(), currentDir );

			prepareSaveDialog( &saveDialog, doc );

			if ( saveDialog.execute() ) {

				saveDialogFinished( &saveDialog );

				fp = saveDialog.getFileName();

				if ( fp.getExtension().empty() ) {
					String selectedFilter = saveDialog.getSelectedFilter();
					selectedFilter.erase( 0, 1 );
					fp = saveDialog.getFileName() + selectedFilter;
				}

				doc->setFileName( fp );
			}
			else {

				return false;
			}
		}
		else {
			//save back up
			File backup( fp );
			String tmp = fp.getPathName(true);
			tmp += "~" + fp.getBaseName() + ".tmp";
			tmpName = tmp;
			backup.copyTo( tmpName );
		}

		if ( fileType.empty() ) {
			fileType = fp.getExtension();
		}

		try {
			result = doc->saveAsType( doc->getFileName(), fileType );
		}
		catch ( BasicException& e) {
			Dialog::showMessage( "Error saving '" + doc->getName() + "'\nError: " + e.getMessage() );
			result = false;
		}

		if ( result ) {
			if ( (!doc->getKeepsBackUpFile()) && File::exists( tmpName ) ) {
				File backup( tmpName );
				backup.remove();
			}
		}
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::openFile() {
	Document* doc = DocInterfacePolicy::getCurrentDocument();

	DocManagerEvent event( NULL, DocumentManager::dmOpenDocument );
	OpenFile.fireEvent( &event );
	if ( !event.allowFileOperation() ) {
		return;
	}

	String currentDir = System::getCurrentWorkingDirectory();

	CommonFileOpen openDialog( Frame::getActiveFrame(), currentDir );

	prepareOpenDialog( &openDialog );



	if ( openDialog.execute() ) {

		Document* doc = openFromFileName( openDialog.getFileName() );

		openDialogFinished( &openDialog );
	}
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::closeCurrentDocument()
{
	closingDocument_ = true;
	Document* currentDoc = DocInterfacePolicy::getCurrentDocument();
	removeDocument( currentDoc );
	DocInterfacePolicy::closeDocument();
	closingDocument_ = false;
	removeUndoRedoStackForDocument( currentDoc );
}

template < typename AppClass, typename DocInterfacePolicy >
Window* DocumentManagerImpl<AppClass,DocInterfacePolicy>::getWindowForNewDocument( Document* document, const DocumentInfo& info )
{
	Window* result;

	if ( DocInterfacePolicy::usesMainWindow() ) {
		if ( NULL == app_->getMainWindow() ) {
			if ( info.window.empty() ) {
				result = new Window();
			}
			else {

				Object* windowObj = ClassRegistry::createNewInstance( info.window );
				result = dynamic_cast<Window*>(windowObj);

			}
			app_->setMainWindow( result );
		}
		else {
			result = app_->getMainWindow();
		}
	}
	else {
		if ( info.window.empty() ) {
			result = new Window();
		}
		else {

			Object* windowObj = ClassRegistry::createNewInstance( info.window );
			result = dynamic_cast<Window*>(windowObj);
		}
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info )
{
	if ( NULL == window->getMenuBar() ) {
		MenuBar* menu = new MenuBar();
		window->setMenuBar(menu);
		window->addComponent( menu );
	}

	DocInterfacePolicy::mergeWindowMenus( standardMenu_, window->getMenuBar() );
}


template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::attachUI( const DocumentInfo& info, Document* document )
{
	Window* window = NULL;

	EventHandler* docEv = app_->getEventHandler("onDocModified");

	window = getWindowForNewDocument( document, info );

	initializeWindowMenus( window, document, info );

	document->setWindow( window );

	if ( NULL == docEv ) {

		docEv = new ModelEventHandler< AppClass >( app_,
					&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocModified,
					"onDocModified" );
	}

	document->addModelHandler( docEv );

	/**
	create a view from the Docinfo if neccessary
	*/
	View* view = NULL;
	if ( !info.view.empty() ) {
		if ( info.window != info.view ) {
			Object* viewObject = NULL;
			viewObject = ClassRegistry::createNewInstance( info.view );

			view = dynamic_cast<View*>(viewObject);
		}
		else {
			view = window;
		}
	}
	else {
		view = window;
	}

	if ( NULL != view ) {
		document->addView( view );

		if ( view != window ) {

			setNewView( info, view, window, document );
		}
	}

	//need to provide a common place to
	//init everything once all the "connections" are in place

	DocInterfacePolicy::afterNewDocument( document );

	DocManagerEvent event( document, DocumentManager::dmDocumentInitialized );

	DocumentInitialized.fireEvent( &event );

	EventHandler* newEv = app_->getEventHandler("onDocWindowClosing");
	if ( NULL == newEv ) {

		newEv = new FrameEventHandler< AppClass >( app_,
					&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWindowClosing,
					"onDocWindowClosing" );
	}
	window->FrameClosing += newEv;


	newEv = app_->getEventHandler("onDocWindowActive");
	if ( NULL == newEv ) {

		newEv = new WindowEventHandler< AppClass >( app_,
					&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWindowActive,
					"onDocWindowActive" );
	}

	window->FrameActivation += newEv;

	window->show();

	document->updateAllViews();
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::attachUIToDocument( const String& mimeType, Document* document )
{
	DocumentInfo info = getDocumentInfo( mimeType );
	Window* window = NULL;

	EventHandler* docEv = app_->getEventHandler("onDocModified");


	if ( DocInterfacePolicy::saveBeforeNewDocument() ) {
		Document* doc = DocInterfacePolicy::getCurrentDocument();
		if ( NULL != doc ) {
			doc->removeModelHandler( docEv );
			if ( doc->isModified() ) {
				switch ( saveChanges( doc ) ) {
					case UIToolkit::mrCancel : {
						doc->addModelHandler( docEv );
						return ;
					}
					break;
				}
			}
		}
	}

	attachUI( info, document );

	ModelEvent e( document, Document::deOpened );
	document->ModelChanged.fireEvent( &e );
}

template < typename AppClass, typename DocInterfacePolicy >
Document* DocumentManagerImpl<AppClass,DocInterfacePolicy>::newDefaultDocument( const String& mimetype )
{

	DocumentInfo info = getDocumentInfo( mimetype );

	Window* window = NULL;

	EventHandler* docEv = app_->getEventHandler("onDocModified");

	if ( DocumentManager::getShouldCreateUI() ) {

		if ( DocInterfacePolicy::saveBeforeNewDocument() ) {
			Document* doc = DocInterfacePolicy::getCurrentDocument();
			if ( NULL != doc ) {
				doc->removeModelHandler( docEv );
				if ( doc->isModified() ) {
					switch ( saveChanges( doc ) ) {
					case UIToolkit::mrCancel : {
						doc->addModelHandler( docEv );
						return NULL;
											   }
						break;
					}
				}
			}
		}
	}

	Document* newDocument = createDocumentFromType( info );


	if ( NULL != newDocument ) {

		newDocument->initNew();
		if ( DocumentManager::getShouldCreateUI() ) {
			attachUI( info, newDocument );
		}
	}
	else {
		//throw exception !
	}

	return newDocument;
}


template < typename AppClass, typename DocInterfacePolicy >
Document* DocumentManagerImpl<AppClass,DocInterfacePolicy>::createDocumentFromType( const DocumentInfo& info ) {
	Document* result = NULL;

	Class* clazz = NULL;
	Object* objInstance = NULL;
	if ( !info.classID.empty() ) {
		objInstance = ClassRegistry::createNewInstanceFromClassID( info.classID );
	}
	else {
		objInstance = ClassRegistry::createNewInstance( info.className );
	}

	result = dynamic_cast<Document*>( objInstance );
	if ( NULL == result ) {
		objInstance->free();
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::createMenus() {
	standardMenu_ = new MenuBar();
	MenuItem* root = standardMenu_->getRootMenuItem();
	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, standardMenu_);

	DefaultMenuItem* fileNew = new DefaultMenuItem( "&New\tCtrl+N", file, standardMenu_);
	fileNew->setAcceleratorKey( vkLetterN, kmCtrl );
	fileNew->setTag( DocumentManager::atFileNew );


	DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open...\tCtrl+O", file, standardMenu_);
	fileOpen->setAcceleratorKey( vkLetterO, kmCtrl );
	fileOpen->setTag( DocumentManager::atFileOpen );

	DefaultMenuItem* fileClose = new DefaultMenuItem( "Close", file, standardMenu_);
	fileClose->setTag( DocumentManager::atFileClose );


	DefaultMenuItem* separator = new DefaultMenuItem( "", file, standardMenu_);
	separator->setSeparator( true );


	DefaultMenuItem* fileSave = new DefaultMenuItem( "&Save...\tCtrl+S", file, standardMenu_);
	fileSave->setAcceleratorKey( vkLetterS, kmCtrl );
	fileSave->setTag( DocumentManager::atFileSave );

	DefaultMenuItem* fileSaveAs = new DefaultMenuItem( "Save &As...\tCtrl+Shift+S", file, standardMenu_);
	fileSaveAs->setAcceleratorKey( vkLetterS, kmCtrl | kmShift );
	fileSaveAs->setTag( DocumentManager::atFileSaveAs );


	DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, standardMenu_);
	DefaultMenuItem* editUndo = new DefaultMenuItem( "&Undo\tCtrl+Z", edit, standardMenu_);
	editUndo->setAcceleratorKey( vkLetterZ, kmCtrl  );
	editUndo->setTag( DocumentManager::atEditUndo );

	DefaultMenuItem* editRedo = new DefaultMenuItem( "&Redo\tCtrl+Shift+Z", edit, standardMenu_);
	editRedo->setAcceleratorKey( vkLetterZ, kmCtrl | kmShift );
	editRedo->setTag( DocumentManager::atEditRedo );

	separator = new DefaultMenuItem( "", edit, standardMenu_);
	separator->setSeparator( true );

	DefaultMenuItem* editCut = new DefaultMenuItem( "Cu&t\tCtrl+X", edit, standardMenu_);
	editCut->setAcceleratorKey( vkLetterX, kmCtrl );
	editCut->setTag( DocumentManager::atEditCut );

	DefaultMenuItem* editCopy = new DefaultMenuItem( "&Copy\tCtrl+C", edit, standardMenu_);
	editCopy->setAcceleratorKey( vkLetterC, kmCtrl );
	editCopy->setTag( DocumentManager::atEditCopy );

	DefaultMenuItem* editPaste = new DefaultMenuItem( "&Paste\tCtrl+V", edit, standardMenu_);
	editPaste->setAcceleratorKey( vkLetterV, kmCtrl );
	editPaste->setTag( DocumentManager::atEditPaste );

	separator = new DefaultMenuItem( "", edit, standardMenu_);
	separator->setSeparator( true );

	DefaultMenuItem* editPreferences = new DefaultMenuItem( "P&references...", edit, standardMenu_);
	editPreferences->setTag( DocumentManager::atEditPreferences );


	if ( NULL != app_ ) {

		DocumentManager::getAction( DocumentManager::atFileNew )->addTarget( fileNew );
		DocumentManager::getAction( DocumentManager::atFileOpen )->addTarget( fileOpen );
		DocumentManager::getAction( DocumentManager::atFileSave )->addTarget( fileSave );
		DocumentManager::getAction( DocumentManager::atFileSaveAs )->addTarget( fileSaveAs );
		DocumentManager::getAction( DocumentManager::atFileClose )->addTarget( fileClose );
		DocumentManager::getAction( DocumentManager::atEditUndo )->addTarget( editUndo );
		DocumentManager::getAction( DocumentManager::atEditRedo )->addTarget( editRedo );
		DocumentManager::getAction( DocumentManager::atEditCut )->addTarget( editCut );
		DocumentManager::getAction( DocumentManager::atEditCopy )->addTarget( editCopy );
		DocumentManager::getAction( DocumentManager::atEditPaste )->addTarget( editPaste );
		DocumentManager::getAction( DocumentManager::atEditPreferences )->addTarget( editPreferences );
	}

}




};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.4  2004/06/29 20:31:35  ddiego
*some minor fixes to the DocumentManager
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.2  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4.2.1  2004/04/10 04:37:19  ddiego
*added a MIMType class that parses mime types.
*
*Revision 1.4  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.4  2004/03/28 00:46:21  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.3.2.3  2004/03/24 21:28:49  ddiego
*minor change to document manager - added
*setCurrentDocument
*
*Revision 1.3.2.2  2004/03/24 04:51:24  ddiego
*empty
*
*Revision 1.3.2.1  2004/03/08 04:41:07  ddiego
*minor changes to DocumentManager - allow the use of
*Actions so that other UI elements can be added besides menu
*items (like Toolbar items)
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.17  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.2.2.16  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.2.2.15  2003/09/22 01:48:03  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.2.2.14  2003/09/19 21:24:21  ddiego
*small changes
*
*Revision 1.2.2.13  2003/09/19 04:12:01  ddiego
*added fix to docmanager
*added fix to handle path components with case insensitivity on Win32
*for file path transformation to relative paths
*
*Revision 1.2.2.12  2003/09/17 03:27:56  ddiego
*added a fix for bug [ 807416 ] CommonFileDialog needs setFileExtension
*added methods for getting data from the open and save dialogs in the
*DocumentManager
*
*Revision 1.2.2.11  2003/09/15 02:52:52  ddiego
*miscellaneous changes
*
*Revision 1.2.2.10  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.2.9  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.2.2.8  2003/09/04 21:49:48  ddiego
*minor changes
*
*Revision 1.2.2.7  2003/09/04 03:20:04  ddiego
**** empty log message ***
*
*Revision 1.2.2.6  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.2.2.5  2003/08/25 21:34:46  ddiego
*miscellaneous
*
*Revision 1.2.2.4  2003/08/25 16:47:03  ddiego
*mods to document manager and policy for closeDocumentWindow to return bool
*
*Revision 1.2.2.3  2003/08/25 03:46:38  ddiego
*some fixes to some of the stream impls
*
*Revision 1.2.2.2  2003/08/21 18:32:34  ddiego
**** empty log message ***
*
*Revision 1.2.2.1  2003/08/20 19:05:25  ddiego
*some minor changes to container logic
*
*Revision 1.2  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.5  2003/08/06 21:26:16  ddiego
*minor changes to doc stuff
*
*Revision 1.1.2.4  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.1.2.3  2003/07/21 03:08:29  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.1.2.2  2003/07/16 04:58:48  ddiego
*added some changes to the fil and stroke classes to allow changing whether
*they use anti-aliasing or not. Also implemented Matrix2D::invert(),
*plus properly implemented clone() on the DefaultMenuItem class.
*
*Revision 1.1.2.1  2003/07/06 01:20:29  ddiego
*added basic Document/View classes. These are based on the existing MVC
*architecture already present in the framework already, and exapnd on the
*existing functionality. Many of the ideas were influenced by the NeXT/Cocoa's
*Document/View architecture. Some of the new features are:
*  automatic creation and connection of the various parts including the
*  Document, view and Window.
*  Automatic default menu items, to ensure standard UI conformance. The menu
*  items are merged with an existing ones.
*  Automatic clipboard support in the form of cut/copy/paste and connecting this
*  directly to the current document
*  Support for Undo/Redo item as well, including default menu item validation
*  Default support for opening and saving documents, including presenting the
*  correct Dialogs to the User, and properly filling the default data, based
*  on the documents data.
*  Support for multiple document types
*  Support for differnt Document Interface policies. Currently we support
*  SDI (Single Document Interface) and MDI (Multiple Document Interface)
*
*/


#endif // _VCF_DOCUMENTMANAGER_H__


