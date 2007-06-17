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
    CFRunLoopTimerRef timerRef = osxPeer->getTimer();
    CFRunLoopAddTimer( runLoopRef_, timerRef, kCFRunLoopDefaultMode );    
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


//class OSXRunLoopPeer::TimerInfo {
//public:
//    TimerInfo(RunLoop *rl, Object* src, EventHandler* hnd, const String&  md, const DateTime& sa)
//        : runLoop(rl), source(src), handler(hnd), mode(md), startedAt(sa)
//    {
//    }
//    
//    ~TimerInfo()
//    {
//    }
//
//    RunLoop*      runLoop;
//    Object*       source;
//    EventHandler* handler;
//    String        mode;
//    DateTime      startedAt;
//};
//
//class OSXRunLoopPeer::EventInfo {
//public:
//    EventInfo(RunLoop *rl, PostedEvent *e, EventHandler *eh, bool deleteHandler) 
//        : runLoop(rl), event(e), handler(eh), deleteHandlerFlag(deleteHandler)  
//    {
//        
//    }
//
//    RunLoop      *runLoop;
//    PostedEvent  *event;
//    EventHandler *handler;
//    bool          deleteHandlerFlag;
//};
//
//OSXRunLoopPeer::OSXRunLoopPeer( RunLoop* runLoop ):
//	runLoop_(runLoop)
//{
//    CFRunLoopSourceContext ctx;
//    ctx.version = 0;
//    ctx.info    = this;
//    ctx.retain  = NULL;
//    ctx.release = NULL;
//    ctx.copyDescription = NULL;
//    ctx.equal = NULL;
//    ctx.hash  = NULL;
//    ctx.schedule = NULL;
//    ctx.cancel   = NULL;
//    ctx.perform  = &OSXRunLoopPeer::EventPerformCallBack;
//    eventSource_ = CFRunLoopSourceCreate( NULL, 0, &ctx );
//    
//    runLoopRef_ = CFRunLoopGetCurrent();
//}
//
//OSXRunLoopPeer::~OSXRunLoopPeer()
//{
//	removeAll();
//}
//
//void OSXRunLoopPeer::run( const String& mode, const DateTime* duration )
//{
////    for ( SourceMap::iterator it = sourceMap_.begin(); it != sourceMap_.end(); ++it ) {
////        Boolean alreadyAdded = CFRunLoopContainsSource( runLoopRef_, it->second, kCFRunLoopDefaultMode );
////        if ( !alreadyAdded ) {
////            CFRunLoopAddSource( runLoopRef_, it->second, kCFRunLoopDefaultMode );            
////        }
////    }
//
////    for ( TimerInfoSet::iterator it = timerInfoSet_.begin(); it != timerInfoSet_.end(); ++it ) {
////        CFTextString mode( (*it->second).mode );
////        Boolean alreadyAdded = CFRunLoopContainsTimer( runLoopRef_, it->first, mode );
////        if ( !alreadyAdded ) {
////            CFRunLoopAddTimer( runLoopRef_, it->first, mode );
////        }
////    }
//
//    Boolean alreadyAdded = CFRunLoopContainsSource( runLoopRef_, eventSource_, kCFRunLoopDefaultMode );
//    if ( !alreadyAdded ) {
//        CFRunLoopAddSource( runLoopRef_, eventSource_, kCFRunLoopDefaultMode );
//    }
//        
//	if ( mode.empty() ) {
//		CFRunLoopRun();
//	}
//	else {
//		CFTextString tmp(mode);
//		CFTimeInterval interval = 0;
//		if ( NULL != duration ) {
//			DateTime current = DateTime::now();
//			DateTimeSpan d = *duration - current;
//
//			interval = (double)d.getTotalMilliseconds() / 1000.0;
//		}
//
//		CFRunLoopRunInMode( tmp, interval, FALSE );
//	}
//    
//    CFRelease( runLoopRef_ );
//    runLoopRef_ = NULL;
//}	
//
//void OSXRunLoopPeer::SrcScheduleCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode )
//{
//}
//
//void OSXRunLoopPeer::SrcCancelCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode )
//{
//    RunLoopSource *rls = static_cast<RunLoopSource*>(info);
//    rls->cancel();
//}
//
//void OSXRunLoopPeer::SrcPerformCallBack ( void *info )
//{
//    RunLoopSource *rls = static_cast<RunLoopSource*>(info);
//    rls->perform();
//}
//
//void OSXRunLoopPeer::EventPerformCallBack ( void *info )
//{
//    OSXRunLoopPeer *rl = static_cast<OSXRunLoopPeer*>(info);
//	rl->runLoop_->internal_processReceivedEvent( rl->eventInfo_->event );
//    delete rl->eventInfo_;
//    rl->eventInfo_ = NULL;
//}
//
//void OSXRunLoopPeer::addSource( RunLoopSource* source )
//{
//	CFRunLoopSourceContext ctx;
//	ctx.version = 0;
//	ctx.info    = source;
//	ctx.retain  = NULL;
//	ctx.release = NULL;
//	ctx.copyDescription = NULL;
//	ctx.equal = NULL;
//	ctx.hash  = NULL;
//	ctx.schedule = &OSXRunLoopPeer::SrcScheduleCallBack;
//	ctx.cancel   = &OSXRunLoopPeer::SrcCancelCallBack;
//	ctx.perform  = &OSXRunLoopPeer::SrcPerformCallBack;
//	
//    CFRunLoopSourceRef rls = CFRunLoopSourceCreate( NULL, 0, &ctx );
//    CFRunLoopAddSource( runLoopRef_, rls, kCFRunLoopDefaultMode );     
//    
//    VCF_ASSERT( sourceMap_.find(source) == sourceMap_.end() );
//    sourceMap_[source] = rls;
//}
//
//void OSXRunLoopPeer::removeSource( RunLoopSource* source )
//{
//    SourceMap::iterator it = sourceMap_.find( source );
//    if ( it != sourceMap_.end() ) {
//        CFRunLoopSourceRef rls = it->second;
//        CFRunLoopRemoveSource( runLoopRef_, rls, kCFRunLoopDefaultMode );           
//    } 
//}
//
//void OSXRunLoopPeer::TimerCallBack ( CFRunLoopTimerRef timer,  void *info )
//{    
//    TimerInfo *timerInfo = static_cast<TimerInfo*>(info);
//    
//    Event event( timerInfo->source, RunLoop::teTimedOut );
//    if ( NULL != timerInfo->handler ) {
//        timerInfo->handler->invoke( &event );
//    }
//    else {
//        timerInfo->runLoop->TimerEvents.fireEvent( &event );
//    }
//}
//
//uint32 OSXRunLoopPeer::addTimer( const String& mode, 
//								  Object* source, 
//								  EventHandler* handler, 
//								  uint32 timeoutInMilliSeconds )
//{
//	uint32 result = 0;
//
//	CFTimeInterval interval = (double)(timeoutInMilliSeconds/1000.0);
//
//    // is this correct? If the runloop isn't running yet, shouldn't this be releative to
//    // start of the runloop?
//	CFAbsoluteTime startingAt = CFAbsoluteTimeGetCurrent();
//	startingAt += interval;
//
//    TimerInfoPtr::Shared timerInfo(new TimerInfo( runLoop_,
//                                                  source,
//                                                  handler,
//                                                  mode,
//                                                  startingAt ) );
//    
//	CFRunLoopTimerContext ctx;
//	ctx.version = 0;
//	ctx.info = timerInfo.get();
//	ctx.retain = NULL;
//	ctx.release = NULL;
//	ctx.copyDescription = NULL;
//
//	CFRunLoopTimerRef timer = CFRunLoopTimerCreate( NULL, 
//													startingAt, 
//													interval, 
//													0, 
//													0, 
//													&OSXRunLoopPeer::TimerCallBack,
//													&ctx );
//
//	result = (uint32)timer;
//    
//
//    if( mode.empty() )
//    {
//        CFRunLoopAddTimer( runLoopRef_, timer, kCFRunLoopCommonModes );
//    }
//    else
//    {
//        CFTextString tmpMode( mode );
//        CFRunLoopAddTimer( runLoopRef_, timer, tmpMode );        
//    }
//
//    timerInfoSet_[timer] = timerInfo;
//	return result;
//}
//
//void OSXRunLoopPeer::removeTimer( uint32 timerID )
//{
//    TimerInfoSet::iterator it = timerInfoSet_.find( reinterpret_cast<CFRunLoopTimerRef>(timerID) );
//    if ( it != timerInfoSet_.end() ) {
//        if ( runLoopRef_ != NULL ) {
//            CFTextString mode( (*it->second).mode );
//            CFRunLoopRemoveTimer( runLoopRef_, it->first, mode );
//        }
//        timerInfoSet_.erase( it );
//    }
//}
//
//void OSXRunLoopPeer::removeAll()
//{
//    if(runLoopRef_ != NULL) {
//        for ( SourceMap::iterator it = sourceMap_.begin(); it != sourceMap_.end(); ++it ) {
//            CFRunLoopRemoveSource( runLoopRef_, it->second, kCFRunLoopDefaultMode );
//            CFRelease( it->second );
//        }
//        sourceMap_.clear();
//        
//        for ( TimerInfoSet::iterator it = timerInfoSet_.begin(); it != timerInfoSet_.end(); ++it ) {
//            CFTextString mode( (*it->second).mode );
//            CFRunLoopRemoveTimer( runLoopRef_, it->first, mode );
//        }
//        timerInfoSet_.clear();
//    } 
//}
//
//void OSXRunLoopPeer::stop()
//{	
//	CFRunLoopStop( runLoopRef_ );
//}
//
//OSHandleID OSXRunLoopPeer::getHandleID()
//{
//	return (OSHandleID) runLoopRef_;
//}
//
//void OSXRunLoopPeer::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
//{
//	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );
//    eventInfo_ = new EventInfo( runLoop_, pe, handler, deleteHandler );
//    CFRunLoopSourceSignal( eventSource_ );
//}


/**
$Id$
*/
