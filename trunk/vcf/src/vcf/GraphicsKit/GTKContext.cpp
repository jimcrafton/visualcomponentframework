//GTKContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/MgcBezierCurve2.h"

using namespace VCF;

GTKContext::GTKContext():
	drawable_(NULL),
	gdkGC_(NULL),
	pixmapWidth_(0),
	pixmapHeight_(0),
	isMemoryCtx_(false),
	parentImage_(NULL),
	pangoCtx_(NULL),
	pangoLayout_(NULL),
	inFillPath_(false),
	isXORModeOn_(false)
{
	init();
}

GTKContext::GTKContext( const unsigned long& width, const unsigned long& height ):
	drawable_(NULL),
	gdkGC_(NULL),
	pixmapWidth_(width),
	pixmapHeight_(height),
	isMemoryCtx_(true),
	parentImage_(NULL),
	pangoCtx_(NULL),
	pangoLayout_(NULL),
	inFillPath_(false),
	isXORModeOn_(false)
{
	init();
}

GTKContext::GTKContext( const unsigned long& contextID ):
	drawable_(NULL),
	gdkGC_(NULL),
	pixmapWidth_(0),
	pixmapHeight_(0),
	isMemoryCtx_(false),
	parentImage_(NULL),
	pangoCtx_(NULL),
	pangoLayout_(NULL),
	inFillPath_(false),
	isXORModeOn_(false)
{
	drawable_ = (GdkDrawable*)contextID;
	init();
}

GTKContext::~GTKContext()
{
	if ( isMemoryCtx_ ) {
		g_object_unref( drawable_ );
	}

	g_object_unref( gdkGC_ );



	if ( NULL != pangoLayout_ ) {
		g_object_unref( pangoLayout_ );
	}
}

void GTKContext:: init()
{
	if ( (NULL == drawable_) && (pixmapWidth_>0) && (pixmapHeight_>0) ) {
		//create a new one, let gdk determine the depth from the root window
		drawable_ = gdk_pixmap_new( gdk_get_default_root_window(), pixmapWidth_, pixmapHeight_, -1 );
	}
	if ( NULL != drawable_ ) {
		gdkGC_ = gdk_gc_new ( drawable_ );
	}

	GTKGraphicsToolkit* toolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();

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


unsigned long GTKContext::getContextID()
{
	return (unsigned long)drawable_;
}

void GTKContext::setContextID( const unsigned long& handle )
{
	if ( isMemoryCtx_ ) {
		g_object_unref( drawable_ );
		isMemoryCtx_ = false;
	}
	drawable_ = (GdkDrawable*)handle;

	if ( NULL != drawable_ ) {
		if ( NULL != gdkGC_ ) {
			g_object_unref( gdkGC_ );
		}
		gdkGC_ = gdk_gc_new ( drawable_ );
	}
}


void GTKContext::setClippingPath( Path* clippingPath )
{
	checkHandle();

	std::vector<Point> points;
	clippingPath->flattenPoints( points );

	std::vector<Point>::iterator it = points.begin();
	std::vector<GdkPoint> pts;
	while ( it != points.end() ) {
		GdkPoint aPt;
		Point& pt = *it;
		aPt.x = (gint)(pt.x_ + origin_.x_);
		aPt.y = (gint)(pt.y_ + origin_.y_);
		pts.push_back( aPt );
		it ++;
	}

	GdkRegion* rgn = gdk_region_polygon( &pts[0], pts.size(),
											clippingPath->getWindingRule() == Path::wrEvenOdd ? GDK_EVEN_ODD_RULE : GDK_WINDING_RULE );

	gdk_gc_set_clip_region( gdkGC_, rgn );


	releaseHandle();
}

void GTKContext::setClippingRect( Rect* clipRect )
{
	checkHandle();

	GdkRectangle rect;
	rect.x = (gint)clipRect->left_;
	rect.y = (gint)clipRect->top_;
	rect.width = (gint)clipRect->getWidth();
	rect.height = (gint)clipRect->getHeight();

	gdk_gc_set_clip_rectangle( gdkGC_, &rect );

	releaseHandle();
}


void GTKContext::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	GTKImage* gtkImg = reinterpret_cast<GTKImage*>(image);
	GdkPixbuf* pb = gtkImg->getPixbuf();

	if ( ((ulong32)imageBounds->getWidth() > image->getWidth()) ||
			((ulong32)imageBounds->getHeight() > image->getHeight()) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Dimensions of image bounds exceed the image itself") );
	}


	gdk_draw_pixbuf( drawable_, gdkGC_, pb,
					(gint)imageBounds->left_,
					(gint)imageBounds->top_,
					(gint)(x + origin_.x_),
					(gint)(y + origin_.y_),
					(gint)imageBounds->getWidth(),
					(gint)imageBounds->getHeight(), GDK_RGB_DITHER_NORMAL, 0, 0 );

}

