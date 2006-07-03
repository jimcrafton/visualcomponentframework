#ifndef _VCF_VARIANTDATA_H__
#define _VCF_VARIANTDATA_H__
//VariantData.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


/**
\class VariantData VariantData.h "vcf/FoundationKit/VariantData.h"
VariantData represents an unknown type of variable - similiar to
Visual Basic's Variant object.
VariantData objects can store int, long, double, bool String, or Object*.
VariantData overrides conversion operators and provides operator equals overloads
to handle the conversion from one type to another. Setting the value of a VariantData
automatically sets the type. For example:
\code
	VariantData val;
	int i = 123;
	val = i; //automatically sets the VariantData::type to equal pdInt
\endcode
To convert from one type to another is equally simple:
\code
	VariantData val;
	int i;
	double d;
	val = 234.8546; //val is 234.8546 and is set to the correct type
	d = val; //val is converted to a double and d is assigned the value 234.8546
	val = 123; //val is now assigned an int (or whatever the compiler assumes 123 is )
	i = val;	//i is now equal to 123
\endcode
Strings are a special case, since the compiler will not allow a union to be made with them,
thus the reason for the StringVal member outside of the union.
VariantData objects can also have their data render as a string and can be assigned strings
and convert then to the correct data value.
*
*@version 1.0
*@author Jim Crafton
*/
class FOUNDATIONKIT_API VariantData  {
public:

	enum {
		DefaultPropertyValLength = 50
	};

	/**
	creates an empty, undefined object
	*/
	VariantData(){
		ObjVal = NULL;
		this->type = pdUndefined;
	};

	/**
	creates a VariantData initialized by an int value
	*/
	VariantData( const int& val ) {
		IntVal = val;
		type = pdInt;
	};

	/**
	creates a VariantData initialized by an unsigned int value
	*/
	VariantData( const unsigned int& val ) {
		UIntVal = val;
		type = pdUInt;
	};

	/**
	creates a VariantData initialized by a long value
	*/
	VariantData( const long& val ) {
		LongVal = val;
		type = pdLong;
	};

	/**
	creates a VariantData initialized by an unsigned long value
	*/
	VariantData( const unsigned long& val ) {
		ULongVal = val;
		type = pdULong;
	};

	/**
	creates a VariantData initialized by a float value
	*/
	VariantData( const float& val ) {
		FloatVal = val;
		type = pdFloat;
	};

	/**
	creates a VariantData initialized by a double value
	*/
	VariantData( const double& val ) {
		DblVal = val;
		type = pdDouble;
	};

	/**
	creates a VariantData initialized by a char value
	*/
	VariantData( const char& val ) {
		CharVal = val;
		type = pdChar;
	};

	/**
	creates a VariantData initialized by a bool value
	*/
	VariantData( const bool& val ) {
		BoolVal = val;
		type = pdBool;
	};

	/**
	creates a VariantData initialized by a short value
	*/
	VariantData( const short& val ) {
		ShortVal = val;
		type = pdShort;
	};

	/**
	creates a VariantData initialized by a short value
	*/
	VariantData( const ushort& val ) {
		UShortVal = val;
		type = pdUShort;
	};


	/**
	creates a VariantData initialized by a String value
	*/
	VariantData( const String& val ) {
		StringVal = val;
		type = pdString;
	};

	VariantData( const char* val ) {
		StringVal = val;
		type = pdString;
	};

	VariantData( const WideChar* val ) {
		StringVal = val;
		type = pdString;
	};

	/**
	creates a VariantData initialized by a Enum value
	*/
	VariantData( const Enum& val ) {
		EnumVal.set( const_cast<Enum*>(&val) );
		type = pdEnum;
	};

	/**
	creates a VariantData initialized by a Enum value
	*/
	VariantData( Enum& val ) {
		EnumVal.set( &val );
		type = pdEnum;
	};

	/**
	creates a VariantData initialized by a Enum* value
	*/
	VariantData( Enum* val ) {
		EnumVal.set( val );
		type = pdEnum;
	};

	/**
	creates a VariantData initialized by a Object* value
	*/
	VariantData( Object* val ) {
		ObjVal = val;
		type = pdObject;
	}

	/**
	creates a VariantData initialized by a Object& value
	*/
	VariantData( Object& val ) {
		ObjVal = &val;
		type = pdObject;
	}

	/**
	creates a VariantData initialized by a const Object& value
	*/
	VariantData( const Object& val ){
		ObjVal = const_cast<Object*>(&val);
		type = pdObject;
	}

	/**
	creates a VariantData initialized by a Interface* value
	*/
	VariantData( Interface* val ){
		InterfaceVal = val;
		type = pdInterface;
	}

#ifdef VCF_VARIANT64
	/**
	creates a Variant initialized by a int64 value
	*/
	VariantData( const VCF::int64& val ) {
		Long64Val = val;
		type = pdLong64;
	};

	/**
	creates a Variant initialized by a uint64 value
	*/
	VariantData( const VCF::uint64& val ) {
		ULong64Val = val;
		type  = pdULong64;
	};

