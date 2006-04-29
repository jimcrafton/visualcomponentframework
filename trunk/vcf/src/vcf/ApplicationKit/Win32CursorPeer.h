#ifndef _VCF_WIN32CURSORPEER_H__
#define _VCF_WIN32CURSORPEER_H__
//Win32CursorPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Cursor;
/**
*Class Win32CursorPeer documentation
*/
class Win32CursorPeer : public Object, public CursorPeer {
public:
	Win32CursorPeer( Cursor* cursor = NULL);

	virtual ~Win32CursorPeer();

	virtual OSHandleID getCursorHandleID(){
		return (OSHandleID)hCursor_;
	}

	virtual void createFromImage( Image* cursorImage, Point* hotSpot );

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

	virtual void createFromResourceName( const String& cursorName, OSHandleID instanceHandle=0 );

	virtual long getCursorID() {
		return cursorID_;
	}

	virtual void setCursorID( const long& cursorID ) {
		cursorID_ = cursorID;
	}

	virtual Cursor* getCursor() {
		return  cursor_;
	}

	virtual void setCursor( Cursor* cursor ) {
		cursor_ = cursor;
	}
protected:
	static HBITMAP colorDDBToMonoDDB( HBITMAP hbm, DWORD biStyle, WORD biBits, HPALETTE hpal );
	static WORD paletteSize( void* pv );
	static WORD dibNumColors ( void* pv );

	bool isSharedCursor_;
	HCURSOR hCursor_;
	long cursorID_;
	Cursor* cursor_;

};


}; //end of namespace VCF


#endif // _VCF_WIN32CURSORPEER_H__

/**
$Id$
*/
