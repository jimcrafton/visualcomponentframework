#ifndef _VCF_NOTOOLKITFOUNDEXCEPTION_H__
#define _VCF_NOTOOLKITFOUNDEXCEPTION_H__
//NoToolKitFoundException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**
\class NoToolKitFoundException NoToolKitFoundException.h "vcf/FoundationKit/NoToolKitFoundException.h"
*/
class APPLICATIONKIT_API NoToolKitFoundException : public VCF::BasicException {
public:

	NoToolKitFoundException(const VCF::String & message):
	  VCF::BasicException( message ){};

	  NoToolKitFoundException():
		VCF::BasicException( NO_TOOLKIT_ERROR ){};

	virtual ~NoToolKitFoundException() throw() {};
};


#endif // _VCF_NOTOOLKITFOUNDEXCEPTION_H__

/**
$Id$
*/
