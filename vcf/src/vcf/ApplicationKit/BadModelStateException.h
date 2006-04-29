#ifndef _VCF_BADMODELSTATEEXCEPTION_H__
#define _VCF_BADMODELSTATEEXCEPTION_H__
//BadModelStateException.h

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
\class BadModelStateException BadModelStateException.h "vcf/ApplicationKit/BadModelStateException.h"

*Throw when a model state has changed and it is determined that the change makes the
*model corrupt or invalid. This error is probably recoverable.
*
*@version 1.0
*author Jim Crafton
*/
class APPLICATIONKIT_API BadModelStateException : public VCF::BasicException {
public:
	BadModelStateException( const VCF::String & message ):
		BasicException( message ){};

	BadModelStateException():
		BasicException( BAD_MODEL_STATE_EXCEPTION ){};

	BadModelStateException( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};

	virtual ~BadModelStateException() throw() {};

};

};


#endif // _VCF_BADMODELSTATEEXCEPTION_H__

/**
$Id$
*/
