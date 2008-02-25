//DiggApp.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/FoundationKit/ThreadKit.h"


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
	ListViewControl* listView;

	virtual ~DiggWindow(){};

};


_class_rtti_(DiggWindow, "VCF::Window", "DiggWindow")
_field_obj_( TextControl*, searchEdit )
_field_obj_( ListViewControl*, listView )
_class_rtti_end_


class DiggStory : public Object {
public:

	DiggStory(): Id(0),diggCount(0){}

	int Id;
	String title;
	String description;
	int diggCount;
	String href;
};

class DiggModel : public SimpleListModel {
protected:
	virtual void destroy() {
		empty();
		SimpleListModel::destroy();
	}

public:
	DiggModel():SimpleListModel(){
		deleteVariantObjects_ = true;
	}

	
	
	virtual bool supportsSubItems() {
		return true;
	}

	virtual String getAsString( const uint32& index ) {
		DiggStory* obj = (DiggStory*) (Object*)get( index);

		return StringUtils::toString( obj->Id );
	}

	virtual VariantData getSubItem( const uint32& index, const uint32& subItemIndex ) {		
		DiggStory* obj = (DiggStory*) (Object*)get( index);

		VariantData v;

		switch ( subItemIndex ) {
			case 0 : {
				v = obj->title;
			}
			break;
			
			case 1 : {
				v = obj->description;
			}
			break;

			case 2 : {
				v = obj->diggCount;
			}
			break;

			case 3 : {
				v = obj->href;
			}
			break;
		}

		return v;
	}

	virtual String getSubItemAsString( const uint32& index, const uint32& subItemIndex ) {
		VariantData v = getSubItem( index, subItemIndex );

		return v.toString();
	}

	virtual uint32 getSubItemsCount( const uint32& index ) {
		return 4;	
	}
};


class DiggItem : public ListItem {
public:

};

class DiggApp : public Application {
public:

	String diggURL;
	String appKey;
	ListModel* listModel;
	TextControl* searchEdit;
	ListViewControl* listView;

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
		Thread::getMainThread()->getRunLoop()->stop();
	}

	void onSearch( Event* ) {
		diggIt( searchEdit->getTextModel()->getText() );
	}

	void viewAsDetails( Event* ) {
		listView->setIconStyle( isDetails );
	}

	void viewAsList( Event* ) {
		listView->setIconStyle( isList );
	}

	void diggIt( const String& searchFor ) {

		listModel->empty();

		CallBack* cb = getCallback( "DiggApp::urlComplete" );
		if ( NULL == cb ) {
			cb = new ClassProcedure1<URLEvent*,DiggApp>(this, &DiggApp::urlComplete, "DiggApp::urlComplete" );
		}

		String s = getDiggURL(searchFor);
		StringUtils::trace(s + "\n");
		AsyncURL url(s);
		url.Finished += cb;
		url.get();

		ThreadManager::getCurrentRunLoop()->run();
		String xml = url.getDataAsString();

		if ( !xml.empty() ) {
			XmlDocument doc;
			doc.setXML(xml);		
			
			XPathIterator xp(doc);
			XPathNodeIterator it = xp.selectNodes("/stories/story");
			while ( it != xp.end() && !it.isNull() ) {
				const XmlNode& n = *it;
				
				DiggStory* story = new DiggStory();
				story->Id = StringUtils::fromStringAsInt( n.getAttribute("id") );
				story->title = n.getChild("title").getContent();
				story->description = n.getChild("description").getContent();
				story->href = n.getAttribute("link");
				story->diggCount = StringUtils::fromStringAsInt( n.getAttribute("diggs") );
				
				listModel->add( story );				

				listView->setItem( listModel->getCount()-1, new DiggItem() );
				
				++it;
			}
			
		}
	}


	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		

		REGISTER_CLASSINFO_EXTERNAL(DiggWindow);
		
		addCallback( new ClassProcedure1<Event*,DiggApp>(this, &DiggApp::onSearch), "DiggApp::onSearch" );
		addCallback( new ClassProcedure1<Event*,DiggApp>(this, &DiggApp::viewAsList), "DiggApp::viewAsList" );
		addCallback( new ClassProcedure1<Event*,DiggApp>(this, &DiggApp::viewAsDetails), "DiggApp::viewAsDetails" );

		DiggWindow* mainWindow = (DiggWindow*) Frame::createWindow( classid(DiggWindow) );

		setMainWindow(mainWindow);
		mainWindow->show();
	
		listModel = new DiggModel();
		addComponent( listModel );
		mainWindow->listView->setListModel( listModel );

		searchEdit = mainWindow->searchEdit;
		listView = mainWindow->listView;

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


