//Win32Image.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;

Win32Image::Win32Image():
	AbstractImage(),
	flipBits_(false),
	ownDC_(true)
{
	init();
}

Win32Image::Win32Image( const uint32& width, const uint32& height ):
	AbstractImage(false),
	flipBits_(false),
	ownDC_(true)
{
	init();

	setSize( width, height );
}

Win32Image::Win32Image( const String& fileName ):
	AbstractImage(false),	
	flipBits_(true),
	ownDC_(true)
{
	init();
	loadFromFile( fileName );
}

Win32Image::Win32Image( GraphicsContext* context, Rect* rect  ):
	AbstractImage(false),
	flipBits_(false),
	ownDC_(true)
{
		init();

	//leave it this way to begin with and then
	//switch to false for the duration after the intial
	//bitmap has been created
	if ( (NULL != context) && (NULL != rect) ){
		Win32Context* ctx = (Win32Context*)(context->getPeer() );
		if ( NULL != ctx ){
			//set up the bitmap data
			IMTRAITS::setChannelType( flags_, IMTRAITS::getTraitsChannelType() );
			IMTRAITS::setChannelSize( flags_, IMTRAITS::getTraitsChannelSize() );
			IMTRAITS::setImageType( flags_, IMTRAITS::getTraitsImageType() );
			IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

			palette_ = NULL;

			HDC contextDC = (HDC)ctx->getContextID();

			setSize( rect->getWidth(), rect->getHeight() );

			BitBlt( hbmp_.dc(), 0, 0, getWidth(), getHeight(), contextDC, (int)rect->left_, (int)rect->top_, SRCCOPY );			
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


Win32Image::Win32Image( HBITMAP bitmap ):
	AbstractImage(false),
	flipBits_(true),
	ownDC_(true)	
{
	init();

	if ( NULL == bitmap ) {
		throw InvalidPointerException(MAKE_ERROR_MSG_2("NULL HBITMAP passed into Win32Image constructor"));
	}
	loadFromBMPHandle( bitmap );
}

Win32Image::Win32Image( HICON icon ):
	AbstractImage(false),
	flipBits_(true),
	ownDC_(true)	
{
	init();

	ICONINFO info;
	memset(&info,0,sizeof(info));
	if ( GetIconInfo( icon, &info ) ) {
		BITMAP bmp;
		if ( GetObject( info.hbmColor, sizeof(BITMAP), &bmp ) ) {
		
			setSize( bmp.bmWidth, bmp.bmHeight );

			if ( !DrawIcon( hbmp_.dc(), 0, 0, icon ) ) {
				StringUtils::traceWithArgs( Format("DrawIcon failed, err: %d\n") % GetLastError()  );
			}
		}
	}
}

Win32Image::~Win32Image()
{
	//if ( NULL != hBitmap_ ){
	//	SelectObject( dc_, hOldBitmap_ );
	//	int err = DeleteObject( hBitmap_ );
	//}

	//the base class AbstractImage will take care of
	//deleting hte GraphicsContext. If we don't
	//own the DC then set the context_ to null
	//to prevent from deleting it
	if ( ownDC_ ) {
		//DeleteDC( dc_ );
	}
	else {
		hbmp_.detach();
		context_ = NULL;
	}
	//imageBits_->pixels_ = NULL;
}

void Win32Image::init()
{
	//NOTE: init() is not called if ownDC_ is true - the constructor takes care of this
	IMTRAITS::setChannelType( flags_, IMTRAITS::getTraitsChannelType() );
	IMTRAITS::setChannelSize( flags_, IMTRAITS::getTraitsChannelSize() );
	IMTRAITS::setImageType( flags_, IMTRAITS::getTraitsImageType() );
	IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

	//hBitmap_ = NULL;

	palette_ = NULL;

	//dc_ = ::CreateCompatibleDC( NULL );

	//the deletion of the context_ should delete the
	//dc_ handle
	context_ = new GraphicsContext( (OSHandleID)hbmp_.dc() );
}

void Win32Image::setSize( const uint32 & width, const uint32 & height )
{
	if ( (!ownDC_) && (hbmp_ != NULL) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}
	AbstractImage::setSize( width, height );
	createBMP();
}


void Win32Image::createBMP()
{
	if ( (!ownDC_) && (hbmp_ != NULL) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}

	

	dataBuffer_ = NULL;
//	imageBits_->pixels_ = NULL;

	hbmp_.setSize( getWidth(), getHeight() );

	BITMAPINFO& bmpInfo = getBMPInfo();

	//hBitmap_ = CreateDIBSection ( dc_, &bmpInfo_, DIB_RGB_COLORS, (void **)&imageBits_->pixels_, NULL, NULL );

	if ( (hbmp_ != NULL) ) {
		
		dataBuffer_ = (unsigned char*)hbmp_.data();
//		imageBits_->pixels_ = (SysPixelType*)hbmp_.data();

		SysPixelType* pix = (SysPixelType*)dataBuffer_;
		int sz = bmpInfo.bmiHeader.biWidth * abs(bmpInfo.bmiHeader.biHeight);
		do {
			sz --;
			pix[sz].a = 255;
		} while( sz > 0 );


		//hOldBitmap_ = (HBITMAP)::SelectObject( dc_, hBitmap_ );
		//::DeleteObject( oldObj );//clear out the old object
	}
}

HBITMAP Win32Image::getBitmap()
{
	return hbmp_;
}

HDC Win32Image::getDC()
{
	return hbmp_.dc();
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
	BITMAP bmp;
	memset(&bmp,0,sizeof(bmp));
	GetObject( bitmap, sizeof(bmp), &bmp );

	setSize( bmp.bmWidth, bmp.bmHeight );

	HDC tmpBMPDC = CreateCompatibleDC( NULL );
	HBITMAP oldBitmap = (HBITMAP)::SelectObject(  tmpBMPDC, bitmap );

	BitBlt( hbmp_.dc(), 0, 0, bmp.bmWidth, bmp.bmHeight, tmpBMPDC, 0, 0, SRCCOPY );

	::SelectObject(  tmpBMPDC, oldBitmap );
	DeleteDC( tmpBMPDC );
	DeleteObject( bitmap );

	SysPixelType* pix = (SysPixelType*) hbmp_.data();
	BITMAPINFO& bmpInfo = getBMPInfo();

	int sz = bmpInfo.bmiHeader.biWidth * abs(bmpInfo.bmiHeader.biHeight);
	do {
		sz --;
		pix[sz].a = 255;
	} while( sz > 0 );
}

void Win32Image::internal_saveToFile( const String& fileName )
{

	/**
	NOTE!!!!
	It's important that this get's written out with "wb", not 
	just "w" here.
	*/
#ifdef VCF_CW
	FILE* f = fopen( fileName.ansi_c_str(), "wb" );
#else
	FILE* f = _wfopen( fileName.c_str(), L"wb" );
#endif

	// write the file header

	const int bitsPerPix = 24;
	//store width for 24bit image NOT 32
	DWORD width = ((((bitsPerPix * getWidth()) + 31) / 32) * 4);

	DWORD size = getHeight() * width;

	BITMAPINFOHEADER bih;
	memset(&bih,0,sizeof(bih));
	
	bih.biHeight = getHeight();
	bih.biWidth = getWidth();
	
	bih.biClrImportant = 0;
	bih.biClrUsed = 0;

	bih.biPlanes = 1;
	bih.biSizeImage = size;
	bih.biBitCount = bitsPerPix;
	bih.biSize = sizeof(BITMAPINFOHEADER);

	bih.biCompression = BI_RGB;

	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;


	BITMAPFILEHEADER bitmapfileheader;
	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = sizeof(BITMAPFILEHEADER) + size;

	bitmapfileheader.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + bih.biSize;
		//sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		//0 * sizeof(RGBQUAD);

	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;

	fwrite( &bitmapfileheader, sizeof(BITMAPFILEHEADER), 1, f );
	


	// write the info header
	fwrite( &bih, bih.biSize, 1, f );



	

	// write the palette here, but we'll do nothing since we don't support palettes


	DWORD height = getHeight();
	ColorPixels pix(this);
	SysPixelType* bits = pix;
	unsigned char* row = new unsigned char[width];
	uint32 imgWidth = getWidth();

	// write the bitmap data

	unsigned char* tmpRow = row;
	for ( int y=height-1;y>=0;y-- ) {		
		tmpRow = row;
		for (uint32 x=0;x<imgWidth;x++ ) {		
			SysPixelType& pix = bits[y*imgWidth + x];
			
			*tmpRow = pix.b;
			tmpRow++;
			*tmpRow = pix.g;
			tmpRow++;
			*tmpRow = pix.r;
			tmpRow++;
		}
		fwrite( row, width, 1, f );
	}
	delete []row;

	fclose( f );
}


void Win32Image::beginDrawing()
{
	//Sadly windows will overwrite the alpha
	//channel if the bmp's context is retreived and then
	//drawn on using Win32 GDI calls like Rectangle, Polyline, etc
	//So we need to store the values out, and then
	//reset them in finishedDrawing()

	ColorPixels pix(this);
	size_t sz = pix.width() * pix.height();

	SysPixelType* bits = pix;

	tempAlphaChannel_ = new unsigned char[sz];	
	
	do {
		sz --;
		tempAlphaChannel_[sz] = bits[sz].a;
	} while( sz > 0 );
}

void Win32Image::finishedDrawing()
{
	if ( NULL != tempAlphaChannel_ ) {
		ColorPixels pix(this);
		size_t sz = pix.width() * pix.height();
		
		SysPixelType* bits = pix;	
		
		do {
			sz --;
			bits[sz].a = tempAlphaChannel_[sz];
		} while( sz > 0 );

		delete [] tempAlphaChannel_;
	}

	tempAlphaChannel_ = NULL;
}


HICON Win32Image::convertToIcon()
{
	HICON result = NULL;
	//this is justa big fat method from HELLLL

	OSVERSIONINFO osVersion;
	memset(&osVersion,0,sizeof(osVersion));
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);

	GetVersionEx( &osVersion );

	SysPixelType* bits = (SysPixelType*) hbmp_.data();

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

	HBITMAP hANDBitmap = CreateDIBSection ( hbmp_.dc(), monochromeInfo, DIB_RGB_COLORS,
		(void **)&ANDBits, NULL, NULL );

	BITMAPINFO info;
	memset(&info,0,sizeof(info));
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biHeight = -getHeight();
	info.bmiHeader.biWidth = getWidth();
	info.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage =
		info.bmiHeader.biWidth * abs(info.bmiHeader.biHeight) * 4;

	HBITMAP hXORBitmap = CreateDIBSection ( hbmp_.dc(), &info, DIB_RGB_COLORS,
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
						int32 bitmaskIndex = 8 - index % 8 - 1;

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

		ICONINFO icoInfo;
		memset(&icoInfo,0,sizeof(icoInfo));
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










Win32GrayScaleImage::Win32GrayScaleImage():
	GrayScaleImage(),
	flipBits_(false),
	ownDC_(true)
{
	init();
}

Win32GrayScaleImage::Win32GrayScaleImage( const String& fileName ):
	GrayScaleImage(false),
	flipBits_(true),
	ownDC_(true)
{
	init();
}

Win32GrayScaleImage::Win32GrayScaleImage( const uint32& width, const uint32& height ):
	GrayScaleImage(false),	
	flipBits_(false),
	ownDC_(true)
{
	init();
	setSize( width, height );
}

Win32GrayScaleImage::Win32GrayScaleImage( GraphicsContext* context, Rect* rect ):
	GrayScaleImage(false),	
	flipBits_(true),
	ownDC_(true)
{
	init();

	//leave it this way to begin with and then
	//switch to false for the duration after the intial
	//bitmap has been created
	if ( (NULL != context) && (NULL != rect) ){
		Win32Context* ctx = reinterpret_cast<Win32Context*>(context->getPeer() );
		if ( NULL != ctx ){
			//set up the bitmap data
			IMTRAITS::setChannelType( flags_, SysGrayscalePixelType::Traits::getTraitsChannelType() );
			IMTRAITS::setChannelSize( flags_, SysGrayscalePixelType::Traits::getTraitsChannelSize() );
			IMTRAITS::setImageType( flags_, SysGrayscalePixelType::Traits::getTraitsImageType() );
			IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

			//hBitmap_ = NULL;

			palette_ = NULL;

			HDC contextDC = (HDC)ctx->getContextID();

			//the deletion of the context_ should delete the
			//dc_ handle
			context_ = context;

			HDC tmpDC = CreateCompatibleDC( contextDC );
			HDC origDC = contextDC;
			contextDC = tmpDC;

			setSize( rect->getWidth(), rect->getHeight() );

			contextDC = origDC;

			int r = BitBlt( tmpDC, 0, 0, getWidth(), getHeight(), contextDC, (int)rect->left_, (int)rect->top_, SRCCOPY );

			::SelectObject( tmpDC, hbmp_.oldBMP() );
			DeleteDC( tmpDC );

			hbmp_.attach( contextDC );

			//hOldBitmap_ = (HBITMAP)::SelectObject( dc_, (HBITMAP)hbmp );
			//ownDC_ = false;
		}
		else {
			//throw exception !!!
			throw InvalidPointerException( MAKE_ERROR_MSG_2("Incorrect peer class (isn't a Win32Context) for passed GraphicsContext instance" ) );
		}
	}
	else {
		//throw exception !!!
		throw InvalidPointerException( MAKE_ERROR_MSG_2("Graphics Context passed in to Win32GrayScaleImage is NULL" ) );
	}
}

Win32GrayScaleImage::Win32GrayScaleImage( HBITMAP bitmap ):
	GrayScaleImage(false),
	flipBits_(true),
	ownDC_(true)
{
	init();
}

Win32GrayScaleImage::Win32GrayScaleImage( HICON icon ):
	GrayScaleImage(false),
	flipBits_(true),
	ownDC_(true)
{
	init();
}

Win32GrayScaleImage::~Win32GrayScaleImage()
{
	if ( !ownDC_ ) {
		hbmp_.detach();
		context_ = NULL;
	}
}

void Win32GrayScaleImage::init()
{
	//NOTE: init() is not called if ownDC_ is true - the constructor takes care of this
	IMTRAITS::setChannelType( flags_, SysGrayscalePixelType::Traits::getTraitsChannelType() );
	IMTRAITS::setChannelSize( flags_, SysGrayscalePixelType::Traits::getTraitsChannelSize() );
	IMTRAITS::setImageType( flags_, SysGrayscalePixelType::Traits::getTraitsImageType() );
	IMTRAITS::setPixelLayoutOrder( flags_, Image::ploBGRA );

	palette_ = NULL;

	//the deletion of the context_ should delete the
	//dc_ handle
	context_ = new GraphicsContext( (OSHandleID)hbmp_.dc() );
}

void Win32GrayScaleImage::setSize( const uint32 & width, const uint32 & height )
{
	if ( (!ownDC_) && (hbmp_ != NULL) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}
	AbstractImage::setSize( width, height );
	createBMP();
}

void Win32GrayScaleImage::createBMP()
{
	if ( (!ownDC_) && (hbmp_ != NULL) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Cannot set size for non modifiable image") );
	}

	

	dataBuffer_ = NULL;

	hbmp_.setSize( getWidth(), getHeight() );

	if ( (hbmp_ != NULL) ) {
		
		dataBuffer_ = (unsigned char*)hbmp_.data();

		//create grayscale palette!

		BITMAPINFO& bmpInfo = getBMPInfo();


		unsigned char* tmp = new unsigned char[ sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256) ];
		LOGPALETTE* pal = (LOGPALETTE*)tmp;

		pal->palNumEntries = 256;
		pal->palVersion = 0x300;

		PALETTEENTRY* entry = &pal->palPalEntry[0];

		for (unsigned short i=0;i<pal->palNumEntries;i++ ) {
			entry->peRed = bmpInfo.bmiColors[i].rgbRed;
			entry->peGreen = bmpInfo.bmiColors[i].rgbGreen;
			entry->peBlue = bmpInfo.bmiColors[i].rgbBlue;
			entry->peFlags = 0;
			entry ++;
		}


		if ( NULL != palette_ ) {
			DeleteObject(palette_); 
			palette_ = NULL;
		}

		palette_ = ::CreatePalette( pal );

		::SelectPalette( hbmp_.dc(), palette_, TRUE );
		::RealizePalette( hbmp_.dc() );

		delete [] tmp;
	}
}

void Win32GrayScaleImage::beginDrawing()
{

}

void Win32GrayScaleImage::finishedDrawing()
{

}

HBITMAP Win32GrayScaleImage::getBitmap()
{
	return hbmp_;
}

HDC Win32GrayScaleImage::getDC()
{
	return hbmp_.dc();
}

HICON Win32GrayScaleImage::convertToIcon()
{
	return NULL;
}

void Win32GrayScaleImage::loadFromFile( const String& fileName )
{

}

void Win32GrayScaleImage::loadFromBMPHandle( HBITMAP bitmap )
{

}

void Win32GrayScaleImage::internal_saveToFile( const String& fileName )
{

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
$Id$
*/
