#ifndef _VCF_OSXRUNLOOPPEER_H__
#define _VCF_OSXRUNLOOPPEER_H__

//OSXRunLoopPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include <vcf/FoundationKit/RunLoopPeer.h>

namespace VCF {
    
    class OSXRunLoopPeer : public RunLoopPeer {
    public:
        OSXRunLoopPeer( RunLoop* runLoop );
        
        virtual void run();
        virtual void stop();
        virtual void addTimer( RunLoopTimerPtr::Shared timer );
        virtual void removeTimer( RunLoopTimerPtr::Shared timer );
        virtual void addSource( RunLoopSourcePtr::Shared source );
        virtual void removeSource( RunLoopSourcePtr::Shared source );
        
    private:
        RunLoop*     runLoop_;
        CFRunLoopRef runLoopRef_;
    };
}

//#include <set>
//#include "vcf/FoundationKit/RunLoopPeer.h"
//
//
//namespace VCF {
//	class RunLoop;
//	
//	class OSXRunLoopPeer : public RunLoopPeer {
//	public:
//
//		OSXRunLoopPeer( RunLoop* runLoop );
//
//		virtual ~OSXRunLoopPeer();
//		
//		virtual void run( const String& mode, const DateTime* duration );
//		
//		virtual void stop();
//		
//		virtual void postEvent( Event* event, EventHandler* handler, bool deleteHandler );
//		
//		virtual OSHandleID getHandleID();
//
//		virtual uint32 addTimer( const String& mode, Object* source, EventHandler* handler, uint32 timeoutInMilliSeconds );
//		
//		virtual void removeTimer( uint32 timerID );
//        
//        virtual void addSource( RunLoopSource* source );
//        
//        virtual void removeSource( RunLoopSource* source );
//        
//	protected:
//		RunLoop* runLoop_;
//
//        class TimerInfo;
//        typedef SmartPtr<TimerInfo> TimerInfoPtr; 
//        typedef std::map<CFRunLoopTimerRef, TimerInfoPtr::Shared> TimerInfoSet;
//        TimerInfoSet timerInfoSet_;
//        
//        typedef std::map<RunLoopSource*, CFRunLoopSourceRef> SourceMap;
//        SourceMap sourceMap_;
//        
//        class EventInfo;
//        EventInfo *eventInfo_;
//        CFRunLoopSourceRef eventSource_;
//        
//       	CFRunLoopRef runLoopRef_;
//
//		void removeAll();
//
//		static void SrcScheduleCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode );
//		static void SrcCancelCallBack ( void *info,  CFRunLoopRef rl, CFStringRef mode );
//		static void SrcPerformCallBack ( void *info );
//        static void TimerCallBack ( CFRunLoopTimerRef timer,  void *info );
//        static void EventPerformCallBack( void *info );
//	};
//
//};


#endif //_VCF_OSXRUNLOOPPEER_H__

/**
$Id$
*/
