#ifndef _VCF_RUNLOOPPEER_H__
#define _VCF_RUNLOOPPEER_H__


/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/RunLoopFwd.h"

namespace VCF {
    
    class FOUNDATIONKIT_API RunLoopPeer {
    public:
        virtual ~RunLoopPeer();
        
        virtual void run() = 0;
        virtual void stop() = 0;
        
        virtual bool isStopped() const = 0;

        virtual void addTimer( RunLoopTimerPtr::Shared timer ) = 0;
        virtual void removeTimer( RunLoopTimerPtr::Shared timer ) = 0;

        virtual void addSource( RunLoopSourcePtr::Shared source ) = 0;
        virtual void removeSource( RunLoopSourcePtr::Shared source ) = 0;
    };
    
    inline RunLoopPeer::~RunLoopPeer()
    {
    }
}

#endif //_VCF_RUNLOOPPEER_H__

/**
$Id$
*/
