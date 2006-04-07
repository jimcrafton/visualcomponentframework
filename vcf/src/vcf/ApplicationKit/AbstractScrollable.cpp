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
	hasVertScrollbar_(false),
	hasHorzScrollbar_(false),
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
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2006/03/22 03:18:20  ddiego
*fixed a glitch in scroll vert and horz position values.
*
*Revision 1.4  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/01/15 00:52:38  marcelloptr
*bugfix [ 1099910 ] plus other improvements of the scrolling
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.7  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.6  2004/09/21 22:27:06  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.5  2004/09/21 05:43:21  dougtinkham
*removed updateVirtualViewSize, addied isVerticalScrollbarVisible, isHorizontalScrollbarVisible
*
*Revision 1.2.2.4  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.3  2004/09/13 06:07:05  dougtinkham
*onControlResized now checks if updateVirtualViewSize should be called
*
*Revision 1.2.2.2  2004/09/11 08:16:41  dougtinkham
*changes to updateVirtualViewSize
*
*Revision 1.2.2.1  2004/09/10 22:31:18  dougtinkham
*added updateVirtualViewSize member fct
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.15  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14.2.2  2004/03/21 20:25:40  marcelloptr
*Scrollable automatically calculates the scroll given the line where to go
*
*Revision 1.14.2.1  2004/03/01 05:59:19  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.14  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.2.3  2003/10/13 04:02:51  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.13.2.2  2003/09/08 05:23:21  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.13.2.1  2003/09/05 21:03:20  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.13  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.12.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.12  2003/05/17 20:37:45  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:12:57  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.10.14.2  2003/01/08 00:19:56  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10.14.1  2002/12/25 22:06:33  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:38  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.9  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


