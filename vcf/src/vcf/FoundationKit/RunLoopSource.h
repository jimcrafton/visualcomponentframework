#ifndef _VCF_RUNLOOPSOURCE_H__
#define _VCF_RUNLOOPSOURCE_H__



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

    class FOUNDATIONKIT_API RunLoopSource {
    public:
        RunLoopSource();
        virtual ~RunLoopSource(); 
        
        void setRunLoop( RunLoop* runLoop );
        void fire();
        
        RunLoopSourcePeerPtr::Shared getPeer();
        
    protected:
        friend class RunLoopSourcePeer;
        void perform();
        void cancel();

        virtual void performImpl() = 0;
        virtual void cancelImpl() = 0;
        
    private:
        RunLoopSourcePeerPtr::Shared peer_;
    };
    
    inline RunLoopSourcePeerPtr::Shared RunLoopSource::getPeer()
    {
        return peer_;
    }

}

#endif //_VCF_RUNLOOPSOURCE_H__

/**
$Id$
*/
