//OSXConditionPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
Note this code is partially (mostly) based on the condition class
from the Boost Threads library by William Kempf.


Copyright (C) 2001-2003
William E. Kempf

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  William E. Kempf makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.
*/




#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXConditionPeer.h"
#include "vcf/FoundationKit/ThreadException.h"

using namespace VCF;


OSXConditionPeer::OSXConditionPeer( Condition* condition ):
	condition_(condition),
	gate_(NULL),
	queue_(NULL),
	mutex_(NULL),
	gone_(0),
	blocked_(0),
	waiting_(0)
{
    MPLibraryIsLoaded();


    OSStatus err = MPCreateSemaphore( 1, 1, &gate_ );
    if ( (err != noErr) || (kInvalidID == gate_) ) {
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateSemaphore failed or returned an invalid gate_ semaphore id") );
    }


    err = MPCreateSemaphore( OSXConditionPeer::MaxQueue, 0, &queue_ );
    if ( (err != noErr) || (kInvalidID == queue_) ) {
        if ( kInvalidID != gate_ ) {
            MPDeleteSemaphore( gate_ );
        }
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateSemaphore failed or returned an invalid queue_ semaphore id") );
    }


    err = MPCreateCriticalRegion( &mutex_ );
    if ( (err != noErr) || (kInvalidID == mutex_) ) {
        if ( kInvalidID != gate_ ) {
            MPDeleteSemaphore( gate_ );
        }

        if ( kInvalidID != queue_ ) {
            MPDeleteSemaphore( queue_ );
        }
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateCriticalRegion failed or returned an invalid mutex_ ") );
    }
}

OSXConditionPeer::~OSXConditionPeer()
{
    OSStatus err = MPDeleteSemaphore( gate_ );
    VCF_ASSERT2( err == noErr, "MPDeleteSemaphore failed for gate_" );

    err = MPDeleteSemaphore( queue_ );
    VCF_ASSERT2( err == noErr, "MPDeleteSemaphore failed for queue_" );


    err = MPDeleteCriticalRegion( mutex_ );
    VCF_ASSERT2( err == noErr, "MPDeleteCriticalRegion failed for mutex_" );

}

