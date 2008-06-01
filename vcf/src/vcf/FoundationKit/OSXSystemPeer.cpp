//OSXSystemPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/DateTime.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/OSXResourceBundle.h"
#include "vcf/FoundationKit/ThreadManager.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


namespace VCF {




OSXSystemPeer::OSXSystemPeer()
{
 	::gettimeofday( &time_, &timeZone_ );
}

OSXSystemPeer::~OSXSystemPeer()
{

}

uint32 OSXSystemPeer::getTickCount()
{

	struct timeval now = {0};
	struct	timezone timeZone;
	::gettimeofday( &now, &timeZone );

	double t1, t2;

	t1 =  (double)(time_.tv_sec * 1000) +
		(double)time_.tv_usec/(1000);

	t2 =  (double)(now.tv_sec * 1000) + (double)now.tv_usec/(1000); //convert to Milliseconds


	uint32 result = (uint32)(t2 - t1);

	return result;
}

void OSXSystemPeer::sleep( const uint32& milliseconds )
{
	if ( 0 == milliseconds ) {
  	return;
	}
	struct timespec req = {0};
	struct timespec rem = {0};
	req.tv_sec = milliseconds / 1000;
	req.tv_nsec = (milliseconds % 1000) * 1000;
	::nanosleep( &req, &rem );
}

bool OSXSystemPeer::doesFileExist( const String& fileName )
{
	bool result = true;
	
	struct stat sb;
	int staterr  = stat( fileName.ansi_c_str(), &sb );
	if ( -1 == staterr ) {
		if ( errno == ENOENT ) {
			result  = false;
		}
	}
	
	return result;
}

String OSXSystemPeer::getCurrentWorkingDirectory()
{
	char tmp[PATH_MAX+1];
	getcwd( tmp, PATH_MAX );
	String result = tmp;
	return result;
}

String OSXSystemPeer::getEnvironmentVariable( const String& variableName )
{
	String result;

	const char* env = getenv( variableName.ansi_c_str() );
	if ( NULL != env ) {
		result = env;
	}

	return result;
}


void OSXSystemPeer::setEnvironmentVariable( const String& variableName, const String& newValue )
{
	if ( 0 != setenv( variableName.ansi_c_str(), newValue.ansi_c_str(), 1 ) ) {
		throw RuntimeException( "Failed to set variable " + variableName + " with value " + newValue  );
	}
}

void OSXSystemPeer::addPathDirectory( const String& directory )
{
	const char* env = getenv( "PATH" );
	String newPath = env;
	newPath += ":" + directory;
	if ( 0 != setenv( "PATH", newPath.ansi_c_str(), 1 ) ) {
		throw RuntimeException( "Failed to set PATH with value " + newPath  );
	}
}

void OSXSystemPeer::setCurrentWorkingDirectory( const String& currentDirectory )
{
	chdir( currentDirectory.ansi_c_str() );
}

String OSXSystemPeer::getCommonDirectory( System::CommonDirectory directory )
{
	String result;

	const char* homeDir = getenv( "HOME" );

	//based on
	//http://developer.apple.com/documentation/MacOSX/Conceptual/BPFileSystem/Articles/LibraryDirectory.html
	switch ( directory ) {
		case System::cdUserHome : {
			result = homeDir;
		}
		break;

		case System::cdUserProgramData : {
			result = homeDir;
			result += "/Library/Application Support";
		}
		break;

		case System::cdUserDesktop : {
			result = homeDir;
			result += "/Desktop";
		}
		break;

		case System::cdUserFavorites : {
			result = homeDir;
			result += "/Library/Favorites";
		}
		break;

		case System::cdUserDocuments : {
			result = homeDir;
			result += "/Documents";
		}
		break;

		case System::cdUserTemp : {
			result = homeDir;
			result += "/tmp";
		}
		break;

		case System::cdSystemPrograms : {
			result = "/Applications";
		}
		break;

		case System::cdSystemTemp : {
			result = "/tmp";
		}
		break;

		case System::cdSystemRoot : {
			result = "/";
		}
		break;
	}

	return result;
}

String OSXSystemPeer::getComputerName()
{
	CFTextString result;
	result = CSCopyMachineName();

	return result;
}

String OSXSystemPeer::getUserName()
{
	CFTextString result;
	result = CSCopyUserName(true);

	return result;
}
	
void OSXSystemPeer::setDateToSystemTime( DateTime* date )
{
	CFAbsoluteTime timeNow = CFAbsoluteTimeGetCurrent();
	CFGregorianDate current = CFAbsoluteTimeGetGregorianDate( timeNow, NULL );
	
	double dsecs = floor(current.second);
	unsigned int second = (unsigned int)dsecs;
	
	double milliseconds = (current.second - dsecs) * 1000.0;
	
	date->set( current.year, current.month, current.day, 
				current.hour, current.minute, second, (unsigned int)milliseconds );
}

void OSXSystemPeer::setDateToLocalTime( DateTime* date )
{
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();

	CFAbsoluteTime timeNow = CFAbsoluteTimeGetCurrent();
	CFGregorianDate current = CFAbsoluteTimeGetGregorianDate( timeNow, tz );
	
	double dsecs = floor(current.second);
	unsigned int second = (int)dsecs;
	
	double milliseconds = (current.second - dsecs) * 1000.0;
	
	
	
	date->set( current.year, current.month, current.day, 
				current.hour, current.minute, second, (unsigned int)milliseconds );
}

void OSXSystemPeer::setCurrentThreadLocale( Locale* locale )
{
	//OSX doesn't really support this, so we fake it
	//anyways
	

	Thread* currentThread = ThreadManager::getCurrentThread();
	if ( NULL != currentThread ) {
		OSXThread* osxThread = (OSXThread*) currentThread->getPeer();

		osxThread->setCurrentLocale( locale );
	}
}

DateTime OSXSystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result;
	
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();
	CFGregorianDate cfDate;
	
