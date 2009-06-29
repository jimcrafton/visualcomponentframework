#ifndef _VCF_CURSOR_H__
#define _VCF_CURSOR_H__
//Cursor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class CursorPeer;

/**
\class Cursor Cursor.h "vcf/ApplicationKit/Cursor.h"
Class Cursor documentation
*/
class APPLICATIONKIT_API Cursor : public HeapObject {
public:
	enum SystemCursorType{
		SCT_DEFAULT=0,
		SCT_CROSSHAIRS,
		SCT_SPLIT_VERT,
		SCT_SPLIT_HORZ,
		SCT_SIZE_HORZ,
		SCT_SIZE_VERT,
		SCT_SIZE_NE_SW,
		SCT_SIZE_NW_SE,
		SCT_TEXT,
		SCT_HELP,
		SCT_NOWAYHOSER,
		SCT_WAITING,
		SCT_POINTING_HAND,
		SCT_WAIT
	};

	Cursor( const SystemCursorType& systemCursor );

	Cursor( Image* cursorImage, Point* hotSpot );

	Cursor( const String& cursorName, AbstractApplication* application=NULL );

	virtual ~Cursor();

	int32 getCursorID();

	void setCursorFromID( const int32& cursorID );

	CursorPeer* getPeer();

	static void registerConstants();
protected:
	CursorPeer* peer_;

	static String getCursorConstants( const String& name );
};


}; //end of namespace VCF


#endif // _VCF_CURSOR_H__

/**
$Id$
*/
