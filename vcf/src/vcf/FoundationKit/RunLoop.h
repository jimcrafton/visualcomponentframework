#ifndef _VCF_RUNLOOP_H__
#define _VCF_RUNLOOP_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include <vcf/FoundationKit/RunLoopFwd.h>

namespace VCF {
        
    class FOUNDATIONKIT_API RunLoop {
    public:
        ~RunLoop();
        
        void run();
        void stop();
        
        void addTimer( RunLoopTimerPtr::Shared timer );
        void removeTimer( RunLoopTimerPtr::Shared timer );

        void addSource( RunLoopSourcePtr::Shared source );
        void removeSource( RunLoopSourcePtr::Shared source );
        
        class Creator;
    protected:
        RunLoop( Thread* thread );
        
    private:
        RunLoopPeerPtr::Scoped peer_;

        // Keep a copy of the sources/timers so that they don't get delete prematurely.
        std::vector<RunLoopTimerPtr::Shared>  timers_;
        std::vector<RunLoopSourcePtr::Shared> sources_;
    };


}

#endif //_VCF_RUNLOOP_H__

/**
$Id$
*/
