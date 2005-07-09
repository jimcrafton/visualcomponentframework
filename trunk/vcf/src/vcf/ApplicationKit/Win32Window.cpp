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
			className = "Win32Window::Win32Window";
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

		setFont( owningControl->getFont() );

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
	DWORD style = (DWORD)::GetWindowLong( hwnd_, GWL_STYLE );
	DWORD exStyle = (DWORD)::GetWindowLong( hwnd_, GWL_EXSTYLE );

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
	//StringUtils::traceWithArgs( "Win32Window::setVisible( %d )\n", visible );
	if ( true == visible ){

		Frame* frame = (Frame*)peerControl_;

		switch ( frame->getFrameStyle() ){
			case fstToolbarBorderFixed : case fstToolbarBorder : case fstSizeable : case fstFixed :{
				::ShowWindow( hwnd_, SW_SHOW );//SW_SHOWNORMAL );
				//not sure if we want this here...
				::BringWindowToTop( hwnd_ );
			}
			break;

			case fstNoBorder : case fstNoBorderFixed : {
				::ShowWindow( hwnd_, SW_SHOWNOACTIVATE );
			}
			break;
		}
	}
	else{
		::ShowWindow( hwnd_, SW_HIDE );
	}
}

void Win32Window::handleActivate()
{
	activatesPending_ = true;

	Frame* frame = (Frame*)peerControl_;
	if ( peerControl_->isNormal() ) {
		frame->activate();
	}
}

