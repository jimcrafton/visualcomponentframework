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


	dbSrc->setDataSet( dataSet );


	dataSet->setActive(true);



	dbSrc->free();


	delete dataSet;


	DatabaseKit::terminate();

	FoundationKit::terminate();
	return 0;
}


