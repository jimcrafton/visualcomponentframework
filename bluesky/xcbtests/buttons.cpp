#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;

class HelloWorld2Application : public Application {
public:

	HelloWorld2Application( int argc, char** argv ): Application(argc, argv) {}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new Window();
		setMainWindow( mainWindow );

		CommandButton* btn = new CommandButton();
		
		mainWindow->add( btn );
		
		btn->setBounds( 10, 10, 100, 35 );

		Rect mainWindowBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->setBounds( &mainWindowBounds );
		mainWindow->setCaption( "Hello World 2" );
		mainWindow->show();

		return result;
	}
};


int main(int argc, char *argv[])
{
	Application* app = new HelloWorld2Application( argc, argv );
	Application::main();
	return 0;
}


/**
$Id: buttons.cpp $
*/
