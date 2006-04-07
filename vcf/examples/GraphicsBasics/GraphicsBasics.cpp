//GraphicsBasics.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


/**
This simple example will demostrate the basics of using the GraphicsContext
class for drawing.
*/
class GraphicsBasicsWindow : public Window {
public:
	GraphicsBasicsWindow() {
		setCaption( "GraphicsBasics" );
	}

	virtual ~GraphicsBasicsWindow(){};



	/**
	To start with we need to override the paint() method
	to handle any custom drawing for our window (or any other control for
	that matter).

	When drawing with the GraphicsContext, the origin is always at the top left
	of the control. The default origin is at 0,0 unless you change it.
	Drawing consists of setting various properties of the GraphicsContext,
	telling it to execute certain drawing commands, and then telling the GraphicsContext
	to stroke or fill the path, if neccessary. Any line drawing, such as straight
	lines, rectangles, ellipses, polylines, etc, are not drawn till the
	GraphicsContext::strokePath() or GraphicsContext::filePath() is called.


	Drawing text or images happens right away.
	*/
	virtual void paint( GraphicsContext* ctx ) {
		//Make sure to call the sub classes paint method
		Window::paint( ctx );

		ctx->setStrokeWidth( 1.0 );
		/**
		Set the current color
		*/
		ctx->setColor( Color::getColor( "black" ) );


		/**
		Lets draw a rectangle, then offset and draw it again, but filled
		with a blue color
		*/
		Rect rect( 20, 20, 100, 100 );
		ctx->rectangle( &rect );
		ctx->strokePath();


		/**
		offset the rect by 100 pixels in the y direction
		*/
		rect.offset( 0, 100 );
		ctx->setColor( &Color(0.0,0.0,1.0) ); //r,g,b, blue is r(0), g(0), b(1)
		ctx->rectangle( &rect );
		ctx->fillPath();


		double x = rect.left_;
		double y = rect.bottom_ + 50;

		/**
		Lets draw 5 lines, each one thicker than the next
		*/
		for (int i=0;i<5;i++) {
			/**
			set the stroke width
			*/
			ctx->setStrokeWidth( i + 1 );

			/**
			draw a horizontal line 100 pixels long
			*/
			ctx->moveTo( x, y + i*10 );
			ctx->lineTo( x + 100, y + i*10 );
			ctx->strokePath();
		}

		/**
		reset the stroke width back to 0
		*/
		ctx->setStrokeWidth( 1.0 );


		/**
		Lets draw some simple text with the current font
		*/

		x = 200;
		y = 20;

		ctx->textAt( x, y, "Here's some simple text" );

		/**
		Let's modify the current font and make it larger
		*/

		ctx->getCurrentFont()->setPointSize( 23 );
		y += 50;

		ctx->textAt( x, y, "Here's some simple text" );


		/**
		Create a font from scratch and then set the GraphicsContext's
		current font
		*/

		Font myFont( "Arial", 40 );
		myFont.setItalic( true );

		/**
		Note that to change the color that text is rendered in
		you have to change the Font's color, not the GraphicsContext's color
		*/
		myFont.setColor( &Color(1.0,0.0,0.0) );

		/**
		Set the current font - the GraphicsContext keeps it own font instance, and
		simply copies all the attributes of the font passed into setCurrentFont().
		This means the font you pass in can be temporary, and allocated on the stack
		if you want.
		*/
		ctx->setCurrentFont( &myFont );

		y += 50;

		ctx->textAt( x, y, "Here's some simple text" );
	}
};


/**
The application class
*/

class GraphicsBasicsApplication : public Application {
public:

	GraphicsBasicsApplication(int argc, char** argv) : Application(argc,argv){

	}
	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new GraphicsBasicsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 5.0, 100.0, 800.0, 375.0 );
		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new GraphicsBasicsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.7  2006/04/07 02:34:28  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.6.4.1  2006/03/19 18:42:10  ddiego
*fixed window size for graphics basics example per fraggles req.
*
*Revision 1.6  2004/12/01 04:15:04  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.5.2.1  2004/11/15 05:41:27  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.5  2004/08/07 02:47:03  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.4.2.5  2004/08/02 04:11:53  ddiego
*added more examples to xcode project
*
*Revision 1.4.2.4  2004/04/29 03:40:53  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


