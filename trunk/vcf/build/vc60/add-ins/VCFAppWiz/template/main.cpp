//$$root$$.cpp


#include "ApplicationKit.h"

using namespace VCF;


class $$Root$$Window : public Window {
public:
	$$Root$$Window() {
		setCaption( "Hello World !!!!" );
		setVisible( true );
	}

	virtual ~$$Root$$Window(){};

};




class $$Root$$Application : public Application {
public:

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* helloWorldWindow = new $$Root$$Window();
		setMainWindow(helloWorldWindow);
		helloWorldWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		return result;
	}

};


int main(int argc, char *argv[])
{
	$$Root$$Application app;

	Application::appMain( argc, argv );
	
	return 0;
}

