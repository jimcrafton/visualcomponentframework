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
	DELEGATE(VerticalScrolling)

	/**
	@delegate HorizontalScrolling
	@event ScrollEvent
	*/
	DELEGATE(HorizontalScrolling)

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


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
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
*Revision 1.2.2.3  2004/09/21 05:49:23  dougtinkham
*removed updateVirtualViewSize
*
*Revision 1.2.2.2  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.1  2004/09/14 21:10:55  dougtinkham
*added updateVirtualViewSize member
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
*Revision 1.4.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.1  2004/03/01 05:58:54  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.4.4  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.2.4.3  2003/10/13 04:00:24  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.2.4.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.4.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.2  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.22.1  2003/03/12 03:09:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.1  2002/03/01 01:56:20  ddiego
*added files for [ 524137 ] ScrollComponent for adding scrolling
*plus CVS log info
*
*/


#endif // _VCF_SCROLLBARMANAGER_H__


