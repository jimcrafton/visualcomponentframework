//ScrollbarManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ScrollbarManager.h

#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


ScrollbarManager::ScrollbarManager():
	scrollable_(NULL),
	target_(NULL)

{
	scrollable_ = new AbstractScrollable();
	((AbstractScrollable*)scrollable_)->setHorizontalScrollingDelegate( &HorizontalScrolling );
	((AbstractScrollable*)scrollable_)->setVerticalScrollingDelegate( &VerticalScrolling );
}

ScrollbarManager::ScrollbarManager( Component* owner ):
	Component( owner ),
	scrollable_(NULL),
	target_(NULL)
{
	scrollable_ = new AbstractScrollable();
	((AbstractScrollable*)scrollable_)->setHorizontalScrollingDelegate( &HorizontalScrolling );
	((AbstractScrollable*)scrollable_)->setVerticalScrollingDelegate( &VerticalScrolling );
}

ScrollbarManager::ScrollbarManager( const String& name, Component* owner ):
	Component( name, owner ),
	scrollable_(NULL),
	target_(NULL)
{
	scrollable_ = new AbstractScrollable();
	((AbstractScrollable*)scrollable_)->setHorizontalScrollingDelegate( &HorizontalScrolling );
	((AbstractScrollable*)scrollable_)->setVerticalScrollingDelegate( &VerticalScrolling );
}

ScrollbarManager::ScrollbarManager( const String& name ):
	Component( name ),
	scrollable_(NULL),
	target_(NULL)
{
	scrollable_ = new AbstractScrollable();
	((AbstractScrollable*)scrollable_)->setHorizontalScrollingDelegate( &HorizontalScrolling );
	((AbstractScrollable*)scrollable_)->setVerticalScrollingDelegate( &VerticalScrolling );
}

ScrollbarManager::~ScrollbarManager()
{
	delete scrollable_;
}

void ScrollbarManager::setTarget( Control* target )
{
	if ( NULL != target_ ) {
		target_->setScrollable( NULL );
	}

	target_ = target;

	if ( NULL != target_ ) {
		target_->setScrollable( scrollable_ );
	}
}

void ScrollbarManager::afterCreate( ComponentEvent* event )
{

}

void ScrollbarManager::setHasVerticalScrollbar( const bool& hasVerticalScrollbar )
{
	scrollable_->setHasVerticalScrollbar( hasVerticalScrollbar );
}

void ScrollbarManager::setHasHorizontalScrollbar( const bool& hasHorizontalScrollbar )
{
	scrollable_->setHasHorizontalScrollbar( hasHorizontalScrollbar );
}

bool ScrollbarManager::hasVerticalScrollBar()
{
	return scrollable_->hasVerticalScrollBar();
}

bool ScrollbarManager::hasHorizontalScrollBar()
{
	return scrollable_->hasHorizontalScrollBar();
}

double ScrollbarManager::getVirtualViewHeight()
{
	return scrollable_->getVirtualViewHeight();
}

double ScrollbarManager::getVirtualViewWidth()
{
	return scrollable_->getVirtualViewWidth();
}

void ScrollbarManager::setVirtualViewHeight( const double& virtualViewHeight )
{
	scrollable_->setVirtualViewHeight( virtualViewHeight );
}

void ScrollbarManager::setVirtualViewWidth( const double& virtualViewWidth )
{
	scrollable_->setVirtualViewWidth( virtualViewWidth );
}

void ScrollbarManager::setVirtualViewSize( const double& virtualViewWidth, const double& virtualViewHeight )
{
	scrollable_->setVirtualViewSize( virtualViewWidth, virtualViewHeight );
}

void ScrollbarManager::setVirtualViewHorzStep( const double& step )
{
	scrollable_->setVirtualViewHorzStep( step );
}

void ScrollbarManager::setVirtualViewVertStep( const double& step )
{
	scrollable_->setVirtualViewVertStep( step );
}

double ScrollbarManager::getVirtualViewHorzStep()
{
	return scrollable_->getVirtualViewHorzStep();
}

double ScrollbarManager::getVirtualViewVertStep()
{
	return scrollable_->getVirtualViewVertStep();
}

void ScrollbarManager::setVerticalPosition( const double& vertPosition )
{
	scrollable_->setVerticalPosition( vertPosition );
}

void ScrollbarManager::setHorizontalPosition( const double& horzPosition )
{
	scrollable_->setHorizontalPosition( horzPosition );
}

double ScrollbarManager::getVerticalPosition()
{
	return scrollable_->getVerticalPosition();
}

double ScrollbarManager::getHorizontalPosition()
{
	return scrollable_->getHorizontalPosition();
}

double ScrollbarManager::getVerticalTopScrollSpace()
{
	return scrollable_->getVerticalTopScrollSpace();
}

double ScrollbarManager::getVerticalBottomScrollSpace()
{
	return scrollable_->getVerticalBottomScrollSpace();
}

void ScrollbarManager::setVerticalTopScrollSpace( const double& topScrollSpace )
{
	scrollable_->setVerticalTopScrollSpace( topScrollSpace );
}

void ScrollbarManager::setVerticalBottomScrollSpace( const double& bottomScrollSpace )
{
	scrollable_->setVerticalBottomScrollSpace( bottomScrollSpace );
}

double ScrollbarManager::getHorizontalLeftScrollSpace()
{
	return scrollable_->getHorizontalLeftScrollSpace();
}

double ScrollbarManager::getHorizontalRightScrollSpace()
{
	return scrollable_->getHorizontalRightScrollSpace();
}

void ScrollbarManager::setHorizontalLeftScrollSpace( const double& leftScrollSpace )
{
	scrollable_->setHorizontalLeftScrollSpace( leftScrollSpace );
}

void ScrollbarManager::setHorizontalRightScrollSpace( const double& rightScrollSpace )
{
	scrollable_->setHorizontalRightScrollSpace( rightScrollSpace );
}

void ScrollbarManager::setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible )
{
	scrollable_->setKeepScrollbarsVisible( horzVisible, vertVisible );
}

bool ScrollbarManager::getKeepHorzScrollbarVisible()
{
	return scrollable_->getKeepHorzScrollbarVisible();
}

bool ScrollbarManager::getKeepVertScrollbarVisible()
{
	return scrollable_->getKeepVertScrollbarVisible();
}

void ScrollbarManager::setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete )
{
	scrollable_->setDiscreteScroll( horzDiscrete, vertDiscrete );
}

bool ScrollbarManager::getDiscreteHorzScroll()
{
	return scrollable_->getDiscreteHorzScroll();
}

bool ScrollbarManager::getDiscreteVertScroll()
{
	return scrollable_->getDiscreteVertScroll();
}


/**
$Id$
*/
