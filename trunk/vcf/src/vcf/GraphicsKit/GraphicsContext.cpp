//GraphicsContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"

#include "thirdparty/common/agg/include/agg_ellipse.h"
#include "thirdparty/common/agg/include/agg_arc.h"

namespace VCF {

/**
* The structure used to fully save and restore the state of a Graphics context.
*@see GraphicsContext::saveState()
*/
class GraphicsState {
public:

	GraphicsState();
	GraphicsState( const GraphicsState& rhs );
	~GraphicsState();

	GraphicsState& operator=( const GraphicsState& rhs );

	void compositeMatrix();

public:
	Fill* fill_;
	Stroke* stroke_;
	Path* clippingPath_;
	GraphicsContext* owningContext_;
	
	double strokeWidth_;
	
	Font font_;
	Matrix2D transformMatrix_;
	Point currentMoveTo_;
	Color color_;

	double rotation_;
	double shearX_;
	double shearY_;
	double translateX_;
	double translateY_;
	double scaleX_;
	double scaleY_;	
};





GraphicsState::GraphicsState():
	fill_(NULL),
	stroke_(NULL),
	clippingPath_(NULL),
	owningContext_(NULL),
	strokeWidth_(1.0),
	rotation_(0.0),
	shearX_(0.0),
	shearY_(0.0),
	translateX_(0.0),
	translateY_(0.0),
	scaleX_(1.0),
	scaleY_(1.0)
{
	transformMatrix_.identity();
}

GraphicsState::GraphicsState( const GraphicsState& rhs ):
	fill_(NULL),
	stroke_(NULL),
	clippingPath_(NULL),
	owningContext_(NULL),
	strokeWidth_(1.0),
	rotation_(0.0),
	shearX_(0.0),
	shearY_(0.0),
	translateX_(0.0),
	translateY_(0.0),
	scaleX_(1.0),
	scaleY_(1.0)
{
	transformMatrix_.identity();
	*this = rhs;
}

GraphicsState::~GraphicsState()
{

	if ( NULL != clippingPath_ ) {
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->release();
	}
	clippingPath_ = NULL;

}

GraphicsState& GraphicsState::operator=( const GraphicsState& rhs )
{
	strokeWidth_ = rhs.strokeWidth_;
	fill_ = rhs.fill_;
	stroke_ = rhs.stroke_;
	font_ = rhs.font_;

	if ( NULL != clippingPath_ ) { //release the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->release();
	}

	clippingPath_ = rhs.clippingPath_;

	if ( NULL != clippingPath_ ) { //take ownership of the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clippingPath_ );
		pathObj->addRef();
	}


	owningContext_ = rhs.owningContext_;
	transformMatrix_ = rhs.transformMatrix_;
	currentMoveTo_ = rhs.currentMoveTo_;
	color_ = rhs.color_;

	rotation_ = rhs.rotation_;
	shearX_ = rhs.shearX_;
	shearY_ = rhs.shearY_;
	translateX_ = rhs.translateX_;
	translateY_ = rhs.translateY_;
	scaleX_ = rhs.scaleX_;
	scaleY_ = rhs.scaleY_;

	return *this;
}

void GraphicsState::compositeMatrix()
{
	Matrix2D rotate;
	rotate.rotate( rotation_ );

	Matrix2D scale;
	scale.scale( scaleX_, scaleY_ );

	Matrix2D shear;
	shear.shear( shearX_, shearY_ );

	Matrix2D translation;
	translation.translate( translateX_, translateY_ );

	Matrix2D tmp;
	tmp.multiply( &scale, &rotate );
	tmp.multiply( &tmp, &shear );
	tmp.multiply( &tmp, &translation );
	transformMatrix_ = tmp;
}



GraphicsContext::GraphicsContext():
	contextPeer_(NULL),
	currentDrawingState_(GraphicsContext::gsNone),		
	drawingArea_(NULL),
	renderBuffer_(NULL),
	renderAreaDirty_(false),
	graphicsStateIndex_(0),
	currentGraphicsState_(NULL)
{
	GraphicsState* newState = new GraphicsState();
	newState->owningContext_ = this;
	stateCollection_.push_back( newState );
	currentGraphicsState_ = stateCollection_[graphicsStateIndex_];

	Font& font = currentGraphicsState_->font_;
	font.setGraphicsContext( this );

	init();
}

GraphicsContext::GraphicsContext( const unsigned long& width, const unsigned long& height ):
	contextPeer_(NULL),
	currentDrawingState_(GraphicsContext::gsNone),		
	drawingArea_(NULL),
	renderBuffer_(NULL),
	renderAreaDirty_(false),
	graphicsStateIndex_(0),
	currentGraphicsState_(NULL)
{
	GraphicsState* newState = new GraphicsState();
	newState->owningContext_ = this;
	stateCollection_.push_back( newState );
	currentGraphicsState_ = stateCollection_[graphicsStateIndex_];

	contextPeer_ = GraphicsToolkit::createContextPeer( width, height );
	if ( NULL == contextPeer_ ){
		//throw exception
	}

	contextPeer_->setContext( this );
	init();
	Font& font = currentGraphicsState_->font_;
	font.setGraphicsContext( this );

	font.setPointSize( font.getPointSize() );

}

GraphicsContext::GraphicsContext( OSHandleID contextID ):	
	contextPeer_(NULL),
	currentDrawingState_(GraphicsContext::gsNone),
	drawingArea_(NULL),
	renderBuffer_(NULL),
	renderAreaDirty_(false),
	graphicsStateIndex_(0),
	currentGraphicsState_(NULL)
{
	GraphicsState* newState = new GraphicsState();
	newState->owningContext_ = this;
	stateCollection_.push_back( newState );
	currentGraphicsState_ = stateCollection_[graphicsStateIndex_];

	contextPeer_ = GraphicsToolkit::createContextPeer( contextID );
	if ( NULL == contextPeer_ ){
		//throw exception
	}
	contextPeer_->setContext( this );
	init();
	Font& font = currentGraphicsState_->font_;
	font.setGraphicsContext( this );

	font.setPointSize( font.getPointSize() );
}

GraphicsContext::~GraphicsContext()
{
	if ( NULL != contextPeer_ ){
		delete contextPeer_;
	}
	contextPeer_ = NULL;


	GraphicsStateCollection::iterator it = stateCollection_.begin();
	while ( it != stateCollection_.end () ) {
		delete *it;
		it ++;
	}
	stateCollection_.clear();

	if ( NULL != drawingArea_ ) {
		delete drawingArea_;
	}
}

void GraphicsContext::init()
{
	//currentFont_ = new Font();
	//currentFont_->setGraphicsContext( this );
	//currentFont_->setPointSize( currentFont_->getPointSize() );

	//transformMatrix_.identity();
}


void GraphicsContext::setCurrentFont(Font * font)
{
	Font& currentFont = currentGraphicsState_->font_;
	currentFont = *font;
	currentFont.setGraphicsContext( this );
	currentFont.setPointSize( currentFont.getPointSize() );
}

void GraphicsContext::setCurrentFont( const Font * font )
{
	Font& currentFont = currentGraphicsState_->font_;
	currentFont = *font;
	currentFont.setGraphicsContext( this );
	currentFont.setPointSize( currentFont.getPointSize() );
}

void GraphicsContext::setCurrentFill(Fill * fill)
{
	if ( NULL != fill ){
		fill->setContext( this );
	}
	currentGraphicsState_->fill_ = fill;
}

void GraphicsContext::setCurrentStroke(Stroke * stroke)
{
	if ( NULL != stroke ){
		stroke->setContext( this );
	}
	currentGraphicsState_->stroke_ = stroke;
}

void GraphicsContext::draw(Path * path)
{
	Fill* fill = currentGraphicsState_->fill_;
	Stroke* stroke = currentGraphicsState_->stroke_;
	if ( NULL != fill ){
		fill->render( path );
	}
	if ( NULL != stroke ){
		stroke->render( path );
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
		Color oldColor = *currentGraphicsState_->font_.getColor();

		currentGraphicsState_->font_.setColor( hilight );

		textAt( x+1, y+1, text );

		currentGraphicsState_->font_.setColor( shadow );

		textAt( x, y, text );

		//reset the original color
		currentGraphicsState_->font_.setColor( &oldColor );
	}
}


void GraphicsContext::textAt(const double & x, const double & y, const String & text)
{
	Rect bounds( x, y, x + getTextWidth(text), y + getTextHeight(text) );
	Rect tmp = bounds;

	double xx = bounds.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei00]) +
							bounds.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei10]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei20]);

	double yy = bounds.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei01]) +
							bounds.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei11]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei21]);

	tmp.offset( xx - tmp.left_, yy - tmp.top_ );


	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( tmp, text );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}

