//Win32ResourceBundle.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ResourceBundle.h"


using namespace VCF;


BOOL CALLBACK Win32ResourceBundle_EnumResTypeProc( HMODULE hModule, LPTSTR lpszType, LPARAM lParam );
BOOL CALLBACK Win32ResourceBundle_EnumResNameProc( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam );

static bool foundResName = false;
static String foundResType="Hello";

Win32ResourceBundle::Win32ResourceBundle()
{
	appPeer_ = NULL;
}

Win32ResourceBundle::~Win32ResourceBundle()
{

}

String Win32ResourceBundle::getString( const String& resourceName )
{
	HINSTANCE hinst = getResourceInstance();
	String result;
	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( hinst, resourceName.c_str(), String(RT_RCDATA).c_str() );
	}
	else {
		resHandle = ::FindResourceA( hinst, resourceName.ansi_c_str(), RT_RCDATA );
	}

	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( hinst, resHandle );
		if ( NULL != data ){
			TCHAR* strData = (TCHAR*)::LockResource( data );
			result = strData;
			::FreeResource( data );
		}
	}
	else {
		bool failed = false;
		//try and see if the resourceName is an int id and find it via 
		//throw exception- resource not found !!!!
		uint32 stringID = StringUtils::fromStringAsUInt(resourceName);
		if ( stringID > 0 ) {
			if ( System::isUnicodeEnabled() ) {
				wchar_t tmp[256];
				int ret = ::LoadStringW( hinst, stringID, tmp, 255 );
				if ( ret ) {
					tmp[ret] = 0;
					result = tmp;
				}				
			}
			else {
				char tmp[256];
				int ret = ::LoadStringA( hinst, stringID, tmp, 255 );
				if ( ret ) {
					tmp[ret] = 0;
					result = tmp;
				}
			}			
		}
		else {
			failed = true;
		}

		if ( failed ) {
			//throw exception???
		}
	}
	return result;
}

String Win32ResourceBundle::getVFF( const String& resourceName )
{
	String result;
	HRSRC resHandle = NULL;
	if ( System::isUnicodeEnabled() ) {
		resHandle = ::FindResourceW( getResourceInstance(), resourceName.c_str(), L"VFF" );
	}
	else {
		resHandle = ::FindResourceA( getResourceInstance(), resourceName.ansi_c_str(), "VFF" );
	}

	if ( NULL != resHandle ){
		HGLOBAL	data = ::LoadResource( NULL, resHandle );
		if ( NULL != data ){
			void* dataPtr = ::LockResource( data );
			TCHAR* strData = (TCHAR*)dataPtr;
			int size = SizeofResource( getResourceInstance(), resHandle );
			result = strData;
			int resSize = result.size();
			void *tmp = dataPtr;
			/**
			*this is here to properly skip over '\0' characters in the stream
			*/
			while ( resSize < size ){
				tmp = (void*)((char*)dataPtr + resSize + 1);
				strData = (TCHAR*)tmp;
				result += "\n";
				result += strData;
				resSize = result.size();
			}
			::FreeResource( data );
		}
	}
	else {
		//throw exception- resource not found !!!!
	}
	return result;
}

Image* Win32ResourceBundle::getImage( const String& resourceName )
{
	HBITMAP resBMP = NULL;
	if ( System::isUnicodeEnabled() ) {
		resBMP = (HBITMAP)LoadImageW( getResourceInstance(), resourceName.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
	}
	else {
		resBMP = (HBITMAP)LoadImageA( getResourceInstance(), resourceName.ansi_c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
	}

	//LoadBitmap( getResourceInstance(), resourceName.c_str() );
	if ( NULL != resBMP ){
		return new Win32Image( resBMP );
	}
	else {
		//throw exception- resource not found !!!!
	}
	return NULL;
}

Resource* Win32ResourceBundle::getResource( const String& resourceName )
{
	foundResName = false;
	foundResType = "\0";

	::EnumResourceTypes( getResourceInstance(),
		                 Win32ResourceBundle_EnumResTypeProc,
						 (LPARAM)resourceName.c_str() );
	if ( true == foundResName ){
		HRSRC resHandle = NULL;

		if ( System::isUnicodeEnabled() ) {
			resHandle = ::FindResourceW( getResourceInstance(),
			                              resourceName.c_str(),
										  foundResType.c_str() );
		}
		else {
			resHandle = ::FindResourceA( getResourceInstance(),
			                              resourceName.ansi_c_str(),
										  foundResType.ansi_c_str() );
		}

		if ( NULL != resHandle ){
			HGLOBAL	dataHandle = ::LoadResource( NULL, resHandle );
			if ( NULL != dataHandle ){
				void* data = ::LockResource( dataHandle );
				int size = ::SizeofResource( getResourceInstance(), resHandle );
				return new Resource( data, size, resourceName );
			}
		}
		else {
			//throw exception- resource not found !!!!
		}
	}
	return NULL;
}

BOOL CALLBACK Win32ResourceBundle_EnumResTypeProc( HMODULE hModule, LPTSTR lpszType, LPARAM lParam )
{
	return ::EnumResourceNames( hModule,
		                        lpszType,
								Win32ResourceBundle_EnumResNameProc,
								lParam );
}

BOOL CALLBACK Win32ResourceBundle_EnumResNameProc( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam )
{
	BOOL result = TRUE;
	const String resName( (TCHAR*)lParam );
	if ( resName == lpszName ){
		foundResName = true;
		foundResType = lpszType;
		result = FALSE;
	}
	return result;
}

HINSTANCE Win32ResourceBundle::getResourceInstance()
{
	HINSTANCE result = NULL;
	if ( NULL != this->appPeer_ ) {
		result = (HINSTANCE)appPeer_->getHandleID();
	}
	else {
		//throw exception !!
	}
	return result;
}


/**
$Id$
*/
