//DocumentManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"

#ifndef _VCF_MESSAGEDIALOG_H__
#	include "vcf/ApplicationKit/MessageDialog.h"
#endif // _VCF_MESSAGEDIALOG_H__

#include "vcf/FoundationKit/PropertyListing.h"
#include "vcf/FoundationKit/StringTokenizer.h"


using namespace VCF;





std::vector<FileTypeInfo> DocumentInfo::getFileTypes() const
{
	std::vector<FileTypeInfo> result;
	
	StringTokenizer tok(fileTypes, ";");
	std::vector<String> elements;
	tok.getElements( elements );
	
	VCF_ASSERT( elements.size() % 2 == 0 );

	
	if ( elements.size() % 2 == 0 ) {
		result.resize( elements.size()/2 );

		for ( size_t i=0;i<elements.size()/2; i ++ ) {
			result[i].extension = elements[i*2];
			result[i].mimeInfo = elements[i*2+1];
		}
	}

	return result;
}

std::vector<String> DocumentInfo::getClipboardTypes() const
{	
	std::vector<String> result;

	StringTokenizer tok(clipboardTypes, ";");
	tok.getElements( result );

	return result;
}

FileTypeInfo DocumentInfo::fileTypeAt( const size_t& index ) const 
{
	return getFileTypes().at( index );
}

String DocumentInfo::clipboardTypeAt( const size_t& index ) const 
{
	return getClipboardTypes().at( index );
}




DocumentManager* DocumentManager::docManagerInstance = NULL;

DocumentManager::DocumentManager():
	shouldCreateUI_(true),
		currentDragDocument_(NULL)
{
	DocumentManager::docManagerInstance = this;
	docInfoContainer_.initContainer( docInfo_ );		
}




DocumentManager::~DocumentManager()
{
}

Enumerator<DocumentInfo>* DocumentManager::getRegisteredDocumentInfo()
{
	return docInfoContainer_.getEnumerator();
}


void DocumentManager::init()
{
	Application* app = Application::getRunningInstance();
	
	
	Resource* res = app->getResourceBundle()->getResource( app->getName() + ".xml" );
	if ( NULL != res ) {

		PropertyListing properties;
		BasicInputStream bis( (const uchar*)res->getData(), res->getDataSize() );

		bis >> &properties;


		const VariantArray& docTypes = properties.getArray( "DocumentTypes" );
		for (size_t i=0;i<docTypes.data.size();i++ ) {
			const PropertyListing& dict =  (const PropertyListing&)(const Object&) docTypes.data[i];
			
			if ( !dict.keyExists("TypeExtensions") ) {
				throw RuntimeException( "Invalid Document Info file - missing 'TypeExtensions' key" );
			}

			if ( !dict.keyExists("TypeContent") ) {
				throw RuntimeException( "Invalid Document Info file - missing 'TypeContent' key" );
			}

			const VariantArray& extensions = dict.getArray( "TypeExtensions" );
			const VariantArray& typeContents = dict.getArray( "TypeContent" );

			VCF_ASSERT( extensions.data.size() == typeContents.data.size() );

			if ( extensions.data.size() != typeContents.data.size() ) {
				throw RuntimeException( "Invalid Document Info file - 'TypeContent' and 'TypeExtensions' array sizes don't match" );
			}


			if ( !dict.keyExists("ClipboardTypeContent") ) {
				throw RuntimeException( "Invalid Document Info file - missing 'ClipboardTypeContent' key" );
			}
			const VariantArray& clipboardTypes = dict.getArray( "ClipboardTypeContent" );

			String icoFile = dict["TypeIcon"];

			size_t pos = icoFile.find("@");
			if ( pos != String::npos ) {
				icoFile.erase( 0, pos+1);

				icoFile = app->getFileName() + "," + icoFile;
			}
			else {
				icoFile = System::findResourceDirectory() + icoFile;
			}
			
			DocumentInfo info;
			info.mimetype = (String)dict["DocTypeContent"];
			info.description = (String)dict["TypeDescription"];
			info.windowClass = (String)dict["DocumentWindow"];
			info.viewClass = (String)dict["DocumentView"];
			info.docClass = (String)dict["DocumentClass"];
			info.modelClass = (String)dict["ModelClass"];
			
			

			for (size_t k=0;k<clipboardTypes.data.size();k++ ) {
				String type = clipboardTypes.data[k];

				if ( k > 0 ) {
					info.clipboardTypes += ";";
				}
				info.clipboardTypes += type;				
			}

			//register type(s)
			UIShell* shell = UIShell::getUIShell();
			for (size_t j=0;j<extensions.data.size();j++ ) {
				String ext = extensions.data[j];
				String mime = typeContents.data[j];
				

				FileAssociationInfo fa;
				fa.extension = ext;
				fa.mimeType = mime;
				fa.documentClass = app->getName() + ".";
				if ( !info.docClass.empty() ) {
					fa.documentClass += info.docClass;
				}
				else {
					fa.documentClass += info.modelClass;
				}
				fa.documentDescription = info.description;
				fa.documentIconPath = icoFile;
				fa.launchingProgram = app->getFileName();

				shell->createFileAssociation( fa, false );				

				if ( j > 0 ) {
					info.fileTypes += ";";
				}
				info.fileTypes += ext;
				info.fileTypes += ";" + mime;
			}


			docInfo_[info.mimetype] = info;
		}

		delete res;
	}
	else {
		throw RuntimeException( "You need to have a resource file named \"" + app->getName() + ".xml\" with the correct data in it."  );
	}
}

