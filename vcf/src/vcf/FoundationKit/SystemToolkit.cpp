//SystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;



SystemToolkit* SystemToolkit::create()
{

	if ( NULL == SystemToolkit::systemToolkitInstance ) {
#if defined(WIN32) && !defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new Win32SystemToolkit();
#elif defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new DotNetSystemToolkit();
#elif VCF_POSIX
		SystemToolkit::systemToolkitInstance = new LinuxSystemToolkit();
#elif VCF_OSX
		SystemToolkit::systemToolkitInstance = new OSXSystemToolkit();
#endif
		if ( NULL == SystemToolkit::systemToolkitInstance ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2(String("No Toolkit instantiated!")) );
		}
		SystemToolkit::systemToolkitInstance->init();
	}

	return SystemToolkit::systemToolkitInstance;
}

void SystemToolkit::terminate()
{
	SystemToolkit::systemToolkitInstance->free();
}


SystemToolkit::SystemToolkit()
{

}

SystemToolkit::~SystemToolkit()
{

}

ProcessPeer* SystemToolkit::createProcessPeer( Process* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessPeer( process );
}

ProcessIORedirectionPeer* SystemToolkit::createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessIORedirectionPeer(process);
}

ThreadPeer* SystemToolkit::createThreadPeer( Thread* thread )
{
	return SystemToolkit::getSystemToolkit()->internal_createThreadPeer(thread);
}

SystemPeer* SystemToolkit::createSystemPeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createSystemPeer();
}

SemaphorePeer* SystemToolkit::createSemaphorePeer( long initialCount, long maxCount )
{
	return SystemToolkit::getSystemToolkit()->internal_createSemaphorePeer(initialCount,maxCount);
}

RegistryPeer* SystemToolkit::createRegistryPeer( Registry* registry )
{
	return SystemToolkit::getSystemToolkit()->internal_createRegistryPeer(registry);
}

MutexPeer* SystemToolkit::createMutexPeer( Mutex* mutex )
{
	return SystemToolkit::getSystemToolkit()->internal_createMutexPeer(mutex);
}

ConditionPeer* SystemToolkit::createConditionPeer( Condition* condition )
{
	return SystemToolkit::getSystemToolkit()->internal_createConditionPeer(condition);
}

LibraryPeer* SystemToolkit::createLibraryPeer( Library* library )
{
	return SystemToolkit::getSystemToolkit()->internal_createLibraryPeer(library);
}

FilePeer* SystemToolkit::createFilePeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFilePeer( file );
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(filename,accessType);
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(file);
}

LocalePeer* SystemToolkit::createLocalePeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createLocalePeer();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/29 02:39:14  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.1.2.4  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.3  2004/06/30 21:30:03  ddiego
*minor mods to copy/paste code in DocumentManager
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:50  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.2  2004/03/11 22:20:00  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*Revision 1.12.2.1  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.12  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.2  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.11.2.1  2003/08/13 21:43:01  ddiego
*thread stuff - fixed bug in auto deleting
*
*Revision 1.11  2003/08/09 02:56:46  ddiego
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
*Revision 1.10.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10.2.1  2003/06/23 23:16:55  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.10  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.14.2  2003/05/15 03:01:03  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.9.14.1  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.8  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.7.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


