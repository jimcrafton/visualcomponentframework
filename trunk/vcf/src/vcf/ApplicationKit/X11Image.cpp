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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:37:40  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:12:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.8.3  2002/12/20 03:29:33  ddiego
*continued more work in integrating imlib2 into the X11Image class. getting
*a little better hand of how to debug with CLI gdb ! Close to having this
*work, and tehn we can work on Fonts !
*
*Revision 1.2.8.2  2002/12/14 23:29:48  ddiego
*partial image support no in
*
*Revision 1.2  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*/


