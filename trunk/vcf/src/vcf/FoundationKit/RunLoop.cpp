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

const String RunLoop::DefaultMode = "DefaultMode";
const String RunLoop::SharedMode = "SharedMode";

struct PostEventInfo {
	PostEventInfo(): eventHandler(NULL),procedureCB(NULL),event(NULL),deleteHandler(false){}

	EventHandler* eventHandler;
	Procedure* procedureCB;
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
			else if ( NULL != info.procedureCB && info.deleteHandler ) {
				info.procedureCB->free();
			}
			++it;
		}
	}

	void postEvent( Procedure* callback, const bool& deleteHandler ) {
		{
			Lock l(m);
			PostEventInfo info;
			info.procedureCB = callback;
			info.deleteHandler = deleteHandler;
			posts.push_back( info );		
		}

		signal();
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
		else if ( NULL != info.procedureCB ) {
			info.procedureCB->invoke() ;
			
			if ( info.deleteHandler ) {
				info.procedureCB->free();
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
	RunLoopSourcePtr::Shared src(new PostEventSource());
	postSources_[RunLoop::DefaultMode] = src;
	addSource( src );
}

RunLoop::~RunLoop()
{
}

void RunLoop::run( const String& mode )
{
	VCF_ASSERT( RunLoop::SharedMode != mode );

	if ( mode == RunLoop::SharedMode ) {
		throw RuntimeException( "attempting to run with RunLoop::SharedMode" );
	}

	LoopEvents( rlStarted );

    peer_->run( NULL, mode );
	
	LoopEvents( rlFinished );
}

void RunLoop::run( const DateTime& till, const String& mode )
{
	run( till - DateTime::now(), mode );
}

void RunLoop::run( const DateTimeSpan& duration, const String& mode )
{
	VCF_ASSERT( RunLoop::SharedMode != mode );

	if ( mode == RunLoop::SharedMode ) {
		throw RuntimeException( "attempting to run with RunLoop::SharedMode" );
	}

	LoopEvents( rlStarted );

    peer_->run( &duration, mode );	
	
	LoopEvents( rlFinished );	
}

void RunLoop::stop( const String& mode )
{
    peer_->stop( mode );	
	LoopEvents( rlStopped );
}

void RunLoop::addTimer( RunLoopTimerPtr::Shared timer, const String& mode )
{
    timers_.push_back( timer );
    peer_->addTimer( timer, mode );
}

void RunLoop::removeTimer( RunLoopTimerPtr::Shared timer, const String& mode )
{
    std::vector<RunLoopTimerPtr::Shared>::iterator it = std::find( timers_.begin(), timers_.end(), timer );
    if( it != timers_.end() ) {
        peer_->removeTimer( timer, mode );
        timers_.erase( it );
    }
}

void RunLoop::addSource( RunLoopSourcePtr::Shared source, const String& mode )
{
    sources_.push_back( source );
    peer_->addSource( source, mode );
}

void RunLoop::removeSource( RunLoopSourcePtr::Shared source, const String& mode )
{
    std::vector<RunLoopSourcePtr::Shared>::iterator it = std::find( sources_.begin(), sources_.end(), source );
    if( it != sources_.end() ) {
        peer_->removeSource( source, mode );
        sources_.erase( it );
    }
}

void RunLoop::postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler, const String& mode )
{
	VCF_ASSERT( RunLoop::SharedMode != mode );

	if ( mode == RunLoop::SharedMode ) {
		throw RuntimeException( "Posting an event with using RunLoop::SharedMode" );
	}

	PostEventSource* postSrc = NULL;
	std::map<String,RunLoopSourcePtr::Shared>::iterator found =
		postSources_.find( mode );
	if ( found == postSources_.end() ) {
		RunLoopSourcePtr::Shared src(new PostEventSource());
		postSources_[mode] = src;
		addSource( src, mode );
		postSrc = static_cast<PostEventSource*>( src.get() );
	}
	else {
		postSrc = static_cast<PostEventSource*>( found->second.get() );
	} 

	postSrc->postEvent( eventHandler, event, deleteHandler );	
}

void RunLoop::postEvent( Procedure* callback, const bool& deleteHandler, const String& mode )
{
	VCF_ASSERT( RunLoop::SharedMode != mode );

	if ( mode == RunLoop::SharedMode ) {
		throw RuntimeException( "Posting an event with using RunLoop::SharedMode" );
	}

	PostEventSource* postSrc = NULL;
	std::map<String,RunLoopSourcePtr::Shared>::iterator found =
		postSources_.find( mode );
	if ( found == postSources_.end() ) {
		RunLoopSourcePtr::Shared src(new PostEventSource());
		postSources_[mode] = src;
		addSource( src, mode );
		postSrc = static_cast<PostEventSource*>( src.get() );
	}
	else {
		postSrc = static_cast<PostEventSource*>( found->second.get() );
	}

	postSrc->postEvent( callback, deleteHandler );
}

void RunLoop::clearAllTimers()
{	
	std::vector<RunLoopTimerPtr::Shared>::iterator it = timers_.begin();
	while ( !timers_.empty() ) {
		removeTimer( *it );
		it = timers_.begin();
	}
}

void RunLoop::clearAllSources()
{
	std::vector<RunLoopSourcePtr::Shared> tmp;
	std::vector<RunLoopSourcePtr::Shared>::iterator it = sources_.begin();
	while ( it != sources_.end() ) {
		RunLoopSourcePtr::Shared src = *it;
		 
		if ( NULL == dynamic_cast<PostEventSource*>(src.get()) ) {
			tmp.push_back( src );
		}
		++it;
	}

	it = tmp.begin();
	while ( it != tmp.end() ) {
		removeSource( *it );
		++it; 
	}
}

/**
$Id$
*/
