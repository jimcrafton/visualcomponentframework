//Win32ToolKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ToolKit.h"
#include "vcf/ApplicationKit/Win32Application.h"
#include "vcf/ApplicationKit/Win32Edit.h"
#include "vcf/ApplicationKit/HeaderControl.h"
#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Win32Listview.h"
#include "vcf/ApplicationKit/Win32Dialog.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"
#include "vcf/ApplicationKit/Win32MenuBar.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/Win32ControlContext.h"
#include "vcf/ApplicationKit/Win32FileOpenDialog.h"
#include "vcf/ApplicationKit/Win32FileSaveDialog.h"
#include "vcf/ApplicationKit/Win32ColorDialog.h"
#include "vcf/ApplicationKit/Win32FolderBrowseDialog.h"
#include "vcf/ApplicationKit/Win32DropTargetPeer.h"
#include "vcf/ApplicationKit/Win32Clipboard.h"
#include "vcf/ApplicationKit/Win32PopupMenu.h"
#include "vcf/ApplicationKit/Win32FontDialog.h"
#include "vcf/ApplicationKit/Win32UIShell.h"
#include "vcf/ApplicationKit/Win32ScrollPeer.h"
#include "vcf/ApplicationKit/Win32CursorPeer.h"
#include "vcf/ApplicationKit/LightweightComponent.h"
#include "vcf/ApplicationKit/Win32Component.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32DragDropPeer.h"
#include "vcf/ApplicationKit/Win32COMUtils.h"
#include "vcf/ApplicationKit/Win32Toolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/SystemTrayPeer.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/Win32AppResourceBundle.h"

#include <shellapi.h>
#include "vcf/ApplicationKit/Win32SystemTrayPeer.h"

//printing
#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/ApplicationKit/Win32PrintDialog.h"


#include "vcf/ApplicationKit/Win32TextPeer.h"

#include "vcf/ApplicationKit/MenuManagerPeer.h"
#include "vcf/ApplicationKit/Win32MenuManagerPeer.h"



#include "thirdparty/win32/Microsoft/htmlhelp.h"

#include "vcf/GraphicsKit/Win32VisualStylesWrapper.h"

#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/Win32PopupWindowPeer.h"

#include "vcf/ApplicationKit/TransparentWindowPeer.h"
#include "vcf/ApplicationKit/Win32TransparentWindowPeer.h"

#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/Win32DropDownPeer.h"




typedef HWND  (WINAPI *HtmlHelpW_Func)(HWND hwndCaller, LPCWSTR pszFile, UINT uCommand, DWORD_PTR dwData );
typedef HWND (WINAPI *HtmlHelpA_Func)(HWND hwndCaller, LPCSTR pszFile, UINT uCommand, DWORD_PTR dwData );




static HtmlHelpW_Func HtmlHelp_W = NULL;
static HtmlHelpA_Func HtmlHelp_A = NULL;
static HMODULE HtmlHelpLibHandle = NULL;




static HWND LastHTMLHelpWnd = NULL;

using namespace VCF;
using namespace VCFWin32;


#define TOOLTIP_TIMERID					30565
#define TOOLTIP_TIMEOUT_TIMERID			30566

static UINT ToolTipTimerID = 0;
static UINT ToolTipTimoutTimerID = 0;

static UINT VCF_POST_EVENT = 0;

HINSTANCE Win32ToolKit_toolkitHInstance = NULL;
static HHOOK Win32ToolKit_mouseHook = NULL;
static HHOOK Win32ToolKit_kbHook = NULL;


UINT Win32ToolKit::AreUMeMessage = 0xFFFFFFFF;
const UINT Win32ToolKit::RestoreSingleInstAppMessage = 
	::RegisterWindowMessageA("RestoreSingleInstAppMessage-32270e92-b3fc-4c12-9027-26810a01b100");	

static String RestoreSingleInstAppCmdLine;



#ifndef _LIB //DLL Linkage...

extern "C" BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:  {
			Win32ToolKit_toolkitHInstance = (HINSTANCE)hModule;
		}
		break;

		case DLL_THREAD_ATTACH: {

		}
		break;

		case DLL_THREAD_DETACH:  {

		}
		break;

		case DLL_PROCESS_DETACH:  {

		}
		break;
    }
    return TRUE;
}

#endif


















using namespace VCFWin32;



uint32 Win32UIUtils::translateKeyMask( UINT win32KeyMask )
{
	uint32 result = VCF::kmUndefined;

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

uint32 Win32UIUtils::translateButtonMask( UINT win32ButtonMask )
{
	uint32 result = VCF::mbmUndefined;

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

DWORD Win32UIUtils::translateStyle( uint32 style )
{
	DWORD result = 0;
	//if ( (style & ) > 0 ){

	//};
	return result;
}

DWORD Win32UIUtils::translateExStyle( uint32 style )
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
KeyboardData Win32UIUtils::translateKeyData( HWND wndHandle, LPARAM keyData )
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



int Win32UIUtils::getXFromLParam( LPARAM lParam )
{
	return (int)(short) LOWORD(lParam);
}

int Win32UIUtils::getYFromLParam( LPARAM lParam )
{
	return (int)(short) HIWORD(lParam);
}

VCF::uint32 Win32UIUtils::translateVKCode( UINT vkCode )
{
	VCF::uint32 result = 0;

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


VCF::uint32 Win32UIUtils::convertCharToVKCode( VCF::VCFChar ch )
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




//UIPolicyManager implementation

class Win32UIPolicyManager : public UIPolicyManager {
public:
	Win32UIPolicyManager() {

	}

	virtual ~Win32UIPolicyManager() {

	}

	virtual Rect adjustInitialDialogBounds( Dialog* dialog ) {
		Rect result;
		Control* owner = dialog->getOwner();
		if ( NULL != owner ) {
			result.left_ = owner->getLeft() + ( owner->getWidth()/2.0 - dialog->getWidth()/2.0 );
			result.top_ = owner->getTop() + ( owner->getHeight()/2.0 - dialog->getHeight()/2.0 );
			result.right_ = result.left_ + dialog->getWidth();
			result.bottom_ = result.top_ + dialog->getHeight();
			if ( NULL != owner->getParent() ) {
				owner->translateToScreenCoords( &result );				
			}

			double w = result.getWidth();
			double h = result.getHeight();
			RECT r;
			SystemParametersInfo( SPI_GETWORKAREA, 0, &r, 0 );
			if ( r.left > result.left_ ) {
				result.left_ = r.left;
				result.right_ = result.left_ + w;
			}

			if ( r.top > result.top_ ) {
				result.top_ = r.top;
				result.bottom_ = result.top_ + h;
			}

			if ( r.right < result.right_ ) {
				result.right_ = r.right;
				result.left_ = result.right_ - w;
			}

			if ( r.bottom < result.bottom_ ) {
				result.bottom_ = r.bottom;
				result.top_ = result.bottom_ - h;
			}
		}

		

		return result;
	}

	virtual Frame* getOwnerForDialog() {
		Frame* result = NULL;
		Frame* activeFrame = Frame::getActiveFrame();

		Application* app = Application::getRunningInstance();

		if ( NULL != activeFrame ) {
			result = activeFrame;
		}
		else if ( NULL != app ) {
			result = app->getMainWindow();
		}

		return result;
	}

	/**
	* merges two menus by adding to the menu items of windowMenu
	* all the items and subitems of appMenu that are not in windowMenu.
	*/
	virtual void mergeMenus( Menu* appMenu, Menu* windowMenu ) {
		MenuItem* windowRoot = windowMenu->getRootMenuItem();
		MenuItem* appRoot = appMenu->getRootMenuItem();
		// add all the first level menu items from appMenu to windowMenu
		Enumerator<MenuItem*>* appChildren = appRoot->getChildren();
		while ( appChildren->hasMoreElements() ) {
			MenuItem* child = appChildren->nextElement();

			MenuItem* matchingChild = getMatchingMenuItem( child, windowRoot );
			if ( NULL == matchingChild ) {
				matchingChild = (MenuItem*)child->clone();// new DefaultMenuItem2( child->getCaption(), windowRoot, windowRoot->getMenuOwner() );
				matchingChild->setMenuOwner( windowRoot->getMenuOwner() );

				String caption = StringUtils::lowerCase( matchingChild->getCaption() );

				if ( String::npos != caption.find( "file" ) ) {
					windowRoot->insertChild( 0, matchingChild );
				}
				else if ( String::npos != caption.find( "edit" ) ) {
					windowRoot->insertChild( 1, matchingChild );
				}
				else {
					windowRoot->addChild( matchingChild );
				}
			}

			// now merges the subitems of the first level menu items
			copyMenuItems( child, matchingChild );

		}
	}

	/**
	*
	*/
	virtual String transformMnemonicValues( const String& input ) {
		return input;
	}

	virtual AcceleratorKey::Value getStandardAcceleratorFor( const StandardAccelerator& val ) {
		AcceleratorKey::Value result;

		switch ( val ) {
			case UIPolicyManager::saApplicationQuit : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterQ );
			}
			break;

			case UIPolicyManager::saApplicationAbout : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterQ );
			}
			break;

			case UIPolicyManager::saApplicationPreferences : {

			}
			break;

			case UIPolicyManager::saFileNew : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterN );
			}
			break;

			case UIPolicyManager::saFileOpen : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterO );
			}
			break;

			case UIPolicyManager::saFileSave : {
				result = AcceleratorKey::Value( kmCtrl,vkLetterS );
			}
			break;

			case UIPolicyManager::saFileSaveAs : {
				result = AcceleratorKey::Value( kmCtrl | kmShift,vkLetterS );
			}
			break;

			case UIPolicyManager::saFilePrint : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterP );
			}
			break;

			case UIPolicyManager::saFilePageSetup : {

			}
			break;

			case UIPolicyManager::saEditUndo : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterZ );
			}
			break;

			case UIPolicyManager::saEditRedo : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterY );
			}
			break;

			case UIPolicyManager::saEditCut : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterX );
			}
			break;

			case UIPolicyManager::saEditCopy : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterC );
			}
			break;

			case UIPolicyManager::saEditPaste : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterV );
			}
			break;

			case UIPolicyManager::saEditDelete : {
				result = AcceleratorKey::Value( kmUndefined, vkDelete );
			}
			break;

			case UIPolicyManager::saEditSelectAll : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterA );
			}
			break;

			case UIPolicyManager::saEditFind : {
				result = AcceleratorKey::Value( kmCtrl, vkLetterF );
			}
			break;

			case UIPolicyManager::saEditFindNext : {
				result = AcceleratorKey::Value( kmUndefined, vkF3 );
			}
			break;

			case UIPolicyManager::saHelpContents : {
				result = AcceleratorKey::Value( kmUndefined, vkF1 );
			}
			break;
		}

		return result;
	}
