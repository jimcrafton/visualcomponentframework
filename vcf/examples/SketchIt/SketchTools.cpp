/**
*CVS Log info
*$Log$
*Revision 1.2  2003/08/09 02:56:42  ddiego
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
*Revision 1.1.2.5  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.1.2.4  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.1.2.3  2003/07/21 03:08:29  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.1.2.2  2003/07/18 04:38:54  ddiego
*got more work done on the sketch examples plus fixed a bug in the application
*of a transform ot a path
*
*Revision 1.1.2.1  2003/07/17 03:02:46  ddiego
*added sketch example
*
*/



#include "ApplicationKit.h"
#include "SketchTools.h"
#include "SketchDocument.h"


using namespace VCF;



void Tool::attach( VCF::Control* control )
{
	EventHandler* ev = getEventHandler( "Tool::onMouseDown" );
	if ( ev == NULL ) {
		ev = new MouseEventHandler<Tool>( this, &Tool::onMouseDown, "Tool::onMouseDown" );
	}

	control->MouseDown += ev;

	ev = getEventHandler( "Tool::onMouseMove" );
	if ( ev == NULL ) {
		ev = new MouseEventHandler<Tool>( this, &Tool::onMouseMove, "Tool::onMouseMove" );
	}

	control->MouseMove += ev;

	ev = getEventHandler( "Tool::onMouseUp" );
	if ( ev == NULL ) {
		ev = new MouseEventHandler<Tool>( this, &Tool::onMouseUp, "Tool::onMouseUp" );
	}

	control->MouseUp += ev;

	
	ev = getEventHandler( "Tool::onDblClick" );
	if ( ev == NULL ) {
		ev = new MouseEventHandler<Tool>( this, &Tool::onDblClick, "Tool::onDblClick" );
	}

	control->MouseDoubleClicked += ev;


	ev = getEventHandler( "Tool::onKeyPressed" );
	if ( ev == NULL ) {
		ev = new KeyboardEventHandler<Tool>( this, &Tool::onKeyPressed, "Tool::onKeyPressed" );
	}

	control->KeyPressed += ev;

	ev = getEventHandler( "Tool::onKeyDown" );
	if ( ev == NULL ) {
		ev = new KeyboardEventHandler<Tool>( this, &Tool::onKeyDown, "Tool::onKeyDown" );
	}

	control->KeyDown += ev;

	ev = getEventHandler( "Tool::onKeyUp" );
	if ( ev == NULL ) {
		ev = new KeyboardEventHandler<Tool>( this, &Tool::onKeyUp, "Tool::onKeyUp" );
	}

	control->KeyUp += ev;

	currentControl_ = control;
}

VCF::Control* Tool::detach()
{
	if ( NULL == currentControl_ ) {
		return NULL;
	}


	EventHandler* ev = getEventHandler( "Tool::onMouseDown" );
	if ( ev != NULL ) {
		currentControl_->MouseDown -= ev;
	}

	ev = getEventHandler( "Tool::onMouseMove" );
	if ( ev != NULL ) {
		currentControl_->MouseMove -= ev;
	}

	ev = getEventHandler( "Tool::onMouseUp" );
	if ( ev != NULL ) {
		currentControl_->MouseUp -= ev;
	}

	ev = getEventHandler( "Tool::onDblClick" );
	if ( ev != NULL ) {
		currentControl_->MouseDoubleClicked -= ev;
	}	


	ev = getEventHandler( "Tool::onKeyPressed" );
	if ( ev != NULL ) {
		currentControl_->KeyPressed -= ev;
	}
	

	ev = getEventHandler( "Tool::onKeyDown" );
	if ( ev != NULL ) {
		currentControl_->KeyDown -= ev;
	}

	ev = getEventHandler( "Tool::onKeyUp" );
	if ( ev != NULL ) {
		currentControl_->KeyUp -= ev;
	}

	Control* result = currentControl_;
	currentControl_ = NULL;

	return result;
	
}

