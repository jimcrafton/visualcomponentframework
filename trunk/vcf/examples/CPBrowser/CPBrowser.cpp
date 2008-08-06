//CPBrowser.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"

#include "vcf/ApplicationKit/ProgressControl.h"
#include "vcf/ApplicationKit/PushButton.h"


#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/InternetKit/InternetKit.h"
#include "vcf/XMLKit/XMLKit.h"




#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;


class URLProgress : public VCF::ProgressControl {
public:

	

	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );


		Rect clientBounds = getClientBounds();

		Rect progressRect = clientBounds;
		progressRect.inflate(-2,-2);
		progressRect.right_ = progressRect.left_ + (progressRect.getWidth() * (position_/(maxVal_-minVal_)));


		ctx->setColor( progressBarColor_ );

		ctx->rectangle( progressRect );
		ctx->fillPath();

		ctx->setColor( progressTextColor_ );
		clientBounds.inflate(-2,-2);

		int32 drawOptions = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &clientBounds, url_, drawOptions );
	}

	String getURL() {
		return url_;
	}

	void setURL( const String& val ) {
		url_ = val;
		repaint();
	}
protected:
	String url_;
};



class CPBrowserWindow : public Window {
public:
	CPBrowserWindow() {}
	virtual ~CPBrowserWindow(){};
};

_class_rtti_(CPBrowserWindow, "VCF::Window", "CPBrowserWindow")
_class_rtti_end_


_class_rtti_(URLProgress, "VCF::ProgressControl", "URLProgress")
_class_rtti_end_


class CPBrowserApp : public Application {
public:
	String cpURL;

	URLProgress* urlProgress;

	CPBrowserApp( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
		InternetKit::init(argc, argv); 
		XMLKit::init( argc, argv );

		cpURL = "www.codeproject.com";

		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserDocTitleChanged), "CPBrowserApp::onBrowserDocTitleChanged" );
		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserURLLoaded), "CPBrowserApp::onBrowserURLLoaded" );
		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserURLLoadBegun), "CPBrowserApp::onBrowserURLLoadBegun" );
		addCallback( new ClassProcedure1<Event*,CPBrowserApp>(this, &CPBrowserApp::onBrowserURLLoading), "CPBrowserApp::onBrowserURLLoading" );
	}

	void onBrowserDocTitleChanged( Event* e ) 	{
		Window* mainWindow = getMainWindow();
		HTMLBrowserControl* browser = (HTMLBrowserControl*) e->getSource();
		mainWindow->setCaption( browser->getDocument().getTitle() );
	}

	void onBrowserURLLoaded( Event* e ) 	{
		urlProgress->setPosition( urlProgress->getMaxValue() );

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

	void onBrowserURLLoadBegun( Event* e ) 	{		
		HTMLBrowserControl* browser = (HTMLBrowserControl*) e->getSource();
		urlProgress->setPosition( 0 );
		urlProgress->setURL( browser->getCurrentURL() );
	}

	void onBrowserURLLoading( Event* e ) 	{
		HTMLEvent* htmlEv = (HTMLEvent*)e;

		double val = ((htmlEv->maxValue > 0) ? ((double)htmlEv->value / (double)htmlEv->maxValue) : 0.0) * urlProgress->getMaxValue();
		if ( htmlEv->maxValue == 0 && htmlEv->value == 0 ) {
			val = urlProgress->getMaxValue();

			HTMLBrowserControl* browser = (HTMLBrowserControl*) e->getSource();
			urlProgress->setURL( browser->getCurrentURL() );
		}

		urlProgress->setPosition( val  );
	}

	virtual bool initRunningApplication(){
		

		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(CPBrowserWindow);
		REGISTER_CLASSINFO_EXTERNAL(URLProgress);
		

		Window* mainWindow = Frame::createWindow( classid(CPBrowserWindow) );

		urlProgress = (URLProgress*)mainWindow->findComponent( "urlProgress", true );

		PushButton* back = (PushButton*)mainWindow->findComponent( "backBtn", true );

		//back->setBtnImageIndex(0);
		
		//back->setBtnImageIndex(1,PushButton::bisHighlight);

		//back->setBtnImageIndex(2,PushButton::bisDown);

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


