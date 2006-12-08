
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBFontPeer.h"

using namespace VCF;

XCBFontPeer::XCBFontPeer( const String& fontName ):
	fontName_(fontName),
	bold_(false),
	underlined_(false),
	italic_(false),
	strikeOut_(false),
	pointSize_(12.0),
	trueTypeFont_(true),
	fixedPitchFont_(false),
	ascent_(0.0),
	descent_(0.0)
{
	if ( fontName_.empty() ) {
		fontName_ = "Arial";
	}
	settingsChanged();
}

XCBFontPeer::XCBFontPeer( const String& fontName, const double& pointSize ):
	fontName_(fontName),
	bold_(false),
	underlined_(false),
	italic_(false),
	strikeOut_(false),
	pointSize_(pointSize),
	trueTypeFont_(true),
	fixedPitchFont_(false),
	ascent_(0.0),
	descent_(0.0)
{
	if ( fontName_.empty() ) {
		fontName_ = "Arial";
	}
	settingsChanged();
}

OSHandleID XCBFontPeer::getFontHandleID()
{
	return 0;
}

String XCBFontPeer::getName()
{
	return fontName_;
}

void XCBFontPeer::setName( const String& name )
{
	fontName_ = name;
	settingsChanged();
}

bool XCBFontPeer::isTrueType()
{
	return trueTypeFont_;
}

double XCBFontPeer::getPointSize()
{
	return pointSize_;
}

void XCBFontPeer::setPointSize( const double pointSize )
{
	pointSize_ = pointSize;
	settingsChanged();
}

double XCBFontPeer::getPixelSize()
{
	double dpi = GraphicsToolkit::getDPI();
	
	return (pointSize_ / 72.0) * dpi;
}

void XCBFontPeer::setPixelSize( const double pixelSize )
{
	double dpi = GraphicsToolkit::getDPI();
	
	pointSize_ = (pixelSize * 72.0) / dpi;
	
	settingsChanged();
}

void XCBFontPeer::setBold( const bool& bold )
{
	bold_ = bold;
	settingsChanged();
}

bool XCBFontPeer::getBold()
{
	return bold_;
}

bool XCBFontPeer::getItalic()
{
	return italic_;
}

void XCBFontPeer::setItalic( const bool& italic )
{
	italic_ = italic;
	settingsChanged();
}

bool XCBFontPeer::getUnderlined()
{
	return underlined_;
}

void XCBFontPeer::setUnderlined( const bool& underlined )
{
	underlined_ = underlined;
	settingsChanged();
}

bool XCBFontPeer::getStrikeOut()
{
	return strikeOut_;
}

void XCBFontPeer::setStrikeOut( const bool& strikeout )
{
	strikeOut_ = strikeout;
	settingsChanged();
}

void XCBFontPeer::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
							const bool& underlined, const bool& struckOut, const String& name )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	
	pointSize_ = pointSize;
	bold_ = bold;
	underlined_ = underlined;
	italic_ = italic;
	strikeOut_ = struckOut;
	fontName_ = name;
	
	settingsChanged();
}

double XCBFontPeer::getAscent()
{
	return ascent_;
}

double XCBFontPeer::getDescent()
{
	return descent_;
}

bool XCBFontPeer::isFixedPitch()
{
	return fixedPitchFont_;
}

void XCBFontPeer::setFont( Font* font )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

String XCBFontPeer::getHashcode()
{
	String result;
	
	VCF_ASSERT( !fontName_.empty() );
	
	result = fontName_;
	result += Format("%.3f") % pointSize_;
	result += Format("%d") % bold_;
	result += Format("%d") % underlined_;
	result += Format("%d") % italic_;
	result += Format("%d") % strikeOut_;
	
	
	return result;
}


void XCBFontPeer::settingsChanged()
{
	XCBGraphicsToolkit::updateFontAttributes( this );
}


/**
$Id$
*/

