
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopTimer.h>
#include <vcf/FoundationKit/Win32RunLoopTimerPeer.h>
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/FoundationKit/RunLoop.h"


using namespace VCF;

Win32RunLoopTimerPeer::Win32RunLoopTimerPeer( RunLoopTimer* owner )
    : timer_( ::CreateWaitableTimer( NULL, FALSE, NULL ) )
    , owner_( owner ),
	active_(false),
	periodicInterval_(0)
{
	dueTime_.QuadPart = 0;
}

Win32RunLoopTimerPeer::~Win32RunLoopTimerPeer()
{
    ::CloseHandle( timer_ );
}

void Win32RunLoopTimerPeer::create( const DateTime &fireDate )
{    
    dueTime_.QuadPart = fireDate.getMilliseconds()*1000;
	periodicInterval_ = 0;

    ::SetWaitableTimer( timer_, &dueTime_, periodicInterval_, NULL, NULL, FALSE );
	active_ = true;
}

void Win32RunLoopTimerPeer::create( const DateTimeSpan &interval )
{
    dueTime_.QuadPart=0;
	periodicInterval_ = interval.getTotalMilliseconds();

    ::SetWaitableTimer( timer_, &dueTime_, periodicInterval_, NULL, NULL, FALSE );
	active_ = true;
}

void Win32RunLoopTimerPeer::create( const DateTime &fireDate, const DateTimeSpan &interval )
{
    DateTime ufireData = fireDate.toUTC();

    uint32 year, month, day, hour, minute, second, millisecond;
    ufireData.get( &year, &month, &day, &hour, &minute, &second, &millisecond );

    SYSTEMTIME st;
    st.wYear = year;
    st.wMonth = month;
    st.wDay = day;
    st.wHour = hour;
    st.wMinute = minute;
    st.wSecond = second;
    st.wMilliseconds = millisecond;

    FILETIME ft;
    ::SystemTimeToFileTime( &st, &ft );

    dueTime_.LowPart  = ft.dwLowDateTime;
    dueTime_.HighPart = ft.dwHighDateTime;
	periodicInterval_ = interval.getTotalMilliseconds();

    ::SetWaitableTimer( timer_, &dueTime_, periodicInterval_, NULL, NULL, TRUE );
	active_ = true;
}

void Win32RunLoopTimerPeer::perform()
{
	lastFire_ = DateTime::now();

    owner_->TimerFired( *owner_ );
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->LoopEvents(rlTimerFired);
}

void Win32RunLoopTimerPeer::setActive( const bool& val )
{
	if ( active_ != val ) {
		active_ = val;

		if ( active_ ) {
			::SetWaitableTimer( timer_, &dueTime_, periodicInterval_, NULL, NULL, FALSE );
		}
		else {
			::CancelWaitableTimer( timer_ );
		}
	}	
}

bool Win32RunLoopTimerPeer::doesRepeat() const
{
	return periodicInterval_ > 0;
}

DateTimeSpan Win32RunLoopTimerPeer::getInterval() const
{	
	return DateTimeSpan(periodicInterval_);
}

DateTime Win32RunLoopTimerPeer::getNextFireDate() const
{
	DateTime result;
	DateTime now = DateTime::now();

	DateTime due;
	due.setMilliseconds( dueTime_.QuadPart / 1000 );

	if ( now < due ) {
		result = due;
	}
	else {
		DateTimeSpan sp = now - lastFire_;
		
		result = now + sp;
	}
	return result;
}

/**
$Id$
*/
