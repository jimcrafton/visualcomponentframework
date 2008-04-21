//Win32Object.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"


using namespace VCF;

std::vector< String > Win32Object::registeredWindowClasses_;

std::map<HWND, Win32Object*> Win32Object::windowMap_;


LRESULT CALLBACK Win32Object_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hWnd );

	if ( NULL != win32Obj ){
		LRESULT result = 0;
		if ( !win32Obj->handleEventMessages( message, wParam, lParam, result ) ) {
			result = win32Obj->defaultWndProcedure( message, wParam, lParam );
		}

		return result;
	}
	else {
		if ( System::isUnicodeEnabled() ) {
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
		else {
			return DefWindowProcA(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}


Win32Object::Win32Object():
	wndProc_(NULL),
	defaultWndProc_(NULL),
	hwnd_(NULL),
	created_(false),
	peerControl_(NULL)
{
	init();
	wndProc_ = Win32Object_WndProc;
	if ( System::isUnicodeEnabled() ) {
		defaultWndProc_ = ::DefWindowProcW;
	}
	else {
		defaultWndProc_ = ::DefWindowProcA;
	}

}

Win32Object::~Win32Object()
{

}

void Win32Object::destroyWindowHandle()
{
	if ( Win32Object::windowMap_.empty() ) {
		return;
	}

	std::map<HWND, Win32Object*>::iterator found =  Win32Object::windowMap_.find( hwnd_ );
	if ( found != Win32Object::windowMap_.end() ){
		Win32Object::windowMap_.erase( found );
	}
}

void Win32Object::subclassWindow()
{
	if ( System::isUnicodeEnabled() ) {
		defaultWndProc_ = (WNDPROC)(LONG_PTR)::SetWindowLongPtrW( hwnd_, GWLP_WNDPROC, (LONG_PTR)wndProc_ );
	}
	else {
		defaultWndProc_ = (WNDPROC)(LONG_PTR)::SetWindowLongPtrA( hwnd_, GWLP_WNDPROC, (LONG_PTR)wndProc_ );
	}
}

void Win32Object::addRegisterWin32Class( const String& className )
{
	Win32Object::registeredWindowClasses_.push_back( className );
}

void Win32Object::registerWin32Class( const String& className, WNDPROC wndProc )
{
	BOOL registered = FALSE;

	if ( System::isUnicodeEnabled() ) {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

		/**
		This gives us a drop shadow, but we probably need a better way...
#define CS_DROPSHADOW  0x20000

		if ( className == "VCF::Win32PopupWindowPeer" ) {
			wcex.style |= CS_DROPSHADOW;
		}
		*/

		wcex.lpfnWndProc	= (WNDPROC)wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)::GetModuleHandle(NULL);
		
		//This is taken care of in the Win32Window::create class, via
		//sending a WM_SETICON message
		wcex.hIcon			= NULL;

		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= className.c_str();
		wcex.hIconSm		= NULL;

		registered = RegisterClassExW(&wcex);
	}
	else {
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc	= (WNDPROC)wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)::GetModuleHandle(NULL);
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= className.ansi_c_str();
		wcex.hIconSm		= NULL;

		registered = RegisterClassExA(&wcex);
	}

	if ( registered ){
		addRegisterWin32Class( className );
	}
}

bool Win32Object::isRegistered()
{
	bool result = false;

	std::vector<String>::iterator it = std::find( Win32Object::registeredWindowClasses_.begin(),
													     Win32Object::registeredWindowClasses_.end(),
					                					 getClassName() );

	result = ( it != Win32Object::registeredWindowClasses_.end() );
	return result;
}

void Win32Object::init()
{
	hwnd_ = NULL;

	wndProc_ = NULL;
	defaultWndProc_ = NULL;

	created_ = false;

	peerControl_ = NULL;
}

Win32Object::CreateParams Win32Object::createParams()
{
	Win32Object::CreateParams result;
	result.first = SIMPLE_VIEW;
	result.second = 0;

	return result;
}

bool Win32Object::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	wndProcResult = 0;	
	return false;
}

Win32Object* Win32Object::getWin32ObjectFromHWND( HWND hwnd )
{
	Win32Object* result = NULL;

	if ( !Win32Object::windowMap_.empty() ) {

		std::map<HWND,Win32Object*>::iterator found =
			Win32Object::windowMap_.find( hwnd );

		if ( found != Win32Object::windowMap_.end() ){
			result = found->second;
		}
	}
	//result = (Win32Object*)::GetWindowLongPtr( hwnd, GWLP_USERDATA );

	return 	result;
}

HWND Win32Object::getHwnd()
{
	return hwnd_;
}

void Win32Object::registerWin32Object( Win32Object* wndObj )
{
	Win32Object::windowMap_[ wndObj->getHwnd() ] = wndObj;
	//::SetWindowLongPtr( wndObj->getHwnd(), GWLP_USERDATA, (LONG_PTR)wndObj );

	::PostMessage( wndObj->getHwnd(), VCF_CONTROL_CREATE, 0, 0 );
}

void Win32Object::registerWin32ObjectQuietly( Win32Object* wndObj )
{
	Win32Object::windowMap_[ wndObj->getHwnd() ] = wndObj;
}

void Win32Object::unRegisterWin32Object( Win32Object* wndObj )
{
	if ( Win32Object::windowMap_.empty() ) {
		return;
	}

	std::map<HWND, Win32Object*>::iterator found =  Win32Object::windowMap_.find( wndObj->getHwnd() );
	if ( found != Win32Object::windowMap_.end() ){
		Win32Object::windowMap_.erase( found );
	}
}

LRESULT Win32Object::defaultWndProcedure( UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;
	
	if ( System::isUnicodeEnabled() ) {
		if ( NULL != defaultWndProc_ ){
			result = CallWindowProcW( defaultWndProc_, hwnd_, message, wParam, lParam );
		}
		else {
			result = DefWindowProcW( hwnd_, message, wParam, lParam );
		}
	}
	else{
		
		if ( NULL != defaultWndProc_ ){
			result = CallWindowProcA( defaultWndProc_, hwnd_, message, wParam, lParam );
		}
		else {
			result = DefWindowProcA( hwnd_, message, wParam, lParam );
		}
	}
	

	return result;
}

void Win32Object::setCreated( const bool& creationComplete )
{
	created_ = creationComplete;
}

bool Win32Object::isCreated()
{
	return created_;
}

void Win32Object::setPeerControl( Control* control )
{
	peerControl_ = control;
}

Control* Win32Object::getPeerControl()
{
	return peerControl_;
}


/**
$Id$
*/
