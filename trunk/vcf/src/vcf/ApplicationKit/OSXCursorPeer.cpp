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

	cursorID_ = (long)systemCursor;
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

void OSXCursorPeer::createFromResourceName( const String& cursorName, const ulong32& instanceHandle )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/27 03:11:40  ddiego
*integrated chrisk changes
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:44  ddiego
*initial OSX ApplicationKit port checkin
*
*/


