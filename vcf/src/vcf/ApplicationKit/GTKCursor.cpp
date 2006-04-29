//GTKCursor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKCursor.h"


using namespace VCF;

GTKCursor::GTKCursor( Cursor* cursor ) :
		cursorID_( CursorManager::UNREGISTERED_ID ),
		cursor_( cursor ),
		gtkCursor_( 0 )
{
}

GTKCursor::~GTKCursor()
{
	if ( 0 != gtkCursor_ ) {
		gdk_cursor_unref( gtkCursor_ );
	}
}

void GTKCursor::createFromImage( Image* cursorImage, Point* hotSpot )
{
}

void GTKCursor::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{

	GdkCursorType id = ( GdkCursorType ) 0;

	cursorID_ = ( long ) systemCursor;
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
				id = GDK_LEFT_PTR;
			}
			break;

		case Cursor::SCT_SPLIT_VERT : {
				id = GDK_SB_V_DOUBLE_ARROW;
			}
			break;

		case Cursor::SCT_SPLIT_HORZ : {
				id = GDK_SB_H_DOUBLE_ARROW;
			}
			break;

		case Cursor::SCT_SIZE_HORZ : {
				id = GDK_SB_H_DOUBLE_ARROW;
			}
			break;

		case Cursor::SCT_SIZE_VERT : {
				id = GDK_SB_V_DOUBLE_ARROW;
			}
			break;

		case Cursor::SCT_SIZE_NE_SW : {
				id = GDK_TOP_LEFT_ARROW;
			}
			break;

		case Cursor::SCT_SIZE_NW_SE : {
				id = GDK_TOP_RIGHT_CORNER;
			}
			break;

		case Cursor::SCT_TEXT : {
				id = GDK_XTERM;
			}
			break;

		case Cursor::SCT_HELP : {
				id = GDK_QUESTION_ARROW;
			}
			break;

		case Cursor::SCT_WAIT : {
				id = GDK_WATCH;
			}
			break;

		case Cursor::SCT_WAITING : {
				id = GDK_WATCH;
			}
			break;

		case Cursor::SCT_NOWAYHOSER : {
				id = GDK_X_CURSOR;
			}
			break;

		case Cursor::SCT_CROSSHAIRS : {
				id = GDK_CROSSHAIR;
			}
			break;

		case Cursor::SCT_POINTING_HAND : {
				id = GDK_HAND2;
			}
			break;
	}

	gtkCursor_ = gdk_cursor_new ( id );

}

void GTKCursor::createFromResourceName( const String& cursorName,
                                        OSHandleID instanceHandle )
{
}


/**
$Id$
*/
