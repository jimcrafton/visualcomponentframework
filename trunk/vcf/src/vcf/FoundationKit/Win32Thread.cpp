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



Win32Thread::Win32Thread( Thread* thread ):
	security_(NULL),
	threadID_(0),
	initFlags_(CREATE_SUSPENDED),
	stackSize_(0),
	threadHandle_(0),
	thread_(thread),
	owningProcessID_(0),
	active_(false)
{

	//threadCollection[thread_] = this;
}

Win32Thread::~Win32Thread()
{
	if ( 0 != threadHandle_ )	{
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
*CVS Log info
*$Log$
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/05/27 21:17:46  pallindo
*Removed the setting of Win32 thread prioritiy to lowest.
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.16  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.15.2.2  2004/03/11 22:20:00  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.15.2.1  2004/02/19 04:52:35  ddiego
*more progress made with TableControl
*
*Revision 1.15  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.4.3  2003/08/14 01:13:05  ddiego
*added the Thread::pause method back
*
*Revision 1.14.4.2  2003/08/13 21:42:49  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.14.4.1  2003/08/13 02:18:32  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.14  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.13.2.1  2003/03/12 03:12:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.2.1  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.12  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.11.8.1  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.11  2002/06/25 01:25:28  ddiego
*added some fixes and documentation to the Thread class
*also added methods to allow for getting the peer classes on the
*Thread, Semeaphore, and Mutex classes. added peer methods for
*retrieving the handleID for a thread,semaphore, or mutex
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.9.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.9  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


