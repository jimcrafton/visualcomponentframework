//DataField.cpp
#include "DatabaseKit.h"

using namespace VCF;



DataField::DataField():
	dataSet_(NULL),
	dataType_(dftUnknown),
	displayWidth_(100),
	fieldNumber_(-1),
	kind_(fkUnknown),
	visible_(true),
	readOnly_(true),
	required_(false),
	size_(0),
	validating_(false)

{

}

void DataField::initField( const FieldDefinition& val )
{
	size_ = val.size;
	if ( NULL != val.owner ) {
		dataSet_ = val.owner->getDataSet();
	}

	name_ = val.name;

	dataType_ = val.dataType;

	required_ = val.required;

	fieldNumber_ = val.fieldNumber;
}

void DataField::bind( bool bindField )
{

}

void DataField::change()
{
	Event e(this,0);

	Changed.fireEvent(&e);
}


void DataField::validate( const unsigned char* buffer, size_t bufferSize )
{
	ValidateFieldEvent e(this);
	e.buffer = buffer;
	e.bufferSize = bufferSize;

	validating_ = true;

	try {
		Validate.fireEvent( &e );
	}
	catch (...) {
		
	}

	validating_ = false;
}

void DataField::dataChanged()
{
	VCF_ASSERT( NULL != this->dataSet_ );

	Event e(this, deFieldChange );
	dataSet_->handleDataEvent( &e );
}

void DataField::propertyChanged( bool layoutAffected )
{
	if ( NULL != dataSet_ ) {
		if ( dataSet_->isActive() ) {
			Event e(this, layoutAffected ? deDataSetChange : deLayoutChange );
			dataSet_->handleDataEvent( &e );
		}
	}
}

void DataField::setName( const String& val )
{
	if ( NULL != dataSet_ ) {
		dataSet_->checkFieldName( val );
	}

	name_ = val;

	if ( displayName_ == val ) {
		displayName_ = "";
	}

	if ( NULL != dataSet_ ) {
		Event e(this, deFieldListChange );
		dataSet_->handleDataEvent( &e );
	}
}

void DataField::setDisplayName( const String& val )
{
	String s;

	if ( s != this->name_ ) {
		s = val;
	}

	if ( s != this->displayName_ ) {
		displayName_ = s;
		propertyChanged( true );
	}
}

String DataField::getDisplayName()
{
	String result;

	if ( !displayName_.empty() ) {
		result = displayName_;
	}
	else {
		result = name_;
	}

	return result;
}

void DataField::setDisplayWidth( int val )
{
	if ( val != this->displayWidth_ ) {
		displayWidth_ = val;

		propertyChanged( true );
	}
}

size_t DataField::getIndex()
{
	size_t result = DataSet::NoFieldPos;

	if ( NULL != dataSet_ ) {
		result = dataSet_->indexOfField( this );
	}

	return result;
}

void DataField::setIndex( size_t val )
{
	size_t currentIdx = getIndex();
	if ( currentIdx != DataSet::NoFieldPos ) {
		
		std::vector<DataField*>& fields = dataSet_->getFieldsArray();
	
		if ( val == DataSet::NoFieldPos ) {
			val = 0;
		}

		val = minVal( val, fields.size()-1 );

		if ( val != currentIdx ) {
			fields.erase( fields.begin() + currentIdx );
			fields.insert( fields.begin() + val, this );

			propertyChanged( true );

			Event e(NULL, deFieldListChange );
			dataSet_->handleDataEvent( &e );
		}
	}
}

