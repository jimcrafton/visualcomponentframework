#ifndef _VCF_WIN32IMAGE_H__
#define _VCF_WIN32IMAGE_H__
//Win32Image.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


class HBitmapData {
public:
	HBitmapData(): dc_(NULL), hbmp_(NULL), hOldBitmap_(NULL), data_(NULL) {
		dc_ = CreateCompatibleDC( NULL );
	}

	HBitmapData( HDC dc ): dc_(NULL), hbmp_(NULL), hOldBitmap_(NULL), data_(NULL) {
		dc_ = CreateCompatibleDC( dc );
	}

	~HBitmapData(){
		if ( NULL != hbmp_ ) {
			::SelectObject( dc_, hOldBitmap_ );
			::DeleteObject( hbmp_ );
		}
		if ( NULL != dc_ ) {
			DeleteDC( dc_ );
		}
	}


	void attach( HDC dc ) {
		if ( NULL != dc_ ) {
			DeleteDC( dc_ );
		}

		dc_ = dc;
		hOldBitmap_ = (HBITMAP)::SelectObject( dc_, hbmp_ );
	}

	HDC detach(){
		HDC result = dc_;
		dc_ = NULL;
		return result;
	}

	HDC dc() {
		return dc_;
	}

	operator HBITMAP() {
		return hbmp_;
	}
	
	void* data() {
		return data_;
	}

	HBITMAP oldBMP() {
		return hOldBitmap_;
	}
protected:

	HDC dc_;
	HBITMAP hbmp_;
	HBITMAP hOldBitmap_;
	void* data_;
};

/**
Win32 utility class 
*/
class HBitmap32Bit : public HBitmapData {
public:
	
	void setSize( size_t width, size_t height ) {
		if ( hbmp_ ) {
			::SelectObject( dc_, hOldBitmap_ );
			DeleteObject( hbmp_ );
		}		

		hbmp_ = NULL;

		BITMAPINFO bmpInfo;		

		memset( &bmpInfo, 0, sizeof (BITMAPINFOHEADER) );
		bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth = width;
		bmpInfo.bmiHeader.biHeight = -height;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biCompression = BI_RGB;
		bmpInfo.bmiHeader.biSizeImage = height * width * 4;

		hbmp_ = CreateDIBSection ( dc_, &bmpInfo, DIB_RGB_COLORS, (void **)&data_, NULL, NULL );

		if ( hbmp_ ) {
			hOldBitmap_ = (HBITMAP)::SelectObject( dc_, hbmp_ );
		}
	}	
};

class HBitmapGrayScale : public HBitmapData {
public:
	

	void setSize( size_t width, size_t height ) {
		if ( hbmp_ ) {
			::SelectObject( dc_, hOldBitmap_ );
			::DeleteObject( hbmp_ );
		}		

		hbmp_ = NULL;
		
		char* bmpStruct = new char[ sizeof(BITMAPINFO) + (sizeof(RGBQUAD) * 256) ];
		
		BITMAPINFO * bmpInfo = (BITMAPINFO*)bmpStruct;
		memset( bmpStruct, 0, sizeof (BITMAPINFO) + (sizeof(RGBQUAD) * 256) );
		
		hbmp_ = NULL;
		
		bmpInfo->bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
		bmpInfo->bmiHeader.biWidth = width;
		
		bmpInfo->bmiHeader.biHeight = -height; // Win32 DIB are upside down - do this to filp it over
		bmpInfo->bmiHeader.biPlanes = 1;
		bmpInfo->bmiHeader.biBitCount = 8;
		bmpInfo->bmiHeader.biCompression = BI_RGB;
		bmpInfo->bmiHeader.biSizeImage = height * width;
		
		RGBQUAD* colors = &bmpInfo->bmiColors[0];
		
		for ( int i=0;i<256;i++ ) {
			colors->rgbBlue = i;
			colors->rgbGreen = i;
			colors->rgbRed = i;
			colors->rgbReserved = 0;
			
			colors ++;
		}
		
		hbmp_ = ::CreateDIBSection ( dc_, bmpInfo, DIB_PAL_COLORS, (void **)&data_, NULL, NULL );
		
		
		
		if ( (NULL != hbmp_) ) {
			
			hOldBitmap_ = (HBITMAP)::SelectObject( dc_, data_ );
			
			colors = &bmpInfo->bmiColors[0];
			
			::SetDIBColorTable( dc_, 0, 256, colors );
		}
		
		delete [] bmpStruct;
	}

	
};

namespace VCF
{

class GRAPHICSKIT_API Win32Image : public AbstractImage
{
public:
	Win32Image();

	Win32Image( const String& fileName );

	Win32Image( const unsigned long& width, const unsigned long& height );

	Win32Image( GraphicsContext* context, Rect* rect );


	Win32Image( HBITMAP bitmap );

	Win32Image( HICON icon );
	

	virtual ~Win32Image();

	void init();

	virtual void setSize( const unsigned long & width, const unsigned long & height );

	void createBMP();

	virtual void beginDrawing();

	virtual void finishedDrawing();

	HBITMAP getBitmap();

	HDC getDC();

	BITMAPINFO bmpInfo_;
	HPALETTE palette_;//for 256 or fewer color images

	HICON convertToIcon();

	void internal_saveToFile( const String& fileName );

protected:
	void loadFromFile( const String& fileName );

	void loadFromBMPHandle( HBITMAP bitmap );

	HBitmap32Bit hbmp_;
	bool flipBits_;
	bool ownDC_;
};

/**
\class BMPLoader Win32Image.h "vcf/GraphicsKit/Win32Image.h"
*/
class GRAPHICSKIT_API BMPLoader : public Object, public ImageLoader {
public:
	BMPLoader();

	virtual ~BMPLoader();

	virtual Image* loadImageFromFile( const String& fileName );


	virtual void saveImageToFile( const String& fileName, Image* image );

	virtual bool canSaveImage(){
		return true;
	}
private:

};

};


#endif // _VCF_WIN32IMAGE_H__

/**
$Id$
*/
