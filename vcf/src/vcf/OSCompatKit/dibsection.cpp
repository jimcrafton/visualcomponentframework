// CDIBSection.cpp : implementation file
//
// General purpose DIB section wrapper class for Win9x, NT 4.0
//
// History :  25 May 1999 - First release
//             4 Jun 1999 - Fixed SetBitmap bug
//             4 May 2000 - 16 or 32 bit compression bug fix (Jim Miller <jam@3dfx.com>)
//            20 Sep 2000 - Bug fix in Save() (saving 4 bytes too many - Tadeusz Dracz)
//                          Allowed lpBits to be NULL in SetBitmap - Don Grasberger
//                          Fixed NumColorEntries bug - Itay Szekely
//                          Fixed buffer overrun bug in Load() - Itay Szekely
//             5 Apr 2000 - Fix for 16/32 bpp bitmaps for PocketPC's (Dan Robbins - DCR)
//
//            12 Nov 2004 - Modified by Dandy Cheung, MFC dependency removed
//             1 Jun 2004 - Updated to Year 2000 version by Dandy Cheung

#include "stdafx.h"
#include "DIBSection.h"

#ifndef ASSERT
#define ASSERT(x)
#endif // ASSERT

#ifndef TRACE
#define TRACE   sizeof
#endif // TRACE

