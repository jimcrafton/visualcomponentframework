#include "DatabaseKit.h"

using namespace VCF;

DataSet::DataSet()
    : Object(), columnCount(0)
{
 selectSQL_ = new StringList();
}

DataSet::~DataSet()
{
 delete selectSQL_;
}

void DataSet::setDatabase( Database* db )
{
    db_ = db;

    if ( tr_ == NULL ) {
        //transaction_ = database_->getTransaction();
    }
}

void DataSet::setTransaction( Transaction* tr )
{
    tr_ = tr;
}

void DataSet::setActive( bool active )
{
    if ( active ) {
        internalOpen();
    } else {
        internalClose();
    }
}

void DataSet::open()
{
    setActive( true );
}

void DataSet::close()
{
    setActive( false );
}

StringList* DataSet::getSelectSQL()
{
 return selectSQL_;
}
