#ifndef _VCF_POSIXMUTEX_H__
#define _VCF_POSIXMUTEX_H__
//PosixMutex.h

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
*Class ConditionalPeer documentation
*/
class PosixMutex : public MutexPeer
{
public:

	PosixMutex();
	virtual ~PosixMutex();
	virtual bool lock();
	virtual bool unlock();
	virtual OSHandleID getHandleID() { return (OSHandleID)&mutex_; }

protected:

    pthread_mutex_t    mutex_;

};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2.4.1  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2.10.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/18 20:03:29  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.1.2.1  2003/02/12 19:35:54  catwallader
*Added PosixMutex class.
*
*/


#endif // _VCF_POSIXMUTEX_H__


