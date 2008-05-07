//AggGraphicsToolkit.cpp

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

#ifdef VCF_WIN
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#endif

#include "AggGraphicsToolkit.h"
#include "AggGraphicsPeers.h"

using namespace VCF;



#ifdef VCF_WIN

bool AGGFontEngine::getMetrics( TextMetric* metrics ) const
{
	OUTLINETEXTMETRIC otm = {0};
	otm.otmSize = sizeof(OUTLINETEXTMETRIC);

	if ( GetOutlineTextMetrics( dc(), sizeof(OUTLINETEXTMETRIC), &otm ) > 0 ) {

		double sx, sy;
		get_scale_values( &sx, &sy );

		metrics->tmAscent = (double)otm.otmTextMetrics.tmAscent * sy;
		metrics->tmDescent = (double)otm.otmTextMetrics.tmDescent * sy;
		metrics->tmHeight = (double)otm.otmTextMetrics.tmHeight * sy;
		

		metrics->tmAveCharWidth = (double)otm.otmTextMetrics.tmAveCharWidth * sx;// + 0.5;
		metrics->tmMaxWidth = (double)otm.otmTextMetrics.tmMaxCharWidth * sx;// + 0.5;

		return true;
	}

	return false;
}

#endif



AggGraphicsToolkit::AggGraphicsToolkit():
	fontEngine_(::GetDC(GetDesktopWindow())),	
	fontManager_(fontEngine_)
{
	
}

AggGraphicsToolkit::~AggGraphicsToolkit()
{

}

ContextPeer* AggGraphicsToolkit::internal_createContextPeer( const uint32& width, const uint32& height )
{
	return new AggContextPeer(width,height);
}

ContextPeer* AggGraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	return new AggContextPeer(contextID);
}

FontPeer* AggGraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new AggFont(fontName);
}

FontPeer* AggGraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	return new AggFont(fontName,pointSize);
}

Image* AggGraphicsToolkit::internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	Image* result = NULL;

	if ( Image::itColor == imageType ) {
		result = new AggRGBAImage( width, height );
	}
	else if ( Image::itGrayscale == imageType ) {
		result = new AggGrayScaleImage( width, height );
	}

	return result;
}

Image* AggGraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	Image* result = NULL;

	if ( Image::itColor == imageType ) {
		result = new AggRGBAImage( context, rect );
	}
	else if ( Image::itGrayscale == imageType ) {
		result = new AggGrayScaleImage( context, rect );
	}
	return result;
}

PrintSessionPeer* AggGraphicsToolkit::internal_createPrintSessionPeer()
{
	return NULL;
}

GraphicsResourceBundlePeer* AggGraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new AggGraphicsResourceBundlePeer();
}

double AggGraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	return 120;
}

void AggGraphicsToolkit::internal_systemSettingsChanged()
{

}

void AggGraphicsToolkit::initSystemFont()
{

}

void AggGraphicsToolkit::loadSystemColors()
{
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



VCF::Font AggGraphicsToolkit::getDefaultFontFor( const int& type )
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


double AggGraphicsToolkit::getValue( const int& type, const String& text, Font* alternateFont )
{
	double result = 0;
	switch ( type ) {
		case LABELHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,8), *alternateFont );
			}
			else {
				VCF::Font f = AggGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,8), f );
			}
			result = sz.height_;
		}
		break;

		case BUTTONHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,14), *alternateFont );
			}
			else {
				VCF::Font f = AggGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,14), f );
			}
			result = sz.height_;
		}
		break;

		case CHECKBOXHEIGHT : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,10), *alternateFont );
			}
			else {
				VCF::Font f = AggGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,10), f );
			}
			result = sz.height_;
		}
		break;

	}
	return result;
}

Size AggGraphicsToolkit::getSize( const int& type, const String& text, Font* alternateFont )
{
	Size result;

	switch ( type ) {
		case TABSIZE : {
			Size sz;
			if ( NULL != alternateFont ) {
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,14), *alternateFont );

				result.width_ = AggGraphicsToolkit::getTextSize( text, alternateFont ).width_ + 10;
			}
			else {
				VCF::Font f = AggGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
				sz = AggGraphicsToolkit::DLUToPixel( Size(0,14), f );

				result.width_ = AggGraphicsToolkit::getTextSize( text, &f ).width_ + 10;
			}




			result.height_ = sz.height_;
		}
		break;
	}

	return result;
}

Rect AggGraphicsToolkit::getRect( const int& type, Rect* rect, Font* alternateFont )
{
	Rect result;
	return result;
}


Size AggGraphicsToolkit::DLUToPixel( const Size& dlu, VCF::Font& font )
{
	Size result;

	int baseUnitY = (int)(font.getAscent() + font.getDescent());

	int cx = 0;
	Size sz = AggGraphicsToolkit::getTextSize( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", &font );


	cx = (int)sz.width_;

	int baseUnitX = (int) ((cx / 26 + 1) / 2);

	result.width_ = (dlu.width_ * baseUnitX) / 4;
	result.height_ = (dlu.height_ * baseUnitY) / 8;

	return result;
}

Size AggGraphicsToolkit::getTextSize( const String& text, Font* font )
{
	AggGraphicsToolkit* toolkit = (AggGraphicsToolkit*) GraphicsToolkit::internal_getDefaultGraphicsToolkit();

	Size result;

	double x1 = 0; //need to convert appropriately 
	double y1 = 0;

	agg::rect_d bounds;
	bounds.x1 = 0;
	bounds.y1 = 0;
	bounds.x2 = 0;
	bounds.y2 = 0;

	int character = 0;
	const agg::glyph_cache* glyph = NULL;

	for ( size_t i=0;i<text.length();i++ ) {
		character = text[i];
	
		glyph = toolkit->fontManager_.glyph(character);


		//glyph = fontManager_.glyph(character);
		if ( NULL != glyph ) {	
			
			double x = x;
			double y = y;

			toolkit->fontManager_.add_kerning(&x, &y);		

			toolkit->fontManager_.init_embedded_adaptors(glyph, x, y);

			if ( glyph->bounds.is_valid() ) {

				agg::rect_d adjustedGlyphBounds;
				adjustedGlyphBounds.x1 = glyph->bounds.x1 + x1;
				adjustedGlyphBounds.x2 = glyph->bounds.x2 + x1;
				
				adjustedGlyphBounds.y1 = glyph->bounds.y1 + y1;
				adjustedGlyphBounds.y2 = glyph->bounds.y2 + y1;
				
				bounds.x1 = (bounds.x1 < adjustedGlyphBounds.x1) ? bounds.x1 : adjustedGlyphBounds.x1;
				bounds.y1 = (bounds.y1 < adjustedGlyphBounds.y1) ? bounds.y1 : adjustedGlyphBounds.y1;
				
				bounds.x2 = (bounds.x2 > adjustedGlyphBounds.x2) ? bounds.x2 : adjustedGlyphBounds.x2;
				bounds.y2 = (bounds.y2 > adjustedGlyphBounds.y2) ? bounds.y2 : adjustedGlyphBounds.y2;
				
			}

			x1 += glyph->advance_x;
			y1 += glyph->advance_y;	
		}
		

	}

	bounds.normalize();
	result.width_ = bounds.x2 - bounds.x1;
	result.height_ = bounds.y2 - bounds.y1;

	return result;
}