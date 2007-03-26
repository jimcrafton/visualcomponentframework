
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"
#include "vcf/GraphicsKit/XCBFontPeer.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/GraphicsKit/XCBImagePeer.h"

#include "thirdparty/common/agg/include/agg_font_freetype.h"
#include "thirdparty/common/agg/include/agg_conv_dash.h"
#include "thirdparty/common/agg/include/agg_renderer_mclip.h"


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
antiAliasing_(true),
fonts_(NULL)
{
	init();
}

XCBContextPeer::XCBContextPeer( const uint32& width, const uint32& height ) :
context_(NULL),
image_(NULL),
drawingSurface_(NULL),
antiAliasing_(true),
fonts_(NULL)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	init();
}

XCBContextPeer::XCBContextPeer( OSHandleID contextID ) :
context_(NULL),
image_(NULL),
drawingSurface_(NULL),
antiAliasing_(true),
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

	VCF_ASSERT( character >= 0 );

	//check to see if we need to resize over 256
	if ( (size_t)character > cachedFontGlyphs_.size()-1 ) {
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

bool XCBContextPeer::prepareForDrawing( int32 drawingOperation )
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
				FcChar8 * filename;
				FcPatternGetString( pattern, FC_FILE, 0, &filename ); //do we need to release this???
				fonts_->glyphRendering = agg::glyph_ren_native_gray8;
				fonts_->fontLoaded = fonts_->engine.load_font( (const char*)filename, 0, fonts_->glyphRendering );
			}


			if ( !fonts_->fontLoaded ) {
				printf( "Error: fonts_->fontLoaded = false, loading hash: %s (prev hash: %s)\n",
							fontHash.ansi_c_str(), prevFontHash_.ansi_c_str() );
			}

			prevFontHash_ = fontHash;

			VCF_ASSERT( fonts_->fontLoaded );



			Color c = *context_->getCurrentFont()->getColor();
			fonts_->color = agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha());

			if ( fonts_->fontLoaded ) {

				//printf( "Font %s loaded!\n",
					//		fontHash.ansi_c_str() );
				fonts_->engine.hinting( false );
				fonts_->engine.height( fontPeer->getPixelSize() );
				fonts_->engine.width( fontPeer->getPixelSize() );

				fonts_->engine.flip_y( true );



				//fonts_->engine.gamma( agg::gamma_threshold(2.50) );

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

void XCBContextPeer::finishedDrawing( int32 drawingOperation )
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


	typedef agg::renderer_mclip<XCBSurface::PixFmt> RendererBase;
	typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolidAA;
	typedef agg::renderer_scanline_bin_solid<RendererBase> RendererSolidBin;




	typedef agg::comp_op_adaptor_rgba<XCBSurface::ColorType, XCBSurface::ComponentOrder> blender_type;
	typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
	typedef agg::renderer_base<pixfmt_type> comp_renderer_type;

	//agg::scanline_u8 scanline;
	if ( GraphicsContext::cmSource == context_->getCompositingMode() ) {
		XCBSurface::PixFmt pixf( renderBuffer_ );
		RendererBase renb(pixf);


		if ( !currentClipRect_.isNull() && !currentClipRect_.isEmpty() ) {
			renb.reset_clipping(false);
			renb.add_clip_box( (int)currentClipRect_.left_,
								(int)currentClipRect_.top_,
								(int)currentClipRect_.right_,
								(int)currentClipRect_.bottom_ );
		}
		else {
			renb.reset_clipping(true);
		}




		if ( antiAliasing_ ) {
			RendererSolidAA renderer( renb );
			renderer.color(color);
			agg::render_scanlines(rasterizer, scanline_, renderer);
		}
		else {
			RendererSolidBin renderer( renb );
			renderer.color(color);
			agg::render_scanlines(rasterizer, scanline_, renderer);
		}
	}
	else {
		pixfmt_type pixf( renderBuffer_ );
		pixf.comp_op( context_->getCompositingMode() );
		comp_renderer_type renb(pixf);
		/*
		How do we do this????
		if ( !currentClipRect_.isNull() && !currentClipRect_.isEmpty() ) {
			renb.reset_clipping(false);
			renb.add_clip_box( currentClipRect_.left_, currentClipRect_.top_,
							currentClipRect_.right_, currentClipRect_.bottom_ );
		}
		else {
			renb.reset_clipping(true);
		}
		*/

		agg::render_scanlines_aa_solid(rasterizer, scanline_, renb, color);
	}
}

void XCBContextPeer::setClippingPath( Path* clippingPath )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setClippingRect( Rect* clipRect )
{
	if ( NULL == clipRect ) {
		currentClipRect_.setNull();
	}
	else {
		currentClipRect_ = *clipRect;
	}
}

void XCBContextPeer::setTextAlignment( const bool& alignTobaseline )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::isTextAlignedToBaseline()
{
	return true;
}

void XCBContextPeer::internal_setGamma( double gamma )
{
	fonts_->engine.gamma( agg::gamma_power(gamma) );
}