bool Win32Window::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;


	static bool windowRestoredAlready = true;
	switch ( message ) {

		case WM_SIZE : {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			switch ( wParam ) {
				case SIZE_MAXIMIZED : {
					windowRestoredAlready = false;
					Frame* frame = (Frame*)peerControl_;
					Window* window = dynamic_cast<Window*>(frame);
					if ( NULL != window ) {
						WindowEvent e(window,WINDOW_EVENT_MAXIMIZE);
						window->WindowMaximize.fireEvent( &e );
					}
				}
				break;

				case SIZE_MINIMIZED : {
					windowRestoredAlready = false;
					Frame* frame = (Frame*)peerControl_;
					Window* window = dynamic_cast<Window*>(frame);
					if ( NULL != window ) {
						WindowEvent e(window,WINDOW_EVENT_MINIMIZE);
						window->WindowMinimize.fireEvent( &e );
					}
				}
				break;

				case SIZE_RESTORED : {

					if ( !windowRestoredAlready ) {
						Frame* frame = (Frame*)peerControl_;
						Window* window = dynamic_cast<Window*>(frame);
						if ( NULL != window ) {
							WindowEvent e(window,WINDOW_EVENT_RESTORE);
							window->WindowRestore.fireEvent( &e );
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
				::PostMessage( hwnd_, WM_ACTIVATE, MAKEWPARAM (WA_ACTIVE,0), 0 );
			}
		}
		break;

		case WM_NCLBUTTONDOWN: {
			handleActivate();			

			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			wndProcResult = 0;
			result = false;
		}
		break;

		case WM_NCACTIVATE : {
			BOOL active = (BOOL)wParam;


			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			Frame* frame = (Frame*)peerControl_;
			//StringUtils::traceWithArgs( "WM_NCACTIVATE, active: %d\n", active );

			if ( active ) {
				handleActivate();
			}
		}
		break;

		case WM_ACTIVATEAPP : {
			BOOL fActive = (BOOL) wParam;

			//StringUtils::traceWithArgs( "WM_ACTIVATEAPP, fActive: %d\n", fActive );
			if ( !fActive && (NULL != peerControl_) ) {
				Frame* frame = (Frame*)peerControl_;

				switch ( frame->getFrameStyle() ){

					case fstNoBorder : case fstNoBorderFixed : {
						Frame::internal_setActiveFrame( NULL );
						if ( frame->getComponentState() == Component::csNormal ) {
							VCF::WindowEvent event( frame, Frame::ACTIVATION_EVENT );
							frame->FrameActivation.fireEvent( &event );
						}
					}
					break;
				}
			}
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_ACTIVATE : {

			BOOL active = LOWORD(wParam);

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			//StringUtils::traceWithArgs( "WM_ACTIVATE, active: %d\n", active );

			if ( active ) {
				handleActivate();

				::BringWindowToTop( hwnd_ );
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
		break;

		case WM_CLOSE:{
			result = false;
			wndProcResult = 0;
			//check if we need to re notify the listeners of the close event

			VCF::Window* window = (VCF::Window*)getControl();

			if ( window->allowClose() ) {

				VCF::WindowEvent event( getControl(), WINDOW_EVENT_CLOSE );


				window->FrameClose.fireEvent( &event );

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
		break;

		case WM_PAINT:{
			if ( true == isCreated() ){
				if ( peerControl_->getComponentState() != Component::csDestroying ) {
					if( !GetUpdateRect( hwnd_, NULL, FALSE ) ){
						wndProcResult = 0;
						result = true;
						return result;
					}

					//check to see if the font needs updating
					checkForFontChange();

					PAINTSTRUCT ps;
					HDC contextID = 0;
					contextID = ::BeginPaint( hwnd_, &ps);

					doControlPaint( contextID, ps.rcPaint, NULL, cpControlOnly );
					updatePaintDC( contextID, ps.rcPaint, NULL );

					::EndPaint( hwnd_, &ps);
				}
			}

			wndProcResult = 1;
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
	long style = ::GetWindowLong( hwnd_, GWL_STYLE );
	long exStyle = ::GetWindowLong( hwnd_, GWL_EXSTYLE );
	bool needsParent = false;
	switch ( frameStyle ){
		case fstSizeable :{
			style |= WS_OVERLAPPEDWINDOW;
			exStyle &= ~WS_EX_TOOLWINDOW;
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

	::SetWindowLong( hwnd_, GWL_STYLE, style );
	::SetWindowLong( hwnd_, GWL_EXSTYLE, exStyle );

	//Rect* r = peerControl_->getBounds();
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( hwnd_ );

	//peerControl_->setBounds( r );
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

void Win32Window::setParent( VCF::Control* parent )
{
	DWORD oldStyle = ::GetWindowLong( hwnd_, GWL_STYLE );
	DWORD style = oldStyle;
	if ( NULL == parent ) {
		style &= ~WS_CHILD;
		style |= WS_POPUP;
		::SetParent( hwnd_, NULL );
	}
	else {
		Frame* frame = (Frame*)peerControl_;
		if ( frame->allowFrameAsChildControl() ) {
			style &= ~WS_POPUP;
			style |= WS_CHILD;
		}
		VCF::ControlPeer* peer = parent->getPeer();
		HWND wndParent = (HWND)peer->getHandleID();
		::SetParent( hwnd_, wndParent );
	}

	if ( oldStyle != style ) {
		::SetWindowLong( hwnd_, GWL_STYLE, style );
		::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
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
	//SetClassLong (hwnd_, GCL_HICON, (LONG)winIcon);
	
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

/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:59  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.5  2005/04/26 02:29:40  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.3.2.4  2005/04/20 02:26:01  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.3  2005/03/20 04:55:51  ddiego
*fixes bug [ 1161656 ] Window resize.
*
*Revision 1.3.2.2  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/10 21:14:00  ddiego
*fixed bug 1082362 App Icons do not appear.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/10/23 13:53:12  marcelloptr
*comments for setUseColorForBackground; setActiveFrame renamed as internal
*
*Revision 1.2.2.3  2004/09/15 17:48:54  ddiego
*fixed win32 registry and a bug in the handling of the WM_CLOSE message that was introduced by the change in event handler signature last weekend.
*
*Revision 1.2.2.2  2004/09/06 21:30:20  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.5  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.4  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.3  2004/07/01 20:53:43  ddiego
*minor fix in WS_XXX styles
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.48.2.2  2004/04/24 02:13:47  ddiego
*fixed incorrect calculation of anchor bounds in certain cases
*
*Revision 1.48.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.48  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.47  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.46.2.3  2004/03/21 00:41:47  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.46.2.2  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.46.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.46  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.45.2.8  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.45.2.7  2003/10/13 21:28:41  ddiego
*fiddles with the containers a bit - didn't fix anything :(
*
*Revision 1.45.2.6  2003/10/10 04:33:22  ddiego
*made the treelist look a bit better
*
*Revision 1.45.2.5  2003/10/10 02:38:12  ddiego
*fixed a big that was not updating the window icon correctly
*
*Revision 1.45.2.4  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.45.2.3  2003/08/26 03:16:50  ddiego
*added a syntax fix cause VC6 is too stupid to compile code correctly.
*Thanks to Marcello for pointing it out.
*
*Revision 1.45.2.2  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.45.2.1  2003/08/17 21:48:35  ddiego
*fixed bug [ 788189 ] ComboBoxControl doesn't close when application loose
*focus. Also cleaned some old trace statements for debugging purposes.
*
*Revision 1.45  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.44.2.7  2003/08/01 00:50:17  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.44.2.6  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.44.2.5  2003/06/13 03:05:32  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.44.2.4  2003/06/13 00:02:14  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.44.2.3  2003/06/09 03:57:15  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.44.2.2  2003/06/05 03:48:54  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.44.2.1  2003/05/27 04:45:39  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.44  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.43.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.43.2.1  2003/03/12 03:12:44  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.43  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.42.8.7  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.42.8.6  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.42.8.5  2002/12/30 00:24:13  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.42.8.4  2002/12/29 00:59:23  marcelloptr
*Minor fixes
*
*Revision 1.42.8.3  2002/12/28 21:51:19  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.42.8.2  2002/12/27 23:04:56  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.42.8.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.42  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.41.6.2  2002/09/10 04:07:49  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.41.6.1  2002/08/13 04:28:23  ddiego
*bugs fixed:
*[ 585085 ] Can't get at multi selected filenames - this was just a matter of exposing a function that was already available in the
*peer class
*
*features:
*58839 Add a method to query closing a Frame, this required a change that included added a new event (FrameEvent and the corresponding
*FrameEventHandler) and a method, bool Frame::allowClose()
*
*Also made fixes in the VCF Builder to now take advantage of this, so the MainWindow class will now register an event
*handler to handler the FrameClosing event, and attempt to set the current workspace to NULL. If this does not happen then
*the closing event will fail and prevent the widnow from being shutdown. Woo hoo !
*
*Revision 1.41  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.40  2002/03/31 21:39:23  ddiego
*minor stuff
*
*Revision 1.39  2002/03/21 04:01:01  ddiego
*fixed [ 532894 ] bug using the Frame::setClientBounds()
*
*Revision 1.38.4.2  2002/04/27 15:52:32  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.38.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.38  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


