#ifndef _VCF_COMPONENTINPUTSTREAM_H__
#define _VCF_COMPONENTINPUTSTREAM_H__
//ComponentInputStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/Stream.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sax/HandlerBase.hpp>
#include <map>

namespace VCF {

#define COMP_TOKEN_UNKNOWN				-1
#define COMP_TOKEN_OBJECT				0
#define COMP_TOKEN_CLASS				1
#define COMP_TOKEN_PROPERTY				2
#define COMP_TOKEN_NAME					3
#define COMP_TOKEN_VALUE				4
#define COMP_TOKEN_CHILDREN				5
#define COMP_TOKEN_OBJECT_PROPERTY		6
#define COMP_TOKEN_CLASSID				7
#define COMP_TOKEN_COMPONENTS			8

#define COMP_OBJECT				"object"
#define COMP_CLASS				"class"
#define COMP_PROPERTY			"property"
#define COMP_NAME				"name"
#define COMP_VALUE				"value"
#define COMP_CHILDREN			"children"
#define COMP_OBJECT_PROPERTY	"objectproperty"
#define COMP_CLASSID			"classid"
#define COMP_COMPONENTS			"components"



class Component;

class Container;

class Property;

class StrX;

class Control;
/**
*This stream is used to load a component from a stream. It is currently
based on the XML format. The DTD for components is extremely simple and is
*as follows:
*the component is declared as an "object" and can have 0 or more "property"s, or
*0 or more "object"s nested inside. A "property" must have a "name", which is a
*string, and a "value" which is a string representation of the property value.
*Basic types (int, double, et. al. ) are converted using the standard sscanf function
*and formatting specs (see CommonDefines.h for the exact formatting strings used).
*Objects are a bit different
*
*Because the XML specifiaction is used, ComponentInputStream derives also from HandlerBase
*which is a class in the Xerces-C library (see http://xml.apache.org/index.html). HandlerBase
*provides the basic handling of the XML format. The
*/

class APPLICATIONKIT_API ComponentInputStream : public InputStream, public HandlerBase
{
public:
	ComponentInputStream( InputStream* inStream );

	virtual ~ComponentInputStream();

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom);

	virtual unsigned long getSize();

	virtual char* getBuffer();

	virtual void read( char* bytesToRead, unsigned long sizeOfBytes );

	/**
	*returns the top elevel control found in the stream with all
	*of its children
	*/
	void readControl( Control** controlToReadInto );
	/**
    *Implementations of the SAX DocumentHandler interface
    */
    void endDocument();

    void endElement( const XMLCh* const name );

    void characters( const XMLCh* const chars, const unsigned int length );

    void ignorableWhitespace( const XMLCh* const chars, const unsigned int length );

    void processingInstruction( const XMLCh* const target, const XMLCh* const data );

    void startDocument();

    void startElement( const XMLCh* const name, AttributeList& attributes );

	/**
    *Implementations of the SAX ErrorHandler interface
    */
    void warning( const SAXParseException& exception );

    void error( const SAXParseException& exception );

    void fatalError( const SAXParseException& exception );

    /**
    *Implementation of the SAX DTDHandler interface
    */
    void notationDecl( const XMLCh* const name, const XMLCh* const publicId,
		               const XMLCh* const systemId );

    void unparsedEntityDecl( const XMLCh* const name, const XMLCh* const publicId,
		                     const XMLCh* const systemId, const XMLCh* const notationName );

	void init();

	virtual bool isEOS()
	{
		// stub impl.
		return false;
	}

private:
	InputStream* inStream_;
	bool doEscapes_;

	long getTokenFromString( const String& string );

	Object* component_;
	Container* prevContainer_;
	Container* currentContainer_;
	String currentPropertyClassName_;
	Object* currentObjectProperty_;
	Control* topLevelControl_;
	int objectPropertyLevel_;
	int collectionPropertyLevel_;
	Property* collectionProperty_;
	std::map<int, Object*> objectPropertyMap_;
	std::map<int, Property*> collectionPropertyMap_;
	std::map<int, Container*> containerPropertyMap_;
	int containerLevel_;

	bool topLevelComponentAlreadyExists_;
	void loadProperties( Object* object, AttributeList&  attributes );
};


/**
*This is a simple class that lets us do easy (though not terribly efficient)
*trancoding of XMLCh data to local code page for display.
*
*original source lifted from "Xerces" SaxPrint sample
*
*@author Jim Crafton
*@version 1.0
*/
class StrX {
public :

    StrX( const XMLCh* const toTranscode ) {
        // Call the private transcoding method
        localForm_ = XMLString::transcode(toTranscode);
    };

    virtual ~StrX(){
        delete [] localForm_;
    }

    const char* localForm() const
    {
        return localForm_;
    }

private :
    /**
    *This is the local code page form of the string.
    */
    char*   localForm_;
};

inline std::ostream& operator<<( std::ostream& target, const StrX& toDump )
{
    target << toDump.localForm();
    return target;
};

inline OutputStream& operator<<( OutputStream& target, const StrX& toDump)
{
    target << String( toDump.localForm() );
    return target;
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
*Revision 1.8.8.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:11:42  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMPONENTINPUTSTREAM_H__


