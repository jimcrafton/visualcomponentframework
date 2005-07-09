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
			long64::int64_t value = this->Long64Val;
			VCFChar tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, VariantData::DefaultPropertyValLength);
			swprintf( tmp, L"%I64d", (__int64)value );
			result += tmp;
		}
		break;

		case pdULong64:{
			ulong64::u64_t value = this->ULong64Val;
			VCFChar tmp[VariantData::DefaultPropertyValLength];
			memset(tmp, 0, VariantData::DefaultPropertyValLength);
			swprintf( tmp, L"%I64u", (unsigned __int64)value );
			result += tmp;
		}
		break;

		case pdDateTime:{
			DateTime dt = (long64)this->Long64Val;
			result += StringUtils::format( dt, L"%Y-%m-%d %H:%M:%S.%s (%w)%a" );
			//result += StringUtils::lowerCase( StringUtils::format( dt, L"%a" ) );
		}
		break;

		case pdDateTimeSpan:{
			DateTimeSpan dts = (long64)this->Long64Val;
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
			result = StringVal;
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

		case pdUInt:{
			UIntVal = StringUtils::fromStringAsUInt( value );
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
			ulong64::int64_t result = 0;
			int ret = swscanf( value.c_str(), L"%I64", &result );
			if ( ret != 1 ) {
				throw BasicException( L"Unable to convert: " + value );
			}
			Long64Val = result;

		}
		break;

		case pdULong64:{
			ulong64::u64_t result = 0;
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
			StringVal = value;
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
			StringVal = value.StringVal;
		}
		break;

		case pdEnum:{
			EnumVal = value.EnumVal;
		}
		break;

		case pdShort : {
			ShortVal = value.ShortVal;
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
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:06  ddiego
*merging in changes from devmain-0-6-7 branch.
*

*Revision 1.4  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.6  2005/06/26 01:49:58  marcelloptr
*added support for long64 and ulong64 and DateTime classes previous VCF_VARIANT64 macro
*
*Revision 1.3.2.3  2005/04/09 17:21:32  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.2  2004/12/24 04:53:59  marcelloptr
*added support for unsigned int in VariantData. Fixed other glitches of this class.
*
*Revision 1.3.2.1  2004/12/24 00:59:28  marcelloptr
*VariantData::toString() made const
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/28 20:14:36  marcelloptr
*minor fix on toString, case long
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*/


