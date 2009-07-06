//Tabs.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/DefaultTabPage.h"
#include "vcf/ApplicationKit/TabbedPages.h"

using namespace VCF;

#define TABSWINDOW_CLASSID		"3906b787-436b-44c2-b439-2b4d880b75e6"


class TabsWindow : public Window {
public:
};

_class_rtti_(TabsWindow, "VCF::Window", TABSWINDOW_CLASSID)
_class_rtti_end_



class MyTabPage : public DefaultTabPage {
public:
	MyTabPage(): DefaultTabPage() {}
	virtual ~MyTabPage(){}


	virtual void paint( GraphicsContext* context, Rect* paintRect ) {
		DefaultTabPage::paint( context, paintRect );
		
		Image* img = GraphicsToolkit::createImage( "res:btn.png" );
		img->setIsTransparent(true);


		context->drawImage( paintRect->getTopRight().offset(-1.0 * (2+img->getWidth()),2), img );

		delete img;

	}
		

};


class TabsApplication : public Application {
public:

	TabsApplication( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<MouseEvent*,TabsApplication>(this, &TabsApplication::tabPageClicked), "TabsApplication::tabPageClicked" );
	}


	void tabPageClicked( MouseEvent* e ) {

		TabbedPages* pages = (TabbedPages*) getMainWindow()->findComponent( "tabs" );

		TabPage* page = pages->tabPageHitTest( *e->getPoint() );
		if ( NULL != page && page->getIndex() == 4 ) {
			Dialog::showMessage( "MyTabPage instance Clicked!" );
		}
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(TabsWindow);

		Window* mainWindow = Frame::createWindow( classid(TabsWindow) );

		setMainWindow(mainWindow);
		mainWindow->show();



		TabbedPages* pages = (TabbedPages*) mainWindow->findComponent( "tabs" );

		pages->setTabPage( 4, new MyTabPage() );

		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TabsApplication( argc, argv );

	Application::main();
	
	return 0;
}


