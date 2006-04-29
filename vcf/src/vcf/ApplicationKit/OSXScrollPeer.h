#ifndef _VCF_OSXSCROLLPEER_H__
#define _VCF_OSXSCROLLPEER_H__
//OSXScrollPeer.h

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
*Class OSXScrollPeer documentation
*/
class OSXScrollPeer : public Object, public ScrollPeer {
public:
	OSXScrollPeer( Control* scrollableControl=NULL );

	virtual ~OSXScrollPeer();

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

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL );
	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL );
protected:
	Control* scrollableControl_;
};


}; //end of namespace VCF


#endif // _VCF_OSXSCROLLPEER_H__

/**
$Id$
*/
