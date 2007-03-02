//Win32PopupWindowPeer.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32PopupWindowPeer.h"

using namespace VCF;

Win32PopupWindowPeer::Win32PopupWindowPeer( Window* window, Window* owner )
{
	
}


Win32PopupWindowPeer::~Win32PopupWindowPeer()
{

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
	return true;
}

void Win32PopupWindowPeer::displayModal()
{
	
}

void Win32PopupWindowPeer::displayAsSheet( Window* owningWindow )
{

}

void Win32PopupWindowPeer::display()
{

}