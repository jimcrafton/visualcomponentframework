#ifndef _VCF_WIN32GRAPHICSTOOLKIT_H__
#define _VCF_WIN32GRAPHICSTOOLKIT_H__
//Win32GraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
*Class Win32GraphicsToolkit documentation
*/
class Win32GraphicsToolkit : public GraphicsToolkit {
public:
	Win32GraphicsToolkit();

	virtual ~Win32GraphicsToolkit();

	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual Font* internal_getDefaultSystemFont() {
		return systemFont_;
	}

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );

	virtual void internal_systemSettingsChanged();
protected:
	void initSystemFont();
	void loadSystemColors();
	Font* systemFont_;
private:
};


}; //end of namespace VCF


#endif // _VCF_WIN32GRAPHICSTOOLKIT_H__

/**
$Id$
*/
