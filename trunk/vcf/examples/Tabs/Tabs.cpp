//Tabs.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;

#define TABSWINDOW_CLASSID		"3906b787-436b-44c2-b439-2b4d880b75e6"


class TabsWindow : public Window {
public:
};

_class_rtti_(TabsWindow, "VCF::Window", TABSWINDOW_CLASSID)
_class_rtti_end_




class TabsApplication : public Application {
public:

	TabsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(TabsWindow);

		Window* mainWindow = Frame::createWindow( classid(TabsWindow) );

		setMainWindow(mainWindow);
		mainWindow->show();


		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TabsApplication( argc, argv );

	Application::main();
	
	return 0;
}


