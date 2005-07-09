//Win32ScrollPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32ScrollPeer.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ScrollPeer.h"


using namespace VCF;


std::map<HWND,Control*> Win32ScrollPeer::hScrollBarMap;

class Win32ScrollCorner : public CustomControl {
public:
	Win32ScrollCorner() {

	}

	virtual ~Win32ScrollCorner(){};

};


Win32ScrollPeer::Win32ScrollPeer( Control* scrollableControl )
{
	this->scrollableControl_ = scrollableControl;
	vScrollHWnd_ = NULL;
	hScrollHWnd_ = NULL;
	scrollCorner_ = NULL;
	isVertSBVisible_ = false;
	isHorzSBVisible_ = false;
}

Win32ScrollPeer::~Win32ScrollPeer()
{
	if ( NULL != scrollCorner_ ) {
		scrollCorner_->free();
	}
}

void Win32ScrollPeer::removeScrollBarsFromMap()
{
	std::map<HWND,Control*>::iterator found = Win32ScrollPeer::hScrollBarMap.find( vScrollHWnd_ );
	if ( found != Win32ScrollPeer::hScrollBarMap.end() ) {
		Win32ScrollPeer::hScrollBarMap.erase( found );
	}

	found = Win32ScrollPeer::hScrollBarMap.find( hScrollHWnd_ );
	if ( found != Win32ScrollPeer::hScrollBarMap.end() ) {
		Win32ScrollPeer::hScrollBarMap.erase( found );
	}
}

void Win32ScrollPeer::addScrollBarsToMap()
{
	Win32ScrollPeer::hScrollBarMap[vScrollHWnd_] = scrollableControl_;
	Win32ScrollPeer::hScrollBarMap[hScrollHWnd_] = scrollableControl_;
}

Control* Win32ScrollPeer::getScrollableControlFromHWnd( HWND scrollhWnd )
{
	Control* result = NULL;
	std::map<HWND,Control*>::iterator found = Win32ScrollPeer::hScrollBarMap.find( scrollhWnd );
	if ( found != Win32ScrollPeer::hScrollBarMap.end() ) {
		result = found->second;
	}
	return result;
}

void Win32ScrollPeer::setScrollableControl( Control* scrollableControl )
{
	if ( NULL != scrollableControl_ )
	{
		removeScrollBarsFromMap();
		BOOL err = DestroyWindow( vScrollHWnd_ );
		err = DestroyWindow( hScrollHWnd_ );
		vScrollHWnd_ = NULL;
		hScrollHWnd_ = NULL;
		scrollCorner_->free();
	}
	this->scrollableControl_ = scrollableControl;
	if ( NULL != scrollableControl_ ) {
		HWND hwnd = (HWND)scrollableControl_->getPeer()->getHandleID();

		Application* app = Application::getRunningInstance();
		HINSTANCE hInst = NULL;
		if ( NULL != app ) {
			hInst = (HINSTANCE)app->getPeer()->getHandleID();
		}
		else {
			hInst = ::GetModuleHandle(NULL);
		}
#if defined(VCF_CW) && defined(UNICODE)
		vScrollHWnd_ = CreateWindowEx( 0, L"SCROLLBAR", NULL, WS_CHILD | SBS_VERT | WS_VISIBLE, 0, 0, 200,
			CW_USEDEFAULT, hwnd, NULL, hInst, NULL );

		hScrollHWnd_ = CreateWindowEx( 0, L"SCROLLBAR", NULL, WS_CHILD | SBS_HORZ | WS_VISIBLE, 0, 0, 200,
			CW_USEDEFAULT, hwnd, NULL, hInst, NULL );
#else
		vScrollHWnd_ = CreateWindowEx( 0, "SCROLLBAR", NULL, WS_CHILD | SBS_VERT | WS_VISIBLE, 0, 0, 200,
			CW_USEDEFAULT, hwnd, NULL, hInst, NULL );

		hScrollHWnd_ = CreateWindowEx( 0, "SCROLLBAR", NULL, WS_CHILD | SBS_HORZ | WS_VISIBLE, 0, 0, 200,
			CW_USEDEFAULT, hwnd, NULL, hInst, NULL );
#endif
		scrollCorner_ = new Win32ScrollCorner();
		HWND scHwnd = (HWND)scrollCorner_->getPeer()->getHandleID();
		SetParent( scHwnd, hwnd );

		addScrollBarsToMap();
	}
}

