
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

#if defined(VCF_WIN)
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#endif 


#include "AggUIToolkit.h"

#include "AggMenuManagerPeer.h"
#include "AggMenuBarPeer.h"
#include "AggUIShellPeer.h"
#include "AggApplicationPeer.h"
#include "AggApplicationResourceBundlePeer.h"
#include "AggCursorPeer.h"
#include "AggWindowPeer.h"
#include "AggControlContextPeer.h"

#include "AggUIMetricsManager.h"
#include "AggButton.h"



using namespace VCF;

AggUIToolkit::AggUIToolkit() 
{
	metricsMgr_ = new AggUIMetricsManager();
}

ControlPeer* AggUIToolkit::internal_createControlPeer( Control* component, ComponentType componentType )
{
	
	return NULL;
}

ContextPeer* AggUIToolkit::internal_createContextPeer( Control* control )
{
	return new AggControlContextPeer( control->getPeer() );
}

ListviewPeer* AggUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
	return NULL;
}

TreePeer* AggUIToolkit::internal_createTreePeer( TreeControl* component )
{
	return NULL;
}

TextPeer* AggUIToolkit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	return NULL;
}

TextEditPeer* AggUIToolkit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl )
{
	return NULL;
}

ButtonPeer* AggUIToolkit::internal_createButtonPeer( CommandButton* button )
{
	return new AggButton(button);
}

DialogPeer* AggUIToolkit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	return NULL;
}

DialogPeer* AggUIToolkit::internal_createDialogPeer()
{
	return NULL;
}

WindowPeer* AggUIToolkit::internal_createWindowPeer( Control* component, Control* owner )
{
	return new AggWindowPeer( component , owner );
}

ToolbarPeer* AggUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
	return NULL;
}

MenuItemPeer* AggUIToolkit::internal_createMenuItemPeer( MenuItem* item )
{
	return NULL;
}

MenuBarPeer* AggUIToolkit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return new AggMenuBarPeer( menuBar );
}

PopupMenuPeer* AggUIToolkit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	return NULL;
}

ClipboardPeer* AggUIToolkit::internal_createClipboardPeer()
{
	return NULL;
}

DragDropPeer* AggUIToolkit::internal_createDragDropPeer()
{
	return NULL;
}

DataObjectPeer* AggUIToolkit::internal_createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* AggUIToolkit::internal_createDropTargetPeer()
{
	return NULL;
}

ApplicationPeer* AggUIToolkit::internal_createApplicationPeer()
{
	return new AggApplicationPeer();
}

CommonFileDialogPeer* AggUIToolkit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	return NULL;
}

CommonFolderBrowseDialogPeer* AggUIToolkit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	return NULL;
}

CommonFileDialogPeer* AggUIToolkit::internal_createCommonFileSaveDialogPeer( Control* owner )
{

	return NULL;
}

CommonColorDialogPeer* AggUIToolkit::internal_createCommonColorDialogPeer( Control* owner )
{
	return NULL;
}

CommonFontDialogPeer* AggUIToolkit::internal_createCommonFontDialogPeer( Control* owner )
{
	return NULL;
}

CommonPrintDialogPeer* AggUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return NULL;
}

UIShellPeer* AggUIToolkit::internal_createUIShellPeer( UIShell* shell )
{
	return new AggUIShellPeer( shell );
}

ScrollPeer* AggUIToolkit::internal_createScrollPeer( Control* control )
{
	return NULL;
}

DropDownPeer* AggUIToolkit::internal_createDropDownPeer( Control* control )
{
	return NULL;
}


CursorPeer* AggUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
	return new AggCursorPeer( cursor );
}

SystemTrayPeer* AggUIToolkit::internal_createSystemTrayPeer()
{
	return NULL;
}

MenuManagerPeer* AggUIToolkit::internal_createMenuManagerPeer()
{
	return new AggMenuManagerPeer();
}

GraphicsResourceBundlePeer* AggUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new AggApplicationResourceBundlePeer( app );
}

bool AggUIToolkit::internal_createCaret( Control* owningControl, Image* caretImage )
{
	return false;
}

