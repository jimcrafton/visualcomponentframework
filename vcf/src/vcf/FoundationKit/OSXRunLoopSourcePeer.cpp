
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopSource.h>
#include <vcf/FoundationKIt/OSXRunLoopSourcePeer.h>

using namespace VCF;

void OSXRunLoopSourcePeer::CancelCallBack( void *info, CFRunLoopRef rl, CFStringRef mode )
{
    OSXRunLoopSourcePeer *peer = static_cast<OSXRunLoopSourcePeer*>( info );
    peer->owner_->internal_cancel();    
}

void OSXRunLoopSourcePeer::PerformCallBack( void *info )
{
    OSXRunLoopSourcePeer *peer = static_cast<OSXRunLoopSourcePeer*>( info );
    peer->owner_->internal_perform();
}

OSXRunLoopSourcePeer::OSXRunLoopSourcePeer( RunLoopSource* source )
    : owner_( source )
{
    CFRunLoopSourceContext context = {
        0,                          // version
        this,                       // info
        NULL,                       // CFAllocatorRetainCallBack
        NULL,                       // CFAllocatorReleaseCallBack
        NULL,                       // CFAllocatorCopyDescriptionCallBack
        NULL,                       // CFRunLoopEqualCallBack
        NULL,                       // CFRunLoopHashCallBack
        NULL,                       // CFRunLoopScheduleCallBack
        &OSXRunLoopSourcePeer::CancelCallBack,
        &OSXRunLoopSourcePeer::PerformCallBack
    };
    sourceRef_ = CFRunLoopSourceCreate( NULL, 0, &context );
}

OSXRunLoopSourcePeer::~OSXRunLoopSourcePeer()
{
}

void OSXRunLoopSourcePeer::fire()
{
    CFRunLoopSourceSignal( sourceRef_ );
}
