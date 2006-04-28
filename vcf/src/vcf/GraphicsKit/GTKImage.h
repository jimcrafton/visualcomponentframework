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

	GTKImage( const unsigned long& width, const unsigned long& height );

	GTKImage( GraphicsContext* context, Rect* rect );

	virtual ~GTKImage();

	void init();

	virtual void beginDrawing();

	virtual void finishedDrawing();

	virtual void setWidth( const unsigned long & width );

	virtual void setHeight( const unsigned long & height );

	GdkDrawable* getDrawable() {
		return pixmap_;
	}

	GdkPixbuf* getPixbuf() {
		return pixBuf_;
	}

	void updatePixmapFromImageBits();

	void updateImageBitsFromPixmap();
protected:
	void createImage( const unsigned long & width, const unsigned long & height );
	GdkDrawable* pixmap_;
	GdkPixbuf* pixBuf_;
	GdkBitmap* bitmap_;
};


};


#endif // _VCF_GTKIMAGE_H__

/**
$Id$
*/
