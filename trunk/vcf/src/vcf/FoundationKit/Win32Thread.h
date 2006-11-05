#ifndef _VCF_WIN32THREAD_H__
#define _VCF_WIN32THREAD_H__
//Win32Thread.h

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

class Thread;

class Win32Thread : public ThreadPeer  {
public:
	Win32Thread( Thread* thread, bool mainThread );

	virtual ~Win32Thread();

	virtual bool start();

	virtual void stop();

	static unsigned __stdcall threadProc( void* param );

	virtual void sleep( unsigned int milliseconds );

	virtual uint32 getThreadID(){
		return threadID_;
	}

	virtual unsigned int getOwningProcessID()	{
		return owningProcessID_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)threadHandle_;
	}

	virtual bool isActive() {
		return active_;
	}

	virtual int wait();

	virtual int wait( uint32 milliseconds );
private:
	unsigned threadID_;
	unsigned owningProcessID_;
	unsigned initFlags_;
	void* security_;
	unsigned stackSize_;
	uintptr threadHandle_;
	Thread* thread_;
	bool active_;
	bool mainThread_;
};


};


#endif // _VCF_WIN32THREAD_H__

/**
$Id$
*/
