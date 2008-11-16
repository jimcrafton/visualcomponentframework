//Win32Window.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Window.h"


using namespace VCF;




Win32Window::Win32Window():
	AbstractWin32Component( NULL ),
	internalClose_(false),
	owner_(NULL),
	activatesPending_(false)
{

}

Win32Window::Win32Window( Control* component, Control* owner ):
	AbstractWin32Component( component ),
	internalClose_(false),
	owner_(owner),
	activatesPending_(false)
{

}

Win32Window::~Win32Window()
{

}

void Win32Window::create( Control* owningControl )
{
	
	CreateParams params = createParams();

	String className = getClassName();

	if ( true != isRegistered() ){
		if ( className.empty() ) {
			className = "VCF::Win32Window";
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

		icon = LoadIconW( Win32ToolKit::getInstanceHandle(), L"DefaultVCFIcon" );
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

		icon = LoadIconA( Win32ToolKit::getInstanceHandle(), "DefaultVCFIcon" );
		//Do we need to destroy the icon????
	}



	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		registerForFontChanges();

		if ( NULL != icon ) {		
			SendMessage( hwnd_, WM_SETICON, ICON_BIG, (LPARAM) icon );
		}

	}
	else {
		//throw exception
	}

	setCreated( true );
}

Win32Object::CreateParams Win32Window::createParams()
{
	Win32Object::CreateParams result;

	result.first = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	result.first &= ~WS_VISIBLE;
	
	result.second = 0;

	return result;
}

Rect Win32Window::getClientBounds()
{
	RECT r;
	::GetWindowRect( hwnd_, &r );
	::GetClientRect( hwnd_, &r );

	Rect result( r.left, r.top, r.right, r.bottom );

	return result;
}

