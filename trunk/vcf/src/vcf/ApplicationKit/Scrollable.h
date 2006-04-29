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
\class Scrollable Scrollable.h "vcf/ApplicationKit/Scrollable.h"
This class is used to add scrolling support to a control.
@see ScrollbarManager
*/
class APPLICATIONKIT_API Scrollable : public Interface {
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


#endif // _VCF_SCROLLABLE_H__

/**
$Id$
*/
