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


/**
* DocManagerPolicy
* the document manager policy is the set of operations defining the documents 
* interface itself.
* Even if the template using a policy as its argument needs the policy to have
* certain members defined, we don't create a generic abstract (pure)
* class DocManagerPolicy. The main reason is that a policy class does NOT have
* virtual methods as it is not necessary at all for template arguments.
*/

namespace VCF {


class Document;


/**
* class SDIPolicy
* policy class for Single Document Interface
* This is the implementation of the regular SDI architecture,
* with all the tipical operations on a document that we can find
* in an application having a single document.
*/
class APPLICATIONKIT_API SDIPolicy {
public:
	SDIPolicy(): currentDocument_(NULL), menusMerged_(false) {}

	/**
	* tells if we want the application to use the main applicaiton's window for a document
	* this is true in a SDI application.
	*/
	bool usesMainWindow() {
		return true;
	}

	/**
	* tells if we want the application to save the current document before activating a new document
	*/
	bool saveBeforeNewDocument() {
		return true;
	}

	/**
	*callback function managing the operation to be done after a new document
	* has been created
	*/
	void afterNewDocument( Document* newDocument ) {
		currentDocument_ = newDocument;

		newDocument->getWindow()->setCaption( getDocumentWindowCaption(newDocument) );
	}

	/**
	* gets the document that currently has the focus, so to speak, in the application
	*/
	Document* getCurrentDocument() {
		return currentDocument_;
	}

	/**
	* sets the specified document as the active one in the application
	*/
	void setCurrentDocument( VCF::Document* doc ) {
		currentDocument_ = doc;

		if ( NULL != currentDocument_ ) {
			currentDocument_->getWindow()->activate();
		}
	}

	/**
	* closes the window associated to the current document
	*/
	void closeDocument() {
		getCurrentDocument()->getWindow()->close();
	}

	/**
	* closes the specified window
	*/
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

	/**
	*gets the appropriate name for the current document
	*@String, the name
	*/
	String getDocumentName( Document* doc ) {
		String result;
		if ( NULL == doc ) {
			result = "No Document";
		}
		else {
			result = doc->getName();
			if ( result.empty() ) {
				result = "Untitled";
			}
			if ( doc->isModified() ) {
				result += "*";
			}
		}

		return result;
	}

	/**
	* 
	* 
	*/
	void documentWindowActivated( Window* window ) {

		window->setCaption( getDocumentWindowCaption( getCurrentDocument() ) );
	}

	String getDocumentWindowCaption( Document* doc ) {
		String result;

		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			result = app->getName() +  " - " + getDocumentName(doc);
		}
		else {
			result = getDocumentName(doc);
		}

		return result;
	}

	/**
	* merges the menu specific of the document window, with the generic
	* application's menu
	*Menu* appMenu, the menu general for any application
	*Menu* documentWindowMenu, the menu specific for this application's document window
	*/
	void mergeWindowMenus( Menu* appMenu, Menu* documentWindowMenu ) {
		if ( !menusMerged_ ) {
			UIToolkit::getUIPolicyManager()->mergeMenus( appMenu, documentWindowMenu );
		}

		menusMerged_ = true;
	}

public:
	/* the document that currently has the focus, so to speak, in the application */
	Document* currentDocument_;

	/* flag telling if the menus have been already merged or not */
	bool menusMerged_;
};







/**
* class MDIPolicy
* policy class for a Multiple Document Interface (MDI).
* This is the implementation of the regular MDI architecture,
* with all the tipical operations with documents that we can find
* in an application having many (more than one) documents.
* It is set up to have 1 Document class associated with 1 Window instance,
* i.e. it is a one to one relationship.
* Each window is a real indipendent window.
*/
class APPLICATIONKIT_API MDIPolicy {
public:
	MDIPolicy(): /*currentDocument_(NULL),*/ documentCount_(0) {}

	/**
	* tells if we want the application to use the main applicaiton's window for a document
	* this is false in a MDI application, as child windows are used instead.
	*/
	bool usesMainWindow() {
		return false;
	}

	/**
	* tells if we want the application to save the current document before activating a new document
	*/
	bool saveBeforeNewDocument() {
		return false;
	}

	/**
	*callback function managing the operation to be done after a new document
	* has been created
	*/
	void afterNewDocument( Document* newDocument ) {
		documents_[newDocument->getWindow()] = newDocument;
		documentCount_ ++;
	}

