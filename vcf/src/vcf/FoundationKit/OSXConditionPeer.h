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
		return (OSHandleID)0;
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


 /**
*CVS Log info
 *$Log$
 *Revision 1.3  2005/01/08 20:52:47  ddiego
 *fixed some glitches in osx impl.
 *
 *Revision 1.2  2004/08/07 02:49:13  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
 *This checks in a bunch of changes to the FoundationKit for OSX
 *porting. The thread, mutex, semaphor, condition, and file peers
 *have all been implemented and tested. The file peer could be improved
 *and needs search functionality. The locale peer is only partially
 *complete, but the functions will return values. The unicode transition
 *is also finished and works OK now.
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.3.2.1  2004/04/26 21:58:42  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:41  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.2.6.1  2004/02/21 03:27:06  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/05/17 20:37:12  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:01  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


#endif // _VCF_OSXCONDITIONPEER_H__


