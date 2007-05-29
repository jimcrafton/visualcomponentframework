//OSXThread.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ThreadException.h"
#include "vcf/FoundationKit/LocalePeer.h"

using namespace VCF;


OSXThread::OSXThread( Thread* thread, bool mainThread ) :
    queueID_(kInvalidID),
    taskID_(kInvalidID),
    thread_(thread),
    isActive_(false),
	locale_("","")
{
    GetCurrentProcess( &processID_ );

    MPLibraryIsLoaded();

    OSStatus err = MPCreateQueue(&queueID_);
    if ( err != noErr ) {
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateQueue failed!") );
    }
}

OSXThread::~OSXThread()
{
    VCF_ASSERT( queueID_ != kInvalidID );

    OSStatus err = MPDeleteQueue(queueID_);

    VCF_ASSERT(err == noErr);
}

bool OSXThread::start()
{
    bool result = true;

    //MPCreateTask starts right away
    OSStatus err = MPCreateTask( &OSXThread::taskProc, this, 0UL, queueID_, NULL,
        NULL, 0UL, &taskID_);
    if (err != noErr) {
        err = MPDeleteQueue(queueID_);
        if ( err != noErr ) {
            throw ThreadException( MAKE_ERROR_MSG_2("MPDeleteQueue failed!") );
        }
        result = false;
    }

	return result;
}

OSStatus OSXThread::taskProc( void *parameter )
{
    OSXThread* thisPtr = (OSXThread*)parameter;

    OSStatus result = noErr;

    if ( NULL != thisPtr->thread_ ) {
        thisPtr->isActive_ = true;

        Thread* thread = thisPtr->thread_;
		bool autoDeleteThread = thread->canAutoDelete();


		if ( !thread->internal_run() ) {
			result = 1;
		}

		thisPtr->isActive_ = false;

		if ( !thread->internal_isStopped() ) {
			/**
			if the thread was NOT shutdown with
			stop then we can go ahead
			and clean up, otherwise the
			clean up will happen in the Thread::stop method
			*/
			if ( true == autoDeleteThread )	{

				thread->free();
			}
		}
    }
    else {
        result = paramErr; // OSXThread has no thread - invalid
    }

    return result;
}

void OSXThread::stop()
{
    wait();//wait forever till we stop running our thread - this is
            //called internally
}

int OSXThread::executionContext()
{
    int result = k_eExecutionContextOther;

    if(MPTaskIsPreemptive(kInvalidID))  {
        result = k_eExecutionContextMPTask;
    }
    else {

        UInt32 taskLevel = TaskLevel();

        if( taskLevel == 0UL)  {
            result = k_eExecutionContextSystemTask;
        }
        else if ( taskLevel & kInDeferredTaskMask ) {
            result = k_eExecutionContextDeferredTask;
        }
    }

    return result;
}

void OSXThread::sleep( uint32 milliseconds )
{

    Duration timeout = kDurationMillisecond * milliseconds;
    AbsoluteTime absTimeout = DurationToAbsolute( timeout );

    if(OSXThread::executionContext() == k_eExecutionContextMPTask) {
        MPDelayUntil( &absTimeout );
    }
    else {
        //uint64_t ullWakeUpTime = force_cast<uint64_t>(*pWakeUpTime);
        uint64 wakeUpTime = timeout;
        setLo32( wakeUpTime, absTimeout.lo );
        setHi32( wakeUpTime, absTimeout.hi );
        AbsoluteTime tmp = UpTime();
        uint64 upTime;
        setLo32( upTime, tmp.lo );
        setHi32( upTime, tmp.hi );

        while( upTime < wakeUpTime) {
            EventRecord event;
            WaitNextEvent(0U, &event, 0UL, NULL);
            tmp = UpTime();
            setLo32( upTime, tmp.lo );
            setHi32( upTime, tmp.hi );
        }
    }
}

int OSXThread::wait()
{
    int result = 0;

	if(OSXThread::executionContext() == k_eExecutionContextMPTask) {
        OSStatus err = MPWaitOnQueue( queueID_, NULL, NULL, NULL, kDurationForever );

        switch ( err ) {
            case kMPTimeoutErr : {
                result =  Waitable::wrTimedOut;
            }
            break;

            case noErr : {
                result =  Waitable::wrWaitFinished;
            }
            break;

            default : {
                result =  Waitable::wrWaitFailed;
            }
            break;
        }
    }
    else   {

        OSStatus lStatus;

        do {
            lStatus = MPWaitOnQueue( queueID_, NULL, NULL, NULL, kDurationImmediate );
            EventRecord event;
            WaitNextEvent(0U, &event, 0UL, NULL);
        } while(lStatus == kMPTimeoutErr );

        switch ( lStatus ) {
            case kMPTimeoutErr : {
                result =  Waitable::wrTimedOut;
            }
            break;

            case noErr : {
                result =  Waitable::wrWaitFinished;
            }
            break;

            default : {
                result =  Waitable::wrWaitFailed;
            }
            break;
        }
    }

	return result;
}

int OSXThread::wait( uint32 milliseconds )
{
    int result = 0;
    Duration timeout = kDurationMillisecond * milliseconds;

    if(OSXThread::executionContext() == k_eExecutionContextMPTask) {
        OSStatus err = MPWaitOnQueue( queueID_, NULL, NULL, NULL, timeout );

        switch ( err ) {
            case kMPTimeoutErr : {
                result =  Waitable::wrTimedOut;
            }
            break;

            case noErr : {
                result =  Waitable::wrWaitFinished;
            }
            break;

            default : {
                result =  Waitable::wrWaitFailed;
            }
            break;
        }
    }
    else   {
        OSStatus lStatus;
        AbsoluteTime expiration = AddDurationToAbsolute( timeout, UpTime());
        uint64 wakeUpTime;
        setLo32( wakeUpTime, expiration.lo );
        setHi32( wakeUpTime, expiration.hi );

        bool expired = false;
        do {
            lStatus = MPWaitOnQueue( queueID_, NULL, NULL, NULL, kDurationImmediate );
            EventRecord event;
            WaitNextEvent(0U, &event, 0UL, NULL);
        } while( lStatus == kMPTimeoutErr && !expired );

        switch ( lStatus ) {
            case kMPTimeoutErr : {
                result =  Waitable::wrTimedOut;
            }
            break;

            case noErr : {
                result =  Waitable::wrWaitFinished;
            }
            break;

            default : {
                result =  Waitable::wrWaitFailed;
            }
            break;
        }
    }

    return result;
}

void OSXThread::setCurrentLocale( Locale* locale )
{
	locale_.getPeer()->setLocale( locale->getLanguageCodeString(), locale->getCountryCodeString(), "" );
}

Locale* OSXThread::getCurrentLocale()
{
	return &locale_;
}


/**
$Id$
*/
