//Win32CursorPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32CursorPeer.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32CursorPeer.h"


using namespace VCF;


#define IDC_HAND            MAKEINTRESOURCE(32649)


#define WIDTHBYTES(bits)  (((bits) + 31) / 32 * 4)



Win32CursorPeer::Win32CursorPeer( Cursor* cursor )
{
	isSharedCursor_ = false;
	cursor_ = cursor;
	hCursor_ = NULL;
	cursorID_ = CursorManager::UNREGISTERED_ID;
}

Win32CursorPeer::~Win32CursorPeer()
{
	if ( (NULL != hCursor_) && (false == isSharedCursor_) ) {
		DestroyCursor( hCursor_ );
	}
}

void Win32CursorPeer::createFromResourceName( const String& cursorName, const ulong32& instanceHandle )
{
	HINSTANCE hInst = (HINSTANCE)instanceHandle;
	if ( NULL == hInst ) {
		hInst = GetModuleHandle(NULL);
	}
	isSharedCursor_ = true;
	if ( System::isUnicodeEnabled() ) {
		hCursor_ = LoadCursorW( hInst, cursorName.c_str() );
	}
	else {
		hCursor_ = LoadCursorA( hInst, cursorName.ansi_c_str() );
	}

}

void Win32CursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{
	LPCTSTR win32SystemCursor = NULL;
	isSharedCursor_ = true;
	cursorID_ = (long)systemCursor;
	switch ( systemCursor ) {
		case Cursor::SCT_DEFAULT : {
			win32SystemCursor = IDC_ARROW;
		}
		break;

		case Cursor::SCT_SPLIT_VERT : {
			win32SystemCursor = IDC_SIZEWE;
		}
		break;

		case Cursor::SCT_SPLIT_HORZ : {
			win32SystemCursor = IDC_SIZENS;
		}
		break;

		case Cursor::SCT_SIZE_HORZ : {
			win32SystemCursor = IDC_SIZEWE;
		}
		break;

		case Cursor::SCT_SIZE_VERT : {
			win32SystemCursor = IDC_SIZENS;
		}
		break;

		case Cursor::SCT_SIZE_NE_SW : {
			win32SystemCursor = IDC_SIZENESW;
		}
		break;

		case Cursor::SCT_SIZE_NW_SE : {
			win32SystemCursor = IDC_SIZENWSE;
		}
		break;

		case Cursor::SCT_TEXT : {
			win32SystemCursor = IDC_IBEAM;
		}
		break;

		case Cursor::SCT_HELP : {
			win32SystemCursor = IDC_HELP;
		}
		break;

		case Cursor::SCT_WAIT : {
			win32SystemCursor = IDC_WAIT;
		}
		break;

		case Cursor::SCT_WAITING : {
			win32SystemCursor = IDC_APPSTARTING;
		}
		break;

		case Cursor::SCT_NOWAYHOSER : {
			win32SystemCursor = IDC_NO;
		}
		break;

		case Cursor::SCT_CROSSHAIRS : {
			win32SystemCursor = IDC_CROSS;
		}
		break;

		case Cursor::SCT_POINTING_HAND : {
			win32SystemCursor = IDC_HAND;
		}
		break;


	}

	hCursor_ = LoadCursor(NULL, win32SystemCursor);

}

void Win32CursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{
	Win32Image* win32Img = (Win32Image*)cursorImage;
	HBITMAP imgHBMP = win32Img->getBitmap();

	HBITMAP hbmMono = Win32CursorPeer::colorDDBToMonoDDB(imgHBMP, 0, 0, NULL);

	ICONINFO iconInfo;
	memset( &iconInfo, 0, sizeof(ICONINFO) );
	iconInfo.fIcon = FALSE;
	iconInfo.hbmColor = imgHBMP;
	iconInfo.hbmMask = hbmMono;
	iconInfo.xHotspot = (long)hotSpot->x_;
	iconInfo.yHotspot = (long)hotSpot->y_;

	hCursor_ = CreateIconIndirect( &iconInfo );

}

WORD Win32CursorPeer::dibNumColors ( void* pv )
{
    int                bits;
    LPBITMAPINFOHEADER lpbi;
    LPBITMAPCOREHEADER lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    // With the BITMAPINFO format headers, the size of the palette is
    // in biClrUsed. In the BITMAPCORE-style headers, it depends on
    // the bits per pixel (2 raised to the power of bits/pixel).

    if (lpbi->biSize != sizeof(BITMAPCOREHEADER))
    {
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		// A 24 bit DIB has no color table
		return 0;
	}
}