void GTKContext::textAt(const Rect& bounds, const String & text, const long& drawOptions )
{
	pango_layout_set_text ( pangoLayout_, (char *)text.ansi_c_str(), text.size());

	PangoFontDescription* pf = (PangoFontDescription*)context_->getCurrentFont()->getFontPeer()->getFontHandleID();

	pango_context_set_font_description( pangoCtx_, pf );

	PangoAlignment alignment = PANGO_ALIGN_LEFT;

	gint x = (gint)bounds.left_;
	gint y = (gint)bounds.top_;

	if ( drawOptions & GraphicsContext::tdoLeftAlign ) {
		alignment = PANGO_ALIGN_LEFT;
	}
	else if ( drawOptions & GraphicsContext::tdoCenterHorzAlign ) {
		alignment = PANGO_ALIGN_CENTER;
	}
	else if ( drawOptions & GraphicsContext::tdoRightAlign ) {
		alignment = PANGO_ALIGN_RIGHT;
	}

	pango_layout_set_alignment ( pangoLayout_, alignment );

	if ( drawOptions & GraphicsContext::tdoWordWrap ) {
		pango_layout_set_width( pangoLayout_, (gint)bounds.getWidth() );
	}
	else {
		pango_layout_set_width( pangoLayout_, -1 );
	}


	pango_layout_context_changed ( pangoLayout_ );


	if ( drawOptions & GraphicsContext::tdoTopAlign ) {
		//formatOptions |= DT_TOP;
	}
	else if ( drawOptions & GraphicsContext::tdoCenterVertAlign ) {
		int height = 0;
		pango_layout_get_pixel_size (pangoLayout_, NULL, &height );

		y = (gint)(bounds.left_ + ( bounds.getHeight()/2.0 - (double)height/2.0 ));
		//formatOptions |= DT_VCENTER;
	}
	else if ( drawOptions & GraphicsContext::tdoBottomAlign ) {
		int height = 0;
		pango_layout_get_pixel_size (pangoLayout_, NULL, &height );

		y = (gint)(bounds.left_ + ( bounds.getHeight() - (double)height ));
	}

	gdk_draw_layout( drawable_, gdkGC_, x, y, pangoLayout_ );

}


double GTKContext::getTextWidth( const String& text )
{
	pango_layout_set_text ( pangoLayout_, (char *)text.ansi_c_str(), text.size());
	int width = 0;
	pango_layout_get_pixel_size (pangoLayout_, &width, NULL);
	return width;
}

double GTKContext::getTextHeight( const String& text )
{
	int height = 0;
	pango_layout_get_pixel_size (pangoLayout_, NULL, &height );
	return height;
}

void GTKContext::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	Rect r(x1,y1,x2,y2);

	r.offset( origin_.x_, origin_.y_ );

	gdk_draw_rectangle( drawable_,
						gdkGC_,
						inFillPath_,
						(gint)r.left_,
						(gint)r.top_,
						(gint)r.getWidth(),
						(gint)r.getHeight() );
}


void GTKContext::ellipse( const double & x1, const double & y1, const double & x2, const double & y2 )
{
	Rect r(x1,y1,x2,y2);

	r.offset( origin_.x_, origin_.y_ );

	gdk_draw_arc(  drawable_,
					gdkGC_,
					inFillPath_,
					(gint)r.left_,
					(gint)r.top_,
					(gint)r.getWidth(),
					(gint)r.getHeight(), 0, 360*64 );
}

void GTKContext::arc( const double & x1, const double & y1, const double & x2, const double & y2,
				  const double & x3, const double & y3, const double & x4, const double & y4 )
{
	//swap out the values to ensure they are normalized since windows is brain dead about this


}


