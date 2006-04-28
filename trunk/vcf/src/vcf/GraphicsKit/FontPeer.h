#ifndef _VCF_FONTPEER_H__
#define _VCF_FONTPEER_H__
//FontPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class GlyphCollection;

class Color;


/**
\class FontPeer FontPeer.h "vcf/GraphicsKit/FontPeer.h"
*Represents the native windowing system's representation of a Font.
*/
class GRAPHICSKIT_API FontPeer {
public:
	virtual ~FontPeer(){};

	/**
	*returns a integer representing some native handle to a font structure.
	*What this actually is depends on the Windowing system implementation.
	*Under Win32 this represents a pointer to a LOGFONT structure.
	*/
	virtual OSHandleID getFontHandleID()  = 0;

	virtual String getName()  = 0;

	virtual void setName( const String& name ) = 0;

	/**
	*is this font a TrueType font ?
	*/
	virtual bool isTrueType()  = 0;

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
	virtual double getPointSize()  = 0;

	/**
	*sets the point size of the FontPeer
	*/
	virtual void setPointSize( const double pointSize ) = 0;

	virtual double getPixelSize()  = 0;


	virtual void setPixelSize( const double pixelSize ) = 0;

	virtual void setBold( const bool& bold ) = 0;

	virtual bool getBold()  = 0;

	virtual bool getItalic()  = 0;

	virtual void setItalic( const bool& italic ) = 0;

	virtual bool getUnderlined()  = 0;

	virtual void setUnderlined( const bool& underlined ) = 0;

	virtual bool getStrikeOut()  = 0;

	virtual void setStrikeOut( const bool& strikeout ) = 0;
	
	/**
	sets ALL the attributes in one fell swoop
	*/
	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name ) = 0;

	virtual double getAscent() = 0;

	virtual double getDescent() = 0;

	virtual bool isFixedPitch() = 0;	

	virtual void setFont( Font* font ) = 0;
};

};


#endif // _VCF_FONTPEER_H__

/**
$Id$
*/
