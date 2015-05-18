
#ifndef _VCF_DOCUMENTMANAGERIMPL_H__
#define _VCF_DOCUMENTMANAGERIMPL_H__
//DocumentManagerImpl.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_MENUMANAGER_H__
	#include "vcf/ApplicationKit/MenuManager.h"
#endif //_VCF_MENUMANAGER_H__


#ifndef _VCF_DOCUMENTMANAGER_H__
	#include "vcf/ApplicationKit/DocumentManager.h"
#endif //_VCF_DOCUMENTMANAGER_H__


namespace VCF {

	

/**
\class DocumentManagerImpl DocumentManagerImpl.h "vcf/ApplicationKit/DocumentManagerImpl.h"
* class DocumentManagerImpl
* implementation of the DocumentManager for which also the DocInterfacePolicy
* is specified.
* The DocInterfacePolicy is the template argument class that specifies
* how the DocumentManager is supposed to manage the collection (of one or more) documents.
* We can say than DocumentManagerImpl is the part of the DocumentManager 
* whose member functions are depending on the DocInterfacePolicy chosen by the user.
*/
template < typename AppClass, typename DocInterfacePolicy >
class DocumentManagerImpl : public DocumentManager, public DocInterfacePolicy {

public:
	DocumentManagerImpl(): 
		app_(NULL), closingDocument_(false), documentClosedOK_(false) {
	}

	/**
	* functions overrides with implementation depending on the DocInterfacePolicy.
	**/

	/**
	* inizialization function for document based applications.
	* This is called just after Application::initRunningApplication().
	*/
	virtual void init();

	/**
	* gets a pointer to the active document.
	*/
	virtual Document* getCurrentDocument() {
		return DocInterfacePolicy::getCurrentDocument();
	}

	/**
	* sets the given document as the active one.
	* Applies the policy's implemenation and send a change notification.
	*/
	virtual void setCurrentDocument( Document* newCurrentDocument ) {

		DocInterfacePolicy::setCurrentDocument(newCurrentDocument);

		VCF::DocumentManager::getDocumentManager()->currentDocumentChanged();
	}

	/**
	* save a document into a file.
	* the standard behaviour is simply save the file if it has been modified,
	* and to create a backup copy first if the document specifies to keep one.
	* If there is a problem with the destination directory, the user is prompted
	* with a dialog in order to specify an alternative location.
	* If we don't want this base behaviour, an event handler must be implemented
	* and added to the SaveFile delegate.
	*@param Document* doc, the document.
	*@return bool, true if the operation completed successfully.
	*@fire DocumentManager::SaveFile
	*@event DocManagerEvent
	*@eventtype DocumentManager::dmSaveDocument
	*/
	virtual bool saveFile( Document* document );

	/**
	* save a document into a file.
	* the standard behaviour is to show a dialog asking the user which file to open.
	* The user is prompted with a dialog if the destination filename is not specified
	* or if its directory does not exists.
	* If the document is saved, then a ModelChanged event with type Document::deSaved
	* is fired.
	* If we don't want this base behaviour, an event handler must be implemented
	* and added to the SaveFile delegate.
	*@param Document* doc, the document.
	*@param const String& newFileName, the new destination filename. By default it is empty
	* so the user is prompted with a dialog.
	*@return bool, true if the operation completed successfully.
	*@fire DocumentManager::SaveFile
	*@event DocManagerEvent
	*@eventtype DocumentManager::dmSaveDocument
	*@fire Model::ModelChanged
	*@event ModelEvent
	*@eventtype Document::deSaved
	*/
	virtual bool saveFileAs( Document* document, const String& newFileName=String( L"" ) );

	/**
	* opens a file.
	* the standard behaviour is to show a dialog asking the user which file to open.
	* If we don't want this base behaviour, an event handler must be implemented
	* and added to the SaveFile delegate.
	*@fire DocumentManager::OpenFile
	*@event DocManagerEvent
	*@eventtype DocumentManager::dmOpenDocument
	*/
	virtual void openFile();

	/**
	* closes the current document, and all its children if they exist
	* according to the policy.
	*/
	virtual bool closeCurrentDocument();

	virtual bool closeDocument(Document* document, bool promptForSave);

	/**
	* reloads a file for an existing document.
	* If the file is modified, the user is prompted to save it or not.
	* It the operation fails, the user is warned with a message,
	* but the document is not closed.
	*@param Document* doc, the document whose file needs to be reloaded.
	*@param const bool& keepPosition, true to reopen the file in the same
	* position as before. The default is true.
	*/
	virtual void reloadDocument( Document* document, const bool& keepPosition=true );

