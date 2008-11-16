//Win32Dialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Dialog.h"


using namespace VCFWin32;

using namespace VCF;


Win32Dialog::Win32Dialog():
	Win32Window()
{
	owner_ = NULL;
	dialogComponent_ = NULL;
}


Win32Dialog::Win32Dialog( Control* owner, Dialog* component ):
	Win32Window( component, owner )
{
	owner_ = owner;
	dialogComponent_ = component;
}


Win32Dialog::~Win32Dialog()
{

}


void Win32Dialog::create( Control* owningControl )
{
	String className = getClassName();
	if ( className.empty() ) {
		className = "VCF::Win32Dialog";
	}
	if ( true != isRegistered() ){
		registerWin32Class( className, wndProc_  );
	}
	
	
	CreateParams params = createParams();

	HWND parent = NULL;
	if ( NULL != owner_ ){

		parent = (HWND)owner_->getPeer()->getHandleID();
	}

	String caption = dialogComponent_->getCaption();

	HICON icon = NULL;

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             className.c_str(),
									 caption.c_str(),
									 params.first,
		                             0,//bounds_.left_,
									 0,//bounds_.top_,
									 0,//bounds_.getWidth(),
									 0,//bounds_.getHeight(),
									 parent,
									 NULL,
									 ::GetModuleHandleW(NULL),
									 NULL );

		icon = LoadIconW( Win32ToolKit::getInstanceHandle(), L"DefaultVCFIcon" );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
		                             className.ansi_c_str(),
									 caption.ansi_c_str(),
									 params.first,
		                             0,//bounds_.left_,
									 0,//bounds_.top_,
									 0,//bounds_.getWidth(),
									 0,//bounds_.getHeight(),
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );

		icon = LoadIconA( Win32ToolKit::getInstanceHandle(), "DefaultVCFIcon" );
	}


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		registerForFontChanges();

		
/*
JC - this needs to be removed as this gives us stupid icon that looks dumb
and forces us to have a system menu!!!
		if ( NULL != icon ) {		
			SendMessage( hwnd_, WM_SETICON, ICON_BIG, (LPARAM) icon );
		}

		HMENU sysMenu = ::GetSystemMenu( hwnd_, FALSE );
		if ( NULL != sysMenu ) 	{
			::RemoveMenu ( sysMenu, SC_MAXIMIZE, MF_BYCOMMAND );
			::RemoveMenu ( sysMenu, SC_MINIMIZE, MF_BYCOMMAND );
			::RemoveMenu ( sysMenu, SC_RESTORE, MF_BYCOMMAND );
			//::RemoveMenu ( sysMenu, SC_SIZE, MF_BYCOMMAND );

		}
		*/

/*
		LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );


			if ( style & WS_MINIMIZEBOX ) {
				style &= ~WS_MINIMIZEBOX;
			}

			if ( style & WS_MAXIMIZEBOX ) {
				style &= ~WS_MAXIMIZEBOX;
			}
			::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
			::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
			*/

	}
	setCreated( true );
}

Win32Object::CreateParams Win32Dialog::createParams()
{
	//WS_CLIPCHILDREN was added to fix bug 585239: Painting weirdness in a modal dialog
	Win32Object::CreateParams result;
	result.first = WS_POPUPWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | /*WS_OVERLAPPED | *//*WS_DLGFRAME |*/ DS_MODALFRAME | DS_3DLOOK;
	result.first &= ~WS_MINIMIZEBOX;
	result.first &= ~WS_MAXIMIZEBOX;
	

	if ( result.first & WS_VISIBLE ) {
		result.first &= ~WS_VISIBLE;
	}

	result.second = WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME | WS_EX_CONTEXTHELP;

	return result;
}

bool Win32Dialog::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {

		case WM_SHOWWINDOW :  {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
			LONG_PTR tmp = style;
			if ( style & WS_MINIMIZEBOX ) {
				style &= ~WS_MINIMIZEBOX;
			}

			if ( style & WS_MAXIMIZEBOX ) {
				style &= ~WS_MAXIMIZEBOX;
			}

			if ( tmp != style ) {
				::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
				::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
			}
		}
		break;
/*
		case WM_KEYDOWN : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );
			Dialog* dlg = (Dialog*)peerControl_;
			if ( true == dlg->isModal() ) {
				KeyboardData keyData = Win32Utils::translateKeyData( hwnd_, lParam );
				VirtualKeyCode vkCode = (VirtualKeyCode)Win32Utils::translateVKCode( keyData.VKeyCode );

				if ( vkCode == vkEscape ) {

					PostMessage( hwnd_, WM_CLOSE, 0, 0 );
				}
			}
		}
		break;*/

		case WM_SYSCOMMAND : {
			UINT cmdType = wParam;
			if ( SC_CONTEXTHELP == cmdType ) {
				StringUtils::trace( "SC_CONTEXTHELP\n" );

				Win32ToolKit* toolkit = (Win32ToolKit*) UIToolkit::internal_getDefaultUIToolkit();
				toolkit->setWhatsThisHelpActive( true );

			}
							 
		}
		break;

		case WM_CLOSE:{
			Dialog* dlg = (Dialog*)peerControl_;

			if ( dlg->allowClose() ) {

				VCF::FrameEvent event( dlg, Frame::CLOSE_EVENT );


				dlg->FrameClose( &event );

				if ( dlg->isModal() ) {
					if ( NULL != dlg->getOwner() ) {
						dlg->getOwner()->setEnabled( true );
					}
					else if ( NULL != Application::getRunningInstance() ){
						Application::getRunningInstance()->getMainWindow()->setEnabled( true );
					}
					else {
						//thorw exception????
					}
				}

				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			}
			else {
				//result = true, don't handle further
				wndProcResult = 0;
				result = true;
			}

		}
		break;

		case WM_DESTROY:{
			
			Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
			Dialog* dlg = (Dialog*)peerControl_;
			if ( NULL != dlg ) {
				if ( true == dlg->isModal() ) {
					PostQuitMessage(0);
				}
			}
		}
		break;

		case  WM_SETFOCUS : {
			
			HWND hwndLoseFocus = (HWND) wParam;
			Win32Object* obj = Win32Object::getWin32ObjectFromHWND( hwndLoseFocus );
			if ( NULL != obj ){

//				StringUtils::trace( Format( "lost focus: %s @ %p\n" ) % obj->getPeerControl()->getClassName() % obj->getPeerControl() );

			}
			
			result = true;//Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case  WM_KILLFOCUS : {
			
			HWND hwndGetFocus = (HWND) wParam;
			Win32Object* obj = Win32Object::getWin32ObjectFromHWND( hwndGetFocus );
			if ( NULL != obj ){

			//	StringUtils::trace( Format( "gained focus: %s @ %p\n" ) % obj->getPeerControl()->getClassName() % obj->getPeerControl() );

			}
			
			
			result = true;//Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		default: result = Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
	}
	return result;
}


