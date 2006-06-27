//X11Context.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/MgcBezierCurve2.h"


using namespace VCF;



X11Context::X11Context():
	X11Display_(NULL),
	x11GC_(0),
	x11Drawable_(0),
	pixmapHeight_(0),
	pixmapWidth_(0),
	parentImage_(NULL),
	memoryImage_(0),
	memoryImageAlpha_(0)
{
	init();
}

X11Context::X11Context( const uint32& width, const uint32& height ):
	X11Display_(NULL),
	x11GC_(0),
	x11Drawable_(0),
	pixmapHeight_(height),
	pixmapWidth_(width),
	parentImage_(NULL),
	memoryImage_(0),
	memoryImageAlpha_(0)
{
	//create a pixmap here
	//x11Drawable_

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	X11Display_ = toolkit->getX11Display();
	int x11screen = toolkit->getX11ScreenID();

	memoryImage_ = imlib_create_image( pixmapWidth_, pixmapHeight_ );

	imlib_context_set_image( memoryImage_ );

	imlib_context_set_drawable( DefaultRootWindow( X11Display_ ) );

	imlib_render_pixmaps_for_whole_image( &x11Drawable_, &memoryImageAlpha_ );

	imlib_context_set_image(0);

	//printf( "Created a backing image of %d by %d pixels for X11Context::X11Context()\n", pixmapWidth_, pixmapHeight_ );

	init();
	isMemoryCtx_ = true;
}

X11Context::X11Context( const int32& contextID ):
	x11GC_(0),
	x11Drawable_(0),
	parentImage_(NULL),
	memoryImage_(0),
	memoryImageAlpha_(0)
{
	x11Drawable_ = (Drawable)contextID;
	init();
}

X11Context::~X11Context()
{
	clearBuffer();


	if ( 0 != x11GC_ ) {
		XFreeGC( X11Display_, x11GC_ );
	}

	/*
	if ( (true == isMemoryCtx_) && (NULL != x11Drawable_) ) {
		XFreePixmap(X11Display_, x11Drawable_);
	}
	*/

	if ( (true == isMemoryCtx_) && (NULL != memoryImage_) ) {
		imlib_context_set_image( memoryImage_ );

		imlib_free_image_and_decache();

		if ( NULL != x11Drawable_ ) {
			imlib_free_pixmap_and_mask( x11Drawable_ );
		}
	}
}

void X11Context::init()
{

	pathOperations_.clear();
	textOperations_.clear();
	pathStarted_ = false;
	isMemoryCtx_ = false;
	oldOrigin_.x_ = 0.0;
	oldOrigin_.y_ = 0.0;
	origin_.x_ = 0.0;
	origin_.y_ = 0.0;
	isXORModeOn_ = false;
	alignToBaseline_ = false;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	X11Display_ = toolkit->getX11Display();

	createDefaultGC();
}


void X11Context::releaseHandle()
{
	clearBuffer();


	if ( NULL != parentImage_ ) {
		imlib_context_set_drawable( parentImage_->getPixMap() );
		imlib_context_set_image( parentImage_->getXImage() );
		imlib_copy_drawable_to_image( parentImage_->getAlphaMaskPixMap(), 0, 0,
										parentImage_->getWidth(), parentImage_->getHeight(),
										0, 0, 0 );

	}
	imlib_context_set_drawable(0);
}

void X11Context::checkHandle()
{
	imlib_context_set_drawable(x11Drawable_);
	//printf( "X11Context::checkHandle() x11Drawable_: %p\n", x11Drawable_ );
	if ( NULL != parentImage_ ) {
		parentImage_->updateImageDataFromImageBits();
	}
}



void X11Context::setCurrentFontState(VCF::FontState * state)
{
	currentFontState_ = *state;
}

VCF::FontState* X11Context::getCurrentFontState()
{
	return &currentFontState_;
}

void X11Context::drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	checkHandle();
	if ( (imageBounds->getWidth() > image->getWidth()) || (imageBounds->getHeight() > image->getHeight()) ) {
		throw BasicException( MAKE_ERROR_MSG("Invalid image bounds requested"), __LINE__);
	}

	Rect tmpBounds = *imageBounds;
	tmpBounds.offset( origin_.x_, origin_.y_ );

	X11Image* x11Image = reinterpret_cast<X11Image*>( image );
	Imlib_Image imImage = x11Image->getXImage();
	imlib_context_set_image( imImage );

	int width = (int)tmpBounds.getWidth();
	int height = (int)tmpBounds.getHeight();

	imlib_render_image_part_on_drawable_at_size( (int)tmpBounds.left_, (int)tmpBounds.top_, width, height,
												(int)(x + origin_.x_), (int)(y + origin_.y_), width, height );

	imlib_context_set_image( 0 );


	releaseHandle();
}

void X11Context::drawImageWithinBounds( Rect* bounds, Image* image )
{
	checkHandle();

	Rect tmpBounds = *bounds;
	tmpBounds.offset( origin_.x_, origin_.y_ );

	X11Image* x11Image = reinterpret_cast<X11Image*>( image );
	Imlib_Image imImage = x11Image->getXImage();
	imlib_context_set_image( imImage );

	int width = minVal<int>( (int)tmpBounds.getWidth(), image->getWidth() );
	int height = minVal<int>( (int)tmpBounds.getHeight(), image->getHeight() );

	imlib_render_image_part_on_drawable_at_size( 0, 0, width, height,
												(int)tmpBounds.left_, (int)tmpBounds.top_,
												width, height );

	imlib_context_set_image( 0 );

	releaseHandle();
}

