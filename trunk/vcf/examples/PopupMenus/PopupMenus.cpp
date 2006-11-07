//PopupMenus.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"

using namespace VCF;


class PopupMenusWindow : public Window {
public:
	PopupMenusWindow() {
		setCaption( "PopupMenus" );		

		CommandButton* cb = new CommandButton();
		cb->setBounds( 20, 20, 100, 30 );
		add( cb );

		cb->ButtonClicked += new GenericEventHandler<PopupMenusWindow>(this, &PopupMenusWindow::btnClick, "btnClick" );

		EventHandler* eh = new GenericEventHandler<PopupMenusWindow>(this, &PopupMenusWindow::onMenuItemClicked, "onMenuItemClicked" );


		PopupMenu* popupMenu = new PopupMenu( this );
		MenuItem* root = popupMenu->getRootMenuItem();

		setPopupMenu( popupMenu );

		for (int i=1;i<=10;i++ ) {
			MenuItem* item = 
				new DefaultMenuItem( Format("Context Menu Item %d") % i, root,popupMenu );
			item->MenuItemClicked += getEventHandler( "onMenuItemClicked" );
		}

	}

	virtual ~PopupMenusWindow(){};

	void btnClick( Event* e ) {
		PopupMenu* popupMenu = new PopupMenu( this );

		MenuItem* root = popupMenu->getRootMenuItem();

		
		for (int i=1;i<=10;i++ ) {
			MenuItem* item = 
				new DefaultMenuItem( Format("Menu Item %d") % i, root,popupMenu );
			item->MenuItemClicked += getEventHandler( "onMenuItemClicked" );
		}

		Point pt(20, 50);
		popupMenu->popup( &pt );

		removeComponent( popupMenu );
		popupMenu->free();
	}
	
	void onMenuItemClicked( Event* e ) {
		MenuItem* item = (MenuItem*)e->getSource();
		Dialog::showMessage( Format("Menu item \"%s\" clicked!") % item->getCaption() );
	}
};




class PopupMenusApplication : public Application {
public:

	PopupMenusApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new PopupMenusWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new PopupMenusApplication( argc, argv );

	Application::main();
	
	return 0;
}


