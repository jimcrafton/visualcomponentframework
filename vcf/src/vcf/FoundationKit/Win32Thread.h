#ifndef _VCF_WIN32THREAD_H__
#define _VCF_WIN32THREAD_H__
//Win32Thread.h

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

class Thread;

class Win32Thread : public ThreadPeer  {
public:
	Win32Thread( Thread* thread );

	virtual ~Win32Thread();

	virtual bool start();

	virtual void stop();

	static unsigned __stdcall threadProc( void* param );

	virtual void sleep( unsigned int milliseconds );

	virtual uint32 getThreadID(){
		return threadID_;
	}

	virtual unsigned int getOwningProcessID()	{
		return owningProcessID_;
	}

	virtual uint32 getHandleID() {
		return threadHandle_;
	}

	virtual bool isActive() {
		return active_;
	}

	virtual int wait();

	virtual int wait( uint32 milliseconds );
private:
	unsigned threadID_;
	unsigned owningProcessID_;
	unsigned initFlags_;
	void* security_;
	unsigned stackSize_;
	uint32 threadHandle_;
	Thread* thread_;
	bool active_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/05 01:55:21  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.12.2.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.2.2  2004/03/11 22:19:58  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.11.2.1  2004/02/19 04:52:34  ddiego
*more progress made with TableControl
*
*Revision 1.11  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.3  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.10.4.2  2003/08/14 01:13:31  ddiego
*added the Thread::pause method back
*
*Revision 1.10.4.1  2003/08/13 21:43:01  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.10  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.14.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.14.1  2003/03/12 03:11:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2002/06/25 01:25:28  ddiego
*added some fixes and documentation to the Thread class
*also added methods to allow for getting the peer classes on the
*Thread, Semeaphore, and Mutex classes. added peer methods for
*retrieving the handleID for a thread,semaphore, or mutex
*
*Revision 1.8  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32THREAD_H__


