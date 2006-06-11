//AbstractScrollable.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AbstractScrollable.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ScrollPeer.h"
#include "vcf/ApplicationKit/ScrollEvent.h"

using namespace VCF;

AbstractScrollable::ControlResizeHandler::ControlResizeHandler( AbstractScrollable* scrollable )
{
	scrollable_ = scrollable;
	ControlEventHandler<ControlResizeHandler>* ch =
		new ControlEventHandler<ControlResizeHandler>( this, &AbstractScrollable::ControlResizeHandler::controlResized, "ControlHandler" );
}

AbstractScrollable::ControlResizeHandler::~ControlResizeHandler()
{

}

void AbstractScrollable::ControlResizeHandler::controlResized( ControlEvent* event )
{
	scrollable_->onControlResized( event );
}

AbstractScrollable::AbstractScrollable():
	resizeHandler_(NULL),
	scrollPeer_(NULL),
	scrollableControl_(NULL),
	virtualViewHorzStep_(5.0),
	virtualViewVertStep_(5.0),
	virtualViewHeight_(0.0),
	virtualViewWidth_(0.0),	
	hasHorzScrollbar_(false),
	hasVertScrollbar_(false),
	vertPosition_(0.0),
	horzPosition_(0.0),
	topScrollSpace_(0.0),
	bottomScrollSpace_(0.0),
	leftScrollSpace_(0.0),
	rightScrollSpace_(0.0),
	keepHorzScrollbarVisible_(false),
	keepVertScrollbarVisible_(false),
	discreteHorzScroll_(false),
	discreteVertScroll_(false),
	vertDelegate_(NULL),
	horzDelegate_(NULL)
{

	resizeHandler_ = new ControlResizeHandler(this);

	scrollPeer_ = UIToolkit::createScrollPeer( NULL ) ;
}

AbstractScrollable::~AbstractScrollable()
{
	resizeHandler_->free();
	delete scrollPeer_;
}

void AbstractScrollable::setScrollableControl( Control* scrollableControl ) {

	EventHandler* ch = resizeHandler_->getEventHandler( "ControlHandler" );
	if ( NULL != scrollableControl_ ) {
		scrollableControl_->ControlSized.removeHandler( ch );
	}
	scrollableControl_ = scrollableControl;
	if ( NULL != scrollableControl_ ) {
		scrollableControl_->ControlSized.addHandler( ch );
	}
	scrollPeer_->setScrollableControl( scrollableControl_ );
}

void AbstractScrollable::setVerticalTopScrollSpace( const double& topScrollSpace )
{
	this->topScrollSpace_ = topScrollSpace;

	this->recalcScrollPositions();
}

void AbstractScrollable::setVerticalBottomScrollSpace( const double& bottomScrollSpace )
{
	this->bottomScrollSpace_ = bottomScrollSpace;

	this->recalcScrollPositions();
}

void AbstractScrollable::setHorizontalLeftScrollSpace( const double& leftScrollSpace )
{
	this->leftScrollSpace_ = leftScrollSpace;

	this->recalcScrollPositions();
}

void AbstractScrollable::setHorizontalRightScrollSpace( const double& rightScrollSpace )
{
	this->rightScrollSpace_ = rightScrollSpace;

	this->recalcScrollPositions();
}

void AbstractScrollable::onControlResized( ControlEvent* event )
{
	recalcScrollPositions();
	//	scrollPeer_->recalcScrollPositions( this );
	//	scrollPeer_->getAdjustedPositions( horzPosition_, vertPosition_ );
}

void AbstractScrollable::setVirtualViewSize( const double& width, const double& height )
{
	virtualViewWidth_ = width;
	virtualViewHeight_ = height;

	recalcScrollPositions();
	//scrollPeer_->recalcScrollPositions( this );
	//scrollPeer_->getAdjustedPositions( horzPosition_, vertPosition_ );
}

bool AbstractScrollable::isVerticalScrollbarVisible() {
	return scrollPeer_->isVerticalScrollbarVisible();
}

bool AbstractScrollable::isHorizontalScrollbarVisible() {
	return scrollPeer_->isHorizontalScrollbarVisible();
}

void AbstractScrollable::recalcScrollPositions()
{
	if ( NULL != this->scrollableControl_ ) {
		scrollPeer_->recalcScrollPositions( this );
		scrollPeer_->getAdjustedPositions( horzPosition_, vertPosition_ );
	}
}

void AbstractScrollable::setVerticalPosition( const double& vertPosition )
{
	vertPosition_ = vertPosition;
	if ( NULL != this->scrollableControl_ ) {
		scrollPeer_->scrollTo( horzPosition_, vertPosition_ );
		scrollPeer_->getAdjustedPositions( horzPosition_, vertPosition_ );
		scrollableControl_->repaint();

		//notify delegate
		if ( NULL != vertDelegate_ ) {
			ScrollEvent e(scrollableControl_,0);
			e.setScrollPoint( Point(horzPosition_,vertPosition_) );
			vertDelegate_->fireEvent( &e );
		}
	}
}

void AbstractScrollable::setHorizontalPosition( const double& horzPosition ) {
	horzPosition_ = horzPosition;
	if ( NULL != this->scrollableControl_ ) {
		scrollPeer_->scrollTo( horzPosition_, vertPosition_ );
		scrollPeer_->getAdjustedPositions( horzPosition_, vertPosition_ );
		scrollableControl_->repaint();

		//notify delegate
		if ( NULL != horzDelegate_ ) {
			ScrollEvent e(scrollableControl_,0);
			e.setScrollPoint( Point(horzPosition_,vertPosition_) );
			horzDelegate_->fireEvent( &e );
		}
	}
}

double AbstractScrollable::getHorizontalScrollbarHeight()
{
	return scrollPeer_->getHorizontalScrollbarHeight();
}

double AbstractScrollable::getVerticalScrollbarWidth()
{
	return scrollPeer_->getVerticalScrollbarWidth();
}

void AbstractScrollable::getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds, Rect* rightBounds )
{
	scrollPeer_->getHorizontalScrollRects( scrollBounds, leftBounds, rightBounds );
}

void AbstractScrollable::getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds, Rect* bottomBounds )
{
	scrollPeer_->getVerticalScrollRects( scrollBounds, topBounds, bottomBounds );
}

void AbstractScrollable::setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible )
{
	keepHorzScrollbarVisible_ = horzVisible;
	keepVertScrollbarVisible_ = vertVisible;

	recalcScrollPositions();
}

bool AbstractScrollable::getKeepHorzScrollbarVisible()
{
	return keepHorzScrollbarVisible_;
}

bool AbstractScrollable::getKeepVertScrollbarVisible()
{
	return keepVertScrollbarVisible_;
}

void AbstractScrollable::setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete )
{
	discreteHorzScroll_ = horzDiscrete;
	discreteVertScroll_ = vertDiscrete;
}

bool AbstractScrollable::getDiscreteHorzScroll()
{
	return discreteHorzScroll_;
}

bool AbstractScrollable::getDiscreteVertScroll()
{
	return discreteVertScroll_;
}


/**
$Id$
*/
