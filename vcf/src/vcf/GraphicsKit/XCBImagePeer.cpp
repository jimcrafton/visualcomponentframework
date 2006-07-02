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

	XCBConnection *connection = XCBGraphicsToolkit::getConnection();
	XCBSCREEN *screen = XCBGraphicsToolkit::getScreen();

	CARD8 depth = XCBAuxGetDepth (connection, screen);

	int componentCount = getType();
	int bpp = getChannelSize() * componentCount;

	uint32 width = getWidth();
	uint32 height = getHeight();
	int bytesPerRow = (width * (bpp/componentCount) * componentCount) / 8;

	dataBuffer_ = new unsigned char[width * height * (bpp / 8)];
	//memset(dataBuffer_, 0, width * height * (bpp / 8));

	image_ = XCBImageCreate(connection, depth, XCBImageFormatZPixmap, 0, dataBuffer_, width, height, bpp, bytesPerRow);

	Color c = Color(1.0, 1.0, 0.0);
	CARD32 pixel = c.getRGBPack8();
	for(uint32 srcY = 0; srcY<height; ++srcY) {
		for(uint32 srcX = 0; srcX<width; ++srcX) {
			XCBImagePutPixel(image_, srcX, srcY, pixel);
		}
	}
}

void XCBImagePeer::destroyImage()
{
	delete [] dataBuffer_;
	image_->data = NULL;
	XCBImageDestroy(image_);
	image_ = NULL;
}

const XCBImage* XCBImagePeer::getImageData() const
{
	return image_;
}

/**
$Id$
*/

