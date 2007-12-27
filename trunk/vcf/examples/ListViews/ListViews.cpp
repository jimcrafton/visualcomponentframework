//ListViews.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/ListViewControl.h"

using namespace VCF;


#define LISTVIEWS_CLASSID		"dc6f263c-d09b-4ae0-b37d-9c453b4511b3"
class ListViews : public Window {
};
_class_rtti_(ListViews, "VCF::Window", LISTVIEWS_CLASSID)
_class_rtti_end_


class ListViewsApplication : public Application {
public:
	typedef ClassProcedure1<Event*,ListViewsApplication> AppHandler;

	ListViewsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(ListViews);

		Window* mainWindow = Frame::createWindow( classid(ListViews) );

		setMainWindow(mainWindow);
		mainWindow->show();
		

		MenuItem* item = (MenuItem*) mainWindow->findComponent( "addItem", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::onAddItem, "onAddItem" );

		item = (MenuItem*)mainWindow->findComponent( "listModelAddItem", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::onAddItem2, "onAddItem2" );
		
		item = (MenuItem*)mainWindow->findComponent( "deleteItem", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::deleteItem, "deleteItem" );
		
		item = (MenuItem*)mainWindow->findComponent( "viewStyleIcon", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::changeStyle, "changeStyle" );
		
		item = (MenuItem*)mainWindow->findComponent( "viewStyleSmall", true );
		item->MenuItemClicked += getCallback( "changeStyle" );

		item = (MenuItem*)mainWindow->findComponent( "viewStyleList", true );
		item->MenuItemClicked += getCallback( "changeStyle" );

		item = (MenuItem*)mainWindow->findComponent( "viewStyleReport", true );
		item->MenuItemClicked += getCallback( "changeStyle" );

		item = (MenuItem*)mainWindow->findComponent( "columnAdd", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::addColumn, "addColumn" );

		item = (MenuItem*)mainWindow->findComponent( "columnDelete", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::deleteColumn, "deleteColumn" );

		item = (MenuItem*)mainWindow->findComponent( "columnChange", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::columnChange, "columnChange" );

		item = (MenuItem*)mainWindow->findComponent( "changeItem", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::changeItem, "changeItem" );

		item = (MenuItem*)mainWindow->findComponent( "addSubItem", true );
		item->MenuItemClicked += new AppHandler( this, &ListViewsApplication::addSubItem, "addSubItem" );

		
		
		return result;
	}

	ListViewControl* getListView() {
		return (ListViewControl*) getMainWindow()->findComponent( "listView", true );
	}

	void onAddItem( Event* e ) {
		getListView()->addItem( Format("New Item %d") % (getListView()->getListModel()->getCount() + 1) );
	}

	void onAddItem2( Event* e ) {
		ListModel* lm = getListView()->getListModel();
		lm->add( (String)(Format("New List Model item %d") % (lm->getCount() + 1)) );
	}

	void deleteItem( Event* e ) {
		ListModel* lm = getListView()->getListModel();
		lm->removeAtIndex( maxVal<>( 0, (int)lm->getCount()-2 ) );
	}

	void changeStyle( Event* e ) {
		Component* c = (Component*)e->getSource();
		switch ( c->getTag() ) {
			case 0 : {
				getListView()->setIconStyle( isLargeIcon );
			}
			break;

			case 1 : {
				getListView()->setIconStyle( isSmallIcon );
			}
			break;

			case 2 : {
				getListView()->setIconStyle( isList );
			}
			break;

			case 3 : {
				getListView()->setIconStyle( isDetails );
			}
			break;
		}
	}

	void addColumn( Event* e ) {
		ColumnModel* cm = getListView()->getColumnModel();
		cm->add( "Column" );

	}
	void deleteColumn( Event* e ) {
		ColumnModel* cm = getListView()->getColumnModel();
		cm->removeAtIndex( cm->getCount()- 1 );
	}

	void columnChange( Event* ) {
		ColumnModel* cm = getListView()->getColumnModel();
		
		cm->setAsString( 0, "New Col: " + System::createTempFileName() );
	}

	void changeItem( Event* ) {
		ListModel* lm = getListView()->getListModel();
		
		lm->setAsString( 0, "New Item: " + System::createTempFileName() );
	}

	void addSubItem( Event* ) {
		ListModel* lm = getListView()->getListModel();
		
	}
};


int main(int argc, char *argv[])
{
	Application* app = new ListViewsApplication( argc, argv );

	Application::main();
	
	return 0;
}


