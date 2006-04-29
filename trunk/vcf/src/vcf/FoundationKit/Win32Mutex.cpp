//Win32Mutex.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32Mutex.h

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;


Win32Mutex::Win32Mutex()
{
	mutexHandle_ =  ::CreateMutex( NULL, 0, NULL );

}

Win32Mutex::~Win32Mutex()
{
	int err = CloseHandle( mutexHandle_ );

}

bool Win32Mutex::lock()
{
	bool result = true;
	int res = ::WaitForSingleObject( mutexHandle_, INFINITE );
	result = (res == WAIT_OBJECT_0);

	return result;
}

bool Win32Mutex::lock( uint32 timeoutInMilliseconds )
{
	bool result = true;
	int res = ::WaitForSingleObject( mutexHandle_, timeoutInMilliseconds );
	result = (res == WAIT_OBJECT_0);

	return result;
}

bool Win32Mutex::unlock()
{
	bool result = true;
	int res = ReleaseMutex( mutexHandle_ );
	result = (res == TRUE);

	return result;
}


/**
$Id$
*/
