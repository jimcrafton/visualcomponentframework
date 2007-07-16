#ifndef _VCF_WIN32RUNLOOPSOURCEPEER_H__
#define _VCF_WIN32RUNLOOPSOURCEPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopSourcePeer.h>
#include <vcf/FoundationKit/RunLoopSource.h>

namespace VCF {
    
    class FOUNDATIONKIT_API Win32RunLoopSourcePeer : public RunLoopSourcePeer {
    public:
        Win32RunLoopSourcePeer( RunLoopSource* source );
        virtual ~Win32RunLoopSourcePeer();
        
        virtual void fire();

        HANDLE getHandle();
        void perform();
    
    private:
        HANDLE         source_;
        RunLoopSource* owner_;
    };    

    inline void Win32RunLoopSourcePeer::perform()
    {
        owner_->internal_perform();
        ::ResetEvent(source_);
    }

    inline HANDLE Win32RunLoopSourcePeer::getHandle()
    {
        return source_;
    }
}

#endif
