#include "DatabaseKit.h"
#include "SQLiteDatabase.h"
#include "SQLiteDataSetPeer.h"
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

DataSetPeer* DatabaseToolkit::createDataSetPeer( const String& type )
{
	VCF_ASSERT( !type.empty() );

    if ( type == SQLITETYPE ) {
        return new SQLiteDataSetPeer();
    }
	return NULL;
}
