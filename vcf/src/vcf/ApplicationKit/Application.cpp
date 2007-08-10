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



Application::Application( int argc, char** argv ):
	autoLoadSaveAppState_(false),
	mainWindow_(NULL)
{
	Application::appInstance_ = this;

	//initialize the ApplicationKit!!!
	ApplicationKit::init( argc, argv );

	//gets added automatically to the app list of event handlers
	WindowHandler* wh =
		new ClassProcedure1<WindowEvent*,Application>( this,&Application::onMainWindowClose, "AppWindowHandler" );

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
/*
I am turning this off completely. There is an MS DLL called blackbox, and 
I'd like to revisit this later.
JC
#if defined( VCF_WIN ) && defined ( VCF_MSC )
	//load the BlacBox error trapper
	try {
		//at the moment this is only meaningful on Win32 platforms
		Library lib( L"BlackBox.dll" );
	}
	catch (...) {
		StringUtils::trace( "Unable to load the BlackBox error detection library\n" );
	}
#endif
	*/
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

		StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );
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

		StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );
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
		//if ( NULL != mainWindow ) {
			Dialog::showMessage( "Unknown exception occurred. Application exiting abnormally.",
									"Framework Exception", Dialog::mbOK, Dialog::msError  );
		//}
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
	CallBack* wl = getEventHandler("AppWindowHandler");
	if ( NULL != mainWindow_ && NULL != wl ){		
		mainWindow_->FrameClose.remove( wl );		
	}
	mainWindow_ = mainWindow;
	if ( NULL != mainWindow_ && NULL != wl ){
		mainWindow_->FrameClose.add( wl );
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

bool Application::displayHelpContents()
{
	return false;
}

bool Application::displayHelpIndex()
{
	return false;
}

void Application::getHelpInfo( String& helpBookName, String& helpDirectory )
{
	helpBookName = "";
	helpDirectory = "";
}


/**
$Id$
*/