void DocumentManager::terminate() {	

	std::vector<Document*>::iterator it2 = openDocuments_.begin();
	while ( it2 != openDocuments_.end() ) {
		Document* document = *it2;
		if ( NULL == document->getOwner() ) {
			document->free();
		}
		it2 ++;
	}


	DocumentUndoRedoMap::iterator it = undoRedoStack_.begin();
	while ( it != undoRedoStack_.end() ) {
		delete it->second;
		it ++;
	}
	undoRedoStack_.clear();
}


void DocumentManager::cutFromDocument( Document* doc ) {
	DataObject* data = doc->cut();
	if ( NULL == data ) {
		//serialize the whole document and clear it
		BasicOutputStream bos;
		DocumentInfo* info = getDocumentInfo( doc );
		if ( NULL != info ) {
			if ( doc->saveAsType( info->mimetype, bos ) ) {
				data = new DataObject();
				BinaryPersistable* persistable = new BinaryPersistable( (const unsigned char*)bos.getBuffer(), bos.getSize() );
				data->addSupportedDataType( info->mimetype, persistable );


				//clear out the doc
				doc->empty();
			}
		}
	}

	if ( NULL != data ) {
		Clipboard* clipboard = UIToolkit::getSystemClipboard();
		clipboard->copyTo( data );
		delete data;
	}
}


void DocumentManager::copyFromDocument( Document* doc ) {
	DataObject* data = doc->copy();
	if ( NULL == data ) {
		//serialize the whole document
		BasicOutputStream bos;
		DocumentInfo* info = getDocumentInfo( doc );
		if ( NULL != info ) {
			if ( doc->saveAsType( info->mimetype, bos ) ) {
				data = new DataObject();
				BinaryPersistable* persistable = new BinaryPersistable( bos.getBuffer(), bos.getSize() );
				data->addSupportedDataType( info->mimetype, persistable );
			}
		}
	}

	if ( NULL != data ) {
		Clipboard* clipboard = UIToolkit::getSystemClipboard();
		clipboard->copyTo( data );

		delete data;
	}
}



void DocumentManager::pasteToDocument( Document* doc ) {
	Clipboard* clipboard = UIToolkit::getSystemClipboard();
	DocumentInfo* info = getDocumentInfo( doc );
	if ( NULL != info ) {
		DataObject* data = clipboard->pasteFrom( info->mimetype );

		String type;
		if ( NULL == data ) {
			Enumerator<MIMEType>* types = doc->getSupportedClipboardFormats();
			while ( types->hasMoreElements() ) {
				type = types->nextElement();
				data = clipboard->pasteFrom( type );
				if ( NULL != data ) {
					break;
				}
			}
		}


		if ( (NULL != data) && (!doc->paste( data )) ) {

			BasicOutputStream bos;
			if ( !type.empty() ) {				
				data->saveToStream( type, &bos );
			}
			else {
				data->saveToStream( info->mimetype, &bos );
			}			

			BasicInputStream bis( bos.getBuffer(), bos.getSize() );

			if ( !type.empty() ) {				
				doc->openFromType( type, bis );
			}
			else {
				doc->openFromType( info->mimetype, bis );
			}	
			doc->setModified( true );
		}

		if ( NULL != data ) {
			delete data;
		}
	}
}


void DocumentManager::undoForDocument( Document* doc ) {
	getUndoRedoStack( doc ).undo();
}


void DocumentManager::redoForDocument( Document* doc ) {
	getUndoRedoStack( doc ).redo();
}

