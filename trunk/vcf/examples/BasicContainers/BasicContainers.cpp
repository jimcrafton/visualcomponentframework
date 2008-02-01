//BasicContainers.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;


#define BASICCONTAINERS_CLASSID		"dc6f263c-d09b-4ae0-b37d-9c453b4511b3"
class BasicContainers : public Window {
};
_class_rtti_(BasicContainers, "VCF::Window", BASICCONTAINERS_CLASSID)
_class_rtti_end_






class BasicContainersApplication : public Application {
public:

	BasicContainersApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(BasicContainers);

		Window* mainWindow = Frame::createWindow( classid(BasicContainers) );

		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new BasicContainersApplication( argc, argv );

	Application::main();
	
	return 0;
}


