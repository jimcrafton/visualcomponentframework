//Mutex.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;

Mutex::Mutex()
{
	peer_ = NULL;

	peer_ = SystemToolkit::createMutexPeer( this );

	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Mutex::~Mutex()
{
	delete peer_;
}

bool Mutex::lock()
{
	return peer_->lock();
}


bool Mutex::lock( uint32 timeoutInMilliseconds )
{
	return peer_->lock(timeoutInMilliseconds);
}

bool Mutex::unlock()
{
	return peer_->unlock();
}


/**
$Id$
*/
