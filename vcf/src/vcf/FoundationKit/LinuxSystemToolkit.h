#ifndef _VCF_LINUXSYSTEMTOOLKIT_H__
#define _VCF_LINUXSYSTEMTOOLKIT_H__ 
//LinuxSystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxSystemToolkit : public SystemToolkit
{
public:

	LinuxSystemToolkit();

	virtual ~LinuxSystemToolkit();

	/**
	*creates a new ProcessPeer instance
	*/
	virtual ProcessPeer* internal_createProcessPeer( Process* process );

	virtual ProcessIORedirectionPeer*
	internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process );
	/**
	*creates a new ThreadPeer instance
	*/
	virtual ThreadPeer* internal_createThreadPeer( Thread* thread );

	/**
	*creates a new system peer
	*/
	virtual SystemPeer* internal_createSystemPeer();

	virtual SemaphorePeer* internal_createSemaphorePeer( long initialCount,
	                                                     long maxCount );

	virtual RegistryPeer* internal_createRegistryPeer( Registry* registry );

	virtual MutexPeer* internal_createMutexPeer( Mutex* mutex );

	virtual ConditionPeer* internal_createConditionPeer( Condition* condition );

	virtual LibraryPeer* internal_createLibraryPeer( Library* library );

	virtual FilePeer* internal_createFilePeer( File* file );

	virtual FileStreamPeer*
	internal_createFileStreamPeer( const String& filename,
	                               const FileStreamAccessType& accessType );

	virtual FileStreamPeer* internal_createFileStreamPeer( File* file );

	virtual LocalePeer* internal_createLocalePeer();

	virtual ResourceBundlePeer* internal_createResourceBundlePeer();
};

}

/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
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
*Revision 1.6.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.5.2.2  2004/03/30 01:48:16  ddiego
*updated linux code
*
*Revision 1.5.2.1  2004/02/16 05:34:04  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.5  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/10/03 01:03:31  ddiego
*added fix for linux compiling
*
*Revision 1.4.4.1  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.4  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/04/19 22:22:56  ddiego
*tested the code developed in windows using gtk in linux. Seems to work ok except for a
*few minor compiler glitches. Had to comment out the partial specialization for
*floating point image bits in include/graphics/ImageBits.h. Also made some
*adjustments in the makefiles for building the GraphicsKit and ApplicationKit
*from the build/make/Makefile.
*
*Revision 1.3  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.2  2003/02/18 20:03:27  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.2.2.1  2002/12/27 23:04:39  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.8.1  2002/09/27 01:54:58  ddiego
*added support for bezier curves - remeber to change over to using teh MgcBeziers in Win32 too
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*
*/


#endif // _VCF_LINUXSYSTEMTOOLKIT_H__


