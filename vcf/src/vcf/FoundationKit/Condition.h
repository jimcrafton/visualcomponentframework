#ifndef _VCF_CONDITION_H__
#define _VCF_CONDITION_H__
//Condition.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ConditionPeer;

/**
\par
The Condition object is used as a synchronization primitive, like the Mutex, and
Semaphore. While the Mutex and Semaphore can cause multiple threads to block, waiting
for the mutex or semaphore to become signaled, only one thread will every wake at
any given moment. In contrast, a Condition can be used to wake up a series of threads
all waiting on the condition.
\par The Condition class follows the same pattern that the Pthreads condition variable
uses, or the <a href="http://boost.org/libs/thread/doc/condition.html">
Boost condition class</a>. In fact, the Win32 implementation is written largely
based of off the excellent code in the Boost condition class that was written by
<a href="http://boost.org/people/william_kempf.htm">William Kempf</a>.
*/
class FOUNDATIONKIT_API Condition : public Object, public Waitable
{
public:


    /**
	Every condtion must be associated with a mutex
	*/
	Condition( Mutex* mutex );

	virtual ~Condition();

    /**
	Signal one waiting thread that condition is true.
	*/
    void signal();

    /* Signal all waiting threads that condition is TRUE */
    virtual void broadcast();

    /* Returns pointer to peer implementation */
	ConditionPeer* getPeer() {
		return peer_;
	}

	/**
	Wait forever until the condition is signaled. The thread that calls this will block
	till the condition is signaled. If the wait fails the method will return
	Waitable::wrFail
	*/
	virtual Waitable::WaitResult wait();

	/**
	Wait for a maximum number of milliseconds until the condition is signaled.
	The thread that calls this will block till the condition is signaled. If the
	condition is signaled before the timeout period is ellapsed the function will
	return Waitable::wrTimeout value.
	*/
	Waitable::WaitResult wait( uint32 milliseconds );

	OSHandleID getPeerHandleID();

	/**
	Returns the mutex associated with the condition.
	*/
	Mutex* getMutex() {
		return mutex_;
	}
protected:
	Mutex* mutex_;
	ConditionPeer* peer_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.2.4.1  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5.2.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.4.2.3  2004/03/12 04:05:30  ddiego
*minor documentation for condition stuff
*
*Revision 1.4.2.2  2004/03/11 22:19:59  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.4.2.1  2004/02/19 04:52:35  ddiego
*more progress made with TableControl
*
*Revision 1.4  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.3  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:11:49  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/18 20:04:38  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*/


#endif // _VCF_CONDITION_H__


