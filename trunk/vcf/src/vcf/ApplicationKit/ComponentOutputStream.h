#ifndef _VCF_COMPONENTOUTPUTSTREAM_H__
#define _VCF_COMPONENTOUTPUTSTREAM_H__
//ComponentOutputStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/Stream.h"
#include "vcf/FoundationKit/Persistable.h"

namespace VCF
{

class Control;

class Persistable;

class Property;

class VariantData;

class APPLICATIONKIT_API ComponentOutputStream : public OutputStream
{
public:
	ComponentOutputStream( OutputStream* outStream );

	virtual ~ComponentOutputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	virtual unsigned long getSize();

	virtual char* getBuffer();

	virtual void write( char* bytesToWrite, unsigned long sizeOfBytes );

	virtual void write( Persistable* persistableObject ){
		OutputStream::write( persistableObject );
	};

	virtual void write( const short& val );

	virtual void write( const long& val );

	virtual void write( const int& val );

	virtual void write( const bool& val );

	virtual void write( const char& val );

	virtual void write( const float& val );

	virtual void write( const double& val );

	virtual void write( const String& val );

	/**
	*Writing a component out to a ComponentOutputStream takes
	*the following steps:
	*	1.	Open a <object> tag and write out the class name (<object class="component::ClassName" )
	*	2.	Get the Class for the component and then write out the properties
	*	3.	For each property write out a <property> tag with the name of the
	*		property (<property name="propertyName" ). If the value of the property
	*		is a basic type (i.e. int, double, etc ), then write out the string value
	*		of the property. If the property value is a Object* then the value should be the
	*		class name of the Object* ( <property name="listModel" value="DefaultListModel"> ).
	*	4.	If the value of the property is a Object* then open a new <objectProperty> tag. Follow
	*		steps 2 & 3. Close out the tag with a </objectProperty> tag.
	*	5.	Close the <property> tag with a </property> tag.
	*	6.	Close the <object> tag with </object>.
	*/
	void writeComponent( Component * component );
private:
	OutputStream* outStream_;
	bool needsDTD_;
	void writeProperty( Property* property, Object* source );
	void writePropertyValue( const String& propName, VariantData* value );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.6.8.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.22.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.22.1  2003/03/12 03:11:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMPONENTOUTPUTSTREAM_H__


