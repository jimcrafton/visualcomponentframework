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
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.7  2006/01/09 02:22:30  ddiego
*more osx code
*
*Revision 1.4.2.6  2005/10/19 04:25:00  ddiego
*minor doc view manager update.
*
*Revision 1.4.2.5  2005/10/18 04:42:38  ddiego
*fixed minor bug in doc manager.
*
*Revision 1.4.2.4  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.4.2.3  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.4.2.2  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.4.2.1  2005/08/12 03:13:44  ddiego
*minor changes
*
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.10  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3.2.9  2005/06/02 15:56:03  marcelloptr
*more documentation. Made some handlers virtual. Added some forgotten onUpdateXXX
*
*Revision 1.3.2.8  2005/04/09 17:20:35  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.7  2005/03/31 01:25:01  ddiego
*fixed a string format glitch in doc mgr.
*
*Revision 1.3.2.6  2005/03/21 17:26:04  marcelloptr
*openFromFileName now throws an exception sooner when trying to open a file that does not exist
*
*Revision 1.3.2.5  2005/03/15 01:51:49  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.4  2005/03/14 04:17:23  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.2.3  2005/03/05 18:21:18  ddiego
*fixed a bug that marcello found in the vcfbuilder that is actually a bug in the document manager (see bug 1157348).
*
*Revision 1.3.2.2  2005/03/02 19:41:10  marcelloptr
*fixed crash when opening a non existing document
*
*Revision 1.3.2.1  2005/01/28 02:49:01  ddiego
*fixed bug 1111096 where the text control was properly handlind
*input from the numbpad keys.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.6  2004/11/21 00:19:10  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.2.2.5  2004/11/19 05:54:28  ddiego
*added some fixes to the text peer for win32 for printing. added toolbars to text edit example anmd added printing
*
*Revision 1.2.2.4  2004/11/15 05:41:27  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.3  2004/11/13 22:30:42  marcelloptr
*more documentation
*
*Revision 1.2.2.1  2004/10/24 18:48:56  marcelloptr
*Document Window documentation
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/30 21:29:47  ddiego
*minor mods to copy/paste code in DocumentManager
*
*Revision 1.1.2.4  2004/06/29 20:31:35  ddiego
*some minor fixes to the DocumentManager
*
*Revision 1.1.2.3  2004/05/06 21:18:33  ddiego
*some more minor win32 unicode changes
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.5  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4.2.4  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.4.2.3  2004/04/12 20:23:15  ddiego
*fixed some exception handling in Document and
*DocumentManager when opening a file.
*
*Revision 1.4.2.2  2004/04/10 04:37:19  ddiego
*added a MIMType class that parses mime types.
*
*Revision 1.4.2.1  2004/04/08 21:08:34  ddiego
*little chocolate cupcakes.
*
*Revision 1.4  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.2  2004/03/28 00:46:22  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.3.2.1  2004/03/08 04:41:07  ddiego
*minor changes to DocumentManager - allow the use of
*Actions so that other UI elements can be added besides menu
*items (like Toolbar items)
*
*Revision 1.3  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.10  2003/10/05 16:43:02  ddiego
*fixed a glitch in the cut handling of a Document - it was calling
*empty() by default - not exactly nice behaviour.
*
*Revision 1.2.2.9  2003/09/22 01:48:04  ddiego
*some minor additions ot the DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.2.2.8  2003/09/19 21:24:06  ddiego
*small changes
*
*Revision 1.2.2.7  2003/09/18 21:15:13  ddiego
*added a way enumerate doc types
*
*Revision 1.2.2.6  2003/09/17 03:27:40  ddiego
*added a fix for bug [ 807416 ] CommonFileDialog needs setFileExtension
*added methods for getting data from the open and save dialogs in the
*DocumentManager
*
*Revision 1.2.2.5  2003/09/02 02:11:13  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.2.2.4  2003/08/27 20:11:33  ddiego
*adjustments to how the DataObject class work and copy/paste
*
*Revision 1.2.2.3  2003/08/26 21:41:17  ddiego
*miscellanesous stuff, minor bugs
*
*Revision 1.2.2.2  2003/08/25 21:34:59  ddiego
*miscellaneous
*
*Revision 1.2.2.1  2003/08/25 03:46:32  ddiego
*some fixes to some of the stream impls
*
*Revision 1.2  2003/08/09 02:56:45  ddiego
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
*Revision 1.1.2.3  2003/08/06 21:27:49  ddiego
*minor changes
*
*Revision 1.1.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
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


