#ifndef _VCF_BASICFILEERROR_H__
#define _VCF_BASICFILEERROR_H__
//BasicFileError.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

/**
\class BasicFileError BasicFileError.h "vcf/FoundationKit/BasicFileError.h"
*/
class FOUNDATIONKIT_API BasicFileError : public BasicException {
public:
	BasicFileError():
		BasicException( "" ){};

	BasicFileError( const String & message ):
		BasicException( message ){};

	virtual ~BasicFileError() throw() {};

};

};


#endif // _VCF_BASICFILEERROR_H__

/**
$Id$
*/