ToolManager::ToolManager():
	currentTool_(NULL),
	currentControl_(NULL)
{

}

ToolManager::~ToolManager()
{
	std::map<VCF::MenuItem*,Tool*>::iterator it = toolMap_.begin();
	while ( it != toolMap_.end() ) {
		delete it->second;
		it ++;
	}
}

ToolManager* ToolManager::manager = NULL;

void ToolManager::init()
{	
	ToolManager::manager = new ToolManager();
}

void ToolManager::terminate()
{
	delete ToolManager::manager;
}

ToolManager* ToolManager::getToolManager()
{
	return ToolManager::manager;
}


void ToolManager::registerTool( Tool* tool, MenuItem* item )
{
	toolMap_[item] = tool;
	EventHandler* ev = getEventHandler( "ToolManager::onMenuItemClicked" );
	if ( NULL == ev ) {
		ev = new MenuItemEventHandler<ToolManager>( this, &ToolManager::onMenuItemClicked, "ToolManager::onMenuItemClicked" );
	}
	item->addMenuItemClickedHandler( ev );

	ev = getEventHandler( "ToolManager::onMenuItemUpdate" );
	if ( NULL == ev ) {
		ev = new MenuItemEventHandler<ToolManager>( this, &ToolManager::onMenuItemUpdate, "ToolManager::onMenuItemUpdate" );
	}

	item->addMenuItemUpdateHandler( ev );
}

void ToolManager::onMenuItemClicked( MenuItemEvent* e )
{
	std::map<MenuItem*,Tool*>::iterator found = toolMap_.find( (MenuItem*)e->getSource() );
	if ( NULL != currentTool_ ) {
		currentTool_->detach();
	}

	if ( found != toolMap_.end() ) {		

		currentTool_ = found->second;
		
		Window* window = DocumentManager::getDocumentManager()->getCurrentDocument()->getWindow();

		currentTool_->attach( window );
		currentTool_->reset();
	}
	else {
		currentTool_ = NULL;
	}	
}

void ToolManager::onMenuItemUpdate( MenuItemEvent* e )
{
	MenuItem* item = (MenuItem*)e->getSource();
	std::map<MenuItem*,Tool*>::iterator found = toolMap_.find( item );

	if ( found != toolMap_.end() ) {
		if ( found->second == currentTool_ ) {
			item->setChecked( true );
		}
		else {
			item->setChecked( false );
		}
	}
}



SelectTool::SelectTool():
	mouseOverShape_(NULL)
{

}

SelectTool::~SelectTool()
{

}

Shape* SelectTool::hitTest( Point& pt )
{
	Shape* result = NULL;

	SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
	Enumerator<Shape*>* shapes = doc->getShapes();
	while ( shapes->hasMoreElements() ) {
		Shape* shape = shapes->nextElement();
		
		if ( shape->fill_ && shape->polygon_.contains( pt ) ) {
			result = shape;
			break;
		}
		else if ( shape->polygon_.intersects( pt ) ) {
			
			result = shape;
			break;
		}
		
	}

	return result;
}

void SelectTool::onMouseDown( VCF::MouseEvent* e )
{
	SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
	if ( e->hasLeftButton() ) {
		Shape* shape =  hitTest( *e->getPoint() );
		if ( shape ) {
			doc->setSelectedShape( shape );
			dragPoint_ = *e->getPoint(); 
			startDragPoint_ = dragPoint_;

		}
		else {
			doc->setSelectedShape( NULL );	
		}
	}
}

void SelectTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();
		

		if ( NULL != shape ) {
			

			Matrix2D m1;
			m1.translate( dragPoint_.x_ - startDragPoint_.x_,
							dragPoint_.y_ - startDragPoint_.y_ );

			m1.invert();
			shape->polygon_.applyTransform( m1 );


			Matrix2D m2;
			m2.translate( e->getPoint()->x_ - startDragPoint_.x_,
							e->getPoint()->y_ - startDragPoint_.y_ );
			
			shape->polygon_.applyTransform( m2 );
			doc->updateAllViews();


			dragPoint_ = *e->getPoint();
		}
	}
	else {
		if ( (!e->hasMiddleButton()) && (!e->hasRightButton()) ) {
			mouseOverShape_ =  hitTest( *e->getPoint() );

			SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
			doc->updateAllViews();
		}
	}
	
	
	//doc->setSelectedShape( shape );	
}

void SelectTool::onMouseUp( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();
		if ( NULL != shape ) {
			

			Matrix2D m1;
			m1.translate( dragPoint_.x_ - startDragPoint_.x_,
							dragPoint_.y_ - startDragPoint_.y_ );

			m1.invert();
			shape->polygon_.applyTransform( m1 );


			Matrix2D m2;
			m2.translate( e->getPoint()->x_ - startDragPoint_.x_,
							e->getPoint()->y_ - startDragPoint_.y_ );
			
			shape->polygon_.applyTransform( m2 );


			
/*
			Control* c = (Control*)e->getSource();
			GraphicsContext* ctx = c->getContext();

			BasicStroke bs;
			ctx->setCurrentStroke( &bs );
			
			bs.setAllowAntiAlias( false );
			bs.setColor( Color::getColor( "green" ) );
			
			ctx->draw( &shape->polygon_ );
			
			ctx->setCurrentStroke( NULL );			
*/
			doc->updateAllViews();
		}
	}
}

void SelectTool::paintState( VCF::GraphicsContext* ctx )
{
	
	SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
	//Shape* shape = doc->getSelectedShape();
	if ( NULL != mouseOverShape_ ) {
		BasicStroke bs;
		ctx->setCurrentStroke( &bs );

		bs.setAllowAntiAlias( false );
		bs.setColor( Color::getColor( "red" ) );

		ctx->draw( &mouseOverShape_->polygon_ );

		ctx->setCurrentStroke( NULL );
	}
	
	BasicStroke bs;
	ctx->setCurrentStroke( &bs );
	bs.setAllowAntiAlias( false );
	bs.setColor( Color::getColor( "green" ) );

	Enumerator<Shape*>* shapes = doc->getSelectedShapes();
	while ( shapes->hasMoreElements() ) {
		Shape* shape = shapes->nextElement();		
		ctx->draw( &shape->polygon_ );
	}

	ctx->setCurrentStroke( NULL );

}


LineTool::LineTool()
{

}

LineTool::~LineTool()
{

}

void LineTool::onMouseDown( VCF::MouseEvent* e )
{
	start_ = *e->getPoint();
	end_ = start_;
	Control* c = (Control*)e->getSource();
	GraphicsContext* ctx = c->getContext();
	ctx->setColor( Color::getColor("blue") );
	ctx->setXORModeOn( true );
	ctx->moveTo( start_ );
	ctx->lineTo( end_ );
	ctx->strokePath();
	ctx->setXORModeOn( false );
}

void LineTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();
		ctx->setColor( Color::getColor("blue") );
		ctx->setXORModeOn( true );
		ctx->moveTo( start_ );
		ctx->lineTo( end_ );
		ctx->strokePath();

		end_ = *e->getPoint();

		ctx->moveTo( start_ );
		ctx->lineTo( end_ );
		ctx->strokePath();

		ctx->setXORModeOn( false );
		
	}
}

void LineTool::onMouseUp( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();
		ctx->setColor( Color::getColor("blue") );
		ctx->setXORModeOn( true );
		ctx->moveTo( start_ );
		ctx->lineTo( end_ );
		ctx->strokePath();

		end_ = *e->getPoint();

		ctx->moveTo( start_ );
		ctx->lineTo( end_ );
		ctx->strokePath();

		ctx->setXORModeOn( false );

		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape shape;
		shape.polygon_.moveTo( start_.x_, start_.y_ );
		shape.polygon_.lineTo( end_.x_, end_.y_ );				
		doc->addShape( shape );
	}
}



