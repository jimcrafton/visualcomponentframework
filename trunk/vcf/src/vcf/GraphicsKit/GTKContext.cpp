//GTKContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h" 
//#include "vcf/FoundationKit/VCFMath.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

GTKContext::GTKContext()
		: drawable_( 0 )
		, gdkGC_( 0 )
		, pangoCtx_( 0 )
		, pangoLayout_( 0 )
		, pixmapWidth_( 0 )
		, pixmapHeight_( 0 )
		//, pathOperations_()
		//, textOperations_()
		, currentMoveTo_()
		, oldOrigin_()
		, origin_()
		, inFillPath_( false )
		, isMemoryCtx_( false )
		//, pathStarted_(false)
		, isXORModeOn_( false )
		, alignToBaseline_( false )
		, context_( 0 )
		, parentImage_( 0 )
{
	this->init();
}

GTKContext::GTKContext( const unsigned long& width, const unsigned long& height )
		: drawable_( 0 )
		, gdkGC_( 0 )
		, pangoCtx_( 0 )
		, pangoLayout_( 0 )
		, pixmapWidth_( width )
		, pixmapHeight_( height )
		//, pathOperations_()
		//, textOperations_()
		, currentMoveTo_()
		, oldOrigin_()
		, origin_()
		, inFillPath_( false )
		, isMemoryCtx_( false )
		//, pathStarted_(false)
		, isXORModeOn_( false )
		, alignToBaseline_( false )
		, context_( 0 )
		, parentImage_( 0 )
{
	this->init();
}

GTKContext::GTKContext( OSHandleID contextID )
		: drawable_( reinterpret_cast<GdkDrawable*>( contextID ) )
		, gdkGC_( 0 )
		, pangoCtx_( 0 )
		, pangoLayout_( 0 )
		, pixmapWidth_( 0 )
		, pixmapHeight_( 0 )
		//, pathOperations_()
		//, textOperations_()
		, currentMoveTo_()
		, oldOrigin_()
		, origin_()
		, inFillPath_( false )
		, isMemoryCtx_( false )
		//, pathStarted_(false)
		, isXORModeOn_( false )
		, alignToBaseline_( false )
		, context_( 0 )
		, parentImage_( 0 )
{
	this->init();
}

GTKContext::~GTKContext()
{
	if ( isMemoryCtx_ ) {
		g_object_unref( drawable_ );
	}

	g_object_unref( gdkGC_ );

	if ( pangoLayout_ ) {
		g_object_unref( pangoLayout_ );
	}
}

void GTKContext::init()
{
	if ( ( ! drawable_ ) and ( pixmapWidth_ > 0 ) and ( pixmapHeight_ > 0 ) ) {
		//create a new one, let gdk determine the depth from the root window
		drawable_ = gdk_pixmap_new( gdk_get_default_root_window(),
		                            pixmapWidth_,
		                            pixmapHeight_,
		                            -1 );
	}
	if ( drawable_ ) {
		gdkGC_ = gdk_gc_new( drawable_ );
	}

	GTKGraphicsToolkit* toolkit =
	    static_cast<GTKGraphicsToolkit*>(
	        GraphicsToolkit::internal_getDefaultGraphicsToolkit() );

	pangoCtx_ = toolkit->getGTKPangoContext();

	pangoLayout_ = pango_layout_new( pangoCtx_ );
}

void GTKContext::setContext( GraphicsContext* context )
{
	context_ = context;
}

GraphicsContext* GTKContext::getContext()
{
	return context_;
}

OSHandleID GTKContext::getContextID()
{
	return reinterpret_cast<OSHandleID>( drawable_ );
}

void GTKContext::setContextID( OSHandleID contextID )
{
	if ( isMemoryCtx_ ) {
		g_object_unref( drawable_ );
		isMemoryCtx_ = false;
	}

	drawable_ = reinterpret_cast<GdkDrawable*>( contextID );
	if ( drawable_ ) {
		if ( gdkGC_ ) {
			g_object_unref( gdkGC_ );
		}
		gdkGC_ = gdk_gc_new( drawable_ );
	}
}

