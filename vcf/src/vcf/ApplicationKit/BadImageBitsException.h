#ifndef _VCF_BADIMAGEBITSEXCEPTION_H__
#define _VCF_BADIMAGEBITSEXCEPTION_H__
//BadImageBitsException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/BasicException.h"


namespace VCF
{

/**
*This exception should be thrown when pointer access to the image's
*pixels has become corrupt. This is almost certainly an unrecoverable
*error.
*
*@version 1.0
*@author Jim Crafton
*/
class BadImageBitsException : public VCF::BasicException {
public:

	BadImageBitsException( const VCF::String & message ):
		BasicException( message ){};

	BadImageBitsException():
		BasicException( BAD_IMAGE_BITS_EXCEPTION ){};

	BadImageBitsException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};

	virtual ~BadImageBitsException() throw() {};
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_BADIMAGEBITSEXCEPTION_H__


