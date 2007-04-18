#ifndef _VCF_BADCOMPONENTSTATEEXCEPTION_H__
#define _VCF_BADCOMPONENTSTATEEXCEPTION_H__
//BadComponentStateException.h

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
\class BadComponentStateException BadComponentStateException.h "vcf/FoundationKit/BadComponentStateException.h"
*This exception should be thrown when a component is used in an incorrect way. FOr
*example, trying to display a component that requires a parent when the component
*has no parent would result in a BadComponentStateException being thrown.
*
*@version 1.0
*@author Jim Crafton
*/
class FOUNDATIONKIT_API BadComponentStateException : public BasicException {
public:

	BadComponentStateException( const VCF::String & message ):
		BasicException( message ){};

	BadComponentStateException():
		BasicException( BAD_COMPONENTSTATE_EXCEPTION ){};

	BadComponentStateException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};

	virtual ~BadComponentStateException() throw() {};


};

};


#endif // _VCF_BADCOMPONENTSTATEEXCEPTION_H__

/**
$Id$
*/
