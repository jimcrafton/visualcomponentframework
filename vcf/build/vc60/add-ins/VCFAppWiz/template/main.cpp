//$$root$$.cpp


#include "ApplicationKit.h"


using namespace VCF;


class $$Root$$Window : public Window {
public:
	$$Root$$Window() {
		setCaption( "$$Root$$" );
		setVisible( true );
	}

	virtual ~$$Root$$Window(){};

};




class $$Root$$Application : public Application {
public:

	$$Root$$Application( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new $$Root$$Window();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	$$Root$$Application app( argc, argv );

	Application::main();
	
	return 0;
}


