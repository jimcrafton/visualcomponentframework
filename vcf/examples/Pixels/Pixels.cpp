//Pixels.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/Pixels.h"



class HiResClock {
public:

	HiResClock(){
		QueryPerformanceFrequency( &frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}



	void start() {
		QueryPerformanceCounter( &performanceCounter1_ );
	}

	void stop() {
		QueryPerformanceCounter( &performanceCounter2_ );
	}

	void clear() {
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return (double)(performanceCounter2_.LowPart - performanceCounter1_.LowPart)/(double)frequency_.LowPart;
	}
protected:
	LARGE_INTEGER frequency_;
	LARGE_INTEGER performanceCounter1_;
	LARGE_INTEGER performanceCounter2_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};






















using namespace VCF;


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

		ctx->bitBlit( 100, y, &Rect(10, 10, 226,80), imgPtr );

		unsigned char* pixPtr = (unsigned char*)imgPtr->getData();

		uint32 sz =  grPix.width() * grPix.height();
		 
		for ( int yy=0;yy<grPix.height();yy++ ) {
			for ( int i=0;i<grPix.width();i++) {
				*pixPtr = i;
				pixPtr ++;
			}
		}


		y += imgPtr->getHeight() + 20;

		ctx->bitBlit( 100, y, imgPtr );


		y += imgPtr->getHeight() + 20;
		imgPtr = GraphicsToolkit::createImage( 100, 100 );

		sz = imgPtr->getHeight() * imgPtr->getWidth();

		{
			ColorPixels pix2 = imgPtr;
			ColorPixels::Type* bits = pix2;
			size_t idx = 0;
			size_t width = pix2.width();
			size_t height = pix2.height();
			for ( int yy=0;yy<height;yy++ ) {
				for ( int i=0;i<width;i++) {
					idx = yy * width + i;
					bits[idx].g = 128;
					bits[idx].a = i;
				}
			}

			{
				HiResClock cl;

				RedChannel c(pix2);
				
				cl.start();
				RedChannel::Iterator it = c.begin();
				while ( it != c.end() ) {
					*it = 255;
					++it ;
				}
				cl.stop();
				StringUtils::trace( Format("RedChannel mod using iterator took %.8f seconds") % cl.duration() );
				

				cl.start();
				bits = pix2;
				uint32 sz = pix2.width() * pix2.height();
				do {
					sz --;
					bits[sz].g = 23;
				} while(sz > 0 );

				cl.stop();
				StringUtils::trace( Format("Direct mod using pointer access took %.8f seconds") % cl.duration() );


				
				cl.start();

				BlueChannel c2(pix2);
				c2.fill( 125 );

				cl.stop();
				StringUtils::trace( Format("BlueChannel::fill() took %.8f seconds") % cl.duration() );


				Image* i = c.createImage();
				c2.updateFromImage( i );

				ctx->drawImage( 400, y, i );

				delete i;

			}

		}

		ctx->drawImage( 100, y, imgPtr, false );
		y += imgPtr->getHeight() + 20;

		ctx->renderImages(); //imgPtr is deleted when this call completes



		
		imgPtr = GraphicsToolkit::createImage( 100, 100 );

		{
			ImageContext imgCtx2 = imgPtr;
			
			imgCtx2->setColor(Color::getColor("green"));
			imgCtx2->rectangle( 0,0,100,100);
			imgCtx2->fillPath();

			imgCtx2->textAt( 10, 50, "Shape 1" );
		}

		ctx->setRotation( 45 );

		ctx->drawImage( 100, y, imgPtr,false );
		ctx->drawImage( 221, 70, imgPtr,false );

		

		Matrix2D m;
		m *= Matrix2D::translation(0,0);
		m *= Matrix2D::rotation( 0 );
		m *= Matrix2D::translation(220, 220);
		ctx->setCurrentTransform( m );

		ctx->setColor( Color::getColor("yellow") );		
		ctx->rectangle( &Rect(0,0,100,100) );
		ctx->strokePath();

		ctx->setCompositingMode( GraphicsContext::cmLighten );
		ctx->setAlpha( 0.68 );
		ctx->drawImage( 0, 0, imgPtr, false );

		ctx->renderImages();


		//ctx->setRotation( 45 );
		

		

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
		mainWindow->setBounds( 100.0, 10.0, 400.0, 880.0 );
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


