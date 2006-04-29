#ifndef _VCF_ABSTRACTSCROLLABLE_H__
#define _VCF_ABSTRACTSCROLLABLE_H__
//AbstractScrollable.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ScrollPeer;

/**
\class AbstractScrollable AbstractScrollable.h "vcf/ApplicationKit/AbstractScrollable.h"
*Class AbstractScrollable documentation.
*This class represents a basic implementation for
*controls that would like to be "scrollable".
*@see Scrollable
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API AbstractScrollable : public Scrollable {
public:
	class ControlResizeHandler : public ObjectWithEvents {
	public:
		ControlResizeHandler( AbstractScrollable* scrollable );

		virtual ~ControlResizeHandler();

		void controlResized( ControlEvent* event );

	private:
		  AbstractScrollable* scrollable_;
	};

	AbstractScrollable();

	virtual ~AbstractScrollable();

	friend class ControlResizeHandler;

	virtual void setHasVerticalScrollbar( const bool& hasVerticalScrollbar ) {
		hasVertScrollbar_ = hasVerticalScrollbar;
		recalcScrollPositions();
	}

	virtual void setHasHorizontalScrollbar( const bool& hasHorizontalScrollbar ) {
		hasHorzScrollbar_ = hasHorizontalScrollbar;
		recalcScrollPositions();
	}

	virtual bool hasVerticalScrollBar() {
		return hasVertScrollbar_;
	}

	virtual bool hasHorizontalScrollBar() {
		return hasHorzScrollbar_;
	}	

	virtual void setVirtualViewSize( const double& width, const double& height );

	virtual void setVirtualViewHeight( const double& virtualViewHeight ) {
		setVirtualViewSize( getVirtualViewWidth(), virtualViewHeight );
	}

	virtual double getVirtualViewHeight() {
		return virtualViewHeight_;
	}

	virtual void setVirtualViewWidth( const double& virtualViewWidth ) {
		setVirtualViewSize( virtualViewWidth, getVirtualViewHeight() );
	}

	virtual double getVirtualViewWidth() {
		return virtualViewWidth_;
	}

	virtual void setVirtualViewHorzStep( const double& step ) {
		virtualViewHorzStep_ = step;
	}

	virtual void setVirtualViewVertStep( const double& step ) {
		virtualViewVertStep_ = step;
	}

	virtual double getVirtualViewHorzStep() {
		return virtualViewHorzStep_;
	}

	virtual double getVirtualViewVertStep() {
		return virtualViewVertStep_;
	}

	virtual bool isVerticalScrollbarVisible();
		
	virtual bool isHorizontalScrollbarVisible();

	virtual void recalcScrollPositions();

	virtual Control* getScrollableControl() {
		return scrollableControl_;
	}

	virtual void setScrollableControl( Control* scrollableControl );

	virtual void setVerticalPosition( const double& vertPosition );

	virtual void setHorizontalPosition( const double& horzPosition );

	virtual double getVerticalPosition() {
		return vertPosition_;
	}

	virtual double getHorizontalPosition() {
		return horzPosition_;
	}

	virtual double getVerticalTopScrollSpace() {
		return topScrollSpace_;
	}

	virtual double getVerticalBottomScrollSpace() {
		return bottomScrollSpace_;
	}

	virtual void setVerticalTopScrollSpace( const double& topScrollSpace );

	virtual void setVerticalBottomScrollSpace( const double& bottomScrollSpace );

	virtual double getHorizontalLeftScrollSpace() {
		return leftScrollSpace_;
	}

	virtual double getHorizontalRightScrollSpace() {
		return rightScrollSpace_;
	}

	virtual void setHorizontalLeftScrollSpace( const double& leftScrollSpace );

	virtual void setHorizontalRightScrollSpace( const double& rightScrollSpace );

	virtual double getHorizontalScrollbarHeight();

	virtual double getVerticalScrollbarWidth();

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL );

	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL );

	virtual void setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible );
	virtual bool getKeepHorzScrollbarVisible();
	virtual bool getKeepVertScrollbarVisible();

	virtual void setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete );
	virtual bool getDiscreteHorzScroll();
	virtual bool getDiscreteVertScroll();

	void setVerticalScrollingDelegate( Delegate* delegate ) {
		vertDelegate_ = delegate;
	}

	void setHorizontalScrollingDelegate( Delegate* delegate ) {
		horzDelegate_ = delegate;
	}

	Delegate* getVerticalScrollingDelegate() {
		return vertDelegate_;
	}

	Delegate* getHorizontalScrollingDelegate() {
		return horzDelegate_;
	}
protected:

	void onControlResized( ControlEvent* event );

	ControlResizeHandler* resizeHandler_;

	ScrollPeer* scrollPeer_;
	Control* scrollableControl_;
	double virtualViewHorzStep_;
	double virtualViewVertStep_;
	double virtualViewHeight_;
	double virtualViewWidth_;	
	bool hasHorzScrollbar_;
	bool hasVertScrollbar_;
	double vertPosition_;
	double horzPosition_;
	double topScrollSpace_;
	double bottomScrollSpace_;
	double leftScrollSpace_;
	double rightScrollSpace_;
	bool keepHorzScrollbarVisible_;
	bool keepVertScrollbarVisible_;
	bool discreteHorzScroll_;
	bool discreteVertScroll_;
	Delegate* vertDelegate_;
	Delegate* horzDelegate_;

};


}; //end of namespace VCF


#endif // _VCF_ABSTRACTSCROLLABLE_H__

/**
$Id$
*/