void Win32ScrollPeer::scrollTo( const double& xPosition, const double& yPosition )
{
	SCROLLINFO si = {0};

	Scrollable* scrollable = scrollableControl_->getScrollable();
	if ( NULL != scrollable ) {

		bool hasVertSB = (scrollable->hasVerticalScrollBar()) && (::IsWindowEnabled(vScrollHWnd_));
		bool hasHorzSB = (scrollable->hasHorizontalScrollBar()) && (::IsWindowEnabled(hScrollHWnd_));

		if ( true == hasVertSB ) {
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = (long)yPosition;
			SetScrollInfo( vScrollHWnd_, SB_CTL, &si, TRUE );
		}

		if ( true == hasHorzSB ) {
			memset( &si, 0, sizeof(si) );
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS ;
			si.nPos = (long)xPosition;
			SetScrollInfo( hScrollHWnd_, SB_CTL, &si, TRUE );
		}
	}
}

bool Win32ScrollPeer::isVerticalScrollbarVisible() {
	return isVertSBVisible_;
}

bool Win32ScrollPeer::isHorizontalScrollbarVisible() {
	return isHorzSBVisible_;
}

void Win32ScrollPeer::recalcScrollPositions( Scrollable* scrollable )
{
	/**
	*if the scrollableControl_ is lightweight then the handle represents the parent's
	*hwnd, so get the control's bounds, instead of using 0,0 for left,top
	*/
	Rect bounds(0,0,0,0);

	if ( true == scrollableControl_->isLightWeight() ) {
		bounds = (scrollableControl_->getBounds());
	}
	else {
		bounds = scrollableControl_->getClientBounds( );
		//bounds.inflate( -1, -1 );
	}

	bool hasVertSB = scrollable->hasVerticalScrollBar();
	bool hasHorzSB = scrollable->hasHorizontalScrollBar();

	bool keepVertSB = scrollable->getKeepVertScrollbarVisible();
	bool keepHorzSB = scrollable->getKeepHorzScrollbarVisible();

	// initially set showVertSB and showHorzSB false, then check.
	bool showVertSB = false;
	bool showHorzSB = false;
	
	// if hasSB and keepSB then we show them anyway
	if ( hasVertSB ) {
		showVertSB = keepVertSB;
	}
	if ( hasHorzSB ) {
		showHorzSB = keepHorzSB;
	}

	/* 
	*now we determine if the scrollbars are actually needed, no matter if we want
	*to keep them visible or not, so we can enable them later if needed.
	*initially set needVertSB and needHorzSB false, then check.
	*/
	bool needVertSB = false;	
	bool needHorzSB = false;

	double virtViewWidth  = scrollable->getVirtualViewWidth();
	double virtViewHeight = scrollable->getVirtualViewHeight();

	double vertSBWidth = getVerticalScrollbarWidth();
	double horzSBWidth = getHorizontalScrollbarHeight();

	// determine whether or not scrollbars are needed
	if ( hasHorzSB && ( virtViewWidth  > bounds.getWidth() ) ) {
		needHorzSB = true;
		showHorzSB = true;
	}

	if ( hasVertSB && ( virtViewHeight > bounds.getHeight() ) ) {
		needVertSB = true;
		showVertSB = true;
	}

	// determine having made one of the scrollbars visible requires the other to be visible also
	if ( hasHorzSB && !needHorzSB && showVertSB && ( (bounds.getWidth() - vertSBWidth ) < virtViewWidth ) ) {
		needHorzSB = true;
	}
	if ( hasVertSB && !needVertSB && showHorzSB && ( (bounds.getHeight() - horzSBWidth ) < virtViewHeight ) ) {
		needVertSB = true;
	}

	// if needed we show them
	if ( needVertSB ) {
		showVertSB = true;
	}
	if ( needHorzSB ) {
		showHorzSB = true;
	}
	
	// set isVertSBVisible_ and isHorzSBVisible_
	isVertSBVisible_ = showVertSB;
	isHorzSBVisible_ = showHorzSB;


	SCROLLINFO scrollInfoVert = {0};
	scrollInfoVert.cbSize = sizeof(SCROLLINFO);
	scrollInfoVert.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	scrollInfoVert.nPage = (long)( needVertSB ? bounds.getHeight() : 0);	
	scrollInfoVert.nPos = (long)scrollable->getVerticalPosition();
	scrollInfoVert.nMin = 0;
	scrollInfoVert.nMax = (long) ( showVertSB  ? virtViewHeight : scrollInfoVert.nMin );	
	if ( showHorzSB && (scrollInfoVert.nMax > 0)) {
		scrollInfoVert.nMax += (long)( horzSBWidth + 1 ); 
	}

	SCROLLINFO scrollInfoHorz = {0};
	scrollInfoHorz.cbSize = sizeof(SCROLLINFO);
	scrollInfoHorz.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	scrollInfoHorz.nPage = (long)( needHorzSB ? bounds.getWidth() : 0 );
	scrollInfoHorz.nPos = (long)scrollable->getHorizontalPosition();
	scrollInfoHorz.nMin = 0;
	scrollInfoHorz.nMax = (long)( showHorzSB ? virtViewWidth : scrollInfoHorz.nMin );
	if ( showVertSB && (scrollInfoHorz.nMax > 0) ) {
		scrollInfoHorz.nMax += (long)( vertSBWidth + 1 );
	}


	// dimensions of the vertical scrollbar
	int x1 = (long)( bounds.left_ + ( bounds.getWidth() - vertSBWidth ) );
	int y1 = (long)( bounds.top_ + scrollable->getVerticalTopScrollSpace() );
	int w1 = vertSBWidth;
	int h1 = (long)( bounds.getHeight() - ( scrollable->getVerticalTopScrollSpace() + scrollable->getVerticalBottomScrollSpace() ) );

	// dimensions of the horizontal scrollbar
	int x2 = (long)( bounds.left_ + scrollable->getHorizontalLeftScrollSpace() );
	int y2 = (long)( bounds.top_ + ( bounds.getHeight() - horzSBWidth ) );
	int w2 = (long)( bounds.getWidth() - ( scrollable->getHorizontalLeftScrollSpace() + scrollable->getHorizontalRightScrollSpace() ) );
	int h2 = horzSBWidth;

	if ( showHorzSB && showVertSB ) {
		// one scrollbar takes space from the other
		h1 -= horzSBWidth;
		w2 -= vertSBWidth;
	}

	if ( showVertSB ) {
		::ShowWindow( vScrollHWnd_, SW_NORMAL );
		MoveWindow( vScrollHWnd_, x1, y1, w1, h1, TRUE );
		if ( !needVertSB ) {
			::EnableWindow( vScrollHWnd_, FALSE );
			scrollInfoVert.nPage = 0;
			scrollInfoVert.nPos = 0;
			scrollInfoVert.nMin = 0;
			scrollInfoVert.nMax = 0;
			SetScrollInfo( vScrollHWnd_, SB_CTL, &scrollInfoVert, TRUE );
		}
		else {
			::EnableWindow( vScrollHWnd_, TRUE );
			SetScrollInfo( vScrollHWnd_, SB_CTL, &scrollInfoVert, TRUE );
		}
	}
	else {
		::ShowWindow( vScrollHWnd_, SW_HIDE );
	}

	if ( showHorzSB ) {
		::ShowWindow( hScrollHWnd_, SW_NORMAL );
		MoveWindow( hScrollHWnd_, x2, y2, w2, h2, TRUE );
		if ( !needHorzSB ) {
			::EnableWindow( hScrollHWnd_, FALSE );
			scrollInfoHorz.nPage = 0;
			scrollInfoHorz.nPos = 0;
			scrollInfoHorz.nMin = 0;
			scrollInfoHorz.nMax = 0;
			SetScrollInfo( hScrollHWnd_, SB_CTL, &scrollInfoHorz, TRUE );
		}
		else {
			::EnableWindow( hScrollHWnd_, TRUE );
			SetScrollInfo( hScrollHWnd_, SB_CTL, &scrollInfoHorz, TRUE );
		}
	}
	else {
		::ShowWindow( hScrollHWnd_, SW_HIDE );
	}

	if ( showVertSB && showHorzSB ) {
		scrollCorner_->setVisible( true );
		scrollCorner_->setBounds( &Rect( x1,y2, x1+w1, y2+h2 ) );
		if ( !needVertSB && !needHorzSB ) {
			scrollCorner_->setEnabled( false );
		}
		else {
			scrollCorner_->setEnabled( true );
		}
	}
	else {
		scrollCorner_->setVisible( false );
	}

}

