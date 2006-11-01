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
	fieldDefs_->setDataSet( this );
}

DataSet::~DataSet()
{
	close();

	
	while ( !dataSources_.empty() ) {
		removeDataSource( dataSources_.front() );
	}

	deleteFields();

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
	if ( active != active_ ) {
		if ( active ) {
			Event e(this,0);
			BeforeOpen.fireEvent(&e);

			try {
				openCursor( false );

				setState( dssBrowse );
			}
			catch ( BasicException& ) {
				setState( dssInactive );

				closeCursor();

				throw;
			}

			Event e2(this,0);
			AfterOpen.fireEvent(&e2);

			Event e3(this,0);
			AfterScroll.fireEvent(&e3);

			active_ = active;
		}
		else {
			Event e(this,0);
			BeforeClose.fireEvent(&e);

			setState( dssInactive );

			closeCursor();

			Event e2(this,0);
			AfterClose.fireEvent(&e2);

			active_ = active;
		}
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

	switch ( fieldType ) {
		case dftString : {
			result = classid(VCF::StringField);
		}
		break;
	}

	return result;
}

void DataSet::deleteFields()
{
	DataFieldArray::Vector::iterator it = fields_().begin();
	while ( it != fields_().end() ) {
		DataField* field = *it;
		field->free();

		++it;
	}

	fields_().clear();
}


void DataSet::createFields()
{
	std::vector<FieldDefinition>& defs = fieldDefs_->fields();
	for ( size_t i=0;i<defs.size();i++ ) {
		if ( defs[i].dataType != dftUnknown ) {
			DataField* field = defs[i].createField();

			if ( NULL != field ) {
				fields_().push_back( field );
			}
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

void DataSet::handleDataEvent( Event* e )
{
	switch ( e->getType() ) {

	}
}

void DataSet::setState( DataSetState val )
{
	if ( val != state_ ) {
		state_ = val;

		modified_ = false;

		Event e(this,deUpdateState);
		handleDataEvent(&e);
	}	
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

void DataSet::openCursor( bool query )
{
	if ( query ) {
		internal_initFieldDefinitions();
	}
	else {
		openData();
	}
}

void DataSet::closeCursor()
{

}

void DataSet::openData()
{
	defaultFields_ = fields_().empty();

	internal_open();

	bof_ = true;
}


void DataSet::setParam( const String& param, VariantData value )
{
    params_[param] = value;
}

VariantData DataSet::getParam ( const String& param )
{
    return params_[param];
}

Enumerator<DataField*>* DataSet::getFields()
{
	return fields_.getEnumerator();
}