void DocumentManager::undo() {
	getSharedUndoRedoStack().undo();
}


void DocumentManager::redo() {
	getSharedUndoRedoStack().redo();
}

UIToolkit::ModalReturnType DocumentManager::saveChanges( Document* document )
{
	UIToolkit::ModalReturnType result;

	String caption;
	Application* app = Application::getRunningInstance();
	if ( NULL != app ) {
		caption = app->getName();
	}
	MessageDialog saveDocPrompt;
	String message = Format("Do you want to save the changes you made to the document named \"%s\" ?") %
	                                              document->getTitle();

	saveDocPrompt.setMessage( message );
	saveDocPrompt.setCaption( caption );
	saveDocPrompt.setInformation( "Your changes will be lost if you don't save them." );
	saveDocPrompt.addActionButton( "Cancel", UIToolkit::mrCancel );
	saveDocPrompt.addActionButton( "Don't Save", UIToolkit::mrNo );
	saveDocPrompt.addActionButton( "Save", UIToolkit::mrYes, true );



	result = saveDocPrompt.showModal();
	switch ( result ) {
		case UIToolkit::mrYes : {
			if ( !saveFile( document ) ) {
				result = UIToolkit::mrCancel;
			}
		}
		break;
	}

	return result;
}

DocumentInfo* DocumentManager::getDocumentInfo( Document* doc )
{
	DocumentInfo* result = NULL;

	DocumentInfoMap::iterator it = docInfo_.begin();
	Class* docClass = doc->getClass();
	Class* modelClass = doc->getModel()->getClass();

	if ( NULL != docClass && NULL != modelClass ) {
		while ( it != docInfo_.end() ) {
			DocumentInfo& info = it->second;
			if ( (info.docClass == docClass->getClassName() ||
					info.docClass == docClass->getID()) || 
					(info.modelClass == modelClass->getClassName() ||
					info.modelClass == modelClass->getID()) ) {
				result = &info;
				break;
			}

			it ++;
		}
	}

	return result;
}

void DocumentManager::updatePaste( ActionEvent* event, Document* doc )
{
	DocumentInfo* info = NULL;
	if ( NULL != doc ) {
		info = getDocumentInfo( doc );
	}

	if ( (NULL != doc) && (NULL != info) ) {
		bool enabled = doc->canPasteToDocument();
		if ( !enabled ) {
			Clipboard* clipboard = UIToolkit::getSystemClipboard();
			enabled = clipboard->hasDataType(info->mimetype);
		}

		event->setEnabled( enabled );
	}
	else {
		event->setEnabled( false );
	}
}

void DocumentManager::updateCut( ActionEvent* event, Document* doc )
{
	if ( NULL != doc ) {
		event->setEnabled( doc->canCutFromDocument() );
	}
	else {
		event->setEnabled( false );
	}
}

void DocumentManager::updateCopy( ActionEvent* event, Document* doc )
{
	if ( NULL != doc ) {
		event->setEnabled( doc->canCopyFromDocument() );
	}
	else {
		event->setEnabled( false );
	}
}

UndoRedoStack& DocumentManager::getUndoRedoStack( Model* model )
{	
	return getUndoRedoStack( getDocument(model) );
}

UndoRedoStack& DocumentManager::getUndoRedoStack( Document* doc )
{
	UndoRedoStack* result = NULL;
	DocumentUndoRedoMap::iterator found = undoRedoStack_.find( doc );
	if ( found == undoRedoStack_.end() ) {
		result = new UndoRedoStack();
		undoRedoStack_[doc] = result;
	}
	else {
		result = found->second;
	}

	return *result;
}

void DocumentManager::removeUndoRedoStackForDocument( Document* doc )
{
	DocumentUndoRedoMap::iterator found = undoRedoStack_.find( doc );
	if ( found != undoRedoStack_.end() ) {
		delete found->second;
		undoRedoStack_.erase( found );
	}
}

void DocumentManager::updateUndo( ActionEvent* event, Document* doc )
{
	if ( NULL != event ) {
		UndoRedoStack& undoRedoStack = getUndoRedoStack( doc );

		bool hasUndoableCmds = undoRedoStack.hasUndoableItems();
		if ( true == hasUndoableCmds ) {
			event->setText( "Undo " + undoRedoStack.getCurrentUndoCommand()->getName() );
		}
		else {
			event->setText( "Nothing to Undo" );
		}
		event->setEnabled( hasUndoableCmds );
	}
}

