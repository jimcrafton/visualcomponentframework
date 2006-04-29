#ifndef _VCF_RESOURCEEXCEPTION_H__
#define _VCF_RESOURCEEXCEPTION_H__
//ResourceException.h

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
\class ResourceException ResourceException.h "vcf/FoundationKit/ResourceException.h"
*/
class FOUNDATIONKIT_API ResourceException : public RuntimeException{

public:
	ResourceException( const VCF::String & message ):
		RuntimeException( message ){

	};

	ResourceException():
		RuntimeException( RUNTIME_ERROR ){

	};

	ResourceException( const VCF::String & message, const int lineNumber ):
		VCF::RuntimeException(message, lineNumber){};

	virtual ~ResourceException() throw() {};

};

}; //end of namespace VCF


#endif // _VCF_RESOURCEEXCEPTION_H__

/**
$Id$
*/
