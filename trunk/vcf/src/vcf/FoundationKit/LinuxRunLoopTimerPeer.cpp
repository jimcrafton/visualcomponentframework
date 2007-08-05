
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopTimer.h>
#include <vcf/FoundationKit/LinuxRunLoopTimerPeer.h>

#include <linux/timerfd.h>
#include <sys/syscall.h>

using namespace VCF;

LinuxRunLoopTimerPeer::LinuxRunLoopTimerPeer( RunLoopTimer* owner )
    : owner_( owner )
    , fileDesc_( 0 )
{
}

LinuxRunLoopTimerPeer::~LinuxRunLoopTimerPeer()
{
	int result = ::close( fileDesc_ );
	if( result != 0 ) {
			// some error occured, but how to handle it?
			perror( "Couldn't close timer file descriptor." );
	}
}

void LinuxRunLoopTimerPeer::create( const DateTime &fireDate )
{
	DateTimeSpan span = fireDate - DateTime::now();
	
	itimerspec ts;
	uint64 ms = span.getTotalMilliseconds();
	ts.it_value.tv_sec  = ms / 1000;
	ts.it_value.tv_nsec = ( (ms * 1000) % 1000000) * 1000;         
	ts.it_interval.tv_sec  = 0; //ts.it_value.tv_sec;
	ts.it_interval.tv_nsec = 0; //ts.it_value.tv_nsec; 

	int tfd = ::syscall( __NR_timerfd, -1, CLOCK_REALTIME, 0, &ts );
	if(tfd < 0) {
		throw RuntimeException( strerror( errno ) );
	}

	fileDesc_ = tfd;
}

void LinuxRunLoopTimerPeer::create( const DateTimeSpan &interval )
{	
	itimerspec ts;
	uint64 ms = interval.getTotalMilliseconds();
	ts.it_value.tv_sec  = ms / 1000;
	ts.it_value.tv_nsec = ( (ms * 1000) % 1000000) * 1000;         
	ts.it_interval.tv_sec  = ts.it_value.tv_sec;
	ts.it_interval.tv_nsec = ts.it_value.tv_nsec; 

	int tfd = ::syscall( __NR_timerfd, -1, CLOCK_REALTIME, 0, &ts );
	if(tfd < 0)	{
		throw RuntimeException( strerror( errno ) );
	}

	fileDesc_ = tfd;	
}

void LinuxRunLoopTimerPeer::create( const DateTime &fireDate, const DateTimeSpan &interval )
{
	DateTimeSpan span = fireDate - DateTime::now();
	
	itimerspec ts;
	uint64 ms = span.getTotalMilliseconds();
	ts.it_value.tv_sec  = ms / 1000;
	ts.it_value.tv_nsec = ( (ms * 1000) % 1000000) * 1000;
	
	ms = interval.getTotalMilliseconds();
	ts.it_interval.tv_sec  = ms / 1000;
	ts.it_interval.tv_nsec = ( (ms * 1000) % 1000000) * 1000;

	int tfd = ::syscall( __NR_timerfd, -1, CLOCK_REALTIME, 0, &ts );
	if(tfd < 0)	{
		throw RuntimeException( strerror( errno ) );
	}

	fileDesc_ = tfd;	
}

void LinuxRunLoopTimerPeer::perform()
{
	int ticks;
	int result = ::read(fileDesc_, &ticks, sizeof(int));
	if( result < 0 ) {
		throw RuntimeException( strerror( errno ) );
	}

    owner_->TimerFired( *owner_ );
}
