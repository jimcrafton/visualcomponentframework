//GraphicsContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"


namespace VCF {


GraphicsContext::GraphicsContext()
{
	init();
}

GraphicsContext::GraphicsContext( const unsigned long& width, const unsigned long& height )
{
	init();

	contextPeer_ = GraphicsToolkit::createContextPeer( width, height );
	if ( NULL == contextPeer_ ){
		//throw exception
	}

	contextPeer_->setContext( this );
}

GraphicsContext::GraphicsContext( const unsigned long& contextID )
{
	init();
	contextPeer_ = GraphicsToolkit::createContextPeer( contextID );
	if ( NULL == contextPeer_ ){
		//throw exception
	}
	contextPeer_->setContext( this );
}

GraphicsContext::~GraphicsContext()
{
	if ( NULL != contextPeer_ ){
		delete contextPeer_;
	}
	contextPeer_ = NULL;

	if ( NULL != currentFill_ ){
		delete currentFill_;
	}
	currentFill_ = NULL;

	if ( NULL != currentStroke_ ){
		delete currentStroke_;
	}
	currentStroke_ = NULL;

	if ( NULL != currentFont_ ){
		delete currentFont_;
	}
	currentFont_ = NULL;

	if ( NULL != clippingPath_ ) {
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->release();
	}
	clippingPath_ = NULL;

	if ( NULL != drawingArea_ ) {
		delete drawingArea_;
	}
}

void GraphicsContext::init()
{
	currentState_ = GraphicsContext::gsNone;

	drawingArea_ = NULL;

	strokeWidth_ = 1.0;
	contextPeer_ = NULL;
	currentFill_ = NULL;
	currentStroke_ = NULL;
	currentFont_ = NULL;
	clippingPath_ = NULL;

	currentFont_ = new Font();

	theta_ = 0.0;
	xScale_ = 1.0;
	yScale_ = 1.0;
	xTranslate_ = 0.0;
	yTranslate_ = 0.0;
	xShear_ = 0.0;
	yShear_ = 0.0;
	transformMatrix_.identity();

	renderBuffer_ = NULL;

	renderAreaDirty_ = false;
}


void GraphicsContext::setCurrentFont(Font * font)
{
	currentFont_->copy( font );
}

void GraphicsContext::setCurrentFill(Fill * fill)
{
	currentFill_ = fill;
	if ( NULL != currentFill_ ){
		currentFill_->setContext( this );
	}
}

void GraphicsContext::setCurrentStroke(Stroke * stroke)
{
	currentStroke_ = stroke;
	if ( NULL != currentStroke_ ){
		currentStroke_->setContext( this );
	}
}

void GraphicsContext::draw(Path * path)
{
	if ( NULL != currentFill_ ){
		currentFill_->render( path );
	}
	if ( NULL != currentStroke_ ){
		currentStroke_->render( path );
	}
}

void GraphicsContext::drawImage( const double& x, const double& y, Image * image)
{
	Rect bounds(0,0,image->getWidth(), image->getHeight() );
	drawPartialImage( x, y, &bounds, image );
}

void GraphicsContext::drawImageWithState( const double& x, const double& y, Image * image, const bool& enabled )
{
	drawImage( x, y, image );
	/*
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doImage ) ) {

		Rect bounds(0,0,image->getWidth(), image->getHeight() );
		contextPeer_->drawImage( x, y, &bounds, image );

		contextPeer_->finishedDrawing( 	GraphicsContext::doImage );
	}
	*/
}

void GraphicsContext::drawImageWithinBounds( Rect* bounds, Image* image )
{
	Rect imageBounds( 0,0,bounds->getWidth(), bounds->getHeight() );
	drawPartialImage( bounds->left_, bounds->top_, &imageBounds, image );
}

void GraphicsContext::drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	//contextPeer_->drawPartialImage( x, y, imageBounds, image );
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doImage ) ) {

		contextPeer_->drawImage( x, y, imageBounds, image );

		contextPeer_->finishedDrawing( 	GraphicsContext::doImage );
	}
}