#define _EPSILON_		0.000000000001


double arcSin (double fValue)
{
    if ( -1.0f < fValue )   {
        if ( fValue < 1.0f )
            return (double)asin(fValue);
        else
            return -(M_PI/2.0);
    }
    else {
        return M_PI/2.0;
    }
}


double getAngleFromLine( Point p1, Point p2 )
{
	double result;

	double a,b,c,d;	

	a = fabs(p1.y_-p2.y_); 
	b = fabs(p1.x_-p2.x_);

	c = sqrt(a*a+b*b);

	

	c = (c <= _EPSILON_) ? 0.0 : b/c;

	d = VCF::Math::radiansToDegrees(arcSin(c));

	if ( (p1.x_ >= p2.x_) && (p1.y_ <= p2.y_)) {
		result = 90-d;
	}
	else if ((p1.x_ < p2.x_) && (p1.y_ <= p2.y_)) {
		result = d+90;
	}
	else if ((p1.x_ < p2.x_) && (p1.y_ > p2.y_)) {
		result = 180+(90-d);
	}
	else if ((p1.x_ >=  p2.x_) && (p1.y_ > p2.y_)) {
		result = 270+d;
	}

	result = 360.00 - result;
		
	return result;
}

void RotateTool::paintState( VCF::GraphicsContext* ctx )
{

}

void RotateTool::onMouseDown( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		startDragPoint_ = dragPoint_ = *e->getPoint();
		startAngle_ = getAngleFromLine( dragPoint_, startDragPoint_ );
		
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();

		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		origin_ = startDragPoint_;

		Rect bounds = shape->polygon_.getBounds();
	}
}

void RotateTool::rotateShape( Shape* shape, Point pt )
{
	Matrix2D m1;
	m1.translate( -origin_.x_, -origin_.y_ );
	
	shape->polygon_.applyTransform( m1 );
	
	double angle = getAngleFromLine( pt, startDragPoint_ ) - getAngleFromLine( dragPoint_, startDragPoint_ ) ;		
	Matrix2D m2;
	m2.rotate( angle );//				
	
	m1.translate( origin_.x_, origin_.y_ );
	
	shape->polygon_.applyTransform( *m2.multiply( &m2, &m1 ) );
}

void RotateTool::onMouseMove( VCF::MouseEvent* e )
{
	
	if ( e->hasLeftButton() ) {		

		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		rotateShape( shape, *e->getPoint() );

		doc->updateAllViews();

		dragPoint_ = *e->getPoint();
	}
}

void RotateTool::onMouseUp( VCF::MouseEvent* e )
{	
	if ( e->hasLeftButton() ) {
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		rotateShape( shape, *e->getPoint() );

		doc->updateAllViews();

		dragPoint_ = *e->getPoint();
	}
}

void ScaleTool::paintState( VCF::GraphicsContext* ctx )
{

}

void ScaleTool::onMouseDown( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		startDragPoint_ = dragPoint_ = *e->getPoint();
		
		
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();

		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}
		origin_ = startDragPoint_;

		bounds_ = shape->polygon_.getBounds();
	}
}

void ScaleTool::scaleShape( Shape* shape, VCF::Point pt )
{
	Matrix2D m1;
	m1.translate( -origin_.x_, -origin_.y_ );
	
	shape->polygon_.applyTransform( m1 );
	
	double dx = pt.x_ - origin_.x_;
	double dy = pt.y_ - origin_.y_;
	double t  = bounds_.getWidth() - (dx) /2.0;
	if ( t  == 0.0 ) {
		t = _EPSILON_;
	}
	double sx = bounds_.getWidth() / t;

	t = bounds_.getHeight() - (dy)/2.0;
	if ( t  == 0.0 ) {
		t = _EPSILON_;
	}

	double sy = bounds_.getHeight() / t;

		
	Matrix2D m2;
	m2.scale( sx,sy );
	
	m1.translate( origin_.x_, origin_.y_ );
	
	shape->polygon_.applyTransform( *m2.multiply( &m2, &m1 ) );	
}

void ScaleTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		scaleShape( shape, *e->getPoint() );

		doc->updateAllViews();

		dragPoint_ = *e->getPoint();
	}
}

void ScaleTool::onMouseUp( VCF::MouseEvent* e )
{

}


void SkewTool::paintState( VCF::GraphicsContext* ctx )
{

}

void SkewTool::onMouseDown( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		startDragPoint_ = dragPoint_ = *e->getPoint();
		startAngle_ = getAngleFromLine( dragPoint_, startDragPoint_ );
		
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();

		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		origin_ = startDragPoint_;

		bounds_ = shape->polygon_.getBounds();
	}
}

void SkewTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape* shape = doc->getSelectedShape();

		if ( NULL == shape ) {
			return;
		}

		skewShape( shape, *e->getPoint() );

		doc->updateAllViews();

		dragPoint_ = *e->getPoint();
	}
}

void SkewTool::onMouseUp( VCF::MouseEvent* e )
{

}

void SkewTool::skewShape( Shape* shape, VCF::Point pt )
{
	double sx1 = dragPoint_.x_;
	double sy1 = origin_.y_;

	double sx2 = origin_.x_;
	double sy2 = bounds_.bottom_;

	double skx = 360.0 - getAngleFromLine( Point(sx1,sy1), Point(sx2,sy2) );

	sx1 = pt.x_;
	sy1 = origin_.y_;

	sx2 = origin_.x_;
	sy2 = bounds_.bottom_;

	skx = (360.0 - getAngleFromLine( Point(sx1,sy1), Point(sx2,sy2) )) - skx;




	sx1 = bounds_.right_;
	sy1 = dragPoint_.y_;

	sx2 = origin_.x_;
	sy2 = origin_.y_;

	double sky = 360 - getAngleFromLine( Point(sx1,sy1), Point(sx2,sy2) );


	sx1 = bounds_.right_;
	sy1 = pt.y_;

	sx2 = origin_.x_;
	sy2 = origin_.y_;

	sky = (360 - getAngleFromLine( Point(sx1,sy1), Point(sx2,sy2) )) - sky;

	Matrix2D m1;
	m1.translate( -origin_.x_, -origin_.y_ );
	
	shape->polygon_.applyTransform( m1 );	
	
	Matrix2D m2;
	m2.shear( skx, sky );
	
	m1.translate( origin_.x_, origin_.y_ );
	
	shape->polygon_.applyTransform( *m2.multiply( &m2, &m1 ) );	
}



void RectangleTool::onMouseDown( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		end_ = start_ = *e->getPoint();

		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();

		ctx->setColor( Color::getColor("blue") );
		ctx->setXORModeOn( true );

		
		ctx->rectangle( &Rect(start_.x_,start_.y_,end_.x_,end_.y_) );
		ctx->strokePath();

		ctx->setXORModeOn( false );
	}
}

void RectangleTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();

		ctx->setColor( Color::getColor("blue") );
		ctx->setXORModeOn( true );
		
		Rect r(start_.x_,start_.y_,end_.x_,end_.y_);
		r.normalize();

		ctx->rectangle( &r );
		ctx->strokePath();

		end_ = *e->getPoint();

		r.setRect(start_.x_,start_.y_,end_.x_,end_.y_);
		r.normalize();

		ctx->rectangle( &r );
		ctx->strokePath();

		ctx->setXORModeOn( false );
	}
}

