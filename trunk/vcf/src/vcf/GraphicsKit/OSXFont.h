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

	virtual ulong32 getFontHandleID() ;

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

	virtual VCF::GlyphCollection* getGlyphCollection( const String& text )  ;

	virtual bool isEqual( Object* object );
	
	virtual void setFont( Font* font );

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

	void initATSUAttrs();
	void updateStyleWithAttrs();
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.5  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/31 13:20:59  ddiego
*more osx updates
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*/


#endif // _VCF_OSXFONT_H__


