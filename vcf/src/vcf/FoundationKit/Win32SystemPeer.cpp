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
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"

#include <lmcons.h>

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
		memset( path, 0, sizeof(path) );
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


void Win32SystemPeer::setEnvironmentVariable( const String& variableName, const String& newValue )
{
	if ( System::isUnicodeEnabled() ) {
		SetEnvironmentVariableW( variableName.c_str(), newValue.c_str() );
	}
	else {
		SetEnvironmentVariableA( variableName.ansi_c_str(), newValue.ansi_c_str() );
	}
	
}

void Win32SystemPeer::addPathDirectory( const String& directory )
{
	String tmpDir = StringUtils::trimRight( directory, '\\' );
	
	if ( System::isUnicodeEnabled() ) {
		String newValue;
		String variableName = L"PATH";
		int charRequired = 32767; // max size accepted by SetEnvironmentVariable including trailing null terminator.
		VCFChar* path = new VCFChar[charRequired];
		memset( path, 0, charRequired*sizeof(VCFChar) );
		
		if ( ::GetEnvironmentVariableW( variableName.c_str(), path, charRequired ) ) { // here size is the number of TCHARs
			newValue = path;
			newValue += ";" + tmpDir;

			if ( newValue.size() > (charRequired-1) ) {
				//warn about the path potentially being too long
				StringUtils::trace( "WARNING: Path being assigned is greater than 32766 characters!\n" ); 
			}
			SetEnvironmentVariableW( variableName.c_str(), newValue.c_str() );
		}

		delete path;
	}
	else {
		AnsiString newValue;
		AnsiString variableName = "PATH";
		int charRequired = 32767; // max size accepted by SetEnvironmentVariable including trailing null terminator.
		char* path = new char[charRequired];
		memset( path, 0, charRequired*sizeof(char) );
		
		if ( ::GetEnvironmentVariableA( variableName.c_str(), path, charRequired ) ) { // here size is the number of TCHARs
			newValue = path;
			newValue += ";" + tmpDir;

			if ( newValue.size() > (charRequired-1) ) {
				//warn about the path potentially being too long
				StringUtils::trace( "WARNING: Path being assigned is greater than 32766 characters!\n" ); 
			}
			SetEnvironmentVariableA( variableName.c_str(), newValue.c_str() );
		}

		delete path;
	}
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

DateTime Win32SystemPeer::convertUTCTimeToLocalTime( const DateTime& date )
{
	DateTime result = date;

	FILETIME   ftUTC, ftLocal;
	SYSTEMTIME st;

	// DateTime --> systemTime
	unsigned long y, m, d, h, min, s, ms;
	date.get( &y, &m, &d, &h, &min, &s, &ms );

	if ( ( y < 1601 ) || ( 30827 < y ) ) {
		throw BasicException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
	}

	st.wYear   = y;
	st.wMonth  = m;
	st.wDayOfWeek = date.getWeekDay();
	st.wDay    = d;
	st.wHour   = h;
	st.wMinute = min;
	st.wSecond = s;
	st.wMilliseconds = ms;

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

	unsigned long y = date.getYear();
	if ( ( y < 1601 ) || ( 30827 < y ) ) {
		throw BasicException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
	}

	// DateTime --> systemTime
	st.wYear = y;
	st.wMonth = date.getMonth();
	st.wDayOfWeek = date.getWeekDay();
	st.wDay = date.getDay();
	st.wHour = date.getHour();
	st.wMinute = date.getMinute();
	st.wSecond = date.getSecond();
	st.wMilliseconds = date.getMillisecond();

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

String Win32SystemPeer::getOSName()
{
	String result;
	OSVERSIONINFO osVersion = {0};

	
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);
	::GetVersionEx( &osVersion );
	//need a way to tell WinCE???
	if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
		result = "WindowsNT";
	}
	else {
		result = "Windows";
	}
	

	return result;
}


String Win32SystemPeer::getOSVersion()
{
	String result;
	OSVERSIONINFO osVersion = {0};

	
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);
	::GetVersionEx( &osVersion );
	
	result = Format("%d.%d %d") % osVersion.dwMajorVersion % osVersion.dwMinorVersion % osVersion.dwBuildNumber;

	return result;
}

ProgramInfo* Win32SystemPeer::getProgramInfoFromFileName( const String& fileName )
{
	return Win32ResourceBundle::getProgramInfoFromFileName( fileName );
}

