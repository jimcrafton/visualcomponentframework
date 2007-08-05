#ifndef _VCF_LINUXRUNLOOPSOURCEPEER_H__
#define _VCF_LINUXRUNLOOPSOURCEPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopSourcePeer.h>
#include <vcf/FoundationKit/RunLoopSource.h>

namespace VCF {

    class FOUNDATIONKIT_API LinuxRunLoopSourcePeer : public RunLoopSourcePeer {
    public:
        LinuxRunLoopSourcePeer( RunLoopSource* source );
        virtual ~LinuxRunLoopSourcePeer();

        virtual void fire();

        int  getFileDesc();
        void perform();

    private:
        int            fileDesc_;
        RunLoopSource* owner_;
    };

    inline int LinuxRunLoopSourcePeer::getFileDesc()
    {
        return fileDesc_;
    }
}

#endif