void X11Context::drawImage( const double & x, const double & y, Image* image )
{
	checkHandle();

	X11Image* x11Image = reinterpret_cast<X11Image*>( image );

	Imlib_Image imImage = x11Image->getXImage();

	imlib_context_set_image( imImage );
	imlib_render_image_on_drawable( (int)(x + origin_.x_), (int)(y + origin_.y_) );

	imlib_context_set_image( 0 );

	releaseHandle();
}

void X11Context::textAt(const double & x, const double & y, const String & text, const int32& drawOptions)
{
	if ( text.empty() ) {
		return;
	}

	checkHandle();

	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
	}
	X11Font* fontImpl = reinterpret_cast<X11Font*>( ctxFont->getFontPeer() );

	if ( NULL == fontImpl ){
		//throw exception
	}

	int oldRed = 0;
	int oldGreen = 0;
	int oldBlue = 0;
	int oldAlpha = 0;

	imlib_context_get_color( &oldRed, &oldGreen, &oldBlue, &oldAlpha );

	Imlib_Font imFont = (Imlib_Font)fontImpl->getFontHandleID();
	if ( NULL == imFont ) {
		throw InvalidPointerException(MAKE_ERROR_MSG_2("(Imlib_Font)fontImpl->getFontHandleID() returned NULL! in X11Context::textAt()"));
	}
	Color* fontColor = ctxFont->getColor();
	imlib_context_set_font( imFont );

	imlib_context_set_color( (int)fontColor->getRed()*255, (int)fontColor->getGreen()*255, (int)fontColor->getBlue()*255, 255 );

	int textWidth = 0;
	int textHeight = 0;

	std::vector<String> lines;

	simpleLineBreak( text, lines );

	if ( !lines.empty() ) {
		std::vector<String>::iterator it = lines.begin();
		std::vector<int> lineHeights;
		lineHeights.resize( lines.size(), 0 );
		std::vector<int>::iterator lhIter = lineHeights.begin();
		//calculate dimensions
		while ( it != lines.end() ) {
			String& lineOfText = *it;
			int w = 0;
			int h = 0;
			imlib_get_text_size( lineOfText.c_str(), &w, &h );

			textWidth = maxVal<int>( textWidth, w );
			textHeight += h;

			*lhIter = h;

			it ++;
			lhIter ++;
		}

		if ( textHeight > 0 && textWidth > 0 ) {
			int ix = (int)(x + origin_.x_);
			int iy = (int)(y + origin_.y_);
			Imlib_Image oldImage = imlib_context_get_image();

			Imlib_Image fontImage = imlib_create_image_frodrawable_( 0, ix, iy, textWidth, textHeight, 0 );
			if ( fontImage ) {
				imlib_context_set_image( fontImage );
				int x = 0;
				int y = 0;
				std::vector<String>::iterator it = lines.begin();
				std::vector<int>::iterator lhIter = lineHeights.begin();
				while ( it != lines.end() ) {
					String& lineOfText = *it;

					imlib_text_draw( x, y, lineOfText.c_str() );

					y += *lhIter;

					it ++;
					lhIter ++;
				}

				imlib_render_image_on_drawable( ix, iy );

				imlib_free_image_and_decache();
			}

			imlib_context_set_image( oldImage );
		}
	}


	imlib_context_set_color( oldRed, oldGreen, oldBlue, oldAlpha );

	releaseHandle();
}

void X11Context::textBoundedBy( Rect* bounds, const String& text, const int32& drawOptions )
{
	textAt( bounds->left_, bounds->top_, text, drawOptions );
}

void X11Context::arc( const double & x1, const double & y1, const double & x2, const double & y2,
                      const double & x3, const double & y3, const double & x4, const double & y4 )
{
	testBuffer();
	pathStarted_ = true;
	//swap out the values to ensure they are normalized since windows is brain dead about this
	double ax1 = x1;
	double ay1 = y1;
	double ax2 = x2;
	double ay2 = y2;

	double tmp = x2;
	if ( ax1 > ax2 ) {
		ax2 = ax1;
		ax1 = tmp;
	}
	tmp = ay2;
	if ( ay1 > ay2 ) {
		ay2 = ay1;
		ay1 = tmp;
	}
	PointOperation* newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ARC;
	newPointOp->x = ax1;
	newPointOp->y = ay1;
	pathOperations_.push_back( newPointOp );

	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ARC;
	newPointOp->x = ax2;
	newPointOp->y = ay2;
	pathOperations_.push_back( newPointOp );

	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ARC;
	newPointOp->x = x3;
	newPointOp->y = y3;
	pathOperations_.push_back( newPointOp );

	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ARC;
	newPointOp->x = x4;
	newPointOp->y = y4;
	pathOperations_.push_back( newPointOp );
}

void X11Context::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	testBuffer();
	pathStarted_ = true;
	PointOperation* newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_RECT;
	newPointOp->x = x1;
	newPointOp->y = y1;
	pathOperations_.push_back( newPointOp );

	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_RECT;
	newPointOp->x = x2;
	newPointOp->y = y2;
	pathOperations_.push_back( newPointOp );

}

