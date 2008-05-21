//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/ApplicationKit/Label.h"

#include "ScribbleModel.h"
#include "ScribbleView.h"


using namespace VCF;

class AboutDialog : public Dialog {
public:
	Label* program;
	Label* author;
	Label* company;
	Label* copyright;
	AboutDialog(){

	}
};

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
				
				modelControl->setToolTipText( String("Shape #") + index  );
			}
			else {
				modelControl->setToolTipText( "" );
			}
		}
	}

	void onMouseDown( MouseEvent* e ) {

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


class Scribble4Window : public Window {
public:
	Scribble4Window() {
		
	}
	virtual ~Scribble4Window(){};

};




class Scribble4App : public Application {
public:

	Scribble4App( int argc, char** argv );

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		

		Window* mainWindow = Frame::createWindow( classid(Scribble4Window) );
		setMainWindow(mainWindow);

		ScribbleModel* m = (ScribbleModel*)findComponent( "scribble", true );
		ScribbleView* view = new ScribbleView();
		mainWindow->setView( view );
		m->addView( view );
		
		ScribbleController* controller = new ScribbleController();
		addComponent(controller);
		controller->setControl( mainWindow );
		controller->setModel( m );



		mainWindow->show();
		
		return result;
	}

	void onAbout(Event*) {
		AboutDialog* aboutDlg = (AboutDialog*)Frame::createDialog( classid(AboutDialog) );
		ProgramInfo* info = this->getResourceBundle()->getProgramInfo();
		if ( NULL != info ) {
			aboutDlg->program->setCaption( info->getProgramName() );
			aboutDlg->author->setCaption( info->getAuthor() );
			aboutDlg->company->setCaption( info->getCompany() );
			aboutDlg->copyright->setCaption( info->getCopyright() );
			delete info;
		}
		aboutDlg->showModal();
	}

};











_class_rtti_(ScribbleController, "VCF::Component", "ScribbleController")
_class_rtti_end_

_class_rtti_(Scribble4Window, "VCF::Window", "Scribble4Window")
_class_rtti_end_

_class_rtti_(AboutDialog, "VCF::Dialog", "AboutDialog")
_field_obj_( Label*, program )
_field_obj_( Label*, copyright )
_field_obj_( Label*, author )
_field_obj_( Label*, company )
_class_rtti_end_


_class_rtti_(ScribbleShape, "VCF::Object", "ScribbleShape")
_property_object_( Color, "fill", getFill, setFill, "" );
_property_object_( Color, "stroke", getStroke, setStroke, "" );
_property_( double, "strokeWidth", getStrokeWidth, setStrokeWidth, "" );
_property_( bool, "filled", getFilled, setFilled, "" );
_property_( String, "data", getData, setData, "" );
_property_( double, "rotation", getRotation, setRotation, "" );
_property_( double, "transX", getTranslateX, setTranslateX, "" );
_property_( double, "transY", getTranslateY, setTranslateY, "" );
_property_( double, "scaleX", getScaleX, setScaleX, "" );
_property_( double, "scaleY", getScaleY, setScaleY, "" );
_property_( double, "shearX", getShearX, setShearX, "" );
_property_( double, "shearY", getShearY, setShearY, "" );
_class_rtti_end_

_class_rtti_(ScribbleModel, "VCF::SimpleListModel", "ScribbleModel")
_property_array_( VariantData, "shapes", get,set,insert,remove,getCount, "" )
_property_object_( Color, "backColor", getBackColor, setBackColor, "" );
_property_object_( Color, "defaultFill", getDefaultFillColor, setDefaultFillColor, "" );
_property_object_( Color, "defaultStroke", getDefaultStrokeColor, setDefaultStrokeColor, "" );
_property_( double, "defaultStrokeWidth", getDefaultWidth, setDefaultWidth, "" );
_property_( bool, "defaultFilled", getDefaultFilled, setDefaultFilled, "" );
_class_rtti_end_

Scribble4App::Scribble4App( int argc, char** argv ) : 
	Application(argc, argv)
{
	REGISTER_CLASSINFO_EXTERNAL(Scribble4Window);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
	REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);
	REGISTER_CLASSINFO_EXTERNAL(AboutDialog);
	
	
	addCallback( new ClassProcedure1<Event*,Scribble4App>(this, &Scribble4App::onAbout), "Scribble4App::onAbout" );
	
}


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble4App>(argc,argv);
}


