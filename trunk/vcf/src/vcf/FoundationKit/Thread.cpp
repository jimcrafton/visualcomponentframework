//Thread.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RuntimeException.h"
#include "vcf/FoundationKit/ThreadManager.h"

using namespace VCF;

Thread* Thread::mainThread = NULL;


Thread::Thread():
	canContinue_(true),
	runnableObject_(NULL),
	peer_(NULL),
	autoDelete_(true),
	autoDeleteRunnable_(false),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, false );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::Thread( Runnable* runnableObject ):
	canContinue_(true),
	runnableObject_(runnableObject),
	peer_(NULL),
	autoDelete_(true),
	autoDeleteRunnable_(true),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, false );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::Thread( Runnable* runnableObject, const bool& autoDelete ):
	canContinue_(true),
	runnableObject_(runnableObject),
	peer_(NULL),
	autoDelete_(autoDelete),
	autoDeleteRunnable_(false),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, false );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::Thread( const bool& autoDelete ):
	canContinue_(true),
	runnableObject_(NULL),
	peer_(NULL),
	autoDelete_(autoDelete),
	autoDeleteRunnable_(false),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, false );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::Thread( Runnable* runnableObject, const bool& autoDeleteRunnable,
			const bool& autoDelete ):
	canContinue_(true),
	runnableObject_(runnableObject),
	peer_(NULL),
	autoDelete_(autoDelete),
	autoDeleteRunnable_(autoDeleteRunnable),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, false );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::Thread( bool mainThread, Runnable* runnableObject, const bool& autoDeleteRunnable,
		const bool& autoDelete ):
	canContinue_(true),
	runnableObject_(runnableObject),
	peer_(NULL),
	autoDelete_(autoDelete),
	autoDeleteRunnable_(autoDeleteRunnable),
	stopped_(false),
	runWithExceptionBlock_(false)
{
	peer_ = SystemToolkit::createThreadPeer( this, mainThread );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Thread::~Thread()
{

	ThreadManager::removeThread( this );

	canContinue_ = false;
	autoDelete_ = false;

	//stop();

	if ( NULL != peer_ ){
		delete peer_;
	}

	peer_ = NULL;

	if ( autoDeleteRunnable_ ) {
		delete runnableObject_;
	}

}

bool Thread::internal_run()
{
	if ( runWithExceptionBlock_ ) {
		return internal_runWithExceptionBlock();
	}
	
	return run();
}

bool Thread::internal_runWithExceptionBlock()
{
	bool result = false;

	try {
		result = run();
	}
	catch ( BasicException& e ) {
		System::println( "VCF Exception caught in thread! Ex: " + e.getMessage() );
		result = false;
	}
	catch ( std::exception& e ) {
		System::println( String("C++ std::exception caught in thread! Ex: ") + e.what() );
		result = false;
	}
	catch (...) {
		System::println( "Unknown exception caught in thread!" );
		result = false;
	}

	return result;
}

bool Thread::run()
{
	bool result = false;
	if ( NULL != runnableObject_ ){
		result = runnableObject_->run();
	}
	else {

	}
	return result;
}


void Thread::stop()
{
	if ( Thread::getMainThread() == this ) {
		return;
	}

	//set this to true immediately
	stopped_ = true;
	/**
	this sets the canContinue_
	member to false which should get picked up in the
	implementers run() method signifying they should exit the
	method, ASAP
	*/
	canContinue_ = false;

	if ( NULL != runnableObject_ ){
		runnableObject_->stop();
	}

	/**
	A blocking call - will wait for the thread to stop
	(or become "unsignaled" in Win32 API terms).
	*/
	peer_->stop();

	/**
	Now clean up here if neccessary
	*/
	if ( true == autoDelete_ )	{
		free();
	}
}

bool Thread::start()
{
	if ( Thread::getMainThread() == this ) {
		return true;
	}

	return peer_->start();
}

void Thread::sleep( uint32 milliseconds )
{
	peer_->sleep( milliseconds );
}

uint32 Thread::getThreadID()
{
	return peer_->getThreadID();
}

uint32 Thread::getOwningProcessID()
{
	return peer_->getOwningProcessID();
}

bool Thread::isActive()
{
	return peer_->isActive();
}

Waitable::WaitResult Thread::wait()
{
	return (Waitable::WaitResult) peer_->wait();
}

Waitable::WaitResult Thread::wait( uint32 milliseconds )
{
	return (Waitable::WaitResult) peer_->wait(milliseconds);
}

OSHandleID Thread::getPeerHandleID()
{
	return peer_->getHandleID();
}

class RunLoop::Creator
{
public:
    static RunLoopPtr::Shared Create( Thread* thread )
    {
        return RunLoopPtr::Shared( new RunLoop( thread ) );
    }
};

RunLoopPtr::Shared Thread::getRunLoop()
{
	if ( NULL == runLoop_ ) {
        if ( ThreadManager::getCurrentThread() == this ) {
            runLoop_ = RunLoop::Creator::Create( this );            
        }
        else {
            throw RuntimeException( "Can not construct a RunLoop." );
        }

	}

	return runLoop_;
}

void Thread::internal_initBeforeRun()
{
	ThreadManager::addThread( this );
}


Thread* Thread::getMainThread()
{
	if ( NULL == Thread::mainThread ) {
		Thread::mainThread = new Thread( true, NULL, false, false );
	}

	return Thread::mainThread;
}


/**
$Id$
*/
