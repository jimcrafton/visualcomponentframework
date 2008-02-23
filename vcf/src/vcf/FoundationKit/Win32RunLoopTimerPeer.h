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
        virtual ~Win32RunLoopTimerPeer();

        virtual void create( const DateTime &fireDate );
        virtual void create( const DateTimeSpan &interval );
        virtual void create( const DateTime &fireDate, const DateTimeSpan &interval );

		virtual bool isActive() const {
			return active_;
		}

		virtual void setActive( const bool& val );

		virtual bool doesRepeat() const;
        virtual DateTimeSpan getInterval() const;
        virtual DateTime getNextFireDate() const;

        HANDLE getHandle();
        void perform();

    private:
        HANDLE        timer_;
        RunLoopTimer *owner_;
		bool active_;
		LARGE_INTEGER dueTime_;
		LONG periodicInterval_;
		DateTime lastFire_;

    };

    inline HANDLE Win32RunLoopTimerPeer::getHandle()
    {
        return timer_;
    }
}

#endif

/**
$Id$
*/
