//Pixels.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/Pixels.h"



using namespace VCF;


struct ImgPtr {
		
};

class PixelsWindow : public Window {
public:
	PixelsWindow() {
		setCaption( "Pixels" );		

	}

	virtual ~PixelsWindow(){};



	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );



		//using smart pointer
		SmartPtr<Image>::Scoped img( GraphicsToolkit::createImage( 100, 100 ) );

		Image* imgPtr = get_pointer(img);

		GraphicsContext* imgCtx = imgPtr->getImageContext();
		
		imgCtx->setColor(Color::getColor("red"));
		imgCtx->rectangle( 0,0,100,100);
		imgCtx->fillPath();
		

		ColorPixels pix = imgPtr;


		ctx->drawImage( 100, 100, imgPtr );

		ctx->bitBlit( 100, 300, imgPtr );

	}



};




class PixelsApplication : public Application {
public:

	PixelsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new PixelsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new PixelsApplication( argc, argv );

	Application::main();
	
	return 0;
}