void GTKContext::polyline( const std::vector<Point>& pts)
{
	std::vector<Point>::const_iterator it = pts.begin();

	std::vector<GdkPoint> xPts;
	std::vector<GdkPoint>::iterator ptIt = xPts.begin();

	xPts.resize( pts.size(), GdkPoint() );

	while ( it != pts.end() ){
		(*ptIt).x = (gint)((*it).x_ + origin_.x_);
		(*ptIt).y = (gint)((*it).y_ + origin_.y_);
		ptIt ++;
		it++;
	}

	if ( !xPts.empty() ) {
		if ( inFillPath_ ) {
			gdk_draw_polygon( drawable_, gdkGC_, TRUE, (GdkPoint*)&xPts[0], xPts.size() );
		}
		else {
			gdk_draw_lines( drawable_, gdkGC_, (GdkPoint*)&xPts[0], xPts.size() );
		}
	}
}

void GTKContext::curve(const double & x1, const double & y1, const double & x2, const double & y2,
					 const double & x3, const double & y3, const double & x4, const double & y4)
{
	int degree = 3; //3rd degree bezier poly - needs 4 controls
	Mgc::Vector2* bezPts = new Mgc::Vector2[4];
	bezPts[0][0] = (long)(x1 + origin_.x_);
	bezPts[0][1] = (long)(y1 + origin_.y_);

	bezPts[1][0] = (long)(x2 + origin_.x_);
	bezPts[1][1] = (long)(y2 + origin_.y_);

	bezPts[2][0] = (long)(x3 + origin_.x_);
	bezPts[2][1] = (long)(y3 + origin_.y_);

	bezPts[3][0] = (long)(x4 + origin_.x_);
	bezPts[3][1] = (long)(y4 + origin_.y_);


	Mgc::BezierCurve2 bezCurve( degree, bezPts );

	//get the length over the duration of the curve from
	//t= 0.0 to t=1.0
	double length = bezCurve.GetLength(0.0, 0.1250 );
	double max = bezCurve.GetMaxTime();
	double min = bezCurve.GetMinTime();
	double t = min;
	std::vector<GdkPoint> xPts;

	double dt = (max - min) / length;
	while ( t < max ) {
		Mgc::Vector2 vec = bezCurve.GetPosition( t );
		GdkPoint pt = {0};
		pt.x = (gint)vec[0];
		pt.y = (gint)vec[1];
		xPts.push_back( pt );
		t += dt;
	}

	if ( !xPts.empty() ) {
		if ( inFillPath_ ) {
			gdk_draw_polygon( drawable_, gdkGC_, TRUE, &xPts[0], xPts.size() );
		}
		else {
			gdk_draw_lines( drawable_, gdkGC_, &xPts[0], xPts.size() );
		}

	}
}

void GTKContext::lineTo(const double & x, const double & y)
{

	gdk_draw_line( drawable_, gdkGC_,
					(int)(currentMoveTo_.x_ + origin_.x_),
					(int)(currentMoveTo_.y_ + origin_.y_),
					(int)(x + origin_.x_),
					(int)(y + origin_.y_) );

	currentMoveTo_.x_ = x;
	currentMoveTo_.y_ = y;
}

void GTKContext::moveTo(const double & x, const double & y)
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
	if ( NULL != sourceContext ){
		checkHandle();

		gdk_draw_drawable( drawable_, gdkGC_,
						(GdkDrawable*)sourceContext->getContextID(),
						(gint)sourceRect.left_, (gint)sourceRect.top_,
						(gint)(destRect.left_ + origin_.x_ ),
						(gint)(destRect.top_ + origin_.y_ ),
						(gint)destRect.getWidth(),
						(gint)destRect.getHeight() );

		releaseHandle();
	}
}

bool GTKContext::isMemoryContext()
{
	return isMemoryCtx_;
}

void GTKContext::checkHandle()
{
	if ( NULL != parentImage_ ) {
		parentImage_->updatePixmapFromImageBits();
	}
}

