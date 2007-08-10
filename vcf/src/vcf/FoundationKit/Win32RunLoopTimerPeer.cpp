
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopTimer.h>
#include <vcf/FoundationKit/Win32RunLoopTimerPeer.h>

using namespace VCF;

Win32RunLoopTimerPeer::Win32RunLoopTimerPeer( RunLoopTimer* owner )
    : timer_( ::CreateWaitableTimer( NULL, FALSE, NULL ) )
    , owner_( owner )
{
}

Win32RunLoopTimerPeer::~Win32RunLoopTimerPeer()
{
    ::CloseHandle( timer_ );
}

void Win32RunLoopTimerPeer::create( const DateTime &fireDate )
{
    LARGE_INTEGER li;
    li.QuadPart = fireDate.getMilliseconds()*1000;
    ::SetWaitableTimer( timer_, &li, 0, NULL, NULL, FALSE );
}

void Win32RunLoopTimerPeer::create( const DateTimeSpan &interval )
{
    LARGE_INTEGER li;
    li.QuadPart=0;
    ::SetWaitableTimer( timer_, &li, interval.getTotalMilliseconds(), NULL, NULL, FALSE );
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

    LARGE_INTEGER li;
    li.LowPart  = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    ::SetWaitableTimer( timer_, &li, interval.getTotalMilliseconds(), NULL, NULL, TRUE );
}

void Win32RunLoopTimerPeer::perform()
{
    owner_->TimerFired( *owner_ );
}

/**
$Id$
*/