VariantData DataField::getCurrentValue()
{
	VariantData result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

bool DataField::getAsBoolean()
{
	bool result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

DateTime DataField::getAsDateTime()
{
	DateTime result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

String DataField::getAsString()
{
	String result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

double DataField::getAsFloat()
{
	double result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

int DataField::getAsInteger()
{
	int result;
	throw DatabaseError("Not implemented for abstract class!");
	return result;
}

void DataField::setAsBoolean( bool val )
{
	throw DatabaseError("Not implemented for abstract class!");
}

void DataField::setAsDateTime( const DateTime& val )
{
	throw DatabaseError("Not implemented for abstract class!");
}

void DataField::setAsString( const String& val )
{
	throw DatabaseError("Not implemented for abstract class!");
}

void DataField::setAsFloat( const double& val )
{
	throw DatabaseError("Not implemented for abstract class!");
}

void DataField::setAsInteger( const int& val )
{
	throw DatabaseError("Not implemented for abstract class!");
}



bool DataField::getData( unsigned char* buffer, size_t bufferSize )
{
	bool result = false;

	if ( NULL == dataSet_ ) {
		throw DatabaseError("Dataset not set for this field!");
	}

	result = dataSet_->getFieldData( this, buffer, bufferSize );
	
	return result;
}

void DataField::setData( const unsigned char* buffer, size_t bufferSize )
{
	if ( NULL == dataSet_ ) {
		throw DatabaseError("Dataset not set for this field!");
	}


	dataSet_->setFieldData( this, buffer, bufferSize );
}

bool DataField::isNull()
{
	return !getData( NULL, 0 );
}






StringField::StringField()
{

}



VariantData StringField::getCurrentValue()
{
	VariantData result = getAsString();
	
	return result;
}

bool StringField::getAsBoolean()
{
	bool result = false;

	String s = getAsString();
	result = StringUtils::fromStringAsBool(s);
	
	return result;
}

DateTime StringField::getAsDateTime()
{
	DateTime result;
	
	if ( NULL != dataSet_ ) {
		String s = getAsString();
		result = dataSet_->getLocale()->toDateTime( s );
	}

	return result;
}

String StringField::getAsString()
{
	String result;
	char tmp[256];

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

double StringField::getAsFloat()
{
	double result = 0;

	String s = getAsString();

	if ( NULL != dataSet_ ) {
		result = dataSet_->getLocale()->toDouble( s );
	}
	else {
		result = StringUtils::fromStringAsDouble(s);
	}

	return result;
}

int StringField::getAsInteger()
{
	int result = 0;
	String s = getAsString();

	if ( NULL != dataSet_ ) {
		result = dataSet_->getLocale()->toInt( s );
	}
	else {
		result = StringUtils::fromStringAsInt(s);
	}

	return result;
}







BooleanField::BooleanField()
{

}



VariantData BooleanField::getCurrentValue()
{
	VariantData result = getAsBoolean();
	
	return result;
}

bool BooleanField::getAsBoolean()
{
	bool result = false;
	
	if ( !getData( (unsigned char*)&result, sizeof(result) ) ) {
		throw DatabaseError( Format("Unable to retrieve data for field \"%s\"") % name_ );
	}
	
	return result;
}


String BooleanField::getAsString()
{
	String result = StringUtils::toString(getAsBoolean());

	return result;
}

int BooleanField::getAsInteger()
{
	int result = getAsBoolean() ? 0 : 1;
	
	return result;
}







DateTimeField::DateTimeField()
{

}



VariantData DateTimeField::getCurrentValue()
{
	VariantData result = getAsDateTime();
	
	return result;
}

DateTime DateTimeField::getAsDateTime()
{
	DateTime result;
	
	uint64 tmp = 0;

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

String DateTimeField::getAsString()
{
	String result;

	if ( NULL != dataSet_ ) {
		result = dataSet_->getLocale()->toStringFromDate( getAsDateTime() );
	}
	else {
		result = StringUtils::format( getAsDateTime(), "%d-%m-%Y %H:%M:%S" );
	}

	return result;
}

int DateTimeField::getAsInteger()
{
	int result;
	
	result = (int) getAsDateTime().getCTime();

	return result;
}








DoubleField::DoubleField()
{

}



VariantData DoubleField::getCurrentValue()
{
	VariantData result = getAsFloat();
	
	return result;
}


String DoubleField::getAsString()
{
	String result;
	
	if ( NULL != dataSet_ ) {
		result = dataSet_->getLocale()->toString( getAsFloat() );
	}
	else {
		result = StringUtils::toString( getAsFloat() );
	}

	return result;
}

double DoubleField::getAsFloat()
{
	double result = 0.0;
	
	if ( !getData( (unsigned char*)&result, sizeof(result) ) ) {
		throw DatabaseError( Format("Unable to retrieve data for field \"%s\"") % name_ );
	}

	return result;
}

int DoubleField::getAsInteger()
{
	int result = (int) getAsFloat();
	
	return result;
}







IntegerField::IntegerField()
{

}



VariantData IntegerField::getCurrentValue()
{
	VariantData result = getAsInteger();
	
	return result;
}

bool IntegerField::getAsBoolean()
{
	bool result = getAsInteger() ? true : false;
	
	return result;
}

DateTime IntegerField::getAsDateTime()
{
	DateTime result ( (time_t) getAsInteger() );
	
	return result;
}

String IntegerField::getAsString()
{
	String result;
	
	if ( NULL != dataSet_ ) {
		result = dataSet_->getLocale()->toString( getAsInteger() );
	}
	else {
		result = StringUtils::toString( getAsInteger() );
	}

	return result;
}

double IntegerField::getAsFloat()
{
	double result = (double) getAsInteger();
	
	return result;
}

int IntegerField::getAsInteger()
{
	int result = 0;
	
	if ( !getData( (unsigned char*)&result, sizeof(result) ) ) {
		throw DatabaseError( Format("Unable to retrieve data for field \"%s\"") % name_ );
	}

	return result;
}