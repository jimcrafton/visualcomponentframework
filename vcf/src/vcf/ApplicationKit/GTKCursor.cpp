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
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


