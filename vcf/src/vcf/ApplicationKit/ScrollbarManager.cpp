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


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.3  2004/09/21 05:50:21  dougtinkham
*removed updateVirtualViewSize
*
*Revision 1.2.2.2  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.1  2004/09/14 21:12:17  dougtinkham
*added updateVirtualViewSize member
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.6  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.5.2.1  2004/03/01 05:59:19  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.5  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.4.4.1  2003/10/13 04:02:52  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.4  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/12 03:13:21  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.1  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.2  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.1  2002/03/01 01:56:20  ddiego
*added files for [ 524137 ] ScrollComponent for adding scrolling
*plus CVS log info
*
*/


