//Win32DateTimePicker.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/DateTimePickerControl.h"
#include "vcf/ApplicationKit/Win32DateTimePicker.h"

using namespace VCF;

Win32DateTimePicker::Win32DateTimePicker()
{

}

void Win32DateTimePicker::create( Control* owningControl )
{
	peerControl_ = owningControl;
	CreateParams params = createParams();
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             DATETIMEPICK_CLASSW,
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
		                             DATETIMEPICK_CLASSA,
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
		Win32Object::registerWin32Object( this );

		subclassWindow();
		registerForFontChanges();			
	}
	else {
		//throw exception
	}

	setCreated( true );
}

Win32Object::CreateParams Win32DateTimePicker::createParams()
{
	Win32Object::CreateParams result;
	result.first = BORDERED_VIEW | DTS_SHOWNONE;
	result.first &= ~WS_BORDER;

	result.second = 0;

	return result;
}

bool Win32DateTimePicker::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc)
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case DTN_DATETIMECHANGE:{
            LPNMDATETIMECHANGE lpChange = (LPNMDATETIMECHANGE)lParam;
            
			DateTimePickerControl* dtp = (DateTimePickerControl*)peerControl_;

			DateTime dt;
			//if ( lpChange->dwFlags & GDT_VALID ) {
				dt.set( lpChange->st.wYear, 
					lpChange->st.wMonth, 
					lpChange->st.wDay, 
					lpChange->st.wHour, 
					lpChange->st.wMinute, 
					lpChange->st.wSecond, 
					lpChange->st.wMilliseconds );				
			//}

			VariantData v = dt;

			Model* model = dtp->getModel();
			if ( NULL != model ) {
				model->setValue( v, dtp->getModelKey() );
			}

			Event e(peerControl_);
			dtp->DateChanged( &e, dt );
        }


		case WM_PAINT:{

			PAINTSTRUCT ps;
			HDC dc = BeginPaint( hwnd_, &ps );

			RECT r;
			GetClientRect( hwnd_, &r );

			Rect paintRect(r.left, r.top,r.right, r.bottom );

			prepForDoubleBufferPaint( dc, paintRect );

			HDC memDC = (HDC) memCtx_->getPeer()->getContextID();

			::SetViewportOrgEx( memDC, -r.left, -r.top, NULL );

			Color* color = peerControl_->getColor();
			COLORREF backColor = color->getColorRef32();

			HBRUSH bkBrush = CreateSolidBrush( backColor );
			FillRect( memDC, &r, bkBrush );
			DeleteObject( bkBrush );



			::SetViewportOrgEx( memDC, -r.left, -r.top, NULL );

			//currentCtx_ = memCtx_;

			defaultWndProcedure( WM_PAINT, (WPARAM)memDC, 0 );

			::BitBlt( dc, r.left, r.top,
					  r.right - r.left,
					  r.bottom - r.top,
					  memDC, r.left, r.top, SRCCOPY );

			//currentCtx_ = NULL;

			EndPaint( hwnd_, &ps );

			wndProcResult = 1;
			result = true;

		}
	    break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result = true;
		}
		break;

		case WM_NCPAINT: {

			wndProcResult = handleNCPaint( wParam, lParam );
			return true;
		}
		break;

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}
	return result;
}

DateTime Win32DateTimePicker::getCurrentDateTime()
{
	DateTime result ;

	SYSTEMTIME t;

	if ( GDT_VALID == DateTime_GetSystemtime( hwnd_, &t ) ) {
		result.set( t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds );
	}

	return result;
}

void Win32DateTimePicker::setCurrentDateTime( const DateTime& dt )
{
	if ( dt.isNull() ) {
		DateTime_SetSystemtime( hwnd_, GDT_NONE, NULL );
		return;
	}

	SYSTEMTIME st;
	uint32 y, m, d, h, min, s, ms;
	dt.get( &y, &m, &d, &h, &min, &s, &ms );

	if ( ( y < 1601 ) || ( 30827 < y ) ) {
		throw BasicException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
	}

	st.wYear   = y;
	st.wMonth  = m;
	st.wDayOfWeek = dt.getWeekDay();
	st.wDay    = d;
	st.wHour   = h;
	st.wMinute = min;
	st.wSecond = s;
	st.wMilliseconds = ms;
	DateTime_SetSystemtime( hwnd_, GDT_VALID, &st );
}



void Win32DateTimePicker::setFormat( const String& format )
{
	if ( System::isUnicodeEnabled() ) {
		SendMessage( hwnd_, DTM_SETFORMATW, 0, (LPARAM)format.c_str() );
	}
	else {
		SendMessage( hwnd_, DTM_SETFORMATA, 0, (LPARAM)format.ansi_c_str() );
	}	
}

bool Win32DateTimePicker::allowsNullDates()
{
	bool result = false;
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	result = DTS_SHOWNONE & style ? true : false;
	return result;
}

void Win32DateTimePicker::setAllowsNullDates( const bool& val )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	if ( val ) {
		style |= DTS_SHOWNONE;
	}
	else {
		style &= ~DTS_SHOWNONE;
	}

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
	InvalidateRect( hwnd_, NULL, TRUE );
}

bool Win32DateTimePicker::upDownControlsVisible()
{
	bool result = false;
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	result = DTS_UPDOWN & style ? true : false;

	return result;
}

void Win32DateTimePicker::setUpDownControlsVisible( const bool& val )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	if ( val ) {
		style |= DTS_UPDOWN;
	}
	else {
		style &= ~DTS_UPDOWN;
	}

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
	InvalidateRect( hwnd_, NULL, TRUE );
}