void Win32Dialog::showMessage( const String& message, const String& caption )
{
	HWND activeWnd = GetActiveWindow();

	String tmp = caption;

	if ( tmp == "" ){
		TCHAR modFilename[MAX_PATH];
		memset(modFilename, 0, sizeof(modFilename) );
		GetModuleFileName( GetModuleHandle(NULL), modFilename, MAX_PATH );
		tmp = modFilename;
		FilePath fp = tmp;
		tmp = fp.getBaseName(true);
	}

	if ( System::isUnicodeEnabled() ) {
		MessageBoxW( activeWnd, message.c_str(), tmp.c_str(), MB_OK );
	}
	else {
		MessageBoxA( activeWnd, message.ansi_c_str(), tmp.ansi_c_str(), MB_OK );
	}

}

UIToolkit::ModalReturnType Win32Dialog::showMessage( const String& message, const String& caption,
												 const int32& messageButtons, const Dialog::MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrNone;

	UINT mbStyle = 0;
	switch ( messageStyle ){
		case Dialog::msDefault: {

		}
		break;

		case Dialog::msError: {
			mbStyle = MB_ICONERROR;
		}
		break;

		case Dialog::msInfo: {
			mbStyle = MB_ICONINFORMATION;
		}
		break;

		case Dialog::msWarning: {
			mbStyle = MB_ICONWARNING;
		}
		break;

		case Dialog::msQuestion: {
			mbStyle = MB_ICONQUESTION;
		}
		break;
	}

	if ( messageButtons & Dialog::mbOK ) {
		mbStyle |= MB_OK;
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		mbStyle |= MB_OKCANCEL;
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		mbStyle |= MB_YESNO;
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		mbStyle |= MB_YESNOCANCEL;
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		mbStyle |= MB_RETRYCANCEL;
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		mbStyle |= MB_ABORTRETRYIGNORE;
	}

	if ( messageButtons & Dialog::mbHelp ) {
		mbStyle |= MB_HELP;
	}


	HWND activeWnd = GetActiveWindow();
	//if ( !IsWindow ( activeWnd ) ) {
		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
		/**
		JC - I commented this line out as it was creating a 
		new entry in the start bar for the window. I do not think that is
		correct behaviour. In addition, it would not return focus to the 
		window that called it. Again I think this is incorrect behaviour
		*/
		//activeWnd = toolkit->getDummyParent();
	//}

	String tmp = caption;

	if ( tmp == "" ){
		TCHAR modFilename[MAX_PATH];
		memset(modFilename, 0, sizeof(modFilename) );
		GetModuleFileName( GetModuleHandle(NULL), modFilename, MAX_PATH );
		tmp = modFilename;
		FilePath fp = tmp;
		tmp = fp.getBaseName(true);
	}

	int returnVal = 0;
	if ( System::isUnicodeEnabled() ) {
		returnVal = ::MessageBoxW( activeWnd, message.c_str(), tmp.c_str(), mbStyle );
	}
	else {
		returnVal = ::MessageBoxA( activeWnd, message.ansi_c_str(), tmp.ansi_c_str(), mbStyle );
	}


	switch ( returnVal ){
		case IDABORT:{
			result = UIToolkit::mrAbort;
		}
		break;

		case IDCANCEL:{
			result = UIToolkit::mrCancel;
		}
		break;
		/*
		case IDCONTINUE:{

		}
		break;
		*/
		case IDIGNORE:{
			result = UIToolkit::mrIgnore;
		}
		break;

		case IDNO:{
			result = UIToolkit::mrNo;
		}
		break;

		case IDOK:{
			result = UIToolkit::mrOK;
		}
		break;

		case IDRETRY:{
			result = UIToolkit::mrRetry;
		}
		break;
		/*
		case IDTRYAGAIN:{

		}
		break;
		*/
		case IDYES:{
			result = UIToolkit::mrYes;
		}
		break;
	}

	return result;
}

LONG_PTR Win32Dialog::generateStyleForSetParent(VCF::Control* parent)
{
	LONG_PTR result = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	if ( NULL == parent ) {
		if ( !peerControl_->isDesigning() ) {
			result &= ~WS_CHILD;
			result |= WS_POPUP;
		}
	}
	else {
		Frame* frame = (Frame*)peerControl_;
		if ( frame->allowFrameAsChildControl() ) {
			result &= ~WS_POPUP;
			result |= WS_CHILD;
			result |= DS_MODALFRAME | DS_3DLOOK;
		}		
	}

	return result;
}


/**
$Id$
*/
