//PosixThread.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LinuxPeer.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

using namespace VCF;
using namespace VCFLinux;

void* PosixThread::threadProc( void* arg )
{
    void* result = NULL;
    PosixThread* peer = (PosixThread*)arg;

    if( NULL != peer->thread_ )
    {
		peer->threadSuspendMutex_.lock();
			peer->isActive_ = true;
			bool autoDeleteThread = peer->thread_->canAutoDelete(); 
		peer->threadSuspendMutex_.unlock();

        if(!peer->thread_->run())
        {
            result = NULL;
        }

		peer->threadSuspendMutex_.lock();
			peer->isActive_ = false;
		peer->threadSuspendCond_.signal();
        

        if(!peer->thread_->internal_isStopped())
        {
            /**
			if the thread was NOT shutdown with
			stop then we can go ahead
			and clean up, otherwise the
			clean up will happen in the Thread::stop method
			*/
			if ( true == autoDeleteThread )	{
				peer->thread_->free();
			}
        }

		if(!autoDeleteThread) {
			pthread_detach(peer->threadID_);
		}
    }

    return result;
}

PosixThread::PosixThread( Thread* thread, bool mainThread ) :
	threadID_(0),
    processID_(getpid()),
	thread_(thread),
    isActive_(false),
	threadSuspendCond_(&threadSuspendMutex_)
{
	if( mainThread ) {
		threadID_ = pthread_self();
		processID_ = getpid();
	}
}

PosixThread::~PosixThread()
{
    stop();
}

bool PosixThread::start()
{
    if ( isActive_ ) {
        return true;
    }

	threadSuspendMutex_.lock();

    int status = pthread_create(&threadID_, NULL, &PosixThread::threadProc, this);

	processID_ = getpid();
	thread_->internal_initBeforeRun();

	threadSuspendMutex_.unlock();

    if ( status == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

void PosixThread::stop()
{
	threadSuspendMutex_.lock();
    if ( isActive_ ) {
		threadSuspendMutex_.unlock();
		void* thread_result = NULL;
        pthread_join(threadID_, &thread_result);
        isActive_ = false;
    }
	else {
		threadSuspendMutex_.unlock();
	}
}

void PosixThread::sleep( uint32 milliseconds )
{
    if ( !isActive_ ) {
		return;
	}

	timespec delay;
	delay.tv_sec = milliseconds / 1000;
	milliseconds *= 1000;
	delay.tv_nsec = 1000* (milliseconds % 1000000);
	if ( delay.tv_nsec >= 1000000000 )
	{
		delay.tv_sec++;
		delay.tv_nsec -= 1000000000;
	}

	if(pthread_equal(threadID_, pthread_self()) != 0) {
		nanosleep(&delay, NULL);
	}
	else {
		threadSuspendCond_.wait(milliseconds);
	}
}

int PosixThread::wait()
{
	threadSuspendMutex_.lock();

    if ( isActive_ && !inThreadProc() ) {
		threadSuspendMutex_.unlock();
        pthread_join(threadID_, NULL);
        isActive_ = false;
    }
	else {
		threadSuspendMutex_.unlock();
	}
	return 0;
}

int PosixThread::wait( uint32 milliseconds )
{
	threadSuspendMutex_.lock();
	if(isActive_) {
		threadSuspendCond_.wait(milliseconds);
	}
	else {
		threadSuspendMutex_.unlock();
	}
	return 0;
}


/**
$Id$
*/
