//VisualFormFiles.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/FoundationKit/VFFInputStream.h"

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;




#define VISUALFORMFILESWINDOW_CLASSID		"6dbafd3f-c8cf-4fc5-9141-43af516db748"
class VisualFormFilesWindow : public Window {
public:
	VisualFormFilesWindow() : label1(NULL) {
		StringUtils::trace( "VisualFormFilesWindow() " + this->toString() + "\n" );

		CallBack* ev = new ClassProcedure1<ComponentEvent*,VisualFormFilesWindow>( this, &VisualFormFilesWindow::onLoaded, "VisualFormFilesWindow::onLoaded" );
		ComponentLoaded += ev;
	}

	virtual ~VisualFormFilesWindow(){};

	void onLoaded( ComponentEvent* e ) {
		CallBack* ev = new ClassProcedure1<MenuItemEvent*,VisualFormFilesWindow>( this, &VisualFormFilesWindow::onFileOpened, "VisualFormFilesWindow::onFileOpened" );

		MenuItem* root = this->getMenuBar()->getRootMenuItem();
		MenuItem* file = root->getChildAt( 0 );
		Enumerator<MenuItem*>* children =  file->getChildren();
		while ( children->hasMoreElements() ) {
			MenuItem* item = children->nextElement();

			item->MenuItemClicked += ev;
		}

		

	}

