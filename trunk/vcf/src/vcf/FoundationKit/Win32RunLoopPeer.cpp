//Win32RunLoopPeer.cpp
/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopTimer.h"
#include "vcf/FoundationKit/RunLoopSource.h"
#include "vcf/FoundationKit/Win32RunLoopPeer.h"
#include "vcf/FoundationKit/Win32RunLoopTimerPeer.h"
#include "vcf/FoundationKit/Win32RunLoopSourcePeer.h"

using namespace VCF;

Win32RunLoopPeer::Win32RunLoopPeer( RunLoop* runLoop )
    : runLoop_(runLoop)
    , done_(false)
    , wakeUpEvent_(CreateEventW(NULL, TRUE, FALSE, NULL))
{
}

void Win32RunLoopPeer::run()
{
    while(!done_)
    {
        std::vector<HANDLE> handles;
        handles.push_back(wakeUpEvent_);
        
        for(std::map<HANDLE, SmartPtr<Procedure>::Shared>::iterator it =  handles_.begin();
                                                                    it != handles_.end();
                                                                    ++it)
        {
            handles.push_back(it->first);
        }

        DWORD result = ::MsgWaitForMultipleObjects(handles.size(), &handles[0], FALSE, INFINITE, QS_ALLEVENTS);

        if(result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0+handles.size())
        {
            HandleCallBackMap::iterator it = handles_.find(handles[result]);
            if(it != handles_.end())
            {
                HANDLE handle = handles[result];
                SmartPtr<Procedure>::Shared procedure = handles_[handle];
                procedure->invoke();
            }
            else
            {
                // It should be the wakeup event.
                VCF_ASSERT(it->first == handles[0]);
                ::ResetEvent(wakeUpEvent_);
            }
        }
        else if(result == WAIT_OBJECT_0+handles.size())
        {
            MSG msg;
            if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
            {
                System::println("Message arrived");
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        else if(result >= WAIT_ABANDONED_0 && result < WAIT_ABANDONED_0+handles.size())
        {

        }
        else if(result == WAIT_TIMEOUT)
        {
            VCF_ASSERT(false);
        }
        else
        {
            VCF_ASSERT(false);
        }
    }
}

void Win32RunLoopPeer::stop()
{
    done_ = true;
    ::SetEvent(wakeUpEvent_);
}

void Win32RunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopTimerPeer>(win32Peer, &Win32RunLoopTimerPeer::perform);
    
    handles_[handle] =  SmartPtr<Procedure>::Shared(callback);
}

void Win32RunLoopPeer::removeTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    handles_.erase(handle);
}

void Win32RunLoopPeer::addSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopSourcePeer>(win32Peer, &Win32RunLoopSourcePeer::perform);

    handles_[handle] = SmartPtr<Procedure>::Shared(callback);
}

void Win32RunLoopPeer::removeSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    handles_.erase(handle);
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
