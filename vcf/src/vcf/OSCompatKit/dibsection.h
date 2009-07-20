// DIBSection.h : header file
//

#ifndef __DIBSECTION_H__
#define __DIBSECTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #define PERSISTANCE_SUPPORT

#ifdef PERSISTANCE_SUPPORT
#ifndef _AFX
#include <afx.h>
#endif // _AFX
#endif // PERSISTANCE_SUPPORT

#ifndef _WINDOWS_
#include <windows.h>
#endif // _WINDOWS_

// Properties:
//  NO  Abstract class (does not have any objects)
//  NO  Derived from CWnd
//  NO  Is a CWnd.                     
//  NO  Two stage creation (constructor & Create())
//  NO  Has a message map
//  NO  Needs a resource (template)
//  YES Persistent objects (saveable on disk)      
//  NO  Uses exceptions

// Desciption:

// CDIBSection is DIB section wrapper class for Win32 platforms.
// This class provides a simple interface to DIB sections including loading,
// saving and displaying.
//

// Using CDIBSection:

// This class is very simple to use. The bitmap can be set using either SetBitmap()
// (which accepts either a Device dependant or device independant bitmap, or a 
// resource ID) or by using Load(), which allows an image to be loaded from disk. 
// To display the bitmap simply use Draw or Stretch.
//
// eg. 
//
//      CDIBSection dibsection;
//      dibsection.Load(_T("image.bmp"));
//      dibsection.Draw(hdc, CPoint(0, 0));  // hdc is of type HDC
//
//      CDIBSection dibsection;
//      dibsection.SetBitmap(IDB_BITMAP); 
//      dibsection.Draw(*pDC, CPoint(0, 0));  // pDC is of type CDC*
//
// The CDIBSection API includes many methods to extract information about the
// image, as well as palette options for getting and setting the current palette.
//

/////////////////////////////////////////////////////////////////////////////
// defines

#if (_WIN32_WCE < 211)
#define DIBSECTION_NO_PALETTE           // No palette support on early CE devices
#endif

#define DS_BITMAP_FILEMARKER  ((WORD) ('M' << 8) | 'B')    // is always "BM" = 0x4D42

/////////////////////////////////////////////////////////////////////////////
// BITMAPINFO wrapper

struct DIBINFO : public BITMAPINFO
{
    RGBQUAD arColors[255];                        // Color table info - adds an extra 255 entries to palette

    operator PBITMAPINFO() { return (PBITMAPINFO)this; }
    operator PBITMAPINFOHEADER() { return &bmiHeader; }
    LPRGBQUAD GetColorTable() { return bmiColors; }
};

#ifndef DIBSECTION_NO_PALETTE
struct PALETTEINFO : public LOGPALETTE
{
    PALETTEENTRY arPalEntries[255];               // Palette entries

    PALETTEINFO() 
    {
        palVersion = (WORD)0x300;
        palNumEntries = 0;
        ZeroMemory(palPalEntry, sizeof(PALETTEENTRY) * 256); 
    }

    operator PLOGPALETTE() { return (PLOGPALETTE)this; }
    operator PPALETTEENTRY() { return (PPALETTEENTRY)palPalEntry; }
};
#endif // DIBSECTION_NO_PALETTE

/////////////////////////////////////////////////////////////////////////////
// CDIBSection object

class CDIBSection
{
// Construction
public:
    CDIBSection();
    virtual ~CDIBSection();

    void CleanUp();

// static helpers
public:
    static int BytesPerLine(int iWidth, int iBitsPerPixel);
    static int NumColorEntries(int iBitsPerPixel, int iCompression, DWORD biClrUsed = 0);

    static PALETTEENTRY ms_StdColors[];

#ifndef DIBSECTION_NO_PALETTE
    static BOOL IsPaletteEnabled(HDC hdc)
    {
        return GetDeviceCaps(hdc, RASTERCAPS) & RC_PALETTE;
    }

    static HPALETTE CreateHalftonePalette(int iNumColors);
#endif // DIBSECTION_NO_PALETTE

// Attributes
public:
    operator HBITMAP() const
    {
        return GetSafeHandle();
    }

    HBITMAP GetSafeHandle() const
    {
        return this ? m_hBitmap : NULL;
    }

    void GetSize(SIZE& size) const 
    {
        size.cx = GetWidth();
        size.cy = GetHeight();
    }

