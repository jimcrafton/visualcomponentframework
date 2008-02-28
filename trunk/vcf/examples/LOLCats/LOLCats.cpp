//LOLCats.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/FoundationKit/Dictionary.h"

#include <shellapi.h>

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
	StatusBar* statusBar;
	HTMLBrowserControl* browser;
	TimerComponent* timer;
	TextControl* updateFreqEdit;
	ToolbarItem* refreshBtn;
	ToolbarItem* quitBtn;
	ToolbarItem* homeBtn;

	LOLCatsWindow();

	virtual ~LOLCatsWindow(){};

};


#define LOLCATSWINDOW_CLASSID		"8d47ad29-296e-4585-a6c0-d7c18a041c83"

_class_rtti_(LOLCatsWindow, "VCF::Window", LOLCATSWINDOW_CLASSID)
	_field_obj_( StatusBar*, statusBar )
	_field_obj_( HTMLBrowserControl*, browser )
	_field_obj_( TimerComponent*, timer )
	_field_obj_( TextControl*, updateFreqEdit )
	_field_obj_( ToolbarItem*, refreshBtn )
	_field_obj_( ToolbarItem*, quitBtn )
	_field_obj_( ToolbarItem*, homeBtn )
	
_class_rtti_end_






class LOLCatsApp : public Application {
public:

	String feedURL;
	uint32 updateFreq;
	StatusBar* statusBar;
	HTMLBrowserControl* browser;
	String lolcatsFile;

	LOLCatsApp( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
		InternetKit::init(argc, argv); 
		XMLKit::init( argc, argv );


		feedURL = "http://feeds.feedburner.com/ICanHasCheezburger/";
		updateFreq = 10 * 60 * 1000; //10 minutes
		lolcatsFile = System::getCurrentWorkingDirectory();
		lolcatsFile += "lolcats.html";

		addCallback( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::onHome), "LOLCatsApp::onHome" );
		addCallback( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::update), "LOLCatsApp::update" );
		addCallback( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::onUpdateFreqChanged), "LOLCatsApp::onUpdateFreqChanged" );
		addCallback( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::onRefresh), "LOLCatsApp::onRefresh" );
		addCallback( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::onQuit), "LOLCatsApp::onQuit" );
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

	void onHome( Event* e ) {
		UIShell::getUIShell()->launch( "http://icanhascheezburger.com", "" );
	}

	void update( Event* e ) {
		CallBack* cb = getCallback( "LOLCatsApp::urlComplete" );
		if ( NULL == cb ) {
			cb = new ClassProcedure1<URLEvent*,LOLCatsApp>(this, &LOLCatsApp::urlComplete, "LOLCatsApp::urlComplete" );
		}
		AsyncURL* url = new AsyncURL(feedURL, true);
		url->DataComplete += cb;

		url->get();

	}

	void displayURL( Event* e ) {
		browser->setCurrentURL( lolcatsFile );
		DateTime dt = DateTime::now();
		statusBar->setStatusText( Format("Last update: %s") % StringUtils::format( dt,"%I:%M:%S" ) );		
	}

	void urlComplete(URLEvent* e) {
		AsyncURL* url = (AsyncURL*)e->getSource();
		
		String xml = url->getDataAsString();
		
		String html;
		html += "<html><body style=\"background-color: #F7F7F7\">\n";

		XmlDocument doc;
		doc.setXML(xml);		

		XPathIterator xp(doc);
		
		XPathNodeIterator it = xp.selectNodes("//media:content");
		while ( it != xp.end() && !it.isNull() ) {
			const XmlNode& n = *it;		
			
			String imageURL = n.getAttribute("url");
			html += "<div style=\"border: 3px outset grey\"><img width=\"100%\" src=\"";
			html += imageURL;
			html += "\"></div><br>\n";

			it ++;
		}

		html += "</body></html>";		
		
		{
			FileOutputStream fos(lolcatsFile);
			fos << html;
		}
		

		Event* event = new Event(this);

		postEvent( new ClassProcedure1<Event*,LOLCatsApp>(this, &LOLCatsApp::displayURL ),
					event );
		
	}

	void setupTimer() {
		TimerComponent* timer = (TimerComponent*)getMainWindow()->findComponent( "timer" );
		timer->setActivated( false );
		timer->setTimeoutInterval( updateFreq );
		timer->setActivated( true );
	}

	void mainWindowLoaded( ComponentEvent* e )	{
		LOLCatsWindow* window = (LOLCatsWindow*)e->getSource();

		window->updateFreqEdit->getTextModel()->ModelChanged += getCallback( "LOLCatsApp::onUpdateFreqChanged" );

		statusBar = window->statusBar;
		browser = window->browser;
	}
};


LOLCatsWindow::LOLCatsWindow()
{
	LOLCatsApp* app = (LOLCatsApp*)Application::getRunningInstance();
	ComponentLoaded += 
		new ClassProcedure1<ComponentEvent*,LOLCatsApp>( app, &LOLCatsApp::mainWindowLoaded, "LOLCatsApp::mainWindowLoaded" );
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


