//ApplicationIcons.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

#include "vcf/ApplicationKit/ControlsKit.h"


using namespace VCF;

/**
This is a simple application that demonstrates how to change a
windows icon programmatically.
At this time changing the application icon programmatically is not possible.
Setting the application is platform specific at the moment, and has to handled
as a build detail specific to your OS/windowing system
*/
class ApplicationIconsWindow : public Window {
public:
	ApplicationIconsWindow() {
		

		setCaption( "ApplicationIcons" );
		

		/**
		Create two buttons
		*/
		CommandButton* cmdButton = new CommandButton();
		cmdButton->setBounds( 20, 20, 100, cmdButton->getPreferredHeight() );
		cmdButton->setCaption( "Set icon1" );
		add( cmdButton );

		cmdButton->addButtonClickHandler( new ButtonEventHandler<ApplicationIconsWindow>( this, &ApplicationIconsWindow::setIcon1, "ApplicationIconsWindow::setIcon1" ) );




		cmdButton = new CommandButton();
		cmdButton->setBounds( 120, 20, 100, cmdButton->getPreferredHeight() );
		add( cmdButton );
		cmdButton->addButtonClickHandler( new ButtonEventHandler<ApplicationIconsWindow>( this, &ApplicationIconsWindow::setIcon2, "ApplicationIconsWindow::setIcon2" ) );
		cmdButton->setCaption( "Set icon2" );
	}

	virtual ~ApplicationIconsWindow(){};

	void setIcon1( ButtonEvent* e ) {
		/**
		Retreive an image named "icon1" from teh application's
		resource bundle
		*/
		Image* img = Application::getRunningInstance()->getResourceBundle()->getImage( "icon1" );

		/**
		Set the frame's icon image
		*/
		setIconImage( img );
		delete img;
	}

	void setIcon2( ButtonEvent* e ) {
		Image* img = Application::getRunningInstance()->getResourceBundle()->getImage( "icon2" );
		setIconImage( img );
		delete img;
	}
};




class ApplicationIconsApplication : public Application {
public:

	ApplicationIconsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new ApplicationIconsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		/**
		This sets the icons for the window. This will determine how the icon in
		the Windows Task Manager will appear.
		*/
		Image* img = Application::getRunningInstance()->getResourceBundle()->getImage( "icon1" );
		mainWindow->setIconImage( img );
		delete img;

		mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ApplicationIconsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:13  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.1  2005/07/23 21:45:33  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.4.4.2  2004/12/10 21:30:31  ddiego
*fixed bug 1082362 App Icons do not appear.
*
*Revision 1.4.4.1  2004/12/10 21:12:27  ddiego
*fixed bug 1082362 App Icons do not appear.
*
*Revision 1.4  2004/08/07 02:46:56  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:51  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