void X11Context::circle(const double & x, const double & y, const double & radius)
{
	ellipse( x - radius, y - radius, x + radius, y + radius );
}

void X11Context::ellipse(const double & x1, const double & y1, const double & x2, const double & y2, const double & angle)
{
	testBuffer();
	pathStarted_ = true;
	//swap out the values to ensure they are normalized since windows is brain dead about this
	double ax1 = x1;
	double ay1 = y1;
	double ax2 = x2;
	double ay2 = y2;

	double tmp = x2;
	if ( ax1 > ax2 ) {
		ax2 = ax1;
		ax1 = tmp;
	}
	tmp = ay2;
	if ( ay1 > ay2 ) {
		ay2 = ay1;
		ay1 = tmp;
	}
	PointOperation* newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ELLIPSE;
	newPointOp->x = ax1;
	newPointOp->y = ay1;
	pathOperations_.push_back( newPointOp );

	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_ELLIPSE;
	newPointOp->x = ax2;
	newPointOp->y = ay2;
	pathOperations_.push_back( newPointOp );

}

void X11Context::setCurrentStrokeState(VCF::StrokeState * state)
{
	currentStroke_ = *state;
}

void X11Context::setCurrentFillState(VCF::FillState * state)
{
	currentFill_ = *state;
}

void X11Context::polyline( std::vector<Point*> & pts)
{
	testBuffer();
	pathStarted_ = true;
	std::vector<Point*>::iterator it = pts.begin();
	PointOperation* newPointOp = NULL;
	while ( it != pts.end() ){
		newPointOp = new PointOperation();
		newPointOp->primitive = PRIMITIVE_POLYLINE;
		newPointOp->x = (*it)->x_;
		newPointOp->y = (*it)->y_;
		pathOperations_.push_back( newPointOp );
		it++;
	}
}

void X11Context::curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4 )
{
	testBuffer();
	pathStarted_ = true;
	PointOperation* newPointOp = NULL;
	//start point 1
	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_BEZIER;
	newPointOp->x = x1;
	newPointOp->y = y1;
	pathOperations_.push_back( newPointOp );

	//start point 1
	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_BEZIER;
	newPointOp->x = x2;
	newPointOp->y = y2;
	pathOperations_.push_back( newPointOp );

	//start point 1
	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_BEZIER;
	newPointOp->x = x3;
	newPointOp->y = y3;
	pathOperations_.push_back( newPointOp );

	//start point 1
	newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_BEZIER;
	newPointOp->x = x4;
	newPointOp->y = y4;
	pathOperations_.push_back( newPointOp );
}

void X11Context::lineTo(const double & x, const double & y)
{
	testBuffer();
	pathStarted_ = true;
	PointOperation* newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_LINE;
	newPointOp->x = x;
	newPointOp->y = y;
	pathOperations_.push_back( newPointOp );
}

void X11Context::moveTo(const double & x, const double & y)
{
	testBuffer();
	pathStarted_ = true;
	PointOperation* newPointOp = new PointOperation();
	newPointOp->primitive = PRIMITIVE_MOVE;
	newPointOp->x = x;
	newPointOp->y = y;
	pathOperations_.push_back( newPointOp );
}

void X11Context::testBuffer()
{
	/**
	*means the path has been finished by a call to fill or stroke path
	*/
	if ( false == pathStarted_ ){
		clearBuffer();
	}
}

void X11Context::fillPath()
{
	checkHandle();

	inFillPath_ = true;
	pathStarted_ = false;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

	uint32 pixel =  toolkit->getPixelForColor( &currentFill_.Color_ );

	XSetForeground ( X11Display_, x11GC_, pixel );
	XSetBackground ( X11Display_, x11GC_, pixel );

	imlib_context_set_color( currentFill_.Color_.getRed()*255, currentFill_.Color_.getGreen()*255, currentFill_.Color_.getBlue()*255, 0 );

	XSetLineAttributes( X11Display_, x11GC_, 0, LineSolid,
				CapProjecting, JoinMiter );

	execPathOperations();

	releaseHandle();
}

void X11Context::strokePath()
{
	checkHandle();

	inFillPath_ = false;
	pathStarted_ = false;

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

	uint32 pixel =  toolkit->getPixelForColor( &currentStroke_.Color_ );

	XSetForeground ( X11Display_, x11GC_, pixel );

	imlib_context_set_color( currentStroke_.Color_.getRed()*255, currentStroke_.Color_.getGreen()*255, currentStroke_.Color_.getBlue()*255, 0 );

	int joinStyle = JoinMiter;
	int capStyle = CapProjecting;

	XSetLineAttributes( X11Display_, x11GC_, (int)currentStroke_.width_,
				translateStrokeStyle( currentStroke_.style_ ),
				capStyle, joinStyle );


	execPathOperations();


	releaseHandle();
}

void X11Context::clearBuffer()
{
	clearPathBuffer();
	clearTextBuffer();
}

void X11Context::clearPathBuffer()
{
	std::vector<PointOperation*>::iterator pts = pathOperations_.begin();
	while ( pts != pathOperations_.end() ){
		delete (*pts);
		pts++;
	}
	pathOperations_.clear();
}

