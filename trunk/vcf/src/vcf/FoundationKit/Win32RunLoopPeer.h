#ifndef _VCF_WIN32RUNLOOPPEER_H__
#define _VCF_WIN32RUNLOOPPEER_H__



//Win32RunLoopPeer.h


/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/




#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/RunLoopPeer.h"

namespace VCF {

    class Win32RunLoopPeer : public RunLoopPeer {
    public:
        Win32RunLoopPeer( RunLoop* runLoop );

        virtual void run();
        virtual void stop();

        virtual void addTimer( RunLoopTimerPtr::Shared timer );
        virtual void removeTimer( RunLoopTimerPtr::Shared timer );

        virtual void addSource( RunLoopSourcePtr::Shared source );
        virtual void removeSource( RunLoopSourcePtr::Shared source );

    private:
        RunLoop* runLoop_;
        bool     done_;
        HANDLE   wakeUpEvent_;
        typedef std::map<HANDLE, SmartPtr<Procedure>::Shared> HandleCallBackMap;
        HandleCallBackMap handles_;
    };
}

/*
namespace VCF {
	class RunLoop;
	
	class Win32RunLoopPeer : public RunLoopPeer {
	public:

		Win32RunLoopPeer( RunLoop* runLoop );

		virtual ~Win32RunLoopPeer();
		
		virtual void run( const String& mode, const DateTime* duration );
		
		virtual void stop();
		
		virtual void postEvent( Event* event, RunLoopCallback* handler, bool deleteHandler );
		
		virtual OSHandleID getHandleID() {
			return NULL;	
		}

		virtual uint32 addTimer( const String& mode, Object* source, RunLoopCallback* handler, uint32 timeoutInMilliSeconds );
		
		virtual void removeTimer( uint32 timerID );
	protected:
		RunLoop* runLoop_;

		class TimerInfo {
		public:
			HANDLE timer;
			Object* source;
			RunLoopCallback* handler;
			String mode;
			DateTime startedAt;
		};

		bool handleMessageAndContinue( MSG& msg );

		void handleTimers( const String& mode );

		std::map<uint32,TimerInfo*> activeTimers_;

		void removeAll();
	};

};

*/
#endif //_VCF_WIN32RUNLOOPPEER_H__

/**
$Id$
*/
