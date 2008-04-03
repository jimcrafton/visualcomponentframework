//Win32DropDownPeer.cpp



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/Win32DropDownPeer.h"
#include "vcf/ApplicationKit/ListModel.h"



using namespace VCFWin32;
using namespace VCF;

typedef struct tagCOMBOBOXINFO {
	DWORD cbSize;
	RECT rcItem;
	RECT rcButton;
	DWORD stateButton;
	HWND hwndCombo;
	HWND hwndItem;
	HWND hwndList;
} COMBOBOXINFO, *PCOMBOBOXINFO, *LPCOMBOBOXINFO;

typedef BOOL  (WINAPI *GetComboBoxInfoPtr) ( HWND, PCOMBOBOXINFO );

static GetComboBoxInfoPtr GetComboBoxInfoFunc = NULL;

Win32DropDownPeer::Win32DropDownPeer():
	listBoxHwnd_(NULL),
		oldLBWndProc_(NULL),
		editEnabled_(false)
{

}

Win32DropDownPeer::~Win32DropDownPeer()
{

}

void Win32DropDownPeer::create( Control* owningControl )
{
	CreateParams params = createParams();
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	editEnabled_ = (params.first & CBS_DROPDOWN) ? true : false;

	HWND wnd = NULL;
	if ( System::isUnicodeEnabled() ) {
		wnd = ::CreateWindowExW( params.second,
		                             L"COMBOBOX",
									 NULL,
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		wnd = ::CreateWindowExA( params.second,
		                             "COMBOBOX",
									 NULL,
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}

	CallBack* cb = 
		new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onCtrlModelChanged, "Win32DropDownPeer::onCtrlModelChanged" );

	owningControl->ControlModelChanged += cb;

	cb = 
		new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onListModelChanged, "Win32DropDownPeer::onListModelChanged" );

	if ( NULL == GetComboBoxInfoFunc ) {
		HINSTANCE user32 = LoadLibrary( "user32.dll" );
		GetComboBoxInfoFunc = (GetComboBoxInfoPtr)::GetProcAddress( user32, "GetComboBoxInfo" );
		FreeLibrary(user32);
		
		if ( NULL == GetComboBoxInfoFunc ) {
			StringUtils::trace( "WARNING! GetComboBoxInfo() was not found in User32.dll. Maybe this is an old version of Windows?\n" );
		}
	}

	attachToHwnd( wnd, owningControl );
}

void Win32DropDownPeer::attachToHwnd( HWND wnd, Control* owner )
{
	if ( NULL != wnd ){
		hwnd_ = wnd;

		bool firstTime = false;

		if ( NULL == peerControl_ ) {
			peerControl_ = owner;
			firstTime = true;
			Win32Object::registerWin32Object( this );
		}
		else {
			Win32Object::registerWin32ObjectQuietly( this );
		}

		subclassWindow();

		if ( firstTime ) {
			registerForFontChanges();
		}
		else {
			setFont( peerControl_->getFont() );
		}

		setCreated( true );
		if ( !firstTime ) {
			canProcessMessages_ = true;
			delete cachedMessages_;
		}

		
		if ( NULL != GetComboBoxInfoFunc ) {
			COMBOBOXINFO info = {0};
			info.cbSize = sizeof(info);
			GetComboBoxInfoFunc( hwnd_, &info );
			listBoxHwnd_ = info.hwndList;


			if ( System::isUnicodeEnabled() ) {
				::SetWindowLongPtr( listBoxHwnd_, GWLP_USERDATA, (LONG_PTR)this );
				oldLBWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtr( listBoxHwnd_, GWLP_WNDPROC, (LONG_PTR)Win32DropDownPeer::LB_WndProc );			
			}
			else {
				::SetWindowLongPtrA( listBoxHwnd_, GWLP_USERDATA, (LONG_PTR)this );
				oldLBWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtrA( listBoxHwnd_, GWLP_WNDPROC, (LONG_PTR)Win32DropDownPeer::LB_WndProc );			
			}			
		}
	}
}