// Standard colors
PALETTEENTRY CDIBSection::ms_StdColors[] =
{
#ifdef USE_HALFTONE_1
    { 0x00, 0x00, 0x00, 0 },    // First 2 will be palette for monochrome bitmaps
    { 0xFF, 0xFF, 0xFF, 0 },

    { 0x00, 0x00, 0xFF, 0 },    // First 16 will be palette for 16 color bitmaps
    { 0x00, 0xFF, 0x00, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0xFF, 0xFF, 0x00, 0 },

    { 0x00, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0x80, 0x00, 0x00, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x80, 0 },

    { 0xC0, 0xC0, 0xC0, 0 },
#else // USE_HALFTONE_1
    { 0x00, 0x00, 0x00, 0 },  // System palette - first 10 colors
    { 0x80, 0x00, 0x00, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x00, 0x00, 0x80, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0xC0, 0xC0, 0xC0, 0 },
    { 0xC0, 0xDC, 0xC0, 0 },
    { 0xA6, 0xCA, 0xF0, 0 },

    { 0x2C, 0x00, 0x00, 0 },
    { 0x56, 0x00, 0x00, 0 },
    { 0x87, 0x00, 0x00, 0 },
    { 0xC0, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0x2C, 0x00, 0 },
    { 0x2C, 0x2C, 0x00, 0 },
    { 0x56, 0x2C, 0x00, 0 },
    { 0x87, 0x2C, 0x00, 0 },
    { 0xC0, 0x2C, 0x00, 0 },
    { 0xFF, 0x2C, 0x00, 0 },
    { 0x00, 0x56, 0x00, 0 },
    { 0x2C, 0x56, 0x00, 0 },
    { 0x56, 0x56, 0x00, 0 },
    { 0x87, 0x56, 0x00, 0 },
    { 0xC0, 0x56, 0x00, 0 },
    { 0xFF, 0x56, 0x00, 0 },
    { 0x00, 0x87, 0x00, 0 },
    { 0x2C, 0x87, 0x00, 0 },
    { 0x56, 0x87, 0x00, 0 },
    { 0x87, 0x87, 0x00, 0 },
    { 0xC0, 0x87, 0x00, 0 },
    { 0xFF, 0x87, 0x00, 0 },
    { 0x00, 0xC0, 0x00, 0 },
    { 0x2C, 0xC0, 0x00, 0 },
    { 0x56, 0xC0, 0x00, 0 },
    { 0x87, 0xC0, 0x00, 0 },
    { 0xC0, 0xC0, 0x00, 0 },
    { 0xFF, 0xC0, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0x2C, 0xFF, 0x00, 0 },
    { 0x56, 0xFF, 0x00, 0 },
    { 0x87, 0xFF, 0x00, 0 },
    { 0xC0, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0x2C, 0 },
    { 0x2C, 0x00, 0x2C, 0 },
    { 0x56, 0x00, 0x2C, 0 },
    { 0x87, 0x00, 0x2C, 0 },
    { 0xC0, 0x00, 0x2C, 0 },
    { 0xFF, 0x00, 0x2C, 0 },
    { 0x00, 0x2C, 0x2C, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x56, 0x2C, 0x2C, 0 },
    { 0x87, 0x2C, 0x2C, 0 },
    { 0xC0, 0x2C, 0x2C, 0 },
    { 0xFF, 0x2C, 0x2C, 0 },
    { 0x00, 0x56, 0x2C, 0 },
    { 0x2C, 0x56, 0x2C, 0 },
    { 0x56, 0x56, 0x2C, 0 },
    { 0x87, 0x56, 0x2C, 0 },
    { 0xC0, 0x56, 0x2C, 0 },
    { 0xFF, 0x56, 0x2C, 0 },
    { 0x00, 0x87, 0x2C, 0 },
    { 0x2C, 0x87, 0x2C, 0 },
    { 0x56, 0x87, 0x2C, 0 },
    { 0x87, 0x87, 0x2C, 0 },
    { 0xC0, 0x87, 0x2C, 0 },
    { 0xFF, 0x87, 0x2C, 0 },
    { 0x00, 0xC0, 0x2C, 0 },
    { 0x2C, 0xC0, 0x2C, 0 },
    { 0x56, 0xC0, 0x2C, 0 },
    { 0x87, 0xC0, 0x2C, 0 },
    { 0xC0, 0xC0, 0x2C, 0 },
    { 0xFF, 0xC0, 0x2C, 0 },
    { 0x00, 0xFF, 0x2C, 0 },
    { 0x2C, 0xFF, 0x2C, 0 },
    { 0x56, 0xFF, 0x2C, 0 },
    { 0x87, 0xFF, 0x2C, 0 },
    { 0xC0, 0xFF, 0x2C, 0 },
    { 0xFF, 0xFF, 0x2C, 0 },
    { 0x00, 0x00, 0x56, 0 },
    { 0x2C, 0x00, 0x56, 0 },
    { 0x56, 0x00, 0x56, 0 },
    { 0x87, 0x00, 0x56, 0 },
    { 0xC0, 0x00, 0x56, 0 },
    { 0xFF, 0x00, 0x56, 0 },
    { 0x00, 0x2C, 0x56, 0 },
    { 0x2C, 0x2C, 0x56, 0 },
    { 0x56, 0x2C, 0x56, 0 },
    { 0x87, 0x2C, 0x56, 0 },
    { 0xC0, 0x2C, 0x56, 0 },
    { 0xFF, 0x2C, 0x56, 0 },
    { 0x00, 0x56, 0x56, 0 },
    { 0x2C, 0x56, 0x56, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x87, 0x56, 0x56, 0 },
    { 0xC0, 0x56, 0x56, 0 },
    { 0xFF, 0x56, 0x56, 0 },
    { 0x00, 0x87, 0x56, 0 },
    { 0x2C, 0x87, 0x56, 0 },
    { 0x56, 0x87, 0x56, 0 },
    { 0x87, 0x87, 0x56, 0 },
    { 0xC0, 0x87, 0x56, 0 },
    { 0xFF, 0x87, 0x56, 0 },
    { 0x00, 0xC0, 0x56, 0 },
    { 0x2C, 0xC0, 0x56, 0 },
    { 0x56, 0xC0, 0x56, 0 },
    { 0x87, 0xC0, 0x56, 0 },
    { 0xC0, 0xC0, 0x56, 0 },
    { 0xFF, 0xC0, 0x56, 0 },
    { 0x00, 0xFF, 0x56, 0 },
    { 0x2C, 0xFF, 0x56, 0 },
    { 0x56, 0xFF, 0x56, 0 },
    { 0x87, 0xFF, 0x56, 0 },
    { 0xC0, 0xFF, 0x56, 0 },
    { 0xFF, 0xFF, 0x56, 0 },
    { 0x00, 0x00, 0x87, 0 },
    { 0x2C, 0x00, 0x87, 0 },
    { 0x56, 0x00, 0x87, 0 },
    { 0x87, 0x00, 0x87, 0 },
    { 0xC0, 0x00, 0x87, 0 },
    { 0xFF, 0x00, 0x87, 0 },
    { 0x00, 0x2C, 0x87, 0 },
    { 0x2C, 0x2C, 0x87, 0 },
    { 0x56, 0x2C, 0x87, 0 },
    { 0x87, 0x2C, 0x87, 0 },
    { 0xC0, 0x2C, 0x87, 0 },
    { 0xFF, 0x2C, 0x87, 0 },
    { 0x00, 0x56, 0x87, 0 },
    { 0x2C, 0x56, 0x87, 0 },
    { 0x56, 0x56, 0x87, 0 },
    { 0x87, 0x56, 0x87, 0 },
    { 0xC0, 0x56, 0x87, 0 },
    { 0xFF, 0x56, 0x87, 0 },
    { 0x00, 0x87, 0x87, 0 },
    { 0x2C, 0x87, 0x87, 0 },
    { 0x56, 0x87, 0x87, 0 },
    { 0x87, 0x87, 0x87, 0 },
    { 0xC0, 0x87, 0x87, 0 },
    { 0xFF, 0x87, 0x87, 0 },
    { 0x00, 0xC0, 0x87, 0 },
    { 0x2C, 0xC0, 0x87, 0 },
    { 0x56, 0xC0, 0x87, 0 },
    { 0x87, 0xC0, 0x87, 0 },
    { 0xC0, 0xC0, 0x87, 0 },
    { 0xFF, 0xC0, 0x87, 0 },
    { 0x00, 0xFF, 0x87, 0 },
    { 0x2C, 0xFF, 0x87, 0 },
    { 0x56, 0xFF, 0x87, 0 },
    { 0x87, 0xFF, 0x87, 0 },
    { 0xC0, 0xFF, 0x87, 0 },
    { 0xFF, 0xFF, 0x87, 0 },
    { 0x00, 0x00, 0xC0, 0 },
    { 0x2C, 0x00, 0xC0, 0 },
    { 0x56, 0x00, 0xC0, 0 },
    { 0x87, 0x00, 0xC0, 0 },
    { 0xC0, 0x00, 0xC0, 0 },
    { 0xFF, 0x00, 0xC0, 0 },
    { 0x00, 0x2C, 0xC0, 0 },
    { 0x2C, 0x2C, 0xC0, 0 },
    { 0x56, 0x2C, 0xC0, 0 },
    { 0x87, 0x2C, 0xC0, 0 },
    { 0xC0, 0x2C, 0xC0, 0 },
    { 0xFF, 0x2C, 0xC0, 0 },
    { 0x00, 0x56, 0xC0, 0 },
    { 0x2C, 0x56, 0xC0, 0 },
    { 0x56, 0x56, 0xC0, 0 },
    { 0x87, 0x56, 0xC0, 0 },
    { 0xC0, 0x56, 0xC0, 0 },
    { 0xFF, 0x56, 0xC0, 0 },
    { 0x00, 0x87, 0xC0, 0 },
    { 0x2C, 0x87, 0xC0, 0 },
    { 0x56, 0x87, 0xC0, 0 },
    { 0x87, 0x87, 0xC0, 0 },
    { 0xC0, 0x87, 0xC0, 0 },
    { 0xFF, 0x87, 0xC0, 0 },
    { 0x00, 0xC0, 0xC0, 0 },
    { 0x2C, 0xC0, 0xC0, 0 },
    { 0x56, 0xC0, 0xC0, 0 },
    { 0x87, 0xC0, 0xC0, 0 },
    { 0xFF, 0xC0, 0xC0, 0 },
    { 0x00, 0xFF, 0xC0, 0 },
    { 0x2C, 0xFF, 0xC0, 0 },
    { 0x56, 0xFF, 0xC0, 0 },
    { 0x87, 0xFF, 0xC0, 0 },
    { 0xC0, 0xFF, 0xC0, 0 },
    { 0xFF, 0xFF, 0xC0, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0x2C, 0x00, 0xFF, 0 },
    { 0x56, 0x00, 0xFF, 0 },
    { 0x87, 0x00, 0xFF, 0 },
    { 0xC0, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0x2C, 0xFF, 0 },
    { 0x2C, 0x2C, 0xFF, 0 },
    { 0x56, 0x2C, 0xFF, 0 },
    { 0x87, 0x2C, 0xFF, 0 },
    { 0xC0, 0x2C, 0xFF, 0 },
    { 0xFF, 0x2C, 0xFF, 0 },
    { 0x00, 0x56, 0xFF, 0 },
    { 0x2C, 0x56, 0xFF, 0 },
    { 0x56, 0x56, 0xFF, 0 },
    { 0x87, 0x56, 0xFF, 0 },
    { 0xC0, 0x56, 0xFF, 0 },
    { 0xFF, 0x56, 0xFF, 0 },
    { 0x00, 0x87, 0xFF, 0 },
    { 0x2C, 0x87, 0xFF, 0 },
    { 0x56, 0x87, 0xFF, 0 },
    { 0x87, 0x87, 0xFF, 0 },
    { 0xC0, 0x87, 0xFF, 0 },
    { 0xFF, 0x87, 0xFF, 0 },
    { 0x00, 0xC0, 0xFF, 0 },
    { 0x2C, 0xC0, 0xFF, 0 },
    { 0x56, 0xC0, 0xFF, 0 },
    { 0x87, 0xC0, 0xFF, 0 },
    { 0xC0, 0xC0, 0xFF, 0 },
    { 0xFF, 0xC0, 0xFF, 0 },
    { 0x2C, 0xFF, 0xFF, 0 },
    { 0x56, 0xFF, 0xFF, 0 },
    { 0x87, 0xFF, 0xFF, 0 },
    { 0xC0, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
    { 0x11, 0x11, 0x11, 0 },
    { 0x18, 0x18, 0x18, 0 },
    { 0x1E, 0x1E, 0x1E, 0 },
    { 0x25, 0x25, 0x25, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x34, 0x34, 0x34, 0 },
    { 0x3C, 0x3C, 0x3C, 0 },
    { 0x44, 0x44, 0x44, 0 },
    { 0x4D, 0x4D, 0x4D, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x5F, 0x5F, 0x5F, 0 },
    { 0x69, 0x69, 0x69, 0 },
    { 0x72, 0x72, 0x72, 0 },
    { 0x7D, 0x7D, 0x7D, 0 },
    { 0x92, 0x92, 0x92, 0 },
    { 0x9D, 0x9D, 0x9D, 0 },
    { 0xA8, 0xA8, 0xA8, 0 },
    { 0xB4, 0xB4, 0xB4, 0 },
    { 0xCC, 0xCC, 0xCC, 0 },
    { 0xD8, 0xD8, 0xD8, 0 },
    { 0xE5, 0xE5, 0xE5, 0 },
    { 0xF2, 0xF2, 0xF2, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },

    { 0xFF, 0xFB, 0xF0, 0 },  // System palette - last 10 colors
    { 0xA0, 0xA0, 0xA4, 0 },
    { 0x80, 0x80, 0x80, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
#endif // USE_HALFTONE_1
};

#ifdef _WIN32_WCE
UINT WINAPI GetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries, LPRGBQUAD pColors);
#endif // _WIN32_WCE

/////////////////////////////////////////////////////////////////////////////
// CDIBSection static functions

// Returns the number of color table entries given the number of bits per pixel
// of a bitmap
int CDIBSection::NumColorEntries(int iBitsPerPixel, int iCompression, DWORD biClrUsed) 
{
    int iColors = 0;

    switch(iBitsPerPixel) 
    {
        case 1:  iColors = 2;   break;
#ifdef _WIN32_WCE
        case 2:  iColors = 4;   break;   // Windows CE only       
#endif // _WIN32_WCE
        case 4:  iColors = 16;  break;
        case 8:  iColors = 256; break;
        case 24: iColors = 0;   break; // 16, 24 or 32 bpp have no color table
        case 16:
        case 32:
#ifdef _WIN32_WCE
            // I've found that PocketPCs need this regardless of BI_RGB or BI_BITFIELDS
            iColors = 3;   break;
#else // _WIN32_WCE
            // 16 or 32 bpp have 3 colors(masks) in the color table if bitfield compression
            iColors = (iCompression == BI_BITFIELDS) ? 3 : 0;
#endif // _WIN32_WCE

        default:
           ASSERT(FALSE);
    }

    // If biClrUsed is provided, and it is a legal value, use it
    if(biClrUsed > 0 && biClrUsed <= (DWORD)iColors)
        return biClrUsed;

    return iColors;
}

// Returns the number of storage bytes needed for each scanline in the bitmap
int CDIBSection::BytesPerLine(int iWidth, int iBitsPerPixel)
{
    return ((iWidth * iBitsPerPixel + 31) & (~31)) >> 3;
}

#ifndef DIBSECTION_NO_PALETTE
// Creates a halftone color palette independant of screen color depth. palette
// will be filled with the colors, and nNumColors is the No. of colors to file.
// If nNumColors is 0 or > 256, then 256 colors are used.
HPALETTE CDIBSection::CreateHalftonePalette(int iNumColors)
{
#ifdef USE_HALFTONE_1
    int iNumStandardColors = sizeof(ms_StdColors) / sizeof(ms_StdColors[0]);
    int iIndex = 0;
    int iNumEntries = iNumColors;
    if(iNumEntries <= 0 || iNumEntries > 256)
        iNumEntries = 256;

    PALETTEINFO pi;                   
    pi.palNumEntries = (WORD)iNumEntries;

    // The standard colors (16)
    for(int i=0; i<iNumStandardColors; i++)
    {
        if(iIndex >= iNumEntries)
            break;

        CopyMemory(&pi.palPalEntry[iIndex], &ms_StdColors[i], sizeof(PALETTEENTRY));
        iIndex++;
    }

    // A color cube (6 divisions = 216)
    for(int blue=0; blue<6; blue++)
    {
        for(int green=0; green<6; green++)
        {
            for(int red=0; red<6; red++)
            {
                if(iIndex >= iNumEntries)
                    break;

                pi.palPalEntry[iIndex].peRed = (BYTE)((red * 255) / 5);
                pi.palPalEntry[iIndex].peGreen = (BYTE)((green * 255) / 5);
                pi.palPalEntry[iIndex].peBlue = (BYTE)((blue * 255) / 5);
                pi.palPalEntry[iIndex].peFlags = 0;

                iIndex++;
            }
        }
    }

    // A grey scale (24 divisions)
    for(int grey=0; grey<24; grey++)
    {
        if(iIndex >= iNumEntries) 
            break;

        pi.palPalEntry[iIndex].peRed = (BYTE)(grey * 255 / 23);
        pi.palPalEntry[iIndex].peGreen = (BYTE)(grey * 255 / 23);
        pi.palPalEntry[iIndex].peBlue = (BYTE)(grey * 255 / 23);
        pi.palPalEntry[iIndex].peFlags = 0;
        iIndex++;
    }

    return CreatePalette(&pi);
#else // USE_HALFTONE_1
    // Sanity check on requested number of colors.
    if(iNumColors <= 0 || iNumColors > 256)
        iNumColors = 256;
    else if(iNumColors <= 2)
        iNumColors = 2;
    else if(iNumColors <= 16)
        iNumColors = 16;
    else if(iNumColors <= 256)
        iNumColors = 256;

    PALETTEINFO pi;                   
    pi.palNumEntries = (WORD)iNumColors;

    if(iNumColors == 2)
    {
        // According to the MS article "The Palette Manager: How and Why"
        // monochrome palettes not really needed (will use B&W)
        pi.palPalEntry[0].peRed   = ms_StdColors[0].peRed;
        pi.palPalEntry[0].peGreen = ms_StdColors[0].peGreen;
        pi.palPalEntry[0].peBlue  = ms_StdColors[0].peBlue;
        pi.palPalEntry[0].peFlags = 0;
        pi.palPalEntry[1].peRed   = ms_StdColors[255].peRed;
        pi.palPalEntry[1].peGreen = ms_StdColors[255].peGreen;
        pi.palPalEntry[1].peBlue  = ms_StdColors[255].peBlue;
        pi.palPalEntry[1].peFlags = 0;
   }
   else if(iNumColors == 16)
   {
	   int i;

        // According to the MS article "The Palette Manager: How and Why"
        // 4-bit palettes not really needed (will use VGA palette)
       for(i=0; i<8; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[i].peRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[i].peGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[i].peBlue;
           pi.palPalEntry[i].peFlags = 0;
       }

       for(i=8; i<16; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[248 + i].peRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[248 + i].peGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[248 + i].peBlue;
           pi.palPalEntry[i].peFlags = 0;
       }
   }
   else // if(iNumColors == 256)
   {
       // Fill palette with full halftone palette
       for(int i=0; i<256; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[i].peRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[i].peGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[i].peBlue;
           pi.palPalEntry[i].peFlags = 0;
       }
   }

   return CreatePalette(&pi);
#endif // USE_HALFTONE_1
}
#endif // DIBSECTION_NO_PALETTE

/////////////////////////////////////////////////////////////////////////////
// CDIBSection

CDIBSection::CDIBSection()
{
#ifdef USE_HALFTONE_1
    // Just in case...
    ASSERT(sizeof(ms_StdColors) / sizeof(ms_StdColors[0]) == 256);
#endif // USE_HALFTONE_1

    m_hBitmap = NULL;
#ifndef DIBSECTION_NO_PALETTE
    m_hPalette = NULL;
#endif // DIBSECTION_NO_PALETTE

#ifdef _WIN32_WCE
	m_hdcMem = NULL;
	m_hbmpOld = NULL;
#ifndef DIBSECTION_NO_MEMDC_REUSE
	m_bReuseMemoryDC = FALSE;
#endif // DIBSECTION_NO_MEMDC_REUSE
#ifndef DIBSECTION_NO_PALETTE
    m_hpalOld = NULL;
#endif // DIBSECTION_NO_PALETTE
#endif // _WIN32_WCE

    CleanUp(); // This will initialise to a known state - ie. empty
}

CDIBSection::~CDIBSection()
{
    CleanUp();
}

// Resets the object to an empty state, and frees all memory used.
void CDIBSection::CleanUp()
{
#ifndef DIBSECTION_NO_PALETTE
    if(m_hPalette != NULL)
    {
        DeleteObject(m_hPalette);
        m_hPalette = NULL;
    }
#endif // DIBSECTION_NO_PALETTE

    if(m_hBitmap != NULL)
    {
        DeleteObject(m_hBitmap);
        m_hBitmap = NULL;
    }

    m_ppvBits = NULL;

    ZeroMemory(&m_DIBinfo, sizeof(m_DIBinfo));

    m_uColorDataType = DIB_RGB_COLORS;
    m_uColorTableSize = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSection operations

// Draws the image 1:1 on the device context
BOOL CDIBSection::Draw(HDC hdc, const POINT& ptDest, BOOL bForceBackground)
{ 
    if(m_hBitmap == NULL)
        return FALSE;

    SIZE size;
    GetSize(size);
    POINT ptSrcOrigin = { 0, 0 };

    BOOL bResult = FALSE;

#ifdef _WIN32_WCE
	// Create a memory DC compatible with the destination DC
	HDC hdcMem = GetMemoryDC(hdc, FALSE);
	if(!hdcMem)
		return FALSE;
#endif // _WIN32_WCE

#ifndef DIBSECTION_NO_PALETTE
    HPALETTE hpalOld = NULL;
    if(m_hPalette != NULL && IsPaletteEnabled(hdc))
    {
        hpalOld = SelectPalette(hdc, m_hPalette, bForceBackground);
        RealizePalette(hdc);
    }
#endif // DIBSECTION_NO_PALETTE

#ifdef _WIN32_WCE
	bResult = BitBlt(hdc, ptDest.x, ptDest.y, size.cx, size.cy, hdcMem, 
						  ptSrcOrigin.x, ptSrcOrigin.y, SRCCOPY);
#else
    bResult = SetDIBitsToDevice(hdc, 
                                ptDest.x, ptDest.y, 
                                size.cx, size.cy,
                                ptSrcOrigin.x, ptSrcOrigin.y,
                                ptSrcOrigin.y, size.cy - ptSrcOrigin.y, 
                                GetDIBits(), GetBitmapInfo(), 
                                DIB_RGB_COLORS); 
#endif // _WIN32_WCE

#ifndef DIBSECTION_NO_PALETTE
    if(hpalOld != NULL)
        SelectPalette(hdc, hpalOld, FALSE);
#endif // DIBSECTION_NO_PALETTE

#ifdef _WIN32_WCE
    ReleaseMemoryDC();
#endif // _WIN32_WCE

    return bResult;
}

// Stretch draws the image to the desired size on the device context
BOOL CDIBSection::Stretch(HDC hdc, const POINT& ptDest, const SIZE& size, BOOL bForceBackground)
{
    if(m_hBitmap == NULL)
        return FALSE;

    SIZE size2;
    GetSize(size2);
    POINT ptSrcOrigin = { 0, 0 };

    BOOL bResult = FALSE;

#ifdef _WIN32_WCE
	// Create a memory DC compatible with the destination DC
	HDC hdcMem = GetMemoryDC(hdc, FALSE);
	if(!hdcMem)
		return FALSE;
#endif // _WIN32_WCE

#ifndef DIBSECTION_NO_PALETTE
    HPALETTE hpalOld = NULL;
    if(m_hPalette != NULL && IsPaletteEnabled(hdc))
    {
        hpalOld = SelectPalette(hdc, m_hPalette, bForceBackground);
        RealizePalette(hdc);
    }
#endif // DIBSECTION_NO_PALETTE

#ifdef _WIN32_WCE
	bResult = StretchBlt(hdc, ptDest.x, ptDest.y, size.cx, size.cy, 
							  hdcMem, 
							  ptSrcOrigin.x, ptSrcOrigin.y, size2.cx, size2.cy, 
							  SRCCOPY);
#else // _WIN32_WCE
    SetStretchBltMode(hdc, COLORONCOLOR);

    bResult = StretchDIBits(hdc, 
                            ptDest.x, ptDest.y, 
                            size.cx, size.cy,
                            ptSrcOrigin.x, ptSrcOrigin.y,
                            size2.cx, size2.cy, 
                            GetDIBits(), GetBitmapInfo(), 
                            DIB_RGB_COLORS, SRCCOPY); 
#endif // _WIN32_WCE

#ifndef DIBSECTION_NO_PALETTE
    if(hpalOld != NULL)
        SelectPalette(hdc, hpalOld, FALSE);
#endif // DIBSECTION_NO_PALETTE

#ifdef _WIN32_WCE
    ReleaseMemoryDC();
#endif // _WIN32_WCE

    return bResult;
}

//////////////////////////////////////////////////////////////////////////////
// Create an empty bitmap

BOOL CDIBSection::CreateBitmap(int cx, int cy, int iBits)
{
    ASSERT(cx > 0);
    ASSERT(cy > 0);

#ifdef _WIN32_WCE
    ASSERT((iBits == 1)
        || (iBits == 2)
        || (iBits == 4) || (iBits == 8)
        || (iBits == 16) || (iBits == 24) || (iBits == 32));
#else
    ASSERT((iBits == 1)
        || (iBits == 4) || (iBits == 8)
        || (iBits == 16) || (iBits == 24) || (iBits == 32));
#endif // _WIN32_WCE

    CleanUp();

    // Initialize the bitmap info header
    ZeroMemory(&m_DIBinfo, sizeof(m_DIBinfo));
    BITMAPINFOHEADER& bmih = *(PBITMAPINFOHEADER)m_DIBinfo;

    // Populate bitmapinfo header
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = cx; // ((((int)cx * 8) + 31) & ~31) >> 3;
    bmih.biHeight = cy;
    bmih.biPlanes = 1;
    bmih.biBitCount = (WORD)iBits;
    bmih.biCompression = BI_RGB;
    bmih.biClrUsed = (iBits > 8) ? 0 : (1 << iBits);
    bmih.biSizeImage = BytesPerLine(cx, iBits) * cy;

    m_uColorTableSize = bmih.biClrUsed;

    /// TODO: fill color table here

    // Create the DIB section.
    m_hBitmap = CreateDIBSection(NULL, (PBITMAPINFO)&bmih, m_uColorDataType, (void**)&m_ppvBits, NULL, 0);

    ASSERT(m_hBitmap);
    ASSERT(m_ppvBits);

    return m_hBitmap != NULL;
}

//////////////////////////////////////////////////////////////////////////////
// Setting the bitmap

BOOL CDIBSection::SetBitmap(UINT uResId, HINSTANCE hInstance)
{   
    return SetBitmap(MAKEINTRESOURCE(uResId), hInstance);
}

BOOL CDIBSection::SetBitmap(LPCTSTR pszResName, HINSTANCE hInstance)
{
    if(hInstance == NULL)
        hInstance = GetModuleHandle(NULL);

    HBITMAP hBitmap = (HBITMAP)LoadImage(hInstance, pszResName, IMAGE_BITMAP, 0, 0,
#ifdef _WIN32_WCE
        0
#else // _WIN32_WCE
        LR_CREATEDIBSECTION
#endif // _WIN32_WCE
        );

    if(hBitmap == NULL)
        return FALSE;

    BOOL bResult = SetBitmap(hBitmap);
    DeleteObject(hBitmap);

    return bResult;
}

BOOL CDIBSection::SetBitmap(PBITMAPINFO pbi, PVOID pBits)
{
    CleanUp();

    if(pbi == NULL/* || pBits == NULL*/)
        return FALSE;

    BOOL bResult = FALSE;

    // Compute the number of colors in the color table
    m_uColorTableSize = NumColorEntries(pbi->bmiHeader.biBitCount, pbi->bmiHeader.biCompression,
        pbi->bmiHeader.biClrUsed);

    DWORD dwSize = sizeof(BITMAPINFO) + sizeof(RGBQUAD) * m_uColorTableSize;

    // Copy over BITMAPINFO contents
    CopyMemory(&m_DIBinfo, pbi, dwSize);

    // Should now have all the info we need to create the sucker.

    m_hBitmap = CreateDIBSection(NULL, (const PBITMAPINFO)m_DIBinfo, m_uColorDataType, (void**)&m_ppvBits, NULL, 0);

    if(m_hBitmap != NULL)
    {
        DWORD& dwImageSize = m_DIBinfo.bmiHeader.biSizeImage;
        if(dwImageSize == 0)
        {
            int nBytesPerLine = BytesPerLine(pbi->bmiHeader.biWidth, pbi->bmiHeader.biBitCount);
            dwImageSize = nBytesPerLine * pbi->bmiHeader.biHeight;
        }

#ifndef _WIN32_WCE
        // Flush the GDI batch queue 
        GdiFlush();
#endif // !_WIN32_WCE

        // Only copy bits if they were provided
        if(pBits != NULL)
            CopyMemory(m_ppvBits, pBits, dwImageSize);

#ifndef DIBSECTION_NO_PALETTE
        if(CreateSparePalette())
#endif // DIBSECTION_NO_PALETTE
            bResult = TRUE;
    }

    if(!bResult)
    {
        _ShowLastError();
        CleanUp();
    }

    return bResult;
}

// Initialises the bitmap from the HBITMAP supplied. If failure, then object is
// initialised back to an empty bitmap.
BOOL CDIBSection::SetBitmap(HBITMAP hBitmap
#ifndef DIBSECTION_NO_PALETTE
                            , HPALETTE hPalette
#endif // DIBSECTION_NO_PALETTE
                            )
{
    CleanUp();

    if(hBitmap == NULL)
        return FALSE;

    // Get dimensions of bitmap
    BITMAP bm;
    if(!GetObject(hBitmap, sizeof(bm), &bm))
        return FALSE;

    BOOL bResult = FALSE;
#ifndef DIBSECTION_NO_PALETTE
    HPALETTE hpalOld = NULL;
#endif // DIBSECTION_NO_PALETTE
    HDC hdcMem = NULL;
    HDC hdcCopy = NULL;
    BITMAPINFOHEADER& bih = m_DIBinfo.bmiHeader;

    if(bm.bmHeight < 0)
        bm.bmHeight = -bm.bmHeight;
   
    HDC hdc = GetWindowDC(NULL);
    if(hdc == NULL)
        goto exit;

    m_uColorTableSize = NumColorEntries(bm.bmBitsPixel, BI_RGB);

    // Initialize the BITMAPINFOHEADER in m_DIBinfo
    bih.biSize          = sizeof(BITMAPINFOHEADER);
    bih.biWidth         = bm.bmWidth;
    bih.biHeight        = bm.bmHeight;
    bih.biPlanes        = 1;                // Must always be 1 according to docs
    bih.biBitCount      = bm.bmBitsPixel;
#ifdef _WIN32_WCE
    // DCR 4/02/01  I've found PocketPCs need BI_BITFIELDS for 16 bit dibs.
    if(bm.bmBitsPixel == 16  || bm.bmBitsPixel == 32)
        bih.biCompression = BI_BITFIELDS; 
    else
        bih.biCompression = BI_RGB;
#else // _WIN32_WCE
    bih.biCompression   = BI_RGB;
#endif // _WIN32_WCE
    bih.biSizeImage     = BytesPerLine(bm.bmWidth, bm.bmBitsPixel) * bm.bmHeight;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed       = 0;
    bih.biClrImportant  = 0;

    DWORD dwColors = GetColorTableEntries(hdc, hBitmap);

	if(bm.bmBitsPixel == 16)
		bih.biClrUsed = dwColors;

    // If the driver did not fill in the biSizeImage field, then compute it
    // Each scan line of the image is aligned on a DWORD (32bit) boundary
    if(bih.biSizeImage == 0)
        bih.biSizeImage = BytesPerLine(bih.biWidth, bih.biBitCount) * bih.biHeight;

#ifndef DIBSECTION_NO_PALETTE
    if(hPalette != NULL)
        SetPalette(hPalette);

    if(m_hPalette != NULL)
    {
        hpalOld = SelectPalette(hdc, m_hPalette, FALSE);
        RealizePalette(hdc);
    }
#endif // DIBSECTION_NO_PALETTE

    // Create it
    m_hBitmap = CreateDIBSection(hdc, (const PBITMAPINFO)m_DIBinfo, m_uColorDataType, (void**)&m_ppvBits, NULL, 0);

#ifndef DIBSECTION_NO_PALETTE
    if(hpalOld != NULL)
    {
        SelectPalette(hdc, hpalOld, FALSE);
        hpalOld = NULL;
    }
#endif // DIBSECTION_NO_PALETTE

    if(m_hBitmap == NULL)
        goto cleanup;

#ifndef DIBSECTION_NO_PALETTE
    // If palette was supplied then create a palette using the entries in the DIB
    // color table.
    if(hPalette == NULL)
        CreateSparePalette();
#endif // DIBSECTION_NO_PALETTE

    // Need to copy the supplied bitmap onto the newly created DIBsection
    hdcMem = CreateCompatibleDC(hdc);
    hdcCopy = CreateCompatibleDC(hdc);
    if(hdcMem == NULL || hdcCopy == NULL) 
        goto cleanup;

#ifndef DIBSECTION_NO_PALETTE
    if(m_hPalette != NULL)
    {
        SelectPalette(hdcMem, m_hPalette, FALSE);
        RealizePalette(hdcMem);

        SelectPalette(hdcCopy, m_hPalette, FALSE);
        RealizePalette(hdcCopy);
    }
#endif // DIBSECTION_NO_PALETTE

#ifndef _WIN32_WCE
    GdiFlush();
#endif // !_WIN32_WCE

    {
    HGDIOBJ hbmpOldMem = SelectObject(hdcMem, hBitmap);
    HGDIOBJ hbmpOldCopy = SelectObject(hdcCopy, m_hBitmap);

    BitBlt(hdcCopy, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0,0, SRCCOPY);

    SelectObject(hdcMem, hbmpOldMem);
    SelectObject(hdcCopy, hbmpOldCopy);
    }

#ifndef DIBSECTION_NO_PALETTE
    if(m_hPalette != NULL)
    {
        SelectObject(hdcMem, GetStockObject(DEFAULT_PALETTE));
        SelectObject(hdcCopy, GetStockObject(DEFAULT_PALETTE));
    }
#endif // DIBSECTION_NO_PALETTE

    bResult = TRUE;

cleanup:
    if(!bResult)
    {
        _ShowLastError();
        CleanUp();
    }

    if(hdcMem != NULL)
        DeleteDC(hdcMem);

    if(hdcCopy != NULL)
        DeleteDC(hdcCopy);

    if(hdc != NULL)
        ReleaseDC(NULL, hdc);

exit:
    return bResult;
}

#ifdef PERSISTANCE_SUPPORT
//////////////////////////////////////////////////////////////////////////////
// Persistance...

// Loads the bitmap from a bitmap file with the name lpszFileName. If failure,
// then object is initialised back to an empty bitmap.
BOOL CDIBSection::Load(LPCTSTR pszFileName)
{
    CFile file;
    if(!file.Open(pszFileName, CFile::modeRead))
        return FALSE;

    // Get the current file position.  
    DWORD dwFileStart = file.GetPosition();

    // The first part of the file contains the file header.
    // This will tell us if it is a bitmap, how big the header is, and how big 
    // the file is. The header size in the file header includes the color table.
    BITMAPFILEHEADER BmpFileHdr;
    int iBytes = file.Read(&BmpFileHdr, sizeof(BmpFileHdr));
    if(iBytes != sizeof(BmpFileHdr)) 
    {
        TRACE("Failed to read file header\n");
        return FALSE;
    }

    // Check that we have the magic 'BM' at the start.
    if(BmpFileHdr.bfType != DS_BITMAP_FILEMARKER)
    {
        TRACE("Not a bitmap file\n");
        return FALSE;
    }

    // Read the header (assuming it's a DIB). 
    DIBINFO BmpInfo;
    iBytes = file.Read(&BmpInfo, sizeof(BITMAPINFOHEADER)); 
    if(iBytes != sizeof(BITMAPINFOHEADER)) 
    {
        TRACE("Failed to read BITMAPINFOHEADER\n");
        return FALSE;
    }

    // Check that we have a real Windows DIB file.
    if(BmpInfo.bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
    {
        TRACE("File is not a Windows DIB\n");
        return FALSE;
    }

    // See how big the color table is in the file (if there is one).  
    int iColors = NumColorEntries(BmpInfo.bmiHeader.biBitCount, BmpInfo.bmiHeader.biCompression, BmpInfo.bmiHeader.biClrUsed);
    if(iColors > 0) 
    {
        // Read the color table from the file.
        int iColorTableSize = sizeof(RGBQUAD) * iColors;
        iBytes = file.Read(BmpInfo.GetColorTable(), iColorTableSize);
        if(iBytes != iColorTableSize) 
        {
            TRACE("Failed to read color table\n");
            return FALSE;
        }
    }

    // So how big the bitmap surface is.
    int iBitsSize = BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;

    // Double check that the bitmap surface if ok (sometimes the file size is a
    // little larger than the bitmap itself, which may cause overflows)
    int iSurfaceSize = BytesPerLine(BmpInfo.bmiHeader.biWidth, 
                                    BmpInfo.bmiHeader.biBitCount) *    BmpInfo.bmiHeader.biHeight;
    if(iSurfaceSize < iBitsSize)
    {
        // In this case we don't need the entire file
        iBitsSize = iSurfaceSize;
    }

    // Allocate the memory for the bits and read the bits from the file.
    PBYTE pBits = (PBYTE)malloc(iBitsSize);
    if(pBits == NULL)
    {
        TRACE("Out of memory for DIB bits\n");
        return FALSE;
    }

    // Seek to the bits in the file.
    file.Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    iBytes = file.Read(pBits, iBitsSize);
    if(iBytes != iBitsSize)
    {
        TRACE("Failed to read bits\n");
        free(pBits);
        return FALSE;
    }

    // Everything went OK.
    BmpInfo.bmiHeader.biSizeImage = iBitsSize;

    if(!SetBitmap((PBITMAPINFO)BmpInfo, pBits))
    {
        TRACE("Failed to set bitmap info\n");
        free(pBits);
        return FALSE;
    }

    free(pBits);

    return TRUE;
}

// Saves the image to file.
BOOL CDIBSection::Save(LPCTSTR pszFileName)
{
    BITMAPFILEHEADER hdr;
    PBITMAPINFOHEADER pbi = GetBitmapInfoHeader();

    if(pbi == NULL || pszFileName == NULL)
        return FALSE;

    CFile file;
    if(!file.Open(pszFileName, CFile::modeWrite | CFile::modeCreate))
        return FALSE;

    DWORD dwBitmapInfoSize = sizeof(BITMAPINFO) + sizeof(RGBQUAD) * (m_uColorTableSize - 1);
    DWORD dwFileHeaderSize = dwBitmapInfoSize + sizeof(hdr);

    // Fill in the fields of the file header 
    hdr.bfType      = DS_BITMAP_FILEMARKER;
    hdr.bfSize      = dwFileHeaderSize + pbi->biSizeImage;
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;
    hdr.bfOffBits   = dwFileHeaderSize;

    // Write the file header 
    file.Write(&hdr, sizeof(hdr));

    // Write the DIB header
    file.Write(pbi, dwBitmapInfoSize);

    // Write DIB bits
    file.Write(GetDIBits(), pbi->biSizeImage);

    return TRUE;
}
#endif // PERSISTANCE_SUPPORT

// Creates a copy of another CDIBSection object
BOOL CDIBSection::Copy(CDIBSection& ds) 
{ 
    BOOL bResult = SetBitmap(ds.GetBitmapInfo(), ds.GetDIBits()); 
    if(bResult)
    {
        SetColorTable(ds.GetColorTableSize(), ds.GetColorTable());
#ifndef DIBSECTION_NO_PALETTE
        CreateSparePalette();
#endif // DIBSECTION_NO_PALETTE
    }

    return bResult;
} 

/////////////////////////////////////////////////////////////////////////////
// CDIBSection palette stuff

BOOL CDIBSection::SetColorTable(UINT uNumColors, LPRGBQUAD pColors)
{
    if(m_hBitmap == NULL || m_uColorTableSize == 0
        || pColors == NULL || uNumColors == 0 || uNumColors > 256)
        return FALSE;

    BOOL bResult = FALSE;

#ifdef _WIN32_WCE
    LPRGBQUAD pColorTable = GetColorTable();
    ASSERT(pColorTable);

    if(pColorTable)
    {
        UINT uCount = min(m_uColorTableSize, uNumColors);
        ZeroMemory(pColorTable, sizeof(RGBQUAD) * m_uColorTableSize);
        CopyMemory(pColorTable, pColors, sizeof(RGBQUAD) * uCount);

        bResult = TRUE;
    }
#else // _WIN32_WCE
    // Create a memory DC compatible with the screen
    HDC hdcMem = CreateCompatibleDC(NULL);
    if(hdcMem != NULL)
    {
        HGDIOBJ hbmpOld = SelectObject(hdcMem, m_hBitmap);
        if(hbmpOld)
        {
            SetDIBColorTable(hdcMem, 0, uNumColors, pColors);
            bResult = TRUE;

            // Clean up
            SelectObject(hdcMem, hbmpOld);
        }

        DeleteDC(hdcMem);
    }
#endif // _WIN32_WCE

    return bResult;
}

#ifndef DIBSECTION_NO_PALETTE
// Creates the palette from the DIB section's color table. Assumes m_uColorTableSize
// has been set and the DIBsection m_hBitmap created
BOOL CDIBSection::CreateSparePalette()
{
    PALETTEINFO pi;

	if(m_hPalette != NULL)
    {
        DeleteObject(m_hPalette);
        m_hPalette = NULL;
    }

    if(m_hBitmap == NULL)
        return FALSE;

    BOOL bPalInfoReady = FALSE;
    HDC hdc = NULL;
    LPRGBQUAD pRGB = NULL;
    HDC hdcMem = NULL;

    // Create a 256 color halftone palette if there is no color table in the DIB section
    if(m_uColorTableSize == 0)
        goto exit;

    hdc = GetDC(NULL);
    if(hdc == NULL)
        return FALSE;

    // Get space for the color entries
    pRGB = new RGBQUAD[m_uColorTableSize];
    if(pRGB == NULL)
        goto cleanup;

    // Create a memory DC compatible with the current DC
    hdcMem = CreateCompatibleDC(hdc);
    if(hdcMem == NULL)
        goto cleanup;

    HGDIOBJ hbmpOld;
    hbmpOld = SelectObject(hdcMem, m_hBitmap);
    if(hbmpOld == NULL)
        goto cleanup;

    // Get the colors used. 
    UINT uColors;
    uColors = GetDIBColorTable(hdcMem, 0, m_uColorTableSize, pRGB);

    // Clean up
    SelectObject(hdc, hbmpOld);

    if(uColors == 0)   // No colors retrieved => the bitmap in the DC is not a DIB section
        goto cleanup;
    
    // Create and fill a LOGPALETTE structure with the colors used.
    pi.palNumEntries = (WORD)m_uColorTableSize;

    int i;
    for(i=0; i<(int)uColors; i++)
    {
        pi.palPalEntry[i].peRed   = pRGB[i].rgbRed;
        pi.palPalEntry[i].peGreen = pRGB[i].rgbGreen;
        pi.palPalEntry[i].peBlue  = pRGB[i].rgbBlue;
        pi.palPalEntry[i].peFlags = 0;
    }

    bPalInfoReady = TRUE;

cleanup:
    if(hdcMem != NULL)
        DeleteDC(hdcMem);

    if(pRGB != NULL)
        delete[] pRGB;

    if(hdc != NULL)
        ReleaseDC(NULL, hdc);

exit:
    // Create Palette
    if(bPalInfoReady)
        m_hPalette = CreatePalette(&pi);
    else
        m_hPalette = CreateHalftonePalette(m_uColorTableSize ? m_uColorTableSize : 256);

    return m_hPalette != NULL;
}

BOOL CDIBSection::SetPalette(HPALETTE hPalette)
{
    if(m_hPalette != NULL)
    {
        DeleteObject(m_hPalette);
        m_hPalette = NULL;
    }

    if(hPalette == NULL)
        return FALSE;

    WORD wEntries;
    GetObject(hPalette, sizeof(WORD), &wEntries);
    UINT uColors = (int)wEntries;
    if(uColors <= 0 || uColors > 256)
        return FALSE;

    // Get palette entries
    PALETTEINFO pi;
    pi.palNumEntries = (WORD)GetPaletteEntries(hPalette, 0, uColors, pi.palPalEntry);
                          
    /// TODO: If pi.palNumEntries < m_uColorTableSize, then fill in blanks with 0's

    return SetLogPalette(&pi);
}

BOOL CDIBSection::SetLogPalette(PLOGPALETTE pLogPalette)
{
    if(pLogPalette == NULL)
    {
        CreateSparePalette();
        return FALSE;
    }

    // Create new palette
    ASSERT(pLogPalette->palVersion == (WORD)0x300);

    UINT uColors = pLogPalette->palNumEntries;
    if(uColors > 0 && uColors <= 256)
    {
        if(m_hPalette != NULL)
            DeleteObject(m_hPalette);

        m_hPalette = CreatePalette(pLogPalette);
    }

    if(uColors <= 0 || uColors > 256 || m_hPalette == NULL)
    {
        CreateSparePalette();
        return FALSE;
    }

    if(m_uColorTableSize == 0)
        return TRUE;

    // Set the DIB colors
    RGBQUAD RGBquads[256]; 
    for(UINT i=0; i<uColors; i++)
    {
        RGBquads[i].rgbRed   = pLogPalette->palPalEntry[i].peRed;
        RGBquads[i].rgbGreen = pLogPalette->palPalEntry[i].peGreen;
        RGBquads[i].rgbBlue  = pLogPalette->palPalEntry[i].peBlue;
        RGBquads[i].rgbReserved = 0;
    }
    
    return FillDIBColorTable(uColors, RGBquads);
}

// Sets the colors used by the image. Only works if # colors <= 256
BOOL CDIBSection::FillDIBColorTable(UINT uNumColors, LPRGBQUAD pRGB)
{
    if(m_hBitmap == NULL || pRGB == NULL || uNumColors == 0 || uNumColors > 256 || m_uColorTableSize == 0)
        return FALSE;

    UINT uColors = 0;

#ifndef _WIN32_WCE
    // Create a memory DC compatible with the screen
    HDC hdcMem = CreateCompatibleDC(NULL);

    if(hdcMem == NULL)
        return FALSE;

    HGDIOBJ hbmpOld = SelectObject(hdcMem, m_hBitmap);

    // Set the bitmap colors.
    uColors = SetDIBColorTable(hdcMem, 0, uNumColors, pRGB);

    // Bug fixed. Update the m_DIBInfo too
    GetDIBColorTable(hdcMem, 0, m_uColorTableSize, m_DIBinfo.bmiColors);

    // Clean up
    if(hbmpOld != NULL)
        SelectObject(hdcMem, hbmpOld);

    DeleteDC(hdcMem);
#else // !_WIN32_WCE
    // get the number of colors to return per BITMAPINFOHEADER docs
    BITMAPINFOHEADER& bmih = *(PBITMAPINFOHEADER)m_DIBinfo;
    if(bmih.biClrUsed)
        uColors = bmih.biClrUsed;
    else
        uColors = 1 << (bmih.biBitCount * bmih.biPlanes);

    // Initialize the loop variables
    uColors = min(uNumColors, uColors);

    LPRGBQUAD pColorTable = m_DIBinfo.GetColorTable();
    for(UINT i=0; i<uColors; i++)
    {
        pColorTable[i].rgbRed      = pRGB[i].rgbRed;
        pColorTable[i].rgbGreen    = pRGB[i].rgbGreen;
        pColorTable[i].rgbBlue     = pRGB[i].rgbBlue;
        pColorTable[i].rgbReserved = 0;
    }
#endif // !_WIN32_WCE

    return uColors > 0;
}
#endif // DIBSECTION_NO_PALETTE

// --- In :  hdc     - the Device Context in which the DIBSection is selected
//           hBitmap - the bitmap whose solor entries are to be queried
//           lpbi    - a pointer to a BITMAPINFO structure that will have it's
//                     color table filled.
// --- Out :
// --- Returns : the number of colors placed in the color table
// --- Effect : This function is a replacement for GetDIBits, in that it retrieves 
//              (or synthesizes) the color table from the given bitmap, and stores 
//              the values in the BITMAPINFO structure supplied.
//
///////////////////////////////////////////////////////////////////////////////

UINT CDIBSection::GetColorTableEntries(HDC hdc, HBITMAP hBitmap)
{
    UINT nCount = 0;

#ifndef _WIN32_WCE
    // calls GetDIBits with NULL bits pointer to fill in the BITMAPINFOHEADER data
    if(::GetDIBits(hdc, hBitmap, 0, GetHeight(), NULL, m_DIBinfo, m_uColorDataType))
    {
        BITMAPINFOHEADER& bmih = *(PBITMAPINFOHEADER)m_DIBinfo;
        if(bmih.biClrUsed)
            nCount = bmih.biClrUsed;
        else
            nCount = 1 << (bmih.biBitCount * bmih.biPlanes);
    }
#else // !_WIN32_WCE
    if(!m_uColorTableSize)
        return 0;

    // Fill the color table with the colors from the bitmap's color table
    LPRGBQUAD pColorTable = GetColorTable();
    
#ifdef _WIN32_WCE
    // DCR 4/02/01  If you are dealing with a 16bpp bitmap in PocketPC, you must
    // set the 3 DWORD color mask. This mask will be applied to a 16bit value to find the 
    // RGB components.  Blue is lowest 5 bits, then Green, then Red.
    if(m_DIBinfo.bmiHeader.biBitCount == 16)
    {
        DWORD dw[3];
        dw[0] = 31744;  // RED bitmask   Bits: 0 11111 00000 00000
        dw[1] = 992;    // GREEN bitmask Bits: 0 00000 11111 00000
        dw[2] = 31;     // BLUE bitmask  Bits: 0 00000 00000 11111
        CopyMemory(pColorTable, dw, sizeof(DWORD) * 3);

        return 3;
    }
#endif // _WIN32_WCE

    // Get the color table from the HBITMAP and copy them over.
    LPRGBQUAD pRGB = new RGBQUAD[m_uColorTableSize];
    if(pRGB)
    {
        HGDIOBJ hbmpOld = SelectObject(hdc, hBitmap);
        nCount = GetDIBColorTable(hdc, 0, m_uColorTableSize, pRGB);
        SelectObject(hdc, hbmpOld);

        if(nCount)
            CopyMemory(pColorTable, pRGB, sizeof(RGBQUAD) * nCount);

        delete[] pRGB;
    }

    // Didn't work - so synthesize one.
    if(!nCount)
    {       
        nCount = min(m_uColorTableSize, sizeof(ms_StdColors) / sizeof(ms_StdColors[0]));
        CopyMemory(pColorTable, ms_StdColors, sizeof(RGBQUAD) * nCount);
    }
#endif // !_WIN32_WCE

    return nCount;
}

// Makes trace windows a little bit more informative...
void CDIBSection::_ShowLastError()
{
#ifdef _DEBUG
    PVOID pMessage;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,    
                  NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR)&pMessage, 0, NULL);
    TRACE("Last error: %s\n", pMessage);
    LocalFree(pMessage);
#endif
}

#ifdef _WIN32_WCE
///////////////////////////////////////////////////////////////////////////////
//
// This function is from the MS KB article "HOWTO: Get the Color Table of a
//  DIBSection in Windows CE".
// 
// PARAMETERS:
// HDC - the Device Context in which the DIBSection is selected
// UINT - the index of the first color table entry to retrieve
// UINT - the number of color table entries to retrieve
// LPRGBQUAD - a buffer large enough to hold the number of RGBQUAD entries requested
//
// RETURNS:
// UINT - the number of colors placed in the buffer
//
//
///////////////////////////////////////////////////////////////////////////////

UINT WINAPI GetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries, LPRGBQUAD pColors)
{   
    if(pColors == NULL)
        return 0;                       // No place to put them, fail

    // Get a description of the DIB Section
    HBITMAP hDIBSection = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);

    DIBSECTION ds;
    DWORD dwSize = GetObject(hDIBSection, sizeof(DIBSECTION), &ds);

    if(dwSize != sizeof(DIBSECTION))
        return 0;                      // Must not be a DIBSection, fail

    if(ds.dsBmih.biBitCount > 8)
        return 0;                      // Not Palettized, fail

    // get the number of colors to return per BITMAPINFOHEADER docs
    UINT cColors;
    if(ds.dsBmih.biClrUsed)
        cColors = ds.dsBmih.biClrUsed;
    else
        cColors = 1 << (ds.dsBmih.biBitCount * ds.dsBmih.biPlanes);

    // Create a mask for the palette index bits for 1, 2, 4, and 8 bpp
    WORD wIndexMask = (0xFF << (8 - ds.dsBmih.biBitCount)) & 0x00FF;

    // Get the pointer to the image bits
    PBYTE pBits = (PBYTE)ds.dsBm.bmBits;

    // Initialize the loop variables
    cColors = min(cColors, cEntries);
    BYTE OldPalIndex = *pBits;

    UINT TestPixelY;
    if(ds.dsBmih.biHeight > 0 )
        // If button up DIB, pBits points to last row
        TestPixelY = ds.dsBm.bmHeight - 1;
    else
        // If top down DIB, pBits points to first row
        TestPixelY = 0;

    for(UINT iColor=uStartIndex; iColor<cColors; iColor++)
    {
        COLORREF rgbColor;
        
        // Set the palette index for the test pixel,
        // modifying only the bits for one pixel
        *pBits = (iColor << (8 - ds.dsBmih.biBitCount)) | (*pBits & ~wIndexMask);
        
        // now get the resulting color
        rgbColor = GetPixel(hdc, 0, TestPixelY);
        
        pColors[iColor - uStartIndex].rgbReserved = 0;
        pColors[iColor - uStartIndex].rgbBlue = GetBValue(rgbColor);
        pColors[iColor - uStartIndex].rgbRed = GetRValue(rgbColor);
        pColors[iColor - uStartIndex].rgbGreen = GetGValue(rgbColor);
    }

    // Restore the test pixel
    *pBits = OldPalIndex;

    return cColors;
}
#endif // _WIN32_WCE

