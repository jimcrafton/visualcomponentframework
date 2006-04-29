//X11Font.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

using namespace VCF;

X11Font::X11Font( const String& fontName ):
	imFont_(NULL),
	fontInfo_(NULL)
{
	pointSize_ = DEFAULT_FONT_PT_SIZE;
	fontName_ = fontName;

	if ( fontName_.empty() ) {
		//hack here - need a better way
		fontName_ = "ARIAL";
	}

	init();
}

X11Font::X11Font( const String& fontName, const double& pointSize ):
	imFont_(NULL),
	fontInfo_(NULL)
{
	pointSize_ = pointSize;
	fontName_ = fontName;
	init();
}

X11Font::~X11Font()
{
	if ( NULL != imFont_ ) {
		imlib_context_set_font( imFont_ );
		imlib_free_font();
	}
	//X11FontManager::removeFont( this );
}

void X11Font::init()
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	int pixelSize = (int)((pointSize_ / 72.0) * dpi);

	fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

	updateFont();

	//X11FontManager::initializeFont( this );
}

void X11Font::updateFont()
{
	if ( NULL != imFont_ ) {
		imlib_context_set_font( imFont_ );
		imlib_free_font();
	}


	imFont_ = imlib_load_font( fontString_.c_str() );
	//printf( "%p = imlib_load_font( \"%s\" )\n", imFont_, fontString_.c_str() );
	fontInfo_ = (ImlibFontHdr*)imFont_;
	if ( NULL == imFont_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("imlib_load_font() failed to return a valid font handle!") );
	}
}

ulong32 X11Font::getFontHandleID()
{
	return (ulong32)imFont_;
}

bool X11Font::isTrueType()
{
	bool result = true;

	return result;
}



double X11Font::getPointSize()
{

	return pointSize_;
}

void X11Font::setPointSize( const double pointSize )
{
	bool needsUpdate = pointSize_ != pointSize;
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}

	pointSize_ = pointSize;

	if ( true == needsUpdate ) {
		X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		double dpi = toolkit->getDPI();
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();

		//X11FontManager::initializeFont( this );
	}
}

double X11Font::getPixelSize()
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	return (pointSize_ / 72.0) * toolkit->getDPI();
}

void X11Font::setPixelSize( const double pixelSize )
{


	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	double tmp = (pixelSize * 72.0)/ dpi;

	bool needsUpdate = tmp != pointSize_;

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}

	pointSize_ = tmp;

	if ( true == needsUpdate ) {
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();
		//X11FontManager::initializeFont( this );
	}
}

void X11Font::setBold( const bool& bold )
{

	bool needsUpdate = false;//(style != logFont_.lfWeight);

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}


	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getBold()
{
	return false;//
}

bool X11Font::getItalic()
{
	return false ;//
}

void X11Font::setItalic( const bool& italic )
{

	bool needsUpdate = false;
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getUnderlined()
{
	return false;
}

void X11Font::setUnderlined( const bool& underlined )
{

	bool needsUpdate = false;//(lfUnderlined != logFont_.lfUnderline);
	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

bool X11Font::getStrikeOut()
{
	return false;
}

void X11Font::setStrikeOut( const bool& strikeout )
{


	bool needsUpdate = false;//(lfStrikeOut != logFont_.lfStrikeOut);

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}



	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

double X11Font::getShear()
{
	return this->shear_;
}

void X11Font::setShear(const double& shear )
{
	this->shear_ = shear;
}

double X11Font::getAngle()
{
	double tmp = (double)0.0;
	return tmp;
}

void X11Font::setAngle( const double& angle )
{
	bool needsUpdate = false;

	if ( true == needsUpdate ) {
		//X11FontManager::removeFont( this );
	}


	if ( true == needsUpdate ) {
		//X11FontManager::initializeFont( this );
	}
}

String X11Font::getName()
{
	String result = "";

	return fontName_;
}

void X11Font::setName( const String& name )
{
	bool needsUpdating = name != fontName_;
	if ( true == needsUpdating ) {
		//X11FontManager::removeFont( this );
	}

	fontName_ = name;

	if ( true == needsUpdating ) {
		X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		double dpi = toolkit->getDPI();
		int pixelSize = (int)((pointSize_ / 72.0) * dpi);

		fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

		updateFont();
		//X11FontManager::initializeFont( this );
	}
}

GlyphCollection* X11Font::getGlyphCollection( const String& text )
{
	return NULL;
}

bool X11Font::isEqual( Object* object )
{
	bool result = false;
	X11Font* fntObj = dynamic_cast<X11Font*>(object);
	if ( NULL != fntObj ){

		if ( (this->fontName_ == fntObj->fontName_) &&
			 (this->pointSize_ == fntObj->pointSize_) ) {
			result = true;
		}
	}

	return result;
}

void X11Font::updateTextMetrics()
{

}

double X11Font::getAscent()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_ascent();

		imlib_context_set_font( current );
	}
	return result;
}

double X11Font::getDescent()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_descent();

		imlib_context_set_font( current );
	}
	return result;
}

double X11Font::getExternalLeading()
{
	return 0.0;
}

double X11Font::getInternalLeading()
{
	return 0.0;
}

double X11Font::getHeight()
{
	double result = 0.0;

	if ( NULL != imFont_ ) {
		Imlib_Font current = imlib_context_get_font();

		imlib_context_set_font( imFont_ );

		result = (double)imlib_get_font_descent() + (double)imlib_get_font_ascent();

		imlib_context_set_font( current );
	}
	return result;
}

VCFChar X11Font::getWordBreakCharacter()
{
	return ' ';
}

VCFChar X11Font::getFirstCharacter()
{
	return 0;
}

VCFChar X11Font::getLastCharacter()
{
	return 0;
}

void X11Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const double& shear,
								const double& angle, const String& name )
{
	pointSize_ = pointSize;
	fontName_ = name;
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	double dpi = toolkit->getDPI();
	int pixelSize = (int)((pointSize_ / 72.0) * dpi);

	fontString_ = StringUtils::format( "%s/%d", fontName_.c_str(), pixelSize );

	updateFont();

	updateTextMetrics();
}


/**
$Id$
*/