    int GetHeight() const
    {
        return m_DIBinfo.bmiHeader.biHeight;
    } 

    int GetWidth() const
    {
        return m_DIBinfo.bmiHeader.biWidth;
    }

    int GetPlanes() const
    { 
        return m_DIBinfo.bmiHeader.biPlanes;
    }

    int GetBitCount() const
    {
        return m_DIBinfo.bmiHeader.biBitCount;
    }

    PVOID GetDIBits()
    {
        return m_ppvBits;
    }

    PBITMAPINFO GetBitmapInfo()
    {
        return (PBITMAPINFO)m_DIBinfo;
    }

    DWORD GetImageSize() const
    {
        return m_DIBinfo.bmiHeader.biSizeImage;
    }

    PBITMAPINFOHEADER GetBitmapInfoHeader()
    {
        return (PBITMAPINFOHEADER)m_DIBinfo;
    }

    BOOL CreateBitmap(int cx, int cy, int iBits);
    BOOL SetBitmap(UINT uResId, HINSTANCE hInstance = NULL);
    BOOL SetBitmap(LPCTSTR pszResName, HINSTANCE hInstance = NULL);
    BOOL SetBitmap(HBITMAP hBitmap
#ifndef DIBSECTION_NO_PALETTE
        , HPALETTE pPalette = NULL
#endif // DIBSECTION_NO_PALETTE
        );
    BOOL SetBitmap(PBITMAPINFO pBitmapInfo, PVOID pBits);   

    LPRGBQUAD GetColorTable()
    {
        return m_DIBinfo.GetColorTable();
    }

    BOOL SetColorTable(UINT uNumColors, LPRGBQUAD pColors);

    UINT GetColorTableSize()
    {
        return m_uColorTableSize;
    }

#ifndef DIBSECTION_NO_PALETTE
    HPALETTE GetPalette()
    {
        return m_hPalette;
    }

    BOOL SetPalette(HPALETTE hPalette);
    BOOL SetLogPalette(PLOGPALETTE pLogPalette);
#endif // DIBSECTION_NO_PALETTE

// Operations
public:
#ifdef PERSISTANCE_SUPPORT
    BOOL Load(LPCTSTR pszFileName);
    BOOL Save(LPCTSTR pszFileName);
#endif // PERSISTANCE_SUPPORT

    BOOL Copy(CDIBSection& ds);

    BOOL Draw(HDC hdc, const POINT& ptDest, BOOL bForceBackground = FALSE);
    BOOL Stretch(HDC hdc, const POINT& ptDest, const SIZE& size, BOOL bForceBackground = FALSE);

// Overrideables

// Implementation
protected:
    void _ShowLastError();

#ifndef DIBSECTION_NO_PALETTE
    BOOL CreateSparePalette();
    BOOL FillDIBColorTable(UINT iNumColors, LPRGBQUAD pRGB);
#endif // DIBSECTION_NO_PALETTE

    UINT GetColorTableEntries(HDC hdc, HBITMAP hBitmap);

#ifdef _WIN32_WCE
    HDC GetMemoryDC(HDC pDC = NULL, BOOL bSelectPalette = TRUE);
    BOOL ReleaseMemoryDC(BOOL bForceRelease = FALSE);

	HDC m_hdcMem;
	HGDIOBJ m_hbmpOld;
#ifndef DIBSECTION_NO_MEMDC_REUSE
	BOOL m_bReuseMemoryDC;
#endif // DIBSECTION_NO_MEMDC_REUSE
#ifndef DIBSECTION_NO_PALETTE
    HPALETTE m_hpalOld;
#endif // DIBSECTION_NO_PALETTE
#endif // _WIN32_WCE

protected:
    HBITMAP  m_hBitmap;                           // Handle to DIBSECTION
    DIBINFO  m_DIBinfo;                           // Bitmap header & color table info
    PBYTE    m_ppvBits;                           // Pointer to bitmap bits
    UINT     m_uColorDataType;                    // color data type (palette or RGB values)
    UINT     m_uColorTableSize;                   // Size of color table

#ifndef DIBSECTION_NO_PALETTE
    HPALETTE m_hPalette;                          // Color palette
#endif // DIBSECTION_NO_PALETTE
};

/////////////////////////////////////////////////////////////////////////////

#endif // __DIBSECTION_H__
