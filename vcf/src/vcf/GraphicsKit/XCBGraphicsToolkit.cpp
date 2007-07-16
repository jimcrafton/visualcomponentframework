
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/GraphicsKit/XCBFontPeer.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"
#include "vcf/GraphicsKit/XCBGraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/XCBImagePeer.h"

#include "thirdparty/common/agg/include/agg_font_freetype.h"



typedef agg::font_engine_freetype_int32 XCBFontEngineType;
typedef agg::font_cache_manager<XCBFontEngineType> XCBFontManagerType;

namespace VCF {
struct XCBFontEngine {
	XCBFontEngine(): engine(), mgr(engine){}

	XCBFontEngineType engine;
	XCBFontManagerType mgr;
	String prevFontHash;
};

};

using namespace VCF;


static XCBGraphicsToolkit* xcbGraphicsToolkit = NULL;



XCBGraphicsToolkit::XCBGraphicsToolkit() :
connection_(NULL),
screen_(NULL),
fontEngine_(NULL)
{
	connection_ = xcb_connect (NULL, NULL);
	if(connection_ != NULL)
	{
		screen_ = xcb_setup_roots_iterator(xcb_get_setup(connection_)).data;
	}

	fontEngine_ = new XCBFontEngine();

	loadSystemColors();

	xcbGraphicsToolkit = this;
}

XCBGraphicsToolkit::~XCBGraphicsToolkit()
{
    xcb_disconnect(connection_);

    std::map<String,FcPattern*>::iterator it = fontPatternCache_.begin();
	while (  it != fontPatternCache_.end() ) {
		FcPatternDestroy( it->second );
		++it;
	}

	delete fontEngine_;
}

xcb_connection_t* XCBGraphicsToolkit::getConnection()
{
	xcb_connection_t* connection = NULL;

	if(xcbGraphicsToolkit != NULL)
	{
		connection = xcbGraphicsToolkit->connection_;
	}
	return connection;
}

xcb_screen_t*     XCBGraphicsToolkit::getScreen()
{
	xcb_screen_t* screen = NULL;

	if(xcbGraphicsToolkit != NULL)
	{
		screen = xcbGraphicsToolkit->screen_;
	}
	return screen;
}

ContextPeer* XCBGraphicsToolkit::internal_createContextPeer( const uint32& width, const uint32& height )
{
	return new XCBContextPeer( width, height );
}

ContextPeer* XCBGraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	return new XCBContextPeer( contextID );
}

FontPeer* XCBGraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new XCBFontPeer( fontName );
}

FontPeer* XCBGraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	return new XCBFontPeer( fontName, pointSize );
}

Image* XCBGraphicsToolkit::internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	if ( Image::itColor == imageType ) {
		return new XCBImagePeer( width, height );
    }
    else if ( Image::itGrayscale == imageType ) {
        return new XCBGrayscaleImagePeer( width, height );
    }

    return NULL;
}

Image* XCBGraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	if ( NULL != context ){
		if ( Image::itColor == imageType ) {
			return new XCBImagePeer( context, rect );
		}
		else if ( Image::itGrayscale == imageType ) {
			return new XCBGrayscaleImagePeer( context, rect );
		}
	}
	return NULL;
}

PrintSessionPeer* XCBGraphicsToolkit::internal_createPrintSessionPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

GraphicsResourceBundlePeer* XCBGraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new XCBGraphicsResourceBundlePeer();
}

double XCBGraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	double result = (double)screen_->height_in_pixels / (screen_->height_in_millimeters / 25.4);

	return result;
}

void XCBGraphicsToolkit::internal_systemSettingsChanged()
{
	loadSystemColors();
}