protected:

	/**
	* adds to the menu items of windowItem all the items of appItem that are not in windowItem.
	* In other words, it appends all the submenu items of appItem as subitems of the windowItem
	* except for the subitems already existing in the subitems of the windowItem.
	*@param MenuItem* appItem, the menu item in the 'source' menu
	*@param MenuItem* windowItem, the menu item in the 'destination' menu
	*/
	void copyMenuItems( MenuItem* appItem, MenuItem* windowItem ) {

		Enumerator<MenuItem*>* appChildren = appItem->getChildren();
		while ( appChildren->hasMoreElements() ) {
			MenuItem* child = appChildren->nextElement();

			if ( NULL == getMatchingMenuItem( child, windowItem ) ) {
				MenuItem* newChild = (MenuItem*)child->clone();
				newChild->setMenuOwner( windowItem->getMenuOwner() );
				windowItem->addChild( newChild );

					//new DefaultMenuItem( child->getCaption(), windowItem, windowItem->getMenuOwner() );
				//we need to be able to copy over event handlers??? HOW ?????

			}
		}
	}


	/**
	* search between the subitems of appItem a subitem having the same caption
	* or the same tag of the window's item to search,
	* no search is performed if appItem is a menu separator.
	*@param MenuItem* appItem, the menu item in the 'source' menu
	*@param MenuItem* windowItemToSearch, the menu item to search
	*/
	MenuItem* getMatchingMenuItem( MenuItem* appItem, MenuItem* windowItemToSearch ) {
		MenuItem* result = NULL;

		Enumerator<MenuItem*>* children = windowItemToSearch->getChildren();
		while ( children->hasMoreElements() ) {


			MenuItem* child = children->nextElement();

			String appItemCaption   = StringUtils::eraseRightOfChar( appItem->getCaption(), '\t', true );
			String childItemCaption = StringUtils::eraseRightOfChar( child->getCaption(), '\t', true );

			if ( ( childItemCaption == appItemCaption ) && (!child->isSeparator()) ) {
				result = child;
				break;
			}
			else if ( (child->getTag() == appItem->getTag()) && (child->getTag()!= -1) ) {
				result = child;
				break;
			}
			else if ( appItem->isSeparator() && child->isSeparator() ) {
				result = NULL;
				break;
			}
		}

		return result;
	}
};


#define CXGAP				1		// num pixels between button and text
#define CXTEXTMARGIN		2		// num pixels after hilite to start text
#define CXBUTTONMARGIN		2		// num pixels wider button is than bitmap
#define CYBUTTONMARGIN		2		// ditto for height

//UIMetricsManager implementation
class Win32UIMetricsManager : public UIMetricsManager {
public:

	static Point DLUToPixel( const Point& dlu, VCF::Font& font ) {
		Point result;
		HDC dc = GetDC( ::GetDesktopWindow() );

		int baseUnitY = 0;
		int cx = 0;

		HFONT hf = NULL;
		HFONT old = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectW( lf );


			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICW tm;
			GetTextMetricsW( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointW( dc,
								L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectA( lf );

			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICA tm;
			GetTextMetricsA( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointA( dc,
								"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}




		int baseUnitX = (cx / 26 + 1) / 2;
		result.x_ = MulDiv(dlu.x_, baseUnitX, 4);
		result.y_ = MulDiv(dlu.y_, baseUnitY, 8);

		//(dlu.x_ * baseUnitX) / 4;
		//result.y_  = (dlu.y_ * baseUnitY) / 8;

		SelectObject(dc, old );
		DeleteObject( hf );
		ReleaseDC( ::GetDesktopWindow(), dc );


		return result;
	}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result;

		NONCLIENTMETRICSA ncm;
		memset( &ncm, 0, sizeof(ncm) );

		ncm.cbSize = sizeof(ncm);

		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_MENUTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
				//
			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_HIGHLIGHTTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftControlFont :  case UIMetricsManager::ftSystemFont : {
				//do nothing the Win32Font already is initialized ot this by default
				result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
			}
			break;

			case UIMetricsManager::ftMessageFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMessageFont.lfFaceName ) ;
					result.setBold( ncm.lfMessageFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
					result.setItalic( ncm.lfMessageFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMessageFont.lfHeight );
					result.setStrikeOut( ncm.lfMessageFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMessageFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftToolTipFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfStatusFont.lfFaceName ) ;
					result.setBold( ncm.lfStatusFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_INFOTEXT ) ) );
					result.setItalic( ncm.lfStatusFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfStatusFont.lfHeight );
					result.setStrikeOut( ncm.lfStatusFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfStatusFont.lfUnderline ? true : false );
				}
			}
			break;
		}

		return result;
	}