void RectangleTool::onMouseUp( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();

		ctx->setColor( Color::getColor("blue") );
		ctx->setXORModeOn( true );
		
		Rect r(start_.x_,start_.y_,end_.x_,end_.y_);
		r.normalize();

		ctx->rectangle( &r );
		ctx->strokePath();

		end_ = *e->getPoint();

		r.setRect(start_.x_,start_.y_,end_.x_,end_.y_);
		r.normalize();

		ctx->rectangle( &r );
		ctx->strokePath();

		ctx->rectangle( &r );
		ctx->strokePath();

		SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
		Shape shape;
		shape.polygon_.rectangle( r );
		doc->addShape( shape );

		ctx->setXORModeOn( false );
	}
}

void CurveTool::drawCurve( VCF::GraphicsContext* ctx )
{
	ctx->setXORModeOn( true );

	ctx->setColor( Color::getColor("blue") );

	ctx->curve( segment_.pt1.x_, segment_.pt1.y_,
					segment_.ctrl1.x_, segment_.ctrl1.y_,
					segment_.ctrl2.x_, segment_.ctrl2.y_,
					segment_.pt2.x_, segment_.pt2.y_ );

	ctx->strokePath();

	ctx->setColor( Color::getColor("black") );

	ctx->setXORModeOn( false );

	Rect r;
	r.setRect( segment_.pt2.x_, segment_.pt2.y_,
				segment_.pt2.x_, segment_.pt2.y_ );

	r.inflate( 2, 2 );

	ctx->rectangle( &r );
	ctx->fillPath();	

	ctx->setXORModeOn( true );

	ctx->circle( end_, 2 );	

	ctx->moveTo( end_ );
	ctx->lineTo( segment_.pt2 );

	ctx->lineTo( start_.x_  - (end_.x_ - start_.x_),
					start_.y_  - (end_.y_ - start_.y_) );

	ctx->circle( start_.x_  - (end_.x_ - start_.x_),
					start_.y_  - (end_.y_ - start_.y_), 2 );

	ctx->strokePath();

	ctx->setXORModeOn( false );

	//if ( CurveTool::sNextPoint == state_  ) {
		ctx->moveTo( segment_.pt1 );
		ctx->lineTo( segment_.ctrl1 );

		ctx->circle( segment_.ctrl1, 2 );		
//	}

	ctx->strokePath();


}	

void CurveTool::onMouseDown( VCF::MouseEvent* e )
{
	StringUtils::traceWithArgs( "CurveTool::onMouseDown, state: %d\n", state_ );
	if ( e->hasLeftButton() ) {		

		switch ( state_ ) {
			case CurveTool::sFirstPoint : {
				segments_.clear();

				end_ = start_ = *e->getPoint();

				segment_.pt1 = segment_.pt2 = segment_.ctrl1 = segment_.ctrl2 = start_;
			}
			break;

			case CurveTool::sNextPoint : {
				start_ = *e->getPoint();

				segment_.pt1 = segment_.pt2;
				segment_.ctrl1 = end_;
				segment_.pt2 = segment_.ctrl2 = start_;

				end_ = start_;

				if ( overFirstPoint( start_ ) ) {
					segments_.push_back( segment_ );
					finishCurve();
				}
			}
			break;
		}

		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();

		

		drawCurve( ctx );

		

		paintSegments( ctx );

		

		
		

		state_ = CurveTool::sNextPoint;
		
	}
}

void CurveTool::onMouseMove( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();
		
		paintSegments( ctx );
		

		
		drawCurve( ctx );

		end_ = *e->getPoint();

		switch ( state_ ) {
			case CurveTool::sFirstPoint : {
				
			}
			break;

			case CurveTool::sNextPoint : {
				segment_.ctrl2.x_ = start_.x_  - (end_.x_ - start_.x_);
				segment_.ctrl2.y_ = start_.y_  - (end_.y_ - start_.y_);


				
			}
			break;
		}		

		
		drawCurve( ctx );

		
	}
}