FcPattern* XCBGraphicsToolkit::getFontPatternForFont( XCBFontPeer* fontPeer )
{
	FcPattern* result = NULL;

	String hash = fontPeer->getHashcode();
	std::map<String,FcPattern*>::iterator found = xcbGraphicsToolkit->fontPatternCache_.find( hash );
	if (  found != xcbGraphicsToolkit->fontPatternCache_.end() ) {
		result = found->second;
	}
	else {
		FcPattern* pattern = FcPatternCreate();
		AnsiString fontName = fontPeer->getName();
		FcValue name;
		name.type = FcTypeString;
		name.u.s = (const FcChar8*)fontName.c_str();
		FcPatternAdd (pattern, FC_FAMILY, name, true);


		FcValue bold;
		bold.type = FcTypeInteger;
		bold.u.i =  fontPeer->getBold() ? FC_WEIGHT_BOLD : FC_WEIGHT_NORMAL;
		FcPatternAdd (pattern, FC_WEIGHT, bold, true);

		FcValue italic;
		italic.type = FcTypeInteger;
		italic.u.i = fontPeer->getItalic() ? FC_SLANT_ITALIC : FC_SLANT_ROMAN;
		FcPatternAdd (pattern, FC_SLANT, italic, true);

		FcValue trueTypeOnly;
		trueTypeOnly.type = FcTypeString;
		trueTypeOnly.u.s = (const FcChar8*)"TrueType";
		FcPatternAdd (pattern, FC_FONTFORMAT, trueTypeOnly, true);

		if ( FcConfigSubstitute (0, pattern, FcMatchPattern) ) {

			FcChar8 * family=NULL;
			if ( FcResultMatch == FcPatternGetString( pattern, FC_FAMILY, 0, &family ) ) {
				#ifdef _DEBUG
				printf( "FcConfigSubstitute succeeded for %s !!!\n", (NULL != family) ? (const char*)family : "NULL" ) ;
				#endif
			}
			else {
				#ifdef _DEBUG
				printf( "FcConfigSubstitute succeeded but FcPatternGetString() didn't for some reason!!!!!!!\n" );
				#endif
			}


			FcDefaultSubstitute (pattern);
			FcResult rlt = FcResultMatch;
			FcPattern* matchPattern = FcFontMatch (0, pattern, &rlt);
			if ( NULL != matchPattern ) {
				result = matchPattern;
				xcbGraphicsToolkit->fontPatternCache_[hash] = result;

				#ifdef _DEBUG
				printf( "FcFontMatch succeeded for %s !!!\n", fontPeer->getName().ansi_c_str() ) ;


				switch( rlt ) {
					case FcResultMatch : {
						printf( "FcResultMatch - Object exists with the specified ID\n" );
					}
					break;

					case FcResultNoMatch : {
						printf( "FcResultNoMatch - Object doesn't exist at all\n" );
					}
					break;

					case FcResultTypeMismatch : {
						printf( "FcResultTypeMismatch - Object exists, but the type doesn't match\n" );
					}
					break;

					case FcResultNoId : {
						printf( "FcResultNoId - Object exists, but has fewer values than specified\n" );
					}
					break;

					case FcResultOutOfMemory : {
						printf( "FcResultOutOfMemory - Malloc failed\n" );
					}
					break;
				}


				FcChar8 * filename;
				FcChar8 * foundry;

				FcPatternGetString( result, FC_FILE, 0, &filename );
				FcPatternGetString( result, FC_FOUNDRY, 0, &foundry );
				FcPatternGetString( result, FC_FAMILY, 0, &family );

				printf( "Font Info:\n\tfilename : %s\n", filename );
				printf( "\tfoundry : %s\n", foundry );
				printf( "\tfamily : %s\n", family );

				#endif
			}
			else {
				#ifdef _DEBUG
				printf( "FcFontMatch returned NULL pattern for %s !!!\n", fontPeer->getName().ansi_c_str() ) ;
				#endif
			}
		}
		else {
			#ifdef _DEBUG
			printf( "FcConfigSubstitute failed for %s !!!\n", fontPeer->getName().ansi_c_str() ) ;
			#endif
		}

		FcPatternDestroy( pattern );
	}

	return result;
}


