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
    cursorHandle_(0)
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
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			//id = GDK_LEFT_PTR;
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			//id = GDK_SB_V_DOUBLE_ARROW;
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			//id = GDK_SB_H_DOUBLE_ARROW;
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			//id = GDK_SB_H_DOUBLE_ARROW;
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			//id = GDK_SB_V_DOUBLE_ARROW;
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			//id = GDK_TOP_LEFT_ARROW;
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			//id = GDK_TOP_RIGHT_CORNER;
		}
		break;

		case Cursor::SCT_TEXT : {
			//id = GDK_XTERM;
		}
		break;

		case Cursor::SCT_HELP : {
			//id = GDK_QUESTION_ARROW;
		}
		break;

		case Cursor::SCT_WAIT : {
			//id = GDK_WATCH;
		}
		break;

		case Cursor::SCT_WAITING : {
			//id = GDK_WATCH;
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			//id = GDK_X_CURSOR;
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			//id = GDK_CROSSHAIR;
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			//id = GDK_HAND2;
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


