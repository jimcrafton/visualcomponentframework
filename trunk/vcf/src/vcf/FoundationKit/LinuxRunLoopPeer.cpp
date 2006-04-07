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

void LinuxRunLoopPeer::TimerSignalHandler(int sig, siginfo_t *extra, void*)
{
	VCF_ASSERT(sig == SIGRTMIN);
	VCF_ASSERT(extra->si_code == SI_TIMER);

	TimerInfo* info = (TimerInfo*)extra->si_value.sival_ptr;
	info->fired = true;
}

class LinuxRunLoopPeer::TimerSignalInstaller
{
public:
	TimerSignalInstaller(){
		struct sigaction act;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = &LinuxRunLoopPeer::TimerSignalHandler;
		int err = sigaction(SIGRTMIN, &act, NULL);
		VCF_ASSERT(err == 0);
	}
};

LinuxRunLoopPeer::LinuxRunLoopPeer( RunLoop* runLoop ):
	runLoop_(runLoop)
{
	static TimerSignalInstaller installSignal;

	stopEvent_.stop = false;
}

LinuxRunLoopPeer::~LinuxRunLoopPeer()
{
	Lock lock(activeTimers_.mutex);
	for(TimerMap::iterator it = activeTimers_.timers.begin();
		                   it != activeTimers_.timers.end(); 
						   ++it) {
		TimerInfo* info  = it->second;
		int r = timer_delete(info->timer);
		VCF_ASSERT(r == 0);
		delete info;
	}
}
void LinuxRunLoopPeer::run( const String& mode, const DateTime* duration )
{
	{
		Lock lock(stopEvent_.mutex);
		stopEvent_.stop = false;
	}

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
			Lock lock(postedEvents_.mutex);
			if(!postedEvents_.events.empty()) {
				pe = postedEvents_.events.front();
				postedEvents_.events.pop();
			}
		}
		if(pe != NULL) {
			runLoop_->internal_processReceivedEvent( pe );
		}
		delete pe;

		{
			Lock lock(stopEvent_.mutex);
			if(stopEvent_.stop) {
				runLoop_->internal_cancelled( mode );
				break;
			}
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

		System::sleep(1);
	}
}

void LinuxRunLoopPeer::stop()
{
	Lock lock(stopEvent_.mutex);
	stopEvent_.stop = true;
}

void LinuxRunLoopPeer::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
{
	PostedEvent* pe = new PostedEvent( event, handler, deleteHandler );
	Lock lock(postedEvents_.mutex);
	postedEvents_.events.push(pe);
}

uint32 LinuxRunLoopPeer::addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds )
{
	TimerInfo* info = new TimerInfo();
	info->source = source;
	info->handler = handler;
	info->mode = mode;
	info->fired = false;

    struct sigevent ev;
	ev.sigev_notify = SIGEV_SIGNAL;
    ev.sigev_signo = SIGRTMIN;
	ev.sigev_value.sival_int = 0;
	ev.sigev_value.sival_ptr = info;


	long err = timer_create(CLOCK_REALTIME, &ev, &info->timer);
	VCF_ASSERT(err == 0);
	uint32 timerID = (uint32)info->timer;
    
    itimerspec itime;
	itime.it_value.tv_sec  = timeoutInMilliSeconds / 1000;
	itime.it_value.tv_nsec = ((timeoutInMilliSeconds * 1000) % 1000000) * 1000; 
	itime.it_interval.tv_sec  = itime.it_value.tv_sec;
	itime.it_interval.tv_nsec = itime.it_value.tv_nsec; 

	err = timer_settime(info->timer, 0, &itime, NULL);
	VCF_ASSERT(err == 0);

	info->startedAt = DateTime::now();
	{
		Lock lock(activeTimers_.mutex);
		activeTimers_.timers[timerID] = info;
	}
    
    return timerID;
}

void LinuxRunLoopPeer::removeTimer( uint32 timerID )
{
	Lock lock(activeTimers_.mutex);
	TimerMap::iterator it = activeTimers_.timers.find(timerID);
	if(it != activeTimers_.timers.end()) {
		TimerInfo* info = it->second;
		int r = timer_delete(info->timer);
		VCF_ASSERT(r == 0);
		delete info;
		activeTimers_.timers.erase(it);
	}
}

void LinuxRunLoopPeer::handleTimers( const String& mode )
{
	Lock lock(activeTimers_.mutex);

	for(TimerMap::iterator it = activeTimers_.timers.begin();
		                   it != activeTimers_.timers.end(); 
						   ++it) {
		TimerInfo& info  = *(it->second);
		if(info.fired) {
			info.fired = false;
			runLoop_->internal_processTimer( info.mode, info.source, info.handler );
		}
	}
}

