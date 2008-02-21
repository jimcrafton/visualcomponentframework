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
#include <vcf/FoundationKit/RunLoopSourcePeer.h>

namespace VCF {

    class FOUNDATIONKIT_API RunLoopSource {
    public:
        RunLoopSource();
        virtual ~RunLoopSource(); 
        
        void setRunLoop( RunLoop* runLoop );
        void signal();
        
        RunLoopSourcePeerPtr::Shared getPeer();

        void internal_perform();
        void internal_cancel();
    protected:

        virtual void perform() = 0;
        virtual void cancel() = 0;
        
    private:
        RunLoopSourcePeerPtr::Shared peer_;
    };
    
    inline RunLoopSourcePeerPtr::Shared RunLoopSource::getPeer()
    {
        return peer_;
    }

    inline void RunLoopSource::signal()
    {
        peer_->signal();
    }

}

#endif //_VCF_RUNLOOPSOURCE_H__

/**
$Id$
*/
