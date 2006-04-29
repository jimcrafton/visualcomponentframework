#ifndef _VCF_CONDITION_H__
#define _VCF_CONDITION_H__
//Condition.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ConditionPeer;

/**
\class Condition Condition.h "vcf/FoundationKit/Condition.h"
The Condition object is used as a synchronization primitive, like the Mutex, and
Semaphore. While the Mutex and Semaphore can cause multiple threads to block, waiting
for the mutex or semaphore to become signaled, only one thread will every wake at
any given moment. In contrast, a Condition can be used to wake up a series of threads
all waiting on the condition.

The Condition class follows the same pattern that the Pthreads condition variable
uses, or the <a href="http://boost.org/libs/thread/doc/condition.html">
Boost condition class</a>. In fact, the Win32 implementation is written largely
based of off the excellent code in the Boost condition class that was written by
<a href="http://boost.org/people/william_kempf.htm">William Kempf</a>.
*/
class FOUNDATIONKIT_API Condition : public Object, public Waitable
{
public:


    /**
	Every condtion must be associated with a mutex
	*/
	Condition( Mutex* mutex );

	virtual ~Condition();

    /**
	Signal one waiting thread that condition is true.
	*/
    void signal();

    /* Signal all waiting threads that condition is TRUE */
    virtual void broadcast();

    /* Returns pointer to peer implementation */
	ConditionPeer* getPeer() {
		return peer_;
	}

	/**
	Wait forever until the condition is signaled. The thread that calls this will block
	till the condition is signaled. If the wait fails the method will return
	Waitable::wrFail
	*/
	virtual Waitable::WaitResult wait();

	/**
	Wait for a maximum number of milliseconds until the condition is signaled.
	The thread that calls this will block till the condition is signaled. If the
	condition is signaled before the timeout period is ellapsed the function will
	return Waitable::wrTimeout value.
	*/
	Waitable::WaitResult wait( uint32 milliseconds );

	OSHandleID getPeerHandleID();

	/**
	Returns the mutex associated with the condition.
	*/
	Mutex* getMutex() {
		return mutex_;
	}
protected:
	Mutex* mutex_;
	ConditionPeer* peer_;
};


}; //end of namespace VCF


#endif // _VCF_CONDITION_H__

/**
$Id$
*/
