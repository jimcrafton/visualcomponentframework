//TransparentWindows.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TransparentWindow.h"


using namespace VCF;



class TransparentWindowsWindow : public Window {
public:
	TransparentWindowsWindow() {}
	virtual ~TransparentWindowsWindow(){};
};

_class_rtti_(TransparentWindowsWindow, "VCF::Window", "TransparentWindowsWindow")
_class_rtti_end_





class TransWndApp : public Application {
public:

	TransWndApp( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<Event*,TransWndApp>(this, &TransWndApp::onBtn1), "TransWndApp::onBtn1" );
		addCallback( new ClassProcedure1<Event*,TransWndApp>(this, &TransWndApp::onBtn2), "TransWndApp::onBtn2" );
		addCallback( new ClassProcedure1<Event*,TransWndApp>(this, &TransWndApp::onTransWndDblClick), "TransWndApp::onTransWndDblClick" );
		addCallback( new ClassProcedure1<ControlEvent*,TransWndApp>(this, &TransWndApp::afterTransWndPaint), "TransWndApp::afterTransWndPaint" );
		addCallback( new ClassProcedure1<MouseEvent*,TransWndApp>(this, &TransWndApp::onTransWndMouseMove), "TransWndApp::onTransWndMouseMove" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(TransparentWindowsWindow);

		Window* mainWindow = Frame::createWindow( classid(TransparentWindowsWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}



	void onTransWndMouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			pts.push_back( *e->getPoint() );
			((Control*)e->getSource())->repaint();
		}
	}

	void afterTransWndPaint( ControlEvent* e ) {

		e->gc->setColor( Color::getColor("blue") );
		e->gc->setStrokeWidth( 4 );
		e->gc->polyline( pts );
		e->gc->strokePath();
	}

	

	void onTransWndDblClick( Event* e ) {
		Frame* f = (Frame*)e->getSource();
		f->close();
		pts.clear();
	}

	void onBtn1(Event* e) {
		Control* textCtrl = (Control*)getMainWindow()->findComponent( "alphaVal" );
		TransparentWindow* trans = new TransparentWindow( getMainWindow() );

		trans->setBounds( 100, 100, 300, 300 );

		trans->show();
		trans->setAlpha( StringUtils::fromStringAsDouble( textCtrl->getViewModel()->getValueAsString() ) );
		trans->setAllowPaintNotification(true);

		trans->MouseDoubleClicked += getCallback( "TransWndApp::onTransWndDblClick" );
		trans->MouseMove += getCallback( "TransWndApp::onTransWndMouseMove" );
		trans->AfterControlPainted += getCallback( "TransWndApp::afterTransWndPaint" );
	}


	void onBtn2(Event* e) {
		Control* textCtrl = (Control*)getMainWindow()->findComponent( "alphaVal" );
		TransparentWindow* trans = new TransparentWindow( getMainWindow() );

		trans->setBounds( 400, 300, 400, 300 );		
		
		Image* img = this->getResourceBundle()->getImage( "shiny_clock.png" );
		img->setIsTransparent(true);
		img->setTransparencyColor( Color::getColor("white") );
		trans->setAlphaImage( img );

		trans->show();

		trans->MouseDoubleClicked += getCallback( "TransWndApp::onTransWndDblClick" );	

		trans->setAlpha( StringUtils::fromStringAsDouble( textCtrl->getViewModel()->getValueAsString() ) );
	}
		


	std::vector<Point> pts;

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<TransWndApp>(argc,argv);
}