bool AggUIToolkit::internal_destroyCaret( Control* owningControl )
{
	return false;
}

void AggUIToolkit::internal_setCaretVisible( const bool& caretVisible )
{
	
}

void AggUIToolkit::internal_setCaretPos( Point* point )
{
	
}

void AggUIToolkit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	
}

void AggUIToolkit::internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds )
{
	
}

void AggUIToolkit::internal_unregisterTimerHandler( EventHandler* handler )
{
	
}

void AggUIToolkit::internal_runEventLoop()
{
	MSG msg = {0};


	while (true) { 
		try {

			HACCEL hAccelTable = NULL;
			bool isIdle = true;
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


			do	{
				//dispatch message, but quit on WM_QUIT
				if ( GetMessage( &msg, NULL, 0, 0 ) ) {

					if (!TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) ) {
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}

					if ( msg.message == WM_QUIT ) {
						StringUtils::trace( "WM_QUIT\n" );
						return;
					}
					else if ( msg.message == WM_EXITMENULOOP ) {
						StringUtils::trace( "WM_EXITMENULOOP\n" );
					}
				}
				else {
					return; //we're outta here - nothing more to do
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
		}
		catch (FoundationKit::Assertion& e) {
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
}

UIToolkit::ModalReturnType AggUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	
	return UIToolkit::mrNone;
}

void AggUIToolkit::internal_quitCurrentEventLoop()
{
	
}


uint32 translateButtonMask( uint32 state )
{
	uint32 result = 0;

	

	return result;
}

uint32 translateKeyMask( uint32 state )
{
	uint32 result = VCF::kmUndefined;

	

	//need to figure out the Alt key.....

	return result;
}



Size AggUIToolkit::internal_getDragDropDelta()
{
	//this is completely arbitrary - need to read this from a file
	Size result(4,4);

	return result;
}

void AggUIToolkit::internal_displayHelpContents( const String& helpBookName, const String& helpDirectory )
{
	
}

void AggUIToolkit::internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory )
{
	
}

void AggUIToolkit::internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection )
{
	
}

bool AggUIToolkit::internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory )
{
	return false;
}

void AggUIToolkit::internal_systemSettingsChanged()
{
	
}

PopupWindowPeer* AggUIToolkit::internal_createPopupWindowPeer( Frame* frame, Window* owner )
{
    return NULL;
}

TransparentWindowPeer* AggUIToolkit::internal_createTransparentWindowPeer( Frame* frame )
{
    return NULL;
}


VCF::uint32 _convertCharToVKCode( VCF::VCFChar ch )
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



#ifdef VCF_WIN

uint32 _translateKeyMask( UINT win32KeyMask )
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

uint32 _translateButtonMask( UINT win32ButtonMask )
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



VCF::uint32 _translateVKCode( UINT vkCode )
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


