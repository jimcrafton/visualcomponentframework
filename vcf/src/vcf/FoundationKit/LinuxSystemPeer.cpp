//LinuxSystemPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <cstdlib>

using namespace VCF;

struct timezone LinuxSystemPeer::timeZone;
struct timeval LinuxSystemPeer::time;

LinuxSystemPeer::LinuxSystemPeer()
{
	::gettimeofday( &LinuxSystemPeer::time, &LinuxSystemPeer::timeZone );
}

LinuxSystemPeer::~LinuxSystemPeer()
{}

unsigned long LinuxSystemPeer::getTickCount()
{
	struct timeval now;
	struct timezone timeZone;
	::gettimeofday( &now, &timeZone );

	double t1 = double( LinuxSystemPeer::time.tv_sec * 1000 ) +
	            double( LinuxSystemPeer::time.tv_usec / ( 1000 ) );

	double t2 = double( now.tv_sec * 1000 ) +
	            double( now.tv_usec / ( 1000 ) ); //convert to Milliseconds

	return ( unsigned long ) ( t2 - t1 );
}

void LinuxSystemPeer::sleep( const uint32& milliseconds )
{
	if ( 0 == milliseconds ) {
		return ;
	}
	struct timespec req, rem;
	req.tv_sec = milliseconds / 1000;
	req.tv_nsec = ( milliseconds % 1000 ) * 1000;
	::nanosleep( &req, &rem );
}

void LinuxSystemPeer::setEnvironmentVariable( const String& variableName,
                                              const String& newValue )
{
	if ( 0 != ::setenv( variableName.ansi_c_str(), newValue.ansi_c_str(), 1 ) ) {
		throw RuntimeException( "Failed to set variable " + variableName
		                        + " with value " + newValue );
	}
}

bool LinuxSystemPeer::doesFileExist( const String& fileName )
{
	FILE * f = ::fopen( fileName.ansi_c_str(), "r" );
	bool fileExist = ( f ) ? true : false;
	if ( f ) {
		::fclose( f );
	}
	return fileExist;
}

String LinuxSystemPeer::getCurrentWorkingDirectory()
{
	std::vector<char> buffer( PATH_MAX + 1, '\0' ) ;
	::getcwd( &buffer[ 0 ], buffer.size() - 1 );
	return String( &buffer[ 0 ] );
}

String LinuxSystemPeer::getEnvironmentVariable( const String& variableName )
{
	char const * env = ::getenv( variableName.ansi_c_str() );
	if ( env ) {
		return String( env );
	}
	return String();
}

void LinuxSystemPeer::addPathDirectory( const String& directory )
{
	char const * env = ::getenv( "PATH" );
	if ( env ) {
		String newPath = env;
		newPath += ":" + directory;
		if ( 0 == ::setenv( "PATH", newPath.ansi_c_str(), 1 ) ) {
			return;
		}
	}
	throw RuntimeException( "Failed to add to PATH value " + directory );
}

void LinuxSystemPeer::setCurrentWorkingDirectory( const String& currentDirectory )
{
	chdir( currentDirectory.ansi_c_str() );
}

void LinuxSystemPeer::setDateToSystemTime( DateTime* date )
{}

String LinuxSystemPeer::getOSName()
{
	return "GNU/Linux";
}


String LinuxSystemPeer::getOSVersion()
{
	return "";
}

ProgramInfo* LinuxSystemPeer::getProgramInfoFromFileName( const String& fileName )
{
	return 0; //LinuxResourceBundle::getProgramInfo( fileName );
}

void LinuxSystemPeer::setDateToLocalTime( DateTime* date )
{}

void LinuxSystemPeer::setCurrentThreadLocale( Locale* locale )
{}

DateTime LinuxSystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result;
	return result;
}

DateTime LinuxSystemPeer::convertLocalTimeToUTCTime( const DateTime& date )
{
	DateTime result;
	return result;
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
*Revision 1.1.2.4  2004/08/02 00:48:23  ddiego
*fixed build errors in linux for FoundationKit
*
*Revision 1.1.2.3  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.6  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.5.8.1  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.5  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.2.4  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4.2.3  2002/12/27 23:04:51  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.4.2.2  2002/12/23 04:36:32  ddiego
*finished very basic support for fonts - so we can at least draw simple
*text now. Woohoo! and they are anti aliased at that!
*
*Revision 1.4.2.1  2002/12/03 01:15:50  ddiego
*stuff
*
*Revision 1.4  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.3.4.1  2002/09/27 01:54:58  ddiego
*added support for bezier curves - remeber to change over to using teh MgcBeziers in Win32 too
*
*Revision 1.3  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.4.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.2  2002/05/27 22:52:34  ddiego
*added two new tests for testing File and System support in the FoudnationKit
*and verified that they work in Linux. Fixed associated code in getting that to
*work.
*
*Revision 1.1  2002/05/27 15:58:22  ddiego
*added linux peer classes for the FoundationKit port to linux
*this now means the FoundationKit will start up correctly on
*linu thought it is still not 100% functional yet
*
*/