String Win32SystemPeer::getCommonDirectory( System::CommonDirectory directory )
{
	String result;
	OSVERSIONINFO osVersion = {0};	
	osVersion.dwOSVersionInfoSize = sizeof(osVersion);
	::GetVersionEx( &osVersion );


	switch ( directory ) {
		case System::cdUserHome : {
			if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
				result = getEnvironmentVariable( "USERPROFILE" );
			}
		}
		break;

		case System::cdUserProgramData : {
			if ( System::isUnicodeEnabled() ) {
				VCF::WideChar tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathW( NULL, tmp, CSIDL_APPDATA, FALSE ) ) ) {
					result = tmp;
				}
			}
			else{
				char tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathA( NULL, tmp, CSIDL_APPDATA, FALSE ) ) ) {
					result = tmp;
				}
			}
			
		}
		break;

		case System::cdUserDesktop : {
			if ( System::isUnicodeEnabled() ) {
				VCF::WideChar tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathW( NULL, tmp, CSIDL_DESKTOPDIRECTORY, FALSE ) ) ) {
					result = tmp;
				}
			}
			else{
				char tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathA( NULL, tmp, CSIDL_DESKTOPDIRECTORY, FALSE ) ) ) {
					result = tmp;
				}
			}
		}
		break;

		case System::cdUserFavorites : {
			if ( System::isUnicodeEnabled() ) {
				VCF::WideChar tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathW( NULL, tmp, CSIDL_FAVORITES, FALSE ) ) ) {
					result = tmp;
				}
			}
			else{
				char tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathA( NULL, tmp, CSIDL_FAVORITES, FALSE ) ) ) {
					result = tmp;
				}
			}
		}
		break;

		case System::cdUserDocuments : {
			if ( System::isUnicodeEnabled() ) {
				VCF::WideChar tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathW( NULL, tmp, CSIDL_PERSONAL, FALSE ) ) ) {
					result = tmp;
				}
			}
			else{
				char tmp[MAX_PATH];
				if ( SUCCEEDED( SHGetSpecialFolderPathA( NULL, tmp, CSIDL_PERSONAL, FALSE ) ) ) {
					result = tmp;
				}
			}
		}
		break;

		case System::cdUserTemp : {
			
			if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
				result = getEnvironmentVariable( "TEMP" );
				/*
				HKEY key;
				//HKEY_CURRENT_USER\Environment
				if ( System::isUnicodeEnabled() ) {
					if ( ERROR_SUCCESS == RegOpenKeyExW( HKEY_CURRENT_USER, L"Environment", 0, KEY_READ, &key ) ) {
						DWORD type = 0;
						DWORD size = 0;
						RegQueryValueExW( key, L"TEMP", 0, &type, NULL, &size );
						if ( size > 0 ) {
							BYTE* buf = NULL;
							buf = new BYTE[(size+1)*sizeof(VCF::WideChar)];
							memset( buf, 0, (size+1)*sizeof(VCF::WideChar) );
							if ( ERROR_SUCCESS == RegQueryValueExW( key, L"TEMP", 0, &type, buf, &size ) ) {								
								result = (VCF::WideChar*)buf;
							}
						}
					}
				}
				else {
					if ( ERROR_SUCCESS == RegOpenKeyExA( HKEY_CURRENT_USER, "Environment", 0, KEY_READ, &key ) ) {
						DWORD type = 0;
						DWORD size = 0;
						RegQueryValueExA( key, "TEMP", 0, &type, NULL, &size );
						if ( size > 0 ) {
							BYTE* buf = NULL;
							buf = new BYTE[size+1];
							memset( buf, 0, (size+1)*sizeof(BYTE) );
							if ( ERROR_SUCCESS == RegQueryValueExA( key, "TEMP", 0, &type, buf, &size ) ) {
								buf[size] = 0;
								result = (char*)buf;
							}
						}
					}
				}
				*/
			}
			else {
				result = getEnvironmentVariable( "TEMP" );
			}

			if ( !result.empty() ) {
				if ( System::isUnicodeEnabled() ) {
					VCF::WideChar tmp[MAX_PATH];
					if ( GetLongPathNameW( result.c_str(), tmp, MAX_PATH ) ) {
						result = tmp;
					}

				}
				else{
					char tmp[MAX_PATH];
					if ( GetLongPathNameA( result.ansi_c_str(), tmp, MAX_PATH ) ) {
						result = tmp;
					}
				}
			}
		}
		break;

		case System::cdSystemPrograms : {			
			result = getEnvironmentVariable( "PROGRAMFILES" );
		}
		break;

		case System::cdSystemTemp : {
			//HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Session Manager\Environment

			if ( VER_PLATFORM_WIN32_NT == osVersion.dwPlatformId ) {
				HKEY key;
				//HKEY_CURRENT_USER\Environment
				if ( System::isUnicodeEnabled() ) {
					if ( ERROR_SUCCESS == RegOpenKeyExW( HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment", 0, KEY_READ, &key ) ) {
						DWORD type = 0;
						DWORD size = 0;
						RegQueryValueExW( key, L"TEMP", 0, &type, NULL, &size );
						if ( size > 0 ) {
							BYTE* buf = NULL;
							buf = new BYTE[(size+1)*sizeof(VCF::WideChar)];
							memset( buf, 0, (size+1)*sizeof(VCF::WideChar) );
							if ( ERROR_SUCCESS == RegQueryValueExW( key, L"TEMP", 0, &type, buf, &size ) ) {								
								VCF::WideChar tmp[MAX_PATH];
								ExpandEnvironmentStringsW( (VCF::WideChar*)buf, tmp, MAX_PATH );
								result = tmp;
							}
						}
					}
				}
				else {
					if ( ERROR_SUCCESS == RegOpenKeyExA( HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment", 0, KEY_READ, &key ) ) {
						DWORD type = 0;
						DWORD size = 0;
						RegQueryValueExA( key, "TEMP", 0, &type, NULL, &size );
						if ( size > 0 ) {
							BYTE* buf = NULL;
							buf = new BYTE[size+1];
							memset( buf, 0, (size+1)*sizeof(BYTE) );
							if ( ERROR_SUCCESS == RegQueryValueExA( key, "TEMP", 0, &type, buf, &size ) ) {
								char tmp[MAX_PATH];
								ExpandEnvironmentStringsA( (char*)buf, tmp, MAX_PATH );
								result = tmp;
							}
						}
					}
				}	
			}
			else {
				result = getEnvironmentVariable( "TEMP" );
			}
		}
		break;

		case System::cdSystemRoot : {
			result = getEnvironmentVariable( "SYSTEMROOT" );
		}
		break;
	}

	return result;
}