void XCBContextPeer::renderLine( const std::vector<GlyphInfo>& glyphs, size_t lastGlyphPos, const Size& currentLineSz,
								const Rect& bounds, const int32& drawOptions )
{
	if ( lastGlyphPos > 0 ) {
		bool doSrcRender = (GraphicsContext::cmSource == context_->getCompositingMode()) ? true : false;
		typedef agg::renderer_mclip<XCBSurface::PixFmt> RendererBase;
		typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolid;

		typedef agg::comp_op_adaptor_rgba<XCBSurface::ColorType, XCBSurface::ComponentOrder> blender_type;
		typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
		typedef agg::renderer_mclip<pixfmt_type> comp_renderer_type;

		XCBSurface::PixFmt pixfSrc( renderBuffer_ );
		RendererBase renbSrc(pixfSrc);
		RendererSolid rendererSrc( renbSrc );
		rendererSrc.color(fonts_->color);

		pixfmt_type pixf( renderBuffer_ );
		pixf.comp_op( context_->getCompositingMode() );
		comp_renderer_type renb(pixf);


		//renbSrc.reset_clipping( false );
		//renbSrc.add_clip_box( (int)bounds.left_, (int)bounds.top_,
		//						(int)bounds.right_, (int)bounds.bottom_ );

		//renb.reset_clipping( false );
		//renb.add_clip_box( (int)bounds.left_, (int)bounds.top_,
			//					(int)bounds.right_, (int)bounds.bottom_ );

		double rightDX = bounds.getWidth() - currentLineSz.width_;
		double centerDX = bounds.getWidth()/2.0 - currentLineSz.width_/2.0;

		for ( size_t i=0;i<=lastGlyphPos;i++ ) {
			const GlyphInfo& glyphInfo = glyphs[i];
			double gx = glyphInfo.x;
			double gy = glyphInfo.y;

			if ( drawOptions & GraphicsContext::tdoRightAlign ) {
				gx = glyphInfo.x + rightDX;
			}
			else if ( drawOptions & GraphicsContext::tdoCenterHorzAlign ) {
				gx = glyphInfo.x + centerDX;
			}

			if ( glyphInfo.visible ) {
				fonts_->mgr.init_embedded_adaptors( glyphInfo.glyph, gx, gy );
				switch( glyphInfo.glyph->data_type ) {
					case agg::glyph_data_mono: {
//						agg::render_scanlines(aggFontManager_.mono_adaptor(),
//												aggFontManager_.mono_scanline(),
//												renderBin);

						LinuxDebugUtils::FunctionNotImplemented( "Not painting glyph_data_mono" );
					}
					break;

					case agg::glyph_data_gray8: {
						if ( doSrcRender ) {
							agg::render_scanlines(fonts_->mgr.gray8_adaptor(), fonts_->mgr.gray8_scanline(), rendererSrc);
						}
						else {
							agg::render_scanlines_aa_solid(fonts_->mgr.gray8_adaptor(), fonts_->mgr.gray8_scanline(),
															renb, fonts_->color);
						}
					}
					break;

					case agg::glyph_data_outline: {
						LinuxDebugUtils::FunctionNotImplemented( "Not painting glyph_data_outline" );
						//rasterizer.reset();
						//rasterizer.add_path(contour);
						//agg::render_scanlines(rasterizer, scanLine, renderSolid);
					}
					break;
				}
			}
		}
	}
}

void XCBContextPeer::textAt( const Rect& bounds, const String & text, const int32& drawOptions )
{
	VCF_ASSERT( fonts_->fontLoaded );

	double dpi = GraphicsToolkit::getDPI();


/*
	agg::rect_d charBounds;
	charBounds.x1 = 0;
	charBounds.y1 = 0;
	charBounds.x2 = 0;
	charBounds.y2 = 0;
*/
	int character = 0;
	size_t size = text.size();
	const VCFChar* textPtr = text.c_str();

	bool crlfChar = false;

	double fontHeight =  getTextHeight("EM");  //(fonts_->currentPointSize / 72.0) * dpi;

	double x1 = bounds.left_;
	double y1 = bounds.top_ + fontHeight;

	Size currentLineSz;
	currentLineSz.height_ = fontHeight;

	const size_t GLYPHS_INCREMENT = 256;
	std::vector<GlyphInfo> currentLine(GLYPHS_INCREMENT);
	size_t lastGlyphPos = 0;

	for ( size_t i=0;i<size;i++ ) {
		character = textPtr[i];

		crlfChar = (character == '\n') || (character == '\r');

		if ( lastGlyphPos >= currentLine.size() ) {
			currentLine.resize( currentLine.size() + GLYPHS_INCREMENT );
		}

		GlyphInfo& glyphInfo = currentLine[lastGlyphPos];

		glyphInfo.glyph = glyph(character, x1, y1 );
		glyphInfo.x = x1;
		glyphInfo.y = y1;
		glyphInfo.visible = !crlfChar;

		if ( crlfChar ) {

			if ( NULL != glyphInfo.glyph ) {


				if ( drawOptions & GraphicsContext::tdoWordWrap ) {
					renderLine( currentLine, lastGlyphPos, currentLineSz, bounds, drawOptions );

					x1 = bounds.left_;
					y1 += fontHeight;

					lastGlyphPos = 0;
					currentLineSz.width_ = 0;
				}
				else {
					currentLineSz.width_ += glyphInfo.glyph->advance_x;
					x1 += glyphInfo.glyph->advance_x;
					y1 += glyphInfo.glyph->advance_y;
					lastGlyphPos ++;
				}
			}
		}
		else {
/*
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
*/

			currentLineSz.width_ += glyphInfo.glyph->advance_x;
			x1 += glyphInfo.glyph->advance_x;
			y1 += glyphInfo.glyph->advance_y;
			lastGlyphPos ++;
		}
	}

	renderLine( currentLine, lastGlyphPos, currentLineSz, bounds, drawOptions );
}

