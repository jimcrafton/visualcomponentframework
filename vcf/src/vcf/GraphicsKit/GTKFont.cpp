//GTKFont.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;

GTKFont::GTKFont( const String& fontName ):
	fontDescriptor_(NULL)
{
	init();
	setAttributes( 12.0, false, false, false, false, 0.0, 0.0, fontName );
}

GTKFont::GTKFont( const String& fontName, const double& pointSize ):
	fontDescriptor_(NULL)
{
	init();
	setAttributes( pointSize, false, false, false, false, 0.0, 0.0, fontName );
}

GTKFont::~GTKFont()
{
	pango_font_description_free( fontDescriptor_ );
}

void GTKFont::init()
{
	fontDescriptor_ = pango_font_description_new();
}

ulong32 GTKFont::getFontHandleID()
{
	return (ulong32)fontDescriptor_;
}

String GTKFont::getName()
{
	String result;

	const char* name = pango_font_description_get_family( fontDescriptor_ );
	if ( NULL != name ) {
		result = name;
	}

	return result;
}

void GTKFont::setName( const String& name )
{
	String lowerCaseName = StringUtils::lowerCase( name );
	pango_font_description_set_family( fontDescriptor_, lowerCaseName.ansi_c_str() );
}

bool GTKFont::isTrueType()
{
	return true;
}

double GTKFont::getPointSize()
{
	return (double)pango_font_description_get_size( fontDescriptor_ ) / (double)PANGO_SCALE;
}

void GTKFont::setPointSize( const double pointSize )
{
	pango_font_description_set_size( fontDescriptor_, (int)pointSize * PANGO_SCALE );
}

double GTKFont::getPixelSize()
{
	double ptSize = (double)pango_font_description_get_size( fontDescriptor_ ) / (double)PANGO_SCALE;

	return (ptSize / 72.0) * GraphicsToolkit::internal_getDefaultGraphicsToolkit()->getDPI();
}

void GTKFont::setPixelSize( const double pixelSize )
{
	pango_font_description_set_size( fontDescriptor_,
				(int)(pixelSize * GraphicsToolkit::internal_getDefaultGraphicsToolkit()->getDPI() * 72.0)  );
}

void GTKFont::setBold( const bool& bold )
{
	pango_font_description_set_weight( fontDescriptor_, bold ? PANGO_WEIGHT_BOLD : PANGO_WEIGHT_NORMAL );
}

bool GTKFont::getBold()
{
	return (pango_font_description_get_weight( fontDescriptor_ ) >= PANGO_WEIGHT_BOLD) ? true : false;
}

bool GTKFont::getItalic()
{
	return (pango_font_description_get_style( fontDescriptor_ ) == PANGO_STYLE_NORMAL) ? false : true;
}

void GTKFont::setItalic( const bool& italic )
{
	pango_font_description_set_style( fontDescriptor_, italic ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL );
}

bool GTKFont::getUnderlined()
{
	return false;
}

void GTKFont::setUnderlined( const bool& underlined )
{

}

bool GTKFont::getStrikeOut()
{
	return false;
}

void GTKFont::setStrikeOut( const bool& strikeout )
{

}

double GTKFont::getShear()
{
	return 0.0;
}

void GTKFont::setShear(const double& shear )
{

}

double GTKFont::getAngle()
{
	return 0.0;
}

void GTKFont::setAngle( const double& angle )
{

}

void GTKFont::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
				const bool& underlined, const bool& struckOut, const double& shear,
				const double& angle, const String& name )

{
	pango_font_description_set_size( fontDescriptor_, (int)pointSize * PANGO_SCALE );
	pango_font_description_set_weight( fontDescriptor_, bold ? PANGO_WEIGHT_BOLD : PANGO_WEIGHT_NORMAL );
	pango_font_description_set_style( fontDescriptor_, italic ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL );
	String lowerCaseName = StringUtils::lowerCase( name );
	pango_font_description_set_family( fontDescriptor_, lowerCaseName.ansi_c_str() );
}

double GTKFont::getAscent()
{
	double result =  0.0;
	PangoFontMetrics* pfm = NULL;

	GTKGraphicsToolkit* toolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(), fontDescriptor_, NULL );

	if ( NULL != pfm ) {
		result = PANGO_PIXELS( pango_font_metrics_get_ascent( pfm ) );
		pango_font_metrics_unref( pfm );
	}

	return result;
}

double GTKFont::getDescent()
{
	double result =  0.0;
	PangoFontMetrics* pfm = NULL;

	GTKGraphicsToolkit* toolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(), fontDescriptor_, NULL );

	if ( NULL != pfm ) {
		result = PANGO_PIXELS( pango_font_metrics_get_descent( pfm ) );
		pango_font_metrics_unref( pfm );
	}

	return result;
}

double GTKFont::getExternalLeading()
{
	return 0.0;
}

double GTKFont::getInternalLeading()
{
	return 0.0;
}

double GTKFont::getHeight()
{
	double result =  0.0;
	PangoFontMetrics* pfm = NULL;

	GTKGraphicsToolkit* toolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	pfm = pango_context_get_metrics( toolkit->getGTKPangoContext(), fontDescriptor_, NULL );

	if ( NULL != pfm ) {
		result = PANGO_PIXELS( pango_font_metrics_get_descent( pfm ) );
		result += PANGO_PIXELS( pango_font_metrics_get_ascent( pfm ) );
		pango_font_metrics_unref( pfm );
	}

	return result;
}

VCFChar GTKFont::getWordBreakCharacter()
{
	return ' ';
}

VCFChar GTKFont::getFirstCharacter()
{
	return 0;
}

VCFChar GTKFont::getLastCharacter()
{
	return 0xff;
}

GlyphCollection* GTKFont::getGlyphCollection( const String& text )
{
	return NULL;
}

bool GTKFont::isEqual( Object* object )
{
	return false;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.3  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.1  2003/04/14 19:06:26  ddiego
*mods to add better support for fonts and text using Pango. Not
*finished and may not compile! :)
*
*Revision 1.2  2003/02/26 04:30:48  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/20 02:46:03  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
Auto generated C++ implementation for class GTKFont
*/


