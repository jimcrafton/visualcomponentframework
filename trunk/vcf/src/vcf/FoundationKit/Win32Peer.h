#ifndef _VCF_WIN32PEER_H__
#define _VCF_WIN32PEER_H__
//Win32Peer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*Main header for implementation object that Win32 headers
*/


/*
these include have now been moved to FrameworkConfig.h
#include <windows.h>
#include <commctrl.h> //make sure to link with comctl32.lib
#include <shlobj.h>
*/



namespace VCFWin32 {

struct KeyboardData {
	int repeatCount;
	int scanCode;
	bool isExtendedKey;
	bool altKeyDown;
	unsigned short character;
	int VKeyCode;
	UINT keyMask;
};

#define KB_CONTEXT_CODE			29
#define KB_PREVIOUS_STATE		30
#define KB_IS_EXTENDED_KEY		24

#define SHIFT_KEY_DOWN \
	((GetKeyState( VK_SHIFT) & 15 ) == 1)

#define VCF_MESSAGE				WM_APP	+ 100
#define VCF_CONTROL_CREATE		VCF_MESSAGE + 99


/**
*what follows are a set of standard utility functions for Win32
*/
class FOUNDATIONKIT_API Win32Utils {

public:
	static unsigned long translateKeyMask( UINT win32KeyMask );

	static unsigned long translateButtonMask( UINT win32ButtonMask );

	static KeyboardData translateKeyData( HWND wndHandle, LPARAM keyData );

	static DWORD translateStyle( unsigned long style );

	static DWORD translateExStyle( unsigned long style );

	static void trace( const VCF::String& text );

	static WORD	getWin32LangID( VCF::Locale* locale );

	static int getXFromLParam( LPARAM lParam );

	static int getYFromLParam( LPARAM lParam );

	static VCF::ulong32 translateVKCode( UINT vkCode );

	static VCF::String getErrorString( const DWORD& errorCode );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/20 02:27:44  ddiego
*fixes for single line text and formatting problems in text window creation.
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
*Revision 1.1.2.2  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.1  2004/06/05 01:18:41  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.6.2  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9.6.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32PEER_H__