Size XCBContextPeer::getTextSize( const String& text )
{
	Size result;

	Font* font = context_->getCurrentFont();
	XCBFontPeer* fontPeer = (XCBFontPeer*)font->getFontPeer();

	String fontHash = fontPeer->getHashcode();

	if ( prevFontHash_ != fontHash ) {
		FcPattern* pattern = XCBGraphicsToolkit::getFontPatternForFont( fontPeer );

		VCF_ASSERT( NULL != pattern );

		clearGlyphs();

		FcChar8 * filename;
		FcPatternGetString( pattern, FC_FILE, 0, &filename ); //do we need to release this???

		fonts_->fontLoaded = fonts_->engine.load_font( (const char*)filename, 0, agg::glyph_ren_native_gray8 );

		VCF_ASSERT( fonts_->fontLoaded );

		if ( fonts_->fontLoaded ) {
			fonts_->engine.hinting( false );
			fonts_->engine.height( fontPeer->getPixelSize() );
			fonts_->engine.width( fontPeer->getPixelSize() );
			fonts_->engine.flip_y( true );

			agg::trans_affine mtx = *context_->getCurrentTransform();
			fonts_->engine.transform(mtx);
			prevFontHash_ = fontHash;
		}
	}

	if ( fonts_->fontLoaded ) {
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

			glyphPtr = glyph( character, x1, y1 );
			if ( NULL != glyphPtr ) {

				fonts_->mgr.init_embedded_adaptors(glyphPtr, x1, y1);

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


double XCBContextPeer::getTextWidth( const String& text )
{
	Size sz = getTextSize( text );

	return sz.width_;
}

double XCBContextPeer::getTextHeight( const String& text )
{
	Size sz = getTextSize( text );

	return sz.height_;
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
	//Not needed - implemented in GraphicsContext
}

void XCBContextPeer::ellipse( const double & x1, const double & y1,
							  const double & x2, const double & y2 )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	//Not needed - implemented in GraphicsContext
}

void XCBContextPeer::arc( const double & x1, const double & y1,
						  const double & x2, const double & y2,
						  const double & x3, const double & y3,
						  const double & x4, const double & y4 )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	//Not needed - implemented in GraphicsContext
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

void XCBContextPeer::closePath()
{
	currentPath_.close_polygon();
}

void XCBContextPeer::setOrigin( const double& x, const double& y )
{
	origin_.x_ = x;
	origin_.y_ = y;
}

Point XCBContextPeer::getOrigin()
{
	return origin_;
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
	return antiAliasing_;
}

void XCBContextPeer::setAntiAliasingOn( bool antiAliasingOn )
{
	antiAliasing_ = antiAliasingOn;
}

void XCBContextPeer::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode )
{
	XCBImagePeer *srcImagePeer = dynamic_cast<XCBImagePeer*>(image);
	if(srcImagePeer != NULL) {
		for(int32 srcY = 0; srcY<imageBounds->getHeight(); ++srcY) {
			for(int32 srcX = 0; srcX<imageBounds->getWidth(); ++srcX) {
				uint32_t pixel = xcb_image_get_pixel(const_cast<xcb_image_t*>(srcImagePeer->getImageData()), srcX, srcY);
				xcb_image_put_pixel(drawingSurface_->drawableImage, x+srcX, y+srcY, pixel);
			}
		}
	}
}

void XCBContextPeer::bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	Color stroke("gray100");
	stroke.setAlpha( 0.2 );
	Color fill("gray128");
	fill.setAlpha( 0.2 );
	int gcs = context_->saveState();
	context_->setColor( &stroke );
	context_->rectangle( rect );
	context_->strokePath();

	context_->setColor( &fill );
	context_->rectangle( rect );
	context_->fillPath();

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	agg::path_storage path;
	path.move_to( rect->left_, rect->top_ );
	path.line_to( rect->right_, rect->top_ );
	path.line_to( rect->right_, rect->bottom_ );
	path.line_to( rect->left_, rect->bottom_ );
	path.close_polygon();
	agg::trans_affine mat = *context_->getCurrentTransform();
	mat*=agg::trans_affine_translation(0.5,0.5);

	mat *= agg::trans_affine_translation( origin_.x_, origin_.y_  );
	agg::conv_curve< agg::path_storage > smooth(path);

	agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);
	agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > dash(xfrmedPath);
	dash.add_dash( 1, 1 );
	dash.dash_start( 0.5 );
	agg::conv_stroke< agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > >  stroke(dash);

	stroke.width( 1 );
	agg::rasterizer_scanline_aa<> rasterizer;
	rasterizer.add_path( stroke );

	Color c("black");
	if ( !state.isEnabled() ) {
		c = Color("gray128");
	}
	renderScanlinesSolid( rasterizer, agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha()) );
}

void XCBContextPeer::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	int gcs = context_->saveState();

	context_->setStrokeWidth(0.5);
	context_->setColor( &face );
	context_->rectangle( rect );
	context_->fillPath();

	if ( state.isEnabled() && state.isPressed() ) {
		context_->setColor( &black );
		context_->moveTo( rect->left_, rect->bottom_ );
		context_->lineTo( rect->left_, rect->top_ );
		context_->lineTo( rect->right_, rect->top_ );
		context_->strokePath();


		context_->setColor( &shad );
		context_->moveTo( rect->left_+1, rect->bottom_-1 );
		context_->lineTo( rect->left_+1, rect->top_+1 );
		context_->lineTo( rect->right_-1, rect->top_+1 );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( rect->right_, rect->top_+1 );
		context_->lineTo( rect->right_, rect->bottom_ );
		context_->lineTo( rect->left_+1, rect->bottom_ );
		context_->strokePath();
	}
	else {


		context_->setColor( &hilite );
		context_->moveTo( rect->left_, rect->bottom_ - 1 );
		context_->lineTo( rect->left_, rect->top_ );
		context_->lineTo( rect->right_-1, rect->top_ );
		context_->strokePath();


		context_->setColor( &shad );
		context_->moveTo( rect->right_-1, rect->top_ +1 );
		context_->lineTo( rect->right_-1, rect->bottom_ - 1 );
		context_->lineTo( rect->left_+1, rect->bottom_ - 1 );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( rect->right_, rect->top_ );
		context_->lineTo( rect->right_, rect->bottom_ );
		context_->lineTo( rect->left_, rect->bottom_ );
		context_->strokePath();
	}

	if ( state.isFocused() ) {
		Rect r = *rect;
		r.inflate( -5, 0);
		r.top_ += 3;
		r.bottom_ -= 4;

		drawThemeFocusRect( &r, state );
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeButtonFocusRect( Rect* rect )
{
	agg::path_storage path;
	path.move_to( rect->left_, rect->top_ );
	path.line_to( rect->right_, rect->top_ );
	path.line_to( rect->right_, rect->bottom_ );
	path.line_to( rect->left_, rect->bottom_ );
	path.close_polygon();
	agg::trans_affine mat = *context_->getCurrentTransform();
	mat*=agg::trans_affine_translation(0.5,0.5);

	mat *= agg::trans_affine_translation( origin_.x_, origin_.y_  );
	agg::conv_curve< agg::path_storage > smooth(path);

	agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);
	agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > dash(xfrmedPath);
	dash.add_dash( 1, 1 );
	dash.dash_start( 0.5 );
	agg::conv_stroke< agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > >  stroke(dash);

	stroke.width( 1 );
	agg::rasterizer_scanline_aa<> rasterizer;

	rasterizer.add_path( stroke );

	Color c("black");

	renderScanlinesSolid( rasterizer, agg::rgba(c.getRed(),c.getGreen(),c.getBlue(),c.getAlpha()) );
}

