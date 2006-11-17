////dbTest.cpp

#include "DatabaseKit.h"

using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	DatabaseKit::init( argc, argv );


	DataSet* dataSet = DatabaseToolkit::createDataSet( "SQLiteType" );

	dataSet->setParam( "databasename", "test.db3" );
	dataSet->setParam( "tablename", "Person" );



	DataSource* dbSrc = new DataSource();

	try {
		
		dbSrc->setDataSet( dataSet );
		
		
		dataSet->setActive(true);
		
		
		
		if ( dataSet->isActive() ) {		
			
			while ( !dataSet->isEOF() ) {			
				Enumerator<DataField*>* fields = dataSet->getFields();
				
				while ( fields->hasMoreElements() ) {
					DataField* field = fields->nextElement();
					System::println( "Field name: " + field->getName() + " value: " + field->getAsString() );
				}
				dataSet->next();
			}
		}
		
	}
	catch ( BasicException& e ) {
		System::println( "Exception: " + e.getMessage() );
	}

	dbSrc->free();


	delete dataSet;


	DatabaseKit::terminate();

	FoundationKit::terminate();
	return 0;
}