	/**
	creates a Variant initialized by a DateTime value
	*/
	VariantData( const DateTime& val ) {
		Long64Val = ( val.operator int64() ).data_; // (uint64::u64_t) (VCF::uint64&) val;
		type  = pdDateTime;
	};

	/**
	creates a Variant initialized by a DateTimeSpan value
	*/
	VariantData( const DateTimeSpan& val ) {
		Long64Val = ( val.operator int64() ).data_; // (uint64::u64_t) (VCF::uint64&) val;
		type  = pdDateTimeSpan;
	};

	///**
	//creates a Variant initialized by a Color value
	//*/
	//VariantData( const Color& val ) {
	//	Long64Val = ( val.operator int64() ).data_; // (uint64::u64_t) (VCF::uint64&) val;
	//	type  = pdDateTimeSpan;
	//};

#endif // VCF_VARIANT64

	/**
	copy constructor
	*/
	VariantData( const VariantData& value ){
		this->type = value.type;
		this->setValue( value );
	};

	/**
	destructor
	*/
	virtual ~VariantData(){};

public:


	/**
	comparison operator
	*/
	bool operator == ( const VariantData& v ) const {
		return (	type == v.type &&
		          ( ( type == pdString && StringVal == v.StringVal ) ||
		            ( type != pdString && ObjVal == v.ObjVal ) )
		          );
	}

	/**
	comparison operator
	*/
	bool operator != ( const VariantData& v ) const {
		return ( !operator==( v ) );
	}

	/**
	*
	conversion operators
	*
	*/



	/**
	converts the VariantData to an int
	*/
	operator int () const {
		return IntVal;
	};

	/**
	converts the VariantData to an long
	*/
	operator long () const {
		return LongVal;
	};

	/**
	converts the VariantData to an short
	*/
	operator short () const {
		return ShortVal;
	};

	/**
	converts the VariantData to an unsigned short
	*/
	operator ushort () const {
		return UShortVal;
	};

	/**
	converts the VariantData to an unsigned int
	*/
	operator unsigned int () const {
		return UIntVal;
	};

	/**
	converts the VariantData to an unsigned long
	*/
	operator unsigned long () const {
		return ULongVal;
	};

	/**
	converts the VariantData to an float
	*/
	operator float () const {
		return FloatVal;
	};

	/**
	converts the VariantData to an char
	*/
	operator char () const {
		return CharVal;
	};

	/**
	converts the VariantData to an double
	*/
	operator double () const {
		return DblVal;
	};

	/**
	converts the VariantData to an Interface pointer
	*/
	operator Interface* () const {
		return InterfaceVal;
	}

	/**
	converts the VariantData to an Object pointer
	*/
	operator Object* () const {
		return ObjVal;
	};

	/**
	converts the VariantData to an Object reference
	*/
	operator Object& () const {
		return *ObjVal;
	};

	/**
	converts the VariantData to an String
	*/
	operator String () const {
		return StringVal;
	};

	/**
	converts the VariantData to a bool
	*/
	operator bool () const {
		return BoolVal;
	};

	/**
	converts the VariantData to an Enum pointer
	*/
	operator Enum* () const {
		return EnumVal.getEnum();
	};

	/**
	converts the VariantData to an Enum reference
	*/
	operator Enum& () const {
		return *EnumVal.getEnum();
	};

#ifdef VCF_VARIANT64
	/**
	converts the Variant to a int64
	*/
	operator VCF::int64 () const {
		return Long64Val;
	};

	/**
	converts the Variant to an uint64
	*/
	operator VCF::uint64 () const {
		return ULong64Val;
	};

	/**
	converts the Variant to a DateTime
	*/
	operator VCF::DateTime () const {
		return (int64) Long64Val; // uses the conversion DateTime::operator int64()
	};

	/**
	converts the Variant to a DateTimeSpan
	*/
	operator VCF::DateTimeSpan () const {
		return (int64) Long64Val; // uses the conversion DateTimeSpan::operator int64()
	};

	///**
	//converts the Variant to a Color
	//*/
	//operator VCF::Color () const {
	//	return Color(ULong64Val);
	//};
#endif // VCF_VARIANT64



	/*
	*
	*	Assignments
	*
	*/

	VariantData& operator= ( const VariantData& newValue ) {
		setValue( newValue );
		return *this;
	}

	VariantData& operator= ( VariantData* newValue ) {
		setValue( *newValue );
		return *this;
	}


	/**
	*Assigns an int value to the VariantData
	*/
	VariantData& operator=( const int& newValue ){
		IntVal = newValue;
		type = pdInt;
		return *this;
	};

	/**
	Assigns an long value to the VariantData
	*/
	VariantData& operator=( const long& newValue ){
		LongVal = newValue;
		type = pdLong;
		return *this;
	};

	/**
	Assigns an short value to the VariantData
	*/
	VariantData& operator=( const short& newValue ){
		ShortVal = newValue;
		type = pdShort;
		return *this;
	};

	/**
	Assigns an unsigned short value to the VariantData
	*/
	VariantData& operator=( const ushort& newValue ){
		UShortVal = newValue;
		type = pdUShort;
		return *this;
	};

