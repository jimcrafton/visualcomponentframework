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



Win32RunLoopPeer::ModeInfo::ModeInfo():
	wakeUpEvent( NULL )
{

}


Win32RunLoopPeer::Win32RunLoopPeer( RunLoop* runLoop )
    : runLoop_( runLoop )
{
	ModeInfo* modeInfo = new ModeInfo();
	
	modeInfo->wakeUpEvent = CreateEventW( NULL, TRUE, FALSE, NULL );
	
	modes_[RunLoop::DefaultMode] = modeInfo;
}

Win32RunLoopPeer::~Win32RunLoopPeer()
{
	ModeMap::iterator it = modes_.begin();
	while ( it != modes_.end() ) {
		delete it->second;
		++it;
	}
	modes_.clear();
}

Win32RunLoopPeer::ModeInfo* Win32RunLoopPeer::initRun(const String& mode)
{
	ModeInfo* result = NULL;

	ModeMap::iterator found = modes_.find( mode );
	if ( found == modes_.end() ) {
		result = new ModeInfo();

		result->wakeUpEvent = CreateEventW( NULL, TRUE, FALSE, NULL );

		modes_[mode] = result;
	}
	else {
		result = modes_[mode];
	}

	VCF_ASSERT( NULL != result );

	result->done.push_back(false);

	return result;
}

void Win32RunLoopPeer::run( const DateTimeSpan* duration, const String& mode )
{
	DWORD timeoutInMS = (NULL != duration) ? (DWORD)duration->getTotalMilliseconds() : INFINITE;
	
    ModeInfo* info = initRun( mode );

	HandleCallBackMap& modeHandles = info->handles;

	DateTime start = DateTime::now();

    while ( !info->done.back() ) {
		//Thanks to obirsoy for rewriting this for Win32!

		DateTimeSpan elapsed = DateTime::now() - start;
		DWORD adjustedTimeOut = (NULL == duration) ? INFINITE : timeoutInMS - elapsed.getTotalMilliseconds();
		DWORD wait = adjustedTimeOut;


        std::vector<HANDLE> handles,firedHandles;
        handles.push_back( info->wakeUpEvent );
        std::map<HANDLE, SmartPtr<Procedure>::Shared>::iterator it;

        for ( it = modeHandles.begin();
				it != modeHandles.end();
				++it) {
            handles.push_back(it->first);
        }

		for ( it = sharedHandles_.begin();
				it != sharedHandles_.end();
				++it) {
            handles.push_back(it->first);
        }															
		

		bool processedAllFires = false;
		while(!processedAllFires) {
			DWORD result = ::MsgWaitForMultipleObjects( handles.size(), &handles[0], FALSE, wait, QS_ALLEVENTS );
			
			if ( result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0+handles.size() ) {
				// add to fired handles list
				firedHandles.push_back(handles[result]);
				
				// remove from wait list
				std::vector<HANDLE>::iterator it = handles.begin();
				std::advance(it, result);
				handles.erase(it);
				
				// only the first wait should be infinite...
				wait = 0;
				
				// end the loop if there is nothing left to wait.
				processedAllFires = handles.empty();
			}
			else if ( result == WAIT_OBJECT_0+handles.size() ) {
				MSG msg;
				if ( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 ) {
					::TranslateMessage( &msg );
					::DispatchMessage( &msg );
				}
			}
			else if ( result >= WAIT_ABANDONED_0 && result < WAIT_ABANDONED_0+handles.size() ) {
				// I don't know. This looks like a logical thing to do...
				processedAllFires = true;
			}
			else if ( result == WAIT_TIMEOUT && wait == adjustedTimeOut ) {
				// The run loop timeout has occurred, so quit, cause we're done running
				processedAllFires = true;
				stop(mode);
			}
			else if ( result == WAIT_TIMEOUT ) {
				// There is no other fired event so exit the loop.
				processedAllFires = true;
			}
			else {
				VCF_ASSERT( false );
			}
		}
		
		// Now fire everything we got..
		for(std::vector<HANDLE>::iterator fit=firedHandles.begin(); fit!=firedHandles.end(); ++fit) {
			HandleCallBackMap::iterator it = modeHandles.find(*fit);
			if ( it != modeHandles.end() ) {
				HANDLE handle = *fit;
				SmartPtr<Procedure>::Shared procedure = modeHandles[handle];
				procedure->invoke();
				::ResetEvent( info->wakeUpEvent );
			}
			else {
				it = sharedHandles_.find(*fit);
				if ( it != sharedHandles_.end() ) {
					HANDLE handle = *fit;
					SmartPtr<Procedure>::Shared procedure = sharedHandles_[handle];
					procedure->invoke();
					::ResetEvent( info->wakeUpEvent );
				}
				else {
					// It should be the wakeup event.
					VCF_ASSERT( *fit == info->wakeUpEvent );
					::ResetEvent( info->wakeUpEvent );
				}
			}
		}
	}

	VCF_ASSERT( !info->done.empty() );
	info->done.pop_back();
}

