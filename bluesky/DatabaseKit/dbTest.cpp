////dbTest.cpp

#include "DatabaseKit.h"


#include "SQLite3Kit.h"




class QueryPerformanceException : public std::logic_error {
public:
	QueryPerformanceException() : std::logic_error("QueryPerformanceFrequency() failed. It's probably not supported!!") {}
};


class HiResClock {
public:

	HiResClock(){
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
		if ( !QueryPerformanceFrequency( &frequency_ ) ) {
			throw QueryPerformanceException();
		}
	}



	void start() {
		if ( !QueryPerformanceCounter( &performanceCounter1_ ) ) {
			throw QueryPerformanceException();
		}
	}

	void stop() {
		if ( !QueryPerformanceCounter( &performanceCounter2_ ) ) {
			throw QueryPerformanceException();
		}
	}

	void clear() {
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {	

		return (double)(performanceCounter2_.LowPart - performanceCounter1_.LowPart)/(double)frequency_.LowPart;
	}
protected:
	LARGE_INTEGER performanceCounter1_;
	LARGE_INTEGER performanceCounter2_;
	LARGE_INTEGER frequency_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};











/**
Current test results (Nov 18 2006) with release build
Iterating through a table with 2715 rows, 4 colums

Simple C++ layer:	0.00265996 seconds
DatabaseKit layer:	0.00615197 seconds

*/



using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	DatabaseKit::init( argc, argv );

	{
		//test simple calls of SQLite to compare the performance 
		//to our more complex API

		Test::DB db("test.db3");

		HiResClock clock;
		clock.start();
		Test::ResultSet rs = db.execSQLWithResults( "select * from Person;" );
		while (!rs.eof()) {
			for ( int i=0;i<rs.getColumnCount();i++ ) {
				Test::Column col = rs[i];
			
				//System::println( "Field name: " + col.name() + " value: " + (std::string)col );
			}

			
			++rs;
		}

		clock.stop();
		System::println( Format("Iteration took %0.8f seconds.") % clock.duration() );
	}


	{

		HiResClock clock;


		DataSet* dataSet = DatabaseToolkit::createDataSet( "SQLiteType" );

		dataSet->setParam( "databasename", "test.db3" );
		dataSet->setParam( "tablename", "Person" );



		DataSource* dbSrc = new DataSource();

		try {
			
			dbSrc->setDataSet( dataSet );
			

			std::vector<String> fieldNames;
			
			if ( dataSet->getFieldNames( fieldNames ) ) {

				for (int i=0;i<fieldNames.size();i++ ) {
					System::println( "Field name: " + fieldNames[i] );
				}
			}
			else {
				System::println( "No field names available." );
			}


			System::println( "------------------------------------------------------------------------------" );
			
			System::println( "Activating data set..." );

			dataSet->setActive(true);
			
			System::println( "------------------------------------------------------------------------------" );
			
			if ( dataSet->isActive() ) {		
			
				clock.start();

				while ( !dataSet->isEOF() ) {			
					Enumerator<DataField*>* fields = dataSet->getFields();
					
					while ( fields->hasMoreElements() ) {
						DataField* field = fields->nextElement();
						//System::println( "Field name: " + field->getName() + " value: " + field->getAsString() );
					}
					dataSet->next();
				}

				clock.stop();
				System::println( Format("Iteration took %0.8f seconds.") % clock.duration() );
			}			
		}
		catch ( BasicException& e ) {
			System::println( "Exception: " + e.getMessage() );
		}

		dbSrc->free();


		delete dataSet;

	}

	DatabaseKit::terminate();

	FoundationKit::terminate();
	return 0;
}


