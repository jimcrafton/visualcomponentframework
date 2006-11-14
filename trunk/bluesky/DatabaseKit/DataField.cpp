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
	size_(0)

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

bool DataField::getData( unsigned char* buffer, size_t bufferSize )
{
	bool result = false;

	if ( NULL == dataSet_ ) {
		throw DatabaseError("Dataset not set for this field!");
	}

	result = dataSet_->getFieldData( this, buffer, bufferSize );
	
	return result;
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
	VariantData result;
	
	return result;
}

bool BooleanField::getAsBoolean()
{
	bool result;
	
	return result;
}

DateTime BooleanField::getAsDateTime()
{
	DateTime result;
	
	return result;
}

String BooleanField::getAsString()
{
	String result;
	char tmp[256];

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

double BooleanField::getAsFloat()
{
	double result;
	
	return result;
}

int BooleanField::getAsInteger()
{
	int result;
	
	return result;
}







DateTimeField::DateTimeField()
{

}



VariantData DateTimeField::getCurrentValue()
{
	VariantData result;
	
	return result;
}

bool DateTimeField::getAsBoolean()
{
	bool result;
	
	return result;
}

DateTime DateTimeField::getAsDateTime()
{
	DateTime result;
	
	return result;
}

String DateTimeField::getAsString()
{
	String result;
	char tmp[256];

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

double DateTimeField::getAsFloat()
{
	double result;
	
	return result;
}

int DateTimeField::getAsInteger()
{
	int result;
	
	return result;
}








DoubleField::DoubleField()
{

}



VariantData DoubleField::getCurrentValue()
{
	VariantData result;
	
	return result;
}

bool DoubleField::getAsBoolean()
{
	bool result;
	
	return result;
}

DateTime DoubleField::getAsDateTime()
{
	DateTime result;
	
	return result;
}

String DoubleField::getAsString()
{
	String result;
	char tmp[256];

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

double DoubleField::getAsFloat()
{
	double result;
	
	return result;
}

int DoubleField::getAsInteger()
{
	int result;
	
	return result;
}







IntegerField::IntegerField()
{

}



VariantData IntegerField::getCurrentValue()
{
	VariantData result;
	
	return result;
}

bool IntegerField::getAsBoolean()
{
	bool result;
	
	return result;
}

DateTime IntegerField::getAsDateTime()
{
	DateTime result;
	
	return result;
}

String IntegerField::getAsString()
{
	String result;
	char tmp[256];

	if ( getData( (unsigned char*)tmp, sizeof(tmp) ) ) {
		result = tmp;
	}

	return result;
}

double IntegerField::getAsFloat()
{
	double result;
	
	return result;
}

int IntegerField::getAsInteger()
{
	int result;
	
	return result;
}