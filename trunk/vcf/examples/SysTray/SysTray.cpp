//SysTray.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SystemTray.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"

/**
This is a simple example that demonstrates how to use the SystemTray component
*/

using namespace VCF;



class SysTrayWindow : public Window {
public:
	SysTrayWindow() {
		setCaption( "SysTray" );
		setVisible( true );

		/**
		Create a new system tray. Passing a pointer to the
		"owner" (in this case the window itself) will automatically
		cause the new child component, the system tray, to be added
		to it's owner. When the owner is destroy, so will any children
		of the owner.
		*/
		SystemTray* tray = new SystemTray(this);

		/**
		Make the tray icon area visible
		*/
		tray->showInTray();


		/**
		Create a new image on the fly, and add it to the tray
		*/
		Image* img = GraphicsToolkit::createImage( 32, 32 );
		img->beginDrawing();
		GraphicsContext* gc = img->getImageContext();
		gc->rectangle( 0, 0, 32, 32 );
		gc->setColor( Color::getColor( "red" ) );
		gc->fillPath();

		gc->circle( 16,16, 5 );
		gc->circle( 10,10, 5 );
		gc->circle( 20,15, 5 );

		gc->setColor( Color::getColor( "blue" ) );
		gc->fillPath();



		img->finishedDrawing();
		
		/**
		Make the image transparent
		*/

		img->setIsTransparent( true );
		/**
		Sets the transparency color
		*/
		img->setTransparencyColor( Color::getColor( "red" ) );

		/**
		Set the image for the tray's icon.
		*/
		tray->setIconImage( img );


		/**
		We are done with the image so delete it!
		*/
		delete img;

		/**
		Set the tooltip popup for the system tray icon
		*/
		tray->setTooltipText( "Hello There!" );
		

		

		/**
		Create a popup menu with three items and attach event 
		handlers to them
		*/

		PopupMenu* pm = new PopupMenu(this);
		DefaultMenuItem* root = new DefaultMenuItem( "root", NULL, pm );

		DefaultMenuItem* hello = new DefaultMenuItem( "Hello!", root, pm );
		hello->MenuItemClicked += new GenericEventHandler<SysTrayWindow>(this,&SysTrayWindow::onHello,"SysTrayWindow::onHello");

		DefaultMenuItem* about = new DefaultMenuItem( "About...", root, pm );
		about->MenuItemClicked += new GenericEventHandler<SysTrayWindow>(this,&SysTrayWindow::onAbout,"SysTrayWindow::onAbout");

		DefaultMenuItem* quit = new DefaultMenuItem( "Quit", root, pm );
		quit->MenuItemClicked += new GenericEventHandler<SysTrayWindow>(this,&SysTrayWindow::onQuit,"SysTrayWindow::onQuit");


		/**
		Set the root item for the popupmenu
		*/
		pm->setRootMenuItem( root );

		/**
		Set the tray icon's popup menu
		*/
		tray->setPopupMenu( pm );
	}

	virtual ~SysTrayWindow(){};

	void onHello( Event* e ) {
		Dialog::showMessage( "Hello There!" );
	}

	void onQuit( Event* e ) {
		close();
	}

	void onAbout( Event* e ) {
		Dialog::showMessage( "Simple application that demonstrates\nhow to use the system tray." );
	}

};




class SysTrayApplication : public Application {
public:

	SysTrayApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new SysTrayWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new SysTrayApplication( argc, argv );

	Application::main();
	
	return 0;
}


