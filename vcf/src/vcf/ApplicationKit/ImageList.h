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
	//ImageList( Image* listOfImages, const uint32& imageWidth, const uint32& imageHeight );

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
	DELEGATE(ImageListDelegate,SizeChanged)

	/**
	@delegate ImageAdded this is fired when a new image is added.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_ADDED
	@see addImage
	@see insertImage
	*/
	DELEGATE(ImageListDelegate,ImageAdded)

	/**
	@delegate ImageDeleted this is fired after an image has been removed from the image list.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_DELETED
	@see deleteImage
	*/
	DELEGATE(ImageListDelegate,ImageDeleted)

	/**
	*returns the width of each image in the list, <b><i>NOT</i></b>
	*the width of the list itself. All images in the list
	*will have the same width and height.
	*/
	uint32 getImageWidth();

	/**
	*returns the height of an image in the list.
	*All images in the list will have the same width and height.
	*/
	uint32 getImageHeight();

	void setImageWidth( const uint32& width );

	void setImageHeight( const uint32& height );

	void setTransparentColor( Color* color );

	Color* getTransparentColor();

	void addImage( Image* newImage );

	void insertImage( const uint32 & index, Image* newImage );

	void deleteImage( const uint32 & index );

	virtual void draw( GraphicsContext* context, const uint32& index, Point* pt );

	/**
	*Draws the image within the bounds specified in bounds. Where the bounds->left_ and top_
	*represent the upper left and top coords. If the boudns width or height is less than the
	*images, then clipping occurs
	*/
	virtual void draw( GraphicsContext* context, const uint32& index, Rect* bounds );

	void copyImage( Image* imageToCopyTo, const uint32& index );

	void setResizeIncrement( const uint32& resizeIncrement ) {
		resizeIncrement_ = resizeIncrement;
	}

	virtual void afterCreate( ComponentEvent* event );

	uint32 getImageCount() {
		return totalImageCount_;
	}

	Image* getMasterImage() {
		return masterImage_;
	}

	virtual void handleEvent( Event* event );
private:
	void changed();

private:
	uint32 imageWidth_;
	uint32 imageHeight_;
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
	uint32 resizeIncrement_;
};


}; // namespace VCF


#endif // _VCF_IMAGELIST_H__

/**
$Id$
*/
