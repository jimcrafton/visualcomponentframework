//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "ScribbleModel.h"


using namespace VCF;



class Scribble2Window : public Window {
public:
	Scribble2Window() {
		
	}
	virtual ~Scribble2Window(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		ScribbleModel* scribble = (ScribbleModel*) getViewModel();

		Rect r = getClientBounds();

		ctx->rectangle( r );
		ctx->setColor( scribble->getBackColor() );
		ctx->fillPath();

		size_t count = scribble->getCount();
		for (size_t i=0;i<count;i++ ) {
			const ScribbleShape* shape = scribble->getShape(i);			

			int gcs = ctx->saveState();

			ctx->setCurrentTransform( shape->mat );
			switch ( shape->type ) {
				case ScribbleShape::stLine : {
					ctx->setColor( &shape->stroke );
					ctx->moveTo( shape->points[0] );
					ctx->lineTo( shape->points[1] );
					ctx->strokePath();
				}
				break;

				case ScribbleShape::stRect : {
					
					r.setRect( shape->points[0].x_, shape->points[0].y_,
								shape->points[1].x_, shape->points[1].y_ );
					ctx->rectangle( r );
				}
				break;

				case ScribbleShape::stEllipse : {
					r.setRect( shape->points[0].x_, shape->points[0].y_,
								shape->points[1].x_, shape->points[1].y_ );

					ctx->ellipse( r.getTopLeft(), r.getBottomRight() );					
				}
				break;

				case ScribbleShape::stPolygon : {
					ctx->polyline( shape->points );
					ctx->closePath( shape->points.back() );
				}
				break;

				case ScribbleShape::stFreehand : {
					ctx->polyline( shape->points );
				}
				break;
			}

			if ( shape->type != ScribbleShape::stLine ) {
				if ( shape->filled ) {
					ctx->setColor( &shape->fill );
					ctx->fillPath();
				}

				ctx->setStrokeWidth( shape->strokeWidth );
				ctx->setColor( &shape->stroke );
				ctx->strokePath();
			}

			ctx->restoreState( gcs );
		}
	}
};

_class_rtti_(Scribble2Window, "VCF::Window", "Scribble2Window")
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




class Scribble1Application : public Application {
public:

	Scribble1Application( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(Scribble2Window);
		REGISTER_CLASSINFO_EXTERNAL(ScribbleShape);
		REGISTER_CLASSINFO_EXTERNAL(ScribbleModel);

		Window* mainWindow = Frame::createWindow( classid(Scribble2Window) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble1Application>(argc,argv);
}


