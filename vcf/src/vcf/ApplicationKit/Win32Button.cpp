//Win32Button.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;


Win32Button::Win32Button( CommandButton* component ):
	AbstractWin32Component( component ),
	commandButton_(component)
{

}

Win32Button::~Win32Button()
{

}

void Win32Button::create( Control* owningControl )
{
	createParams();

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = getClassName();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( exStyleMask_,
		                             L"BUTTON",
									 windowCaption_.c_str(),
									 styleMask_,
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
		hwnd_ = ::CreateWindowExA( exStyleMask_,
		                             "BUTTON",
									 windowCaption_.ansi_c_str(),
									 styleMask_,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}



	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );
		subclassWindow();
	}
	else {
		//throw exception
	}

	setCreated( true );
}

void Win32Button::createParams()
{
	styleMask_ = WS_VISIBLE | WS_CHILD | BS_OWNERDRAW;
}

Image* Win32Button::getImage()
{
	return NULL;
}


void Win32Button::setImage( Image* image )
{

}

ulong32 Win32Button::getState()
{
	ulong32 result = 0;

	return result;
}

void Win32Button::setState( const ulong32& state )
{

}

void Win32Button::drawBasicButton( HDC hdc, DRAWITEMSTRUCT& drawStruct )
{

	COLORREF backColor = RGB( peerControl_->getColor()->getRed() * 255.0,
								peerControl_->getColor()->getGreen() * 255.0,
								peerControl_->getColor()->getBlue() * 255.0 );

	HBRUSH backBrush = CreateSolidBrush( backColor );
	HPEN hilightPen = CreatePen( PS_SOLID, 0, ::GetSysColor( COLOR_3DHIGHLIGHT ) );
	HPEN shadowPen = CreatePen( PS_SOLID, 0, ::GetSysColor( COLOR_3DSHADOW ) );
	HPEN blackPen = CreatePen( PS_SOLID, 0, 0 );

	HBRUSH oldBrush = (HBRUSH)::SelectObject( hdc, backBrush );
	::FillRect( hdc, &drawStruct.rcItem, backBrush );

	bool isPressed = (drawStruct.itemState & ODS_SELECTED) != 0;

	commandButton_->setIsPressed( isPressed );

	HPEN oldPen = NULL;

	RECT tmpRect = drawStruct.rcItem;
	InflateRect( &tmpRect, -1, -1 );

	RECT captionRect = drawStruct.rcItem;

	if ( true == isPressed ) {
		HBRUSH shadowBrush = CreateSolidBrush( ::GetSysColor( COLOR_3DSHADOW ) );
		::FrameRect( hdc, &tmpRect, shadowBrush );
		DeleteObject( shadowBrush );
		::OffsetRect( &captionRect, 1, 1 );
	}
	else {
		oldPen = (HPEN) ::SelectObject( hdc, hilightPen );

		::MoveToEx( hdc, tmpRect.right, tmpRect.top, NULL );
		::LineTo( hdc, tmpRect.left, tmpRect.top );
		::LineTo( hdc, tmpRect.left, tmpRect.bottom-1 );

		::SelectObject( hdc, shadowPen );
		::MoveToEx( hdc, tmpRect.right-2, tmpRect.top+1, NULL );
		::LineTo( hdc, tmpRect.right-2, tmpRect.bottom-2 );
		::LineTo( hdc, tmpRect.left, tmpRect.bottom-2 );

		::SelectObject( hdc, blackPen );
		::MoveToEx( hdc, tmpRect.right-1, tmpRect.top, NULL );
		::LineTo( hdc, tmpRect.right-1, tmpRect.bottom-1 );
		::LineTo( hdc, tmpRect.left-1, tmpRect.bottom-1 );
	}

	bool enabled = !(drawStruct.itemState & ODS_DISABLED);

	windowCaption_ = commandButton_->getCaption();


	HFONT font = NULL;
	HFONT oldFont = NULL;

	Rect centerRect( captionRect.left, captionRect.top, captionRect.right, captionRect.bottom );
	if ( System::isUnicodeEnabled() ) {
		LOGFONTW* lf = (LOGFONTW*) commandButton_->getFont()->getFontPeer()->getFontHandleID();
		font = ::CreateFontIndirectW( lf );
		oldFont = (HFONT) ::SelectObject( hdc, font );

		::DrawTextW( hdc, windowCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	}
	else {
		LOGFONTA* lf = (LOGFONTA*) commandButton_->getFont()->getFontPeer()->getFontHandleID();
		font = ::CreateFontIndirectA( lf );
		oldFont = (HFONT) ::SelectObject( hdc, font );

		::DrawTextA( hdc, windowCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	}


	::OffsetRect( &captionRect,
		(centerRect.getWidth() - (captionRect.right - captionRect.left))/2,
		(centerRect.getHeight() - (captionRect.bottom - captionRect.top))/2 );

	int oldBkMode = SetBkMode( hdc, TRANSPARENT );


	COLORREF textColor = 0;
	if ( true == enabled ) {
		textColor = RGB( peerControl_->getFont()->getColor()->getRed() * 255.0,
								peerControl_->getFont()->getColor()->getGreen() * 255.0,
								peerControl_->getFont()->getColor()->getBlue() * 255.0 );
	}
	else {
		textColor = ::GetSysColor( COLOR_GRAYTEXT );
	}



	COLORREF oldTextColor = SetTextColor( hdc, textColor );

	if ( false == enabled ) {
		SetTextColor( hdc, ::GetSysColor( COLOR_BTNHIGHLIGHT ) );

		OffsetRect( &captionRect, 1, 1 );

		if ( System::isUnicodeEnabled() ) {
			::DrawTextW( hdc, windowCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
		}
		else {
			::DrawTextA( hdc, windowCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
		}

		OffsetRect( &captionRect, -1, -1 );

		SetTextColor( hdc, textColor );
	}

	if ( System::isUnicodeEnabled() ) {
		::DrawTextW( hdc, windowCaption_.c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
	}
	else {
		::DrawTextA( hdc, windowCaption_.ansi_c_str(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
	}



	SetTextColor( hdc, oldTextColor );
	SetBkMode( hdc, oldBkMode );

	::SelectObject( hdc, oldFont );
	::DeleteObject( font );



	if ( (drawStruct.itemState & ODS_FOCUS) || peerControl_->isFocused() ) {
		RECT focusRect = drawStruct.rcItem;
		InflateRect( &focusRect, -4, -4 );
		::DrawFocusRect( hdc, &focusRect );
	}

	if ( NULL != oldBrush ) {
		::SelectObject( hdc, oldBrush );
	}
	if ( NULL != oldPen ) {
		::SelectObject( hdc, oldPen );
	}

	::DeleteObject( hilightPen );
	::DeleteObject( shadowPen );
	::DeleteObject( blackPen );
	::DeleteObject( backBrush );

}

LRESULT Win32Button::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc )
{
	LRESULT result = 0;

	switch ( message ) {
		case WM_PAINT:{
			//result = CallWindowProc( oldButtonWndProc_, hwnd_, message, wParam, lParam );
			
		}
		break;

		case WM_ERASEBKGND:{
			return TRUE;
		}
		break;

		case WM_DRAWITEM:{
			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;
			if ( true == peerControl_->isDoubleBuffered() ){

				if ( NULL == memDC_ ) {
						//create here
					HDC dc = ::GetDC(0);
					memDC_ = ::CreateCompatibleDC( dc );
					::ReleaseDC( 0,	dc );
				}

				VCF::GraphicsContext* ctx = peerControl_->getContext();

				int dcState = ::SaveDC( drawItem->hDC );
				Rect tmp(drawItem->rcItem.left, drawItem->rcItem.top, drawItem->rcItem.right, drawItem->rcItem.bottom);

				HBITMAP memBitmap =
					::CreateCompatibleBitmap( drawItem->hDC,
												drawItem->rcItem.right - drawItem->rcItem.left,
												drawItem->rcItem.bottom - drawItem->rcItem.top );

				HBITMAP oldBMP = (HBITMAP)::SelectObject( memDC_, memBitmap );

				::SetViewportOrgEx( memDC_, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				//VCF::GraphicsContext memCtx( tmp.getWidth(), tmp.getHeight() );

				//memCtx.setOrigin( -tmp.left_, -tmp.top_ );

				//HDC memDC = (HDC)memCtx.getPeer()->getContextID();

				drawBasicButton( memDC_, *drawItem );

				ctx->getPeer()->setContextID( (long)memDC_ );

				((ControlGraphicsContext*)ctx)->setOwningControl( NULL );

				peerControl_->paint( ctx );

				((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );

				::SetViewportOrgEx( memDC_, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				int err = ::BitBlt( drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top,
									drawItem->rcItem.right - drawItem->rcItem.left,
									drawItem->rcItem.bottom - drawItem->rcItem.top,
									memDC_, drawItem->rcItem.left, drawItem->rcItem.top, SRCCOPY );

				::SelectObject( memDC_, oldBMP );

				::DeleteObject( memBitmap );

				::RestoreDC ( memDC_, dcState );

				if ( err == FALSE ) {
					err = GetLastError();
					StringUtils::traceWithArgs( "error in BitBlt during drawing of double buffered Comp: error code=%d\n",
						err );
				}
			}
			else {
				VCF::GraphicsContext* ctx = peerControl_->getContext();

				ctx->getPeer()->setContextID( (long)drawItem->hDC );

				drawBasicButton( drawItem->hDC, *drawItem );

				peerControl_->paint( ctx );
			}
			result = TRUE;
		}
		break;

		case BN_CLICKED :{

			commandButton_->click();
/*
			HWND wnd = (HWND)peerControl_->getParent()->getPeer()->getHandleID();
			WPARAM msgWParam = 0;
			switch ( commandButton_->getCommandType() ){
				case BC_NONE : {

				}
				break;

				case BC_OK : {
					msgWParam = MAKEWPARAM(0,IDOK);
				}
				break;

				case BC_CANCEL : {
					msgWParam = MAKEWPARAM(0,IDCANCEL);
				}
				break;

				case BC_YES : {
					msgWParam = MAKEWPARAM(0,IDYES);
				}
				break;

				case BC_NO : {
					msgWParam = MAKEWPARAM(0,IDNO);
				}
				break;

				case BC_MAYBE : {

				}
				break;
			}
			PostMessage( wnd, WM_COMMAND, msgWParam, NULL );
			*/
		}
		break;

		case WM_COMMAND: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );			
		}

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );

		}
	}
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.24.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.24  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.23.4.1  2004/03/23 05:04:28  ddiego
*minor nigglies
*
*Revision 1.23  2003/08/09 02:56:46  ddiego
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
*Revision 1.22.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.22.2.1  2003/05/27 04:45:33  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.22  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.21.2.1  2003/03/12 03:12:19  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.21  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.20.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.20  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.19.4.2  2002/04/27 15:52:24  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.19.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.19  2002/01/30 22:12:47  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.18  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.17  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


