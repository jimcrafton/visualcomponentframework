#ifndef _VCF_THREADPEER_H__
#define _VCF_THREADPEER_H__
//ThreadPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

/**
*@interface ThreadPeer
*Basic Thread interface to wrap native thread OS calls.
*
*@author Jim Crafton
*@version 1.0
*/
class FOUNDATIONKIT_API ThreadPeer
{
public:
	virtual ~ThreadPeer() {}

	/**
	*Starts (or resumes) a thread running.
	*/
	virtual bool start() = 0;

	/**
	*gracefully stops the thread and shuts it down, releasing
	*any OS resources associated with the thread
	*/
	virtual void stop() = 0;

	/**
	*causes the thread the thread to sleep for the specified number of
	*milliseconds
	*@param uint32 - the number of milliseconds to sleep
	*/
	virtual void sleep( uint32 milliseconds ) = 0;

	/**
	*returns the thread associated with this thread of execution
	*/
	virtual uint32 getThreadID() = 0;

	/**
	*returns the process ID that this thread is part of
	*/
	virtual uint32 getOwningProcessID() = 0;

	/**
	*returns a handle ID for the thread. It's use and signifigance
	*are platform specific. On Win32 systems this is the HANDLE
	*returned by the CreateThread/_beginthreadex() calls
	*/
	virtual uint32 getHandleID() = 0;

	virtual bool isActive() = 0;

	virtual int wait() = 0;

	virtual int wait( uint32 milliseconds ) = 0;
};



};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.11.2.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.10.2.2  2004/03/11 22:19:58  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.10.2.1  2004/02/19 04:52:34  ddiego
*more progress made with TableControl
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.4  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9.4.3  2003/08/23 02:01:28  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.9.4.2  2003/08/14 01:13:31  ddiego
*added the Thread::pause method back
*
*Revision 1.9.4.1  2003/08/13 21:43:01  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.9  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/23 03:23:49  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.12.2  2003/02/18 20:02:17  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.7.12.1  2003/02/06 00:21:33  catwallader
*Added thread methods: isActive(), isDetached(), join(), exit(), yield() and detach().  Fleshed out PosixThread::stop().
*
*Revision 1.7  2002/06/25 01:25:21  ddiego
*added some fixes and documentation to the Thread class
*also added methods to allow for getting the peer classes on the
*Thread, Semeaphore, and Mutex classes. added peer methods for
*retrieving the handleID for a thread,semaphore, or mutex
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_THREADPEER_H__


