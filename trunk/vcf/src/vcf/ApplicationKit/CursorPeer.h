#ifndef _VCF_CURSORPEER_H__
#define _VCF_CURSORPEER_H__
//CursorPeer.h

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
\class CursorPeer CursorPeer.h "vcf/ApplicationKit/CursorPeer.h"
*Class CursorPeer documentation
*/
class APPLICATIONKIT_API CursorPeer {
public:
	virtual ~CursorPeer(){};

	virtual OSHandleID getCursorHandleID() = 0;

	virtual void createFromImage( Image* cursorImage, Point* hotSpot ) = 0;

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor ) = 0;

	virtual void createFromResourceName( const String& cursorName, OSHandleID instanceHandle=NULL ) = 0;

	virtual long getCursorID() = 0;

	virtual void setCursorID( const long& cursorID ) = 0;

	virtual Cursor* getCursor() = 0;

	virtual void setCursor( Cursor* cursor ) = 0;
};


}; //end of namespace VCF


#endif // _VCF_CURSORPEER_H__

/**
$Id$
*/
