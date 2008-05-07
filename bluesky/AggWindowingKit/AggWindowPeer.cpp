
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggWindowPeer.h"
#include "AggUIToolkit.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

#if defined(VCF_WIN)
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#endif 



#include "AggGraphicsPeers.h"




using namespace VCF;

#ifdef VCF_WIN 

static ATOM AggWndClassAtom = NULL;

static std::deque<AggWindowPeer*> windowPeerStack;

LRESULT CALLBACK AggWindowPeer::InitialWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	AggWindowPeer* thisPtr = windowPeerStack.front();
	windowPeerStack.pop_front();

	thisPtr->hwnd_ = hwnd;
	thisPtr->thunker_.init( AggWindowPeer::WndProc, thisPtr );

	WNDPROC proc = (WNDPROC) &(thisPtr->thunker_.thunk);
	::SetWindowLong( hwnd, GWL_WNDPROC, (LONG)proc );

	return proc( hwnd, msg, wParam, lParam );
}



LRESULT CALLBACK AggWindowPeer::WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;

	AggWindowPeer* thisPtr = (AggWindowPeer*)hwnd;

	MSG wndMsg = {0};
	wndMsg.hwnd = thisPtr->hwnd_;
	wndMsg.lParam = lParam;
	wndMsg.message = message;
	wndMsg.wParam = wParam;
	
	OSMessage msg;
	msg.control = thisPtr->control_;
	msg.msgData = &wndMsg;

	Event* event = UIToolkit::createEventFromNativeOSEventData( &msg );


	switch ( message ) {

		case WM_PAINT:{
			PAINTSTRUCT ps = {0};
			::BeginPaint( thisPtr->hwnd_, &ps );


			if ( (NULL != thisPtr->memDC_) && (NULL != thisPtr->memBMP_) ) {
				RECT r;
				GetClientRect( thisPtr->hwnd_, &r );
				DrawingSurface surf;
				surf.dirtyRect.left_ = ps.rcPaint.left;
				surf.dirtyRect.top_ = ps.rcPaint.top;
				surf.dirtyRect.right_ = ps.rcPaint.right;
				surf.dirtyRect.bottom_ = ps.rcPaint.bottom;
				surf.imageData = (unsigned char*)  thisPtr->memDataPtr_;
				surf.height = r.bottom - r.top;
				surf.width = r.right - r.left;				

				GraphicsContext gc (&surf) ;


				thisPtr->control_->paint( &gc );

			}


			::BitBlt( ps.hdc, ps.rcPaint.left, ps.rcPaint.top, 
						ps.rcPaint.right - ps.rcPaint.left,
						ps.rcPaint.bottom - ps.rcPaint.top,
						thisPtr->memDC_, ps.rcPaint.left, ps.rcPaint.top,SRCCOPY );

			


			::EndPaint( thisPtr->hwnd_, &ps );
		}
		break;


		case WM_SIZE:{

			if ( NULL == thisPtr->memDC_ ) {
				//create
				HDC dc = ::GetDC( ::GetDesktopWindow() );
				thisPtr->memDC_ = ::CreateCompatibleDC( dc );
				::ReleaseDC( ::GetDesktopWindow(), dc );
			}

			if ( NULL != thisPtr->memBMP_ ) {
				DeleteObject( thisPtr->memBMP_ );
			}

			BITMAPINFO bmpInfo;		
			memset( &bmpInfo, 0, sizeof (BITMAPINFOHEADER) );
			bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
			bmpInfo.bmiHeader.biWidth = LOWORD(lParam);
			bmpInfo.bmiHeader.biHeight = -HIWORD(lParam);
			bmpInfo.bmiHeader.biPlanes = 1;
			bmpInfo.bmiHeader.biBitCount = 32;
			bmpInfo.bmiHeader.biCompression = BI_RGB;
			bmpInfo.bmiHeader.biSizeImage = HIWORD(lParam) * LOWORD(lParam) * 4;
			
			thisPtr->memBMP_ = CreateDIBSection ( thisPtr->memDC_, &bmpInfo, DIB_RGB_COLORS, (void **)&thisPtr->memDataPtr_, NULL, NULL );

			::SelectObject( thisPtr->memDC_, thisPtr->memBMP_ );


			result = ::DefWindowProc( thisPtr->hwnd_, message, wParam, lParam );
		}
		break;


		case WM_CLOSE:{
			if ( !thisPtr->control_->isDesigning() ) {				
				//check if we need to re notify the listeners of the close event
				
				VCF::Window* window = (VCF::Window*)thisPtr->getControl();
				
				if ( window->allowClose() ) {
					
					VCF::FrameEvent event( thisPtr->getControl(), Frame::CLOSE_EVENT );
					
					
					window->FrameClose( &event );
					
					if ( !thisPtr->internalClose_ ){
						//check if the main window is clossing - if it is
						//then close the app !
						
						Application* app = Application::getRunningInstance();
						if ( NULL != app ){
							Window* mainWindow = app->getMainWindow();
							if ( mainWindow == thisPtr->getControl() ){
								::PostMessage( thisPtr->hwnd_, WM_QUIT, 0, 0 );
							}
							else {
								result = ::DefWindowProc( thisPtr->hwnd_, message, wParam, lParam );
							}
						}
					}
					else {
						result = ::DefWindowProc( thisPtr->hwnd_, message, wParam, lParam );
					}
				}
				else {
					result = 0;
				}
			}
		}
		break;

		default :
		{
			if ( NULL != event ) {
				thisPtr->control_->handleEvent( event );
			}

			result = ::DefWindowProc( thisPtr->hwnd_, message, wParam, lParam );
		}
		break;
	}	

	if ( NULL != event ) {
		delete event;
	}

	return result;
}