WORD Win32CursorPeer::paletteSize( void* pv )
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = Win32CursorPeer::dibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return NumColors * sizeof(RGBTRIPLE);
    else
        return NumColors * sizeof(RGBQUAD);
}

HBITMAP Win32CursorPeer::colorDDBToMonoDDB( HBITMAP hbm, DWORD biStyle, WORD biBits, HPALETTE hpal )
{
    BITMAP               bm;
    BITMAPINFOHEADER     bi;
    BITMAPINFOHEADER FAR *lpbi;
    DWORD                dwLen;
    HANDLE               hdib;
    HANDLE               h;
    HDC                  hdc;
    HBITMAP              hbmMono;

    if (!hbm)
        return NULL;

    if (hpal == NULL)
        hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

    GetObject(hbm, sizeof(bm), (LPSTR)&bm);

    if (biBits == 0)
        biBits = bm.bmPlanes * bm.bmBitsPixel;

    bi.biSize          = sizeof(BITMAPINFOHEADER);
    bi.biWidth         = bm.bmWidth;
    bi.biHeight        = bm.bmHeight;
    bi.biPlanes        = 1;
    bi.biBitCount      = biBits;
    bi.biCompression   = biStyle;
    bi.biSizeImage     = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed       = 0;
    bi.biClrImportant  = 0;

    dwLen = bi.biSize + Win32CursorPeer::paletteSize(&bi);

    hdc = GetDC(::GetDesktopWindow());
    hpal = SelectPalette(hdc, hpal, FALSE);
    RealizePalette(hdc);

    hdib = GlobalAlloc(GHND, dwLen);

    if (!hdib)
	{
        SelectPalette(hdc, hpal, FALSE);
        ReleaseDC(::GetDesktopWindow(), hdc);
        return NULL;
	}

    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    *lpbi = bi;

    // Call GetDIBits with a NULL lpBits parameter; it will calculate
    // the biSizeImage field.
    GetDIBits(hdc, hbm, 0, (WORD)bi.biHeight,
        NULL, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);

    // If the driver did not fill in the biSizeImage field,
    // calculate it.
    if (bi.biSizeImage == 0)
	{
        bi.biSizeImage = WIDTHBYTES((DWORD)bm.bmWidth * biBits)
            * bm.bmHeight;
        if (biStyle != BI_RGB)
            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

    // Reallocate the buffer big enough to hold all the bits.
    dwLen = bi.biSize + Win32CursorPeer::paletteSize(&bi) + bi.biSizeImage;
    if ((h = GlobalReAlloc(hdib, dwLen, 0)))
        hdib = h;
    else
	{
        GlobalFree(hdib);
        hdib = NULL;

        SelectPalette(hdc, hpal, FALSE);
        ReleaseDC(::GetDesktopWindow(), hdc);
        return (HBITMAP)hdib;
	}

    // Call GetDIBits with a NON-NULL lpBits parameter, to actually
    // get the bits this time.
    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    if (GetDIBits(hdc, hbm, 0, (WORD)bi.biHeight,
		(LPSTR)lpbi + (WORD)lpbi->biSize + Win32CursorPeer::paletteSize(lpbi),
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS) == 0)
	{
		GlobalUnlock(hdib);
		hdib = NULL;
		SelectPalette(hdc, hpal, FALSE);
		ReleaseDC(::GetDesktopWindow(), hdc);
		return NULL;
	}

    // Finally, create a monochrome DDB, and put the DIB into it.
    // SetDIBits does smart color conversion.
    hbmMono = CreateBitmap((WORD)lpbi->biWidth, (WORD)lpbi->biHeight,
		1, 1, NULL);
    SetDIBits(hdc, hbmMono, 0, lpbi->biHeight,
		(LPSTR)lpbi + lpbi->biSize + Win32CursorPeer::paletteSize(lpbi),
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);
    GlobalFree(hdib);

    SelectPalette(hdc, hpal, FALSE);
    ReleaseDC(::GetDesktopWindow(), hdc);
    return hbmMono;

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
*Revision 1.11.8.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.11  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:12:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:28  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.8  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


