//ImageFormats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "ImageFormats/ImageFormats.h"

#include "thirdparty/common/paintlib/common/PaintLib.h"


using namespace VCF;


Image* loadImageFromFile( const String& fileName )
{
	Image* result = NULL;	

	PLAnyPicDecoder Decoder;
	PLAnyBmp dib;
		
	Decoder.MakeBmpFromFile (fileName.ansi_c_str(), &dib);		
		
	ulong32 width  = dib.GetWidth();
	ulong32 height = dib.GetHeight();

	uchar* bits = NULL;
	unsigned bpp = dib.GetBitsPerPixel();

	if ( bpp < 32 ) {
		PLAnyBmp dib2;

		// NOTE: This is Win32 format BGRA order. Need to change for OSX and Linux
		dib2.CreateCopy(dib, PLPixelFormat::B8G8R8X8);

		bits = dib2.GetPixels();

		if ( NULL != bits ) {			
			result = GraphicsToolkit::createImage( width, height );			
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}
	}
	else {
		bits = dib.GetPixels();

		if ( NULL != bits ) {			
			result = GraphicsToolkit::createImage( width, height );			
			uchar* imageBits = (uchar*)result->getImageBits()->pixels_;
			int size = height * (width * 4);
			memcpy( imageBits, bits, size );
		}
	}
	return result;
}

Image* TIFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;

}
	
void TIFFLoader::saveImageToFile( const String& fileName, Image* image )
{
	ulong32 width = image->getWidth();
	ulong32 height = image->getHeight();
//	uchar* imageBits = (uchar*)image->getImageBits()->pixels_;
}


Image* IFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void IFFLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* PCXLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void PCXLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* PSDLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void PSDLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* TARGALoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void TARGALoader::saveImageToFile( const String& fileName, Image* image )
{
	
}

Image* PGMLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void PGMLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* PICTLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void PICTLoader::saveImageToFile( const String& fileName, Image* image )
{
	
}


Image* SGILoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}
	
void SGILoader::saveImageToFile( const String& fileName, Image* image )
{
	
}




class ImageFormatsApplication : public LibraryApplication {
public:

	virtual bool initRunningApplication(){
		bool result = LibraryApplication::initRunningApplication();	
		
		//FreeImage_Initialise(); //intialize FreeImage

		//register the image formats here

		GraphicsToolkit::registerImageLoader( "image/tiff", new TIFFLoader() );

		GraphicsToolkit::registerImageLoader( "image/iff", new IFFLoader() );

		GraphicsToolkit::registerImageLoader( "image/pcx", new PCXLoader() );

		GraphicsToolkit::registerImageLoader( "image/psd", new PSDLoader() );

		GraphicsToolkit::registerImageLoader( "image/targa", new TARGALoader() );

		GraphicsToolkit::registerImageLoader( "image/pgm", new PGMLoader() );

		GraphicsToolkit::registerImageLoader( "image/pict", new PICTLoader() );

		GraphicsToolkit::registerImageLoader( "image/sgi", new SGILoader() );

		return result;
	}

	virtual void terminateRunningApplication() {
		//FreeImage_DeInitialise();

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