void GTKContext::setClippingPath( Path* clippingPath )
{
	this->checkHandle();

	std::vector<Point> points;
	clippingPath->flattenPoints( points );

	std::vector<GdkPoint> pts;
	for ( std::vector<Point>::iterator pt = points.begin();
	        pt != points.end();
	        ++pt ) {
		GdkPoint aPt;
		aPt.x = gint( ( *pt ).x_ + origin_.x_ );
		aPt.y = gint( ( *pt ).y_ + origin_.y_ );
		pts.push_back( aPt );
	}

	GdkRegion* rgn =
	    gdk_region_polygon( &pts[ 0 ],
	                        pts.size(),
	                        ( clippingPath->getWindingRule() == Path::wrEvenOdd )
	                        ? GDK_EVEN_ODD_RULE
	                        : GDK_WINDING_RULE );

	gdk_gc_set_clip_region( gdkGC_, rgn );

	this->releaseHandle();
}

void GTKContext::setClippingRect( Rect* clipRect )
{
	this->checkHandle();

	GdkRectangle rect;
	rect.x = gint( clipRect->left_ );
	rect.y = gint( clipRect->top_ );
	rect.width = gint( clipRect->getWidth() );
	rect.height = gint( clipRect->getHeight() );

	gdk_gc_set_clip_rectangle( gdkGC_, &rect );

	this->releaseHandle();
}


void GTKContext::drawImage( const double& x,
                            const double& y,
                            Rect* imageBounds,
                            Image* image )
{
	GTKImage * gtkImg = reinterpret_cast<GTKImage*>( image );
	GdkPixbuf* pb = gtkImg->getPixbuf();

	if ( ulong32( imageBounds->getWidth() ) > image->getWidth()
	        or ulong32( imageBounds->getHeight() ) > image->getHeight() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2(
		                            "Dimensions of image bounds exceed the "
		                            "image itself" ) );
	}

	gdk_draw_pixbuf( drawable_,
	                 gdkGC_,
	                 pb,
	                 gint( imageBounds->left_ ),
	                 gint( imageBounds->top_ ),
	                 gint( x + origin_.x_ ),
	                 gint( y + origin_.y_ ),
	                 gint( imageBounds->getWidth() ),
	                 gint( imageBounds->getHeight() ),
	                 GDK_RGB_DITHER_NORMAL,
	                 0,
	                 0 );
}

void GTKContext::textAt( const Rect& bounds,
                         const String & text,
                         const long& drawOptions )
{
	pango_layout_set_text( pangoLayout_, text.ansi_c_str(), text.size() );

	PangoFontDescription* pf =
	    reinterpret_cast<PangoFontDescription*>( context_->getCurrentFont()
	                                             ->getFontPeer()
	                                             ->getFontHandleID() );

	pango_context_set_font_description( pangoCtx_, pf );

	PangoAlignment alignment = PANGO_ALIGN_LEFT;

	gint x = gint( bounds.left_ );
	gint y = gint( bounds.top_ );

	if ( drawOptions & GraphicsContext::tdoLeftAlign ) {
		alignment = PANGO_ALIGN_LEFT;
	} else if ( drawOptions & GraphicsContext::tdoCenterHorzAlign ) {
		alignment = PANGO_ALIGN_CENTER;
	} else if ( drawOptions & GraphicsContext::tdoRightAlign ) {
		alignment = PANGO_ALIGN_RIGHT;
	}

	pango_layout_set_alignment( pangoLayout_, alignment );

	if ( drawOptions & GraphicsContext::tdoWordWrap ) {
		pango_layout_set_width( pangoLayout_, gint( bounds.getWidth() ) );
	} else {
		pango_layout_set_width( pangoLayout_, -1 );
	}

	pango_layout_context_changed( pangoLayout_ );

	if ( drawOptions & GraphicsContext::tdoTopAlign ) {
		//formatOptions |= DT_TOP;
	} else if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
		int height = 0;
		pango_layout_get_pixel_size( pangoLayout_, 0, &height );

		y = gint( bounds.left_
		          + ( double( bounds.getHeight() ) / 2.0
		              - double( height ) / 2.0 ) );
		//formatOptions |= DT_VCENTER;
	} else if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
		int height = 0;
		pango_layout_get_pixel_size( pangoLayout_, 0, &height );

		y = gint( bounds.left_ + ( bounds.getHeight() - height ) );
	}

	gdk_draw_layout( drawable_, gdkGC_, x, y, pangoLayout_ );
}

