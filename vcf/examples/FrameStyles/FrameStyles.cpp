//FrameStyles.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;

/**
This is a simple example that illustrates how to control the
frame style of a Frame instance.
*/

class FrameStylesWindow : public Window {
public:
	FrameStylesWindow() {
		setCaption( "FrameStyles" );
		setVisible( true );


		/**
		Add a series of menus to allow the user to dynamically set the
		main window's frame style.
		*/
		MenuBar* menu = new MenuBar(this);

		setMenuBar( menu );

		MenuItem* main = new DefaultMenuItem( "FrameStyles", menu->getRootMenuItem(), menu );

		MenuItem* frameStyle = new DefaultMenuItem( "Set Frame Style to", main, menu );

		EventHandler* ev = new MenuItemEventHandler<FrameStylesWindow>(this, &FrameStylesWindow::onSetFrameStyle, "FrameStylesWindow::onSetFrameStyle" );
		MenuItem* sizeable = new DefaultMenuItem( "fstSizeable", frameStyle, menu );
		sizeable->MenuItemClicked += ev;
		sizeable->setTag( 0 );


		MenuItem* noBorder = new DefaultMenuItem( "fstNoBorder", frameStyle, menu );
		noBorder->MenuItemClicked += ev;
		noBorder->setTag( 1 );

		MenuItem* fixed = new DefaultMenuItem( "fstFixed", frameStyle, menu );
		fixed->MenuItemClicked += ev;
		fixed->setTag( 2 );

		MenuItem* noBorderFixed = new DefaultMenuItem( "fstNoBorderFixed", frameStyle, menu );
		noBorderFixed->MenuItemClicked += ev;
		noBorderFixed->setTag( 3 );

		MenuItem* toolbarBorder = new DefaultMenuItem( "fstToolbarBorder", frameStyle, menu );
		toolbarBorder->MenuItemClicked += ev;
		toolbarBorder->setTag( 4 );

		MenuItem* toolbarBorderFixed = new DefaultMenuItem( "fstToolbarBorderFixed", frameStyle, menu );
		toolbarBorderFixed->MenuItemClicked += ev;
		toolbarBorderFixed->setTag( 5 );
	}

	virtual ~FrameStylesWindow(){};


	void onSetFrameStyle( MenuItemEvent* e ) {
		MenuItem* item = (MenuItem*)e->getSource();
		
		//check the menu item tag, and set the frame style 
		//accordingly
		switch ( item->getTag() ) {
			case 0 : {
				setFrameStyle(fstSizeable) ;
			}
			break;

			case 1 : {
				setFrameStyle(fstNoBorder) ;
			}
			break;

			case 2 : {
				setFrameStyle(fstFixed) ;
			}
			break;

			case 3 : {
				setFrameStyle(fstNoBorderFixed) ;
			}
			break;

			case 4 : {
				setFrameStyle(fstToolbarBorder) ;
			}
			break;

			case 5 : {
				setFrameStyle(fstToolbarBorderFixed) ;
			}
			break;
		}
	}

};




class FrameStylesApplication : public Application {
public:

	FrameStylesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new FrameStylesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new FrameStylesApplication( argc, argv );

	Application::main();
	
	return 0;
}


