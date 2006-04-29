//Condition.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

Condition::Condition(Mutex* mutex):
	mutex_(mutex),
	peer_(NULL)
{

	peer_ = SystemToolkit::createConditionPeer( this );

	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Condition::~Condition()
{
	delete peer_;
}

Waitable::WaitResult Condition::wait()
{
	return (Waitable::WaitResult) peer_->wait();
}

Waitable::WaitResult Condition::wait( uint32 milliseconds )
{
	return (Waitable::WaitResult) peer_->wait(milliseconds);
}

void Condition::signal()
{
	peer_->signal();
}

void Condition::broadcast()
{
	peer_->broadcast();
}

OSHandleID Condition::getPeerHandleID()
{
	return peer_->getHandleID();
}


/**
$Id$
*/
