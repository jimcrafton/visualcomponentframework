
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopTimer.h>
#include <vcf/FoundationKit/OSXRunLoopTimerPeer.h>


namespace VCF {

OSXRunLoopTimerPeer::OSXRunLoopTimerPeer( RunLoopTimer* timer )
    : owner_( timer )
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
    peer->owner_->TimerFired( *peer->owner_ );
}

OSXRunLoopTimerPeer::~OSXRunLoopTimerPeer()
{
    CFRelease( timerRef_ );
}

bool OSXRunLoopTimerPeer::isActive() const
{
	return CFRunLoopTimerIsValid( timerRef_ ) ? true : false;
}

void OSXRunLoopTimerPeer::setActive( const bool& val )
{
	
}

bool OSXRunLoopTimerPeer::doesRepeat() const
{
	return CFRunLoopTimerDoesRepeat( timerRef_ ) ? true : false;
}

DateTimeSpan OSXRunLoopTimerPeer::getInterval() const
{
	CFTimeInterval interval = CFRunLoopTimerGetInterval( timerRef_ );
	
	return DateTimeSpan( interval * 1000.0 );
}

DateTime OSXRunLoopTimerPeer::getNextFireDate() const
{
	DateTime result;
	CFAbsoluteTime nextFire = CFRunLoopTimerGetNextFireDate( timerRef_ );
	
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();
	CFGregorianDate current = CFAbsoluteTimeGetGregorianDate( nextFire, tz );
	
	double dsecs = floor(current.second);
	unsigned int second = (int)dsecs;
	
	double milliseconds = (current.second - dsecs) * 1000.0;	
	
	result.set( current.year, current.month, current.day, 
				current.hour, current.minute, second, (unsigned int)milliseconds );
				
				
	return result;
}

};


/**
$Id$
*/
