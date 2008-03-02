//VariantData.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
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

		case pdObject:{
			Object* object = *this;
			if ( NULL != object ){
				//result += object->toString();
				Persistable* persist = dynamic_cast<Persistable*>(object);
				if ( NULL != persist ){
					TextOutputStream tos;

					persist->saveToStream( &tos );

					result += tos.getTextBuffer();
				}
				else {
					result += object->toString();
				}
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
			IntVal = StringUtils::fromStringAsInt( value );
		}
		break;

		case pdLong:{
			LongVal = StringUtils::fromStringAsLong( value );
		}
		break;

		case pdShort:{
			ShortVal = StringUtils::fromStringAsShort( value );
		}
		break;

		case pdUShort:{
			UShortVal = (ushort) StringUtils::fromStringAsShort( value );
		}
		break;

		case pdUInt:{
			UIntVal = StringUtils::fromStringAsUInt( value );
		}
		break;

		case pdEnumMask:{
			ULongVal = StringUtils::fromStringAsULong( value );
		}
		break;

		case pdULong:{
			ULongVal = StringUtils::fromStringAsULong( value );
		}
		break;

		case pdFloat:{
			FloatVal = StringUtils::fromStringAsFloat( value );
		}
		break;

		case pdChar:{
			CharVal = StringUtils::fromStringAsChar( value );
		}
		break;

		case pdDouble:{
			DblVal = StringUtils::fromStringAsDouble( value );
		}
		break;

		case pdBool:{
			BoolVal = StringUtils::fromStringAsBool( value );
		}
		break;

		case pdInt64:{
			Int64Val = StringUtils::fromStringAsInt64( value );
		}
		break;

		case pdUInt64:{
			UInt64Val = StringUtils::fromStringAsUInt64( value );
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

		case pdObject:{
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

		case pdObject:{
			if ( NULL != ObjVal ) {
				result += ObjVal->sizeOf();
			}
		}
		break;
	}


	return result;
}

/**
$Id$
*/
