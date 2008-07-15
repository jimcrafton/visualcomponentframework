//Win32Peer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCFWin32;


void Win32Utils::trace( const VCF::String& text )
{
#ifdef _DEBUG
#ifdef VCF_WIN32CE
	OutputDebugStringW( text.c_str() );
#else
	if ( VCF::System::isUnicodeEnabled() ) {
		OutputDebugStringW( text.c_str() );
	}
	else {
		OutputDebugStringA( text.ansi_c_str() );
	}
#endif
#endif
}

WORD Win32Utils::getWin32LangID( VCF::Locale* locale )
{
	WORD result = MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT );

	return result;
}

VCF::String Win32Utils::getErrorString( const DWORD& errorCode )
{
	VCF::String result;
#ifdef VCF_WIN32CE
	VCF::VCFChar* msgBuf;
	DWORD bufSize = FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									NULL,
									errorCode,
									0, // Default language
									(LPWSTR) &msgBuf,
									0,
									NULL );

	result.append( msgBuf, bufSize );

	// Free the buffer.
	LocalFree( msgBuf );
#else
	if ( VCF::System::isUnicodeEnabled() ) {
		VCF::VCFChar* msgBuf;
		DWORD bufSize = FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
										NULL,
										errorCode,
										0, // Default language
										(LPWSTR) &msgBuf,
										0,
										NULL );

		result.append( msgBuf, bufSize );

		// Free the buffer.
		LocalFree( msgBuf );
	}
	else {
		char* msgBuf;
		DWORD bufSize = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
										NULL,
										errorCode,
										0, // Default language
										(LPSTR) &msgBuf,
										0,
										NULL );

		result.append( msgBuf, bufSize );
		// Free the buffer.
		LocalFree( msgBuf );
	}
#endif

	return result;
}


/**
$Id$
*/
