//OSXMutexPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ThreadException.h"


using namespace VCF;

OSXMutex::OSXMutex():
    mutex_(NULL)
{
    MPLibraryIsLoaded();

    OSStatus err = MPCreateCriticalRegion( &mutex_ );

    if ( (err != noErr) ||  (mutex_ == kInvalidID) ) {
        throw ThreadException( MAKE_ERROR_MSG_2("MPCreateCriticalRegion failed or returned an invalid critical region ID") );
    }
}

OSXMutex::~OSXMutex()
{
    OSStatus err = MPDeleteCriticalRegion( mutex_ );
    VCF_ASSERT(err == noErr);
}

bool OSXMutex::lock( uint32 timeoutInMilliseconds )
{	
	Duration timeout = kDurationMillisecond * timeoutInMilliseconds;
		
	OSStatus err = MPEnterCriticalRegion( mutex_, timeout );
	return (err == noErr) ? true : false;
}

bool OSXMutex::lock()
{
   OSStatus err = MPEnterCriticalRegion( mutex_, kDurationForever );
   return (err == noErr) ? true : false;
}

bool OSXMutex::unlock()
{
    OSStatus err = MPExitCriticalRegion( mutex_ );

    return (err == noErr) ? true : false;
}


/**
$Id$
*/