/*
	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;

		result.width_ = ::GetSystemMetrics( SM_CXHTHUMB )*0.85+1;
		result.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;

		NONCLIENTMETRICSA ncInfo;
		ncInfo.cbSize = sizeof(ncInfo);
		::SystemParametersInfoA (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
		HFONT menuHFont = CreateFontIndirectA( &ncInfo.lfMenuFont );
		if ( NULL != menuHFont ) {
			HDC dc = ::CreateCompatibleDC( NULL );// screen DC--I won't actually draw on it
			HFONT oldFont = (HFONT)SelectObject( dc, menuHFont );
			RECT rcText = {0,0,0,0};
			if ( System::isUnicodeEnabled() ) {
				::DrawTextW( dc, caption.c_str(), caption.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}
			else {
				AnsiString tmp = caption;
				::DrawTextA( dc, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}


			SelectObject( dc, oldFont );

			// height of item is just height of a standard menu item
			result.height_ = maxVal<double>( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );

			const int CXGAP = 1;		// num pixels between button and text
			const int CXTEXTMARGIN = 2;		// num pixels after hilite to start text
			const int CXBUTTONMARGIN = 2;		// num pixels wider button is than bitmap
			const int CYBUTTONMARGIN = 2;		// ditto for height

			// width is width of text plus a bunch of stuff
			int cx = rcText.right - rcText.left;	// text width
			cx += CXTEXTMARGIN << 1;		// L/R margin for readability
			cx += CXGAP;					// space between button and menu text

			//cx += szButton_.cx<<1;		// button width (L=button; R=empty margin)

			// whatever value I return in lpms->itemWidth, Windows will add the
			// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
			//
			cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
			result.width_ = cx;		// done deal

			::DeleteObject( menuHFont );
			::DeleteDC( dc );
		}

		return result;
	}
*/
	virtual double getValue( const MetricType& type, const String& text, Font* alternateFont ) {		
		double result = 0;

		switch ( type ) {
			case mtLabelHeight : {				
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,8), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,8), f );
				}
				result = pt.y_;
			}
			break;

			case mtComboBoxHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,14), f );
				}
				result = pt.y_;
			}
			break;

			case mtListItemHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;
			}
			break;

			case mtButtonHeight : {			
				
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					RECT r;
					memset(&r,0,sizeof(r));
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_PUSHBUTTON, PBS_NORMAL, 
																&r, TS_TRUE, &sz);

					MARGINS m = {0};
					Win32VisualStylesWrapper::GetThemeMargins( theme, dc, BP_PUSHBUTTON, 0, TMT_CONTENTMARGINS, NULL, &m );

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					//sz.cy += m.cyTopHeight + m.cyBottomHeight;
					result = sz.cy;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,14), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,14), f );
					}

					result = pt.y_;
				}
			}
			break;

			case mtRadioBoxHeight : {			
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				
				result = pt.y_;				
			}
			break;

			case mtCheckBoxHeight : {				
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;				
			}
			break;

			case mtToolTipHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;
			}
			break;

			case mtSeparatorHeight : {
				result = 2.0;
			}
			break;

			case mtHeaderHeight : {
				HTHEME theme = NULL;
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"Header" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					RECT r;
					memset(&r,0,sizeof(r));
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, HP_HEADERITEM, HIS_NORMAL, 
																&r, TS_TRUE, &sz);

					MARGINS m = {0};
					Win32VisualStylesWrapper::GetThemeMargins( theme, dc, HP_HEADERITEM, 0, TMT_CONTENTMARGINS, NULL, &m );

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					sz.cy += m.cyTopHeight + m.cyBottomHeight;
					result = sz.cy;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,10), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,10), f );
					}
					result = pt.y_;
				}
			}
			break;

			case mtTreeItemHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,9), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,9), f );
				}
				result = pt.y_;
			}
			break;

			case mtTextControlHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,12), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,12), f );
				}
				result = pt.y_;
			}
			break;

			case mtVerticalProgressWidth : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(14,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(14,14), f );
				}
				result = pt.x_;
			}
			break;

			case mtHorizontalProgressHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,14), f );
				}
				result = pt.y_;
			}
			break;

			case mtInformationalControlHeight : {
				
				HTHEME theme = NULL;
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					//theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"STATUS" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					HRESULT hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SP_PANE, 0, 
						NULL, TS_TRUE, &sz);
					
					MARGINS m = {0};
					hr = Win32VisualStylesWrapper::GetThemeMargins(theme, dc, SP_PANE,0,TMT_CONTENTMARGINS,
						NULL, &m );

					int h = 0;
					hr = Win32VisualStylesWrapper::GetThemeMetric(theme,dc,SP_GRIPPER,1,TMT_HEIGHT,&h);
					

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy + 10;// + m.;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,14), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,14), f );
					}
					result = pt.y_;
				}
				
			}
			break;

			case mtVerticalScrollbarThumbWidth : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_THUMBBTNVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cx;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollWidth;
				}
			}
			break;

			case mtHorizontalScrollbarThumbHeight : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_THUMBBTNHORZ, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollHeight;
				}
			}
			break;

			case mtVerticalScrollbarWidth : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_LOWERTRACKVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cx;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollWidth;
				}
			}
			break;

			case mtHorizontalScrollbarHeight : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_LOWERTRACKHORZ, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollHeight;
				}
			}
			break;

			case mtMenuIndent : {

				result = (double) ::GetSystemMetrics( SM_CXMENUCHECK ) + CXGAP + CXTEXTMARGIN;
			}
			break;

			case mtMenuSeparatorHeight : {
				result = 2;//????? Guestimate????
			}
			break;

			case mtMenuBarHeight : {
				NONCLIENTMETRICS ncm;
				memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
				ncm.cbSize = sizeof(NONCLIENTMETRICS);
				
				SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
				
				result = ncm.iMenuHeight;
			}
			break;

			

			case mtWindowBorderDelta : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,7), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,7), f );
				}

				result = pt.y_;
			}
			break;

			case mtContainerBorderDelta : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,7), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,7), f );
				}
				result = pt.y_;
			}
			break;

			case mtControlVerticalSpacing : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			case mtControlHorizontalSpacing : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(4,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(4,4), f );
				}
				result = pt.x_;
			}
			break;

			case mtInformationControlTopSpacer : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			case mtInformationControlBottomSpacer : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}

	virtual Size getSize( const MetricType& type, const String& text, Font* alternateFont ) {
		Size result;
		
		switch ( type ) {
			case mtMenuItemSize : {
				NONCLIENTMETRICSA ncInfo;
				ncInfo.cbSize = sizeof(ncInfo);
				::SystemParametersInfoA (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
				HFONT menuHFont = CreateFontIndirectA( &ncInfo.lfMenuFont );
				if ( NULL != menuHFont ) {
					HDC dc = ::CreateCompatibleDC( NULL );// screen DC--I won't actually draw on it
					HFONT oldFont = (HFONT)SelectObject( dc, menuHFont );
					RECT rcText = {0,0,0,0};
					if ( System::isUnicodeEnabled() ) {
						::DrawTextW( dc, text.c_str(), text.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
					}
					else {
						AnsiString tmp = text;
						::DrawTextA( dc, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
					}
					
					
					SelectObject( dc, oldFont );
					
					// height of item is just height of a standard menu item
					result.height_ = maxVal<double>( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );
					
					
					// width is width of text plus a bunch of stuff
					int cx = rcText.right - rcText.left;	// text width
					cx += CXTEXTMARGIN << 1;		// L/R margin for readability
					cx += CXGAP;					// space between button and menu text
					
					int cxButn = result.height_;				// width of button

					cx += cxButn;//<<1;		// button width (L=button; R=empty margin)
					
					// whatever value I return in lpms->itemWidth, Windows will add the
					// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
					//
					cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
					result.width_ = cx;		// done deal
					
					::DeleteObject( menuHFont );
					::DeleteDC( dc );
				}
			}
			break;

			case mtMenuItemSeparatorSize : {
				result.height_ = GetSystemMetrics(SM_CYMENU)>>1;
				result.width_  = 0;
			}
			break;

			case mtVerticalSliderThumbSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TKP_THUMBVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					Point pt = DLUToPixel( Point(15,15), f );
					
					result.height_ = 11;
					result.width_ = pt.x_;
				}
			}
			break;

			case mtHorizontalSliderThumbSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TKP_THUMB, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					Point pt = DLUToPixel( Point(0,15), f );
					
					result.height_ = pt.y_;
					result.width_ = 11;
				}
			}
			break;

			case mtTabSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					int dcs = SaveDC(dc);
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					HFONT font = NULL;	
					SIZE textSz;
					memset(&textSz,0,sizeof(textSz));

					if ( System::isUnicodeEnabled() ) {
						LOGFONTW* lf = (LOGFONTW*) f.getFontPeer()->getFontHandleID();
						font = ::CreateFontIndirectW( lf );
						::SelectObject( dc, font );
						
						if ( text.empty() ) {
							::GetTextExtentPoint32W( dc, L"EM", 2, &textSz );
						}
						else {
							::GetTextExtentPoint32W( dc, text.c_str(), text.size(), &textSz );
						}
					}
					else {
						LOGFONTA* lf = (LOGFONTA*) f.getFontPeer()->getFontHandleID();
						AnsiString s = text;
						font = ::CreateFontIndirectA( lf );
						::SelectObject( dc, font );
						
						if ( s.empty() ) {
							::GetTextExtentPoint32A( dc, "EM", 2, &textSz );
						}
						else {
							::GetTextExtentPoint32A( dc, s.c_str(), s.size(), &textSz );
						}
					}

					RestoreDC(dc, dcs);
					DeleteObject( font );

					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TABP_TABITEM, 0, 
																NULL, TS_TRUE, &sz);					


					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx + textSz.cx;
					result.height_ = sz.cy;
				}
				else {
					HDC dc = ::GetDC( ::GetDesktopWindow() );
					int dcs = SaveDC(dc);
					SIZE textSz;
					memset(&textSz,0,sizeof(textSz));
					SIZE textSz2;
					memset(&textSz2,0,sizeof(textSz2));
					
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					HFONT font = NULL;			
					if ( System::isUnicodeEnabled() ) {
						LOGFONTW* lf = (LOGFONTW*) f.getFontPeer()->getFontHandleID();
						font = ::CreateFontIndirectW( lf );
						::SelectObject( dc, font );
						::GetTextExtentPoint32W( dc, L"EM", 2, &textSz );
						if ( text.empty() ) {
							textSz2 = textSz;
						}
						else {
							::GetTextExtentPoint32W( dc, text.c_str(), text.size(), &textSz2 );
						}
					}
					else {
						LOGFONTA* lf = (LOGFONTA*) f.getFontPeer()->getFontHandleID();
						AnsiString s = text;
						font = ::CreateFontIndirectA( lf );
						::SelectObject( dc, font );
						::GetTextExtentPoint32A( dc, "EM", 2, &textSz );
						if ( s.empty() ) {
							textSz2 = textSz;
						}
						else {
							::GetTextExtentPoint32A( dc, s.c_str(), s.size(), &textSz2 );
						}
					}
					
					result.height_ = maxVal<int>( textSz.cy, 21 );
					result.width_ = textSz2.cx + result.height_ + 5.0;
					
					
					
					RestoreDC(dc, dcs);
					DeleteObject( font );
					::ReleaseDC( ::GetDesktopWindow(), dc );
				}
			}
			break;

			case mtRadioBoxBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_RADIOBUTTON, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					result.width_ = 13;
					result.height_ = 13;
				}
			}
			break;

			case mtCheckBoxBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_CHECKBOX, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					result.width_ = 13;
					result.height_ = 13;
				}
			}
			break;

			case mtComboBoxDropBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"COMBOBOX" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, CP_DROPDOWNBUTTON, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					result.width_ = ncm.iScrollWidth;
					result.height_ = ncm.iScrollHeight;
				}
			}
			break;

			case mtDisclosureButtonSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TREEVIEW" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TVP_GLYPH, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {

				}
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}

	virtual Rect getRect( const MetricType& type, Rect* rect, Font* alternateFont ) {
		Rect result;

		switch ( type ) {
			case mtTabPaneContentRect : {
				if ( NULL == rect ) {					
					throw RuntimeException( MAKE_ERROR_MSG_2("mtTabPaneContentRect needs a valid rect instance - you passed in a NULL one!") );
				}


				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
				}
				
				if ( theme ) {					
					HDC dc = GetDC( ::GetDesktopWindow() );
					
					
					result = *rect;
					
					RECT r;
					r.left = result.left_;
					r.top = result.top_;
					r.right = result.right_;
					r.bottom = result.bottom_;
					RECT paneContent = r;
					RECT bodyContent = r;
					
					
					Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc, 
						TABP_PANE, 1, &r, &paneContent );
					
					Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc, 
						TABP_BODY, 1, &r, &bodyContent );

					int dy = abs(bodyContent.top - paneContent.top);
					
					SIZE tabSz;
					memset(&tabSz,0,sizeof(tabSz));
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TABP_TABITEM, TIS_NORMAL, 
																&r, TS_TRUE, &tabSz);

										
					paneContent.top += tabSz.cy + dy;
					

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.left_ = paneContent.left;
					result.top_ = paneContent.top;
					result.right_ = paneContent.right;
					result.bottom_ = paneContent.bottom;
				}
				else {
					result = *rect;

					result.inflate( -5, -5 );

					Size sz = getSize(mtTabSize,"",NULL);
					result.top_ += sz.height_;
				}

			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}
};








/**
*used by the ToolKitHookWndProc andthe construcor for Win32ToolKit()
*/
static HHOOK hookHandle;

class Win32PostEventRecord {
public:
	Win32PostEventRecord( EventHandler* handler, Event* event, bool deleteHandler ) {
		handler_ = handler;
		event_ = event;
		deleteHandler_ = deleteHandler;
	}

	virtual ~Win32PostEventRecord() {
		if ( NULL != event_ ) {
			delete event_;
		}

		event_ = NULL;

		if ( true == deleteHandler_ ) {
			handler_->free();
		}
		handler_ = NULL;
	}

	EventHandler* handler_;
	Event* event_;
	bool deleteHandler_;
};




class Win32ToolTip : public Window {
public:
	Win32ToolTip() {
		Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();

		setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP ) );
		getFont()->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP_TEXT ) );
		setFrameStyle( fstNoBorderFixed );
		setFrameTopmost( true );

		setUseColorForBackground( true );

		getPeer()->setText( "Win32ToolTip" );
	};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );
		ctx->setColor( Color::getColor( "black" ) );
		Rect r(0,0,getWidth() - 1.0, getHeight() - 1.0 );
		ctx->rectangle( &r );
		ctx->strokePath();

		r.inflate( -1, -1 );

		ctx->setCurrentFont( getFont() );

		int32 drawingOptions = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &r, getCaption(), drawingOptions );
	}

	virtual void mouseClick( MouseEvent* e ) {
		hide();
	}

	virtual void mouseDown( MouseEvent* e ) {
		hide();
	}

	virtual bool allowsActivation() {
		return false;
	}
};

class ToolTipWatcher : public ObjectWithCallbacks {
public:
	ToolTipWatcher() {
		currentControlWithTooltip_ = NULL;
		
		autoDestroyEmbeddedTooltipControl_ = false;
		embeddedTooltipControl_ = NULL;

		toolTip_ = NULL;

		if ( NULL == toolTip_ ) {
			toolTip_ = new Win32ToolTip();

			//toolTip_->setVisible( false );
			toolTip_->FrameActivation += 
				new ClassProcedure1<WindowEvent*,ToolTipWatcher>( this,
													&ToolTipWatcher::onToolTipLostFocus,
													"toolTipWatcherHandler" );

			Frame* f = Window::getActiveFrame();
			//toolTip_->setParent( f );
		}

	}

	virtual ~ToolTipWatcher() {
		if ( NULL != toolTip_ ) {
			toolTip_->free();
		}
	}

	Control* getActualToolTipControl( Control* control, Point* pt ) {
		Control* result = NULL;

		Container* container = control->getContainer();
		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();
			bool found = false;
			while ( (true == children->hasMoreElements()) && (false == found) ) {
				Control* child = children->nextElement();
				if ( true == child->isLightWeight() ) {
					Rect bounds = child->getBounds();
					if ( true == bounds.containsPt( pt ) ) {
						Point tmpPt = *pt;
						child->translateToLocal( &tmpPt );
						result = getActualToolTipControl( child, &tmpPt );
						if ( NULL != result  ) {
							found = true;//quit the loop
						}
					}
				}
			}
			if ( (false == found) && (NULL == result) ) {
				result = control;
			}
		}
		else {
			result = control;
		}

