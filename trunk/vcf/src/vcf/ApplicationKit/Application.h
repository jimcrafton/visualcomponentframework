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
Represents the main process for a application.
Each application contains a main window, pointed to by  mainWindow_.
Application are started by some entry point of the executing process.
Once the entry point has been called, usually main(),
the static function Application::appMain() is called to start
the application initializing itself.
While the Application instance is optional, if it is present
there should only be one instance that is created on the stack.
 \par
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
	\par
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.19.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.19  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.5  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.18.2.4  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.18.2.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.18.2.2  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.18.2.1  2003/08/13 02:18:31  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.18  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.17.2.1  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.17  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.1  2003/03/12 03:09:15  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.20.5  2003/01/08 04:25:34  marcelloptr
*ColorNames static map and Color::s_ now use String instead than String* - VCF_LARGE_COLOR_LIST introduced
*
*Revision 1.15.20.4  2003/01/08 00:19:42  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.15.20.3  2002/12/30 00:24:12  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.15.20.2  2002/12/28 21:50:46  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.15.20.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.15  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.14  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.13  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_APPLICATION_H__


