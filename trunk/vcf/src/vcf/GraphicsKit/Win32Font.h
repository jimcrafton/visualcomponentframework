#ifndef _VCF_WIN32FONT_H__
#define _VCF_WIN32FONT_H__
//Win32Font.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class GRAPHICSKIT_API Win32Font : public FontPeer  {

public:
	Win32Font( const String& fontName );

	Win32Font( const String& fontName, const double& pointSize );

	virtual ~Win32Font();

	void init();

	/**
	*returns a integer representing some native handle to a font structure.
	*What this actually is depends on the Windowing system implementation.
	*Under Win32 this represents a pointer to a LOGFONT structure.
	*/
	virtual OSHandleID getFontHandleID() ;

	virtual String getName() ;

	virtual void setName( const String& name );

	/**
	*is this font a TrueType font ?
	*/
	virtual bool isTrueType() ;

	/**
	*return the point size of the Font. One point is 1/72 of an inch
	*( or 0.0352552 cm for our more civilized friends !), so to figure
	*out the pixels involved, find out the Pixels per Inch and then apply
	*the following formula
	*<code>
	* (PointSize / 72) * PPI
	*</code>
	*where PPI represents the Pixels Per Inch
	*/
    virtual double getPointSize() ;

	/**
	*sets the point size of the FontPeer
	*/
	virtual void setPointSize( const double pointSize );

	virtual double getPixelSize() ;

	virtual void setPixelSize( const double pixelSize );

    virtual void setBold( const bool& bold );

    virtual bool getBold() ;

    virtual bool getItalic() ;

    virtual void setItalic( const bool& italic );

    virtual bool getUnderlined() ;

    virtual void setUnderlined( const bool& underlined );

    virtual bool getStrikeOut() ;

    virtual void setStrikeOut( const bool& strikeout );

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name );

	virtual double getAscent()  ;

	virtual double getDescent() ;

	virtual bool isFixedPitch();

	virtual Size getTextSize( const String& text );

	virtual void updateLocaleSettings();

	/**
	*returns a GlyphCollection that represents the set of shapes
	*for the specified text string.
	*@param String text - the group of characters to put in the GlyphCollection
	*@return GlyphCollection the collection of Glyphs, or vectorized shapes that
	*represent the text string.
	*/
    virtual GlyphCollection* getGlyphCollection( const String& text )  ;

	virtual bool isEqual( Object* object );

	void setFont( Font* font ) {
		font_ = font;
	}
protected:
	void updateTextMetrics();
	Font* font_;
	void* logFont_;
	void* tm_;
	double pointSize_;
	String fontName_;
	int oldDPI_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32FONT_H__

/**
$Id$
*/
