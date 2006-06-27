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

uint32 Win32SystemPeer::getTickCount()
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

	OSVERSIONINFO osVersion;
	memset(&osVersion,0,sizeof(osVersion));
		
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
	uint32 y, m, d, h, min, s, ms;
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

	uint32 y = date.getYear();
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
	OSVERSIONINFO osVersion;
	memset(&osVersion,0,sizeof(osVersion));
		
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
	OSVERSIONINFO osVersion;
	memset(&osVersion,0,sizeof(osVersion));
		
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
	OSVERSIONINFO osVersion;
	memset(&osVersion,0,sizeof(osVersion));
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
$Id$
*/
