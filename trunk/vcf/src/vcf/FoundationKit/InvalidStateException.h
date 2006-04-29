#ifndef _VCF_INVALIDSTATEEXCEPTION_H__
#define _VCF_INVALIDSTATEEXCEPTION_H__
//InvalidStateException.h

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
\class InvalidStateException InvalidStateException.h "vcf/FoundationKit/InvalidStateException.h"
*/
class APPLICATIONKIT_API InvalidStateException : public BasicException {
public:
	InvalidStateException(const VCF::String & message ):
		BasicException( message ){

	};

	InvalidStateException():
		BasicException( BAD_ITEMSTATE_EXCEPTION ){

	};

	InvalidStateException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};



};

}; //end of namespace VCF


#endif // _VCF_INVALIDSTATEEXCEPTION_H__

/**
$Id$
*/
