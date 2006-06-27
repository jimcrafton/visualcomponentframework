#ifndef _VCF_X11CURSOR_H__
#define _VCF_X11CURSOR_H__
//X11Cursor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**

*/
class X11Cursor : public Object, public CursorPeer {
public:

	X11Cursor( Cursor* cursor );

	virtual ~X11Cursor();

	virtual uint32 getCursorHandleID(){
		return (uint32)xCursor_;
	}

	virtual void createFromImage( Image* cursorImage, Point* hotSpot );

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

	virtual void createFromResourceName( const String& cursorName, const uint32& instanceHandle=0 );

	virtual int32 getCursorID() {
		return cursorID_;
	}

	virtual void setCursorID( const int32& cursorID ) {
		cursorID_ = cursorID;
	}

	virtual Cursor* getCursor() {
		return  cursor_;
	}

	virtual void setCursor( Cursor* cursor ) {
		cursor_ = cursor;
	}
protected:

	bool isSharedCursor_;

	int32 cursorID_;
	Cursor* cursor_;
	xLib::Cursor xCursor_;
};


};


#endif // _VCF_X11CURSOR_H__

/**
$Id$
*/
