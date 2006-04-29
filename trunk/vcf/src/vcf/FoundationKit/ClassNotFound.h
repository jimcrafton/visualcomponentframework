#ifndef _VCF_CLASSNOTFOUND_H__
#define _VCF_CLASSNOTFOUND_H__
//ClassNotFound.h

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
\class ClassNotFound ClassNotFound.h "vcf/FoundationKit/ClassNotFound.h"
*Exception should be thrown when attempting to create
*a class or cast to class type that the run time system
*is unable to find.
*/
class FOUNDATIONKIT_API ClassNotFound : public BasicException
{
public:
	ClassNotFound():
		BasicException( CLASS_NOT_FOUND ){};

	ClassNotFound( const VCF::String & message ):
		BasicException( message ){};

	virtual ~ClassNotFound() throw() {};

};


};


#endif // _VCF_CLASSNOTFOUND_H__

/**
$Id$
*/
