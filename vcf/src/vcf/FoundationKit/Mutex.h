#ifndef _VCF_MUTEX_H__
#define _VCF_MUTEX_H__
//Mutex.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class MutexPeer;

/**
\class Mutex Mutex.h "vcf/FoundationKit/Mutex.h"
Class Mutex documentation
*/
class FOUNDATIONKIT_API Mutex : public Object, public SynchObject
{
public:

	Mutex();

	virtual ~Mutex();

    /* Acquires and locks mutex */
	virtual bool lock();

	virtual bool lock( uint32 timeoutInMilliseconds );

    /* Unlocks mutex */
	virtual bool unlock();

    /* Returns pointer to peer implementation */
	MutexPeer* getPeer() { return peer_; }

protected:

	MutexPeer* peer_;
};


}; //end of namespace VCF


#endif // _VCF_MUTEX_H__

/**
$Id$
*/
