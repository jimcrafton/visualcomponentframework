//X11Cursor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Cursor.h"
#include <X11/cursorfont.h>

using namespace VCF;

X11Cursor::X11Cursor( Cursor* cursor ):
	cursorID_(CursorManager::UNREGISTERED_ID),
	cursor_(cursor),
	xCursor_(0),
	isSharedCursor_(false)
{
	//printf( "X11Cursor::X11Cursor( %p )\n", cursor );
}

X11Cursor::~X11Cursor()
{

}

void X11Cursor::createFromImage( Image* cursorImage, Point* hotSpot )
{

}

void X11Cursor::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{
	unsigned int xCursorID = 0;
	cursorID_ = (long)systemCursor;
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			xCursorID = XC_left_ptr;
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			xCursorID = XC_sb_v_double_arrow;
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			xCursorID = XC_sb_h_double_arrow;
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			xCursorID = XC_sb_h_double_arrow;
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			xCursorID = XC_sb_v_double_arrow;
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			xCursorID = XC_top_left_arrow;
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			xCursorID = XC_top_right_corner;
		}
		break;

		case Cursor::SCT_TEXT : {
			xCursorID = XC_xterm;
		}
		break;

		case Cursor::SCT_HELP : {
			xCursorID = XC_question_arrow;
		}
		break;

		case Cursor::SCT_WAIT : {
			xCursorID = XC_watch;
		}
		break;

		case Cursor::SCT_WAITING : {
			xCursorID = XC_watch;
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			xCursorID = XC_X_cursor;
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			xCursorID = XC_crosshair;
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			xCursorID = XC_hand2;
		}
		break;
	}

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	xCursor_ = XCreateFontCursor( toolkit->getX11Display(), xCursorID );
}

void X11Cursor::createFromResourceName( const String& cursorName, const ulong32& instanceHandle )
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
*Revision 1.1.2.4  2003/01/19 03:11:59  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.1.2.3  2003/01/16 04:46:53  ddiego
*added support for default X11 cursors
*added support for translating coordinates from screen to client
*and client to screen, where  the screen is the RootWindow
*
*Revision 1.1.2.2  2003/01/08 03:49:18  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.1.2.1  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
Auto generated C++ implementation for class X11Cursor
*/


