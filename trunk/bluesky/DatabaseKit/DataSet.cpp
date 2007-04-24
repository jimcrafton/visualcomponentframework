#include "DatabaseKit.h"
#include "DataLink.h"


using namespace VCF;

DataSet::DataSet()
    : Component(),
	fieldDefs_(NULL),
	active_(false),
	state_(dssInactive),
	canModify_(true),
	bof_(false),
	eof_(false),
	modified_(false),
	defaultFields_(true),
	filtered_(false),
	filterOptions_(foNoOptions),
	recordCount_(0),
	usableRecordCount_(0),
	activeRecordIndex_(DataSet::NoRecPos),
	currentRecordIndex_(DataSet::NoRecPos),
	locale_(NULL),
	db_(NULL),
	peer_(NULL)
{
	fieldDefs_ = new FieldDefinitions(); 
	fieldDefs_->setDataSet( this );

	setLocale( System::getCurrentThreadLocale() );
}

DataSet::~DataSet()
{
	VCF_ASSERT( dataSources_.empty() );
	VCF_ASSERT( NULL == locale_ );
	VCF_ASSERT( NULL == fieldDefs_ );
	VCF_ASSERT( dssInactive == state_ );
	

}

void DataSet::destroy()
{
	close();
	
	while ( !dataSources_.empty() ) {
		removeDataSource( dataSources_.front() );
	}

	deleteFields();

	delete fieldDefs_;
	fieldDefs_ = NULL;


	delete locale_;
	locale_ = NULL;	

	state_ = dssInactive;

	delete peer_;

	Component::destroy();
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
		peer_->initFieldDefinitions();
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

			if ( state_ != dssSetKey ) {
				if ( field->getKind() == fkData ) {
					//if we internally calc fields, then recalc them now...
				}
				//else see if we need to auto calc field sizes???

				field->change();
			}
		}
		break;

		case dePropertyChange : {
			fieldDefs_->setUpdated(false);
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
					updateRecord();

					if ( isModified() ) {
						post();
					}
					else {
						cancel();
					}
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
	recordCount_ = 0;
}

void DataSet::activateRecords()
{
	bof_ = false;
	eof_ = false;
	currentRecordIndex_ = 0;
	activeRecordIndex_ = 0;
	recordCount_ = 1;
}

void DataSet::first()
{
	checkMode( cmsBrowse );

	Event e1(this,0);
	BeforeScroll.fireEvent(&e1);

	clearRecords();


	try {
		this->peer_->first();

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
		size_t oldRecCount = recordCount_;


		if ( activeRecordIndex_ < recordCount_- 1 ) {
			activeRecordIndex_ ++;
		}
		else {			
			if ( getNextRecord() ) {
				if ( activeRecordIndex_ < (recordCount_ - 1) ) {
					activeRecordIndex_ ++;
				}
			}
			else {
				eof_ = true;
			}
		}


		if ( oldRecCount != recordCount_ ) {
			Event e(this,deDataSetChange);
			handleDataEvent( &e );
		}
		else {
			Event e(this,deDataSetScroll);
			handleDataEvent( &e );
		}

		Event e2(this,0);
		AfterScroll.fireEvent(&e2);
	}
}

void DataSet::refresh()
{
	checkMode( cmsBrowse );
	
	this->peer_->refresh();

	resync(0);
}

void DataSet::edit()
{
	if ( (state_ != dssEdit) && (state_ != dssInsert) ) {
		//no insert yet...
		checkMode( cmsBrowse );

		if ( !canModify_ ) {
			throw DatabaseError( "Can't modify, the Dataset is in read-only mode." );
		}

		Event e1(this,0);
		BeforeEdit.fireEvent(&e1);

		try {
			this->peer_->edit();
		}
		catch ( ... ) {
			Event e2(this,0);
			EditError.fireEvent(&e2);
		}

		setState( dssEdit );

		Event e3(this,deRecordChange);
		handleDataEvent( &e3 );

		Event e4(this,0);
		AfterEdit.fireEvent(&e4);
	}
}

void DataSet::beginNewRecord()
{
	checkMode( cmsBrowse );

	if ( !canModify_ ) {
		throw DatabaseError( "Can't modify, the Dataset is in read-only mode." );
	}

	Event e1(this,0);
	BeforeInsert.fireEvent(&e1);

	Event e2(this,0);
	BeforeScroll.fireEvent(&e2);
}

void DataSet::endNewRecord()
{
	setState( dssInsert );

	try {
		handleNewRecord();
	}
	catch (...) {
		//update cursor pos???
		freeFieldBuffers();

		setState( dssBrowse );

		resync(0);
		throw;
	}

	modified_ = false;

	Event e1(this,deDataSetChange);
	handleDataEvent( &e1 );

	Event e2(this,0);
	AfterInsert.fireEvent(&e2);

	Event e3(this,0);
	AfterScroll.fireEvent(&e3);
}