void GraphicsContext::textWithStateAt( const double& x, const double& y, const String& text, const bool& enabled )
{
	if ( enabled ) {
		textAt( x, y, text );
	}
	else {
		Color* shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		Color* hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		Color oldColor = *currentFont_->getColor();

		currentFont_->setColor( hilight );

		textAt( x+1, y+1, text );

		currentFont_->setColor( shadow );

		textAt( x, y, text );

		//reset the original color
		currentFont_->setColor( &oldColor );
	}
}


void GraphicsContext::textAt(const double & x, const double & y, const String & text)
{
	Rect bounds( x, y, x + getTextWidth(text), y + getTextHeight(text) );

	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( bounds, text );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}

void GraphicsContext::textAt( const double & x, const double & y, const String& text, const long drawOptions )
{
	Rect bounds( x, y, x + getTextWidth(text), y + getTextHeight(text) );

	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {

		contextPeer_->textAt( bounds, text, drawOptions );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}


void GraphicsContext::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptRect) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptRect) );
}

void GraphicsContext::roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
								const double & xc, const double & yc)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptRoundRect) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptRoundRect) );
	pathOperations_.push_back( PointOperation(xc,yc,PointOperation::ptRoundRect) );
}

void GraphicsContext::circle(const double & x, const double & y, const double & radius)
{
	ellipse( x - radius, y - radius, x + radius, y + radius );
}

void GraphicsContext::ellipse(const double & x1, const double & y1, const double & x2, const double & y2)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptEllipse) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptEllipse) );
}

void GraphicsContext::arc(const double & x1, const double & y1, const double & x2, const double & y2,
                          const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptArc) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptArc) );
	pathOperations_.push_back( PointOperation(x3,y3,PointOperation::ptArc) );
	pathOperations_.push_back( PointOperation(x4,y4,PointOperation::ptArc) );
}

void GraphicsContext::pie(const double & x1, const double & y1, const double & x2, const double & y2,
                          const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	//contextPeer_->pie( x1, y1, x2, y2, x3, y3, x4, y4 );
}

void GraphicsContext::chord(const double & x1, const double & y1, const double & x2, const double & y2,
                            const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	//contextPeer_->chord( x1, y1, x2, y2, x3, y3, x4, y4 );
}


void GraphicsContext::polyline( const std::vector<Point>& pts )
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	std::vector<Point>::const_iterator it = pts.begin();
	while ( it != pts.end() ) {
		const Point& pt = *it;
		pathOperations_.push_back( PointOperation(pt.x_, pt.y_, PointOperation::ptPolyLine) );
		it ++;
	}
}

void GraphicsContext::curve(const double & x1, const double & y1, const double & x2, const double & y2,
                            const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x3,y3,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x4,y4,PointOperation::ptBezier) );
}

void GraphicsContext::lineTo(const double & x, const double & y)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x,y,PointOperation::ptLineTo) );
}

void GraphicsContext::moveTo(const double & x, const double & y)
{
	checkPathOperations();
	currentState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x,y,PointOperation::ptMoveTo) );
}

void GraphicsContext::fillPath()
{
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doFill ) ) {

		execPathOperations();

		contextPeer_->finishedDrawing( 	GraphicsContext::doFill );
	}
}

void GraphicsContext::strokePath()
{
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doStroke ) ) {

		execPathOperations();

		contextPeer_->finishedDrawing( 	GraphicsContext::doStroke );
	}
}

ContextPeer* GraphicsContext::getPeer()
{
	return contextPeer_;
}

void GraphicsContext::setOrigin( const double& x, const double& y )
{
	contextPeer_->setOrigin( x, y );
}

Point GraphicsContext::getOrigin()
{
	return contextPeer_->getOrigin();
}


void GraphicsContext::copyContext( const Rect& sourceRect,
						const Rect& destRect,
						GraphicsContext* context )
{
	contextPeer_->copyContext( sourceRect, destRect, context->getPeer() );
}

void GraphicsContext::setCurrentTransform( Matrix2D* transform )
{
	transformMatrix_ = *transform;
}

Matrix2D* GraphicsContext::getCurrentTransform()
{
	compositeMatrices();
	return &transformMatrix_;
}

void GraphicsContext::setRotation( const double& theta )
{
	theta_ = theta;
}

void GraphicsContext::setTranslation( const double transX, const double& transY )
{
	xTranslate_ = transX;
	yTranslate_ = transY;
}

