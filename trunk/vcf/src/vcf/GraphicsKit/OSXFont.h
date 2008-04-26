#ifndef _VCF_OSXFONT_H__
#define _VCF_OSXFONT_H__
//OSXFont.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifdef __OBJC__
	@class NSFont;
	@class NSDictionary;
	@class NSMutableDictionary;
#else
	class NSFont;
	class NSDictionary;
	class NSMutableDictionary;
#endif


namespace VCF {

class OSXFont : public FontPeer , public Object {

public:

	enum {
		attrFontName = 0,
		attrFontSize = 1,
		attrFontBold = 2,
		attrFontItalic = 3,
		attrFontUnderline=4,
		attrFontColor = 5,
		tagCount = 6
	};

	OSXFont( const String& fontName );

	OSXFont( const String& fontName, const double& pointSize );

	virtual ~OSXFont();

	void init();

	virtual OSHandleID getFontHandleID() ;

	virtual String getName() ;

	virtual void setName( const String& name );

	virtual bool isTrueType() ;

	virtual double getPointSize() ;

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

	virtual bool isEqual( Object* object );
	
	virtual void setFont( Font* font );

	virtual Size getTextSize( const String& text );

	virtual void updateLocaleSettings();
	
	ATSUStyle getATSUStyle() {
		return fontStyle_;
	}

	ATSUFontID getATSUFontID() {
		return attrFontID_;
	}
    void setColor( Color* color );
protected:
	double shear_;
	double pointSize_;
	String fontName_;
	ATSUStyle fontStyle_;

	ATSUAttributeTag attrTags_[OSXFont::tagCount];
	ByteCount attrSizes_[OSXFont::tagCount];
	ATSUAttributeValuePtr attrValues_[OSXFont::tagCount];
	Boolean attrBold_;
	Boolean attrItalic_;
	Boolean attrUnderlined_;
	ATSURGBAlphaColor attrColor_;
	ATSUFontID attrFontID_;
	Fixed attrSize_;
	Font* font_;

	void initATSUAttrs();
	void updateStyleWithAttrs();
};

}; //end of namespace VCF


#endif // _VCF_OSXFONT_H__

/**
$Id$
*/