void DataSet::handleNewRecord()
{
	Event e1(this,0);
	NewRecord.fireEvent(&e1);	
}

void DataSet::initNewRecord( Record* record )
{
	VCF_ASSERT( NULL != record );
	
	this->peer_->initNewRecord( record );

	//clear calc fields
	//bookmark this inserted rec!
}

void DataSet::appendRecord()
{
	beginNewRecord();

	VCF_ASSERT( activeRecordIndex_ != DataSet::NoRecPos );

	Record* record = records_[ activeRecordIndex_ ];

	initNewRecord( record );	

	if ( recordCount_ == 0 ) {

	}
	else {

	}

	if ( recordCount_ < this->usableRecordCount_ ) {
		recordCount_ ++;
	}

	endNewRecord();
}

void DataSet::deleteRecord()
{
	checkMode( cmsActive );

	if ( (state_ == dssSetKey) || (state_ == dssInsert) ) {
		cancel();
	}
	else {
		if ( 0 == recordCount_ ) {
			throw DatabaseError( "Can't delete from an empty dataset." );
		}

		Event e(this,deCheckBrowseMode);
		handleDataEvent(&e);

		Event e1(this,0);
		BeforeDelete.fireEvent( &e1 );

		Event e2(this,0);
		BeforeScroll.fireEvent( &e2 );

		this->peer_->deleteRecord();

		freeFieldBuffers();
		setState( dssBrowse );
		resync( 0 );

		Event e3(this,0);
		AfterDelete.fireEvent( &e3 );

		Event e4(this,0);
		AfterScroll.fireEvent( &e4 );

	}
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
				this->peer_->post();
			}
			catch (BasicException& e) {
				DataErrorEvent e3(this);
				e3.reason = e.getMessage();

				PostError.fireEvent( &e3 );
			}
			catch (...) {
				DataErrorEvent e3(this);
				e3.reason = "Unknown error.";

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
	if ( (state_ == dssEdit) || (state_ == dssInsert) ) {
		Event e(this,deCheckBrowseMode);
		handleDataEvent(&e);

		Event e1(this,0);
		BeforeCancel.fireEvent( &e1 );

		//update cursor pos/????
		
		if ( state_ == dssEdit ) {
			this->peer_->cancel();
		}

		freeFieldBuffers();
		setState( dssBrowse );
		resync(0);


		Event e2(this,0);
		AfterCancel.fireEvent( &e2 );
	}
}

void DataSet::openCursor( bool query )
{
	if ( query ) {
		this->peer_->initFieldDefinitions();
	}
	else {
		openData();
	}
}

void DataSet::closeCursor()
{
	freeFieldBuffers();

	clearRecords();

	this->peer_->close();

	defaultFields_ = false;

}

void DataSet::openData()
{
	defaultFields_ = fields_->empty();

	currentRecordIndex_ = 0;

	this->peer_->open();

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
	if ( numberOfRecords == usableRecordCount_ ) {
		return;
	}

	if ( this->usableRecordCount_ > numberOfRecords  && recordCount_ > 0 ) {

		int delta = 0;
		for (size_t i=dataSources_.size()-1;(i>=0) && (i<dataSources_.size());i-- ) {
			
			DataSource* dataSrc = dataSources_[i];
			size_t dlCount = dataSrc->getDataLinkCount();

			for (size_t j=dlCount-1;(j>=0) && (j<dlCount);j-- ) {
				DataLink* dataLink =  dataSrc->getDataLink(j);
				if ( dataLink->isActive() && (dataLink->firstRecord_ < delta) ) {
					delta = dataLink->firstRecord_;
				}
			}
		}

		for ( size_t k=numberOfRecords;k<records_.size();k++ ) {
			Record* record =  records_[k];
			
			delete record;
		}
		RecordsArray::iterator it = records_.begin() + numberOfRecords;
		records_.erase( it, records_.end() );
	}
	else {
		try {
			size_t oldSize = records_.size();

			records_.resize(numberOfRecords+1);
			
			if ( oldSize == 0 ) {
				oldSize = 1;
			}

			for ( size_t i=oldSize-1;i<records_.size();i++ ) {
				records_[i] = this->peer_->allocateRecordData();
			}

		}
		catch ( BasicException& ) {
			throw;
		}
	}

	usableRecordCount_ = numberOfRecords;

	VCF_ASSERT( numberOfRecords == records_.size()-1 );

	getNextRecords();
}

size_t DataSet::getNextRecords()
{
	size_t result = 0;
	while ( recordCount_ < usableRecordCount_ ) {
		if ( !getNextRecord() ) {
			break;
		}
		result ++;
	}

	return result;
}

