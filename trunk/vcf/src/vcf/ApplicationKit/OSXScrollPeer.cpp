//OSXScrollPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//OSXScrollPeer.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXScrollPeer.h"


using namespace VCF;



OSXScrollPeer::OSXScrollPeer( Control* scrollableControl ):
	scrollableControl_(scrollableControl)
{

}

OSXScrollPeer::~OSXScrollPeer()
{
	
}


void OSXScrollPeer::setScrollableControl( Control* scrollableControl )
{
	if ( NULL != scrollableControl_ ) {
		
	}

	scrollableControl_ = scrollableControl;

	if ( NULL != scrollableControl_ ) {
		
	}
}

void OSXScrollPeer::scrollTo( const double& xPosition, const double& yPosition )
{
	Scrollable* scrollable = scrollableControl_->getScrollable();
	if ( NULL != scrollable ) {

	}
}

bool OSXScrollPeer::isVerticalScrollbarVisible() 
{
	return false;
}

bool OSXScrollPeer::isHorizontalScrollbarVisible() 
{
	return false;
}

void OSXScrollPeer::recalcScrollPositions( Scrollable* scrollable )
{
	
}

double OSXScrollPeer::getHorizontalScrollbarHeight()
{
	return 0;
}

double OSXScrollPeer::getVerticalScrollbarWidth()
{
	return 0;
}

void OSXScrollPeer::getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds, Rect* rightBounds )
{
	if ( NULL != scrollBounds ) {
		scrollBounds->setNull();
	}
	if ( NULL != leftBounds ) {
		leftBounds->setNull();
	}
	if ( NULL != rightBounds ) {
		rightBounds->setNull();
	}

}

void OSXScrollPeer::getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds, Rect* bottomBounds )
{
	if ( NULL != scrollBounds ) {
		scrollBounds->setNull();
	}
	if ( NULL != topBounds ) {
		topBounds->setNull();
	}
	if ( NULL != bottomBounds ) {
		bottomBounds->setNull();
	}

}

void OSXScrollPeer::getAdjustedPositions( double& xPosition, double& yPosition )
{
	Scrollable* scrollable = scrollableControl_->getScrollable();
	if ( NULL != scrollable ) {
		
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.1  2005/06/23 00:35:36  ddiego
*added osx classes
*
*/


