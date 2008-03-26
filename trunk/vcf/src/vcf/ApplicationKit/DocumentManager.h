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

#ifndef _VCF_MENUMANAGER_H__
	#include "vcf/ApplicationKit/MenuManager.h"
#endif //_VCF_MENUMANAGER_H__



namespace VCF {


/**
\class DocumentInfo DocumentManager.h "vcf/ApplicationKit/DocumentManager.h"
Contains the string infos characterizing a document class or a kind of document.

	
	\li docClass   is the name for this class of documents.
	\li modelClass is the name for this class of documents.	
	\li viewClass        is the name identifying the kind of view to be associated to this kind of document.
	\li windowClass      is the name identifying the kind of window to be associated to this kind of document.
	\li fileTypes   is the list of allowed extension (separated by ';') for the files associated to this
                kind of document.
	\li mimetype    is the mime type for this kind of document.
	\li description is just a generic description for this class of documents.
*/
class APPLICATIONKIT_API DocumentInfo {
public:	
	String docClass;
	String modelClass;
	String viewClass;
	String windowClass;
	String fileTypes;
	MIMEType mimetype;
	String clipboardTypes;
	String description;
};



/**
\class DocManagerEvent DocumentManager.h "vcf/ApplicationKit/DocumentManager.h"
class DocManagerEvent

while a normal event is appropriated to notify the user interface
that a file operation has been performed on a document,
a user will need this special kind of event if he needs to bypass
a standard operation on documents as normally execute by the DocumentManager.
Even if the DocumentManager is already very flexible, this let the user
to have a comlete control in some case he may need ( very unfrequent though ).

This how this mechanism works:
this event class has two member functions that are normally supposed
to work togheter. Yet are normally *not* used.
Let's take the case of DocumentManager::saveFile() for example,
and imagine that the user needs to completely bypass the way saveFile works 
and adopt his personal implementation.
In order to do that he needs to add an handler to the manager, that is performing
the operation in hte way he needs. He will also have to setAllowFileOperation( false )
from inside this handler, and setFileOperationStatus( true ) whenever the saving 
operation has been completed successfuly.
The standard implementation of saveFile will then call the handler, collect that 
fileOperationStatus_ value and return it. See comment for setFileOperationStatus.

@see saveFile()
*/
class APPLICATIONKIT_API DocManagerEvent : public Event {
public:
	DocManagerEvent( Object* source, uint32 type ): Event( source, type ),
			allowFileOp_(true), fileOperationStatus_(false) {

	}

	/**
	* tells if we want to allow the DocumentManager to perform the standard file operation
	* that he has been requested.
	*@return bool, false if an event handler has caught this event and performed the file
	* operation in an alternative way.
	*/
	bool allowFileOperation() {
		return allowFileOp_;
	}

	/**
	* sets this flag as false from the event handler in order 
	* in order to make the manager aware that an alternative way,
	* implemented by the handler, is preferred.
	*/
	void setAllowFileOperation( const bool& val ) {
		allowFileOp_ = val;
	}

	/**
	* gets the status of a file operation after the event handler 
	* has been executed
	*/
	bool getFileOperationStatus() {
		return fileOperationStatus_;
	}

