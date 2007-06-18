#ifndef _VCF_RUNLOOPTIMER_H__
#define _VCF_RUNLOOPTIMER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopFwd.h>

namespace VCF {
    
    class FOUNDATIONKIT_API RunLoopTimer {
    public:
        RunLoopTimer( const DateTime &fireDate );
        RunLoopTimer( const DateTimeSpan &interval );
        RunLoopTimer( const DateTime &fireDate, const DateTimeSpan &interval );
        
        ~RunLoopTimer();
        
        Delegate1<RunLoopTimer&> TimerFired;
        
        bool doesRepeat() const;
        DateTimeSpan getInterval() const;
        DateTime getNextFireDate() const;
        void invalidate();
        bool isValid() const;
        
        RunLoopTimerPeerPtr::Shared getPeer();
        
    private:
        RunLoopTimerPeerPtr::Shared peer_;
    };
    
    inline RunLoopTimerPeerPtr::Shared RunLoopTimer::getPeer()
    {
        return peer_;
    }
        
}

#endif
