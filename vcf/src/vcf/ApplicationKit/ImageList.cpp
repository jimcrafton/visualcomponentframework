//ImageList.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;

ImageList::ImageList()
{
	init();
}

/*
ImageList::ImageList( Image* listOfImages, const uint32& imageWidth, const uint32& imageHeight )
{
	init();
}
*/



ImageList::ImageList( Component* owner ):
	Component( owner )
{
	init();
}

ImageList::ImageList( const String& name, Component* owner ):
	Component( name, owner )
{
	init();
}

ImageList::ImageList( const String& name ):
	Component( name )
{
	init();
}


ImageList::~ImageList()
{
	if ( NULL != masterImage_ ) {
		delete masterImage_;
		masterImage_ = NULL;
	}
}

void ImageList::init()
{
	imageWidth_ = 32;
	imageHeight_ = 32;
	imageCount_ = 5;
	resizeIncrement_ = 5;
	totalImageCount_ = 0;
	masterImage_ = NULL;
	changed();
}

uint32 ImageList::getImageWidth()
{
	return imageWidth_;
}

uint32 ImageList::getImageHeight()
{
	return imageHeight_;
}

void ImageList::setImageWidth( const uint32& width )
{
	imageWidth_ = 	width;
	changed();
	ImageListEvent event( this, IMAGELIST_EVENT_WIDTH_CHANGED );
	SizeChanged( &event );
}

void ImageList::setImageHeight( const uint32& height )
{
	imageHeight_ = height;
	changed();
	ImageListEvent event( this, IMAGELIST_EVENT_HEIGHT_CHANGED );
	SizeChanged( &event );
}

void ImageList::setTransparentColor( Color* color )
{
	transparentColor_.copy( color );
}

Color* ImageList::getTransparentColor()
{
	return &transparentColor_;
}

void ImageList::addImage( Image* newImage )
{
	VCF_ASSERT( NULL != newImage );

	if ( newImage->getHeight() != imageHeight_ ) {
		//throw exception
		return;
	}

	if ( newImage->getWidth() != imageWidth_ ) {
		//throw exception
		return;
	}

	int incr  = imageWidth_ * totalImageCount_;

	totalImageCount_++;
	if ( totalImageCount_ >= imageCount_ ) {
		//resize the master image
		imageCount_ += resizeIncrement_;
		changed();
	}

	ColorPixels pix(masterImage_);
	SysPixelType* bits = pix;
	bits += incr;

	ColorPixels newPix(newImage);
	SysPixelType* newImgBits = newPix;
	int scanlineWidthToCopy = newImage->getWidth();
	int scanlineWidthOfMasterImage = masterImage_->getWidth();//scanlineToCopy * imageCount_;
	for (uint32 i=0;i<imageHeight_;i++) {
		memcpy( bits, newImgBits, scanlineWidthToCopy*sizeof(SysPixelType) );

		bits += scanlineWidthOfMasterImage;
		newImgBits += scanlineWidthToCopy;
	}

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_ADDED, newImage );
	event.setIndexOfImage( totalImageCount_-1 );
	ImageAdded( &event );
}

void ImageList::insertImage( const uint32 & index, Image* newImage )
{
	if ( newImage->getHeight() != imageHeight_ ) {
		//throw exception
		return;
	}

	if ( newImage->getWidth() != imageWidth_ ) {
		//throw exception
		return;
	}

	int incr  = (imageWidth_ * sizeof(SysPixelType)) * index;
	int oldImgCount = totalImageCount_;
	int tmpSize = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * (totalImageCount_-index);
	int tmpLineIncr = (imageWidth_ * sizeof(SysPixelType)) * (totalImageCount_-index);
	int fullLineIncr = (imageWidth_ * sizeof(SysPixelType)) * totalImageCount_;

	//save off the old section of the
	//image that will have to be moved over
	unsigned char* tmpBits = new unsigned char[tmpSize];
	unsigned char* tmpBitsPtr = tmpBits;
	unsigned char* oldBits = (unsigned char*)masterImage_->getData();
	oldBits += incr;
	uint32 y = 0;
	for ( y=0;y<imageHeight_;y++) {
		memcpy( tmpBitsPtr, oldBits, tmpLineIncr );
		tmpBitsPtr += tmpLineIncr;
		oldBits += fullLineIncr;
	}

	//resize the image if neccessary
	totalImageCount_++;
	if ( totalImageCount_ >= imageCount_ ) {
		//resize the master image
		imageCount_ += resizeIncrement_;
		changed();
	}

	int moveOverIncr = (imageWidth_ * sizeof(SysPixelType)) * index+1;
	int indexIncr = (imageWidth_ * sizeof(SysPixelType)) * index;
	unsigned char* buf = (unsigned char*)masterImage_->getData();

	unsigned char* newImgBits = (unsigned char*)newImage->getData();
	memcpy( oldBits, newImgBits, imageHeight_ * imageWidth_ * sizeof(SysPixelType) );

	tmpBitsPtr = tmpBits;
	for ( y=0;y<imageHeight_;y++) {
		//copy back the original bits, moving over by one spot
		oldBits = buf;
		oldBits += moveOverIncr + (y * fullLineIncr);
		memcpy( oldBits, tmpBits, tmpLineIncr );

		//copy over the inserted image bits
		oldBits = buf;
		oldBits += indexIncr + (y * fullLineIncr);
		memcpy( oldBits, tmpBitsPtr, tmpLineIncr );
		tmpBitsPtr += tmpLineIncr;
	}

	delete [] tmpBits;

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_ADDED, newImage );
	event.setIndexOfImage( index );
	ImageAdded( &event );
}

