//VisualFormFiles.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/VFFInputStream.h"

using namespace VCF;




#define VISUALFORMFILESWINDOW_CLASSID		"6dbafd3f-c8cf-4fc5-9141-43af516db748"
class VisualFormFilesWindow : public Window {
public:
	VisualFormFilesWindow() : label1(NULL) {
		StringUtils::trace( "VisualFormFilesWindow() " + this->toString() + "\n" );

		EventHandler* ev = new ComponentEventHandler<VisualFormFilesWindow>( this, &VisualFormFilesWindow::onLoaded, "VisualFormFilesWindow::onLoaded" );
		ComponentLoaded += ev;
	}

	virtual ~VisualFormFilesWindow(){};

	void onLoaded( ComponentEvent* e ) {
		EventHandler* ev = new MenuItemEventHandler<VisualFormFilesWindow>( this, &VisualFormFilesWindow::onFileOpened, "VisualFormFilesWindow::onFileOpened" );

		fileOpenMenu->addMenuItemClickedHandler( ev );

	}

	void onFileOpened( MenuItemEvent* e ) {

	}

	MenuItem* fileOpenMenu;
	MenuItem* fileOpenMenu1;
	MenuItem* fileOpenMenu2;
	MenuItem* fileOpenMenu3;
	MenuItem* fileOpenMenu4;
	MenuItem* fileOpenMenu5;
	MenuItem* fileOpenMenu6;
	MenuItem* fileOpenMenu7;
	MenuItem* fileOpenMenu8;
	MenuItem* fileOpenMenu9;
	MenuItem* fileOpenMenu10;
	MenuItem* fileOpenMenu11;
	MenuItem* fileOpenMenu12;
	MenuItem* fileOpenMenu13;
	MenuItem* fileOpenMenu14;
	MenuItem* fileOpenMenu15;
	MenuItem* fileOpenMenu16;
	MenuItem* fileOpenMenu17;
	MenuItem* fileOpenMenu18;
	MenuItem* fileOpenMenu19;
	MenuItem* fileOpenMenu20;
	MenuItem* fileOpenMenu21;
	MenuItem* fileOpenMenu22;
	MenuItem* fileOpenMenu23;
	MenuItem* fileOpenMenu24;
	MenuItem* fileOpenMenu25;
	MenuItem* fileOpenMenu26;
	MenuItem* fileOpenMenu27;
	MenuItem* fileOpenMenu28;
	MenuItem* fileOpenMenu29;
	MenuItem* fileOpenMenu30;
	MenuItem* fileOpenMenu31;
	MenuItem* fileOpenMenu32;
	MenuItem* fileOpenMenu33;
	MenuItem* fileOpenMenu34;
	MenuItem* fileOpenMenu35;
	MenuItem* fileOpenMenu36;
	MenuItem* fileOpenMenu37;
	MenuItem* fileOpenMenu38;
	MenuItem* fileOpenMenu39;
	MenuItem* fileOpenMenu40;
	MenuItem* fileOpenMenu41;
	MenuItem* fileOpenMenu42;
	MenuItem* fileOpenMenu43;
	MenuItem* fileOpenMenu44;
	MenuItem* fileOpenMenu45;
	MenuItem* fileOpenMenu46;
	MenuItem* fileOpenMenu47;
	MenuItem* fileOpenMenu48;
	MenuItem* fileOpenMenu49;
	MenuItem* fileOpenMenu50;
	MenuItem* fileOpenMenu51;
	MenuItem* fileOpenMenu52;
	MenuItem* fileOpenMenu53;
	MenuItem* fileOpenMenu54;
	MenuItem* fileOpenMenu55;
	MenuItem* fileOpenMenu56;
	MenuItem* fileOpenMenu57;



