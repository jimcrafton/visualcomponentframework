#ifndef _VCF_OSXCURSORPEER_H__
#define _VCF_OSXCURSORPEER_H__
//OSXCursorPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**

*/
class OSXCursorPeer : public Object, public CursorPeer {
public:

	OSXCursorPeer( Cursor* cursor );

	virtual ~OSXCursorPeer();

	virtual OSHandleID getCursorHandleID(){
		return (OSHandleID)cursorHandle_;
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
	
	bool isSystemCursor() {
		return isSystemCursor_;
	}

protected:
	bool isSystemCursor_;
	ThemeCursor cursorID_; 
	Cursor* cursor_;
    CCrsrHandle cursorHandle_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
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
*Revision 1.1.2.4  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXCURSORPEER_H__


