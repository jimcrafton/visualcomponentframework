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

	/**
	\class RunLoop RunLoop.h "vcf/FoundationKit/RunLoop.h"
	The RunLoop class is used to create an instance of an OS
	event queue. This can then be run and you can post events
	to it, or add a timer, or some other source of notification.

	The idea behind this is neither new or original. In our
	case we have \em heavily borrowed upon Apple's 
	CFRunLoop, so you may want to check their documentation
	here:
	http://developer.apple.com/documentation/CoreFoundation/Reference/CFRunLoopRef/Reference/reference.html

	You never create a RunLoop. Instead you get access to it 
	through the ThreadManager's getCurrentRunLoop() function
	which will return the RunLoop for the thread that's running
	when the call was made. Also you can get the run loop
	from a valid, running thread instance.
	*/
    class FOUNDATIONKIT_API RunLoop {
    public:
		static const String DefaultMode;
		static const String SharedMode;

        ~RunLoop();

		RunLoopDelegate LoopEvents;

		/**
		starts the run loop running. it will keep 
		running till you call stop().
		*/
        void run( const String& mode=DefaultMode );

		/**
		Run the run loop till the current time hits the passed
		in date time value.
		@param DateTime the time to run the loop till.
		*/
		void run( const DateTime& till, const String& mode=DefaultMode );

		/**
		Runs the run loop for the specified duration.
		*/
		void run( const DateTimeSpan& duration, const String& mode=DefaultMode );

		/**
		Stops the run loop
		*/
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