void GraphicsContext::textAt( const double & x, const double & y, const String& text, const long drawOptions )
{
	Rect bounds( x, y, x + getTextWidth(text), y + getTextHeight(text) );

	double xx = x * (currentGraphicsState_->transformMatrix_[Matrix2D::mei00]) +
							y * (currentGraphicsState_->transformMatrix_[Matrix2D::mei10]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei20]);

	double yy = x * (currentGraphicsState_->transformMatrix_[Matrix2D::mei01]) +
							y * (currentGraphicsState_->transformMatrix_[Matrix2D::mei11]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei21]);

	bounds.offset( xx - bounds.left_, yy - bounds.top_ );

	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {

		contextPeer_->textAt( bounds, text, drawOptions );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}


void GraphicsContext::rectangle(const double & x1, const double & y1, const double & x2, const double & y2)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptRect) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptRect) );
}

void GraphicsContext::roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
								const double & xc, const double & yc)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

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
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptEllipse) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptEllipse) );
}


void GraphicsContext::arc( const double& centerX,  const double& centerY,
				const double& radiusWidth, const double& radiusHeight,
				const double& startAngle, const double& endAngle)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(centerX,centerY,PointOperation::ptArc) );
	pathOperations_.push_back( PointOperation(radiusHeight,radiusHeight,PointOperation::ptArc) );
	pathOperations_.push_back( PointOperation(startAngle,endAngle,PointOperation::ptArc) );
}