void X11Context::clearTextBuffer()
{

}

int32 X11Context::translateFillStyle( const FillStyle& fillState )
{
	int32 result = 0;

	return result;
}

int32 X11Context::translateHatch( const FillStyle& fillState )
{
	int32 result = 0;

	return result;
}

void X11Context::execPathOperations()
{
	std::vector<PointOperation*>::iterator pts = pathOperations_.begin();
	int32 remaingOps = pathOperations_.size();

	PointOperation* prevPointOp = NULL;

	while ( (pts != pathOperations_.end()) && (remaingOps > 0) ){
		PointOperation* pointOp = *pts;
		if ( NULL != pointOp ){
			switch ( pointOp->primitive ){
				case PRIMITIVE_MOVE:{
					currentMoveTo_.x_ = pointOp->x;
					currentMoveTo_.y_ = pointOp->y;
					prevPointOp = NULL;
				}
				break;

				case PRIMITIVE_LINE:{

					if ( NULL != prevPointOp ) {

						xDrawLine( prevPointOp->x + origin_.x_, prevPointOp->y + origin_.y_,
									pointOp->x + origin_.x_, pointOp->y + origin_.y_ );
								

					}
					else {

						xDrawLine( currentMoveTo_.x_ + origin_.x_, currentMoveTo_.y_ + origin_.y_,
								pointOp->x + origin_.x_, pointOp->y + origin_.y_ );

					}

					prevPointOp = pointOp;
				}
				break;

				case PRIMITIVE_POLYLINE:{
					std::vector<PointOperation*> tmpPts;
					std::vector<XPoint> xPts;
					PointOperation* tmpPtOp = NULL;
					ImlibPolygon poly = imlib_polygon_new();
					while ( (pts != pathOperations_.end()) && (pointOp->primitive == PRIMITIVE_POLYLINE) ) {
						XPoint pt = {0};
						pt.x = (short)(pointOp->x + origin_.x_);
						pt.y = (short)(pointOp->y + origin_.y_);
						imlib_polygon_add_point( poly, (int)(pointOp->x + origin_.x_), (int)(pointOp->y + origin_.y_) );
						xPts.push_back( pt );
						pts++;
						pointOp = *pts;
						remaingOps --;
					}

					if ( !xPts.empty() ) {
						xDrawLines( poly, (XPoint*)xPts.begin(), xPts.size() );
					}

					imlib_polygon_free( poly );

					tmpPts.clear();
				}
				break;

				case PRIMITIVE_BEZIER:{
					if ( (remaingOps - 4) < 0 ){
						//throw exception !!
					}

					int degree = 3; //3rd degree bezier poly - needs 4 controls
					Mgc::Vector2* bezPts = new Mgc::Vector2[4];
					bezPts[0][0] = (int32)(pointOp->x + origin_.x_);
					bezPts[0][1] = (int32)(pointOp->y + origin_.y_);
					pts++;
					pointOp = *pts;
					bezPts[1][0] = (int32)(pointOp->x + origin_.x_);
					bezPts[1][1] = (int32)(pointOp->y + origin_.y_);
					pts++;
					pointOp = *pts;
					bezPts[2][0] = (int32)(pointOp->x + origin_.x_);
					bezPts[2][1] = (int32)(pointOp->y + origin_.y_);
					pts++;
					pointOp = *pts;
					bezPts[3][0] = (int32)(pointOp->x + origin_.x_);
					bezPts[3][1] = (int32)(pointOp->y + origin_.y_);


					Mgc::BezierCurve2 bezCurve( degree, bezPts );

					//get the length over the duration of the curve from
					//t= 0.0 to t=1.0
					double length = bezCurve.GetLength(0.0, 0.1250 );
					double max = bezCurve.GetMaxTime();
					double min = bezCurve.GetMinTime();
					double t = min;
					std::vector<XPoint> xPts;

					double dt = (max - min) / length;
					ImlibPolygon poly = imlib_polygon_new();
					while ( t < max ) {
						Mgc::Vector2 vec = bezCurve.GetPosition( t );
						XPoint pt = {0};
						pt.x = (short)vec[0];
						pt.y = (short)vec[1];

						imlib_polygon_add_point( poly, (int)(vec[0] + origin_.x_), (int)(vec[1] + origin_.y_) );

						xPts.push_back( pt );
						t += dt;
					}

					if ( !xPts.empty() ) {
						xDrawLines(  poly, (XPoint*)xPts.begin(), xPts.size() );
					}

					imlib_polygon_free( poly );


					remaingOps -= 4;
				}
				break;

				case PRIMITIVE_RECT:{
					if ( (remaingOps - 1) < 0 ){
						//throw exceptiox11Drawablen_ !!
					}

					Rect r;
					r.left_ = (int32)(pointOp->x);
					r.top_ = (int32)(pointOp->y);
					pts++;
					pointOp = *pts;

					r.right_ = (int32)(pointOp->x);
					r.bottom_ = (int32)(pointOp->y);

					r.offset( origin_.x_, origin_.y_ );

					xDrawRectangle( r.left_, r.top_, r.right_, r.bottom_ );

					remaingOps -= 1;
				}
				break;

				case PRIMITIVE_ELLIPSE:{
					if ( (remaingOps - 1) < 0 ){
						//throw exception !!
					}

					Rect r;
					r.left_ = (int32)(pointOp->x + origin_.x_);
					r.top_ = (int32)(pointOp->y + origin_.y_);
					pts++;
					pointOp = *pts;

					r.right_ = (int32)(pointOp->x + origin_.x_);
					r.bottom_ = (int32)(pointOp->y + origin_.y_);
					xDrawEllipse( r.left_, r.top_, r.right_, r.bottom_, 0 );

					remaingOps -= 1;
				}
				break;

				case PRIMITIVE_ARC:{

				}
				break;

				case PRIMITIVE_CLOSE:{
					if ( NULL != prevPointOp ) {

						xDrawLine( prevPointOp->x + origin_.x_, prevPointOp->y + origin_.y_,
								currentMoveTo_.x_ + origin_.x_, currentMoveTo_.y_ + origin_.y_ );


					}
				}
				break;
			}
		}
		pts ++;
		remaingOps --;
	}
}