	void onFileOpened( MenuItemEvent* e ) {
		MenuItem* item = (MenuItem*)e->getSource();

		Dialog::showMessage( "Menu Item " + item->getCaption() + " clicked!" );
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


_class_rtti_(VisualFormFilesWindow, "VCF::Window", VISUALFORMFILESWINDOW_CLASSID)
_field_obj_( Label*, label1 )
_field_obj_( MenuItem*, fileOpenMenu )
_field_obj_( MenuItem*, fileOpenMenu1 )
_field_obj_( MenuItem*, fileOpenMenu2 )
_field_obj_( MenuItem*, fileOpenMenu3 )
_field_obj_( MenuItem*, fileOpenMenu4 )
_field_obj_( MenuItem*, fileOpenMenu5 )
_field_obj_( MenuItem*, fileOpenMenu6 )
_field_obj_( MenuItem*, fileOpenMenu7 )
_field_obj_( MenuItem*, fileOpenMenu8 )
_field_obj_( MenuItem*, fileOpenMenu9 )
_field_obj_( MenuItem*, fileOpenMenu10 )
_field_obj_( MenuItem*, fileOpenMenu11 )
_field_obj_( MenuItem*, fileOpenMenu12 )
_field_obj_( MenuItem*, fileOpenMenu13 )
_field_obj_( MenuItem*, fileOpenMenu14 )
_field_obj_( MenuItem*, fileOpenMenu15 )
_field_obj_( MenuItem*, fileOpenMenu16 )
_field_obj_( MenuItem*, fileOpenMenu17 )
_field_obj_( MenuItem*, fileOpenMenu18 )
_field_obj_( MenuItem*, fileOpenMenu19 )
_field_obj_( MenuItem*, fileOpenMenu20 )
_field_obj_( MenuItem*, fileOpenMenu21 )
_field_obj_( MenuItem*, fileOpenMenu22 )
_field_obj_( MenuItem*, fileOpenMenu23 )
_field_obj_( MenuItem*, fileOpenMenu24 )
_field_obj_( MenuItem*, fileOpenMenu25 )
_field_obj_( MenuItem*, fileOpenMenu26 )
_field_obj_( MenuItem*, fileOpenMenu27 )
_field_obj_( MenuItem*, fileOpenMenu28 )
_field_obj_( MenuItem*, fileOpenMenu29 )
_field_obj_( MenuItem*, fileOpenMenu30 )
_field_obj_( MenuItem*, fileOpenMenu31 )
_field_obj_( MenuItem*, fileOpenMenu32 )
_field_obj_( MenuItem*, fileOpenMenu33 )
_field_obj_( MenuItem*, fileOpenMenu34 )
_field_obj_( MenuItem*, fileOpenMenu35 )
_field_obj_( MenuItem*, fileOpenMenu36 )
_field_obj_( MenuItem*, fileOpenMenu37 )
_field_obj_( MenuItem*, fileOpenMenu38 )
_field_obj_( MenuItem*, fileOpenMenu39 )
_field_obj_( MenuItem*, fileOpenMenu40 )
_field_obj_( MenuItem*, fileOpenMenu41 )
_field_obj_( MenuItem*, fileOpenMenu42 )
_field_obj_( MenuItem*, fileOpenMenu43 )
_field_obj_( MenuItem*, fileOpenMenu44 )
_field_obj_( MenuItem*, fileOpenMenu45 )
_field_obj_( MenuItem*, fileOpenMenu46 )
_field_obj_( MenuItem*, fileOpenMenu47 )
_field_obj_( MenuItem*, fileOpenMenu48 )
_field_obj_( MenuItem*, fileOpenMenu49 )
_field_obj_( MenuItem*, fileOpenMenu50 )
_field_obj_( MenuItem*, fileOpenMenu51 )
_field_obj_( MenuItem*, fileOpenMenu52 )
_field_obj_( MenuItem*, fileOpenMenu53 )
_field_obj_( MenuItem*, fileOpenMenu54 )
_field_obj_( MenuItem*, fileOpenMenu55 )
_field_obj_( MenuItem*, fileOpenMenu56 )
_field_obj_( MenuItem*, fileOpenMenu57 )


_field_obj_( MenuItem*, editStuffMenu )
_field_obj_( MenuItem*, editStuffMenu1 )
_field_obj_( MenuItem*, editStuffMenu2 )
_field_obj_( MenuItem*, editStuffMenu3 )
_field_obj_( MenuItem*, editStuffMenu4 )
_field_obj_( MenuItem*, editStuffMenu5 )
_field_obj_( MenuItem*, editStuffMenu6 )
_field_obj_( MenuItem*, editStuffMenu7 )
_field_obj_( MenuItem*, editStuffMenu8 )
_field_obj_( MenuItem*, editStuffMenu9 )
_field_obj_( MenuItem*, editStuffMenu10 )
_field_obj_( MenuItem*, editStuffMenu11 )
_field_obj_( MenuItem*, editStuffMenu12 )
_field_obj_( MenuItem*, editStuffMenu13 )
_field_obj_( MenuItem*, editStuffMenu14 )
_field_obj_( MenuItem*, editStuffMenu15 )
_field_obj_( MenuItem*, editStuffMenu16 )
_field_obj_( MenuItem*, editStuffMenu17 )
_field_obj_( MenuItem*, editStuffMenu18 )
_field_obj_( MenuItem*, editStuffMenu19 )
_field_obj_( MenuItem*, editStuffMenu20 )
_field_obj_( MenuItem*, editStuffMenu21 )
_field_obj_( MenuItem*, editStuffMenu22 )
_field_obj_( MenuItem*, editStuffMenu23 )
_field_obj_( MenuItem*, editStuffMenu24 )
_field_obj_( MenuItem*, editStuffMenu25 )
_field_obj_( MenuItem*, editStuffMenu26 )
_field_obj_( MenuItem*, editStuffMenu27 )
_field_obj_( MenuItem*, editStuffMenu28 )
_field_obj_( MenuItem*, editStuffMenu29 )
_field_obj_( MenuItem*, editStuffMenu30 )
_field_obj_( MenuItem*, editStuffMenu31 )
_field_obj_( MenuItem*, editStuffMenu32 )
_field_obj_( MenuItem*, editStuffMenu33 )
_field_obj_( MenuItem*, editStuffMenu34 )
_field_obj_( MenuItem*, editStuffMenu35 )
_field_obj_( MenuItem*, editStuffMenu36 )
_field_obj_( MenuItem*, editStuffMenu37 )
_field_obj_( MenuItem*, editStuffMenu38 )
_field_obj_( MenuItem*, editStuffMenu39 )
_field_obj_( MenuItem*, editStuffMenu40 )
_field_obj_( MenuItem*, editStuffMenu41 )
_field_obj_( MenuItem*, editStuffMenu42 )
_field_obj_( MenuItem*, editStuffMenu43 )
_field_obj_( MenuItem*, editStuffMenu44 )
_field_obj_( MenuItem*, editStuffMenu45 )
_field_obj_( MenuItem*, editStuffMenu46 )
_field_obj_( MenuItem*, editStuffMenu47 )
_field_obj_( MenuItem*, editStuffMenu48 )
_field_obj_( MenuItem*, editStuffMenu49 )
_field_obj_( MenuItem*, editStuffMenu50 )
_field_obj_( MenuItem*, editStuffMenu51 )
_field_obj_( MenuItem*, editStuffMenu52 )
_field_obj_( MenuItem*, editStuffMenu53 )
_field_obj_( MenuItem*, editStuffMenu54 )
_field_obj_( MenuItem*, editStuffMenu55 )
_field_obj_( MenuItem*, editStuffMenu56 )
_field_obj_( MenuItem*, editStuffMenu57 )
_class_rtti_end_




class VisualFormFilesApplication : public Application {
public:

	VisualFormFilesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		REGISTER_CLASSINFO_EXTERNAL(VisualFormFilesWindow);

		VisualFormFilesWindow* w = (VisualFormFilesWindow*) Frame::createWindow( classid(VisualFormFilesWindow) );

		setMainWindow(w);

		w->show();

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
$Id$
*/
