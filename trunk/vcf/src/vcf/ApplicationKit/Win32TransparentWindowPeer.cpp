//Win32TransparentWindowPeer.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/TransparentWindowPeer.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/ApplicationKit/Win32TransparentWindowPeer.h"

using namespace VCF;

#if(_WIN32_WINNT < 0x0500)

# define WS_EX_LAYERED 0x80000 
#define LWA_COLORKEY 1 
#define LWA_ALPHA 2 

#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004

typedef DWORD (WINAPI *SetLayeredWindowAttributesFunc)(HWND, DWORD, BYTE, DWORD);

static SetLayeredWindowAttributesFunc SetLayeredWindowAttributes = NULL;

typedef BOOL (WINAPI *UpdateLayeredWindowFunc)(HWND, HDC, POINT*,SIZE*,HDC,POINT*,
										   COLORREF,BLENDFUNCTION*,DWORD);

static UpdateLayeredWindowFunc UpdateLayeredWindow = NULL;

#endif


Win32TransparentWindowPeer::Win32TransparentWindowPeer( Frame* frame )
{
	owner_ = frame;
	alpha_ = 1.0;
#if(_WIN32_WINNT < 0x0500)
	HMODULE user32DLL = LoadLibrary ("user32");
	if ( NULL == SetLayeredWindowAttributes ) {
		SetLayeredWindowAttributes =  
    (SetLayeredWindowAttributesFunc) GetProcAddress(user32DLL,"SetLayeredWindowAttributes");
	}

	if ( NULL == UpdateLayeredWindow ) {
		UpdateLayeredWindow =  
    (UpdateLayeredWindowFunc) GetProcAddress(user32DLL,"UpdateLayeredWindow");
	}

	FreeLibrary( user32DLL );
#endif
}


Win32TransparentWindowPeer::~Win32TransparentWindowPeer()
{

}

Win32Object::CreateParams Win32TransparentWindowPeer::createParams()
{
	Win32Object::CreateParams result;

	result.first = WS_POPUP | WS_VISIBLE;
	result.second = WS_EX_LAYERED;


	return result;
}

void Win32TransparentWindowPeer::create( Control* owningControl )
{
	peerControl_ = owningControl;

	CreateParams params = createParams();

	String className = getClassName();

	if ( true != isRegistered() ){
		if ( className.empty() ) {
			className = "VCF::Win32TransparentWindowPeer";
		}
		registerWin32Class( className, wndProc_  );
	}

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();

	HWND parent = NULL;//toolkit->getDummyParent();

	if ( NULL != owner_ ){
		parent = (HWND)owner_->getPeer()->getHandleID();
	}

	HICON icon = NULL;

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
									 NULL, ::GetModuleHandleW(NULL), NULL );

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
									 NULL, ::GetModuleHandleA(NULL), NULL );
		
	}



	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		registerForFontChanges();

		//SetLayeredWindowAttributes ( hwnd_, RGB(255,255,255), (int) (255.0 * alpha_), LWA_ALPHA );

		ShowWindow( hwnd_, SW_HIDE );
	}

	setCreated( true );
}

void Win32TransparentWindowPeer::setAlpha( const double& alphaValue )
{
	alpha_ = alphaValue;

	SetLayeredWindowAttributes ( hwnd_, RGB(255,255,255), (int) (255.0 * alpha_), LWA_ALPHA );
}

double Win32TransparentWindowPeer::getAlpha()
{
	return alpha_;
}

void Win32TransparentWindowPeer::setAlphaImage( Image* img )
{
	if ( NULL != img ) {
		COLORREF alphaColor;

		if ( img->isTransparent() ) {
			alphaColor = RGB(0,0,0);//img->getTransparencyColor()->getColorRef32();
		}
		else {
			ColorPixels pix = img;
			ColorPixels::Type* bits = pix;

			alphaColor = RGB( bits[0].r, bits[0].g, bits[0].b );
		}
		SetLayeredWindowAttributes ( hwnd_, alphaColor,100, 
									LWA_COLORKEY );

		RedrawWindow(hwnd_, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME |
										RDW_ALLCHILDREN);
	}
	else {
		SetLayeredWindowAttributes ( hwnd_, RGB(255,255,255), (int) (255.0 * alpha_), LWA_ALPHA );
	}


}

bool Win32TransparentWindowPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc)
{
	bool result = false;	

	switch ( message ) {
		case WM_MOUSEACTIVATE : {
			wndProcResult = MA_NOACTIVATE;
			result = true;
		}
		break;

		case WM_NCACTIVATE : {
			
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

		default : {
			result = Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult, defaultWndProc );
		}
		break;
	}

	return result;
}

void Win32TransparentWindowPeer::setVisible( const bool& visible )
{
	if ( visible ){
		::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );				
	}
	else{
		::ShowWindow( hwnd_, SW_HIDE );
	}
}