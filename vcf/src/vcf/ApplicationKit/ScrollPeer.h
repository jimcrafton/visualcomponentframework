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
\class ScrollPeer ScrollPeer.h "vcf/ApplicationKit/ScrollPeer.h"
*Class ScrollPeer documentation
*/
class APPLICATIONKIT_API ScrollPeer : public Interface {
public:
	/**
	* destructor should be virtual
	*/
	virtual ~ScrollPeer(){};

	/**
	* moves the scrollbox of a scrollbar to the specified position.
	* Keep in mind that the final position may differ fom the specified 
	* one because the OS may change that actual position because of
	* roundings and other internal considerations related to the position 
	* of the involved controls and windows.
	*@see ScrollPeer::getAdjustedPositions()
	*@param const double& xPosition, the desired position in the horizontal scrollbar 
	*@param const double& yPosition, the desired position in the vertical scrollbar
	*/
	virtual void scrollTo( const double& xPosition, const double& yPosition ) = 0;

	/**
	* gets the position of the scrollbox of a scrollbar adjusted by what 
	* the OS decides that position to be.
	*@see ScrollPeer::scrollTo()
	*/
	virtual void getAdjustedPositions( double& xPosition, double& yPosition ) = 0;

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
	virtual void recalcScrollPositions( Scrollable* scrollable ) = 0;

	/**
	* gets the control this scroll peer has been assogiated to.
	*@see setScrollableControl()
	*/
	virtual Control* getScrollableControl() = 0;

	/**
	* sets the target control for the scrolling operation of this scroll peer
	* instance. At this point the content of the control will be scrolled by 
	* the scrollable.
	*@see Scrollable::setScrollableControl()
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
};


}; //end of namespace VCF


#endif // _VCF_SCROLLPEER_H__

/**
$Id$
*/
