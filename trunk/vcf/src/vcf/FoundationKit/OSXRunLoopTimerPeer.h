#ifndef _VCF_OSXRUNLOOPTIMERPEER_H__
#define _VCF_OSXRUNLOOPTIMERPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/RunLoopTimerPeer.h>

namespace VCF {
    
    class FOUNDATIONKIT_API OSXRunLoopTimerPeer : public RunLoopTimerPeer {
    public:
        OSXRunLoopTimerPeer( RunLoopTimer* timer );
        ~OSXRunLoopTimerPeer();

        CFRunLoopTimerRef getTimer();
        
        virtual void create( const DateTime &fireDate );
        virtual void create( const DateTimeSpan &interval );
        virtual void create( const DateTime &fireDate, const DateTimeSpan &interval );
        
		virtual bool isActive() const;
		virtual void setActive( const bool& val );

		virtual bool doesRepeat() const;
        virtual DateTimeSpan getInterval() const;
        virtual DateTime getNextFireDate() const;
    private:
        static void TimerCallback( CFRunLoopTimerRef timer, void *info );
        
    private:
        RunLoopTimer     *owner_;
        CFRunLoopTimerRef timerRef_;
    };
    
    inline CFRunLoopTimerRef OSXRunLoopTimerPeer::getTimer()
    {
        return timerRef_;
    }
    
}

#endif

/**
$Id$
*/
