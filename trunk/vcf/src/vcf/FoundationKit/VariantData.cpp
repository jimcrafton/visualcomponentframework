//VariantData.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/UnitTransformer.h"

using namespace VCF;



String VariantData::toString() const
{
	String result = "";
	switch ( type ) {
		case pdInt:{
			int i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%d", i );
			result += tmp;
		}
		break;

		case pdLong:{
			long i = (long)*this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%ld", i );
			result += tmp;
		}
		break;

		case pdShort:{
			short i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%hd", i );
			result += tmp;
		}
		break;

		case pdUShort:{
			ushort i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%u", i );
			result += tmp;
		}
		break;

		case pdUInt:{
			unsigned int i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%u", i );
			result += tmp;
		}
		break;

		case pdULong:{
			unsigned long i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%lu", i );
			result += tmp;
		}
		break;

		case pdFloat:{
			float i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%.5f", i );
			result += tmp;
		}
		break;

		case pdChar:{
			char i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%c", i );
			result += tmp;
		}
		break;

		case pdDouble:{
			double i = *this;
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%.5f", i );
			result += tmp;
		}
		break;

		case pdBool:{
			bool i = *this;
			result += i ? "true" : "false";
		}
		break;

		case pdInt64:{
			int64 value = this->Int64Val;
			result += StringUtils::toString( value );
		}
		break;

		case pdUInt64:{
			uint64 value = this->UInt64Val;
			result += StringUtils::toString( value );
		}
		break;

		case pdVoidPointer:{
			void* value = this->VoidPtrVal;
			
			char tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, sizeof(tmp));
			sprintf( tmp, "%p", value );

			result = tmp;
		}
		break;

		case pdDateTime:{
			DateTime dt;
			dt.setMilliseconds( this->UInt64Val );
			result += StringUtils::format( dt, L"%Y-%m-%d %H:%M:%S.%s (%w)%a" );
		}
		break;

		case pdDateTimeSpan:{
			DateTimeSpan dts = this->UInt64Val;
			result += StringUtils::toString( dts.getTotalMilliseconds() );
		}
		break;

		case pdObject:
		case pdConstObject:{
			const Object* object = *this;
			if ( NULL != object ){
				result += object->toString();
				/*
				Persistable* persist = dynamic_cast<Persistable*>(object);
				if ( NULL != persist ){
					TextOutputStream tos;

					persist->saveToStream( &tos );

					result += tos.getTextBuffer();
				}
				else {
					result += object->toString();
				}
				*/
			}
			else{
				result += "null";
			}
		}
		break;

		case pdInterface:{
			Interface* intrFace = *this;
			if ( NULL != intrFace ){
				Persistable* persist = dynamic_cast<Persistable*>(intrFace);
				if ( NULL != persist ){
					TextOutputStream tos;

					persist->saveToStream( &tos );

					result += tos.getTextBuffer();
				}
				else {
					result += "null";
				}
			}
			else{
				result += "null";
			}
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = *StringVal;
			}
		}
		break;

		case pdEnum:{
			Enum* enumObj = *this;
			if ( NULL != enumObj ){
				result += enumObj->toString();
			}
			else{
				result += "null";
			}
		}
		break;

		case pdUndefined:{
			//no-op
		}
		break;
	}
	return result;
}


