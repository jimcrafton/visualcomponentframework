#ifndef _VCF_LINUXPROCESSIOREDIRECTOR_H__
#define _VCF_LINUXPROCESSIOREDIRECTOR_H__
//LinuxProcessIORedirector.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

//LinuxProcessIORedirector

namespace VCF
{

/**
Win32 (NT or better) implementation of ProcessIORedirectionPeer
original code swiped from:  (c) 2002 Andreas Saurwein - saurwein@uniwares.com
Any mistakes are mine due to the "port" over into the VCF.
*/
class LinuxProcessIORedirector : public Object, public ProcessIORedirectionPeer
{
public:
	LinuxProcessIORedirector();

	virtual ~LinuxProcessIORedirector();

	virtual void addOutputReadyHandler( EventHandler* eventHandler )
	{
		outputReady_.add( eventHandler );
	}

	virtual void removeOutputReadyHandler( EventHandler* eventHandler )
	{
		outputReady_.remove( eventHandler );
	}

	virtual int getProcessID()
	{
		return processID_;
	}

	/**
	*returns the process's main thread ID
	*/
	virtual int getProcessThreadID()
	{
		return processThreadID_;
	}

	/**
	*creates a new process specified by the fully
	*qualified file name in the processName argument.
	*@param String the fully qualified file name of
	*process to start. This must represent an actual
	*executable file
	*@return bool returns true if the process was successfully started
	*otherwise false.
	*/
	virtual bool createProcess( const String& processName, const String& arguments );

	/**
	*returns the fully qualified file name of the process the
	*object represents.
	*/
	virtual String getProcessFileName()
	{
		return commandLine_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)childProcess_;
	}

	virtual void setProcess( ProcessWithRedirectedIO* process )
	{
		process_ = process;
	}

	virtual uint32 terminate();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	//this is the handle to the child process that gets started
	uint32 childProcess_;
	ProcessWithRedirectedIO* process_;
	int processID_;
	int processThreadID_;
	String commandLine_;
	Delegate outputReady_;
};

}


#endif // _VCF_LINUXPROCESSIOREDIRECTOR_H__

/**
$Id$
*/
