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
*VariantData represents an unknown type of variable - similiar to
*Visual Basic's Variant object.
*VariantData objects can store int, long, double, bool String, or Object*.
*VariantData overrides conversion operators and provides operator equals overloads
*to handle the conversion from one type to another. Setting the value of a VariantData
*automatically sets the type. For example:
*<pre>
*	VariantData val;
*	<b>int</b> i = 123;
*	val = i; <i>//automatically sets the VariantData::type to equal pdInt</i>
*</pre>
*To convert from one type to another is equally simple:
*<pre>
*	VariantData val;
*	<b>int</b> i;
*	<b>double</b> d;
*	val = 234.8546; <i>//val is 234.8546 and is set to the correct type</i>
*	d = val; <i>//val is converted to a double and d is assigned the value 234.8546</i>
*	val = 123; <i>//val is now assigned an int (or whatever the compiler assumes 123 is )</i>
*	i = val;	<i>//i is now equal to 123</i>
*</pre>
*Strings are a special case, since the compiler will not allow a union to be made with them,
*thus the reason for the StringVal member outside of the union.
*VariantData objects can also have their data render as a string and can be assigned strings
*and convert then to the correct data value.
*
*@version 1.0
*@author Jim Crafton
*/
class FOUNDATIONKIT_API VariantData /*: public Object*/ {
public:

	enum {
		DefaultPropertyValLength = 50
	};

	/**
	*creates an empty, undefined object
	*/
	VariantData(){
		ObjVal = NULL;
		this->type = pdUndefined;
	};

	/**
	*creates a VariantData initialized by an int value
	*/
	VariantData( const int& val ) {
		IntVal = val;
		type = pdInt;
	};

	/**
	*creates a VariantData initialized by a long value
	*/
	VariantData( const long& val ) {
		LongVal = val;
		type = pdLong;
	};

	/**
	*creates a VariantData initialized by an unsigned long value
	*/
	VariantData( const unsigned long& val ) {
		ULongVal = val;
		type = pdULong;
	};

	/**
	*creates a VariantData initialized by a float value
	*/
	VariantData( const float& val ) {
		FloatVal = val;
		type = pdFloat;
	};

	/**
	*creates a VariantData initialized by a double value
	*/
	VariantData( const double& val ) {
		DblVal = val;
		type = pdDouble;
	};

	/**
	*creates a VariantData initialized by a char value
	*/
	VariantData( const char& val ) {
		CharVal = val;
		type = pdChar;
	};

	/**
	*creates a VariantData initialized by a bool value
	*/
	VariantData( const bool& val ) {
		BoolVal = val;
		type = pdBool;
	};

	/**
	*creates a VariantData initialized by a short value
	*/
	VariantData( const short& val ) {
		ShortVal = val;
		type = pdShort;
	};

	/**
	*creates a VariantData initialized by a String value
	*/
	VariantData( const String& val ) {
		StringVal = val;
		type = pdString;
	};

	/**
	*creates a VariantData initialized by a Enum value
	*/
	VariantData( const Enum& val ) {
		EnumVal.set( const_cast<Enum*>(&val) );
		type = pdEnum;
	};

	/**
	*creates a VariantData initialized by a Enum value
	*/
	VariantData( Enum& val ) {
		EnumVal.set( &val );
		type = pdEnum;
	};

	/**
	*creates a VariantData initialized by a Enum* value
	*/
	VariantData( Enum* val ) {
		EnumVal.set( val );
		type = pdEnum;
	};

	/**
	*creates a VariantData initialized by a Object* value
	*/
	VariantData( Object* val ) {
		ObjVal = val;
		type = pdObject;
	}

	/**
	*creates a VariantData initialized by a Object& value
	*/
	VariantData( Object& val ) {
		ObjVal = &val;
		type = pdObject;
	}

	/**
	*creates a VariantData initialized by a const Object& value
	*/
	VariantData( const Object& val ){
		ObjVal = const_cast<Object*>(&val);
		type = pdObject;
	}

	/**
	*creates a VariantData initialized by a Interface* value
	*/
	VariantData( Interface* val ){
		InterfaceVal = val;
		type = pdInterface;
	}

	/**
	*copy constructor
	*/
	VariantData( const VariantData& value ){
		this->type = value.type;
		this->setValue( value );
	};

	virtual ~VariantData(){};

	/**
	*defines the data type of the VariantData, where type can represent
	*an int, long, unsigned long, short, char, double, float, bool, string,
	*Enum pointer, or Object pointer.
	*/
	PropertyDescriptorType type;

	union{
			int IntVal;
			long LongVal;
			short ShortVal;
			unsigned long ULongVal;
			float FloatVal;
			char CharVal;
			double DblVal;
			bool BoolVal;
			Object* ObjVal;
			EnumValue EnumVal;
			Interface* InterfaceVal;
	};

	/**
	*string are a special case, not allowed in unions
	*/
	String StringVal;

	/**
	*converts the VariantData to an int
	*/
	operator int () {
		return IntVal;
	};

	/**
	*converts the VariantData to an long
	*/
	operator long () {
		return LongVal;
	};

