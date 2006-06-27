//OSXCursorPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"


using namespace VCF;

OSXCursorPeer::OSXCursorPeer( Cursor* cursor ):
	cursorID_(CursorManager::UNREGISTERED_ID),
	cursor_(cursor),
    cursorHandle_(0),
	isSystemCursor_(false)
{
    cursorHandle_ = GetCCursor(0);
}

OSXCursorPeer::~OSXCursorPeer()
{
    if( NULL != cursorHandle_ ) {
        DisposeCCursor( cursorHandle_ );
    }
}

void OSXCursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{

}

void OSXCursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{

	cursorID_ = (int32)systemCursor;
	isSystemCursor_ = true;

	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			cursorID_ = kThemeArrowCursor;
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			cursorID_ = kThemeResizeLeftRightCursor;
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			cursorID_ = kThemeResizeLeftRightCursor;  //Wrong mapping
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			cursorID_ = kThemeResizeLeftRightCursor;  //Wrong mapping
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			cursorID_ = kThemeResizeLeftRightCursor;
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			cursorID_ = kThemeCrossCursor;
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			cursorID_ = kThemeCrossCursor;
		}
		break;

		case Cursor::SCT_TEXT : {
			cursorID_ = kThemeIBeamCursor;
		}
		break;

		case Cursor::SCT_HELP : {
			cursorID_ = kThemeArrowCursor;    //Wrong mapping
		}
		break;

		case Cursor::SCT_WAIT : {
			cursorID_ = kThemeSpinningCursor;
		}
		break;

		case Cursor::SCT_WAITING : {
//			/cursorID_ = kThemeArrowCursor;    //Wrong mapping
			cursorID_ = kThemeSpinningCursor;
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			cursorID_ = kThemeArrowCursor;    //Wrong mapping
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			cursorID_ = kThemeCrossCursor;
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			cursorID_ = kThemePointingHandCursor;
		}
		break;
	}
}

void OSXCursorPeer::createFromResourceName( const String& cursorName, OSHandleID instanceHandle )
{

}


/**
$Id$
*/
