//AbstractImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */

#include "vcf/GraphicsKit/GraphicsKit.h"

using namespace VCF;


AbstractImage::AbstractImage( const bool& needsMemAlloc ):	
//	imageBits_(NULL),
	dataBuffer_(NULL),
	height_(0),
	width_(0),	
	context_(NULL),
	isTransparent_(false),
	needsMemAlloc_(needsMemAlloc)
{
	//imageBits_ = new ImageBits(0,0,needsMemAlloc);	
}

AbstractImage::~AbstractImage()
{
	delete context_;
	//delete imageBits_;
}

void AbstractImage::setSize(const uint32 & width, const uint32 & height )
{
	width_ = width;
	height_ = height;
	if ( (width_ > 0) && (height_ > 0) ) {
//		imageBits_->allocatePixelMemory( width_, height_ );

		ImageEvent event(this);
		event.setType( IMAGE_EVENT_WIDTH_CHANGED );
		event.setNewWidth( width );
		ImageSizeChanged( &event );

		ImageEvent event2(this);
		event2.setType( IMAGE_EVENT_HEIGHT_CHANGED );
		event2.setNewHeight( height_ );
		ImageSizeChanged( &event2 );
	}
}

uint32 AbstractImage::getWidth()
{
	return width_;
}


uint32 AbstractImage::getHeight(){
	return height_;
}

GraphicsContext* AbstractImage::getImageContext()
{
	return context_;
}
/*
ImageBits* AbstractImage::getImageBits()
{
	return imageBits_;
}
*/

void AbstractImage::saveToStream( OutputStream * stream )
{
	int32 bitDepth = getType() * getChannelSize();

	stream->write( bitDepth );


	stream->write( (int32)height_ );
	stream->write( (int32)width_ );

	const unsigned char* buffer = (const unsigned char*)getData();
	stream->write( buffer, height_ * width_ * getType() );

}

void AbstractImage::loadFromStream( InputStream * stream )
{

	int32 bitDepth;
	stream->read( bitDepth );

	int32 height = 0;
	int32 width = 0;
	stream->read( height );
	stream->read( width );
	setSize( width, height );
	unsigned char* buffer = (unsigned char*)getData();
	stream->read( buffer, height_ * width_ * getType() );
}

Image::ImageType AbstractImage::getType() const
{
	return IMTRAITS::getImageType( flags_ );
}


Image::ImageChannelSize AbstractImage::getChannelSize() const
{
	return IMTRAITS::getChannelSize( flags_ );
}

Image::ImageChannelType AbstractImage::getChannelType() const
{
	return IMTRAITS::getChannelType( flags_ );
}

Image::PixelLayoutOrder AbstractImage::getPixelLayoutOrder() const
{
	return IMTRAITS::getPixelLayoutOrder( flags_ );
}

void* AbstractImage::getData()
{
//	dataBuffer_ = (unsigned char*)imageBits_->pixels_;
	return dataBuffer_;
}

/**
$Id$
*/
