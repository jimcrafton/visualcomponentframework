//Scribble1.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "ScribbleModel.h"


using namespace VCF;



class Scribble1Window : public Window {
public:
	Scribble1Window() {
		ScribbleModel* scribble = new ScribbleModel();

		addComponent( scribble );
		scribble->addView( this );

		scribble->addLine( Point(10, 100), Point(100, 300) );

		scribble->addRect( Point(100, 20), Point(200, 110) );

		ScribbleShape* shape = new ScribbleShape();
		shape->type = ScribbleShape::stPolygon;
		shape->points.push_back( Point(40, 30) );
		shape->points.push_back( Point(34, 120) );
		shape->points.push_back( Point(200, 180) );
		shape->points.push_back( Point(300, 100) );
		shape->points.push_back( Point(260, 80) );
		shape->points.push_back( Point(100, 40) );
		shape->strokeWidth = 5;
		shape->filled = true;
		shape->fill = *Color::getColor("red");
		shape->stroke = *Color::getColor("purple");
		shape->mat = Matrix2D::translation( -40, -30 ) * Matrix2D::rotation(-25) * Matrix2D::translation( 70, 200 );


		scribble->add( shape );


	}
	virtual ~Scribble1Window(){};

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

_class_rtti_(Scribble1Window, "VCF::Window", "Scribble1Window")
_class_rtti_end_






class Scribble1Application : public Application {
public:

	Scribble1Application( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(Scribble1Window);


		Window* mainWindow = Frame::createWindow( classid(Scribble1Window) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Scribble1Application>(argc,argv);
}


