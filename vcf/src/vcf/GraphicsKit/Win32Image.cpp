//Win32Image.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;

Win32Image::Win32Image()
{
	flipBits_ = false;
	ownDC_ = true;
	init();
}

Win32Image::Win32Image( const unsigned long& width, const unsigned long& height ):
	AbstractImage(false)
{
	flipBits_ = false;
	ownDC_ = true;
	init();

	setSize( width, height );
}

Win32Image::Win32Image( const String& fileName ):
	AbstractImage(false)
{
	flipBits_ = true;
	ownDC_ = true;
	init();
	loadFromFile( fileName );
}

Win32Image::Win32Image( GraphicsContext* context, Rect* rect  ):
	AbstractImage(false)
{
	flipBits_ = false;
	ownDC_ = false; //leave it this way to begin with and then
	//switch to false for the duration after the intial
	//bitmap has been created
	if ( (NULL != context) && (NULL != rect) ){
		Win32Context* ctx = reinterpret_cast<Win32Context*>(context->getPeer() );
		if ( NULL != ctx ){
			//set up the bitmap data
			IMTRAITS::setChannelType( flags_, IMTRAITS::getTraitsChannelType() );
			IMTRAITS::setChannelSize( flags_, IMTRAITS::getTraitsChannelSize() );
			IMTRAITS::setImageType( flags_, IMTRAITS::getTraitsImageType() );
			IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

			hBitmap_ = NULL;

			palette_ = NULL;

			dc_ = (HDC)ctx->getContextID();

			//the deletion of the context_ should delete the
			//dc_ handle
			context_ = context;

			HDC tmpDC = CreateCompatibleDC( dc_ );
			HDC origDC = dc_;
			dc_ = tmpDC;

			setSize( rect->getWidth(), rect->getHeight() );

			dc_ = origDC;

			int r = BitBlt( tmpDC, 0, 0, getWidth(), getHeight(), dc_, (int)rect->left_, (int)rect->top_, SRCCOPY );

			::SelectObject( tmpDC, hOldBitmap_ );
			DeleteDC( tmpDC );

			hOldBitmap_ = (HBITMAP)::SelectObject( dc_, hBitmap_ );
			//ownDC_ = false;
		}
		else {
			//throw exception !!!
			throw InvalidPointerException( MAKE_ERROR_MSG_2("Incorrect peer class (isn't a Win32Context) for passed GraphicsContext instance" ) );
		}
	}
	else {
		//throw exception !!!
		throw InvalidPointerException( MAKE_ERROR_MSG_2("Graphics Context passed in to Win32Image is NULL" ) );
	}
}


Win32Image::Win32Image( HBITMAP bitmap )
	:AbstractImage(false)
{
	flipBits_ = true;
	ownDC_ = true;
	init();

	if ( NULL == bitmap ) {
		throw InvalidPointerException(MAKE_ERROR_MSG_2("NULL HBITMAP passed into Win32Image constructor"));
	}
	loadFromBMPHandle( bitmap );
}

Win32Image::Win32Image( HICON icon )
	:AbstractImage(false)
{
	flipBits_ = true;
	ownDC_ = true;
	init();

	ICONINFO info = {0};
	if ( GetIconInfo( icon, &info ) ) {
		BITMAP bmp;
		if ( GetObject( info.hbmColor, sizeof(BITMAP), &bmp ) ) {
		
			setSize( bmp.bmWidth, bmp.bmHeight );

			if ( !DrawIcon( dc_, 0, 0, icon ) ) {
				StringUtils::traceWithArgs( Format("DrawIcon failed, err: %d\n") % GetLastError()  );
			}
		}
	}
}

Win32Image::~Win32Image()
{
	if ( NULL != hBitmap_ ){
		SelectObject( dc_, hOldBitmap_ );
		int err = DeleteObject( hBitmap_ );
	}

	//the base class AbstractImage will take care of
	//deleting hte GraphicsContext. If we don't
	//own the DC then set the context_ to null
	//to prevent from deleting it
	if ( ownDC_ ) {
		DeleteDC( dc_ );
	}
	else {
		context_ = NULL;
	}
	imageBits_->pixels_ = NULL;
}

void Win32Image::init()
{
	//NOTE: init() is not called if ownDC_ is true - the constructor takes care of this
	IMTRAITS::setChannelType( flags_, IMTRAITS::getTraitsChannelType() );
	IMTRAITS::setChannelSize( flags_, IMTRAITS::getTraitsChannelSize() );
	IMTRAITS::setImageType( flags_, IMTRAITS::getTraitsImageType() );
	IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

	hBitmap_ = NULL;

	palette_ = NULL;

	dc_ = ::CreateCompatibleDC( NULL );

	//the deletion of the context_ should delete the
	//dc_ handle
	context_ = new GraphicsContext( (OSHandleID)dc_ );
}

