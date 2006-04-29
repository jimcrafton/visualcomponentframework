#ifndef _VCF_WIN32MUTEX_H__
#define _VCF_WIN32MUTEX_H__
//Win32Mutex.h

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
*Class Win32Mutex documentation
*/
class Win32Mutex : public VCF::Object, public MutexPeer {
public:
	Win32Mutex();

	virtual ~Win32Mutex();

	virtual bool lock();

	virtual bool unlock();

	virtual bool lock( uint32 timeoutInMilliseconds );

	virtual OSHandleID getHandleID() {
		return (OSHandleID)mutexHandle_;
	}
protected:
	HANDLE mutexHandle_;

};


}; //end of namespace VCF


#endif // _VCF_WIN32MUTEX_H__

/**
$Id$
*/
