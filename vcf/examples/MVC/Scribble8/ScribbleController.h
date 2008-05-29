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

double getAngleFromLine( Point p1, Point p2 )
{
	return  VCF::Math::radiansToDegrees( atan2( p1.y_-p2.y_, p1.x_-p2.x_ ) );
}



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
	ScribbleController(): model(NULL), modelControl(NULL),activeShape(NULL) {
		addCallback( new ClassProcedure1<Event*,ScribbleController>(this, &ScribbleController::onModelChanged), "ScribbleController::onModelChanged" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseMove), "ScribbleController::onMouseMove" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseDown), "ScribbleController::onMouseDown" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseUp), "ScribbleController::onMouseUp" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseDblClick), "ScribbleController::onMouseDblClick" );
		addCallback( new ClassProcedure1<KeyboardEvent*,ScribbleController>(this, &ScribbleController::onKeyDown), "ScribbleController::onKeyDown" );
	}

	void setControl( Control* val ) {
		modelControl = val;
	}

	void setModel( ScribbleModel* scribbleModel ) {
		
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
		if ( e->getVirtualCode() == vkDelete ) {
			deleteCurrentShape();
		}
	}

	void onMouseMove( MouseEvent* e ) {
		if ( e->getButtonMask() == 0 ) {
			ScribbleShape* tmp = hitTest( *e->getPoint() );
			if ( tmp != activeShape  ) {
				model->setActiveShape( tmp );
				activeShape = tmp;
				
				if ( NULL != activeShape ) {
					
					VariantData v;
					v = activeShape;
					uint32 index = model->getIndexOf( v );
					
					modelControl->setToolTipText( String("Shape #") + (index+1)  );
				}
				else {
					modelControl->setToolTipText( "" );
				}
			}
		}


		if ( e->hasLeftButton() ) {
			ScribbleShape* shape = model->getActiveShape();
			if ( e->hasShiftKey() ) {				
				if ( NULL != shape ) {	
					Rect tmp = originalScaleBounds;
					tmp.inflate( (e->getPoint()->x_ - scalePt.x_), 
						(e->getPoint()->y_ - scalePt.y_));
					tmp.normalize();
					
					Rect tmp2 = getBounds( shape );
					tmp2.normalize();

					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::scaling( maxVal(0.001,tmp.getWidth() / tmp2.getWidth()),
														maxVal(0.001,tmp.getHeight() / tmp2.getHeight()) );
					m *= Matrix2D::translation( cx, cy );

					model->setShapeMatrix( shape, m );
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

					model->setShapeMatrix( shape, m );

					currentDragPt = *e->getPoint();
				}
			}
			else {
				if ( NULL != shape ) {	
					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( e->getPoint()->x_ - currentDragPt.x_,
													e->getPoint()->y_ - currentDragPt.y_ );
					model->setShapeMatrix( shape, m );
				}

				currentDragPt = *e->getPoint();
			}			
		}
	}

	void onMouseDown( MouseEvent* e ) {
		ScribbleShape* shape = hitTest( *e->getPoint() );
		model->setActiveShape( shape );

		modelControl->setFocused();

		modelControl->keepMouseEvents();

		if ( e->hasLeftButton() && NULL != shape ) {
			if ( e->hasShiftKey() ) {
				scalePt = *e->getPoint();
				originalScaleBounds = getBounds( shape );
			}
			else if ( e->hasControlKey() ) {
				rotatePt = *e->getPoint();
				originalScaleBounds = getBounds( shape );
				currentDragPt = *e->getPoint();
			}
			else {
				currentDragPt = *e->getPoint();
			}
		}
	}

	void onMouseUp( MouseEvent* e ) {
		modelControl->releaseMouseEvents();

		if ( e->hasLeftButton() ) {
			ScribbleShape* shape = model->getActiveShape();
			if ( e->hasShiftKey() ) {
				if ( NULL != shape ) {	
					Rect tmp = originalScaleBounds;
					tmp.inflate( (e->getPoint()->x_ - scalePt.x_), 
						(e->getPoint()->y_ - scalePt.y_));
					tmp.normalize();
					
					Rect tmp2 = getBounds( shape );
					tmp2.normalize();

					double cx, cy;
					cx = originalScaleBounds.left_ + originalScaleBounds.getWidth()/2.0;
					cy = originalScaleBounds.top_ + originalScaleBounds.getHeight()/2.0;

					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( -cx, -cy );
					m *= Matrix2D::scaling( tmp.getWidth() / tmp2.getWidth(),
														tmp.getHeight() / tmp2.getHeight() );
					m *= Matrix2D::translation( cx, cy );

					model->setShapeMatrix( shape, m );
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

					model->setShapeMatrix( shape, m );

					currentDragPt = *e->getPoint();
				}
			}
			else {
				if ( NULL != shape ) {	
					Matrix2D m = shape->getMatrix();
					m *= Matrix2D::translation( e->getPoint()->x_ - currentDragPt.x_,
													e->getPoint()->y_ - currentDragPt.y_ );
					model->setShapeMatrix( shape, m );
				}

				currentDragPt = *e->getPoint();
			}			
		}
	}

	void onMouseDblClick( MouseEvent* e ) {
		ScribbleShape* shape = hitTest( *e->getPoint() );
		model->setActiveShape( shape );
		editShape( shape );
	}

	void deleteCurrentShape() {
		if ( NULL != model->getActiveShape() ) {
			VariantData v;
			v = model->getActiveShape();
			
			uint32 index = model->getIndexOf( v );
			model->remove( index );
		}
	}

	void editShape( ScribbleShape* shape ) {
		if ( NULL != shape ) { 			
			typedef VCF::SmartPtr<ShapeEditDialog> ShapeEditDialogPtr;
			
			ShapeEditDialogPtr::Shared editDlg = ShapeEditDialogPtr::New( (ShapeEditDialog*)Frame::createDialog( classid(ShapeEditDialog) ) );
			editDlg->initFromShape(shape);

			if ( editDlg->showModal() == UIToolkit::mrOK ) {
				shape->setFill( &editDlg->fillColor );
				shape->setStroke( &editDlg->strokeColor );

				shape->setFilled( editDlg->filled );

				shape->setStrokeWidth( editDlg->width );

				model->updateAllViews();
				
			}
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

	Control* modelControl;
	ScribbleModel* model;
	ScribbleShape* activeShape;
	Point currentDragPt;
	Point scalePt;
	Point rotatePt;
	Rect originalScaleBounds;

};

#endif //SCRIBBLECONTROLLER_H__