void Win32DropDownPeer::detachFromHwnd( HWND wnd )
{
	Win32Object::unRegisterWin32Object( this );

	if ( System::isUnicodeEnabled() ) {
		::SetWindowLongPtrW( wnd, GWLP_WNDPROC, (LONG_PTR)defaultWndProc_ );	
	}
	else {
		::SetWindowLongPtrA( wnd, GWLP_WNDPROC, (LONG_PTR)defaultWndProc_ );	
	}

	if ( NULL != listBoxHwnd_ ) {	
		if ( System::isUnicodeEnabled() ) {
			::SetWindowLongPtrW( listBoxHwnd_, GWLP_WNDPROC, (LONG_PTR)oldLBWndProc_ );	
		}
		else {
			::SetWindowLongPtrA( listBoxHwnd_, GWLP_WNDPROC, (LONG_PTR)oldLBWndProc_ );	
		}
	}

	listBoxHwnd_ = NULL;
	hwnd_ = NULL;	
	setCreated( false );	
	canProcessMessages_ = false;
}

LRESULT CALLBACK Win32DropDownPeer::LB_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	Win32DropDownPeer* dropDownPeer = (Win32DropDownPeer*)(LONG_PTR) ::GetWindowLongPtr( hWnd, GWLP_USERDATA );

	switch ( message ) {	

		case LB_GETTEXT : {

			result = ::SendMessage( dropDownPeer->hwnd_, CB_GETLBTEXT, wParam, lParam );
		}
		break;

		case LB_GETTEXTLEN : {

			result = ::SendMessage( dropDownPeer->hwnd_, CB_GETLBTEXTLEN, wParam, lParam );
		}
		break;

		default : {
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( dropDownPeer->oldLBWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( dropDownPeer->oldLBWndProc_, hWnd, message, wParam, lParam );
			}
		}
		break;
	}


	return result;
}

Win32Object::CreateParams Win32DropDownPeer::createParams()
{
	Win32Object::CreateParams result;
	result.first = BORDERED_VIEW | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE  | CBS_HASSTRINGS | WS_VSCROLL;
	//result.first &= ~WS_BORDER;	

	result.second = 0;

	return result;
}

bool Win32DropDownPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc)
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case WM_ERASEBKGND:{
			wndProcResult = TRUE;
			result = true;
		}
		break;

		case WM_GETTEXT:{
			wndProcResult = 0;
			result = true;

			ListModel* lm = (ListModel*) peerControl_->getViewModel();
			UINT res = ::SendMessage( hwnd_, CB_GETCURSEL, 0, 0 );
			if ( res != CB_ERR ) {
				size_t index = res;
				String s = lm->getAsString( index );
				size_t len = wParam;
				if ( System::isUnicodeEnabled() ) {
					WCHAR* str = (WCHAR*)lParam;
					wndProcResult = s.copy( str, minVal<>(len,s.length()) );
					
				}
				else {
					char* str = (char*)lParam;					
					AnsiString tmp = s;
					wndProcResult = tmp.copy( str, minVal<>(len,tmp.length()) );
				}
			}
		}
		break;

		
		case WM_GETTEXTLENGTH :{
			wndProcResult = 0;
			result = true;

			ListModel* lm = (ListModel*) peerControl_->getViewModel();
			UINT res = ::SendMessage( hwnd_, CB_GETCURSEL, 0, 0 );
			if ( res != CB_ERR ) {
				size_t index = res;
				String s = lm->getAsString( index );
				if ( System::isUnicodeEnabled() ) {
					wndProcResult = s.length();
				}
				else {
					AnsiString tmp = s;
					wndProcResult = tmp.length();
				}
			}
		}
		break;

		case CB_GETLBTEXTLEN :{
			wndProcResult = TRUE;
			result = true;

			ListModel* lm = (ListModel*) peerControl_->getViewModel();
			size_t index = wParam;
			String s = lm->getAsString( index );
			if ( System::isUnicodeEnabled() ) {
				wndProcResult = s.length();
			}
			else {
				AnsiString tmp = s;
				wndProcResult = tmp.length();
			}
		}
		break;		

		case CB_GETLBTEXT :{
			wndProcResult = 0;
			result = true;

			ListModel* lm = (ListModel*) peerControl_->getViewModel();
			size_t index = wParam;
			String s = lm->getAsString( index );
			size_t len = 0;
			if ( System::isUnicodeEnabled() ) {
				WCHAR* str = (WCHAR*)lParam;
				len = wcslen( str );
				wndProcResult = s.copy( str, minVal<>(len,s.length()) );

			}
			else {
				char* str = (char*)lParam;
				len = strlen( str );
				AnsiString tmp = s;
				wndProcResult = tmp.copy( str, minVal<>(len,tmp.length()) );
			}
		}
		break;

		

		case WM_PAINT:{
			//AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			wndProcResult = 0;
		}
		break;

		case WM_DRAWITEM:{
			//result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			DRAWITEMSTRUCT* drawItemStruct = (DRAWITEMSTRUCT*) lParam;

			Win32Font* fontPeer = (Win32Font*) peerControl_->getFont()->getFontPeer();
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );

			ListModel* lm = (ListModel*) peerControl_->getViewModel();
			size_t count = lm->getCount();
			if ( drawItemStruct->itemID >= 0 && drawItemStruct->itemID < count ) {

				String s = lm->getAsString( drawItemStruct->itemID );

				GraphicsContext gc( drawItemStruct->hDC );
				Rect r;
				r.left_ = drawItemStruct->rcItem.left;
				r.top_ = drawItemStruct->rcItem.top;
				r.right_ = drawItemStruct->rcItem.right;
				r.bottom_ = drawItemStruct->rcItem.bottom;

				Color* color = peerControl_->getColor();
				Color* defaultBackClr = color;
				
				if ( drawItemStruct->itemState & ODS_SELECTED ) {
					defaultBackClr = GraphicsToolkit::getSystemColor( SYSCOLOR_SELECTION );
				}

				gc.setColor( defaultBackClr );
				gc.rectangle( &r );
				gc.fillPath();


				gc.textBoundedBy( &r, s );

			}			
			
		}
		break;

		case WM_MEASUREITEM:{
			MEASUREITEMSTRUCT* measureItem = (MEASUREITEMSTRUCT*)lParam;
			Win32Font* fontPeer = (Win32Font*) peerControl_->getFont()->getFontPeer();
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );

			HDC dc = GetDC( GetDesktopWindow() );

			HFONT oldf = (HFONT)SelectObject( dc, fontHandle );

			TEXTMETRIC tm = {0};
			GetTextMetrics(dc, &tm);
			measureItem->itemHeight = tm.tmHeight + tm.tmExternalLeading + 1;

			SelectObject( dc, oldf );

			ReleaseDC( GetDesktopWindow(), dc );
			result = true;
		}
		break;

		default : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}



	return result;
}

