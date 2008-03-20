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

uint32 LinuxSystemPeer::getTickCount()
{
	struct timeval now;
	struct timezone timeZone;
	::gettimeofday( &now, &timeZone );

	double t1 = double( LinuxSystemPeer::time_.tv_sec * 1000 ) +
	            double( LinuxSystemPeer::time_.tv_usec / ( 1000 ) );

	double t2 = double( now.tv_sec * 1000 ) +
	            double( now.tv_usec / ( 1000 ) ); //convert to Milliseconds

	return ( uint32 ) ( t2 - t1 );
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
	uint64 millisecs = uint64(tmv.tv_sec)*1000+uint64(tmv.tv_usec)/1000;
	DateTime tmp(1970, 1, 1);
	millisecs += tmp.getMilliseconds();
	date->setMilliseconds( millisecs );
}

void LinuxSystemPeer::setCurrentThreadLocale( Locale* locale )
{
// using boost::shared pointer might solve the leak.
	static __thread locale_t prevLocale = NULL;

	if(prevLocale != NULL &&
	   prevLocale != LC_GLOBAL_LOCALE) {
		freelocale(prevLocale);
	}
	locale_t loc = duplocale( reinterpret_cast<locale_t>(locale->getPeer()->getHandleID()) );
    prevLocale = uselocale(loc);
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

void LinuxSystemPeer::setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz )
{

}

/**
$Id$
*/
