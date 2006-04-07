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


/**
*CVS Log info
 *$Log$
 *Revision 1.6  2006/04/07 02:35:34  ddiego
 *initial checkin of merge from 0.6.9 dev branch.
 *
 *Revision 1.5.2.1  2005/11/11 22:07:40  ddiego
 *small osx updates.
 *
 *Revision 1.5  2005/07/09 23:15:04  ddiego
 *merging in changes from devmain-0-6-7 branch.
 *
 *Revision 1.4  2005/01/08 20:52:47  ddiego
 *fixed some glitches in osx impl.
 *
 *Revision 1.3.4.1  2005/05/08 19:55:32  ddiego
 *osx updates, not yet functional.
 *
 *Revision 1.3  2004/08/08 22:09:33  ddiego
 *final checkin before the 0-6-5 release
 *
 *Revision 1.2  2004/08/07 02:49:14  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
 *This checks in a bunch of changes to the FoundationKit for OSX
 *porting. The thread, mutex, semaphor, condition, and file peers
 *have all been implemented and tested. The file peer could be improved
 *and needs search functionality. The locale peer is only partially
 *complete, but the functions will return values. The unicode transition
 *is also finished and works OK now.
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.3.2.1  2004/04/26 21:58:43  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:42  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.2.6.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXTHREAD_H__


