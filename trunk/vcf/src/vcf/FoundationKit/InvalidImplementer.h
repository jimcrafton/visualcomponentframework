#ifndef _VCF_INVALIDIMPLEMENTER_H__
#define _VCF_INVALIDIMPLEMENTER_H__
//InvalidImplementer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//



#include "vcf/FoundationKit/BasicException.h"

namespace VCF
{

class InvalidImplementer : public BasicException{
public:

	InvalidImplementer( const VCF::String & message ):
	  VCF::BasicException( message ){};

	InvalidImplementer():
		VCF::BasicException( NO_IMPLEMENTER ){};

	InvalidImplementer( const VCF::String & message, const int lineNumber ):
		VCF::BasicException(message, lineNumber){};

	virtual ~InvalidImplementer() throw() {};
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_INVALIDIMPLEMENTER_H__


