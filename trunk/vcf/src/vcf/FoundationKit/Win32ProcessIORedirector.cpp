//Win32ProcessIORedirector.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ProcessWithRedirectedIO.h"
#include "vcf/FoundationKit/Win32ProcessIORedirector.h"


using namespace VCF;


Win32ProcessIORedirector::Win32ProcessIORedirector():
	childProcess_(NULL),
	process_(NULL),
	processID_(0),
	processThreadID_(0),
	readThreadID_(0),
	readThread_(NULL),
	childStdinRdHandle_(NULL),
	childStdinWrHandle_(NULL),
	childStdoutRdHandle_(NULL),
	childStdoutWrHandle_(NULL),
	savedStdinHandle_(NULL),
	savedStdoutHandle_(NULL),
	startInfoPtr_(NULL),
    canContinueReading_(false)
{
	memset( &processInfo_, 0, sizeof(processInfo_) );



	if ( System::isUnicodeEnabled() ) {
		startInfoPtr_ = new STARTUPINFOW;
		memset( startInfoPtr_, 0, sizeof(STARTUPINFOW) );
		((STARTUPINFOW*)startInfoPtr_)->cb = sizeof(STARTUPINFOW);
	}
	else {
		startInfoPtr_ = new STARTUPINFOA;
		memset( startInfoPtr_, 0, sizeof(STARTUPINFOA) );
		((STARTUPINFOA*)startInfoPtr_)->cb = sizeof(STARTUPINFOA);
	}


}

Win32ProcessIORedirector::~Win32ProcessIORedirector()
{
	canContinueReading_ = false;
	WaitForSingleObject( readThread_, INFINITE );
	CloseHandle( readThread_ );

	readThread_ = NULL;


	if ((DWORD)processID_ != DWORD(-1))	{
		DWORD dwExitCode;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID_);

		// if the process handle is INVALID_HANDLEVALUE or
		// the process handle is valid but ExitCode is set
		if (!hProcess || (hProcess && GetExitCodeProcess(hProcess, &dwExitCode))) {
			processID_ = DWORD(-1);
		}
		else
			if ( !CloseHandle(hProcess)) {
				throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(hProcess)"));
			}
	}

	if ( System::isUnicodeEnabled() ) {
		delete ((STARTUPINFOW*)startInfoPtr_);
	}
	else {
		delete ((STARTUPINFOA*)startInfoPtr_);
	}
}


bool Win32ProcessIORedirector::testProcess()
{
	if ((DWORD)processID_ != DWORD(-1))
	{
		HANDLE hProcess = this->childProcess_;//::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID_);
		if (hProcess) {
			DWORD exitCode;
			GetExitCodeProcess(hProcess, &exitCode);//WaitForSingleObject(hProcess,0);// 	// fails when the process is active
			//if  (!CloseHandle(hProcess)) {
			//	throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(hProcess)"));
		//	}
			return (exitCode == STILL_ACTIVE) ? true : false;
		}
	}
	return false;
}

void Win32ProcessIORedirector::readPipe()
{
	DWORD bytesRead = 0;
	const int BUFSIZE = 256;
	char readBuffer[BUFSIZE+1];

	DWORD bytesLeftToRead = 1;

	while ( bytesLeftToRead > 0 ) {
		if (!ReadFile(childStdoutRdHandle_, readBuffer, BUFSIZE, &bytesRead, NULL) || bytesRead == 0)  {

			if (::GetLastError() == ERROR_BROKEN_PIPE)
				break;
			else
				VCF_ASSERT2(false, "ReadFile failed");
		}

		readBuffer[bytesRead/sizeof(char)] = 0;

		//notify folks of an OutputReady event
		String outputData = readBuffer;
		OutputReadyEvent event( process_, outputData );
		process_->OutputReady( &event );

		Sleep(100);
		int err = PeekNamedPipe( childStdoutRdHandle_, NULL, 0, NULL, &bytesLeftToRead, NULL);


		if ( !err || bytesLeftToRead == 0 ) {
			if( !testProcess() ) {
				//break;
				bytesLeftToRead = 0;
			}
			else {

				bytesLeftToRead = 1;
			}
		}
	}

	if ( bytesLeftToRead > 0 ) {
		//do one last read
		if (!ReadFile(childStdoutRdHandle_, readBuffer, BUFSIZE, &bytesRead, NULL) || bytesRead == 0)  {
			if (::GetLastError() != ERROR_BROKEN_PIPE) {
				//??????
			}
		}

		readBuffer[bytesRead/sizeof(char)] = 0;

		//notify folks of an OutputReady event
		String outputData = readBuffer;
		OutputReadyEvent event( process_, outputData );
		process_->OutputReady( &event );
	}

	if ( !CloseHandle(childStdinRdHandle_) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(pThis->hChildStdinRd_)"));
	}
	if ( !CloseHandle(childStdoutWrHandle_)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(pThis->childStdoutWrHandle_)"));
	}

	if ( !CloseHandle(childStdinWrHandle_)){
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(pThis->hChildStdinWr_)"));
	}

	if ( !CloseHandle(childStdoutRdHandle_)){
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(pThis->childStdoutRdHandle_)"));
	}
}

