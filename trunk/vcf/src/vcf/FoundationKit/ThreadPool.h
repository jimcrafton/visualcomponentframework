#ifndef _VCF_THREADPOOL_H__
#define _VCF_THREADPOOL_H__


/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_THREADMANAGER_H__
	#include "vcf/FoundationKit/ThreadManager.h"
#endif

#include <deque>


namespace VCF {


class PoolThread;


/**
A simple class for thread pooling. 
This class allows you to specify the number of threads to be 
run in the pool. The pool works by allowing you to post "work"
to it in the form of a valid Runnable instance, and then having
one of the threads run this "work" item when the thread is available
for work. The work item is executed by having the pool thread call
the item's run() method. After the item's run() method is called
the thread deletes the item, and waits for the pool to give a 
new item of work to run.
You can wait for the pool's threads to finish running their work
by using the ThreadPool::wait() method. You can start or stop 
the pool at will.
The pool is meant to be easy to use, for 
example:
\code

class SomeWork : public Runnable {
public:
	virtual bool run() {
		printf( "SomeWork %p was run!\n", this );		
		return true;
	}
	virtual void stop(){}
};

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	
	{
		ThreadPool pool(3);
		pool.start();
		
		pool.postWork( new SomeWork() );
		pool.postWork( new SomeWork() );
		pool.postWork( new SomeWork() );
		pool.postWork( new SomeWork() );
		
		
		pool.wait(  );
		pool.stop();
	}

	FoundationKit::terminate();
	return 0;
}
\endcode

@see Runnable
@see PoolThread
*/
class ThreadPool {
public:
	/**
	Creates a thread pool instance. When called 
	the pool is initialized with the specified number
	of threads
	*/
	ThreadPool( size_t poolSize ): 
		workAvailable_(&cdtnMtx_),
		waitForWorkDone_(&waitForWorkDoneMtx_),
		stopped_(true){

		threads_.resize(poolSize);

		initPool();		
	}

	/**
	Returns the number of threads associated with this pool.
	*/
	uint32 getThreadCount() const {
		return threads_.size();
	}

	/**
	Initializes the pool. The threads for the pool are created 
	here, but \em not started yet.
	@see start
	*/
	void initPool();

	/**
	Starts the pool's threads running. The threads that were 
	created by the call to initPool() are now started here.
	Once all the threads are running, the method exits.
	*/
	void start();

	/**
	Stop the pool from running. This will stop and 
	shutdown all the pool's threads, and delete 
	any remaing work items. This call will block 
	until all of the above has been accomplished.
	*/
	void stop();

	/**
	Waits for all work to be finished. Note that 
	while all the work on the current pool may
	be "done", the pool can still be "running",
	waiting for new work to do. This will block
	indefinitely, until there is no more work
	in the queue left, or until the ThreadPool::stop()
	method is called.
	*/
	void wait();

	/**
	Waits for all work to be finished. Note that 
	while all the work on the current pool may
	be "done", the pool can still be "running",
	waiting for new work to do. This will block
	for the specified number of miiliseconds, 
	until there is no more work in the queue 
	left, or until the ThreadPool::stop() method 
	is called.
	@param uint32 the number of milliseconds to 
	wait before returning from a timeout. Note that
	the function may return sooner than the specified
	number of millseconds if all the work is finished
	by then.
	*/
	void wait( uint32 timeoutInMilliseconds );

	/**
	This method adds the new work item to the
	queue of work items and returns immediately. 
	It temporarily locks the workMtx to protect 
	access to the queue, thus it's a thread safe 
	method to call.	After the item is added, one 
	thread from the	pool is notified of this, 
	so that it can get the next item on the queue 
	and	run it. It's very important to note that
	you must \em always pass items in on the heap, i.e.
	you cannot pass a pointer to an item that has
	been allocated on the stack. For exameple:
	\code
	\\correct way
	Runnable* workItem = new MyRunnable();
	pool.postWork( workItem );

	\\INCORRECT way
	Runnable workItem;
	pool.postWork( &workItem );
	\endcode
	The reason this is important is that the pool will
	manage the lifetime of the Runnable instance and 
	will delete it for you. Passing a pointer to an 
	item allocated on the stack will lead to memory corruption.

	@param Runnable a new isntance of work to perform
	in form of a Runnable instance. The instance's 
	run method will eventually be called when the 
	work is ready to be executed. 
	*/
	void postWork( Runnable* workToDo ) {		
		VCF_ASSERT( NULL != workToDo );

		{
			Lock l(workMtx_);

			//add the runnable work item to the queue
			work_.push_back( workToDo ); 
		}

		//wake up one thread, one thread only Vasily...
		workAvailable_.signal(); 
	}

	/**
	Call this method to wait until new work has arrived.
	This method will block until there is a work item 
	that can be returned. If there is existing work on the
	queue then it will return immediately.
	\par
	This method is called by the PoolThread in a loop.

	\par
	Note that the caller is responsible for deleting the 
	Runnable instance returned by this method.

	@return Runnable indicates a new wortk item that
	can be run. This may be NULL if there is no work 
	to be done because the ThreadPool instance is 
	being shut down as a result of the ThreadPool::stop()
	method being called. 
	@see ThreadPool::stop()
	@see Runnable
	@see PoolThread
	*/
	Runnable* waitForWork() {
		Runnable* result = NULL;
		{
			/**
			lock down our mutex.
			check if anything is available,
			if it is, then get that item, and pop
			it off the queue and return
			If nothing is left (i.e. the queue
			is empty), then notify *all* the 
			threads waiting.
			Check the result at this point,
			if it's NOT NULL, then return,
			otherwise...
			*/

			Lock l(workMtx_);

			if ( stopped_ ) {
				return result;
			}

			if ( !work_.empty() ) {
				result = work_.front();
				work_.pop_front();				
			}

			if ( work_.empty() ) {
				waitForWorkDone_.broadcast();
			}

			if ( NULL != result ) {
				return result;
			}
		}

		/**
		Wait for some work item to arrive!
		*/
		workAvailable_.wait();

		{
			/**
			Ha! Work has arrived!
			Lock down our mutex again.
			Check for work, if we have any
			get the work item ,and pop
			it off the queue. If the 
			queue is empty at this point
			after getting the work item,
			broadcast this to everyone
			waiting on the thread pool
			(by calling ThreadPool::wait()).
			*/
			Lock l(workMtx_);

			if ( !work_.empty() ) {
				result = work_.front();
				work_.pop_front();
			}

			if ( work_.empty() ) {
				waitForWorkDone_.broadcast();
			}
		}
		return result;
	}

