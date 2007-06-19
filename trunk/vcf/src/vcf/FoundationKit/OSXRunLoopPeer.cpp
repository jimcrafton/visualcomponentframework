//OSXRunLoopPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopSource.h"
#include <vcf/FoundationKit/RunLoopTimer.h>
#include "vcf/FoundationKit/OSXRunLoopPeer.h"
#include <vcf/FoundationKit/OSXRunLoopTimerPeer.h>
#include <vcf/FoundationKit/OSXRunLoopSourcePeer.h>


using namespace VCF;

OSXRunLoopPeer::OSXRunLoopPeer( RunLoop* runLoop )
    : runLoop_( runLoop )
    , runLoopRef_( CFRunLoopGetCurrent() )
{
}

void OSXRunLoopPeer::run()
{
    VCF_ASSERT( CFRunLoopGetCurrent() == runLoopRef_ );
    CFRunLoopRun();   
}

void OSXRunLoopPeer::stop()
{
    CFRunLoopStop( runLoopRef_ );
}

void OSXRunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    OSXRunLoopTimerPeer *osxPeer = static_cast<OSXRunLoopTimerPeer*>( peer.get() );
    if( osxPeer != NULL ) {
        CFRunLoopTimerRef timerRef = osxPeer->getTimer();
        if( timerRef != NULL ) {
            CFRunLoopAddTimer( runLoopRef_, timerRef, kCFRunLoopDefaultMode );            
        }
    }
}

void OSXRunLoopPeer::removeTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    OSXRunLoopTimerPeer *osxPeer = static_cast<OSXRunLoopTimerPeer*>( peer.get() );
    if( osxPeer != NULL ) {
        CFRunLoopTimerRef timerRef = osxPeer->getTimer();
        if( timerRef != NULL ) {
            CFRunLoopRemoveTimer( runLoopRef_, timerRef, kCFRunLoopDefaultMode );            
        }
    }
}

void OSXRunLoopPeer::addSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    OSXRunLoopSourcePeer *osxPeer = static_cast<OSXRunLoopSourcePeer*>( peer.get() );
    if( osxPeer != NULL ) {
        CFRunLoopSourceRef sourceRef = osxPeer->getSource();
        if( sourceRef != NULL ) {
            CFRunLoopAddSource( runLoopRef_, sourceRef, kCFRunLoopDefaultMode );                        
        }
    }
}

void OSXRunLoopPeer::removeSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    OSXRunLoopSourcePeer *osxPeer = static_cast<OSXRunLoopSourcePeer*>( peer.get() );
    if( osxPeer != NULL ) {
        CFRunLoopSourceRef sourceRef = osxPeer->getSource();
        if( sourceRef != NULL ) {
            CFRunLoopRemoveSource( runLoopRef_, sourceRef, kCFRunLoopDefaultMode );                        
        }
    }
}

/**
$Id$
*/
