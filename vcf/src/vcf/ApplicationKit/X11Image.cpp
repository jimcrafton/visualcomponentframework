//X11Image.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;

X11Image::X11Image():
	x11ImagePixmap_(0),
	x11AlphaMask_(0),
	ximage_(NULL)
{

	init();
}

X11Image::X11Image( const unsigned long& width, const unsigned long& height ):
	AbstractImage(false),
	x11ImagePixmap_(0),
	x11AlphaMask_(0),
	ximage_(NULL)
{

	init();

	setWidth( width );
	setHeight( height );
}

X11Image::X11Image( const String& fileName ):
	AbstractImage(false),
	x11ImagePixmap_(0),
	x11AlphaMask_(0),
	ximage_(NULL)
{

	init();
	loadFromFile( fileName );
}

X11Image::X11Image( GraphicsContext* context, Rect* rect  ):
	AbstractImage(false),
	x11ImagePixmap_(0),
	x11AlphaMask_(0),
	ximage_(NULL)
{


}


X11Image::~X11Image()
{
	imlib_context_set_image( ximage_ );
	imlib_free_pixmap_and_mask( x11ImagePixmap_ );
	imlib_free_image_and_decache();
	imlib_context_set_image( 0 );

	imageBits_->bits_ = NULL;
}

void X11Image::init()
{

	context_ = NULL;//new GraphicsContext(0);//(long)dc_ );
}

void X11Image::setWidth( const unsigned long & width )
{
	AbstractImage::setWidth( width );
	createBitmap();
}

void X11Image::setHeight( const unsigned long & height )
{
	AbstractImage::setHeight( height );
	createBitmap();
}


void X11Image::createBitmap()
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	Display* x11Display = toolkit->getX11Display();

	imlib_context_set_image( ximage_ );

	if ( NULL != ximage_ ) {
		imlib_free_image_and_decache();
	}

	if ( NULL != x11ImagePixmap_ ) {
		imlib_free_pixmap_and_mask( x11ImagePixmap_ );
	}

	imlib_context_set_image( 0 );

	imageBits_->bits_ = NULL;

	ulong32 width = getWidth();
	ulong32 height = getHeight();


	if ( (width > 0) && (height > 0) ) {

		int x11screen = toolkit->getX11ScreenID();

		ximage_ = imlib_create_image( width, height );

		if ( NULL == ximage_ ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2("X11Image::createBitmap() error: Imlib2 is unable to create a an Image") );
		}

		imlib_context_set_image( ximage_ );

		imlib_context_set_drawable( DefaultRootWindow( toolkit->getX11Display() ) );

		imlib_render_pixmaps_for_whole_image( &x11ImagePixmap_, &x11AlphaMask_ );


		DATA32* imImageData = imlib_image_get_data();

		imageBits_->bits_ = (RGBAVals*)imImageData;

		imlib_context_set_image(0);

		if ( x11ImagePixmap_ == 0 ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2("X11Image::createBitmap() error: Imlib2 is unable to allocate a pixmap for the image" ) );
		}

		if ( NULL == context_ ) {
			context_ = new GraphicsContext(x11ImagePixmap_);
		}

		X11Context* ctxPeer = dynamic_cast<X11Context*>(context_->getPeer());
		if ( NULL == ctxPeer ) {
			throw RuntimeException( MAKE_ERROR_MSG_2( "The peer associated with this image's GraphicsContext is NOT an X11Context instance" ) );
		}

		ctxPeer->setContextID( (long) x11ImagePixmap_ );
		ctxPeer->setParentImage( this );
	}
}

ImageBits* X11Image::getImageBits()
{
	imlib_context_set_image( ximage_ );

	DATA32* imImageData = imlib_image_get_data();

	imageBits_->bits_ = (RGBAVals*)imImageData;

	imlib_context_set_image(0);

	return imageBits_;
}

void X11Image::updateImageDataFromImageBits()
{
	DATA32* imImageData = (DATA32*)imageBits_->bits_;
	imlib_context_set_image( ximage_ );
	imlib_image_put_back_data( imImageData );
	imlib_context_set_image(0);
}

void X11Image::loadFromFile( const String& fileName )
{

}


void X11Image::saveToFile( const String& fileName )
{

}





XPMLoader::XPMLoader()
{

}

XPMLoader::~XPMLoader()
{

}

Image* XPMLoader::loadImageFromFile( const String& fileName )
{
	return new X11Image( fileName );
}

void XPMLoader::saveImageToFile( const String& fileName, Image* image )
{

}


/**
$Id$
*/