int OSXConditionPeer::wait()
{
	int result = 0;

    OSStatus err = MPWaitOnSemaphore( gate_, kDurationForever );
    VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");


	++blocked_;


    err = MPSignalSemaphore( gate_ );
    VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");



	Mutex* conditionMutex = condition_->getMutex();

	conditionMutex->unlock();


    err = MPWaitOnSemaphore( queue_, kDurationForever );

	switch ( err ) {
		case kMPTimeoutErr : {
			result = Waitable::wrTimedOut;
		}
		break;

		case noErr : {
			result = Waitable::wrWaitFinished;
		}
		break;

		default : {
			result = Waitable::wrWaitFailed;
		}
		break;
	}


	unsigned was_waiting=0;
	unsigned was_gone=0;

	err = MPEnterCriticalRegion( mutex_, kDurationForever );
	VCF_ASSERT2(err == noErr,"MPEnterCriticalRegion( mutex_ ) failed");


	was_waiting = waiting_;
	was_gone = gone_;

	if ( was_waiting != 0 ) {
		waiting_ --;

		if ( waiting_ == 0 ) {
			if (blocked_ != 0) {
                err = MPSignalSemaphore( gate_ );
                VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");

				was_waiting = 0;
			}
			else if (gone_ != 0) {
				gone_ = 0;
			}
		}
	}
	else {
		gone_ ++;
		if ( gone_ == OSXConditionPeer::MaxQueue ) {
			// timeout occured, normalize the gone_ count
			// this may occur if many calls to wait with a timeout are made and
			// no call to notify_* is made
            err = MPWaitOnSemaphore( gate_, kDurationForever );
            VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");


			blocked_ -= gone_;
			err = MPSignalSemaphore( gate_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");

			gone_ = 0;
		}
	}

    err = MPExitCriticalRegion( mutex_ );
    VCF_ASSERT2(err == noErr,"MPExitCriticalRegion( mutex_ ) failed");


	if (was_waiting == 1)	{
		for (/**/ ; was_gone; --was_gone)	{
			// better now than spurious later
            err = MPWaitOnSemaphore( queue_, kDurationForever );
            VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( queue_ ) failed");

		}

        err = MPSignalSemaphore( gate_ );
        VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");
	}


	conditionMutex->lock();

	return result;
}

int OSXConditionPeer::wait( uint32 milliseconds )
{
	Mutex* conditionMutex = condition_->getMutex();

    OSStatus err = MPWaitOnSemaphore( gate_, kDurationForever );
    VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");

	++blocked_;

    err = MPSignalSemaphore( gate_ );
    VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");


	conditionMutex->unlock();

	int result = 0;

	Duration timeout = kDurationMillisecond * milliseconds;

    err = MPWaitOnSemaphore( queue_, timeout );

	switch ( err ) {
		case kMPTimeoutErr : {
			result = Waitable::wrTimedOut;
		}
		break;

		case noErr : {
			result = Waitable::wrWaitFinished;
		}
		break;

		default : {
			result = Waitable::wrWaitFailed;
		}
		break;
	}


	unsigned was_waiting=0;
	unsigned was_gone=0;

    err = MPEnterCriticalRegion( mutex_, kDurationForever );
	VCF_ASSERT2(err == noErr,"MPEnterCriticalRegion( mutex_ ) failed");


	was_waiting = waiting_;
	was_gone = gone_;
	if (was_waiting != 0) {
		if ( Waitable::wrTimedOut == result ) { // timeout
			if (blocked_ != 0) {
				--blocked_;
			}
			else {
				++gone_; // count spurious wakeups
			}
		}
		waiting_ --;
		if ( 0 == waiting_ ) {
			if (blocked_ != 0) {

                err = MPSignalSemaphore( gate_ );
                VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");

				was_waiting = 0;
			}
			else if (gone_ != 0) {
				gone_ = 0;
			}
		}
	}
	else {
		gone_ ++;
		if ( gone_ == OSXConditionPeer::MaxQueue ) {
			// timeout occured, normalize the gone_ count
			// this may occur if many calls to wait with a timeout are made and
			// no call to notify_* is made
            err = MPWaitOnSemaphore( gate_, kDurationForever );
            VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");

			blocked_ -= gone_;

            err = MPSignalSemaphore( gate_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");

			gone_ = 0;
		}
	}

    err = MPExitCriticalRegion( mutex_ );
    VCF_ASSERT2(err == noErr,"MPExitCriticalRegion( mutex_ ) failed");


	if (was_waiting == 1) {
		for (/**/ ; was_gone; --was_gone)	{
			// better now than spurious later
            err = MPWaitOnSemaphore( queue_, kDurationForever );
            VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( queue_ ) failed");


		}

        err = MPSignalSemaphore( gate_ );
        VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");
	}


	conditionMutex->lock();



	return result;
}

void OSXConditionPeer::signal()
{
	unsigned signals = 0;

    OSStatus err = MPEnterCriticalRegion( mutex_, kDurationForever );
	VCF_ASSERT2(err == noErr,"MPEnterCriticalRegion( mutex_ ) failed");


	if ( waiting_ != 0 ) 	{
		// the gate_ is already closed

		if (blocked_ == 0) {
            err = MPExitCriticalRegion( mutex_ );
            VCF_ASSERT2(err == noErr,"MPEnterCriticalRegion( mutex_ ) failed");

			return;
		}

		++waiting_;
		--blocked_;
		signals = 1;
	}
	else {
        err = MPWaitOnSemaphore( gate_, kDurationForever );
        VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");

		if ( blocked_ > gone_ ) {
			if (gone_ != 0)	{
				blocked_ -= gone_;
				gone_ = 0;
			}
			signals = waiting_ = 1;
			--blocked_;
		}
		else {
            err = MPSignalSemaphore( gate_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");
		}
	}


    err = MPExitCriticalRegion( mutex_ );
	VCF_ASSERT2(err == noErr,"MPExitCriticalRegion( mutex_ ) failed");

	if ( signals ) {
        for ( int sigCount=0;sigCount<signals;sigCount++ ) {
            err = MPSignalSemaphore( queue_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( queue_ ) failed");
        }
	}
}

void OSXConditionPeer::broadcast()
{
	unsigned signals = 0;

	int res = 0;

    OSStatus err = MPEnterCriticalRegion( mutex_, kDurationForever );
	VCF_ASSERT2(err == noErr,"MPEnterCriticalRegion( mutex_ ) failed");


	if (waiting_ != 0) {
		// the gate_ is already closed
		if (blocked_ == 0) {
            err = MPExitCriticalRegion( mutex_ );
            VCF_ASSERT2(err == noErr,"MPExitCriticalRegion( mutex_ ) failed");

			return;
		}

		waiting_ += (signals = blocked_);
		blocked_ = 0;
	}
	else {
        err = MPWaitOnSemaphore( gate_, kDurationForever );
        VCF_ASSERT2(err == noErr,"MPWaitOnSemaphore( gate_ ) failed");

		if (blocked_ > gone_)	{
			if (gone_ != 0) {
				blocked_ -= gone_;
				gone_ = 0;
			}
			signals = waiting_ = blocked_;
			blocked_ = 0;
		}
		else {
            err = MPSignalSemaphore( gate_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( gate_ ) failed");
		}
	}

    err = MPExitCriticalRegion( mutex_ );
    VCF_ASSERT2(err == noErr,"MPExitCriticalRegion( mutex_ ) failed");



	if ( signals ) {
        for ( int sigCount=0;sigCount<signals;sigCount++ ) {
            err = MPSignalSemaphore( queue_ );
            VCF_ASSERT2( err == noErr, "MPSignalSemaphore( queue_ ) failed");
        }
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
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

*/


