//Win32RunLoopPeer.cpp
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/Win32RunLoopPeer.h"


#define VCF_POSTMSGTORUNLOOP		WM_APP + 919

using namespace VCF;

Win32RunLoopPeer::Win32RunLoopPeer( RunLoop* runLoop ):
    runLoop_(runLoop)
{
}

void Win32RunLoopPeer::run()
{

}

void Win32RunLoopPeer::stop()
{

}

void Win32RunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer )
{

}

void Win32RunLoopPeer::addSource( RunLoopSourcePtr::Shared source )
{

}


/*Win32RunLoopPeer::Win32RunLoopPeer( RunLoop* runLoop ):
	runLoop_(runLoop)
{

}

Win32RunLoopPeer::~Win32RunLoopPeer()
{
	removeAll();
}

void Win32RunLoopPeer::run( const String& mode, const DateTime* duration )
{
	/**
	A better way to handle this:
	Use GetMessage(), and is duration is non-null, then add a timer to 
	fire after the requested elapsed amount of time. When this happens
	quit the loop
	MSG msg;
	memset(&msg,0,sizeof(msg));
	
	DateTime current = DateTime::now();

	DateTime end;
	if ( NULL != duration ) {
		end = *duration;
	}
	else {
		end = current;
	}

	while ( true ) {
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			if ( !handleMessageAndContinue( msg ) ) {	
				runLoop_->internal_cancelled( mode );
				break;
			}
		}


		if ( current > end ) {
			runLoop_->internal_cancelled( mode );
			break;
		}

		
		runLoop_->internal_executeOnce( mode );

		handleTimers( mode );

		current = DateTime::now();
		if ( NULL == duration ) {
			end = current;
		}

		Sleep(1);
	}
}

bool Win32RunLoopPeer::handleMessageAndContinue( MSG& msg )
{	
	switch ( msg.message ) {
		case WM_QUIT : {
			return false;
		}
		break;

		case VCF_POSTMSGTORUNLOOP : {
			PostedEvent* pe = (PostedEvent*)msg.lParam;
			
			runLoop_->internal_processReceivedEvent( pe );

			delete pe;
		}
		break;		
	}
	
	TranslateMessage(&msg); 

	DispatchMessage(&msg); 

	return true;
}

void Win32RunLoopPeer::handleTimers( const String& mode )
{
	HANDLE* timerHandles = new HANDLE[activeTimers_.size()];
	int actualCount = 0;

	std::map<uint32,TimerInfo*>::iterator it = activeTimers_.begin();
	while ( it != activeTimers_.end() ) {
		TimerInfo* info = it->second;		
		timerHandles[actualCount] = info->timer;
		actualCount ++;
		
		it ++;
	}

	if ( actualCount > 0 ) {
		DWORD res = WaitForMultipleObjects( actualCount, timerHandles, FALSE, 5 );
		if ( (res >= WAIT_OBJECT_0) && (res < (WAIT_OBJECT_0+actualCount)) ) {
			//somebody has been signaled!

			HANDLE signaledTimer = timerHandles[res-WAIT_OBJECT_0];

			for (it = activeTimers_.begin(); it != activeTimers_.end(); it++) {
				TimerInfo* info = it->second;
				if ( info->timer == signaledTimer ) {
					DateTime dt = DateTime::now();
					DateTimeSpan s = dt - info->startedAt;

					runLoop_->internal_processTimer( info->mode, info->source, info->handler );
				}
			}
		}
	}

	delete [] timerHandles;
}


uint32 Win32RunLoopPeer::addTimer( const String& mode, 
								  Object* source, 
								  RunLoopCallback* handler, 
								  uint32 timeoutInMilliSeconds )
{
	TimerInfo* info = new TimerInfo();
	info->source = source;
	info->handler = handler;
	info->mode = mode;	

	info->timer = ::CreateWaitableTimer( NULL, FALSE, NULL );
	uint32 timerID = PtrToUInt32( info->timer );

	activeTimers_[timerID] = info;

	LARGE_INTEGER timeOut;
	memset(&timeOut,0,sizeof(timeOut));
	
	timeOut.QuadPart = 0;

	DateTime dueTime = System::convertLocalTimeToUTCTime( DateTime::now() );

	dueTime.incrMilliSecond( timeoutInMilliSeconds );
	
	SYSTEMTIME st;
	st.wDay = dueTime.getDay();
	st.wHour = dueTime.getHour();
	st.wMinute = dueTime.getMinute();
	st.wSecond = dueTime.getSecond();
	st.wMilliseconds = dueTime.getMillisecond();
	st.wDayOfWeek = dueTime.getWeekDay();
	st.wMonth = dueTime.getMonth();
	st.wYear = dueTime.getYear();

	SystemTimeToFileTime( &st, (FILETIME*)&timeOut );
	

	SetWaitableTimer( info->timer, &timeOut, timeoutInMilliSeconds, NULL, NULL, FALSE );

	info->startedAt = DateTime::now();

	return timerID;
}

void Win32RunLoopPeer::removeTimer( uint32 timerID )
{
	std::map<uint32,TimerInfo*>::iterator found = activeTimers_.find( timerID );
	VCF_ASSERT( found != activeTimers_.end() );

	if ( found != activeTimers_.end() ) {
		TimerInfo* info = found->second;
		CancelWaitableTimer( info->timer );
		CloseHandle( info->timer );
		delete info;
		activeTimers_.erase( found );
	}
}

void Win32RunLoopPeer::removeAll()
{
	std::map<uint32,TimerInfo*>::iterator it = activeTimers_.begin();
	while ( it != activeTimers_.end() ) {
		TimerInfo* info = it->second;
		CancelWaitableTimer( info->timer );
		CloseHandle( info->timer );

		delete info;

		it ++;
	}
}

void Win32RunLoopPeer::stop()
{	
	PostThreadMessage( runLoop_->getOwningThread()->getThreadID(), WM_QUIT, 0, 0 );
}

void Win32RunLoopPeer::postEvent( Event* event, RunLoopCallback* handler, bool deleteHandler )
{
	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );

	PostThreadMessage( runLoop_->getOwningThread()->getThreadID(), VCF_POSTMSGTORUNLOOP, 0, (LPARAM)pe );
}
*/

/**
$Id$
*/