void GTKContext::releaseHandle()
{
	if ( NULL != parentImage_ ) {
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
	GtkStyle* result = NULL;

	if ( (NULL != widget) && GTK_IS_WIDGET(widget) ) {
		result = widget->style;
	}
	else {
		GTKGraphicsToolkit* toolkit = (GTKGraphicsToolkit*)GraphicsToolkit::internal_getDefaultGraphicsToolkit();
		result = toolkit->getDefaultGTKStyle();
	}

	return result;
}

GtkStateType GTKContext::getGTKState( GtkWidget* widget )
{
	GtkStateType result = GTK_STATE_NORMAL;

	if ( (NULL != widget) && GTK_IS_WIDGET(widget) ) {
		result = (GtkStateType)GTK_WIDGET_STATE(widget);
	}

	return result;
}

void GTKContext::drawSelectionRect( Rect* rect )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_paint_focus ( style, drawable_,
						getGTKState(widget),
						&r,
						widget,
						NULL,
						r.x,
						r.y,
						r.width,
						r.height );
}

void GTKContext::drawButtonRect( Rect* rect, const bool& isPressed )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_paint_box ( style, drawable_,
						getGTKState(widget),
						isPressed ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
						&r,
						widget,
						"button",
						r.x,
						r.y,
						r.width,
						r.height );

}

void GTKContext::drawCheckboxRect( Rect* rect, const bool& isPressed )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_paint_check ( style, drawable_,
						getGTKState(widget),
						isPressed ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
						&r,
						widget,
						"button",
						r.x,
						r.y,
						r.width,
						r.height );
}

void GTKContext::drawRadioButtonRect( Rect* rect, const bool& isPressed )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_paint_option ( style, drawable_,
						getGTKState(widget),
						isPressed ? GTK_SHADOW_IN : GTK_SHADOW_OUT,
						&r,
						widget,
						"button",
						r.x,
						r.y,
						r.width,
						r.height );
}

void GTKContext::drawVerticalScrollButtonRect( Rect* rect, const bool& topButton, const bool& isPressed )
{

}

void GTKContext::drawDisclosureButton( Rect* rect, const long& state )
{

}

void GTKContext::drawHorizontalScrollButtonRect( Rect* rect, const bool& leftButton, const bool& isPressed )
{

}

void GTKContext::drawTab( Rect* rect, const bool& selected, const String& caption )
{

}

void GTKContext::drawTabPage( Rect* rect )
{

}

void GTKContext::drawTickMarks( Rect* rect, const SliderInfo& sliderInfo  )
{

}

void GTKContext::drawSliderThumb( Rect* rect, const SliderInfo& sliderInfo )
{

}

void GTKContext::drawSlider( Rect* rect, const SliderInfo& sliderInfo )
{

}

void GTKContext::drawHeader( Rect* rect )
{

}

void GTKContext::drawEdge( Rect* rect, const long& edgeSides, const long& edgeStyle )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	GtkShadowType shadow = GTK_SHADOW_NONE;

	switch ( edgeStyle ) {
		case GraphicsContext::etRecessed : {
			shadow = GTK_SHADOW_IN;
		}
		break;

		case GraphicsContext::etEtched : {
			shadow = GTK_SHADOW_ETCHED_IN;
		}
		break;

		case GraphicsContext::etRaised : {
			shadow = GTK_SHADOW_ETCHED_OUT;
		}
		break;

		case GraphicsContext::etSunken : {
			shadow = GTK_SHADOW_OUT;
		}
		break;
	}

	if ( GTK_SHADOW_NONE == shadow ) {
		return ;
	}

	if ( (edgeSides & GraphicsContext::etLeftSide) &&
			(edgeSides & GraphicsContext::etRightSide) &&
			(edgeSides & GraphicsContext::etTopSide) &&
			(edgeSides & GraphicsContext::etBottomSide) ) {

		gtk_paint_box( style, drawable_,
						getGTKState(widget), shadow, &r,
						widget,
						"button",
						r.x,
						r.y,
						r.width,
						r.height );
	}
	else {
		if ( edgeSides & GraphicsContext::etLeftSide ) {
			gtk_paint_vline( style, drawable_, getGTKState(widget),
							&r,	widget,	"",
							r.y, r.y + r.height, r.x );
		}

		if ( edgeSides & GraphicsContext::etRightSide ) {
			gtk_paint_vline( style, drawable_, getGTKState(widget),
							&r,	widget,	"",
							r.y, r.y + r.height, r.x + r.width );
		}

		if ( edgeSides & GraphicsContext::etTopSide ) {
			gtk_paint_hline( style, drawable_, getGTKState(widget),
							&r,	widget,	"",
							r.x, r.x + r.width, r.y );
		}

		if ( edgeSides & GraphicsContext::etBottomSide ) {
			gtk_paint_hline( style, drawable_, getGTKState(widget),
							&r,	widget,	"",
							r.x, r.x + r.width, r.y + r.height );
		}
	}
}

