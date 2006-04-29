#ifndef _VCF_WIN32PROCESSPEER_H__
#define _VCF_WIN32PROCESSPEER_H__
//Win32ProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32ProcessPeer : public ProcessPeer {

public:
	Win32ProcessPeer();

	virtual ~Win32ProcessPeer();

	virtual int getProcessID();

	virtual int getProcessThreadID();

	virtual bool createProcess( const String& processName, const String& arguments );

	virtual String getProcessFileName();

	virtual OSHandleID getHandleID();

	virtual ulong32 terminate();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	VCF::String processFileName_;
	PROCESS_INFORMATION win32ProcessInfo_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32PROCESSPEER_H__

/**
$Id$
*/
