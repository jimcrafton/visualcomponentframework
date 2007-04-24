//dbtest2.cpp


#include "DatabaseUIKit.h"

#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/CommandButton.h"

#include "DataLabel.h"
#include "DataLink.h"

using namespace VCF;







class dbtest2Window : public Window {
public:
	dbtest2Window() {
		setCaption( "dbtest2" );
		dataSet = new DataSet();
		dataSet->setPeerType( "SQLiteType" );

		//DatabaseToolkit::createDataSet( "SQLiteType" );

		dataSet->setParam( "databasename", "test.db3" );
		dataSet->setParam( "tablename", "Person" );

		dbSrc = new DataSource();
		dbSrc->setEnabled( true );

		dbSrc->setDataSet( dataSet );


		DataLabel* label1 = new DataLabel();
		label1->setCaption( "Test data here..." );
		add( label1 );
		label1->setBounds( 10, 20, 100, 25 );

		label1->setDataSource( dbSrc );
		label1->setFieldName( "FirstName" );


		DataLabel* label2 = new DataLabel();
		label2->setCaption( "Test data here..." );
		add( label2 );
		label2->setBounds( 110, 20, 100, 25 );

		label2->setDataSource( dbSrc );
		label2->setFieldName( "LastName" );


		dataSet->setActive( true );

		CommandButton* first = new CommandButton();
		first->setCaption( "First" );
		first->ButtonClicked +=
			new GenericEventHandler<dbtest2Window>(this,&dbtest2Window::onFirst,"dbtest2Window::onFirst");

		add( first );
		first->setBounds( 10, 120, 100, 35 );


		CommandButton* next = new CommandButton();
		next->setCaption( "Next" );
		next->ButtonClicked +=
			new GenericEventHandler<dbtest2Window>(this,&dbtest2Window::onNext,"dbtest2Window::onNext");

		add( next );
		next->setBounds( 10, 70, 100, 35 );		

	}

	virtual ~dbtest2Window(){
		dbSrc->free();
		dataSet->free();
	};


	void onFirst( Event* ) {
		dataSet->first();
	}

	void onNext( Event* ) {
		dataSet->next();
	}

	DataSet* dataSet;
	DataSource* dbSrc;
		
};




class dbtest2Application : public Application {
public:

	dbtest2Application( int argc, char** argv ) : Application(argc, argv) {
		DatabaseUIKit::init( argc, argv );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new dbtest2Window();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

	virtual void terminateRunningApplication() {
		DatabaseUIKit::terminate();

		Application::terminateRunningApplication();
	}

};


int main(int argc, char *argv[])
{
	Application* app = new dbtest2Application( argc, argv );

	Application::main();
	
	return 0;
}


