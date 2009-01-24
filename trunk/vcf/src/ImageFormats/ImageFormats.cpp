//ImageFormats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "ImageFormats/ImageFormats.h"

#include "thirdparty/common/paintlib/common/PaintLib.h"


using namespace VCF;


Image* loadImageFromFile( const String& fileName )
{
	Image* imgPtr = NULL;	

	PLAnyPicDecoder Decoder;
	PLAnyBmp dib;
		
	Decoder.MakeBmpFromFile (fileName.ansi_c_str(), &dib);		
		
	uint32 width  = dib.GetWidth();
	uint32 height = dib.GetHeight();

	uchar* bits = NULL;
	unsigned bpp = dib.GetBitsPerPixel();

	if ( bpp < 32 ) {
		PLAnyBmp dib2;

#if defined(WIN32)		
		dib2.CreateCopy(dib, PLPixelFormat::B8G8R8X8);

		bits = dib2.GetPixels();
#elif defined(VCF_X11) || defined(VCF_GTK) || defined(VCF_OSX)
		dib2.CreateCopy(dib, PLPixelFormat::R8G8B8X8);
		bits = dib2.GetPixels();
#endif		

		if ( NULL != bits ) {			
			//SmartPtr<Image>::Scoped img( GraphicsToolkit::createImage( width, height ) );
			//Image* imgPtr = get_pointer(img);
			imgPtr = GraphicsToolkit::createImage( width, height );			
			unsigned char* pixPtr = (unsigned char*)imgPtr->getData();
			int size = height * (width * 4);
			memcpy( pixPtr, bits, size );
		}
	}
	else {
		bits = dib.GetPixels();

		if ( NULL != bits ) {			
			//SmartPtr<Image>::Scoped img( GraphicsToolkit::createImage( width, height ) );
			//Image* imgPtr = get_pointer(img);
			imgPtr = GraphicsToolkit::createImage( width, height );			
			unsigned char* pixPtr = (unsigned char*)imgPtr->getData();
			int size = height * (width * 4);
			memcpy( pixPtr, bits, size );
		}
	}
	return imgPtr;
}

Image* TIFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;

}
	
Image* TIFFLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* TIFFLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
}

void TIFFLoader::saveImageToFile( const String& fileName, Image* image )
{
	uint32 width = image->getWidth();
	uint32 height = image->getHeight();
//	uchar* imageBits = (uchar*)image->getImageBits()->pixels_;
}


Image* IFFLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	result = loadImageFromFile( fileName );

	return result;
}

	
Image* IFFLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* IFFLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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
	
Image* PCXLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* PCXLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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

VCF::Image* PSDLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
}

	
Image* PSDLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
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
	
Image* TARGALoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* TARGALoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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


Image* PGMLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* PGMLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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

Image* PICTLoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* PICTLoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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

Image* SGILoader::loadImageFromBytes( const unsigned char* imageData, const uint64& dataLength )
{
	return NULL;
}

VCF::Image* SGILoader::loadImageFromStream( VCF::InputStream* stream )
{
	return NULL;
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


