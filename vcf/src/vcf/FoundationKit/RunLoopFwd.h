
#ifndef _VCF_RUNLOOPFWD_H__
#define _VCF_RUNLOOPFWD_H__

/*
 Copyright 2007 The VCF Project, Orhun Birsoy
 Please see License.txt in the top level directory
 where you installed the VCF.
*/

#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
    
    class RunLoopTimer;
    class RunLoopTimerPeer;
    typedef SmartPtr<RunLoopTimer>     RunLoopTimerPtr;
    typedef SmartPtr<RunLoopTimerPeer> RunLoopTimerPeerPtr;
    
    class RunLoopSource;
    class RunLoopSourcePeer;
    typedef SmartPtr<RunLoopSource>     RunLoopSourcePtr;
    typedef SmartPtr<RunLoopSourcePeer> RunLoopSourcePeerPtr;
  
    class RunLoop;
    class RunLoopPeer;
    typedef SmartPtr<RunLoop> RunLoopPtr;
    typedef SmartPtr<RunLoopPeer> RunLoopPeerPtr;
}


#endif

/**
$Id$
*/