AggWindowPeer::AggWindowPeer( Control* control, Control* owner ) :
    AggAbstractControl(control),
		hwnd_(NULL),
		internalClose_(false),
		memDC_(NULL),
		memBMP_(NULL),
		memDataPtr_(NULL)
{
	
}

Rect AggWindowPeer::getClientBounds()
{
	RECT r;
	::GetClientRect( hwnd_, &r );

	clientBounds_.setRect( r.left, r.top, r.right, r.bottom );

	return clientBounds_;
}

void  AggWindowPeer::setClientBounds( Rect* bounds )
{
	clientBounds_ = *bounds;

	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	LONG_PTR exStyle = ::GetWindowLongPtr( hwnd_, GWL_EXSTYLE );

	RECT r = {0,0,0,0};

	r.left = bounds->left_;
	r.top = bounds->top_;
	r.right = bounds->right_;
	r.bottom = bounds->bottom_;

	if ( (style & WS_DLGFRAME) || (style & WS_THICKFRAME) ) {
		r.left = (r.left - GetSystemMetrics(SM_CXFRAME));

		r.top = (r.top - GetSystemMetrics(SM_CYFRAME));

		r.right += GetSystemMetrics(SM_CXFRAME);

		r.bottom += GetSystemMetrics(SM_CYFRAME);
	}

	if ( (style & WS_CAPTION) != 0 ) {
		int cy = GetSystemMetrics( SM_CYCAPTION );
		if ( (exStyle & WS_EX_TOOLWINDOW) != 0 ) {
			cy = GetSystemMetrics( SM_CYSMCAPTION );
		}
		else {
			cy = GetSystemMetrics( SM_CYCAPTION );
		}

		r.top -= cy;
	}


	::MoveWindow( hwnd_, r.left, r.top,
			r.right - r.left, r.bottom - r.top, TRUE );
}

void AggWindowPeer::close()
{
	if ( false == internalClose_ ){
		internalClose_ = true;
		Application* app = Application::getRunningInstance();
		if ( NULL != app ){
			Window* mainWindow = app->getMainWindow();
			if ( mainWindow == getControl() ){
				::PostMessage( hwnd_, WM_QUIT, 0, 0 );
			}
		}
	}

	::PostMessage( hwnd_, WM_CLOSE, 0, 0 );
}

void AggWindowPeer::setFrameStyle( const FrameStyleType& frameStyle )
{
	
}

void AggWindowPeer::setFrameTopmost( const bool& isTopmost )
{
	
}

bool AggWindowPeer::isMaximized()
{
	
	return false;
}

void AggWindowPeer::setMaximized( const bool maximised )
{
	
}

bool AggWindowPeer::isMinimized()
{
	return false;
}

void AggWindowPeer::setMinimized( const bool& minimized )
{
	
}

void AggWindowPeer::restore()
{
	
}

void AggWindowPeer::setIconImage( Image* icon )
{
	
}

