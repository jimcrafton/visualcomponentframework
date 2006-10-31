//DataField.cpp
#include "DatabaseKit.h"

using namespace VCF;



DataField::DataField()
{

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