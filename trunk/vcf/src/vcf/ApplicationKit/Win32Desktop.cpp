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
	desktop_->getContext()->getPeer()->setContextID( (long)dc );
}

void Win32Desktop::desktopEndPainting()
{
	::LockWindowUpdate( NULL );//unlocks the window update
	HDC dc = (HDC)desktop_->getContext()->getPeer()->getContextID();
	desktop_->getContext()->getPeer()->setContextID( (long)0 );
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
			memset( desktopPath, 0, MAX_PATH );
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

ulong32 Win32Desktop::desktopGetHandleID()
{
	return (ulong32)GetDesktopWindow();
}

ulong32 Win32Desktop::desktopGetGraphicsContextHandleID()
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.16.8.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.16  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.1  2003/03/12 03:12:26  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.14.2  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14.14.1  2002/12/26 04:32:11  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Revision 1.14  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.2  2002/04/27 15:52:28  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.13  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.12  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


