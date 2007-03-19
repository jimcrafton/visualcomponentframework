//Win32PopupWindowPeer.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32PopupWindowPeer.h"
#include "vcf/ApplicationKit/PopupWindow.h"


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

	void setCurrentPopupHwnd( HWND val ) {
		currentPopupHwnd_ = val;
	}
protected:
	static Win32PopupHook* hookInstance;
	static LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK ActivateAndKBProc( int nCode, WPARAM wParam, LPARAM lParam );

	HHOOK mouseHook_;
	HHOOK keyboardHook_;
	HHOOK activateAndKBHook_;
	int refs_;
	HWND currentPopupHwnd_;
private:

	Win32PopupHook():refs_(0),mouseHook_(NULL),activateAndKBHook_(NULL),currentPopupHwnd_(NULL){
		mouseHook_ = SetWindowsHookEx( WH_MOUSE, Win32PopupHook::MouseProc, NULL, GetCurrentThreadId() );
		activateAndKBHook_ = SetWindowsHookEx( WH_CALLWNDPROC, Win32PopupHook::ActivateAndKBProc, NULL, GetCurrentThreadId() );
	}

	~Win32PopupHook(){
		if ( !UnhookWindowsHookEx( mouseHook_ ) ) {
			int err = GetLastError();
		}
		UnhookWindowsHookEx( activateAndKBHook_ );
		mouseHook_ = NULL;
		activateAndKBHook_ = NULL;
	}	
};

Win32PopupHook* Win32PopupHook::hookInstance = NULL;



LRESULT CALLBACK Win32PopupHook::MouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != Win32PopupHook::hookInstance ) {
		if ( (WM_LBUTTONDOWN == wParam) || (WM_MBUTTONDOWN == wParam) || (WM_RBUTTONDOWN == wParam) ) {
			//close the popup!!!
			MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;
			BOOL isChild = IsChild( Win32PopupHook::hookInstance->currentPopupHwnd_, mh->hwnd );
			StringUtils::trace( Format("IsChild %d hwnd %p, popup hwnd %p\n") % isChild % 
									mh->hwnd % Win32PopupHook::hookInstance->currentPopupHwnd_ );
			if ( !isChild ) {
				StringUtils::trace( "Win32PopupHook::MouseProc posting WM_CLOSE\n" );
				PostMessage( Win32PopupHook::hookInstance->currentPopupHwnd_, WM_CLOSE, 0, 0 );
			}
		}
		else if ( (wParam == WM_NCLBUTTONDOWN) ||
					(wParam == WM_NCMBUTTONDOWN) ||
					(wParam == WM_NCRBUTTONDOWN) ) {

			StringUtils::trace( "Win32PopupHook::MouseProc/WM_NCXBUTTONDOWN posting WM_CLOSE\n" );
			PostMessage( Win32PopupHook::hookInstance->currentPopupHwnd_, WM_CLOSE, 0, 0 );
		}
		return CallNextHookEx( Win32PopupHook::hookInstance->mouseHook_, nCode, wParam, lParam );
	}
	return 1;
}

LRESULT CALLBACK Win32PopupHook::ActivateAndKBProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != Win32PopupHook::hookInstance ) {
		CWPSTRUCT* cwp = (CWPSTRUCT*)lParam;
		if ( cwp->message == WM_ACTIVATE ) {
			if ( WA_INACTIVE == LOWORD(cwp->wParam) ) {
				//close the popup!!!
				StringUtils::trace( "Win32PopupHook::ActivateAndKBProc/WM_ACTIVATE posting WM_CLOSE\n" );
				PostMessage( Win32PopupHook::hookInstance->currentPopupHwnd_, WM_CLOSE, 0, 0 );
			}
		}
		else if ( cwp->message == WM_KEYUP ) {
			switch ( wParam ) {
				case VK_ESCAPE : {
					StringUtils::trace( "Win32PopupHook::ActivateAndKBProc/VK_ESCAPE posting WM_CLOSE\n" );
					PostMessage( Win32PopupHook::hookInstance->currentPopupHwnd_, WM_CLOSE, 0, 0 );
				}
				break;
			}
		}
		else if ( (cwp->message == WM_NCLBUTTONDOWN) ||
					(cwp->message == WM_NCMBUTTONDOWN) ||
					(cwp->message == WM_NCRBUTTONDOWN) ) {

			StringUtils::trace( "Win32PopupHook::ActivateAndKBProc/WM_NCXBUTTONDOWN posting WM_CLOSE\n" );
			PostMessage( Win32PopupHook::hookInstance->currentPopupHwnd_, WM_CLOSE, 0, 0 );
		}

		return CallNextHookEx( Win32PopupHook::hookInstance->activateAndKBHook_, nCode, wParam, lParam );
	}

	return 1;	
}







Win32PopupWindowPeer::Win32PopupWindowPeer( Frame* frame, Window* owner )
{
	Win32PopupHook::instance()->inc();

	owner_ = owner;
	peerControl_ = frame;
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
	else {
		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
		parent = toolkit->getDummyParent();	
	}


	// parent can't be NULL otherwise we end up with a "button" in the task bar
	VCF_ASSERT( NULL != parent );


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

void Win32PopupWindowPeer::setBorder( Border* border )
{	
	VCF_ASSERT(NULL != hwnd_);
	SetWindowPos(hwnd_, NULL,0,0,0,0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

bool Win32PopupWindowPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case WM_CLOSE:{
			
			PopupWindow* popup = (PopupWindow*)peerControl_;

			VCF::WindowEvent event( popup, WINDOW_EVENT_CLOSE );

			popup->FrameClose.fireEvent( &event );
			
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_DESTROY:{
			
			Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
			PopupWindow* popup = (PopupWindow*)peerControl_;
			if ( NULL != popup ) {
				if ( popup->isModal() ) {
					PostQuitMessage(0);
				}
			}
		}
		break;

		case WM_MOUSEACTIVATE : {
			wndProcResult = MA_NOACTIVATE;
			result = true;
		}
		break;

		case WM_SETFOCUS : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		
		case WM_ACTIVATE : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_LBUTTONDOWN : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_NCACTIVATE : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_NCLBUTTONDOWN : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case VCF_CONTROL_CREATE: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			activatesPending_ = false;			
		}
		break;

		default: {
			result = Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}
	return result;
}

void Win32PopupWindowPeer::showModal()
{
	VCF_ASSERT( NULL != hwnd_ );
	
	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );

	Win32PopupHook::instance()->setCurrentPopupHwnd( hwnd_ );

	UIToolkit::runModalEventLoopFor( peerControl_ );

	StringUtils::trace( "Win32PopupWindowPeer::showModal() done\n" );
}

void Win32PopupWindowPeer::showAsSheet( Window* owningWindow )
{
	VCF_ASSERT( NULL != hwnd_ );

	Win32PopupHook::instance()->setCurrentPopupHwnd( hwnd_ );

	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}

void Win32PopupWindowPeer::show()
{
	VCF_ASSERT( NULL != hwnd_ );

	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}