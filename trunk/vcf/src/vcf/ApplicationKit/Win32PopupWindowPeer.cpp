//Win32PopupWindowPeer.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32PopupWindowPeer.h"

using namespace VCF;


class Win32PopupHook {
public:
	void inc() {
		refs_ ++;
	}

	void dec() {
		if ( refs_ > 0 ) {
			refs_ --;
		}

		if ( refs_ <= 0 ) {
			delete this;
			Win32PopupHook::hookInstance = NULL;
			return;
		}
	}

	static Win32PopupHook* instance() {


		if ( NULL == Win32PopupHook::hookInstance ) {
			Win32PopupHook::hookInstance = new Win32PopupHook();
		}

		return Win32PopupHook::hookInstance;
	}
protected:
	static Win32PopupHook* hookInstance;
	static LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK ActivateAndKBProc( int nCode, WPARAM wParam, LPARAM lParam );

	HHOOK mouseHook_;
	HHOOK keyboardHook_;
	HHOOK activateAndKBHook_;
	int refs_;
private:

	Win32PopupHook():refs_(0),mouseHook_(NULL),activateAndKBHook_(NULL){
		mouseHook_ = SetWindowsHookEx( WH_MOUSE, Win32PopupHook::MouseProc, NULL, GetCurrentThreadId() );
		activateAndKBHook_ = SetWindowsHookEx( WH_CALLWNDPROC, Win32PopupHook::ActivateAndKBProc, NULL, GetCurrentThreadId() );
	}

	~Win32PopupHook(){
		UnhookWindowsHookEx( mouseHook_ );
		UnhookWindowsHookEx( activateAndKBHook_ );
		mouseHook_ = NULL;
		activateAndKBHook_ = NULL;
	}	
};

Win32PopupHook* Win32PopupHook::hookInstance = NULL;

LRESULT CALLBACK Win32PopupHook::MouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	Win32PopupHook* hookInst = Win32PopupHook::instance();

	if ( (WM_LBUTTONDOWN == wParam) || (WM_MBUTTONDOWN == wParam) || (WM_RBUTTONDOWN == wParam) ) {
		//close the popup!!!
		MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;

		PostMessage( mh->hwnd, WM_CLOSE, 0, 0 );
	}
	return CallNextHookEx( hookInst->mouseHook_, nCode, wParam, lParam );
}

LRESULT CALLBACK Win32PopupHook::ActivateAndKBProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	Win32PopupHook* hookInst = Win32PopupHook::instance();
	CWPSTRUCT* cwp = (CWPSTRUCT*)lParam;
	if ( cwp->message == WM_ACTIVATE ) {
		if ( WA_INACTIVE == LOWORD(cwp->wParam) ) {
			//close the popup!!!

			PostMessage( cwp->hwnd, WM_CLOSE, 0, 0 );
		}
	}
	else if ( cwp->message == WM_KEYUP ) {
		switch ( wParam ) {
			case VK_ESCAPE : {
				PostMessage( cwp->hwnd, WM_CLOSE, 0, 0 );
			}
			break;
		}
	}

	return CallNextHookEx( hookInst->activateAndKBHook_, nCode, wParam, lParam );
}





Win32PopupWindowPeer::Win32PopupWindowPeer( Frame* frame, Window* owner )
{
	Win32PopupHook::instance()->inc();
}


Win32PopupWindowPeer::~Win32PopupWindowPeer()
{
	Win32PopupHook::instance()->dec();
}



void Win32PopupWindowPeer::create( Control* owningControl )
{
	String className = getClassName();
	if ( className.empty() ) {
		className = "VCF::Win32PopupWindowPeer";
	}
	if ( !isRegistered() ){
		registerWin32Class( className, wndProc_  );
	}
	
	
	CreateParams params = createParams();

	HWND parent = NULL;
	if ( NULL != owner_ ){

		parent = (HWND)owner_->getPeer()->getHandleID();
	}




	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             className.c_str(),
									 NULL,
									 params.first,
		                             0,
									 0,
									 0,
									 0,
									 parent,
									 NULL,
									 ::GetModuleHandleW(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
		                             className.ansi_c_str(),
									 NULL,
									 params.first,
		                             0,
									 0,
									 0,
									 0,
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		registerForFontChanges();
	}
	setCreated( true );
}



Win32Object::CreateParams Win32PopupWindowPeer::createParams()
{
	Win32Object::CreateParams result;
	result.first = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	result.second = WS_EX_TOPMOST;

	return result;
}

void Win32PopupWindowPeer::setText( const String& text )
{
	//no-op
}

void Win32PopupWindowPeer::setVisible( const bool& visible )
{
	if ( visible ) {
		::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
	}
	else {
		::ShowWindow( hwnd_, SW_HIDE );
	}
}


void Win32PopupWindowPeer::setBounds( Rect* bounds )
{
	::SetWindowPos( hwnd_, 
					HWND_TOPMOST, 
					bounds->left_,
					bounds->top_, 
					bounds->getWidth(), 
					bounds->getHeight(), 
					SWP_NOACTIVATE );
}

void Win32PopupWindowPeer::setClientBounds( Rect* bounds )
{
	::SetWindowPos( hwnd_, 
					HWND_TOPMOST, 
					bounds->left_,
					bounds->top_, 
					bounds->getWidth(), 
					bounds->getHeight(), 
					SWP_NOACTIVATE );
}

void Win32PopupWindowPeer::close()
{

}

void Win32PopupWindowPeer::setFrameStyle( const FrameStyleType& frameStyle )
{
	//no-op
}

void Win32PopupWindowPeer::setFrameTopmost( const bool& isTopmost )
{
	//no-op
}

bool Win32PopupWindowPeer::isMaximized()
{
	return false;
}

void Win32PopupWindowPeer::setMaximized( const bool maximised )
{
	//no-op
}

bool Win32PopupWindowPeer::isMinimized()
{
	return false;
}

void Win32PopupWindowPeer::setMinimized( const bool& minimized )
{
	//no-op
}

void Win32PopupWindowPeer::restore()
{
	//no-op
}

void Win32PopupWindowPeer::setIconImage( Image* icon )
{
	//no-op
}

bool Win32PopupWindowPeer::isActiveWindow()
{
	return false;
}

bool Win32PopupWindowPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case WM_CLOSE:{
			/*
			Dialog* dlg = (Dialog*)peerControl_;

			if ( dlg->allowClose() ) {

				VCF::WindowEvent event( dlg, WINDOW_EVENT_CLOSE );


				dlg->FrameClose.fireEvent( &event );

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
			*/
		}
		break;

		case WM_DESTROY:{
			/*
			Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
			Dialog* dlg = (Dialog*)peerControl_;
			if ( NULL != dlg ) {
				if ( true == dlg->isModal() ) {
					PostQuitMessage(0);
				}
			}
			*/
		}
		break;

		case WM_MOUSEACTIVATE : {
			wndProcResult = MA_NOACTIVATE;
			result = true;
		}
		break;

		case VCF_CONTROL_CREATE: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			activatesPending_ = false;			
		}
		break;

		default: result = Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
	}
	return result;
}

void Win32PopupWindowPeer::showModal()
{
	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}

void Win32PopupWindowPeer::showAsSheet( Window* owningWindow )
{
	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}

void Win32PopupWindowPeer::show()
{
	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}