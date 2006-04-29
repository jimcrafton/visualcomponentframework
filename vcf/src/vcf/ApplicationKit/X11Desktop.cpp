//X11Desktop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Desktop.h"

using namespace VCF;

X11Desktop::X11Desktop( Desktop* desktop )
{

}

X11Desktop::~X11Desktop()
{

}


void X11Desktop::desktopBeginPainting( Rect* clippingRect )
{

}

/**
*called after finished painting on the desktop
*allows for native Windowing system cleanup to happen
*/
void X11Desktop::desktopEndPainting()
{

}

bool X11Desktop::desktopSupportsVirtualDirectories()
{
	bool result = false;

	return result;
}

bool X11Desktop::desktopHasFileSystemDirectory()
{
	bool result = false;

	return result;
}

String X11Desktop::desktopGetDirectory()
{
	return "";
}

ulong32 X11Desktop::desktopGetHandleID()
{
	ulong32 result = 0;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();
	result = (ulong32) DefaultRootWindow( display );

	return result;
}

ulong32 X11Desktop::desktopGetGraphicsContextHandleID()
{
	ulong32 result = desktopGetHandleID();
	//printf( "desktopGetHandleID(): %d\n", result );
	return result;
}

void X11Desktop::desktopSetDesktop( Desktop* desktop )
{

}

void X11Desktop::desktopTranslateToScreenCoords( Control* control, Point* pt )
{
	//printf( "X11Desktop::desktopTranslateToScreenCoords( %p, [%.3f, %.3f] )\n",
		//		control, pt->x_, pt->y_ );


	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();
	xLib::Window rootWnd = (ulong32) DefaultRootWindow( display );
	xLib::Window controlWnd = (xLib::Window)control->getPeer()->getHandleID();
	int x = pt->x_;
	int y = pt->y_;

	int x2 = pt->x_;
	int y2 = pt->y_;
	xLib::Window child = NULL;
	if ( True == XTranslateCoordinates( display, controlWnd, rootWnd, x, y, &x2, &y2, &child ) ) {
		pt->x_ = x2;
		pt->y_ = y2;
	}
	else {

		throw RuntimeException( MAKE_ERROR_MSG_2("XTranslateCoordinates() failed") );//an exception! ???
	}
}

void X11Desktop::desktopTranslateFromScreenCoords( Control* control, Point* pt )
{
	//printf( "X11Desktop::desktopTranslateFromScreenCoords( %p, [%.3f, %.3f] )\n",
		//		control, pt->x_, pt->y_ );

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();
	xLib::Window rootWnd = (ulong32) DefaultRootWindow( display );
	xLib::Window controlWnd = (xLib::Window)control->getPeer()->getHandleID();
	int x = pt->x_;
	int y = pt->y_;

	int x2 = pt->x_;
	int y2 = pt->y_;
	xLib::Window child = NULL;
	if ( True == XTranslateCoordinates( display, rootWnd, controlWnd, x, y, &x2, &y2, &child ) ) {
		pt->x_ = x2;
		pt->y_ = y2;
	}
	else {
		//throw an exception! ???
	}
}

ulong32 X11Desktop::desktopGetWidth()
{
	ulong32 result = 0;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();

	result = DisplayWidth( display, toolkit->getX11ScreenID() );

	return result;
}

ulong32 X11Desktop::desktopGetHeight()
{
	ulong32 result = 0;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();

	result = DisplayHeight( display, toolkit->getX11ScreenID() );

	return result;
}


Rect X11Desktop::desktopGetUsableBounds()
{
	Rect result;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* display = toolkit->getX11Display();
	int screenID = toolkit->getX11ScreenID();

	result.left_ = 0.0;
	result.top_ = 0.0;

	result.right_ = DisplayWidth( display, screenID );
	result.bottom_ = DisplayHeight( display, screenID );

	return result;
}


/**
$Id$
*/
