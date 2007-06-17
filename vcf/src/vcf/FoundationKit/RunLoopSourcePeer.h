#ifndef _VCF_RUNLOOPSOURCEPEER_H__
#define _VCF_RUNLOOPSOURCEPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//


namespace VCF {
    class FOUNDATIONKIT_API RunLoopSourcePeer {
    public:
        RunLoopSourcePeer( RunLoopSource* source );
        virtual ~RunLoopSourcePeer();
        
        virtual void fire() = 0;
        
    protected:
        void doPerform();
        void doCancel();
        
    protected:
        RunLoopSource *owner_;
    };
    
    inline RunLoopSourcePeer::RunLoopSourcePeer( RunLoopSource* source )
        : owner_( source )
    {
    }
    
    inline RunLoopSourcePeer::~RunLoopSourcePeer()
    {
    }
}

#endif
