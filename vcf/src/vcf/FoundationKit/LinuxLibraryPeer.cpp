//LinuxLibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <dlfcn.h>

using namespace VCF;

LinuxLibraryPeer::LinuxLibraryPeer()
		: libHandle_( 0 )
{}

LinuxLibraryPeer::~LinuxLibraryPeer()
{}

void LinuxLibraryPeer::load( const String& libraryFilename )
{
	System::println("Opening "+libraryFilename);
	//for now, till we find a better way, we are going
	//do default to Lazy loading - the alternate is
	//have all the symbols of libary resolved at once,
	//which would mean this call would block till that was
	//done
	libHandle_ = ::dlopen( libraryFilename.ansi_c_str(), RTLD_LAZY );

	StringUtils::traceWithArgs( Format("dlopen( %s ) returned %p\n") %
								 libraryFilename %  libHandle_ );

	if ( ! libHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( dlerror() ) );
	}
}

void* LinuxLibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;

	if ( ! libHandle_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2(
		                                   "You are trying to get function adress "
		                                   "without a valid handle to a library" ) );
	}
	result = dlsym( libHandle_, functionName.ansi_c_str() );
	if(result == NULL) {
		StringUtils::traceWithArgs( Format( "error are: %s\n" ) % String(dlerror()) );
	}
	return result;
}

OSHandleID LinuxLibraryPeer::getHandleID()
{
    return libHandle_;
}

void LinuxLibraryPeer::unload()
{
	if ( libHandle_ ) {
		dlclose( libHandle_ );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.4  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.4.2.3  2005/11/18 16:02:53  obirsoy
*changes required for gcc under Linux, and some warning clean up.
*
*Revision 1.4.2.2  2005/11/11 00:21:00  ddiego
*comitting mostuffs linux foundationkit patchs [1351922].
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
*Revision 1.2.4.1  2005/03/15 01:51:51  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.14.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.14.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/05/28 03:03:15  ddiego
*added another test: FileStreaming to test out the FileStream class in
*linux. Added some changes to the LinuxFileStream class. Also added the
*LinuxLibraryPeer so the Library class now works in linux.
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*/