	/**
	* just creates the object from its type using the VCF RTTI
	* The info.classID is used first if available,
	* otherwise the info.className.
	*/
	virtual Document* createDocumentFromType( const DocumentInfo& info );

	virtual Model* createModelFromType( const DocumentInfo& info );

	/**
	* gets a window to be associated to the document just created.
	* This implementation just creates the associated window 
	* from its type using the VCF RTTI.
	* In a SDI policy the new window for the document is the main window.
	* In a MDI policy the new window for the document is simply a new window.
	* In an AdvancedMDIPolicy this implementation needs to be overriden.
	*/
	virtual Window* getWindowForNewDocument( Document* document, const DocumentInfo& info );

	/**
	* default procedures when creating a new document
	* <ul>
	*		<li>under SDI it saves the previous document if it was modified.
	*		<li>it creates a document instance according to the mimetype.
	*		<li>it calls the user implementation of Document::initNew()
	*		<li>it attaches a UI to the document if this getShouldCreateUI() is true.
	* </ul>
	*
	* this is normally called before actually opening the file for the document.
	*
	* In a SDI policy saveBeforeNewDocument() returns true so,
	* if we create a new document while the current document has been modified
	* the user is asked what to do, and the operation is aborted if the he decides to.
	*@fire DocumentInitialized, indirectly if attachUI() is called.
	*@see DocInterfacePolicy::saveBeforeNewDocument()
	*@see DocumentManagerImpl:: attachUI()
	*/
	virtual Document* newDefaultDocument( const String& fileName, const MIMEType& mimetype=MIMEType() );

	/**
	* attaches a document specific User Interface to a document
	* using the appropriate DocumentInfo extracted from the mimeType.
	* In this standard implementation:
	*   first it saves the current document if the policy requests this
	*   then it does the work of attaching the UI ( by calling attachUI ),
	*   finally it notifies the document has been changed.
	* The implementation is very similar to newDefaultDocument() with 
	* the difference that a document instance is already given.
	*@fire DocumentInitialized, indirectly if attachUI() is called.
	*@fire Document::ModelChanged
	*@event ModelEvent
	*@eventtype Document::deOpened
	*/
	virtual void attachUIToDocument( const String& mimeType, Document* document );

	/**
	* creates the standard menu for a document based application
	* and adds them as target to the appropriate action instances.
	* The menu follows a standard for all the OS.
	*/
	virtual void createMenus();

	/**
	* initializes the menu for the window associated to a document.
	* The DocumentInfo is also specified.
	* Initializes the appropriate menu for the document's window, 
	* by merging it with the application menu.
	*@param DocumentInfo& info, the DocumentInfo.
	*@param Window* window, the window.
	*@param Document* document, the document.
	*@see DocInterfacePolicy::mergeWindowMenus
	*/
	virtual void initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info  );

	virtual void createInitialUI();

	virtual void openFromCommandLine(const CommandLine& comdLine);
protected:
	/**
	* attaches a UI to the specified document
	*param const DocumentInfo& info, the infos about this document's class.
	*param Document* document, the document to attach the UI to.
	*@fire DocumentManager::DocumentInitialized
	*@event DocManagerEvent
	*@eventtype DocumentManager::dmDocumentInitialized
	* this event is fired after the UI has been attached to the given document;
	* it is useful for custom document initializations ( preferences ).
	*/
	void attachUI( const DocumentInfo& info, Document* document );

	/**
	* initializes the actions for the application.
	* These are tipical for any document based application.
	*/
	void initActions();

protected:
	/**
	* message handlers.
	* many of the associated events are called for the UI.
	**/

