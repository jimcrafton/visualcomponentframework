//HtmlMVC.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/HTMLKit/HTMLKit.h"


using namespace VCF;



class HtmlMVCWindow : public Window {
public:
	HtmlMVCWindow() {}
	virtual ~HtmlMVCWindow(){};
};

_class_rtti_(HtmlMVCWindow, "VCF::Window", "HtmlMVCWindow")
_class_rtti_end_





class HtmlMVCApplication : public Application {
public:

	HtmlMVCApplication( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(HtmlMVCWindow);

		Window* mainWindow = Frame::createWindow( classid(HtmlMVCWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<HtmlMVCApplication>(argc,argv);
}