void GraphicsContext::setShear( const double& shearX, const double& shearY )
{
	xShear_ = shearX;
	yShear_ = shearY;
}

void GraphicsContext::setScale( const double& scaleX, const double& scaleY )
{
	xScale_ = scaleX;
	yScale_ = scaleY;
}

void GraphicsContext::compositeMatrices()
{
	Matrix2D rot;
	rot.rotate( theta_ );
	Matrix2D trans;
	trans.translate( xTranslate_, yTranslate_ );
	Matrix2D scale;
	scale.scale( xScale_, yScale_ );
	Matrix2D shear;
	shear.shear( xShear_, yShear_ );
	Matrix2D tmp;
	tmp.multiply( &rot, &trans );
	tmp.multiply( &tmp, &scale );
	tmp.multiply( &tmp, &shear );
	transformMatrix_ = tmp;
}

Font* GraphicsContext::getCurrentFont()
{
	return currentFont_;
}

void GraphicsContext::setColor( Color* color )
{
	if ( NULL != color ){
		color_.copy( color );
	}
}

Color* GraphicsContext::getColor()
{
	return &color_;
}


void GraphicsContext::textBoundedBy( Rect* bounds, const String& text, const bool& wordWrap )
{
	long drawOptions = wordWrap ? GraphicsContext::tdoWordWrap : GraphicsContext::tdoNone;
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( *bounds, text, drawOptions );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}

void GraphicsContext::textBoundedBy( Rect* bounds, const String& text, const long drawOptions )
{
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( *bounds, text, drawOptions );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}

bool GraphicsContext::isXORModeOn()
{
	return contextPeer_->isXORModeOn();
}

void GraphicsContext::setXORModeOn( const bool& XORModeOn )
{
	contextPeer_->setXORModeOn( XORModeOn );
}

double GraphicsContext::getTextWidth( const String& text )
{
	return contextPeer_->getTextWidth( text );
}

double GraphicsContext::getTextHeight( const String& text )
{
	return contextPeer_->getTextHeight( text );
}

void GraphicsContext::setClippingRect( Rect* rect )
{
	BezierCurve* rectClipPath = NULL;
	if ( NULL != rect ) {
		rectClipPath = new BezierCurve();
		rectClipPath->moveTo( rect->left_, rect->top_ );
		rectClipPath->lineTo( rect->right_, rect->top_ );
		rectClipPath->lineTo( rect->right_, rect->bottom_ );
		rectClipPath->lineTo( rect->left_, rect->bottom_ );
		rectClipPath->close();
	}

	if ( NULL != clippingPath_ ) { //release the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->release();
	}

	clippingPath_ = rectClipPath;

	if ( NULL != clippingPath_ ) { //take ownership of the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->addRef();
	}

	contextPeer_->setClippingRect( rect );
}

void GraphicsContext::setClippingPath( Path* clippingPath )
{
	if ( NULL != clippingPath_ ) { //release the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->release();
	}

	clippingPath_ = clippingPath;

	if ( NULL != clippingPath_ ) { //take ownership of the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->addRef();
	}

	contextPeer_->setClippingPath( clippingPath_ );
}

Rect GraphicsContext::getClippingRect()
{
	Rect result;

	if ( NULL != clippingPath_ ) {
		result = clippingPath_->getBounds();
	}

	return result;
}

Path* GraphicsContext::getClippingPath()
{
	return clippingPath_;
}

