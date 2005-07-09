#ifndef _VCF_THREAD_H__
#define _VCF_THREAD_H__
//Thread.h

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

class ThreadPeer;
class RunLoop;


/**
*The Thread class represents a thread of execution in a process.
*A Thread object can automatically delete itself if neccessary.
*A Thread can either be derived from and the run() method overridden,
*or a separate class that derives from Runnable may be passed into the
*Thread's constructor and this class's run() method will get called.
*For example:<br>
*Method 1) deriving a new thread class and over riding the run() method
*<pre>
class MyThread : public VCF::Thread {
public:
	MyThread() : VCF::Thread() {};

	virtual bool run() {
		//do stuff here, for example a loop
		//be a good citizen and check with the
		//canContinue() method to see if we should
		//still be executing
		while ( true == canContinue() ) {
			//do some work

			if ( somethingWentWrong ) {
				return false;
			}
		}
		return true;
	}
};

usage:

int main() {
    FoundationKit::init();

	MyThread* thread = new MyThread();
	thread->start(); //start the thread

	//program does stuff here

	//stop the thread cause we are shutting down
	thread->stop();

	//delete the thread since it is NOT set to auto delete
	//if we had passed in true in the Thread constructor then
	//we would not need this part
	thread->free();

	FoundationKit::terminate();
	return 0;
}
*</pre>
*<br>
*Method 2) deriving a new class from Runnable and pass it to a Thread you create
*<pre>
class MyMultiThreadedClass : public VCF::Object, public VCF::Runnable  {
public:
	MyMultiThreadedClass() {};

	//other methods here...

	//override the run() method of Runnable - MUST do this
	//for your class to be a concrete class
	virtual bool run() {
		//do stuff here, for example a loop

		//you must supply you own check methods to
		//determine if you can keep looping,
		//assuming that is what you need to do

		return true;
	}
};

usage:

int main() {
    FoundationKit::init();

	MyMultiThreadedClass multiThreader;

	Thread* thread = new Thread( &multiThreader, true ); //will auto delete

	thread->start(); //start the thread

	//program does stuff here

	//stop the thread cause we are shutting down
	thread->stop();

	//thread will auto delete itself

	FoundationKit::terminate();
	return 0;
}
*</pre>
*/
class FOUNDATIONKIT_API Thread : public Object, public Runnable, public Waitable {
public:
	Thread();

	Thread( const bool& autoDelete );

	/**
	*creates a thread with the attached runnableObject (if appropriate)
	*@param Runnable the runnableObject the thread will use. By default this
	*is NULL, which means the Thread's run method has been overridden in
	*a derived class.
	*@param bool indicates whose responsibility it is to clean up after the
	*thread is stopped. If autoDelete is true then the thread instance will
	*clean up for itself, if autoDelete is false, then it is the caller's
	*responsibility to clean up
	*/
	Thread( Runnable* runnableObject, const bool& autoDelete );

	/**
	Creates a thread with a runnable object, and allows the thread to
	automatically delete the runnable if appropriate.
	*/
	Thread( Runnable* runnableObject, const bool& autoDeleteRunnable,
			const bool& autoDelete );

	Thread( Runnable* runnableObject );


	virtual ~Thread();

	/**
	*run method for the thread. Overide this method to provide additional functionality.
	*If runnableObject_ is non NULL then it's run() will be called in here.
	*/
	virtual bool run();


	/**
	*gracefully stops the thread and shuts it down, releasing
	*any OS resources associated with the thread.
	*Once a thread is stopped that thread instance may NOT be
	*started again. If the thread is set of automatic deletion
	*this is where it will happen
	*/
	virtual void stop();

	/**
	*Starts (or resumes) a thread running.
	*/
	bool start();

	/**
	*causes the thread the thread to sleep for the specified number of
	*milliseconds
	*@param uint32 - the number of milliseconds to sleep
	*/
	void sleep( unsigned int milliseconds );

	/**
	*can the thread continue to execute ?
	*@return bool true if the thread can safely continue to execute, otherwise false
	*indicating it should stop executing.
	*/
	bool canContinue(){
		return canContinue_;
	}

	/**
	*can the thread auto delete itself ?
	*@return bool true if the thread will auto delete itself. Determined by the parameters
	*passed into the thread's constructor
	*/
	bool canAutoDelete(){
		return autoDelete_;
	}

	/**
	*returns the thread associated with this thread of execution
	*/
	uint32 getThreadID();

	/**
	*returns the process ID that this thread is part of
	*/
	uint32 getOwningProcessID();

	ThreadPeer* getPeer() {
		return peer_;
	}

    /*Returns TRUE if thread is running, FALSE if not
	*/
    bool isActive();


	virtual WaitResult wait();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual OSHandleID getPeerHandleID();

	RunLoop* getRunLoop();


	static Thread* getMainThread();


	/**
	for thread peer's usage only -
	called to see if the thread is
	being shutdown via the stop()
	method.
	*/
    bool internal_isStopped() {
		return stopped_;
	}
	
	/**
	Called by the thread peer implementation. Initializes the thread
	with the thread manager.
	*/
	void internal_initBeforeRun();

protected:

	bool canContinue_;
	Runnable* runnableObject_;
	ThreadPeer* peer_;
	bool autoDelete_;
	bool autoDeleteRunnable_;
	bool stopped_;
	RunLoop* runLoop_;

	static Thread* mainThread;
private:
	//this is used ONLY to create a wrapper around the main thread
	Thread( bool mainThread, Runnable* runnableObject, const bool& autoDeleteRunnable,
		const bool& autoDelete );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.4.1  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.16.2.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.16  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.15.2.2  2004/03/11 22:19:59  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.15.2.1  2004/02/19 04:52:35  ddiego
*more progress made with TableControl
*
*Revision 1.15  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.6  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.14.4.5  2003/08/23 02:01:28  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.14.4.4  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.14.4.3  2003/08/14 01:13:33  ddiego
*added the Thread::pause method back
*
*Revision 1.14.4.2  2003/08/13 21:43:01  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.14.4.1  2003/08/13 02:18:31  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.14  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:11:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.12.3  2003/02/19 00:12:45  catwallader
*Fixed comments and added some more to Thread.h.
*
*Revision 1.12.12.2  2003/02/06 00:22:04  catwallader
*Added thread methods: isActive(), isDetached(), join(), exit(), yield() and detach().  Fleshed out PosixThread::stop().
*
*Revision 1.12.12.1  2003/02/04 19:16:34  ddiego
*commented out the ThreadLooper class declaration, as this caused link
*prblems in VC6
*
*Revision 1.12  2002/06/25 01:25:28  ddiego
*added some fixes and documentation to the Thread class
*also added methods to allow for getting the peer classes on the
*Thread, Semeaphore, and Mutex classes. added peer methods for
*retrieving the handleID for a thread,semaphore, or mutex
*
*Revision 1.11  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_THREAD_H__