void GraphicsContext::pie(const double & x1, const double & y1, const double & x2, const double & y2,
                          const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	//contextPeer_->pie( x1, y1, x2, y2, x3, y3, x4, y4 );
}

void GraphicsContext::chord(const double & x1, const double & y1, const double & x2, const double & y2,
                            const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	//contextPeer_->chord( x1, y1, x2, y2, x3, y3, x4, y4 );
}


void GraphicsContext::polyline( const std::vector<Point>& pts )
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	std::vector<Point>::const_iterator it = pts.begin();
	while ( it != pts.end() ) {
		const Point& pt = *it;
		pathOperations_.push_back( PointOperation(pt.x_, pt.y_, PointOperation::ptPolyLine) );
		++it;
	}
}

void GraphicsContext::curve(const double & x1, const double & y1, const double & x2, const double & y2,
                            const double & x3, const double & y3, const double & x4, const double & y4)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x1,y1,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x2,y2,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x3,y3,PointOperation::ptBezier) );
	pathOperations_.push_back( PointOperation(x4,y4,PointOperation::ptBezier) );
}

void GraphicsContext::lineTo(const double & x, const double & y)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

	pathOperations_.push_back( PointOperation(x,y,PointOperation::ptLineTo) );
}

void GraphicsContext::moveTo(const double & x, const double & y)
{
	checkPathOperations();
	currentDrawingState_ = GraphicsContext::gsAddingGraphicsOps;

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

void GraphicsContext::setCurrentTransform( const Matrix2D& transform )
{
	currentGraphicsState_->transformMatrix_ = transform;
}

Matrix2D* GraphicsContext::getCurrentTransform()
{
	return &currentGraphicsState_->transformMatrix_;
}

void GraphicsContext::setRotation( const double& theta )
{
	currentGraphicsState_->rotation_  = theta;
	currentGraphicsState_->compositeMatrix();
}

void GraphicsContext::setTranslation( const double transX, const double& transY )
{
	currentGraphicsState_->translateX_  = transX;
	currentGraphicsState_->translateY_  = transY;
	currentGraphicsState_->compositeMatrix();
}

void GraphicsContext::setShear( const double& shearX, const double& shearY )
{
	currentGraphicsState_->shearX_  = shearX;
	currentGraphicsState_->shearY_  = shearY;
	currentGraphicsState_->compositeMatrix();
}

void GraphicsContext::setScale( const double& scaleX, const double& scaleY )
{
	currentGraphicsState_->scaleX_  = scaleX;
	currentGraphicsState_->scaleY_  = scaleY;
	currentGraphicsState_->compositeMatrix();
}

void GraphicsContext::concatRotation( const double& theta )
{
	currentGraphicsState_->rotation_  += theta;
	Matrix2D rot;
	rot.rotate( currentGraphicsState_->rotation_ );
	Matrix2D tmp;
	tmp.multiply( &rot, &currentGraphicsState_->transformMatrix_ );

	currentGraphicsState_->transformMatrix_ = tmp;

}

void GraphicsContext::concatTranslation( const double transX, const double& transY )
{
	currentGraphicsState_->translateX_  += transX;
	currentGraphicsState_->translateY_  += transY;
	Matrix2D translation;
	translation.translate( currentGraphicsState_->translateX_, currentGraphicsState_->translateY_);
	Matrix2D tmp;
	tmp.multiply( &translation, &currentGraphicsState_->transformMatrix_ );

	currentGraphicsState_->transformMatrix_ = tmp;
}

void GraphicsContext::concatShear( const double& shearX, const double& shearY )
{
	currentGraphicsState_->shearX_  += shearX;
	currentGraphicsState_->shearY_  += shearY;
	Matrix2D shear;
	shear.shear( currentGraphicsState_->shearX_, currentGraphicsState_->shearY_ );
	Matrix2D tmp;
	tmp.multiply( &shear, &currentGraphicsState_->transformMatrix_ );

	currentGraphicsState_->transformMatrix_ = tmp;
}

void GraphicsContext::concatScale( const double& scaleX, const double& scaleY )
{
	currentGraphicsState_->scaleX_  += scaleX;
	currentGraphicsState_->scaleY_  += scaleY;
	Matrix2D scale;
	scale.scale( currentGraphicsState_->scaleX_, currentGraphicsState_->scaleY_ );
	Matrix2D tmp;
	tmp.multiply( &scale, &currentGraphicsState_->transformMatrix_ );

	currentGraphicsState_->transformMatrix_ = tmp;
}

Font* GraphicsContext::getCurrentFont()
{
	return &currentGraphicsState_->font_;
}

void GraphicsContext::setColor( Color* color )
{
	if ( NULL != color ) {
		currentGraphicsState_->color_ = *color;
	}
}

void GraphicsContext::setColor( const Color* color )
{
	if ( NULL != color ) {
		currentGraphicsState_->color_ = *color;
	}
}

Color* GraphicsContext::getColor()
{
	return &currentGraphicsState_->color_;
}


void GraphicsContext::textBoundedBy( Rect* bounds, const String& text, const bool& wordWrap )
{
	long drawOptions = wordWrap ? GraphicsContext::tdoWordWrap : GraphicsContext::tdoNone;

	Rect tmp = *bounds;
	double xx = tmp.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei00]) +
							tmp.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei10]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei20]);

	double yy = tmp.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei01]) +
							tmp.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei11]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei21]);

	tmp.offset( xx - tmp.left_, yy - tmp.top_ );

	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( tmp, text, drawOptions );

		contextPeer_->finishedDrawing( 	GraphicsContext::doText );
	}
}