	/**
	A vector of threads that are being run
	by the pool. Each thread instance is 
	based on the PoolThread class.
	*/
	std::vector<PoolThread*> threads_;

	/**
	A queue of work to be performed. Each item
	needs to implement the Runnable interface. 
	Any remaining items are destroyed by the pool.
	*/
	std::deque<Runnable*> work_;

	/**
	The mutext to protect access to the work_, 
	and stopped_ variables.
	*/
	Mutex workMtx_;


	/**
	The condition used to indicate whether or not
	there is work available.
	*/
	Condition workAvailable_;
	Mutex cdtnMtx_;

	/**
	The condition used to indicate that all the work
	has been completed/processed.
	*/
	Condition waitForWorkDone_;
	Mutex waitForWorkDoneMtx_;

	/**
	The variable used to tell if the pool is being shut
	down as a result of the ThreadPool::stop() method being
	called. The default value is "false", and calling stop() 
	sets it to "true".
	*/
	bool stopped_;

	private:
		ThreadPool(); //can't be created with specifying the number of threads
		ThreadPool( const ThreadPool& ); //can't be copied
};


/**
This is the specific thread class that the thread pool
uses to create the threads for itself.
*/
class PoolThread : public Thread {
public:
	/**
	This creates a thread for the pool. The constructor
	takes a pointer to the pool the thread belongs to
	as well as the  thread's index in the pool's thread 
	array. Note that the thread is created with auto deletion
	flagged \em off. This means that the thread pool will
	completely control the lifetime of the thread and it's 
	eventual destruction, as opposed to letting this 
	happen automatically.
	*/
	PoolThread( ThreadPool* owningThreadPool, uint32 index ):
		Thread(false),pool_(owningThreadPool),id_(index) {

	}

	virtual ~PoolThread() {
		printf( "Deleting PoolThread %p id# %u\n", this, id_ );
	}

	void cantContinue() {
		canContinue_ = false;
	}

	/**
	This is the thread's execution method. All it does is to
	loop (until it can no longer continue) and wait for
	work items to be come available in the thread pool
	this thread has been assigned to. When a work item is
	returned, if it's non NULL, then the item's run() 
	method is invoked within a try/catch block. After 
	the run() method returns, the item is then deleted.

	@see Thread::canContinue
	@see ThreadPool::waitForWork
	@see Runnable::run
	*/
	virtual bool run() {
		VCF_ASSERT( NULL != pool_ );

		printf( "Starting PoolThread %p id# %u\n", this, id_ );

		while ( canContinue() ) {
			Runnable* work = pool_->waitForWork();

			if ( NULL != work ) {
				if ( canContinue() ) {

					try {
						work->run();
					}
					catch ( BasicException& e1 ) {

					}
					catch ( std::exception& e2 ) {

					}
					catch ( ... ) {

					}

					delete work;
				}
				else {
					delete work;
					break;
				}
			}
		}

		return true;
	}

	ThreadPool* pool_;
	uint32 id_;
};

inline void ThreadPool::initPool() 
{
	for (uint32 i=0;i<threads_.size();i++ ) {
		threads_[i] = new PoolThread(this,i);
	}
}

inline void ThreadPool::start()
{
	stopped_ = false;

	for (uint32 i=0;i<threads_.size();i++ ) {
		threads_[i]->start();
	}	
}

inline void ThreadPool::stop()
{
	printf( "ThreadPool::stop()\n" );

	{
		Lock l(workMtx_);

		stopped_ = true;

		if ( !work_.empty() ) {
			//delete remaining runnables...

			std::deque<Runnable*>::iterator it = work_.begin();
			while ( it != work_.end() ) {
				delete *it;
				++it;
			}
			work_.clear();
		}
	}

	workAvailable_.broadcast();

	for (uint32 j=0;j<threads_.size();j++ ) {
		threads_[j]->cantContinue();
	}
	
	printf( "\tstopping threads...\n" );
	for (uint32 k=0;k<threads_.size();k++ ) {
		Thread* th = threads_[k];
		th->stop();

		delete th;

		threads_[k] = NULL;
	}
	
	waitForWorkDone_.broadcast();
}

inline void ThreadPool::wait() 
{
	{
		Lock l(workMtx_);

		printf( "ThreadPool::wait() work_.size() %u\n", work_.size() );

		if ( stopped_ ) {
			return;
		}

		if ( work_.empty() ) {
			return;
		}
	}

	waitForWorkDone_.wait();
}


inline void ThreadPool::wait( uint32 timeoutInMilliseconds )
{
	{
		Lock l(workMtx_);

		printf( "ThreadPool::wait( %u ) work_.size() %u\n", timeoutInMilliseconds, work_.size() );

		if ( stopped_ ) {
			return;
		}

		if ( work_.empty() ) {
			return;
		}
	}

	waitForWorkDone_.wait(timeoutInMilliseconds);
}

}; //namespace VCF

#endif //_VCF_THREADPOOL_H__

