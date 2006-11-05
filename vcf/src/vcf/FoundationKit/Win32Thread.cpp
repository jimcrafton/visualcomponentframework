//Win32Thread.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"



class CriticalSection  {
public:
	CriticalSection() : isLocked_(false) {
		memset( &cs_, 0, sizeof(cs_) );
		InitializeCriticalSection( &cs_ );
	}

	~CriticalSection() {
		DeleteCriticalSection( &cs_ );
	}

	bool lock() {
		EnterCriticalSection( &cs_ );
		isLocked_ = true;
		return true;
	}

	bool unlock() {
		LeaveCriticalSection( &cs_ );
		isLocked_ = false;
		return true;
	}

	inline bool isLocked() const {
		return isLocked_;
	}

	inline CRITICAL_SECTION* getHandle() {
		return &cs_;
	}
protected:
	CRITICAL_SECTION cs_;
	bool isLocked_;

};



using namespace VCF;



//static CriticalSection threadCollectionCS;

//static std::map<Thread*,Win32Thread*> threadCollection;



Win32Thread::Win32Thread( Thread* thread, bool mainThread ):
	security_(NULL),
	threadID_(0),
	initFlags_(CREATE_SUSPENDED),
	stackSize_(0),
	threadHandle_(0),
	thread_(thread),
	owningProcessID_(0),
	active_(false),
	mainThread_(mainThread)
{

	//threadCollection[thread_] = this;

	if ( mainThread_ ) {
		threadHandle_ = (uintptr)::GetCurrentThread();
		threadID_ = ::GetCurrentThreadId();
		owningProcessID_ = GetCurrentProcessId();
	}
}

Win32Thread::~Win32Thread()
{
	if ( (0 != threadHandle_) && (!mainThread_) )	{
		int err = CloseHandle( (HANDLE)threadHandle_ );
		if ( !err ) {
			err = GetLastError();
		}
	}
	threadHandle_ = 0;

}

bool Win32Thread::start()
{
	if ( 0 == threadHandle_ ) {
		threadHandle_ = _beginthreadex( security_, stackSize_, Win32Thread::threadProc, (void*)this, initFlags_, &threadID_ );

		owningProcessID_ = GetCurrentProcessId();

		thread_->internal_initBeforeRun();

//	Why was this put in here?
//		SetThreadPriority( (HANDLE)threadHandle_, THREAD_PRIORITY_LOWEST );
	}

	/**
	According to MSDN docs on ResumeThread:
	"If the return value is 0, the specified thread was not suspended.
	If the return value is 1, the specified thread was suspended but was
	restarted. If the return value is greater than 1, the specified
	thread is still suspended."
	Thus a value of 1, in this case, since the thread was created
	with the CREATE_SUSPENDED flag, means we have successfully restarted the
	previously suspended thread.
	*/
	return ::ResumeThread( (HANDLE)threadHandle_ ) == 1;
}


void Win32Thread::stop()
{
	WaitForSingleObject( (HANDLE)threadHandle_, INFINITE );
}

unsigned __stdcall Win32Thread::threadProc( void* param )
{
	unsigned result = 0;

	Win32Thread* peer = (Win32Thread*)param;
	if ( NULL != peer->thread_ ){

		peer->active_ = true;

		Thread* thread = peer->thread_;
		bool autoDeleteThread = thread->canAutoDelete();		

		if ( !thread->run() ) {
			result = 1;
		}

		peer->active_ = false;

		if ( !thread->internal_isStopped() ) {
			/**
			if the thread was NOT shutdown with
			stop then we can go ahead
			and clean up, otherwise the
			clean up will happen in the Thread::stop method
			*/
			if ( true == autoDeleteThread )	{

				thread->free();
			}
		}

	}
	return result;
}


void Win32Thread::sleep( unsigned int milliseconds )
{
	::Sleep( milliseconds );
}

int Win32Thread::wait()
{
	DWORD result = ::WaitForSingleObject( (HANDLE)threadHandle_, INFINITE );

	switch ( result ) {

		case WAIT_TIMEOUT : {
			return Waitable::wrTimedOut;
		}
		break;

		case WAIT_OBJECT_0 : case WAIT_ABANDONED : {
			return Waitable::wrWaitFinished;
		}
		break;

		case WAIT_FAILED : {
			return Waitable::wrWaitFailed;
		}
		break;
	}

	return 0;
}

int Win32Thread::wait( uint32 milliseconds )
{
	DWORD result = ::WaitForSingleObject( (HANDLE)threadHandle_, milliseconds );

	switch ( result ) {

		case WAIT_TIMEOUT : {
			return Waitable::wrTimedOut;
		}
		break;

		case WAIT_OBJECT_0 : case WAIT_ABANDONED : {
			return Waitable::wrWaitFinished;
		}
		break;

		case WAIT_FAILED : {
			return Waitable::wrWaitFailed;
		}
		break;
	}

	return 0;
}


/**
$Id$
*/
