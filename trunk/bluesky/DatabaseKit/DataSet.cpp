#include "DatabaseKit.h"

using namespace VCF;

DataSet::DataSet()
    : Object(),
	fieldDefs_(NULL),
	active_(false),
	state_(dssInactive),
	canModify_(false),
	bof_(false),
	eof_(false),
	modified_(false),
	defaultFields_(true),
	recordSize_(0),
	activeRecordIndex_(DataSet::NoRecPos),
	currentRecordIndex_(DataSet::NoRecPos),
	locale_("en", "US")
{
	fieldDefs_ = new FieldDefinitions(); 
	fieldDefs_->setDataSet( this );

	setLocale( System::getCurrentThreadLocale() );
}

DataSet::~DataSet()
{
	close();
	
	while ( !dataSources_.empty() ) {
		removeDataSource( dataSources_.front() );
	}

	deleteFields();

	delete fieldDefs_;
}

void DataSet::setDatabase( Database* db )
{
    db_ = db;
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
	DataFieldArray::Vector::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;
		field->free();

		++it;
	}

	fields_->clear();
}


void DataSet::createFields()
{
	std::vector<FieldDefinition>& defs = fieldDefs_->fields();
	for ( size_t i=0;i<defs.size();i++ ) {
		if ( defs[i].dataType != dftUnknown ) {
			DataField* field = defs[i].createField();

			if ( NULL != field ) {
				fields_->push_back( field );
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

void DataSet::checkMode( CheckModeState mode )
{
	switch ( mode ) {
		case cmsBrowse : {
			checkMode( cmsActive );

			Event e(this,deCheckBrowseMode);
			handleDataEvent(&e);

			switch ( getState() )  {
				case dssEdit : case dssInsert : {
					//update the record???
				}
				break;

				case dssSetKey : {
					post();
				}
				break;
			}
		}
		break;

		case cmsActive : {
			if ( dssInactive == state_ ) {
				throw DatabaseError( "Dataset is inactive!" );
			}
		}
		break;

		case cmsInactive : {

		}
		break;
	}
}

void DataSet::clearRecords()
{
	bof_ = true;
	eof_ = true;
	currentRecordIndex_ = 0;
	activeRecordIndex_ = 0;	
}

void DataSet::activateRecords()
{
	bof_ = false;
	eof_ = false;
	currentRecordIndex_ = 0;
	activeRecordIndex_ = 0;
}

void DataSet::first()
{
	checkMode( cmsBrowse );

	Event e1(this,0);
	BeforeScroll.fireEvent(&e1);

	clearRecords();


	try {
		internal_first();

		getNextRecord();

		getNextRecords();
	}
	catch ( BasicException& ) {

	}
	catch ( ... ) {

	}

	bof_ = true;
	Event e2(this,deDataSetChange);
	handleDataEvent(&e2);

	Event e3(this,0);
	AfterScroll.fireEvent(&e3);
}

void DataSet::next()
{
	checkMode( cmsBrowse );
	Event e1(this,0);
	BeforeScroll.fireEvent(&e1);

	if ( !isEOF() ) {
		bof_ = false;
		eof_ = false;

		if ( activeRecordIndex_ < (records_.size() - 1) ) {
			activeRecordIndex_ ++;
		}
		else {			
			if ( getNextRecord() ) {
				if ( activeRecordIndex_ < (records_.size() - 1) ) {
					activeRecordIndex_ ++;
				}
			}
			else {
				eof_ = true;
			}
		}

		Event e2(this,0);
		AfterScroll.fireEvent(&e2);
	}
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
	defaultFields_ = fields_->empty();

	currentRecordIndex_ = 0;

	internal_open();

	updateRecordSize();

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

void DataSet::setRecordCount( size_t numberOfRecords )
{
	if ( numberOfRecords == records_.size() ) {
		return;
	}

	if ( numberOfRecords < records_.size() ) {
		for ( size_t i=numberOfRecords;i<records_.size();i++ ) {
			Record* record =  records_[i];
			
			delete record;
		}
		RecordsArray::iterator it = records_.begin() + numberOfRecords;
		records_.erase( it, records_.end() );
	}
	else {
		try {
			size_t oldSize = records_.size();

			records_.resize(numberOfRecords);
			
			if ( oldSize == 0 ) {
				oldSize = 1;
			}

			for ( size_t i=oldSize-1;i<records_.size();i++ ) {
				records_[i] = allocateRecordData();
			}

		}
		catch ( BasicException& ) {
			throw;
		}
	}

	VCF_ASSERT( numberOfRecords == records_.size() );

	getNextRecords();
}

size_t DataSet::getNextRecords()
{
	size_t result = 0;
	while ( (result < records_.size()) && getNextRecord() ) {		
		result ++;		
	}

	return result;
}

bool DataSet::getNextRecord()
{
	bool result = false;

	GetRecordMode mode = grmNext;

	if ( records_.size() > 0 ) {
		//currentRecordIndex_ = records_.size() - 1; 
	}	
	
	GetResultType res = getRecord( records_[ currentRecordIndex_ ], mode );
	if ( grFailed != res ) {
		result = true;		
	}

	if ( result ) {
		if ( records_.size() - 1 == 0 ) {
			activateRecords();
		}

		currentRecordIndex_ = records_.size() - 1; 		
	}

	return result;
}


void DataSet::updateRecordSize()
{
	if ( isCursorOpen() ) {
		size_t maxRecCount = 1;

		for (size_t i=0;i<dataSources_.size();i++ ) {
			//possibly modify the maxRecCount from data source links in the future...
		}

		setRecordCount( maxRecCount );
	}
}

Locale* DataSet::getLocale()
{
	return &locale_;
}

void DataSet::setLocale( Locale* val )
{
	locale_ = *val;
}

size_t DataSet::getRecordCount()
{
	return records_.size();	
}