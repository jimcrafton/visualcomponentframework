//ScreenDPI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;


class DPITest : public Window {
public:
};

_class_rtti_(DPITest, "VCF::Window", "")
_class_rtti_end_



class ScreenDPIApplication : public Application {
public:

	ScreenDPIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(DPITest);

		Window* mainWindow = Frame::createWindow( classid(DPITest) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ScreenDPIApplication( argc, argv );

	Application::main();
	
	return 0;
}


