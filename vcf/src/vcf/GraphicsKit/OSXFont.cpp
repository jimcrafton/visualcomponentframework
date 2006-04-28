//OSXFont.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"



using namespace VCF;


OSXFont::OSXFont( const String& fontName ):
	fontStyle_(nil),
	attrBold_(FALSE),
	attrItalic_(FALSE),
	attrUnderlined_(FALSE),
    attrFontID_(0),
	font_(NULL)
{
	attrColor_.red = 0;
	attrColor_.green = 0;
	attrColor_.blue = 0;
    attrColor_.alpha = 1.0;

	OSStatus err = ATSUCreateStyle (&fontStyle_);
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUCreateStyle failed to create font style!" ) );
	}

	attrSize_ = IntToFixed((int)12);

	SInt16 iFONDNumber = 0;
    Str255 pStr;
    CopyCStringToPascal( fontName.empty() ? "Arial" : fontName.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);

	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed to create font ID instance!" ) );
	}


	initATSUAttrs();
}

OSXFont::OSXFont( const String& fontName, const double& pointSize ):
	fontStyle_(nil),
	attrBold_(FALSE),
	attrItalic_(FALSE),
	attrUnderlined_(FALSE),
    attrFontID_(0),
	font_(NULL)
{
	attrColor_.red = 0;
	attrColor_.green = 0;
	attrColor_.blue = 0;
    attrColor_.alpha = 1.0;

	OSStatus err = ATSUCreateStyle (&fontStyle_);
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUCreateStyle failed to create font style!" ) );
	}
	SInt16 iFONDNumber = 0;
    Str255 pStr;
    CopyCStringToPascal( fontName.empty() ? "Arial" : fontName.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);

	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed to create font ID instance!" ) );
	}

	attrSize_ = IntToFixed((int)pointSize);

	initATSUAttrs();
}

void OSXFont::initATSUAttrs()
{
	attrSizes_[OSXFont::attrFontName] = sizeof(ATSUFontID);
	attrSizes_[OSXFont::attrFontSize] = sizeof(Fixed);
	attrSizes_[OSXFont::attrFontBold] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontItalic] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontUnderline] = sizeof(Boolean);
	attrSizes_[OSXFont::attrFontColor] = sizeof(ATSURGBAlphaColor);


	attrValues_[OSXFont::attrFontName] = &attrFontID_;
	attrValues_[OSXFont::attrFontSize] = &attrSize_;
	attrValues_[OSXFont::attrFontBold] = &attrBold_;
	attrValues_[OSXFont::attrFontItalic] = &attrItalic_;
	attrValues_[OSXFont::attrFontUnderline] = &attrUnderlined_;
	attrValues_[OSXFont::attrFontColor] = &attrColor_;

	attrTags_[OSXFont::attrFontName] = kATSUFontTag;
	attrTags_[OSXFont::attrFontSize] = kATSUSizeTag;
	attrTags_[OSXFont::attrFontBold] = kATSUQDBoldfaceTag;
	attrTags_[OSXFont::attrFontItalic] = kATSUQDItalicTag;
	attrTags_[OSXFont::attrFontUnderline] = kATSUQDUnderlineTag;
	attrTags_[OSXFont::attrFontColor] = kATSURGBAlphaColorTag;

	updateStyleWithAttrs();
}

void OSXFont::updateStyleWithAttrs()
{
	OSStatus err = ATSUSetAttributes (fontStyle_,
											OSXFont::tagCount,
											attrTags_,
											attrSizes_,
											attrValues_);

	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("ATSUSetAttributes failed in updateStyleWithAttrs()") );
	}
}

OSXFont::~OSXFont()
{
	if ( nil != fontStyle_ ) {
		ATSUDisposeStyle( fontStyle_ );
	}
}

void OSXFont::init()
{

}

OSHandleID OSXFont::getFontHandleID()
{
	return (OSHandleID)fontStyle_;
}

String OSXFont::getName()
{
	return "FoobarBaz";
}

