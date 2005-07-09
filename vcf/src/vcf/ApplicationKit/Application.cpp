//Application.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"
#include "vcf/ApplicationKit/ApplicationResourceBundle.h"

using namespace VCF;


Application* Application::appInstance_ = NULL;


void initLoadedLibraryApplications()
{
	//enumerate through all the loaded LibraryApplications
	Enumerator<VCF::LibraryApplication*>* libaries = LibraryApplication::getRegisteredLibraries();
	bool libraryInitializationFailed = false;
	String failedLib;
	while ( (true == libaries->hasMoreElements()) && (!libraryInitializationFailed) ) {
		VCF::LibraryApplication* libraryApp = libaries->nextElement();
		libraryInitializationFailed = !libraryApp->initRunningApplication();
		if ( libraryInitializationFailed ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("Error initializing " + libraryApp->getName() ) );
		}
	}
}

void terminateLoadedLibraryApplications()
{
	Enumerator<VCF::LibraryApplication*>* libaries = LibraryApplication::getRegisteredLibraries();
	bool libraryInitializationFailed = false;
	String failedLib;
	while ( (true == libaries->hasMoreElements()) && (!libraryInitializationFailed) ) {
		VCF::LibraryApplication* libraryApp = libaries->nextElement();
		libraryApp->terminateRunningApplication();
	}
}


/*
class AppTerm {
public:
	AppTerm(){}

	~AppTerm() {

	}
};

static AppTerm appTerm;
*/


Application::Application( int argc, char** argv ):
	mainWindow_(NULL),
	autoLoadSaveAppState_(false)
{
	Application::appInstance_ = this;

	//initialize the ApplicationKit!!!
	ApplicationKit::init( argc, argv );

	//gets added automatically to the app list of event handlers
	WindowEventHandler<Application>* wh =
		new WindowEventHandler<Application>( this,&Application::onMainWindowClose, "AppWindowHandler" );

	//install a new resource bundle
	//this new resource bundle is aware of the 
	//application resource handle, which may be different if the app is the 
	//main app instance (like it is here), or if it's a library application
	System::internal_replaceResourceBundleInstance( new ApplicationResourceBundle(this) );
}

Application::~Application()
{

}

void Application::internal_terminate()
{
	applicationPeer_->terminateApp();

	std::map<String,Library*>::iterator it = VPLMap_.begin();
	while ( it != VPLMap_.end() ){
		Library* lib = it->second;
		lib->free();
		lib = NULL;
		it++;
	}


	delete applicationPeer_;

	Application::appInstance_ = NULL;
}

void Application::init()
{


	applicationPeer_ = UIToolkit::createApplicationPeer();

	if ( NULL == applicationPeer_ )
	{
		throw InvalidPointerException( MAKE_ERROR_MSG_2("Application peer is NULL - UIToolkit::createApplicationPeer() implementation not implemented correctly") );
	}

	applicationPeer_->setApplication( this );

#if defined( WIN32 ) && defined ( _MSC_VER )
	//load the BlacBox error trapper
	try {
		//at the moment this is only meaningful on Win32 platforms
		Library lib( L"BlackBox.dll" );
	}
	catch (...) {
		StringUtils::trace( "Unable to load the BlackBox error detection library\n" );
	}
#endif
}

