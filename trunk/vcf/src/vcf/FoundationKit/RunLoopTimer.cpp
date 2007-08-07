//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/RunLoopTimerPeer.h>
#include <vcf/FoundationKit/RunLoopTimer.h>

using namespace VCF;

RunLoopTimer::RunLoopTimer( const DateTime &fireDate )
{
    peer_.reset( SystemToolkit::createRunLoopTimerPeer( this ) );
    peer_->create( fireDate );
}

RunLoopTimer::RunLoopTimer( const DateTimeSpan &interval )
{
    peer_.reset( SystemToolkit::createRunLoopTimerPeer( this ) );
    peer_->create( interval );
}

RunLoopTimer::RunLoopTimer( const DateTime &fireDate, const DateTimeSpan &interval )
{
    peer_.reset( SystemToolkit::createRunLoopTimerPeer( this ) );
    peer_->create( fireDate, interval );
}

RunLoopTimer::~RunLoopTimer()
{
}

/**
$Id:$
*/
