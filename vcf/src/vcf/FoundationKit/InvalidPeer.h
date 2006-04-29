#ifndef _VCF_INVALIDPEER_H__
#define _VCF_INVALIDPEER_H__
//InvalidPeer.h

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
\class InvalidPeer InvalidPeer.h "vcf/FoundationKit/InvalidPeer.h"
*/
class InvalidPeer : public BasicException{
public:

	InvalidPeer( const String & message ):
	  BasicException( message ){};

	InvalidPeer():
		BasicException( NO_PEER ){};

	InvalidPeer( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~InvalidPeer() throw() {};
};


};


#endif // _VCF_INVALIDPEER_H__

/**
$Id$
*/
