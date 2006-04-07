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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
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
*Revision 1.4  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.6.1  2004/03/30 01:48:26  ddiego
*updated linux code
*
*Revision 1.3  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/06 00:22:04  catwallader
*Added thread methods: isActive(), isDetached(), join(), exit(), yield() and detach().  Fleshed out PosixThread::stop().
*
*Revision 1.1.2.1  2003/01/30 22:32:22  catwallader
*Added the PosixThread class.  Modified Makefiles and toolkit files to accomodate it.
*
*/