		return result;
	}

	void showTooltip( Control* control, Point* pt ) {

		if ( toolTip_->getVisible() ) {
			return;
		}
		
		if ( NULL != embeddedTooltipControl_ ) {
			toolTip_->remove(embeddedTooltipControl_) ;
			if ( autoDestroyEmbeddedTooltipControl_ ) {
				Component* owner = embeddedTooltipControl_->getOwner();
				owner->removeComponent( embeddedTooltipControl_ );
				embeddedTooltipControl_->free();
			}
		}


		toolTip_->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP ) );
		autoDestroyEmbeddedTooltipControl_ = false;
		embeddedTooltipControl_ = NULL;

		//pt is in screen coordinates
		Point tmpPt = *pt;
		Point adjustedPtForCursor = *pt;
		

		control->translateFromScreenCoords( &tmpPt );

		Control* actualToolTipControl = getActualToolTipControl( control, &tmpPt );
		if ( NULL == actualToolTipControl ) {
			return;// nothing to do
		}

		

		String tooltip = actualToolTipControl->getToolTipText();

		ToolTipEvent tooltipEvent( actualToolTipControl, 0 );
		
		tooltipEvent.backgroundColor = *toolTip_->getColor();

		tooltipEvent.tooltipLocation = adjustedPtForCursor;	
		

		if ( tooltip.empty() ) {
			//fire a tooltip requested
			tooltipEvent.setType( TOOLTIP_EVENT_TIP_REQESTED );

			actualToolTipControl->ToolTipRequested( &tooltipEvent );

			tooltip = tooltipEvent.tooltipString;

			tooltipEvent.setType( 0 );			
		}

		tooltipEvent.tooltipLocation.y_ += (::GetSystemMetrics( SM_CYCURSOR )*0.66);

		if ( !tooltip.empty() ) {

			actualToolTipControl->ToolTip( &tooltipEvent );
			tmpPt = tooltipEvent.tooltipLocation;


			toolTip_->setColor( &tooltipEvent.backgroundColor );

			toolTip_->setLeft( tmpPt.x_ );
			toolTip_->setTop( tmpPt.y_ );

			if ( tooltipEvent.tooltipSize.height_ > 0.0 ) {
				toolTip_->setHeight( tooltipEvent.tooltipSize.height_ );
			}
			else {
				toolTip_->setHeight( toolTip_->getFont()->getTextHeight( "EM" ) + 5 );
			}

			if ( tooltipEvent.tooltipSize.width_ > 0.0 ) {
				toolTip_->setWidth( tooltipEvent.tooltipSize.width_ );
			}
			else {
				toolTip_->setWidth( toolTip_->getFont()->getTextWidth( tooltip ) + 10 );
			}

			if ( toolTip_->getParent() == NULL ) {
				//toolTip_->setParent(  );
			}

			//embed control?
			
			if ( NULL != tooltipEvent.embeddedControl ) {
				embeddedTooltipControl_ = tooltipEvent.embeddedControl;
				autoDestroyEmbeddedTooltipControl_ = tooltipEvent.autoDestroyEmbeddedControl;			
				
				toolTip_->add( embeddedTooltipControl_, AlignClient );
			}
			

			toolTip_->setCaption( tooltip );
			
			toolTip_->show();
			//toolTip_->setFrameTopmost( true );
			currentControlWithTooltip_ = actualToolTipControl;
		}
	}

	void hideToolTip() {
		
		toolTip_->hide();

		if ( NULL != embeddedTooltipControl_ ) {
			toolTip_->remove(embeddedTooltipControl_) ;
			if ( autoDestroyEmbeddedTooltipControl_ ) {
				Component* owner = embeddedTooltipControl_->getOwner();
				owner->removeComponent( embeddedTooltipControl_ );
				embeddedTooltipControl_->free();
			}
		}

		embeddedTooltipControl_ = NULL;
		autoDestroyEmbeddedTooltipControl_ = false;
	}

	void onToolTipLostFocus( WindowEvent* e ) {
		
		Window* w = (Window*)e->getSource();		
		if ( w == toolTip_ ) {
			hideToolTip();
		}
		else {			
			if ( !w->isActive() ) {				
				w->hide();
			}
		}
	};
	
	bool autoDestroyEmbeddedTooltipControl_;
	Win32ToolTip* toolTip_;
	Point checkPt_;
	Control* currentControlWithTooltip_;
	Control* embeddedTooltipControl_;
};

static ToolTipWatcher* toolTipWatcher = NULL;

LRESULT CALLBACK ToolKitHookWndProc( int nCode, WPARAM wParam, LPARAM lParam );



void Win32ToolKit::initAreUMeMessage( const String& uniqueAppName )
{
	Win32ToolKit::AreUMeMessage = ::RegisterWindowMessageA(uniqueAppName.ansi_c_str());	
}