	uint32 year;
	uint32 month;
	uint32 day;
	uint32 hour;
	uint32 minute;
	uint32 second;
	uint32 millisecond;	
	date.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
	
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = second;
	if ( millisecond > 0 ) {
		cfDate.second += (1000.0/(double)millisecond);
	}
	
	//GMT/UTC time
	CFAbsoluteTime utcTime = CFGregorianDateGetAbsoluteTime( cfDate, NULL );
	
	cfDate = CFAbsoluteTimeGetGregorianDate( utcTime, tz );
	
	double dsecs = floor(cfDate.second);
	second = (uint32) dsecs;
	
	double milliseconds = (cfDate.second - dsecs) * 1000.0;
	
	
	
	result.set( cfDate.year, cfDate.month, cfDate.day, 
				cfDate.hour, cfDate.minute, second, (unsigned int)milliseconds );
				
	
	return result;
}

DateTime OSXSystemPeer::convertLocalTimeToUTCTime( const DateTime& date )
{
	DateTime result;
	
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();
	CFGregorianDate cfDate;
	
	uint32 year;
	uint32 month;
	uint32 day;
	uint32 hour;
	uint32 minute;
	uint32 second;
	uint32 millisecond;	
	date.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
	
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = second;
	if ( millisecond > 0 ) {
		cfDate.second += (1000.0/(double)millisecond);
	}
	//GMT/UTC time
	CFAbsoluteTime localTime = CFGregorianDateGetAbsoluteTime( cfDate, tz );
	
	cfDate = CFAbsoluteTimeGetGregorianDate( localTime, NULL );
	
	double dsecs = floor(cfDate.second);
	second = (unsigned int)dsecs;
	
	double milliseconds = (cfDate.second - dsecs) * 1000.0;
	
	
	
	result.set( cfDate.year, cfDate.month, cfDate.day, 
				cfDate.hour, cfDate.minute, second, (unsigned int)milliseconds );
				
	
	return result;
}

String OSXSystemPeer::getOSName()
{
	return "Mac OSX";
}

String OSXSystemPeer::getOSVersion()
{
	long response = 0;
	Gestalt( gestaltSystemVersion, &response );
	int bug = (0x0000000F) & response;
	int minor = ((0x000000F0) & response) >> 4;
	int major = ((0x0000FFFF) & response) >> 8;	
	
	return Format("%x.%x.%x") % major % minor % bug ;
}

ProgramInfo* OSXSystemPeer::getProgramInfoFromFileName( const String& fileName )
{
	return OSXResourceBundle::getProgramInfo( fileName );
}

String OSXSystemPeer::createTempFileName( const String& directory )
{
	String result;
	throw RuntimeException( MAKE_ERROR_MSG_2("OSXSystemPeer::createTempFileName() not implemented!") );
	return result;
}
	
void OSXSystemPeer::setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz )
{

}

};


/**
$Id$
*/
