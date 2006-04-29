#ifndef _VCF_X11FONT_H__
#define _VCF_X11FONT_H__
//X11Font.h

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
	This is the imlib2 font header (I got this from the test example that comes with the
	code. This probably will change (?), need to find this out, as well as is it possible to get
	the raw handle that freetype uses.
*/
class ImlibFontHdr {
public:
	ImlibFontHdr() :
			type(0),
			next(NULL),
			name(NULL),
			ref(0),
			font_count(0),
			font_struct(NULL),
			font_name(NULL),
			ascent(0),
			descent(0),
			max_ascent(0),
			max_descent(0),
			max_width(0),
			ttf(NULL)	{

		memset( &xfontset, 0, sizeof(XFontSet) );

	};

	int	type;
	ImlibFontHdr  *next;
	char	*name;
	int	ref;
	XFontSet xfontset;
	int font_count;
	XFontStruct **font_struct;
	char **font_name;
	int ascent;
	int descent;
	int max_ascent;
	int max_descent;
	int	max_width;
	ImlibFontHdr  *ttf;
};

class GRAPHICSKIT_API X11Font : public FontPeer , public Object {
public:
	X11Font( const String& fontName );

	X11Font( const String& fontName, const double& pointSize );

	virtual ~X11Font();

	void init();

	/**
	*returns a integer representing some native handle to a font structure.
	*What this actually is depends on the Windowing system implementation.
	*Under Win32 this represents a pointer to a LOGFONT structure.
	*/
	virtual ulong32 getFontHandleID() ;

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

	virtual double getShear() ;

	virtual void setShear(const double& shear );

	virtual double getAngle() ;

	virtual void setAngle( const double& angle );

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
					const bool& underlined, const bool& struckOut, const double& shear,
					const double& angle, const String& name );

	virtual double getAscent() ;

	virtual double getDescent() ;

	virtual double getExternalLeading() ;

	virtual double getInternalLeading() ;

	virtual double getHeight() ;

	virtual VCFChar getWordBreakCharacter() ;

	virtual VCFChar getFirstCharacter() ;

	virtual VCFChar getLastCharacter() ;


	/**
	*returns a GlyphCollection that represents the set of shapes
	*for the specified text string.
	*@param String text - the group of characters to put in the GlyphCollection
	*@return GlyphCollection the collection of Glyphs, or vectorized shapes that
	*represent the text string.
	*/
	virtual GlyphCollection* getGlyphCollection( const String& text ) ;

	virtual bool isEqual( Object* object );
protected:
	double shear_;
	double pointSize_;
	String fontName_;
	void updateTextMetrics();

	Imlib_Font imFont_;
	ImlibFontHdr* fontInfo_;
	String fontString_;
	void updateFont();
};

}; //end of namespace VCF


#endif // _VCF_X11FONT_H__

/**
$Id$
*/