	/**
	*converts the VariantData to an short
	*/
	operator short () {
		return ShortVal;
	};

	/**
	*converts the VariantData to an unsigned long
	*/
	operator unsigned long () {
		return ULongVal;
	};

	/**
	*converts the VariantData to an float
	*/
	operator float () {
		return FloatVal;
	};

	/**
	*converts the VariantData to an char
	*/
	operator char () {
		return CharVal;
	};

	/**
	*converts the VariantData to an double
	*/
	operator double () {
		return DblVal;
	};

	/**
	*converts the VariantData to an Interface pointer
	*/
	operator Interface* (){
		return InterfaceVal;
	}

	/**
	*converts the VariantData to an Object pointer
	*/
	operator Object* (){
		return ObjVal;
	};

	/**
	*converts the VariantData to an Object reference
	*/
	operator Object& (){
		return *ObjVal;
	};

	/**
	*converts the VariantData to an String
	*/
	operator String () {
		return StringVal;
	};

	/**
	*converts the VariantData to a bool
	*/
	operator bool ()  {
		return BoolVal;
	};

	/**
	*converts the VariantData to an Enum pointer
	*/
	operator Enum* (){
		return EnumVal.getEnum();
	};

	/**
	*converts the VariantData to an Enum reference
	*/
	operator Enum& (){
		return *EnumVal.getEnum();
	};

	/**
	*Assigns an int value to the VariantData
	*/
	VariantData& operator=( const int& newValue ){
		IntVal = newValue;
		type = pdInt;
		return *this;
	};

	/**
	*Assigns an long value to the VariantData
	*/
	VariantData& operator=( const long& newValue ){
		LongVal = newValue;
		type = pdLong;
		return *this;
	};

	/**
	*Assigns an short value to the VariantData
	*/
	VariantData& operator=( const short& newValue ){
		ShortVal = newValue;
		type = pdShort;
		return *this;
	};

	/**
	*Assigns an unsigned long value to the VariantData
	*/
	VariantData& operator=( const unsigned long& newValue ){
		ULongVal = newValue;
		type = pdULong;
		return *this;
	};

	/**
	*Assigns an float value to the VariantData
	*/
	VariantData& operator=( const float& newValue ){
		FloatVal = newValue;
		type = pdFloat;
		return *this;
	};

	/**
	*Assigns an char value to the VariantData
	*/
	VariantData& operator=( const char& newValue ){
		CharVal = newValue;
		type = pdChar;
		return *this;
	};

	/**
	*Assigns an double value to the VariantData
	*/
	VariantData& operator=( const double& newValue ){
		DblVal = newValue;
		type = pdDouble;
		return *this;
	};

	/**
	*Assigns an bool value to the VariantData
	*/
	VariantData& operator=( const bool& newValue ){
		BoolVal = newValue;
		type = pdBool;
		return *this;
	};

	/**
	*Assigns an string (as an array of char's) to the VariantData
	*/
	VariantData& operator=( const char* newValue ){
		StringVal = newValue;
		type = pdString;
		return *this;
	};

	/**
	*Assigns an Interface pointer to the VariantData
	*/
	VariantData& operator=( Interface* newValue ){
		//ObjVal->copy( newValue );
		InterfaceVal = newValue;
		type = pdInterface;
		return *this;
	};

	/**
	*Assigns an Object pointer to the VariantData
	*/
	VariantData& operator=( Object* newValue ){
		//ObjVal->copy( newValue );
		ObjVal = newValue;
		type = pdObject;
		return *this;
	};

	/**
	*Assigns an Object reference to the VariantData
	*/
	VariantData& operator=( const Object& newValue ){
		//ObjVal->copy( newValue );
		ObjVal = const_cast<Object*>(&newValue);
		type = pdObject;
		return *this;
	};

	/**
	*Assigns an string (as an String) to the VariantData
	*/
	VariantData& operator=( const String& newValue ){
		StringVal = newValue;
		type = pdString;
		return *this;
	};

	/**
	*Assigns an Enum pointer to the VariantData
	*/
	VariantData& operator=( Enum* newValue ){
		EnumVal.set( newValue );
		type = pdEnum;
		return *this;
	};

	/**
	*Assigns an Enum reference to the VariantData
	*/
	VariantData& operator=( const Enum& newValue ){
		EnumVal.set( const_cast<Enum*>(&newValue) );
		type = pdEnum;
		return *this;
	};

	VariantData& operator= ( const VariantData& newValue ) {
		setValue( newValue );
		return *this;
	}

	VariantData& operator= ( VariantData* newValue ) {
		setValue( *newValue );
		return *this;
	}

	/**
	*converts the VariantData to a string, no matter
	*what the type. Object* are persisted to a TextOutputStream
	*if they support Persistable, otherwise the Object's toString()
	*method is invoked.
	*/
	virtual String toString();
	/**
	*Assigns the VariantData's data from a string. The conversion
	*process is dependent on the type of the VariantData.
	*/
	void setFromString( const String& value );

protected:
	void setValue( const VariantData& value );
};



};


/**
*CVS Log info
*$Log$
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


