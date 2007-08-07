#ifndef _VCF_LINUXRUNLOOPTIMERPEER_H__
#define _VCF_LINUXRUNLOOPTIMERPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopTimerPeer.h>

namespace VCF {

    class FOUNDATIONKIT_API LinuxRunLoopTimerPeer : public RunLoopTimerPeer {
    public:
        LinuxRunLoopTimerPeer( RunLoopTimer* owner );
        virtual ~LinuxRunLoopTimerPeer();

        virtual void create( const DateTime &fireDate );
        virtual void create( const DateTimeSpan &interval );
        virtual void create( const DateTime &fireDate, const DateTimeSpan &interval );

        int  getFileDesc();
        void perform();

    private:
        RunLoopTimer *owner_;
        int           fileDesc_;        
    };

    inline int LinuxRunLoopTimerPeer::getFileDesc()
    {
        return fileDesc_;
    }
}

#endif

/**
$Id:$
*/
