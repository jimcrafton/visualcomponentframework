//LOLCats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;

/**
Modeled after Ryan Paul's article at Ars Technica:
http://arstechnica.com/journals/linux.ars/2008/02/04/you-can-has-lolcats-with-ruby-and-gtk
*/

class LOLCatsWindow : public Window {
public:
	LOLCatsWindow() {
				
	}

	virtual ~LOLCatsWindow(){};

};


#define LOLCATSWINDOW_CLASSID		"8d47ad29-296e-4585-a6c0-d7c18a041c83"

_class_rtti_(LOLCatsWindow, "VCF::Window", LOLCATSWINDOW_CLASSID)
_class_rtti_end_






class LOLCatsApplication : public Application {
public:

	LOLCatsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(LOLCatsWindow);

		Window* mainWindow = Frame::createWindow( classid(LOLCatsWindow) );

		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new LOLCatsApplication( argc, argv );

	Application::main();
	
	return 0;
}


