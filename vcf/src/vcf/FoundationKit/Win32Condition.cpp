//Win32Condition.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
Note this code is partially (mostly) based on the condition class
from the Boost Threads library by William Kempf.


Copyright (C) 2001-2003
William E. Kempf

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  William E. Kempf makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.
*/




#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/Win32Condition.h"

using namespace VCF;


Win32Condition::Win32Condition( Condition* condition ):
	condition_(condition),
	gate_(NULL),
	queue_(NULL),
	mutex_(NULL),
	gone_(0),
	blocked_(0),
	waiting_(0)
{
	gate_ = CreateSemaphore( 0, 1, 1, 0 );

	queue_ = CreateSemaphore( 0, 0, Win32Condition::MaxQueue, 0 );

	mutex_ = ::CreateMutex( NULL, 0, NULL );

	if ( (NULL == mutex_) || (NULL == gate_) || (NULL == queue_) )  {
		int res = 0;
		if ( mutex_ )	{
			res = CloseHandle( mutex_ );
			VCF_ASSERT2( res ? true : false, "CloseHandle failed for mutex_!" );
		}

		if ( gate_ )	{
			res = CloseHandle( gate_ );
			VCF_ASSERT2( res ? true : false, "CloseHandle failed for gate_!" );
		}

		if ( queue_ ) {
			res = CloseHandle( queue_ );
			VCF_ASSERT2( res ? true : false, "CloseHandle failed for gate_!" );
		}

		throw RuntimeException( MAKE_ERROR_MSG_2("Failed to allocate system resources for Condition.") );
	}
}

Win32Condition::~Win32Condition()
{
	int res = 0;

	if ( mutex_ )	{
		res = CloseHandle( mutex_ );
		VCF_ASSERT2( res ? true : false, "CloseHandle failed for mutex_!" );
	}

	if ( gate_ )	{
		res = CloseHandle( gate_ );
		VCF_ASSERT2( res ? true : false, "CloseHandle failed for gate_!" );
	}

	if ( queue_ ) {
		res = CloseHandle( queue_ );
		VCF_ASSERT2( res ? true : false, "CloseHandle failed for gate_!" );
	}
}

int Win32Condition::wait()
{
	int result = 0;

	int res = 0;
	res = WaitForSingleObject(gate_, INFINITE);
	VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( gate_ ) failed");

	++blocked_;
	res = ReleaseSemaphore(gate_, 1, 0);
	VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( gate_ ) failed");

	Mutex* conditionMutex = condition_->getMutex();

	conditionMutex->unlock();


	res = WaitForSingleObject( queue_, INFINITE );

	switch ( res ) {
		case WAIT_TIMEOUT : {
			result = Waitable::wrTimedOut;
		}
		break;

		case WAIT_OBJECT_0 : case WAIT_ABANDONED : {
			result = Waitable::wrWaitFinished;
		}
		break;

		case WAIT_FAILED : {
			result = Waitable::wrWaitFailed;
		}
		break;
	}


	unsigned was_waiting=0;
	unsigned was_gone=0;

	res = WaitForSingleObject( mutex_, INFINITE );
	VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( mutex_ ) failed");


	was_waiting = waiting_;
	was_gone = gone_;

	if ( was_waiting != 0 ) {
		waiting_ --;

		if ( waiting_ == 0 ) {
			if (blocked_ != 0) {
				res = ReleaseSemaphore( gate_, 1, 0 ); // open gate_
				VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( gate_ ) failed");

				was_waiting = 0;
			}
			else if (gone_ != 0) {
				gone_ = 0;
			}
		}
	}
	else {
		gone_ ++;
		if ( gone_ == Win32Condition::MaxQueue ) {
			// timeout occured, normalize the gone_ count
			// this may occur if many calls to wait with a timeout are made and
			// no call to notify_* is made
			res = WaitForSingleObject( gate_, INFINITE );
			VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( gate_ ) failed");

			blocked_ -= gone_;
			res = ReleaseSemaphore(gate_, 1, 0);
			VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( gate_ ) failed");

			gone_ = 0;
		}
	}

	res = ReleaseMutex( mutex_ );
	VCF_ASSERT2( res ? true : false,"ReleaseMutex( mutex_ ) failed");


	if (was_waiting == 1)	{
		for (/**/ ; was_gone; --was_gone)	{
			// better now than spurious later
			res = WaitForSingleObject( queue_, INFINITE );
			VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( queue_ ) failed");
		}
		res = ReleaseSemaphore(gate_, 1, 0);
		VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( gate_ ) failed");
	}


	conditionMutex->lock();

	return result;
}

