/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBImagePeer.h"

using namespace VCF;

XCBImagePeer::XCBImagePeer() :
AbstractImage(false),
image_(NULL)
{
	init();
}

XCBImagePeer::XCBImagePeer( const uint32& width, const uint32& height ) :
AbstractImage(false),
image_(NULL)
{
	init();
    setSize(width, height);
}

XCBImagePeer::XCBImagePeer( GraphicsContext* context, Rect* rect ) :
AbstractImage(false),
image_(NULL)
{
	init();
}

XCBImagePeer::~XCBImagePeer()
{
}

void XCBImagePeer::setSize( const unsigned long & width, const unsigned long & height )
{
    AbstractImage::setSize( width, height );
	createBMP();
}

void XCBImagePeer::beginDrawing()
{
}

void XCBImagePeer::finishedDrawing()
{
}

void XCBImagePeer::init()
{
	//NOTE: init() is not called if ownDC_ is true - the constructor takes care of this
	IMTRAITS::setChannelType( flags_, IMTRAITS::getTraitsChannelType() );
	IMTRAITS::setChannelSize( flags_, IMTRAITS::getTraitsChannelSize() );
	IMTRAITS::setImageType( flags_, IMTRAITS::getTraitsImageType() );
	IMTRAITS::setPixelLayoutOrder( flags_, Image::ploRGBA );
}

void XCBImagePeer::createBMP()
{
	createImage();
}

void XCBImagePeer::createImage()
{
	if(image_ != NULL) {
		destroyImage();
	}

	xcb_connection_t *connection = XCBGraphicsToolkit::getConnection();
	xcb_screen_t *screen = XCBGraphicsToolkit::getScreen();

	unsigned char depth = xcb_aux_get_depth (connection, screen);

	int componentCount = getType();
	int bpp = getChannelSize() * componentCount;

	uint32 width = getWidth();
	uint32 height = getHeight();
	int bytesPerRow = (width * (bpp/componentCount) * componentCount) / 8;

	dataBuffer_ = new unsigned char[width * height * (bpp / 8)];
	//memset(dataBuffer_, 0, width * height * (bpp / 8));

	image_ = xcb_image_create(connection, depth, XCB_IMAGE_FORMAT_Z_PIXMAP, 0, dataBuffer_, width, height, bpp, bytesPerRow);

	Color c = Color(1.0, 1.0, 0.0);
	unsigned int pixel = c.getRGBPack8();
	for(uint32 srcY = 0; srcY<height; ++srcY) {
		for(uint32 srcX = 0; srcX<width; ++srcX) {
			xcb_image_put_pixel(image_, srcX, srcY, pixel);
		}
	}
}

void XCBImagePeer::destroyImage()
{
	delete [] dataBuffer_;
	image_->data = NULL;
	xcb_image_destroy(image_);
	image_ = NULL;
}

const xcb_image_t* XCBImagePeer::getImageData() const
{
	return image_;
}











XCBGrayscaleImagePeer::XCBGrayscaleImagePeer() :
AbstractImage(false),
image_(NULL)
{
	init();
}

XCBGrayscaleImagePeer::XCBGrayscaleImagePeer( const uint32& width, const uint32& height ) :
AbstractImage(false),
image_(NULL)
{
	init();
    setSize(width, height);
}

XCBGrayscaleImagePeer::XCBGrayscaleImagePeer( GraphicsContext* context, Rect* rect ) :
AbstractImage(false),
image_(NULL)
{
	init();
}

XCBGrayscaleImagePeer::~XCBGrayscaleImagePeer()
{
}

void XCBGrayscaleImagePeer::setSize( const unsigned long & width, const unsigned long & height )
{
    AbstractImage::setSize( width, height );
	createBMP();
}

void XCBGrayscaleImagePeer::beginDrawing()
{
}

void XCBGrayscaleImagePeer::finishedDrawing()
{
}

void XCBGrayscaleImagePeer::init()
{
	//NOTE: init() is not called if ownDC_ is true - the constructor takes care of this
	IMTRAITS::setChannelType( flags_, SysGrayscalePixelType::Traits::getTraitsChannelType() );
	IMTRAITS::setChannelSize( flags_, SysGrayscalePixelType::Traits::getTraitsChannelSize() );
	IMTRAITS::setImageType( flags_, SysGrayscalePixelType::Traits::getTraitsImageType() );
	IMTRAITS::setPixelLayoutOrder( flags_, Image::ploRGBA );
}

void XCBGrayscaleImagePeer::createBMP()
{
	createImage();
}

void XCBGrayscaleImagePeer::createImage()
{
	if(image_ != NULL) {
		destroyImage();
	}

	xcb_connection_t *connection = XCBGraphicsToolkit::getConnection();
	xcb_screen_t *screen = XCBGraphicsToolkit::getScreen();

	unsigned char depth = xcb_aux_get_depth (connection, screen);

	int componentCount = getType();
	int bpp = getChannelSize() * componentCount;

	uint32 width = getWidth();
	uint32 height = getHeight();
	int stride = ((width * SysGrayscalePixelType::Traits::getTraitsChannelSize() + 31) & (~31)) / 8;

	dataBuffer_ = new unsigned char[stride * height];

	image_ = xcb_image_create(connection, depth, XCB_IMAGE_FORMAT_Z_PIXMAP, 0, dataBuffer_, width, height, bpp, stride);

	unsigned int pixel = 0xFF;
	for(uint32 srcY = 0; srcY<height; ++srcY) {
		for(uint32 srcX = 0; srcX<width; ++srcX) {
			xcb_image_put_pixel(image_, srcX, srcY, pixel);
		}
	}
}

void XCBGrayscaleImagePeer::destroyImage()
{
	delete [] dataBuffer_;
	image_->data = NULL;
	xcb_image_destroy(image_);
	image_ = NULL;
}

const xcb_image_t* XCBGrayscaleImagePeer::getImageData() const
{
	return image_;
}
/**
$Id$
*/