void DocumentManager::updateRedo( ActionEvent* event, Document* doc )
{
	if ( NULL != event ) {
		UndoRedoStack& undoRedoStack = getUndoRedoStack( doc );
		bool hasRedoableCmds = undoRedoStack.hasRedoableItems();
		if ( true == hasRedoableCmds ) {
			event->setText( "Redo " + undoRedoStack.getCurrentRedoCommand()->getName() );
		}
		else {
			event->setText( "Nothing to Redo" );
		}
		event->setEnabled( hasRedoableCmds );
	}
}

bool DocumentManager::saveDocument( Document* doc )
{
	bool result = true;

	if ( doc != NULL ) {
		if ( doc->isModified() ) {

			switch ( saveChanges( doc ) ) {
				case UIToolkit::mrCancel : {
					result = false;
				}
				break;
			}
		}
	}

	return result;
}

void DocumentManager::updateSave( ActionEvent* event, Document* doc )
{
	event->setEnabled( NULL != doc );
}

void DocumentManager::updateSaveAs( ActionEvent* event, Document* doc )
{
	event->setEnabled( NULL != doc );
}

void DocumentManager::updateClose( ActionEvent* event, Document* doc )
{
	event->setEnabled( NULL != doc );
}

DocumentManager* DocumentManager::getDocumentManager()
{
	return DocumentManager::docManagerInstance;
}

void DocumentManager::prepareOpenDialog( CommonFileOpenDialog* openDialog )
{
	DocumentInfoMap::iterator it = docInfo_.begin();

	String fileTypes;
	while ( it != docInfo_.end() ) {
		DocumentInfo& info = it->second;

		std::vector<FileTypeInfo> fileTypes = info.getFileTypes();
		std::vector<FileTypeInfo>::iterator it2 = fileTypes.begin();
		
		while ( it2 != fileTypes.end() ) {
			const FileTypeInfo& fti = *it2;

			String filter = fti.extension;
			if ( filter[0] != '.' ) {
				filter.insert(0,".");
			}
			openDialog->addFilter( info.description + " (*" + filter + ")", "*" + filter );
			++it2;
		}
		++it;
	}

}

void DocumentManager::prepareSaveDialog( CommonFileSaveDialog* saveDialog, Document* doc )
{
	String fileType;
	std::vector<FileTypeInfo> fileTypes;
	String desc;
	DocumentInfo* info = getDocumentInfo( doc );
	if ( NULL != info ) {
		fileType = info->mimetype;
		fileTypes = info->getFileTypes();
		desc = info->description;
	}

	
	std::vector<FileTypeInfo>::iterator it = fileTypes.begin();

	while ( it != fileTypes.end() ) {
		const FileTypeInfo& fti = *it;
		
		String filter = fti.extension;
		if ( filter[0] != '.' ) {
			filter.insert(0,".");
		}

		saveDialog->addFilter( desc + " file (*" + filter + ")", "*" + filter );
		++it;
	}
}

MIMEType DocumentManager::getDocTypeFromFileExtension( const String& fileName )
{
	MIMEType result;
	DocumentInfoMap::iterator it = docInfo_.begin();
	String mimetype;

	
	String ext = FilePath::getExtension(fileName);
	if ( ext[0] == '.' ) {
		ext.erase( 0, 1 );
	}

	while ( it != docInfo_.end() ) {
		DocumentInfo& info = it->second;

		if ( String::npos != info.fileTypes.find( ext ) ) {

			result = info.mimetype;
			break;
		}
		it ++;
	}

	return result;
}

MIMEType DocumentManager::getFileTypeFromFileExtension( const String& fileName )
{
	MIMEType result;
	DocumentInfoMap::iterator it = docInfo_.begin();
	String mimetype;

	
	String ext = FilePath::getExtension(fileName);
	if ( ext[0] == '.' ) {
		ext.erase( 0, 1 );
	}

	bool done = false;
	while ( it != docInfo_.end() || !done ) {
		DocumentInfo& info = it->second;

		std::vector<FileTypeInfo> fileTypes = info.getFileTypes();
		std::vector<FileTypeInfo>::iterator it2 = fileTypes.begin();
		while ( it2 != fileTypes.end() ) {
			const FileTypeInfo& fti = *it2;
			if ( 0 == StringUtils::noCaseCompare( fti.extension, ext ) ) {
				result = fti.mimeInfo;
				done = true;
				break;
			}

			++it2;
		}		

		it ++;
	}

	return result;
}

