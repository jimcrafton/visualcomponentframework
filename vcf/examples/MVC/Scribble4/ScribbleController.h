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

class ScribbleController : public Component {
public:
	ScribbleController(): model(NULL), modelControl(NULL),activeShape(NULL) {
		addCallback( new ClassProcedure1<Event*,ScribbleController>(this, &ScribbleController::onModelChanged), "ScribbleController::onModelChanged" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseMove), "ScribbleController::onMouseMove" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseDown), "ScribbleController::onMouseDown" );
		addCallback( new ClassProcedure1<MouseEvent*,ScribbleController>(this, &ScribbleController::onMouseUp), "ScribbleController::onMouseUp" );
	}

	void setControl( Control* val ) {
		if ( NULL != modelControl ) {

		}

		modelControl = val;

		if ( NULL != modelControl ) {
			modelControl->MouseMove += getCallback( "ScribbleController::onMouseMove" );
			modelControl->MouseDown += getCallback( "ScribbleController::onMouseDown" );
			modelControl->MouseUp += getCallback( "ScribbleController::onMouseUp" );
		}
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

	void onMouseMove( MouseEvent* e ) {
		const ScribbleShape* tmp = hitTest( *e->getPoint() );
		if ( tmp != activeShape ) {
			model->setActiveShape( tmp );
			activeShape = tmp;

			if ( NULL != activeShape ) {
				
				VariantData v;
				v = (Object*)activeShape;
				uint32 index = model->getIndexOf( v );
				
				modelControl->setToolTipText( String("Shape #") + (index+1)  );
			}
			else {
				modelControl->setToolTipText( "" );
			}
		}
	}

	void onMouseDown( MouseEvent* e ) {
		const ScribbleShape* shape = hitTest( *e->getPoint() );
		model->setActiveShape( shape );
	}

	void onMouseUp( MouseEvent* e ) {
		
	}


	const ScribbleShape* hitTest( const Point& point ) {
		const ScribbleShape* result = NULL;

		BezierCurve curve;
		VCF::Ellipse ellipse;
		Path* p = NULL;
		size_t count = model->getCount();
		for (int i=count-1;i>=0;i-- ) {
			const ScribbleShape* shape = model->getShape(i);	
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

		return result;
	}

	Control* modelControl;
	ScribbleModel* model;
	const ScribbleShape* activeShape;
};

#endif //SCRIBBLECONTROLLER_H__