void Win32DropDownPeer::enableEditBox( bool val )
{
	if ( val == editEnabled_ ) {
		return;
	}


	bool visible = this->getVisible();

	UINT style = BORDERED_VIEW | CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_OWNERDRAWVARIABLE  | CBS_HASSTRINGS;

	if ( val ) {
		style &= ~CBS_DROPDOWNLIST;
		style |= CBS_DROPDOWN;
	}
	else {
		style &= ~CBS_DROPDOWN;
		style |= CBS_DROPDOWNLIST;
	}

	if ( visible ) {
		style |= WS_VISIBLE;
	}
	

	HWND parent = GetParent(hwnd_);
	LONG styleEx = GetWindowLong( hwnd_, GWL_EXSTYLE );
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND dummy = toolkit->getDummyParent();


	RECT r = {0};
	GetWindowRect( hwnd_, &r );
	
	POINT pt;
	pt.x = r.left;
	pt.y = r.top;

	ScreenToClient( parent, &pt );
	r.left = pt.x;
	r.top = pt.y;

	pt.x = r.right;
	pt.y = r.bottom;

	ScreenToClient( parent, &pt );
	r.right = pt.x;
	r.bottom = pt.y;

	HWND wnd = hwnd_;
	detachFromHwnd( wnd );

	DestroyWindow( wnd );

	wnd = NULL;
	if ( System::isUnicodeEnabled() ) {
		wnd = ::CreateWindowExW( styleEx,
		                             L"COMBOBOX",
									 NULL,
									 style,
		                             r.left,
									 r.top,
									 r.right - r.left,
									 (r.bottom - r.top) * 5,
									 dummy,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		wnd = ::CreateWindowExA( styleEx,
		                             "COMBOBOX",
									 NULL,
									 style,
		                             r.left,
									 r.top,
									 r.right - r.left,
									 r.bottom - r.top,
									 dummy,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}

	attachToHwnd( wnd );

	::SetParent( hwnd_, parent );

	
	ListModel* lm = (ListModel*)peerControl_->getViewModel();

	size_t modelCount = lm->getCount();	
	UINT count = 0;
	if ( modelCount > count ) {
		while ( count < modelCount ) {
			::SendMessage( hwnd_, CB_ADDSTRING, 0, (LPARAM)"null" );
			count ++;
		}		
	}
	editEnabled_ = val;
}

bool Win32DropDownPeer::editBoxEnabled()
{
	LONG style = GetWindowLong( hwnd_, GWL_STYLE );
	return (style & CBS_DROPDOWN) ? true : false;
}

void Win32DropDownPeer::setEditText( const String& text )
{
	
}

String Win32DropDownPeer::getEditText()
{
	return getText();
}

void Win32DropDownPeer::setDropDownWidth( double val )
{
	//
	::SendMessage( hwnd_, CB_SETDROPPEDWIDTH, (WPARAM)(int)val, 0 );
}

double Win32DropDownPeer::getDropDownWidth()
{
	double result = 0.0;
	result = ::SendMessage( hwnd_, CB_GETDROPPEDWIDTH, 0, 0 );
	return result;
}

void Win32DropDownPeer::setDropDownCount( const uint32& dropDownCount )
{
	RECT r = {0};
	GetWindowRect( hwnd_, &r );
	r.bottom = r.top + ((r.bottom-r.top) * dropDownCount);
	POINT pt;
	pt.x = r.left;
	pt.y = r.top;

	ScreenToClient( GetParent(hwnd_), &pt );
	r.left = pt.x;
	r.top = pt.y;

	pt.x = r.right;
	pt.y = r.bottom;

	ScreenToClient( GetParent(hwnd_), &pt );
	r.right = pt.x;
	r.bottom = pt.y;

	SetWindowPos( hwnd_, NULL, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER );
}

void Win32DropDownPeer::onCtrlModelChanged( Event* e )
{
 	Model* model = peerControl_->getViewModel();
	model->ModelChanged += getCallback( "Win32DropDownPeer::onListModelChanged" );	
	
	ListModel* lm = (ListModel*)model;

	size_t modelCount = lm->getCount();

	::SendMessage( hwnd_, CB_RESETCONTENT, 0, 0 );
	UINT count = 0;
	if ( modelCount > count ) {
		while ( count < modelCount ) {
			::SendMessage( hwnd_, CB_ADDSTRING, 0, (LPARAM)"null" );
			count ++;
		}		
	}
	InvalidateRect( hwnd_, NULL, TRUE );
}

void Win32DropDownPeer::onListModelChanged( Event* e )
{
	ListModel* lm = (ListModel*)e->getSource();

	size_t modelCount = lm->getCount();

	UINT count = ::SendMessage( hwnd_, CB_GETCOUNT, 0, 0 );

	if ( modelCount > count ) {
		while ( count < modelCount ) {
			::SendMessage( hwnd_, CB_ADDSTRING, 0, (LPARAM)"null" );
			count ++;
		}
		InvalidateRect( hwnd_, NULL, TRUE );
	}
	else if ( modelCount < count ){
		if ( modelCount == 0 ) {
			::SendMessage( hwnd_, CB_RESETCONTENT, 0, 0 );
		}
		else {
			while ( count > modelCount ) {
				::SendMessage( hwnd_, CB_DELETESTRING, count-1, 0 );
				count --;
			}
		}
		InvalidateRect( hwnd_, NULL, TRUE );
	}	
}

void Win32DropDownPeer::selectItem( const uint32& index )
{
	::SendMessage( hwnd_, CB_SETCURSEL, index, 0 );	
}

uint32 Win32DropDownPeer::getSelectedItem()
{
	uint32 result = ListModel::InvalidIndex;

	UINT idx = ::SendMessage( hwnd_, CB_GETCURSEL, 0, 0 );
	if ( idx != CB_ERR ) {
		result = idx;
	}
	
	return result;
}

uint32 Win32DropDownPeer::getFocusedItem()
{
	return getSelectedItem();
}

bool Win32DropDownPeer::isItemSelected( const uint32& index )
{
	UINT idx = ::SendMessage( hwnd_, CB_GETCURSEL, 0, 0 );
	if ( idx != CB_ERR ) {
		return index == idx;
	}

	return false;
}

Rect Win32DropDownPeer::getItemRect( const uint32& index )
{
	Rect result ;

	return result;
}

Rect Win32DropDownPeer::getItemImageRect( const uint32& index )
{
	Rect result ;

	return result;
}

uint32 Win32DropDownPeer::hitTest( const Point& point )
{
	return ListModel::InvalidIndex;
}

Enumerator<uint32>* Win32DropDownPeer::getSelectedItems()
{
	return NULL;
}

void Win32DropDownPeer::rangeSelect( const Rect& selectionRect )
{

}

bool Win32DropDownPeer::allowsMultiSelect()
{
	return false;
}

void Win32DropDownPeer::setAllowsMultiSelect( const bool& allowsMultiSelect )
{

}

void Win32DropDownPeer::setLargeImageList( ImageList* imageList )
{

}

void Win32DropDownPeer::setSmallImageList( ImageList* imageList )
{

}