	/**
	* sets the status of a file operation from the event handler.
	* The value set with this function will be the value returned
	* by the DocumentManager's member function that was supposed to 
	* perform the standard implementation of this file operation.
	* Use setAllowFileOperation( false ) to make this function active.
	*@param const bool&, true if the file operation has been completed
	* successfully, false otherwise.
	*/
	void setFileOperationStatus( const bool& val ) {
		fileOperationStatus_ = val;
	}

protected:
	bool allowFileOp_;
	bool fileOperationStatus_;
};


typedef Delegate1<DocManagerEvent*> DocManagerDelegate;

/**
\class DocumentManager DocumentManager.h "vcf/ApplicationKit/DocumentManager.h"
The DocumentManager manages the interaction between the application (and any other
UI classes) and a collection of one or more documents.
A DocumentBasedApplication inherits from this class and from a DocInterfacePolicy
The DocInterfacePolicy is the template argument class that specifies
how the DocumentManager is supposed to manage the collection (of one or more) documents.
The member functions of this DocumentManager class are very general and common to any
kind document manager interface, and so it contributes to define the Document Interface 
pattern itself.
The DocumentManager allows only for a single instance, which you can get at by calling the
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
	/**
	* events types. See the DELEGATEs of this class.
	*/
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
		atEditPreferences,
		atLast,
	};

	/**
	* @delegate SaveFile this is called when the document manager's saveFile()
	* method is called from the UI. It implements the way used to bypass 
	* the normal behaviour of the document manager's saveFile() method itself.
	* It is effective only if a DocManagerEvent event handler is added to this 
	* delegate and setAllowFileOperation( false ) is called from the handler.
	* @event VCF::DocManagerEvent
	* @eventtype DocumentManager::dmSaveDocument
	* @see saveFile()
	*/
	DELEGATE(DocManagerDelegate,SaveFile);

	/**
	* @delegate OpenFile this is called when the document manager's openFile()
	* method is called from the UI. It implements the way used to bypass 
	* the normal behaviour of the document manager's openFile() method itself.
	* It is effective only if a DocManagerEvent event handler is added to this 
	* delegate and setAllowFileOperation( false ) is called from the handler.
	* @event VCF::DocManagerEvent
	* @eventtype  DocumentManager::dmOpenDocument
	* @see openFile()
	*/
	DELEGATE(DocManagerDelegate,OpenFile);

	/**
	* @delegate DocumentInitialized this is called after a newly created document has
	* been fully initialized by the document manager. At this point the document should
	* be connected to it's views (at least as many of them as the document manager knows
	* about), as well as having a window set for it.
	* @event VCF::Event
	* @eventtype DocumentManager::dmDocumentInitialized
	* @see Document::setWindow
	*/
	DELEGATE(DocManagerDelegate,DocumentInitialized)

	/**
	* @delegate DocumentClosed this fires to notify the user it is the time to
	* close the document. It is up to the implementer to add an event handler
	* to this delegate so to handle how to close the document and destroy it.
	* @event VCF::Event
	* @eventtype DocumentManager::dmCloseDocument
	*/
	DELEGATE(DocManagerDelegate,DocumentClosed)

	/**
	* @delegate CurrentDocumentChanged this is fired whenever the
	* currentDocumentChanged() method is called, to motify that 
	* the application has changed its active document.
	* It is the responsibility of the DocInterfacePolicy to call 
	* the currentDocumentChanged() method when appropriate.
	* An event fired from this delegate causes the UI to be notified of any changes
	* on any document so it can choose to display them or else.
	* @event VCF::Event
	* @eventtype DocumentManager::dmCurrentDocumentChanged
	*/
	DELEGATE(DocManagerDelegate,CurrentDocumentChanged)

