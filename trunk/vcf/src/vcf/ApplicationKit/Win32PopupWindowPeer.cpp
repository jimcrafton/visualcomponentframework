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

	void setCurrentPopupHwnd( Win32PopupWindowPeer* val ) {
		currentPopup_ = val;

		if ( NULL == currentPopup_ ) {
			ignoreRemainingMessages_ = true;
		}
	}
protected:
	static Win32PopupHook* hookInstance;
	static LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK ActivateAndKBProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK KBProc( int nCode, WPARAM wParam, LPARAM lParam );

	HHOOK mouseHook_;
	HHOOK keyboardHook_;
	int refs_;
	Win32PopupWindowPeer* currentPopup_;
	bool ignoreRemainingMessages_;
private:

	Win32PopupHook():refs_(0),
			mouseHook_(NULL),
			currentPopup_(NULL),
			ignoreRemainingMessages_(false){
		mouseHook_ = SetWindowsHookEx( WH_MOUSE, Win32PopupHook::MouseProc, NULL, GetCurrentThreadId() );		
		keyboardHook_ = SetWindowsHookEx( WH_KEYBOARD, Win32PopupHook::KBProc, NULL, GetCurrentThreadId() );
	}

	~Win32PopupHook(){
		if ( !UnhookWindowsHookEx( mouseHook_ ) ) {
			int err = GetLastError();
		}
		UnhookWindowsHookEx( keyboardHook_ );
		
		mouseHook_ = NULL;
		keyboardHook_ = NULL;

		StringUtils::trace( "Hooks removed for Win32PopupWindow\n" );
	}	
};

Win32PopupHook* Win32PopupHook::hookInstance = NULL;


LRESULT CALLBACK Win32PopupHook::KBProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != Win32PopupHook::hookInstance ) {

		if ( !Win32PopupHook::hookInstance->ignoreRemainingMessages_ ) {
			switch ( wParam ) {
				case VK_ESCAPE : {
					StringUtils::trace( "Win32PopupHook::KBProc/VK_ESCAPE posting WM_CLOSE\n" );
					Win32PopupHook::hookInstance->ignoreRemainingMessages_ = true;
					Win32PopupHook::hookInstance->currentPopup_->closePopup();
				}
				break;

				case VK_RETURN : {
					StringUtils::trace( "Win32PopupHook::KBProc/VK_ESCAPE posting VK_RETURN\n" );
					Win32PopupHook::hookInstance->ignoreRemainingMessages_ = true;					
					Win32PopupHook::hookInstance->currentPopup_->closePopup();
				}
				break;
			}
		}
		return CallNextHookEx( Win32PopupHook::hookInstance->keyboardHook_, nCode, wParam, lParam );
	}
	return 1;
}

LRESULT CALLBACK Win32PopupHook::MouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != Win32PopupHook::hookInstance ) {
		if ( !Win32PopupHook::hookInstance->ignoreRemainingMessages_ ) {
			if ( (WM_LBUTTONDOWN == wParam) || (WM_MBUTTONDOWN == wParam) || (WM_RBUTTONDOWN == wParam) ) {
				//close the popup!!!
				MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;
				HWND popup = (HWND)Win32PopupHook::hookInstance->currentPopup_->getHandleID();
				BOOL isChild = IsChild( popup, mh->hwnd );				
				if ( !isChild && popup != mh->hwnd ) {
					StringUtils::trace( "Win32PopupHook::MouseProc posting WM_CLOSE\n" );
					Win32PopupHook::hookInstance->ignoreRemainingMessages_ = true;
					Win32PopupHook::hookInstance->currentPopup_->closePopup();
				}
			}
			if ( (wParam == WM_NCLBUTTONDOWN) ||
						(wParam == WM_NCMBUTTONDOWN) ||
						(wParam == WM_NCRBUTTONDOWN) ) {				

				StringUtils::trace( "Win32PopupHook::MouseProc/WM_NCXBUTTONDOWN posting WM_CLOSE\n" );
				Win32PopupHook::hookInstance->ignoreRemainingMessages_ = true;
				Win32PopupHook::hookInstance->currentPopup_->closePopup();
			}
		}
		return CallNextHookEx( Win32PopupHook::hookInstance->mouseHook_, nCode, wParam, lParam );
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

void Win32PopupWindowPeer::setMaximized( const bool& maximised )
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

void Win32PopupWindowPeer::closePopup()
{
	PopupWindow* popup = (PopupWindow*)peerControl_;
	if ( NULL != popup ) {
		if ( popup->isModal() ) {
			//PostQuitMessage(0);
			//SendMessage( hwnd_, WM_QUIT, 0, 0 );
			ShowWindow( hwnd_, SW_HIDE );

			UIToolkit::quitModalEventLoop();			
		}
		else {
			SendMessage( hwnd_, WM_CLOSE, 0, 0 );
		}
	}
}

bool Win32PopupWindowPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case WM_CLOSE:{
			
			Win32PopupHook::instance()->setCurrentPopupHwnd( NULL );

			PopupWindow* popup = (PopupWindow*)peerControl_;

			VCF::FrameEvent event( popup, Frame::CLOSE_EVENT );

			popup->FrameClose( &event );
			
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_MOUSEACTIVATE : {
			wndProcResult = MA_NOACTIVATE;
			result = true;
		}
		break;

		case WM_LBUTTONDOWN: 
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONDBLCLK:
		case WM_NCRBUTTONDOWN:
		case WM_NCRBUTTONDBLCLK:
		case WM_NCMBUTTONDOWN:
		case WM_NCMBUTTONDBLCLK:
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_MOUSEWHEEL: {
			closePopup();
		}
		break;
		
		case WM_ACTIVATEAPP: {

			if ( !wParam ) {
				closePopup();
			}
		}
		break;

		case WM_NCACTIVATE : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			HWND ownerHwnd = (HWND)this->owner_->getPeer()->getHandleID();

			wndProcResult = defaultWndProcedure( message, wParam, lParam );
			result = false;

			//////////////////////////////////////////////////////////////
			//This is a HACK! I read about it here ( http://vbaccelerator.com/home/NET/Code/Controls/Popup_Windows/Popup_Windows/article.asp)
			//as a way to force the owner window to reactivate itself in the case that
			//we have a some child windows that we click on in the popup
			//window. It works but god only know if it's actually the 
			//correct thing to do
			//////////////////////////////////////////////////////////////
			SendMessage( ownerHwnd, WM_NCACTIVATE, TRUE, 0 );
		}
		break;

		case VCF_CONTROL_CREATE: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			activatesPending_ = false;			
		}
		break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result= true;
		}
		break;

		case WM_NCPAINT: {
			wndProcResult = handleNCPaint( wParam, lParam );
			result= true;
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
	
	//(HWND)owner_->getPeer()->getHandleID()

	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );

	Win32PopupHook::instance()->setCurrentPopupHwnd( this );

	UIToolkit::runModalEventLoopFor( peerControl_ );

	SendMessage( hwnd_, WM_CLOSE, 0, 0 );

//	SetActiveWindow(  );

	StringUtils::trace( "Win32PopupWindowPeer::showModal() done\n" );
}

void Win32PopupWindowPeer::showAsSheet( Window* owningWindow )
{
	VCF_ASSERT( NULL != hwnd_ );

	Win32PopupHook::instance()->setCurrentPopupHwnd( this );

	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}

void Win32PopupWindowPeer::show()
{
	VCF_ASSERT( NULL != hwnd_ );

	::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
}