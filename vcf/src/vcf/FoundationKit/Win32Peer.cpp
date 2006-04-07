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
	if ( VCF::System::isUnicodeEnabled() ) {
		OutputDebugStringW( text.c_str() );
	}
	else {
		OutputDebugStringA( text.ansi_c_str() );
	}

#endif
}

WORD Win32Utils::getWin32LangID( VCF::Locale* locale )
{
	WORD result = MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT );
	/*
	if ( NULL != locale ){
		switch( locale->getCountryCode() ){
			case LOCALE_USA_CODE :{
				if ( locale->getLanguage() == "en" ){
					result = MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US );
				}
			}
			break;
		}
	}
	*/

	return result;
}

VCF::String Win32Utils::getErrorString( const DWORD& errorCode )
{
	VCF::String result;

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


	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2005/11/21 21:28:06  ddiego
*updated win32 code a bit due to osx changes.
*
*Revision 1.3.2.1  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.3  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/02/17 04:06:36  ddiego
*fixed bug in handling wm_keydown event in win32edit
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.19.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.19  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.17.6.3  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.17.6.2  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.17.6.1  2004/01/18 04:52:46  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.17  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.1  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.8.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.15  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.14.6.1  2002/09/10 04:07:48  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.14  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.13  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.12  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


