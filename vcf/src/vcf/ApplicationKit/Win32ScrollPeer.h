#ifndef _VCF_WIN32SCROLLPEER_H__
#define _VCF_WIN32SCROLLPEER_H__
//Win32ScrollPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ScrollPeer.h"


namespace VCF  {

/**
*Class Win32ScrollPeer documentation
*/
class Win32ScrollPeer : public Object, public ScrollPeer {
public:
	Win32ScrollPeer( Control* scrollableControl=NULL );

	virtual ~Win32ScrollPeer();

	virtual void scrollTo( const double& xPosition, const double& yPosition );

	virtual void getAdjustedPositions( double& xPosition, double& yPosition );

	virtual bool isVerticalScrollbarVisible();

	virtual bool isHorizontalScrollbarVisible();	

	virtual void recalcScrollPositions( Scrollable* scrollable );

	virtual Control* getScrollableControl() {
		return scrollableControl_;
	}

	virtual void setScrollableControl( Control* scrollableControl );

	virtual double getHorizontalScrollbarHeight();

	virtual double getVerticalScrollbarWidth();

	static Control* getScrollableControlFromHWnd( HWND scrollhWnd );

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL );
	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL );
protected:
	static std::map<HWND,Control*> hScrollBarMap;
	void removeScrollBarsFromMap();
	void addScrollBarsToMap();
	Control* scrollableControl_;
	Control* scrollCorner_;
	HWND vScrollHWnd_;
	HWND hScrollHWnd_;	

	bool isVertSBVisible_;//move to AbstractScrollable
	bool isHorzSBVisible_;//move to AbstractScrollable
};


}; //end of namespace VCF


#endif // _VCF_WIN32SCROLLPEER_H__

/**
$Id$
*/
