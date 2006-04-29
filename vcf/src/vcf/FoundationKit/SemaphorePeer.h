#ifndef _VCF_SEMAPHOREPEER_H__
#define _VCF_SEMAPHOREPEER_H__
//SemaphorePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// SemaphorePeer.h: interface for the SemaphorePeer class.



namespace VCF  {

/**
\class SemaphorePeer SemaphorePeer.h "vcf/FoundationKit/SemaphorePeer.h"
*Class MutexPeer documentation
*/
class FOUNDATIONKIT_API SemaphorePeer
{
public:
	virtual ~SemaphorePeer(){}

	virtual bool lock() = 0;

	virtual bool lock( uint32 timeoutInMilliseconds ) = 0;

	virtual bool unlock() = 0;

	virtual OSHandleID getHandleID() = 0;

};
} // end of namespace VCF


#endif // _VCF_SEMAPHOREPEER_H__

/**
$Id$
*/
