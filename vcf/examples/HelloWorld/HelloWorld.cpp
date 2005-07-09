//HelloWorld.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
*A hello world application
*This demonstrates the simplest
*code possible to create a running app
*and display a window with the text
*"Hello World" in it's caption bar.
*/


/**
*include the ApplicationKit.h
*this has all the core files you'll need to get started.
*In general, you'll probably want to make this
*the first header you include within your .cpp files
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


/**
*use the VCF namespace to make it more convenient
*to refer to VCF classes
*/
using namespace VCF;


class HelloWorldApp : public Application {
public:
	HelloWorldApp( int argc, char** argv ): Application(argc, argv) {

	}

	virtual bool initRunningApplication() {
		Application::initRunningApplication();

		/**
		*create the main Window here.
		*Note that is on the heap, not the stack.
		*The application will clean it up for you,
		*so do NOT make this a stack based object
		*/
		Window* mainWindow = new Window();

		/**
		*set the Application's main window.
		*Failure to do this will prevent the Application
		*of being notified to close correctly, and it will not
		*be able to free up the heap based memory for the
		*Window object.
		*In the VCF there is always a main window for GUI based
		*applications, which can be a Dialog or a Window object.
		*When this main window closes, the app shuts down as well.
		*/
		setMainWindow( mainWindow );


		/**
		*Set the caption of the main window. Setting the caption
		*cause the text passed in to the method to appear on
		*the window frame's caption bar.
		*/
		mainWindow->setCaption( "Hello World" );

        mainWindow->setBounds( 100, 100, 500, 500 );

		/**
		*show the main window.
		*By default the window is invisible until
		*either show() or setVisible(true) is called.
		*We could have called mainWindow->setVisible(true)
		*and it would have worked as well.
		*/
		mainWindow->show();

		return true;
	}

};


/**
here's the heart of the program, in good old main.
yes this will work on Windows without displaying any
console
*/
int main(int argc, char *argv[])
{
	/**
	create an instance of the HelloWorldApp class
	on the heap - DO NOT create it on the stack or
	you will get a crash whn you close you application.
	This will be the only instance of this class in the process.
	*/
	Application* app = new HelloWorldApp( argc, argv );

	/**
	hand off the command line to the static appMain() call
	which in turn begins the main application loop.
	*/

	Application::main();

	return 0;


}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:38  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.4.1  2005/03/06 22:50:53  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.4  2004/08/07 02:47:04  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.11  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.3.2.10.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*Revision 1.3.2.10.2.2  2004/07/09 02:01:24  ddiego
*more osx updates
*
*Revision 1.3.2.10.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.3.2.10  2004/06/07 03:07:06  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.3.2.9  2004/06/06 07:05:27  marcelloptr
*changed macros, text reformatting, copyright sections
*

*Revision 1.3.2.7  2004/05/31 22:24:52  ddiego
*OSX code for handling focus events
*
*Revision 1.3.2.6  2004/05/15 17:59:36  marcelloptr
*minor project changes
*
*Revision 1.3.2.5  2004/05/06 03:03:43  ddiego
*checking in OSX updates
*
*Revision 1.3.2.4  2004/04/29 03:40:54  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


