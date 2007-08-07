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

void Win32RunLoopPeer::run()
{
    while ( !done_ ) {
        std::vector<HANDLE> handles;
        handles.push_back( wakeUpEvent_ );
        
        for ( std::map<HANDLE, SmartPtr<Procedure>::Shared>::iterator it =  handles_.begin();
                                                                    it != handles_.end();
                                                                    ++it) {
            handles.push_back(it->first);
        }

        DWORD result = ::MsgWaitForMultipleObjects( handles.size(), &handles[0], FALSE, INFINITE, QS_ALLEVENTS );

        if ( result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0+handles.size() ) {
            HandleCallBackMap::iterator it = handles_.find(handles[result]);
            if ( it != handles_.end() ) {
                HANDLE handle = handles[result];
                SmartPtr<Procedure>::Shared procedure = handles_[handle];
                procedure->invoke();
            }
            else {
                // It should be the wakeup event.
                VCF_ASSERT( it->first == handles[0] );
                ::ResetEvent( wakeUpEvent_ );
            }
        }
        else if ( result == WAIT_OBJECT_0+handles.size() ) {
            MSG msg;
            if ( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 ) {
                ::TranslateMessage( &msg );
                ::DispatchMessage( &msg );
            }
        }
        else if ( result >= WAIT_ABANDONED_0 && result < WAIT_ABANDONED_0+handles.size() ) {

        }
        else if ( result == WAIT_TIMEOUT ) {
            VCF_ASSERT( false );
        }
        else {
            VCF_ASSERT( false );
        }
    }
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