/**
*this is a weird case that Win32 gives us, so here's the deal:
*A hidden dummy window, whose parent is the UIShell, is created and made
*available as a temporary parent to Peers before the created window is actually
*hooked into into the real parent. What seems to happen with the common controls
*is the first parent hwnd sent in to the control when it is first created is the
*one to which all future WM_NOTIFY messages are sent to. This is fine and well if
*you are writing a big fat SDK switch statement (like the one you're looking at now :),
*but really sucks if you have your code broken up into a well organized
*framework (like I am attempting to build here ! ). What this means is
*that Control objects can never handle their own notifications!
*So the code below exists to route those messages back to the child Win32Object
*where they are handled. So to facilitate this we'll do our processing here
*(which at the moment is nothing) and then pass the message right back to the
*child that sent it !
*First the lParam is typecasted into a NMHDR structure. This gives us access to
*the hwnd and hopefully the Win32Object. If we have a valid Win32Object then we
*call the Win32Object::handleEventMessages(), passing the NMHDR.code field as the
*reflected window message, the original wParam, which gets ignored anyways, and
*the original lParam, which upon arriving back at the child control will again
*get typcast back to some other notification structure.
*PS: Yes, this is one of the biggest hacks I've seen  ;-)
*PPS This also works for WM_COMMAND messages as well
*/
LRESULT CALLBACK Win32ToolKit::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if ( (message == Win32ToolKit::AreUMeMessage) && (Win32ToolKit::AreUMeMessage != 0xFFFFFFFF) ) {
		return Win32ToolKit::AreUMeMessage;
	}
	else if ( message == Win32ToolKit::RestoreSingleInstAppMessage ) {
		StringUtils::trace( "Win32ToolKit::RestoreSingleInstAppMessage recvd\n" );

		Window* mainWnd = Application::getRunningInstance()->getMainWindow();
		
		if ( NULL != mainWnd ) {
			HWND mainHwnd = (HWND)mainWnd->getPeer()->getHandleID();
			::SetForegroundWindow( mainHwnd );
			
			if ( IsIconic( mainHwnd ) )
			{ /* restore */
				::ShowWindow( mainHwnd, SW_RESTORE );
			} /* restore */
		}

		CommandLine cmdLine;
		StringTokenizer tok(RestoreSingleInstAppCmdLine);
		std::vector<String> cmds;
		while ( tok.hasMoreElements() ) {
			cmds.push_back( tok.nextElement() );
		}
		cmdLine.splitLine( cmds );

		Application::getRunningInstance()->processCommandLine( cmdLine );

		RestoreSingleInstAppCmdLine = String();
	}

	switch ( message ){

		case WM_COPYDATA : {
			COPYDATASTRUCT* cpd = (COPYDATASTRUCT*)lParam;
			if ( NULL != cpd ) {
				if ( cpd->dwData == Win32ToolKit::RestoreSingleInstAppMessage ) {
					RestoreSingleInstAppCmdLine.assign( (VCFChar*)cpd->lpData, cpd->cbData / sizeof(VCFChar) );
				}
			}
		}
		break;

		case WM_INPUTLANGCHANGE : {
			StringUtils::trace( "WM_INPUTLANGCHANGE\n" );
		}
		break;

		case WM_SETTINGCHANGE : {
			//settings change!			
			UIToolkit::systemSettingsChanged();
		}
		break;

		case WM_ACTIVATEAPP: {

			BOOL fActive = (BOOL) wParam;

			/**
			this is a total hack to get around the fact that if I create the dummyParentWnd_
			with a WS_CHILD style it causes a WM_NCACTIVATE with a active=0 to teh new popup
			window, which de-activates the caption bar and focus. However if I change the
			creation style to WS_POPUP it avoids the above, but then any time a popup window
			(like that of the ComboBox popup) is created it causes the main parent window to
			lose focus. So...create the dummyParentWnd_ with a WS_POPUP style to avoid the first
			goof, and then switch it back to a WS_CHILD style here to avoid the other goof.
			Of course, ideally it would be nice to never get either goof, but...
			*/
			static bool changeStyle = true;

			Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();

			if ( NULL == toolkit ) {
				return 0;
			}

			if ( changeStyle ) {
				
				LONG_PTR style = ::GetWindowLongPtr( toolkit->dummyParentWnd_, GWL_STYLE );
				if ( style & WS_POPUP ) {
					style &= ~WS_POPUP;
					style |= WS_CHILD;
					::SetWindowLongPtr( toolkit->dummyParentWnd_, GWL_STYLE, style );
					::SetWindowPos( toolkit->dummyParentWnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
				}
			}
			changeStyle = false;

			if ( fActive ) {

				ToolTipTimerID = ::SetTimer( hWnd, TOOLTIP_TIMERID, 500, NULL );
				Frame* activeFrame = Frame::getActiveFrame();
				
				if ( NULL != activeFrame ) {
					/**
					REMARK: if we break here with a crash of the application, we probably had the
					crash before the main frame window for the application has been fully initialized.
					In order to see what the cause was, please put a break on the Dialog::showMessage
					line inside the catch block of Application::main() and then skip it and continue 
					to run from the throw statement.
					*/
					activeFrame->activate();
				}
			}
			else {
				::KillTimer( hWnd, TOOLTIP_TIMERID );
				ToolTipTimerID = 0;
			}

			toolkit->setWhatsThisHelpActive( false );
		}
		break;

		case WM_CREATE:	{

		}
		break;

		case WM_TIMER:	{

			UINT wTimerID = wParam;
			if ( ToolTipTimerID == wTimerID ) {
				POINT pt = {0,0};
				if ( NULL == toolTipWatcher ) {
					toolTipWatcher = new ToolTipWatcher();
				}
				if ( GetCursorPos( &pt ) ) {
					Point tmpPt( pt.x, pt.y );
					HWND hwndCursorIsOver = WindowFromPoint( pt );
					if ( NULL != hwndCursorIsOver ) {
						ScreenToClient( hwndCursorIsOver, &pt );						 
						HWND childWnd = ChildWindowFromPointEx( hwndCursorIsOver, pt, CWP_SKIPINVISIBLE );
						if ( childWnd != NULL ) {
							ClientToScreen( hwndCursorIsOver, &pt );

							hwndCursorIsOver = childWnd;

							ScreenToClient( hwndCursorIsOver, &pt );
						}

						if ( IsWindow( hwndCursorIsOver ) ) {
							Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCursorIsOver );

							if ( NULL != win32Obj ) {

								if ( NULL != toolTipWatcher->toolTip_ ) {
									if ( (HWND)toolTipWatcher->toolTip_->getPeer()->getHandleID() == hwndCursorIsOver ) {
										break;
									}
								}
								

								if ( (toolTipWatcher->checkPt_.x_ == tmpPt.x_) && (toolTipWatcher->checkPt_.y_ == tmpPt.y_) ) {
									
									toolTipWatcher->showTooltip( win32Obj->getPeerControl(), &tmpPt );
									ToolTipTimoutTimerID = ::SetTimer( hWnd, TOOLTIP_TIMEOUT_TIMERID, 5000, NULL );
								}
								else {
									if ( NULL != toolTipWatcher->toolTip_ ) {
										toolTipWatcher->toolTip_->hide();
									}
								}
							}
						}
					}
					toolTipWatcher->checkPt_ = tmpPt;
				}
			}

			else if ( ToolTipTimoutTimerID == wTimerID ) {				
				::KillTimer( hWnd, TOOLTIP_TIMEOUT_TIMERID );
				::KillTimer( hWnd, TOOLTIP_TIMERID );
				ToolTipTimerID = 0;

				if ( NULL != toolTipWatcher->toolTip_ ) {
					toolTipWatcher->checkPt_.x_ = -1;
					toolTipWatcher->checkPt_.y_ = -1;
					toolTipWatcher->hideToolTip();
				}

			}
			else {
				//we may have a registered timer to look for
				Win32ToolKit::TimerRec* timerRec =
					((Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit())->findTimerRec( wTimerID );

				if ( NULL != timerRec ) {
					EventHandler* handler = timerRec->handler_;
					TimerEvent event( timerRec->source_, TIMER_EVENT_PULSE );
					handler->invoke( &event );
				}
			}
		}
		break;

		case WM_DESTROY:	{
			::KillTimer( hWnd, TOOLTIP_TIMERID );
			ToolTipTimerID = 0;
			delete toolTipWatcher;
			if ( System::isUnicodeEnabled() ) {
				result =  DefWindowProcW( hWnd, message, wParam, lParam );
			}
			else {
				result =  DefWindowProcA( hWnd, message, wParam, lParam );
			}
		}
		break;

		case WM_NOTIFY:{
			NMHDR* notificationHdr = (LPNMHDR)lParam;

			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( notificationHdr->hwndFrom );
			if ( NULL != win32Obj ){
				win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, result );
			}
			else {
				//handle some special case messages here that wouldn't ordinarily get caught
				//because they are from child windows of a common control (like the header control in a listview)
				switch ( notificationHdr->code ) {
				case HDN_GETDISPINFOW : case HDN_ITEMCHANGING: case HDN_TRACK: case HDN_ENDTRACK : case HDN_BEGINTRACK: {
						HWND parent = ::GetParent( notificationHdr->hwndFrom );
						win32Obj = Win32Object::getWin32ObjectFromHWND( parent );
						if ( NULL != win32Obj ){
							win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, result );
						}
					}
					break;
				}
			}
		}
		break;

		case WM_COMMAND:{

			HWND hwndCtl = (HWND) lParam;
			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
			if ( NULL != win32Obj ){
				if ( win32Obj->acceptsWMCommandMessages() ) {
					win32Obj->handleEventMessages( message, wParam, lParam, result );
				}
			}
			if ( System::isUnicodeEnabled() ) {
				result =  DefWindowProcW( hWnd, message, wParam, lParam );
			}
			else {
				result =  DefWindowProcA( hWnd, message, wParam, lParam );
			}
		}
		break;

		case WM_DRAWITEM:{
			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;
			if ( ODT_BUTTON == drawItem->CtlType || 
					ODT_COMBOBOX == drawItem->CtlType ) {
				HWND hwndCtl = drawItem->hwndItem;
				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( WM_DRAWITEM, wParam, lParam, result );
				}
				else {
					if ( System::isUnicodeEnabled() ) {
						result =  DefWindowProcW( hWnd, message, wParam, lParam );
					}
					else {
						result =  DefWindowProcA( hWnd, message, wParam, lParam );
					}
				}
			}
			else {
				if ( System::isUnicodeEnabled() ) {
					result =  DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result =  DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
		}
		break;

		case WM_MEASUREITEM:{
			MEASUREITEMSTRUCT* measureItem = (MEASUREITEMSTRUCT*)lParam;
			if ( ODT_COMBOBOX == measureItem->CtlType ) {
				HWND hwndCtl = GetDlgItem( hWnd, measureItem->CtlID );

				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( WM_MEASUREITEM, wParam, lParam, result );
				}
				else {
					if ( System::isUnicodeEnabled() ) {
						result =  DefWindowProcW( hWnd, message, wParam, lParam );
					}
					else {
						result =  DefWindowProcA( hWnd, message, wParam, lParam );
					}
				}
			}
			else {
				if ( System::isUnicodeEnabled() ) {
					result =  DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result =  DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
		}
		break;

		/*
		case WM_CTLCOLOREDIT : case WM_CTLCOLORBTN: case WM_CTLCOLORLISTBOX: {

			HWND hwndCtl = (HWND) lParam; // handle to static control
			Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndCtl );
			if ( NULL != win32Obj ){
				result = win32Obj->handleEventMessages( message, wParam, lParam );
			}
			if ( result != 0 ) {
				result = ::DefWindowProc( hWnd, message, wParam, lParam );
			}
		}
		break;
		*/
		default : {
			if ( VCF_POST_EVENT == message ) {
				Win32PostEventRecord* postedRecord = (Win32PostEventRecord*)lParam;

				VCF_ASSERT( NULL != postedRecord->handler_ );

				if ( NULL != postedRecord->handler_ ) { 
					postedRecord->handler_->invoke( postedRecord->event_ );
				}
				delete postedRecord;
			}
			else {
				if ( System::isUnicodeEnabled() ) {
					result =  DefWindowProcW( hWnd, message, wParam, lParam );
				}
				else {
					result =  DefWindowProcA( hWnd, message, wParam, lParam );
				}
			}
		}
		break;
	}
	return result;
}

LRESULT CALLBACK Win32ToolKit::mouseHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();
	
	if ( NULL != toolTipWatcher ) {
		if ( WM_MOUSEMOVE == wParam ) {
			if ( 0 == ToolTipTimerID ) {
				ToolTipTimerID = ::SetTimer( toolkit->getDummyParent(), TOOLTIP_TIMERID, 500, NULL );
			}			
		}
		else {
			ToolTipTimoutTimerID = ::SetTimer( toolkit->getDummyParent(), TOOLTIP_TIMEOUT_TIMERID, 1, NULL );
		}
	}
	
	if ( WM_LBUTTONDOWN == wParam ) {
		toolkit->setWhatsThisHelpActive(false);
	}
	
	return CallNextHookEx( Win32ToolKit_mouseHook, nCode, wParam, lParam );
}

LRESULT CALLBACK Win32ToolKit::keyboardHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != toolTipWatcher ) {
		Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::toolKitInstance;
		
		ToolTipTimoutTimerID = ::SetTimer( toolkit->getDummyParent(), TOOLTIP_TIMEOUT_TIMERID, 1, NULL );
		
	}
	return CallNextHookEx( Win32ToolKit_kbHook, nCode, wParam, lParam );	
}

ATOM Win32ToolKit::RegisterWin32ToolKitClass(HINSTANCE hInstance)
{
	if ( System::isUnicodeEnabled() ) {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= 0;
		wcex.lpfnWndProc	= (WNDPROC)Win32ToolKit::wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;
		wcex.hbrBackground	= 0;
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= L"Win32ToolKit";
		wcex.hIconSm		= NULL;

		return RegisterClassExW(&wcex);
	}
	else{
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= 0;
		wcex.lpfnWndProc	= (WNDPROC)Win32ToolKit::wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;
		wcex.hbrBackground	= 0;
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= "Win32ToolKit";
		wcex.hIconSm		= NULL;

		return RegisterClassExA(&wcex);
	}

	return NULL;
}


Win32ToolKit::Win32ToolKit():
	UIToolkit(),
	dummyParentWnd_(NULL),
	runEventCount_(0),
	whatsThisHelpActive_(false)

