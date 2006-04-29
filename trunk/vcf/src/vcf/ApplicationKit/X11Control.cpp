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
$Id$
*/
