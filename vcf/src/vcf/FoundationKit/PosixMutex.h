#ifndef _VCF_POSIXMUTEX_H__
#define _VCF_POSIXMUTEX_H__
//PosixMutex.h

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
*Class ConditionalPeer documentation
*/
class PosixMutex : public MutexPeer
{
public:

	PosixMutex();
	virtual ~PosixMutex();
	virtual bool lock();
    virtual bool lock( uint32 timeoutInMilliseconds );
	virtual bool unlock();
	virtual OSHandleID getHandleID() { return (OSHandleID)&mutex_; }

protected:

    pthread_mutex_t    mutex_;

};

};


#endif // _VCF_POSIXMUTEX_H__

/**
$Id$
*/
