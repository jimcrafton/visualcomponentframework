//HelloWorld3.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
*The purpose of this example is to demonstrate creating not only
*our own custom application class, but our first case of deriving
*a new window class
*/

#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


/**
*This is our main window class. The code that was previously
*in the initialization method of our app class, but will now
*migrate to our constructor
*/
class HelloWorld3Window : public Window {
public:
	HelloWorld3Window() {
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
		*Here we can use the debug trace with variable
		*arguments just like printf(), in this
		*case printing out the value of our "this" pointer
		*and the string value returned by the Rect's toString()
		*method
		*/
		StringUtils::traceWithArgs( Format("HelloWorld3Window constructor @%p, bounds: %s\n")
									% this % bounds.toString().c_str() );

		/**
		*Show the main window. Previously we had used
		*the show(), but setVisible(true) also works
		*/
		setVisible( true );

		Locale loc(Locale::lcPolish, Locale::ccPoland );
		System::setCurrentThreadLocale( &loc );

	}

	/**
	*Always, always, always make our destructor virtual
	*/
	virtual ~HelloWorld3Window(){};


	virtual void paint( GraphicsContext* c ) {
		Window::paint( c );

		Locale loc(Locale::lcPolish, Locale::ccPoland );
		c->getCurrentFont()->setName( "Arial" );
		c->textAt( 20, 20, loc.translate( "Hello" ) );
	}
};




class HelloWorld3Application : public Application {
public:

	HelloWorld3Application( int argc, char** argv ): Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		/**
		*allocate some dummy temporary memory - we
		*will clean this up in the termination method of our
		*app class
		*/
		m_tmpDummyBuffer = new char[4096];

		/**
		*Create a new instance of our window class
		*/
		Window* mainWindow = new HelloWorld3Window();


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
		delete [] m_tmpDummyBuffer;
		m_tmpDummyBuffer = NULL;

		/**
		*here's an example of outputting to
		*debug messages. In Win32 these get
		*resolved to a call to OutputDebugString
		*thus if you're debugging with VC++ you'll
		*see this in the Output window.
		*/
		StringUtils::trace( "HelloWorld3Application::terminateRunningApplication() cleaned up memory\n" );
		Application::terminateRunningApplication();
	}


	char* m_tmpDummyBuffer;
};


int main(int argc, char *argv[])
{
	Application* app = new HelloWorld3Application( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:38  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.4.1  2005/04/17 15:11:45  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.4  2004/08/07 02:47:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.5  2004/04/29 03:40:54  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


