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

	//HBITMAP hBitmap_;
	//HBITMAP hOldBitmap_;
	//HDC dc_;
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


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.4  2006/03/12 22:42:08  ddiego
*more doc updates - specific to graphicskit.
*
*Revision 1.3.4.3  2006/02/14 20:19:25  ddiego
*some minor bugs
*
*Revision 1.3.4.2  2005/10/17 01:36:34  ddiego
*some more under the hood image stuff. updated agg.
*
*Revision 1.3.4.1  2005/10/11 00:54:52  ddiego
*added initial changes for grayscale image support. fixed some minor changes to form loading and creating.
*
*Revision 1.3  2004/12/01 04:31:45  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/21 00:19:11  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.11.6.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.3  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.10.2.2  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.10.2.1  2003/05/25 19:07:11  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.10  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.22.1  2003/03/12 03:11:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32IMAGE_H__