public:
	DocumentManager();

	virtual ~DocumentManager();

	/**
	* inizialization function for document based applications.
	* This is called just after Application::initRunningApplication().
	*/
	virtual void init();

	/**
	* termination function for document based applications.
	* This is called just before Application::terminateRunningApplication().
	*/
	virtual void terminate();

	/**
	* gives the current document manager instance.
	* This is a singleton, so this function is static.
	*@return DocumentManager*, a pointer to the only DocumentManager for the application.
	*/
	static DocumentManager* getDocumentManager();


	/**
	* gets the current document.
	* The current document is the document having the focus, so to speak.
	* It is also called the active document, as the default operations
	* are performed on this one.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@return Document*, the currently active document.
	*/
	virtual Document* getCurrentDocument() {
		return NULL;
	}

	/**
	* sets the new current document.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param Document*, the document that we want to be active.
	*/
	virtual void setCurrentDocument( Document* newCurrentDocument ) {

	}

	/**
	* saves the specified document.
	*@param Document* doc, the document.
	*/
	bool saveDocument( Document* doc );

	/**
	* save a document into a file.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param Document* doc, the document.
	*@return bool, true if the operation completed successfully.
	*/
	virtual bool saveFile( Document* document ){
		return false;
	}

	/**
	* save a document into a file.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param Document* doc, the document.
	*@param const String& newFileName, the new destination filename. By default it is empty
	* so the user is prompted with a dialog.
	*@return bool, true if the operation completed successfully.
	*/
	virtual bool saveFileAs( Document* document, const String& newFileName=L"" ){
		return false;
	}

	/**
	* opens a document instance from a file.
	* the mime type identifying the document is extracted from
	* the file extension stored with all the DocumentInfo(s)
	* registered to the manager.
	* Afterward creating/opening the document, the file is 
	* actually loaded too.
	*@param const String&, the filename.
	*@return Document*, the opened document.
	*@see DocumentManager::getMimeTypeFromFileExtension()
	*@see Document::openFromType()
	*/
	virtual Document* openFromFileName( const String& fileName );

	/**
	* opens a file.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*/
	virtual void openFile() {
	
	};

	/**
	* close the current ( active ) document.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*/
	virtual void closeCurrentDocument(){
	
	};

	/**
	* reloads from the hard drive the file for an existing document.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param Document* doc, the document whose file needs to be reloaded.
	*@param const bool& keepPosition, true to reopen the file in the same
	* position as before. The default is true.
	*/
	virtual void reloadDocument( Document* document, const bool& keepPosition=true ) {

	};

	/**
	* this method is called to notify the application has changed
	* its active document, child or not.
	*/
	void currentDocumentChanged() {
		DocManagerEvent event( getCurrentDocument()->getModel(), DocumentManager::dmCurrentDocumentChanged );
		CurrentDocumentChanged( &event );
	}

	/**
	* creates a new document.
	* The default implementation is to create a default document
	* as this is what happens in a SDI policy ( where only one DocumentInfo
	* has been registered into this DocumentManager).
	* By overriding this function the user could change this default 
	* implementation and open an appropriate New File dialog.
	*/
	virtual void newDocument() {
		newDefaultDocument("", MIMEType());
	}

	/**
	* creates a new default document.
	* The mimetype of the document to be opened can be optionally specified.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param const String& mimetype, the mime type. Default is an empty String, as this 
	*function will be called only from a SDI policy.
	*in which case the only registered DocumentInfo is used to open the document.
	*@return Document*, the newly created document.
	*/
	virtual Document* newDefaultDocument( const String& fileName, const MIMEType& mimetype ) {
		return NULL;
	};

	/**
	* creates a new document with specified Document infos.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param const DocumentInfo& info, the characteristic infos of the document to be created.
	*@return Document*, the newly created document.
	*/
	virtual Document* createDocumentFromType( const DocumentInfo& info ){
		return NULL;
	};

	virtual Model* createModelFromType( const DocumentInfo& info ){
		return NULL;
	};

	/**
	* gets the appropriate window to be associated to a new document.
	* The standard implementation of a Document Interface is 
	* a one to one relationship between documents and windows.
	* The basic functionality is empty. The real implementation is dependent on the policy, 
	* as this is depending on the type of Document Interface.
	*@param const Document* doc, the document.
	*@param const DocumentInfo& info, the DocInfo to create the window from if necessary.
	*@return Window*, the window to be associated with the document.
	*/
	virtual Window* getWindowForNewDocument( Document* document, const DocumentInfo& info ) {
		return NULL;
	}

	/**
	*there is an internal association map between a mimeType and the DocumentInfo
	*this function adds an item to this map.
	*@param const String&, the mime type.
	*@param const DocumentInfo& info, the DocumentInfo.
	*/
	void addDocumentInfo( const MIMEType& mimeType, const DocumentInfo& info );

	/**
	* gets a pointer to the enumerator of all the registered DocumentInfo(s).
	*@param Enumerator<DocumentInfo>*, the pointer to this enumerator.
	*/
	Enumerator<DocumentInfo>* getRegisteredDocumentInfo();

	/**
	* gets the DocumentInfo of a document from its mime type only.
	*@param const String&, the mime type.
	*@return DocumentInfo, the document infos.
	*/
	DocumentInfo getDocumentInfo( const MIMEType& mimeType );

	/**
	* gets the mime type of a document from the extension of its associated file.
	*@param const String&, the filename.
	*@return String, the mime type.
	*/
	MIMEType getMimeTypeFromFileExtension( const String& fileName );

	/**
	* sets a specified view for a specified new document.
	* In this default implementation the window, previously 'assigned' 
	* to the document, becomes the view itself.
	* The DocumentInfo is also specified because in alternative 
	* implementations we may need to decide to select which view
	* will be associated to the document: the window could be the view 
	* itself or the control hosting the view instead.
	*@param DocumentInfo& info, the DocumentInfo.
	*@param View* view, the specified view.
	*@param Window* window, the window.
	*@param Document* newDocument, the new document.
	*/
	virtual void setNewView( const DocumentInfo& info, View* view, Window* window, Document* newDocument ) {
		view->setViewControl( window );
		window->setView( view );
		newDocument->addView( window );
	}


	/**
	* preferences support.
	* performs any editing operation on the application's preferences.
	* The basic functionality is empty. Override this to implement one.
	*/
	virtual void editPreferences(){
	
	};

	/**
	* tells if our Document manager is expected to have (create) a User Interface.
	*@return bool, true if it does.
	*/
	bool getShouldCreateUI() {
		return shouldCreateUI_;
	}

	/**
	* states if our Document manager should create a User Interface.
	*@param bool, true if we want to have it.
	*/
	void setShouldCreateUI( bool val ) {
		shouldCreateUI_ = val;
	}

	/**
	* attaches a document specific User Interface to a document.
	* using the appropriate DocumentInfo extracted from the mimeType.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*/
	virtual void attachUIToDocument( const String& mimeType, Document* document ) {
	
	};

	/**
	* gets a pointer to an enumerator of all the opened documents in the application.
	*@return Enumerator<Document*>* , the pointer to this enumerator.
	*/
	Enumerator<Document*>* getOpenedDocuments();


	/**
	* creates the menus associated to our document based application.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*/
	virtual void createMenus(){
	
	};

	/**
	* initializes the menu for the window associated to a document.
	* The DocumentInfo is also specified.
	* The basic functionality is empty. The real implementation is dependent on the policy.
	*@param DocumentInfo& info, the DocumentInfo.
	*@param Window* window, the window.
	*@param Document* document, the document.
	*/
	virtual void initializeWindowMenus( Window* window, Document* document, const DocumentInfo& info ) {
	
	}

	/**
	* gets the action associated to an action tag, as specified by this document manager.
	*@param ActionTag, the action's tag.
	*@return Action*, the pointer to the associated action.
	*@see Action
	*/
	Action* getAction( uint32 tag );

	/**
	* performs a cut operation on the document,
	* if the document allows for it.
	*@param Document* doc, the document.
	*/
	virtual void cutFromDocument( Document* doc );

	/**
	* performs a copy operation on the document,
	* if the document allows for it.
	*@param Document* doc, the document.
	*/
	virtual void copyFromDocument( Document* doc );

	/**
	* performs a paste operation on the document,
	* if the document allows for it.
	*@param Document* doc, the document.
	*/
	virtual void pasteToDocument( Document* doc );

	/**
	* performs an undo operation on the document.
	*@param Document* doc, the document.
	*/
	virtual void undoForDocument( Document* doc );

	/**
	* performs a redo operation on the document.
	*@param Document* doc, the document.
	*/
	virtual void redoForDocument( Document* doc );

	/**
	performs an undo operation using
	the shared undo-redo stack
	*/
	void undo();

	/**
	performs a redo operation using
	the shared undo-redo stack
	*/
	void redo();

	/**
	* gets the undo-redo stack associated with a document.
	*@param Document* doc, the document. If this is NULL
	then the function returns the default undo-redo 
	stack, that is "global" and not specific to a particular
	document.
	*@return UndoRedoStack&, a reference to the document's stack.
	*/
	UndoRedoStack& getUndoRedoStack( Document* doc );

	UndoRedoStack& getUndoRedoStack( Model* model );

	/**
	Returns the shared undo-redo stack for the document 
	manager.
	@return UndoRedoStack&, a reference to the document's stack.
	@see getUndoRedoStack()
	*/	
	UndoRedoStack& getSharedUndoRedoStack() {
		return getUndoRedoStack( (Document*)NULL );
	}

	void linkDocumentToModel( Document* document, Model* model );
	void unlinkDocumentToModel( Document* document );

	Document* getDocument( Model* model );
	Model* getModel( Document* document );

