#ifndef _VCF_LINUXRUNLOOPPEER_H__
#define _VCF_LINUXRUNLOOPPEER_H__



//LinuxRunLoopPeer.h


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/RunLoop.h"
#include <queue>

namespace VCF {
	class RunLoop;
	
	class LinuxRunLoopPeer : public RunLoopPeer {
	public:

		LinuxRunLoopPeer( RunLoop* runLoop );

		virtual ~LinuxRunLoopPeer();

        
		virtual void run( const String& mode, const DateTime* duration );
		
		virtual void stop();
		
		virtual void postEvent( Event* event, EventHandler* handler, bool deleteHandler );
		
		virtual OSHandleID getHandleID() {
			return NULL;	
		}

		virtual uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds );
		
		virtual void removeTimer( uint32 timerID );


	protected:
		void handleTimers( const String& mode );

		static void TimerSignalHandler(int sig, siginfo_t *extra, void*);
		class TimerSignalInstaller;
		friend class TimerSignalInstaller;
	protected:
		RunLoop* runLoop_;

		class PostedEvents {
		public:
			Mutex                     mutex;
			std::queue<PostedEvent*>  events;
		} postedEvents_;

		class StopEvent {
		public:
			Mutex mutex;
			bool  stop;
		} stopEvent_;

		class TimerInfo {
		public:
			timer_t       timer;
			Object*       source;
			EventHandler* handler;
			String        mode;
			DateTime      startedAt;
			bool          fired;
		};

		class TimerMap {
		public:
			typedef std::map<uint32, TimerInfo*>::iterator iterator;
			std::map<uint32, TimerInfo*> timers;
			Mutex                        mutex;
		} activeTimers_;

	};
};

#endif //_VCF_LINUXRUNLOOPPEER_H__

