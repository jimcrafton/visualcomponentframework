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
#include "vcf/FoundationKit/AtomicCount.h"

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
		static void TimerNotifyHandler(sigval_t sigval);

	protected:
		RunLoop* runLoop_;

		class PostedEvents {
		public:
			Mutex                     mutex_;
			std::queue<PostedEvent*>  events_;
		} postedEvents_;

		class StopEvent {
		public:
			Mutex mutex_;
			bool  stop_;
		} stopEvent_;

		class TimerInfo {
		public:
			TimerInfo(Object *source, EventHandler *handler, const String &mode);
			timer_t       timer_;
			Object*       source_;
			EventHandler* handler_;
			String        mode_;
			DateTime      startedAt_;
			AtomicCount   fired_;
		};

		class TimerMap {
		public:
			typedef std::map<uint32, TimerInfo*>::iterator iterator;
			std::map<uint32, TimerInfo*> timers_;
			Mutex                        mutex_;
		} activeTimers_;

	};
};

#endif //_VCF_LINUXRUNLOOPPEER_H__

/**
$Id$
*/