void GraphicsContext::textBoundedBy( Rect* bounds, const String& text, const long drawOptions )
{
	Rect tmp = *bounds;
	double xx = tmp.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei00]) +
							tmp.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei10]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei20]);

	double yy = tmp.left_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei01]) +
							tmp.top_ * (currentGraphicsState_->transformMatrix_[Matrix2D::mei11]) +
								(currentGraphicsState_->transformMatrix_[Matrix2D::mei21]);

	tmp.offset( xx - tmp.left_, yy - tmp.top_ );

	if ( contextPeer_->prepareForDrawing( GraphicsContext::doText ) ) {
		contextPeer_->textAt( tmp, text, drawOptions );

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

	Path* clipPath = currentGraphicsState_->clippingPath_;

	if ( NULL != clipPath ) { //release the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clipPath );
		pathObj->release();
	}

	clipPath = rectClipPath;

	if ( NULL != clipPath ) { //take ownership of the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clipPath );
		pathObj->addRef();
	}

	currentGraphicsState_->clippingPath_ = clipPath;

	contextPeer_->setClippingRect( rect );
}

void GraphicsContext::setClippingPath( Path* clippingPath )
{
	Path* clipPath = currentGraphicsState_->clippingPath_;

	if ( NULL != clipPath ) { //release the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clipPath );
		pathObj->release();
	}

	clipPath = clippingPath;

	if ( NULL != clipPath ) { //take ownership of the underlying object instance
		Object* pathObj = dynamic_cast<Object*>( clipPath );
		pathObj->addRef();
	}

	currentGraphicsState_->clippingPath_ = clipPath;

	contextPeer_->setClippingPath( clipPath );
}

Rect GraphicsContext::getClippingRect()
{
	Rect result;

	Path* clipPath = currentGraphicsState_->clippingPath_;

	if ( NULL != clipPath ) {
		result = clipPath->getBounds();
	}

	return result;
}