void Win32Image::setSize( const unsigned long & width, const unsigned long & height )
{
	if ( (!ownDC_) && (NULL != hBitmap_) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}
	AbstractImage::setSize( width, height );
	createBMP();
}


void Win32Image::createBMP()
{
	if ( (!ownDC_) && (NULL != hBitmap_) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}

	if ( NULL != hBitmap_ ) {
		::SelectObject( dc_, hOldBitmap_ );
		int err = DeleteObject( hBitmap_ );
	}

	hBitmap_ = NULL;
	memset( &bmpInfo_, 0, sizeof (BITMAPINFOHEADER) );
	bmpInfo_.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	bmpInfo_.bmiHeader.biWidth = getWidth();
	if ( true == flipBits_ ) {
		bmpInfo_.bmiHeader.biHeight = -getHeight(); // Win32 DIB are upside down - do this to filp it over
	}
	else {
		//this needs to be fixed
		//I put this back for now JEC-12-10-2001
		bmpInfo_.bmiHeader.biHeight = -getHeight(); // this is WRONG, cause there are times when we don't
													 // want it this way, but it will have to do for now :(
	}
	bmpInfo_.bmiHeader.biPlanes = 1;
	bmpInfo_.bmiHeader.biBitCount = 32;
	bmpInfo_.bmiHeader.biCompression = BI_RGB;
	bmpInfo_.bmiHeader.biSizeImage = abs(bmpInfo_.bmiHeader.biHeight) * bmpInfo_.bmiHeader.biWidth * 4;
	imageBits_->pixels_ = NULL;

	hBitmap_ = CreateDIBSection ( dc_, &bmpInfo_, DIB_RGB_COLORS, (void **)&imageBits_->pixels_, NULL, NULL );

	if ( (NULL != hBitmap_) ) {
		SysPixelType* pix = imageBits_->pixels_;
		int sz = bmpInfo_.bmiHeader.biWidth * abs(bmpInfo_.bmiHeader.biHeight);
		do {
			sz --;
			pix[sz].a = 255;
		} while( sz > 0 );


		hOldBitmap_ = (HBITMAP)::SelectObject( dc_, hBitmap_ );
		//::DeleteObject( oldObj );//clear out the old object
	}
}

HBITMAP Win32Image::getBitmap()
{
	return hBitmap_;
}

HDC Win32Image::getDC()
{
	return dc_;
}

