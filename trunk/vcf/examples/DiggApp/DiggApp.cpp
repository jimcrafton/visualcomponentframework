//DiggApp.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TextControl.h"


#if !defined(VCF_DISABLE_PRAGMA_LINKING)
#   define USE_INTERNETKIT_DLL
#endif

#include "vcf/InternetKit/InternetKit.h"
#include "vcf/XMLKit/XMLKit.h"


using namespace VCF;


class DiggWindow : public Window {
public:
	DiggWindow() {
		setCaption( "DiggApp" );		
	}

	TextControl* searchEdit;

	virtual ~DiggWindow(){};

};


_class_rtti_(DiggWindow, "VCF::Window", "DiggWindow")
_field_obj_( TextControl*, searchEdit )
_class_rtti_end_


class DiggApp : public Application {
public:

	String diggURL;
	String appKey;

	DiggApp( int argc, char** argv ) : Application(argc, argv) {
		appKey = "http%%3A%%2F%%2Fvcf-online.org";
		diggURL = "http://services.digg.com/stories/topic/%s?count=20&appkey=" + appKey;

		InternetKit::init(argc, argv);
		XMLKit::init( argc, argv );
	}

	String getDiggURL( const String& searchText ) {
		return Format(diggURL) % searchText;
	}

	void urlComplete(URLEvent* e) {
		AsyncURL* url = (AsyncURL*)e->getSource();
		String xml = url->getDataAsString();

		XmlDocument doc;
		doc.setXML(xml);		

		XPathIterator xp(doc);
		XPathNodeIterator it = xp.selectNodes("/stories/story");
		while ( it != xp.end() && !it.isNull() ) {
			const XmlNode& n = *it;
			++it;
		}
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		

		REGISTER_CLASSINFO_EXTERNAL(DiggWindow);
		
		Window* mainWindow = Frame::createWindow( classid(DiggWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
	
		CallBack* cb = getCallback( "DiggApp::urlComplete" );
		if ( NULL == cb ) {
			cb = new ClassProcedure1<URLEvent*,DiggApp>(this, &DiggApp::urlComplete, "DiggApp::urlComplete" );
		}

		String s = getDiggURL("apple");
		StringUtils::trace(s + "\n");
		AsyncURL* url = new AsyncURL(s, true);
		url->DataComplete += cb;
		url->get();


		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new DiggApp( argc, argv );

	Application::main();
	InternetKit::terminate();
	XMLKit::terminate();
	return 0;
}


