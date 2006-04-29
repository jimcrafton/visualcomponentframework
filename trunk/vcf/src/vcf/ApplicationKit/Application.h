#ifndef _VCF_APPLICATION_H__
#define _VCF_APPLICATION_H__
//Application.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Window;

class WindowEvent;

class Library;

/**
\class Application Application.h "vcf/ApplicationKit/Application.h"
Represents the main process for a application.
Each application contains a main window, pointed to by  mainWindow_.
Application are started by some entry point of the executing process.
Once the entry point has been called, usually main(),
the static function Application::appMain() is called to start
the application initializing itself.
While the Application instance is optional, if it is present
there should only be one instance that is created on the stack.
 
 Typically the startup code looks like this:
 *\code
 int main( int argc, char** argv ) {
		Application theApp(argc, argv);

		Application::main();

		return 0;
  }
 *\endcode
 *
 *@version 1.0
 *@author Jim Crafton
 @delegates
	@del Application::nativeOSEventReceived
 */

class APPLICATIONKIT_API Application : public AbstractApplication {
public:
	/**
	Every derived class \b must at least take argc, and argv
	arguments to it's constructor. These in turn get passed to
	the ApplicationKit and it's underlying platform implementation
	in order to properly initialize them.
	These arguments can be retrieved in the form of the
	CommandLine instance that is part of the FoundationKit. For
	example:
	\code
	CommandLine cmdLine =  FoundationKit::getCommandLine();
	//get the first argument
	cmdLine.getArgument(0);
	\endcode

	@see CommandLine
	*/
	Application( int argc, char** argv );

	virtual ~Application();

	/**
	*The entry point into the application object starting up.
	*/
	static void main();

	/**
	*returns the singleton instance of the current
	*application for this process. May be null if the
	*VCF is being used without Application support.
	*@return Application the single instance for this process. Do not assume
	*it will be non NULL.
	*/
	static Application* getRunningInstance();

	/**
	*starts the application event loop running
	*/
	void run();

	/**
	*This happens after the Application object is constructed, after the initialize() method,
	*and just before the app's run() method is called
	*successful. if false, it calls terminate() and then kills the app process.
	*this method also builds the accellerator table used for keyboard shortcuts
	*@return bool this tells whether or not the initialization of the application was
	*/
	virtual bool initRunningApplication();

	/**
	*terminates the running application
	*/
	virtual void terminateRunningApplication();

	/**
	*gets the main window of the application. All applications have a main window of some
	*sort. This can a be a tool type window, a dialog, or just a regular window. When this
	*window is closed, the application begins it's shutdown priocess
	*@return Window* the main window
	*/
	Window* getMainWindow();

	/**
	*sets the main window for the application
	*/
	void setMainWindow( Window* mainWindow );

	/**
	*event handler for the main window closing down.
	*/
	void onMainWindowClose( WindowEvent* event );

	/**
	*load a VPL, calls the initPackage() function, and adds the library
	*to it's list. The library will be unloaded when the app quits.
	*/
	void loadVPL( const String& vplFileName );

	virtual bool loadState();

	virtual bool saveState();

	virtual bool loadFrameState( Frame* frame );

	virtual bool saveFrameState( Frame* frame );

	void setAutoLoadSaveAppState( const bool& autoLoadSaveState );

	/**
	This gets called by the internals of the framework 
	in response standard OS events. You can customize how
	or what help contents are loaded by overriding this function.
	@return bool returns true if this function handles
	the help message. Otherwise it returns false, in which
	case the framework handles the rest. The default behaviour
	is to return false.
	*/
	virtual bool displayHelpContents();

	/**
	This gets called by the internals of the framework 
	in response standard OS events. You can customize how
	or what help index is loaded by overriding this function.
	@return bool returns true if this function handles
	the help message. Otherwise it returns false, in which
	case the framework handles the rest. The default behaviour
	is to return false.
	*/
	virtual bool displayHelpIndex();

	/**
	returns the values for the help book and the directory it's 
	located in. The default returns empty strings for both values.
	*/
	virtual void getHelpInfo( String& helpBookName, String& helpDirectory );

	//Event handlers

	/**
	Use this delegate to attach an event handler for native OS Events
	@delegate ToolTip fires an ControlEvent.
	@event Event
	*/
	Delegate nativeOSEventReceived;

	/**
	default implamentation simply passes the event to the Delegate to be passed off to
	any other EventHandlers. To prevent this from happening, do NOT call the base class's
	onOSNativeEvent()
	@param Event this instance has in it's UserData a pointer to a wrapper struct. For Win32
	systems please see the Win32Toolkit.h and look at the Win32MSG class. This will wrap
	up a MSG struct that you can use.
	
	Example (this is pertinent ONLY to Win32 systems):
	\code
		void MyApp::onOSNativeEvent( Event* e )
		{
			//comment the next line out if you want to prevent the
			//delegate from notifying event handlers
			Application::onOSNativeEvent(e);

			Win32MSG* msg = (Win32MSG*)e->getUserData();

			switch( msg->msg_.message ) {
				//do whatever here
			}
		}
	\endcode
	*/
	virtual void onOSNativeEvent( Event* nativeOSEvent ) {
		nativeOSEventReceived.fireEvent( nativeOSEvent );
	}
protected:
	static Application* appInstance_;
	std::map<String,Library*> VPLMap_;
	bool autoLoadSaveAppState_;
	void init();

	void internal_terminate();
private:
    Window * mainWindow_;
};

};


#endif // _VCF_APPLICATION_H__

/**
$Id$
*/
