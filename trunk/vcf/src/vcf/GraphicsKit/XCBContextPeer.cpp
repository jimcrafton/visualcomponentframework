
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"
#include "vcf/GraphicsKit/XCBFontPeer.h"

#include "thirdparty/common/agg/include/agg_font_freetype.h"



typedef agg::font_engine_freetype_int32 XCBFontEngineType;
typedef agg::font_cache_manager<XCBFontEngineType> XCBFontManagerType;

namespace VCF {
struct FontStruct {
	FontStruct(): engine(), mgr(engine){}
	
	XCBFontEngineType engine;
	XCBFontManagerType mgr;
	bool fontLoaded;
	agg::glyph_rendering glyphRendering;
	double currentPointSize;		
	agg::rgba color;
};	

struct CachedGlyph {		
	const agg::glyph_cache* glyph;
	double kernX;
	double kernY;
};
	
};


using namespace VCF;

XCBContextPeer::XCBContextPeer() :
context_(NULL),
image_(NULL),
drawingSurface_(NULL),
fonts_(NULL)
{
	init();
}

XCBContextPeer::XCBContextPeer( const unsigned long& width, const unsigned long& height ) :
context_(NULL),
image_(NULL),
drawingSurface_(NULL),
fonts_(NULL)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	init();
}

XCBContextPeer::XCBContextPeer( OSHandleID contextID ) :
context_(NULL),
image_(NULL),
drawingSurface_(NULL),
fonts_(NULL)
{
	init();
    setContextID( contextID );	
}

void XCBContextPeer::init()
{
	fonts_ = new FontStruct();
}

XCBContextPeer::~XCBContextPeer()
{
	delete fonts_;
	std::vector<CachedGlyph*>::iterator it = cachedFontGlyphs_.begin();
	while ( it != cachedFontGlyphs_.end() ) {
		if ( NULL != *it ) {
			delete *it;
		}
		it ++;
	}
	cachedFontGlyphs_.clear();
}

void XCBContextPeer::checkHandle()
{
	//no-op
}

void XCBContextPeer::releaseHandle()
{
	//no-op
}

void XCBContextPeer::setContext( GraphicsContext* context )
{
	context_ = context;
}

GraphicsContext* XCBContextPeer::getContext()
{
	return context_;
}

OSHandleID XCBContextPeer::getContextID()
{
	return (OSHandleID) drawingSurface_;
}

void XCBContextPeer::setContextID( OSHandleID contextID )
{
	if ( NULL != drawingSurface_ ) {
		//clear out old render buff...
		renderBuffer_.attach( NULL, 0, 0, 0 );
	}
	
	drawingSurface_ = (XCBSurface*)contextID;
	
	if ( NULL != drawingSurface_ ) {
		unsigned char* imageData = drawingSurface_->drawableImage->data;
		
		renderBuffer_.attach( imageData, drawingSurface_->drawableImage->width, drawingSurface_->drawableImage->height, 
								drawingSurface_->drawableImage->width * 4 );
	}
}

void XCBContextPeer::resetPath()
{
	currentPath_.remove_all();
	currentPath_.free_all();
	currentPath_.rewind(0);
}

void XCBContextPeer::clearGlyphs()
{
	std::vector<CachedGlyph*>::iterator it = cachedFontGlyphs_.begin();
	while ( it != cachedFontGlyphs_.end() ) {
		if ( NULL != *it ) {
			delete *it;
		}
		it ++;
	}
	cachedFontGlyphs_.clear();
	cachedFontGlyphs_.resize(256,0);
}

const agg::glyph_cache* XCBContextPeer::glyph( int character, double& x, double& y )
{
	CachedGlyph* cg = NULL;

	//check to see if we need to resize over 256
	if ( character > cachedFontGlyphs_.size()-1 ) {
		cachedFontGlyphs_.resize( cachedFontGlyphs_.size() + (character - (cachedFontGlyphs_.size()-1)), 0 );
	}
	
	if ( NULL != cachedFontGlyphs_[character] ) {
		cg = cachedFontGlyphs_[character];
		x += cg->kernX;
		y += cg->kernY;
	}
	else {
		const agg::glyph_cache* glyph = NULL;

		if ( (character == '\n') || (character == '\r') ) {
			glyph = fonts_->mgr.glyph(character);
			if ( NULL != glyph ) {
				double x1 = x;
				double y1 = y;
		
				cg = new CachedGlyph();
				cachedFontGlyphs_[character] = cg;
				
				cg->glyph = glyph;
				cg->kernX = x - x1;
				cg->kernY = y - y1;
			}
		}
		else {
			glyph = fonts_->mgr.glyph(character);
			if ( NULL != glyph ) {				
				double x1 = x;
				double y1 = y;

				fonts_->mgr.add_kerning(&x1, &y1);

				cg = new CachedGlyph();
				cachedFontGlyphs_[character] = cg;
				
				cg->glyph = glyph;
				cg->kernX = x - x1;
				cg->kernY = y -y1;
			}
		}
	}

	return cg->glyph;
}