#ifdef _WIN32_WCE
// Creates a memory DC and selects in the current bitmap so it can be modified using
// the GDI functions. Only one memory DC can be created for a given CDIBSection
// object. If you have a memory DC but wish to recreate it as compatible with a
// different DC, then call ReleaseMemoryDC first.
// If the memory DC has already been created then it will be recycled.
// Note that if using this in an environment where the color depth of the screen may
// change, then you will need to set "m_bReuseMemDC" to FALSE
HDC CDIBSection::GetMemoryDC(HDC hdc, BOOL bSelectPalette)
{
#ifdef DIBSECTION_NO_MEMDC_REUSE
    ReleaseMemoryDC(TRUE);
#else
    if(!m_bReuseMemoryDC)
        ReleaseMemoryDC(TRUE);
    else if(m_hdcMem)   // Already created?
    {
#ifndef _WIN32_WCE
        // Flush the GDI batch queue 
        GdiFlush();
#endif
        return m_hdcMem;
    }
#endif // DIBSECTION_NO_MEMDC_REUSE

    // Create a memory DC compatible with the given DC
    m_hdcMem = ::CreateCompatibleDC(hdc);
    if(m_hdcMem == NULL)
        return NULL;

    // Select in the bitmap
    m_hbmpOld = ::SelectObject(m_hdcMem, m_hBitmap);

#ifndef DIBSECTION_NO_PALETTE
    // Select in the palette
    if(bSelectPalette && IsPaletteEnabled(m_hdcMem))
    {
        // Palette should already have been created - but just in case...
        if(m_hPalette == NULL)
            CreateSparePalette();

        m_hpalOld = SelectPalette(m_hdcMem, m_hPalette, FALSE);
        RealizePalette(m_hdcMem);
    }
    else
        m_hpalOld = NULL;
#endif // DIBSECTION_NO_PALETTE

#ifndef _WIN32_WCE
    // Flush the GDI batch queue 
    GdiFlush();
#endif // _WIN32_WCE

    return m_hdcMem;
}

