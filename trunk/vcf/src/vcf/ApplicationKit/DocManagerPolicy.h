#ifndef _VCF_DOCMANAGERPOLICY_H__
#define _VCF_DOCMANAGERPOLICY_H__
//DocManagerPolicy.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class Document;


class APPLICATIONKIT_API SDIPolicy {
public:
	SDIPolicy(): currentDocument_(NULL), menusMerged_(false) {}

	bool usesMainWindow() {
		return true;
	}

	bool saveBeforeNewDocument() {
		return true;
	}

	void afterNewDocument( Document* newDocument ) {
		currentDocument_ = newDocument;

		newDocument->getWindow()->setCaption( getDocumentWindowCaption() );
	}

	void closeDocument() {
		getCurrentDocument()->getWindow()->close();
	}

	Document* getCurrentDocument() {
		return currentDocument_;
	}

	void setCurrentDocument( VCF::Document* doc ) {
		currentDocument_ = doc;

		if ( NULL != currentDocument_ ) {
			currentDocument_->getWindow()->activate();
		}
	}

	bool closeDocumentWindow( Window* window ) {
		
		if ( currentDocument_->isModified() ) {
			if ( !VCF::DocumentManager::getDocumentManager()->saveDocument( currentDocument_ ) ) {
				return false;
			}
		}					
		
		VCF::DocManagerEvent event( currentDocument_, VCF::DocumentManager::dmCloseDocument );
		
		VCF::DocumentManager::getDocumentManager()->DocumentClosed.fireEvent( &event );

		currentDocument_ = NULL;
		window->setView( NULL );
		window->setViewModel( NULL );
		return true;
	}

	String getDocumentName() {
		String result;
		if ( NULL == currentDocument_ ) {
			result = "No Document";
		}
		else {
			result = currentDocument_->getName();
			if ( result.empty() ) {
				result = "Untitled";
			}
			if ( currentDocument_->isModified() ) {
				result += "*";
			}
		}

		return result;
	}

	void documentWindowActivated( Window* window ) {

		window->setCaption( getDocumentWindowCaption() );
	}

	String getDocumentWindowCaption() {
		String result;

		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			result = app->getName() +  " - " + getDocumentName();
		}
		else {
			result = getDocumentName();
		}

		return result;
	}

	void mergeWindowMenus( Menu* appMenu, Menu* documentWindowMenu ) {
		if ( !menusMerged_ ) {
			UIToolkit::getUIPolicyManager()->mergeMenus( appMenu, documentWindowMenu );
		}

		menusMerged_ = true;
	}

	bool menusMerged_;
	Document* currentDocument_;
};







class APPLICATIONKIT_API MDIPolicy {
public:
	MDIPolicy(): currentDocument_(NULL),documentCount_(0) {}

	bool usesMainWindow() {
		return false;
	}

	bool saveBeforeNewDocument() {
		return false;
	}

	void afterNewDocument( Document* newDocument ) {
		documents_[newDocument->getWindow()] = newDocument;
		documentCount_ ++;
	}

	Document* getCurrentDocument() {
		return currentDocument_;
	}

	void setCurrentDocument( VCF::Document* doc ) {
		currentDocument_ = doc;

		if ( NULL != currentDocument_ ) {
			currentDocument_->getWindow()->activate();
		}
	}

	void closeDocument() {
		getCurrentDocument()->getWindow()->close();
	}

	bool closeDocumentWindow( Window* window ) {
		std::map<Window*,Document*>::iterator found = documents_.find( window );
		std::map<Window*,Document*>::iterator next = documents_.end();
		if ( found != documents_.end() ) {

			window->setView( NULL );
			window->setViewModel( NULL );

			// In a map: erase() invalidates all iterators on the erased element
			//		and does not invalidate any other iterator.
			next = found;
			++next;
			documents_.erase( found );

			//currentDocument_ = NULL;
		}

		std::vector<Menu*>::iterator found2 = std::find( mergedMenus_.begin(), mergedMenus_.end(), window->getMenuBar() );
		if ( found2 != mergedMenus_.end() ) {
			mergedMenus_.erase( found2 );
		}

		currentDocument_ = NULL;
		if ( documents_.empty() ) {
			//Buh bye!
			UIToolkit::quitCurrentEventLoop();
		}
		else {
			if ( next == documents_.end() ) {
				next = documents_.begin();
			}


			StringUtils::trace( "next->second->getWindow()->show()\n" );
			if ( next->second->getWindow()->isActive() ) {
				StringUtils::trace( "next->second->getWindow()->isActive()\n" );
				documentWindowActivated( next->second->getWindow() );
			}
			else {
				next->second->getWindow()->show();
				next->second->getWindow()->activate();
			}

		}
		return true;
	}

	String getDocumentName() {
		String result;
		if ( NULL == currentDocument_ ) {
			result = "No Document";
		}
		else {
			result = currentDocument_->getName();
			if ( result.empty() ) {
				result = "Document" + StringUtils::toString( documentCount_ );
				currentDocument_->setName( result );
			}

			if ( currentDocument_->isModified() ) {
				result += "*";
			}
		}

		return result;
	}

	void documentWindowActivated( Window* window ) {
		StringUtils::trace( "documentWindowActivated\n" );

		currentDocument_ = NULL;

		std::map<Window*,Document*>::iterator found = documents_.find( window );
		if ( found != documents_.end() ) {
			currentDocument_ = found->second;

			window->setCaption( getDocumentWindowCaption() );
		}
	}

	String getDocumentWindowCaption() {
		String result;

		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			result = app->getName() +  " - [" + getDocumentName() + "]";
		}
		else {
			result = getDocumentName();
		}

		return result;
	}

	void mergeWindowMenus( Menu* appMenu, Menu* documentWindowMenu ) {
		std::vector<Menu*>::iterator found = std::find( mergedMenus_.begin(), mergedMenus_.end(), documentWindowMenu );
		if ( found == mergedMenus_.end() ) {

			UIToolkit::getUIPolicyManager()->mergeMenus( appMenu, documentWindowMenu );

			mergedMenus_.push_back( documentWindowMenu );
		}
	}



	Document* currentDocument_;
	std::map<Window*,Document*> documents_;
	std::vector<Menu*> mergedMenus_;
	long documentCount_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/01 04:02:17  ddiego
*minor stuff
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
*Revision 1.4.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.1  2004/03/24 21:28:49  ddiego
*minor change to document manager - added
*setCurrentDocument
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.4  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.2.2.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.2.2  2003/09/04 03:20:04  ddiego
**** empty log message ***
*
*Revision 1.2.2.1  2003/08/25 16:47:03  ddiego
*mods to document manager and policy for closeDocumentWindow to return bool
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
*Revision 1.1.2.4  2003/08/06 21:26:16  ddiego
*minor changes to doc stuff
*
*Revision 1.1.2.3  2003/08/02 00:41:12  marcelloptr
*fixes for vc6;  improved dependencies
*
*Revision 1.1.2.2  2003/07/24 04:10:43  ddiego
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


#endif // _VCF_DOCMANAGERPOLICY_H__


