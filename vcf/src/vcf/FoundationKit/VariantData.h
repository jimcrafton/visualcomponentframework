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
	creates a Variant initialized by a long64 value
	*/
	VariantData( const VCF::long64& val ) {
		Long64Val = val;
		type = pdLong64;
	};

	/**
	creates a Variant initialized by a ulong64 value
	*/
	VariantData( const VCF::ulong64& val ) {
		ULong64Val = val;
		type  = pdULong64;
	};

	/**
	creates a Variant initialized by a DateTime value
	*/
	VariantData( const DateTime& val ) {
		Long64Val = ( val.operator long64() ).data_; // (ulong64::u64_t) (VCF::ulong64&) val;
		type  = pdDateTime;
	};

	/**
	creates a Variant initialized by a DateTimeSpan value
	*/
	VariantData( const DateTimeSpan& val ) {
		Long64Val = ( val.operator long64() ).data_; // (ulong64::u64_t) (VCF::ulong64&) val;
		type  = pdDateTimeSpan;
	};

	///**
	//creates a Variant initialized by a Color value
	//*/
	//VariantData( const Color& val ) {
	//	Long64Val = ( val.operator long64() ).data_; // (ulong64::u64_t) (VCF::ulong64&) val;
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
	converts the Variant to a long64
	*/
	operator VCF::long64 () const {
		return Long64Val;
	};

	/**
	converts the Variant to an ulong64
	*/
	operator VCF::ulong64 () const {
		return ULong64Val;
	};

	/**
	converts the Variant to a DateTime
	*/
	operator VCF::DateTime () const {
		return (long64) Long64Val; // uses the conversion DateTime::operator long64()
	};

	/**
	converts the Variant to a DateTimeSpan
	*/
	operator VCF::DateTimeSpan () const {
		return (long64) Long64Val; // uses the conversion DateTimeSpan::operator long64()
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
	Assigns a long64 value to the Variant
	*/
	VariantData& operator= ( const long64& newValue ){
		Long64Val = newValue;
		type = pdLong64;
		return *this;
	};

	/**
	Assigns an ulong64 value to the Variant
	*/
	VariantData& operator= ( const ulong64& newValue ){
		ULong64Val = newValue;
		type = pdULong64;
		return *this;
	};

	/**
	Assigns a DateTime value to the Variant
	*/
	VariantData& operator= ( const DateTime& newValue ){
		Long64Val = ( newValue.operator long64() ).data_;
		type = pdDateTime;
		return *this;
	};

	/**
	Assigns a DateTimeSpan value to the Variant
	*/
	VariantData& operator= ( const DateTimeSpan& newValue ){
		Long64Val = ( newValue.operator long64() ).data_;
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
			VCF::ulong64::int64_t Long64Val;
			VCF::ulong64::u64_t   ULong64Val;
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


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.3  2006/03/12 22:01:44  ddiego
*doc updates.
*
*Revision 1.5.2.2  2006/02/23 01:41:58  ddiego
*some minor changes to teh variantdata class, added support for specific char* and WideChar* cosntructor and for unsigned short types.
*
*Revision 1.5.2.1  2005/08/01 17:20:46  marcelloptr
*minor changes
*
*Revision 1.5  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.4  2005/07/09 23:15:06  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.7  2005/06/26 01:49:59  marcelloptr
*added support for long64 and ulong64 and DateTime classes previous VCF_VARIANT64 macro
*
*Revision 1.2.4.4  2005/06/07 16:32:48  marcelloptr
*code simply rearranged
*
*Revision 1.2.4.3  2005/02/24 05:51:05  marcelloptr
*Added comparison operators to VariantData
*
*Revision 1.2.4.2  2004/12/24 04:53:59  marcelloptr
*added support for unsigned int in VariantData. Fixed other glitches of this class.
*
*Revision 1.2.4.1  2004/12/24 00:59:28  marcelloptr
*VariantData::toString() made const
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.5.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.4.2.1  2004/01/18 04:52:45  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.4  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.3  2003/05/17 20:37:05  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.2.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*
*/


#endif // _VCF_VARIANTDATA_H__


