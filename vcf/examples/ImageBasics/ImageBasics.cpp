//ImageBasics.cpp


#include "ApplicationKit.h"


using namespace VCF;

/**
This example will demonstrate some of the basics of 
working with images
*/

class ImageBasicsWindow : public Window {
public:
	ImageBasicsWindow() {
		setCaption( "ImageBasics" );
		setVisible( true );
	}

	virtual ~ImageBasicsWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );


		/**
		This will create an image from a given file name
		*/
		Image* logoImage = GraphicsToolkit::createImage( "logo.bmp" );

		/**
		Simplest way to draw an image
		*/

		double x = 20;
		double y = 20;

		ctx->drawImage( x, y, logoImage );

		y += logoImage->getHeight() + 20;

		/**
		Draw a portion of the image
		*/

		Rect r( 0, 0, logoImage->getWidth(), logoImage->getHeight() );
		r.offset( x, y );

		//original bounds
		ctx->setColor( Color::getColor("black") );
		ctx->rectangle( &r );
		ctx->strokePath();

		r.inflate( -10, -10 );

		ctx->drawImageWithinBounds( &r, logoImage );

		y += logoImage->getHeight() + 20;

		String imageInfo = StringUtils::format( "Image width: %d, height: %d", 
												logoImage->getWidth(),
												logoImage->getHeight() );

		ctx->textAt( x, y, imageInfo );

		y += ctx->getTextHeight( imageInfo ) + 20;

		/**
		draw on the image
		*/
		/**
		first lock the image
		*/
		logoImage->beginDrawing();

		GraphicsContext* imgCtx = logoImage->getImageContext();

		/**
		draw a red rectangle on the image
		*/
		imgCtx->setColor( Color::getColor("red") );
		
		imgCtx->rectangle( 20, 20, 100, 75 );
		imgCtx->fillPath();

		/**
		unlock the image makes sure the image pixels are uptodate
		*/
		logoImage->finishedDrawing();

		/**
		draw the image again
		*/
		ctx->drawImage( x, y, logoImage );

		y += logoImage->getHeight() + 20;

		/**
		bitblt a portion of the image context to our current ctx
		*/
		logoImage->beginDrawing();
		imgCtx = logoImage->getImageContext();

		Rect src(0,0,100,50);
		Rect dest(10, y, 10 + src.getWidth(), y + src.getHeight() );

		ctx->copyContext( src, dest, imgCtx );

		logoImage->finishedDrawing();

		y += dest.getHeight() + 20;

		/**
		Now draw the image transparently. Note that this does not use any sort 
		of alpha channel transparency
		*/

		logoImage->setIsTransparent( true );
		logoImage->setTransparencyColor( Color::getColor("red") );

		ctx->drawImage( x, y, logoImage );

		y += logoImage->getHeight() + 20;


		logoImage->setIsTransparent( false );
		/**
		Manipulate the pixel bits
		*/

		/**
		retrieve the image bits - you'll get a pointer to
		a SysPixelType
		*/
		SysPixelType* pix = logoImage->getImageBits()->pixels_;

		/**
		Calculate the size, width * height
		*/
		int size = logoImage->getHeight() * logoImage->getWidth();
		/**
		manipulate the values of the green color channel
		*/
		for ( int i=0;i<size;i++ ) {
			pix[i].g = minVal<>( 255, pix[i].g + 50 );
		}


		ctx->drawImage( x, y, logoImage );

		/**
		delete the image cause we don't need it anymore
		*/
		delete logoImage;
		
	}
};




class ImageBasicsApplication : public Application {
public:

	ImageBasicsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ImageBasicsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ImageBasicsApplication( argc, argv );

	Application::main();
	
	return 0;
}


