#ifndef _VCF_POSIXTHREAD_H__
#define _VCF_POSIXTHREAD_H__
//PosixThread.h

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

class PosixThread : public ThreadPeer
{

public:

    /* Creates a normal priority, joinable thread */
    PosixThread( Thread* thread, bool mainThread);

    /* Cancels the thread if it is still running */
	virtual ~PosixThread();

    /* Start the thread */
	virtual bool start();

    /* Stops the thread.  If called in Thread::run() the thread exits. */
	virtual void stop();

    /* Returns thread id */
	virtual uint32 getThreadID() {
		return threadID_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)threadID_;
	}

    /* Returns process that created thread.  Is this useful? */
	virtual uint32 getOwningProcessID() {
		return processID_;
	}

    /* Returns TRUE if called in Thread::run(), FALSE if not */
    int inThreadProc() {
		return pthread_equal(pthread_self(), threadID_) != 0;
	}

	virtual void sleep( uint32 milliseconds );

	virtual int wait();

	virtual int wait( uint32 milliseconds );

	virtual bool isActive() {
		return isActive_;
	}
	
protected:
    static void* threadProc(void* arg);

protected:

	pthread_t threadID_;
    pid_t     processID_;
	Thread*   thread_;
    bool      isActive_;

	// these are required to create the thread suspended.
	Mutex     threadSuspendMutex_;
	Condition threadSuspendCond_;
};

};


#endif // _VCF_POSIXTHREAD_H__

/**
$Id$
*/