String Win32SystemPeer::getComputerName()
{
	String result;
	DWORD size = MAX_COMPUTERNAME_LENGTH + 25;
	size -= 1;
	if ( System::isUnicodeEnabled() ) {
		VCF::WideChar tmp[MAX_COMPUTERNAME_LENGTH + 25];
		if ( GetComputerNameW( tmp, &size ) ) {			
			result = tmp;
		}
	}		
	else {
		char tmp[MAX_COMPUTERNAME_LENGTH + 25];
		if ( GetComputerNameA( tmp, &size ) ) {			
			result = tmp;
		}
	}	

	return result;
}


String Win32SystemPeer::getUserName()
{
	String result;

	DWORD size = UNLEN + 25;
	size -= 1;
	if ( System::isUnicodeEnabled() ) {
		VCF::WideChar tmp[UNLEN + 25];
		if ( GetUserNameW( tmp, &size ) ) {			
			result = tmp;
		}
	}		
	else {
		char tmp[UNLEN + 25];
		if ( GetUserNameA( tmp, &size ) ) {			
			result = tmp;
		}
	}

	return result;
}

String Win32SystemPeer::createTempFileName( const String& directory )
{
	String result;

	if ( System::isUnicodeEnabled() ) {
		VCF::WideChar tmp[MAX_PATH];
		memset( tmp,0,sizeof(tmp) * sizeof(tmp[0]) );
		::GetTempFileNameW( directory.c_str(), L"tmp", 0, tmp );
		result = tmp;

		WIN32_FIND_DATAW fnd;		
		HANDLE found = ::FindFirstFileW( tmp, &fnd );
		if ( found != INVALID_HANDLE_VALUE ) {
			::FindClose(found);
			::DeleteFileW(tmp);		
		}
	}
	else {
		char tmp[MAX_PATH];
		memset( tmp,0,sizeof(tmp) * sizeof(tmp[0]) );
		::GetTempFileNameA( directory.ansi_c_str(), "tmp", 0, tmp );
		result = tmp;

		WIN32_FIND_DATAA fnd;		
		HANDLE found = ::FindFirstFileA( tmp, &fnd );
		if ( found != INVALID_HANDLE_VALUE ) {
			::FindClose(found);
			::DeleteFileA(tmp);		
		}
	}

	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/02/19 06:50:31  ddiego
*minor updates.
*
*Revision 1.5.2.1  2005/08/01 17:20:46  marcelloptr
*minor changes
*
*Revision 1.5  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:24  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.5  2005/04/09 17:21:35  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.4  2005/03/26 00:10:30  ddiego
*added some minor funs to system class
*
*Revision 1.3.2.3  2005/03/15 01:51:52  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.2  2005/01/08 00:03:45  marcelloptr
*fixed buffer management for GetEnvironmentVariable
*
*Revision 1.3.2.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.6  2004/11/07 19:32:20  marcelloptr
*more documentation
*
*Revision 1.2.2.5  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2.2.4  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.3  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2.2.2  2004/08/26 04:05:48  marcelloptr
*minor change on name of getMillisecond
*
*Revision 1.2.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
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