DocumentInfo DocumentManager::getDocumentInfo( const MIMEType& mimeType )
{
	DocumentInfo result;

	if ( mimeType.isEmpty() ) {
		result = docInfo_.begin()->second;
	}
	else {
		result = docInfo_[mimeType];
	}
	return result;
}

void DocumentManager::addDocumentInfo( const MIMEType& mimeType, const DocumentInfo& info )
{
	docInfo_[mimeType] = info;
}

void DocumentManager::addDocument( Document* document )
{
	openDocuments_.push_back( document );
	//document->addRef();
}

void DocumentManager::removeDocument( Document* document )
{
	std::vector<Document*>::iterator found = std::find( openDocuments_.begin(), openDocuments_.end(), document );
	if ( found != openDocuments_.end() ) {
		openDocuments_.erase( found );
		//document->release();
	}
}


Enumerator<Document*>* DocumentManager::getOpenedDocuments()
{
	return openDocuments_.getEnumerator();
}

Document* DocumentManager::openFromFileName( const String& fileName )
{
	//throw an exception for invalid file names!!
	if ( fileName.empty() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid file name. For whatever reason a file name was passed in that was an empty string (\"\").") );
	}

	/**
	Whoops! Someone alert Bozo The Clown, we've been passed a 
	bogus file name!!!
	*/
	if ( !File::exists( fileName ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("DocumentManager: the file \"" + fileName + "\" does not exists." ) );
	}

	FilePath fp = fileName;
	String mimetype = getDocTypeFromFileExtension( fp );

	Document* doc = NULL;
	if ( !mimetype.empty() )  {
		// provides a default document to 'host' the file, and its UI too if it should
		doc = newDefaultDocument( "", mimetype );
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("DocumentManager failed to find a corresponding mime type!") );
	}

	// finally reads what is specific about the document: its file
	if ( NULL != doc ) {
		doc->setFileName( fp );
		mimetype = getFileTypeFromFileExtension( fp );
		if ( !doc->openFromType( fp, mimetype ) ) {
			// failed to open the file, we close the default document just opened.
			setCurrentDocument( doc );
			closeCurrentDocument();
			doc = NULL;

			throw RuntimeException( MAKE_ERROR_MSG_2("DocumentManager failed to open the file \" + fileName + \"" ) );
		}
	}
	else {
		//put an error message!
		throw RuntimeException( MAKE_ERROR_MSG_2("Unable to create a default document!" ) );
	}



	return doc;
}

Action* DocumentManager::getAction( uint32 tag )
{
	Action* result = NULL;

	ActionMap::iterator found = actionsMap_.find( tag );
	if ( found != actionsMap_.end() ) {
		result = found->second;
	}

	return result;
}

void DocumentManager::addAction( uint32 tag, Action* action )
{
	actionsMap_[tag] = action;
	action->setTag( tag );

	MenuManager::getMainMenu()->addComponent( action );
}

void DocumentManager::linkDocumentToModel( Document* document, Model* model )
{
	docModelMap_[document] = model;
}

void DocumentManager::unlinkDocumentToModel( Document* document )
{
	DocumentModelMap::iterator it = docModelMap_.find(document);
	if ( it != docModelMap_.end() ) {
		docModelMap_.erase( it );
	}
}

Document* DocumentManager::getDocument( Model* model )
{
	Document* result = NULL;
	DocumentModelMap::iterator it = docModelMap_.begin();
	while ( it != docModelMap_.end() ) {
		if ( it->second == model ) {
			result = it->first;
			break;
		}
		++it;
	}
	return result;
}

Model* DocumentManager::getModel( Document* document )
{
	Model* result = NULL;
	DocumentModelMap::iterator it = docModelMap_.find(document);
	if ( it != docModelMap_.end() ) {
		result = it->second;
	}
	return result;
}

