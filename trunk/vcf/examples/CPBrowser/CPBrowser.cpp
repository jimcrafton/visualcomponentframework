//CPBrowser.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/InternetKit/InternetKit.h"
#include "vcf/XMLKit/XMLKit.h"




#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;



class CPBrowserWindow : public Window {
public:
	CPBrowserWindow() {}
	virtual ~CPBrowserWindow(){};
};

_class_rtti_(CPBrowserWindow, "VCF::Window", "CPBrowserWindow")
_class_rtti_end_





class CPBrowserApp : public Application {
public:
	String cpURL;

	CPBrowserApp( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
		InternetKit::init(argc, argv); 
		XMLKit::init( argc, argv );

		cpURL = "www.codeproject.com";

		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserDocTitleChanged), "CPBrowserApp::onBrowserDocTitleChanged" );
		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserURLLoaded), "CPBrowserApp::onBrowserURLLoaded" );
		
	}

	void onBrowserDocTitleChanged( Event* e ) 	{
		Window* mainWindow = getMainWindow();
		HTMLBrowserControl* browser = (HTMLBrowserControl*) e->getSource();
		mainWindow->setCaption( browser->getDocument().getTitle() );
	}

	void onBrowserURLLoaded( Event* e ) 	{
		HTMLBrowserControl* browser = (HTMLBrowserControl*) e->getSource();

		HTMLDocument doc = browser->getDocument();

		URL url = doc.getURL();
		String host = url.getHost();

		if ( cpURL == StringUtils::lowerCase(host) ) {			
			
			HTMLElementCollection all = doc.getAll();
			
			for (int i=0;i<all.getLength();i++ ) {
				HTMLElement* element = all[i];
				
				String tag = element->getTagName();
				if ( StringUtils::lowerCase(tag) == "link" ) {
					String rel = element->getAttribute( "rel", false );
					String href = element->getAttribute( "href" );
				}
			}
		}
	}

	virtual bool initRunningApplication(){
		

		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(CPBrowserWindow);

		Window* mainWindow = Frame::createWindow( classid(CPBrowserWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	ApplicationKitMain<CPBrowserApp>(argc,argv);
	XMLKit::terminate();
	HTMLKit::terminate();
	InternetKit::terminate();

	return 0;
}


