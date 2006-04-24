//HTMLBrowserControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//HTMLBrowserControl.h
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"
#include "vcf/HTMLKit/HTMLBrowserPeer.h"


using namespace VCF;


HTMLBrowserControl::HTMLBrowserControl():
	browserPeer_(NULL),
	policyState_(0)
{
	browserPeer_ = HTMLToolkit::createHTMLBrowserPeer( this );

	if ( NULL == browserPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_ = dynamic_cast<ControlPeer*>(browserPeer_);
	
	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );
	setVisible( true );

	policyState_ |= HTMLBrowserControl::hpAllowPopups;
	policyState_ |= HTMLBrowserControl::hpAllowDefaultContextMenu;
	policyState_ |= HTMLBrowserControl::hpUseDefaultAuthenticationUI;
	policyState_ |= HTMLBrowserControl::hpAllowsScrollbars;
	policyState_ |= HTMLBrowserControl::hpAllowsTextSelection;

}

HTMLBrowserControl::~HTMLBrowserControl()
{

}

void HTMLBrowserControl::paint( GraphicsContext* ctx )
{

}

void HTMLBrowserControl::afterCreate( ComponentEvent* e )
{

}

String HTMLBrowserControl::getCurrentURL()
{
	return browserPeer_->getCurrentURL();
}

void HTMLBrowserControl::setCurrentURL( const String& url )
{
	browserPeer_->setCurrentURL( url );
}

void HTMLBrowserControl::goBack()
{
	browserPeer_->goBack();
}

void HTMLBrowserControl::goForward()
{
	browserPeer_->goForward();
}

void HTMLBrowserControl::goHome()
{
	browserPeer_->goHome();
}

void HTMLBrowserControl::refresh()
{
	browserPeer_->refresh();
}

bool HTMLBrowserControl::isLoadingURL()
{
	return browserPeer_->isLoadingURL();
}

void HTMLBrowserControl::stopLoadingURL()
{
	browserPeer_->stopLoadingURL();
}

void HTMLBrowserControl::setFromHTML( const String& html )
{
	browserPeer_->setFromHTML( html );
}

String HTMLBrowserControl::getTitle()
{
	return browserPeer_->getTitle();
}

void HTMLBrowserControl::edit( const bool& val )
{
	browserPeer_->edit( val );
}

void HTMLBrowserControl::copy()
{
	browserPeer_->copy() ;
}

void HTMLBrowserControl::selectAll()
{
	browserPeer_->selectAll() ;
}

void HTMLBrowserControl::setAllowsPopupWindows( bool val )
{	
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowPopups;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowPopups;
	}

	browserPeer_->setAllowsPopupWindows( val ) ;
}


void HTMLBrowserControl::setAllowsScrollbars( bool val )
{
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowsScrollbars;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowsScrollbars;
	}	

	browserPeer_->setAllowsScrollbars( val ) ;
}


void HTMLBrowserControl::setAllowsTextSelection( bool val )
{
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowsTextSelection;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowsTextSelection;
	}

	browserPeer_->setAllowsTextSelection( val ) ;
}


String HTMLBrowserControl::getElementHTMLText( const String& elementName )
{
	return browserPeer_->getElementHTMLText( elementName ) ;
}

void HTMLBrowserControl::setElementHTMLText( const String& elementName, const String& html )
{
	browserPeer_->setElementHTMLText( elementName, html ) ;
}

String HTMLBrowserControl::getElementText( const String& elementName )
{
	return browserPeer_->getElementText( elementName ) ;
}

void HTMLBrowserControl::setElementText( const String& elementName, const String& text )
{
	browserPeer_->setElementText( elementName, text ) ;
}

String HTMLBrowserControl::getActiveElementID()
{
	return browserPeer_->getActiveElementID() ;
}

String HTMLBrowserControl::getElementIDFromPoint( Point* pt )
{
	return browserPeer_->getElementIDFromPoint(pt) ;
}

bool HTMLBrowserControl::setElementClickedEventHandler( const String& elementName, EventHandler* handler )
{
	return browserPeer_->setElementClickedEventHandler( elementName, handler );
}

HTMLDocument HTMLBrowserControl::getDocument()
{	
	return browserPeer_->getDocument();
}



/**
*CVS Log info
*$Log$
*Revision 1.2  2006/04/07 02:35:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.1.2.1  2006/03/06 03:48:31  ddiego
*more docs, plus update add-ins, plus migrated HTML browser code to a new kit called HTMLKit.
*
*Revision 1.3.2.3  2006/02/15 05:14:33  ddiego
*more browser code.
*
*Revision 1.3.2.2  2006/02/14 05:13:09  ddiego
*more browser updates.
*
*Revision 1.3.2.1  2006/02/13 22:11:59  ddiego
*added further html support and better browser example code.
*
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/02/27 01:45:33  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.7  2003/08/09 02:56:45  ddiego
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
*Revision 1.6.2.2  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.6.2.1  2003/05/27 04:45:40  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.6  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.5.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:13:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.2  2002/04/27 15:52:50  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.3.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


