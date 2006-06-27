#ifndef _VCF_X11IMAGE_H__
#define _VCF_X11IMAGE_H__
//X11Image.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class GRAPHICSKIT_API X11Image : public AbstractImage
{
public:
	X11Image();

	X11Image( const String& fileName );

	X11Image( const uint32& width, const uint32& height );

	X11Image( GraphicsContext* context, Rect* rect );


	virtual ~X11Image();

	void init();

	virtual void setWidth( const uint32 & width );

	virtual void setHeight( const uint32 & height );

	Imlib_Image getXImage() {
		return ximage_;
	}

	Pixmap getPixMap() {
		return x11ImagePixmap_;
	}

	Pixmap getAlphaMaskPixMap() {
		return x11AlphaMask_;
	}

	void updateImageDataFromImageBits();

	virtual ImageBits* getImageBits();
protected:
	void loadFromFile( const String& fileName );


	void saveToFile( const String& fileName );

	Imlib_Image ximage_;

	Pixmap x11ImagePixmap_;
	Pixmap x11AlphaMask_;

	void createBitmap();
};


class GRAPHICSKIT_API XPMLoader : public Object, public ImageLoader {
public:
	XPMLoader();

	virtual ~XPMLoader();

	virtual Image* loadImageFromFile( const String& fileName );


	virtual void saveImageToFile( const String& fileName, Image* image );

	virtual bool canSaveImage(){
		return true;
	}
private:

};

};


#endif // _VCF_X11IMAGE_H__

/**
$Id$
*/
