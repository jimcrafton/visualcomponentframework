#ifndef _VCF_OSXPROCESSPEER_H__
#define _VCF_OSXPROCESSPEER_H__
//OSXProcessPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**
This is the handle class that OSXProcessPeer::getHandleID() returns.
You should check isUnixProcess to determine how to access the information in this struct.
If isUnixProcess is true, then launchBlock is just zero'ed out and is meaningless and
pid will be set to the process id. If isUnixProcess is false then launchBlock
will have valid information in it, and pid will be set to the unix process id 
of the launchBlock.launchProcessSN
*/
class OSXProcessHandle {
public:
	bool isUnixProcess;
	LaunchParamBlockRec launchBlock;
	int pid;	
};

class OSXProcessPeer : public ProcessPeer {

public:
	OSXProcessPeer();

	virtual ~OSXProcessPeer();

	virtual int getProcessID() {
		return processHandle_.pid;
	}

	virtual int getProcessThreadID();

	virtual bool createProcess( const String& processName, const String& arguments );

	virtual String getProcessFileName();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)&processHandle_;
	}

    virtual ulong32 terminate();
	
	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	OSXProcessHandle processHandle_;
	VCF::String processFileName_;
	bool processTerminated_;
	static OSStatus osxProcessTerminated( EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void * inUserData );
};

}; //end of namespace VCF


#endif // _VCF_OSXPROCESSPEER_H__

/**
$Id$
*/
