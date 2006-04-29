//Win32ProcessPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"


using namespace VCF;

Win32ProcessPeer::Win32ProcessPeer()
{
	memset( &win32ProcessInfo_, 0, sizeof( win32ProcessInfo_ ) );
	win32ProcessInfo_.dwProcessId = ::GetCurrentProcessId();
	win32ProcessInfo_.dwThreadId = ::GetCurrentThreadId();
	win32ProcessInfo_.hProcess = ::GetCurrentProcess();
	win32ProcessInfo_.hThread = ::GetCurrentThread();

	TCHAR moduleFileName[MAX_PATH];
	memset( moduleFileName, 0, sizeof(moduleFileName) );
	//retreive the current running file name
	::GetModuleFileName( NULL, moduleFileName, MAX_PATH );
	processFileName_ = moduleFileName;
}

Win32ProcessPeer::~Win32ProcessPeer()
{

}

int Win32ProcessPeer::getProcessID()
{
	return win32ProcessInfo_.dwProcessId;
}

int Win32ProcessPeer::getProcessThreadID()
{
	return win32ProcessInfo_.dwThreadId;
}

bool Win32ProcessPeer::createProcess( const String& processName, const String& arguments )
{
	bool result = false;
	processFileName_ = "";

	String commandLine = "";
	BOOL bInheritHandles = FALSE;
	DWORD dwCreationFlags = 0;

	memset( &win32ProcessInfo_, 0, sizeof( win32ProcessInfo_ ) );

	String cmdLine = processName + " " + arguments;



	if ( System::isUnicodeEnabled() ) {
		STARTUPINFOW si;
		memset(&si,0,sizeof(si) );
		si.cb = sizeof(STARTUPINFOW);

		VCFChar* tmp = new VCFChar[cmdLine.size()+1];
		cmdLine.copy( tmp, cmdLine.size() );
		tmp[cmdLine.size()] = 0;

		result = ::CreateProcessW( NULL, tmp, NULL, NULL,
										bInheritHandles, dwCreationFlags,
										NULL, NULL, &si, &win32ProcessInfo_ ) ? true : false;

		delete [] tmp;
	}
	else {
		STARTUPINFOA si;
		memset(&si,0,sizeof(si) );
		si.cb = sizeof(STARTUPINFOA);

		AnsiString tmpCmdLine = cmdLine;
		char* tmp = new char[tmpCmdLine.size()+1];
		tmpCmdLine.copy( tmp, tmpCmdLine.size() );
		tmp[tmpCmdLine.size()] = 0;
		result = ::CreateProcessA( NULL, tmp, NULL, NULL,
										bInheritHandles, dwCreationFlags,
										NULL, NULL, &si, &win32ProcessInfo_ ) ? true : false;

		delete [] tmp;
	}



	if ( true == result ) {
		processFileName_ = processName;
	}
	else {
		int err = GetLastError();
	}

	return result;
}

String Win32ProcessPeer::getProcessFileName()
{
	return processFileName_;
}

OSHandleID Win32ProcessPeer::getHandleID()
{
	return (OSHandleID)win32ProcessInfo_.hProcess;
}

ulong32 Win32ProcessPeer::terminate()
{
	TerminateProcess( win32ProcessInfo_.hProcess, -1 );
	return -1;
}

Waitable::WaitResult Win32ProcessPeer::wait( uint32 milliseconds )
{
	Waitable::WaitResult result;

	DWORD  res = WaitForSingleObject( win32ProcessInfo_.hProcess, milliseconds );
	if ( WAIT_TIMEOUT == res ) {
		result = Waitable::wrTimedOut;
	}
	else if ( WAIT_OBJECT_0 == res ) {
		result = Waitable::wrWaitFinished;
	}

	return result;
}

Waitable::WaitResult Win32ProcessPeer::wait()
{
	Waitable::WaitResult result;
	
	DWORD  res = WaitForSingleObject( win32ProcessInfo_.hProcess, INFINITE );
	if ( WAIT_TIMEOUT == res ) {
		result = Waitable::wrTimedOut;
	}
	else if ( WAIT_OBJECT_0 == res ) {
		result = Waitable::wrWaitFinished;
	}

	return result;
}


/**
$Id$
*/
