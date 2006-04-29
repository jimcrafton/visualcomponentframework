//PosixMutex.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

PosixMutex::PosixMutex()
{
    pthread_mutex_init(&mutex_, NULL);
}

PosixMutex::~PosixMutex()
{
    pthread_mutex_destroy(&mutex_);
}

bool PosixMutex::lock()
{
    if ( pthread_mutex_lock(&mutex_) == 0 ) {
		return true;
	}
    return false;
}

bool PosixMutex::lock( uint32 timeoutInMilliseconds )
{
    timespec ts;
    ts.tv_sec = timeoutInMilliseconds / 1000;
    ts.tv_nsec = (timeoutInMilliseconds * 1000) - (ts.tv_sec*1000*1000)  ;
    if ( pthread_mutex_timedlock(&mutex_, &ts) == 0 ) {
		return true;
	}
    return false;
}


bool PosixMutex::unlock()
{
    if ( pthread_mutex_unlock(&mutex_) == 0 ) {
		return true;
	}
    return false;
}


/**
$Id$
*/
