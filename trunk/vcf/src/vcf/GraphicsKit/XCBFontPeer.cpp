
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
	pointSize_(12.0)
{

}

OSHandleID XCBFontPeer::getFontHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

String XCBFontPeer::getName()
{
	return fontName_;
}

void XCBFontPeer::setName( const String& name )
{
	fontName_ = name;
}

bool XCBFontPeer::isTrueType()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

double XCBFontPeer::getPointSize()
{
	return pointSize_;
}

void XCBFontPeer::setPointSize( const double pointSize )
{
	pointSize_ = pointSize;
}

double XCBFontPeer::getPixelSize()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

void XCBFontPeer::setPixelSize( const double pixelSize )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBFontPeer::setBold( const bool& bold )
{
	bold_ = bold;
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
}

bool XCBFontPeer::getUnderlined()
{
	return underlined_;
}

void XCBFontPeer::setUnderlined( const bool& underlined )
{
	underlined_ = underlined;
}

bool XCBFontPeer::getStrikeOut()
{
	return strikeOut_;
}

void XCBFontPeer::setStrikeOut( const bool& strikeout )
{
	strikeOut_ = strikeout;
}

void XCBFontPeer::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
							const bool& underlined, const bool& struckOut, const String& name )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

double XCBFontPeer::getAscent()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

double XCBFontPeer::getDescent()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

bool XCBFontPeer::isFixedPitch()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBFontPeer::setFont( Font* font )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

String XCBFontPeer::getHashcode()
{
	String result;
	
	result = fontName_;
	result += Format("%.3f") % pointSize_;
	result += Format("%d") % bold_;
	result += Format("%d") % underlined_;
	result += Format("%d") % italic_;
	result += Format("%d") % strikeOut_;
	
	
	return result;
}

/**
$Id$
*/

