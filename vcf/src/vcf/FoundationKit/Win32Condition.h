#ifndef _VCF_WIN32CONDITION_H__
#define _VCF_WIN32CONDITION_H__
//Win32Condition.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


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
Class Win32Condition documentation
Part/most of the implementation for this class comes from
William E. Kempf's excellent condition class that is a
part of the Thread library in Boost. Any mistakes are almost
certainly mine in translating it.
*/
class Win32Condition : public VCF::Object, public ConditionPeer {
public:

	enum {
		MaxQueue = ((uint32)-1)/2
	};

	Win32Condition( Condition* condition );

	virtual ~Win32Condition();

	virtual int wait();

	virtual int wait( uint32 milliseconds );

	virtual void signal();

    virtual void broadcast();


	virtual OSHandleID getHandleID() {
		return (OSHandleID)queue_;
	}
protected:
	Condition* condition_;

	HANDLE gate_;
    HANDLE queue_;
	HANDLE mutex_;

	unsigned gone_;  // # threads that timed out and never made it to queue_
    uint32 blocked_; // # threads blocked on the condition
    unsigned waiting_; // # threads no longer waiting for the condition but
                        // still waiting to be removed from queue_
};


}; //end of namespace VCF


#endif // _VCF_WIN32CONDITION_H__

/**
$Id$
*/
