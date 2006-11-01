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




StringField::StringField()
{

}



VariantData StringField::getCurrentValue()
{
	VariantData result;
	
	return result;
}

bool StringField::getAsBoolean()
{
	bool result;
	
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
	
	return result;
}

double StringField::getAsFloat()
{
	double result;
	
	return result;
}

int StringField::getAsInteger()
{
	int result;
	
	return result;
}