void  Win32Window::setClientBounds( Rect* bounds )
{
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

void Win32Window::setBounds( VCF::Rect* rect )
{
	AbstractWin32Component::setBounds( rect );
}

void Win32Window::setVisible( const bool& visible )
{
	if ( peerControl_->isDesigning() || peerControl_->isLoading() ) {
		
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
		//StringUtils::trace( Format( "Win32Window::setVisible( %d )\n" ) % visible );
		if ( true == visible ){
			
			Frame* frame = (Frame*)peerControl_;
			
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

void Win32Window::handleActivate()
{	
	if ( NULL != peerControl_ ) {
		//do nothing if we are in design mode

		if ( peerControl_->isDesigning() || peerControl_->isLoading() ) {
			return;
		}

		activatesPending_ = true;
		
		Frame* frame = (Frame*)peerControl_;
		if ( peerControl_->isNormal() ) {
			frame->activate();
		}
	}	
}

bool Win32Window::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;


	static bool windowRestoredAlready = true;
	switch ( message ) {
		case WM_SETTINGCHANGE : {
			//settings change!

			result = true;

			wndProcResult = 0;

			::RedrawWindow( hwnd_, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

			return result;
		}
		break;


		case WM_GETMINMAXINFO : {
			
			if ( !peerControl_->isDesigning() ) {
				result = false;
				wndProcResult = 0;
				
				Size minSize = peerControl_->getMinSize();
				Size maxSize = peerControl_->getMaxSize();
				
				
				MINMAXINFO* info = (MINMAXINFO*)lParam;
				
				if ( minSize.width_ > Control::mmIgnoreMinWidth ) {
					info->ptMinTrackSize.x = minSize.width_;
				}
				
				if ( minSize.height_ > Control::mmIgnoreMinHeight ) {
					info->ptMinTrackSize.y = minSize.height_;
				}
				
				if ( maxSize.width_ > Control::mmIgnoreMaxWidth ) {
					info->ptMaxTrackSize.x = maxSize.width_;
				}
				
				if ( maxSize.height_ > Control::mmIgnoreMaxHeight ) {
					info->ptMaxTrackSize.y = maxSize.height_;
				}
			}

		}
		break;

		case WM_SIZE : {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			switch ( wParam ) {
				case SIZE_MAXIMIZED : {
					windowRestoredAlready = false;
					Frame* frame = (Frame*)peerControl_;
					Window* window = dynamic_cast<Window*>(frame);
					if ( NULL != window ) {
						WindowEvent e(window,WINDOW_EVENT_MAXIMIZE);
						window->WindowMaximize( &e );
					}
				}
				break;

				case SIZE_MINIMIZED : {
					windowRestoredAlready = false;
					Frame* frame = (Frame*)peerControl_;
					Window* window = dynamic_cast<Window*>(frame);
					if ( NULL != window ) {
						WindowEvent e(window,WINDOW_EVENT_MINIMIZE);
						window->WindowMinimize( &e );
					}
				}
				break;

				case SIZE_RESTORED : {

					if ( !windowRestoredAlready ) {
						Frame* frame = (Frame*)peerControl_;
						Window* window = dynamic_cast<Window*>(frame);
						if ( NULL != window ) {
							WindowEvent e(window,WINDOW_EVENT_RESTORE);
							window->WindowRestore( &e );
						}
					}
					windowRestoredAlready = true;
				}
				break;
			}

		}
		break;

		

		case VCF_CONTROL_CREATE: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			if ( activatesPending_ ) {
				activatesPending_ = false;
				if ( !(peerControl_->isDesigning() || peerControl_->isLoading()) ) {
					::PostMessage( hwnd_, WM_ACTIVATE, MAKEWPARAM (WA_ACTIVE,0), 0 );
				}
			}
		}
		break;

		case WM_SYSCOMMAND: {
			
			if ( peerControl_->isDesigning() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			}		
		}
		break;

		case WM_NCLBUTTONDOWN: {
			handleActivate();

			if ( peerControl_->isDesigning() ) {
				wndProcResult = 0;
				result = false;
			}
			else {
				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
				wndProcResult = 0;
				result = false;
			}			
		}
		break;

		case WM_NCACTIVATE : {
			if ( NULL != peerControl_ ) {
				BOOL active = (BOOL)wParam;
				
				if ( peerControl_->isDesigning() || peerControl_->isLoading() ) {
					wndProcResult = TRUE;
					result = true;
				}
				else {
					result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
					
					Frame* frame = (Frame*)peerControl_;
					//StringUtils::trace( Format( "WM_NCACTIVATE, active: %d\n" ) % active );
					
					if ( active ) {
						handleActivate();
					}
				}
			}
		}
		break;

		case WM_ACTIVATEAPP : {
			BOOL fActive = (BOOL) wParam;

			//do nothing if we are in design mode
			if ( peerControl_->isDesigning() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				//StringUtils::trace( Format( "WM_ACTIVATEAPP, fActive: %d\n" ) % fActive );
				if ( !fActive && (NULL != peerControl_) ) {
					
					Frame* frame = (Frame*)peerControl_;
					
					switch ( frame->getFrameStyle() ){
						
						case fstNoBorder : case fstNoBorderFixed : {
							Frame::internal_setActiveFrame( NULL );
							if ( frame->getComponentState() == Component::csNormal ) {
								VCF::WindowEvent event( frame, Frame::ACTIVATION_EVENT );
								frame->FrameActivation( &event );
							}
						}
						break;
					}
					
				}
				else if ( fActive && (NULL != peerControl_) ) {
					RedrawWindow( hwnd_, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN );	
				}
				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			}
		}
		break;

		case WM_ACTIVATE : {

			if ( NULL != peerControl_ ) {
				BOOL active = LOWORD(wParam);
				
				if ( peerControl_->isDesigning() || peerControl_->isLoading() ) {
					wndProcResult = 0;
					result = (WA_INACTIVE == active) ? false : true;
					
					HWND hwndPrevious = (HWND) lParam; 
					
					Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hwndPrevious );			
					
					if ( (NULL != win32Obj) && active ) {
						SetActiveWindow( hwndPrevious );
					}
				}
				else {
					result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
					
					
					
					if ( active ) {
						handleActivate();
						
						if ( !peerControl_->isDesigning() ) {
							::BringWindowToTop( hwnd_ );
						}
					}
				}
			}
		}
		break;

		case WM_LBUTTONDOWN : {
			Frame* frame = (Frame*)peerControl_;

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			handleActivate();
		}
		break;

		case WM_MOUSEACTIVATE : {

			if ( peerControl_->isDesigning() || peerControl_->isLoading() ) {
				wndProcResult = MA_NOACTIVATE;
				result = true;
			}
			else {
				Frame* frame = (Frame*)peerControl_;

				switch ( frame->getFrameStyle() ){
					case fstToolbarBorderFixed : case fstToolbarBorder : case fstSizeable : case fstFixed :{
						result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
					}
					break;

					case fstNoBorder : case fstNoBorderFixed : {

						/**
						NOTE!!!!
						This MUST return true. Returning true means that we have handled all the processing
						and no further processing by the DefWndProc is required. If we don't return 
						true here (i.e. result = true), then we end up with focus/activate issues with the
						controls that popup a fixed window, like the drop down list box for the
						ComboBoxControl.
						*/
						result = true;
						wndProcResult = MA_NOACTIVATE;
					}
					break;
				}

				handleActivate();
			}
		}
		break;

		case WM_CLOSE:{
			if ( peerControl_->isDesigning() ) {
				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			}
			else {
				result = false;
				wndProcResult = 0;
				//check if we need to re notify the listeners of the close event
				
				VCF::Window* window = (VCF::Window*)getControl();
				
				if ( window->allowClose() ) {
					
					VCF::FrameEvent event( getControl(), Frame::CLOSE_EVENT );
					
					
					window->FrameClose( &event );
					
					if ( false == internalClose_ ){
						//check if the main window is clossing - if it is
						//then close the app !
						
						Application* app = Application::getRunningInstance();
						if ( NULL != app ){
							Window* mainWindow = app->getMainWindow();
							if ( mainWindow == getControl() ){
								::PostMessage( hwnd_, WM_QUIT, 0, 0 );
							}
							else {
								result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
							}
						}
					}
					else {
						result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
					}
				}
				else {
					result = true;
				}
			}
		}
		break;

		case WM_PAINT:{
			if ( isCreated() ){
				if ( peerControl_->getComponentState() != Component::csDestroying ) {
					if( !GetUpdateRect( hwnd_, NULL, FALSE ) ){
						wndProcResult = 0;
						result = true;
						return result;
					}

					PAINTSTRUCT ps;
					HDC contextID = 0;
					contextID = ::BeginPaint( hwnd_, &ps);

					Rect r(ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right,ps.rcPaint.bottom);
					this->prepForDoubleBufferPaint(ps.hdc,r);

					doControlPaint( contextID, ps.rcPaint, NULL, cpControlOnly );
					updatePaintDC( contextID, ps.rcPaint, NULL );

					::EndPaint( hwnd_, &ps);
				}
			}

			wndProcResult = 0;
			result = true;
		}
		break;

		case WM_DESTROY: {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}

	return result;
}

void Win32Window::close()
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

void Win32Window::setFrameStyle( const FrameStyleType& frameStyle )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	LONG_PTR exStyle = ::GetWindowLongPtr( hwnd_, GWL_EXSTYLE );
	bool needsParent = false;
	switch ( frameStyle ){
		case fstSizeable :{
			style |= WS_OVERLAPPEDWINDOW;
			exStyle &= ~WS_EX_TOOLWINDOW;
			exStyle |= WS_EX_WINDOWEDGE;// otherwise it is not resizable anymore (MP)
			style |= WS_THICKFRAME;
		}
		break;

		case fstNoBorder :{
			style &= ~WS_DLGFRAME;
			style &= ~WS_OVERLAPPEDWINDOW;
			style |= WS_THICKFRAME;
			exStyle &= ~WS_EX_TOOLWINDOW;
			needsParent = true;
		}
		break;

		case fstFixed :{
			style |= WS_OVERLAPPEDWINDOW;
			
			//remove the max/min box
			style &= ~WS_MAXIMIZEBOX;
			style &= ~WS_MINIMIZEBOX;

			style &= ~WS_THICKFRAME;
			exStyle &= ~WS_EX_TOOLWINDOW;
		}
		break;

		case fstNoBorderFixed :{
			style &= ~WS_OVERLAPPEDWINDOW;
			exStyle &= ~WS_EX_TOOLWINDOW;
		}
		break;

		case fstToolbarBorder :{
			style &= ~WS_OVERLAPPEDWINDOW;
			style |= WS_POPUPWINDOW | WS_DLGFRAME | WS_THICKFRAME | WS_OVERLAPPED | 0x0003B00;

			exStyle |= WS_EX_TOOLWINDOW;
		}
		break;

		case fstToolbarBorderFixed :{
			exStyle |= WS_EX_TOOLWINDOW;
			style &= ~WS_THICKFRAME;
		}
		break;

	}

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
	::SetWindowLongPtr( hwnd_, GWL_EXSTYLE, exStyle );

	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( hwnd_ );
}

void Win32Window::setFrameTopmost( const bool& isTopmost )
{
	if ( true == isTopmost ){
		::SetWindowPos( hwnd_, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );
	}
	else{
		::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	}
}

LONG_PTR Win32Window::generateStyleForSetParent(VCF::Control* parent)
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
		}		
	}

	return result;
}

