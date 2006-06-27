#ifndef _VCF_GTKIMAGE_H__
#define _VCF_GTKIMAGE_H__
//GTKImage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**

*/
class GTKImage : public AbstractImage {
public:

	GTKImage( const String& fileName );

	GTKImage( const uint32& width, const uint32& height );

	GTKImage( GraphicsContext* context, Rect* rect );

	virtual ~GTKImage();

	void init();

	virtual void beginDrawing();

	virtual void finishedDrawing();

	virtual void setWidth( const uint32 & width );

	virtual void setHeight( const uint32 & height );

	GdkDrawable* getDrawable() {
		return pixmap_;
	}

	GdkPixbuf* getPixbuf() {
		return pixBuf_;
	}

	void updatePixmapFromImageBits();

	void updateImageBitsFromPixmap();
protected:
	void createImage( const uint32 & width, const uint32 & height );
	GdkDrawable* pixmap_;
	GdkPixbuf* pixBuf_;
	GdkBitmap* bitmap_;
};


};


#endif // _VCF_GTKIMAGE_H__

/**
$Id$
*/
