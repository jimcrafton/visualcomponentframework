#ifndef _VCF_LINUXSEMAPHOREPEER_H__
#define _VCF_LINUXSEMAPHOREPEER_H__ 
//LinuxSemaphorePeer.h



/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

// LinuxSemaphorePeer.h: interface for the LinuxSemaphorePeer class.

namespace VCF
{

/**
*Class LinuxSemaphorePeer documentation
Implements the base SemaphorePeer class
used for synchronizing access to threaded
resources
*/ 
/**
*Class LinuxSemaphorePeer
*@author Jim Crafton, May 26 2002
*/
class LinuxSemaphorePeer : public VCF::Object, public VCF::SemaphorePeer
{
public:
	LinuxSemaphorePeer( long initialCount , long maxCount );

	virtual ~LinuxSemaphorePeer();

	virtual bool lock();

    virtual bool lock( uint32 timeoutInMilliseconds );

	virtual bool unlock();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)&semaphore_;
	}
	
protected:
	sem_t semaphore_;

};

} // end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.4.2.1  2005/11/10 00:04:08  obirsoy
*changes required for gcc under Linux.
*
*Revision 1.4  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2.4.1  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.10.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.10.1  2003/03/12 03:11:04  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.4.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*/


#endif // _VCF_LINUXSEMAPHOREPEER_H__


