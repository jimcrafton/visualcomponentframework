//$$root$$.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;



class $$Root$$Window : public Window {
public:
	$$Root$$Window() {}
	virtual ~$$Root$$Window(){};
};

_class_rtti_($$Root$$Window, "VCF::Window", "$$Root$$Window")
_class_rtti_end_





class $$Root$$Application : public Application {
public:

	$$Root$$Application( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL($$Root$$Window);

		Window* mainWindow = Frame::createWindow( classid($$Root$$Window) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<$$Root$$Application>(argc,argv);
}


