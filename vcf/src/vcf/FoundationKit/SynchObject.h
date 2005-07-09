#ifndef _VCF_SYNCHOBJECT_H__
#define _VCF_SYNCHOBJECT_H__
//SynchObject.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// SynchObject.h: interface for the SynchObject class.


namespace VCF
{

/**
*Class SynchObject documentation
Defines an abstract base class for synchronisation classes
like mutexes and semaphores, to be used with the lock class
*/

class FOUNDATIONKIT_API SynchObject : public VCF::Interface
{
public:
	virtual ~SynchObject(){};
	
	/**
	Attempts tp lock the SynchObject and will block
	indefinitely till a lock is achieved.
	*/
	virtual bool lock() = 0;
	
	/**
	Attempts tp lock the SynchObject and will block
	for timeoutInMilliseconds till a lock is achieved.
	*/
	virtual bool lock( uint32 timeoutInMilliseconds ) = 0;

	virtual bool unlock() = 0;
};
}; // end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
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
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.4  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.22.1  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SYNCHOBJECT_H__