int Win32Condition::wait( uint32 milliseconds )
{
	Mutex* conditionMutex = condition_->getMutex();

	int res = 0;
	res = WaitForSingleObject(gate_, INFINITE);
	VCF_ASSERT2( res == WAIT_OBJECT_0, "WaitForSingleObject( gate_ ) failed" );

	++blocked_;
	res = ReleaseSemaphore(gate_, 1, 0);
	VCF_ASSERT2( res ? true : false, "ReleaseSemaphore( gate_ ) failed" );



	conditionMutex->unlock();



	int result = 0;



	res = WaitForSingleObject(queue_,milliseconds);
	switch ( res ) {
		case WAIT_TIMEOUT : {
			result = Waitable::wrTimedOut;
		}
		break;

		case WAIT_OBJECT_0 : case WAIT_ABANDONED : {
			result = Waitable::wrWaitFinished;
		}
		break;

		case WAIT_FAILED : {
			result = Waitable::wrWaitFailed;
		}
		break;
	}


	unsigned was_waiting=0;
	unsigned was_gone=0;

	res = WaitForSingleObject( mutex_, INFINITE );
	VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( mutex_ ) failed");



	was_waiting = waiting_;
	was_gone = gone_;
	if (was_waiting != 0) {
		if ( Waitable::wrTimedOut == result ) { // timeout
			if (blocked_ != 0) {
				--blocked_;
			}
			else {
				++gone_; // count spurious wakeups
			}
		}
		waiting_ --;
		if ( 0 == waiting_ ) {
			if (blocked_ != 0) {
				res = ReleaseSemaphore( gate_, 1, 0 ); // open gate_
				VCF_ASSERT2( res ? true : false, "ReleaseSemaphore( gate_ ) failed" );

				was_waiting = 0;
			}
			else if (gone_ != 0) {
				gone_ = 0;
			}
		}
	}
	else {
		gone_ ++;
		if ( gone_ == Win32Condition::MaxQueue ) {
			// timeout occured, normalize the gone_ count
			// this may occur if many calls to wait with a timeout are made and
			// no call to notify_* is made
			res = WaitForSingleObject(gate_, INFINITE);
			VCF_ASSERT2( res == WAIT_OBJECT_0, "WaitForSingleObject( gate_ ) failed" );

			blocked_ -= gone_;

			res = ReleaseSemaphore(gate_, 1, 0);
			VCF_ASSERT2( res ? true : false, "ReleaseSemaphore( gate_ ) failed" );

			gone_ = 0;
		}
	}


	res = ReleaseMutex( mutex_ );
	VCF_ASSERT2( res ? true : false,"ReleaseMutex( mutex_ ) failed");



	if (was_waiting == 1) {
		for (/**/ ; was_gone; --was_gone)	{
			// better now than spurious later
			res = WaitForSingleObject(queue_, INFINITE);

			VCF_ASSERT2( res == WAIT_OBJECT_0, "WaitForSingleObject( queue_ ) failed" );
		}
		res = ReleaseSemaphore(gate_, 1, 0);
		VCF_ASSERT2( res ? true : false, "ReleaseSemaphore( gate_ ) failed" );
	}




	conditionMutex->lock();



	return result;
}

void Win32Condition::signal()
{
	unsigned signals = 0;

	int res = 0;

	res = WaitForSingleObject( mutex_, INFINITE );
	VCF_ASSERT2( res == WAIT_OBJECT_0, "WaitForSingleObject(mutex_) failed!");


	if ( waiting_ != 0 ) 	{
		// the gate_ is already closed

		if (blocked_ == 0) {
			res = ReleaseMutex( mutex_ );
			VCF_ASSERT2( res ? true : false, "ReleaseMutex(mutex_) failed!");

			return;
		}

		++waiting_;
		--blocked_;
		signals = 1;
	}
	else {
		res = WaitForSingleObject( gate_, INFINITE );

		VCF_ASSERT2( res == WAIT_OBJECT_0, "gate_ wait failed!");

		if ( blocked_ > gone_ ) {
			if (gone_ != 0)	{
				blocked_ -= gone_;
				gone_ = 0;
			}
			signals = waiting_ = 1;
			--blocked_;
		}
		else {
			res = ReleaseSemaphore( gate_, 1, 0 );
			VCF_ASSERT2( res ? true : false, "ReleaseSemaphore(gate_)  failed!");
		}
	}

	res = ReleaseMutex( mutex_ );
	VCF_ASSERT2( res ? true : false, "ReleaseMutex(mutex_)  failed!");


	if ( signals ) {
		res = ReleaseSemaphore( queue_, signals, 0 );
		VCF_ASSERT2( res ? true : false, "ReleaseSemaphore(queue_)  failed!");
	}
}

void Win32Condition::broadcast()
{
	unsigned signals = 0;

	int res = 0;

	res = WaitForSingleObject( mutex_, INFINITE );
	VCF_ASSERT2( res == WAIT_OBJECT_0, "WaitForSingleObject(queue_)  failed!");



	if (waiting_ != 0) {
		// the gate_ is already closed
		if (blocked_ == 0) {
			res = ReleaseMutex( mutex_ );
			VCF_ASSERT2( res ? true : false, "ReleaseMutex(mutex_)  failed!");

			return;
		}

		waiting_ += (signals = blocked_);
		blocked_ = 0;
	}
	else {
		res = WaitForSingleObject( gate_, INFINITE );
		VCF_ASSERT2(res == WAIT_OBJECT_0,"WaitForSingleObject( gate_ ) failed");

		if (blocked_ > gone_)	{
			if (gone_ != 0) {
				blocked_ -= gone_;
				gone_ = 0;
			}
			signals = waiting_ = blocked_;
			blocked_ = 0;
		}
		else {
			res = ReleaseSemaphore(gate_, 1, 0);
			VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( gate_ ) failed");
		}
	}

	res = ReleaseMutex( mutex_ );
	VCF_ASSERT2( res ? true : false, "ReleaseMutex(mutex_)  failed!");


	if (signals) {
		res = ReleaseSemaphore( queue_, signals, 0 );
		VCF_ASSERT2( res ? true : false,"ReleaseSemaphore( queue_ ) failed");
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.1  2004/06/05 01:18:41  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.4  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.1.2.3  2004/03/18 22:28:58  marcelloptr
*just spacing formatting
*
*Revision 1.1.2.2  2004/03/12 04:05:30  ddiego
*minor documentation for condition stuff
*
*Revision 1.1.2.1  2004/03/11 22:20:00  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*/


