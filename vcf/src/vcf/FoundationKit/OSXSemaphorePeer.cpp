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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
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