Event* AggUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
	Event* result = NULL;

	OSMessage* msg = (OSMessage*)eventData;
	MSG* wndMsg = (MSG*)msg->msgData;

	switch ( wndMsg->message ) {
		case WM_SIZE: {
			VCF::Size sz( LOWORD(wndMsg->lParam), HIWORD(wndMsg->lParam) );
			result = new ControlEvent( msg->control, sz );
		}
		break;

		case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:{
			VCF::Point pt( LOWORD( wndMsg->lParam ),
							HIWORD( wndMsg->lParam ) );

			Scrollable* scrollable = msg->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent ( msg->control, Control::MOUSE_DOWN,
											_translateButtonMask( wndMsg->wParam ),
											_translateKeyMask( wndMsg->wParam ), &pt );
		}
		break;

		case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:{
			VCF::Point pt( LOWORD( wndMsg->lParam ) ,
						   HIWORD( wndMsg->lParam ) );


			Scrollable* scrollable = msg->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			WPARAM tmpWParam = wndMsg->wParam;
			switch ( wndMsg->message ){
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

			result = new VCF::MouseEvent( msg->control, Control::MOUSE_UP,
											_translateButtonMask( tmpWParam ),
											_translateKeyMask( tmpWParam ), &pt );

		}
		break;

		case WM_SETFOCUS: {
			result = new VCF::FocusEvent ( msg->control, Control::FOCUS_GAINED );
		}
		break;

		case WM_KILLFOCUS: {
			result = new VCF::FocusEvent ( msg->control, Control::FOCUS_LOST );
		}
		break;

		case WM_CREATE: {
			result = new VCF::ComponentEvent( msg->control, Component::COMPONENT_CREATED );
		}
		break;

		case WM_HELP : {
			HELPINFO* helpInfo = (HELPINFO*) wndMsg->lParam;
			result = new HelpEvent(msg->control);

		}
		break;

		case WM_DESTROY: {
			result = new VCF::ComponentEvent( msg->control, Component::COMPONENT_DESTROYED );
		}
		break;

		case WM_LBUTTONDBLCLK: case WM_MBUTTONDBLCLK: case WM_RBUTTONDBLCLK:{

			VCF::Point pt( LOWORD( wndMsg->lParam ) ,
							HIWORD( wndMsg->lParam ) );

			Scrollable* scrollable = msg->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control, Control::MOUSE_DBLCLICK,
											_translateButtonMask( wndMsg->wParam ),
											_translateKeyMask( wndMsg->wParam ), &pt );


		}
		break;

		case WM_MOVE: {
			VCF::Point pt( LOWORD( wndMsg->lParam ) ,
							HIWORD( wndMsg->lParam ) );

			result = new VCF::ControlEvent( msg->control, pt );

		}
		break;

		case WM_MOUSEMOVE: {
			VCF::Point pt( LOWORD( wndMsg->lParam ) ,
							HIWORD( wndMsg->lParam ) );

			Scrollable* scrollable = msg->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}


			result = new VCF::MouseEvent ( msg->control, Control::MOUSE_MOVE,
											_translateButtonMask( wndMsg->wParam ),
											_translateKeyMask( wndMsg->wParam ),
											&pt );
		}
		break;

		case WM_MOUSELEAVE: {
			POINT pt = {0,0};
			::GetCursorPos( &pt );
			ScreenToClient( wndMsg->hwnd, &pt );

			VCF::Point pt2( pt.x , pt.y );

			Scrollable* scrollable = msg->control->getScrollable();
			if ( NULL != scrollable ) {
				pt2.x_ += scrollable->getHorizontalPosition();
				pt2.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( msg->control, Control::MOUSE_LEAVE,
											_translateButtonMask( 0 ),
											_translateKeyMask( 0 ), &pt2 );
		}
		break;

		case WM_CHAR: case WM_KEYDOWN: case WM_KEYUP: {
			uint32 eventType = 0;
			uint32 repeatCount = 1;

			uint32 keyMask = 0;

			VCFChar keyVal = 0;
			
			HKL keyboardLayout = GetKeyboardLayout( GetWindowThreadProcessId( wndMsg->hwnd, NULL ) );

			BYTE ks = (wndMsg->lParam >> 30) & 0xFF;
			ToAsciiEx( wndMsg->wParam, (wndMsg->lParam >> 16) & 0xFF, &ks, 
							&keyVal, 1, keyboardLayout );


			VirtualKeyCode virtualKeyCode = (VirtualKeyCode)_translateVKCode( wndMsg->wParam );


			switch ( wndMsg->message ){
				case WM_CHAR: {
					eventType = Control::KEYBOARD_PRESSED;
					keyVal = (VCFChar)wndMsg->wParam;
					if ( isgraph( keyVal ) ) {
						virtualKeyCode = (VirtualKeyCode)_convertCharToVKCode( keyVal );
					}
				}
				break;

				case WM_KEYDOWN: {					
					eventType = Control::KEYBOARD_DOWN;//KEYBOARD_EVENT_DOWN;

					virtualKeyCode = (VirtualKeyCode)_translateVKCode( wndMsg->wParam );
				}
				break;

				case WM_KEYUP: {
					eventType = Control::KEYBOARD_UP;
					virtualKeyCode = (VirtualKeyCode)_translateVKCode( wndMsg->wParam );
				}
				break;
			}


			result = new VCF::KeyboardEvent( msg->control,
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


#endif //VCF_WIN
/**
$Id$
*/

