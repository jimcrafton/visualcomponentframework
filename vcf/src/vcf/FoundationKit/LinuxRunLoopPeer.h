#ifndef _VCF_LINUXRUNLOOPPEER_H__
#define _VCF_LINUXRUNLOOPPEER_H__

//LinuxRunLoopPeer.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/RunLoopPeer.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/AtomicCount.h"

namespace VCF {
    class RunLoop;

    class LinuxRunLoopPeer : public RunLoopPeer {
    public:

        LinuxRunLoopPeer( RunLoop* runLoop );

        virtual ~LinuxRunLoopPeer();

        virtual void run( const DateTimeSpan* duration );
        virtual void stop();
        
        virtual bool isStopped() const;

        virtual void addTimer( RunLoopTimerPtr::Shared timer );
        virtual void removeTimer( RunLoopTimerPtr::Shared timer );

        virtual void addSource( RunLoopSourcePtr::Shared source );
        virtual void removeSource( RunLoopSourcePtr::Shared source );
        
	private:
		RunLoop* owner_;
		int      epollfd_;
		int      wakeupEventfd_;
		bool     done_;
		typedef std::map<int, SmartPtr<Procedure>::Shared> FileDescCallBackMap;
        FileDescCallBackMap callbackMap_;
    };
}

#endif //_VCF_LINUXRUNLOOPPEER_H__

/**
$Id$
*/

