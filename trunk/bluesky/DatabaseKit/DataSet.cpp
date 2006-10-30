#include "DatabaseKit.h"

using namespace VCF;

DataSet::DataSet()
    : Object(), columnCount(0),
	fieldDefs_(NULL),
	active_(false),
	state_(dssInactive),
	canModify_(false),
	bof_(false),
	eof_(false),
	modified_(false),
	defaultFields_(true)
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
	active_ = active;
    if ( active ) {
        internal_open();
    } 
	else {
        internal_close();
    }
}

bool DataSet::isActive()
{
	return active_;
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

		initFieldDefinitions();

		fieldDefs_->setUpdated( true );
	}
}

void DataSet::initFieldDefinitions()
{
	if ( !isActive() ) {
		internal_initFieldDefinitions();
	}
}

Class* DataSet::getFieldClass( int fieldType )
{
	Class* result = NULL;

	return result;
}

void DataSet::createFields()
{
	std::vector<FieldDefinition>& defs = fieldDefs_->fields();
	for ( size_t i=0;i<defs.size();i++ ) {
		if ( defs[i].dataType != ftUnknown ) {
			DataField* field = defs[i].createField();
		}
	}
}

void DataSet::addDataSource( DataSource* source )
{
	DataSourceArray::iterator found = std::find( dataSources_.begin(), dataSources_.end(), source );
	if ( found == dataSources_.end() ) {
		dataSources_.push_back( source );
		source->setDataSet( this );

		source->updateState();
	}
}

void DataSet::removeDataSource( DataSource* source )
{
	DataSourceArray::iterator found = std::find( dataSources_.begin(), dataSources_.end(), source );
	if ( found == dataSources_.begin() ) {
		source->setDataSet( NULL );

		dataSources_.erase( found );

		source->updateState();
	}
}


void DataSet::setState( DataSetState val )
{
	state_ = val;
}


void DataSet::first()
{

}

void DataSet::next()
{

}

void DataSet::refresh()
{

}

void DataSet::edit()
{

}

void DataSet::appendRecord()
{

}

void DataSet::deleteRecord()
{

}

void DataSet::post()
{

}

void DataSet::cancel()
{

}