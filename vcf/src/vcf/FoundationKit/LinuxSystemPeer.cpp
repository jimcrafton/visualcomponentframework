//LinuxSystemPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"

#include <cstdlib>
#include <sys/utsname.h>
#include <pwd.h>

using namespace VCF;

LinuxSystemPeer::LinuxSystemPeer()
{
	::gettimeofday( &time_, &timeZone_ );
}

LinuxSystemPeer::~LinuxSystemPeer()
{}

unsigned long LinuxSystemPeer::getTickCount()
{
	struct timeval now;
	struct timezone timeZone;
	::gettimeofday( &now, &timeZone );

	double t1 = double( LinuxSystemPeer::time_.tv_sec * 1000 ) +
	            double( LinuxSystemPeer::time_.tv_usec / ( 1000 ) );

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
	req.tv_nsec = ((milliseconds * 1000) % 1000000) * 1000;
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

String LinuxSystemPeer::getCommonDirectory( System::CommonDirectory directory )
{
	String result;

    switch( directory ) {
        case System::cdUserHome :{
            result = getEnvironmentVariable("HOME");
            if(result.empty())
            {
                passwd *pswd = getpwuid(getuid());
                assert(pswd != NULL);
                result = pswd->pw_dir;
            }
        }
        break;

        case System::cdUserProgramData :
            result = "usr/share";
        break;

        case System::cdUserDesktop :
            result = getCommonDirectory(System::cdUserHome);
        break;

        case System::cdUserFavorites :
            result = getCommonDirectory(System::cdUserHome);
        break;

        case System::cdUserDocuments :
            result = getCommonDirectory(System::cdUserHome);
        break;

        case System::cdUserTemp :
            result = getCommonDirectory(System::cdUserHome);
        break;

        case System::cdSystemPrograms :
            result = "/usr/bin";
        break;

        case System::cdSystemTemp :
            result = "/tmp";
        break;

        case System::cdSystemRoot :
            return "/";
        break;

        default:
            // Unkown CommonDirectory type
            VCF_ASSERT(false);
        break;
    }

	return result;
}

String LinuxSystemPeer::createTempFileName( const String& directory )
{
    return tempnam(directory.ansi_c_str(), "vcftmp");;
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
	return 0;
}

void LinuxSystemPeer::setDateToLocalTime( DateTime* date )
{
	::timeval tmv;
	::gettimeofday(&tmv, NULL);
	ulong64 millisecs = ulong64(tmv.tv_sec)*1000+ulong64(tmv.tv_usec)/1000;
	DateTime tmp(1970, 1, 1);
	millisecs += tmp.getMilliseconds();
	date->setMilliseconds( millisecs );
}

void LinuxSystemPeer::setCurrentThreadLocale( Locale* locale )
{
    uselocale( reinterpret_cast<locale_t>(locale->getPeer()->getHandleID()));
}

DateTime LinuxSystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result = date;
	return result;
}

DateTime LinuxSystemPeer::convertLocalTimeToUTCTime( const DateTime& date )
{
	DateTime result = date;
	return result;
}

String LinuxSystemPeer::getComputerName()
{
    utsname uts;
    uname(&uts);
    String result = uts.nodename;
    return result;
}

String LinuxSystemPeer::getUserName()
{
    String result;
    passwd *pswd = getpwuid(getuid());
    if(pswd != NULL)
    {
        result = pswd->pw_gecos;
    }
    if(result.empty())
    {
        result = getlogin();
    }
    return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.5  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.4.2.4  2005/12/01 01:13:00  obirsoy
*More linux improvements.
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
*Revision 1.2.4.1  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
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


