//Win32SemaphorePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Win32SemaphorePeer.cpp: implementation of the Win32SemaphorePeer class.
// Win32SemaphorePeer.h: interface for the Win32SemaphorePeer class.


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Win32SemaphorePeer::Win32SemaphorePeer(long initialCount/* = 1*/, long maxCount /*= 1*/)
{
	hObject_ = ::CreateSemaphore(NULL, initialCount, maxCount,NULL);
	if (hObject_ == NULL)
	{
		// here we should throw something!
	}
}

Win32SemaphorePeer::~Win32SemaphorePeer()
{
	if(hObject_ != NULL)
	{
		::CloseHandle(hObject_);
		hObject_ = NULL;
	}
}

bool Win32SemaphorePeer::unlock()
{
	BOOL flag = ::ReleaseSemaphore(hObject_, 1, NULL);

	return flag == FALSE? false:true;
}

bool Win32SemaphorePeer::lock()
{
	if (::WaitForSingleObject(hObject_, INFINITE) == WAIT_OBJECT_0)
		return true;
	else
		return false;
}

bool Win32SemaphorePeer::lock( uint32 timeoutInMilliseconds )
{
	if (::WaitForSingleObject(hObject_, timeoutInMilliseconds) == WAIT_OBJECT_0)
		return true;
	else
		return false;
}


/**
$Id$
*/