	/**
	* saves the current document, if it has been modified.
	*/
	virtual void onSave( Event* e ) {
		saveFile( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateSave( ActionEvent* e ) {
		updateSave( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* saves the current document, but let the user to specify
	* an alternative filename and type through a dialog box.
	*/
	virtual void onSaveAs( Event* e ) {
		Document* doc = DocInterfacePolicy::getCurrentDocument();

		saveFileAs( doc );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateSaveAs( ActionEvent* e ) {
		updateSaveAs( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* opens a document.
	*/
	virtual void onOpen( Event* e ) {
		openFile();
	}

	/**
	* closes a document.
	*/
	virtual void onClose( Event* e ) {
		//closeCurrentDocument();

		Document* doc = DocInterfacePolicy::getCurrentDocument();
		Window* window = NULL;
		if ( NULL != doc ) {
			window = doc->getWindow();			
		}
		DocInterfacePolicy::closeDocumentWindow( window );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateClose( ActionEvent* e ) {
		updateClose( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* creates a new document.
	*/
	virtual void onNew( Event* e ) {
		newDocument();
	}

	/**
	* let the user to change preferences.
	*/
	virtual void onPreferences( Event* e ) {
		editPreferences();
	}

	/**
	* handles notification that the user preferences has been changed
	*/
	virtual void onUpdatePreferences( ActionEvent* e ) {

	}

	/**
	* closes the document's window
	*/
	void onDocWindowClosing( FrameEvent* e ) {
		Window* window = (Window*)e->getSource();
		
		if ( !closeDocument( DocInterfacePolicy::getDocumentForWindow(window), true ) ) {
			e->setOkToClose( false );
		}
	}

	/**
	* activates a window and its document
	*/
	void onDocWindowActive( WindowEvent* e ) {
		Window* window = (Window*)e->getSource();

		if ( window->isActive() ) {
			DocInterfacePolicy::documentWindowActivated( window );
		}
	}

	/**
	Happens the first time after the window is created.
	This will activate the window and its document
	*/
	void onDocWindowCreated( Event* e ) {
		Window* window = (Window*)e->getSource();

		window->show();		
	}

	/**
	* handles notification that a document ( specified  by the event ) has been changed.
	* The UI will set the caption to the caption of modified document's window.
	*/
	void onDocModified( ModelEvent* e ) {
		Document* doc = (Document*)e->getSource();
		String caption = DocInterfacePolicy::getDocumentWindowCaption(doc);

		if ( caption != doc->getWindow()->getCaption() ) {
			doc->getWindow()->setCaption( caption );
		}
	}

	void onDocModelModified( ModelEvent* e ) {
		Model* model = (Model*)e->getSource();

		Document* doc = this->getDocument( model );

		String caption = DocInterfacePolicy::getDocumentWindowCaption(doc);

		if ( caption != doc->getWindow()->getCaption() ) {
			doc->getWindow()->setCaption( caption );
		}
	}

	/**
	* starts cut operation
	*/
	virtual void onCut( Event* e ) {
		cutFromDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateCut( ActionEvent* e ) {
		updateCut( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* starts copy operation
	*/
	virtual void onCopy( Event* e ) {
		copyFromDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateCopy( ActionEvent* e ) {
		updateCopy( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* starts paste operation
	*/
	virtual void onPaste( Event* e ) {
		pasteToDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdatePaste( ActionEvent* e ) {
		updatePaste( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* starts undo operation
	*/
	virtual void onUndo( Event* e ) {
		undoForDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateUndo( ActionEvent* e ) {
		updateUndo( e, DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* starts redo operation
	*/
	virtual void onRedo( Event* e ) {
		redoForDocument( DocInterfacePolicy::getCurrentDocument() );
	}

	/**
	* called when this target gets notified for update events
	*@see Action::update
	*/
	virtual void onUpdateRedo( ActionEvent* e ) {

		updateRedo( e, DocInterfacePolicy::getCurrentDocument() );
	}


protected:
	/** pointer to the application */
	AppClass* app_;

	bool closingDocument_;

	bool documentClosedOK_;
};





///////////////////////////////////////////////////////////////////////////////
// inlines

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
	action->Performed += new ClassProcedure1< Event*,AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onNew,
	                        "onNew" );
	addAction( DocumentManager::atFileNew, action );

	action = new Action();
	action->setName("FileOpen");
	action->Performed += new ClassProcedure1< Event*,AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onOpen,
	                        "onOpen" );
	addAction( DocumentManager::atFileOpen, action );

	action = new Action();
	action->setName("FileSave");
	action->Performed += new ClassProcedure1< Event*,AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onSave,
	                        "onSave" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateSave,
	                        "onUpdateSave" );
	addAction( DocumentManager::atFileSave, action );

	action = new Action();
	action->setName("FileSaveAs");
	action->Performed += new ClassProcedure1< Event*,AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onSaveAs,
	                        "onSaveAs" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateSaveAs,
	                        "onUpdateSaveAs" );
	addAction( DocumentManager::atFileSaveAs, action );

	action = new Action();
	action->setName("FileClose");
	action->Performed += new ClassProcedure1< Event*,AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onClose,
	                        "onClose" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateClose,
	                        "onUpdateClose" );
	addAction( DocumentManager::atFileClose, action );

	action = new Action();
	action->setName("EditUndo");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUndo,
	                        "onUndo" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateUndo,
	                        "onUpdateUndo" );
	addAction( DocumentManager::atEditUndo, action );

	action = new Action();
	action->setName("EditRedo");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onRedo,
	                        "onRedo" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateRedo,
	                        "onUpdateRedo" );
	addAction( DocumentManager::atEditRedo, action );


	action = new Action();
	action->setName("EditCut");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onCut,
	                        "onCut" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateCut,
	                        "onUpdateCut" );

	addAction( DocumentManager::atEditCut, action );

	action = new Action();
	action->setName("EditCopy");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onCopy,
	                        "onCopy" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdateCopy,
	                        "onUpdateCopy" );

	addAction( DocumentManager::atEditCopy, action );


	action = new Action();
	action->setName("EditPaste");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onPaste,
	                        "onPaste" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdatePaste,
	                        "onUpdatePaste" );

	addAction( DocumentManager::atEditPaste, action );


	action = new Action();
	action->setName("EditPreferences");
	action->Performed += new ClassProcedure1< Event*, AppClass >( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onPreferences,
	                        "onPreferences" );
	action->Update += new ClassProcedure1<ActionEvent*,AppClass>( app_,
	                        &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onUpdatePreferences,
	                        "onUpdatePreferences" );

	addAction( DocumentManager::atEditPreferences, action );

}


template < typename AppClass, typename DocInterfacePolicy >
bool DocumentManagerImpl<AppClass,DocInterfacePolicy>::saveFile( Document* doc )
{
	bool result = false;

	if ( NULL == doc ) {
		return false;
	}

	if ( doc->isModified() ) {

		FilePath fp = doc->getFileName();

		FilePath tmpName;
		if ( File::exists( fp ) ) {
			//save back up first
			File backup( fp );
			String tmp = fp.getPathName(true);
			tmp += "~" + fp.getBaseName() + ".tmp";
			tmpName = tmp;
			backup.copyTo( tmpName );
		}

		result = saveFileAs( doc, fp );

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
bool DocumentManagerImpl<AppClass,DocInterfacePolicy>::saveFileAs( Document* doc, const String& newFileName )
{
	bool result = false;

	if ( NULL == doc ) {
		return false;
	}

	/**
	* allow the base behaviour to be bypassed if necessary.
	*@see DocManagerEvent
	*/
	DocManagerEvent event( doc, DocumentManager::dmSaveDocument );
	SaveFile( &event );
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


	// prompts the user with a dialog if the destination filename is empty
	// or if its directory does not exists.
	bool prompt = false;

	FilePath fp = newFileName;
	if ( newFileName.empty() ) {
		fp = doc->getFileName();
		prompt = true;
	}

	String currentDir = fp.getPathName(true);
	if ( !prompt && !File::exists( currentDir ) ) {
		prompt = true;
	}

	if ( prompt ) {

		String basename = fp.getBaseName(true);

		if ( currentDir.empty() ) {
			currentDir = System::getCurrentWorkingDirectory();
		}
		else {
			if ( !File::exists( currentDir ) ) {
				// we look for the first existing parent directory
				String appDir = currentDir;
				std::vector<String> pathComponents = fp.getPathComponents();
				std::vector<String>::reverse_iterator it = pathComponents.rbegin();

				bool found = false;
				while ( it != pathComponents.rend() ) {
					String s = (*it);
					size_t length = (*it).length();// + FilePath::getDirectorySeparator().length();

					appDir = appDir.erase( appDir.length()-length, length );
					
					if ( File::exists( appDir ) ) {
						found = true;
						break;
					}

					it ++;
				}

				if ( found ) {
					currentDir = appDir;
				}
				else {
					currentDir = System::getCurrentWorkingDirectory();
				}
			}
		}

		CommonFileSaveDialog saveDialog( doc->getWindow(), currentDir );

		saveDialog.setFileName( currentDir + basename );
		prepareSaveDialog( &saveDialog, doc );
		saveDialog.addFilter( "All files", "*.*" );
		if ( saveDialog.execute() ) {

			saveDialogFinished( &saveDialog );

			fp = saveDialog.getFileName();

			// adds the filter's extension if specified but missing from the filename
			String selectedFilter = saveDialog.getSelectedFilter();
			selectedFilter = selectedFilter.erase( 0, 1 );
			if ( ( !selectedFilter.empty() ) && ( selectedFilter != L".*" ) && 
			     ( selectedFilter != fp.getExtension() ) ) {
				fp = fp + selectedFilter;
			}
		}
		else {

			return false;
		}
	}

	if ( fileType.empty() ) {
		fileType = fp.getExtension();
	}

	//store off the current name
	String oldName = doc->getTitle();
	//set the name to the new file
	doc->setFileName( fp );
	try {

		fileType = getFileTypeFromFileExtension( fp );

		result = doc->saveAsType( fp, fileType );

		//reset it back to the old name, we'll change it later
		doc->setFileName( oldName );
	}
	catch ( BasicException& e) {
		Dialog::showMessage( "Error saving '" + doc->getTitle() + "'\nError: " + e.getMessage() );
		result = false;
	}

	if ( result ) {
		doc->setModified(false); // it already is, we just make sure.
		doc->setFileName( fp );

		// notifies the UI that the document has changed name
		DocumentEvent e( doc, Document::deSaved );
		doc->DocumentChanged( &e );
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::openFile()
{
	Document* doc = DocInterfacePolicy::getCurrentDocument();

	/**
	* allow the base behaviour to be bypassed if necessary.
	*@see DocManagerEvent
	*/
	DocManagerEvent event( NULL, DocumentManager::dmOpenDocument );
	OpenFile( &event );
	if ( !event.allowFileOperation() ) {
		return;
	}

	String currentDir = System::getCurrentWorkingDirectory();

	CommonFileOpenDialog openDialog( Frame::getActiveFrame(), currentDir );

	prepareOpenDialog( &openDialog );



	if ( openDialog.execute() ) {

		Document* doc = NULL;
		String errMsg;
		try {
			doc = openFromFileName( openDialog.getFileName() );
		}		
		catch(const BasicException& e) {
			doc = NULL;
			errMsg = e.getMessage();
		}
		catch(...) {
			doc = NULL;
			errMsg = "Unknown error occurred while attempting to open the document.";
		}

		openDialogFinished( &openDialog, doc, errMsg );
	}
}

template < typename AppClass, typename DocInterfacePolicy >
bool DocumentManagerImpl<AppClass,DocInterfacePolicy>::closeDocument(Document* document, bool promptForSave)
{
	
	if ( NULL != document ) {

		if ( document->isModified() && promptForSave ) {
			if ( !VCF::DocumentManager::getDocumentManager()->saveDocument( document ) ) {
				return false;
			}
		}
		Window* window = document->getWindow();
		VCF::DocManagerEvent event( document->getModel(), VCF::DocumentManager::dmCloseDocument );
		
		VCF::DocumentManager::getDocumentManager()->DocumentClosed( &event );

		cleanupDropTarget( document );	
		removeDocument( document );
		removeUndoRedoStackForDocument( document );
	}

	DocInterfacePolicy::closeDocument( document );

	return true;
}

template < typename AppClass, typename DocInterfacePolicy >
bool DocumentManagerImpl<AppClass,DocInterfacePolicy>::closeCurrentDocument()
{
	Document* currentDoc = DocInterfacePolicy::getCurrentDocument();	

	return closeDocument( currentDoc, true );
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::reloadDocument( Document* document, const bool& keepPosition )
{
	// returns if the user doesn't want to save the changes.
	if ( !saveDocument( document ) ) {
		return;
	};

	String fileName = document->getFileName();

	//String mimetype = app->getMimeTypeFromFileExtension( fileName );
	//String mimetype = getDocumentMimeType( document );

	String mimeType;
	String fileTypes;

	DocumentInfo* info = getDocumentInfo( document );
	if ( NULL != info ) {
		mimeType = info->mimetype;
		fileTypes = info->fileTypes;
	}
	//VCF_ASSERT( !mimetype.empty() );

	document->openFromType( fileName, mimeType );

	// reset the undo/redo stack
	getUndoRedoStack( document).clearCommands();
}

template < typename AppClass, typename DocInterfacePolicy >
Window* DocumentManagerImpl<AppClass,DocInterfacePolicy>::getWindowForNewDocument( Document* document, const DocumentInfo& info )
{
	Window* result;

	if ( DocInterfacePolicy::usesMainWindow() ) {
		// in a SDI policy the new window for the document is the main window
		if ( NULL == app_->getMainWindow() ) {


			result = Frame::createWindow( ClassRegistry::getClass(info.windowClass) );

			if ( NULL == result ) {
				
				if ( info.windowClass.empty() ) {
					result = new Window();
				}
				else {
					Object* windowObj = ClassRegistry::createNewInstance( info.windowClass );
					result = dynamic_cast<Window*>(windowObj);
				}
			}
			app_->setMainWindow( result );
		}
		else {
			result = app_->getMainWindow();
		}
	}
	else {
		// in a MDI policy the new window for the document is a new window		
		
		if ( !info.windowClass.empty() ) {
			result = Frame::createWindow( ClassRegistry::getClass(info.windowClass) );
			if ( NULL == result ) {			
				//probably not a resource based window, try just creating the window class
				Object* windowObj = ClassRegistry::createNewInstance( info.windowClass );
				result = dynamic_cast<Window*>(windowObj);
			}
		}
		else {
			result = new Window();
		}

		if ( NULL != result ) {
			app_->addComponent(result);
		}
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info )
{
	/* if the window has no menu yet, we need to have one */
	if ( NULL == window->getMenuBar() ) {
		MenuBar* menu = new MenuBar();
		window->setMenuBar(menu);
		window->addComponent( menu );
	}

	DocInterfacePolicy::mergeWindowMenus( MenuManager::getMainMenu(), window->getMenuBar() );
}


template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::attachUI( const DocumentInfo& info, Document* document )
{
	Window* window = NULL;

	CallBack* docEv = app_->getCallback("onDocModified");

	window = getWindowForNewDocument( document, info );

	initializeWindowMenus( window, document, info );

	if ( NULL != document ) {
		document->setWindow( window );
		window->addComponent( document );
	}	

	DropTarget* dropTarget = new DropTarget(window);

	CallBack* cb = app_->getCallback( "onDocWndEntered" );
	if ( cb == NULL ) {
		cb =
		new ClassProcedure1<DropTargetEvent*, AppClass>( app_, &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWndEntered, "onDocWndEntered" );
	}

	dropTarget->DropTargetEntered += cb;

	cb = app_->getCallback( "onDocWndDragging" );
	if ( cb == NULL ) {
		cb =
		new ClassProcedure1<DropTargetEvent*, AppClass>( app_, &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWndDragging, "onDocWndDragging" );
	}

	dropTarget->DropTargetDraggingOver += cb;

	cb = app_->getCallback( "onDocWndDropped" );
	if ( cb == NULL ) {
		cb =
		new ClassProcedure1<DropTargetEvent*, AppClass>( app_, &DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWndDropped, "onDocWndDropped" );
	}

	dropTarget->DropTargetDropped += cb;

	addDropTarget( dropTarget );


	if ( NULL != document ) {
		if ( NULL == docEv ) {

			docEv = new ClassProcedure1<ModelEvent*,AppClass >( app_,
						&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocModified,
						"onDocModified" );
		}

		document->DocumentChanged += docEv;

		docEv = app_->getCallback("onDocModelModified");
		if ( NULL == docEv ) {

			docEv = new ClassProcedure1<ModelEvent*,AppClass >( app_,
						&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocModelModified,
						"onDocModelModified" );
		}	

		document->getModel()->ModelChanged += docEv;
	

		/**
		create a view from the DocInfo if necessary
		*/
		View* view = NULL;
		if ( !info.viewClass.empty() ) {
			if ( info.windowClass != info.viewClass ) {
				Object* viewObject = NULL;
				viewObject = ClassRegistry::createNewInstance( info.viewClass );

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
				// sets a child view for the document inside the window
				setNewView( info, view, window, document );
			}
		}

		//need to provide a common place to
		//init everything once all the "connections" are in place	

		DocManagerEvent event( document, DocumentManager::dmDocumentInitialized );

		DocumentInitialized( &event );

		// let the policy to update its data to the new document
		DocInterfacePolicy::afterNewDocument( document );
	}


	// makes sure the Frame has an handler to 
	// to catch if the document's window is to be closing
	CallBack* newEv = app_->getCallback("onDocWindowClosing");
	if ( NULL == newEv ) {

		newEv = new ClassProcedure1< FrameEvent*,AppClass >( app_,
					&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWindowClosing,
					"onDocWindowClosing" );
	}
	window->FrameClosing += newEv;

	// makes sure the window has an handler to catch if the document's window has been activated
	newEv = app_->getCallback("onDocWindowActive");
	if ( NULL == newEv ) {

		newEv = new ClassProcedure1< WindowEvent*,AppClass >( app_,
					&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWindowActive,
					"onDocWindowActive" );
	}
	window->FrameActivation += newEv;

	newEv = app_->getCallback("onDocWindowCreated");
	if ( NULL == newEv ) {

		newEv = new ClassProcedure1<Event*,AppClass>( app_, 
							&DocumentManagerImpl<AppClass,DocInterfacePolicy>::onDocWindowCreated,
							"onDocWindowCreated" );
	}

	window->ComponentCreated += newEv;

	if ( NULL != document ) {
		setCurrentDocument(document);
		document->updateAllViews();
	}
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::attachUIToDocument( const String& mimeType, Document* document )
{
	Window* window = NULL;

	DocumentInfo info = getDocumentInfo( mimeType );

	// this handler notifies the UI to display any changes on the document
	CallBack* docEv = app_->getCallback("onDocModified");

	// see DocumentManagerImpl::newDefaultDocument() for explanation
	if ( DocInterfacePolicy::saveBeforeNewDocument() ) {
		Document* doc = DocInterfacePolicy::getCurrentDocument();
		if ( NULL != doc ) {
			doc->DocumentChanged -= docEv;
			if ( doc->isModified() ) {
				switch ( saveChanges( doc ) ) {
					case UIToolkit::mrCancel : {
						doc->DocumentChanged += docEv;
						return ;
					}
					break;
				}
			}
		}
	}

	// creates or activates a window for it, and fires event for custom initializations.
	attachUI( info, document );

	// after the document has been created, we notify that it has
	// been changed, so the UI can updates itself.
	DocumentEvent e( document, Document::deOpened );
	document->DocumentChanged( &e );
}

template < typename AppClass, typename DocInterfacePolicy >
Document* DocumentManagerImpl<AppClass,DocInterfacePolicy>::newDefaultDocument( const String& fileName, const MIMEType& mimetype )
{
	/**
	* if we create a new document while the current document of 
	* the same type has been modified, we need to ask the user 
	* what to do and abort the operation if the user wants to.
	*/

	DocumentInfo info = getDocumentInfo( mimetype );

	Window* window = NULL;

	// this handler notifies the UI to display any changes on the document
	CallBack* docEv = app_->getCallback("onDocModified");

	if ( DocumentManager::getShouldCreateUI() ) {		
		if ( DocInterfacePolicy::saveBeforeNewDocument() ) {
			// only in a SDI policy

			Document* doc = DocInterfacePolicy::getCurrentDocument();
			if ( NULL != doc ) {
				// we remove this handler as we don't want the UI to display any changes at this point
				doc->DocumentChanged -= docEv;
				if ( doc->isModified() ) {
					// a dialog is shown to the user asking him to save the changes 
					// of the current document previously modified
					switch ( saveChanges( doc ) ) {
					case UIToolkit::mrCancel : {
							// the user wanted to abort saving the previous document
							//   no new document is created, and
							//	 we put the handler back to the unsaved document 
							doc->DocumentChanged += docEv;
							return NULL;
						}
						break;
					}
				}
			}
		}		
	}


	// just creates the object from its type using the VCF RTTI
	Document* newDocument = createDocumentFromType( info );
	Model* newModel = createModelFromType( info );


	if ( NULL != newDocument && NULL != newModel ) {

		newDocument->setModel( newModel );
		newDocument->addComponent( newModel );

		String types = info.clipboardTypes;
		size_t pos = types.find(";");
		while ( pos != String::npos ) {
			newDocument->addSupportedClipboardFormat( types.substr(0,pos) ) ;
			types = types.erase(0,pos+1);
			pos = types.find(";");
		}
		if ( !types.empty() ) {
			newDocument->addSupportedClipboardFormat( types ) ;
		}

		if ( !fileName.empty() ) {
			newDocument->setFileName( fileName );
		}

		addDocument( newDocument );

		// calls user implementation
		newDocument->initNew();

		if ( DocumentManager::getShouldCreateUI() ) {
			// creates or activates a window for it, and fires event for custom initializations.
			attachUI( info, newDocument );
		}	
	}
	else {
		//throw exception !
		if ( NULL == newDocument ) {
			throw RuntimeException( "Unable to create document of type: \"" + info.docClass + "\".\nCheck the applications resource .xml file for a valid DocumentClass entry with valid class name, \nand make sure that the class is registered with the VCF ClassRegistry." );
		}

		if ( NULL == newModel ) {
			throw RuntimeException( "Unable to create model of type: \"" + info.modelClass + "\". \nCheck the applications resource .xml file for a valid ModelClass entry with valid class name, \nand make sure that the class is registered with the VCF ClassRegistry." );
		}
	}
	

	

	return newDocument;
}


template < typename AppClass, typename DocInterfacePolicy >
Document* DocumentManagerImpl<AppClass,DocInterfacePolicy>::createDocumentFromType( const DocumentInfo& info ) {
	Document* result = NULL;

	
	if ( info.docClass.empty() ) {
		result = new Document();
	}
	else {
		Class* clazz = NULL;
		Object* objInstance = NULL;
		try {
			objInstance = ClassRegistry::createNewInstance( info.docClass );
		}
		catch (...) {
			try {
				objInstance = ClassRegistry::createNewInstanceFromClassID( info.docClass );
			}
			catch (...) {		
				objInstance = new Document();
			}
		}
		result = dynamic_cast<Document*>( objInstance );
		if ( NULL == result ) {
			delete objInstance;
		}
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
Model* DocumentManagerImpl<AppClass,DocInterfacePolicy>::createModelFromType( const DocumentInfo& info ) {
	Model* result = NULL;

	if ( !info.modelClass.empty() ) {
		Class* clazz = NULL;
		Object* objInstance = NULL;
		try {
			objInstance = ClassRegistry::createNewInstance( info.modelClass );
		}
		catch (...) {
			objInstance = ClassRegistry::createNewInstanceFromClassID( info.modelClass );
		}
		
		result = dynamic_cast<Model*>( objInstance );
		if ( NULL == result ) {
			delete objInstance;
		}
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::createInitialUI()
{
	if ( DocInterfacePolicy::createDefaultUI() ) {
		attachUI( getDocumentInfo( MIMEType("") ), NULL );
	}
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::createMenus() {
	Menu* standardMenu = MenuManager::getMainMenu();
	
	UIPolicyManager* mgr = UIToolkit::getUIPolicyManager();

	MenuItem* root = standardMenu->getRootMenuItem();
	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, standardMenu);

	DefaultMenuItem* fileNew = new DefaultMenuItem( "&New", file, standardMenu);

	AcceleratorKey::Value val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileNew);

	fileNew->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	fileNew->setTag( DocumentManager::atFileNew );


	DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open...", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileOpen);
	fileOpen->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	fileOpen->setTag( DocumentManager::atFileOpen );

	DefaultMenuItem* fileClose = new DefaultMenuItem( "Close", file, standardMenu);
	fileClose->setTag( DocumentManager::atFileClose );


	DefaultMenuItem* separator = new DefaultMenuItem( "", file, standardMenu);
	separator->setSeparator( true );


	DefaultMenuItem* fileSave = new DefaultMenuItem( "&Save", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileSave);
	fileSave->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	fileSave->setTag( DocumentManager::atFileSave );

	DefaultMenuItem* fileSaveAs = new DefaultMenuItem( "Save &As...", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileSaveAs);
	fileSaveAs->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	fileSaveAs->setTag( DocumentManager::atFileSaveAs );


	DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, standardMenu);
	DefaultMenuItem* editUndo = new DefaultMenuItem( "&Undo", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditUndo);
	editUndo->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask()  );
	editUndo->setTag( DocumentManager::atEditUndo );

	DefaultMenuItem* editRedo = new DefaultMenuItem( "&Redo", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditRedo);
	editRedo->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	editRedo->setTag( DocumentManager::atEditRedo );

	separator = new DefaultMenuItem( "", edit, standardMenu);
	separator->setSeparator( true );

	DefaultMenuItem* editCut = new DefaultMenuItem( "Cu&t", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCut);
	editCut->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	editCut->setTag( DocumentManager::atEditCut );

	DefaultMenuItem* editCopy = new DefaultMenuItem( "&Copy", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCopy);
	editCopy->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	editCopy->setTag( DocumentManager::atEditCopy );

	DefaultMenuItem* editPaste = new DefaultMenuItem( "&Paste", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditPaste);
	editPaste->setAcceleratorKeyInfo( val.getKeyCode(), val.getModifierMask() );
	editPaste->setTag( DocumentManager::atEditPaste );

	separator = new DefaultMenuItem( "", edit, standardMenu);
	separator->setSeparator( true );

	DefaultMenuItem* editPreferences = new DefaultMenuItem( "P&references...", edit, standardMenu);
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


template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::openFromCommandLine(const CommandLine& comdLine)
{
	size_t argc = comdLine.getArgCount();
	
	if ( argc > 1 ) {
		String docFileName = comdLine.getArgument(1);
		
		openFromFileName( docFileName );
	}
	else if( DocInterfacePolicy::createInitialDocument() ){
		newDefaultDocument("", VCF::MIMEType() );
	}
}

};


#endif //_VCF_DOCUMENTMANAGERIMPL_H__