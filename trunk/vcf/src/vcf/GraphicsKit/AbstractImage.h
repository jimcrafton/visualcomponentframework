#ifndef _VCF_ABSTRACTIMAGE_H__
#define _VCF_ABSTRACTIMAGE_H__
//AbstractImage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

//class ImageBits;
class GraphicsContext;

/**
\class AbstractImage AbstractImage.h "vcf/GraphicsKit/AbstractImage.h"
AbstractImage represents a base implementation of the Image interface. It implements
common functions, such as getWidth, etc, but still requires actually image class to be
derived from it. It also provides basic support for ImageSizeChangedHandlers, so derived classes
do not have to baother with it. See Image for more information on what the functions do.

@version 1.0
@author Jim Crafton
@see Image
@delegates
	@del AbstractImage::ImageSizeChanged
*/
class GRAPHICSKIT_API AbstractImage : public Image , public Object, public Persistable {
public:

	AbstractImage( const bool& needsMemAlloc=true );

	virtual ~AbstractImage();


	virtual void setSize( const uint32 & width, const uint32 & height );

    virtual uint32 getWidth();

    virtual uint32 getHeight();

	/**
	@delegate ImageSizeChanged this is fired when the image's dimensions are changed
	by calling setSize().
	@event ImageEvent
	@eventtype IMAGE_EVENT_WIDTH_CHANGED
	@eventtype IMAGE_EVENT_HEIGHT_CHANGED
	@see setSize()
	*/
    DELEGATE(ImageDelegate,ImageSizeChanged);

	/**
	*This macro creates a method for adding a listener to the AbstractImage's ImageSizeChangedHandler events
	*/
	virtual void addImageSizeChangedHandler( EventHandler* handler ) {
		ImageSizeChanged += handler;
	}

	/**
	*This macro creates a method for removing a listener to the AbstractImage's ImageSizeChangedHandler events
	*/
	virtual void removeImageSizeChangedHandler( EventHandler* handler ) {
		ImageSizeChanged.remove( handler );
	}

    virtual GraphicsContext* getImageContext();

	//virtual ImageBits* getImageBits();

	/**
	*returns the color that is used to blend with the contents of
	*a GraphicsContext when the Image is drawn. Only used when the
	*Image is set to Transparent
	*/
	virtual Color* getTransparencyColor() {
		return &transparencyColor_;
	}

	virtual void setTransparencyColor( Color* transparencyColor ) {
		transparencyColor_ = *transparencyColor;
	}

	/**
	*Indicates whether or not the Image is using a transparent
	*color.
	*@return bool if this is true then the Image is transparent
	*and the contents of the underlying GraphicsContext will show through
	*wherever a pixel in the image is found that is the transparency color
	*/
	virtual bool isTransparent() {
		return isTransparent_;
	}

	virtual void setIsTransparent( const bool& transparent ) {
		isTransparent_ = transparent;
	}

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );

	virtual Image::ImageType getType() const ;

	virtual Image::ImageChannelSize getChannelSize() const;

	virtual Image::ImageChannelType getChannelType() const ;

	virtual Image::PixelLayoutOrder getPixelLayoutOrder() const ;

	virtual void* getData();
protected:
	//ImageBits* imageBits_;
	unsigned char* dataBuffer_;
	int height_;
    int width_;
	GraphicsContext * context_;
	Color transparencyColor_;
	bool isTransparent_;
	bool needsMemAlloc_;

	/**
	Implementer note: flags_ needs to be intialized in the constructor of the
	platform implementation of the Image class. For Win32 an example might be:
	\code
	ImageBits::Traits::setChannelType( flags_, ImageBits::Traits::getTraitsChannelType() );
	ImageBits::Traits::setChannelSize( flags_, ImageBits::Traits::getTraitsChannelSize() );
	ImageBits::Traits::setImageType( flags_, ImageBits::Traits::getTraitsImageType() );
	ImageBits::Traits::setPixelLayoutOrder( flags_, Image::ploBGRA );
	\endcode
	*/
	ImageDescriptor flags_;

};

};


#endif // _VCF_ABSTRACTIMAGE_H__

/**
$Id$
*/