bool DataSet::getNextRecord()
{
	bool result = false;

	GetRecordMode mode = grmNext;

	if ( recordCount_ > 0 ) {
		currentRecordIndex_ = recordCount_ - 1; 
	}	
	
	GetResultType res = this->peer_->getRecord( records_[ recordCount_ ], mode );
	if ( grFailed != res ) {
		result = true;		
	}

	if ( result ) {
		if ( recordCount_ == 0 ) {
			activateRecords();
		}
		else {
			if ( recordCount_ < usableRecordCount_ ) {
				recordCount_ ++;
			}
			else {
				swapRecord( 0, recordCount_ );
			}
		}

		currentRecordIndex_ = recordCount_ - 1; 		
	}
	else {
		cursorPositionChanged();
	}

	return result;
}


void DataSet::updateRecordSize()
{
	if ( this->peer_->isCursorOpen() ) {
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
	return usableRecordCount_;	
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

		GetResultType res = this->peer_->getRecord( records_[ recordCount_ ], grmCurrent );

		if ( res != grOK ) {
			throw DatabaseError("Data set unable to modify the record. The record was not found.");
		}
	}
	else {

		if ( this->peer_->getRecord( records_[ recordCount_ ], grmCurrent ) != grOK ) {
			if ( this->peer_->getRecord( records_[ recordCount_ ], grmNext ) != grOK ) {
				clearRecords();
				Event e(this,deDataSetChange);
				return;
			}
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


void DataSet::internal_setRecordData( Record* record, size_t offset, size_t column, const unsigned char* buffer, size_t bufferSize )
{
	size_t newRecordSize = 0;
	size_t col = 0;	
	

	std::vector<DataField*>::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;
		if ( col == column ) {
			newRecordSize += bufferSize;
		}
		else {
			newRecordSize += field->getSize();
		}
		
		++it;
		col++;
	}

	if ( newRecordSize != record->size ) {
		//need to resize the memory :(
		unsigned char* tmp = new unsigned char[newRecordSize];

		size_t newOffset = 0;
		size_t oldOffset = 0;
		col = 0;
		it = fields_->begin();

		while ( it != fields_->end() ) {
			DataField* field = *it;
			if ( col == column ) {

				memcpy( &tmp[newOffset], buffer, bufferSize );

				oldOffset += field->getSize();

				field->setSize( bufferSize );
				
				newOffset += bufferSize;
			}
			else {
				memcpy( &tmp[newOffset], &record->buffer[oldOffset], field->getSize() );

				oldOffset += field->getSize();
				newOffset += field->getSize();
			}
			
			++it;
			col ++;
		}

		delete [] record->buffer;

		record->size = newRecordSize;
		record->buffer = tmp;
	}
	else { //Yeah, we get to do a straight memcpy
		memcpy( &record->buffer[offset], buffer, bufferSize );
	}

}

VariantData DataSet::getFieldValue( const String& fieldName )
{
	DataField* field = fieldByName( fieldName );

	return field->getValue();
}

void DataSet::setFieldValue( const String& fieldName, VariantData& val )
{
	DataField* field = fieldByName( fieldName );
	field->setValue( val );
}

void DataSet::addField( DataField* field )
{
	fields_->push_back( field );
	field->dataSet_ = this;

	Event e(this,deFieldListChange);
	handleDataEvent(&e);
}

void DataSet::removeField( DataField* field )
{
	field->dataSet_ = NULL;

	DataFieldArray::Vector::iterator found = 
		std::find( fields_->begin(), fields_->end(), field );

	if ( found != fields_->end() ) {
		fields_->erase( found );
	}


	Event e(this,deFieldListChange);
	handleDataEvent(&e);
}

void DataSet::checkInactive()
{
	
}

void DataSet::swapRecord( size_t fromIndex, size_t toIndex )
{
	if ( fromIndex != toIndex ) {
		DataSet::Record* tmp = records_[fromIndex];

		if ( fromIndex < toIndex ) {
			for (size_t i=0;i<toIndex-fromIndex;i++ ) {				
				records_[fromIndex+i] = records_[fromIndex+i+1];
			}			
		}
		else {
			for (size_t i=0;i<fromIndex-toIndex;i++ ) {				
				records_[toIndex+i+1] = records_[toIndex+i];
			}
		}
		records_[toIndex] = tmp;
	}
}

void DataSet::setPeerType( const String& val )
{
	if ( peerType_ != val ) {
		
		peerType_ = "";
		
		if ( NULL != peer_ ) {
			delete peer_;
		}
		
		peer_ = DatabaseToolkit::createDataSetPeer( val );
		if ( NULL != peer_ ) {
			peerType_ = val;
			peer_->setDataSet( this );
		}
	}
}

bool DataSet::getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize )
{
	return peer_->getFieldData( field, buffer, bufferSize );
}

void DataSet::setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize )
{
	peer_->setFieldData( field, buffer, bufferSize );
}