void Application::main()
{
	// this is used in order to break in the right place when an exception is thrown. - MP -
	Window* mainWindow = NULL;

	//main try...catch
	try {
		if ( NULL == Application::getRunningInstance() ){
			//throw exception
		}
		else{//enter the main loop

			Application* runningInstance = Application::getRunningInstance();
			if ( runningInstance->applicationName_.empty() ) {
				runningInstance->applicationName_ = runningInstance->getClassName();
			}

			//init the running instance
			runningInstance->init();

			/**
			*initialize the implementer first - we are not going to rely
			*on someone remembering to call the base class functionality of the Application
			*if the Peer returns false then bomb out and terminate
			*/
			ApplicationPeer* appPeer = runningInstance->getPeer();
			if ( NULL == appPeer ){
				//throw exception - this is very BADDDDD
				throw InvalidPointerException( MAKE_ERROR_MSG_2("Application Peer is NULL") );
			}
			if ( true != appPeer->initApp() ){
				//ouch - something bad happened - terminate the app
				appPeer->terminateApp();
			}
			else {
				if ( true != runningInstance->initRunningApplication() ) { //initialization failed

					runningInstance->terminateRunningApplication();

					if ( runningInstance->mainWindow_ != NULL ) {
						StringUtils::trace( "Oops! The Main window has not been freed.\nDid you forget to call the super class's terminateRunningApplication() method?\n" );
					}

					appPeer->terminateApp();
				}
				else{
					mainWindow = runningInstance->mainWindow_;

					bool libsInitialized = false;
					try {
						initLoadedLibraryApplications();
						libsInitialized = true;
					}
					catch ( BasicException& e  ){
						String errString = e.getMessage().c_str();

						Dialog::showMessage( errString, "Exception Initializing Library Applications", Dialog::mbOK, Dialog::msError  );
					}
					catch ( ... ){
						String errString = "unknown error occured attempting to initialize a VCF Library Application";
						Dialog::showMessage( errString, "Exception Initializing Library Applications", Dialog::mbOK, Dialog::msError  );
					}

					if ( libsInitialized ) {

						if ( true == runningInstance->autoLoadSaveAppState_ ) {
							if ( false == runningInstance->loadState() ) {
								//note an error
							}
						}

						runningInstance->run();


					}

					terminateLoadedLibraryApplications();

					/**
					JC - I moved the code to free the main window inside of terminateRunningApplication()
					This requires that people correctly call the application super class's terminateRunningApplication()
					inside of their overide of it.
					*/
					runningInstance->terminateRunningApplication();

					mainWindow = runningInstance->mainWindow_;

					if ( runningInstance->mainWindow_ != NULL ) {
						StringUtils::trace( "Oops! The Main window has not been freed.\nDid you forget to call the super class's terminateRunningApplication() method?\n" );
					}

					runningInstance->internal_terminate();

					runningInstance->free();

					ApplicationKit::terminate();
				}
			}
		}
	}

	catch ( BasicException& e  ){
		String errString = e.getMessage().c_str();

		StringUtils::trace( "Framework Exception: " + errString + "\n" );
		if ( NULL != mainWindow ) {
			Dialog::showMessage( errString, "Framework Exception", Dialog::mbOK, Dialog::msError  );
		}

#ifdef _DEBUG
		throw;
#endif
	}
	catch (FoundationKit::Assertion& e){
		String errString = "Assertion Exception caught.\n\"";
		errString += e.what();
		errString += "\".\nApplication exiting abnormally.";

		StringUtils::trace( "Framework Exception: " + errString + "\n" );
		if ( NULL != mainWindow ) {
			Dialog::showMessage( errString, "Framework Assertion Exception", Dialog::mbOK, Dialog::msError  );
		}

#ifdef _DEBUG
		throw;
#endif
	}
	catch (std::exception& e){
		String errString = "STL C++ exception throw.\nError : \"";
#ifdef VCF_RTTI
		String clasName = typeid(e).name();
#else
		String clasName = "Unknown - RTTI not enabled";
#endif
		errString += " (Exception of type : " + clasName + ")";
		errString += e.what();
		errString += "\".\nApplication exiting abnormally.";

		if ( NULL != mainWindow ) {
			Dialog::showMessage( errString, "Framework Exception", Dialog::mbOK, Dialog::msError  );
		}

#ifdef _DEBUG
		throw;
#endif
	}
	catch (...){
		if ( NULL != mainWindow ) {
			Dialog::showMessage( "Unknown exception occurred. Application exiting abnormally.",
									"Framework Exception", Dialog::mbOK, Dialog::msError  );
		}
//#ifdef _DEBUG
		throw ;
//#endif
	}


}

Application* Application::getRunningInstance()
{
	return Application::appInstance_;
}

Window* Application::getMainWindow()
{
	return mainWindow_;
}

void Application::setMainWindow( Window* mainWindow )
{
	EventHandler* wl = getEventHandler("AppWindowHandler");
	if ( NULL != mainWindow_ ){
		mainWindow_->FrameClose.removeHandler( wl );
	}
	mainWindow_ = mainWindow;
	if ( NULL != mainWindow_ ) {
		mainWindow_->FrameClose.addHandler( wl );
	}
}

bool Application::initRunningApplication()
{
	return true;
}

void Application::onMainWindowClose( WindowEvent* event )
{
	Control* comp = (Control*)event->getSource();


}


void Application::terminateRunningApplication()
{
	if ( true == autoLoadSaveAppState_ ) {
		if ( false == saveState() ) {
			//note an error
		}
	}

	/**
	JC - I moved this code here to guarantee that the main window is
	destroyed during derinved Application class's terminateRunningApplication()
	*/
	if ( NULL != mainWindow_ ){
		mainWindow_->free();
		mainWindow_ = NULL;
	}
}

void Application::run()
{
	//run the event loop from the toolkit

	UIToolkit::runEventLoop();

	//finished with events - app can terminate

}

