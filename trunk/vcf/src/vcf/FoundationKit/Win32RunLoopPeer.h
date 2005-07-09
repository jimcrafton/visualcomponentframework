#ifndef _VCF_WIN32RUNLOOPPEER_H__
#define _VCF_WIN32RUNLOOPPEER_H__



//Win32RunLoopPeer.h


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/




#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/RunLoopPeer.h"


namespace VCF {
	class RunLoop;
	
	class Win32RunLoopPeer : public RunLoopPeer {
	public:

		Win32RunLoopPeer( RunLoop* runLoop );

		virtual ~Win32RunLoopPeer();
		
		virtual void run( const String& mode, const DateTime* duration );
		
		virtual void stop();
		
		virtual void postEvent( Event* event, EventHandler* handler, bool deleteHandler );
		
		virtual OSHandleID getHandleID() {
			return NULL;	
		}

		virtual uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds );
		
		virtual void removeTimer( uint32 timerID );
	protected:
		RunLoop* runLoop_;

		class TimerInfo {
		public:
			Object* source;
			EventHandler* handler;
			String mode;
			DateTime startedAt;
		};

		bool handleMessageAndContinue( MSG& msg );

		void handleTimers( const String& mode );

		std::map<HANDLE,TimerInfo*> activeTimers_;

		void removeAll();
	};

};


#endif //_VCF_WIN32RUNLOOPPEER_H__

