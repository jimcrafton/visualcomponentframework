#ifndef _VCF_LOCK_H__
#define _VCF_LOCK_H__
//Lock.h

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
\class Lock Lock.h "vcf/FoundationKit/Lock.h"
The Lock class represents a way to automatically lock or unlock a 
syncronizeable primitive, like a thread, mutex, or semaphore, by 
having the lifetime of the Lock stack based. This frees the 
developer from having to remember to call lock or unlock on the
sync object. For example:
\code
Mutex* mutex = //get a mutex
Lock l( *mutex );
//do some operations on a shared resource
\endcode
When the lock instance falls off of the stack, and it's destructor is called,
and the sync object's unlock method will be called.
@see SynchObject
@author Tiziano Franzoi, Nov 15, 2001
*/
class FOUNDATIONKIT_API Lock :public VCF::Object
{
public:
	Lock( VCF::SynchObject& synchObject ):synchObject_(synchObject)
	{
		validSynchObject_ = synchObject_.lock();
	}


	virtual ~Lock()
	{
		if( true == validSynchObject_ )
		{
			synchObject_.unlock();
		}
	}
protected:
	bool validSynchObject_;
	VCF::SynchObject& synchObject_;

private:
	/**
	* we forbid to copy a lock, as it would probably
	* cause some trouble.
	* Plus it would be impossible to define an explicit 
	* assignment operator with a reference. With this
	* the CodeWarrior doesn't complain anymore.
	*/
	Lock& operator = ( const Lock& lock ) { return *this; };

};
} // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.4  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.4  2005/05/15 23:17:39  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.4.3  2004/12/20 23:49:02  marcelloptr
*forbidden assignment operator for the Lock class
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.6  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.16.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.16.1  2003/03/12 03:11:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.4  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LOCK_H__


