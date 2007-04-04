//LinuxRunLoopPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/LinuxRunLoopPeer.h"

using namespace VCF;

void LinuxRunLoopPeer::TimerNotifyHandler( sigval_t sigval )
{
	// System::println(Format("TimerHandler ThreadID RunLoop %lu") % pthread_self());
	TimerInfo* info = reinterpret_cast<TimerInfo*>( sigval.sival_ptr );
	++info->fired_;
}

LinuxRunLoopPeer::TimerInfo::TimerInfo( Object *source, EventHandler *handler, const String &mode ) :
	source_(source),
	handler_(handler),
	mode_(mode),
	fired_(0)
{
}

LinuxRunLoopPeer::LinuxRunLoopPeer( RunLoop* runLoop ) :
	runLoop_( runLoop )
{
	stopEvent_.stop_ = false;
}

LinuxRunLoopPeer::~LinuxRunLoopPeer()
{
	Lock lock( activeTimers_.mutex_ );
	for(TimerMap::iterator it = activeTimers_.timers_.begin();
		                   it != activeTimers_.timers_.end(); 
						   ++it) {
		TimerInfo* info  = it->second;
		int r = timer_delete( info->timer_ );
		VCF_ASSERT(r == 0);
		delete info;
	}
}

void LinuxRunLoopPeer::run( const String& mode, const DateTime* duration )
{
	stopEvent_.stop_ = false;

	DateTime current = DateTime::now();

	DateTime end;
	if ( NULL != duration ) {
		end = *duration;
	}
	else {
		end = current;
	}

	while ( true ) {
		PostedEvent* pe = NULL;
		{
			Lock lock( postedEvents_.mutex_ );
			if ( !postedEvents_.events_.empty() ) {
				pe = postedEvents_.events_.front();
				postedEvents_.events_.pop();
			}
		}
		if ( NULL != pe ) {
			runLoop_->internal_processReceivedEvent( pe );
			delete pe;
		}

		if ( stopEvent_.stop_ ) {
			runLoop_->internal_cancelled( mode );
			break;
		}

		if ( current > end ) {
			runLoop_->internal_cancelled( mode );
			break;
		}

		runLoop_->internal_executeOnce( mode );

		handleTimers( mode );

		current = DateTime::now();
		if ( NULL == duration ) {
			end = current;
		}
	}
}

void LinuxRunLoopPeer::stop()
{
	stopEvent_.stop_ = true;
}

void LinuxRunLoopPeer::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
{
	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );
	Lock lock( postedEvents_.mutex_ );
	postedEvents_.events_.push(pe);
}

uint32 LinuxRunLoopPeer::addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds )
{
	TimerInfo* info = new TimerInfo( source, handler, mode );

    sigevent ev;
	ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_signo = 0;
	ev.sigev_notify_function = &LinuxRunLoopPeer::TimerNotifyHandler;
	ev.sigev_notify_attributes = NULL;
	ev.sigev_value.sival_ptr = info;

	int32 err = timer_create( CLOCK_REALTIME, &ev, &info->timer_ );
	VCF_ASSERT(err == 0);
	uint32 timerID = (uint32)info->timer_;
    
    itimerspec itime;
	itime.it_value.tv_sec  = timeoutInMilliSeconds / 1000;
	itime.it_value.tv_nsec = ((timeoutInMilliSeconds * 1000) % 1000000) * 1000; 
	itime.it_interval.tv_sec  = itime.it_value.tv_sec;
	itime.it_interval.tv_nsec = itime.it_value.tv_nsec; 

	err = timer_settime( info->timer_, 0, &itime, NULL );
	VCF_ASSERT(err == 0);

	info->startedAt_ = DateTime::now();
	{
		Lock lock( activeTimers_.mutex_ );
		activeTimers_.timers_[timerID] = info;
	}
    
    return timerID;
}

void LinuxRunLoopPeer::removeTimer( uint32 timerID )
{
	Lock lock( activeTimers_.mutex_ );
	TimerMap::iterator it = activeTimers_.timers_.find( timerID );
	if ( it != activeTimers_.timers_.end() ) {
		TimerInfo* info = it->second;
		int r = timer_delete( info->timer_ );
		VCF_ASSERT(r == 0);
		delete info;
		activeTimers_.timers_.erase( it );
	}
}

void LinuxRunLoopPeer::handleTimers( const String& mode )
{
	Lock lock( activeTimers_.mutex_ );

	for(TimerMap::iterator it = activeTimers_.timers_.begin();
		                   it != activeTimers_.timers_.end(); 
						   ++it) {
		TimerInfo& info  = *(it->second);
		if ( info.fired_ > 0 ) {
			--info.fired_;
			runLoop_->internal_processTimer( info.mode_, info.source_, info.handler_ );
		}
	}
}


/**
$Id$
*/
