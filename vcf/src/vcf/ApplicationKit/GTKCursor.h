#ifndef _VCF_GTKCURSOR_H__
#define _VCF_GTKCURSOR_H__
//GTKCursor.h

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
class GTKCursor : public Object, public CursorPeer {
public:

	GTKCursor( Cursor* cursor );

	virtual ~GTKCursor();

	virtual ulong32 getCursorHandleID(){
		return (ulong32)gtkCursor_;
	}

	virtual void createFromImage( Image* cursorImage, Point* hotSpot );

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

	virtual void createFromResourceName( const String& cursorName, const ulong32& instanceHandle=0 );

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

	long cursorID_;
	Cursor* cursor_;
	GdkCursor* gtkCursor_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2.8.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.1  2003/04/17 04:29:48  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


#endif // _VCF_GTKCURSOR_H__


