#ifndef _VCF_WIN32PROCESSIOREDIRECTOR_H__
#define _VCF_WIN32PROCESSIOREDIRECTOR_H__
//Win32ProcessIORedirector.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//Win32ProcessIORedirector


namespace VCF {



/**
Win32 (NT or better) implementation of ProcessIORedirectionPeer
original code swiped from:  (c) 2002 Andreas Saurwein - saurwein@uniwares.com
Any mistakes are mine due to the "port" over into the VCF.
*/
class Win32ProcessIORedirector  : public Object, public ProcessIORedirectionPeer {
public:
	Win32ProcessIORedirector();

	virtual ~Win32ProcessIORedirector();	

	virtual int getProcessID() {
		return processID_;
	}

	/**
	*returns the process's main thread ID
	*/
	virtual int getProcessThreadID() {
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
	virtual String getProcessFileName() {
		return commandLine_;
	}

	virtual OSHandleID getHandleID() {
		return (OSHandleID)childProcess_;
	}

	virtual void setProcess( ProcessWithRedirectedIO* process ) {
		process_ = process;
	}

	virtual ulong32 terminate();

	virtual Waitable::WaitResult wait( uint32 milliseconds );

	virtual Waitable::WaitResult wait();
protected:
	//this is the handle to the child process that gets started
	HANDLE childProcess_;
	ProcessWithRedirectedIO* process_;
	int processID_;
	int processThreadID_;
	UINT readThreadID_;
	String commandLine_;
	HANDLE readThread_;

	HANDLE	childStdinRdHandle_;
	HANDLE	childStdinWrHandle_;
	HANDLE	childStdoutRdHandle_;
	HANDLE	childStdoutWrHandle_;
	HANDLE	savedStdinHandle_;
	HANDLE	savedStdoutHandle_;
	PROCESS_INFORMATION processInfo_;

	void*	startInfoPtr_;

	bool canContinueReading_;

	void readPipe();

	static UINT __stdcall ReadPipeThreadProc(LPVOID pParam);
	bool testProcess();
};


};


#endif // _VCF_WIN32PROCESSIOREDIRECTOR_H__

/**
$Id$
*/
