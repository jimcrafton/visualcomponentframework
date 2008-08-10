//MVCAdapters.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AdapterModels.h"
#include "vcf/ApplicationKit/ListViewControl.h"



#include "vcf/FoundationKit/RTTIMacros.h"



using namespace VCF;






class MVCAdaptersWindow : public Window {
public:
	MVCAdaptersWindow() {}
	virtual ~MVCAdaptersWindow(){};
};

_class_rtti_(MVCAdaptersWindow, "VCF::Window", "MVCAdaptersWindow")	
_class_rtti_end_


class MyObject : public Component {
public:
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
_class_rtti_end_

class MVCAdaptersApp : public Application {
public:

	MVCAdaptersApp( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<Event*,MVCAdaptersApp>(this, &MVCAdaptersApp::onSelected), "MVCAdaptersApp::onSelected" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(MVCAdaptersWindow);
		REGISTER_CLASSINFO_EXTERNAL(MyObject);
		
		
		

		Window* mainWindow = Frame::createWindow( classid(MVCAdaptersWindow) );
		setMainWindow(mainWindow);

		int d[3] = {12,3,444};
		ArrayModel<int> am( &d[0], 3 );


		ObjectModel* objModel = (ObjectModel*)findComponent( "model", true );

		objModel->setValueAsString( "3.1", "cost" );

		mainWindow->show();
		
		return result;
	}


	void onSelected( Event* e ) {
		ListViewControl* lv = (ListViewControl*)e->getSource();

		ItemEvent* ie = (ItemEvent*)e;
		Object* o = lv->getListModel()->get( ie->index );

		ObjectModel* objModel = (ObjectModel*)findComponent( "model", true );
		objModel->setSource( o );
	}
};


int main(int argc, char *argv[])
{

	return ApplicationKitMain<MVCAdaptersApp>(argc,argv);
}


