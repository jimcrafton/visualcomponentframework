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

#include <vcf/FoundationKit/RunLoopFwd.h>

namespace VCF
{

class ThreadPeer;


/**
\class Thread Thread.h "vcf/FoundationKit/Thread.h"
The Thread class represents a thread of execution in a process.
A Thread object can automatically delete itself if neccessary.
A Thread can either be derived from and the run() method overridden,
or a separate class that derives from Runnable may be passed into the
Thread's constructor and this class's run() method will get called.


For example:
\li Method 1) deriving a new thread class and over riding the run() method
\code
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
\endcode

\li Method 2) deriving a new class from Runnable and pass it to a Thread you create
\code
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
\endcode
*/
class FOUNDATIONKIT_API Thread : public Object, public Runnable, public Waitable {
public:
	Thread();

	Thread( const bool& autoDelete );

	/**
	creates a thread with the attached runnableObject (if appropriate)
	@param Runnable the runnableObject the thread will use. By default this
	is NULL, which means the Thread's run method has been overridden in
	a derived class.
	@param bool indicates whose responsibility it is to clean up after the
	thread is stopped. If autoDelete is true then the thread instance will
	clean up for itself, if autoDelete is false, then it is the caller's
	responsibility to clean up
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
	run method for the thread. Overide this method to provide additional functionality.
	If runnableObject_ is non NULL then it's run() will be called in here.
	*/
	virtual bool run();


	/**
	gracefully stops the thread and shuts it down, releasing
	any OS resources associated with the thread.
	Once a thread is stopped that thread instance may NOT be
	started again. If the thread is set for automatic deletion
	this is where it will happen. 
	This method \em will block until the thread is stopped.
	*/
	virtual void stop();

	/**
	Starts (or resumes) a thread running. If you want to protect
	the thread's execution within a try/catch block, make sure to 
	call setRunsWithExceptionHandler(true), prior to calling this
	method.

	@see setRunsWithExceptionHandler
	*/
	bool start();

	/**
	causes the thread the thread to sleep for the specified number of
	milliseconds
	@param uint32 - the number of milliseconds to sleep
	*/
	void sleep( uint32 milliseconds );

	/**
	can the thread continue to execute ?
	@return bool true if the thread can safely continue to execute, otherwise false
	indicating it should stop executing.
	*/
	bool canContinue(){
		return canContinue_;
	}

	/**
	can the thread auto delete itself ?
	@return bool true if the thread will auto delete itself. Determined by the parameters
	passed into the thread's constructor
	*/
	bool canAutoDelete(){
		return autoDelete_;
	}

	/**
	returns the thread associated with this thread of execution
	*/
	uint32 getThreadID();

	/**
	returns the process ID that this thread is part of
	*/
	uint32 getOwningProcessID();

	ThreadPeer* getPeer() {
		return peer_;
	}

    /**
	Returns TRUE if thread is running, FALSE if not.
	*/
    bool isActive();


	virtual WaitResult wait();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual OSHandleID getPeerHandleID();

	RunLoopPtr::Shared getRunLoop();

	/**
	Returns whether or not the thread's run() method is wrapped with an 
	try/catch block.
	@return bool True if the thread's run() method is wrapped in an 
	try/catch block. False if it's not.
	*/
	bool getRunsWithExceptionHandler() {
		return runWithExceptionBlock_;
	}

	/**
	Sets the variable that determines whether or not the thread's run() method 
	is wrapped in an try/catch block. If this is set to true, then the run() method
	will have a try/catch block around it, which will catch \em all exceptions thrown,
	preventing exceptions from propagating outside the threads execution. If
	this is set to false, the default value, then no try/catch block is used 
	when the thread's run() method is invoked. This means that exceptions thrown 
	will cause problems if not caught within the execution of the thread.

	Note that this only makes sense to call \em before the thread's start() 
	method is called. Once start() is called, the thread's run() will be executed 
	and calling this method at that point will have no effect.
	*/
	void setRunsWithExceptionHandler( bool val ) {
		runWithExceptionBlock_ = val;
	}

	/**
	Returns the main or primary thread for a program. There
	is always at \em least one thread (what you might 
	say is the "primary" thread of execution) that an
	executable program will create when it is started up. 
	This function will return that primary thread. You don't 
	create it, and you don't destroy it, that's handled 
	by the framework.
	*/
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

	bool internal_run();
protected:

	bool canContinue_;
	Runnable* runnableObject_;
	ThreadPeer* peer_;
	bool autoDelete_;
	bool autoDeleteRunnable_;
	bool stopped_;
	RunLoopPtr::Shared runLoop_;
	bool runWithExceptionBlock_;

	static Thread* mainThread;
private:
	//this is used ONLY to create a wrapper around the main thread
	Thread( bool mainThread, Runnable* runnableObject, const bool& autoDeleteRunnable,
		const bool& autoDelete );


	bool internal_runWithExceptionBlock();
};


};


#endif // _VCF_THREAD_H__

/**
$Id$
*/
