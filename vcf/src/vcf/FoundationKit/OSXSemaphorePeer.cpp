//OSXSemaphorePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ThreadException.h"

using namespace VCF;



OSXSemaphore::OSXSemaphore( long initialCount, long maxCount ):
    semaphoreID_(NULL)
{
    MPLibraryIsLoaded();

    OSStatus err = MPCreateSemaphore( maxCount, initialCount, &semaphoreID_ );

    if ( (err != noErr) || (kInvalidID == semaphoreID_) ) {
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateSemaphore failed or returned an invalid semaphore id") );
    }
}

OSXSemaphore::~OSXSemaphore()
{
    OSStatus err = MPDeleteSemaphore( semaphoreID_ );
    VCF_ASSERT2( err == noErr, "MPDeleteSemaphore failed" );
}

bool OSXSemaphore::lock( uint32 timeoutInMilliseconds )
{
	Duration timeout = kDurationMillisecond * timeoutInMilliseconds;
    
	OSStatus err = MPWaitOnSemaphore( semaphoreID_, timeout );
    return (err == noErr) ? true : false;
}

bool OSXSemaphore::lock()
{
    OSStatus err = MPWaitOnSemaphore( semaphoreID_, kDurationForever );
    return (err == noErr) ? true : false;
}


bool OSXSemaphore::unlock()
{
    OSStatus err = MPSignalSemaphore( semaphoreID_ );
    return (err == noErr) ? true : false;
}


/**
$Id$
*/
