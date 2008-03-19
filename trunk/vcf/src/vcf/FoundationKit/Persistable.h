#ifndef _VCF_PERSISTABLE_H__
#define _VCF_PERSISTABLE_H__
//Persistable.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/FilePath.h"
#include "vcf/FoundationKit/MIMEType.h"




namespace VCF {

class OutputStream;
class InputStream;


/**
\class Persistable Persistable.h "vcf/FoundationKit/Persistable.h"
Persistable is a simple interface used to indicate that an object
can read or write itself to an input or output stream. This assumes 
that the object has been instantiated already. 

Reading the object from a stream is done by implementing the 
loadFromStream method, and writing the object is accomplished 
by implementing the saveToStream method.

In both cases (loadFromStream() or saveToStream()) an
optional type may be passed which indicates to the 
object what kind of data may be present in the stream or
what kind of preferred data should be written to the
stream. The default value for this parameter is empty (see
MIMEType::isEmpty() ) and can be ignored if you don't require 
it.

@see MIMEType
@see OutputStream
@see InputStream
*/
class FOUNDATIONKIT_API Persistable {
public:

	virtual ~Persistable(){};

	/**
	Write the object to the specified output stream	
	@param OutputStream
	@param MIMEType indicates how the object should write it's 
	data. For example, if the object was some sort of image 
	object, and had an array of pixels, then the type might
	indicate what kind of image type to write the data in,
	such as the JPEG format ("image/jpeg"), or the PNG format
	("image/png").

	*/
    virtual void saveToStream( OutputStream * stream, const MIMEType& type=MIMEType() ) = 0;

	/**
	Read the object from the specified input stream
	@param InputStream
	@param MIMEType indicates how to read the data from the stream. For 
	example, if the object was some sort of image object, and had an 
	array of pixels, then the type might indicate how the data in the 
	stream should be interpreted, such as the JPEG format ("image/jpeg"), 
	or the PNG format ("image/png").
	*/
    virtual void loadFromStream( InputStream * stream, const MIMEType& type=MIMEType() ) = 0;


};

};


#endif // _VCF_PERSISTABLE_H__

/**
$Id$
*/
