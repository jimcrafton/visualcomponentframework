//Win32Peer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCFWin32;



unsigned long Win32Utils::translateKeyMask( UINT win32KeyMask )
{
	unsigned long result = VCF::kmUndefined;

	if ( (win32KeyMask & MK_CONTROL) != 0 ){
		result |= VCF::kmCtrl;
	}

	if ( (win32KeyMask & MK_SHIFT) != 0 ){
		result |= VCF::kmShift;
	}

	if ( ::GetAsyncKeyState( VK_MENU ) < 0 ) {
		result |= VCF::kmAlt;
	}

	return result;
}

unsigned long Win32Utils::translateButtonMask( UINT win32ButtonMask )
{
	unsigned long result = VCF::mbmUndefined;

	if ( (win32ButtonMask & MK_LBUTTON) != 0 ){
		result |= VCF::mbmLeftButton;
	}

	if ( (win32ButtonMask & MK_MBUTTON) != 0 ){
		result |= VCF::mbmMiddleButton;
	}

	if ( (win32ButtonMask & MK_RBUTTON) != 0 ){
		result |= VCF::mbmRightButton;
	}

	return result;
}

DWORD Win32Utils::translateStyle( unsigned long style )
{
	DWORD result = 0;
	//if ( (style & ) > 0 ){

	//};
	return result;
}

DWORD Win32Utils::translateExStyle( unsigned long style )
{
	DWORD result = 0;

	return result;
}

/**
*translates the Win32 key code into an actually usable
*structure.
*Specifies the repeat count, scan code, extended-key flag, context code, previous key-state flag,
*and transition-state flag, as shown in the following table.
*Value Description
*	0–15 Specifies the repeat count for the current message.
*	     The value is the number of times the keystroke is autorepeated
*		 as a result of the user holding down the key. If the keystroke is held
*		 long enough, multiple messages are sent. However, the repeat count is not cumulative.
*
*	16–23 Specifies the scan code. The value depends on the original equipment manufacturer (OEM).
*
*	24   Specifies whether the key is an extended key, such as the right-hand ALT and CTRL keys that
*	     appear on an enhanced 101- or 102-key keyboard. The value is 1 if it is an extended key;
*		 otherwise, it is 0.
*
*	25–28 Reserved; do not use.
*
*	29   Specifies the context code. The value is 1 if the ALT key is held down while the
*        key is pressed; otherwise, the value is 0.
*
*	30   Specifies the previous key state. The value is 1 if the key is down before
*        the message is sent, or it is 0 if the key is up.
*	31   Specifies the transition state. The value is 1 if the key is being released, or it
*	     is 0 if the key is being pressed.
*/
KeyboardData Win32Utils::translateKeyData( HWND wndHandle, LPARAM keyData )
{
	KeyboardData result;
	memset( &result, 0, sizeof(KeyboardData) );
	int sum = 0;

	sum = ((BYTE*)&keyData)[2]; //gets bits 16-23

	BYTE keyState[256];
	if ( GetKeyboardState( &keyState[0] ) ){
		result.scanCode = sum;
		result.repeatCount = keyData & 0xFFFF; //mask out the upper 16 bits
		result.altKeyDown = ( keyData & KB_CONTEXT_CODE ) != 0;//replace with #define
		result.isExtendedKey = ( keyData & KB_IS_EXTENDED_KEY ) != 0;
		result.character = 0;

		result.VKeyCode = MapVirtualKey( result.scanCode, 1);



		HKL keyboardLayout = GetKeyboardLayout( GetWindowThreadProcessId( wndHandle, NULL ) );

		ToAsciiEx( result.VKeyCode, result.scanCode, &keyState[0], &result.character, 1, keyboardLayout );

		std::bitset<16> keyBits;
		keyBits = GetAsyncKeyState( VK_SHIFT );
		if ( keyBits[15] == 1 ){
			result.keyMask |= MK_SHIFT;
		}

		keyBits = GetAsyncKeyState( VK_CONTROL );
		if ( keyBits[15] == 1 ){
			result.keyMask |= MK_CONTROL;
		}

		keyBits = GetAsyncKeyState( VK_MENU );
		if ( keyBits[15] == 1 ){
			result.altKeyDown = true;
		}

	}
	return result;
}

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

int Win32Utils::getXFromLParam( LPARAM lParam )
{
	return (int)(short) LOWORD(lParam);
}

int Win32Utils::getYFromLParam( LPARAM lParam )
{
	return (int)(short) HIWORD(lParam);
}

VCF::ulong32 Win32Utils::translateVKCode( UINT vkCode )
{
	VCF::ulong32 result = 0;

	switch ( vkCode ){
		case VK_F1 :{
			result = VCF::vkF1;
		}
		break;

		case VK_F2 :{
			result = VCF::vkF2;
		}
		break;

		case VK_F3 :{
			result = VCF::vkF3;
		}
		break;

		case VK_F4 :{
			result = VCF::vkF4;
		}
		break;

		case VK_F5 :{
			result = VCF::vkF5;
		}
		break;

		case VK_F6 :{
			result = VCF::vkF6;
		}
		break;

		case VK_F7 :{
			result = VCF::vkF7;
		}
		break;

		case VK_F8 :{
			result = VCF::vkF8;
		}
		break;

		case VK_F9 :{
			result = VCF::vkF9;
		}
		break;

		case VK_F10 :{
			result = VCF::vkF10;
		}
		break;

		case VK_F11 :{
			result = VCF::vkF11;
		}
		break;

		case VK_F12 :{
			result = VCF::vkF12;
		}
		break;

		case VK_UP :{
			result = VCF::vkUpArrow;
		}
		break;

		case VK_DOWN :{
			result = VCF::vkDownArrow;
		}
		break;

		case VK_LEFT :{
			result = VCF::vkLeftArrow;
		}
		break;

		case VK_RIGHT :{
			result = VCF::vkRightArrow;
		}
		break;

		case VK_DELETE :{
			result = VCF::vkDelete;
		}
		break;

		case VK_RETURN :{
			result = VCF::vkReturn;
		}
		break;

		case VK_BACK :{
			result = VCF::vkBackSpace;
		}
		break;

		case VK_SPACE :{
			result = VCF::vkSpaceBar;
		}
		break;

		case VK_ESCAPE :{
			result = VCF::vkEscape;
		}
		break;

		case VK_NEXT :{
			result = VCF::vkPgDown;
		}
		break;

		case VK_PRIOR :{
			result = VCF::vkPgUp;
		}
		break;

		case VK_HOME :{
			result = VCF::vkHome;
		}
		break;

		case VK_END :{
			result = VCF::vkEnd;
		}
		break;

		case VK_CONTROL :{
			result = VCF::vkCtrl;
		}
		break;

		case VK_MENU :{
			result = VCF::vkAlt;
		}
		break;

		case VK_SHIFT :{
			result = VCF::vkShift;
		}
		break;

		case VK_TAB :{
			result = VCF::vkTab;
		}
		break;
		//from WINUSER.h
		/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
		case VK_NUMPAD0: case 0x30 :{
			result = VCF::vkNumber0;
		}
		break;

		case VK_NUMPAD1: case 0x31 :{
			result = VCF::vkNumber1;
		}
		break;

		case VK_NUMPAD2: case 0x32 :{
			result = VCF::vkNumber2;
		}
		break;

		case VK_NUMPAD3: case 0x33 :{
			result = VCF::vkNumber3;
		}
		break;

		case VK_NUMPAD4: case 0x34 :{
			result = VCF::vkNumber4;
		}
		break;

		case VK_NUMPAD5: case 0x35 :{
			result = VCF::vkNumber5;
		}
		break;

		case VK_NUMPAD6: case 0x36 :{
			result = VCF::vkNumber6;
		}
		break;

		case VK_NUMPAD7: case 0x37 :{
			result = VCF::vkNumber7;
		}
		break;

		case VK_NUMPAD8: case 0x38 :{
			result = VCF::vkNumber8;
		}
		break;

		case VK_NUMPAD9: case 0x39 :{
			result = VCF::vkNumber9;
		}
		break;

		//from WINUSER.h
		/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */
		case 'A' :{
			result = VCF::vkLetterA;
		}
		break;

		case 'B' :{
			result = VCF::vkLetterB;
		}
		break;

		case 'C' :{
			result = VCF::vkLetterC;
		}
		break;

		case 'D' :{
			result = VCF::vkLetterD;
		}
		break;

		case 'E' :{
			result = VCF::vkLetterE;
		}
		break;

		case 'F' :{
			result = VCF::vkLetterF;
		}
		break;

		case 'G' :{
			result = VCF::vkLetterG;
		}
		break;

		case 'H' :{
			result = VCF::vkLetterH;
		}
		break;

		case 'I' :{
			result = VCF::vkLetterI;
		}
		break;

		case 'J' :{
			result = VCF::vkLetterJ;
		}
		break;

		case 'K' :{
			result = VCF::vkLetterK;
		}
		break;

		case 'L' :{
			result = VCF::vkLetterL;
		}
		break;

		case 'M' :{
			result = VCF::vkLetterM;
		}
		break;

		case 'N' :{
			result = VCF::vkLetterN;
		}
		break;

		case 'O' :{
			result = VCF::vkLetterO;
		}
		break;

		case 'P' :{
			result = VCF::vkLetterP;
		}
		break;

		case 'Q' :{
			result = VCF::vkLetterQ;
		}
		break;
		case 'R' :{
			result = VCF::vkLetterR;
		}
		break;

		case 'S' :{
			result = VCF::vkLetterS;
		}
		break;

		case 'T' :{
			result = VCF::vkLetterT;
		}
		break;

		case 'U' :{
			result = VCF::vkLetterU;
		}
		break;

		case 'V' :{
			result = VCF::vkLetterV;
		}
		break;

		case 'W' :{
			result = VCF::vkLetterW;
		}
		break;

		case 'X' :{
			result = VCF::vkLetterX;
		}
		break;

		case 'Y' :{
			result = VCF::vkLetterY;
		}
		break;

		case 'Z' :{
			result = VCF::vkLetterZ;
		}
		break;

		case VK_SNAPSHOT :{
			result = VCF::vkPrintScreen;
		}
		break;

		case VK_PAUSE :{
			result = VCF::vkPause;
		}
		break;

		case VK_SCROLL :{
			result = VCF::vkScrollLock;
		}
		break;

		case VK_MULTIPLY :{
			result = VCF::vkMultiplySign;
		}
		break;

		case VK_ADD :{
			result = VCF::vkPlusSign;
		}
		break;

		/*
		case VK_SEPARATOR :{
			result = VCF::vkScrollLock;
		}
		break;
		*/

		case VK_SUBTRACT :{
			result = VCF::vkMinusSign;
		}
		break;

		case VK_DECIMAL :{
			result = VCF::vkPeriod;
		}
		break;

		case VK_DIVIDE :{
			result = VCF::vkDivideSign;
		}
		break;		
	}

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

VCF::uint32 Win32Utils::convertCharToVKCode( VCF::VCFChar ch )
{
	VCF::uint32 result = 0;

	ch = tolower( ch );
	switch ( ch ) {
		case 'a' : {
			result = VCF::vkLetterA;
		}
		break;

		case 'b' : {
			result = VCF::vkLetterB;
		}
		break;

		case 'c' : {
			result = VCF::vkLetterC;
		}
		break;

		case 'd' : {
			result = VCF::vkLetterD;
		}
		break;

		case 'e' : {
			result = VCF::vkLetterE;
		}
		break;

		case 'f' : {
			result = VCF::vkLetterF;
		}
		break;

		case 'g' : {
			result = VCF::vkLetterG;
		}
		break;

		case 'h' : {
			result = VCF::vkLetterH;
		}
		break;

		case 'i' : {
			result = VCF::vkLetterI;
		}
		break;

		case 'j' : {
			result = VCF::vkLetterJ;
		}
		break;

		case 'k' : {
			result = VCF::vkLetterK;
		}
		break;

		case 'l' : {
			result = VCF::vkLetterL;
		}
		break;

		case 'm' : {
			result = VCF::vkLetterM;
		}
		break;

		case 'n' : {
			result = VCF::vkLetterN;
		}
		break;

		case 'o' : {
			result = VCF::vkLetterO;
		}
		break;

		case 'p' : {
			result = VCF::vkLetterP;
		}
		break;

		case 'q' : {
			result = VCF::vkLetterQ;
		}
		break;

		case 'r' : {
			result = VCF::vkLetterR;
		}
		break;

		case 's' : {
			result = VCF::vkLetterS;
		}
		break;

		case 't' : {
			result = VCF::vkLetterT;
		}
		break;

		case 'u' : {
			result = VCF::vkLetterU;
		}
		break;

		case 'v' : {
			result = VCF::vkLetterV;
		}
		break;

		case 'w' : {
			result = VCF::vkLetterW;
		}
		break;

		case 'x' : {
			result = VCF::vkLetterX;
		}
		break;

		case 'y' : {
			result = VCF::vkLetterY;
		}
		break;

		case 'z' : {
			result = VCF::vkLetterZ;
		}
		break;

		case '0' : {
			result = VCF::vkNumber0;
		}
		break;

		case '1' : {
			result = VCF::vkNumber1;
		}
		break;

		case '2' : {
			result = VCF::vkNumber2;
		}
		break;

		case '3' : {
			result = VCF::vkNumber3;
		}
		break;

		case '4' : {
			result = VCF::vkNumber4;
		}
		break;

		case '5' : {
			result = VCF::vkNumber5;
		}
		break;

		case '6' : {
			result = VCF::vkNumber6;
		}
		break;

		case '7' : {
			result = VCF::vkNumber7;
		}
		break;

		case '8' : {
			result = VCF::vkNumber8;
		}
		break;

		case '9' : {
			result = VCF::vkNumber9;
		}
		break;

		case '/' : {
			result = VCF::vkDivideSign;
		}
		break;

		case '+' : {
			result = VCF::vkPlusSign;
		}
		break;

		case '-' : {
			result = VCF::vkMinusSign;
		}
		break;

		case '=' : {
			result = VCF::vkEqualsSign;
		}
		break;

		case '_' : {
			result = VCF::vkUnderbar;
		}
		break;

		case '|' : {
			result = VCF::vkUprightBar;
		}
		break;

		case '{' : {
			result = VCF::vkOpenBrace;
		}
		break;

		case '}' : {
			result = VCF::vkCloseBrace;
		}
		break;

		case '[' : {
			result = VCF::vkOpenBracket;
		}
		break;

		case ']' : {
			result = VCF::vkCloseBracket;
		}
		break;

		case '<' : {
			result = VCF::vkLessThan;
		}
		break;

		case '>' : {
			result = VCF::vkGreaterThan;
		}
		break;

		case '.' : {
			result = VCF::vkPeriod;
		}
		break;

		case ',' : {
			result = VCF::vkComma;
		}
		break;

		case '!' : {
			result = VCF::vkExclamation;
		}
		break;

		case '~' : {
			result = VCF::vkTilde;
		}
		break;

		case '`' : {
			result = VCF::vkLeftApostrophe;
		}
		break;

		case '@' : {
			result = VCF::vkCommercialAt;
		}
		break;

		case '#' : {
			result = VCF::vkNumberSign;
		}
		break;

		case '$' : {
			result = VCF::vkDollarSign;
		}
		break;

		case '%' : {
			result = VCF::vkPercent;
		}
		break;

		case '^' : {
			result = VCF::vkCircumflex;
		}
		break;

		case '&' : {
			result = VCF::vkAmpersand;
		}
		break;

		case '*' : {
			result = VCF::vkAsterix;
		}
		break;

		case '(' : {
			result = VCF::vkOpenParen;
		}
		break;

		case ')' : {
			result = VCF::vkCloseParen;
		}
		break;

		case ':' : {
			result = VCF::vkColon;
		}
		break;

		case ';' : {
			result = VCF::vkSemiColon;
		}
		break;

		case '"' : {
			result = VCF::vkDoubleQuote;
		}
		break;

		case '\'' : {
			result = VCF::vkSingleQuote;
		}
		break;

		case '\\' : {
			result = VCF::vkBackSlash;
		}
		break;

		case '?' : {
			result = VCF::vkQuestionMark;
		}
		break;
	}
	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2005/09/30 02:23:46  ddiego
*fixed a bug in the way key board event were handled - does a better job of interpreting key hits on the num pad area.
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


