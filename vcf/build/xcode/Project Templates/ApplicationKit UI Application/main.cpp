/**
Application ÇPROJECTNAMEÈ
This is a simple application built by XCode for you to use as a starting point in 
creating VCF based apps on OSX.
*/

//main.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


/**
*This is our main window class.
*/
class ÇPROJECTNAMEASIDENTIFIERÈWindow : public Window {
public:
	ÇPROJECTNAMEASIDENTIFIERÈWindow() {
		/**
		*Here we get the current running Application instance for
		*this process
		*/
		Application* runningApp = Application::getRunningInstance();

		/**
		*This gets the app instance's class name to put in the
		*caption of our man window
		*/
		String appname = runningApp->getClassName();

		/**
		*this sets the caption of the main window
		*/
		setCaption( appname + " - Hello World!" );

		/*
		*This will set the bounds of the window, see the
		*previous HelloWorld example for a more in depth
		*discussion of this.
		*/
		Rect bounds( 100.0, 100.0, 500.0, 500.0 );
		setBounds( &bounds );

		/**
		*Show the main window. Previously we had used
		*the show(), but setVisible(true) also works
		*/
		show();
	}

	virtual ~ÇPROJECTNAMEASIDENTIFIERÈWindow(){};


	virtual void paint( GraphicsContext* c ) {
		Window::paint( c );
		
		//your custom paint handling here
	}
};




class ÇPROJECTNAMEASIDENTIFIERÈApplication : public Application {
public:

	ÇPROJECTNAMEASIDENTIFIERÈApplication( int argc, char** argv ): Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		/**
		*Create a new instance of our ÇPROJECTNAMEÈWindow window class
		*/
		Window* mainWindow = new ÇPROJECTNAMEASIDENTIFIERÈWindow();


		/**
		*set the app's main window
		*/
		setMainWindow(mainWindow);

		return result;
	}

	/**
	*terminates the running application. This is where
	*you can do your clean up of resources
	*In our case we'll clean up the memory we had allocated in our
	*initRunningApplication() method above
	*and then call the super classes terminateRunningApplication()
	*/
	virtual void terminateRunningApplication() {
		Application::terminateRunningApplication();
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ÇPROJECTNAMEASIDENTIFIERÈApplication( argc, argv );

	Application::main();

	return 0;
}

