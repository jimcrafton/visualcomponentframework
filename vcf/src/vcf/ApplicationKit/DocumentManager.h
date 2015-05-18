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

#define REGISTERDOCTYPES "register"



class Document;



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
class APPLICATIONKIT_API FileTypeInfo {
public:	
	String extension;
	MIMEType mimeInfo;
};
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

	FileTypeInfo fileTypeAt( const size_t& index ) const ;
	String clipboardTypeAt( const size_t& index ) const ;

	std::vector<FileTypeInfo> getFileTypes() const;
	std::vector<String> getClipboardTypes() const;
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

	bool initFromApp( AbstractApplication* application );

	bool initFromPath( AbstractApplication* application );

	bool initFromResourceBundle( const String& resName, AbstractApplication* application );

	bool initFromStream( InputStream* stream, AbstractApplication* application );
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
	virtual bool closeCurrentDocument(){
		return false;
	};

	virtual bool closeDocument(Document* document, bool promptForSave ){
		return false;
	}

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
	void currentDocumentChanged();

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
	MIMEType getDocTypeFromFileExtension( const String& fileName );
	MIMEType getFileTypeFromFileExtension( const String& fileName );

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
	virtual void setNewView( const DocumentInfo& info, View* view, Window* window, Document* newDocument );


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


	virtual void createInitialUI() {}

	/**
	* gets the action associated to an action tag, as specified by this document manager.
	*@param ActionTag, the action's tag.
	*@return Action*, the pointer to the associated action.
	*@see Action
	*/
	Action* getAction( uint32 tag );

	void addActionTarget( uint32 tag, UIComponent* target );

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

	void addDropTarget( DropTarget* dropTarget );
	void cleanupDropTarget( Document* doc );
	
	/** called to add a document to the document based application */
	void addDocument( Document* document );

	/** called to remove a document from the document based application */
	void removeDocument( Document* document );

	virtual void openFromCommandLine(const CommandLine& comdLine){};

protected:

	/**
	* gives the document info associated to the document
	* this implementation uses the VCF RTTI for this document.
	*/
	DocumentInfo* getDocumentInfo( Document* doc );

	/** called to prepare a file open dialog */
	virtual void prepareOpenDialog( CommonFileOpenDialog* openDialog );

	/** called after the file open dialog has been closed by the user and confirmed Ok,  
	openedDoc represents the newly opend doc if successful, if NULL, then there was an 
	error opening the document*/
	virtual void openDialogFinished( CommonFileOpenDialog* openDialog, Document* openedDoc, const String& errString ){};

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

	


	typedef Array<DocumentInfo> DocumentInfoMap;
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

	std::vector<DropTarget*> dropTargets_;	
	Document* currentDragDocument_;

	

	void onDocWndEntered( DropTargetEvent* e );

	void onDocWndDragging( DropTargetEvent* e );

	void onDocWndDropped( DropTargetEvent* e );
};



};


#endif // _VCF_DOCUMENTMANAGER_H__

/**
$Id$
*/