void Win32Image::loadFromFile( const String& fileName )
{
	flipBits_ = true;

	HBITMAP hBMP = NULL;
	if ( System::isUnicodeEnabled() ) {
		hBMP = (HBITMAP)LoadImageW( NULL, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	}
	else {
		hBMP = (HBITMAP)LoadImageA( NULL, fileName.ansi_c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	}

	if ( NULL == hBMP ) {
		throw ImageLoaderException(MAKE_ERROR_MSG_2("Image file unreadable - this may be due to an incorrect file name"));
	}
	loadFromBMPHandle( hBMP );
}

void Win32Image::loadFromBMPHandle( HBITMAP bitmap )
{
	flipBits_ = true;

	//hBitmap_ = bitmap;
	BITMAP bmp = {0};
	GetObject( bitmap, sizeof(bmp), &bmp );

	setSize( bmp.bmWidth, bmp.bmHeight );

	HDC tmpBMPDC = CreateCompatibleDC( NULL );
	HBITMAP oldBitmap = (HBITMAP)::SelectObject(  tmpBMPDC, bitmap );

	BitBlt( dc_, 0, 0, bmp.bmWidth, bmp.bmHeight, tmpBMPDC, 0, 0, SRCCOPY );

	::SelectObject(  tmpBMPDC, oldBitmap );
	DeleteDC( tmpBMPDC );
	DeleteObject( bitmap );

	SysPixelType* pix = imageBits_->pixels_;
	int sz = bmpInfo_.bmiHeader.biWidth * abs(bmpInfo_.bmiHeader.biHeight);
	do {
		sz --;
		pix[sz].a = 255;
	} while( sz > 0 );
}

void Win32Image::internal_saveToFile( const String& fileName )
{
#ifdef VCF_CW
	FILE* f = fopen( fileName.ansi_c_str(), "w" );
#else
	FILE* f = _wfopen( fileName.c_str(), L"w" );
#endif

	bool bitFields = (bmpInfo_.bmiHeader.biBitCount == 16);

	// write the file header

	//store width for 24bit image NOT 32
	DWORD width = ((((24 * getWidth()) + 31) / 32) * 4);

	DWORD size = getHeight() * width;

	BITMAPFILEHEADER bitmapfileheader;
	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = bmpInfo_.bmiHeader.biSize + size + sizeof(BITMAPFILEHEADER);

	bitmapfileheader.bfOffBits = (DWORD) sizeof(bitmapfileheader) + bmpInfo_.bmiHeader.biSize;
		//sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		//0 * sizeof(RGBQUAD);

	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;

	if (bitFields) {
		bitmapfileheader.bfSize += 3 * sizeof(DWORD);
		bitmapfileheader.bfOffBits += 3 * sizeof(DWORD);
	}

	fwrite( &bitmapfileheader, sizeof(BITMAPFILEHEADER), 1, f );

	// write the info header

	BITMAPINFOHEADER bih = {0};
	memcpy( &bih, &bmpInfo_.bmiHeader, sizeof(bih) );
	bih.biSizeImage = size;
	bih.biBitCount = 24;
	bih.biHeight = abs(bih.biHeight);

	bih.biCompression = (bitFields) ? 3 : 0;

	fwrite( &bih, sizeof(BITMAPINFOHEADER), 1, f );

	// write the palette here, but we'll do nothing since we don't support palettes


	DWORD height = getHeight();
	SysPixelType* bits = getImageBits()->pixels_;
	unsigned char* row = new unsigned char[width];
	unsigned long imgWidth = getWidth();
	int xx = 0;

	// write the bitmap data

	unsigned char* tmpRow = row;
	for ( int y=height-1;y>=0;y-- ) {
		memset( row, 0, width * sizeof(unsigned char) );
		tmpRow = row;
		for (unsigned long x=0;x<imgWidth;x++ ) {
			if ( xx < width ) {
				SysPixelType& pix = bits[y*imgWidth + x];
				*tmpRow = pix.b;
				tmpRow++;
				*tmpRow = pix.g;
				tmpRow++;
				*tmpRow = pix.r;
				tmpRow++;
				xx += 3;
			}
		}
		fwrite( row, width, 1, f );
		xx = 0;
	}
	delete []row;


	fclose( f );
}


void Win32Image::beginDrawing()
{
	//no-op don't need to worry about this
}

void Win32Image::finishedDrawing()
{
	//no-op don't need to worry about this
}


HICON Win32Image::convertToIcon()
{
	HICON result = NULL;
	//this is justa big fat method from HELLLL

	OSVERSIONINFO osVersion = {0};
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);

	GetVersionEx( &osVersion );

	SysPixelType* bits = getImageBits()->pixels_;

	int alphaColorCount = 2;
	bool isWindowsXP = (osVersion.dwMajorVersion >=5) && (osVersion.dwMinorVersion >= 1);
	if ( isWindowsXP ) {
		alphaColorCount = 256;
	}


	char* monochromeInfoBuffer = new char[sizeof(BITMAPINFO) + (alphaColorCount * sizeof( RGBQUAD ))];
	BITMAPINFO* monochromeInfo = (BITMAPINFO*) monochromeInfoBuffer;

	monochromeInfo->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	monochromeInfo->bmiHeader.biWidth = getWidth();
	monochromeInfo->bmiHeader.biHeight = -(getHeight());
	monochromeInfo->bmiHeader.biPlanes = 1;
	
	monochromeInfo->bmiHeader.biBitCount = isWindowsXP ? 8 : 1;

	monochromeInfo->bmiHeader.biCompression = BI_RGB;
	monochromeInfo->bmiHeader.biSizeImage = 0;
	monochromeInfo->bmiHeader.biXPelsPerMeter = 0;
	monochromeInfo->bmiHeader.biYPelsPerMeter = 0;
	monochromeInfo->bmiHeader.biClrUsed = 0;
	monochromeInfo->bmiHeader.biClrImportant = 0;

	if ( isWindowsXP ) {
		for ( int i=0;i<alphaColorCount;i++ ) {
			monochromeInfo->bmiColors[i].rgbRed = i;
			monochromeInfo->bmiColors[i].rgbGreen = i;
			monochromeInfo->bmiColors[i].rgbBlue = i;
			monochromeInfo->bmiColors[i].rgbReserved = i;
		}
	}
	else {
		monochromeInfo->bmiColors[0].rgbRed = 0;
		monochromeInfo->bmiColors[0].rgbGreen = 0;
		monochromeInfo->bmiColors[0].rgbBlue = 0;
		monochromeInfo->bmiColors[0].rgbReserved = 0;
		monochromeInfo->bmiColors[1].rgbRed = 255;
		monochromeInfo->bmiColors[1].rgbGreen = 255;
		monochromeInfo->bmiColors[1].rgbBlue = 255;
		monochromeInfo->bmiColors[1].rgbReserved = 0;
	}

	
	

	unsigned char* ANDBits = NULL;
	SysPixelType* XORBits = NULL;

	HBITMAP hANDBitmap = CreateDIBSection ( dc_, monochromeInfo, DIB_RGB_COLORS,
		(void **)&ANDBits, NULL, NULL );

	BITMAPINFO info = {0};
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biHeight = -getHeight();
	info.bmiHeader.biWidth = getWidth();
	info.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage =
		info.bmiHeader.biWidth * abs(info.bmiHeader.biHeight) * 4;

	HBITMAP hXORBitmap = CreateDIBSection ( dc_, &info, DIB_RGB_COLORS,
		(void **)&XORBits, NULL, NULL );

	unsigned char andAlphaVal = isTransparent_ ? 255 : 0;
	unsigned char xorAlphaVal = 255;

	if ( isWindowsXP && isTransparent_ ) {
		xorAlphaVal = ~andAlphaVal;
	}

	if ( (NULL != hANDBitmap) && (NULL != hXORBitmap) ) {
		//white out
		int sz = info.bmiHeader.biWidth * abs(info.bmiHeader.biHeight);

		for ( int i=0;i<sz;i++){
			if ( isWindowsXP ) {
				ANDBits[i] = andAlphaVal;
			}
			else{
				if ( i < sz/8 ) {
					ANDBits[i] = andAlphaVal;
				}
			}

			

			XORBits[i].b = (unsigned char)0;
			XORBits[i].g = (unsigned char)0;
			XORBits[i].r = (unsigned char)0;
			XORBits[i].a = (unsigned char)xorAlphaVal;
		}

		SysPixelType maskColor = {(unsigned char)0,
			(unsigned char)255,
			(unsigned char)0,
			(unsigned char)255};


		maskColor.b = getTransparencyColor()->getBlue()*255;
		maskColor.r = getTransparencyColor()->getRed()*255;
		maskColor.g = getTransparencyColor()->getGreen()*255;

		int index = 0;
		int andIndex = 0;

		for ( int y=0;y<abs(info.bmiHeader.biHeight);y++){
			for ( int x=0;x<info.bmiHeader.biWidth;x++){
				index = y*info.bmiHeader.biWidth+x;
				if ( true == isTransparent_ ) {
					if ( (maskColor.b != bits[index].b) ||
						(maskColor.g != bits[index].g) ||
						(maskColor.r != bits[index].r) ) {
						long bitmaskIndex = 8 - index % 8 - 1;

						andIndex = isWindowsXP ? index : index/8;
						
						andAlphaVal = isWindowsXP ? 0 : (255 ^ (1 << bitmaskIndex));

						ANDBits[andIndex] = isWindowsXP ? 0 : (ANDBits[andIndex] & (255 ^ (1 << bitmaskIndex)));

						XORBits[index].b = bits[index].b;
						XORBits[index].g = bits[index].g;
						XORBits[index].r = bits[index].r;
					}
				}
				else {
					if ( isWindowsXP ) {
						ANDBits[index] = 255;
					}
					XORBits[index].b = bits[index].b;
					XORBits[index].g = bits[index].g;
					XORBits[index].r = bits[index].r;
				}
			}
		}

		ICONINFO icoInfo = {0};
		icoInfo.fIcon = TRUE;
		icoInfo.hbmColor = hXORBitmap;
		icoInfo.hbmMask = hANDBitmap;

		result = CreateIconIndirect( &icoInfo );

		DeleteObject( hXORBitmap );
		DeleteObject( hANDBitmap );
	}
	delete [] monochromeInfoBuffer;

	return result;
}

BMPLoader::BMPLoader()
{

}

BMPLoader::~BMPLoader()
{

}

Image* BMPLoader::loadImageFromFile( const String& fileName )
{
	VCF_ASSERT( !fileName.empty() );
	return new Win32Image( fileName );
}

void BMPLoader::saveImageToFile( const String& fileName, Image* image )
{
	VCF_ASSERT( !fileName.empty() );

	Win32Image* win32Img = (Win32Image*)image;

	win32Img->internal_saveToFile( fileName );
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:06:02  ddiego
*added missing gtk files
*
*Revision 1.4  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.5  2005/04/11 17:07:17  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3.2.4  2005/04/09 17:21:39  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.3  2005/04/03 18:13:45  ddiego
*fixed bug 1175667 - Lack of SysTray Icon Transparency.
*
*Revision 1.3.2.2  2005/03/15 01:51:54  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.1  2004/12/19 04:05:05  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/11/21 00:19:11  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.2.2.1  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/08/01 18:55:06  kiklop74
*A bit ugly workaround around BCB5 bugs during compilation
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.33.4.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.33  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.32.2.1  2003/10/07 00:11:38  marcelloptr
*fix: selecting oldBitmap before deleting the device context
*
*Revision 1.32  2003/08/09 02:56:46  ddiego
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
*Revision 1.31.2.3  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.31.2.2  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.31.2.1  2003/05/25 19:07:14  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.31  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.30.2.3  2003/04/07 03:39:32  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.30.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.30.2.1  2003/03/12 03:12:38  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.30  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.29.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.29  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.28.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.28.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.28  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.27  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


