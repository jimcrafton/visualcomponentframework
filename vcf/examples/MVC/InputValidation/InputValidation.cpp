//InputValidation.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;




class InputValidationWindow : public Window {
public:
	InputValidationWindow() {}
	virtual ~InputValidationWindow(){};
};

_class_rtti_(InputValidationWindow, "VCF::Window", "InputValidationWindow")
_class_rtti_end_





class InputValidationApplication : public Application {
public:

	InputValidationApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(InputValidationWindow);
		
		

		Window* mainWindow = Frame::createWindow( classid(InputValidationWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<InputValidationApplication>(argc,argv);
}


