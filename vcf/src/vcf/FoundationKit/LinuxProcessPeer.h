#ifndef _VCF_LINUXPROCESSPEER_H__
#define _VCF_LINUXPROCESSPEER_H__ 
//LinuxProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxProcessPeer : public ProcessPeer
{

public:
	LinuxProcessPeer();

	virtual ~LinuxProcessPeer();

	virtual int getProcessID();

	virtual int getProcessThreadID();

	virtual bool createProcess( const String& processName, const String& arguments );

	virtual String getProcessFileName();

	virtual OSHandleID getHandleID();

	virtual uint32 terminate();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();

protected:
	pid_t  processHandle_;
	String processFileName_;
};

} //end of namespace VCF


#endif // _VCF_LINUXPROCESSPEER_H__

/**
$Id$
*/