{

	if ( NULL == Win32ToolKit_toolkitHInstance ) {
		Win32ToolKit_toolkitHInstance = ::GetModuleHandle( NULL );
	}

	if ( System::isUnicodeEnabled() ) {
		VCF_POST_EVENT = RegisterWindowMessageW( L"VCF_POST_EVENT" );
	}
	else {
		VCF_POST_EVENT = RegisterWindowMessageA( "VCF_POST_EVENT" );
	}

	if ( 0 == VCF_POST_EVENT ) {
		//oops it failed - do it the stupid way
		VCF_POST_EVENT = WM_USER + 2000;
	}

	

	if ( System::isUnicodeEnabled() ) {
		HBITMAP bmp = (HBITMAP)::LoadImageW( Win32ToolKit_toolkitHInstance, L"stop", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			stopImage_ = new Win32Image( bmp );
		}

		bmp = (HBITMAP)::LoadImageW( Win32ToolKit_toolkitHInstance, L"warning", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			warningImage_ = new Win32Image( bmp );
		}

		bmp = (HBITMAP)::LoadImageW( Win32ToolKit_toolkitHInstance, L"inform", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			informationImage_ = new Win32Image( bmp );
			informationImage_->setTransparencyColor( &Color(0.0,1.0,0.0) );
			informationImage_->setIsTransparent( true );
		}

		bmp = (HBITMAP)::LoadImageW( Win32ToolKit_toolkitHInstance, L"question", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			questionImage_ = new Win32Image( bmp );
		}
	}
	else {
		HBITMAP bmp = (HBITMAP)::LoadImageA( Win32ToolKit_toolkitHInstance, "stop", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			stopImage_ = new Win32Image( bmp );
		}

		bmp = (HBITMAP)::LoadImageA( Win32ToolKit_toolkitHInstance, "warning", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			warningImage_ = new Win32Image( bmp );
		}

		bmp = (HBITMAP)::LoadImageA( Win32ToolKit_toolkitHInstance, "inform", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			informationImage_ = new Win32Image( bmp );
			informationImage_->setTransparencyColor( &Color(0.0,1.0,0.0) );
			informationImage_->setIsTransparent( true );
		}

		bmp = (HBITMAP)::LoadImageA( Win32ToolKit_toolkitHInstance, "question", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		if ( NULL != bmp ) {
			questionImage_ = new Win32Image( bmp );
		}
	}

	Win32ToolKit_mouseHook = SetWindowsHookEx( WH_MOUSE, Win32ToolKit::mouseHookProc, NULL, GetCurrentThreadId() );
	Win32ToolKit_kbHook = SetWindowsHookEx( WH_KEYBOARD, Win32ToolKit::keyboardHookProc, NULL, GetCurrentThreadId() );

	createDummyParentWindow();

	policyMgr_ = new Win32UIPolicyManager();


	VCFCOM::COMUtils::registerDataTypes();

	//Load HTML Help module

	HtmlHelpLibHandle = LoadLibrary( "hhctrl.ocx" );

	if ( NULL != HtmlHelpLibHandle ) {
		HtmlHelp_W = (HtmlHelpW_Func)::GetProcAddress(HtmlHelpLibHandle,"HtmlHelpW");
		HtmlHelp_A = (HtmlHelpA_Func)::GetProcAddress(HtmlHelpLibHandle,"HtmlHelpA");
	}
	else {
		StringUtils::trace( "Oops - looks like your system doesn't support HTML Help, as you don't have the hhctrl.ocx in your path." );
	}
}


Win32ToolKit::~Win32ToolKit()
{

	if ( NULL != HtmlHelpLibHandle ) {
		/*
		if ( System::isUnicodeEnabled() ) {
			//HtmlHelp_W( NULL, NULL, HH_CLOSE_ALL, 0 );
		}
		else {
			//HtmlHelp_A( NULL, NULL, HH_CLOSE_ALL, 0 );
		}
		*/

		if ( NULL != LastHTMLHelpWnd ) {
			::SendMessage( LastHTMLHelpWnd, WM_CLOSE, 0, 0 );
		}

		Sleep( 5 );
		FreeLibrary( HtmlHelpLibHandle );
	}


	std::map<UINT,TimerRec*>::iterator it = timerMap_.begin();
	while ( it != timerMap_.end() ) {
		KillTimer( dummyParentWnd_, it->first );
		delete it->second;
		it++;
	}
	timerMap_.clear();

	if ( !::DestroyWindow( dummyParentWnd_ ) ) {
		int err = GetLastError();
		StringUtils::trace( Format("::DestroyWindow( dummyParentWnd_[=%p] ) failed!, err: %d\n") % dummyParentWnd_ % err );

		if ( NULL != toolTipWatcher ) {
			delete toolTipWatcher;
		}
	}

	UnhookWindowsHookEx( Win32ToolKit_mouseHook );
	UnhookWindowsHookEx( Win32ToolKit_kbHook );
}

ApplicationPeer* Win32ToolKit::internal_createApplicationPeer()
{
	return new Win32Application();
}

TextPeer* Win32ToolKit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	return new Win32TextPeer(autoWordWrap,multiLined);
}

TextEditPeer* Win32ToolKit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl)
{
	return new Win32Edit( component, isMultiLineControl );
}

TreePeer* Win32ToolKit::internal_createTreePeer( TreeControl* component )
{
	return new Win32Tree( component );
}

ListviewPeer* Win32ToolKit::internal_createListViewPeer( ListViewControl* component )
{
	return new Win32Listview( component );
}


DialogPeer* Win32ToolKit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	return new Win32Dialog( owner, component );
}

DialogPeer* Win32ToolKit::internal_createDialogPeer()
{
	return new Win32Dialog();
}

void Win32ToolKit::createDummyParentWindow()
{

	HWND parent = ::GetDesktopWindow();


	if ( System::isUnicodeEnabled() ) {
		RegisterWin32ToolKitClass( ::GetModuleHandleW( NULL ) );

		dummyParentWnd_ = ::CreateWindowW( L"Win32ToolKit", NULL, WS_POPUP , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleW( NULL ), NULL );
	}
	else {
		RegisterWin32ToolKitClass( ::GetModuleHandleA( NULL ) );

		dummyParentWnd_ = ::CreateWindowA( "Win32ToolKit", NULL, WS_POPUP , 0, 0, 0, 0, parent, NULL, ::GetModuleHandleA( NULL ), NULL );
	}
}

HWND Win32ToolKit::getDummyParent()
{
	if ( NULL == dummyParentWnd_ ){
		this->createDummyParentWindow();
	}
	return this->dummyParentWnd_;
}

MenuItemPeer* Win32ToolKit::internal_createMenuItemPeer( MenuItem* item )
{
	return new Win32MenuItem( item );
}

MenuBarPeer* Win32ToolKit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return new Win32MenuBar( menuBar );
}

ButtonPeer* Win32ToolKit::internal_createButtonPeer( CommandButton* component)
{
	return new Win32Button( component );
}

ContextPeer* Win32ToolKit::internal_createContextPeer( Control* component )
{
	return new Win32ControlContext( component->getPeer() );
}

CommonFileDialogPeer* Win32ToolKit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	return new Win32FileOpenDialog( owner );
}

CommonFileDialogPeer* Win32ToolKit::internal_createCommonFileSaveDialogPeer( Control* owner )
{
	return new Win32FileSaveDialog( owner );
}

CommonColorDialogPeer* Win32ToolKit::internal_createCommonColorDialogPeer( Control* owner )
{
	return new Win32ColorDialog( owner );
}

CommonFolderBrowseDialogPeer* Win32ToolKit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	return new Win32FolderBrowseDialog();
}

DragDropPeer* Win32ToolKit::internal_createDragDropPeer()
{
	return new Win32DragDropPeer();
}

DataObjectPeer* Win32ToolKit::internal_createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* Win32ToolKit::internal_createDropTargetPeer()
{
	return new Win32DropTargetPeer();
}

ClipboardPeer* Win32ToolKit::internal_createClipboardPeer()
{
	return new Win32Clipboard();
}

PopupMenuPeer* Win32ToolKit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	return new Win32PopupMenu( popupMenu );
}

CommonFontDialogPeer* Win32ToolKit::internal_createCommonFontDialogPeer( Control* owner )
{
	return new Win32FontDialog( owner );
}

CommonPrintDialogPeer* Win32ToolKit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return new Win32PrintDialog( owner );
}


UIShellPeer* Win32ToolKit::internal_createUIShellPeer( UIShell* shell )
{
	return new Win32UIShell( shell );
}

ScrollPeer* Win32ToolKit::internal_createScrollPeer( Control* control )
{
	return new Win32ScrollPeer( control );
}

CursorPeer* Win32ToolKit::internal_createCursorPeer( Cursor* cursor )
{
	return new Win32CursorPeer( cursor );
}

ControlPeer* Win32ToolKit::internal_createControlPeer( Control* component, ComponentType componentType)
{
	ControlPeer* result = NULL;

	switch ( componentType ){
		case CT_LIGHTWEIGHT:{
			result = new LightweightComponent( component );
		}
		break;

		case CT_DEFAULT: case CT_HEAVYWEIGHT:{
			result = new Win32Component( component );
		}
		break;
	}
	return result;
}


WindowPeer* Win32ToolKit::internal_createWindowPeer( Control* component, Control* owner)
{
	return new Win32Window( component, owner );
}

PopupWindowPeer* Win32ToolKit::internal_createPopupWindowPeer( Frame* frame, Window* owner )
{
	VCF_ASSERT( frame != owner );

	if ( frame == owner ) {
		return NULL;
	}

	return new Win32PopupWindowPeer( frame, owner );
}

TransparentWindowPeer* Win32ToolKit::internal_createTransparentWindowPeer( Frame* frame )
{
	return new Win32TransparentWindowPeer( frame );
}

DropDownPeer* Win32ToolKit::internal_createDropDownPeer( Control* control )
{
	return new Win32DropDownPeer(control);
}

ToolbarPeer* Win32ToolKit::internal_createToolbarPeer( Toolbar* toolbar )
{
	return new Win32Toolbar( toolbar );
}

SystemTrayPeer* Win32ToolKit::internal_createSystemTrayPeer()
{
	return new Win32SystemTrayPeer();
}

MenuManagerPeer* Win32ToolKit::internal_createMenuManagerPeer()
{
	return new Win32MenuManagerPeer();
}

GraphicsResourceBundlePeer* Win32ToolKit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new Win32AppResourceBundle( app );
}

bool Win32ToolKit::internal_createCaret( Control* owningControl, Image* caretImage  )
{
	return false;
}

bool Win32ToolKit::internal_destroyCaret( Control* owningControl )
{
	return false;
}

void Win32ToolKit::internal_setCaretVisible( const bool& caretVisible )
{

}

void Win32ToolKit::internal_setCaretPos( Point* point )
{

}

void Win32ToolKit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	Win32PostEventRecord* postEventRecord = new Win32PostEventRecord( eventHandler, event, deleteHandler );
	if ( ! ::PostMessage( dummyParentWnd_, VCF_POST_EVENT, 0, (LPARAM)postEventRecord ) ) {
		int err = ::GetLastError();
		StringUtils::trace( Format("!!!!!!! WARNING ::PostMessage Failed (GetLastError(): %d !!!!!!\n") %
									err );

	}
}

void Win32ToolKit::internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds )
{
	std::map<UINT,TimerRec*>::iterator found = timerMap_.begin();
	while ( found != timerMap_.end() ) {
		if ( found->second->handler_ == handler ) {
			KillTimer( dummyParentWnd_, found->first );

			delete found->second;

			timerMap_.erase( found );

			break;
		}
		found ++;
	}

	UINT id = ::SetTimer( dummyParentWnd_, (UINT_PTR)handler, timeoutInMilliSeconds, NULL );

	if ( id == 0 ) {
		//throw exception
	}
	else {
		timerMap_[id] = new TimerRec( source, handler );
	}
}

void Win32ToolKit::internal_unregisterTimerHandler( EventHandler* handler )
{
	std::map<UINT,TimerRec*>::iterator found = timerMap_.begin();
	while ( found != timerMap_.end() ) {
		if ( found->second->handler_ == handler ) {
			KillTimer( dummyParentWnd_, found->first );
			delete found->second;

			timerMap_.erase( found );

			break;
		}
		found ++;
	}
}

Win32ToolKit::TimerRec* Win32ToolKit::findTimerRec( UINT id )
{
	TimerRec* result = NULL;
	std::map<UINT,TimerRec*>::iterator found = timerMap_.find( id );
	if ( found != timerMap_.end() ) {
		result = found->second;
	}

	return result;
}

HINSTANCE Win32ToolKit::getInstanceHandle()
{
	return Win32ToolKit_toolkitHInstance;
}

