//ViewMaker.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "ViewManager.h"

using namespace VCF;








class ViewMakerWindow : public Window {
public:
	ViewMakerWindow() {
		setCaption( "ViewMaker" );
		setVisible( true );

		ViewManagerPanel* p = new ViewManagerPanel();		
		add( p );

		DockablePanel* p1 = new DockablePanel();
		p1->setViewManager( p );
		p->add( p1, AlignClient );

		DockablePanel* p2 = new DockablePanel();
		p2->setHeight( 100 );
		p2->setViewManager( p );
		p->add( p2, AlignBottom );

		DockablePanel* p3 = new DockablePanel();
		p3->setWidth( 100 );
		p3->setViewManager( p );
		p->add( p3, AlignLeft );


		p3->add( new Panel(), AlignClient );

	}

	virtual ~ViewMakerWindow(){};

};




class ViewMakerApplication : public Application {
public:

	ViewMakerApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ViewMakerWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ViewMakerApplication( argc, argv );

	Application::main();
	
	return 0;
}


