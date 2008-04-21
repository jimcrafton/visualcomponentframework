//ShapedWindow.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;



class ShapedWindowWindow : public Window {
public:
	ShapedWindowWindow() {}
	virtual ~ShapedWindowWindow(){};
};

_class_rtti_(ShapedWindowWindow, "VCF::Window", "ShapedWindowWindow")
_class_rtti_end_





class ShapedWindowApplication : public Application {
public:

	ShapedWindowApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ShapedWindowWindow);

		Window* mainWindow = Frame::createWindow( classid(ShapedWindowWindow) );
		setMainWindow(mainWindow);

		VCF::Ellipse e;
		e.ellipse( Rect(0, 0, 320, 300 ) );
		

		mainWindow->setBorderPath( &e );


		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<ShapedWindowApplication>(argc,argv);
}


