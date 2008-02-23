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
#include <deque>

namespace VCF {	

    class Win32RunLoopPeer : public RunLoopPeer {
    public:
        Win32RunLoopPeer( RunLoop* runLoop );
		virtual ~Win32RunLoopPeer();

        virtual void run( const DateTimeSpan* duration, const String& mode );
        virtual void stop( const String& mode );

        virtual bool isStopped(const String& mode) const;

        virtual void addTimer( RunLoopTimerPtr::Shared timer, const String& mode );
        virtual void removeTimer( RunLoopTimerPtr::Shared timer, const String& mode );

        virtual void addSource( RunLoopSourcePtr::Shared source, const String& mode );
        virtual void removeSource( RunLoopSourcePtr::Shared source, const String& mode );

    private:	

		typedef std::map<HANDLE, SmartPtr<Procedure>::Shared> HandleCallBackMap;
		typedef std::deque<bool> DoneStack;

		class ModeInfo {
		public:

			ModeInfo();

			HandleCallBackMap handles;
			DoneStack done;
			HANDLE wakeUpEvent;
		};


		typedef std::map<String,ModeInfo*> ModeMap;

		ModeInfo* initRun(const String& mode);


        RunLoop* runLoop_;
		ModeMap modes_;
		HandleCallBackMap sharedHandles_;
		
    };
}

#endif //_VCF_WIN32RUNLOOPPEER_H__

/**
$Id$
*/
