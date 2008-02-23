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
		rlStopped,
		rlFinished
	};

	typedef Delegate1<RunLoopEvents> RunLoopDelegate;

    class FOUNDATIONKIT_API RunLoop {
    public:
		static const String DefaultMode;
		static const String SharedMode;

        ~RunLoop();

		RunLoopDelegate LoopEvents;

        void run( const String& mode=DefaultMode );

		void run( const DateTime& till, const String& mode=DefaultMode );

		void run( const DateTimeSpan& duration, const String& mode=DefaultMode );

        void stop( const String& mode=DefaultMode );
        
        void addTimer( RunLoopTimerPtr::Shared timer, const String& mode=DefaultMode );
        void removeTimer( RunLoopTimerPtr::Shared timer, const String& mode=DefaultMode );

        void addSource( RunLoopSourcePtr::Shared source, const String& mode=DefaultMode );
        void removeSource( RunLoopSourcePtr::Shared source, const String& mode=DefaultMode );
        
		void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true, const String& mode=DefaultMode );

		void postEvent( Procedure* callback, const bool& deleteHandler=true, const String& mode=DefaultMode );

		void clearAllTimers();

		void clearAllSources();

        class Creator;
    protected:

		friend class Creator;

        RunLoop( Thread* thread );
        
    private:
        RunLoopPeerPtr::Scoped peer_;
		std::map<String,RunLoopSourcePtr::Shared> postSources_;

        // Keep a copy of the sources/timers so that they don't get delete prematurely.
        std::vector<RunLoopTimerPtr::Shared>  timers_;
        std::vector<RunLoopSourcePtr::Shared> sources_;
    };


}

#endif //_VCF_RUNLOOP_H__

/**
$Id$
*/