void XCBContextPeer::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	int gcs = context_->saveState();

	Size cb(13,13);

	context_->setStrokeWidth(0.5);
	Rect tmp = *rect;
	tmp.top_ = (int)(rect->top_ + rect->getHeight() /2.0 + 0.5);
	tmp.top_ -= cb.height_/2.0;
	tmp.bottom_ = tmp.top_ + cb.height_;
	tmp.right_ = tmp.left_ + cb.height_;

	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	Color wnd = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
	Color disabled = *GraphicsToolkit::getSystemColor( SYSCOLOR_INACTIVE_CAPTION );

	context_->setColor( &wnd );
	context_->rectangle( &tmp );
	context_->fillPath();


	context_->setColor( &shad );
	context_->moveTo( tmp.left_, tmp.bottom_-1 );
	context_->lineTo( tmp.left_, tmp.top_ );
	context_->lineTo( tmp.right_-1, tmp.top_ );
	context_->strokePath();

	context_->setColor( &hilite );
	context_->moveTo( tmp.right_, tmp.top_ );
	context_->lineTo( tmp.right_, tmp.bottom_ );
	context_->lineTo( tmp.left_, tmp.bottom_ );
	context_->strokePath();

	context_->setColor( &black );
	context_->moveTo( tmp.left_+1, tmp.bottom_-2 );
	context_->lineTo( tmp.left_+1, tmp.top_+1 );
	context_->lineTo( tmp.right_-2, tmp.top_+1 );
	context_->strokePath();

	context_->setColor( &face );
	context_->moveTo( tmp.right_-1, tmp.top_+1 );
	context_->lineTo( tmp.right_-1, tmp.bottom_-1 );
	context_->lineTo( tmp.left_+1, tmp.bottom_-1 );
	context_->strokePath();


	if ( state.isToggled() ) {

		if ( state.isEnabled() ) {
			context_->setColor( &black );
		}
		else {
			context_->setColor( &disabled );
		}

		context_->moveTo( tmp.left_ + 3, tmp.top_ + 7 );
		context_->lineTo( tmp.left_ + 5, tmp.top_ + 9 );
		context_->lineTo( tmp.left_ + 9, tmp.top_ + 5 );
		context_->lineTo( tmp.left_ + 9, tmp.top_ + 3 );
		context_->lineTo( tmp.left_ + 5, tmp.top_ + 7 );
		context_->closePath( tmp.left_ + 3, tmp.top_ + 5 );
		context_->fillPath();

	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	int gcs = context_->saveState();

	Size cb(13,13);

	context_->setStrokeWidth(0.5);
	Rect tmp = *rect;
	tmp.top_ = (int)(rect->top_ + rect->getHeight() /2.0 + 0.5);
	tmp.top_ -= cb.height_/2.0;
	tmp.bottom_ = tmp.top_ + cb.height_;
	tmp.right_ = tmp.left_ + cb.height_;

	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	Color wnd = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
	Color disabled = *GraphicsToolkit::getSystemColor( SYSCOLOR_INACTIVE_CAPTION );

	context_->setColor( &face );
	context_->rectangle( &tmp );
	context_->fillPath();

	context_->setColor( &shad );

	int w = cb.width_/2;
	int r = w;

	double angle = 360-45;
	context_->arc( tmp.left_ + w, tmp.top_ + w, r, r, angle+180, angle+360 );
	context_->strokePath();

	context_->setColor( &hilite );
	context_->arc( tmp.left_ + w, tmp.top_ + w, r, r, angle, angle+180 );
	context_->strokePath();

	r--;

	context_->setColor( &black );
	context_->arc( tmp.left_ + w, tmp.top_ + w, r, r, angle+180, angle+360 );
	context_->strokePath();

	context_->setColor( &face );
	context_->arc( tmp.left_ + w, tmp.top_ + w, r, r, angle, angle+180 );
	context_->strokePath();

	context_->setColor( &wnd );
	context_->circle( tmp.left_ + w, tmp.top_ + w, w-4 );
	context_->fillPath();



	if ( state.isToggled() ) {

		if ( state.isEnabled() ) {
			context_->setColor( &black );
		}
		else {
			context_->setColor( &disabled );
		}

		context_->circle( tmp.left_ + w, tmp.top_ + w, w-5 );
		context_->fillPath();
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	int gcs = context_->saveState();


	context_->setStrokeWidth(0.5);

	Rect tmp = *rect;


	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	Color wnd = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
	Color disabled = *GraphicsToolkit::getSystemColor( SYSCOLOR_INACTIVE_CAPTION );

	context_->setColor( &wnd );
	context_->rectangle( &tmp );
	context_->fillPath();


	context_->setColor( &shad );
	context_->moveTo( tmp.left_, tmp.bottom_-1 );
	context_->lineTo( tmp.left_, tmp.top_ );
	context_->lineTo( tmp.right_-1, tmp.top_ );
	context_->strokePath();

	context_->setColor( &hilite );
	context_->moveTo( tmp.right_, tmp.top_ );
	context_->lineTo( tmp.right_, tmp.bottom_ );
	context_->lineTo( tmp.left_, tmp.bottom_ );
	context_->strokePath();

	context_->setColor( &black );
	context_->moveTo( tmp.left_+1, tmp.bottom_-2 );
	context_->lineTo( tmp.left_+1, tmp.top_+1 );
	context_->lineTo( tmp.right_-2, tmp.top_+1 );
	context_->strokePath();

	context_->setColor( &face );
	context_->moveTo( tmp.right_-1, tmp.top_+1 );
	context_->lineTo( tmp.right_-1, tmp.bottom_-1 );
	context_->lineTo( tmp.left_+1, tmp.bottom_-1 );
	context_->strokePath();


	Rect btnR = tmp;
	btnR.right_ -= 2;
	btnR.left_ = btnR.right_ - 15;
	btnR.inflate( 0, -2 );

	context_->setColor( &face );
	context_->rectangle( &btnR );
	context_->fillPath();





	if ( state.isPressed() ) {
		context_->setColor( &face );
		context_->moveTo( btnR.left_, btnR.bottom_-1 );
		context_->lineTo( btnR.left_, btnR.top_ );
		context_->lineTo( btnR.right_-1, btnR.top_ );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( btnR.right_, btnR.top_ );
		context_->lineTo( btnR.right_, btnR.bottom_ );
		context_->lineTo( btnR.left_, btnR.bottom_ );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( btnR.left_+1, btnR.bottom_-2 );
		context_->lineTo( btnR.left_+1, btnR.top_+1 );
		context_->lineTo( btnR.right_-2, btnR.top_+1 );
		context_->strokePath();

		context_->setColor( &shad );
		context_->moveTo( btnR.right_-1, btnR.top_+1 );
		context_->lineTo( btnR.right_-1, btnR.bottom_-1 );
		context_->lineTo( btnR.left_+1, btnR.bottom_-1 );
		context_->strokePath();
	}
	else {
		context_->setColor( &shad );
		context_->moveTo( btnR.left_, btnR.bottom_-1 );
		context_->lineTo( btnR.left_, btnR.top_ );
		context_->lineTo( btnR.right_-1, btnR.top_ );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( btnR.right_, btnR.top_ );
		context_->lineTo( btnR.right_, btnR.bottom_ );
		context_->lineTo( btnR.left_, btnR.bottom_ );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( btnR.left_+1, btnR.bottom_-2 );
		context_->lineTo( btnR.left_+1, btnR.top_+1 );
		context_->lineTo( btnR.right_-2, btnR.top_+1 );
		context_->strokePath();

		context_->setColor( &face );
		context_->moveTo( btnR.right_-1, btnR.top_+1 );
		context_->lineTo( btnR.right_-1, btnR.bottom_-1 );
		context_->lineTo( btnR.left_+1, btnR.bottom_-1 );
		context_->strokePath();
	}

	double cx = btnR.left_ + btnR.getWidth()/2.0;
	double cy = btnR.top_ + btnR.getHeight()/2.0;

	context_->setColor( &black );
	context_->moveTo( cx - 3, cy-2 );
	context_->lineTo( cx + 3, cy-2 );
	context_->lineTo( cx, cy+2 );
	context_->closePath( cx-3, cy-2 );
	context_->fillPath();


	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	int gcs = context_->saveState();


	context_->setStrokeWidth(0.5);

	Rect tmp = *rect;


	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	Color wnd = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
	Color disabled = *GraphicsToolkit::getSystemColor( SYSCOLOR_INACTIVE_CAPTION );

	context_->setColor( &face );
	context_->rectangle( &tmp );
	context_->fillPath();
	bool pressed = state.isScrollBarIncrArrowPressed() || state.isScrollBarDecrArrowPressed();
	if ( pressed ) {
		context_->setColor( &face );
		context_->moveTo( tmp.left_, tmp.bottom_-1 );
		context_->lineTo( tmp.left_, tmp.top_ );
		context_->lineTo( tmp.right_-1, tmp.top_ );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( tmp.right_, tmp.top_ );
		context_->lineTo( tmp.right_, tmp.bottom_ );
		context_->lineTo( tmp.left_, tmp.bottom_ );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( tmp.left_+1, tmp.bottom_-2 );
		context_->lineTo( tmp.left_+1, tmp.top_+1 );
		context_->lineTo( tmp.right_-2, tmp.top_+1 );
		context_->strokePath();

		context_->setColor( &shad );
		context_->moveTo( tmp.right_-1, tmp.top_+1 );
		context_->lineTo( tmp.right_-1, tmp.bottom_-1 );
		context_->lineTo( tmp.left_+1, tmp.bottom_-1 );
		context_->strokePath();
	}
	else {
		context_->setColor( &shad );
		context_->moveTo( tmp.left_, tmp.bottom_-1 );
		context_->lineTo( tmp.left_, tmp.top_ );
		context_->lineTo( tmp.right_-1, tmp.top_ );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( tmp.right_, tmp.top_ );
		context_->lineTo( tmp.right_, tmp.bottom_ );
		context_->lineTo( tmp.left_, tmp.bottom_ );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( tmp.left_+1, tmp.bottom_-2 );
		context_->lineTo( tmp.left_+1, tmp.top_+1 );
		context_->lineTo( tmp.right_-2, tmp.top_+1 );
		context_->strokePath();

		context_->setColor( &face );
		context_->moveTo( tmp.right_-1, tmp.top_+1 );
		context_->lineTo( tmp.right_-1, tmp.bottom_-1 );
		context_->lineTo( tmp.left_+1, tmp.bottom_-1 );
		context_->strokePath();
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTab( Rect* rect, TabState& state )
{
	context_->setStrokeWidth(0.5);

	int gcs = context_->saveState();

	Color* hilite = GraphicsToolkit::getSystemColor(SYSCOLOR_HIGHLIGHT);
	Color* shadow = GraphicsToolkit::getSystemColor(SYSCOLOR_SHADOW);
	Color* face = GraphicsToolkit::getSystemColor(SYSCOLOR_FACE);
	Color* textColor = GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT );
	Color* selectedTextColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );

	context_->setColor( face );
	context_->rectangle( rect );
	context_->fillPath();
	Color oldFontColor;

	oldFontColor = *context_->getCurrentFont()->getColor();
	context_->getCurrentFont()->setColor( textColor );

	if ( state.isPressed() ) {
		context_->getCurrentFont()->setBold( true );
		context_->setColor( hilite );
		context_->moveTo(rect->left_ , rect->bottom_ -1 );
		context_->lineTo(rect->left_ , rect->top_ + 2 );
		context_->lineTo(rect->left_ + 2 , rect->top_ );
		context_->lineTo(rect->right_ - 2 , rect->top_);
		context_->strokePath();

		context_->setColor( Color::getColor( "black" ) );
		context_->moveTo( rect->right_ - 2 , rect->top_ + 1);
		context_->lineTo( rect->right_ - 1 , rect->top_ + 2);
		context_->lineTo( rect->right_ - 1 , rect->bottom_ );
		context_->strokePath();

		context_->setColor( shadow );
		context_->moveTo( rect->right_ - 2, rect->top_ + 2);
		context_->lineTo( rect->right_ - 2, rect->bottom_ );
		context_->strokePath();
	}
	else {
		context_->setColor( hilite );
		context_->moveTo(rect->left_ , rect->bottom_ );
		context_->lineTo(rect->left_ , rect->top_ + 2 );
		context_->lineTo(rect->left_ + 2 , rect->top_  );
		context_->lineTo(rect->right_ - 2 , rect->top_ );
		context_->strokePath();

		context_->setColor( Color::getColor( "black" ) );
		context_->moveTo( rect->right_ - 2 , rect->top_ + 1);
		context_->lineTo( rect->right_ - 1 , rect->top_ + 2);
		context_->lineTo( rect->right_ - 1 , rect->bottom_ );
		context_->strokePath();

		context_->setColor( shadow );
		context_->moveTo( rect->right_ - 2, rect->top_ + 2);
		context_->lineTo( rect->right_ - 2, rect->bottom_ );
		context_->strokePath();
	}

	Rect tmpR = *rect;

	tmpR.inflate( -4, 0 );
	tmpR.normalize();
	int32 flags = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;
	context_->textBoundedBy( &tmpR, state.tabCaption_, flags );

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	BackgroundState bkg;
	bkg.setEnabled( state.isEnabled() );
	bkg.setActive( state.isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;

	drawThemeBackground( rect, bkg );

	//Size sz = UIToolkit::getUIMetricSize( UIMetricsManager::mtTabSize );
}

void XCBContextPeer::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	BackgroundState bkg;
	bkg.setEnabled( state.isEnabled() );
	bkg.setActive( state.isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;

	drawThemeBackground( rect, bkg );
}

void XCBContextPeer::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex )
{
	int gcs = context_->saveState();

	BackgroundState bkg;
	bkg.setEnabled( paneState.isEnabled() );
	bkg.setActive( paneState.isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;

	context_->drawThemeBackground( rect, bkg );

	Font f = XCBGraphicsToolkit::getDefaultFontFor(CONTROLFONT);

	context_->setCurrentFont( &f );

	Rect tabRect = *rect;
	Rect selectedTabRect;
	String selectedTabText;
	double w = 0;
	for (size_t i=0; i<tabNames.size(); i ++ ) {
		const String& tab = tabNames[i];

		Size sz = XCBGraphicsToolkit::getSize( TABSIZE, tab, &f );
		w = sz.width_ + 5.0 + sz.height_;
		tabRect.right_ = tabRect.left_ + w;
		tabRect.bottom_ = tabRect.top_ + sz.height_;

		if ( selectedTabIndex == (int)i ) {
			selectedTabRect = tabRect;
			selectedTabText = tab;
		}
		else {
			TabState ts = otherTabs;
			ts.tabCaption_ = tab;
			drawThemeTab( &tabRect, ts );
		}

		tabRect.offset( w, 0 );
	}

	TabState sts = selectedTabState;
	sts.setPressed(true);
	sts.tabCaption_ = selectedTabText;
	drawThemeTab( &selectedTabRect, sts );

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	if ( state.tickMarkFrequency_ <= 0 ) {
		return;
	}

	int gcs = context_->saveState();

	context_->setStrokeWidth(0.5);

	context_->setColor( Color::getColor( "black" ) );

	double incr = 0;
	if ( state.isVertical() ) {
		incr = (1.0/(double)(state.tickMarkFrequency_)) * rect->getHeight();
	}
	else {
		incr = (1.0/(double)(state.tickMarkFrequency_)) * rect->getWidth();
	}

	double y = rect->top_;
	double x = rect->left_;

	for (long i=0;i<=state.tickMarkFrequency_;i++ ) {
		if ( state.isVertical() ) {


			if ( state.isTickMarkingOnTopLeft() ) {
				x = rect->left_;
				double x2 = x - 5;

				context_->moveTo( x, y );
				context_->lineTo( x2, y );
				context_->strokePath();
			}

			if ( state.isTickMarkingOnBottomRight() ) {
				x = rect->right_;
				double x2 = x + 5;

				context_->moveTo( x, y );
				context_->lineTo( x2, y );
				context_->strokePath();
			}
			y += incr;
		}
		else {
			if ( state.isTickMarkingOnTopLeft() ) {
				y = rect->top_;
				double y2 = y - 5;

				context_->moveTo( x, y );
				context_->lineTo( x, y2 );
				context_->strokePath();
			}

			if ( state.isTickMarkingOnBottomRight() ) {
				y = rect->bottom_;
				double y2 = y + 5;

				context_->moveTo( x, y );
				context_->lineTo( x, y2 );
				context_->strokePath();
			}
			x += incr;
		}
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeSlider( Rect* rect, SliderState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeProgress( Rect* rect, ProgressState& state )
{
	int gcs = context_->saveState();


	context_->setStrokeWidth(0.5);

	Rect tmp = *rect;


	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	Color wnd = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW );
	Color disabled = *GraphicsToolkit::getSystemColor( SYSCOLOR_INACTIVE_CAPTION );

	context_->setColor( &face );
	context_->rectangle( &tmp );
	context_->fillPath();

	context_->setColor( &shad );
	context_->moveTo( tmp.left_, tmp.bottom_-1 );
	context_->lineTo( tmp.left_, tmp.top_ );
	context_->lineTo( tmp.right_-1, tmp.top_ );
	context_->strokePath();

	context_->setColor( &hilite );
	context_->moveTo( tmp.right_, tmp.top_ );
	context_->lineTo( tmp.right_, tmp.bottom_ );
	context_->lineTo( tmp.left_, tmp.bottom_ );
	context_->strokePath();

	tmp.inflate( -2, -2 );

	Rect progressRect = tmp;

	double s = minVal<>( state.min_, state.max_ );
	double e = maxVal<>( state.min_, state.max_ );

	if ( state.isVertical() ) {
		progressRect.top_ = progressRect.bottom_ - ((state.position_/fabs(e-s)) * tmp.getHeight());
	}
	else {
		progressRect.right_ = progressRect.left_ + ((state.position_/(e-s)) * tmp.getWidth());
	}

	Color* progressBarColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION );

	if ( state.useCustomProgressColor() ) {
		progressBarColor = &state.customColor_;
	}

	context_->setColor( progressBarColor );
	context_->rectangle( progressRect );
	context_->fillPath();


	if ( !state.progressCaption_.empty() ) {
		Rect textBounds;

		if ( state.isVertical() ) {
			textBounds.left_ = progressRect.left_;
			textBounds.right_ = progressRect.right_;

			double h = minVal<>( context_->getTextHeight( "EM" ), tmp.getHeight()-2 );
			textBounds.top_ = tmp.top_ +
				(tmp.getHeight()/2.0 - h/2.0);

			textBounds.bottom_ = textBounds.top_ + h;

			textBounds.inflate( 0, 2 );
		}
		else {
			textBounds.top_ = progressRect.top_;
			textBounds.bottom_ = progressRect.bottom_;

			double w = minVal<>( context_->getTextWidth( state.progressCaption_ ), tmp.getWidth()-2 );

			textBounds.left_ = tmp.left_ +
				(tmp.getWidth()/2.0 - w/2.0);

			textBounds.right_ = textBounds.left_ + w;
		}

		int32 drawOptions = GraphicsContext::tdoNone;
		drawOptions |= GraphicsContext::tdoCenterHorzAlign;
		drawOptions |= GraphicsContext::tdoCenterVertAlign;


		Color* progressTextColor = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION_TEXT );
		if ( state.useCustomProgressTextColor() ) {
			progressTextColor = &state.customTextColor_;
		}
		context_->getCurrentFont()->setColor( progressTextColor );

		context_->textBoundedBy( &textBounds, state.progressCaption_, drawOptions );
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeHeader( Rect* rect, ButtonState& state )
{
	Color face = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	Color shad = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color hilite = *GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
	Color black("black");

	int gcs = context_->saveState();

	context_->setStrokeWidth(0.5);

	context_->setColor( &face );
	context_->rectangle( rect );
	context_->fillPath();

	if ( state.isEnabled() && state.isPressed() ) {
		context_->setColor( &black );
		context_->moveTo( rect->left_, rect->bottom_ );
		context_->lineTo( rect->left_, rect->top_ );
		context_->lineTo( rect->right_, rect->top_ );
		context_->strokePath();


		context_->setColor( &shad );
		context_->moveTo( rect->left_+1, rect->bottom_-1 );
		context_->lineTo( rect->left_+1, rect->top_+1 );
		context_->lineTo( rect->right_-1, rect->top_+1 );
		context_->strokePath();

		context_->setColor( &hilite );
		context_->moveTo( rect->right_, rect->top_+1 );
		context_->lineTo( rect->right_, rect->bottom_ );
		context_->lineTo( rect->left_+1, rect->bottom_ );
		context_->strokePath();
	}
	else {


		context_->setColor( &hilite );
		context_->moveTo( rect->left_, rect->bottom_ - 1 );
		context_->lineTo( rect->left_, rect->top_ );
		context_->lineTo( rect->right_-1, rect->top_ );
		context_->strokePath();


		context_->setColor( &shad );
		context_->moveTo( rect->right_-1, rect->top_ +1 );
		context_->lineTo( rect->right_-1, rect->bottom_ - 1 );
		context_->lineTo( rect->left_+1, rect->bottom_ - 1 );
		context_->strokePath();

		context_->setColor( &black );
		context_->moveTo( rect->right_, rect->top_ );
		context_->lineTo( rect->right_, rect->bottom_ );
		context_->lineTo( rect->left_, rect->bottom_ );
		context_->strokePath();
	}


	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeEdge( Rect* rect, DrawUIState& state, const int32& edgeSides, const int32& edgeStyle )
{
	int gcs = context_->saveState();
	Color* hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );

	Color shadow1 = *GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
	Color shadow2 = shadow1;
	int l = shadow2.getLuminosity();
	shadow2.setLuminosity( int(l * 0.5) );

	Color* face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );

	context_->setStrokeWidth(1);


	if ( edgeSides & GraphicsContext::etAllSides ) {

		context_->setColor( face );
		context_->rectangle( rect );
		context_->fillPath();


		switch ( edgeStyle ) {
			case GraphicsContext::etRecessed : {
				context_->setColor( hilight );
				context_->moveTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->strokePath();

				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );

				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_, rect->bottom_ );

				context_->strokePath();
			}
			break;

			case GraphicsContext::etEtched : {
				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );

				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_, rect->bottom_ );

				context_->strokePath();
			}
			break;

			case GraphicsContext::etRaised : {
				context_->setColor( face );
				context_->moveTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->strokePath();

				context_->setColor( &shadow2 );
				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_+1, rect->bottom_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );
				context_->strokePath();

				context_->setColor( &shadow1 );
				context_->moveTo( rect->right_-1, rect->top_+1 );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_+1, rect->bottom_-1 );
				context_->strokePath();
			}
			break;

			case GraphicsContext::etSunken : {
				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_+1, rect->bottom_ );
				context_->strokePath();

				context_->setColor( &shadow2 );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );
				context_->strokePath();

				context_->setColor( face );
				context_->moveTo( rect->right_-1, rect->top_+1 );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_+1, rect->bottom_-1 );
				context_->strokePath();
			}
			break;
		}
	}
	else {
		switch ( edgeStyle ) {
			case GraphicsContext::etRecessed : {
				if ( edgeSides & GraphicsContext::etLeftSide ) {
					context_->setColor( hilight );
					context_->moveTo( rect->left_, rect->top_ );
					context_->lineTo( rect->right_-1, rect->top_ );
					context_->lineTo( rect->right_-1, rect->bottom_-1 );
					context_->lineTo( rect->left_, rect->bottom_-1 );
					context_->lineTo( rect->left_, rect->top_ );
					context_->strokePath();
				}

				if ( edgeSides & GraphicsContext::etTopSide ) {
					context_->setColor( hilight );
					context_->moveTo( rect->left_, rect->top_ );
					context_->lineTo( rect->right_-1, rect->top_ );
					context_->lineTo( rect->right_-1, rect->bottom_-1 );
					context_->lineTo( rect->left_, rect->bottom_-1 );
					context_->lineTo( rect->left_, rect->top_ );
					context_->strokePath();
				}

				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );

				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_, rect->bottom_ );

				context_->strokePath();
			}
			break;

			case GraphicsContext::etEtched : {
				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );

				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_, rect->bottom_ );

				context_->strokePath();
			}
			break;

			case GraphicsContext::etRaised : {
				context_->setColor( face );
				context_->moveTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->strokePath();

				context_->setColor( &shadow2 );
				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_+1, rect->bottom_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );
				context_->strokePath();

				context_->setColor( &shadow1 );
				context_->moveTo( rect->right_-1, rect->top_+1 );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_+1, rect->bottom_-1 );
				context_->strokePath();
			}
			break;

			case GraphicsContext::etSunken : {
				context_->setColor( &shadow1 );
				context_->moveTo( rect->left_, rect->bottom_-1 );
				context_->lineTo( rect->left_, rect->top_ );
				context_->lineTo( rect->right_-1, rect->top_ );
				context_->strokePath();

				context_->setColor( hilight );
				context_->moveTo( rect->right_, rect->top_ );
				context_->lineTo( rect->right_, rect->bottom_ );
				context_->lineTo( rect->left_+1, rect->bottom_ );
				context_->strokePath();

				context_->setColor( &shadow2 );
				context_->moveTo( rect->left_+1, rect->bottom_-2 );
				context_->lineTo( rect->left_+1, rect->top_+1 );
				context_->lineTo( rect->right_-2, rect->top_+1 );
				context_->strokePath();

				context_->setColor( face );
				context_->moveTo( rect->right_-1, rect->top_+1 );
				context_->lineTo( rect->right_-1, rect->bottom_-1 );
				context_->lineTo( rect->left_+1, rect->bottom_-1 );
				context_->strokePath();
			}
			break;
		}
	}

	context_->restoreState( gcs );
}

