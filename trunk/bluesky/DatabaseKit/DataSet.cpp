#include "DatabaseKit.h"

using namespace VCF;

DataSet::DataSet()
    : Object(), columnCount(0),
	fieldDefs_(0)
{
	selectSQL_ = new StringList();
	fieldDefs_ = new FieldDefinitions(); 
}

DataSet::~DataSet()
{
	delete selectSQL_;
	delete fieldDefs_;
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

void DataSet::updateFieldDefs()
{
	if ( !fieldDefs_->isUpdated() ) {
		


		fieldDefs_->setUpdated( true );
	}
}

void DataSet::initFieldDefs()
{
	internal_initFieldDefs();
}