void DocumentManager::onDocWndEntered( DropTargetEvent* e )
{
	currentDragDocument_ = NULL;

	DropTarget* dt = (DropTarget*)e->getSource();	

	//the point of the following is 
	//to make sure we are actually talking about the right document
	//and window pairing for the specific drop target that 
	//we're getting this callback for
	Window* window = (Window*)dt->getTarget();
	Document* doc = NULL;

	Array<Document*>::iterator it = openDocuments_.begin();
	while ( it != openDocuments_.end() ) {
		if ( (*it)->getWindow() == window ) {
			doc = *it;
			break;
		}
		++it;
	}

	VCF_ASSERT( doc != NULL );

	if ( doc == NULL ) {
		return;
	}	

	DocumentInfo* info = getDocumentInfo( doc );
	VCF_ASSERT( info != NULL );

	if ( info == NULL ) {
		return;
	}

	DataObject* dataObj = e->getDataObject();

	/*
	StringTokenizer tok( info->clipboardTypes, ";" );

	bool matchFound = false;
	while ( !matchFound && tok.hasMoreElements() ) {
		String type = tok.nextElement();
		if ( dataObj->isTypeSupported( type ) ) {
			matchFound = true;
			break;
		}
	}
	*/

		//if (  ) {
		//	matchFound = true;//let it go through we'll figure this out on a drop
			/*
			BasicOutputStream stream; //dump the file names here
			//write the data in the data object to the stream
			if ( dataObj->saveToStream( FILE_DATA_TYPE, &stream ) ) {
				//create a string from the output streams data
				String fileNames;
				fileNames.append( (VCF::WideChar*)stream.getBuffer(), stream.getSize()/sizeof(VCF::WideChar) );

				//create a string tokenizer, with the delimeter set to '\n'
				tok.assign( fileNames, "\n");
				//enumerate through all the file names
				while ( tok.hasMoreElements() ) {
					String fileName = tok.nextElement();
					
				}
			}
			*/
		//}
	//}

	if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
		currentDragDocument_ = doc;
	}


	e->setActionType( dataObj->isTypeSupported( FILE_DATA_TYPE ) ? daCopy : daNone );
}

void DocumentManager::onDocWndDragging( DropTargetEvent* e )
{
	e->setActionType( (NULL != currentDragDocument_) ? daCopy : daNone );	
}

void DocumentManager::onDocWndDropped( DropTargetEvent* e )
{
	if ( NULL != currentDragDocument_ ) {
		DocumentInfo* info = getDocumentInfo( currentDragDocument_ );
		VCF_ASSERT( info != NULL );
		
		if ( info == NULL ) {
			return;
		}
		
		DataObject* dataObj = e->getDataObject();

		if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
			BasicOutputStream stream; //dump the file names here
			//write the data in the data object to the stream
			if ( dataObj->saveToStream( FILE_DATA_TYPE, &stream ) ) {
				//create a string from the output streams data
				String fileNames;
				fileNames.append( (VCF::WideChar*)stream.getBuffer(), stream.getSize()/sizeof(VCF::WideChar) );

				//create a string tokenizer, with the delimeter set to '\n'
				StringTokenizer tok( fileNames, "\n");
				//enumerate through all the file names
				while ( tok.hasMoreElements() ) {
					String fileName = tok.nextElement();
					Document* doc = openFromFileName( fileName );
					break;
				}
			}
		}

		//turn this off for now - we don't want to deal with 
		//NON file dragging
		/*
		else {
			if ( !currentDragDocument_->paste( dataObj ) ) {
				
				StringTokenizer tok( info->clipboardTypes, ";" );
				
				String type;				
				while ( tok.hasMoreElements() ) {
					type = tok.nextElement();
					
					if ( dataObj->isTypeSupported( type ) ) {
						break;
					}
					else {
						type = "";
					}
				}

				if ( !type.empty() ) {
					BasicOutputStream bos;
					if ( !type.empty() ) {				
						dataObj->saveToStream( type, &bos );
					}		
					
					BasicInputStream bis( bos.getBuffer(), bos.getSize() );
					
					if ( !type.empty() ) {				
						currentDragDocument_->openFromType( type, bis );
					}
					currentDragDocument_->setModified( true );
				}
			}
		}
		*/

	}
	currentDragDocument_ = NULL;
}

void DocumentManager::addDropTarget( DropTarget* dropTarget )
{
	dropTargets_.push_back(dropTarget);
}

void DocumentManager::cleanupDropTarget( Document* doc )
{
	std::vector<DropTarget*>::iterator it = dropTargets_.begin();
	while ( it != dropTargets_.end() ) {
		DropTarget* dt = *it;
		if ( dt->getTarget() == doc->getWindow() ) {
			dt->removeTargetControl( doc->getWindow() );
			dt->free();
			dropTargets_.erase( it );
			break;
		}
		++it;
	}
}

void DocumentManager::openFromCommandLine(const CommandLine& comdLine)
{	
	size_t argc = comdLine.getArgCount();
	
	if ( argc > 1 ) {
		String docFileName = comdLine.getArgument(1);
		
		openFromFileName( docFileName );
	}
	else {
		newDefaultDocument("", VCF::MIMEType() );
	}
}

/**
$Id$
*/

