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
*Class CursorPeer documentation
*/
class APPLICATIONKIT_API CursorPeer {
public:
	virtual ~CursorPeer(){};

	virtual OSHandleID getCursorHandleID() = 0;

	virtual void createFromImage( Image* cursorImage, Point* hotSpot ) = 0;

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor ) = 0;

	virtual void createFromResourceName( const String& cursorName, OSHandleID instanceHandle=0 ) = 0;

	virtual long getCursorID() = 0;

	virtual void setCursorID( const long& cursorID ) = 0;

	virtual Cursor* getCursor() = 0;

	virtual void setCursor( Cursor* cursor ) = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.26.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.2.26.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CURSORPEER_H__