bool XCBContextPeer::prepareForDrawing( long drawingOperation )
{
	resetPath();
	
	switch ( drawingOperation ) {
		case GraphicsContext::doStroke : {
			
				
			switch ( context_->getLineCapStyle() ) {
				case GraphicsContext::lcsButtCap : {
				}
				break;

				case GraphicsContext::lcsRoundCap : {
				}
				break;

				case GraphicsContext::lcsSquareCap : {
				}
				break;
			}

			switch ( context_->getLineJoinStyle() ) {
				case GraphicsContext::ljsMiterJoin : {

				}
				break;

				case GraphicsContext::ljsRoundJoin : {

				}
				break;

				case GraphicsContext::ljsBevelJoin : {
				}
				break;
			}


			if ( context_->getCompositingMode() == GraphicsContext::cmXOR ) {

			}
		}
		break;

		case GraphicsContext::doFill : {
				
		}
		break;

		case GraphicsContext::doText : {
			
			
			Font* font = context_->getCurrentFont();
			XCBFontPeer* fontPeer = (XCBFontPeer*)font->getFontPeer();			
			
			String fontHash = fontPeer->getHashcode();
			
			
			FcPattern* pattern = XCBGraphicsToolkit::getFontPatternForFont( fontPeer );
	
			
			VCF_ASSERT( NULL != pattern );
			
			//this check to see if the font's changed - if it 
			//has we need to clear the glyph cache
			if ( prevFontHash_ != fontHash ) { 
				clearGlyphs();
			}
	
			prevFontHash_ = fontHash;
			
			FcChar8 * filename;
			FcPatternGetString( pattern, FC_FILE, 0, &filename ); //do we need to release this???	

			Color c = *context_->getCurrentFont()->getColor();
			printf( "color: %.2f, %.2f, %.2f, %.2f\n",
						c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha() );
			fonts_->color = agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha());
			fonts_->glyphRendering = agg::glyph_ren_agg_gray8;
			fonts_->fontLoaded = fonts_->engine.load_font( (const char*)filename, 0, fonts_->glyphRendering );
			if ( fonts_->fontLoaded ) {
				fonts_->engine.hinting( false );
				fonts_->engine.height( fontPeer->getPointSize() );
				fonts_->engine.width( fontPeer->getPointSize() );
				fonts_->engine.flip_y( true );
				
				fonts_->currentPointSize = fontPeer->getPointSize();
				
				agg::trans_affine mtx = *context_->getCurrentTransform();
				fonts_->engine.transform(mtx);
			}
		}
		break;

		case GraphicsContext::doImage : {

		}
		break;
	}
		
	return true;
}

void XCBContextPeer::finishedDrawing( long drawingOperation )
{
	Matrix2D& currentXFrm = *context_->getCurrentTransform();
	agg::trans_affine mat = currentXFrm;
	mat*=agg::trans_affine_translation(0.5,0.5);
	
	switch ( drawingOperation ) {
		case GraphicsContext::doStroke : {			

			agg::conv_curve< agg::path_storage > smooth(currentPath_);
			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);

			int lcs = 0;
			int ljs = 0;

			switch ( context_->getLineCapStyle() ) {
				case GraphicsContext::lcsButtCap : {
					lcs = agg::butt_cap;
				}
				break;

				case GraphicsContext::lcsRoundCap : {
					lcs = agg::round_cap;
				}
				break;

				case GraphicsContext::lcsSquareCap : {
					lcs = agg::square_cap;
				}
				break;
			}

			switch ( context_->getLineJoinStyle() ) {
				case GraphicsContext::ljsMiterJoin : {
					ljs = agg::miter_join;
				}
				break;

				case GraphicsContext::ljsRoundJoin : {
					ljs = agg::round_join;
				}
				break;

				case GraphicsContext::ljsBevelJoin : {
					ljs = agg::bevel_join;
				}
				break;
			}
	
			agg::conv_stroke< agg::conv_transform< agg::conv_curve< agg::path_storage > > >  stroke(xfrmedPath);
				
			stroke.width( maxVal<>( 0.5, context_->getStrokeWidth() ) );
			stroke.line_cap( (agg::line_cap_e)lcs );
			stroke.line_join( (agg::line_join_e)ljs );
			stroke.miter_limit( context_->getMiterLimit() );
	
			agg::rasterizer_scanline_aa<> rasterizer;
				
			rasterizer.add_path( stroke );
			Color c = *context_->getColor();
			
			renderScanlinesSolid( rasterizer, agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha()) );			
				
			if ( context_->getCompositingMode() == GraphicsContext::cmXOR ) {

			}
		}
		break;

		case GraphicsContext::doFill : {
			agg::conv_curve<agg::path_storage> smooth(currentPath_);
			
			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);
			
			agg::rasterizer_scanline_aa<> rasterizer;		
			rasterizer.add_path( xfrmedPath );

			Color c = *context_->getColor();

			renderScanlinesSolid( rasterizer, agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha()) );	
		}
		break;

		case GraphicsContext::doText : {
				

		}
		break;

		case GraphicsContext::doImage : {

		}
		break;
	}
	

}


