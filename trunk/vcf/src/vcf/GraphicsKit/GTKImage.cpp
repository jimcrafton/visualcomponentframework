//GTKImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

GTKImage::GTKImage( const String& fileName ):
	AbstractImage(false),
	pixmap_(NULL),
	pixBuf_(NULL),
	bitmap_(NULL)
{
	init();
}

GTKImage::GTKImage( const unsigned long& width, const unsigned long& height ):
	AbstractImage(false),
	pixmap_(NULL),
	pixBuf_(NULL),
	bitmap_(NULL)
{
	init();
	createImage( width, height );
	AbstractImage::setSize( width, height );
}

GTKImage::GTKImage( GraphicsContext* context, Rect* rect ):
	AbstractImage(false),
	pixmap_(NULL),
	pixBuf_(NULL),
	bitmap_(NULL)
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

	context_ = new GraphicsContext( (unsigned long) gdk_get_default_root_window() );
	GTKContext* gtkCtx = (GTKContext*)context_->getPeer();
	gtkCtx->setParentImage( this );
}

void GTKImage::setWidth( const unsigned long & width )
{
	if ( width > 0 && getHeight() > 0 ) {
		createImage( width, getHeight() );
		AbstractImage::setSize( width, getHeight() );
	}
}

void GTKImage::setHeight( const unsigned long & height )
{
	if ( getWidth() > 0 && height > 0 ) {
		createImage( getWidth(), height );
		AbstractImage::setSize( getWidth(), height );
	}
}

void GTKImage::createImage( const unsigned long & width, const unsigned long & height )
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
		throw InvalidPointerException( MAKE_ERROR_MSG_2("gdk_pixbuf_new returned a NULL pixbuf handle") );
	}

	gdk_pixbuf_fill( pixBuf_, 0xFFFFFFFF );

	gdk_pixbuf_render_pixmap_and_mask( pixBuf_, &pixmap_, &bitmap_, 255 );

	context_->getPeer()->setContextID( (unsigned long)pixmap_ );

	imageBits_->pixels_ = (SysPixelType*)gdk_pixbuf_get_pixels( pixBuf_ );

}

void GTKImage::updatePixmapFromImageBits()
{
	GTKContext* gtkCtx = (GTKContext*)context_->getPeer();

	gdk_draw_pixbuf( pixmap_, gtkCtx->getGC(), pixBuf_, 0, 0, 0, 0,
					getWidth(), getHeight(), GDK_RGB_DITHER_NORMAL, 0, 0 );
}

void GTKImage::updateImageBitsFromPixmap()
{
	GdkColormap* colorMap = gdk_drawable_get_colormap( pixmap_ );
	GdkPixbuf* pb = gdk_pixbuf_get_from_drawable( pixBuf_, pixmap_, colorMap, 0, 0, 0, 0,
													getWidth(), getHeight() );

}


void GTKImage::beginDrawing()
{

}

void GTKImage::finishedDrawing()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/08/09 02:56:46  ddiego
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
*Revision 1.3.2.2  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.3.2.1  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.3  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:48  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/23 05:08:47  ddiego
*finished up the GTKImage class. Now putting in text rendering with pango support
*
*Revision 1.1.2.1  2003/02/20 02:46:03  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
Auto generated C++ implementation for class GTKImage
*/


