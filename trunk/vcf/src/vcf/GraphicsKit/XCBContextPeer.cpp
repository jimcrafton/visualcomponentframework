
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"
#include "thirdparty/common/agg/include/agg_font_freetype.h"



typedef agg::font_engine_freetype_int32 XCBFontEngineType;
typedef agg::font_cache_manager<XCBFontEngineType> XCBFontManagerType;

namespace VCF {
struct FontStruct {
	FontStruct(): engine(), mgr(engine){}
	
	XCBFontEngineType engine;
	XCBFontManagerType mgr;
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
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

double XCBContextPeer::getTextWidth( const String& text )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

double XCBContextPeer::getTextHeight( const String& text )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
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