double GTKContext::getTextWidth( const String& text )
{
	pango_layout_set_text( pangoLayout_, text.ansi_c_str(), text.size() );
	int width = 0;
	pango_layout_get_pixel_size( pangoLayout_, &width, 0 );
	return width;
}

double GTKContext::getTextHeight( const String& text )
{
	int height = 0;
	pango_layout_get_pixel_size( pangoLayout_, 0, &height );
	return height;
}

void GTKContext::rectangle( const double & x1,
                            const double & y1,
                            const double & x2,
                            const double & y2 )
{
	Rect r( x1, y1, x2, y2 );
	r.offset( origin_.x_, origin_.y_ );
	gdk_draw_rectangle( drawable_,
	                    gdkGC_,
	                    inFillPath_,
	                    gint( r.left_ ),
	                    gint( r.top_ ),
	                    gint( r.getWidth() ),
	                    gint( r.getHeight() ) );
}

void GTKContext::ellipse( const double & x1,
                          const double & y1,
                          const double & x2,
                          const double & y2 )
{
	Rect r( x1, y1, x2, y2 );
	r.offset( origin_.x_, origin_.y_ );
	gdk_draw_arc( drawable_,
	              gdkGC_,
	              inFillPath_,
	              gint( r.left_ ),
	              gint( r.top_ ),
	              gint( r.getWidth() ),
	              gint( r.getHeight() ),
	              0,
	              360 * 64 );
}

