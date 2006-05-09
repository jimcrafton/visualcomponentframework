//GTKFont.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;

GTKFont::GTKFont( const String& fontName )
		: fontDescriptor_( 0 )
{
	this->init();
	this->setAttributes( 12.0, false, false, false, false, fontName );
}

GTKFont::GTKFont( const String& fontName, const double& pointSize )
		: fontDescriptor_( 0 )
{
	this->init();
	this->setAttributes( pointSize, false, false, false, false, fontName );
}

GTKFont::~GTKFont()
{
	pango_font_description_free( fontDescriptor_ );
}

void GTKFont::init()
{
	fontDescriptor_ = pango_font_description_new();
}

OSHandleID GTKFont::getFontHandleID()
{
	return fontDescriptor_;
}

String GTKFont::getName()
{
	const char * name = pango_font_description_get_family( fontDescriptor_ );
	if ( name ) {
		return String( name );
	}
	return String();
}

void GTKFont::setName( const String& name )
{
	String lowerCaseName = StringUtils::lowerCase( name );
	pango_font_description_set_family( fontDescriptor_, lowerCaseName.ansi_c_str() );
}

bool GTKFont::isTrueType()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return true;
}

double GTKFont::getPointSize()
{
	return double( pango_font_description_get_size( fontDescriptor_ )
	               / double( PANGO_SCALE ) );
}

void GTKFont::setPointSize( const double pointSize )
{
	pango_font_description_set_size( fontDescriptor_,
	                                 int( pointSize * PANGO_SCALE ) );
}

double GTKFont::getPixelSize()
{
	double ptSize = double( pango_font_description_get_size( fontDescriptor_ ) )
	                / double( PANGO_SCALE );

	return ( ptSize / 72.0 )
	       * GraphicsToolkit::internal_getDefaultGraphicsToolkit() ->getDPI();
}

void GTKFont::setPixelSize( const double pixelSize )
{
	pango_font_description_set_size(
	    fontDescriptor_,
	    int( pixelSize
	         * GraphicsToolkit::internal_getDefaultGraphicsToolkit() ->getDPI()
	         * 72.0 ) );
}

void GTKFont::setBold( const bool& bold )
{
	pango_font_description_set_weight( fontDescriptor_,
	                                   ( bold )
	                                   ? PANGO_WEIGHT_BOLD
	                                   : PANGO_WEIGHT_NORMAL );
}

bool GTKFont::getBold()
{
	return ( pango_font_description_get_weight( fontDescriptor_ )
	         >= PANGO_WEIGHT_BOLD )
	       ? true
	       : false;
}

bool GTKFont::getItalic()
{
	return ( pango_font_description_get_style( fontDescriptor_ )
	         == PANGO_STYLE_NORMAL )
	       ? false
	       : true;
}

void GTKFont::setItalic( const bool& italic )
{
	pango_font_description_set_style( fontDescriptor_,
	                                  ( italic )
	                                  ? PANGO_STYLE_ITALIC
	                                  : PANGO_STYLE_NORMAL );
}

bool GTKFont::getUnderlined()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return false;
}

void GTKFont::setUnderlined( const bool& underlined )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

bool GTKFont::getStrikeOut()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return false;
}

void GTKFont::setStrikeOut( const bool& strikeout )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

// double GTKFont::getShear()
// {
// 	return 0.0;
// }
//
// void GTKFont::setShear( const double& shear )
// {}
//
// double GTKFont::getAngle()
// {
// 	return 0.0;
// }
//
// void GTKFont::setAngle( const double& angle )
// {}

void GTKFont::setAttributes( const double& pointSize,
                             const bool& bold,
                             const bool& italic,
                             const bool& underlined,
                             const bool& struckOut,
                             //const double& shear,
                             //const double& angle,
                             const String& name )

{
	pango_font_description_set_size( fontDescriptor_,
	                                 int( pointSize	* PANGO_SCALE ) );
	pango_font_description_set_weight( fontDescriptor_,
	                                   ( bold )
	                                   ? PANGO_WEIGHT_BOLD
	                                   : PANGO_WEIGHT_NORMAL );
	pango_font_description_set_style( fontDescriptor_,
	                                  ( italic )
	                                  ? PANGO_STYLE_ITALIC
	                                  : PANGO_STYLE_NORMAL );
	String lowerCaseName = StringUtils::lowerCase( name );
	pango_font_description_set_family( fontDescriptor_,
	                                   lowerCaseName.ansi_c_str() );
}

double GTKFont::getAscent()
{
	double result = 0.0;
	PangoFontMetrics* pfm = 0;

	GTKGraphicsToolkit* toolkit = ( GTKGraphicsToolkit* ) GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(), fontDescriptor_, 0 );

	if ( 0 != pfm ) {
		result = PANGO_PIXELS( pango_font_metrics_get_ascent( pfm ) );
		pango_font_metrics_unref( pfm );
	}

	return result;
}

double GTKFont::getDescent()
{
	GTKGraphicsToolkit * toolkit =
	    static_cast<GTKGraphicsToolkit*>(
	        GraphicsToolkit::internal_getDefaultGraphicsToolkit() );

	PangoFontMetrics* pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(),
	                                                   fontDescriptor_,
	                                                   0 );
	double result = 0.0;
	if ( pfm ) {
		result = PANGO_PIXELS( pango_font_metrics_get_descent( pfm ) );
		pango_font_metrics_unref( pfm );
	}
	return result;
}

// double GTKFont::getExternalLeading()
// {
// 	return 0.0;
// }
//
// double GTKFont::getInternalLeading()
// {
// 	return 0.0;
// }
//
// double GTKFont::getHeight()
// {
// 	double result = 0.0;
// 	PangoFontMetrics* pfm = 0;
//
// 	GTKGraphicsToolkit* toolkit = ( GTKGraphicsToolkit* ) GraphicsToolkit::internal_getDefaultGraphicsToolkit();
// 	pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(), fontDescriptor_, 0 );
//
// 	if ( 0 != pfm ) {
// 		result = PANGO_PIXELS( pango_font_metrics_get_descent( pfm ) );
// 		result += PANGO_PIXELS( pango_font_metrics_get_ascent( pfm ) );
// 		pango_font_metrics_unref( pfm );
// 	}
//
// 	return result;
// }
//
// VCFChar GTKFont::getWordBreakCharacter()
// {
// 	return ' ';
// }
//
// VCFChar GTKFont::getFirstCharacter()
// {
// 	return 0;
// }
//
// VCFChar GTKFont::getLastCharacter()
// {
// 	return 0xff;
// }

GlyphCollection* GTKFont::getGlyphCollection( const String& text )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0;
}

bool GTKFont::isFixedPitch()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return true;
}

// bool GTKFont::isEqual( Object* object )
// {
// 	return false;
// }


void GTKFont::setFont( Font* font )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

/**
$Id$
*/
