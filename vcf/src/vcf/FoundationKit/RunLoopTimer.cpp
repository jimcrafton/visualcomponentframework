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

//bool
//RunLoopTimer::doesRepeat() const
//{
//    return false;
//}
//
//DateTimeSpan
//RunLoop::Timer::getInterval() const
//{
//    DateTimeSpan dts;
//    return dts;
//}
//
//DateTime 
//RunLoop::Timer::getNextFireDate() const
//{
//    DateTime dt;
//    return dt;
//}
//
//void 
//RunLoop::Timer::invalidate()
//{
//}
//
//bool 
//RunLoop::Timer::isValid() const
//{
//    return false;
//}
//
//RunLoop::Timer::Peer*
//RunLoop::Timer::getPeer()
//{
//    return peer_.get();
//}
