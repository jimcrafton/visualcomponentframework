#ifndef _VCF_NOSUCHELEMENTEXCEPTION_H__
#define _VCF_NOSUCHELEMENTEXCEPTION_H__
//NoSuchElementException.h

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
\class NoSuchElementException NoSuchElementException.h "vcf/FoundationKit/NoSuchElementException.h"
*/
class FOUNDATIONKIT_API NoSuchElementException : public BasicException {
public:
	NoSuchElementException( const String & message ):
	  BasicException( message ){};

	NoSuchElementException():
		BasicException( NO_SUCH_ELEMENT_FOUND ){};

	NoSuchElementException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~NoSuchElementException() throw() {};
};

};


#endif // _VCF_NOSUCHELEMENTEXCEPTION_H__

/**
$Id$
*/