void XCBGraphicsToolkit::updateFontAttributes( XCBFontPeer* fontPeer )
{

	String hash = fontPeer->getHashcode();
	if ( xcbGraphicsToolkit->fontEngine_->prevFontHash != hash ) {
		FcPattern* pattern = XCBGraphicsToolkit::getFontPatternForFont( fontPeer );
		VCF_ASSERT( NULL != pattern );
		FcChar8 * filename = NULL;
		FcPatternGetString( pattern, FC_FILE, 0, &filename ); //do we need to release this???


		if ( xcbGraphicsToolkit->fontEngine_->engine.load_font( (const char*)filename, 0, agg::glyph_ren_agg_gray8 ) ) {
			xcbGraphicsToolkit->fontEngine_->prevFontHash = hash;
			xcbGraphicsToolkit->fontEngine_->engine.height( fontPeer->getPixelSize() );
			xcbGraphicsToolkit->fontEngine_->engine.width( fontPeer->getPixelSize() );
			xcbGraphicsToolkit->fontEngine_->engine.hinting( true );
			xcbGraphicsToolkit->fontEngine_->engine.flip_y( true );


			fontPeer->internal_setAscent( fabs( xcbGraphicsToolkit->fontEngine_->engine.ascender() ) );
			fontPeer->internal_setDescent( fabs( xcbGraphicsToolkit->fontEngine_->engine.descender() ) );
		}
		else {
			printf( "Failed to load font \"%s\" in file \"%s\"\n",
					fontPeer->getName().ansi_c_str(), (const char*)filename	);
		}
	}
}

void XCBGraphicsToolkit::loadSystemColors()
{
	printf( "Warning - system colors are hard-coded till GTK theme support is added." );
	Color* sysColor = NULL;
	sysColor = new Color( (unsigned int)0xFF9d9dA1, Color::cpsABGR );
	systemColors_[SYSCOLOR_SHADOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SHADOW";

	sysColor = new Color( (unsigned int)0xeFF0dfe3, Color::cpsABGR );
	systemColors_[SYSCOLOR_FACE] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_FACE";

	sysColor = new Color( (unsigned int)0xFFffffff, Color::cpsABGR );
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_HIGHLIGHT";

	sysColor = new Color( (unsigned int)0xFFc0c0c0, Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_CAPTION";

	sysColor = new Color( (unsigned int)0xFFd4d0c8, Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_BORDER";

	sysColor = new Color( (unsigned int)0xFF585768, Color::cpsABGR );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_DESKTOP";

	sysColor = new Color( (unsigned int)0xFF0e1010, Color::cpsABGR );
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_CAPTION_TEXT";

	sysColor = new Color( (unsigned int)0xFFb2b4bf, Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION";

	sysColor = new Color( (unsigned int)0xFF000000, Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION_TEXT";

	sysColor = new Color( (unsigned int)0xFFd4d0c8, Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_BORDER";

	sysColor = new Color( (unsigned int)0xFFffffff, Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_CAPTION";

	sysColor = new Color( (unsigned int)0xFFffffe1, Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP";

	sysColor = new Color( (unsigned int)0xFF000000, Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP_TEXT";

	sysColor = new Color( (unsigned int)0xFFFFFFFF, Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU";

	sysColor = new Color( (unsigned int)0xFF000000, Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU_TEXT";

	sysColor = new Color( (unsigned int)0xFFFFFFFF, Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW";

	sysColor = new Color( (unsigned int)0xFF000000, Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_TEXT";

	sysColor = new Color( (unsigned int)0xFF000000, Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_FRAME";
}


VCF::Font XCBGraphicsToolkit::getDefaultFontFor( const int& type )
{
	VCF::Font result("Arial",9);
	switch ( type ) {
		case MENUITEMFONT : {

		}
		break;

		case SELECTEDMENUITEMFONT : {

		}
		break;

		case SYSTEMFONT : {

		}
		break;

		case CONTROLFONT : {

		}
		break;

		case MESSAGEFONT : {

		}
		break;

		case TOOLTIPFONT : {

		}
		break;
	}

	return result;
}

double XCBGraphicsToolkit::getValue( const int& type, const String& text, Font* alternateFont )
{
	double result = 0;
	switch ( type ) {
		case LABELHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,8), *alternateFont );
			}
			else {
				VCF::Font f = XCBGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,8), f );
			}
			result = sz.height_;
		}
		break;

		case BUTTONHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,14), *alternateFont );
			}
			else {
				VCF::Font f = XCBGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,14), f );
			}
			result = sz.height_;
		}
		break;

		case CHECKBOXHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,10), *alternateFont );
			}
			else {
				VCF::Font f = XCBGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,10), f );
			}
			result = sz.height_;
		}
		break;

	}
	return result;
}

