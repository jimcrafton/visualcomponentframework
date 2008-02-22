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
    : runLoop_( runLoop )
    , done_( false )
    , wakeUpEvent_( CreateEventW( NULL, TRUE, FALSE, NULL ) )
{
}

void Win32RunLoopPeer::run( const DateTimeSpan* duration )
{
	DWORD timeoutInMS = (NULL != duration) ? duration->getTotalMilliseconds() : INFINITE;

    while ( !done_ ) {
		//Thanks to obirsoy for rewriting this for Win32!

        std::vector<HANDLE> handles,firedHandles;
        handles.push_back( wakeUpEvent_ );
        
        for ( std::map<HANDLE, SmartPtr<Procedure>::Shared>::iterator it =  handles_.begin();
                                                                    it != handles_.end();
                                                                    ++it) {
            handles.push_back(it->first);
        }

		DWORD wait = timeoutInMS;
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
			HandleCallBackMap::iterator it = handles_.find(*fit);
			if ( it != handles_.end() ) {
				HANDLE handle = *fit;
				SmartPtr<Procedure>::Shared procedure = handles_[handle];
				procedure->invoke();
				::ResetEvent( wakeUpEvent_ );
			}
			else {
				// It should be the wakeup event.
				VCF_ASSERT( *fit == handles[0] );
				::ResetEvent( wakeUpEvent_ );
			}
		}
	}

	done_ = false;
}

void Win32RunLoopPeer::stop()
{
    done_ = true;
    ::SetEvent( wakeUpEvent_ );
}

bool Win32RunLoopPeer::isStopped() const
{
    return done_;
}

void Win32RunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopTimerPeer>( win32Peer, &Win32RunLoopTimerPeer::perform );
    
    handles_[handle] =  SmartPtr<Procedure>::Shared( callback );
}

void Win32RunLoopPeer::removeTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    Win32RunLoopTimerPeer *win32Peer = static_cast<Win32RunLoopTimerPeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    handles_.erase( handle );
}

void Win32RunLoopPeer::addSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    
    Procedure *callback = new ClassProcedure<Win32RunLoopSourcePeer>( win32Peer, &Win32RunLoopSourcePeer::perform );

    handles_[handle] = SmartPtr<Procedure>::Shared(callback);
}

void Win32RunLoopPeer::removeSource( RunLoopSourcePtr::Shared source )
{
    source->internal_cancel();
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    Win32RunLoopSourcePeer *win32Peer = static_cast<Win32RunLoopSourcePeer*>( peer.get() );
    HANDLE handle = win32Peer->getHandle();
    handles_.erase( handle );
}

/**
$Id$
*/
