#ifndef _VCF_SCROLLPEER_H__
#define _VCF_SCROLLPEER_H__
//ScrollPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Control;

class Scrollable;

/**
*Class ScrollPeer documentation
*/
class APPLICATIONKIT_API ScrollPeer : public Interface {
public:
	virtual ~ScrollPeer(){};

	virtual void scrollTo( const double& xPosition, const double& yPosition ) = 0;

	virtual void getAdjustedPositions( double& xPosition, double& yPosition ) = 0;

	virtual bool isVerticalScrollbarVisible() = 0;

	virtual bool isHorizontalScrollbarVisible() = 0;
	
	virtual void recalcScrollPositions( Scrollable* scrollable ) = 0;

	virtual Control* getScrollableControl() = 0;

	virtual void setScrollableControl( Control* scrollableControl ) = 0;

	virtual double getHorizontalScrollbarHeight() = 0;

	virtual double getVerticalScrollbarWidth() = 0;

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL ) = 0;

	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL ) = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/21 05:39:48  dougtinkham
*removed updateVirtualViewSize, added isVerticalScrollbarVisible, isHorizontalScrollbarVisible
*
*Revision 1.2.2.1  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.1  2004/03/21 20:25:03  marcelloptr
*Scrollable automatically calculates the scroll given the line where to go
*
*Revision 1.3  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.20.3  2003/10/13 04:01:50  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.2.20.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.20.1  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.2  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/05/01 01:19:50  ddiego
*added remaining new files from switching stuff around
*like the peer classes and some of the drag drop stuff
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SCROLLPEER_H__


