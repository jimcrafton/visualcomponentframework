#include "DatabaseKit.h"

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

Database* DatabaseToolkit::createDatabase( DatabaseType type )
{
    if ( type == dtFirebird ) {
        return new FBDatabase();
    }

    return NULL;
}

DataSet* DatabaseToolkit::createDataSet( DatabaseType type )
{
    if ( type == dtFirebird ) {
        return new FBDataSet();
    }

    return NULL;
}