void OSXFont::setName( const String& name )
{
	SInt16 iFONDNumber = 0;
	Str255 pStr;
    CopyCStringToPascal( name.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
    if ( iFONDNumber != kInvalidFontFamily ) {
        OSStatus err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
        if ( err != noErr ) {
            throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed - probably due to an invalid font name, or perhaps conversion to a Pascal String failed.") );
        }
    }

	updateStyleWithAttrs();
}

void OSXFont::setColor( Color* color )
{
    attrColor_.red = color->getRed();
    attrColor_.green = color->getGreen();
    attrColor_.blue = color->getBlue();
    attrColor_.alpha = 1.0;

    updateStyleWithAttrs();
}

bool OSXFont::isTrueType()
{
	return true;
}

double OSXFont::getPointSize()
{
	return (double) VCF_FIXEDTOINT(attrSize_);
}

void OSXFont::setPointSize( const double pointSize )
{
	attrSize_ = VCF_INTTOFIXED((int)pointSize);

	updateStyleWithAttrs();
}

double OSXFont::getPixelSize()
{
	return (double) VCF_FIXEDTOINT(attrSize_);
}

void OSXFont::setPixelSize( const double pixelSize )
{
	setPointSize( pixelSize );
}

void OSXFont::setBold( const bool& bold )
{
	attrBold_ = bold ? TRUE : FALSE;

	updateStyleWithAttrs();
}

bool OSXFont::getBold()
{
	return (attrBold_ == TRUE) ? true : false;
}

bool OSXFont::getItalic()
{
	return (attrItalic_ == TRUE) ? true : false;
}

void OSXFont::setItalic( const bool& italic )
{
	attrItalic_ = italic ? TRUE : FALSE;

	updateStyleWithAttrs();
}

bool OSXFont::getUnderlined()
{
	return (attrUnderlined_ == TRUE) ? true : false;
}

void OSXFont::setUnderlined( const bool& underlined )
{
	attrUnderlined_ = underlined ? TRUE : FALSE;

	updateStyleWithAttrs();
}

bool OSXFont::getStrikeOut()
{
	return false;
}

void OSXFont::setStrikeOut( const bool& strikeout )
{

}

void OSXFont::setFont( Font* font ) 
{
	font_ = font;
}

void OSXFont::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name )
{
	attrBold_ = bold ? TRUE : FALSE;
	attrItalic_ = italic ? TRUE : FALSE;
	attrUnderlined_ = underlined ? TRUE : FALSE;

	attrSize_ = IntToFixed((int)pointSize);

	SInt16 iFONDNumber = 0;
	Str255 pStr;
    CopyCStringToPascal( name.ansi_c_str(), pStr );
	iFONDNumber = FMGetFontFamilyFromName( pStr );
	if ( iFONDNumber != kInvalidFontFamily ) {
        OSStatus err = ATSUFONDtoFontID(iFONDNumber,  NULL, &attrFontID_);
        if ( err != noErr ) {
            throw RuntimeException( MAKE_ERROR_MSG_2("ATSUFONDtoFontID failed - probably due to an invalid font name, or perhaps conversion to a Pascal String failed.") );
        }
    }

	updateStyleWithAttrs();
}

double OSXFont::getAscent()
{
	ATSUTextMeasurement val = 0;
	ByteCount sz = sizeof(val);
	OSStatus err = ATSUGetAttribute( fontStyle_, kATSUAscentTag, sizeof(val), &val, &sz );
	if ( err != noErr ) {
		return -1.0;
	}
	
	return FixedPointNumber(val);
}

double OSXFont::getDescent()
{
	ATSUTextMeasurement val = 0;
	ByteCount sz = sizeof(val);
	OSStatus err = ATSUGetAttribute( fontStyle_, kATSUDescentTag, sizeof(val), &val, &sz );
	if ( err != noErr ) {
		return -1.0;
	}
	
	return FixedPointNumber(val);
}

bool OSXFont::isFixedPitch()
{
	return false;
}

bool OSXFont::isEqual( Object* object )
{
	bool result = false;
	OSXFont* fntObj = dynamic_cast<OSXFont*>(object);
	if ( NULL != fntObj ){

		if ( (this->attrFontID_ == fntObj->attrFontID_) &&
			 (this->attrBold_ == fntObj->attrBold_) &&
			 (this->attrItalic_ == fntObj->attrItalic_) &&
			 (this->attrUnderlined_ == fntObj->attrUnderlined_) &&
			 (this->attrSize_ == fntObj->attrSize_)  ) {
			result = true;
		}
	}

	return result;
}


/**
$Id$
*/
