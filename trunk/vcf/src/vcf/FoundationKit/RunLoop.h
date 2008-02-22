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
        
	enum RunLoopEvents {
		rlStarted = 0,
		rlSourceFired,
		rlTimerFired,
		rlStopped
	};

	typedef Delegate1<RunLoopEvents> RunLoopDelegate;

    class FOUNDATIONKIT_API RunLoop {
    public:
        ~RunLoop();

		RunLoopDelegate LoopEvents;

        void run();

		void run( const DateTime& till );

		void run( const DateTimeSpan& duration );

        void stop();
        
        void addTimer( RunLoopTimerPtr::Shared timer );
        void removeTimer( RunLoopTimerPtr::Shared timer );

        void addSource( RunLoopSourcePtr::Shared source );
        void removeSource( RunLoopSourcePtr::Shared source );
        
		void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true );

        class Creator;
    protected:

		friend class Creator;

        RunLoop( Thread* thread );
        
    private:
        RunLoopPeerPtr::Scoped peer_;
		RunLoopSourcePtr::Shared postEventSource_;

        // Keep a copy of the sources/timers so that they don't get delete prematurely.
        std::vector<RunLoopTimerPtr::Shared>  timers_;
        std::vector<RunLoopSourcePtr::Shared> sources_;
    };


}

#endif //_VCF_RUNLOOP_H__

/**
$Id$
*/