void VariantData::setFromString( const String& value )
{
	bool unicodeEnabled = System::isUnicodeEnabled();

	switch( type ){
		case pdInt:{
			IntVal = StringUtils::fromStringAsInt( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdLong:{
			LongVal = StringUtils::fromStringAsLong( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdShort:{
			ShortVal = StringUtils::fromStringAsShort( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdUShort:{
			UShortVal = (ushort) StringUtils::fromStringAsShort( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdUInt:{
			UIntVal = StringUtils::fromStringAsUInt( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdEnumMask:{
			ULongVal = StringUtils::fromStringAsULong( value );
		}
		break;

		case pdULong:{
			ULongVal = StringUtils::fromStringAsULong( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdFloat:{
			FloatVal = StringUtils::fromStringAsFloat( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdChar:{
			CharVal = StringUtils::fromStringAsChar( value );
		}
		break;

		case pdDouble:{
			DblVal = StringUtils::fromStringAsDouble( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdBool:{
			BoolVal = StringUtils::fromStringAsBool( value );
		}
		break;

		case pdInt64:{
			Int64Val = StringUtils::fromStringAsInt64( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdUInt64:{
			UInt64Val = StringUtils::fromStringAsUInt64( UnitTransformer::xfrmString(value) );
		}
		break;

		case pdDateTime:{
			throw NotImplementedException();
		}
		break;

		case pdDateTimeSpan:{
			throw NotImplementedException();
		}
		break;

		case pdVoidPointer:{
			VoidPtrVal = (void*)StringUtils::fromStringAsHexNumber ( value );
		}
		break;

		case pdObject:{
			if ( NULL != ObjVal ){
				Persistable* persist = dynamic_cast<Persistable*>(ObjVal);
				if ( NULL != persist ){

					BasicInputStream bis( value );
					TextInputStream tis( &bis );
					persist->loadFromStream( &tis );
				}
				else if ( (value == L"NULL") || (value == L"null") || (value == L"nil") || (value == L"0") ) {
					ObjVal = NULL;
				}
				else {
					ObjVal->setFromString( value );
				}
			}
		}
		break;

		case pdConstObject:{
			throw NotImplementedException();
		}
		break;

		case pdInterface:{
			if ( NULL != InterfaceVal ){
				Persistable* persist = dynamic_cast<Persistable*>(InterfaceVal);
				if ( NULL != persist ){

					BasicInputStream bis( value );
					TextInputStream tis( &bis );
					persist->loadFromStream( &tis );
				}
				else if ( (value == L"NULL") || (value == L"null") || (value == L"nil") || (value == L"0") ) {
					ObjVal = NULL;
				}
			}
		}
		break;

		case pdString:{

			checkStringVal();

			*StringVal = value;
		}
		break;

		case pdEnum:{
			if ( NULL != EnumVal.getEnum() ){
				EnumVal.set( value );
			}
		}
		break;

		default : {
			checkStringVal();

			*StringVal = value;
			type = pdString;
		}
		break;
	}
}

void VariantData::setValue( const VariantData& value )
{
	type = value.type;
	switch( type ){
		case pdInt:{
			IntVal = value.IntVal;
		}
		break;

		case pdLong:{
			LongVal = value.LongVal;
		}
		break;

		case pdDouble:{
			DblVal = value.DblVal;
		}
		break;

		case pdBool:{
			BoolVal = value.BoolVal;
		}
		break;

		case pdObject:
		case pdConstObject:{
			ObjVal = value.ObjVal;
		}
		break;

		case pdInterface:{
			InterfaceVal = value.InterfaceVal;
		}
		break;

		case pdVoidPointer:{
			VoidPtrVal = value.VoidPtrVal;
		}
		break;

		case pdString:{
			if ( NULL == value.StringVal ) {
				if ( NULL != StringVal ) {
					*StringVal = "";
				}
			}
			else{
				checkStringVal();
				*StringVal = *value.StringVal;
			}
		}
		break;

		case pdEnum:{
			EnumVal = value.EnumVal;
		}
		break;

		case pdEnumMask:{
			ULongVal = value.ULongVal;
		}
		break;

		case pdShort : {
			ShortVal = value.ShortVal;
		}

		case pdUShort : {
			UShortVal = value.UShortVal;
		}

		case pdUInt : {
			UIntVal = value.UIntVal;
		}
		break;

		case pdULong : {
			ULongVal = value.ULongVal;
		}
		break;

		case pdFloat : {
			FloatVal = value.FloatVal;
		}
		break;

		case pdChar : {
			CharVal = value.CharVal;
		}
		break;

		case pdInt64 : {
			Int64Val = value.Int64Val;
		}
		break;

		case pdUInt64 : {
			UInt64Val = value.UInt64Val;
		}
		break;

		case pdDateTime : {
			UInt64Val = value.UInt64Val;
		}
		break;

		case pdDateTimeSpan : {
			UInt64Val = value.UInt64Val;
		}
		break;

		case pdUndefined : {

		}
		break;

		case pdNull : {
			setNull();
		}
		break;

		default:
			type = pdUndefined;
			// this let this class to work with types not considered in this implementation.
			ObjVal = value.ObjVal;
			Int64Val = value.Int64Val;
			StringVal = value.StringVal;
			type = value.type;
	}
}

uint64 VariantData::sizeOf() const
{
	uint64 result = sizeof(VariantData);

	switch( type ){
		case pdString:{
			if ( NULL != StringVal ) {
				result += StringVal->sizeOf();
			}
		}
		break;

		case pdObject:
		case pdConstObject:{
			if ( NULL != ObjVal ) {
				result += ObjVal->sizeOf();
			}
		}
		break;
	}


	return result;
}




 
double VariantData::convertToDbl() const  {
	double result = double();
	switch ( type ) {
		case pdInt:{
			result = (double) IntVal;
		}
		break;

		case pdLong:{
			result = (double) LongVal;
		}
		break;

		case pdShort:{
			result = (double) ShortVal;
		}
		break;

		case pdUShort:{
			result = (double) UShortVal;
		}
		break;

		case pdUInt:{
			result = (double) UIntVal;
		}
		break;

		case pdULong:{
			result = (double) ULongVal;
		}
		break;

		case pdFloat:{
			result = (double) FloatVal;
		}
		break;

		case pdChar:{
			result = (double) CharVal;
		}
		break;

		case pdDouble:{
			result = (double) DblVal;
		}
		break;

		case pdBool:{
			result = (double) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (double) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (double) (int64)UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (double) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (double) (int64)UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (double) (int64)UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsDouble( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


int VariantData::convertToInt() const 
{
	int result = int();
	switch ( type ) {
		case pdInt:{
			result = (int) IntVal;
		}
		break;

		case pdLong:{
			result = (int) LongVal;
		}
		break;

		case pdShort:{
			result = (int) ShortVal;
		}
		break;

		case pdUShort:{
			result = (int) UShortVal;
		}
		break;

		case pdUInt:{
			result = (int) UIntVal;
		}
		break;

		case pdULong:{
			result = (int) ULongVal;
		}
		break;

		case pdFloat:{
			result = (int) FloatVal;
		}
		break;

		case pdChar:{
			result = (int) CharVal;
		}
		break;

		case pdDouble:{
			result = (int) DblVal;
		}
		break;

		case pdBool:{
			result = (int) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (int) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (int) (int64)UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (int) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (int) (int64)UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (int) (int64)UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsInt( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


long VariantData::convertToLong() const 
{
	long result = long();
	switch ( type ) {
		case pdInt:{
			result = (long) IntVal;
		}
		break;

		case pdLong:{
			result = (long) LongVal;
		}
		break;

		case pdShort:{
			result = (long) ShortVal;
		}
		break;

		case pdUShort:{
			result = (long) UShortVal;
		}
		break;

		case pdUInt:{
			result = (long) UIntVal;
		}
		break;

		case pdULong:{
			result = (long) ULongVal;
		}
		break;

		case pdFloat:{
			result = (long) FloatVal;
		}
		break;

		case pdChar:{
			result = (long) CharVal;
		}
		break;

		case pdDouble:{
			result = (long) DblVal;
		}
		break;

		case pdBool:{
			result = (long) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (long) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (long) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (long) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (long) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (long) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsLong( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


short VariantData::convertToShort() const 
{
	short result = short();
	switch ( type ) {
		case pdInt:{
			result = (short) IntVal;
		}
		break;

		case pdLong:{
			result = (short) LongVal;
		}
		break;

		case pdShort:{
			result = (short) ShortVal;
		}
		break;

		case pdUShort:{
			result = (short) UShortVal;
		}
		break;

		case pdUInt:{
			result = (short) UIntVal;
		}
		break;

		case pdULong:{
			result = (short) ULongVal;
		}
		break;

		case pdFloat:{
			result = (short) FloatVal;
		}
		break;

		case pdChar:{
			result = (short) CharVal;
		}
		break;

		case pdDouble:{
			result = (short) DblVal;
		}
		break;

		case pdBool:{
			result = (short) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (short) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (short) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (short) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (short) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (short) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsShort( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


VCF::ushort VariantData::convertToUShort() const 
{
	VCF::ushort result = VCF::ushort();
	switch ( type ) {
		case pdInt:{
			result = (ushort) IntVal;
		}
		break;

		case pdLong:{
			result = (ushort) LongVal;
		}
		break;

		case pdShort:{
			result = (ushort) ShortVal;
		}
		break;

		case pdUShort:{
			result = (ushort) UShortVal;
		}
		break;

		case pdUInt:{
			result = (ushort) UIntVal;
		}
		break;

		case pdULong:{
			result = (ushort) ULongVal;
		}
		break;

		case pdFloat:{
			result = (ushort) FloatVal;
		}
		break;

		case pdChar:{
			result = (ushort) CharVal;
		}
		break;

		case pdDouble:{
			result = (ushort) DblVal;
		}
		break;

		case pdBool:{
			result = (ushort) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (ushort) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (ushort) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (ushort) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (ushort) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (ushort) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = (ushort) StringUtils::fromStringAsShort( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


unsigned int VariantData::convertToUInt() const 
{
	unsigned int result = 0;
	switch ( type ) {
		case pdInt:{
			result = (unsigned int) IntVal;
		}
		break;

		case pdLong:{
			result = (unsigned int) LongVal;
		}
		break;

		case pdShort:{
			result = (unsigned int) ShortVal;
		}
		break;

		case pdUShort:{
			result = (unsigned int) UShortVal;
		}
		break;

		case pdUInt:{
			result = (unsigned int) UIntVal;
		}
		break;

		case pdULong:{
			result = (unsigned int) ULongVal;
		}
		break;

		case pdFloat:{
			result = (unsigned int) FloatVal;
		}
		break;

		case pdChar:{
			result = (unsigned int) CharVal;
		}
		break;

		case pdDouble:{
			result = (unsigned int) DblVal;
		}
		break;

		case pdBool:{
			result = (unsigned int) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (unsigned int) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (unsigned int) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (unsigned int) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (unsigned int) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (unsigned int) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsUInt( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


unsigned long VariantData::convertToULong() const 
{
	unsigned long result = 0;
	switch ( type ) {
		case pdInt:{
			result = (unsigned long) IntVal;
		}
		break;

		case pdLong:{
			result = (unsigned long) LongVal;
		}
		break;

		case pdShort:{
			result = (unsigned long) ShortVal;
		}
		break;

		case pdUShort:{
			result = (unsigned long) UShortVal;
		}
		break;

		case pdUInt:{
			result = (unsigned long) UIntVal;
		}
		break;

		case pdULong:{
			result = (unsigned long) ULongVal;
		}
		break;

		case pdFloat:{
			result = (unsigned long) FloatVal;
		}
		break;

		case pdChar:{
			result = (unsigned long) CharVal;
		}
		break;

		case pdDouble:{
			result = (unsigned long) DblVal;
		}
		break;

		case pdBool:{
			result = (unsigned long) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (unsigned long) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (unsigned long) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (unsigned long) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (unsigned long) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (unsigned long) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsULong( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


float VariantData::convertToFloat() const 
{
	float result = float();
	switch ( type ) {
		case pdInt:{
			result = (float) IntVal;
		}
		break;

		case pdLong:{
			result = (float) LongVal;
		}
		break;

		case pdShort:{
			result = (float) ShortVal;
		}
		break;

		case pdUShort:{
			result = (float) UShortVal;
		}
		break;

		case pdUInt:{
			result = (float) UIntVal;
		}
		break;

		case pdULong:{
			result = (float) ULongVal;
		}
		break;

		case pdFloat:{
			result = (float) FloatVal;
		}
		break;

		case pdChar:{
			result = (float) CharVal;
		}
		break;

		case pdDouble:{
			result = (float) DblVal;
		}
		break;

		case pdBool:{
			result = (float) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (float) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (float) (int64)UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (float) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (float) (int64)UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (float) (int64)UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsFloat( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


char VariantData::convertToChar() const 
{
	char result = char();
	switch ( type ) {
		case pdInt:{
			result = (char) IntVal;
		}
		break;

		case pdLong:{
			result = (char) LongVal;
		}
		break;

		case pdShort:{
			result = (char) ShortVal;
		}
		break;

		case pdUShort:{
			result = (char) UShortVal;
		}
		break;

		case pdUInt:{
			result = (char) UIntVal;
		}
		break;

		case pdULong:{
			result = (char) ULongVal;
		}
		break;

		case pdFloat:{
			result = (char) FloatVal;
		}
		break;

		case pdChar:{
			result = (char) CharVal;
		}
		break;

		case pdDouble:{
			result = (char) DblVal;
		}
		break;

		case pdBool:{
			result = (char) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (char) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (char) (int64)UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (char) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (char) (int64)UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (char) (int64)UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsChar(*StringVal);
			}
		}
		break;
	}
	

	return result;
}


bool VariantData::convertToBool() const 
{
	bool result = bool();
	switch ( type ) {
		case pdInt:{
			result = IntVal ? true : false;
		}
		break;

		case pdLong:{
			result =  LongVal ? true : false;
		}
		break;

		case pdShort:{
			result =  ShortVal ? true : false;
		}
		break;

		case pdUShort:{
			result =  UShortVal ? true : false;
		}
		break;

		case pdUInt:{
			result =  UIntVal ? true : false;
		}
		break;

		case pdULong:{
			result =  ULongVal ? true : false;
		}
		break;

		case pdFloat:{
			result =  FloatVal > 0  ? true : false;
		}
		break;

		case pdChar:{
			result =  CharVal ? true : false;
		}
		break;

		case pdDouble:{
			result =  DblVal > 0  ? true : false;
		}
		break;

		case pdBool:{
			result =  BoolVal;			
		}
		break;

		case pdInt64:{
			result =  Int64Val ? true : false;
		}
		break;

		case pdUInt64:{
			result =  (int64)UInt64Val ? true : false;
		}
		break;

		case pdVoidPointer:{
			result =  (int)VoidPtrVal != 0  ? true : false;
		}
		break;

		case pdDateTime:{
			result =  (int64)UInt64Val ? true : false;
		}
		break;

		case pdDateTimeSpan:{
			result =  (int64)UInt64Val ? true : false;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsBool(*StringVal);
			}
		}
		break;
	}
	

	return result;
}


int64 VariantData::convertToInt64() const 
{
	int64 result = int64();
	switch ( type ) {
		case pdInt:{
			result = (int64) IntVal;
		}
		break;

		case pdLong:{
			result = (int64) LongVal;
		}
		break;

		case pdShort:{
			result = (int64) ShortVal;
		}
		break;

		case pdUShort:{
			result = (int64) UShortVal;
		}
		break;

		case pdUInt:{
			result = (int64) UIntVal;
		}
		break;

		case pdULong:{
			result = (int64) ULongVal;
		}
		break;

		case pdFloat:{
			result = (int64) FloatVal;
		}
		break;

		case pdChar:{
			result = (int64) CharVal;
		}
		break;

		case pdDouble:{
			result = (int64) DblVal;
		}
		break;

		case pdBool:{
			result = (int64) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (int64) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (int64) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (int64) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (int64) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (int64) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsInt64( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


uint64 VariantData::convertToUInt64() const 
{
	uint64 result = uint64();
	switch ( type ) {
		case pdInt:{
			result = (uint64) IntVal;
		}
		break;

		case pdLong:{
			result = (uint64) LongVal;
		}
		break;

		case pdShort:{
			result = (uint64) ShortVal;
		}
		break;

		case pdUShort:{
			result = (uint64) UShortVal;
		}
		break;

		case pdUInt:{
			result = (uint64) UIntVal;
		}
		break;

		case pdULong:{
			result = (uint64) ULongVal;
		}
		break;

		case pdFloat:{
			result = (uint64) FloatVal;
		}
		break;

		case pdChar:{
			result = (uint64) CharVal;
		}
		break;

		case pdDouble:{
			result = (uint64) DblVal;
		}
		break;

		case pdBool:{
			result = (uint64) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (uint64) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (uint64) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (uint64) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (uint64) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (uint64) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = StringUtils::fromStringAsUInt64( UnitTransformer::xfrmString(*StringVal) );
			}
		}
		break;
	}
	

	return result;
}


void* VariantData::convertToVoidPtr() const 
{
	void* result = NULL;
	switch ( type ) {
		case pdInt:{
			result = (void*) IntVal;
		}
		break;

		case pdLong:{
			result = (void*) LongVal;
		}
		break;

		case pdShort:{
			result = (void*) ShortVal;
		}
		break;

		case pdUShort:{
			result = (void*) UShortVal;
		}
		break;

		case pdUInt:{
			result = (void*) UIntVal;
		}
		break;

		case pdULong:{
			result = (void*) ULongVal;
		}
		break;

		case pdFloat:{
			result = (void*) (int)FloatVal;
		}
		break;

		case pdChar:{
			result = (void*) CharVal;
		}
		break;

		case pdDouble:{
			result = (void*) (int)DblVal;
		}
		break;

		case pdBool:{
			result = (void*) BoolVal;			
		}
		break;

		case pdInt64:{
			result = (void*) Int64Val;
		}
		break;

		case pdUInt64:{
			result = (void*) UInt64Val;
		}
		break;

		case pdVoidPointer:{
			result = (void*) (int)VoidPtrVal;
		}
		break;

		case pdDateTime:{
			result = (void*) UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			result = (void*) UInt64Val;
		}
		break;

		case pdString:{
			if ( NULL != StringVal ) {
				result = (void*)StringUtils::fromStringAsHexNumber(*StringVal);
			}
		}
		break;
	}
	

	return result;
}

bool VariantData::operator == ( const VariantData& v ) const
{
	if ( type != v.type ) {
		return false;
	}

	switch ( type ) {
		case pdInt:{
			return IntVal == v.IntVal;
		}
		break;

		case pdLong:{
			return LongVal == v.LongVal;
		}
		break;

		case pdShort:{
			return ShortVal == v.ShortVal;
		}
		break;

		case pdUShort:{
			return UShortVal == v.UShortVal;
		}
		break;

		case pdUInt:{
			return UIntVal == v.UIntVal;
		}
		break;

		case pdULong:{
			return ULongVal == v.ULongVal;
		}
		break;

		case pdFloat:{
			return FloatVal == v.FloatVal;
		}
		break;

		case pdChar:{
			return CharVal == v.CharVal;
		}
		break;

		case pdDouble:{
			return DblVal == v.DblVal;
		}
		break;

		case pdBool:{
			return BoolVal == v.BoolVal;		
		}
		break;

		case pdInt64:{
			return Int64Val == v.Int64Val;
		}
		break;

		case pdUInt64:{
			return UInt64Val == v.UInt64Val;
		}
		break;

		case pdObject:
		case pdConstObject:{
			return ObjVal == v.ObjVal;
		}
		break;

		case pdVoidPointer:{
			return VoidPtrVal == v.VoidPtrVal;
		}
		break;

		case pdDateTime:{
			return UInt64Val == v.UInt64Val;
		}
		break;

		case pdDateTimeSpan:{
			return UInt64Val == v.UInt64Val;
		}
		break;

		case pdString:{
			if ( (NULL != StringVal) && (NULL != v.StringVal) ) {
				return *StringVal == *v.StringVal;
			}
		}
		break; 
	}


	return false;
}

VariantData VariantData::convertToType( PropertyDescriptorType valType ) const 
{
	VariantData result;

	result.type = valType;

	
	switch ( valType ) {
		case pdInt:{
			result = convertToInt();
		}
		break;

		case pdLong:{
			result = convertToLong();
		}
		break;

		case pdShort:{
			result = convertToShort();
		}
		break;

		case pdUShort:{
			result = convertToUShort();
		}
		break;

		case pdUInt:{
			result = convertToUInt();
		}
		break;

		case pdULong:{
			result = convertToULong();
		}
		break;

		case pdFloat:{
			result = convertToFloat();
		}
		break;

		case pdChar:{
			result = convertToChar();
		}
		break;

		case pdDouble:{
			result = convertToDbl();
		}
		break;

		case pdBool:{
			result = convertToBool();
		}
		break;

		case pdInt64:{
			result = convertToInt64();
		}
		break;

		case pdUInt64:{
			result = convertToUInt64();
		}
		break;

		case pdVoidPointer:{
			result = convertToVoidPtr();
		}
		break;

		case pdDateTime:{
			result = convertToUInt64();
		}
		break;

		case pdDateTimeSpan:{
			result = convertToUInt64();
		}
		break;

		case pdString:{
			result = toString();
		}
		break;

		case pdObject:{
			result.ObjVal = ObjVal;
		}
		break;

		case pdConstObject:{
			throw NotImplementedException();
		}
		break;

		case pdInterface:{
			result.InterfaceVal = InterfaceVal;
		}
		break;

		case pdEnum:{
			result.EnumVal = EnumVal;
		}
		break;
	}

	return result;
}

bool VariantData::operator< (const VariantData& rhs ) const 
{
	if ( type == rhs.type ) {
		switch ( type ) {
			case pdULong: case pdUInt: case pdUShort: case pdShort: 
			case pdChar: case pdLong: case pdInt: {
				return IntVal < rhs.IntVal;
			}
			break;

			case pdFloat:{
				return FloatVal < rhs.FloatVal;
			}
			break;

			case pdDouble:{
				return DblVal < rhs.DblVal;
			}
			break;

			case pdDateTimeSpan: case pdDateTime:{
				return UInt64Val < rhs.UInt64Val;
			}
			break;

			case pdInt64:{
				return Int64Val < rhs.Int64Val;
			}
			break;

			case pdUInt64:{
				return UInt64Val < rhs.UInt64Val;
			}
			break;

			case pdObject:
			case pdConstObject:{
				return ObjVal < rhs.ObjVal;
			}
			break;

			case pdVoidPointer:{
				return VoidPtrVal < rhs.VoidPtrVal;
			}
			break;

			case pdString:{
				if ( (NULL != StringVal) && (NULL != rhs.StringVal) ) {
					return *StringVal < *rhs.StringVal;
				}
				else if ( (NULL != StringVal) && (NULL == rhs.StringVal) ) {
					return false;
				}
				else if ( (NULL == StringVal) && (NULL != rhs.StringVal) ) {
					return true;
				}
			}
			break; 
		}
	}
	else {
		VariantData tmp = rhs.convertToType(type);
		return *this < tmp;
	}

	return false;
}

bool VariantData::operator> (const VariantData& rhs ) const 
{	
	if ( type == rhs.type ) {
		switch ( type ) {
			case pdULong: case pdUInt: case pdUShort: case pdShort: 
			case pdChar: case pdLong: case pdInt: {
				return IntVal > rhs.IntVal;
			}
			break;

			case pdFloat:{
				return FloatVal > rhs.FloatVal;
			}
			break;

			case pdDouble:{
				return DblVal > rhs.DblVal;
			}
			break;

			case pdDateTimeSpan: case pdDateTime:{
				return UInt64Val > rhs.UInt64Val;
			}
			break;

			case pdInt64:{
				return Int64Val > rhs.Int64Val;
			}
			break;

			case pdUInt64:{
				return UInt64Val > rhs.UInt64Val;
			}
			break;

			case pdObject:
			case pdConstObject:{
				return ObjVal > rhs.ObjVal;
			}
			break;

			case pdVoidPointer:{
				return VoidPtrVal > rhs.VoidPtrVal;
			}
			break;

			case pdString:{
				if ( (NULL != StringVal) && (NULL != rhs.StringVal) ) {
					return *StringVal > *rhs.StringVal;
				}
				else if ( (NULL != StringVal) && (NULL == rhs.StringVal) ) {
					return false;
				}
				else if ( (NULL == StringVal) && (NULL != rhs.StringVal) ) {
					return true;
				}
			}
			break; 
		}
	}
	else {
		VariantData tmp = rhs.convertToType(type);
		return *this > tmp;
	}
	return false;
}

bool VariantData::operator<= (const VariantData& rhs ) const 
{
	if ( type == rhs.type ) {
		switch ( type ) {
			case pdULong: case pdUInt: case pdUShort: case pdShort: 
			case pdChar: case pdLong: case pdInt: {
				return IntVal <= rhs.IntVal;
			}
			break;

			case pdFloat:{
				return FloatVal <= rhs.FloatVal;
			}
			break;

			case pdDouble:{
				return DblVal <= rhs.DblVal;
			}
			break;

			case pdDateTimeSpan: case pdDateTime:{
				return UInt64Val <= rhs.UInt64Val;
			}
			break;

			case pdInt64:{
				return Int64Val <= rhs.Int64Val;
			}
			break;

			case pdUInt64:{
				return UInt64Val <= rhs.UInt64Val;
			}
			break;

			case pdObject:
			case pdConstObject:{
				return ObjVal <= rhs.ObjVal;
			}
			break;

			case pdVoidPointer:{
				return VoidPtrVal <= rhs.VoidPtrVal;
			}
			break;

			case pdString:{
				if ( (NULL != StringVal) && (NULL != rhs.StringVal) ) {
					return *StringVal <= *rhs.StringVal;
				}
				else if ( (NULL != StringVal) && (NULL == rhs.StringVal) ) {
					return false;
				}
				else if ( (NULL == StringVal) && (NULL != rhs.StringVal) ) {
					return true;
				}
			}
			break; 
		}
	}
	else {
		VariantData tmp = rhs.convertToType(type);
		return *this <= tmp;
	}
	return false;
}

bool VariantData::operator>= (const VariantData& rhs ) const 
{
	if ( type == rhs.type ) {
		switch ( type ) {
			case pdULong: case pdUInt: case pdUShort: case pdShort: 
			case pdChar: case pdLong: case pdInt: {
				return IntVal >= rhs.IntVal;
			}
			break;

			case pdFloat:{
				return FloatVal >= rhs.FloatVal;
			}
			break;

			case pdDouble:{
				return DblVal >= rhs.DblVal;
			}
			break;

			case pdDateTimeSpan: case pdDateTime:{
				return UInt64Val >= rhs.UInt64Val;
			}
			break;

			case pdInt64:{
				return Int64Val >= rhs.Int64Val;
			}
			break;

			case pdUInt64:{
				return UInt64Val >= rhs.UInt64Val;
			}
			break;

			case pdObject:
			case pdConstObject:{
				return ObjVal >= rhs.ObjVal;
			}
			break;

			case pdVoidPointer:{
				return VoidPtrVal >= rhs.VoidPtrVal;
			}
			break;

			case pdString:{
				if ( (NULL != StringVal) && (NULL != rhs.StringVal) ) {
					return *StringVal >= *rhs.StringVal;
				}
				else if ( (NULL != StringVal) && (NULL == rhs.StringVal) ) {
					return false;
				}
				else if ( (NULL == StringVal) && (NULL != rhs.StringVal) ) {
					return true;
				}
			}
			break; 
		}
	}
	else {
		VariantData tmp = rhs.convertToType(type);
		return *this >= tmp;
	}

	return false;
}
/**
$Id$
*/
