//MinMax.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


class MinMaxWindow : public Window {
public:
	MinMaxWindow() {
		setCaption( "MinMax" );

		setMinWidth( 300 );
		setMinHeight( 200 );
		setMaxWidth( 400 );
		setMaxHeight( 600 );
	}

	virtual ~MinMaxWindow(){};

};




class MinMaxApplication : public Application {
public:

	MinMaxApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new MinMaxWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new MinMaxApplication( argc, argv );

	Application::main();
	
	return 0;
}


