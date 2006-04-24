//ImageBasics.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/Win32Image.h"
#include "vcf/GraphicsKit/Pixels.h"



using namespace VCF;

/**
This example will demonstrate some of the basics of
working with images
*/


class ImageBasicsWindow : public Window {
public:
	ImageBasicsWindow() {
		setCaption( "ImageBasics" );		
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

		String imageInfo = Format( "Image width: %d, height: %d")
									 %logoImage->getWidth() % logoImage->getHeight();

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
		{
			ColorPixels pix(logoImage);//->getImageBits()->pixels_;

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
		}

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

		mainWindow->setBounds( 100.0, 100.0, 400.0, 875.0 );
		mainWindow->show();


		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ImageBasicsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:30  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.12  2006/03/19 18:54:45  ddiego
*adjusted image basics window height.
*
*Revision 1.5.2.11  2006/03/16 18:45:24  kdmix
*setVisible(true) removed from constructor of the main window.
*
*Revision 1.5.2.10  2006/02/15 18:24:27  iamfraggle
*Corrected pixels etc. constructor calls
*
*Revision 1.5.2.9  2006/02/14 20:19:25  ddiego
*some minor bugs
*
*Revision 1.5.2.8  2005/11/11 00:20:58  ddiego
*comitting mostuffs linux foundationkit patchs [1351922].
*
*Revision 1.5.2.7  2005/11/02 16:07:16  ddiego
*updates to createinfo program.
*
*Revision 1.5.2.6  2005/10/11 00:54:51  ddiego
*added initial changes for grayscale image support. fixed some minor changes to form loading and creating.
*
*Revision 1.5.2.5  2005/09/22 18:16:56  ddiego
*added save support for png loader.
*
*Revision 1.5.2.4  2005/09/22 04:02:55  ddiego
*added more png support. we can read png files now.
*
*Revision 1.5.2.3  2005/09/22 00:32:51  ddiego
*added jpeg support to graphics kit.
*
*Revision 1.5.2.2  2005/09/14 18:55:15  ddiego
*update to win32window. initial code for new pixels
*type to replace imagebits class.
*
*Revision 1.5.2.1  2005/07/23 21:45:37  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.4.4.2  2005/04/17 17:19:10  iamfraggle
*Small fixes
*
*Revision 1.4.4.1  2005/04/17 15:11:45  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.4  2004/08/07 02:47:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:54  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