int32 X11Context::translateStrokeStyle( const StrokeStyle& strokeStyle )
{
	int32 result = LineSolid;
	switch( strokeStyle ) {
		//need to implement some more styles
	}
	return result;
}

StrokeState* X11Context::getCurrentStrokeState()
{
	return &currentStroke_;
}

FillState* X11Context::getCurrentFillState()
{
	return &currentFill_;
}

int32 X11Context::getContextID()
{
	return (int32)x11Drawable_;//xgm__isMemoryCtxd.getGC();
}


void X11Context::setOrigin( const double& x, const double& y )
{
	origin_.x_ = x;
	origin_.y_ = y;

	//apparently X does not support this so we have to handle this ourselves
}

Point* X11Context::getOrigin()
{
	return &origin_;
}
void X11Context::copyContext( const double& x, const double& y, ContextPeer* context )
{
	if ( NULL != context ){
		checkHandle();



		X11Context* x11Ctx = reinterpret_cast<X11Context*>(context);

		if ( x11Ctx->isMemoryCtx_ ) {

			imlib_context_set_drawable( x11Ctx->x11Drawable_ );
			imlib_context_set_image( x11Ctx->memoryImage_ );

			imlib_copy_drawable_to_image( x11Ctx->memoryImageAlpha_, 0, 0,
										x11Ctx->pixmapWidth_, x11Ctx->pixmapHeight_,
										0, 0, 0 );

			imlib_context_set_drawable( x11Drawable_ );

			imlib_render_image_on_drawable( (int)x, (int)y );
		}
		releaseHandle();

	}
	else throw InvalidPointerException( MAKE_ERROR_MSG_2("Context peer passed in to X11Context::copyContext() was NULL") );
}

bool X11Context::isMemoryContext()
{
	return isMemoryCtx_;
}

void X11Context::copyToImage( X11Image* image )
{

}


void X11Context::setContext( GraphicsContext* context )
{
	context_ = context;
}

GraphicsContext* X11Context::getContext()
{
	return context_;
}

void X11Context::createDefaultGC()
{
	//pitch the old GC
	if ( 0 != x11GC_ ) {
		XFreeGC( X11Display_, x11GC_ );
	}

	/*
	if ( 0 == x11Drawable_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("X11 Drawable is NULL! - can't create a GC!") );
	}
	*/

	if ( NULL != x11Drawable_ ) {
		//intial gc values
		//probably want to read in the StrokeState and FillState
		//here!
		int valMask = 0;
		XGCValues values;
		unsigned int lineWidth = 1;
		int lineStyle = LineSolid;
		int capStyle = CapButt;
		int joinStyle = JoinBevel;

		x11GC_ = XCreateGC( X11Display_, x11Drawable_, valMask, &values );
	}
}

void X11Context::setContextID( const int32& handle )
{
	//xgd_ = *( (X11GraphicsDevice*)handle );
	x11Drawable_ = handle;
	if ( 0 == x11Drawable_ ) {
		XFreeGC( X11Display_, x11GC_ );
		x11GC_ = 0;
	}
	else {
		//reset the GC
		createDefaultGC();
	}
}


bool X11Context::isXORModeOn()
{
	return isXORModeOn_;
}

void X11Context::setXORModeOn( const bool& XORModeOn )
{
	isXORModeOn_ = XORModeOn;
}

double X11Context::getTextWidth( const String& text )
{
	checkHandle();
	if ( NULL == context_ ){
		//throw exception !
		throw InvalidPointerException( MAKE_ERROR_MSG_2("context_ is NULL! - can't get text width!") );
	}
	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
		throw InvalidPointerException( MAKE_ERROR_MSG_2("current Font is NULL! - can't get text width!") );
	}
	FontPeer* fontImpl = ctxFont->getFontPeer();

	if ( NULL == fontImpl ){
		//throw exception
		throw InvalidPointerException( MAKE_ERROR_MSG_2("current Font Peer is NULL! - can't get text width!") );
	}

	Imlib_Font imFont = (Imlib_Font)fontImpl->getFontHandleID();
	if ( NULL == imFont ) {
		throw InvalidPointerException(MAKE_ERROR_MSG_2("(Imlib_Font)fontImpl->getFontHandleID() returned NULL! in X11Context::getTextWidth()"));
	}

	imlib_context_set_font( imFont );

	int textWidth = 0;
	int textHeight = 0;

	imlib_get_text_size( text.c_str(), &textWidth, &textHeight );

	releaseHandle();

	return (double)textWidth;
}


