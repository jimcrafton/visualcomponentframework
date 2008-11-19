//OGLDraw.cpp




#include "vcf/ApplicationKit/ApplicationKit.h"



#include "GL/glew.h"




#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"


#ifdef  _DEBUG
#pragma comment (lib,"glew32sd.lib")
#else
#pragma comment (lib,"glew32s.lib")
#endif

using namespace VCF;


#define FRAG_CODE	"void main()\n"\
	"{\n"\
		"gl_FragColor = vec4(0.4,0.4,0.8,1.0);\n"\
	"}\n"


class OGLView : public OpenGLControl {
public:

	GLuint frag;
	GLuint prog;

	OGLView() {

		

	}

	GLuint texture;
	GLuint tex2;

	uint32 imWidth;
	uint32 imHeight;

	virtual void paint(GraphicsContext * context) {
		OpenGLControl::paint( context );

		static initialized = false;

		if ( !initialized ) {
			texture = -1;
			tex2 = -1;

			GLenum err = glewInit();
			prog = glCreateProgramObjectARB();


			String s;
			{
				FileInputStream fis("frag.shader");
				fis >> s;
			}

			frag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

			AnsiString src = s;
			int len = src.size();
			const char* srcStr = src.c_str();
			glShaderSourceARB(frag, 1, (const GLcharARB**)&srcStr, &len);

			glCompileShaderARB(frag);


			int i;
			glGetObjectParameterivARB(frag,GL_OBJECT_COMPILE_STATUS_ARB,&i);
			char* s2 = (char*)malloc(32768);
			glGetInfoLogARB(frag,32768,NULL,s2);
			s = String("Compile Log:\n") +  s2;
			::free(s2);
			Dialog::showMessage( s );



			glAttachObjectARB(prog, frag);
			glLinkProgramARB(prog);


			

			
			Image* img = GraphicsToolkit::createImage( "res:logo.png" );
			if ( img ) {
				imWidth = img->getWidth();
				imHeight = img->getHeight();

				glGenTextures(1, &texture);
				glGenTextures(1, &tex2);
				
				
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use nice (linear) scaling
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use nice (linear) scaling
				glTexImage2D(GL_TEXTURE_2D, 0, 4, img->getWidth(), img->getHeight(), 
					0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getData() );

				delete img;
			}
		}

		initialized = true;




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


		

		if ( texture != -1 ) {


			glBindTexture(GL_TEXTURE_2D, texture);
			float alpha = 1.0;
			glColor4f(1.0, 1.0, 1.0, alpha);

			uint32 h,w;
			w = imWidth;
			h = imHeight;

			int x,y;
			x = 10;
			y = 10;

			double u,v;
			u=0.5;
			v=0.5;

			glUseProgramObjectARB( prog );
			int u1 = glGetUniformLocationARB(prog, "myTexture");
			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1iARB(u1, 0);







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

			w = imWidth/2;
			h = imHeight/2;

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

			w = imWidth;
			h = imHeight;


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
			y = 300;
			u=1.0;
			v=1.0;

			w = imWidth;
			h = imHeight;

			glUseProgramObjectARB(0);

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


			glUseProgramObjectARB(prog);

			x = 10;
			y = 320;
			u=1.0;
			v=1.0;

			w = imWidth;
			h = imHeight;


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
		}

		


		swapBuffers();

		context->rectangle( 100, 300, 200, 400 );
		context->fillPath();
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


