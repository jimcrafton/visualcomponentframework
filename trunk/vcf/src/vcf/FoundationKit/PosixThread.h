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
    PosixThread( Thread* thread );

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

	virtual uint32 getHandleID() {
		return threadID_;
	}

    /* Returns process that created thread.  Is this useful? */
	virtual uint32 getOwningProcessID() {
		return processID_;
	}


    /* Returns TRUE if called in Thread::run(), FALSE if not */
    int inThreadProc() {
		return pthread_self() == threadID_;
	}

    /* Not implemented yet */
	virtual void sleep( uint32 milliseconds );

	virtual int wait();

	virtual int wait( uint32 milliseconds );

	virtual bool isActive() {
		return isActive_;
	}
	
protected:


	pthread_t threadID_;
    pid_t processID_;
	Thread* thread_;
    bool isActive_;
    bool isDetached_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.6.1  2004/03/30 01:48:16  ddiego
*updated linux code
*
*Revision 1.3  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.6  2003/02/19 00:12:33  catwallader
*Fixed comments and added some more to Thread.h.
*
*Revision 1.1.2.5  2003/02/18 20:03:30  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.1.2.4  2003/02/12 19:35:54  catwallader
*Added PosixMutex class.
*
*Revision 1.1.2.3  2003/02/08 18:49:06  ddiego
*added some fixes to handle multiple lines of text. Also made a minor change to
*PosixThread so everything links OK.
*
*Revision 1.1.2.2  2003/02/06 00:22:04  catwallader
*Added thread methods: isActive(), isDetached(), join(), exit(), yield() and detach().  Fleshed out PosixThread::stop().
*
*Revision 1.1.2.1  2003/01/30 22:32:20  catwallader
*Added the PosixThread class.  Modified Makefiles and toolkit files to accomodate it.
*
*/


#endif // _VCF_POSIXTHREAD_H__


