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
	filtered_(false),
	filterOptions_(foNoOptions),
	recordSize_(0),
	activeRecordIndex_(DataSet::NoRecPos),
	currentRecordIndex_(DataSet::NoRecPos),
	locale_(NULL)
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

	delete locale_;
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

bool DataSet::getFieldNames( std::vector<String>& fieldNames )
{
	fieldNames.clear();

	if ( fields_->empty() ) {
		updateFieldDefs();

		std::vector<FieldDefinition>& defs = fieldDefs_->fields();
		for ( size_t i=0;i<defs.size();i++ ) {			 
			fieldNames.push_back( defs[i].name );
		}
	}
	else {
		DataFieldArray::Vector::iterator it = fields_->begin();
		while ( it != fields_->end() ) {
			DataField* field = *it;
			
			fieldNames.push_back( field->getName() );
			
			++it;
		}
	}

	return !fieldNames.empty();
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

		case dftBoolean : {
			result = classid(VCF::BooleanField);
		}
		break;

		case dftDate : case dftTime : case dftDateTime :{
			result = classid(VCF::DateTimeField);
		}
		break;

		case dftFloat : {
			result = classid(VCF::DoubleField);
		}
		break;

		case dftSmallint : case dftInteger : case dftWord : {
			result = classid(VCF::IntegerField);
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
		case deFieldChange : {
			DataField* field = (DataField*)e->getSource();
			if ( field->getKind() & fkData ) { //add fkInternalCalc later
				modified_ = true;	
			}

			if ( this->state_ != dssSetKey ) {
				if ( field->getKind() == fkData ) {
					//if we internally calc fields, then recalc them now...
				}
				//else see if we need to auto calc field sizes???

				field->change();
			}
		}
		break;

		case dePropertyChange : {
			this->fieldDefs_->setUpdated(false);
		}
		break;
	}

	//deal with disable counts here??

	DataSourceArray::iterator it = dataSources_.begin();
	while ( it != dataSources_.end() ) {
		DataSource* dataSrc = *it;
		dataSrc->handleDataEvent( e );
		++it;
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
	checkMode( cmsBrowse );
	
	this->internal_refresh();

	resync(0);
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

void DataSet::checkRequiredFields()
{
	DataFieldArray::Vector::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;

		if ( field->isRequired() && 
				(!field->isReadOnly()) && 
				(field->getKind() == fkData) &&
				field->isNull() ) {

			//focus control here somehow...
			throw DatabaseError( Format("Field \"%s\" is a required field and needs data.") % field->getDisplayName() );
		}

		++it;
	}
}

void DataSet::post()
{
	updateRecord();

	switch ( state_ ) {
		case dssEdit : case dssInsert : {
			Event e(this,deCheckBrowseMode);
			handleDataEvent(&e);

			checkRequiredFields();

			Event e2(this,0);
			BeforePost.fireEvent(&e2);

			try {
				internal_post();
			}
			catch (...) {
				Event e3(this,0);
				PostError.fireEvent( &e3 );
			}


			freeFieldBuffers();

			setState( dssBrowse );

			resync( 0 );

			Event e4(this,0);
			AfterPost.fireEvent(&e4);
		}
		break;
	}
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

	Event e(this,dePropertyChange);
	handleDataEvent( &e );
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
		
		for (size_t i=dataSources_.size()-1;(i>=0) && (i<dataSources_.size());i-- ) {
			//possibly modify the maxRecCount from data source links in the future...
			DataSource* dataSrc = dataSources_[i];
			size_t dlCount = dataSrc->getDataLinkCount();

			for (size_t j=dlCount-1;(j>=0) && (j<dlCount);j-- ) {
				DataLink* dataLink =  dataSrc->getDataLink(j);
				//compare the dl's record count to maxRecCount if it's bigger then use it!
			}
		}
		

		setRecordCount( maxRecCount );
	}
}

Locale* DataSet::getLocale()
{
	return locale_;
}

void DataSet::setLocale( Locale* val )
{
	delete locale_;
	locale_ = new Locale( val->getLanguageCode(), val->getCountryCode() );
}

size_t DataSet::getRecordCount()
{
	return records_.size();	
}

void DataSet::checkFieldName( const String& fieldName )
{
	if ( fieldName.empty() ) {
		throw DatabaseError( "Invalid Field name. Field name is empty/blank." );
	}

	if ( findField( fieldName ) != NULL ) {
		throw DatabaseError( "Invalid Field name. Field name already exists." );
	}
}

DataField* DataSet::findField( const String& fieldName )
{
	DataField* result = NULL;

	DataFieldArray::Vector::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;
		if ( fieldName == field->getName() ) {
			result = field;
			break;
		}
		++it;
	}

	return result;
}

DataField* DataSet::fieldByName( const String& fieldName )
{
	DataField* result = findField( fieldName );

	if ( NULL == result ) {
		throw DatabaseError("No Field found that's named \"" + fieldName + "\"." );
	}

	return result;
}

size_t DataSet::indexOfField( DataField* field )
{
	size_t result = NoFieldPos;

	DataFieldArray::Vector::iterator found = std::find( fields_->begin(), fields_->end(), field );
	if ( found != fields_->end() ) {
		result = found - fields_->begin();
	}

	return result;
}

void DataSet::setFiltered( bool val )
{
	filtered_ = val;
}

void DataSet::setFilter( const String& val )
{
	filter_ = val;
}

void DataSet::setFilterOptions( int val )
{
	filterOptions_ = (FilterOptions)val;
}

void DataSet::updateRecord()
{
	if ( !((state_ & dssEdit) || (state_ & dssInsert)) ) {
		throw DatabaseError("Data set not in editing mode.");
	}

	Event e(this,deUpdateRecord);
	handleDataEvent( &e );
}

void DataSet::freeFieldBuffers()
{
	DataFieldArray::Vector::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;
		
		field->freeBuffers();

		++it;
	}	
}

void DataSet::cursorPositionChanged()
{
	currentRecordIndex_ = DataSet::NoRecPos;	
}

void DataSet::resync( int mode )
{
	if ( mode & rmExact ) {
		cursorPositionChanged();

		GetResultType res = getRecord( records_[ records_.size()-1 ], grmCurrent );

		if ( res != grOK ) {
			throw DatabaseError("Data set unable to modify the record. The record was not found.");
		}
	}
	else {

		if ( (getRecord( records_[ records_.size()-1 ], grmCurrent ) != grOK) &&
			(getRecord( records_[ records_.size()-1 ], grmNext ) != grOK) ) {

			clearRecords();
			Event e(this,deDataSetChange);
			return;
		}

		if ( mode & rmCenter ) {

		}
		else {

		}

		activateRecords();

		try {
			getNextRecords();
		}
		catch (...){

		}
	}

	Event e(this,deDataSetChange);
	handleDataEvent( &e );
}