void Win32Window::setParent( VCF::Control* parent )
{
	bool showWindow = false;

	LONG_PTR oldStyle = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	LONG_PTR style = generateStyleForSetParent(parent);

	if ( NULL == parent ) {
		if ( !peerControl_->isDesigning() ) {
			::SetParent( hwnd_, NULL );
		}
	}
	else {
		VCF::ControlPeer* peer = parent->getPeer();
		HWND wndParent = (HWND)peer->getHandleID();
		::SetParent( hwnd_, wndParent );

		if ( (peerControl_->isDesigning()) && (NULL != wndParent) && (style & WS_CHILD) ) {
			showWindow = peerControl_->getVisible();
		}
	}

	if ( oldStyle != style ) {
		::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
		::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
	}

	if ( showWindow ) {
		setVisible( true );
	}
}

bool Win32Window::isMaximized()
{
	bool result = false;

	WINDOWPLACEMENT wndPlacement;
	memset( &wndPlacement, 0, sizeof(WINDOWPLACEMENT) );
	wndPlacement.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement( hwnd_, &wndPlacement );

	result = (wndPlacement.showCmd == SW_SHOWMAXIMIZED);

	return result;
}

void Win32Window::setMaximized( const bool maximised )
{
	WINDOWPLACEMENT wndPlacement;
	memset( &wndPlacement, 0, sizeof(WINDOWPLACEMENT) );
	wndPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement( hwnd_, &wndPlacement );

	wndPlacement.showCmd = maximised ? SW_SHOWMAXIMIZED : SW_NORMAL;
	SetWindowPlacement( hwnd_, &wndPlacement );
}

