#ifndef _VCF_OUTOFBOUNDSEXCEPTION_H__
#define _VCF_OUTOFBOUNDSEXCEPTION_H__
//OutOfBoundsException.h

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
\class OutOfBoundsException OutOfBoundsException.h "vcf/FoundationKit/OutOfBoundsException.h"
*/
class FOUNDATIONKIT_API OutOfBoundsException : public BasicException {
public:
	OutOfBoundsException( const String & message ):
	  BasicException( message ){};

	OutOfBoundsException():
		BasicException( OUT_OF_BOUNDS_EXCEPTION ){};

	OutOfBoundsException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~OutOfBoundsException() throw() {};
};


};


#endif // _VCF_OUTOFBOUNDSEXCEPTION_H__

/**
$Id$
*/