Path* GraphicsContext::getClippingPath()
{
	return currentGraphicsState_->clippingPath_;
}

void GraphicsContext::drawThemeSelectionRect( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeSelectionRect( rect, state );
}

void GraphicsContext::drawThemeFocusRect( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeFocusRect( rect, state );
}

void GraphicsContext::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect )
{
	contextPeer_->drawThemeButtonRect( rect, state, captionRect );
}

void GraphicsContext::drawThemeButtonFocusRect( Rect* rect )
{
	contextPeer_->drawThemeButtonFocusRect( rect );
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

void GraphicsContext::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	contextPeer_->drawThemeTabContent( rect, state );
}

void GraphicsContext::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex )
{
	contextPeer_->drawThemeTabs( rect, paneState, selectedTabState, otherTabs, tabNames, selectedTabIndex );
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
	currentGraphicsState_->strokeWidth_ = width;
}

double GraphicsContext::getStrokeWidth()
{
	return currentGraphicsState_->strokeWidth_;
}

void GraphicsContext::execPathOperations()
{
	currentDrawingState_ = GraphicsContext::gsExecutingGraphicsOps;

	std::vector<PointOperation>::iterator it = pathOperations_.begin();

	double tmpX;
	double tmpY;


	Matrix2D& transform = currentGraphicsState_->transformMatrix_;

	while ( it != pathOperations_.end() ) {
		PointOperation& pointOp = *it;

		switch ( pointOp.primitive ){
			case PointOperation::ptMoveTo : {
				currentGraphicsState_->currentMoveTo_.x_ = pointOp.x;
				currentGraphicsState_->currentMoveTo_.y_ = pointOp.y;

				tmpX = pointOp.x * (transform[Matrix2D::mei00]) +
							pointOp.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				tmpY = pointOp.x * (transform[Matrix2D::mei01]) +
							pointOp.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);



				contextPeer_->moveTo( tmpX, tmpY );
				++it;
			}
			break;

			case PointOperation::ptLineTo :{
				tmpX = pointOp.x * (transform[Matrix2D::mei00]) +
							pointOp.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				tmpY = pointOp.x * (transform[Matrix2D::mei01]) +
							pointOp.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

				contextPeer_->lineTo( tmpX, tmpY );
				++it;
			}
			break;

			case PointOperation::ptPolyLine :{
				std::vector<Point> tmpPts;
				PointOperation::PrimitiveType type = pointOp.primitive;

				while ( (it != pathOperations_.end()) && (type == PointOperation::ptPolyLine) ) {
					PointOperation& pt = *it;
					type = pt.primitive;
					tmpX = pt.x * (transform[Matrix2D::mei00]) +
							pt.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

					tmpY = pt.x * (transform[Matrix2D::mei01]) +
							pt.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

					tmpPts.push_back( Point(tmpX,tmpY) );
					++it;
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

				Point p1;
				Point p2;
				Point p3;
				Point p4;

				PointOperation& pt1 = *it;
				p1.x_ = pt1.x * (transform[Matrix2D::mei00]) +
							pt1.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				p1.y_ = pt1.x * (transform[Matrix2D::mei01]) +
							pt1.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

				++it;

				PointOperation& pt2 = *it;
				p2.x_ = pt2.x * (transform[Matrix2D::mei00]) +
							pt2.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				p2.y_ = pt2.x * (transform[Matrix2D::mei01]) +
							pt2.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

				++it;

				PointOperation& pt3 = *it;
				p3.x_ = pt3.x * (transform[Matrix2D::mei00]) +
							pt3.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				p3.y_ = pt3.x * (transform[Matrix2D::mei01]) +
							pt3.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

				++it;

				PointOperation& pt4 = *it;
				p4.x_ = pt4.x * (transform[Matrix2D::mei00]) +
							pt4.y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

				p4.y_ = pt4.x * (transform[Matrix2D::mei01]) +
							pt4.y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

				++it;

				contextPeer_->curve( p1.x_, p1.y_, p2.x_, p2.y_,
										p3.x_, p3.y_, p4.x_, p4.y_ );


			}
			break;

			case PointOperation::ptRect:{

				PointOperation& pt1 = *it;
				++it;

				PointOperation& pt2 = *it;
				++it;


				std::vector<Point> tmpPts(5);
				tmpPts[0].x_ = pt1.x;
				tmpPts[0].y_ = pt1.y;
				tmpPts[1].x_ = pt2.x;
				tmpPts[1].y_ = pt1.y;
				tmpPts[2].x_ = pt2.x;
				tmpPts[2].y_ = pt2.y;
				tmpPts[3].x_ = pt1.x;
				tmpPts[3].y_ = pt2.y;
				tmpPts[4] = tmpPts[0];

				std::vector<Point>::iterator ptIt = tmpPts.begin();

				while ( ptIt != tmpPts.end() ) {
					Point& p = *ptIt;
					tmpX = p.x_ * (transform[Matrix2D::mei00]) +
							p.y_ * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

					tmpY = p.x_ * (transform[Matrix2D::mei01]) +
							p.y_ * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

					p.x_ = tmpX;
					p.y_ = tmpY;
					++ptIt;
				}

				contextPeer_->polyline( tmpPts );



				//contextPeer_->rectangle( pt1.x, pt1.y, pt2.x, pt2.y );
			}
			break;

			case PointOperation::ptRoundRect :{



				PointOperation& pt1 = *it;
				++it;

				PointOperation& pt2 = *it;
				++it;

				PointOperation& pt3 = *it;
				++it;

				std::vector<Point> tmpPts;
				buildRoundRect( pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, tmpPts, transform );

				contextPeer_->polyline( tmpPts );

			}
			break;

			case PointOperation::ptEllipse : {
				PointOperation& pt1 = *it;
				++it;

				PointOperation& pt2 = *it;
				++it;

				//contextPeer_->ellipse( pt1.x, pt1.y, pt2.x, pt2.y );

				std::vector<Point> tmpPts;
				buildEllipse( pt1.x, pt1.y, pt2.x, pt2.y, tmpPts, transform );

				contextPeer_->polyline( tmpPts );
			}
			break;

			case PointOperation::ptArc :{
				if ( (pathOperations_.end() - it) < 3 ) {
					throw RuntimeException( MAKE_ERROR_MSG_2("Not enough path operations left to complete the bezier curve") );
				}

				PointOperation& pt1 = *it;
				++it;

				PointOperation& pt2 = *it;
				++it;

				PointOperation& pt3 = *it;
				++it;


				std::vector<Point> tmpPts;
				buildArc( pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, tmpPts, transform );

				contextPeer_->polyline( tmpPts );
			}
			break;

			case PointOperation::ptClose : {
				PointOperation& pt = *it;
				contextPeer_->lineTo( pt.x, pt.y );
				++it;
			}
			break;

			default : {
				it = pathOperations_.end();
				break; //quit the loop
			}
			break;
		}
	}

	currentDrawingState_ = GraphicsContext::gsNone;
}