bool AggWindowPeer::isActiveWindow()
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////
void AggWindowPeer::create( Control* owningControl )
{
	
	WNDCLASSEXW wndClass = {0};
	wndClass.cbSize = sizeof(wndClass);

	AggWndClassAtom = ::GetClassInfoExW( NULL, L"VCF::AggWindow", &wndClass );
	if ( NULL == AggWndClassAtom ) {
		//register

		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_DBLCLKS | CS_OWNDC;
		wndClass.lpfnWndProc = AggWindowPeer::InitialWndProc;
		wndClass.lpszClassName = L"VCF::AggWindow";

		AggWndClassAtom = ::RegisterClassExW(&wndClass);
	}

	owningWindow_ = this;

	windowPeerStack.push_back( this );

	

	HWND h = CreateWindowExW( 0, (LPCWSTR)MAKELONG(AggWndClassAtom, 0), NULL, 
							WS_POPUP | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
							0, 0, 1, 1, NULL, NULL, ::GetModuleHandleW(NULL), NULL );


	VCF_ASSERT(hwnd_ != NULL);
}

void AggWindowPeer::destroyControl()
{
	if ( NULL != hwnd_ ){
		if ( IsWindow( hwnd_ ) ) {
			::DestroyWindow( hwnd_ );
		}
	}

	if ( NULL != this->memBMP_ ) {
		DeleteObject( memBMP_ );
		memBMP_ = NULL;
	}
	if ( NULL != this->memDC_ ) {
		DeleteDC(memDC_);
	}
}

OSHandleID AggWindowPeer::getHandleID()
{
	return reinterpret_cast<OSHandleID>(NULL);
}

String AggWindowPeer::getText()
{
	
	return "";
}

void AggWindowPeer::setText( const String& text )
{
	::SetWindowTextW( hwnd_, text.c_str() );
}

void AggWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);
	VCF_ASSERT(hwnd_ != NULL);

	RECT r = {0,0,0,0};

	r.left = rect->left_;
	r.top = rect->top_;
	r.right = rect->right_;
	r.bottom = rect->bottom_;
	
	int err = ::SetWindowPos( hwnd_, NULL, (int)rect->left_, (int)rect->top_,
			          (int)rect->getWidth(), (int)rect->getHeight(), SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER );

	err = ::GetLastError();
	
}

bool AggWindowPeer::beginSetBounds( const uint32& numberOfChildren )
{	
	return true;
}

void AggWindowPeer::endSetBounds()
{
}

Rect AggWindowPeer::getBounds()
{
	VCF_ASSERT(hwnd_ != NULL);

	RECT r = {0};
	GetWindowRect( hwnd_, &r );

	Rect result( r.left, r.top, r.right, r.bottom );
	
	return result;
}

void AggWindowPeer::setVisible( const bool& visible )
{
	VCF_ASSERT(hwnd_ != NULL);

	if ( control_->isDesigning() || control_->isLoading() ) {
		
		if ( NULL != GetParent(hwnd_) ) {
			if ( visible ){
				::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );				
			}
			else{
				::ShowWindow( hwnd_, SW_HIDE );
			}
		}
	}
	else {
		
		if ( true == visible ){
			
			Frame* frame = (Frame*)control_;
			
			switch ( frame->getFrameStyle() ){
				case fstToolbarBorderFixed : case fstToolbarBorder : case fstSizeable : case fstFixed :{
					::ShowWindow( hwnd_, SW_SHOW );//SW_SHOWNORMAL );
					//not sure if we want this here...
					::BringWindowToTop( hwnd_ );

					//we need this here to repaint the window contents???
					//seems kind of funky, but it works
					::RedrawWindow( hwnd_, NULL, NULL, RDW_INVALIDATE | RDW_ERASENOW | RDW_ALLCHILDREN);
				}
				break;
				
				case fstNoBorder : case fstNoBorderFixed : {
					::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
					::RedrawWindow( hwnd_, NULL, NULL, RDW_INVALIDATE | RDW_ERASENOW | RDW_ALLCHILDREN);
				}
				break;
			}
		}
		else{
			::ShowWindow( hwnd_, SW_HIDE );
		}
	}
}

bool AggWindowPeer::getVisible()
{

	return ::IsWindowVisible( hwnd_ ) ? true : false;
}


void AggWindowPeer::setCursor( Cursor* cursor )
{
	
}


bool AggWindowPeer::isFocused()
{
	return AggAbstractControl::isFocused();
}

void AggWindowPeer::setFocused()
{
	AggAbstractControl::setFocused();
}

bool AggWindowPeer::isEnabled()
{
	return AggAbstractControl::isEnabled();
}

void AggWindowPeer::setEnabled( const bool& enabled )
{
	AggAbstractControl::setEnabled( enabled );
}

void AggWindowPeer::setFont( Font* font )
{
	AggAbstractControl::setFont( font );
}

void AggWindowPeer::repaint( Rect* repaintRect, const bool& immediately )
{
	
}

