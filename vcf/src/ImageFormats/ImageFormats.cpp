//ImageFormats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "ImageFormats/ImageFormats.h"

#include "thirdparty/common/FreeImage/Source/FreeImage.h"

using namespace VCF;


PNGLoader::PNGLoader()
{

}

PNGLoader::~PNGLoader()
{

}

Image* PNGLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadPNG(fileName.ansi_c_str(), PNG_DEFAULT);
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}


void PNGLoader::saveImageToFile( const String& fileName, Image* image )
{
	ulong32 width = image->getWidth();
	ulong32 height = image->getHeight();
	uchar* imageBits = (uchar*)image->getImageBits()->pixels_;

	FIBITMAP* dib = FreeImage_ConvertFromRawBits( imageBits, width, height, width*4, 32, 0, 0, 0, true );

	if ( NULL != dib ) {
		FreeImage_SavePNG( dib, fileName.ansi_c_str() );

		FreeImage_Free( dib ); 
	}
}

Image* JPEGLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadJPEG( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void JPEGLoader::saveImageToFile( const String& fileName, Image* image )
{
	ulong32 width = image->getWidth();
	ulong32 height = image->getHeight();
	uchar* imageBits = (uchar*)image->getImageBits()->pixels_;

	FIBITMAP* dib = FreeImage_ConvertFromRawBits( imageBits, width, height, width*4, 32, 0, 0, 0, true );

	//convert to 24 bits;
	FIBITMAP* oldDib = dib;
	dib = FreeImage_ConvertTo24Bits( oldDib );
	FreeImage_Free( oldDib );	
	if ( NULL != dib ) {
		FreeImage_SaveJPEG( dib, fileName.ansi_c_str() );

		FreeImage_Free( dib ); 
	}
}


Image* TIFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadTIFF( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void TIFFLoader::saveImageToFile( const String& fileName, Image* image )
{
	ulong32 width = image->getWidth();
	ulong32 height = image->getHeight();
	uchar* imageBits = (uchar*)image->getImageBits()->pixels_;

	FIBITMAP* dib = FreeImage_ConvertFromRawBits( imageBits, width, height, width*4, 32, 0, 0, 0, true );

	if ( NULL != dib ) {
		FreeImage_SaveTIFF( dib, fileName.ansi_c_str() );

		FreeImage_Free( dib ); 
	}
}


Image* IFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadIFF( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void IFFLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* KOALALoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadKOALA( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void KOALALoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* LBMLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadLBM( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void LBMLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* MNGLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadMNG( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void MNGLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* PCDLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadPCD( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void PCDLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}



Image* PCXLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadPCX( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void PCXLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}



Image* PNMLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadPNM( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void PNMLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* PSDLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadPSD( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void PSDLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* RASLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadRAS( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void RASLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}



Image* TARGALoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_LoadTARGA( fileName.ansi_c_str() );
	
	if (dib != NULL) {				
		
		int bpp = FreeImage_GetBPP( dib );

		BITMAPINFOHEADER* bih = FreeImage_GetInfoHeader( dib );

		if ( bpp < 32 ) {
			FIBITMAP * oldDib = dib;			

			dib = FreeImage_ConvertTo32Bits( oldDib );

			FreeImage_Free(oldDib);	
		}

		ulong32 width = FreeImage_GetWidth( dib );
		ulong32 height = FreeImage_GetHeight( dib );

		uchar* bits = FreeImage_GetBits( dib );
		
		if ( NULL != bits ) {
			result = GraphicsToolkit::createImage( width, height );
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}		
		
		//now we're finished
		FreeImage_Free(dib);
	}
	return result;
}
	
void TARGALoader::saveImageToFile( const String& fileName, Image* image )
{
	
}



class ImageFormatsApplication : public LibraryApplication {
public:

	virtual bool initRunningApplication(){
		bool result = LibraryApplication::initRunningApplication();	
		
		FreeImage_Initialise(); //intialize FreeImage

		//register the image formats here

		GraphicsToolkit::registerImageLoader( "image/png", new PNGLoader() );

		GraphicsToolkit::registerImageLoader( "image/jpeg", new JPEGLoader() );

		GraphicsToolkit::registerImageLoader( "image/tiff", new TIFFLoader() );

		GraphicsToolkit::registerImageLoader( "image/iff", new IFFLoader() );

		GraphicsToolkit::registerImageLoader( "image/koala", new KOALALoader() );

		GraphicsToolkit::registerImageLoader( "image/lbm", new LBMLoader() );

		GraphicsToolkit::registerImageLoader( "image/mng", new MNGLoader() );

		GraphicsToolkit::registerImageLoader( "image/pcd", new PCDLoader() );

		GraphicsToolkit::registerImageLoader( "image/pcx", new PCXLoader() );

		GraphicsToolkit::registerImageLoader( "image/pnm", new PNMLoader() );

		GraphicsToolkit::registerImageLoader( "image/psd", new PSDLoader() );

		GraphicsToolkit::registerImageLoader( "image/ras", new RASLoader() );

		GraphicsToolkit::registerImageLoader( "image/targa", new TARGALoader() );

		return result;
	}

	virtual void terminateRunningApplication() {
		FreeImage_DeInitialise();

		LibraryApplication::terminateRunningApplication();		
	}

};






#ifdef WIN32

#include "vcf/FoundationKit/Win32Peer.h"

static ImageFormatsApplication* singleImageFormatsApplicationInstance = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			singleImageFormatsApplicationInstance = new ImageFormatsApplication();

			singleImageFormatsApplicationInstance->getPeer()->setHandleID( hModule );
			
			singleImageFormatsApplicationInstance->setName( "ImageFormats" );

			LibraryApplication::registerLibrary( singleImageFormatsApplicationInstance );

			if ( false == singleImageFormatsApplicationInstance->initRunningApplication() ) {
				singleImageFormatsApplicationInstance->terminateRunningApplication();

				delete singleImageFormatsApplicationInstance;

				singleImageFormatsApplicationInstance = NULL;
			}
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {
			if ( NULL != singleImageFormatsApplicationInstance ) {
				delete singleImageFormatsApplicationInstance;
				singleImageFormatsApplicationInstance = NULL;
			}
		}
		break;
    }
    return TRUE;
}

#endif //WIN32