void GTKContext::drawSizeGripper( Rect* rect )
{

}

void GTKContext::drawControlBackground( Rect* rect )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_style_apply_default_background ( style,widget->window, FALSE,
                                             getGTKState(widget),
                                             &r, r.x, r.y, r.width, r.height);
}

void GTKContext::drawWindowBackground( Rect* rect )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_style_apply_default_background ( style,widget->window, FALSE,
                                             getGTKState(widget),
                                             &r, r.x, r.y, r.width, r.height);
}

void GTKContext::drawMenuItemBackground( Rect* rect, const bool& selected )
{
	GdkRectangle r = {(gint)rect->left_, (gint)rect->top_, (gint)rect->getWidth(), (gint)rect->getHeight() };

	GtkWidget* widget = NULL;
	gdk_window_get_user_data( drawable_, (gpointer*)&widget );
	GtkStyle* style = getGTKStyle( widget );

	gtk_style_apply_default_background ( style,widget->window, FALSE,
                                             getGTKState(widget),
                                             &r, r.x, r.y, r.width, r.height);
}


bool GTKContext::prepareForDrawing( long drawingOperation )
{
	bool result = false;

	checkHandle();

	inFillPath_ = false;

	if ( NULL != gdkGC_ ){

		Color* current = context_->getColor();

		GdkColor color;
		color.red = (guint16)(current->getRed() * 65535.0);
		color.green = (guint16)(current->getGreen() * 65535.0);
		color.blue = (guint16)(current->getBlue() * 65535.0);

		gdk_gc_set_rgb_fg_color( gdkGC_, &color );

		gdk_gc_set_fill( gdkGC_, GDK_SOLID );


		if ( isXORModeOn_ ) {
			GdkGCValues values;
			values.function = GDK_XOR;

			gdk_gc_set_values( gdkGC_, &values, GDK_GC_FUNCTION );
		}
		else {
			GdkGCValues values;
			values.function = GDK_COPY;

			gdk_gc_set_values( gdkGC_, &values, GDK_GC_FUNCTION );
		}

		GraphicsContext::DrawingOperation op = (GraphicsContext::DrawingOperation)drawingOperation;



		switch ( op ) {
			case GraphicsContext::doStroke : {


				gdk_gc_set_line_attributes( gdkGC_, (gint)context_->getStrokeWidth(), GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER );



			}
			break;

			case GraphicsContext::doFill : {


				inFillPath_ = true;
			}
			break;

			case GraphicsContext::doText : {

				Font* ctxFont = context_->getCurrentFont();

				Color* fontColor = ctxFont->getColor();

				color.red = (guint16)(fontColor->getRed() * 65535.0);
				color.green = (guint16)(fontColor->getGreen() * 65535.0);
				color.blue = (guint16)(fontColor->getBlue() * 65535.0);

				gdk_gc_set_rgb_fg_color( gdkGC_, &color );

			}
			break;

			case GraphicsContext::doImage : {

			}
			break;
		}


		result = true;
	}

	return result;
}

void GTKContext::finishedDrawing( long drawingOperation )
{
	if ( NULL == gdkGC_ ){
		throw InvalidPointerException( MAKE_ERROR_MSG_2("GdkGC handle is NULL!!!") );
	}

	pango_layout_set_width( pangoLayout_, -1 );

	releaseHandle();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/09 21:12:50  thrysoee
*Fix VCF::String (Unicode) related segfaults on Linux
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.5  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.2.4  2003/11/01 20:35:23  ddiego
*added GTKToolbar class impl - no real functionality at this point
*
*Revision 1.4.2.3  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.4.2.2  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.4.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.4  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.3.2.4  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.3.2.3  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.3.2.2  2003/06/01 16:44:00  ddiego
*further GTK support added
*
*Revision 1.3.2.1  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.3  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.5  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.2.2.4  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.3  2003/04/14 19:06:25  ddiego
*mods to add better support for fonts and text using Pango. Not
*finished and may not compile! :)
*
*Revision 1.2.2.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:48  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/23 05:08:46  ddiego
*finished up the GTKImage class. Now putting in text rendering with pango support
*
*Revision 1.1.2.1  2003/02/20 02:46:03  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
Auto generated C++ implementation for class GTKContext
*/


