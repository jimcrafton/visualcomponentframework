#include "DatabaseKit.h"
#include "SQLiteDatabase.h"
#include "SQLiteDataSet.h"
#include "ADODataSet.h"



using namespace VCF;

DatabaseToolkit* DatabaseToolkit::Instance = NULL;

void DatabaseToolkit::create()
{
    DatabaseToolkit::Instance = new DatabaseToolkit();

    VCF_ASSERT( NULL != DatabaseToolkit::Instance );
}

void DatabaseToolkit::destroy()
{
    delete DatabaseToolkit::Instance;
}

Database* DatabaseToolkit::createDatabase( const String& type )
{
	VCF_ASSERT( !type.empty() );

    if ( type == SQLITETYPE ) {
		return new SQLiteDatabase();
    }

    return NULL;
}

DataSet* DatabaseToolkit::createDataSet( const String& type )
{
	VCF_ASSERT( !type.empty() );

    if ( type == SQLITETYPE ) {
        return new SQLiteDataSet();
    }
	else if ( type == ADOTYPE ) {
		return new ADODataSet();
	}

    return NULL;
}
