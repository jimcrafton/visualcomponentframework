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
    : peer_( SystemToolkit::createRunLoopPeer( this ) )
{
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
    peer_->addTimer( timer );
}

void RunLoop::addSource( RunLoopSourcePtr::Shared source )
{
    peer_->addSource( source );
}

/**
$Id$
*/