double X11Context::getTextHeight( const String& text )
{
	checkHandle();
	if ( NULL == context_ ){
		//throw exception !
		throw InvalidPointerException( MAKE_ERROR_MSG_2("context_ is NULL! - can't get text height!") );
	}
	Font* ctxFont = context_->getCurrentFont();
	if ( NULL == ctxFont ){
		//throw exception
		throw InvalidPointerException( MAKE_ERROR_MSG_2("current Font is NULL! - can't get text height!") );
	}
	FontPeer* fontImpl = ctxFont->getFontPeer();

	if ( NULL == fontImpl ){
		//throw exception
		throw InvalidPointerException( MAKE_ERROR_MSG_2("current Font Peer is NULL! - can't get text height!") );
	}

	Imlib_Font imFont = (Imlib_Font)fontImpl->getFontHandleID();
	if ( NULL == imFont ) {
		throw InvalidPointerException(MAKE_ERROR_MSG_2("(Imlib_Font)fontImpl->getFontHandleID() returned NULL! in X11Context::getTextHeight()"));
	}

	imlib_context_set_font( imFont );

	int textWidth = 0;
	int textHeight = 0;

	std::vector<String> lines;

	simpleLineBreak( text, lines );

	if ( !lines.empty() ) {
		std::vector<String>::iterator it = lines.begin();

		//calculate dimensions
		while ( it != lines.end() ) {
			String& lineOfText = *it;
			int w = 0;
			int h = 0;
			imlib_get_text_size( lineOfText.c_str(), &w, &h );

			textWidth = maxVal<int>( textWidth, w );
			textHeight += h;

			it ++;
		}
	}

	releaseHandle();
	return (double)textHeight;
}

void X11Context::setTextAlignment( const bool& alignTobaseline )
{
	alignToBaseline_ = alignTobaseline;
}

bool X11Context::isTextAlignedToBaseline()
{
	return alignToBaseline_;
}


void X11Context::drawTransparentBitmap(int hdc, int hBitmap, int32 xStart,
                           int32 yStart, uint32 cTransparentColor)
{

}

void X11Context::drawSelectionRect( Rect* rect )
{
	checkHandle();

	char dash[6] = {1,1,1,1,1,2};
	XSetDashes( X11Display_, x11GC_, 0, dash, 2 );

	XSetLineAttributes( X11Display_, x11GC_, 1, LineOnOffDash, CapButt, JoinMiter );

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

	Color* selectColor = toolkit->getSystemColor( SYSCOLOR_WINDOW_TEXT );

	uint32 pixel =  toolkit->getPixelForColor( selectColor );

	XSetForeground ( X11Display_, x11GC_, pixel );


	XDrawRectangle( X11Display_, x11Drawable_, x11GC_,
			(int)(rect->left_ + origin_.x_), (int)(rect->top_ + origin_.y_), (int)rect->getWidth(), (int)rect->getHeight() );


	releaseHandle();
}

void X11Context::drawButtonRect( Rect* rect, const bool& isPressed )
{
	checkHandle();

	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();

	if ( isPressed ) {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		rectangle( rect->left_, rect->top_, rect->right_, rect->bottom_ );
		fillPath();

		currentStroke_.Color_ = *Color::getColor("black" );
		moveTo( rect->left_, rect->bottom_ );
		lineTo( rect->left_, rect->top_ );
		lineTo( rect->right_, rect->top_ );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );
		moveTo( rect->left_+1, rect->bottom_+1 );
		lineTo( rect->left_+1, rect->top_-1 );
		lineTo( rect->right_-1, rect->top_-1 );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );
		moveTo( rect->right_, rect->top_ );
		lineTo( rect->right_, rect->bottom_ );
		lineTo( rect->left_, rect->bottom_ );
		strokePath();
	}
	else {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		rectangle( rect->left_, rect->top_, rect->right_, rect->bottom_ );
		fillPath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );
		moveTo( rect->left_, rect->bottom_ );
		lineTo( rect->left_, rect->top_ );
		lineTo( rect->right_, rect->top_ );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );
		moveTo( rect->right_-1, rect->top_+1 );
		lineTo( rect->right_-1, rect->bottom_-1 );
		lineTo( rect->left_+1, rect->bottom_-1 );
		strokePath();

		currentStroke_.Color_ = *Color::getColor("black" );//*toolkit->getSystemColor( SYSCOLOR_SHADOW );
		moveTo( rect->right_, rect->top_ );
		lineTo( rect->right_, rect->bottom_ );
		lineTo( rect->left_, rect->bottom_ );
		strokePath();
	}

	releaseHandle();
}

