#ifndef _VCF_FIELD_H__
#define _VCF_FIELD_H__
//Field.h

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
\class Field Field.h "vcf/FoundationKit/Field.h"
The Field class allows RTTI introspection to support member variables of
a class. There are some limits on how it works though, due to some
features of teh C++ langauge. At the very least you cannot use it
with member variables whose type is itself a class that has operator&
overloaded.
*/
class FOUNDATIONKIT_API Field {
public:
	Field() :source_(NULL){

	}

	Field( const Field& rhs ) :name_(rhs.name_), source_(rhs.source_) {

	}

	virtual ~Field(){}

	String getName() {
		return name_;
	}

	void setName( const String& name ) {
		name_ = name;
	}

	virtual Field* clone()  = 0;

	virtual ulong32 getFieldSize()  = 0;

	virtual String getFieldTypeName() = 0;

	virtual VariantData* get( Object* source ) = 0;

	virtual void set( Object* source, VariantData* data ) = 0;

	virtual void setSource( Object* source ) {
		source_ = source ;
	};

	VariantData* get() {
		if ( NULL == source_ ) {
			return NULL;
		}
		else {
			return get( source_ );
		}
	}

	void set( VariantData* data ) {
		if ( source_ != NULL ) {
			set( source_, data );
		}
	}
protected:
	String name_;
	Object* source_;
};



};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_FIELD_H__


