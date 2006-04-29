#ifndef _VCF_SEMAPHORE_H__
#define _VCF_SEMAPHORE_H__
//Semaphore.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Semaphore.h: interface for the Semaphore class.


namespace VCF  {


/**
\class Semaphore Semaphore.h "vcf/FoundationKit/Semaphore.h"
Class Semaphore
@author Tiziano Franzoi, Nov 15, 2001
*/
class FOUNDATIONKIT_API Semaphore : public Object, public VCF::SynchObject
{
public:
	Semaphore(long initialCount = 1, long maxCount = 1);

	virtual ~Semaphore();

	virtual bool lock();

	virtual bool lock( uint32 timeoutInMilliseconds );

	virtual bool unlock();


	SemaphorePeer* getPeer() {
		return peer_;
	}
protected:
	SemaphorePeer* peer_;
};
}; // end of namespace VCF


#endif // _VCF_SEMAPHORE_H__

/**
$Id$
*/
