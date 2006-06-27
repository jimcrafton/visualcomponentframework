#ifndef _VCF_XCBCURSORPEER_H__
#define _VCF_XCBCURSORPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/CursorPeer.h"

namespace VCF {

	class XCBCursorPeer : public CursorPeer {
	public:
		XCBCursorPeer( Cursor* cursor );

		virtual OSHandleID getCursorHandleID();

		virtual void createFromImage( Image* cursorImage, Point* hotSpot );

		virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

		virtual void createFromResourceName( const String& cursorName, OSHandleID instanceHandle=NULL );

		virtual int32 getCursorID();

		virtual void setCursorID( const int32& cursorID );

		virtual Cursor* getCursor();

		virtual void setCursor( Cursor* cursor );
	};
};

#endif //_VCF_XCBCURSORPEER_H__

/**
$Id$
*/

