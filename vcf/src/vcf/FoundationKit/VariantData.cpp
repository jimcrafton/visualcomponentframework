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

#ifdef VCF_VARIANT64
		case pdLong64:{
			int64::int64_t value = this->Long64Val;
			VCFChar tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, VariantData::DefaultPropertyValLength);
			swprintf( tmp, L"%I64d", (__int64)value );
			result += tmp;
		}
		break;

		case pdULong64:{
			uint64::u64_t value = this->ULong64Val;
			VCFChar tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, VariantData::DefaultPropertyValLength);
			swprintf( tmp, L"%I64u", (unsigned __int64)value );
			result += tmp;
		}
		break;

		case pdDateTime:{
			DateTime dt = (int64)this->Long64Val;
			result += StringUtils::format( dt, L"%Y-%m-%d %H:%M:%S.%s (%w)%a" );
			//result += StringUtils::lowerCase( StringUtils::format( dt, L"%a" ) );
		}
		break;

		case pdDateTimeSpan:{
			DateTimeSpan dts = (int64)this->Long64Val;
			result += StringUtils::format( dts, L"%y-%m-%d %h:%m:%s" );
		}
		break;

#endif // VCF_VARIANT64

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

#ifdef VCF_VARIANT64
		case pdLong64:{
			uint64::int64_t result = 0;
			int ret = swscanf( value.c_str(), L"%I64", &result );
			if ( ret != 1 ) {
				throw BasicException( L"Unable to convert: " + value );
			}
			Long64Val = result;
		}
		break;

		case pdULong64:{
			uint64::u64_t result = 0;
			int ret = swscanf( value.c_str(), L"%I64u", &result );
			if ( ret != 1 ) {
				throw BasicException( L"Unable to convert: " + value );
			}
			ULong64Val = result;
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

#endif // VCF_VARIANT64

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

#ifdef VCF_VARIANT64
		case pdLong64 : {
			Long64Val = value.Long64Val;
		}
		break;

		case pdULong64 : {
			ULong64Val = value.ULong64Val;
		}
		break;

		case pdDateTime : {
			Long64Val = value.Long64Val;
		}
		break;

		case pdDateTimeSpan : {
			Long64Val = value.Long64Val;
		}
		break;

#endif // VCF_VARIANT64

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
#ifdef VCF_VARIANT64
			Long64Val = value.Long64Val;
			StringVal = value.StringVal;
#endif // VCF_VARIANT64
			type = value.type;
	}
}


/**
$Id$
*/