// Selects out the current bitmap and deletes the mem dc. If bForceRelease is FALSE,
// then the DC release will not actually occur. This is provided so you can have
//
//   GetMemoryDC(...)
//   ... do something
//   ReleaseMemoryDC()
//
// bracketed calls. If m_bReuseMemDC is subsequently set to FALSE, then the same code
// fragment will still work.
BOOL CDIBSection::ReleaseMemoryDC(BOOL bForceRelease /*=FALSE*/)
{
    if(m_hdcMem == NULL
#ifndef DIBSECTION_NO_MEMDC_REUSE
        || (m_bReuseMemoryDC && !bForceRelease) 
#endif // DIBSECTION_NO_MEMDC_REUSE
        )
        return TRUE; // Nothing to do

#ifndef _WIN32_WCE
    // Flush the GDI batch queue 
    GdiFlush();
#endif // _WIN32_WCE

    // Select out the current bitmap
    if(m_hbmpOld)
	{
        ::SelectObject(m_hdcMem, m_hbmpOld);
        m_hbmpOld = NULL;
	}

#ifndef DIBSECTION_NO_PALETTE
    // Select out the current palette
    if(m_hpalOld)
    {
        ::SelectPalette(m_hdcMem, m_hpalOld, FALSE);
        m_hpalOld = NULL;
    }
#endif // DIBSECTION_NO_PALETTE

    // Delete the memory DC
    BOOL bRet = ::DeleteDC(m_hdcMem);
    m_hdcMem = NULL;

    return bRet;
}
#endif // _WIN32_WCE
