//Win32LibraryPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

Win32LibraryPeer::Win32LibraryPeer()
{
	libHandle_ = NULL;
}

Win32LibraryPeer::~Win32LibraryPeer()
{
	libHandle_ = NULL;
}


void Win32LibraryPeer::load( const String& libraryFilename )
{
	if ( System::isUnicodeEnabled() ) {
		libHandle_ = LoadLibraryW( libraryFilename.c_str() );
	}
	else {
		libHandle_ = LoadLibraryA( libraryFilename.ansi_c_str() );
	}


	if ( NULL == libHandle_ ){
		String error = "Win32LibraryPeer::load() exception: \nError loading \"" + libraryFilename + "\"\n" +
				VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}
}

void* Win32LibraryPeer::getFunction( const String& functionName )
{
	void* result = NULL;

	if ( NULL == libHandle_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	}

#ifdef VCF_WIN32CE
	result = (void*)GetProcAddress( libHandle_, functionName.c_str() );	
#else
	result = (void*)GetProcAddress( libHandle_, functionName.ansi_c_str() );
#endif

	if ( NULL == result ){
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}

	return result;
}

void Win32LibraryPeer::unload()
{
	if ( NULL == libHandle_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	}

	BOOL freeLibResult = FreeLibrary( libHandle_ );

	if ( FALSE == freeLibResult ){
		String error = VCFWin32::Win32Utils::getErrorString( GetLastError() );
		throw RuntimeException( error );
	}
}


/**
$Id$
*/
