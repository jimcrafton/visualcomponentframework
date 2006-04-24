//[!output PROJECT_NAME]Application.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "[!output PROJECT_NAME]Application.h"
#include "MainWindow.h"

[!if SPLASH_SCREEN]
#include "SplashScreen.h"
[!endif]

using namespace VCF;

[!output PROJECT_NAME]Application::[!output PROJECT_NAME]Application( int argc, char** argv ) : 
	Application(argc, argv)
{
	
}

[!output PROJECT_NAME]Application::~[!output PROJECT_NAME]Application()
{
	
}

bool [!output PROJECT_NAME]Application::initRunningApplication(){
	bool result = Application::initRunningApplication();
[!if SPLASH_SCREEN]
	SplashScreen* splash = new SplashScreen();
[!endif]
	MainWindow* mainWindow = new MainWindow();
	
	setMainWindow(mainWindow);
	mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
	mainWindow->setVisible( true );
	mainWindow->setCaption( "[!output PROJECT_NAME]" );
	
	return result;
}


