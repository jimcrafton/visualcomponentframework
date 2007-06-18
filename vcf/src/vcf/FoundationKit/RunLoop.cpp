//RunLoop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/RunLoopSource.h"

using namespace VCF;

RunLoop::RunLoop( Thread* thread ) 
{
    peer_.reset(SystemToolkit::createRunLoopPeer(this));
    if ( peer_ == NULL ) {
        throw NoPeerFoundException();
    }
}

RunLoop::~RunLoop()
{
}

void RunLoop::run()
{
    peer_->run();
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
    std::vector<RunLoopTimerPtr::Shared>::iterator it = std::find(timers_.begin(), timers_.end(), timer);
    if( it != timers_.end() ) {
        peer_->removeTimer( timer );
        timers_.erase(it);
    }
}

void RunLoop::addSource( RunLoopSourcePtr::Shared source )
{
    sources_.push_back( source );
    peer_->addSource( source );
}

void RunLoop::removeSource( RunLoopSourcePtr::Shared source )
{
    std::vector<RunLoopSourcePtr::Shared>::iterator it = std::find(sources_.begin(), sources_.end(), source);
    if( it != sources_.end() ) {
        peer_->removeSource( source );
        source->internal_cancel();
        sources_.erase(it);
    }
}

/**
$Id$
*/
