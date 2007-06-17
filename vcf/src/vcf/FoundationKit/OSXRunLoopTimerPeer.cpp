
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopTimer.h>
#include <vcf/FoundationKIt/OSXRunLoopTimerPeer.h>


using namespace VCF;

OSXRunLoopTimerPeer::OSXRunLoopTimerPeer( RunLoopTimer* timer )
    : RunLoopTimerPeer( timer )
{
}

namespace
{
    CFAbsoluteTime Convert( const DateTime &dt )
    {
        uint32 year;
        uint32 month;
        uint32 day;
        uint32 hour;
        uint32 minute;
        uint32 second;
        uint32 millisecond;	
        dt.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
        
        CFGregorianDate cfDate;
        cfDate.year = year;
        cfDate.month = month;
        cfDate.day = day;
        cfDate.hour = hour;
        cfDate.minute = minute;
        cfDate.second = second + millisecond / 1000.0;
        
        CFAbsoluteTime absTime = CFGregorianDateGetAbsoluteTime( cfDate, CFTimeZoneCopySystem() );
        return absTime;
    }
    
    CFTimeInterval Convert( const DateTimeSpan &interval )
    {
        return interval.getSeconds() + interval.getMilliseconds() / 1000.0;
    }
}

void OSXRunLoopTimerPeer::create( const DateTime &fireDate )
{
    CFRunLoopTimerContext context = { 0, this, NULL, NULL, NULL };
    timerRef_ = CFRunLoopTimerCreate(NULL, Convert( fireDate ), 0, 0, 0, &OSXRunLoopTimerPeer::TimerCallback, &context);    
}

void OSXRunLoopTimerPeer::create( const DateTimeSpan &interval )
{
    CFRunLoopTimerContext context = { 0, this, NULL, NULL, NULL };
    timerRef_ = CFRunLoopTimerCreate(NULL, CFAbsoluteTimeGetCurrent(), Convert( interval ), 0, 0, &OSXRunLoopTimerPeer::TimerCallback, &context);    
}

void OSXRunLoopTimerPeer::create( const DateTime &fireDate, const DateTimeSpan &interval )
{
    CFRunLoopTimerContext context = { 0, this, NULL, NULL, NULL };
    timerRef_ = CFRunLoopTimerCreate(NULL, Convert( fireDate ), Convert( interval ), 0, 0, &OSXRunLoopTimerPeer::TimerCallback, &context);    
}

void 
OSXRunLoopTimerPeer::TimerCallback( CFRunLoopTimerRef timer, void *info )
{
    OSXRunLoopTimerPeer *peer = (OSXRunLoopTimerPeer*)info;
    Event event( NULL, 0 );
    peer->owner_->TimerFired( &event );
}

OSXRunLoopTimerPeer::~OSXRunLoopTimerPeer()
{
    CFRelease( timerRef_ );
}
