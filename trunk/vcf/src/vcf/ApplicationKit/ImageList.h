#ifndef _VCF_IMAGELIST_H__
#define _VCF_IMAGELIST_H__
//ImageList.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define IMAGELIST_CLASSID				"2EA88629-682F-4b01-BB6F-9990BCF67DD6"

class Image;

class GraphicsContext;

/**
\class ImageList ImageList.h "vcf/ApplicationKit/ImageList.h"
An image list is a collection of images.
The image list is used by controls like the TreeControl, ListViewControl, and
others. The collection of images is implemented by storing them on one single
image.
@delegates
	@del ImageList::SizeChanged
	@del ImageList::ImageAdded
	@del ImageList::ImageDeleted
*/
class APPLICATIONKIT_API ImageList : public Component{
public:


	ImageList();

	ImageList( Component* owner );

	ImageList( const String& name, Component* owner );

	ImageList( const String& name );

	/**
	*Creates a new imagelist from a Image and the
	*appropriate width and height.
	*/
	//ImageList( Image* listOfImages, const unsigned long& imageWidth, const unsigned long& imageHeight );

	virtual ~ImageList();

	void init();

	/**
	@delegate SizeChanged is fired when the size of teh image list changes. This
	happens whenever the setImageWidth() or setImageHeight() methods are called.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_WIDTH_CHANGED
	@eventtype IMAGELIST_EVENT_HEIGHT_CHANGED
	@see setImageWidth
	@see setImageHeight
	*/
	DELEGATE(SizeChanged)

	/**
	@delegate ImageAdded this is fired when a new image is added.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_ADDED
	@see addImage
	@see insertImage
	*/
	DELEGATE(ImageAdded)

	/**
	@delegate ImageDeleted this is fired after an image has been removed from the image list.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_DELETED
	@see deleteImage
	*/
	DELEGATE(ImageDeleted)

	/**
	*returns the width of each image in the list, <b><i>NOT</i></b>
	*the width of the list itself. All images in the list
	*will have the same width and height.
	*/
	unsigned long getImageWidth();

	/**
	*returns the height of an image in the list.
	*All images in the list will have the same width and height.
	*/
	unsigned long getImageHeight();

	void setImageWidth( const unsigned long& width );

	void setImageHeight( const unsigned long& height );

	void setTransparentColor( Color* color );

	Color* getTransparentColor();

	void addImage( Image* newImage );

	void insertImage( const unsigned long & index, Image* newImage );

	void deleteImage( const unsigned long & index );

	virtual void draw( GraphicsContext* context, const unsigned long& index, Point* pt );

	/**
	*Draws the image within the bounds specified in bounds. Where the bounds->left_ and top_
	*represent the upper left and top coords. If the boudns width or height is less than the
	*images, then clipping occurs
	*/
	virtual void draw( GraphicsContext* context, const unsigned long& index, Rect* bounds );

	void copyImage( Image* imageToCopyTo, const unsigned long& index );

	void setResizeIncrement( const ulong32& resizeIncrement ) {
		resizeIncrement_ = resizeIncrement;
	}

	virtual void afterCreate( ComponentEvent* event );

	uint32 getImageCount() {
		return totalImageCount_;
	}

	Image* getMasterImage() {
		return masterImage_;
	}

private:
	void changed();

private:
	unsigned long imageWidth_;
	unsigned long imageHeight_;
	Color transparentColor_;

	/**
	*this represents the number of images the masterImage_
	*can hold
	*/
	uint32 imageCount_;

	/**
	*this represents the number of images actually
	*displayed within the masterImage_
	*/
	uint32 totalImageCount_;
	Image* masterImage_;
	ulong32 resizeIncrement_;
};


}; // namespace VCF


#endif // _VCF_IMAGELIST_H__

/**
$Id$
*/
