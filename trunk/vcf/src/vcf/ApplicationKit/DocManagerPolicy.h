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
\class SDIPolicy DocManagerPolicy.h "vcf/ApplicationKit/DocManagerPolicy.h"
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

		//destroy the old document if neccessary
		if ( NULL != currentDocument_ ) {
			Component* owner = currentDocument_->getOwner();
			if ( NULL != owner ) {
				owner->removeComponent( currentDocument_ );
				currentDocument_->free();
			}
		}

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
		
		VCF::DocumentManager::getDocumentManager()->DocumentClosed( &event );

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
\class MDIPolicy DocManagerPolicy.h "vcf/ApplicationKit/DocManagerPolicy.h"
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
		

		//StringUtils::traceWithArgs( Format("currentDocument_: %p\n") % result );

		return result;
	}

	/**
	* sets the specified document as the active one in the application
	*/
	void setCurrentDocument( VCF::Document* doc ) {
		

		StringUtils::trace( Format("setCurrentDocument( %p )\n") % doc );

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
		
			VCF::DocumentManager::getDocumentManager()->DocumentClosed( &event );

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


		UIToolkit::postEvent( new EventHandler(MDIPolicy::postQuitEventLoop), new Event(NULL,0) );

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
	int32 documentCount_;
};

}; // namespace VCF


#endif // _VCF_DOCMANAGERPOLICY_H__

/**
$Id$
*/
