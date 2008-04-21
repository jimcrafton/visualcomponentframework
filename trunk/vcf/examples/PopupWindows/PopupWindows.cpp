//PopupWindows.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/PopupWindow.h"


using namespace VCF;



class PopupWindowsWindow : public Window {
public:
	PopupWindowsWindow() {}
	virtual ~PopupWindowsWindow(){};
};

_class_rtti_(PopupWindowsWindow, "VCF::Window", "PopupWindowsWindow")
_class_rtti_end_





class PopupApp : public Application {
public:

	PopupApp( int argc, char** argv ) : Application(argc, argv) {

		addCallback( new ClassProcedure1<Event*,PopupApp>(this, &PopupApp::onBtn1), "PopupApp::onBtn1" );
	}

	void onBtn1(Event* e) {
		PopupWindow* puw = new PopupWindow( this->getMainWindow() );

		Control* c = (Control*)e->getSource();
		Rect r = c->getBounds();
		c->getParent()->translateToScreenCoords(&r);

		TextControl* tc = new TextControl();
		tc->setBounds( 20, 20, 100, 20 );
		puw->add(tc);
		puw->setBounds( r.left_, r.bottom_, 200, 300 );
		puw->setBorder( new Basic3DBorder(false) );

		puw->showModal();

		puw->free();
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(PopupWindowsWindow);

		Window* mainWindow = Frame::createWindow( classid(PopupWindowsWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<PopupApp>(argc,argv);
}


