#ifndef _VCF_SCROLLABLE_H__
#define _VCF_SCROLLABLE_H__
//Scrollable.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
*Class Scrollable documentation
*/
class Scrollable : public Interface {
public:
	virtual ~Scrollable(){};

	virtual void setHasVerticalScrollbar( const bool& hasVerticalScrollbar ) = 0;

	virtual void setHasHorizontalScrollbar( const bool& hashorizontalScrollbar ) = 0;

	virtual bool hasVerticalScrollBar() = 0;

	virtual bool hasHorizontalScrollBar() = 0;

	virtual double getVirtualViewHeight() = 0;

	virtual double getVirtualViewWidth() = 0;

	virtual void setVirtualViewHeight( const double& virtualViewHeight ) = 0;

	virtual void setVirtualViewWidth( const double& virtualViewWidth ) = 0;

	virtual void recalcScrollPositions() = 0;

	virtual void setVerticalPosition( const double& vertPosition ) = 0;

	virtual void setHorizontalPosition( const double& horzPosition ) = 0;

	virtual double getVerticalPosition() = 0;

	virtual double getHorizontalPosition() = 0;

	virtual double getVerticalTopScrollSpace() = 0;

	virtual double getVerticalBottomScrollSpace() = 0;

	virtual void setVerticalTopScrollSpace( const double& topScrollSpace ) = 0;

	virtual void setVerticalBottomScrollSpace( const double& bottomScrollSpace ) = 0;

	virtual double getHorizontalLeftScrollSpace() = 0;

	virtual double getHorizontalRightScrollSpace() = 0;

	virtual void setHorizontalLeftScrollSpace( const double& leftScrollSpace ) = 0;

	virtual void setHorizontalRightScrollSpace( const double& rightScrollSpace ) = 0;

	virtual Control* getScrollableControl() = 0;

	virtual void setScrollableControl( Control* scrollableControl ) = 0;

	virtual double getHorizontalScrollbarHeight() = 0;

	virtual double getVerticalScrollbarWidth() = 0;

	/**
	this will retrieves the values for three rectangular bounds, the bounds
	of the scroll bar portion, the bounds of the left most spacer, and the
	bounds of the right most spacer.
	If a scroll bar has it's left and/or right scroll space set to 0, then the
	right and left bounds for the spacers may be null, or a rect of (0,0,0,0).
	@param Rect scrollBounds, the bounds of the actual horizontal scroll bar rect,
	if this is NULL no value is returned
	@param Rect leftBounds, the bounds of the left spacer rect,
	if this is NULL no value is set
	@param Rect rightBounds, the bounds of the right spacer rect,
	if this is NULL no value is set
	*/
	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL ) = 0;

	/**
	this will retrieves the values for three rectangular bounds, the bounds
	of the scroll bar portion, the bounds of the left most spacer, and the
	bounds of the right most spacer.
	If a scroll bar has it's left and/or right scroll space set to 0, then the
	right and left bounds for the spacers may be null, or a rect of (0,0,0,0).
	@param Rect scrollBounds, the bounds of the actual vertical scroll bar rect,
	if this is NULL no value is set
	@param Rect topBounds, the bounds of the top spacer rect,
	if this is NULL no value is set
	@param Rect bottomBounds, the bounds of the bottom spacer rect,
	if this is NULL no value is set
	*/
	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL ) = 0;

	virtual void setKeepScrollbarsVisible( const bool& val )  = 0;
	virtual bool getKeepScrollbarsVisible()  = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.26.4  2003/10/13 04:00:23  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.4.26.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.4.26.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4.26.1  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.4  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SCROLLABLE_H__


