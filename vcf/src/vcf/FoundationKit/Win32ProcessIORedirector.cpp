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
	processID_(0),
	process_(NULL),
	processThreadID_(0),
	readThreadID_(0),
	readThread_(NULL),
	childStdinRdHandle_(NULL),
	childStdinWrHandle_(NULL),
	childStdoutRdHandle_(NULL),
	childStdoutWrHandle_(NULL),
	savedStdinHandle_(NULL),
	savedStdoutHandle_(NULL),
	canContinueReading_(false),
	startInfoPtr_(NULL)
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


	if (processID_ != DWORD(-1))	{
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
	if (processID_ != DWORD(-1))
	{
		HANDLE hProcess = this->childProcess_;//::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID_);
		if (hProcess) {
			DWORD exitCode;
			BOOL bRet =  GetExitCodeProcess(hProcess, &exitCode);//WaitForSingleObject(hProcess,0);// 	// fails when the process is active
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
		process_->OutputReady.fireEvent( &event );

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
		process_->OutputReady.fireEvent( &event );
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


ulong32 Win32ProcessIORedirector::terminate()
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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2006/03/12 22:01:44  ddiego
*doc updates.
*
*Revision 1.3.2.2  2006/02/17 05:23:05  ddiego
*fixed some bugs, and added support for minmax in window resizing, as well as some fancier control over tooltips.
*
*Revision 1.3.2.1  2005/11/28 21:01:06  ddiego
*added wait function to process class. added stubs for linux.
*
*Revision 1.3  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/09 17:21:34  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.7  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.6.2.3  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.6.2.2  2004/01/30 22:08:09  ddiego
*more fixes to the table model and table control
*
*Revision 1.6.2.1  2004/01/20 19:18:28  ddiego
*mod to Process class to allow it to be terminated
*
*Revision 1.6  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.2  2003/10/30 20:12:33  ddiego
*fixed some bugs in the xml parser, added support for cdata and basic
*enities, also fiddled with the redirected IO for processes.
*
*Revision 1.5.2.1  2003/10/29 22:28:45  ddiego
*minor little change in how text widht is calculated (takes into consider
*ation the width of tabs)
*
*Revision 1.5  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.4.2.1  2003/06/24 02:45:26  ddiego
*mods to the Process class and the Win32 peers
*
*Revision 1.4  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.2  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2.2.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.3  2002/09/20 21:28:44  ddiego
*added mods to support building from the VCF Builder and display the
*console build process. Also allows for double clicking in the output
*area and being able to read the output in a generic manner
*
*Revision 1.1.2.2  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.1.2.1  2002/09/17 18:48:36  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


