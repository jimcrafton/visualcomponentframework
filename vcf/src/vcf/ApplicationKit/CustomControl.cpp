//CustomControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;

	
CustomControl::CustomControl():
	Control(),
	isLightweight_(false),
	isTransparent_(false),
	useColorForBackground_(false)
{
	peer_ =	UIToolkit::createControlPeer( this );
	peer_->create( this );

	init();
}

CustomControl::CustomControl( const bool& useHeavyweightPeer ):
	Control(),
	isLightweight_(!useHeavyweightPeer),
	isTransparent_(false),
	useColorForBackground_(false)
{
	if ( isLightweight_ ){
		peer_ = UIToolkit::createControlPeer( this, CT_LIGHTWEIGHT );
	}
	else{
		peer_ = UIToolkit::createControlPeer( this, CT_HEAVYWEIGHT );
	}

	peer_->create( this );
	init();
}

CustomControl::~CustomControl()
{
}

void CustomControl::paint(GraphicsContext * context)
{
	if ( NULL != getView() ) {
		getView()->paintView( context );
		return;
	}


	

	Rect innerBounds = getClientBounds( true );//we DO need to account for the border here

	

	if ( (!isTransparent_) || (!isLightWeight()) ){
		if ( useColorForBackground_ ) {
			context->setColor( getColor() );
			
			context->rectangle( &innerBounds );
			
			context->fillPath();		
		}
		else {	
			BackgroundState bkg;
			bkg.setEnabled( isEnabled() );
			bkg.setActive( isActive() );
			bkg.colorType_ = SYSCOLOR_FACE;	
			
			context->drawThemeBackground( &innerBounds, bkg );
		}
	}

	context->setCurrentFont( getFont() );

	Scrollable* scrollable = getScrollable();
	if ( scrollable ) {
		Rect viewBounds = context->getViewableBounds();

		Point origin = context->getOrigin();

		adjustViewableBoundsAndOriginForScrollable( context, viewBounds, origin );

		context->setOrigin( origin );

		context->setViewableBounds( viewBounds );
	}
}

void CustomControl::init()
{
	setEnabled( true );
	setVisible( true );
	setFocused();
}

bool CustomControl::isLightWeight()
{
	return isLightweight_;
}

bool CustomControl::isTransparent()
{
	return isTransparent_;
}

void CustomControl::setTransparent( const bool& transparent )
{
	isTransparent_ = transparent;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:20  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 21:30:19  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.17  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.3  2003/10/13 04:02:52  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.16.2.2  2003/09/25 04:00:26  ddiego
*minor fixes to better adjust the voewable bounds when scrolling is enabled
*added a Scrolling example
*
*Revision 1.16.2.1  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.16  2003/08/09 02:56:45  ddiego
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
*Revision 1.15.2.4  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.15.2.3  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.15.2.2  2003/06/01 16:44:01  ddiego
*further GTK support added
*
*Revision 1.15.2.1  2003/05/27 04:45:39  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.15  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.4  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.14.2.3  2003/04/17 04:29:52  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.14.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:13:05  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.13.2.1  2002/12/27 23:05:00  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.13  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.12.10.2  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.12.10.1  2002/10/01 20:34:59  ddiego
*borders
*
*Revision 1.12  2002/03/21 04:01:22  ddiego
*fixed [ 532894 ] bug using the Frame::setClientBounds()
*
*Revision 1.11  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


