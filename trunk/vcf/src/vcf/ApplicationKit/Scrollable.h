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
	Scrollable(){
	};

	virtual ~Scrollable(){
	};

	/**
	* sets if the vertical scrolbar is ever visible
	*@param const bool& hasVerticalScrollbar, false if it is never visible.
	*/
	virtual void setHasVerticalScrollbar( const bool& hasVerticalScrollbar ) = 0;

	/**
	* sets if the orizontal scrolbar is ever visible
	*@param const bool& hasHorizontalScrollbar, false if it is never visible.
	*/
	virtual void setHasHorizontalScrollbar( const bool& hashorizontalScrollbar ) = 0;

	/**
	* tells if the vertical scrolbar is ever visible
	*/
	virtual bool hasVerticalScrollBar() = 0;

	/**
	* tells if the orizontal scrolbar is ever visible
	*/
	virtual bool hasHorizontalScrollBar() = 0;

	/**
	* gets the height of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	virtual double getVirtualViewHeight() = 0;

	/**
	* gets the width of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	virtual double getVirtualViewWidth() = 0;

	/**
	* sets the height of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	virtual void setVirtualViewHeight( const double& virtualViewHeight ) = 0;

	/**
	* sets the width of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	virtual void setVirtualViewWidth( const double& virtualViewWidth ) = 0;

	/**
	* sets the size (dimensions) of the area that needs to be displayed.
	* For example if we want to show an image, this size will be set 
	* the same as the size of the image.
	* The name virtual comes from the fact that it can be partly hidden.
	* This area can be larger of the area actually displayed, and in this case
	* the scrollbars will appear if not visible.
	*/
	virtual void setVirtualViewSize( const double& width, const double& height ) = 0;

	/**
	* sets how many pixel we want to vertically scroll the area to be displayed
	* when pressing the arrows of the vertical scrollbar.
	*/
	virtual void setVirtualViewVertStep( const double& step ) = 0;

	/**
	* sets how many pixel we want to horizontally scroll the area to be displayed
	* when pressing the arrows of the horizontal scrollbar.
	*/
	virtual void setVirtualViewHorzStep( const double& step ) = 0;

	/**
	* tells how many pixel we want the area to be displayed will be vertically 
	* scrolled when pressing the arrows of the vertical scrollbar.
	*/
	virtual double getVirtualViewVertStep() = 0;

	/**
	* tells how many pixel we want the area to be displayed will be vertically 
	* scrolled when pressing the arrows of the vertical scrollbar.
	*/
	virtual double getVirtualViewHorzStep() = 0;

	/**
	* tells if the vertical scollbar is actually visible.
	*/
	virtual bool isVerticalScrollbarVisible() = 0;

	/**
	* tells if the horizontal scollbar is actually visible.
	*/
	virtual bool isHorizontalScrollbarVisible() = 0;	

	/**
	* recalculates all the positions and visibility status of all
	* the scrollbars connected to a control.
	* This function must be called after some changes have been made
	* on the target, the size of the object to scroll, or any scrollbar.
	*/
	virtual void recalcScrollPositions() = 0;

	/**
	* moves the scrollbox of a vertical scrollbar to the specified position.
	* Keep in mind that the final position may differ fom the specified 
	* one because the OS may change that actual position because of
	* roundings and other considerations related to the position 
	* of other controls.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	virtual void setVerticalPosition( const double& vertPosition ) = 0;

	/**
	* moves the scrollbox of a vertical scrollbar to the specified position.
	* Keep in mind that the final position may differ fom the specified 
	* one because the OS may change that actual position because of
	* roundings and other considerations related to the position 
	* of other controls.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	virtual void setHorizontalPosition( const double& horzPosition ) = 0;

	/**
	* gets the position of the scrollbox of a vertical scrollbar.
	* This position is always the one adjusted by the OS according
	* to internal considerations.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	virtual double getVerticalPosition() = 0;

	/**
	* gets the position of the scrollbox of a horizontal scrollbar.
	* This position is always the one adjusted by the OS according 
	* to internal considerations.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	virtual double getHorizontalPosition() = 0;

	/**
	* gets the height of the space above the vertical scrollbar.
	*/
	virtual double getVerticalTopScrollSpace() = 0;

	/**
	* gets the height of the space below the vertical scrollbar.
	*/
	virtual double getVerticalBottomScrollSpace() = 0;

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the top of the vertical scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	virtual void setVerticalTopScrollSpace( const double& topScrollSpace ) = 0;

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the bottom of the vertical scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	virtual void setVerticalBottomScrollSpace( const double& bottomScrollSpace ) = 0;

	/**
	* gets the width of the space on the left of the horizontal scrollbar.
	*/
	virtual double getHorizontalLeftScrollSpace() = 0;

	/**
	* gets the width of the space on the right of the horizontal scrollbar.
	*/
	virtual double getHorizontalRightScrollSpace() = 0;

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the left of the horizontal scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	virtual void setHorizontalLeftScrollSpace( const double& leftScrollSpace ) = 0;

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the right of the horizontal scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	virtual void setHorizontalRightScrollSpace( const double& rightScrollSpace ) = 0;

	/**
	* gets the control this scrollable has been assogiated to.
	*@see setScrollableControl()
	*/
	virtual Control* getScrollableControl() = 0;

	/**
	* sets the target control for the scrolling operation of the scrollable
	* instance. At this point the scrollbars will be resized with the control
	* and it's content will be scrolled by the scrollable.
	*@see ScrollbarManager::setTarget()
	*@see Control::setScrollable()
	*/
	virtual void setScrollableControl( Control* scrollableControl ) = 0;

	/**
	* gets the height ( the 'thickness' ) of an horizontal scrollbar.
	*/
	virtual double getHorizontalScrollbarHeight() = 0;

	/**
	* gets the width ( the 'thickness' ) of a vertical scrollbar.
	*/
	virtual double getVerticalScrollbarWidth() = 0;

	/**
	* this will retrieves the values for three rectangular bounds, the bounds
	* of the scroll bar portion, the bounds of the left most spacer, and the
	* bounds of the right most spacer.
	* If a scroll bar has it's left and/or right scroll space set to 0, then the
	* right and left bounds for the spacers may be null, or a rect of (0,0,0,0).
	*@param Rect scrollBounds, the bounds of the actual horizontal scroll bar rect,
	* if this is NULL no value is returned
	*@param Rect leftBounds, the bounds of the left spacer rect,
	* if this is NULL no value is set
	*@param Rect rightBounds, the bounds of the right spacer rect,
	* if this is NULL no value is set
	*/
	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL ) = 0;

	/**
	* this will retrieves the values for three rectangular bounds, the bounds
	* of the scroll bar portion, the bounds of the left most spacer, and the
	* bounds of the right most spacer.
	* If a scroll bar has it's left and/or right scroll space set to 0, then the
	* right and left bounds for the spacers may be null, or a rect of (0,0,0,0).
	*@param Rect scrollBounds, the bounds of the actual vertical scroll bar rect,
	* if this is NULL no value is set
	*@param Rect topBounds, the bounds of the top spacer rect,
	* if this is NULL no value is set
	*@param Rect bottomBounds, the bounds of the bottom spacer rect,
	* if this is NULL no value is set
	*/
	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL ) = 0;

	/**
	* this allows you to control whether or not the scrollbars disappear when they are no longer needed.
	* By default this is false, which means that the scrollabars will disappear when the virtual width
	* or height is less than the control's actual width or height. If this is true, then the
	* scrollbars will stay visible, but become disabled.
	*@param bool visible, true if we want it visible
	*/
	virtual void setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible ) = 0;

	/**
	* gets whether or not the scrollbars disappear when they are no longer needed.
	* @return true if they stay visible even when not needed
	*/
	virtual bool getKeepHorzScrollbarVisible() = 0;
	virtual bool getKeepVertScrollbarVisible() = 0;

	/**
	* this allows you to control whether or not the scrolling needs to be discrete or not.
	* By default this is false, ( i.e. rounded to the same amount indicated by getVirtualViewStep ).
	*@param bool visible, true if we want it visible
	*/
	virtual void setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete ) = 0;

	/**
	* gets whether or not the scrolling needs to be discrete or not.
	*@return true if the scrolling is discrete.
	*/
	virtual bool getDiscreteHorzScroll() = 0;
	virtual bool getDiscreteVertScroll() = 0;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/06/25 21:05:52  marcelloptr
*minor fix on a comment
*
*Revision 1.3.2.3  2005/01/17 17:52:19  marcelloptr
*bugfix [ 1099910 ] plus other improvements of the scrolling
*
*Revision 1.3.2.1  2005/01/13 19:41:48  marcelloptr
*scrollable documentation and related
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.3  2004/09/21 05:51:55  dougtinkham
*removed updateVirtualViewSize, added isVerticalScrollbarVisible, isHorizontalScrollbarVisible
*
*Revision 1.2.2.2  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.1  2004/09/10 22:28:10  dougtinkham
*added updateVirtualViewSize member
*
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


