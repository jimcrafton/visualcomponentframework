#ifndef SCRIBBLECONTROLLER_H__
#define SCRIBBLECONTROLLER_H__

using VCF::Object;
using VCF::Component;
using VCF::Event;
using VCF::MouseEvent;
using VCF::ClassProcedure1;
using VCF::CallBack;
using VCF::Path;
using VCF::BezierCurve;
using VCF::VariantData;
using VCF::SmartPtr;
using VCF::Dialog;
using VCF::CheckBoxControl;
using VCF::TextControl;
using VCF::CommonColorDialog;
using VCF::Frame;
using VCF::UIToolkit;
using VCF::KeyboardEvent;
using VCF::vkDelete;
using VCF::maxVal;
using VCF::Component;
using VCF::ActionEvent;
using VCF::ToolbarItem;
using VCF::DragSource;
using VCF::daCopy;
using VCF::daMove;
using VCF::daNone;
using VCF::DataObject;
using VCF::BasicOutputStream;
using VCF::MIMEType;
using VCF::BinaryPersistable;
using VCF::Document;
using VCF::DropTargetEvent;


double getAngleFromLine( Point p1, Point p2 )
{
	return  VCF::Math::radiansToDegrees( atan2( p1.y_-p2.y_, p1.x_-p2.x_ ) );
}

class ScribbleController;

class Tool {
public:
	Tool():controller(NULL){}
	virtual ~Tool(){}

	virtual void mouseDown( MouseEvent* e ) {}
	virtual void mouseMove( MouseEvent* e ) {}
	virtual void mouseUp( MouseEvent* e ) {}

	virtual void keyDown( KeyboardEvent* e ) {}
	virtual void keyUp( KeyboardEvent* e ) {}

	ScribbleController* controller;
};




class ShapeEditDialog : public Dialog {
public:

	Color strokeColor;
	Color fillColor;
	bool filled;
	double width;

	ShapeEditDialog(){
		addCallback( new ClassProcedure1<Event*,ShapeEditDialog>(this, &ShapeEditDialog::onDoColor), "ShapeEditDialog::onDoColor" );

		FrameClose += new ClassProcedure1<Event*,ShapeEditDialog>(this, &ShapeEditDialog::onClose,"onClose");
	}


	void initFromShape( ScribbleShape* shape ) {
		Control* c = (Control*)findComponent("fillColor",true);
		c->setColor( shape->getFill() );

		c = (Control*)findComponent("strokeColor",true);
		c->setColor( shape->getStroke() );

		CheckBoxControl* cb = (CheckBoxControl*)findComponent("filled",true);
		cb->setChecked( shape->getFilled() );
		
		TextControl* tc = (TextControl*)findComponent("strokeWidth",true);
		tc->setText( StringUtils::toString(shape->getStrokeWidth()) );

		tc = (TextControl*)findComponent("strokeOpacity",true);
		tc->setText( StringUtils::toString(shape->getStroke()->getAlpha()) );

		tc = (TextControl*)findComponent("fillOpacity",true);
		tc->setText( StringUtils::toString(shape->getFill()->getAlpha()) );
	}
	

	void onClose( Event* ) {
		Control* c = (Control*)findComponent("fillColor",true);
		fillColor = *c->getColor();

		c = (Control*)findComponent("strokeColor",true);
		strokeColor = *c->getColor();

		CheckBoxControl* cb = (CheckBoxControl*)findComponent("filled",true);
		filled = cb->isChecked();

		TextControl* tc = (TextControl*)findComponent("strokeWidth",true);
		width = StringUtils::fromStringAsDouble(tc->getText());

		tc = (TextControl*)findComponent("strokeOpacity",true);

		strokeColor.setAlpha( StringUtils::fromStringAsDouble(tc->getText()) );

		tc = (TextControl*)findComponent("fillOpacity",true);
		fillColor.setAlpha( StringUtils::fromStringAsDouble(tc->getText()) );
	}

	void onDoColor(Event* e) {
		Control* ctrl = (Control*)e->getSource();
		CommonColorDialog colorDlg;
		colorDlg.setSelectedColor( ctrl->getColor() );
		if ( colorDlg.execute() ) {
			
			ctrl->setColor( colorDlg.getSelectedColor() );
		}
	}
};