/*
void GraphicsContext::drawSelectionRect( Rect* rect )
{
	contextPeer_->drawSelectionRect( rect );
}

void GraphicsContext::drawButtonRect( Rect* rect, const bool& isPressed )
{
	contextPeer_->drawButtonRect( rect, isPressed );
}

void GraphicsContext::drawCheckboxRect( Rect* rect, const bool& isPressed )
{
	contextPeer_->drawCheckboxRect( rect, isPressed );
}

void GraphicsContext::drawRadioButtonRect( Rect* rect, const bool& isPressed )
{
	contextPeer_->drawRadioButtonRect( rect, isPressed );
}

void GraphicsContext::drawVerticalScrollButtonRect( Rect* rect, const bool& topButton, const bool& isPressed )
{
	contextPeer_->drawVerticalScrollButtonRect( rect, topButton, isPressed );
}

void GraphicsContext::drawHorizontalScrollButtonRect( Rect* rect, const bool& leftButton, const bool& isPressed )
{
	contextPeer_->drawHorizontalScrollButtonRect( rect, leftButton, isPressed );
}

void GraphicsContext::drawDisclosureButton( Rect* rect, const DisclosureStateType& state )
{
	contextPeer_->drawDisclosureButton( rect, state );
}

void GraphicsContext::drawTab( Rect* rect, const bool& selected, const String& caption )
{
	contextPeer_->drawTab( rect, selected, caption );
}

void GraphicsContext::drawTabPage( Rect* rect )
{
	contextPeer_->drawTabPage( rect );
}

void GraphicsContext::drawTickMarks( Rect* rect, const SliderInfo& sliderInfo )
{
	contextPeer_->drawTickMarks( rect, sliderInfo );
}

void GraphicsContext::drawSliderThumb( Rect* rect, const SliderInfo& sliderInfo )
{
	contextPeer_->drawSliderThumb( rect, sliderInfo );
}

void GraphicsContext::drawSlider( Rect* rect, const SliderInfo& sliderInfo )
{
	contextPeer_->drawSlider( rect, sliderInfo );
}

void GraphicsContext::drawHeader( Rect* rect )
{
	contextPeer_->drawHeader( rect );
}

void GraphicsContext::drawEdge( Rect* rect, const long& edgeSides, const long& edgeStyle )
{
	contextPeer_->drawEdge( rect, edgeSides, edgeStyle );
}

void GraphicsContext::drawSizeGripper( Rect* rect )
{
	contextPeer_->drawSizeGripper( rect );
}

void GraphicsContext::drawControlBackground( Rect* rect )
{
	contextPeer_->drawControlBackground( rect );
}

void GraphicsContext::drawWindowBackground( Rect* rect )
{
	contextPeer_->drawWindowBackground( rect );
}

void GraphicsContext::drawMenuItemBackground( Rect* rect, const bool& selected )
{
	contextPeer_->drawMenuItemBackground( rect, selected );
}
*/

void GraphicsContext::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeSelectionRect( rect, state );
}

void GraphicsContext::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeFocusRect( rect, state );
}

void GraphicsContext::drawThemeButtonRect( Rect* rect, ButtonState& state )
{
	contextPeer_->drawThemeButtonRect( rect, state );
}

void GraphicsContext::drawThemeCheckboxRect( Rect* rect, ButtonState& state )
{
	contextPeer_->drawThemeCheckboxRect( rect, state );
}

void GraphicsContext::drawThemeRadioButtonRect( Rect* rect, ButtonState& state )
{
	contextPeer_->drawThemeRadioButtonRect( rect, state );
}

void GraphicsContext::drawThemeComboboxRect( Rect* rect, ButtonState& state )
{
	contextPeer_->drawThemeComboboxRect( rect, state );
}


void GraphicsContext::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state )
{   
	contextPeer_->drawThemeScrollButtonRect( rect, state );
}

void GraphicsContext::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state )
{
	contextPeer_->drawThemeDisclosureButton( rect, state );
}

void GraphicsContext::drawThemeTab( Rect* rect, TabState& state )
{
	contextPeer_->drawThemeTab( rect, state );
}

void GraphicsContext::drawThemeTabPage( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeTabPage( rect, state );
}

void GraphicsContext::drawThemeTickMarks( Rect* rect, SliderState& state )
{
	contextPeer_->drawThemeTickMarks( rect, state );
}

void GraphicsContext::drawThemeSlider( Rect* rect, SliderState& state )
{
	contextPeer_->drawThemeSlider( rect, state );
}

void GraphicsContext::drawThemeProgress( Rect* rect, ProgressState& state )
{
	contextPeer_->drawThemeProgress( rect, state );
}

void GraphicsContext::drawThemeImage( Rect* rect, Image* image, DrawUIState& state )
{
	contextPeer_->drawThemeImage( rect, image, state );
}

void GraphicsContext::drawThemeHeader( Rect* rect, ButtonState& state )
{
	contextPeer_->drawThemeHeader( rect, state );
}

void GraphicsContext::drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle )
{
	contextPeer_->drawThemeEdge( rect, state, edgeSides, edgeStyle );
}

