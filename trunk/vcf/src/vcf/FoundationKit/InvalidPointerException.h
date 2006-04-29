#ifndef _VCF_INVALIDPOINTEREXCEPTION_H__
#define _VCF_INVALIDPOINTEREXCEPTION_H__
//InvalidPointerException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{
/**
\class InvalidPointerException InvalidPointerException.h "vcf/FoundationKit/InvalidPointerException.h"
*/
class InvalidPointerException : public BasicException {
public:

	InvalidPointerException(const String & message ):
		BasicException( message ){

	};

	InvalidPointerException():
		BasicException( INVALID_POINTER_ERROR ){

	};

	InvalidPointerException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~InvalidPointerException() throw() {};

};


};


#endif // _VCF_INVALIDPOINTEREXCEPTION_H__

/**
$Id$
*/