class ScribbleController : public Component {
public:
	ScribbleController();
	virtual ~ScribbleController();

	void setControl( Control* val ) {
		modelControl = val;
	}

	void setModel( ScribbleModel* scribbleModel ) {
		setCurrentTool(0);
		
		CallBack* ev = getCallback( "ScribbleController::onModelChanged" );


		if ( NULL != model ) {			
			model->ModelChanged -= ev;			
		}

		model = scribbleModel;

		if ( NULL != model ) {
			model->ModelChanged += ev;


			Scrollable* scrollable = modelControl->getScrollable();


			if ( NULL != scrollable ) {
				Rect bounds = model->getMaxBounds();
				bounds.inflate( 0,0,20,20);
				scrollable->setVirtualViewHeight( bounds.getHeight() );
				scrollable->setVirtualViewWidth( bounds.getWidth() );
			}
		}
	}

	void onModelChanged( Event* e ) {
		Scrollable* scrollable = modelControl->getScrollable();
		
		
		if ( NULL != scrollable ) {
			Rect bounds = model->getMaxBounds();
			bounds.inflate( 0,0,20,20);
			scrollable->setVirtualViewHeight( bounds.getHeight() );
			scrollable->setVirtualViewWidth( bounds.getWidth() );
		}
	}

	void onKeyDown( KeyboardEvent* e ) {
		if ( NULL != currentTool ) {
			currentTool->keyDown(e);
		}
	}

	void onMouseMove( MouseEvent* e ) {
		if ( NULL != currentTool ) {
			currentTool->mouseMove(e);
		}		
	}

	void onMouseDown( MouseEvent* e ) {
		if ( NULL != currentTool ) {
			currentTool->mouseDown(e);
		}		
	}

	void onMouseUp( MouseEvent* e ) {

		if ( NULL != currentTool ) {
			currentTool->mouseUp(e);
		}		
	}

	void onMouseDblClick( MouseEvent* e ) {
		ScribbleShape* shape = hitTest( *e->getPoint() );
		model->setActiveShape( shape );
		editShape( shape );
	}

	void deleteShape( ScribbleShape* shape ) {
		VariantData v;
		v = shape;
		
		uint32 index = model->getIndexOf( v );
		model->remove( index );
	}

	void deleteCurrentShape() {
		if ( NULL != model->getActiveShape() ) {			
			deleteShape( model->getActiveShape() );
		}
	}

	void editShape( ScribbleShape* shape ) {
		if ( NULL != shape ) { 			
			typedef VCF::SmartPtr<ShapeEditDialog> ShapeEditDialogPtr;
			
			ShapeEditDialogPtr::Shared editDlg = ShapeEditDialogPtr::New( (ShapeEditDialog*)Frame::createDialog( classid(ShapeEditDialog) ) );
			editDlg->initFromShape(shape);

			if ( editDlg->showModal() == UIToolkit::mrOK ) {
				model->modifyAttributes( shape, editDlg->filled, editDlg->fillColor, editDlg->strokeColor, editDlg->width );				
			}
		}
	}

	void onChangeTool( Event* e ) {
		Component* component = (Component*)e->getSource();
		this->setCurrentTool( component->getTag() );
	}

	void onUpdateChangeTool( ActionEvent* e ) {
		Component* component = (Component*)e->getSource();

		std::vector<Tool*>::iterator found = std::find( tools.begin(), tools.end(), currentTool );
		if ( found != tools.end() ) {
			e->setChecked( component->getTag() == (found - tools.begin()) );

			if ( component->getTag() == (found - tools.begin()) ) {
				e->setState( e->getState() | ToolbarItem::tisPressed );
			}
			else {
				e->setState( e->getState() & ~ToolbarItem::tisPressed );
			}
		}
		else {
			e->setChecked( false );
			e->setState( e->getState() & ~ToolbarItem::tisPressed );
		}
		


		
		
	}

