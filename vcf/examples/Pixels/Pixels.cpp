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

		double y = 10;

		ctx->drawImage( 100, y, imgPtr );

		y += imgPtr->getHeight() + 20;

		ctx->bitBlit( 100, y, imgPtr );

		y += imgPtr->getHeight() + 20;




		SmartPtr<Image>::Scoped grImg( GraphicsToolkit::createImage( 256, 100, Image::itGrayscale ) );


		imgPtr = get_pointer(grImg);
		GrayPixels grPix = imgPtr;

		imgCtx = imgPtr->getImageContext();

		imgCtx->setColor(Color::getColor("yellow"));
		imgCtx->moveTo( 10, 10 );
		imgCtx->lineTo( 90, 78 );
		imgCtx->strokePath();

		ctx->drawImage( 100, y, imgPtr );

		y += imgPtr->getHeight() + 20;

		ctx->bitBlit( 100, y, imgPtr );

		unsigned char* pixPtr = (unsigned char*)imgPtr->getData();

		uint32 sz =  grPix.width() * grPix.height();
		 
		for ( int yy=0;yy<grPix.height();yy++ ) {
			for ( int i=0;i<grPix.width();i++) {
				*pixPtr = i;
				pixPtr ++;
				//grPix.at(i,yy).value = i;
			}
		}


		y += imgPtr->getHeight() + 20;

		ctx->bitBlit( 100, y, imgPtr );
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


