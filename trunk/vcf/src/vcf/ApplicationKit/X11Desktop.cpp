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
*Revision 1.2.2.1  2003/03/12 03:12:45  ddiego
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
*Revision 1.1.2.4  2003/02/03 05:22:54  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.1.2.3  2003/01/19 03:11:59  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.1.2.2  2003/01/16 04:46:53  ddiego
*added support for default X11 cursors
*added support for translating coordinates from screen to client
*and client to screen, where  the screen is the RootWindow
*
*Revision 1.1.2.1  2002/12/26 04:32:12  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
Auto generated C++ implementation for class X11Desktop
*/


