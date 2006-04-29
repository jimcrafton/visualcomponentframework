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


using namespace VCF;



DocumentManager* DocumentManager::docManagerInstance = NULL;

DocumentManager::DocumentManager():
	shouldCreateUI_(true)
{
	DocumentManager::docManagerInstance = this;
	docInfoContainer_.initContainer( docInfo_ );
	openDocContainer_.initContainer( openDocuments_ );
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
	FilePath dir = app->getFileName();
	
	String fileName = dir.getPathName(true);
	fileName += app->getName();	
	fileName += ".xml";
	
	FileInputStream fs( fileName );

	XMLParser parser;
	parser.parse( &fs );
	Enumerator<XMLNode*>* nodes = parser.getParsedNodes();
	while ( nodes->hasMoreElements() ) {
		XMLNode* node = nodes->nextElement();
		if ( node->getName() == "document" ) {

			XMLAttr* attr = node->getAttrByName( "classname" );

			DocumentInfo info;
			info.className = attr->getValue();

			attr = node->getAttrByName( "classid" );
			if ( attr ) {
				info.classID = attr->getValue();
			}

			Enumerator<XMLNode*>* properties = node->getChildNodes();
			while ( properties->hasMoreElements() ) {
				XMLNode* prop = properties->nextElement();
				if ( prop->getName() == "property" ) {
					XMLAttr* name = prop->getAttrByName( "name" );
					XMLAttr* val = prop->getAttrByName( "value" );

					if ( name->getValue() == "mimetype" ) {
						info.mimetype = val->getValue();
					}
					else if ( name->getValue() == "role" ) {

					}
					else if ( name->getValue() == "extension" ) {
						info.fileTypes = val->getValue();
					}
					else if ( name->getValue() == "description" ) {
						info.description = val->getValue();
					}
					else if ( name->getValue() == "view" ) {
						info.view = val->getValue();
					}
					else if ( name->getValue() == "window" ) {
						info.window = val->getValue();
					}
				}
			}

			docInfo_[info.mimetype] = info;
		}
	}

}

void DocumentManager::terminate() {
	DocumentUndoRedoMap::iterator it = undoRedoStack_.begin();
	while ( it != undoRedoStack_.end() ) {
		delete it->second;
		it ++;
	}
	undoRedoStack_.clear();

	std::vector<Document*>::iterator it2 = openDocuments_.begin();
	while ( it2 != openDocuments_.end() ) {
		Document* document = *it2;
		if ( NULL == document->getOwner() ) {
			document->release();
		}
		it2 ++;
	}
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
		data->free();
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
				BinaryPersistable* persistable = new BinaryPersistable( (const unsigned char*)bos.getBuffer(), bos.getSize() );
				data->addSupportedDataType( info->mimetype, persistable );
			}
		}
	}

	if ( NULL != data ) {
		Clipboard* clipboard = UIToolkit::getSystemClipboard();
		clipboard->copyTo( data );

		data->free();
	}
}



void DocumentManager::pasteToDocument( Document* doc ) {
	Clipboard* clipboard = UIToolkit::getSystemClipboard();
	DocumentInfo* info = getDocumentInfo( doc );
	if ( NULL != info ) {
		DataObject* data = clipboard->pasteFrom( info->mimetype );

		String type;
		if ( NULL == data ) {
			Enumerator<String>* types = doc->getSupportedClipboardFormats();
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
			
		}

		if ( NULL != data ) {
			data->free();
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
	String message = StringUtils::format( Format("Do you want to save the changes you made to the document \"%s\" ?") %
	                                              document->getName() );

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
	Class* clazz = doc->getClass();

	if ( NULL != clazz ) {
		while ( it != docInfo_.end() ) {
			DocumentInfo& info = it->second;
			if ( info.classID == clazz->getID() ) {
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
		fileTypes = info.fileTypes;

		size_t pos = fileTypes.find( ";" );
		while ( pos != String::npos ) {
			String filter = fileTypes.substr( 0 , pos );
			fileTypes.erase( 0, pos + 1 );
			openDialog->addFilter( info.description + " (*" + filter + ")", "*" + filter );

			pos = fileTypes.find( ";" );
		}
		if ( !fileTypes.empty() ) {
			openDialog->addFilter( info.description + " (*" + fileTypes + ")", "*" + fileTypes );
		}

		it ++;
	}

}

void DocumentManager::prepareSaveDialog( CommonFileSaveDialog* saveDialog, Document* doc )
{
	String fileType;
	String fileTypes;

	DocumentInfo* info = getDocumentInfo( doc );
	if ( NULL != info ) {
		fileType = info->mimetype;
		fileTypes = info->fileTypes;
	}

	size_t pos = fileTypes.find( ";" );
	while ( pos != String::npos ) {
		String filter = fileTypes.substr( 0 , pos );
		fileTypes.erase( 0, pos + 1 );
		saveDialog->addFilter( filter + " files", "*" + filter );

		pos = fileTypes.find( ";" );
	}
	if ( !fileTypes.empty() ) {
		saveDialog->addFilter( fileTypes + " files", "*" + fileTypes );
	}
}

String DocumentManager::getMimeTypeFromFileExtension( const String& fileName )
{
	String result;
	DocumentInfoMap::iterator it = docInfo_.begin();
	String mimetype;

	FilePath fp = fileName;

	while ( it != docInfo_.end() ) {
		DocumentInfo& info = it->second;

		if ( String::npos != info.fileTypes.find( fp.getExtension() ) ) {

			result = info.mimetype;
			break;
		}
		it ++;
	}

	return result;
}

DocumentInfo DocumentManager::getDocumentInfo( const String& mimeType )
{
	DocumentInfo result;

	if ( mimeType.empty() ) {
		result = docInfo_.begin()->second;
	}
	else {
		result = docInfo_[mimeType];
	}
	return result;
}

void DocumentManager::addDocumentInfo( const VCF::String& mimeType, const DocumentInfo& info )
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
	return openDocContainer_.getEnumerator();
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
	String mimetype = getMimeTypeFromFileExtension( fp );

	Document* doc = NULL;
	if ( !mimetype.empty() )  {
		// provides a default document to 'host' the file, and its UI too if it should
		doc = newDefaultDocument( "", mimetype );
	}

	// finally reads what is specific about the document: its file
	if ( NULL != doc ) {
		doc->setFileName( fp );
		if ( doc->openFromType( fp, mimetype ) ) {
			addDocument( doc );
		}
		else {
			// failed to open the file, we close the default document just opened.
			setCurrentDocument( doc );
			closeCurrentDocument();
			doc = NULL;

			throw RuntimeException( MAKE_ERROR_MSG_2("DocumentManager failed to open the file \" + fileName + \"" ) );
		}
	}
	else {
		//put an error message!
	}



	return doc;
}

Action* DocumentManager::getAction( ulong32 tag )
{
	Action* result = NULL;

	ActionMap::iterator found = actionsMap_.find( tag );
	if ( found != actionsMap_.end() ) {
		result = found->second;
	}

	return result;
}

void DocumentManager::addAction( ulong32 tag, Action* action )
{
	actionsMap_[tag] = action;
	action->setTag( tag );

	MenuManager::getMainMenu()->addComponent( action );
}


/**
$Id$
*/
