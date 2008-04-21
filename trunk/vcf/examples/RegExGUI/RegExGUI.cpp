//RegExGUI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;



class RegExGUIWindow : public Window {
public:
	RegExGUIWindow() {
		setCaption( "RegExGUI" );		
	}

	virtual ~RegExGUIWindow(){};

};

_class_rtti_(RegExGUIWindow, "VCF::Window", "RegExGUIWindow")
_class_rtti_end_




class RegExGUIApplication : public Application {
public:

	RegExGUIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(RegExGUIWindow);

		Window* mainWindow = Frame::createWindow( classid(RegExGUIWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new RegExGUIApplication( argc, argv );

	Application::main();
	
	return 0;
}


