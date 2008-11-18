//OGLDraw.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"

using namespace VCF;

class OGLView : public OpenGLControl {
public:

	virtual void paint(GraphicsContext * context) {
		OpenGLControl::paint( context );

		Rect r = getClientBounds();

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, r.getWidth(), r.getHeight(), 0, -1, 1);
		glViewport( 0, 0, r.getWidth(), r.getHeight() );
		
		glDisable(GL_DEPTH_TEST);		

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(1.0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);


		Image* img = GraphicsToolkit::createImage( "C:\\code\\vcfdev\\dev\\bluesky\\D3DTest\\logo.png" );
		if ( img ) {

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use nice (linear) scaling
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use nice (linear) scaling
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img->getWidth(), img->getHeight(), 
							0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getData() );



			glBindTexture(GL_TEXTURE_2D, texture);
			float alpha = 1.0;
			glColor4f(1.0, 1.0, 1.0, alpha);

			uint32 h,w;
			w = img->getWidth();
			h = img->getHeight();

			int x,y;
			x = 10;
			y = 10;

			double u,v;
			u=0.5;
			v=0.5;

			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex2i(x, y);

			glTexCoord2f(u, 0.0);
			glVertex2i(x+w, y);

			glTexCoord2f(u, v);
			glVertex2i(x+w, y+h);

			glTexCoord2f(0.0, v);
			glVertex2i(x, y+h);

			glEnd();



			x = 10;
			y = 100;
			u=1.0;
			v=1.0;

			w = img->getWidth()/2;
			h = img->getHeight()/2;

			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex2i(x, y);

			glTexCoord2f(u, 0.0);
			glVertex2i(x+w, y);

			glTexCoord2f(u, v);
			glVertex2i(x+w, y+h);

			glTexCoord2f(0.0, v);
			glVertex2i(x, y+h);

			glEnd();



			x = 10;
			y = 200;
			u=1.0;
			v=1.0;

			w = img->getWidth();
			h = img->getHeight();

			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex2i(x, y);

			glTexCoord2f(u, 0.0);
			glVertex2i(x+w, y);

			glTexCoord2f(u, v);
			glVertex2i(x+w, y+h);

			glTexCoord2f(0.0, v);
			glVertex2i(x, y+h);

			glEnd();


			delete img;
		}

		


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

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new OGLDrawWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 700.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<OGLDrawApplication>(argc,argv);
}