Event* Win32ToolKit::internal_createEventFromNativeOSEventData( void* eventData )
{
	Event* result = NULL;

	Win32MSG* msg = (Win32MSG*)eventData;

	switch ( msg->msg_.message ) {
		case WM_SIZE: {
			VCF::Size sz( LOWORD(msg->msg_.lParam), HIWORD(msg->msg_.lParam) );
			result = new ControlEvent( msg->control_, sz );
		}
		break;

		case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:{
			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ),
							Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_DOWN,
											Win32UIUtils::translateButtonMask( msg->msg_.wParam ),
											Win32UIUtils::translateKeyMask( msg->msg_.wParam ), &pt );
		}
		break;

		case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:{
			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ) ,
						   Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );


			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			WPARAM tmpWParam = msg->msg_.wParam;
			switch ( msg->msg_.message ){
				case WM_LBUTTONUP:{
					tmpWParam |= MK_LBUTTON;
				}
				break;
				case WM_MBUTTONUP:{
					tmpWParam |= MK_MBUTTON;
				}
				break;

				case WM_RBUTTONUP:{
					tmpWParam |= MK_RBUTTON;
				}
				break;
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_UP,
											Win32UIUtils::translateButtonMask( tmpWParam ),
											Win32UIUtils::translateKeyMask( tmpWParam ), &pt );

		}
		break;

		case WM_SETFOCUS: {
			result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_GAINED );
		}
		break;

		case WM_KILLFOCUS: {
			result = new VCF::FocusEvent ( msg->control_, Control::FOCUS_LOST );
		}
		break;

		case WM_CREATE: {
			result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_CREATED );
		}
		break;

		case WM_HELP : {
			HELPINFO* helpInfo = (HELPINFO*) msg->msg_.lParam;
			result = new HelpEvent(msg->control_);

		}
		break;

		case VCF_CONTROL_CREATE: {
			result = new VCF::ComponentEvent ( msg->control_, Component::COMPONENT_CREATED );
		}
		break;

		case WM_DESTROY: {
			result = new VCF::ComponentEvent( msg->control_, Component::COMPONENT_DESTROYED );
		}
		break;

		case WM_LBUTTONDBLCLK: case WM_MBUTTONDBLCLK: case WM_RBUTTONDBLCLK:{

			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ) ,
							Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_DBLCLICK,
											Win32UIUtils::translateButtonMask( msg->msg_.wParam ),
											Win32UIUtils::translateKeyMask( msg->msg_.wParam ), &pt );


		}
		break;

		case WM_MOVE: {
			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ) ,
							Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );

			result = new VCF::ControlEvent( msg->control_, pt );

		}
		break;

		case WM_MOUSEMOVE: {
			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ) ,
							Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}


			result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_MOVE,
											Win32UIUtils::translateButtonMask( msg->msg_.wParam ),
											Win32UIUtils::translateKeyMask( msg->msg_.wParam ),
											&pt );
		}
		break;

		case WM_MOUSEWHEEL:
		{
			VCF::Point pt( Win32UIUtils::getXFromLParam( msg->msg_.lParam ) ,
				Win32UIUtils::getYFromLParam( msg->msg_.lParam ) );
		  
			//edited
			result = new VCF::MouseEvent ( msg->control_, Control::MOUSE_WHEEL,
				  Win32UIUtils::translateButtonMask( msg->msg_.wParam ),
				  Win32UIUtils::translateKeyMask( msg->msg_.wParam ),
				  &pt );

			//edited
			short mouseDelta = (short)HIWORD(msg->msg_.wParam);   // wheel rotation
			((VCF::MouseEvent *)result)->setMouseDelta(mouseDelta);
		 }
		 break;

		case WM_MOUSELEAVE: {
			POINT pt = {0,0};
			::GetCursorPos( &pt );
			ScreenToClient( msg->msg_.hwnd, &pt );

			VCF::Point pt2( pt.x , pt.y );

			Scrollable* scrollable = msg->control_->getScrollable();
			if ( NULL != scrollable ) {
				pt2.x_ += scrollable->getHorizontalPosition();
				pt2.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control_, Control::MOUSE_LEAVE,
											Win32UIUtils::translateButtonMask( 0 ),
											Win32UIUtils::translateKeyMask( 0 ), &pt2 );
		}
		break;

		case WM_CHAR: case WM_KEYDOWN: case WM_KEYUP: {		

			KeyboardData keyData = Win32UIUtils::translateKeyData( msg->msg_.hwnd, msg->msg_.lParam );
			

			uint32 eventType = 0;
			uint32 repeatCount = keyData.repeatCount;

			uint32 keyMask = Win32UIUtils::translateKeyMask( keyData.keyMask );

			VCFChar keyVal = 0;
			
			VirtualKeyCode virtualKeyCode = (VirtualKeyCode)Win32UIUtils::translateVKCode( keyData.VKeyCode );


			switch ( msg->msg_.message ){
				case WM_CHAR: {
					eventType = Control::KEYBOARD_PRESSED;
					keyVal = (VCFChar)msg->msg_.wParam;
					if ( isgraph( keyVal ) ) {
						virtualKeyCode = (VirtualKeyCode)Win32UIUtils::convertCharToVKCode( keyVal );
					}
				}
				break;

				case WM_KEYDOWN: {
					keyVal = keyData.character;
					eventType = Control::KEYBOARD_DOWN;//KEYBOARD_EVENT_DOWN;

					virtualKeyCode = (VirtualKeyCode)Win32UIUtils::translateVKCode( msg->msg_.wParam );
				}
				break;

				case WM_KEYUP: {
					eventType = Control::KEYBOARD_UP;
					keyVal = keyData.character;
					virtualKeyCode = (VirtualKeyCode)Win32UIUtils::translateVKCode( msg->msg_.wParam );
				}
				break;
			}


			result = new VCF::KeyboardEvent( msg->control_,
											eventType,
											repeatCount,
											keyMask,
											keyVal,
											virtualKeyCode );

		}
		break;

	}


	return result;
}

bool Win32ToolKit::runEventLoopRunOnce( MSG& msg, bool& isIdle )
{
	HACCEL hAccelTable = NULL;
	Application* runningApp = Application::getRunningInstance();
	// phase1: check to see if we can do idle work
	while ( isIdle && (!::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) ) {

		internal_idleTime();

		if ( NULL != runningApp ) {
			//StringUtils::trace( "runningApp->idleTime()\n" );
			runningApp->idleTime();
		}

		//check library apps;
		Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
		while ( true == registeredLibs->hasMoreElements() ) {
			LibraryApplication* libraryApp = registeredLibs->nextElement();
			libraryApp->idleTime();
		}
		isIdle = false;
	}

	if ( msg.message == WM_QUIT ) {
		StringUtils::trace( "WM_QUIT\n" );
		return false;
	}
	else if ( msg.message == WM_EXITMENULOOP ) {
		StringUtils::trace( "WM_EXITMENULOOP\n" );
	}
	else if ( msg.message == WM_INPUTLANGCHANGE ) {
		StringUtils::trace( "WM_INPUTLANGCHANGE\n" );
	}
	else if ( msg.message == WM_WININICHANGE ) {
		StringUtils::trace( "WM_WININICHANGE\n" );
	}

	do	{
		//dispatch message, but quit on WM_QUIT
		if ( GetMessage( &msg, NULL, 0, 0 ) ) {
			/**
			*we're going to want to handle accelerators here
			*the steps should
			*identify if the message is a
			*WM_KEYPRESS
			*if it is then check to find the Control associated with the msg
			*if it is then call the Control's getAccelator and match to the
			*key stroke's VK code and modifier keys. if the accelerator is
			*found the call the invoke() method on the event handler for hte
			*accelerator.
			*if no accelerator is found on the control or no control is found,
			*try and get the running Application. if one is found then call
			*the getAccelerator() on the Application and do the same thing as described
			*for the control
			*if any accelerator is found then do NOT call TranslateMessage() and DispatchMessage()
			*
			*
			*/
			bool doTranslateAndDispatch = true;
			switch( msg.message ) {

				case WM_KEYDOWN :  case WM_SYSKEYDOWN : {

					KeyboardData keyData = Win32UIUtils::translateKeyData( msg.hwnd, msg.lParam );

					KeyboardMasks modifierKey = (KeyboardMasks)Win32UIUtils::translateKeyMask( keyData.keyMask );
					VirtualKeyCode vkCode = (VirtualKeyCode)Win32UIUtils::translateVKCode( keyData.VKeyCode );

					if ( vkUndefined == vkCode ) { //tranlsate by ascii value

						switch ( keyData.character ) {
							case '{' : {
								vkCode = vkOpenBrace;
							}
							break;

							case '}' : {
								vkCode = vkCloseBrace;
							}
							break;

							case '[' : {
								vkCode = vkOpenBracket;
							}
							break;

							case ']' : {
								vkCode = vkCloseBracket;
							}
							break;

							case '~' : {
								vkCode = vkTilde;
							}
							break;

							case '`' : {
								vkCode = vkLeftApostrophe;
							}
							break;
						}
					}

					Win32Object* w = Win32Object::getWin32ObjectFromHWND( msg.hwnd );

					Control* control = NULL;
					Control* currentFocusedControl = Control::getCurrentFocusedControl();

					if ( NULL != w ) {
						control = w->getPeerControl();
						if ( NULL != currentFocusedControl ) {
							if ( (control != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
								control = currentFocusedControl;
							}
						}
					}
					/**
					JC - I put this very small change to attempt to
					properly capture the "correct" focused control,
					from the VCF's perspective. It seems to work fine.
					*/
					else {
						control = currentFocusedControl;
					}

					KeyboardEvent event( control, Control::KEYBOARD_ACCELERATOR, keyData.repeatCount,
						modifierKey, keyData.character, vkCode );

					handleKeyboardEvent( &event );
					if ( event.isConsumed() ) {
						doTranslateAndDispatch = false;
					}
				}
			}

			if ( doTranslateAndDispatch ) {

				if ( !runMsgFilter( &msg ) ) {
					
					if (!TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) ) {
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
				}
			}

			if ( msg.message == WM_QUIT ) {
				StringUtils::trace( "WM_QUIT\n" );
				return false;
			}
			else if ( msg.message == WM_EXITMENULOOP ) {
				StringUtils::trace( "WM_EXITMENULOOP\n" );
			}
		}
		else {
			return false; //we're outta here - nothing more to do
		}

		/**
		0x0118 is a WM_SYSTIMER, according to MSDN:
		"The WM_SYSTIMER message in Windows is an undocumented system message;
		it should not be trapped or relied on by an application. This message
		can occasionally be viewed in Spy or in CodeView while debugging.

		Windows uses the WM_SYSTIMER message internally to control the scroll
		rate of highlighted text (text selected by the user) in edit controls,
		or highlighted items in list boxes.

		NOTE: The WM_SYSTIMER message is for Windows's internal use only and
		can be changed without prior notice. "
		*/

		// WM_PAINT and WM_SYSTIMER (caret blink)
		bool isIdleMessage = ( (msg.message != WM_PAINT) && (msg.message != 0x0118) );
		if ( isIdleMessage ) {
			if ( (msg.message == WM_MOUSEMOVE) || (msg.message == WM_NCMOUSEMOVE) ) {
				//check the prev mouse pt;
			}
		}

		if ( isIdleMessage ) {
			isIdle = true;
		}

	}
	while ( ::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) );

	return true;
}

