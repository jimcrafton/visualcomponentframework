#ifndef _VCF_OSXRUNLOOPSOURCEPEER_H__
#define _VCF_OSXRUNLOOPSOURCEPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopSourcePeer.h>

namespace VCF {
    
    class FOUNDATIONKIT_API OSXRunLoopSourcePeer : public RunLoopSourcePeer {
    public:
        OSXRunLoopSourcePeer( RunLoopSource* source );
        virtual ~OSXRunLoopSourcePeer();
        
        CFRunLoopSourceRef getSource();
        
        virtual void signal();
        
    private:
        static void CancelCallBack( void *info, CFRunLoopRef rl, CFStringRef mode );
        static void PerformCallBack( void *info );
        
    private:
        RunLoopSource     *owner_;
        CFRunLoopSourceRef sourceRef_;
    };
    
    inline CFRunLoopSourceRef OSXRunLoopSourcePeer::getSource()
    {
        return sourceRef_;
    }
}

#endif

/**
$Id$
*/
