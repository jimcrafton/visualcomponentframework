//LinuxSemaphorePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

// LinuxSemaphorePeer.cpp: implementation of the LinuxSemaphorePeer class.
// LinuxSemaphorePeer.h: interface for the LinuxSemaphorePeer class.

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

#include <errno.h>

using namespace VCF;

LinuxSemaphorePeer::LinuxSemaphorePeer( int32 initialCount, int32 maxCount )
{
	sem_init(&semaphore_, 0, initialCount);
}

LinuxSemaphorePeer::~LinuxSemaphorePeer()
{
	sem_destroy(&semaphore_);
}

bool LinuxSemaphorePeer::lock ()
{
	int retCode = sem_wait(&semaphore_);
	return retCode == 0;
}

bool  LinuxSemaphorePeer::lock( uint32 timeoutInMilliseconds )
{
	int retCode = 0;
	uint32 timeout = 0;
	while(timeout < timeoutInMilliseconds) {
		timespec delay;
        delay.tv_sec = 0;
		delay.tv_nsec = 1000000;  // 1 milli sec

		retCode = sem_trywait(&semaphore_); // event semaphore handle
                                            // non blocking call
		if(retCode == 0) {
			break;
		}
		else {
			// check whether somebody else has the mutex
			if (retCode == EPERM ) {
				// sleep for delay time
				nanosleep(&delay, NULL);
				timeout++ ;
			}
			else { 
				// Error, what should we do?
				retCode = -1;
				break;
			}
		}
	}
    return retCode == 0;
}

bool LinuxSemaphorePeer::unlock()
{
	int retCode = sem_post(&semaphore_);
	return retCode == 0;
}


/**
$Id$
*/
