#ifndef _VCF_WIN32RUNLOOPTIMERPEER_H__
#define _VCF_WIN32RUNLOOPTIMERPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopTimerPeer.h>

namespace VCF {
    
    class FOUNDATIONKIT_API Win32RunLoopTimerPeer : public RunLoopTimerPeer {
    public:
        Win32RunLoopTimerPeer( RunLoopTimer* owner );
        ~Win32RunLoopTimerPeer();
        
        virtual void create( const DateTime &fireDate );
        virtual void create( const DateTimeSpan &interval );
        virtual void create( const DateTime &fireDate, const DateTimeSpan &interval );        

        HANDLE getHandle();
        void perform();
    
    private:
        HANDLE        timer_;
        RunLoopTimer *owner_;
    };    

    inline HANDLE Win32RunLoopTimerPeer::getHandle()
    {
        return timer_;
    }
}

#endif