	MenuItem* editStuffMenu;
	MenuItem* editStuffMenu1;
	MenuItem* editStuffMenu2;
	MenuItem* editStuffMenu3;
	MenuItem* editStuffMenu4;
	MenuItem* editStuffMenu5;
	MenuItem* editStuffMenu6;
	MenuItem* editStuffMenu7;
	MenuItem* editStuffMenu8;
	MenuItem* editStuffMenu9;
	MenuItem* editStuffMenu10;
	MenuItem* editStuffMenu11;
	MenuItem* editStuffMenu12;
	MenuItem* editStuffMenu13;
	MenuItem* editStuffMenu14;
	MenuItem* editStuffMenu15;
	MenuItem* editStuffMenu16;
	MenuItem* editStuffMenu17;
	MenuItem* editStuffMenu18;
	MenuItem* editStuffMenu19;
	MenuItem* editStuffMenu20;
	MenuItem* editStuffMenu21;
	MenuItem* editStuffMenu22;
	MenuItem* editStuffMenu23;
	MenuItem* editStuffMenu24;
	MenuItem* editStuffMenu25;
	MenuItem* editStuffMenu26;
	MenuItem* editStuffMenu27;
	MenuItem* editStuffMenu28;
	MenuItem* editStuffMenu29;
	MenuItem* editStuffMenu30;
	MenuItem* editStuffMenu31;
	MenuItem* editStuffMenu32;
	MenuItem* editStuffMenu33;
	MenuItem* editStuffMenu34;
	MenuItem* editStuffMenu35;
	MenuItem* editStuffMenu36;
	MenuItem* editStuffMenu37;
	MenuItem* editStuffMenu38;
	MenuItem* editStuffMenu39;
	MenuItem* editStuffMenu40;
	MenuItem* editStuffMenu41;
	MenuItem* editStuffMenu42;
	MenuItem* editStuffMenu43;
	MenuItem* editStuffMenu44;
	MenuItem* editStuffMenu45;
	MenuItem* editStuffMenu46;
	MenuItem* editStuffMenu47;
	MenuItem* editStuffMenu48;
	MenuItem* editStuffMenu49;
	MenuItem* editStuffMenu50;
	MenuItem* editStuffMenu51;
	MenuItem* editStuffMenu52;
	MenuItem* editStuffMenu53;
	MenuItem* editStuffMenu54;
	MenuItem* editStuffMenu55;
	MenuItem* editStuffMenu56;
	MenuItem* editStuffMenu57;

	Label* label1;
};


BEGIN_CLASSINFO(VisualFormFilesWindow, "VisualFormFilesWindow", "VCF::Window", VISUALFORMFILESWINDOW_CLASSID)
OBJ_FIELD( VisualFormFilesWindow, Label*, label1 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu1 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu2 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu3 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu4 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu5 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu6 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu7 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu8 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu9 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu10 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu11 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu12 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu13 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu14 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu15 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu16 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu17 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu18 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu19 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu20 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu21 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu22 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu23 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu24 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu25 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu26 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu27 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu28 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu29 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu30 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu31 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu32 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu33 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu34 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu35 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu36 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu37 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu38 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu39 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu40 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu41 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu42 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu43 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu44 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu45 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu46 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu47 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu48 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu49 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu50 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu51 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu52 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu53 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu54 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu55 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu56 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, fileOpenMenu57 )


OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu1 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu2 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu3 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu4 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu5 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu6 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu7 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu8 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu9 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu10 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu11 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu12 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu13 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu14 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu15 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu16 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu17 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu18 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu19 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu20 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu21 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu22 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu23 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu24 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu25 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu26 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu27 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu28 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu29 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu30 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu31 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu32 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu33 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu34 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu35 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu36 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu37 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu38 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu39 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu40 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu41 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu42 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu43 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu44 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu45 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu46 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu47 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu48 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu49 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu50 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu51 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu52 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu53 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu54 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu55 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu56 )
OBJ_FIELD( VisualFormFilesWindow, MenuItem*, editStuffMenu57 )
END_CLASSINFO(VisualFormFilesWindow)


class VisualFormFilesApplication : public Application {
public:

	VisualFormFilesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		REGISTER_CLASSINFO_EXTERNAL(VisualFormFilesWindow);

		FilePath fp = getFileName();

		FileInputStream fs( fp.getPathName(true) + "Form1.vff");
		String vff;
		fs >> vff;

		Window* window;
		BasicInputStream bis( vff );
		VFFInputStream vis( &bis );
		vis.readComponent( (Component**)&window );

		VisualFormFilesWindow* w = (VisualFormFilesWindow*)window;

		setMainWindow(window);

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new VisualFormFilesApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:41  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.2.4  2004/04/29 03:40:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