double Win32ScrollPeer::getHorizontalScrollbarHeight()
{
	return ::GetSystemMetrics( SM_CYHSCROLL );
}

double Win32ScrollPeer::getVerticalScrollbarWidth()
{
	return ::GetSystemMetrics( SM_CXVSCROLL );
}

void Win32ScrollPeer::getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds, Rect* rightBounds )
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

	if ( ::IsWindowVisible( hScrollHWnd_ ) ) {
		HWND scHwnd = (HWND)scrollableControl_->getPeer()->getHandleID();

		RECT r = {0};
		POINT pt = {0};

		::GetWindowRect( hScrollHWnd_, &r );
		pt.x = r.left;
		pt.y = r.top;
		ScreenToClient( scHwnd, &pt );
		r.left = pt.x;
		r.top = pt.y;


		pt.x = r.right;
		pt.y = r.bottom;
		ScreenToClient( scHwnd, &pt );
		r.right = pt.x;
		r.bottom = pt.y;

		if ( NULL != scrollBounds ) {
			scrollBounds->setRect( r.left, r.top, r.right, r.bottom );
		}
		if ( NULL != leftBounds ) {
			leftBounds->setRect( 0, r.top, r.left, r.bottom );
		}

		if ( NULL != rightBounds ) {
			rightBounds->setRect( r.right, r.top, scrollCorner_->getLeft(), r.bottom );
		}
	}
}