void GTKContext::arc( const double & x1,
                      const double & y1,
                      const double & x2,
                      const double & y2,
                      const double & x3,
                      const double & y3,
                      const double & x4,
                      const double & y4 )
{
	//swap out the values to ensure they are normalized since windows is
	//brain dead about this
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::polyline( const std::vector<Point>& pts )
{
	std::vector<GdkPoint> xPts;
	xPts.resize( pts.size(), GdkPoint() );
	std::vector<GdkPoint>::iterator ptIt = xPts.begin();
	for ( std::vector<Point>::const_iterator it = pts.begin();
	        it != pts.end();
	        ++it, ++ptIt ) {
		( *ptIt ).x = gint( ( *it ).x_ + origin_.x_ );
		( *ptIt ).y = gint( ( *it ).y_ + origin_.y_ );
	}

	if ( !xPts.empty() ) {
		if ( inFillPath_ ) {
			gdk_draw_polygon( drawable_,
			                  gdkGC_,
			                  TRUE,
			                  &xPts[ 0 ],
			                  xPts.size() );
		} else {
			gdk_draw_lines( drawable_,
			                gdkGC_,
			                &xPts[ 0 ],
			                xPts.size() );
		}
	}
}

void GTKContext::curve( const double & x1,
                        const double & y1,
                        const double & x2,
                        const double & y2,
                        const double & x3,
                        const double & y3,
                        const double & x4,
                        const double & y4 )
{
	// 	int degree = 3; //3rd degree bezier poly - needs 4 controls
	// 	Mgc::Vector2* bezPts = new Mgc::Vector2[ 4 ];
	// 	bezPts[ 0 ][ 0 ] = long( x1 + origin_.x_ );
	// 	bezPts[ 0 ][ 1 ] = long( y1 + origin_.y_ );
	// 	bezPts[ 1 ][ 0 ] = long( x2 + origin_.x_ );
	// 	bezPts[ 1 ][ 1 ] = long( y2 + origin_.y_ );
	// 	bezPts[ 2 ][ 0 ] = long( x3 + origin_.x_ );
	// 	bezPts[ 2 ][ 1 ] = long( y3 + origin_.y_ );
	// 	bezPts[ 3 ][ 0 ] = long( x4 + origin_.x_ );
	// 	bezPts[ 3 ][ 1 ] = long( y4 + origin_.y_ );
	//
	// 	Mgc::BezierCurve2 bezCurve( degree, bezPts );
	//
	// 	//get the length over the duration of the curve from
	// 	//t= 0.0 to t=1.0
	// 	double length = bezCurve.GetLength( 0.0, 0.1250 );
	// 	double max = bezCurve.GetMaxTime();
	// 	double min = bezCurve.GetMinTime();
	// 	double dt = ( max - min ) / length;
	//
	// 	std::vector<GdkPoint> xPts;
	// 	for ( double t = min ; t < max; t += dt ) {
	// 		Mgc::Vector2 vec = bezCurve.GetPosition( t );
	// 		GdkPoint pt;
	// 		pt.x = gint( vec[ 0 ] );
	// 		pt.y = gint( vec[ 1 ] );
	// 		xPts.push_back( pt );
	// 	}
	//
	// 	if ( !xPts.empty() ) {
	// 		if ( inFillPath_ ) {
	// 			gdk_draw_polygon( drawable_, gdkGC_, TRUE, &xPts[ 0 ], xPts.size() );
	// 		} else {
	// 			gdk_draw_lines( drawable_, gdkGC_, &xPts[ 0 ], xPts.size() );
	// 		}
	// 	}
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::lineTo( const double & x, const double & y )
{
	gdk_draw_line( drawable_, gdkGC_,
	               int( currentMoveTo_.x_ + origin_.x_ ),
	               int( currentMoveTo_.y_ + origin_.y_ ),
	               int( x + origin_.x_ ),
	               int( y + origin_.y_ ) );

	currentMoveTo_.x_ = x;
	currentMoveTo_.y_ = y;
}

void GTKContext::moveTo( const double & x, const double & y )
{
	currentMoveTo_.x_ = x;
	currentMoveTo_.y_ = y;
}

void GTKContext::setOrigin( const double& x, const double& y )
{
	origin_.x_ = x;
	origin_.y_ = y;
}

Point GTKContext::getOrigin()
{
	return origin_;
}

void GTKContext::copyContext( const Rect& sourceRect,
                              const Rect& destRect,
                              ContextPeer* sourceContext )
{
	if ( sourceContext ) {
		this->checkHandle();

		gdk_draw_drawable( drawable_,
		                   gdkGC_,
		                   reinterpret_cast<GdkDrawable*>(
		                       sourceContext->getContextID() ),
		                   gint( sourceRect.left_ ),
		                   gint( sourceRect.top_ ),
		                   gint( destRect.left_ + origin_.x_ ),
		                   gint( destRect.top_ + origin_.y_ ),
		                   gint( destRect.getWidth() ),
		                   gint( destRect.getHeight() ) );

		releaseHandle();
	}
}

bool GTKContext::isMemoryContext()
{
	return isMemoryCtx_;
}

void GTKContext::checkHandle()
{
	if ( parentImage_ ) {
		parentImage_->updatePixmapFromImageBits();
	}
}

void GTKContext::releaseHandle()
{
	if ( parentImage_ ) {
		parentImage_->updateImageBitsFromPixmap();
	}
}

bool GTKContext::isXORModeOn()
{
	return isXORModeOn_;
}

void GTKContext::setXORModeOn( const bool& XORModeOn )
{
	isXORModeOn_ = XORModeOn;
}

void GTKContext::setTextAlignment( const bool& alignTobaseline )
{
	alignToBaseline_ = alignTobaseline;
}

bool GTKContext::isTextAlignedToBaseline()
{
	return alignToBaseline_;
}

GtkStyle* GTKContext::getGTKStyle( GtkWidget* widget )
{
	if ( widget and GTK_IS_WIDGET( widget ) ) {
		return widget->style;
	} else {
		GTKGraphicsToolkit* toolkit =
		    static_cast<GTKGraphicsToolkit*>(
		        GraphicsToolkit::internal_getDefaultGraphicsToolkit() );
		return toolkit->getDefaultGTKStyle();
	}

}

GtkStateType GTKContext::getGTKState( GtkWidget* widget )
{
	GtkStateType result = GTK_STATE_NORMAL;

	if ( widget and GTK_IS_WIDGET( widget ) ) {
		result = GtkStateType( GTK_WIDGET_STATE( widget ) );
	}

	return result;
}

// void GTKContext::drawSelectionRect( Rect* rect )
// {
// 	GdkRectangle r = { gint( rect->left_ ),
// 	                   gint( rect->top_ ),
// 	                   gint( rect->getWidth() ),
// 	                   gint( rect->getHeight() ) };
//
// 	GtkWidget* widget = 0;
// 	gdk_window_get_user_data( drawable_, &widget );
// 	GtkStyle* style = getGTKStyle( widget );
//
// 	gtk_paint_focus( style,
// 	                 drawable_,
// 	                 getGTKState( widget ),
// 	                 &r,
// 	                 widget,
// 	                 0,
// 	                 r.x,
// 	                 r.y,
// 	                 r.width,
// 	                 r.height );
// }

// void GTKContext::drawButtonRect( Rect* rect, const bool& isPressed )
// {
// 		GdkRectangle r = { gint( rect->left_ ),
// 		                   gint( rect->top_ ),
// 		                   gint( rect->getWidth() ),
// 		                   gint( rect->getHeight() ) };
//
// 	GtkWidget * widget = 0;
// 	gdk_window_get_user_data( drawable_, &widget );
// 	GtkStyle* style = getGTKStyle( widget );
//
// 	gtk_paint_box( style, drawable_,
// 	               getGTKState( widget ),
// 	               ( isPressed ) ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
// 	               &r,
// 	               widget,
// 	               "button",
// 	               r.x,
// 	               r.y,
// 	               r.width,
// 	               r.height );
//
// }

// void GTKContext::drawCheckboxRect( Rect* rect, const bool& isPressed )
// {
// 	GdkRectangle r = { gint( rect->left_ ),
// 	                   gint( rect->top_ ),
// 	                   gint( rect->getWidth() ),
// 	                   gint( rect->getHeight() ) };
//
// 	GtkWidget* widget = 0;
// 	gdk_window_get_user_data( drawable_, &widget );
// 	GtkStyle* style = getGTKStyle( widget );
//
// 	gtk_paint_check( style, drawable_,
// 	                 getGTKState( widget ),
// 	                 ( isPressed ) ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
// 	                 &r,
// 	                 widget,
// 	                 "button",
// 	                 r.x,
// 	                 r.y,
// 	                 r.width,
// 	                 r.height );
// }

void GTKContext::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	GdkRectangle r = { gint( rect->left_ ),
	                   gint( rect->top_ ),
	                   gint( rect->getWidth() ),
	                   gint( rect->getHeight() ) };

	gpointer widgetPtr = 0;
	gdk_window_get_user_data( drawable_, &widgetPtr );
	GtkWidget* widget = reinterpret_cast<GtkWidget*>( &widgetPtr );
	GtkStyle* style = getGTKStyle( widget );

	gtk_paint_option( style, drawable_,
	                  getGTKState( widget ),
	                  ( state.isPressed() ) ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
	                  &r,
	                  widget,
	                  "button",
	                  r.x,
	                  r.y,
	                  r.width,
	                  r.height );
}

void GTKContext::drawThemeProgress( Rect* rect, ProgressState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

// void GTKContext::drawVerticalScrollButtonRect( Rect* rect,
//                                                const bool& topButton,
//                                                const bool& isPressed )
// {}

// void GTKContext::drawDisclosureButton( Rect* rect, const long& state )
// {}

// void GTKContext::drawHorizontalScrollButtonRect( Rect* rect,
//                                                  const bool& leftButton,
//                                                  const bool& isPressed )
// {}

// void GTKContext::drawTab( Rect* rect, const bool& selected, const String& caption )
// {}

// void GTKContext::drawTabPage( Rect* rect )
// {}

// void GTKContext::drawTickMarks( Rect* rect, const SliderInfo& sliderInfo )
// {}

// void GTKContext::drawSliderThumb( Rect* rect, const SliderInfo& sliderInfo )
// {}

// void GTKContext::drawSlider( Rect* rect, const SliderInfo& sliderInfo )
// {}

// void GTKContext::drawHeader( Rect* rect )
// {}

// void GTKContext::drawEdge( Rect* rect, const long& edgeSides, const long& edgeStyle )
// {
// 	GdkRectangle r = { gint( rect->left_ ),
// 	                   gint( rect->top_ ),
// 	                   gint( rect->getWidth() ),
// 	                   gint( rect->getHeight() ) };
//
// 	GtkWidget* widget = 0;
// 	gdk_window_get_user_data( drawable_, &widget );
// 	GtkStyle* style = getGTKStyle( widget );
//
// 	GtkShadowType shadow = GTK_SHADOW_NONE;
//
// 	switch ( edgeStyle ) {
// 		case GraphicsContext::etRecessed : {
// 				shadow = GTK_SHADOW_IN;
// 			}
// 			break;
//
// 		case GraphicsContext::etEtched : {
// 				shadow = GTK_SHADOW_ETCHED_IN;
// 			}
// 			break;
//
// 		case GraphicsContext::etRaised : {
// 				shadow = GTK_SHADOW_ETCHED_OUT;
// 			}
// 			break;
//
// 		case GraphicsContext::etSunken : {
// 				shadow = GTK_SHADOW_OUT;
// 			}
// 			break;
// 	}
//
// 	if ( GTK_SHADOW_NONE == shadow ) {
// 		return ;
// 	}
//
// 	if ( edgeSides & GraphicsContext::etLeftSide
// 	        and edgeSides & GraphicsContext::etRightSide
// 	        and edgeSides & GraphicsContext::etTopSide
// 	        and edgeSides & GraphicsContext::etBottomSide ) {
//
// 		gtk_paint_box( style, drawable_,
// 		               getGTKState( widget ),
// 		               shadow,
// 		               &r,
// 		               widget,
// 		               "button",
// 		               r.x,
// 		               r.y,
// 		               r.width,
// 		               r.height );
// 	} else {
// 		if ( edgeSides & GraphicsContext::etLeftSide ) {
// 			gtk_paint_vline( style, drawable_, getGTKState( widget ),
// 			                 &r, widget, "",
// 			                 r.y, r.y + r.height, r.x );
// 		}
//
// 		if ( edgeSides & GraphicsContext::etRightSide ) {
// 			gtk_paint_vline( style, drawable_, getGTKState( widget ),
// 			                 &r, widget, "",
// 			                 r.y, r.y + r.height, r.x + r.width );
// 		}
//
// 		if ( edgeSides & GraphicsContext::etTopSide ) {
// 			gtk_paint_hline( style, drawable_, getGTKState( widget ),
// 			                 &r, widget, "",
// 			                 r.x, r.x + r.width, r.y );
// 		}
//
// 		if ( edgeSides & GraphicsContext::etBottomSide ) {
// 			gtk_paint_hline( style, drawable_, getGTKState( widget ),
// 			                 &r, widget, "",
// 			                 r.x, r.x + r.width, r.y + r.height );
// 		}
// 	}
// }

// void GTKContext::drawSizeGripper( Rect* rect )
// {}

// void GTKContext::drawControlBackground( Rect* rect )
// {
// 	GdkRectangle r = { gint( rect->left_ ),
// 	                   gint( rect->top_ ),
// 	                   gint( rect->getWidth() ),
// 	                   gint( rect->getHeight() ) };
//
// 	GtkWidget* widget = 0;
// 	gdk_window_get_user_data( drawable_, &widget );
// 	GtkStyle* style = getGTKStyle( widget );
//
// 	gtk_style_apply_default_background( style, widget->window, FALSE,
// 	                                    getGTKState( widget ),
// 	                                    &r, r.x, r.y, r.width, r.height );
// }

void GTKContext::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	GdkRectangle r = { gint( rect->left_ ),
	                   gint( rect->top_ ),
	                   gint( rect->getWidth() ),
	                   gint( rect->getHeight() ) };

	gpointer widgetPtr = 0;
	gdk_window_get_user_data( drawable_, &widgetPtr );
	GtkWidget* widget = reinterpret_cast<GtkWidget*>( &widgetPtr );
	GtkStyle* style = getGTKStyle( widget );

	gtk_style_apply_default_background( style,
	                                    widget->window,
	                                    FALSE,
	                                    getGTKState( widget ),
	                                    &r,
	                                    r.x,
	                                    r.y,
	                                    r.width,
	                                    r.height );
}

void GTKContext::drawThemeMenuItem( Rect* rect, MenuState& state )
{
	GdkRectangle r = { gint( rect->left_ ),
	                   gint( rect->top_ ),
	                   gint( rect->getWidth() ),
	                   gint( rect->getHeight() ) };

	gpointer widgetPtr = 0;
	gdk_window_get_user_data( drawable_, &widgetPtr );
	GtkWidget* widget = reinterpret_cast<GtkWidget*>( &widgetPtr );
	GtkStyle* style = getGTKStyle( widget );

	gtk_style_apply_default_background( style,
	                                    widget->window,
	                                    FALSE,
	                                    getGTKState( widget ),
	                                    &r,
	                                    r.x,
	                                    r.y,
	                                    r.width,
	                                    r.height );
}

bool GTKContext::prepareForDrawing( long drawingOperation )
{
	this->checkHandle();
	inFillPath_ = false;

	if ( gdkGC_ ) {
		Color * current = context_->getColor();
		GdkColor color;
		color.red = guint16( current->getRed() * 65535.0 );
		color.green = guint16( current->getGreen() * 65535.0 );
		color.blue = guint16( current->getBlue() * 65535.0 );
		gdk_gc_set_rgb_fg_color( gdkGC_, &color );
		gdk_gc_set_fill( gdkGC_, GDK_SOLID );

		GdkGCValues values;
		values.function = ( isXORModeOn_ )
		                  ? GDK_XOR
		                  : GDK_COPY;

		gdk_gc_set_values( gdkGC_, &values, GDK_GC_FUNCTION );

		GraphicsContext::DrawingOperation op =
		    GraphicsContext::DrawingOperation( drawingOperation );

		switch ( op ) {
			case GraphicsContext::doStroke : {
					gdk_gc_set_line_attributes( gdkGC_,
					                            gint( context_->getStrokeWidth() ),
					                            GDK_LINE_SOLID,
					                            GDK_CAP_BUTT,
					                            GDK_JOIN_MITER );
				}
				break;

			case GraphicsContext::doFill : {
					inFillPath_ = true;
				}
				break;

			case GraphicsContext::doText : {
					Font* ctxFont = context_->getCurrentFont();
					Color* fontColor = ctxFont->getColor();
					color.red = guint16( fontColor->getRed() * 65535.0 );
					color.green = guint16( fontColor->getGreen() * 65535.0 );
					color.blue = guint16( fontColor->getBlue() * 65535.0 );
					gdk_gc_set_rgb_fg_color( gdkGC_, &color );

				}
				break;

			case GraphicsContext::doImage : {}
				break;
		}
		return true;
	}
	return false;
}

void GTKContext::finishedDrawing( long drawingOperation )
{
	if ( ! gdkGC_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2(
		                                   "GdkGC handle is 0!!!" ) );
	}
	pango_layout_set_width( pangoLayout_, -1 );
	this->releaseHandle();
}

void GTKContext::roundRect( const double & x1,
                            const double & y1,
                            const double & x2,
                            const double & y2,
                            const double & xc,
                            const double & yc )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

bool GTKContext::isAntiAliasingOn()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return false;
}

void GTKContext::setAntiAliasingOn( bool antiAliasingOn )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeDisclosureButton( Rect* rect,
                                            DisclosureButtonState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeTab( Rect* rect, TabState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeSlider( Rect* rect, SliderState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeHeader( Rect* rect, ButtonState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeEdge( Rect* rect, DrawUIState& state,
                                const long& edgeSides,
                                const long& edgeStyle )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeText( Rect* rect, TextState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeMenuItemText( Rect* rect, MenuState& state )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeButtonFocusRect( Rect* rect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKContext::bitBlit( const double& x, const double& y, Image* image )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

/**
$Id$
*/
