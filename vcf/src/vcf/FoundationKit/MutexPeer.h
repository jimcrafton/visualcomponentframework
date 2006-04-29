#ifndef _VCF_MUTEXPEER_H__
#define _VCF_MUTEXPEER_H__
//MutexPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
\class MutexPeer MutexPeer.h "vcf/FoundationKit/MutexPeer.h"
Class MutexPeer documentation
*/
class FOUNDATIONKIT_API MutexPeer {
public:
    MutexPeer(){}

	virtual ~MutexPeer(){}

	virtual bool lock() = 0;

	virtual bool lock( uint32 timeoutInMilliseconds ) = 0;

	virtual bool unlock() = 0;

	virtual OSHandleID getHandleID() = 0;
};


}; //end of namespace VCF


#endif // _VCF_MUTEXPEER_H__

/**
$Id$
*/