UINT __stdcall Win32ProcessIORedirector::ReadPipeThreadProc(LPVOID pParam)
{
	UINT result = 0;

	Win32ProcessIORedirector* thisPtr = (Win32ProcessIORedirector*)pParam;
	thisPtr->readPipe();

	return result;
}

bool Win32ProcessIORedirector::createProcess( const String& processName, const String& arguments )
{
	bool result = false;

	canContinueReading_ = true;
	commandLine_ = processName + " " + arguments;

	if ( NULL != readThread_ ) {

		::WaitForSingleObject( readThread_, INFINITE );
		::CloseHandle( readThread_ );

		if ( !::CloseHandle(childStdinRdHandle_) ){
			throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(childStdinRdHandle_) failed"));
		}
		if ( !::CloseHandle(childStdoutWrHandle_) ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(childStdoutWrHandle_) failed"));
		}
		if ( !::CloseHandle(childStdinWrHandle_) ){
			throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(childStdinWrHandle_) failed"));
		}
		if ( !::CloseHandle(childStdoutRdHandle_) ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(childStdoutRdHandle_) failed"));
		}

		readThread_ = NULL;
	}

	HANDLE hChildStdoutRdTmp, hChildStdinWrTmp;
	SECURITY_ATTRIBUTES saAttr;
	memset( &saAttr, 0, sizeof(saAttr) );
	BOOL bSuccess;

	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	//from Andreas notes
	// The steps for redirecting child process's STDOUT:
	//	 1. Save current STDOUT, to be restored later.
	//	 2. Create anonymous pipe to be STDOUT for child process.
	//	 3. Set STDOUT of the parent process to be write handle to
	//		the pipe, so it is inherited by the child process.
	//	 4. Create a noninheritable duplicate of the read handle and
	//		close the inheritable read handle.

	// Save the handle to the current STDOUT.
	savedStdoutHandle_ = ::GetStdHandle(STD_OUTPUT_HANDLE);

	// Create a pipe for the child process's STDOUT.
	if (!::CreatePipe(&hChildStdoutRdTmp, &childStdoutWrHandle_, &saAttr, 0))	{
		throw RuntimeException( MAKE_ERROR_MSG_2("Stdout pipe creation failed") );
	}

	// Set a write handle to the pipe to be STDOUT.
	if (!::SetStdHandle(STD_OUTPUT_HANDLE, childStdoutWrHandle_)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Redirecting STDOUT failed"));
	}

	// Create noninheritable read handle and close the inheritable read handle.
	bSuccess = ::DuplicateHandle(::GetCurrentProcess(), hChildStdoutRdTmp,
									::GetCurrentProcess(), &childStdoutRdHandle_,
									0, FALSE, DUPLICATE_SAME_ACCESS);
	if (!bSuccess) {
		throw RuntimeException( MAKE_ERROR_MSG_2("DuplicateHandle failed") ) ;
	}

	if (! ::CloseHandle(hChildStdoutRdTmp)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(hChildStdoutRdTmp)") );
	}

	// The steps for redirecting child process's STDIN:
	//	 1.  Save current STDIN, to be restored later.
	//	 2.  Create anonymous pipe to be STDIN for child process.
	//	 3.  Set STDIN of the parent to be the read handle to the
	//		 pipe, so it is inherited by the child process.
	//	 4.  Create a noninheritable duplicate of the write handle,
	//		 and close the inheritable write handle.

	// Save the handle to the current STDIN.
	savedStdinHandle_ = GetStdHandle(STD_INPUT_HANDLE);

	// Create a pipe for the child process's STDIN.
	if (!::CreatePipe(&childStdinRdHandle_, &hChildStdinWrTmp, &saAttr, 0)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Stdin pipe creation failed") );
	}

	// Set a read handle to the pipe to be STDIN.
	if (!::SetStdHandle(STD_INPUT_HANDLE, childStdinRdHandle_)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Redirecting Stdin failed") );
	}

	// Duplicate the write handle to the pipe so it is not inherited.
	bSuccess = ::DuplicateHandle(::GetCurrentProcess(), hChildStdinWrTmp,
									::GetCurrentProcess(), &childStdinWrHandle_,
									0, FALSE,// not inherited
									DUPLICATE_SAME_ACCESS);
	if (!bSuccess)  {
		throw RuntimeException( MAKE_ERROR_MSG_2("DuplicateHandle failed") );
	}

	if (!::CloseHandle(hChildStdinWrTmp)) {
		throw RuntimeException( MAKE_ERROR_MSG_2("CloseHandle(hChildStdinWrTmp)") );
	}


	//now start the child process - this will start a new cmd with the
	//the cmd line sent to it
	childProcess_ = NULL;


	String tmp = System::getEnvironmentVariable( L"ComSpec" );

	if (tmp.empty()) {
		result = false;
	}
	else {
		String shellCmdLine = tmp;
		shellCmdLine += L" /A /C ";
		shellCmdLine += commandLine_;



		BOOL retVal = FALSE;

		if ( System::isUnicodeEnabled() ) {
			// Set up members of STARTUPINFO structure.
			((STARTUPINFOW*)startInfoPtr_)->dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
			((STARTUPINFOW*)startInfoPtr_)->wShowWindow = SW_HIDE;
			((STARTUPINFOW*)startInfoPtr_)->hStdInput = childStdinRdHandle_;
			((STARTUPINFOW*)startInfoPtr_)->hStdOutput = childStdoutWrHandle_;
			((STARTUPINFOW*)startInfoPtr_)->hStdError = childStdoutWrHandle_;

			VCFChar tmp[4096];
			memset(tmp,0,sizeof(tmp));
			shellCmdLine.copy( tmp, minVal<int>( 4095,shellCmdLine.size() ) );


			retVal = CreateProcessW(NULL,
									tmp, 	   // applicatin name
									NULL, 		  // process security attributes
									NULL, 		  // primary thread security attributes
									TRUE, 		  // handles are inherited
									CREATE_NEW_CONSOLE, // creation flags
									NULL, 		  // use parent's environment
									NULL, 		  // use parent's current directory
									(STARTUPINFOW*)startInfoPtr_,  // STARTUPINFO pointer
									&processInfo_);  // receives PROCESS_INFORMATION
		}
		else {
			((STARTUPINFOA*)startInfoPtr_)->dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
			((STARTUPINFOA*)startInfoPtr_)->wShowWindow = SW_HIDE;
			((STARTUPINFOA*)startInfoPtr_)->hStdInput = childStdinRdHandle_;
			((STARTUPINFOA*)startInfoPtr_)->hStdOutput = childStdoutWrHandle_;
			((STARTUPINFOA*)startInfoPtr_)->hStdError = childStdoutWrHandle_;

			char tmp[4096];
			memset(tmp,0,sizeof(tmp));
			AnsiString tmp2 = shellCmdLine;

			tmp2.copy( tmp, minVal<int>( 4095,tmp2.size() ) );


			retVal = CreateProcessA(NULL,
									tmp, 	   // applicatin name
									NULL, 		  // process security attributes
									NULL, 		  // primary thread security attributes
									TRUE, 		  // handles are inherited
									CREATE_NEW_CONSOLE, // creation flags
									NULL, 		  // use parent's environment
									NULL, 		  // use parent's current directory
									(STARTUPINFOA*)startInfoPtr_,  // STARTUPINFO pointer
									&processInfo_);  // receives PROCESS_INFORMATION

		}

		if (retVal){
			processID_ = processInfo_.dwProcessId;
			childProcess_ = processInfo_.hProcess;
			processThreadID_ = processInfo_.dwThreadId;
		}
		else {
			processID_ = GetLastError();
			DebugBreak();
		}


		readThread_ = (HANDLE)_beginthreadex( NULL,
											0,
											Win32ProcessIORedirector::ReadPipeThreadProc,
											(void*)this,
											CREATE_SUSPENDED,
											&readThreadID_ );


		::SetThreadPriority( readThread_, THREAD_PRIORITY_BELOW_NORMAL );
		//read thread is started
		::ResumeThread( readThread_ );

		if (!readThread_) {
			throw RuntimeException( MAKE_ERROR_MSG_2("Cannot start read-redirect thread!") );
		}




		WaitForSingleObject( childProcess_, INFINITE );

		//readPipe();


		CloseHandle( childProcess_ );



		// After process creation, restore the saved STDIN and STDOUT.
		if (!SetStdHandle(STD_INPUT_HANDLE, savedStdinHandle_ ))
			throw RuntimeException( MAKE_ERROR_MSG_2("Re-redirecting Stdin failed") );

		if (!SetStdHandle(STD_OUTPUT_HANDLE, savedStdoutHandle_))
			throw RuntimeException( MAKE_ERROR_MSG_2("Re-redirecting Stdout failed") );

		canContinueReading_ = false;

		::WaitForSingleObject( readThread_, INFINITE );
		::CloseHandle( readThread_ );
		readThread_ = NULL;
		childProcess_ = NULL;
		processID_ = 0;



		result = retVal ? true : false;
	}

	canContinueReading_ = false;

	return result;
}


uint32 Win32ProcessIORedirector::terminate()
{
	TerminateProcess( processInfo_.hProcess, -1 );
	return -1;
}

Waitable::WaitResult Win32ProcessIORedirector::wait( uint32 milliseconds )
{
	Waitable::WaitResult result(Waitable::wrWaitFailed);

	DWORD  res = WaitForSingleObject( processInfo_.hProcess, milliseconds );
	if ( WAIT_TIMEOUT == res ) {
		result = Waitable::wrTimedOut;
	}
	else if ( WAIT_OBJECT_0 == res ) {
		result = Waitable::wrWaitFinished;
	}

	return result;
}

Waitable::WaitResult Win32ProcessIORedirector::wait()
{
	Waitable::WaitResult result(Waitable::wrWaitFailed);

	DWORD  res = WaitForSingleObject( processInfo_.hProcess, INFINITE );
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
