#ifndef _VCF_X11GRAPHICSTOOLKIT_H__
#define _VCF_X11GRAPHICSTOOLKIT_H__
//X11GraphicsToolkit.h

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
*Class X11GraphicsToolkit documentation
*/
class X11GraphicsToolkit : public GraphicsToolkit {
public:
	X11GraphicsToolkit();

	virtual ~X11GraphicsToolkit();

	virtual ContextPeer* createContextPeer( const unsigned long& width, const unsigned long& height );

	virtual ContextPeer* createContextPeer( const long& contextID );

	virtual FontPeer* createFontPeer( const String& fontName );

	virtual FontPeer* createFontPeer( const String& fontName, const double& pointSize );

	virtual OpenGLPeer* createOpenGLPeer( GraphicsContext* glContext );

	virtual Image* createImage( const unsigned long& width, const unsigned long& height );

	virtual Image* createImage( GraphicsContext* context, Rect* rect );

	virtual Font* getDefaultSystemFont() {
		return systemFont_;
	}

	//X11 specific functions

	double getDPI();

	Display* getX11Display() {
		return X11Display_;
	}

	int getX11ScreenID() {
		return X11ScreenID_;
	}

	ulong32 getPixelForColor( Color* color );

	/**
	this should return a path that represents the common font directory available to
	all users. By default this will be in /usr/local/share/fonts unless changed by the
	X11GraphicsToolkit implementation
	*/
	String getSharedFontsPath();

	/**
	this will return a path to the users font directory. Typically this is
	$HOME/fonts
	*/
	String getUserFontsPath();
protected:

	void initSystemFont();
	void loadSystemColors();
	virtual void initSystemFontNames();

	Font* systemFont_;
	Display* X11Display_;
	int X11ScreenID_;

	std::map<ulong32,ulong32> colorLookupMap_;
private:
};


}; //end of namespace VCF


#endif // _VCF_X11GRAPHICSTOOLKIT_H__

/**
$Id$
*/
