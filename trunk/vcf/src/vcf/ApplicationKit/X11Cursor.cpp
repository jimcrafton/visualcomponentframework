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
$Id$
*/