void Application::loadVPL( const String& vplFileName )
{
	std::map<String,Library*>::iterator found = VPLMap_.find( vplFileName );
	if ( found == VPLMap_.end() ){
		Library* vplLib = new Library();
		try{
			vplLib->load( vplFileName );
			typedef void (*InitFunc)();
			InitFunc initFunc = (InitFunc)vplLib->getFunction("initPackage");
			initFunc();

			VPLMap_[vplFileName] = vplLib;
		}
		catch ( BasicException& ex ){
			Dialog::showMessage( ex.getMessage(), "Framework Exception", Dialog::mbOK, Dialog::msError  );
		}
	}
}

bool Application::loadState()
{
	bool result = true;

	Registry reg;

	reg.setRoot( RKT_CURRENT_USER );
	if ( true == reg.openKey( "Software\\" + getName(), false ) ) {
		if ( NULL != mainWindow_ ) {
			result = loadFrameState( mainWindow_ );
		}
	}
	else {
		result = false;
	}

	return result;
}

bool Application::saveState()
{
	bool result = true;

	Registry reg;
	reg.setRoot( RKT_CURRENT_USER );
	if ( true == reg.openKey( "Software\\" + getName(), true ) ) {
		if ( NULL != mainWindow_ ) {
			result = saveFrameState( mainWindow_ );
		}
	}
	else {
		result = false;
	}

	return result;
}

bool Application::loadFrameState( Frame* frame )
{
	bool result = true;

	Registry reg;

	reg.setRoot( RKT_CURRENT_USER );
	if ( true == reg.openKey( "Software\\" + getName() + "\\Frames", false ) ) {

		char* buf = NULL;
		uint32 bufSize = 0;
		String valName = "MainWindow";

		reg.getDataBufValue( valName, bufSize, (void**)&buf );
		if ( bufSize > 0 ) {
			BasicInputStream bis(buf,bufSize);
			Frame::State state;
			bis >> static_cast<Persistable*>(&state);
			state.applyState( frame );
		}
		else {
			result = false;
		}
	}
	else {
		result = false;
	}
	return result;
}

bool Application::saveFrameState( Frame* frame )
{
	bool result = true;

	Registry reg;

	reg.setRoot( RKT_CURRENT_USER );
	if ( true == reg.openKey( "Software\\" + getName() + "\\Frames", true ) ) {
		BasicOutputStream bos;
		Frame::State state;
		state.initState( frame );
		bos << &state;
		String valName = "MainWindow";
		result = reg.setValue( bos.getBuffer(), bos.getSize(), valName );
	}
	else {
		result = false;
	}

	return result;
}

void Application::setAutoLoadSaveAppState( const bool& autoLoadSaveState )
{
	autoLoadSaveAppState_ = autoLoadSaveState;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:20  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.4  2005/07/04 03:44:18  marcelloptr
*made the error handling block to break in the right place even when the main application's frame is not fully initialized yet.
*
*Revision 1.3.2.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/27 19:54:56  marcelloptr
*Color changes
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:27:13  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.35.2.1  2004/04/11 23:32:32  ddiego
*added a new container for column based layout (useful for
*dialogs where you are laying out a number for form fields
*
*Revision 1.35  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.31.2.4  2004/03/28 00:46:21  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.31.2.3  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.31.2.2  2004/01/25 22:43:07  marcelloptr
*changes related to rethrowing exceptions
*
*Revision 1.31.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.31  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.30.2.4  2003/09/06 19:45:15  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.30.2.3  2003/09/05 21:03:20  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.30.2.2  2003/08/28 21:46:56  ddiego
*added escape reponse...
*
*Revision 1.30.2.1  2003/08/13 02:18:32  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.30  2003/08/09 02:56:44  ddiego
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
*Revision 1.29.2.4  2003/08/06 21:27:49  ddiego
*minor changes
*
*Revision 1.29.2.3  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.29.2.2  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.29.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.29  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.28.2.1  2003/03/12 03:12:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.28  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.27.2.11  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.27.2.10  2003/02/05 01:26:13  notandor
*Fixed a compilation error on VC6SP5
*
*Revision 1.27.2.9  2003/02/03 05:22:54  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.27.2.8  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.27.2.7  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.27.2.6  2002/12/30 00:24:13  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.27.2.5  2002/12/28 21:51:20  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.27.2.4  2002/12/27 23:04:58  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.27.2.3  2002/12/26 04:44:24  ddiego
*odds and ends
*
*Revision 1.27.2.2  2002/12/26 04:32:12  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Revision 1.27.2.1  2002/12/25 22:06:33  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.27  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.26.4.1  2002/10/28 05:40:01  ddiego
*finished basics for adding new forms, adding interface for dealing with resources
*
*Revision 1.26  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.25.4.1  2002/09/10 04:07:50  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.25  2002/06/19 21:48:46  ddiego
**** empty log message ***
*
*Revision 1.24  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.23.4.3  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.23.4.2  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.23.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.23  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.22  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


