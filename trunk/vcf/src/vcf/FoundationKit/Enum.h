#ifndef _VCF_ENUM_H__
#define _VCF_ENUM_H__
//Enum.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Enum.h:



namespace VCF
{

/**
\class Enum Enum.h "vcf/FoundationKit/Enum.h"
The Enum class is used to wrap C++ enum types,
allowing the user to iterate forward and backward
through the enum type. This works best with enums
that have members whose value changes in intervals
of 1.
*/
class FOUNDATIONKIT_API Enum {
public:
	Enum(){};

	virtual ~Enum(){};

	/**
	*moves to the next value.
	*When the end of the enum is reached
	*it cycles back to the begining
	*@return int the int value of the enum
	*/
	virtual int next() = 0;

	/**
	*Moves to the last value of the enum
	*@return int the int value of the enum
	*/
	virtual int end() = 0;

	/**
	*gets the current value of the enum
	*@return int the int value of the enum
	*/
	virtual int get() = 0;

	/**
	*Moves to the first value of the enum
	*@return int the int value of the enum
	*/
	virtual int begin() = 0;

	/**
	*Sets the current value of the enum
	*@return int the int value of the enum
	*/
	virtual void set( const int& intVal ) = 0;

	

	operator int (){
		return get();
	};

	virtual String toString() = 0;

	/**
	*sets the enum val from a string. The default behaviour
	*is to assume the string represents an integer (i.e. "1" or "3")
	*if this is not the case then the enum wil be set to 0 value
	*/
	virtual void setFromString( const String& textVal, PropertyDescriptorType valueHint ){
		set( StringUtils::fromStringAsInt( textVal ) );
	};
};




/**
\class EnumValue Enum.h "vcf/FoundationKit/Enum.h"
*/
class FOUNDATIONKIT_API EnumValue {
public:
	Enum* getEnum() const {
		if ( NULL != enum_ ) {
			enum_->set( enumValue_ );
		}
		return enum_;
	}

	int getEnumVal() const {
		return 	enumValue_;
	}

	void set( const EnumValue& enumVal ) {
		enum_ = enumVal.enum_;
		if ( NULL != enum_ ) {
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

	void set( const String& stringVal ) {
		if ( NULL != enum_ ) {
			enum_->setFromString( stringVal,pdUndefined );
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

	void set( Enum* enumVal ) {
		enum_ = enumVal;
		if ( NULL != enum_ ) {
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

protected:
	int enumValue_;
	Enum* enum_;
};

};


#endif // _VCF_ENUM_H__

/**
$Id$
*/