void GraphicsContext::checkPathOperations()
{
	if ( GraphicsContext::gsAddingGraphicsOps != currentDrawingState_ ) {
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

		//FIXME!!!!!!!
		//drawingArea_->getImageBits()->renderBuffer_->clip_box( agg::rect( viewableBounds_.left_,
		//																	viewableBounds_.top_,
		//																	viewableBounds_.right_,
		//																	viewableBounds_.bottom_ ) );

		drawPartialImage(  viewableBounds_.getTopLeft(), &viewableBounds_, drawingArea_ );
	}

	renderAreaDirty_ = false;
}

void GraphicsContext::buildArc( double centerX,  double centerY,
            double radiusWidth, double radiusHeight,
            double startAngle, double endAngle, std::vector<Point>& pts, const Matrix2D& transform )
{
	agg::path_storage path;

	agg::arc arcPath(centerX,
						centerY,
						radiusWidth, radiusHeight,
						Math::degreesToRadians(startAngle), Math::degreesToRadians(endAngle));

	path.concat_path( arcPath );

	for ( size_t i=0;i<path.total_vertices();i++ ) {
		double vert_x,vert_y;
		path.vertex(i,&vert_x, &vert_y);	

		Point pt;
		pt.x_ = vert_x * (transform[Matrix2D::mei00]) +
							vert_y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

		pt.y_ = vert_x * (transform[Matrix2D::mei01]) +
							vert_y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

		pts.push_back( pt );
	}


	path.remove_all();
}