void AggWindowPeer::keepMouseEvents()
{
	AggAbstractControl::keepMouseEvents();

	VCF_ASSERT(NULL != hwnd_);
	::SetCapture( hwnd_ );
}

void AggWindowPeer::releaseMouseEvents()
{
	AggAbstractControl::releaseMouseEvents();
	VCF_ASSERT(NULL != hwnd_);
	::ReleaseCapture();
}

void AggWindowPeer::translateToScreenCoords( Point* pt )
{
	VCF_ASSERT(NULL != hwnd_);
	POINT aPt = { (int32)pt->x_, (int32)pt->y_ };
	ClientToScreen( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AggWindowPeer::translateFromScreenCoords( Point* pt )
{
	VCF_ASSERT(NULL != hwnd_);
	POINT aPt = { (int32)pt->x_, (int32)pt->y_ };
	ScreenToClient( hwnd_, &aPt );
	pt->x_ = aPt.x;
	pt->y_ = aPt.y;
}

void AggWindowPeer::setBorder( Border* border )
{
	VCF_ASSERT(NULL != hwnd_);
	SetWindowPos(hwnd_, NULL,0,0,0,0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE);
}

void AggWindowPeer::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{

}

void AggWindowPeer::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{

}


void AggWindowPeer::setBorderPath( Path* path )
{

}

#else 
AggWindowPeer::AggWindowPeer( Control* control, Control* owner ) :
    AggAbstractControl(control)
	
{
	
}

Rect AggWindowPeer::getClientBounds()
{
	return clientBounds_;
}

void  AggWindowPeer::setClientBounds( Rect* bounds )
{
	clientBounds_ = *bounds;

	
}

void AggWindowPeer::close()
{
	
}

void AggWindowPeer::setFrameStyle( const FrameStyleType& frameStyle )
{
	
}

void AggWindowPeer::setFrameTopmost( const bool& isTopmost )
{
	
}

bool AggWindowPeer::isMaximized()
{
	
	return false;
}

void AggWindowPeer::setMaximized( const bool maximised )
{
	
}

bool AggWindowPeer::isMinimized()
{
	return false;
}

void AggWindowPeer::setMinimized( const bool& minimized )
{
	
}

void AggWindowPeer::restore()
{
	
}

void AggWindowPeer::setIconImage( Image* icon )
{
	
}

bool AggWindowPeer::isActiveWindow()
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////
void AggWindowPeer::create( Control* owningControl )
{
	

	owningWindow_ = this;
}

void AggWindowPeer::destroyControl()
{
	
}

OSHandleID AggWindowPeer::getHandleID()
{
	return reinterpret_cast<OSHandleID>(NULL);
}

String AggWindowPeer::getText()
{
	
	return "";
}

void AggWindowPeer::setText( const String& text )
{
	
}

void AggWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	
}

bool AggWindowPeer::beginSetBounds( const uint32& numberOfChildren )
{	
	return true;
}

void AggWindowPeer::endSetBounds()
{
}

Rect AggWindowPeer::getBounds()
{
	return clientBounds_;
}

void AggWindowPeer::setVisible( const bool& visible )
{
	
}

bool AggWindowPeer::getVisible()
{

	return AggAbstractControl::getVisible();
}


void AggWindowPeer::setCursor( Cursor* cursor )
{
	
}


bool AggWindowPeer::isFocused()
{
	return AggAbstractControl::isFocused();
}

void AggWindowPeer::setFocused()
{
	AggAbstractControl::setFocused();
}

bool AggWindowPeer::isEnabled()
{
	return AggAbstractControl::isEnabled();
}

void AggWindowPeer::setEnabled( const bool& enabled )
{
	AggAbstractControl::setEnabled( enabled );
}

void AggWindowPeer::setFont( Font* font )
{
	AggAbstractControl::setFont( font );
}

void AggWindowPeer::repaint( Rect* repaintRect, const bool& immediately )
{
	
}

void AggWindowPeer::keepMouseEvents()
{
	AggAbstractControl::keepMouseEvents();
}

void AggWindowPeer::releaseMouseEvents()
{
	AggAbstractControl::releaseMouseEvents();
}

void AggWindowPeer::translateToScreenCoords( Point* pt )
{
	
}

void AggWindowPeer::translateFromScreenCoords( Point* pt )
{
	
}

void AggWindowPeer::setBorder( Border* border )
{
	
}

void AggWindowPeer::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{

}

void AggWindowPeer::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{

}


void AggWindowPeer::setBorderPath( Path* path )
{

}

#endif //VCF_WIN


/**
$Id$
*/


