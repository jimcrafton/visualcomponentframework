//OpenGLShapes.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"

using namespace VCF;

/**
This example demostrates how to use OpenGL
*/

class OpenGLShapesControl : public OpenGLControl {
public:
	OpenGLShapesControl():OpenGLControl(){
		initialized=false;
		angle=0;
		shape=0;
		sphere=gluNewQuadric();

		EventHandler* ev=new GenericEventHandler<OpenGLShapesControl>( this, &OpenGLShapesControl::onTimer, "OpenGLShapesControl::onTimer" );

		TimerComponent* timer = new TimerComponent();
		addComponent( timer );
		timer->TimerPulse.addHandler(ev);
		timer->setTimeoutInterval( 33 ); //around 30 FPS
		timer->setActivated( true );
	}

	~OpenGLShapesControl(){
		gluDeleteQuadric(sphere);
	}

	void onTimer( Event* e ) {
		angle++;
		repaint();
	}


	void paint(GraphicsContext *ctx){
		OpenGLControl::paint(ctx);

		Rect clientBounds = getClientBounds();

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		glViewport(0,0,clientBounds.getWidth(),clientBounds.getHeight());

		glLoadIdentity();

		gluPerspective(80,1,1,10);
		glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glColor3f( 1.0f, 0.0f, 0.0f );

		glTranslatef(0,0,-5);
		glRotatef(angle,0,1,1);

		switch(shape){
			case(0):
				glBegin(GL_QUADS);
					glVertex3f(-1,-1,-1);
					glVertex3f(1,-1,-1);
					glVertex3f(1,-1,1);
					glVertex3f(-1,-1,1);

					glVertex3f(-1,1,-1);
					glVertex3f(1,1,-1);
					glVertex3f(1,1,1);
					glVertex3f(-1,1,1);

					glVertex3f(-1,-1,-1);
					glVertex3f(-1,1,-1);
					glVertex3f(-1,1,1);
					glVertex3f(-1,-1,1);

					glVertex3f(1,-1,-1);
					glVertex3f(1,1,-1);
					glVertex3f(1,1,1);
					glVertex3f(1,-1,1);

					glVertex3f(-1,-1,-1);
					glVertex3f(1,-1,-1);
					glVertex3f(1,1,-1);
					glVertex3f(-1,1,-1);

					glVertex3f(-1,-1,1);
					glVertex3f(1,-1,1);
					glVertex3f(1,1,1);
					glVertex3f(-1,1,1);
				glEnd();
				break;
			case(1):
				glBegin(GL_TRIANGLES);
					glVertex3f(-1,-1,-1);
					glVertex3f(0,-1,1);
					glVertex3f(1,-1,-1);

					glVertex3f(-1,-1,-1);
					glVertex3f(0,1,0);
					glVertex3f(0,-1,1);

					glVertex3f(1,-1,-1);
					glVertex3f(0,1,0);
					glVertex3f(0,-1,1);

					glVertex3f(-1,-1,-1);
					glVertex3f(0,1,0);
					glVertex3f(1,-1,-1);
				glEnd();
				break;
			default:
				gluSphere(sphere,1,10,10);
				break;
		}

		swapBuffers();
	}

	bool initialized;

	float angle;
	int shape;
	GLUquadricObj *sphere;
};

class OpenGLShapes : public Window {
public:
	OpenGLShapes() {
		setCaption( "OpenGLShapes" );

		setWidth( 500 );
		setHeight( 500 );

		Panel *topPanel=new Panel();
		topPanel->setHeight(40);
		add(topPanel,AlignTop);

		CommandButton *cube=new CommandButton();
		EventHandler* cubeButton=new ButtonEventHandler<OpenGLShapes>(this,OpenGLShapes::cube,"cube");
		cube->addButtonClickHandler(cubeButton);
		cube->setCaption("Cube");
		cube->setWidth(100);
		topPanel->add(cube,AlignRight);

		CommandButton *tetrahedron=new CommandButton();
		EventHandler* tetrahedronButton=new ButtonEventHandler<OpenGLShapes>(this,OpenGLShapes::tetrahedron,"tetrahedron");
		tetrahedron->addButtonClickHandler(tetrahedronButton);
		tetrahedron->setCaption("Tetrahedron");
		tetrahedron->setWidth(100);
		topPanel->add(tetrahedron,AlignClient);

		CommandButton *sphere=new CommandButton();
		EventHandler* sphereButton=new ButtonEventHandler<OpenGLShapes>(this,OpenGLShapes::sphere,"sphere");
		sphere->addButtonClickHandler(sphereButton);
		sphere->setCaption("Sphere");
		sphere->setWidth(100);
		topPanel->add(sphere,AlignLeft);

		mControl=new OpenGLShapesControl();
		add(mControl,AlignClient);
	}

	void cube(ButtonEvent *e){
		mControl->shape=0;
	}

	void tetrahedron(ButtonEvent *e){
		mControl->shape=1;
	}

	void sphere(ButtonEvent *e){
		mControl->shape=2;
	}

	virtual ~OpenGLShapes(){};

	OpenGLShapesControl *mControl;
};

class OpenGLShapesApplication : public Application {
public:

	OpenGLShapesApplication( int argc, char** argv ) : Application(argc, argv) {
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new OpenGLShapes();
		setMainWindow(mainWindow);
		mainWindow->show();

		return result;
	}

};

int main(int argc, char *argv[]) {
	Application* app = new OpenGLShapesApplication( argc, argv );

	Application::main();

	return 0;
}

