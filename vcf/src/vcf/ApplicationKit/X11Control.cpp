//X11Control.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Control.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"

using namespace VCF;



X11Control::X11Control( Control* control )
{
	control_ = control;
	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	X11UIToolkit* toolkit = (X11UIToolkit*)UIToolkit::getDefaultUIToolkit();

	XSetWindowAttributes attrs;
	memset( &attrs, 0, sizeof(XSetWindowAttributes) );
	attrs.background_pixmap = None;
	attrs.background_pixel = 0;
	attrs.border_pixmap = CopyFromParent;
	attrs.border_pixel = 0;
	attrs.bit_gravity = ForgetGravity;
	attrs.win_gravity = NorthWestGravity;
	attrs.backing_store = NotUseful;
	attrs.colormap = CopyFromParent;
	attrs.backing_planes = 0xffffffff;
	attrs.cursor = None;
	attrs.override_redirect = True;

	wndHandle_ = XCreateWindow( grafToolkit->getX11Display(),
										toolkit->getDefaultParentWnd(),
										0, 0, 1, 1, 0,
										CopyFromParent,//DefaultDepth( x11Display_, toolkit->getX11ScreenID() ),
										InputOutput,
										CopyFromParent,//DefaultVisual( x11Display_, toolkit->getX11ScreenID() ),
										0,
										&attrs );

	if ( NULL != wndHandle_ ) {
		int eventMask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;
		eventMask |= FocusChangeMask | PropertyChangeMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask;
		eventMask |= PointerMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask;
		eventMask |= VisibilityChangeMask;
		//eventMask |= SubstructureNotifyMask;


		registerX11Control( this );
		XSelectInput( grafToolkit->getX11Display(), wndHandle_, eventMask );

		toolkit->postToolkitMessage( toolkit->getVCFCreateWindowMsg(), (void*)control_ );

	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("XCreateWindow returned a NULL window ID in creating the peer wind") );
	}
}

X11Control::~X11Control()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:40  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:44  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.5  2003/01/08 03:49:18  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.1.2.4  2003/01/02 04:07:46  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.1.2.3  2002/12/31 07:02:19  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.1.2.2  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.1.2.1  2002/12/27 06:44:45  ddiego
*added initial control peer for X11 controls
*
Auto generated C++ implementation for class X11Control
*/


