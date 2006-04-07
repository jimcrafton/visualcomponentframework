#ifndef _VCF_OSXRUNLOOPPEER_H__
#define _VCF_OSXRUNLOOPPEER_H__



//OSXRunLoopPeer.h


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
	
	class OSXRunLoopPeer : public RunLoopPeer {
	public:

		OSXRunLoopPeer( RunLoop* runLoop );

		virtual ~OSXRunLoopPeer();
		
		virtual void run( const String& mode, const DateTime* duration );
		
		virtual void stop();
		
		virtual void postEvent( Event* event, EventHandler* handler, bool deleteHandler );
		
		virtual OSHandleID getHandleID();

		virtual uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds );
		
		virtual void removeTimer( uint32 timerID );
	protected:
		RunLoop* runLoop_;
		CFRunLoopSourceRef runLoopSrc_;

		class TimerInfo {
		public:
			Object* source;
			EventHandler* handler;
			String mode;
			DateTime startedAt;
		};

		void removeAll();

		static void SrcScheduleCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode );
		static void SrcCancelCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode );
		static void SrcPerformCallBack ( void *info );
		static void TimerCallBack ( CFRunLoopTimerRef timer,  void *info );
	};

};


#endif //_VCF_OSXRUNLOOPPEER_H__


