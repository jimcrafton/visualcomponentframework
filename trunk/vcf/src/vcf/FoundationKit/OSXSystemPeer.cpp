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
#include <unistd.h>


using namespace VCF;




OSXSystemPeer::OSXSystemPeer()
{
 	::gettimeofday( &time_, &timeZone_ );
}

OSXSystemPeer::~OSXSystemPeer()
{

}

unsigned long OSXSystemPeer::getTickCount()
{

	struct timeval now = {0};
	struct	timezone timeZone;
	::gettimeofday( &now, &timeZone );

	double t1, t2;

	t1 =  (double)(time_.tv_sec * 1000) +
		(double)time_.tv_usec/(1000);

	t2 =  (double)(now.tv_sec * 1000) + (double)now.tv_usec/(1000); //convert to Milliseconds


	unsigned long result = (unsigned long)(t2 - t1);

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
	bool result = false;
	FILE* f = fopen( fileName.ansi_c_str(), "r" );
    result = (NULL != f ) ? true : false;
    if ( NULL != f ) {
        fclose( f );
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

void OSXSystemPeer::setDateToSystemTime( DateTime* date )
{
	CFAbsoluteTime timeNow = CFAbsoluteTimeGetCurrent();
	CFGregorianDate current = CFAbsoluteTimeGetGregorianDate( timeNow, NULL );
	
	double dsecs = floor(current.second);
	int second = dsecs;
	
	double milliseconds = (current.second - dsecs) * 1000.0;
	
	date->set( current.year, current.month, current.day, 
				current.hour, current.minute, second, milliseconds );
}

void OSXSystemPeer::setDateToLocalTime( DateTime* date )
{
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();

	CFAbsoluteTime timeNow = CFAbsoluteTimeGetCurrent();
	CFGregorianDate current = CFAbsoluteTimeGetGregorianDate( timeNow, tz );
	
	double dsecs = floor(current.second);
	int second = dsecs;
	
	double milliseconds = (current.second - dsecs) * 1000.0;
	
	
	
	date->set( current.year, current.month, current.day, 
				current.hour, current.minute, second, milliseconds );
}

void OSXSystemPeer::setCurrentThreadLocale( Locale* locale )
{

}

DateTime OSXSystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result;
	
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();
	CFGregorianDate cfDate;
	
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
	unsigned long millisecond;	
	date.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
	
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = ((double)second) + ( 1000.0/(double)millisecond );
	
	//GMT/UTC time
	CFAbsoluteTime utcTime = CFGregorianDateGetAbsoluteTime( cfDate, NULL );
	
	cfDate = CFAbsoluteTimeGetGregorianDate( utcTime, tz );
	
	double dsecs = floor(cfDate.second);
	second = dsecs;
	
	double milliseconds = (cfDate.second - dsecs) * 1000.0;
	
	
	
	result.set( cfDate.year, cfDate.month, cfDate.day, 
				cfDate.hour, cfDate.minute, second, milliseconds );
				
	
	return result;
}

DateTime OSXSystemPeer::convertLocalTimeToUTCTime( const DateTime& date )
{
	DateTime result;
	
	CFRefObject<CFTimeZoneRef> tz = CFTimeZoneCopySystem();
	CFGregorianDate cfDate;
	
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
	unsigned long millisecond;	
	date.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
	
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = ((double)second) + ( 1000.0/(double)millisecond );
	
	//GMT/UTC time
	CFAbsoluteTime localTime = CFGregorianDateGetAbsoluteTime( cfDate, tz );
	
	cfDate = CFAbsoluteTimeGetGregorianDate( localTime, NULL );
	
	double dsecs = floor(cfDate.second);
	second = dsecs;
	
	double milliseconds = (cfDate.second - dsecs) * 1000.0;
	
	
	
	result.set( cfDate.year, cfDate.month, cfDate.day, 
				cfDate.hour, cfDate.minute, second, milliseconds );
				
	
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
	
	return StringUtils::format( "%x.%x.%x", major, minor, bug );
}

ProgramInfo* OSXSystemPeer::getProgramInfoFromFileName( const String& fileName )
{
	return OSXResourceBundle::getProgramInfo( fileName );
}
	
/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/08 20:52:47  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
*osx updates
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.7  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.6.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.4  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*Revision 1.2  2003/08/09 02:56:46  ddiego
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
*Revision 1.1.2.2  2003/06/23 23:16:55  ddiego
*added some furtther implementation for the osx port
*
*Revision 1.1.2.1  2003/05/22 04:40:05  ddiego
*removed the .cpp files in favor of .mm files to allow Objective-C++ compiling
*
*/


