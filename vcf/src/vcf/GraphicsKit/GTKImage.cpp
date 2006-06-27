//GTKImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

GTKImage::GTKImage( const String& fileName ) :
		AbstractImage( false ),
		pixmap_( NULL ),
		pixBuf_( NULL ),
		bitmap_( NULL )
{
	init();
}

GTKImage::GTKImage( const uint32& width, const uint32& height ) :
		AbstractImage( false ),
		pixmap_( NULL ),
		pixBuf_( NULL ),
		bitmap_( NULL )
{
	init();
	createImage( width, height );
	AbstractImage::setSize( width, height );
}

GTKImage::GTKImage( GraphicsContext* context, Rect* rect ) :
		AbstractImage( false ),
		pixmap_( NULL ),
		pixBuf_( NULL ),
		bitmap_( NULL )
{
	init();
}

GTKImage::~GTKImage()
{
	//context_->getPeer()->setContextID( 0 );

	if ( NULL != pixmap_ ) {
		g_object_unref( pixmap_ );
	}
	if ( NULL != pixBuf_ ) {
		g_object_unref( pixBuf_ );
	}
	if ( NULL != bitmap_ ) {
		g_object_unref( bitmap_ );
	}
}

void GTKImage::init()
{
	context_ = new GraphicsContext( gdk_get_default_root_window() );
	GTKContext* gtkCtx = ( GTKContext* ) context_->getPeer();
	gtkCtx->setParentImage( this );
}

void GTKImage::setWidth( const uint32 & width )
{
	if ( width > 0 && getHeight() > 0 ) {
		createImage( width, getHeight() );
		AbstractImage::setSize( width, getHeight() );
	}
}

void GTKImage::setHeight( const uint32 & height )
{
	if ( getWidth() > 0 && height > 0 ) {
		createImage( getWidth(), height );
		AbstractImage::setSize( getWidth(), height );
	}
}

void GTKImage::createImage( const uint32 & width, const uint32 & height )
{
	if ( NULL != pixmap_ ) {
		g_object_unref( pixmap_ );
	}
	if ( NULL != pixBuf_ ) {
		g_object_unref( pixBuf_ );
	}
	if ( NULL != bitmap_ ) {
		g_object_unref( bitmap_ );
	}


	pixBuf_ = gdk_pixbuf_new( GDK_COLORSPACE_RGB, TRUE, 8, width, height );



	if ( NULL == pixBuf_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "gdk_pixbuf_new returned a NULL pixbuf handle" ) );
	}

	gdk_pixbuf_fill( pixBuf_, 0xFFFFFFFF );

	gdk_pixbuf_render_pixmap_and_mask( pixBuf_, &pixmap_, &bitmap_, 255 );

	context_->getPeer() ->setContextID( pixmap_ );

	imageBits_->pixels_ = ( SysPixelType* ) gdk_pixbuf_get_pixels( pixBuf_ );

}

void GTKImage::updatePixmapFromImageBits()
{
	GTKContext * gtkCtx = ( GTKContext* ) context_->getPeer();

	gdk_draw_pixbuf( pixmap_, gtkCtx->getGC(), pixBuf_, 0, 0, 0, 0,
	                 getWidth(), getHeight(), GDK_RGB_DITHER_NORMAL, 0, 0 );
}

void GTKImage::updateImageBitsFromPixmap()
{
	GdkColormap * colorMap = gdk_drawable_get_colormap( pixmap_ );
	GdkPixbuf* pb = gdk_pixbuf_get_from_drawable( pixBuf_, pixmap_, colorMap, 0, 0, 0, 0,
	                                              getWidth(), getHeight() );

}


void GTKImage::beginDrawing()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKImage::finishedDrawing()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}


/**
$Id$
*/
