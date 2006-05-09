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

void GraphicsContext::bitBlit( const double& x, const double& y, Image* image )
{
	if ( contextPeer_->prepareForDrawing( GraphicsContext::doImage ) ) {

		contextPeer_->bitBlit( x, y, image );

		contextPeer_->finishedDrawing( 	GraphicsContext::doImage );
	}
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

void GraphicsContext::drawThemeMenuItemText( Rect* rect, MenuState& state )
{
	contextPeer_->drawThemeMenuItemText( rect, state );
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
$Id$
*/
