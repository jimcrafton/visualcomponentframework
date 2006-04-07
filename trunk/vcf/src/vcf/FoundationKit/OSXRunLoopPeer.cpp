//OSXRunLoopPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/OSXRunLoopPeer.h"



using namespace VCF;

OSXRunLoopPeer::OSXRunLoopPeer( RunLoop* runLoop ):
	runLoop_(runLoop),
	runLoopSrc_(NULL)
{
	CFRunLoopSourceContext ctx;
	ctx.version = 0;
	ctx.info = this;
	ctx.retain = NULL;
	ctx.release = NULL;
	ctx.copyDescription = NULL;
	ctx.equal = NULL;
	ctx.hash = NULL;
	ctx.schedule = OSXRunLoopPeer::SrcScheduleCallBack;
	ctx.cancel = OSXRunLoopPeer::SrcCancelCallBack;
	ctx.perform = OSXRunLoopPeer::SrcPerformCallBack;
	

	runLoopSrc_ = CFRunLoopSourceCreate( NULL, 0, &ctx );
}

OSXRunLoopPeer::~OSXRunLoopPeer()
{
	removeAll();

	CFRelease( runLoopSrc_ );
}

void OSXRunLoopPeer::run( const String& mode, const DateTime* duration )
{
	CFRunLoopRef runLoopRef = CFRunLoopGetCurrent();
	//CFRunLoopAddSource( runLoopRef, runLoopSrc_ );

	if ( mode.empty() ) {
		CFRunLoopRun();
	}
	else {
		CFTextString tmp(mode);
		CFTimeInterval interval = 0;
		if ( NULL != duration ) {
			DateTime current = DateTime::now();
			DateTimeSpan d = *duration - current;

			interval = (double)d.getTotalMilliseconds() / 1000.0;
		}

		CFRunLoopRunInMode( tmp, interval, FALSE );
	}
}	

void OSXRunLoopPeer::SrcScheduleCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode )
{
	
}

void OSXRunLoopPeer::SrcCancelCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode )
{

}

void OSXRunLoopPeer::SrcPerformCallBack ( void *info )
{

}


void OSXRunLoopPeer::TimerCallBack ( CFRunLoopTimerRef timer,  void *info )
{

}

uint32 OSXRunLoopPeer::addTimer( const String& mode, 
								  Object* source, 
								  EventHandler* handler, 
								  uint32 timeoutInMilliSeconds )
{
	uint32 result = 0;
	
	CFRunLoopRef runLoopRef = CFRunLoopGetCurrent();

	CFTimeInterval interval = (double)(timeoutInMilliSeconds/1000.0);

	CFAbsoluteTime startingAt = CFAbsoluteTimeGetCurrent();
	startingAt += interval;

	CFRunLoopTimerContext ctx;
	ctx.version = 0;
	ctx.info = this;
	ctx.retain = NULL;
	ctx.release = NULL;
	ctx.copyDescription = NULL;

	CFRunLoopTimerRef timer = CFRunLoopTimerCreate( NULL, 
													startingAt, 
													interval, 
													0, 
													0, 
													OSXRunLoopPeer::TimerCallBack,
													&ctx );

	result = (uint32)timer;

	CFTextString tmp(mode);

	CFRunLoopAddTimer( runLoopRef, timer, tmp );

	return result;
}

void OSXRunLoopPeer::removeTimer( uint32 timerID )
{
	
}

void OSXRunLoopPeer::removeAll()
{
	
}

void OSXRunLoopPeer::stop()
{	
	CFRunLoopRef runLoopRef = CFRunLoopGetCurrent();
	CFRunLoopStop( runLoopRef );
}

OSHandleID OSXRunLoopPeer::getHandleID()
{
	return (OSHandleID) CFRunLoopGetCurrent();
}

void OSXRunLoopPeer::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
{
	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );
	
}