void Win32ToolKit::internal_runEventLoop()
{
	runEventCount_ ++;

	MSG msg;
	memset( &msg, 0, sizeof(MSG) );	

	bool isIdle = true;
	while (true) {
		try {
			if ( !runEventLoopRunOnce( msg, isIdle ) ) {
				return;
			}
		}
		catch (FoundationKit::Assertion& e){
			String errString = "Assertion Exception caught.\n\"";
			errString += e.what();
			errString += "\".\nApplication exiting abnormally.";
			
			StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );
			
			if ( !Application::showAssertMessage( errString, "Framework Assertion Exception"  ) ) {
#ifdef _DEBUG
				//rethrow the exception and let the application fail out.
				throw;
#endif			
			}
		}
	}

	runEventCount_ --;
}



UIToolkit::ModalReturnType Win32ToolKit::internal_runModalEventLoopFor( Control* control )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrTrue;

	try {
		HWND controlHwnd = (HWND)control->getPeer()->getHandleID();

		Application* runningApp = Application::getRunningInstance();
		int err = 0;
		MSG msg;
		memset( &msg, 0, sizeof(MSG) );

		bool done = false;
		while (!done && !quitModalLoop_ ) {

			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}

			do	{
				bool doTranslateAndDispatch = true;

				bool ESCkeyPressed = false;
				if ( GetMessage(  &msg, NULL, 0, 0 ) ) {
					switch( msg.message ) {

						case WM_KEYDOWN :  case WM_SYSKEYDOWN : {
							KeyboardData keyData = Win32UIUtils::translateKeyData( msg.hwnd, msg.lParam );

							KeyboardMasks modifierKey = (KeyboardMasks)Win32UIUtils::translateKeyMask( keyData.keyMask );
							VirtualKeyCode vkCode = (VirtualKeyCode)Win32UIUtils::translateVKCode( keyData.VKeyCode );

							ESCkeyPressed = (vkCode == vkEscape);

							Win32Object* w = Win32Object::getWin32ObjectFromHWND( msg.hwnd );

							Control* msgControl = NULL;
							if ( NULL != w ) {
								msgControl = w->getPeerControl();
								Control* currentFocusedControl = Control::getCurrentFocusedControl();
								if ( NULL != currentFocusedControl ) {
									if ( (msgControl != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
										msgControl = currentFocusedControl;
									}
								}
							}

							KeyboardEvent event( msgControl, Control::KEYBOARD_ACCELERATOR, keyData.repeatCount,
													modifierKey, keyData.character, vkCode );

							handleKeyboardEvent( &event );
							if ( event.isConsumed() ) {
								doTranslateAndDispatch = false;
							}
						}
					}
					if ( doTranslateAndDispatch ) {
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
				}
				else {
					done = true;
					break;
				}

				switch ( msg.message ){
					case WM_KEYDOWN : {
						if ( ESCkeyPressed ) {
							result = UIToolkit::mrCancel;
						}
					}
					break;

					case WM_SYSCOMMAND: {
						if ( SC_CLOSE == msg.wParam ){
							result = UIToolkit::mrCancel;
							PostQuitMessage(0);
						}
					}
					break;

					case WM_QUIT:{
						done = true;
					}
					break;
				}

				if ( ! IsWindow( controlHwnd ) ) {

					PostQuitMessage(0);
				}

			} while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) && !quitModalLoop_ );
		} //outer for loop

	}
	catch (VCF::FoundationKit::Assertion& e) {
		String errString = "Assertion Exception caught.\n\"";
		errString += e.what();
		StringUtils::trace( "!!! Framework Exception: !!!\n\t" + errString + "\n" );		
		Application::showErrorMessage( errString, "Framework Assertion Exception"  );

		//display error ?
		result = mrFalse;
	}
	catch (...) {
		
		//display error ?
		result = mrFalse;
	}

	quitModalLoop_ = false;

	return result;
}

void Win32ToolKit::internal_quitCurrentEventLoop()
{
	PostQuitMessage(0);
	//if (!PostMessage( dummyParentWnd_, WM_QUIT, 0, 0 )) {
	//	StringUtils::trace( Format( "GetLastError(): %d\n" ) % GetLastError() );
	//}
	//else {
	//	StringUtils::trace( "internal_quitCurrentEventLoop called, PostMessage(WM_QUIT) sent\n" );
	//}
}

Size Win32ToolKit::internal_getDragDropDelta()
{
	Size result;

	result.width_ = ::GetSystemMetrics( SM_CXDRAG );
	result.height_ = ::GetSystemMetrics( SM_CYDRAG );

	return result;
}

void Win32ToolKit::internal_displayHelpContents( const String& helpBookName, const String& helpDirectory )
{	
	if ( NULL == HtmlHelpLibHandle ) {
		StringUtils::trace( "HTML Help features are not available on your system. Please install HTML Help to rectify this." );
		return;
	}
	FilePath helpPath = FilePath::makeDirectoryName(helpDirectory)  + helpBookName;

	//check to see if need to add the .chm extension
	if ( helpBookName.find( ".chm" ) == String::npos ) {
		helpPath += ".chm";
	}

	//check to see if the file exists
	if ( !File::exists( helpPath ) ) {
		//oops it doesn't try a fill path, and assume that 
		//the current value in helpPath is not complete 
		String path = System::findResourceDirectory();
		helpPath = path + helpPath;
	}


	if ( File::exists( helpPath ) ) {
		if ( System::isUnicodeEnabled() ) {
			LastHTMLHelpWnd = HtmlHelp_W( 0, helpPath.getFileName().c_str(), HH_DISPLAY_TOC, NULL );	
		}
		else {
			LastHTMLHelpWnd = HtmlHelp_A( 0, helpPath.getFileName().ansi_c_str(), HH_DISPLAY_TOC, NULL );	
		}
	}
}

void Win32ToolKit::internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory )
{
	if ( NULL == HtmlHelpLibHandle ) {
		StringUtils::trace( "HTML Help features are not available on your system. Please install HTML Help to rectify this." );
		return;
	}

	FilePath helpPath = FilePath::makeDirectoryName(helpDirectory)  + helpBookName;

	//check to see if need to add the .chm extension
	if ( helpBookName.find( ".chm" ) == String::npos ) {
		helpPath += ".chm";
	}

	//check to see if the file exists
	if ( !File::exists( helpPath ) ) {
		//oops it doesn't try a fill path, and assume that 
		//the current value in helpPath is not complete 
		String path = System::findResourceDirectory();
		helpPath = path + helpPath;
	}


	if ( File::exists( helpPath ) ) {
		if ( System::isUnicodeEnabled() ) {
			LastHTMLHelpWnd = HtmlHelp_W( 0, helpPath.getFileName().c_str(), HH_DISPLAY_INDEX, NULL );	
		}
		else {
			LastHTMLHelpWnd = HtmlHelp_A( 0, helpPath.getFileName().ansi_c_str(), HH_DISPLAY_INDEX, NULL );	
		}
	}
}

bool Win32ToolKit::internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory )
{
	if ( NULL == HtmlHelpLibHandle ) {
		StringUtils::trace( "HTML Help features are not available on your system. Please install HTML Help to rectify this." );
		return false;
	}

	bool result = false;
	String whatsThis = control->getWhatsThisHelpString();

	WhatsThisHelpEvent event(control);

	control->ControlHelpRequested( &event );

	if ( !event.helpString.empty() ) {
		whatsThis = event.helpString;
	}

	if ( !whatsThis.empty() ) {
		HH_POPUP popup;
		memset( &popup, 0, sizeof(popup));
		popup.cbStruct = sizeof(popup);

		::GetCursorPos(	&popup.pt );

		popup.pszText = whatsThis.ansi_c_str();
		popup.clrForeground = -1;
		popup.clrBackground = -1;
		memset( &popup.rcMargins, -1, sizeof(popup.rcMargins) );

		LastHTMLHelpWnd = HtmlHelp_A( (HWND)control->getPeer()->getHandleID(), NULL, HH_DISPLAY_TEXT_POPUP, (ULONG_PTR) &popup);
		result =true;
	}

	return result;
}

void Win32ToolKit::internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection )
{
	if ( NULL == HtmlHelpLibHandle ) {
		StringUtils::trace( "HTML Help features are not available on your system. Please install HTML Help to rectify this." );
		return;
	}

	FilePath helpPath = FilePath::makeDirectoryName(helpDirectory)  + helpBookName;

	//check to see if need to add the .chm extension
	if ( helpBookName.find( ".chm" ) == String::npos ) {
		helpPath += ".chm";
	}

	//check to see if the file exists
	if ( !File::exists( helpPath ) ) {
		//oops it doesn't try a fill path, and assume that 
		//the current value in helpPath is not complete 
		String path = System::findResourceDirectory();
		helpPath = path + helpPath;
	}


	if ( File::exists( helpPath ) ) {

		//add the section:

		if ( !helpSection.empty() ) {
			helpPath += "::/" + helpSection;
		}

		if ( System::isUnicodeEnabled() ) {
			LastHTMLHelpWnd = HtmlHelp_W( 0, helpPath.getFileName().c_str(), HH_DISPLAY_TOPIC, NULL );	
		}
		else {
			LastHTMLHelpWnd = HtmlHelp_A( 0, helpPath.getFileName().ansi_c_str(), HH_DISPLAY_TOPIC, NULL );	
		}
	}
}

void Win32ToolKit::internal_systemSettingsChanged()
{
	
}

int Win32ToolKit::addFilter( FilterCallbackFunc callback, void* userData )
{	
	static int id = 1;

	int result = id;
	FilterCBData data;
	data.cb = callback;
	data.userData = userData;

	filterMap_[id] = data;

	id ++;

	return result;
}

void Win32ToolKit::removeFilter( int id )
{
	std::map<int,FilterCBData>::iterator found = filterMap_.find( id );
	if ( found != filterMap_.end() ) {
		filterMap_.erase( found );
	}
}

bool Win32ToolKit::runMsgFilter( MSG* msg )
{
	std::map<int,FilterCBData>::iterator it = filterMap_.begin();
	while ( it != filterMap_.end() ) {
		FilterCBData& fcb = it->second;
		if ( fcb.cb( msg, fcb.userData ) ) {
			return true;
		}
		++it;
	}

	return false;
}

/**
$Id$
*/
