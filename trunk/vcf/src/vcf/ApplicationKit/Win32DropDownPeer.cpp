//Win32DropDownPeer.cpp



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/Win32DropDownPeer.h"
#include "vcf/ApplicationKit/ListModel.h"



using namespace VCFWin32;
using namespace VCF;


Win32DropDownPeer::Win32DropDownPeer()
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

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
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
		hwnd_ = ::CreateWindowExA( params.second,
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

	if ( NULL != hwnd_ ){
		peerControl_ = owningControl;

		Win32Object::registerWin32Object( this );

		subclassWindow();
		registerForFontChanges();

		CallBack* cb = 
			new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onCtrlModelChanged, "Win32DropDownPeer::onCtrlModelChanged" );

		owningControl->ControlModelChanged += cb;

		cb = 
			new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onListModelChanged, "Win32DropDownPeer::onListModelChanged" );

		setCreated( true );
	}
}

Win32Object::CreateParams Win32DropDownPeer::createParams()
{
	Win32Object::CreateParams result;
	result.first = BORDERED_VIEW | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS;
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

		case WM_PAINT:{
			//result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_DRAWITEM:{
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
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
	LONG style = GetWindowLong( hwnd_, GWL_STYLE );
	if ( val ) {
		style &= ~CBS_DROPDOWNLIST;
		style |= CBS_DROPDOWN;
	}
	else {
		style &= ~CBS_DROPDOWN;
		style |= CBS_DROPDOWNLIST;
	}

	::SetWindowLong( hwnd_, GWL_STYLE, style );

	SetWindowPos(hwnd_, NULL,0,0,0,0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE);
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