void X11Context::drawCheckboxRect( Rect* rect, const bool& isPressed )
{
	checkHandle();

	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();

	if ( isPressed ) {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		rectangle( rect->left_, rect->top_, rect->right_, rect->bottom_ );
		fillPath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );//*Color::getColor("black" );
		moveTo( rect->left_, rect->bottom_ );
		lineTo( rect->left_, rect->top_ );
		lineTo( rect->right_, rect->top_ );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );
		moveTo( rect->right_, rect->top_ );
		lineTo( rect->right_, rect->bottom_ );
		lineTo( rect->left_, rect->bottom_ );
		strokePath();
	}
	else {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		rectangle( rect->left_, rect->top_, rect->right_, rect->bottom_ );
		fillPath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );
		moveTo( rect->left_, rect->bottom_ );
		lineTo( rect->left_, rect->top_ );
		lineTo( rect->right_, rect->top_ );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );
		moveTo( rect->right_, rect->top_ );
		lineTo( rect->right_, rect->bottom_ );
		lineTo( rect->left_, rect->bottom_ );
		strokePath();
	}

	releaseHandle();
}

void X11Context::drawRadioButtonRect( Rect* rect, const bool& isPressed )
{
	checkHandle();

	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();

	if ( isPressed ) {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		std::vector<Point*> pts;
		pts.push_back( new Point(rect->left_, rect->top_ + rect->getHeight()/2.0) );
		pts.push_back( new Point(rect->left_ + rect->getWidth()/2.0, rect->top_) );
		pts.push_back( new Point(rect->right_, rect->top_ + rect->getHeight()/2.0) );
		pts.push_back( new Point(rect->left_ + rect->getWidth()/2.0, rect->bottom_) );
		polyline( pts );
		fillPath();
		for (int i=0;i<pts.size();i++ ){
			delete pts[i];
		}

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );//*Color::getColor("black" );
		moveTo( rect->left_, rect->top_ + rect->getHeight()/2.0 );
		lineTo( rect->left_ + rect->getWidth()/2.0, rect->top_ );
		lineTo( rect->right_, rect->top_ + rect->getHeight()/2.0 );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );
		moveTo( rect->right_, rect->top_ + rect->getHeight()/2.0 );
		lineTo( rect->left_ + rect->getWidth()/2.0, rect->bottom_ );
		lineTo( rect->left_, rect->top_ + rect->getHeight()/2.0 );
		strokePath();
	}
	else {
		currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );
		std::vector<Point*> pts;
		pts.push_back( new Point(rect->left_, rect->top_ + rect->getHeight()/2.0) );
		pts.push_back( new Point(rect->left_ + rect->getWidth()/2.0, rect->top_) );
		pts.push_back( new Point(rect->right_, rect->top_ + rect->getHeight()/2.0) );
		pts.push_back( new Point(rect->left_ + rect->getWidth()/2.0, rect->bottom_) );
		polyline( pts );
		fillPath();
		for (int i=0;i<pts.size();i++ ){
			delete pts[i];
		}

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_HIGHLIGHT );//*Color::getColor("black" );
		moveTo( rect->left_, rect->top_ + rect->getHeight()/2.0 );
		lineTo( rect->left_ + rect->getWidth()/2.0, rect->top_ );
		lineTo( rect->right_, rect->top_ + rect->getHeight()/2.0 );
		strokePath();

		currentStroke_.Color_ = *toolkit->getSystemColor( SYSCOLOR_SHADOW );
		moveTo( rect->right_, rect->top_ + rect->getHeight()/2.0 );
		lineTo( rect->left_ + rect->getWidth()/2.0, rect->bottom_ );
		lineTo( rect->left_, rect->top_ + rect->getHeight()/2.0 );
		strokePath();
	}

	releaseHandle();
}

void X11Context::drawVerticalScrollButtonRect( Rect* rect, const bool& topButton, const bool& isPressed )
{
	checkHandle();

	drawButtonRect( rect, isPressed );

	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();

	Rect innerRect = *rect;

	innerRect.inflate( -innerRect.getWidth()*0.20, -innerRect.getHeight()*0.20 );

	if ( isPressed ) {
		//innerRect.offset( 2, 2 );
	}

	double cx = innerRect.left_ + innerRect.getWidth() / 2.0;
	double cy = innerRect.top_ + innerRect.getHeight() / 2.0;

	std::vector<Point*> pts;

	if ( topButton ) {
		pts.push_back( new Point(cx, innerRect.top_) );
		pts.push_back( new Point(innerRect.right_, innerRect.bottom_) );
		pts.push_back( new Point(innerRect.left_, innerRect.bottom_) );
	}
	else {
		pts.push_back( new Point(innerRect.left_, innerRect.top_) );
		pts.push_back( new Point(innerRect.right_, innerRect.top_) );
		pts.push_back( new Point(cx, innerRect.bottom_) );
	}

	currentFill_.Color_ = *Color::getColor("black");

	polyline( pts );
	fillPath();
	for (int i=0;i<pts.size();i++ ){
		delete pts[i];
	}


	releaseHandle();
}

