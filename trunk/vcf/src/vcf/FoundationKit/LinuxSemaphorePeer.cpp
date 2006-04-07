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

LinuxSemaphorePeer::LinuxSemaphorePeer( long initialCount, long maxCount )
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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3.2.1  2005/11/10 00:04:08  obirsoy
*changes required for gcc under Linux.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.14.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*/