	Rect getBounds( ScribbleShape* shape ) {
		Rect result;

		BezierCurve curve;
		VCF::Ellipse ellipse;
		Path* p = NULL;

		switch ( shape->type ) {
			case ScribbleShape::stLine : {
				Point pt = shape->points[0];
				curve.moveTo( pt.x_, pt.y_ );
				pt = shape->points[1];
				curve.lineTo( pt.x_, pt.y_ );
				p = &curve;
			}
			break;

			case ScribbleShape::stRect : {
				Point pt1 = shape->points[0];
				Point pt2 = shape->points[1];
				Rect r(pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
				curve.rectangle( r );
				p = &curve;
			}
			break;

			case ScribbleShape::stEllipse : {
				Point pt1 = shape->points[0];
				Point pt2 = shape->points[1];
				Rect r(pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
				ellipse.ellipse( r );
				p = &ellipse;
			}
			break;

			case ScribbleShape::stPolygon : {
				std::vector<Point>::const_iterator it = shape->points.begin();			
				while ( it != shape->points.end() ) {
					const Point& pt = *it;
					if ( it == shape->points.begin() ) {
						curve.moveTo( pt.x_, pt.y_ );
					}
					else {
						curve.lineTo( pt.x_, pt.y_ );
					}
					++it;
				}
				p = &curve;
			}
			break;

			case ScribbleShape::stFreehand : {
				std::vector<Point>::const_iterator it = shape->points.begin();			
				while ( it != shape->points.end() ) {
					const Point& pt = *it;
					if ( it == shape->points.begin() ) {
						curve.moveTo( pt.x_, pt.y_ );
					}
					else {
						curve.lineTo( pt.x_, pt.y_ );
					}
					++it;
				}
				p = &curve;
			}
			break;
		}

		if ( NULL != p ) {
			p->applyTransform( shape->mat );
			result = p->getBounds();
		}
		return result;
	}

	ScribbleShape* hitTest( const Point& point ) {
		ScribbleShape* result = NULL;

		BezierCurve curve;
		VCF::Ellipse ellipse;
		Path* p = NULL;
		size_t count = model->getCount();		

		for (int i=count-1;i>=0;i-- ) {
			ScribbleShape* shape = model->getShape(i);	
			curve.clear();
			

			switch ( shape->type ) {
				case ScribbleShape::stLine : {
					Point pt = shape->points[0];
					curve.moveTo( pt.x_, pt.y_ );
					pt = shape->points[1];
					curve.lineTo( pt.x_, pt.y_ );
					p = &curve;
				}
				break;

				case ScribbleShape::stRect : {
					Point pt1 = shape->points[0];
					Point pt2 = shape->points[1];
					Rect r(pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
					curve.rectangle( r );
					p = &curve;
				}
				break;

				case ScribbleShape::stEllipse : {
					Point pt1 = shape->points[0];
					Point pt2 = shape->points[1];
					Rect r(pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
					ellipse.ellipse( r );
					p = &ellipse;
				}
				break;

				case ScribbleShape::stPolygon : {
					std::vector<Point>::const_iterator it = shape->points.begin();			
					while ( it != shape->points.end() ) {
						const Point& pt = *it;
						if ( it == shape->points.begin() ) {
							curve.moveTo( pt.x_, pt.y_ );
						}
						else {
							curve.lineTo( pt.x_, pt.y_ );
						}
						++it;
					}
					p = &curve;
				}
				break;

				case ScribbleShape::stFreehand : {
					std::vector<Point>::const_iterator it = shape->points.begin();			
					while ( it != shape->points.end() ) {
						const Point& pt = *it;
						if ( it == shape->points.begin() ) {
							curve.moveTo( pt.x_, pt.y_ );
						}
						else {
							curve.lineTo( pt.x_, pt.y_ );
						}
						++it;
					}
					p = &curve;
				}
				break;
			}

			
			if ( NULL != p ) {
				p->applyTransform( shape->mat );
				if ( shape->filled && shape->type != ScribbleShape::stLine ) {
					if ( p->contains( point ) ) {
						result = shape;
						break;
					}
				}
				else {
					if ( p->intersects( point ) ) {
						result = shape;
						break;
					}
				}
			}
		}

		return result;
	}

	void setCurrentTool( const size_t index ) {
		if ( index < tools.size() ) {
			currentTool = tools[ index ];
			currentTool->controller = this;
		}
		else {
			currentTool = NULL;
		}
	}


	void onContentPanelEntered( DropTargetEvent* e ) {
		e->setActionType( daNone );	
		ScribbleView* view = (ScribbleView*)modelControl->getView();
		view->dragShape = NULL;


		DataObject* dataObj = e->getDataObject();
		Document* doc = DocumentManager::getDocumentManager()->getCurrentDocument();
		Enumerator<MIMEType>* clipboardFmts = doc->getSupportedClipboardFormats();
		while ( clipboardFmts->hasMoreElements() ) {
			MIMEType m =  clipboardFmts->nextElement();
			if ( dataObj->isTypeSupported( m ) ) {
				e->setActionType( daMove );	
				view->dragShape = dragShape;
				break;
			}
		}
	}

	void onContentPanelDragging( DropTargetEvent* e ) {
		

		if ( NULL != dragShape && e->getAction() != daNone ) {
			Rect r = getBounds( dragShape );
			
			Point pt = e->getDropPoint();
			Matrix2D m = dragShape->mat * Matrix2D::translation( pt.x_ - (r.left_ + r.getWidth()/2.0), 
														pt.y_ - (r.top_ + r.getHeight()/2.0));

			model->setShapeMatrix( dragShape, m );
		}
	}

	void onContentPanelDropped( DropTargetEvent* e ) {
		ScribbleView* view = (ScribbleView*)modelControl->getView();
		view->dragShape = NULL;
		DataObject* dataObj = e->getDataObject();
		Document* doc = DocumentManager::getDocumentManager()->getCurrentDocument();
		doc->paste( dataObj );
		Point pt = e->getDropPoint();

		ScribbleShape* shape = model->getShape( model->getCount()-1 );

		Rect r = getBounds( shape );

		Matrix2D m = shape->mat * Matrix2D::translation( pt.x_ - (r.left_ + r.getWidth()/2.0), 
														pt.y_ - (r.top_ + r.getHeight()/2.0));
		model->setShapeMatrix( shape, m );
	}


	Control* modelControl;
	ScribbleModel* model;
	ScribbleShape* activeShape;	
	ScribbleShape* dragShape;

	std::vector<Tool*> tools;
	Tool* currentTool;
	

};






class DrawRectTool : public Tool {
	Point anchorPt;

	virtual void mouseDown( MouseEvent* e ) {
		
		if ( e->hasLeftButton() ) {
			anchorPt = *e->getPoint();

			controller->model->addRect( anchorPt, anchorPt );			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setRect( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setRect( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}
};



class DrawLineTool : public Tool {
	Point anchorPt;

	virtual void mouseDown( MouseEvent* e ) {
		
		if ( e->hasLeftButton() ) {
			anchorPt = *e->getPoint();

			controller->model->addLine( anchorPt, anchorPt );			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setLine( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setLine( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}
};



class DrawEllipseTool : public Tool {
	Point anchorPt;

	virtual void mouseDown( MouseEvent* e ) {
		
		if ( e->hasLeftButton() ) {
			anchorPt = *e->getPoint();

			controller->model->addEllipse( anchorPt, anchorPt );			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setEllipse( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {

			controller->model->setEllipse( controller->model->getCount() - 1, anchorPt, *e->getPoint() );
		}
	}
};




class DrawPolygonTool : public Tool {	

	virtual void mouseDown( MouseEvent* e ) {
		
		if ( e->hasLeftButton() ) {			
			std::vector<Point> pts(1);
			pts[0] = *e->getPoint();
			controller->model->addPolygon( pts );			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			controller->model->addPolygonPt( controller->model->getCount() - 1, *e->getPoint() );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			controller->model->addPolygonPt( controller->model->getCount() - 1, *e->getPoint() );
		}
	}
};



class DrawFreehandTool : public Tool {	

	virtual void mouseDown( MouseEvent* e ) {
		
		if ( e->hasLeftButton() ) {			
			std::vector<Point> pts(1);
			pts[0] = *e->getPoint();
			controller->model->addFreehand( pts );			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			controller->model->addPolygonPt( controller->model->getCount() - 1, *e->getPoint() );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			controller->model->addPolygonPt( controller->model->getCount() - 1, *e->getPoint() );
		}
	}
};


class SelectTool : public Tool {
public:
	Point currentDragPt;
	Point scalePt;
	Point rotatePt;
	Rect originalScaleBounds;
	Matrix2D originalMat;


	SelectTool() {}


	void beginDrag( Point pt, ScribbleShape* shape ) {
		DragSource src;
		src.setActionType( daMove );

		Document* doc = DocumentManager::getDocumentManager()->getCurrentDocument();
		DataObject* shapeData = doc->copy();
		controller->dragShape = shape;

		Matrix2D oldMat = shape->mat;

		src.startDragDrop( shapeData );
		switch ( src.getActionType() ) {
			case daNone : {

			}
			break;

			case daCopy : {
				 controller->model->setShapeMatrix( shape, originalMat );
			}
			break;

			case daMove : {
				controller->deleteShape( shape );
			}
			break;
		}



		delete shapeData;
		controller->dragShape = NULL;
		ScribbleView* view = (ScribbleView*)controller->modelControl->getView();
		view->dragShape = NULL;
		controller->modelControl->repaint();
	}


	virtual void mouseDown( MouseEvent* e ) {
		ScribbleShape* shape = controller->hitTest( *e->getPoint() );
		controller->model->setActiveShape( shape );

		controller->modelControl->setFocused();

		controller->modelControl->keepMouseEvents();
		
		if ( e->hasLeftButton() && NULL != shape ) {
			originalMat = shape->mat;
			if ( e->hasShiftKey() ) {
				scalePt = *e->getPoint();
				originalScaleBounds = controller->getBounds( shape );
			}
			else if ( e->hasControlKey() ) {
				rotatePt = *e->getPoint();
				originalScaleBounds = controller->getBounds( shape );
				currentDragPt = *e->getPoint();
			}
			else {
				currentDragPt = *e->getPoint();
			}
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->getButtonMask() == 0 ) {
			ScribbleShape* tmp = controller->hitTest( *e->getPoint() );
			if ( tmp != controller->activeShape  ) {
				
				controller->activeShape = tmp;
				ScribbleView* view = (ScribbleView*)controller->modelControl->getView();
				view->hotShape = controller->activeShape;
				controller->modelControl->repaint();


				if ( NULL != controller->activeShape ) {
					
					VariantData v;
					v = controller->activeShape;
					uint32 index = controller->model->getIndexOf( v );
					
					controller->modelControl->setToolTipText( String("Shape #") + (index+1)  );
				}
				else {
					controller->modelControl->setToolTipText( "" );
				}
			}
		}


		if ( e->hasLeftButton() ) {

			ScribbleShape* shape = controller->model->getActiveShape();
			
			if ( e->hasShiftKey() ) {				
				if ( NULL != shape ) {	
					Rect tmp = originalScaleBounds;
					tmp.inflate( (e->getPoint()->x_ - scalePt.x_), 
						(e->getPoint()->y_ - scalePt.y_));
					tmp.normalize();
					
					Rect tmp2 = controller->getBounds( shape );
					tmp2.normalize();

					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::scaling( maxVal(0.001,tmp.getWidth() / tmp2.getWidth()),
														maxVal(0.001,tmp.getHeight() / tmp2.getHeight()) );
					m *= Matrix2D::translation( cx, cy );

					controller->model->setShapeMatrix( shape, m );
				}
			}
			else if ( e->hasControlKey() ) {
				if ( NULL != shape ) {	
					double a1 = getAngleFromLine( rotatePt, currentDragPt );
					double a2 = getAngleFromLine( rotatePt, *e->getPoint() );
					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::rotation( a2-a1 );
					m *= Matrix2D::translation( cx, cy );

					controller->model->setShapeMatrix( shape, m );

					currentDragPt = *e->getPoint();
				}
			}
			else {
				Scrollable* scrollable = controller->modelControl->getScrollable();

				Rect r = controller->modelControl->getClientBounds();

				if ( (NULL != shape) && (!r.containsPt( e->getPoint() )) ) {
					controller->modelControl->releaseMouseEvents();

					beginDrag(  *e->getPoint(), shape );
				}
				else if ( NULL != shape ) {	
					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( e->getPoint()->x_ - currentDragPt.x_,
						e->getPoint()->y_ - currentDragPt.y_ );
					controller->model->setShapeMatrix( shape, m );					
				}			

				currentDragPt = *e->getPoint();
			}			
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		controller->modelControl->releaseMouseEvents();

		if ( e->hasLeftButton() ) {
			ScribbleShape* shape = controller->model->getActiveShape();
			if ( e->hasShiftKey() ) {
				if ( NULL != shape ) {	
					Rect tmp = originalScaleBounds;
					tmp.inflate( (e->getPoint()->x_ - scalePt.x_), 
						(e->getPoint()->y_ - scalePt.y_));
					tmp.normalize();
					
					Rect tmp2 = controller->getBounds( shape );
					tmp2.normalize();

					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::scaling( tmp.getWidth() / tmp2.getWidth(),
														tmp.getHeight() / tmp2.getHeight() );
					m *= Matrix2D::translation( cx, cy );

					shape->mat = originalMat;
					controller->model->setShapeMatrix( shape, m, true );
				}
			}
			else if ( e->hasControlKey() ) {
				if ( NULL != shape ) {	
					double a1 = getAngleFromLine( rotatePt, currentDragPt );
					double a2 = getAngleFromLine( rotatePt, *e->getPoint() );
					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();

					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::rotation( a2-a1 );
					m *= Matrix2D::translation( cx, cy );

					shape->mat = originalMat;
					controller->model->setShapeMatrix( shape, m, true );

					currentDragPt = *e->getPoint();
				}
			}
			else {
				if ( NULL != shape ) {	
					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( e->getPoint()->x_ - currentDragPt.x_,
													e->getPoint()->y_ - currentDragPt.y_ );

					shape->mat = originalMat;
					controller->model->setShapeMatrix( shape, m, true );
				}

				currentDragPt = *e->getPoint();
			}			
		}
	}

	
	virtual void keyDown( KeyboardEvent* e ) {
		if ( vkDelete == e->virtualKeyCode ) {
			controller->deleteCurrentShape();
		}
	}
};





ScribbleController::ScribbleController(): 
	model(NULL), modelControl(NULL),activeShape(NULL),currentTool(NULL),dragShape(NULL)
{
	addCallback( new ClassProcedure1<Event*,ScribbleController>(this, &ScribbleController::onModelChanged), "ScribbleController::onModelChanged" );
	addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseMove), "ScribbleController::onMouseMove" );
	addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseDown), "ScribbleController::onMouseDown" );
	addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseUp), "ScribbleController::onMouseUp" );
	addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseDblClick), "ScribbleController::onMouseDblClick" );
	addCallback( new ClassProcedure1<KeyboardEvent*,ScribbleController>(this, &ScribbleController::onKeyDown), "ScribbleController::onKeyDown" );

	addCallback( new ClassProcedure1<Event*,ScribbleController>(this, &ScribbleController::onChangeTool), "ScribbleController::onChangeTool" );
	addCallback( new ClassProcedure1<ActionEvent*,ScribbleController>(this, &ScribbleController::onUpdateChangeTool), "ScribbleController::onUpdateChangeTool" );
	
	addCallback( new ClassProcedure1<DropTargetEvent*,ScribbleController>(this, &ScribbleController::onContentPanelEntered), "ScribbleController::onContentPanelEntered" );
	addCallback( new ClassProcedure1<DropTargetEvent*,ScribbleController>(this, &ScribbleController::onContentPanelDragging), "ScribbleController::onContentPanelDragging" );
	addCallback( new ClassProcedure1<DropTargetEvent*,ScribbleController>(this, &ScribbleController::onContentPanelDropped), "ScribbleController::onContentPanelDropped" );
	

	tools.push_back( new SelectTool() );
	tools.push_back( new DrawRectTool() );
	tools.push_back( new DrawLineTool() );
	tools.push_back( new DrawEllipseTool() );
	tools.push_back( new DrawPolygonTool() );
	tools.push_back( new DrawFreehandTool() );
	
	
	

	setCurrentTool(0);
}

ScribbleController::~ScribbleController()
{
	for (size_t i=0;i<tools.size();i++ ) {
		delete tools[i];
	}
}

#endif //SCRIBBLECONTROLLER_H__