void ImageList::deleteImage( const uint32 & index )
{
	int incr  = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;

	int oldImgCount = totalImageCount_;

	int tmpSize = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * (oldImgCount-(index+1));
	//save off the old section of the
	//image that will have to be moved over
	unsigned char* tmpBits = new unsigned char[tmpSize];
	unsigned char* oldBits = (unsigned char*)masterImage_->getData();
	oldBits += incr;
	memcpy( tmpBits, oldBits, tmpSize );

	totalImageCount_--;
	//resize the image if neccessary
	if ( (totalImageCount_ % imageCount_) == resizeIncrement_ ) {
		//resize the master image
		imageCount_ -= resizeIncrement_;
		changed();
	}
	//copy back the original bits, moving over by one spot
	int moveOverIncr = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;
	oldBits = (unsigned char*)masterImage_->getData();
	oldBits += moveOverIncr;
	memcpy( oldBits, tmpBits, tmpSize );
	delete [] tmpBits;

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_DELETED );
	event.setIndexOfImage( index );
	ImageAdded( &event );
}

void ImageList::draw( GraphicsContext* context, const uint32& index, Point* pt )
{
	if ( index >= totalImageCount_ ) {
		return;
	}

	Rect bounds( index * imageWidth_, 0, index * imageWidth_ + imageWidth_, imageHeight_ );
	masterImage_->setIsTransparent( true );
	masterImage_->setTransparencyColor( &transparentColor_ );
	context->drawPartialImage( pt->x_, pt->y_, &bounds, masterImage_ );
}

void ImageList::draw( GraphicsContext* context, const uint32& index, Rect* bounds )
{
	if ( index >= totalImageCount_ ) {
		return;
	}

	double w = minVal<double>( bounds->getWidth(), imageWidth_ );
	double h = minVal<double>( bounds->getHeight(), imageHeight_ );
	Rect tmpBounds( index * imageWidth_, 0, index * imageWidth_ + w, h );
	masterImage_->setIsTransparent( true );
	masterImage_->setTransparencyColor( &transparentColor_ );
	//context->drawImage( bounds->left_, bounds->top_, masterImage_ );
	context->drawPartialImage( bounds->left_, bounds->top_, &tmpBounds, masterImage_ );
}

void ImageList::copyImage( Image* imageToCopyTo, const uint32& index )
{
	int incr  = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;
	unsigned char* buf = (unsigned char*)masterImage_->getData();
	buf += incr;
	unsigned char* copyBuf = (unsigned char*)imageToCopyTo->getData();
	memcpy( copyBuf, buf, (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) );
}

void ImageList::changed()
{
	Image* oldImage = masterImage_;


	masterImage_ = GraphicsToolkit::createImage( imageWidth_ * imageCount_, imageHeight_ );
	if ( NULL == masterImage_ ) {
		throw InvalidImage( "Toolkit couldn't create Image" );
	}

	if ( NULL != oldImage ) {
		ColorPixels oldPix(oldImage);
		SysPixelType* oldBits = oldPix;
		int32 oldWidth = oldImage->getWidth();
		int32 oldHeight = oldImage->getHeight();

		ColorPixels masterPix(masterImage_);
		SysPixelType* newBits = masterPix;
		int32 newWidth = masterImage_->getWidth();

		uint32 size = minVal<uint32>( oldWidth,newWidth );

		for ( uint32 i=0;i<imageHeight_;i++ ){
			if ( i < oldHeight ) {
				memcpy( newBits, oldBits, size * sizeof(SysPixelType) );
				oldBits +=  oldWidth;
				newBits += newWidth;
			}
			else {
				break;
			}
		}

		delete oldImage;
		oldImage = NULL;
	}
}

void ImageList::afterCreate( ComponentEvent* event )
{

}


/**
$Id$
*/
