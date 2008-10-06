//HtmlMVC.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/HTMLKit/HTMLKit.h"


using namespace VCF;



class HtmlMVCWindow : public Window {
public:
	HtmlMVCWindow() {}
	virtual ~HtmlMVCWindow(){};
};

_class_rtti_(HtmlMVCWindow, "VCF::Window", "HtmlMVCWindow")
_class_rtti_end_


class MyObject : public Component {
public:
	MyObject(): count(0), cost(0){}

	int count;
	String title;
	String version;
	double cost;

	int getCount() { return count;}
	String getTitle() { return title;}
	String getVersion() { return version;}
	double getCost() { return cost;}

	void setCount( const int& val ) { count = val; }
	void setTitle( const String& val ) { title = val; }
	void setVersion( const String& val ) { version = val; }
	void setCost( const double& val ) { cost = val; }
};



_class_rtti_(MyObject, "VCF::Component", "MyObject")
	_property_( int, "count", getCount, setCount, "" )
	_property_( String, "title", getTitle, setTitle, "" )
	_property_( String, "version", getVersion, setVersion, "" )
	_property_( double, "cost", getCost, setCost, "" )

	_field_( int, count )	
	_field_( double, cost )
	_field_( VCF::String, title )
	_field_( String, version )
_class_rtti_end_


class HtmlMVCApplication : public Application {
public:

	HtmlMVCApplication( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );

		addCallback( new ClassProcedure1<Event*,HtmlMVCApplication>(this, &HtmlMVCApplication::onDocComplete), "HtmlMVCApplication::onDocComplete" );
		addCallback( new ClassProcedure1<Event*,HtmlMVCApplication>(this, &HtmlMVCApplication::onCostDblClick), "HtmlMVCApplication::onCostDblClick" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(HtmlMVCWindow);
		REGISTER_CLASSINFO_EXTERNAL(MyObject);


		Window* mainWindow = Frame::createWindow( classid(HtmlMVCWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();

		return result;
	}

	void onDocComplete( Event* e ) {
		HTMLBrowserControl* browser = (HTMLBrowserControl*)findComponent( "browser", true );
	}

	void onCostDblClick( Event* e ) {
		HTMLBrowserControl* browser = (HTMLBrowserControl*)findComponent( "browser", true );

		HTMLDocument doc = browser->getDocument();
		HTMLElementCollection all = doc.getAll();
		HTMLElement* found = NULL;
		for (int i=0;i<all.getLength();i++ ) {
			found = all.item(i);
			if ( found->getID() == L"root" ) {
				String html = found->getInnerHTML();
				html += "<div>More Content</div>";
				found->setInnerHTML( html );

				break;
			}
		}
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<HtmlMVCApplication>(argc,argv);
}