void Win32RunLoopPeer::stop( const String& mode )
{
	ModeMap::iterator found = modes_.find( mode );
	if ( found != modes_.end() ) {
		ModeInfo* info = found->second;
		if ( !info->done.empty() ) {
			info->done.back() = true;
		}
		::SetEvent( info->wakeUpEvent );
	}
}

bool Win32RunLoopPeer::isStopped(const String& mode) const
{
	ModeMap::const_iterator found = modes_.find( mode );
	if ( found != modes_.end() ) {
		const ModeInfo* info = found->second;
		if ( !info->done.empty() ) {
			return info->done.back();
		}
	}

    return true;
}

void Win32RunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer, const String& mode )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
	
	HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopTimerPeer>( win32Peer, &Win32RunLoopTimerPeer::perform );


	if ( RunLoop::SharedMode == mode ) {
		sharedHandles_[handle] = SmartPtr<Procedure>::Shared(callback);
	}
	else{
		
		ModeInfo* info = NULL;
		
		ModeMap::iterator found = modes_.find( mode );
		if ( found == modes_.end() ) {
			info = new ModeInfo();
			
			info->wakeUpEvent = CreateEventW( NULL, TRUE, FALSE, NULL );
			
			modes_[mode] = info;
		}
		else {
			info = found->second;
		}    
		
		info->handles[handle] =  SmartPtr<Procedure>::Shared( callback );
	}
}

void Win32RunLoopPeer::removeTimer( RunLoopTimerPtr::Shared timer, const String& mode )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();

	if ( RunLoop::SharedMode == mode ) {
		sharedHandles_.erase( handle );
	}
	else {
		ModeMap::iterator found = modes_.find( mode );
		if ( found != modes_.end() ) {
			ModeInfo* info = found->second;		
			info->handles.erase( handle );
		}
	}
}

void Win32RunLoopPeer::addSource( RunLoopSourcePtr::Shared source, const String& mode )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopSourcePeer>( win32Peer, &Win32RunLoopSourcePeer::perform );

	if ( RunLoop::SharedMode == mode ) {
		sharedHandles_[handle] = SmartPtr<Procedure>::Shared(callback);
	}
	else{
		
		ModeInfo* info = NULL;
		
		ModeMap::iterator found = modes_.find( mode );
		if ( found == modes_.end() ) {
			info = new ModeInfo();
			
			info->wakeUpEvent = CreateEventW( NULL, TRUE, FALSE, NULL );
			
			modes_[mode] = info;
		}
		else {
			info = found->second;
		}
		
		info->handles[handle] = SmartPtr<Procedure>::Shared(callback);
	}
}

void Win32RunLoopPeer::removeSource( RunLoopSourcePtr::Shared source, const String& mode )
{
    source->internal_cancel();
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();

	if ( RunLoop::SharedMode == mode ) {
		sharedHandles_.erase( handle );
	}
	else {
		ModeMap::iterator found = modes_.find( mode );
		if ( found != modes_.end() ) {
			ModeInfo* info = found->second;
			info->handles.erase( handle );
		}
	}
}

/**
$Id$
*/
