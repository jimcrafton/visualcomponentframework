#ifndef _VCF_OSXTHREAD_H__
#define _VCF_OSXTHREAD_H__
//OSXThread.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{

class OSXThread : public ThreadPeer
{

public:
    enum {
        k_eExecutionContextSystemTask,
        k_eExecutionContextDeferredTask,
        k_eExecutionContextMPTask,
        k_eExecutionContextOther
    };

    /* Creates a normal priority, joinable thread */
    OSXThread( Thread* thread, bool mainThread );

    /* Cancels the thread if it is still running */
	virtual ~OSXThread();

    /* Start the thread */
	virtual bool start();

    /* Stops the thread.  If called in Thread::run() the thread exits. */
	virtual void stop();

    /* Returns thread id */
	virtual uint32 getThreadID() {
		return (uint32)taskID_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)taskID_;
	}

    /** Returns process that created thread.  Is this useful?
    For OSX this is a pointer to a ProcessSerialNumber struct. See
    the ProcessManager API for more info
    */
	virtual uint32 getOwningProcessID() {
		return (uint32)&processID_;
	}

    /* Returns TRUE if thread is running, FALSE if not */
    virtual bool isActive() {
		return isActive_;
	}


	virtual void sleep( uint32 milliseconds );

    virtual int wait();

	virtual int wait( uint32 milliseconds );

	void setCurrentLocale( Locale* locale );
	Locale* getCurrentLocale();
protected:
    static int executionContext();

    static OSStatus taskProc( void *parameter );
    MPQueueID queueID_;
    MPTaskID taskID_;
    ProcessSerialNumber processID_;
	Thread* thread_;
    bool isActive_;
	Locale locale_;
};

};


#endif // _VCF_OSXTHREAD_H__

/**
$Id$
*/