void Win32ScrollPeer::getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds, Rect* bottomBounds )
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

	if ( ::IsWindowVisible( vScrollHWnd_ ) ) {
		HWND scHwnd = (HWND)scrollableControl_->getPeer()->getHandleID();

		RECT r = {0};
		POINT pt = {0};

		::GetWindowRect( vScrollHWnd_, &r );
		pt.x = r.left;
		pt.y = r.top;
		ScreenToClient( scHwnd, &pt );
		r.left = pt.x;
		r.top = pt.y;


		pt.x = r.right;
		pt.y = r.bottom;
		ScreenToClient( scHwnd, &pt );
		r.right = pt.x;
		r.bottom = pt.y;

		if ( NULL != scrollBounds ) {
			scrollBounds->setRect( r.left, r.top, r.right, r.bottom );
		}
		if ( NULL != topBounds ) {
			topBounds->setRect( r.left, 0, r.right, r.top );
		}

		if ( NULL != bottomBounds ) {
			bottomBounds->setRect( r.left, r.bottom, r.right, scrollCorner_->getTop() );
		}
	}
}

void Win32ScrollPeer::getAdjustedPositions( double& xPosition, double& yPosition )
{
	Scrollable* scrollable = scrollableControl_->getScrollable();
	if ( NULL != scrollable ) {
		bool hasVertSB = (scrollable->hasVerticalScrollBar()) && (::IsWindowEnabled(vScrollHWnd_));
		bool hasHorzSB = (scrollable->hasHorizontalScrollBar()) && (::IsWindowEnabled(hScrollHWnd_));

		SCROLLINFO si;

		if ( hasVertSB ) {
			memset( &si, 0, sizeof(si) );
			si.cbSize = sizeof(si);
			si.fMask = SIF_POS | SIF_TRACKPOS | SIF_PAGE;
			GetScrollInfo( vScrollHWnd_, SB_CTL, &si );
			yPosition = si.nPos;
		} else {
			yPosition = 0;
		}

		if ( hasHorzSB ) {
			memset( &si, 0, sizeof(si) );
			si.cbSize = sizeof(si);
			si.fMask = SIF_POS | SIF_TRACKPOS | SIF_PAGE;
			GetScrollInfo( hScrollHWnd_, SB_CTL, &si );
			xPosition = si.nPos;
		} else {
			xPosition = 0;
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/04/13 00:57:02  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.3.2.1  2005/03/07 01:59:51  ddiego
*minor fix to win32 scroll peer, and fix to win32 list view for display of list items.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.6  2004/09/22 18:54:42  dougtinkham
*to get it working again
*
*Revision 1.2.2.5  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.4  2004/09/21 05:33:59  dougtinkham
*modified recalcScrollPositions, remove updateVirtualViewSize
*
*Revision 1.2.2.3  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.2  2004/09/14 18:21:13  dougtinkham
*fixed mistake in last checkin
*
*Revision 1.2.2.1  2004/09/14 05:13:45  dougtinkham
*changes to scrollTo and getAdjustedPositions for horizontal scrolling
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.14  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.2  2004/03/26 18:37:59  marcelloptr
*very minor fixes
*
*Revision 1.13.2.1  2004/03/21 20:25:41  marcelloptr
*Scrollable automatically calculates the scroll given the line where to go
*
*Revision 1.13  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.6  2003/11/24 05:05:24  ddiego
*added some more docs, and some minor changes to the Win32ScrollPeer
*
*Revision 1.12.4.5  2003/10/13 04:02:52  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.12.4.4  2003/09/25 04:01:13  ddiego
*minor fixes to better adjust the voewable bounds when scrolling is enabled
*added a Scrolling example
*
*Revision 1.12.4.3  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.12.4.2  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.12.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.12  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