void GraphicsContext::buildRoundRect( double x1, double y1, double x2, double y2,
							double cornerArcWidth, double cornerArcHeight,
							std::vector<Point>& pts, const Matrix2D& transform )
{
	agg::path_storage path;

	path.move_to( x1 + cornerArcWidth/2.0, y1 );
	path.line_to( x2 - cornerArcWidth, y1 );

	agg::arc arc1(x2 - cornerArcWidth/2.0,
		y1 + cornerArcHeight/2.0,
		cornerArcWidth/2.0, cornerArcHeight/2.0,
		Math::degreesToRadians(270), Math::degreesToRadians(0));

	path.concat_path( arc1 );

	path.line_to( x2, y2 - cornerArcHeight/2.0 );

	agg::arc arc2(x2 - cornerArcWidth/2.0,
		y2 - cornerArcHeight/2.0,
		cornerArcWidth/2.0, cornerArcHeight/2.0,
		Math::degreesToRadians(0), Math::degreesToRadians(90));

	path.concat_path( arc2 );

	path.line_to( x1 + cornerArcWidth/2.0, y2 );

	agg::arc arc3(x1 + cornerArcWidth/2.0,
		y2 - cornerArcHeight/2.0,
		cornerArcWidth/2.0, cornerArcHeight/2.0,
		Math::degreesToRadians(90), Math::degreesToRadians(180));

	path.concat_path( arc3 );

	path.line_to( x1, y1 + cornerArcHeight/2.0 );

	agg::arc arc4(x1 + cornerArcWidth/2.0,
		y1 + cornerArcHeight/2.0,
		cornerArcWidth/2.0, cornerArcHeight/2.0,
		Math::degreesToRadians(180), Math::degreesToRadians(270));

	path.concat_path( arc4 );


	//agg::path_storage::const_iterator it = path.begin();
	for (size_t i=0;i<path.total_vertices();i++ ) {	
		double vert_x, vert_y;
		path.vertex( i, &vert_x, &vert_y );


		Point pt;
		pt.x_ = vert_x * (transform[Matrix2D::mei00]) +
							vert_y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

		pt.y_ = vert_x * (transform[Matrix2D::mei01]) +
							vert_y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

		pts.push_back( pt );
	}
}

void GraphicsContext::buildEllipse( double x1, double y1, double x2, double y2,
							std::vector<Point>& pts, const Matrix2D& transform )
{
	agg::path_storage path;
	agg::ellipse ellipseShape( x1 + ((x2-x1)/2.0), y1 + ((y2-y1)/2.0),
								abs(static_cast<long>(x2-x1)), abs(static_cast<long>(y2-y1)), 100 );
	path.concat_path( ellipseShape );

	for (size_t i=0;i<path.total_vertices();i++ ) {
		double vert_x, vert_y;
		path.vertex( i, &vert_x, &vert_y );


		Point pt;
		pt.x_ = vert_x * (transform[Matrix2D::mei00]) +
							vert_y * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

		pt.y_ = vert_x * (transform[Matrix2D::mei01]) +
							vert_y * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);

		pts.push_back( pt );
	}

	pts.back() = pts[0];
}

int GraphicsContext::saveState()
{
	GraphicsState* newState = new GraphicsState(*stateCollection_.back());

	stateCollection_.push_back( newState );
	graphicsStateIndex_ = stateCollection_.size() - 1;

	currentGraphicsState_ = stateCollection_[graphicsStateIndex_];

	return graphicsStateIndex_;
}

void GraphicsContext::restoreState( int state )
{
	VCF_ASSERT( state < (int)stateCollection_.size() );
	VCF_ASSERT( state >= 0 );
	if ( (stateCollection_.size() - state) > 0 ) {
		for ( size_t i=state;i<stateCollection_.size();i++ ) {
			delete stateCollection_[i];
		}

		stateCollection_.erase( stateCollection_.begin() + state,
								stateCollection_.end() );
	}

	graphicsStateIndex_ = maxVal<>(0,(state - 1));
	currentGraphicsState_ = stateCollection_[graphicsStateIndex_];
}

bool GraphicsContext::isDefaultTransform()
{
	return (currentGraphicsState_->rotation_ == 0.0) &&
			(currentGraphicsState_->translateX_ == 0.0) &&
			(currentGraphicsState_->translateY_ == 0.0) &&
			(currentGraphicsState_->shearX_ == 0.0) &&
			(currentGraphicsState_->shearY_ == 0.0) &&
			(currentGraphicsState_->scaleX_ == 1.0) &&
			(currentGraphicsState_->scaleY_ == 1.0);
}

