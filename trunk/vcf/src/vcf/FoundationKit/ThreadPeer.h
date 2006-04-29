#ifndef _VCF_THREADPEER_H__
#define _VCF_THREADPEER_H__
//ThreadPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

/**
\class ThreadPeer ThreadPeer.h "vcf/FoundationKit/ThreadPeer.h"
*@interface ThreadPeer
*Basic Thread interface to wrap native thread OS calls.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API ThreadPeer
{
public:
	virtual ~ThreadPeer() {}

	/**
	*Starts (or resumes) a thread running.
	*/
	virtual bool start() = 0;

	/**
	*gracefully stops the thread and shuts it down, releasing
	*any OS resources associated with the thread
	*/
	virtual void stop() = 0;

	/**
	*causes the thread the thread to sleep for the specified number of
	*milliseconds
	*@param uint32 - the number of milliseconds to sleep
	*/
	virtual void sleep( uint32 milliseconds ) = 0;

	/**
	*returns the thread associated with this thread of execution
	*/
	virtual uint32 getThreadID() = 0;

	/**
	*returns the process ID that this thread is part of
	*/
	virtual uint32 getOwningProcessID() = 0;

	/**
	*returns a handle ID for the thread. It's use and signifigance
	*are platform specific. On Win32 systems this is the HANDLE
	*returned by the CreateThread/_beginthreadex() calls
	*/
	virtual OSHandleID getHandleID() = 0;

	virtual bool isActive() = 0;

	virtual int wait() = 0;

	virtual int wait( uint32 milliseconds ) = 0;
};



};


#endif // _VCF_THREADPEER_H__

/**
$Id$
*/
