//GraphicsAndMouseMoves.cpp


#include "ApplicationKit.h"


using namespace VCF;

/**
This example will discuss using the graphics
API's in various mouse events, such as drawing a 
selection rect

*/

class GraphicsAndMouseMovesWindow : public Window {
public:
	GraphicsAndMouseMovesWindow() {
		setCaption( "GraphicsAndMouseMoves" );
		
		
	}

	virtual ~GraphicsAndMouseMovesWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		ctx->getCurrentFont()->setColor( &Color(1.0,0.0,0.0) );
		ctx->getCurrentFont()->setPointSize( 15 );
		ctx->getCurrentFont()->setName( "Arial" );


		ctx->textAt( 50, 50, "Drag the mouse with the left button down!" );
	}

	/**
	override the mouse down. move, and up
	methods to draw a simple selection rect
	*/
	virtual void mouseDown( MouseEvent* e ) {
		/**
		Check to see if we have a left mouse click
		*/
		if ( e->hasLeftButton() ) {

			/**
			keeps all the mouse events, so they continue
			to be routed to this control even if the mouse is outside
			the controls bounds.
			*/
			keepMouseEvents();

			Point& pt = *e->getPoint();

			/**
			initialize the rect
			*/
			dragRect_.setRect( pt.x_, pt.y_, pt.x_, pt.y_ );


			/**
			retrieve the GraphicsContext associate with this control
			*/
			GraphicsContext* ctx = getContext();

			/**
			turn the GraphicsContext's XOR mode on. This allows for the 
			rubber banding effect. 
			*/
			ctx->setXORModeOn( true );

			/*
			Draw a rectangle
			*/
			ctx->rectangle( &dragRect_ );
			ctx->strokePath();


			/**
			turn the GraphicsContext's XOR mode off
			*/
			ctx->setXORModeOn( false );
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			GraphicsContext* ctx = getContext();
			ctx->setXORModeOn( true );

			/**
			Draw the rectangle again - this will erase the previous 
			rectangle since we are in XOR drawing mode.
			*/
			ctx->rectangle( &dragRect_ );
			ctx->strokePath();

			Point& pt = *e->getPoint();

			/**
			set the rectangles bottom,right corner to the
			current mouse point.
			*/
			dragRect_.right_ = pt.x_;
			dragRect_.bottom_ = pt.y_;

			/**
			Draw the rectangle at it's current coordinates.
			*/
			ctx->rectangle( &dragRect_ );
			ctx->strokePath();

			ctx->setXORModeOn( false );
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		releaseMouseEvents();

		if ( e->hasLeftButton() ) {
			GraphicsContext* ctx = getContext();
			ctx->setXORModeOn( true );

			/**
			Same as before - draw the rectangle again to erase the previous
			shape.
			*/
			ctx->rectangle( &dragRect_ );
			ctx->strokePath();

			Point& pt = *e->getPoint();

			/**
			set the rectangles bottom,right corner to the
			current mouse point.
			*/
			dragRect_.right_ = pt.x_;
			dragRect_.bottom_ = pt.y_;

			/**
			Draw the rectangle *twice* this time - this is to 
			draw it at the new coordinates, and then draw it 
			again to erase the shape.
			*/
			ctx->rectangle( &dragRect_ );
			ctx->strokePath();

			ctx->rectangle( &dragRect_ );
			ctx->strokePath();

			ctx->setXORModeOn( false );
		}
	}

	Rect dragRect_;
};




class GraphicsAndMouseMovesApplication : public Application {
public:

	GraphicsAndMouseMovesApplication(int argc, char** argv) : Application(argc,argv){

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new GraphicsAndMouseMovesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	GraphicsAndMouseMovesApplication app( argc, argv );

	Application::main();
	
	return 0;
}

