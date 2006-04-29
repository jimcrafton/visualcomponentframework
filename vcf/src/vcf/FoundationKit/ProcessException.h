#ifndef _VCF_PROCESSEXCEPTION_H__
#define _VCF_PROCESSEXCEPTION_H__
//ProcessException.h

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
\class ProcessException ProcessException.h "vcf/FoundationKit/ProcessException.h"
*/
class FOUNDATIONKIT_API ProcessException : public RuntimeException{

public:
	ProcessException( const String& message ) : RuntimeException(message) {};

	ProcessException(): RuntimeException("Can't start process."){};

	virtual ~ProcessException() throw() {};

};

}; //end of namespace VCF


#endif // _VCF_PROCESSEXCEPTION_H__

/**
$Id$
*/
