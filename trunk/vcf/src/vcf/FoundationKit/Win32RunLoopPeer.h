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

#endif //_VCF_WIN32RUNLOOPPEER_H__

/**
$Id$
*/
