//Win32SystemPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/DateTime.h"

#include "vcf/FoundationKit/DateTime.h"

#include "vcf/FoundationKit/DateTime.h"

using namespace VCF;

Win32SystemPeer::Win32SystemPeer()
{

}

Win32SystemPeer::~Win32SystemPeer()
{

}

unsigned long Win32SystemPeer::getTickCount()
{
	return ::GetTickCount();
}

void Win32SystemPeer::sleep( const uint32& milliseconds )
{
	::Sleep( milliseconds );
}

bool Win32SystemPeer::doesFileExist( const String& fileName )
{
	bool result = true;


	HANDLE hfile = NULL;

	if ( System::isUnicodeEnabled() ) {
		hfile = ::CreateFileW( fileName.c_str(), 0,
								0/*FILE_SHARE_READ | FILE_SHARE_WRITE*/, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM, NULL );
	}
	else {
		hfile = ::CreateFileA( fileName.ansi_c_str(), 0,
								0/*FILE_SHARE_READ | FILE_SHARE_WRITE*/, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM, NULL );
	}


	if ( INVALID_HANDLE_VALUE == hfile ) {
		int err = ::GetLastError();
		if ( (err == ERROR_FILE_NOT_FOUND) || (err == ERROR_PATH_NOT_FOUND) ){
			result = false;
		}
	}
	else {
		CloseHandle( hfile );
	}

	return result;
}

String Win32SystemPeer::getEnvironmentVariable( const String& variableName )
{
	String result;

	BOOL ret = FALSE;
	if ( System::isUnicodeEnabled() ) {
		VCFChar path[4096];
		memset( path, 0, 4096*sizeof(VCFChar) );
		ret = ::GetEnvironmentVariableW( variableName.c_str(), path, (4096-1)*sizeof(VCFChar) );
		if ( ret ) {
			result = path;
		}
	}
	else {
		char path[4096];
		memset( path, 0, 4096 );
		ret = ::GetEnvironmentVariableA( variableName.ansi_c_str(), path, 4096-1 );
		if ( ret ) {
			result = path;
		}
	}

	if ( !ret ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}

	return result;
}

String Win32SystemPeer::getCurrentWorkingDirectory()
{
	String result;

	VCFChar path[MAX_PATH+1];
	BOOL ret = FALSE;
	if ( System::isUnicodeEnabled() ) {
		ret = GetCurrentDirectoryW( MAX_PATH, path );
		if ( ret ) {
			result = path;
		}
	}
	else {
		char tmp[MAX_PATH+1];
		ret = GetCurrentDirectoryA( MAX_PATH, tmp );
		if ( ret ) {
			result = tmp;
		}
	}
	if ( !ret ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}
	else {

		if ( result[result.size()-1] != '\\' ) {
			result += "\\";
		}
	}

	return result;
}

void Win32SystemPeer::setCurrentWorkingDirectory( const String& currentDirectory )
{
	BOOL result = FALSE;
	if ( System::isUnicodeEnabled() ) {
		result = SetCurrentDirectoryW( currentDirectory.c_str() );
	}
	else {
		result = SetCurrentDirectoryA( currentDirectory.ansi_c_str() );
	}
	if ( !result ) {
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( MAKE_ERROR_MSG_2( error ) );
	}
}


void Win32SystemPeer::setDateToSystemTime( DateTime* date )
{
	//get current time
	SYSTEMTIME tm;
	::GetSystemTime( &tm );
	date->set( tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds );
}

void Win32SystemPeer::setDateToLocalTime( DateTime* date )
{
	//get current time
	SYSTEMTIME tm;
	::GetLocalTime( &tm );
	date->set( tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds );
}

void Win32SystemPeer::setCurrentThreadLocale( Locale* locale )
{

	SetThreadLocale( (LCID) locale->getPeer()->getHandleID() );
}

bool Win32SystemPeer::isUnicodeEnabled()
{
	bool result = false;

	OSVERSIONINFO osVersion = {0};
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);

	GetVersionEx( &osVersion );

	if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
		result = true;
	}

	return result;
}

DateTime Win32SystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result = date;

	FILETIME   ftUTC, ftLocal;
	SYSTEMTIME st;


	// DateTime --> systemTime
	st.wYear = date.getYear();
	st.wMonth = date.getMonth();
	st.wDayOfWeek = date.getWeekDay();
	st.wDay = date.getDay();
	st.wHour = date.getHour();
	st.wMinute = date.getMinute();
	st.wSecond = date.getSecond();
	st.wMilliseconds = date.getMilliSecond();

	// convert system time to filetime
	if ( !::SystemTimeToFileTime( &st, &ftUTC ) ) { // stUTC --> ftUTC
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	// convert UTC time to local time
	if (!::FileTimeToLocalFileTime( &ftUTC, &ftLocal ) ) {	// ftUTC --> ftUTC
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	// convert the local file time from UTC to system time
	if ( !::FileTimeToSystemTime( &ftLocal, &st ) ) { // ftLocal --> stLocal
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	result.set( st.wYear, st.wMonth, st.wDay,
						st.wHour, st.wMinute, st.wSecond, 
						st.wMilliseconds );	
	return result;
}

DateTime Win32SystemPeer::convertLocalTimeToUTCTime( const DateTime& date )
{
	DateTime result = date;

	// see also HOWTO: FileTimeToLocalFileTime() Adjusts for Daylight Saving Time

	FILETIME   ftLocal, ftUTC;
	SYSTEMTIME st;

	// DateTime --> systemTime
	st.wYear = date.getYear();
	st.wMonth = date.getMonth();
	st.wDayOfWeek = date.getWeekDay();
	st.wDay = date.getDay();
	st.wHour = date.getHour();
	st.wMinute = date.getMinute();
	st.wSecond = date.getSecond();
	st.wMilliseconds = date.getMilliSecond();

	// convert system time to filetime
	if ( !::SystemTimeToFileTime( &st, &ftLocal ) ) { // stUTC --> ftUTC
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	// convert UTC time to local time
	if (!::LocalFileTimeToFileTime( &ftLocal, &ftUTC ) ) {	// ftUTC --> ftUTC
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	// convert the local file time from UTC to system time
	if ( !::FileTimeToSystemTime( &ftUTC, &st ) ) { // ftLocal --> stLocal
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw BasicException( error );
	}

	result.set( st.wYear, st.wMonth, st.wDay,
						st.wHour, st.wMinute, st.wSecond, 
						st.wMilliseconds );

	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/08/03 20:57:22  marcelloptr
*minor change on name DateTime:getSecond DateTime:getMillisecond
*
*Revision 1.1.2.3  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.13.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.13  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.2.3  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.11.2.2  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.11.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.11  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.6.1  2003/08/22 04:39:18  ddiego
*minor improvemtn to Diretory constructor, fixed bug in DefaultTableCellItem
*
*Revision 1.10  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.2.1  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.8.4.1  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.8  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.6.2  2002/07/26 04:24:29  ddiego
*added more support for properly querying modified document, and removing the
*documents from the doc tab pages, made some changes in TabbedPages to support
*this as well
*
*Revision 1.7.6.1  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