void CurveTool::onMouseUp( VCF::MouseEvent* e )
{
	StringUtils::traceWithArgs( "CurveTool::onMouseUp, state: %d\n", state_ );

	if ( e->hasLeftButton() ) {
		Control* c = (Control*)e->getSource();
		GraphicsContext* ctx = c->getContext();		
		
		drawCurve( ctx );

		end_ = *e->getPoint();		
		
		if ( (!segments_.empty()) && ( CurveTool::sNextPoint == state_) ) {
			segment_.ctrl2.x_ = start_.x_  - (end_.x_ - start_.x_);
			segment_.ctrl2.y_ = start_.y_  - (end_.y_ - start_.y_);
		}
				
		drawCurve( ctx );
		
		segments_.push_back( segment_ );

		paintSegments( ctx );
	}
	
}

void CurveTool::finishCurve()
{
	state_ = CurveTool::sFirstPoint;
	

	SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
	Shape shape;
	std::vector<Segment>::iterator it = segments_.begin();
	while ( it != segments_.end() ) {
		Segment& segment = *it;
		shape.polygon_.curve( segment.pt1.x_, segment.pt1.y_,
							segment.ctrl1.x_, segment.ctrl1.y_,
							segment.ctrl2.x_, segment.ctrl2.y_,
							segment.pt2.x_, segment.pt2.y_ );
		it++;
	}

	if ( overFirstPoint( start_ ) ) {
		shape.polygon_.close();
	}
	doc->addShape( shape );

	segments_.clear();
}

void CurveTool::onDblClick( VCF::MouseEvent* e )
{
	StringUtils::traceWithArgs( "CurveTool::onDblClick, state: %d\n", state_ );

	finishCurve();
}

void CurveTool::paintState( VCF::GraphicsContext* ctx )
{
	StringUtils::trace( "CurveTool::paintState\n" );
	//paintSegments( ctx );
}

void CurveTool::paintSegments( VCF::GraphicsContext* ctx )
{
	
	std::vector<Segment>::iterator it = segments_.begin();
	while ( it != segments_.end() ) {
		Segment& segment = *it;
		
		if ( segment != segment_ ) {
			ctx->curve( segment.pt1.x_, segment.pt1.y_,
							segment.ctrl1.x_, segment.ctrl1.y_,
							segment.ctrl2.x_, segment.ctrl2.y_,
							segment.pt2.x_, segment.pt2.y_ );
		}

		it ++;
	}

	ctx->strokePath();
}


bool CurveTool::overFirstPoint( VCF::Point& pt )
{
	bool result = false;
	std::vector<Segment>::iterator it = segments_.begin();
	while ( it != segments_.end() ) {
		Segment& segment = *it;
		if ( pt == segment.pt1 ) {
			result = true;
			break;
		}
		it++;
	}

	return result;
}

void CurveTool::reset()
{
	state_ = CurveTool::sFirstPoint;

	segments_.clear();
}


void ImageTool::onMouseDown( VCF::MouseEvent* e )
{
	if ( e->hasLeftButton() ) {
		CommonFileOpen openDlg;
		if ( openDlg.execute() ) {
			FilePath fp = openDlg.getFileName();
			
			Image* img = GraphicsToolkit::createImage( fp );

	
			if ( NULL != img ) {
				Rect imageRect;
				imageRect.setRect( e->getPoint()->x_, e->getPoint()->y_,
									e->getPoint()->x_ + img->getWidth(),
									e->getPoint()->y_ + img->getHeight());


				SketchDocument* doc = (SketchDocument*) DocumentManager::getDocumentManager()->getCurrentDocument();
				Shape shape;
				shape.polygon_.rectangle( imageRect );
				shape.image_ = img;
				shape.image_->getImageBits()->attachRenderBuffer( img->getWidth(), img->getHeight() );
				doc->addShape( shape );			
			}
			
		}
	}
}

void ImageTool::onMouseMove( VCF::MouseEvent* e )
{

}

void ImageTool::onMouseUp( VCF::MouseEvent* e )
{

}

void ImageTool::paintState( VCF::GraphicsContext* ctx )
{
	
}



