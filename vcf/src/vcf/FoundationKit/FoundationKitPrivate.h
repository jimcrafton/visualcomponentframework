#ifndef _VCF_FOUNDATIONKITPRIVATE_H__
#define _VCF_FOUNDATIONKITPRIVATE_H__
//FoundationKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#if defined(WIN32) && !defined(VCF_DOTNET)
#	include "vcf/FoundationKit/Win32SystemToolkit.h"
#	include "vcf/FoundationKit/Win32SemaphorePeer.h"
#	include "vcf/FoundationKit/Win32LibraryPeer.h"
#	include "vcf/FoundationKit/Win32Peer.h"
#	include "vcf/FoundationKit/Win32FilePeer.h"
#	include "vcf/FoundationKit/Win32FileStream.h"
#	include "vcf/FoundationKit/Win32ProcessPeer.h"
#	include "vcf/FoundationKit/Win32SystemPeer.h"
#	include "vcf/FoundationKit/Win32Thread.h"
#	include "vcf/FoundationKit/Win32Registry.h"
#	include "vcf/FoundationKit/Win32Mutex.h"
#elif defined(VCF_DOTNET)
#	include "vcf/FoundationKit/DotNetSystemToolkit.h"
#	include "vcf/FoundationKit/DotNetSemaphorePeer.h"
#	include "vcf/FoundationKit/DotNetLibraryPeer.h"
#	include "vcf/FoundationKit/DotNetPeer.h"
#	include "vcf/FoundationKit/DotNetFilePeer.h"
#	include "vcf/FoundationKit/DotNetFileStream.h"
#	include "vcf/FoundationKit/DotNetProcessPeer.h"
#	include "vcf/FoundationKit/DotNetSystemPeer.h"
#	include "vcf/FoundationKit/DotNetThread.h"
#	include "vcf/FoundationKit/DotNetRegistry.h"
#	include "vcf/FoundationKit/DotNetMutex.h"
#elif defined (VCF_POSIX)
	//pull in the linux headers here
	#include <sys/stat.h>
	#include <signal.h>
	#include <semaphore.h>
#	include "vcf/FoundationKit/LinuxSystemToolkit.h"
#	include "vcf/FoundationKit/LinuxPeer.h"
#	include "vcf/FoundationKit/LinuxFilePeer.h"
#	include "vcf/FoundationKit/LinuxFileStream.h"
#	include "vcf/FoundationKit/LinuxSemaphorePeer.h"
#	include "vcf/FoundationKit/LinuxLibraryPeer.h"
#	include "vcf/FoundationKit/LinuxProcessPeer.h"
#	include "vcf/FoundationKit/LinuxSystemPeer.h"
#	include "vcf/FoundationKit/PosixThread.h"
#	include "vcf/FoundationKit/LinuxRegistry.h"
#	include "vcf/FoundationKit/PosixMutex.h"
#	include "vcf/FoundationKit/PosixCondition.h"
#elif defined (VCF_OSX)
//pull in the OSX Foundation headers here
#include <Carbon/Carbon.h>
#include "vcf/FoundationKit/OSXSystemToolkit.h"
#include "vcf/FoundationKit/OSXPeer.h"
#include "vcf/FoundationKit/OSXFilePeer.h"
#include "vcf/FoundationKit/OSXFileStream.h"
#include "vcf/FoundationKit/OSXSemaphorePeer.h"
#include "vcf/FoundationKit/OSXLibraryPeer.h"
#include "vcf/FoundationKit/OSXProcessPeer.h"
#include "vcf/FoundationKit/OSXSystemPeer.h"
#include "vcf/FoundationKit/OSXThread.h"
#include "vcf/FoundationKit/OSXRegistry.h"
#include "vcf/FoundationKit/OSXMutexPeer.h"
#include "vcf/FoundationKit/OSXConditionPeer.h"
#endif


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/30 21:30:03  ddiego
*minor mods to copy/paste code in DocumentManager
*
*Revision 1.1.2.3  2004/06/05 01:55:21  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.7.2.1  2003/06/23 23:16:54  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.7  2003/05/17 20:36:58  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.2  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.6.2.1  2003/03/23 03:23:42  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.8.4  2003/02/18 20:01:03  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.5.8.3  2003/02/12 19:35:03  catwallader
*Added PosixMutex class.
*
*Revision 1.5.8.2  2003/01/30 22:31:14  catwallader
*Added the PosixThread class.  Modified Makefiles and toolkit files to accomodate it.
*
*Revision 1.5.8.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.5  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.4.4.1  2002/08/10 05:48:06  ddiego
*added basic support to the X11COntext for drawing lines, rectangles, and ellipses
*Bezier curves are more complex and will have to be done by hand as X has no
*convenient way to do this
*
*Revision 1.4  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*Revision 1.3  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.6  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.1.2.5  2002/04/03 19:37:16  zzack
*include style changed
*
*Revision 1.1.2.4  2002/03/27 04:24:55  cesarmello
*Linux bugfixes
*
*Revision 1.1.2.3  2002/03/26 04:46:07  cesarmello
*Linux headers
*
*Revision 1.1.2.2  2002/03/25 04:25:42  ddiego
*added some of the BSD license header plus the cvs log stamp to the
*new foundation kit and network global headers
*
*
*/


#endif // _VCF_FOUNDATIONKITPRIVATE_H__


