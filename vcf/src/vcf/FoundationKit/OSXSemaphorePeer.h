#ifndef _VCF_OSXSEMAPHOREPEER_H__
#define _VCF_OSXSEMAPHOREPEER_H__
//OSXSemaphorePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

/**
*Class MutexPeer documentation
*/
class OSXSemaphore : public SemaphorePeer {
public:

    OSXSemaphore( long initialCount, long maxCount );
	virtual ~OSXSemaphore();

	virtual bool lock();

	virtual bool unlock();

    /**
    on OSX this returns a MPSemaphoreID
    */
	virtual OSHandleID getHandleID() {
        return (OSHandleID) semaphoreID_;
    }

protected:
    MPSemaphoreID semaphoreID_;

};


}; // end of namespace VCF


 /**
*CVS Log info
 *$Log$
 *Revision 1.3  2005/01/08 20:52:47  ddiego
 *fixed some glitches in osx impl.
 *
 *Revision 1.2  2004/08/07 02:49:14  ddiego
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
 *Revision 1.3.2.1  2004/04/26 21:58:43  marcelloptr
 *changes for dir reorganization: _VCF_MACRO_H__
 *
 *Revision 1.3  2004/04/03 15:48:42  ddiego
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


#endif // _VCF_OSXSEMAPHOREPEER_H__


