#ifndef _VCF_OSXCONDITIONPEER_H__
#define _VCF_OSXCONDITIONPEER_H__
//OSXConditionPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
Note this code is partially (mostly) based on the condition class
from the Boost Threads library by William Kempf.


Copyright (C) 2001-2003
William E. Kempf

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  William E. Kempf makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.
*/





namespace VCF  {

/**
Class OSXConditionPeer documentation
Part/most of the implementation for this class comes from
William E. Kempf's excellent condition class that is a
part of the Thread library in Boost. Any mistakes are almost
certainly mine in translating it.
*/
class OSXConditionPeer : public VCF::Object, public ConditionPeer {
public:

	enum {
		MaxQueue = ((unsigned long)-1)/2
	};

	OSXConditionPeer( Condition* condition );

	virtual ~OSXConditionPeer();

	virtual int wait();

	virtual int wait( uint32 milliseconds );

	virtual void signal();

    virtual void broadcast();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)mutex_;
	}
protected:
	Condition* condition_;

	MPSemaphoreID gate_;
    MPSemaphoreID queue_;
	MPCriticalRegionID mutex_;

	unsigned gone_;  // # threads that timed out and never made it to queue_
    unsigned long blocked_; // # threads blocked on the condition
    unsigned waiting_; // # threads no longer waiting for the condition but
                        // still waiting to be removed from queue_
};



}; //end of namespace VCF


#endif // _VCF_OSXCONDITIONPEER_H__

/**
$Id$
*/
