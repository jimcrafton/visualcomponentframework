//Win32UIShell.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32UIShell.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32UIShell.h"


using namespace VCF;


Win32UIShell::Win32UIShell( UIShell* shell )
{
	shell_ = shell;
	if ( NULL == shell_ ) {
		//throw exception
	}

}

Win32UIShell::~Win32UIShell()
{

}

void Win32UIShell::shellBeginPainting( Rect* clippingRect )
{
	hClipRgn_ = NULL;
	DWORD flags = DCX_WINDOW|DCX_CACHE;

	if ( NULL != clippingRect ) {
		hClipRgn_ = ::CreateRectRgn( (int32)clippingRect->left_, (int32)clippingRect->top_, (int32)clippingRect->right_, (int32)clippingRect->bottom_ );
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
	shell_->getContext()->getPeer()->setContextID( (OSHandleID)dc );
}

void Win32UIShell::shellEndPainting()
{
	::LockWindowUpdate( NULL );//unlocks the window update
	HDC dc = (HDC)shell_->getContext()->getPeer()->getContextID();
	shell_->getContext()->getPeer()->setContextID( (OSHandleID)0 );
	ReleaseDC( ::GetDesktopWindow(), dc );
	if ( NULL != hClipRgn_ ) {
		DeleteObject( hClipRgn_ );
	}
	InvalidateRect( ::GetDesktopWindow(), NULL, TRUE );
}

bool Win32UIShell::shellSupportsVirtualDirectories()
{
	return true;
}

bool Win32UIShell::shellHasFileSystemDirectory()
{
	return true;
}

String Win32UIShell::shellGetDirectory()
{
	String result = "";

	IMalloc* mallocObj = NULL;
	HRESULT hr = SHGetMalloc(&mallocObj);
	if ( SUCCEEDED(hr) ) {
		if ( System::isUnicodeEnabled() ) {
			VCFChar shellPath[MAX_PATH];
			memset( shellPath, 0, MAX_PATH*sizeof(VCFChar) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListW(pidl, shellPath);

				if ( FALSE != err ) {
					result = shellPath;
				}

				mallocObj->Free( pidl );
			}
		}
		else {
			char shellPath[MAX_PATH];
			memset( shellPath, 0, MAX_PATH*sizeof(char) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListA(pidl, shellPath);

				if ( FALSE != err ) {
					result = shellPath;
				}

				mallocObj->Free( pidl );
			}
		}

		mallocObj->Release();
	}

	return result;
}

OSHandleID Win32UIShell::shellGetHandleID()
{
	return (OSHandleID)GetDesktopWindow();
}

OSHandleID Win32UIShell::shellGetGraphicsContextHandleID()
{
	return 0;
}

void Win32UIShell::shellSetUIShell( UIShell* shell )
{
	shell_ = shell;
}

void Win32UIShell::shellTranslateToScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (int32)pt->x_, (int32)pt->y_ };
	::ClientToScreen( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

void Win32UIShell::shellTranslateFromScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (int32)pt->x_, (int32)pt->y_ };
	::ScreenToClient( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

uint32 Win32UIShell::shellGetWidth()
{
	return (uint32)GetSystemMetrics( SM_CXSCREEN );
}

uint32 Win32UIShell::shellGetHeight()
{
	return (uint32)GetSystemMetrics( SM_CYSCREEN );
}

Rect Win32UIShell::shellGetUsableBounds()
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

Point Win32UIShell::getCurrentMousePosition()
{
	::POINT pt;
	::GetCursorPos(&pt);
	return Point( pt.x, pt.y );
}


/**
$Id: Win32UIShell.cpp 2807 2006-06-27 20:25:49Z kdmix $
*/
