#ifndef _VCF_GTKFONT_H__
#define _VCF_GTKFONT_H__ 
//GTKFont.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

/**
 
*/
class GTKFont : public Object, public FontPeer
{
public:
	GTKFont( const String& fontName );

	GTKFont( const String& fontName, const double& pointSize );

	virtual ~GTKFont();

	void init();

	virtual OSHandleID getFontHandleID();

	virtual String getName();

	virtual void setName( const String& name );

	virtual bool isTrueType();

	virtual double getPointSize();

	virtual void setPointSize( const double pointSize );

	virtual double getPixelSize();

	virtual void setPixelSize( const double pixelSize );

	virtual void setBold( const bool& bold );

	virtual bool getBold();

	virtual bool getItalic();

	virtual void setItalic( const bool& italic );

	virtual bool getUnderlined();

	virtual void setUnderlined( const bool& underlined );

	virtual bool getStrikeOut();

	virtual void setStrikeOut( const bool& strikeout );

	//virtual double getShear();

	//virtual void setShear( const double& shear );

	//virtual double getAngle();

	//virtual void setAngle( const double& angle );
	
	virtual void setAttributes( const double& pointSize,
	                            const bool& bold,
	                            const bool& italic,
	                            const bool& underlined,
	                            const bool& struckOut,
	                            //const double& shear,
	                            //const double& angle,
	                            const String& name );

	virtual double getAscent();

	virtual double getDescent();

	//virtual double getExternalLeading();

	//virtual double getInternalLeading();

	//virtual double getHeight();

	//virtual VCFChar getWordBreakCharacter();

	//virtual VCFChar getFirstCharacter();

	//virtual VCFChar getLastCharacter();

	virtual GlyphCollection* getGlyphCollection( const String& text );

	virtual bool isFixedPitch();

	virtual void setFont( Font* font );

	//virtual bool isEqual( Object* object );

	PangoFontDescription* getPangoFontDescription()
	{
		return fontDescriptor_;
	}
protected:
	PangoFontDescription* fontDescriptor_;
};

}


#endif // _VCF_GTKFONT_H__

/**
$Id$
*/