protected:

	/**
	* gives the document info associated to the document
	* this implementation uses the VCF RTTI for this document.
	*/
	DocumentInfo* getDocumentInfo( Document* doc );

	/** called to prepare a file open dialog */
	virtual void prepareOpenDialog( CommonFileOpenDialog* openDialog );

	/** called after the file open dialog has been closed by the user and confirmed Ok */
	virtual void openDialogFinished( CommonFileOpenDialog* openDialog ){};

	/** called to prepare a file save dialog */
	virtual void prepareSaveDialog( CommonFileSaveDialog* saveDialog, Document* doc );

	/** called after the file save dialog has been closed by the user and confirmed Ok */
	virtual void saveDialogFinished( CommonFileSaveDialog* saveDialog ){};

	/** called when this target gets notified for update events of the UI of a save operation */
	virtual void updateSave( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a saveAs operation */
	virtual void updateSaveAs( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a close operation */
	virtual void updateClose( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a cut operation */
	virtual void updateCut( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a copy operation */
	virtual void updateCopy( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a paste operation */
	virtual void updatePaste( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a undo operation */
	virtual void updateUndo( ActionEvent* event, Document* doc );

	/** called when this target gets notified for update events of the UI of a redo operation */
	virtual void updateRedo( ActionEvent* event, Document* doc );

	/** removes the undo redo stack from the specified document */
	void removeUndoRedoStackForDocument( Document* doc );

	/** called to save the changes done on a specified document */
	virtual UIToolkit::ModalReturnType saveChanges( Document* document );

	/** add an action to the internal action map */
	void addAction( uint32 tag, Action* action );

	/** called to add a document to the document based application */
	void addDocument( Document* document );

	/** called to remove a document from the document based application */
	void removeDocument( Document* document );


	typedef std::map<String,DocumentInfo> DocumentInfoMap;
	typedef std::map<Document*,UndoRedoStack*> DocumentUndoRedoMap;
	typedef std::map< uint32, Action* > ActionMap;
	typedef std::map<Document*,Model*> DocumentModelMap;

	/** 
	the only document manager instance for the application 
	*/
	static DocumentManager* docManagerInstance;

	/**
	The map of all registered DocumentInfo(s) 
	*/
	DocumentInfoMap docInfo_;
	EnumeratorMapContainer< DocumentInfoMap, DocumentInfo > docInfoContainer_;

	/**
	The list of all the opened document at this moment 
	*/
	Array<Document*> openDocuments_;

	/** 
	this DocumentManager has a User Interface 
	*/
	bool shouldCreateUI_;

	
	/**
	the map of all actions and their associated tags according 
	to our document manager 
	*/
	ActionMap actionsMap_;

	/** 
	the map of all undo redo stack associated to each document 
	*/
	DocumentUndoRedoMap undoRedoStack_;

	DocumentModelMap docModelMap_;
};



/**
\class DocumentManagerImpl DocumentManager.h "vcf/ApplicationKit/DocumentManager.h"
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
	virtual void closeCurrentDocument();

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
		closeCurrentDocument();
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

		if ( !DocInterfacePolicy::closeDocumentWindow( (Window*)e->getSource() ) ) {
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

					appDir.erase( appDir.length()-length, length );
					
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
			selectedFilter.erase( 0, 1 );
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
	String oldName = doc->getName();
	//set the name to the new file
	doc->setFileName( fp );
	try {
		result = doc->saveAsType( fp, fileType );

		//reset it back to the old name, we'll change it later
		doc->setFileName( oldName );
	}
	catch ( BasicException& e) {
		Dialog::showMessage( "Error saving '" + doc->getName() + "'\nError: " + e.getMessage() );
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

		Document* doc = openFromFileName( openDialog.getFileName() );

		openDialogFinished( &openDialog );
	}
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::closeCurrentDocument()
{
	//JC - I got rid of this because I beleive it is no longer 
	//neccessary
	/*closingDocument_ = true;

	Document* currentDoc = DocInterfacePolicy::getCurrentDocument();

	Component* owner = currentDoc->getOwner();
	if ( NULL != owner ) {
		owner->removeComponent( currentDoc );
	}
	documentClosedOK_ = false;
	// closes the current document window ( and so the window 
	// associated  to the just deleted document ).
	DocInterfacePolicy::closeDocument();


	// remove the current document form the list of opened documents
	// and frees it.
	removeDocument( currentDoc );	

	closingDocument_ = false;

	removeUndoRedoStackForDocument( currentDoc );

	currentDoc->free();

	documentClosedOK_ = false;
	*/

	DocInterfacePolicy::closeDocument();
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

	document->setWindow( window );
	window->addComponent( document );

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

	document->updateAllViews();
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
Document* DocumentManagerImpl<AppClass,DocInterfacePolicy>::newDefaultDocument( const String& fileName, const MIMEType& mimetype=MIMEType() )
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
							/* the user wanted to abort saving the previous document
							   no new document is created, and
								 we put the handler back to the unsaved document */
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
			types.erase(0,pos+1);
			pos = types.find(";");
		}
		if ( !types.empty() ) {
			newDocument->addSupportedClipboardFormat( types ) ;
		}

		if ( !fileName.empty() ) {
			newDocument->setFileName( fileName );
		}

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
			throw RuntimeException( "Unable to create document of type: \"" + info.docClass + "\"" );
		}

		if ( NULL == newModel ) {
			throw RuntimeException( "Unable to create model of type: \"" + info.modelClass + "\"" );
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
			objInstance = ClassRegistry::createNewInstanceFromClassID( info.docClass );
		}
		result = dynamic_cast<Document*>( objInstance );
		if ( NULL == result ) {
			objInstance->free();
		}
	}

	

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
Model* DocumentManagerImpl<AppClass,DocInterfacePolicy>::createModelFromType( const DocumentInfo& info ) {
	Model* result = NULL;

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
		objInstance->free();
	}

	return result;
}

template < typename AppClass, typename DocInterfacePolicy >
void DocumentManagerImpl<AppClass,DocInterfacePolicy>::createMenus() {
	Menu* standardMenu = MenuManager::getMainMenu();
	
	UIPolicyManager* mgr = UIToolkit::getUIPolicyManager();

	MenuItem* root = standardMenu->getRootMenuItem();
	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, standardMenu);

	DefaultMenuItem* fileNew = new DefaultMenuItem( "&New", file, standardMenu);

	AcceleratorKey::Value val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileNew);

	fileNew->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	fileNew->setTag( DocumentManager::atFileNew );


	DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open...", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileOpen);
	fileOpen->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	fileOpen->setTag( DocumentManager::atFileOpen );

	DefaultMenuItem* fileClose = new DefaultMenuItem( "Close", file, standardMenu);
	fileClose->setTag( DocumentManager::atFileClose );


	DefaultMenuItem* separator = new DefaultMenuItem( "", file, standardMenu);
	separator->setSeparator( true );


	DefaultMenuItem* fileSave = new DefaultMenuItem( "&Save", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileSave);
	fileSave->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	fileSave->setTag( DocumentManager::atFileSave );

	DefaultMenuItem* fileSaveAs = new DefaultMenuItem( "Save &As...", file, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saFileSaveAs);
	fileSaveAs->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	fileSaveAs->setTag( DocumentManager::atFileSaveAs );


	DefaultMenuItem* edit = new DefaultMenuItem( "&Edit", root, standardMenu);
	DefaultMenuItem* editUndo = new DefaultMenuItem( "&Undo", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditUndo);
	editUndo->setAcceleratorKey( val.getKeyCode(), val.getModifierMask()  );
	editUndo->setTag( DocumentManager::atEditUndo );

	DefaultMenuItem* editRedo = new DefaultMenuItem( "&Redo", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditRedo);
	editRedo->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	editRedo->setTag( DocumentManager::atEditRedo );

	separator = new DefaultMenuItem( "", edit, standardMenu);
	separator->setSeparator( true );

	DefaultMenuItem* editCut = new DefaultMenuItem( "Cu&t", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCut);
	editCut->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	editCut->setTag( DocumentManager::atEditCut );

	DefaultMenuItem* editCopy = new DefaultMenuItem( "&Copy", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditCopy);
	editCopy->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
	editCopy->setTag( DocumentManager::atEditCopy );

	DefaultMenuItem* editPaste = new DefaultMenuItem( "&Paste", edit, standardMenu);
	val = mgr->getStandardAcceleratorFor(UIPolicyManager::saEditPaste);
	editPaste->setAcceleratorKey( val.getKeyCode(), val.getModifierMask() );
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




};


#endif // _VCF_DOCUMENTMANAGER_H__

/**
$Id$
*/