void GraphicsContext::makeDefaultTransform()
{
	currentGraphicsState_->rotation_ = 0.0;
	currentGraphicsState_->translateX_ = 0.0;
	currentGraphicsState_->translateY_ = 0.0;
	currentGraphicsState_->shearX_ = 0.0;
	currentGraphicsState_->shearY_ = 0.0;
	currentGraphicsState_->scaleX_ = 1.0;
	currentGraphicsState_->scaleY_ = 1.0;

	currentGraphicsState_->compositeMatrix();
}

double GraphicsContext::getRotation()
{
	return currentGraphicsState_->rotation_;
}

double GraphicsContext::getTranslationX()
{
	return currentGraphicsState_->translateX_;
}

double GraphicsContext::getTranslationY()
{
	return currentGraphicsState_->translateY_;
}

double GraphicsContext::getShearX()
{
	return currentGraphicsState_->shearX_;
}

double GraphicsContext::getShearY()
{
	return currentGraphicsState_->shearY_;
}

double GraphicsContext::getScaleX()
{
	return currentGraphicsState_->scaleX_;
}

double GraphicsContext::getScaleY()
{
	return currentGraphicsState_->scaleY_;
}

bool GraphicsContext::isAntiAliasingOn()
{
	return contextPeer_->isAntiAliasingOn();
}

void GraphicsContext::setAntiAliasingOn( bool antiAliasingOn )
{
	contextPeer_->setAntiAliasingOn( antiAliasingOn );
}


};	// namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.7  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.6.2.8  2006/03/04 02:35:48  ddiego
*upgraded agg from 2.2 to the latest 2.4 version.
*
*Revision 1.6.2.7  2006/03/01 04:34:57  ddiego
*fixed tab display to use themes api.
*
*Revision 1.6.2.6  2006/02/21 04:32:51  ddiego
*comitting moer changes to theme code, progress bars, sliders and tab pages.
*
*Revision 1.6.2.5  2005/11/27 23:55:45  ddiego
*more osx updates.
*
*Revision 1.6.2.4  2005/11/21 04:00:51  ddiego
*more osx updates.
*
*Revision 1.6.2.3  2005/11/10 02:02:39  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.6.2.2  2005/10/17 01:36:34  ddiego
*some more under the hood image stuff. updated agg.
*
*Revision 1.6.2.1  2005/09/03 14:03:53  ddiego
*added a package manager to support package info instances, and
*fixed feature request 1278069 - Background color of the TableControl cells.
*
*Revision 1.6  2005/07/09 23:05:58  ddiego
*added missing gtk files
*
*Revision 1.5  2005/01/02 03:04:25  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.4.2.3  2005/06/26 01:27:53  marcelloptr
*added images to a PushButton
*
*Revision 1.4.2.2  2005/04/25 00:11:59  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.4.2.1  2004/12/19 04:05:03  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3  2004/08/13 18:43:20  ddiego
*fixed missing roundrect functionality, and incorrect value in vc70/71 projects
*
*Revision 1.2.2.14  2004/11/07 19:32:20  marcelloptr
*more documentation
*
*Revision 1.2.2.13  2004/10/27 03:12:18  ddiego
*integrated chrisk changes
*
*Revision 1.2.2.12  2004/10/04 15:50:49  kiklop74
*Added explicit cast to avoid ambiquity on BCB6
*
*Revision 1.2.2.11  2004/09/09 03:09:26  marcelloptr
*minor change for style
*
*Revision 1.2.2.10  2004/09/06 04:40:43  ddiego
*added font rotation back in, this time with support for matching
*the graphic contexts current transform.
*
*Revision 1.2.2.9  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2.2.8  2004/09/03 04:05:46  ddiego
*fixes to add matrix transform support for images.
*
*Revision 1.2.2.7  2004/09/01 03:50:39  ddiego
*fixed font drawing bug that tinkham pointed out.
*
*Revision 1.2.2.6  2004/08/31 21:12:07  ddiego
*graphice save and restore state
*
*Revision 1.2.2.5  2004/08/31 10:24:15  marcelloptr
*project changed postfix operator into prefix where not necessary so to eliminate agg warning
*
*Revision 1.2.2.4  2004/08/31 04:12:13  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.3  2004/08/26 01:44:40  ddiego
*fixed font pix size bug that handled non true type fonts poorly.
*
*Revision 1.2.2.2  2004/08/24 04:29:58  ddiego
*more printing work, still not yet integrated.
*
*Revision 1.2.2.1  2004/08/19 03:22:54  ddiego
*updates so new system tray code compiles
*
*Revision 1.3  2004/08/13 18:43:20  ddiego
*fixed missing roundrect functionality, and incorrect value in vc70/71 projects
*
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


