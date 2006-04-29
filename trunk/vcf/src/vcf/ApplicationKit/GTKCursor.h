#ifndef _VCF_GTKCURSOR_H__
#define _VCF_GTKCURSOR_H__ 
//GTKCursor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

/**
 
*/
class GTKCursor : public Object, public CursorPeer
{
public:

	GTKCursor( Cursor* cursor );

	virtual ~GTKCursor();

	virtual OSHandleID getCursorHandleID()
	{
		return gtkCursor_;
	}

	virtual void createFromImage( Image* cursorImage, Point* hotSpot );

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

	virtual long getCursorID()
	{
		return cursorID_;
	}

	virtual void setCursorID( const long& cursorID )
	{
		cursorID_ = cursorID;
	}

	virtual Cursor* getCursor()
	{
		return cursor_;
	}

	virtual void setCursor( Cursor* cursor )
	{
		cursor_ = cursor;
	}

	virtual void createFromResourceName( const String& cursorName,
	                                     OSHandleID instanceHandle = 0 );

protected:

	long cursorID_;
	Cursor* cursor_;
	GdkCursor* gtkCursor_;
};


};


#endif // _VCF_GTKCURSOR_H__

/**
$Id$
*/