Size XCBGraphicsToolkit::getSize( const int& type, const String& text, Font* alternateFont )
{
	Size result;

	switch ( type ) {
		case TABSIZE : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,14), *alternateFont );

				result.width_ = xcbGraphicsToolkit->getTextSize( text, alternateFont ).width_ + 10;
			}
			else {
				VCF::Font f = XCBGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = XCBGraphicsToolkit::DLUToPixel( Size(0,14), f );

				result.width_ = xcbGraphicsToolkit->getTextSize( text, &f ).width_ + 10;
			}




			result.height_ = sz.height_;
		}
		break;
	}

	return result;
}

Rect XCBGraphicsToolkit::getRect( const int& type, Rect* rect, Font* alternateFont )
{
	Rect result;
	return result;
}


Size XCBGraphicsToolkit::getTextSize( const String& text, Font* font )
{
	Size result;

	XCBFontPeer* fontPeer = (XCBFontPeer*)font->getFontPeer();

	FcPattern* pattern = XCBGraphicsToolkit::getFontPatternForFont( fontPeer );

	VCF_ASSERT( NULL != pattern );

	FcChar8 * filename;
	FcPatternGetString( pattern, FC_FILE, 0, &filename ); //do we need to release this???

	if ( fontEngine_->engine.load_font( (const char*)filename, 0, agg::glyph_ren_agg_gray8 ) ) {
		fontEngine_->engine.height( fontPeer->getPixelSize() );
		fontEngine_->engine.width( fontPeer->getPixelSize() );
		fontEngine_->engine.hinting( true );
		fontEngine_->engine.flip_y( true );

		agg::trans_affine mtx;
		fontEngine_->engine.transform(mtx);

		double x1 = 0; //need to convert appropriately
		double y1 = 0;

		agg::rect_d bounds;
		bounds.x1 = 0;
		bounds.y1 = 0;
		bounds.x2 = 0;
		bounds.y2 = 0;

		int character = 0;
		const agg::glyph_cache* glyphPtr = NULL;

		size_t sz = text.size();
		const VCFChar* textPtr = text.c_str();

		for ( size_t i=0;i<sz;i++ ) {
			character = textPtr[i];

			glyphPtr = fontEngine_->mgr.glyph(character);

			if ( NULL != glyphPtr ) {
				fontEngine_->mgr.add_kerning(&x1, &y1);

				fontEngine_->mgr.init_embedded_adaptors(glyphPtr, x1, y1);

				if ( glyphPtr->bounds.is_valid() ) {

					agg::rect_d adjustedGlyphBounds;
					adjustedGlyphBounds.x1 = glyphPtr->bounds.x1 + x1;
					adjustedGlyphBounds.x2 = glyphPtr->bounds.x2 + x1;

					adjustedGlyphBounds.y1 = glyphPtr->bounds.y1 + y1;
					adjustedGlyphBounds.y2 = glyphPtr->bounds.y2 + y1;

					bounds.x1 = (bounds.x1 < adjustedGlyphBounds.x1) ? bounds.x1 : adjustedGlyphBounds.x1;
					bounds.y1 = (bounds.y1 < adjustedGlyphBounds.y1) ? bounds.y1 : adjustedGlyphBounds.y1;

					bounds.x2 = (bounds.x2 > adjustedGlyphBounds.x2) ? bounds.x2 : adjustedGlyphBounds.x2;
					bounds.y2 = (bounds.y2 > adjustedGlyphBounds.y2) ? bounds.y2 : adjustedGlyphBounds.y2;

				}

				x1 += glyphPtr->advance_x;
				y1 += glyphPtr->advance_y;
			}
		}

		bounds.normalize();
		result.width_ = bounds.x2 - bounds.x1;
		result.height_ = bounds.y2 - bounds.y1;
	}

	return result;
}


Size XCBGraphicsToolkit::DLUToPixel( const Size& dlu, VCF::Font& font )
{
	Size result;

	int baseUnitY = (int)(font.getAscent() + font.getDescent());

	int cx = 0;
	Size sz = xcbGraphicsToolkit->getTextSize( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", &font );


	cx = (int)sz.width_;

	int baseUnitX = (int) ((cx / 26 + 1) / 2);

	result.width_ = (dlu.width_ * baseUnitX) / 4;
	result.height_ = (dlu.height_ * baseUnitY) / 8;

	return result;
}

/**
$Id$
*/