void GraphicsContext::drawThemeSizeGripper( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeSizeGripper( rect, state );
}

void GraphicsContext::drawThemeBackground( Rect* rect, BackgroundState& state )
{
	contextPeer_->drawThemeBackground( rect, state );
}

void GraphicsContext::drawThemeMenuItem( Rect* rect, MenuState& state )
{
	contextPeer_->drawThemeMenuItem( rect, state );
}

void GraphicsContext::drawThemeText( Rect* rect, TextState& state )
{
	contextPeer_->drawThemeText( rect, state );
}

void GraphicsContext::setStrokeWidth( const double& width )
{
	strokeWidth_ = width;
}


void GraphicsContext::execPathOperations()
{
	currentState_ = GraphicsContext::gsExecutingGraphicsOps;

	std::vector<PointOperation>::iterator it = pathOperations_.begin();

	while ( it != pathOperations_.end() ) {
		PointOperation& pointOp = *it;

		switch ( pointOp.primitive ){
			case PointOperation::ptMoveTo :{
				currentMoveTo_.x_ = pointOp.x;
				currentMoveTo_.y_ = pointOp.y;
				contextPeer_->moveTo( pointOp.x, pointOp.y );
				it ++;
			}
			break;

			case PointOperation::ptLineTo :{
				contextPeer_->lineTo( pointOp.x, pointOp.y );
				it ++;
			}
			break;

			case PointOperation::ptPolyLine :{
				std::vector<Point> tmpPts;
				PointOperation::PrimitiveType type = pointOp.primitive;

				while ( (it != pathOperations_.end()) && (type == PointOperation::ptPolyLine) ) {
					PointOperation& pt = *it;
					type = pt.primitive;
					tmpPts.push_back( Point(pt.x,pt.y) );
					it++;
				}

				contextPeer_->polyline( tmpPts );
			}
			break;

			case PointOperation::ptBezier :{
				/*
				if ( (remaingOps - 3) < 0 ){
					//throw exception !!
				}
				*/
				if ( (pathOperations_.end() - it) < 4 ) {
					throw RuntimeException( MAKE_ERROR_MSG_2("Not enough path operations left to complete the bezier curve") );
				}

				PointOperation& pt1 = *it;
				it ++;

				PointOperation& pt2 = *it;
				it ++;

				PointOperation& pt3 = *it;
				it ++;

				PointOperation& pt4 = *it;
				it ++;

				contextPeer_->curve( pt1.x, pt1.y, pt2.x, pt2.y,
										pt3.x, pt3.y, pt4.x, pt4.y );


			}
			break;

			case PointOperation::ptRect:{

				PointOperation& pt1 = *it;
				it ++;

				PointOperation& pt2 = *it;
				it ++;

				contextPeer_->rectangle( pt1.x, pt1.y, pt2.x, pt2.y );
			}
			break;

			case PointOperation::ptRoundRect :{

				it += 2;

				//remaingOps -= 2;
			}
			break;

			case PointOperation::ptEllipse : {
				PointOperation& pt1 = *it;
				it ++;

				PointOperation& pt2 = *it;
				it ++;

				contextPeer_->ellipse( pt1.x, pt1.y, pt2.x, pt2.y );
			}
			break;

			case PointOperation::ptArc :{
				if ( (pathOperations_.end() - it) < 4 ) {
					throw RuntimeException( MAKE_ERROR_MSG_2("Not enough path operations left to complete the bezier curve") );
				}

				PointOperation& pt1 = *it;
				it ++;

				PointOperation& pt2 = *it;
				it ++;

				PointOperation& pt3 = *it;
				it ++;

				PointOperation& pt4 = *it;
				it ++;

				contextPeer_->arc( pt1.x, pt1.y, pt2.x, pt2.y,
										pt3.x, pt3.y, pt4.x, pt4.y );
			}
			break;

			case PointOperation::ptClose : {
				PointOperation& pt = *it;
				contextPeer_->lineTo( pt.x, pt.y );
				it ++;
			}
			break;

			default : {
				it = pathOperations_.end();
				break; //quit the loop
			}
			break;
		}
	}

	currentState_ = GraphicsContext::gsNone;
}


void GraphicsContext::checkPathOperations()
{
	if ( GraphicsContext::gsAddingGraphicsOps != currentState_ ) {
		pathOperations_.clear();
	}
}

