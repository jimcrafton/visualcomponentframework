#ifndef _VCF_SCROLLBARMANAGER_H__
#define _VCF_SCROLLBARMANAGER_H__
//ScrollbarManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define SCROLLBARMANAGER_CLASSID		"9dac628d-a522-4a59-b255-8f825b78681d"


namespace VCF  {

/**
\class ScrollbarManager ScrollbarManager.h "vcf/ApplicationKit/ScrollbarManager.h"
*The ScrollbarManager represents a component used for managing
*scrolbars for a target control.
*The target control is specified and then a Scrollable instance is associated
*with the target. The manager componenent also exposes the Scrollable object's
*properties, allowing the developer to work with them at design time as well
*as programmatically.
*/
class APPLICATIONKIT_API ScrollbarManager : public Component {
public:

	/**
	@delegate VerticalScrolling
	@event ScrollEvent
	*/
	DELEGATE(ScrollDelegate,VerticalScrolling)

	/**
	@delegate HorizontalScrolling
	@event ScrollEvent
	*/
	DELEGATE(ScrollDelegate,HorizontalScrolling)

	ScrollbarManager();

	ScrollbarManager( Component* owner );

	ScrollbarManager( const String& name, Component* owner );

	ScrollbarManager( const String& name );

	/**
	* override of the callback always called when a component is created.
	*/
	virtual void afterCreate( ComponentEvent* event );

	/**
	* gets the control containing the scrollbars and associated to them.
	* This the control whose content will be moved by the scrollable, as
	* for example the listbox or the text editor when it has scrollbars.
	*/
	Control* getTarget() {
		return target_;
	}

	/**
	* assign the target control for the scrolling operations.
	* This is the control containing the scrollbars which are associated
	* to it. It's content is scrolled by the scrollable.
	*/
	void setTarget( Control* target );

	/**
	* sets if the vertical scrolbar is ever visible
	*@param const bool& hasVerticalScrollbar, false if it is never visible.
	*/
	void setHasVerticalScrollbar( const bool& hasVerticalScrollbar );

	/**
	* sets if the orizontal scrolbar is ever visible
	*@param const bool& hasHorizontalScrollbar, false if it is never visible.
	*/
	void setHasHorizontalScrollbar( const bool& hasHorizontalScrollbar );

	/**
	* tells if the vertical scrolbar is ever visible
	*/
	bool hasVerticalScrollBar();

	/**
	* tells if the orizontal scrolbar is ever visible
	*/
	bool hasHorizontalScrollBar();	

	/**
	* gets the height of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	double getVirtualViewHeight();

	/**
	* gets the width of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	double getVirtualViewWidth();

	/**
	* sets the height of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	void setVirtualViewHeight( const double& virtualViewHeight );

	/**
	* sets the width of the area that needs to be displayed.
	* @see setVirtualViewSize
	*/
	void setVirtualViewWidth( const double& virtualViewWidth );

	/**
	* sets the size (dimensions) of the area that needs to be displayed.
	* For example if we want to show an image, this size will be set 
	* the same as the size of the image.
	* The name virtual comes from the fact that it can be partly hidden.
	* This area can be larger of the area actually displayed, and in this case
	* the scrollbars will appear if not visible.
	*/
	void setVirtualViewSize( const double& virtualViewWidth, const double& virtualViewHeight );

	/**
	* sets how many pixel we want to vertically scroll the area to be displayed
	* when pressing the arrows of the vertical scrollbar.
	*/
	virtual void setVirtualViewVertStep( const double& step );

	/**
	* sets how many pixel we want to horizontally scroll the area to be displayed
	* when pressing the arrows of the horizontal scrollbar.
	*/
	virtual void setVirtualViewHorzStep( const double& step );

	/**
	* tells how many pixel we want the area to be displayed will be vertically 
	* scrolled when pressing the arrows of the vertical scrollbar.
	*/
	virtual double getVirtualViewVertStep();

	/**
	* tells how many pixel we want the area to be displayed will be vertically 
	* scrolled when pressing the arrows of the vertical scrollbar.
	*/
	virtual double getVirtualViewHorzStep();

	/**
	* moves the scrollbox of a vertical scrollbar to the specified position.
	* Keep in mind that the final position may differ fom the specified 
	* one because the OS may change that actual position because of
	* roundings and other considerations related to the position 
	* of other controls.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	void setVerticalPosition( const double& vertPosition );

	/**
	* moves the scrollbox of a vertical scrollbar to the specified position.
	* Keep in mind that the final position may differ fom the specified 
	* one because the OS may change that actual position because of
	* roundings and other considerations related to the position 
	* of other controls.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	void setHorizontalPosition( const double& horzPosition );

	/**
	* gets the position of the scrollbox of a vertical scrollbar.
	* This is postion is always the one adjusted by the OS according
	* to internal considerations.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	double getVerticalPosition();

	/**
	* gets the position of the scrollbox of a horizontal scrollbar.
	* This is postion is always the one adjusted by the OS according
	* to internal considerations.
	*@see ScrollPeer::getAdjustedPositions()
	*/
	double getHorizontalPosition();

	/**
	* gets the height of the space above the vertical scrollbar.
	*/
	double getVerticalTopScrollSpace();

	/**
	* gets the height of the space below the vertical scrollbar.
	*/
	double getVerticalBottomScrollSpace();

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the top of the vertical scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	void setVerticalTopScrollSpace( const double& topScrollSpace );

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the bottom of the vertical scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	void setVerticalBottomScrollSpace( const double& bottomScrollSpace );

	/**
	* gets the width of the space on the left of the horizontal scrollbar.
	*/
	double getHorizontalLeftScrollSpace();

	/**
	* gets the width of the space on the right of the horizontal scrollbar.
	*/
	double getHorizontalRightScrollSpace();

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the left of the horizontal scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	void setHorizontalLeftScrollSpace( const double& leftScrollSpace );

	/**
	* the scrollbars are always inside the area to display.
	* this let us to create a space on the right of the horizontal scrollbar,
	* which can be used to place other controls in there.
	* As result of this the scrollbar will appear smaller.
	*/
	void setHorizontalRightScrollSpace( const double& rightScrollSpace );

	/**
	* sets if we want the horizontal and vertical scrollbar always visible, 
	* even when not needed, or not.
	*/
	void setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible );

	/**
	* tells if we choosed to have the vertical scrollbar always visible, 
	* even when not needed.
	*/
	bool getKeepVertScrollbarVisible();

	/**
	* tells if we choosed to have the horizontal scrollbar always visible, 
	* even when not needed.
	*/
	bool getKeepHorzScrollbarVisible();

	/**
	* this allows you to control whether or not the scrolling needs to be discrete or not.
	* By default this is false, ( i.e. rounded to the same amount indicated by getVirtualViewStep ).
	*@param bool visible, true if we want it visible
	*/
	virtual void setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete );

	/**
	* gets whether or not the scrolling on the vertical scrollbar
	* needs to be discrete or not.
	*@return true if the scrolling is discrete.
	*/
	virtual bool getDiscreteVertScroll();

	/**
	* gets whether or not the scrolling on the horizontal scrollbar
	* needs to be discrete or not.
	*@return true if the scrolling is discrete.
	*/
	virtual bool getDiscreteHorzScroll();

protected:
	virtual ~ScrollbarManager();

protected:
	Scrollable* scrollable_;
	Control* target_;
};


}; //end of namespace VCF


#endif // _VCF_SCROLLBARMANAGER_H__

/**
$Id$
*/
