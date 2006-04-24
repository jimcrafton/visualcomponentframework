//RunLoop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/RunLoopSource.h"

using namespace VCF;

RunLoop::RunLoop( Thread* thread ):
	peer_(NULL),
	stopped_(true),
	owningThread_(thread)
{
	peer_ = SystemToolkit::createRunLoopPeer( this );
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

RunLoop::~RunLoop()
{
	delete peer_;
}

void RunLoop::run()
{
	String defaultMode;
	
	pushCurrentMode( defaultMode );

	peer_->run( defaultMode, NULL );
	
	popCurrentMode();
}

void RunLoop::run( const String& mode, const DateTime& duration )
{
	stopped_ = false;
	pushCurrentMode( mode );
	
	peer_->run( mode, &duration );	

	popCurrentMode();
}

void RunLoop::stop()
{
	stopped_ = true;
	peer_->stop();
}

String RunLoop::getCurrentRunMode()
{
	String result;
	if ( !modes_.empty() ) {
		result = modes_.front();
	}
	return result;
}

void RunLoop::pushCurrentMode( const String& mode )
{
	Lock l(mutex_);
	
	modes_.push_front(mode);
}

void RunLoop::popCurrentMode()
{
	Lock l(mutex_);
	if ( !modes_.empty() ) {
		modes_.pop_front();
	}
}

RunLoopPeer* RunLoop::getPeer()
{
	return peer_;
}

void RunLoop::addSource( RunLoopSource* source )
{
	Lock l(mutex_);
	//check for duplicate entries
	std::vector<RunLoopSource*>::iterator found = std::find( sources_.begin(), sources_.end(), source );
	if ( found == sources_.end() ) {
		sources_.push_back( source );
		source->setRunLoop( this );
	}
}

void RunLoop::removeSource( RunLoopSource* source )
{
	Lock l(mutex_);
	std::vector<RunLoopSource*>::iterator found = std::find( sources_.begin(), sources_.end(), source );
	if ( found != sources_.end() ) {
		sources_.erase( found );
	}
}

void RunLoop::postEvent( Event* event )
{
	peer_->postEvent( event, NULL, false );
}

void RunLoop::postEvent( Event* event, EventHandler* handler, bool deleteHandler )
{
	peer_->postEvent( event, handler, deleteHandler );
}

uint32 RunLoop::addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds )
{
	Lock l(mutex_);
	return peer_->addTimer( mode, source, handler, timeoutInMilliSeconds );
}

uint32 RunLoop::addTimer( const String& mode, uint32 timeoutInMilliSeconds )
{
	Lock l(mutex_);
	return peer_->addTimer( mode, NULL, NULL, timeoutInMilliSeconds );
}


void RunLoop::removeTimer( uint32 timerID )
{
	Lock l(mutex_);
	peer_->removeTimer( timerID );
}

void RunLoop::internal_processTimer( const String& mode, 
									Object* source, 
									EventHandler* handler )
{
	String currentMode = getCurrentRunMode();

	if ( currentMode == mode ) {
		Event e( source, RunLoop::teTimedOut );
		
		if ( NULL != handler ) {
			handler->invoke( &e );
		}
		else {
			TimerEvents.fireEvent( &e );
		}
	}
}

void RunLoop::internal_executeOnce( const String& mode )
{
	doSources();
}

void RunLoop::internal_cancelled( const String& mode )
{	
	Lock l(mutex_);
	std::vector<RunLoopSource*>::iterator it = sources_.begin();
	while ( it != sources_.end() ) {
		(*it)->cancel();
		it ++;
	}	
}

void RunLoop::doSources()
{
	Lock l(mutex_);

	std::vector<RunLoopSource*>::iterator it = sources_.begin();
	while ( it != sources_.end() ) {
		(*it)->perform();
		it++;
	}
}

void RunLoop::internal_processReceivedEvent( PostedEvent* postedEvent )
{
	if ( NULL == postedEvent->handler_ ) {
		LoopEvents.fireEvent( postedEvent->event_ );
	}
	else {
		postedEvent->handler_->invoke( postedEvent->event_ );
	}

	if ( postedEvent->deleteHandler_ ) {
		delete postedEvent->handler_;
	}

	delete postedEvent->event_;
}


