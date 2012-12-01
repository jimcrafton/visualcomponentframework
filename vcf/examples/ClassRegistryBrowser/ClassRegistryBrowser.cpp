//ClassRegistryBrowser.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/ApplicationKit/TreeListControl.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Label.h"

using namespace VCF;


enum ClassImages {
	ciClassImg = 0,
	ciPropertyImg,
	ciDelegateImg
};

class ClassRegistryBrowserWindow : public Window {
public:
	ClassRegistryBrowserWindow() {}
	virtual ~ClassRegistryBrowserWindow(){};

	HTMLBrowserControl* classDocBrowser;
	ListViewControl* classList;
	TreeListControl* classData;
};

_class_rtti_(ClassRegistryBrowserWindow, "VCF::Window", "ClassRegistryBrowserWindow")
_field_obj_( HTMLBrowserControl*, classDocBrowser )
_field_obj_( ListViewControl*, classList )
_field_obj_( TreeListControl*, classData )
_class_rtti_end_





class ClassRegistryBrowser : public Application {
public:

	String classDocsRootURL;
	HTMLBrowserControl* classDocBrowser;
	ListViewControl* classList;
	TreeListControl* classData;

	ClassRegistryBrowser( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );


		addCallback( new ClassProcedure1<Event*,ClassRegistryBrowser>(this, &ClassRegistryBrowser::onClassSelected), "ClassRegistryBrowser::onClassSelected" );		
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ClassRegistryBrowserWindow);

		ClassRegistryBrowserWindow* mainWindow = 
			(ClassRegistryBrowserWindow*) Frame::createWindow( classid(ClassRegistryBrowserWindow) );

		setMainWindow(mainWindow);
		mainWindow->initializeSettings(true);


		classDocBrowser = mainWindow->classDocBrowser;
		classList = mainWindow->classList;
		classData = mainWindow->classData;

		classDocsRootURL = "http://vcf-online.org/docs/src_manual/";
		refresh();

		mainWindow->show();
		
		return result;
	}

	void refresh()
	{
		ListModel* lm = classList->getListModel();

		lm->empty();

		TreeModel* tm =  classData->getTreeModel();
		tm->empty();

	
		uint32 totBytes = 0;

		Enumerator<Class*>* classes = ClassRegistry::getClasses();
		while ( classes->hasMoreElements() ) {
			Class* clazz = classes->nextElement();

			totBytes += clazz->sizeOf();

			lm->add( clazz->getClassName() );

			classList->getItem( lm->getCount()-1 )->setImageIndex( ciClassImg );
		}

		Label* tbLable = (Label*) getMainWindow()->findComponent( "totalBytes", true );
		tbLable->setCaption( StringUtils::toString(totBytes) );

	}

	void onClassSelected( Event* e ) {		

		ListModel* lm = classList->getListModel();
		String className = lm->get( classList->getSelectedItem() );

		Class* clazz = ClassRegistry::getClass( className );
		if ( NULL != clazz ) {
			refreshClassData( clazz );


			String ns = "";

			size_t pos = className.find( "VCF::" );

			String classBaseName = className;
			if ( pos != String::npos ) {
				classBaseName = className.substr( pos + 5, className.length() - (pos+5) );
			}

			classDocBrowser->setCurrentURL( classDocsRootURL + "classVCF_1_1" + classBaseName + ".html" );
		}
	}

	void refreshClassData( Class* clazz ) {
		TreeModel* tm =  classData->getTreeModel();
		tm->empty();


		tm->insert( "Class Name:  " + clazz->getClassName() );
		tm->insert( "ID:  " + clazz->getID() );		


		TreeModel::Key superKey = tm->insert( "Class Hierarchy:" );

		std::vector<Class*> derived;
		Class* super = clazz->getSuperClass();
		while ( NULL != super ) {
			derived.push_back( super );
			super = super->getSuperClass();
		}


		std::vector<Class*>::reverse_iterator it = derived.rbegin();
		while ( it != derived.rend() ) {
			Class* super = *it;
			
			superKey = tm->insert( super->getClassName(), superKey );
			classData->getItemFromKey(superKey)->setImageIndex( ciClassImg );

			++it;
		}

		superKey = tm->insert( clazz->getClassName(), superKey );	
		classData->getItemFromKey(superKey)->setImageIndex( ciClassImg );


		TreeModel::Key propsKey = tm->insert( "Properties:" );

		Enumerator<Property*>* props = clazz->getProperties();

		while ( props->hasMoreElements() ) {
			Property* prop = props->nextElement();

			TreeModel::Key k = tm->insert( prop->getDisplayName(), propsKey );
			classData->getItemFromKey(k)->setImageIndex( ciPropertyImg );

			tm->insertSubItem( k, 0, prop->getTypeClassName() );

		}


		classData->getItemFromKey(propsKey)->expand( true );

		
		TreeModel::Key delegatesKey = tm->insert( "Delegates:" );

		Enumerator<DelegateProperty*>* delegates = clazz->getDelegates();

		while ( delegates->hasMoreElements() ) {
			DelegateProperty* prop = delegates->nextElement();

			TreeModel::Key k = tm->insert( prop->getDelegateName(), delegatesKey );
			classData->getItemFromKey(k)->setImageIndex( ciDelegateImg );

			tm->insertSubItem( k, 0, prop->getDelegateClassName() );
		}

		classData->getItemFromKey(delegatesKey)->expand( true );


		classData->getItemFromKey(superKey)->expand( true );
	}
};


int main(int argc, char *argv[])
{
	Application* app = new ClassRegistryBrowser( argc, argv );

	Application::main();
	
	HTMLKit::terminate();
	
	return 0;
}


