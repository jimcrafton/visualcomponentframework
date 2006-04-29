//Win32Desktop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32Desktop.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Desktop.h"


using namespace VCF;


Win32Desktop::Win32Desktop( Desktop* desktop )
{
	desktop_ = desktop;
	if ( NULL == desktop_ ) {
		//throw exception
	}

}

Win32Desktop::~Win32Desktop()
{

}

void Win32Desktop::desktopBeginPainting( Rect* clippingRect )
{
	hClipRgn_ = NULL;
	DWORD flags = DCX_WINDOW|DCX_CACHE;

	if ( NULL != clippingRect ) {
		hClipRgn_ = ::CreateRectRgn( (long)clippingRect->left_, (long)clippingRect->top_, (long)clippingRect->right_, (long)clippingRect->bottom_ );
		flags |= DCX_INTERSECTRGN;
	}

	HDC dc = NULL;


	if ( LockWindowUpdate( ::GetDesktopWindow() ) ) {
		flags |= DCX_LOCKWINDOWUPDATE;
	}

	dc = ::GetDCEx( ::GetDesktopWindow(), hClipRgn_, flags );

	if ( NULL == dc ) {
		//throw exception !!
	}
	desktop_->getContext()->getPeer()->setContextID( (OSHandleID)dc );
}

void Win32Desktop::desktopEndPainting()
{
	::LockWindowUpdate( NULL );//unlocks the window update
	HDC dc = (HDC)desktop_->getContext()->getPeer()->getContextID();
	desktop_->getContext()->getPeer()->setContextID( (OSHandleID)0 );
	ReleaseDC( ::GetDesktopWindow(), dc );
	if ( NULL != hClipRgn_ ) {
		DeleteObject( hClipRgn_ );
	}
	InvalidateRect( ::GetDesktopWindow(), NULL, TRUE );
}

bool Win32Desktop::desktopSupportsVirtualDirectories()
{
	return true;
}

bool Win32Desktop::desktopHasFileSystemDirectory()
{
	return true;
}

String Win32Desktop::desktopGetDirectory()
{
	String result = "";

	IMalloc* mallocObj = NULL;
	HRESULT hr = SHGetMalloc(&mallocObj);
	if ( SUCCEEDED(hr) ) {
		if ( System::isUnicodeEnabled() ) {
			VCFChar desktopPath[MAX_PATH];
			memset( desktopPath, 0, MAX_PATH*sizeof(VCFChar) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListW(pidl, desktopPath);

				if ( FALSE != err ) {
					result = desktopPath;
				}

				mallocObj->Free( pidl );
			}
		}
		else {
			char desktopPath[MAX_PATH];
			memset( desktopPath, 0, MAX_PATH*sizeof(char) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListA(pidl, desktopPath);

				if ( FALSE != err ) {
					result = desktopPath;
				}

				mallocObj->Free( pidl );
			}
		}

		mallocObj->Release();
	}

	return result;
}

OSHandleID Win32Desktop::desktopGetHandleID()
{
	return (OSHandleID)GetDesktopWindow();
}

OSHandleID Win32Desktop::desktopGetGraphicsContextHandleID()
{
	return 0;
}

void Win32Desktop::desktopSetDesktop( Desktop* desktop )
{
	desktop_ = desktop;
}

void Win32Desktop::desktopTranslateToScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (long)pt->x_, (long)pt->y_ };
	::ClientToScreen( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

void Win32Desktop::desktopTranslateFromScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (long)pt->x_, (long)pt->y_ };
	::ScreenToClient( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

ulong32 Win32Desktop::desktopGetWidth()
{
	return (ulong32)GetSystemMetrics( SM_CXSCREEN );
}

ulong32 Win32Desktop::desktopGetHeight()
{
	return (ulong32)GetSystemMetrics( SM_CYSCREEN );
}

Rect Win32Desktop::desktopGetUsableBounds()
{
	Rect result;

	RECT r;
	SystemParametersInfo( SPI_GETWORKAREA, 0, &r, 0 );
	result.left_ = r.left;
	result.top_ = r.top;
	result.right_ = r.right;
	result.bottom_ = r.bottom;

	return result;
}

Point Win32Desktop::getCurrentMousePosition()
{
	::POINT pt;
	::GetCursorPos(&pt);
	return Point( pt.x, pt.y );
}


/**
$Id$
*/
