//OGLDraw.cpp




#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/RTTIMacros.h"





#include "ImageKit.h"




namespace VCF { 


class GL2DView : public View {
public:
	virtual void paintView( GraphicsContext* ctx ) {
		Rect r = getViewControl()->getClientBounds();

		Color c = *getViewControl()->getColor();

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, r.getWidth(), r.getHeight(), 0, -1, 1);
		glViewport( 0, 0, r.getWidth(), r.getHeight() );
		
		glDisable(GL_DEPTH_TEST);		

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor( c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha() );
		glClear(GL_COLOR_BUFFER_BIT);
	}
};




};//namespace vcf




using namespace VCF;



class OGLView : public OpenGLControl {
public:


	OGLView() {

		hueAdj = NULL;

	}

	IKImage img;
	HueAdjust* hueAdj;
	Brighten* bright;
	Mixer* mix;

	IKImage img2;

	void doGL()
	{
		static initialized = false;

		if ( !initialized ) {


			initialized = true;

			img.initFromFile( "res:logo.png" );
			img2.initFromFile( "res:logo2.png" );


			hueAdj = new HueAdjust();

			bright = new Brighten();

			mix = new Mixer();
		}

		initialized = true;



		Rect r = getClientBounds();

		IKImageContext ic;

		ic.initView( r.getWidth(), r.getHeight() );

		Color c = *getColor();
		glClearColor( c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha() );
		glClear(GL_COLOR_BUFFER_BIT);		
		
		static double a = 0;	
		
		ic.multiTransformMatrix( Matrix2D::rotation(a) * Matrix2D::scaling(1.3,1.3) );
		
		ic.draw( 10, 10, &img );


		ic.setTransformMatrix( Matrix2D::translation( 50, 100 ) );
		ic.setOpacity( sin( 0.1250 * (a/6.28) ) );
		ic.draw( 10, 10, &img );

		ic.setTransformMatrix( Matrix2D() );
		ic.draw( 30, 210, &img );
		ic.draw( 130, 310, &img );

		ic.multiTransformMatrix( Matrix2D::rotation(a) );
		ic.draw( 10, 210, &img );
		ic.draw( 231, 410, &img );

		a += 1.0;





		

		//hueAdj->setInputImage( &img );
		//hueAdj->setHueVal( 1.5 );

		//bright->setInputImage( hueAdj->getOutputImage() );
		//bright->setBrightness( 0.5 );

		mix->setInputImage( &img );
		mix->setInput2Image( &img2 );

		ic.setTransformMatrix( Matrix2D() );
		ic.setOpacity( 1.0 );		

		ic.draw( 300, 350, mix->getOutputImage() );
	}


	virtual void paint(GraphicsContext * context) {
		OpenGLControl::paint( context );

		doGL();

		swapBuffers();
	}
};

class OGLDrawWindow : public Window {
public:
	OGLDrawWindow() {
		setCaption( "OGLDraw" );		

		OGLView* view = new OGLView();
		add( view, AlignClient );
	}

	virtual ~OGLDrawWindow(){};

};




class OGLDrawApplication : public Application {
public:

	OGLDrawApplication( int argc, char** argv ) : Application(argc, argv) {
		
		OpenGLKit::init(argc,argv);
		ImageKit::init(argc,argv);
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		

		Window* mainWindow = new OGLDrawWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 700.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

	virtual void terminateRunningApplication() {
		ImageKit::terminate();
		Application::terminateRunningApplication();
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<OGLDrawApplication>(argc,argv);
}


