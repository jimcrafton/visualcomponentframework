//Semaphore.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Semaphore.cpp: implementation of the Semaphore class.

#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

Semaphore::Semaphore(int32 initialCount /*= 1*/, int32 maxCount /*= 1*/):
	peer_( NULL )
{
	peer_ = SystemToolkit::createSemaphorePeer( initialCount, maxCount );

	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Semaphore::~Semaphore()
{
	delete peer_;
}

bool Semaphore::lock()
{
	return peer_->lock();
}


bool Semaphore::lock( uint32 timeoutInMilliseconds )
{
	return peer_->lock(timeoutInMilliseconds);
}

bool Semaphore::unlock()
{
	return peer_->unlock();
}


/**
$Id$
*/
