//PosixCondition.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <sys/time.h>
#include <errno.h>

using namespace VCF;

PosixCondition::PosixCondition( Condition* condition )
{
    MutexPeer *mpeer = condition->getMutex()->getPeer();
    mutex_ = (pthread_mutex_t*)(mpeer->getHandleID());
    pthread_cond_init(&cond_, NULL);
}

PosixCondition::~PosixCondition()
{
    pthread_cond_destroy(&cond_);
}

int PosixCondition::wait()
{
    pthread_cond_wait(&cond_, mutex_);
	pthread_mutex_unlock(mutex_);
    return (int)true;
}

int PosixCondition::wait( uint32 milliseconds )
{
    int result;
    struct timespec timeout;
    struct timeval  now;
    unsigned int sec, usec;

	sec = milliseconds / 1000;
    milliseconds *= 1000;
    usec = milliseconds % 1000000;

    gettimeofday(&now, NULL);
    timeout.tv_sec = now.tv_sec + sec;
    timeout.tv_nsec = now.tv_usec + usec;
    timeout.tv_nsec *= 1000;
    if ( timeout.tv_nsec >= 1000000000 )
    {
        timeout.tv_sec++;
        timeout.tv_nsec -= 1000000000;
    }

    result = pthread_cond_timedwait(&cond_, mutex_, &timeout);
	pthread_mutex_unlock(mutex_);
    if ( result == 0 ) {
		return 1;
	}
    else if ( result == ETIMEDOUT ) {
		return 0;
	}
    else {
		return -1;
	}
}

void PosixCondition::signal()
{
    pthread_cond_signal(&cond_);
	pthread_mutex_unlock(mutex_);
}

void PosixCondition::broadcast()
{
    pthread_cond_broadcast(&cond_);
	pthread_mutex_unlock(mutex_);
}


/**
$Id$
*/
