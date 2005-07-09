//LinuxSystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ProcessIORedirectionPeer.h"
#include "vcf/FoundationKit/LinuxProcessIORedirector.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/LinuxLocalePeer.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/LinuxResourceBundle.h"



using namespace VCF;

LinuxSystemToolkit::LinuxSystemToolkit()
{}

LinuxSystemToolkit::~LinuxSystemToolkit()
{}

ProcessPeer* LinuxSystemToolkit::internal_createProcessPeer( Process* process )
{
	return new LinuxProcessPeer();
}

ThreadPeer* LinuxSystemToolkit::internal_createThreadPeer( Thread* thread )
{
	return new PosixThread( thread );
}

SystemPeer* LinuxSystemToolkit::internal_createSystemPeer()
{
	return new LinuxSystemPeer();
}

SemaphorePeer* LinuxSystemToolkit::internal_createSemaphorePeer( long initialCount,
                                                                 long maxCount )
{
	return new LinuxSemaphorePeer( initialCount, maxCount );
}

RegistryPeer* LinuxSystemToolkit::internal_createRegistryPeer( Registry* registry )
{
	return new LinuxRegistry();
}

MutexPeer* LinuxSystemToolkit::internal_createMutexPeer( Mutex* mutex )
{
	return new PosixMutex();
}

ConditionPeer*
LinuxSystemToolkit::internal_createConditionPeer( Condition* condition )
{
	return new PosixCondition( condition );
}

LibraryPeer* LinuxSystemToolkit::internal_createLibraryPeer( Library* library )
{
	return new LinuxLibraryPeer();
}

FilePeer* LinuxSystemToolkit::internal_createFilePeer( File* file )
{
	return new LinuxFilePeer( file );
}

FileStreamPeer*
LinuxSystemToolkit::internal_createFileStreamPeer( const String& filename,
                                                   const FileStreamAccessType& accessType )
{
	return new LinuxFileStream( filename, accessType );
}

FileStreamPeer* LinuxSystemToolkit::internal_createFileStreamPeer( File* file )
{
	return new LinuxFileStream( file );
}

ProcessIORedirectionPeer* LinuxSystemToolkit::internal_createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	ProcessIORedirectionPeer * result = new LinuxProcessIORedirector();
	result->setProcess( process );
	return result;
}

LocalePeer* LinuxSystemToolkit::internal_createLocalePeer()
{
	return new LinuxLocalePeer();
}

ResourceBundlePeer* LinuxSystemToolkit::internal_createResourceBundlePeer()
{
	return new LinuxResourceBundle();
}



/**
*CVS Log info
*$Log$
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
*Revision 1.1.2.3  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.6  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.5.2.2  2004/03/30 01:48:26  ddiego
*updated linux code
*
*Revision 1.5.2.1  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.5  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/10/03 01:01:24  ddiego
*added a fix for compiling in linux
*
*Revision 1.4.4.1  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.4  2003/05/17 20:37:34  ddiego
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
*Revision 1.3  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.5  2003/02/18 20:05:40  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.2.2.4  2003/02/12 19:35:55  catwallader
*Added PosixMutex class.
*
*Revision 1.2.2.3  2003/01/30 22:32:21  catwallader
*Added the PosixThread class.  Modified Makefiles and toolkit files to accomodate it.
*
*Revision 1.2.2.2  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.2.2.1  2002/12/27 23:04:51  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
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
*/