void X11Context::drawHorizontalScrollButtonRect( Rect* rect, const bool& leftButton, const bool& isPressed )
{
	checkHandle();

	drawButtonRect( rect, isPressed );

	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();

	Rect innerRect = *rect;

	innerRect.inflate( -innerRect.getWidth()*0.20, -innerRect.getHeight()*0.20 );

	if ( isPressed ) {
		//innerRect.offset( 2, 2 );
	}

	double cx = innerRect.left_ + innerRect.getWidth() / 2.0;
	double cy = innerRect.top_ + innerRect.getHeight() / 2.0;

	std::vector<Point*> pts;

	if ( leftButton ) {
		pts.push_back( new Point(innerRect.right_, innerRect.top_) );
		pts.push_back( new Point(innerRect.left_, cy) );
		pts.push_back( new Point(innerRect.right_, innerRect.bottom_) );
	}
	else {
		pts.push_back( new Point(innerRect.left_, innerRect.top_) );
		pts.push_back( new Point(innerRect.right_, cy) );
		pts.push_back( new Point(innerRect.left_, innerRect.bottom_) );
	}

	currentFill_.Color_ = *Color::getColor("black");

	polyline( pts );
	fillPath();
	for (int i=0;i<pts.size();i++ ){
		delete pts[i];
	}

	releaseHandle();
}

void X11Context::setClippingRect( Rect* clipRect )
{
	checkHandle();

	if ( NULL != clipRect ) {


		clipRect_.left_ = maxVal<double>( 0.0, clipRect->left_ );
		clipRect_.top_ = maxVal<double>( 0.0, clipRect->top_ );
		clipRect_.right_ = clipRect->right_;
		clipRect_.bottom_ = clipRect->bottom_;

		if ( isMemoryCtx_ ) {
			clipRect_.right_ = minVal<double>( pixmapWidth_ + clipRect_.left_, clipRect_.right_ );
			clipRect_.bottom_ = minVal<double>( pixmapHeight_ + clipRect_.top_, clipRect_.bottom_ );
		}

	}
	else {
		clipRect_.setRect(0,0,0,0);
	}

	releaseHandle();
}

void X11Context::setClippingPath( Path* clippingPath )
{
	checkHandle();



	releaseHandle();
}


void X11Context::drawDisclosureButton( Rect* rect, const int32& state )
{

}

void X11Context::drawTab( Rect* rect, const bool& selected, const String& caption )
{

}

void X11Context::drawTabPage( Rect* rect )
{

}

void X11Context::drawTickMark( Rect* rect )
{

}

void X11Context::drawSliderThumb( Rect* rect, const bool& pressed )
{

}

void X11Context::drawSlider( Rect* rect )
{

}

void X11Context::drawHeader( Rect* rect )
{

}

void X11Context::drawEdge( Rect* rect, const int32& edgeSides, const int32& edgeStyle )
{

}

void X11Context::drawSizeGripper( Rect* rect )
{

}

void X11Context::drawControlBackground( Rect* rect )
{
	GraphicsToolkit* toolkit = GraphicsToolkit::getDefaultGraphicsToolkit();
	currentFill_.Color_ = *toolkit->getSystemColor( SYSCOLOR_FACE );


}

void X11Context::drawWindowBackground( Rect* rect )
{

}

void X11Context::drawMenuItemBackground( Rect* rect, const bool& selected )
{

}

void X11Context::xDrawLine( double x1, double y1, double x2, double y2 )
{
	XDrawLine( X11Display_, x11Drawable_, x11GC_, (int)x1, (int)y1, (int)x2, (int)y2 );
}

void X11Context::xDrawRectangle( double x1, double y1, double x2, double y2 )
{
	if ( true == inFillPath_ ) {
		XFillRectangle( X11Display_, x11Drawable_, x11GC_, (int)x1, (int)y1, (int)(x2-x1), (int)(y2-y1) );
	}
	else {
		XDrawRectangle( X11Display_, x11Drawable_, x11GC_, (int)x1, (int)y1, (int)(x2-x1), (int)(y2-y1) );
	}
}

void X11Context::xDrawEllipse( double x1, double y1, double x2, double y2, double angle )
{
	if ( true == inFillPath_ ) {
		XFillArc( X11Display_, x11Drawable_, x11GC_,
			(int)x1, (int)y1, (int)(x2-x1), (int)(y2-y1), 0, 23040 );
	}
	else {
		XDrawArc( X11Display_, x11Drawable_, x11GC_,
			(int)x1, (int)y1, (int)(x2-x1), (int)(y2-y1), 0, 23040 );
	}
}

void X11Context::xDrawLines( ImlibPolygon poly, XPoint* points, int numberOfPoints )
{
	if ( true == inFillPath_ ) {
		XFillPolygon( X11Display_, x11Drawable_, x11GC_,
				points, numberOfPoints,
				Complex,
				CoordModeOrigin );
	}
	else {
		XDrawLines( X11Display_, x11Drawable_, x11GC_,
				points, numberOfPoints, CoordModeOrigin );
	}
}

void X11Context::simpleLineBreak( const String& text, std::vector<String>& lines )
{
	const VCFChar* P = text.c_str();
	const VCFChar* start = P;
	const VCFChar* line = P;
	int textSize = text.size();
	String lineOfText;
	while ( (P-start) < textSize ) {
		if ( (*P == '\n') || ((*P == '\r') && (*(P+1) == '\n')) ) {

			lineOfText = "";
			lineOfText.append( line, P-line );
			lines.push_back( lineOfText );


			//process the new line
			if ( *(P+1) == '\n' ) {
				P++;
			}
			P++;
			line = P;
		}
		P++;
	}

	if ( (line < P) && ((start-line) < textSize) ) {
		lineOfText = "";
		lineOfText.append( line, P-line );
		lines.push_back( lineOfText );
	}
}


/**
$Id$
*/