bool Win32Window::isMinimized()
{
	bool result = false;

	WINDOWPLACEMENT wndPlacement;
	memset( &wndPlacement, 0, sizeof(WINDOWPLACEMENT) );

	wndPlacement.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement( hwnd_, &wndPlacement );

	result = (wndPlacement.showCmd == SW_SHOWMINIMIZED);

	return result;
}

void Win32Window::setMinimized( const bool& minimized )
{
	WINDOWPLACEMENT wndPlacement ;
	memset( &wndPlacement, 0, sizeof(WINDOWPLACEMENT) );
	wndPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement( hwnd_, &wndPlacement );

	wndPlacement.showCmd = minimized ? SW_MINIMIZE : SW_NORMAL;
	SetWindowPlacement( hwnd_, &wndPlacement );
}

void Win32Window::restore()
{
	WINDOWPLACEMENT wndPlacement;
	memset( &wndPlacement, 0, sizeof(WINDOWPLACEMENT) );
	wndPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement( hwnd_, &wndPlacement );

	wndPlacement.showCmd = SW_RESTORE;

	SetWindowPlacement( hwnd_, &wndPlacement );
}

void Win32Window::setIconImage( Image* icon )
{
	Win32Image* win32Img = (Win32Image*)icon;

	HICON winIcon = win32Img->convertToIcon();

	//JC - I got rid of this - I don't know why it was 
	//here????
	//::SetClassLongPtr (hwnd_, GCL_HICON, (LONG_PTR)winIcon);
	
	SendMessage( hwnd_, WM_SETICON, ICON_BIG, (LPARAM)winIcon );

	RedrawWindow( hwnd_, NULL, 0, RDW_FRAME | RDW_INVALIDATE );


	//JC I commented this out. If this get's called
	//just before the window is made visible for the first time
	//then it ends up making everything (all the icons) disapear
	//in the TaskManager
	//::DestroyIcon( winIcon );
}

bool Win32Window::isActiveWindow()
{	
	return ::GetActiveWindow() == hwnd_ ? true : false;
}

void Win32Window::setText( const VCF::String& text )
{	
	if ( System::isUnicodeEnabled() ) {

		::SetWindowTextW( hwnd_, text.c_str() );
	}
	else {
		::SetWindowTextA( hwnd_, text.ansi_c_str() );
	}

}

void Win32Window::setBorderPath( Path* path )
{
	std::vector<Point> pts;

	path->flattenPoints(pts);

	std::vector<POINT> rgnPts(pts.size());
	for (size_t i=0;i<pts.size();i++ ) {
		POINT& p = rgnPts[i];
		const Point& p2 = pts[i];
		p.x = p2.x_;
		p.y = p2.y_;
	}


	HRGN rgn = CreatePolygonRgn( &rgnPts[0], rgnPts.size(), WINDING );

	if ( NULL != rgn ) {
		::SetWindowRgn( hwnd_, rgn, TRUE );
	}

}

/**
$Id$
*/