	/**
	Assigns an unsigned int value to the VariantData
	*/
	VariantData& operator=( const unsigned int& newValue ){
		UIntVal = newValue;
		type = pdUInt;
		return *this;
	};

	/**
	Assigns an unsigned long value to the VariantData
	*/
	VariantData& operator=( const unsigned long& newValue ){
		ULongVal = newValue;
		type = pdULong;
		return *this;
	};

	/**
	Assigns an float value to the VariantData
	*/
	VariantData& operator=( const float& newValue ){
		FloatVal = newValue;
		type = pdFloat;
		return *this;
	};

	/**
	Assigns an char value to the VariantData
	*/
	VariantData& operator=( const char& newValue ){
		CharVal = newValue;
		type = pdChar;
		return *this;
	};

	/**
	Assigns an double value to the VariantData
	*/
	VariantData& operator=( const double& newValue ){
		DblVal = newValue;
		type = pdDouble;
		return *this;
	};

	/**
	Assigns an bool value to the VariantData
	*/
	VariantData& operator=( const bool& newValue ){
		BoolVal = newValue;
		type = pdBool;
		return *this;
	};

	/**
	Assigns an string (as an array of char's) to the VariantData
	*/
	VariantData& operator=( const char* newValue ){
		StringVal = newValue;
		type = pdString;
		return *this;
	};

	/**
	Assigns an Interface pointer to the VariantData
	*/
	VariantData& operator=( Interface* newValue ){
		//ObjVal->copy( newValue );
		InterfaceVal = newValue;
		type = pdInterface;
		return *this;
	};

	/**
	Assigns an Object pointer to the VariantData
	*/
	VariantData& operator=( Object* newValue ){
		//ObjVal->copy( newValue );
		ObjVal = newValue;
		type = pdObject;
		return *this;
	};

	/**
	Assigns an Object reference to the VariantData
	*/
	VariantData& operator=( const Object& newValue ){
		//ObjVal->copy( newValue );
		ObjVal = const_cast<Object*>(&newValue);
		type = pdObject;
		return *this;
	};

	/**
	Assigns an string (as an String) to the VariantData
	*/
	VariantData& operator=( const String& newValue ){
		StringVal = newValue;
		type = pdString;
		return *this;
	};

	/**
	Assigns an Enum pointer to the VariantData
	*/
	VariantData& operator=( Enum* newValue ){
		EnumVal.set( newValue );
		type = pdEnum;
		return *this;
	};

	/**
	Assigns an Enum reference to the VariantData
	*/
	VariantData& operator=( const Enum& newValue ){
		EnumVal.set( const_cast<Enum*>(&newValue) );
		type = pdEnum;
		return *this;
	};


#ifdef VCF_VARIANT64
	/**
	Assigns a int64 value to the Variant
	*/
	VariantData& operator= ( const int64& newValue ){
		Long64Val = newValue;
		type = pdLong64;
		return *this;
	};

	/**
	Assigns an uint64 value to the Variant
	*/
	VariantData& operator= ( const uint64& newValue ){
		ULong64Val = newValue;
		type = pdULong64;
		return *this;
	};

	/**
	Assigns a DateTime value to the Variant
	*/
	VariantData& operator= ( const DateTime& newValue ){
		Long64Val = ( newValue.operator int64() ).data_;
		type = pdDateTime;
		return *this;
	};

	/**
	Assigns a DateTimeSpan value to the Variant
	*/
	VariantData& operator= ( const DateTimeSpan& newValue ){
		Long64Val = ( newValue.operator int64() ).data_;
		type = pdDateTimeSpan;
		return *this;
	};
#endif // VCF_VARIANT64



	/**
	converts the VariantData to a string, no matter
	what the type. Object* are persisted to a TextOutputStream
	if they support Persistable, otherwise the Object's toString()
	method is invoked.
	*/
	virtual String toString() const;

	/**
	Assigns the VariantData's data from a string. The conversion
	process is dependent on the type of the VariantData.
	*/
	void setFromString( const String& value );

protected:
	void setValue( const VariantData& value );


public:
	union{
			int IntVal;
			long LongVal;
			short ShortVal;
			ushort UShortVal;
			unsigned int UIntVal;
			unsigned long ULongVal;
			float FloatVal;
			char CharVal;
			double DblVal;
			bool BoolVal;
			Object* ObjVal;
			EnumValue EnumVal;
			Interface* InterfaceVal;
#ifdef VCF_VARIANT64
			VCF::uint64::int64_t Long64Val;
			VCF::uint64::u64_t   ULong64Val;
#endif // VCF_VARIANT64
	};

	/**
	string are a special case, not allowed in unions
	*/
	String StringVal;

	/**
	defines the data type of the VariantData, where type can represent
	an int, unsigned int, long, unsigned long, short, char, 
	double, float, bool, string, Enum pointer, or Object pointer.
	*/
	PropertyDescriptorType type;

};



}; // namespace VCF


#endif // _VCF_VARIANTDATA_H__

/**
$Id$
*/
