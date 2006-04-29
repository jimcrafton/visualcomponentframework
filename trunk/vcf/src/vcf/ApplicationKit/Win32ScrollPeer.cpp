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

		if ( System::isUnicodeEnabled() ) {
			vScrollHWnd_ = CreateWindowExW( 0, L"SCROLLBAR", NULL, WS_CHILD | SBS_VERT | WS_VISIBLE, 0, 0, 200,
			CW_USEDEFAULT, hwnd, NULL, hInst, NULL );

			hScrollHWnd_ = CreateWindowExW( 0, L"SCROLLBAR", NULL, WS_CHILD | SBS_HORZ | WS_VISIBLE, 0, 0, 200,
				CW_USEDEFAULT, hwnd, NULL, hInst, NULL );
		}
		else {
			vScrollHWnd_ = CreateWindowExA( 0, "SCROLLBAR", NULL, WS_CHILD | SBS_VERT | WS_VISIBLE, 0, 0, 200,
				CW_USEDEFAULT, hwnd, NULL, hInst, NULL );

			hScrollHWnd_ = CreateWindowExA( 0, "SCROLLBAR", NULL, WS_CHILD | SBS_HORZ | WS_VISIBLE, 0, 0, 200,
				CW_USEDEFAULT, hwnd, NULL, hInst, NULL );

		}

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

		double h = scrollableControl_->getHeight();

		bool hasVertSB = (scrollable->hasVerticalScrollBar()) && (::IsWindowEnabled(vScrollHWnd_));
		bool hasHorzSB = (scrollable->hasHorizontalScrollBar()) && (::IsWindowEnabled(hScrollHWnd_));

		int x, origX;
		x = origX = 0;

		int y, origY;
		y = origY = 0;

		if ( true == hasVertSB ) {
			origY = y = GetScrollPos( vScrollHWnd_, SB_CTL );
			y = (int)yPosition;

			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = (long)yPosition;
			SetScrollInfo( vScrollHWnd_, SB_CTL, &si, TRUE );
		}

		if ( true == hasHorzSB ) {
			origX = x = GetScrollPos( hScrollHWnd_, SB_CTL );
			x = (int)xPosition;

			memset( &si, 0, sizeof(si) );
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS ;
			si.nPos = (long)xPosition;
			SetScrollInfo( hScrollHWnd_, SB_CTL, &si, TRUE );
		}

		if ( hasHorzSB || hasVertSB ) {
			Container* container = scrollableControl_->getContainer();
			if ( NULL != container ) {
				Enumerator<Control*>* children = container->getChildren();
				while ( children->hasMoreElements() ) {
					Control* child = children->nextElement();
					if ( !child->ignoreForParentScrolling() ) {
						Rect r = child->getBounds();
						r.offset( -(x-origX), -(y-origY) );
						child->setBounds( &r );
					}
				}
			}
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
	scrollInfoVert.nPos =  (long)scrollable->getVerticalPosition();
	scrollInfoVert.nMin = 0;
	scrollInfoVert.nMax = (long) ( showVertSB  ? virtViewHeight : scrollInfoVert.nMin );	
	if ( showHorzSB && (scrollInfoVert.nMax > 0)) {
		scrollInfoVert.nMax += (long)( horzSBWidth + 1 ); 
	}

	SCROLLINFO scrollInfoHorz = {0};
	scrollInfoHorz.cbSize = sizeof(SCROLLINFO);
	scrollInfoHorz.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	scrollInfoHorz.nPage = (long)( needHorzSB ? bounds.getWidth() : 0 );
	scrollInfoHorz.nPos =  (long)scrollable->getHorizontalPosition();
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
		::InvalidateRect( vScrollHWnd_, NULL, TRUE );
		UpdateWindow( vScrollHWnd_ );
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
		::InvalidateRect( hScrollHWnd_, NULL, TRUE );
		UpdateWindow( hScrollHWnd_ );
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
$Id$
*/