/*
Image* GraphicsContext::getImage( Rect* imageBounds )
{
	Image* result = contextPeer_->getImage( imageBounds );

	ImageRect imgRect(result,imageBounds);

	imageMap_[result] = imgRect;
	return result;
}

void GraphicsContext::putImage( Image* image )
{

	std::map<Image*, ImageRect>::iterator found = imageMap_.find( image );
	if ( found != imageMap_.end() ) {

		Rect& bounds = found->second.bounds_;
		contextPeer_->putImage( bounds.left_, bounds.top_, image );

		imageMap_.erase( found );
		delete image;
	}
	else {
		//throw an exception of some sort!
	}
}

*/




void GraphicsContext::setDrawingArea( Rect bounds )
{
	drawingAreaTopLeft_.x_ = bounds.left_;
	drawingAreaTopLeft_.y_ = bounds.top_;

	if ( NULL == drawingArea_ ) {
		drawingArea_ = GraphicsToolkit::createImage( (uint32)bounds.getWidth(), (uint32)bounds.getHeight() );
	}
	else {
		drawingArea_->setSize( (uint32)bounds.getWidth(), (uint32)bounds.getHeight() );
	}

	drawingArea_->getImageBits()->attachRenderBuffer( drawingArea_->getWidth(), drawingArea_->getHeight() );
	drawingArea_->getImageContext()->setRenderingBuffer( drawingArea_->getImageBits()->renderBuffer_ );

	drawingArea_->getImageContext()->setOrigin( -bounds.left_, -bounds.top_ );

	renderAreaDirty_ = true;
}

void GraphicsContext::deleteDrawingArea()
{
	delete drawingArea_;
	drawingArea_ = NULL;
}

void GraphicsContext::flushDrawingArea()
{
	if ( viewableBounds_.isNull() ) {
		drawImage( drawingAreaTopLeft_, drawingArea_ );
	}
	else {

		drawingArea_->getImageBits()->renderBuffer_->clip_box( agg::rect( viewableBounds_.left_,
																			viewableBounds_.top_,
																			viewableBounds_.right_,
																			viewableBounds_.bottom_ ) );

		drawPartialImage(  viewableBounds_.getTopLeft(), &viewableBounds_, drawingArea_ );
	}

	renderAreaDirty_ = false;
}


};	// namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.4  2004/06/27 18:19:16  ddiego
*more osx updates
*
*Revision 1.1.2.2.2.3  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.2.2.2  2004/06/16 05:18:56  ddiego
*further updates to OSX theme compliant drawing code
*
*Revision 1.1.2.2.2.1  2004/06/15 04:04:38  ddiego
*revamped osx theme drawing API
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.23  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.22.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*Revision 1.22  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.21.2.1  2003/10/28 04:06:12  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.21  2003/08/09 02:56:45  ddiego
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
*Revision 1.20.2.8  2003/08/08 03:21:36  ddiego
*got rid of some miscellaneous graphics files
*
*Revision 1.20.2.7  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.20.2.6  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.20.2.5  2003/07/07 03:52:08  ddiego
*added further osx porting code, primarily to the GraphicsKit - hey we can
*draw lines ! Woot!
*
*Revision 1.20.2.4  2003/06/20 04:36:59  ddiego
*further AGG integration
*moved files over to renamed directories
*
*Revision 1.20.2.3  2003/06/17 03:54:25  ddiego
*further agg integration - took out the getImage/putImage from GraphicsContext -
*this was too slow. now have an alternate solution that seems to work OK
*
*Revision 1.20.2.2  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.20.2.1  2003/06/05 03:48:54  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.20  2003/05/17 20:37:21  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.2.5  2003/05/14 03:04:29  ddiego
*fixed some bugs caused by some of the changes in the graphics kit that I made
*yesterday. All is well now.
*
*Revision 1.19.2.4  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.19.2.3  2003/04/17 04:29:50  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.19.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.19.2.1  2003/03/12 03:12:01  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.19  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.18.2.4  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Revision 1.18.2.3  2002/12/31 07:02:17  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.18.2.2  2002/12/28 21:51:19  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.18.2.1  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.18  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.17.10.2  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.17.10.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.17  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.16.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.16  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


