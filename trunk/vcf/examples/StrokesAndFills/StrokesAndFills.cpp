//StrokesAndFills.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"



using namespace VCF;


/**
This example will demonstrate the use of the 
Fill and Stroke classes and the new AGG anti-aliased
vector library support.
*/

class StrokesAndFillsWindow : public Window {
public:
	StrokesAndFillsWindow() {
		setCaption( "StrokesAndFills" );

		/**
		Create a checkbox button, and add an event handler
		when the button is clicked
		*/
		CheckBoxControl* antiAliasToggle = new CheckBoxControl();
		antiAliasToggle->setCaption( "Anti-aliased" );
		antiAliasToggle->setBounds( 20, 20, 100, antiAliasToggle->getPreferredHeight() );
		add( antiAliasToggle );

		antiAliasToggle->ButtonClicked += new ButtonEventHandler<StrokesAndFillsWindow>( this, &StrokesAndFillsWindow::onButtonClicked, "StrokesAndFillsWindow::onButtonClicked" );
	}

	virtual ~StrokesAndFillsWindow(){};


	/**
	This event handler will toggle whether or not hte render
	buffer is enabled. If the render buffer is enabled 
	(isUsingRenderBuffer() returns true) then anti-aliased
	drawing is possible for the control, otherwise no 
	anti-aliased drawing will take place.
	*/
	void onButtonClicked( ButtonEvent* e ) {
		CheckBoxControl* antiAliasToggle = (CheckBoxControl*)e->getSource();

		antiAliasToggle->setChecked( !isUsingRenderBuffer() );

		/**
		calling this method sets the use of an render buffer
		to support the anti-aliasing features of AGG. Each control
		can control whether or not it support this, and by 
		default controls start up *not* using the render 
		buffer.
		*/
		setUsingRenderBuffer( antiAliasToggle->isChecked() );

		
		if ( isUsingRenderBuffer() ) {
			GraphicsContext* ctx = getContext();
			ctx->setDrawingArea( getClientBounds() );
		}

		repaint();
	}


	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		/**
		This is a path that supports lines, and curves.
		You call the moveTo, lineTo, curveTo, etc methods
		to add points to the path.
		*/
		BezierCurve shape;

		/**
		This is a stroke object. You can use it 
		to draw the shape of your path. You 
		set properties of the stroke object 
		such as the width, color, etc.
		*/
		BasicStroke stroke;

		/**
		This sets the current stroke to use. This 
		pointer is *not* owned by the GraphicsContext
		so be sure to set it to NULL (or 
		the previous value) when you're done
		*/
		ctx->setCurrentStroke( &stroke );
		
		/**
		Add two points to the path
		*/
		shape.moveTo( 100, 100 );
		shape.lineTo( 300, 300 );

		/**
		Draw the path. The GraphicsContext will use
		it's current Stroke and Fill pointers to stroke
		and fill the path. Since we have not specified a 
		Fill to use, the path will only be stroked
		*/
		ctx->draw( &shape );

		/**
		Adjust the GraphicsContext's matrix
		to offset by 0 pixels to the left, and 50 pixel down
		This will transform any paths that are drawn but will
		*not* directly modify the path's points
		*/
		ctx->setTranslation( 0, 50 );

		/**
		set the stroke's color to green and the 
		width to 3
		*/
		stroke.setColor( &Color(0.0,1.0,0.0) ); 
		stroke.setWidth( 3.0 );

		ctx->draw( &shape );

		/*
		reset the translation
		*/
		ctx->setTranslation( 0, 0 );

		/**
		create a curved shape .
		the curve() method takes 4 points, a
		starting point, the first control point, the second 
		control point, and the end point.
		*/
		BezierCurve shape2;

		/**
		This will overlap the previous shapes a bit
		so we can see the effects of setting the 
		stroke's opacity
		*/
		shape2.curve( 50, 300,
						100, 250,
						300, 250,
						375, 300 );


		stroke.setColor( &Color(1.0,0.0,0.75) ); 
		stroke.setWidth( 15.0 );
		/**
		Note we set the stroke to be 75% opaque
		so we'll be able to partially see what ever is
		"underneath" this shape. However this will
		only take effect if the anti-aliasing support 
		is enabled by calling setUsingRenderBuffer() with 
		a true value passed in.
		*/
		stroke.setOpacity( 0.75 );

		ctx->draw( &shape2 );


		BezierCurve rect;

		rect.rectangle( Rect(75,350,175,450) );

		ctx->draw( &rect );

		BasicFill fill;
		fill.setColor( *Color::getColor("yellow") );
		fill.setOpacity( 0.65 );

		ctx->setCurrentFill( &fill );

		/**
		We're going to directly modify the points of our
		path by using a series to matrices to transform
		the shape by first rotating 45 degrees and then
		offsetting by 50 pixels
		*/
		Matrix2D translate;
		/**
		tranlation matrix to move the rect shape back to 
		0,0 centered around it's center.
		Our rect's left/top coordinate was at 75,350
		and it's width/height was 100,100 so to center
		it around the origin (0,0) we need to
		translate it by -125,-400
		*/
		translate.translate( -125, -400 );

		Matrix2D rotate;
		rotate.rotate( 45 );

		Matrix2D mat;
		
		mat.multiply( &translate, &rotate );	

		/**
		apply the rotation/translation matrix to the shape
		*/
		rect.applyTransform( mat );

		translate.translate( 125, 400 );

		/**
		transalte the shape back to it's original position
		only now's been rotated 45 degrees
		*/
		rect.applyTransform( translate );

		translate.translate( 0, 50 );
		//move it down 50 pixels
		rect.applyTransform( translate );

		Color ltBlue(0.0,0.0,1.0);
		//change the color by manipulating the HSV components
		ltBlue.changeHSV( 0.23, 0.0, 0.0 );

		stroke.setColor( &ltBlue );
		stroke.setWidth( 4.0 );
		stroke.setOpacity( 0.45 );

		ctx->draw( &rect );


		ctx->setCurrentFill( NULL );
		ctx->setCurrentStroke( NULL );
	}
};




class StrokesAndFillsApplication : public Application {
public:

	StrokesAndFillsApplication(int argc, char** argv) : Application(argc,argv){

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new StrokesAndFillsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new StrokesAndFillsApplication( argc, argv );

	Application::main();
	
	return 0;
}