void XCBContextPeer::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	int gcs = context_->saveState();

	Color* backColor = GraphicsToolkit::getSystemColor( state.colorType_ );

	if ( state.colorType_ == SYSCOLOR_WINDOW ) {
		backColor = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
	}

	context_->setColor( backColor );
	context_->rectangle( rect );
	context_->fillPath();

	context_->restoreState( gcs );
}



String generateMenuItemCaption( MenuState& state )
{
	String acceleratorText;

	//generate accelerator text if we are not owner drawn

	if ( state.hasControlKey() ) {
		acceleratorText += "Ctrl";
	}

	if ( state.hasShiftKey() ) {
		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}
		acceleratorText += "Shift";
	}

	if ( state.hasAltKey() ) {
		if ( !acceleratorText.empty() ) {
			acceleratorText += "+";
		}
		acceleratorText += "Alt";
	}

	if ( !acceleratorText.empty() ) {
		acceleratorText += "+";
	}

	acceleratorText +=
			StringUtils::translateVKCodeToString( (VirtualKeyCode)state.keyCode_ );


	String result = state.menuCaption_;

	if ( !acceleratorText.empty() ) {
		result = result + "\t" + acceleratorText;
	}

	return result;
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
	int gcs = context_->saveState();

	Font font;

	switch ( state.themeFontType_ ) {
		case GraphicsContext::ttMenuItemFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( MENUITEMFONT );
		}
		break;

		case GraphicsContext::ttSelectedMenuItemFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( SELECTEDMENUITEMFONT );
		}
		break;

		case GraphicsContext::ttSystemFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( SYSTEMFONT );
		}
		break;

		case GraphicsContext::ttSystemSmallFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( SYSTEMFONT );
		}
		break;

		case GraphicsContext::ttControlFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( CONTROLFONT );
		}
		break;

		case GraphicsContext::ttMessageFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( MESSAGEFONT );
		}
		break;

		case GraphicsContext::ttToolTipFont : {
			font = XCBGraphicsToolkit::getDefaultFontFor( TOOLTIPFONT );
		}
		break;
	}

	context_->setCurrentFont( &font );

	context_->textBoundedBy( rect, state.text_, state.wrapText_ );

	context_->restoreState( gcs );
}

void XCBContextPeer::internal_setImage(xcb_image_t *image)
{
	image_ = image;
}

/**
$Id$
*/

