#ifndef _VCF_XCBFONTPEER_H__
#define _VCF_XCBFONTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

class XCBFontPeer : public FontPeer {
public:
	XCBFontPeer( const String& fontName );

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

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name );

	virtual double getAscent();

	virtual double getDescent();

	virtual bool isFixedPitch();

	virtual void setFont( Font* font );

};

}; //end of namespace VCF

#endif // _VCF_XCBFONTPEER_H__

/**
$Id$
*/