	/**
	* gets the document that currently has the focus, so to speak, in the application
	*/
	Document* getCurrentDocument() {
		Document* result = NULL;
		std::map<Window*,Document*>::iterator found = documents_.find( (Window*)Frame::getActiveFrame() );
		if ( found != documents_.end() ) {
			result = found->second;
		}
		

		StringUtils::traceWithArgs( "currentDocument_: %p\n", result );

		return result;
	}

	/**
	* sets the specified document as the active one in the application
	*/
	void setCurrentDocument( VCF::Document* doc ) {
		

		StringUtils::traceWithArgs( "setCurrentDocument( %p )\n", doc );

		if ( NULL != doc ) {
			doc->getWindow()->activate();
		}
	}

	/**
	* closes the window associated to the current document
	*/
	void closeDocument() {
		getCurrentDocument()->getWindow()->close();
	}

	/**
	* closes the specified window
	* and activates the next document window in the internal list
	*/
	bool closeDocumentWindow( Window* window ) {
		std::map<Window*,Document*>::iterator found = documents_.find( window );
		std::map<Window*,Document*>::iterator next = documents_.end();
		if ( found != documents_.end() ) {

			Document* currentDoc = found->second;
			if ( currentDoc->isModified() ) {
				if ( !VCF::DocumentManager::getDocumentManager()->saveDocument( currentDoc ) ) {
					return false;
				}
			}					
		
			VCF::DocManagerEvent event( currentDoc, VCF::DocumentManager::dmCloseDocument );
		
			VCF::DocumentManager::getDocumentManager()->DocumentClosed.fireEvent( &event );

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

		//currentDocument_ = NULL;
		if ( documents_.empty() ) {
			lastDocumentClosed();
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

	/**
	*specifies what to do after the last application's document has been closed
	*the defalt behaviour is, for the moment, to close the entire application
	*this will be rewritten in a different way soon
	*/
	void lastDocumentClosed() {
		//Buh bye!

		UIToolkit::postEvent( new StaticEventHandlerInstance<Event>(MDIPolicy::postQuitEventLoop), new Event(NULL,0) );
		//UIToolkit::quitCurrentEventLoop();
	}

	static void postQuitEventLoop( Event* e ) {
		UIToolkit::quitCurrentEventLoop();
	}
	/**
	*gets the appropriate name for the current document
	*@String, the name
	*/
	String getDocumentName(Document* doc) {
		String result;
		if ( NULL == doc ) {
			result = "No Document";
		}
		else {
			result = doc->getName();
			if ( result.empty() ) {
				result = "Document" + StringUtils::toString( documentCount_ );
				doc->setName( result );
			}

			if ( doc->isModified() ) {
				result += "*";
			}
		}

		return result;
	}

	/**
	* 
	* 
	*/
	void documentWindowActivated( Window* window ) {
		StringUtils::trace( "documentWindowActivated\n" );

		//currentDocument_ = NULL;

		std::map<Window*,Document*>::iterator found = documents_.find( window );
		if ( found != documents_.end() ) {
			//currentDocument_ = found->second;

			window->setCaption( getDocumentWindowCaption( found->second ) );
		}
	}

	/**
	*gets the appropriate name for the current document
	*@String, the name
	*/
	String getDocumentWindowCaption( Document* doc ) {
		String result;

		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			result = app->getName() +  " - [" + getDocumentName(doc) + "]";
		}
		else {
			result = getDocumentName(doc);
		}

		return result;
	}

	/**
	* merges the menu specific of the document window, with the generic
	* application's menu
	* an internal vector keeps track of the menus already merged so this is done only once
	*Menu* appMenu, the menu general for any application
	*Menu* documentWindowMenu, the menu specific for the document window we need
	*/
	void mergeWindowMenus( Menu* appMenu, Menu* documentWindowMenu ) {
		std::vector<Menu*>::iterator found = std::find( mergedMenus_.begin(), mergedMenus_.end(), documentWindowMenu );
		if ( found == mergedMenus_.end() ) {

			UIToolkit::getUIPolicyManager()->mergeMenus( appMenu, documentWindowMenu );

			mergedMenus_.push_back( documentWindowMenu );
		}
	}

public:
	/* the document that currently has the focus, so to speak, in the application */
	//Document* currentDocument_;

	/**
	* the association map between each window and its document in the application
	* in a standard MDI this relationship is one to one
	*/
	std::map<Window*,Document*> documents_;

	/**
	* vector used to keep track of the menus already merged
	*/
	std::vector<Menu*> mergedMenus_;

	/**
	* the total number of newly created documents
	*/
	long documentCount_;
};

}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/24 18:48:56  marcelloptr
*Document Window documentation
*
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


