//RunLoop.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/RunLoopSource.h"
#include <deque>

using namespace VCF;

struct PostEventInfo {
	PostEventInfo(): eventHandler(NULL),event(NULL),deleteHandler(false){}

	EventHandler* eventHandler;
	Event* event;
	bool deleteHandler;
};

class PostEventSource : public RunLoopSource {
public:	
	
	virtual ~PostEventSource() {
		std::deque<PostEventInfo>::iterator it = posts.begin();
		while ( it != posts.end() ) {
			PostEventInfo& info = *it;	
			if ( NULL != info.eventHandler && info.deleteHandler ) {
				info.eventHandler->free();
			}
			++it;
		}
	}

	void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler ) {
		{
			Lock l(m);
			PostEventInfo info;
			info.eventHandler = eventHandler;
			info.event = event;
			info.deleteHandler = deleteHandler;
			posts.push_back( info );		
		}

		signal();
	}

	virtual void perform() {
		PostEventInfo info;

		{
			Lock l(m);
			if ( !posts.empty() ) {
				info = posts.front();
				posts.pop_front();
			}
		}

		if ( NULL != info.eventHandler ) {
			info.eventHandler->invoke( info.event ) ;
			
			if ( info.deleteHandler ) {
				info.eventHandler->free();
			}
		}
	}

	virtual void cancel() {	}

protected:
	Mutex m;
	std::deque<PostEventInfo> posts;
};



RunLoop::RunLoop( Thread* thread ) 	
{
    peer_.reset( SystemToolkit::createRunLoopPeer( this ) );
    if ( peer_.get() == NULL ) {

        throw NoPeerFoundException();
    }

	postEventSource_.reset( new PostEventSource() );
	addSource( postEventSource_ );
}

RunLoop::~RunLoop()
{
}

void RunLoop::run()
{
	LoopEvents( rlStarted );

    peer_->run( NULL );
	
	LoopEvents( rlStopped );
}

void RunLoop::run( const DateTime& till )
{
	run( till - DateTime::now() );
}

void RunLoop::run( const DateTimeSpan& duration )
{
	LoopEvents( rlStarted );

    peer_->run( &duration );
	
	LoopEvents( rlStopped );
}

void RunLoop::stop()
{
    peer_->stop();	
}

void RunLoop::addTimer( RunLoopTimerPtr::Shared timer )
{
    timers_.push_back( timer );
    peer_->addTimer( timer );
}

void RunLoop::removeTimer( RunLoopTimerPtr::Shared timer )
{
    std::vector<RunLoopTimerPtr::Shared>::iterator it = std::find( timers_.begin(), timers_.end(), timer );
    if( it != timers_.end() ) {
        peer_->removeTimer( timer );
        timers_.erase( it );
    }
}

void RunLoop::addSource( RunLoopSourcePtr::Shared source )
{
    sources_.push_back( source );
    peer_->addSource( source );
}

void RunLoop::removeSource( RunLoopSourcePtr::Shared source )
{
    std::vector<RunLoopSourcePtr::Shared>::iterator it = std::find( sources_.begin(), sources_.end(), source );
    if( it != sources_.end() ) {
        peer_->removeSource( source );
        sources_.erase( it );
    }
}

void RunLoop::postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	PostEventSource* postSrc = static_cast<PostEventSource*>( postEventSource_.get() );

	postSrc->postEvent( eventHandler, event, deleteHandler );	
}

/**
$Id$
*/
