//LOLCats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/FoundationKit/Dictionary.h"

#include "vcf/HTMLKit/HTMLKit.h"
#if !defined(VCF_DISABLE_PRAGMA_LINKING)
#   define USE_INTERNETKIT_DLL
#endif

#include "vcf/InternetKit/InternetKit.h"


#include "vcf/XMLKit/XMLKit.h"




#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;

/**
Modeled after Ryan Paul's article at Ars Technica:
http://arstechnica.com/journals/linux.ars/2008/02/04/you-can-has-lolcats-with-ruby-and-gtk
*/

class LOLCatsWindow : public Window {
public:
	LOLCatsWindow();

	virtual ~LOLCatsWindow(){};

};


#define LOLCATSWINDOW_CLASSID		"8d47ad29-296e-4585-a6c0-d7c18a041c83"

_class_rtti_(LOLCatsWindow, "VCF::Window", LOLCATSWINDOW_CLASSID)
_class_rtti_end_






class LOLCatsApp : public Application {
public:

	String feedURL;
	uint32 updateFreq;
	StatusBar* statusBar;
	HTMLBrowserControl* browser;

	LOLCatsApp( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
		InternetKit::init(argc, argv); 
		XMLKit::init( argc, argv );

		feedURL = "http://feeds.feedburner.com/ICanHasCheezburger/";
		updateFreq = 10 * 60 * 1000; //10 minutes
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(LOLCatsWindow);

		Window* mainWindow = Frame::createWindow( classid(LOLCatsWindow) );		

		setMainWindow(mainWindow);
		mainWindow->show();		

		update(NULL);

		return result;
	}

	void onUpdateFreqChanged( Event* e ) {
		TextModel* tm = (TextModel*)e->getSource();
		updateFreq = StringUtils::fromStringAsUInt( tm->getText() ) * (60 * 1000);
		setupTimer();
	}

	void onQuit( Event* e ) {
		getMainWindow()->close();
	}
	

	void onRefresh( Event* e ) {
		update(NULL);
	}

	void update( Event* e ) {
		DateTime dt = DateTime::now();		
		statusBar->setStatusText( Format("Last update: %s") % StringUtils::format( dt,"%I:%M:%S" ) );

		AsyncURL* url = new AsyncURL(feedURL);
		url->DataComplete += 
			new ClassProcedure1<URLEvent*,LOLCatsApp>(this, LOLCatsApp::urlComplete, "LOLCatsApp::urlComplete" );
		
		url->get();

	}

	void displayURL( Event* e ) {
		AsyncURL* url = (AsyncURL*)e->getSource();	
		String xml = url->getDataAsString();
		
		String html;
		html += "<html><body>\n";

		XmlDocument doc;
		doc.setXML(xml);
		XPathIterator xp(doc);
		Dictionary nsDict;
		nsDict["media"] = "http://search.yahoo.com/mrss";
		xp.registerNamespaces(nsDict);

		XPathNodeIterator it = xp.selectNodes("//media:content");
		while ( it != xp.end() && !it.isNull() ) {
			const XmlNode& n = *it;		
			
			String imageURL = n.getAttribute("url");
			html += "<div><img src=\"";
			html += imageURL;
			html += "\"></div><br>\n";

			it ++;
		}

		html += "</body></html>";

		
		String filename = System::getCurrentWorkingDirectory();
		filename += "/tmp.html";
		
		{
			FileOutputStream fos(filename);
			fos << html;
		}

		

		browser->setCurrentURL( filename );

		url->free();
	}

	void urlComplete(URLEvent* e) {
		AsyncURL* url = (AsyncURL*)e->getSource();		
		
		Event* event = new Event(url);

		postEvent( new ClassProcedure1<Event*,LOLCatsApp>(this, LOLCatsApp::displayURL ),
					event );
		
	}

	void setupTimer() {
		TimerComponent* timer = (TimerComponent*)getMainWindow()->findComponent( "timer" );
		timer->setActivated( false );
		timer->setTimeoutInterval( updateFreq );
		timer->setActivated( true );
	}

	void mainWindowLoaded( ComponentEvent* e )	{
		Component* component = (Component*)e->getSource();

		TimerComponent* timer = (TimerComponent*)component->findComponent( "timer" );
		timer->TimerPulse += 
			new ClassProcedure1<Event*,LOLCatsApp>(this, LOLCatsApp::update, "LOLCatsApp::update" );


		TextControl* updateFreqEdit = (TextControl*)component->findComponent( "updateFreqEdit", true );
		updateFreqEdit->getTextModel()->ModelChanged +=
			new ClassProcedure1<Event*,LOLCatsApp>(this, LOLCatsApp::onUpdateFreqChanged, "LOLCatsApp::onUpdateFreqChanged" );


		ToolbarItem* tbi = (ToolbarItem*)component->findComponent( "btn1", true );
		tbi->ItemClicked += 
			new ClassProcedure1<Event*,LOLCatsApp>(this, LOLCatsApp::onRefresh, "LOLCatsApp::onRefresh" );

		tbi = (ToolbarItem*)component->findComponent( "btn2", true );
		tbi->ItemClicked += 
			new ClassProcedure1<Event*,LOLCatsApp>(this, LOLCatsApp::onQuit, "LOLCatsApp::onQuit" );


		statusBar = (StatusBar*)component->findComponent( "status", true );
		browser = (HTMLBrowserControl*)component->findComponent( "browser", true );
	}
};


LOLCatsWindow::LOLCatsWindow()
{
	LOLCatsApp* app = (LOLCatsApp*)Application::getRunningInstance();
	ComponentLoaded += 
		new ClassProcedure1<ComponentEvent*,LOLCatsApp>( app, LOLCatsApp::mainWindowLoaded, "LOLCatsApp::mainWindowLoaded" );
}


int main(int argc, char *argv[])
{
	Application* app = new LOLCatsApp( argc, argv );

	Application::main();
	
	XMLKit::terminate();
	HTMLKit::terminate();
	InternetKit::terminate();

	return 0;
}


