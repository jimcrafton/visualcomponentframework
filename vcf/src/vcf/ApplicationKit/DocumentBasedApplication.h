#ifndef _VCF_DOCUMENTBASEDAPPLICATION_H__
#define _VCF_DOCUMENTBASEDAPPLICATION_H__
//DocumentBasedApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class DocumentBasedApplication DocumentBasedApplication.h "vcf/ApplicationKit/DocumentBasedApplication.h"
*/
template <typename DocInterfacePolicy >
class DocumentBasedApplication : public Application,
								public DocumentManagerImpl< DocumentBasedApplication<DocInterfacePolicy>, DocInterfacePolicy> {
public:

	DocumentBasedApplication( int argc, char** argv ) : Application(argc, argv){

	}

	typedef DocumentManagerImpl<DocumentBasedApplication<DocInterfacePolicy>,DocInterfacePolicy> DocMgrImpl;

	virtual bool initRunningApplication() {
		Application::initRunningApplication();

		DocMgrImpl::init();
		DocMgrImpl::createMenus();

		return true;
	}

	void terminateRunningApplication() {
		DocMgrImpl::terminate();

		Application::terminateRunningApplication();
	}
};



typedef DocumentBasedApplication<SDIPolicy> SDIDocumentBasedApplication;
typedef DocumentBasedApplication<MDIPolicy> MDIDocumentBasedApplication;


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.2  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.3  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.2.2.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.2.1  2003/08/13 02:53:24  ddiego
*some more app changes to take advantage of the new constructor parameters
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


#endif // _VCF_DOCUMENTBASEDAPPLICATION_H__