void XCBContextPeer::renderScanlinesSolid( agg::rasterizer_scanline_aa<>& rasterizer, const agg::rgba& color )
{
	typedef agg::renderer_base<XCBSurface::PixFmt> RendererBase;
	typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolid;

	typedef agg::comp_op_adaptor_rgba<XCBSurface::ColorType, XCBSurface::ComponentOrder> blender_type;
	typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
	typedef agg::renderer_base<pixfmt_type> comp_renderer_type;

	if ( GraphicsContext::cmSource == context_->getCompositingMode() ) {
		XCBSurface::PixFmt pixf( renderBuffer_ );
		RendererBase renb(pixf);
		RendererSolid renderer( renb );

		renderer.color(color);


		agg::render_scanlines(rasterizer, scanline_, renderer);
	}
	else {
		pixfmt_type pixf( renderBuffer_ );
		pixf.comp_op( context_->getCompositingMode() );
		comp_renderer_type renb(pixf);

		agg::render_scanlines_aa_solid(rasterizer, scanline_, renb, color);
	}
}

void XCBContextPeer::setClippingPath( Path* clippingPath )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setClippingRect( Rect* clipRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setTextAlignment( const bool& alignTobaseline )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::isTextAlignedToBaseline()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBContextPeer::textAt( const Rect& bounds, const String & text, const long& drawOptions )
{	
	VCF_ASSERT( fonts_->fontLoaded );
	
	double x1 = bounds.left_; 
	double y1 = renderBuffer_.height() - bounds.bottom_;
	
	agg::rect_d charBounds;
	charBounds.x1 = 0;
	charBounds.y1 = 0;
	charBounds.x2 = 0;
	charBounds.y2 = 0;
	
	int character = 0;
	const agg::glyph_cache* glyphPtr = NULL;
	size_t size = text.size();
	const VCFChar* textPtr = text.c_str();
	
	bool crlfChar = false;
	
	typedef agg::renderer_base<XCBSurface::PixFmt> RendererBase;
	typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolid;

	typedef agg::comp_op_adaptor_rgba<XCBSurface::ColorType, XCBSurface::ComponentOrder> blender_type;
	typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
	typedef agg::renderer_base<pixfmt_type> comp_renderer_type;

	XCBSurface::PixFmt pixfSrc( renderBuffer_ );
	RendererBase renbSrc(pixfSrc);
	RendererSolid rendererSrc( renbSrc );
	rendererSrc.color(fonts_->color);
	
	//pixfmt_type pixf( renderBuffer_ );
	//pixf.comp_op( context_->getCompositingMode() );
	//comp_renderer_type renb(pixf);
	
	bool doSrcRender = (GraphicsContext::cmSource == context_->getCompositingMode()) ? true : false;
	
	for ( size_t i=0;i<size;i++ ) {
		character = textPtr[i];
		
		crlfChar = (character == '\n') || (character == '\r');
		
		if ( crlfChar ) {
			glyphPtr = glyph(character, x1, y1 );
			if ( NULL != glyphPtr ) {
				

				x1 = bounds.left_;
				y1 -= fonts_->currentPointSize; 
				
				fonts_->mgr.init_embedded_adaptors(glyphPtr, x1, y1);
			}
		}
		else {
			glyphPtr = glyph(character, x1, y1 );
			fonts_->mgr.init_embedded_adaptors(glyphPtr, x1, y1);
			
			if ( glyphPtr->bounds.is_valid() ) {

				agg::rect_d adjustedGlyphBounds;
				adjustedGlyphBounds.x1 = glyphPtr->bounds.x1 + x1;
				adjustedGlyphBounds.x2 = glyphPtr->bounds.x2 + x1;
				
				adjustedGlyphBounds.y1 = glyphPtr->bounds.y1 + y1;
				adjustedGlyphBounds.y2 = glyphPtr->bounds.y2 + y1;
				
				charBounds.x1 = (charBounds.x1 < adjustedGlyphBounds.x1) ? charBounds.x1 : adjustedGlyphBounds.x1;
				charBounds.y1 = (charBounds.y1 < adjustedGlyphBounds.y1) ? charBounds.y1 : adjustedGlyphBounds.y1;
				
				charBounds.x2 = (charBounds.x2 > adjustedGlyphBounds.x2) ? charBounds.x2 : adjustedGlyphBounds.x2;
				charBounds.y2 = (charBounds.y2 > adjustedGlyphBounds.y2) ? charBounds.y2 : adjustedGlyphBounds.y2;
				
			}
			
			switch( glyphPtr->data_type ) {
				case agg::glyph_data_mono: {
//						agg::render_scanlines(aggFontManager_.mono_adaptor(),
//												aggFontManager_.mono_scanline(), 
//												renderBin);
				}
				break;

				case agg::glyph_data_gray8: {
					//if ( doSrcRender ) {
						agg::render_scanlines(fonts_->mgr.gray8_adaptor(), fonts_->mgr.gray8_scanline(), rendererSrc);
					//}
					//else {
					//	agg::render_scanlines_aa_solid(fonts_->mgr.gray8_adaptor(), fonts_->mgr.gray8_scanline(), 
					//									renb, fonts_->color);
					//}
				}
				break;

				case agg::glyph_data_outline: {
					//rasterizer.reset();                        
					//rasterizer.add_path(contour);
					//agg::render_scanlines(rasterizer, scanLine, renderSolid);
				}
				break;
			}
			
			x1 += glyphPtr->advance_x;
			y1 += glyphPtr->advance_y;
		}
	}
	
	//agg::render_scanlines(rasterizer, scanline_, renderer);
}

double XCBContextPeer::getTextWidth( const String& text )
{
	//LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 100.0;
}

double XCBContextPeer::getTextHeight( const String& text )
{
	//LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 25.0;
}

void XCBContextPeer::rectangle( const double & x1, const double & y1,
								const double & x2, const double & y2 )
{
	currentPath_.move_to( x1, y1 );
	currentPath_.line_to( x2, y1 );
	currentPath_.line_to( x2, y2 );
	currentPath_.line_to( x1, y2 );
	currentPath_.close_polygon();
}

void XCBContextPeer::roundRect( const double & x1, const double & y1,
								const double & x2, const double & y2,
								const double & xc, const double & yc )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::ellipse( const double & x1, const double & y1,
							  const double & x2, const double & y2 )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::arc( const double & x1, const double & y1,
						  const double & x2, const double & y2,
						  const double & x3, const double & y3,
						  const double & x4, const double & y4 )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::polyline( const std::vector<Point>& pts )
{
	if ( pts.empty() ) {
		return;
	}
	
	
	std::vector<Point>::const_iterator it = pts.begin();
	const Point& first = *it;
	currentPath_.move_to( first.x_, first.y_ );
	++it;
	while ( it != pts.end() ) {
		const Point& p = *it;
		currentPath_.line_to( p.x_, p.y_ );
		++it;
	}
}

void XCBContextPeer::curve( const double & x1, const double & y1, const double & x2, const double & y2,
							const double & x3, const double & y3, const double & x4, const double & y4 )
{
	currentPath_.move_to( x1, y1 );
	currentPath_.curve4( x2,y2, x3,y3, x4,y4 );	
}

void XCBContextPeer::moveTo( const double & x, const double & y )
{
	currentPath_.move_to( x, y );
}

void XCBContextPeer::lineTo( const double & x, const double & y )
{
	currentPath_.line_to( x, y );
}

void XCBContextPeer::setOrigin( const double& x, const double& y )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Point XCBContextPeer::getOrigin()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Point();
}

void XCBContextPeer::copyContext( const Rect& sourceRect,
								  const Rect& destRect,
								  ContextPeer* sourceContext )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::isMemoryContext()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

bool XCBContextPeer::isAntiAliasingOn()
{
	return true;
}

void XCBContextPeer::setAntiAliasingOn( bool antiAliasingOn )
{
//no-op
}

void XCBContextPeer::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeButtonFocusRect( Rect* rect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTab( Rect* rect, TabState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSlider( Rect* rect, SliderState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeProgress( Rect* rect, ProgressState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeHeader( Rect* rect, ButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeMenuItem( Rect* rect, MenuState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeMenuItemText( Rect* rect, MenuState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeText( Rect* rect, TextState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::internal_setImage(XCBImage *image)
{
	image_ = image;
}

/**
$Id$
*/

