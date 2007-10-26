//Win32Edit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Edit.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/FoundationKit/Dictionary.h"

#if defined(VCF_MINGW)  /* mingw misses some richedit defines */
#include "imm.h"

#define RICHEDIT_CLASSA		"RichEdit20A"
#define RICHEDIT_CLASSW		L"RichEdit20W"

#endif

#include <richedit.h>
#include "thirdparty/win32/Microsoft/TOM.h"
#include "thirdparty/win32/Microsoft/textserv.h"
#include <Richole.h>


#if defined(VCF_MINGW)  /* mingw w32api-3.8 richole.h misses this GUID */

#define DEFINE_GUIDXXX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID CDECL name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

/* Values taken from uuid.c in mingw w32api-3.6  */
DEFINE_GUIDXXX(IID_IRichEditOle,0x20d00,0,0,0xc0,0,0,0,0,0,0,0x46);
DEFINE_GUIDXXX(IID_IRichEditOleCallback,0x20d03,0,0,0xc0,0,0,0,0,0,0,0x46);


#endif

using namespace VCFWin32;
using namespace VCF;


namespace VCF {

class Win32RichEditOleCallback : public  IRichEditOleCallback {
public:
	STDMETHODIMP QueryInterface( REFIID iid, void ** ppvObject ) {
		String uuidStr;
		
		if ( iid == IID_IRichEditOleCallback ) {
			*ppvObject = (void*) (IRichEditOleCallback*)this;
		}
		else if ( iid == IID_IUnknown ) {
			*ppvObject = (void*) (IUnknown*)this;
		}
		else {
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}

		return S_OK;
	}

	STDMETHODIMP_(ULONG) AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG) Release() {
		return 0;
	}

	// *** IRichEditOleCallback methods ***
	STDMETHODIMP GetNewStorage ( LPSTORAGE FAR * lplpstg) {
		return E_NOTIMPL;
	}

    STDMETHODIMP GetInPlaceContext(LPOLEINPLACEFRAME FAR * lplpFrame,
								  LPOLEINPLACEUIWINDOW FAR * lplpDoc,
								  LPOLEINPLACEFRAMEINFO lpFrameInfo) {
		return E_NOTIMPL;
	}

	STDMETHODIMP ShowContainerUI(BOOL fShow) {
		return E_NOTIMPL;
	}

	STDMETHODIMP QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg,
		LONG cp) {
		return E_NOTIMPL;
	}

	STDMETHODIMP DeleteObject( LPOLEOBJECT lpoleobj) {
		return E_NOTIMPL;
	}

	STDMETHODIMP QueryAcceptData (LPDATAOBJECT lpdataobj,
								CLIPFORMAT FAR * lpcfFormat, DWORD reco,
								BOOL fReally, HGLOBAL hMetaPict) {

		if ( !fReally ) {
			
		}
		return S_FALSE;
	}

	STDMETHODIMP ContextSensitiveHelp ( BOOL fEnterMode) {
		return E_NOTIMPL;
	}

	STDMETHODIMP GetClipboardData ( CHARRANGE FAR * lpchrg, DWORD reco,
		LPDATAOBJECT FAR * lplpdataobj) {
		return E_NOTIMPL;
	}

	STDMETHODIMP GetDragDropEffect ( BOOL fDrag, DWORD grfKeyState,
		LPDWORD pdwEffect) {
		if ( fDrag ) {
			*pdwEffect = 0;
		}
		return S_OK;
	}

	STDMETHODIMP GetContextMenu ( WORD seltype, LPOLEOBJECT lpoleobj,
									CHARRANGE FAR * lpchrg,
									HMENU FAR * lphmenu) {
		return E_NOTIMPL;
	}
};

}; // namespace VCF


static bool Win32RicheditLibraryLoaded = false;

Win32Edit::Win32Edit( TextControl* component, const bool& isMultiLineControl ):
	AbstractWin32Component( component ),
	Win32TextPeer(),
	textControl_(component),
	backgroundBrush_(NULL),
	editState_(0),
	currentSelLength_(0),
	currentSelStart_(-1),
	richEditCallback_(NULL)
{
	if ( isMultiLineControl ) {
		editState_ |= esMultiLined; 
	}
}

Win32Edit::~Win32Edit()
{
	if ( NULL != backgroundBrush_ ) {
		DeleteObject( backgroundBrush_ );
	}
	if ( NULL != richEditCallback_ ) {
		SendMessage( hwnd_, EM_SETOLECALLBACK, 0, (LPARAM)0 );
		delete richEditCallback_;		
	}
}

void Win32Edit::create( Control* owningControl )
{
	if ( NULL == textControl_ ){
		//throw exception !!!!!!
	}

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className;

	AnsiString richeditLibrary = "RICHED20.Dll";

	if ( !Win32RicheditLibraryLoaded ) {
		if  ( NULL != LoadLibraryA( richeditLibrary.c_str() ) ) {
			Win32RicheditLibraryLoaded = true;
		}
		else {
			String errMsg =
				StringUtils::format( Format("Failed to load \"%s\", a required DLL when using richedit controls. \n"\
				"Please make sure this DLL is located in your Windows system, or application directory.") %
				richeditLibrary.c_str() );

			throw RuntimeException( errMsg );
		}
	}

	if ( System::isUnicodeEnabled() ) {
		className = RICHEDIT_CLASSW;
	}
	else {
		className = RICHEDIT_CLASSA;
	}

	CreateParams params = createParams();



	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
									 className.c_str(),
									 NULL,
									 params.first,
									 0,
									 0,
									 1,
									 1,
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

		registerForFontChanges();

		//make sure that we get ALL richedit change notfications!
		::SendMessage( hwnd_, EM_SETEVENTMASK, 0, ENM_CHANGE | ENM_SELCHANGE );
		

		textControl_->ControlModelChanged +=
			new ClassProcedure1<Event*,Win32Edit>( this, &Win32Edit::onControlModelChanged, "Win32Edit::onControlModelChanged" );

		initFromRichEdit( hwnd_ );

	}
	else {
		//throw exception
		throw RuntimeException( "Runtime Exception: " + Win32Utils::getErrorString( ::GetLastError() ) );
	}

	setCreated( true );
}

Win32Object::CreateParams Win32Edit::createParams()
{
	Win32Object::CreateParams result;


	result.first = WS_CHILD;// SIMPLE_VIEW;
	result.first &= ~WS_BORDER;


	result.first &= ~WS_VISIBLE;
	// this is a temporary solution: it would be better to implement
	// a method giving the option to the user, and painting the selection
	// in an unfocused control with a light gray on the background - MP.

	result.first |= ES_AUTOHSCROLL | ES_SAVESEL /*| ES_NOHIDESEL*/;
	if ( editState_ & esMultiLined ) {
		result.first |= ES_SAVESEL | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL;// | ES_WANTRETURN;
	}

	return result;
}

OSHandleID Win32Edit::getTextObjectHandle()
{
	return Win32TextPeer::getTextObjectHandle();
}

void Win32Edit::setRightMargin( const double & rightMargin )
{
	editState_ |= esStyleChanging;

	::SendMessage( hwnd_, EM_SETMARGINS, EC_RIGHTMARGIN, (LPARAM)rightMargin );

	editState_ &= ~esStyleChanging;
}

void Win32Edit::setLeftMargin( const double & leftMargin )
{
	editState_ |= esStyleChanging;

	::SendMessage( hwnd_, EM_SETMARGINS, EC_LEFTMARGIN, (LPARAM)leftMargin );

	editState_ &= ~esStyleChanging;
}

uint32 Win32Edit::getLineCount()
{
	return ::SendMessage( hwnd_, EM_GETLINECOUNT, 0, 0 );
}

Rect Win32Edit::getContentBoundsForWidth(const double& width)
{
	return Win32TextPeer::getContentBoundsForWidth(width);
}

uint32 Win32Edit::getCurrentLinePosition()
{
	DWORD pos = getSelectionStart();

	uint32 result = ::SendMessage( hwnd_, EM_LINEFROMCHAR, pos, 0 );


	return result;
}

double Win32Edit::getLeftMargin()
{
	double result = 0.0;

	DWORD margin = ::SendMessage( hwnd_, EM_GETMARGINS, 0, 0 );
	result = LOWORD(margin);
	return result;
}

double Win32Edit::getRightMargin()
{
	double result = 0.0;

	DWORD margin = ::SendMessage( hwnd_, EM_GETMARGINS, 0, 0 );
	result = HIWORD(margin);
	return result;
}


void Win32Edit::insertText( unsigned int start, const String& text )
{
	editState_ |= esPeerTextChanging;

	Win32TextPeer::insertText( start, text );

	editState_ &= ~esPeerTextChanging;
}

void Win32Edit::deleteText( unsigned int start, unsigned int length )
{
	editState_ |= esPeerTextChanging;

	Win32TextPeer::deleteText( start, length );

	editState_ &= ~esPeerTextChanging;
}

unsigned int Win32Edit::getTextLength()
{
	return Win32TextPeer::getTextLength();
}

String Win32Edit::getText( unsigned int start, unsigned int length )
{
	return Win32TextPeer::getText(start,length);
}

String Win32Edit::getText()
{	
	String result;
	ITextRange* range;
	textDocument_->Range( 0, 0, &range );
	if ( NULL != range ) {
		long len = 0;
		range->GetStoryLength( &len );
		range->SetEnd ( len );

		BSTR str = SysAllocString( NULL );
		range->GetText( &str );

		/**
		don't copy the very last character as this will be a 
		0x0D, from MSDN:
		"Another important feature is that all stories contain 
		an undeletable final CR (0xD) character at the end. So 
		even an empty story has a single character, namely the 
		final CR."
		*/

		result.assign( str, SysStringLen(str)-1 );

		SysFreeString( str );

		range->Release();
	}
	return result;
}



void Win32Edit::paint( GraphicsContext* context, const Rect& paintRect )
{
	Win32TextPeer::paint( context, paintRect );
}


void Win32Edit::setTopMargin( const double & topMargin )
{
	editState_ |= esStyleChanging;

	Win32TextPeer::setTopMargin( topMargin );

	editState_ &= ~esStyleChanging;
}

void Win32Edit::setBottomMargin( const double & bottomMargin )
{
	editState_ |= esStyleChanging;

	Win32TextPeer::setBottomMargin( bottomMargin );

	editState_ &= ~esStyleChanging;
}


double Win32Edit::getTopMargin()
{
	return Win32TextPeer::getTopMargin();
}

double Win32Edit::getBottomMargin()
{
	return Win32TextPeer::getBottomMargin();
}

void Win32Edit::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	editState_ |= esStyleChanging;

	Win32TextPeer::setStyle( start, length, styles );

	editState_ &= ~esStyleChanging;
}

void Win32Edit::getStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	Win32TextPeer::getStyle( start, length, styles );
}


void Win32Edit::setDefaultStyle( Dictionary& styles )
{
	editState_ |= esStyleChanging;

	Win32TextPeer::setDefaultStyle( styles );

	editState_ &= ~esStyleChanging;
}



VCF::Point* Win32Edit::getPositionFromCharIndex( const uint32& index )
{
	DWORD pos = ::SendMessage( hwnd_, EM_POSFROMCHAR, index, 0 );
	posAtChar_.x_ = LOWORD(pos);
	posAtChar_.y_ = HIWORD(pos);
	return &posAtChar_;
}

uint32 Win32Edit::getCharIndexFromPosition( VCF::Point* point )
{
	DWORD pos = 0;

	pos = MAKELONG( (WORD)point->x_, (WORD)point->y_ );

	uint32 result = ::SendMessage( hwnd_, EM_CHARFROMPOS, 0, pos );

	return result;
}

uint32 Win32Edit::getCaretPosition()
{

	return getSelectionStart();
}

void Win32Edit::setCaretPosition( const uint32& caretPos )
{

}

//Ugly hack for bcb6 w. Stlport w. fixed ctype.h header
#if defined(VCF_BCC) && defined(__SGI_STL_PORT) && ((__BORLANDC__ >= 0x0560) && (__BORLANDC__ < 0x0570))
#define toupper std::_ltoupper
#define tolower std::_ltolower
#endif



bool Win32Edit::stateAllowsModelChange()
{
	bool result = false;

	if ( !(editState_ & esStyleChanging) && 
		!(editState_ & esPeerTextChanging) &&
		!(editState_ & esKeyEvent) &&
		!(editState_ & esExternalTextChanging) ) {

		result = true;
	}

	return result;
}

bool Win32Edit::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;	

	switch ( message ) {

		case WM_RBUTTONDOWN :  case WM_LBUTTONDOWN : {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			long start = 0;
			long end = 0;

			getSelectionMark( start, end );
			currentSelLength_ = end - start;
			currentSelStart_ = start;

		}
		break;

		case WM_SETTEXT : case EM_STREAMIN : {
			if ( textControl_->getReadOnly() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				result = true;
				
				editState_ |= esPeerTextChanging;
				
				//let the default rich text code handle this!
				wndProcResult = defaultWndProcedure( message, wParam, lParam );
				
				//modify the model, but ignore an change notifications to us!
				editState_ |= esModelTextChanging;
				
				textControl_->getTextModel()->setText( getText() );
				
				editState_ &= ~esModelTextChanging;
				
				editState_ &= ~esPeerTextChanging;
			}
		}
		break;
/*
		case WM_TIMER : {
			StringUtils::trace( "WM_TIMER\n" );
						}
			break;

			case EM_SETSEL : {
			StringUtils::trace( "EM_SETSEL\n" );
						}
			break;

			case EM_EXSETSEL : {
				StringUtils::trace( "EM_EXSETSEL\n" );

							   }
				break;
*/
		case WM_RBUTTONUP : case WM_LBUTTONUP : {

			result = true;
			wndProcResult = defaultWndProcedure( message, wParam, lParam ); //this causes weird double selection


			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			long start = 0;
			long end = 0;

			getSelectionMark( start, end );

			if ( (currentSelLength_ != (end - start)) || (currentSelStart_ != start) ) {
				//selection changed
				TextEvent event( textControl_, start, end - start );

				textControl_->SelectionChanged( &event );
			}

			currentSelLength_ = end - start;
			currentSelStart_ = start;
		}
		break;

		case WM_KEYDOWN: {

			if ( textControl_->getReadOnly() ) {
				wndProcResult = 0;
				result = true;
			}
			else {

				editState_ |= esKeyEvent;

				uint32 virtKeyCode = Win32UIUtils::translateVKCode( wParam );

				switch ( virtKeyCode ) {
					case vkLeftArrow : 
					case vkRightArrow : 
					case vkPgUp : 
					case vkPgDown : 
					case vkHome : 
					case vkEnd : 
					case vkDownArrow :
					case vkUpArrow : {
						long start = 0;
						long end = 0;

						getSelectionMark( start, end );
						currentSelLength_ = end - start;
						currentSelStart_ = start;
					}
					break;
				}


				if ( (peerControl_->getComponentState() != Component::csDestroying) ) {

					KeyboardData keyData = Win32UIUtils::translateKeyData( hwnd_, lParam );
					uint32 eventType = Control::KEYBOARD_DOWN;


					uint32 keyMask = Win32UIUtils::translateKeyMask( keyData.keyMask );

					//virtKeyCode = Win32UIUtils::translateVKCode( keyData.VKeyCode );

					VCF::KeyboardEvent event( peerControl_, eventType, keyData.repeatCount,
						keyMask, (VCF::VCFChar)keyData.character, (VirtualKeyCode)virtKeyCode );



					peerControl_->handleEvent( &event );

					switch ( virtKeyCode ) {
						case vkLeftArrow : 
						case vkRightArrow : 
						case vkPgUp : 
						case vkPgDown : 
						case vkHome : 
						case vkEnd : 
						case vkDownArrow :
						case vkUpArrow : {


							long start = 0;
							long end = 0;

							getSelectionMark( start, end );

							if ( event.hasShiftKey() && ((currentSelLength_ != (end - start)) || (currentSelStart_ != start)) ) {
								//selection changed
								TextEvent event( textControl_, start, end - start );

								textControl_->SelectionChanged( &event );
							}

							currentSelLength_ = end - start;
							currentSelStart_ = start;
						}
						break;
					}

					//wndProcResult = 1;
					result = true;
				}

				if ( !(peerControl_->getComponentState() & Component::csDesigning) ) {
					wndProcResult = defaultWndProcedure(  message, wParam, lParam );
					result = true;
				}


				editState_ &= ~esKeyEvent;
			}
		}
		break;

		case WM_CHAR:  case WM_KEYUP:{
			if ( textControl_->getReadOnly() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				
				editState_ |= esKeyEvent;

				/**
				JC
				I moved the defaultWndProcedure(  message, wParam, lParam );
				block *after* I call the peerControl_->handleEvent() 
				method. Otherwise the caretpos is "wrong", for lack of a better 
				word, which in turn screws up where data is removed from the model.
				*/
				if ( !peerControl_->isDestroying() && !peerControl_->isDesigning() ) {

					KeyboardData keyData = Win32UIUtils::translateKeyData( hwnd_, lParam );
					uint32 virtKeyCode = Win32UIUtils::translateVKCode( keyData.VKeyCode );

					uint32 eventType = 0;
					switch ( message ){
						case WM_CHAR: {
							/**
							JC
							we do this to overcome getting weird virtual key values
							for WM_CHAR messages, as translateKeyData isn't quite right.
							In fact, we should conceivably look into ditching period
							*/
							eventType = Control::KEYBOARD_PRESSED;
							keyData.character = (VCFChar)wParam;

							/**
							JC
							if the character is a graphic char (like ":" or "a")
							then re-calculate the virtual key code, based on the 
							character value. This was put here to overcome a bug
							when handling WM_CHAR's from the numpad, which gives
							us the right character, but a bogus virtual key
							*/
							if ( iswgraph( keyData.character ) ) {

								virtKeyCode = Win32UIUtils::convertCharToVKCode( keyData.character );
							}
						}
						break;

						case WM_KEYUP: {
							eventType = Control::KEYBOARD_UP;
						}
						break;
					}

					uint32 keyMask = Win32UIUtils::translateKeyMask( keyData.keyMask );

					VCF::KeyboardEvent event( peerControl_, eventType, keyData.repeatCount,
						keyMask, (VCF::VCFChar)keyData.character, (VirtualKeyCode)virtKeyCode );

					peerControl_->handleEvent( &event );

					result = true;
				}

				if ( !peerControl_->isDesigning() ) {
					wndProcResult = defaultWndProcedure( message, wParam, lParam );
					result = true;
				}
				else if ( peerControl_->isDesigning() ) {
					wndProcResult = 0;
					result = true;
				}

				editState_ &= ~esKeyEvent;
			}
		}
		break;

		case WM_COMMAND:{


			wndProcResult = defaultWndProcedure(  message, wParam, lParam );
			result = true;

			switch ( HIWORD(wParam) ) {
				case EN_CHANGE:{
					if ( stateAllowsModelChange() ) {
						editState_ |= esModelTextChanging;

						VCF::TextModel* model = textControl_->getTextModel();
						if ( NULL != model ) {
							String text = getText();

							model->setText( text );
						}

						editState_ &= ~esModelTextChanging;
					}
				}
				break; 


			}

		}
		break;

		
		case EN_SELCHANGE : {
			wndProcResult = 0;
			result = true;

			

			SELCHANGE* selChange = (SELCHANGE*)lParam;

			//StringUtils::trace( Format("EN_SELCHANGE selChange->seltyp:%d cpMax: %d,  cpMin: %d\n") %
			//					 selChange->seltyp % selChange->chrg.cpMax % selChange->chrg.cpMin	);
			if ( selChange->chrg.cpMax != selChange->chrg.cpMin ) {
				//selection changed

				//StringUtils::trace( "Changing sel start and sel leng\n" );
				currentSelLength_ = selChange->chrg.cpMax - selChange->chrg.cpMin;
				currentSelStart_ = selChange->chrg.cpMin;

				TextEvent event( textControl_, currentSelStart_, currentSelLength_ );

				textControl_->SelectionChanged( &event );
			}

			
		}
		break;

		case WM_CUT : case EM_REDO :case EM_UNDO : case WM_PASTE : {
			if ( textControl_->getReadOnly() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				wndProcResult = 0;
				result = false;
	
				editState_ |= esExternalTextChanging;
	
				if ( !peerControl_->isDesigning() ) {
					wndProcResult = defaultWndProcedure(  message, wParam, lParam );
					result = true;
				}
	
				// copy the control's text into the model
				
				VCF::TextModel* model = textControl_->getTextModel();
				if ( NULL != model ) {
					editState_ |= esModelTextChanging;
					
					String text = getText();
					
					/*if ( WM_PASTE == message ) {
						//remove \r\n and replace with \n
						uint32 pos = text.find( "\r\n" );
						while ( pos != String::npos ) {
							text.erase( pos, 1 ); //erase \r
							pos = text.find( "\r\n" );
						}
					}*/
	
					model->setText( text );
					
					editState_ &= ~esModelTextChanging;
				}
				
				
				editState_ &= ~esExternalTextChanging;
			}
		}
		break;

		case WM_ERASEBKGND :{
			wndProcResult = 1;

			Color* color = peerControl_->getColor();
			COLORREF backColor = color->getColorRef32();

			SendMessage( hwnd_, EM_SETBKGNDCOLOR, 0, (LPARAM)backColor );


			result = true;
		}
		break;

		case WM_PAINT:{
			wndProcResult = 0;
			result = false;
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

		case WM_CTLCOLOREDIT : {
			HDC hdcEdit = (HDC) wParam;   // handle to display context
			HWND hwndEdit = (HWND) lParam; // handle to static control
			if ( NULL != backgroundBrush_ ) {
				DeleteObject( backgroundBrush_ );
			}
			Color* color = peerControl_->getColor();
			COLORREF backColor = color->getColorRef32();

			color = peerControl_->getFont()->getColor();
			COLORREF textColor = color->getColorRef32();

			backgroundBrush_ = CreateSolidBrush( backColor );
			SetBkColor( hdcEdit, backColor );
			SetTextColor( hdcEdit, textColor );

			wndProcResult = (LRESULT)backgroundBrush_;
			return true;
		}
		break;


		//this may be useful to uncomment, but at the
		//moment it never gets called, possible because we
		//do not use the default Dialog wnd proc
		//case WM_GETDLGCODE : {

		//	result = DLGC_WANTALLKEYS;
		//}
		//break;
/*
		case WM_SETFOCUS: {
			AbstractWin32Component::defaultWndProcedure( message, wParam, lParam );

			DWORD s, e;
			SendMessage( hwnd_, EM_GETSEL, (WPARAM)&s, (LPARAM)&e );

			StringUtils::trace( Format("WM_SETFOCUS s: %d, e: %d \n") %
									s % e );

			currentSelLength_ = e - s;
			currentSelStart_ = s;

			editState_ |= esGotFocus;
			
			result = true;
			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_CAPTURECHANGED : {
			HWND hwndNewCapture = (HWND) lParam;

			editState_ |= esCaptureChanged;
			DWORD s2, e2;
			SendMessage( hwnd_, EM_GETSEL, (WPARAM)&s2, (LPARAM)&e2 );


			StringUtils::trace( Format("WM_CAPTURECHANGED s2: %d, e2: %d hwnd_: 0x%08X hwndNewCapture: 0x%08X\n") %
									s2 % e2 % hwnd_ % hwndNewCapture );

								 }
			break;
*/

		default: {	

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

		}
		break;

	}

	return result;
}

void Win32Edit::onTextModelTextChanged( TextEvent* event )
{
	if ( (NULL != event) && 
		!(editState_ & esModelTextChanging) &&
		!(editState_ & esKeyEvent) ){

		switch ( event->getType() ) {
			case TextModel::tmTextInserted : {
				insertText( event->getChangeStart(),
											event->getChangeText() );
			}
			break;

			case TextModel::tmTextReplaced : {
				String originalText = event->getOriginalText();
				deleteText( event->getChangeStart(),
											originalText.size() );

				insertText( event->getChangeStart(),
											event->getChangeText() );
			}
			break;

			case TextModel::tmTextRemoved : {
				deleteText( event->getChangeStart(),
											event->getChangeLength() );
			}
			break;

			case TextModel::tmTextSet : {
				setText( textControl_->getTextModel()->getText() );
			}
			break;
		}
	}
}



int Win32Edit::getCRCount( const uint32& begin, const uint32& end, const bool& limitCountsAreExact )
{
	// Fixes a Microsoft bug:
	//	EM_GETSEL doesn't count the '\r' characters: so the '\r' counts must be added to (begin,end) afterword
	//	EM_SETSEL doesn't count the '\r' characters either: but the effect is the '\r' counts must be subtracted first
	//																			before submitting (begin,end) with EM_SETSEL to the control
	//
	// Usage:
	//		use _limitCountsAreExact = true  with setSelectionMark  ( after  EM_GETSEL )
	//		use _limitCountsAreExact = false with getSelectionStart ( before EM_SETSEL )
	//	in general:
	//		use _limitCountsAreExact = true when the exact limit of the count of CRs is known, false otherwise


	TextControl* tc = (TextControl*)this->getControl();

	String text = tc->getTextModel()->getText();

	uint32 size = text.size();
	uint32 b = VCF::minVal<>( begin, size );
	uint32 e = VCF::minVal<>( end, size );

	int foundCRTot = 0;
	int foundCR = 0;
	const VCFChar* p = text.c_str();

	const VCFChar* start = p + b;
	const VCFChar* finish = p + e;
	const VCFChar* endText = p + size;

	p = start;
	// the first time counts the '\r' characters until 'finish'
	// the following times the count is adjusted if 'finish' moves forward
	while ( p < endText ) {
		foundCR = 0;

		// counts the '\r' characters between the current position and 'finish'
		// note: it is really possible to have ( p < finish && p < endText ) while ( endText < finish )
		while ( p < finish && p < endText ) {
			if ( *p == '\r' ) {
				foundCR++;
			}
			p++;
		}

		finish += foundCR;
		foundCRTot += foundCR;
		if ( limitCountsAreExact || 0 == foundCR ) {
			break;
		}
	}

	return foundCRTot;
}


void Win32Edit::setText( const VCF::String& text )
{
	editState_ |= esPeerTextChanging;

	int firstLine1 = ::SendMessage( hwnd_, EM_GETFIRSTVISIBLELINE, (WPARAM)0, (LPARAM)0 );

	DWORD start = getSelectionStart();
	DWORD count = getSelectionCount();

	ITextRange* range;
	textDocument_->Range( 0, 0, &range );
	if ( NULL != range ) {

		long len = 0;
		range->GetStoryLength( &len );
		range->SetEnd( len );

		BSTR str = SysAllocStringLen( text.c_str(), text.length() );

		range->SetText( str );

		SysFreeString( str );

		range->Release();
	}

	setSelectionMark( start, count );

	int firstLine2 = ::SendMessage( hwnd_, EM_GETFIRSTVISIBLELINE, (WPARAM)0, (LPARAM)0 );

	if ( firstLine2 != firstLine1 ) {
		// workaround necessary only while insertText is implemented with setText - MP
		// if we could know the number of lines visible in the editor, we would be able
		// to save these two calls.
		// setText() empties the editor first, then puts back the text plus the added text,
		// but in this way it looses the scrolling position information.
		// At that point setSelectionMark() will make the selection visible, but at the end
		// of the page.
		::SendMessage( hwnd_, EM_LINESCROLL, (WPARAM)0, (LPARAM)(-(firstLine2-firstLine1)) );

		// this will not move the the scrollbar if the selection is already visible
		setSelectionMark( start, count );
	}

	editState_ &= ~esPeerTextChanging;
}

uint32 Win32Edit::getSelectionStart()
{
	long start = 0;
	long end = -1;

	getSelectionMark( start, end );

	return ( start );
}

uint32 Win32Edit::getSelectionCount()
{
	long start = 0;
	long end = 0;

	getSelectionMark( start, end );

	return ( end - start );
}

void Win32Edit::getSelectionMark( long & start, long & end )
{
	ITextSelection* selection = NULL;
	textDocument_->GetSelection( &selection );
	if ( NULL != selection ) {
		selection->GetStart( (long*)&start );
		selection->GetEnd( (long*)&end );
		selection->Release();
	}
}

void Win32Edit::clearSelection()
{
	::SendMessage( hwnd_, EM_SETSEL, (WPARAM)-1, (LPARAM)0 );	
}

void Win32Edit::setSelectionMark( const uint32& start, const uint32& count )
{
	uint32 end = start + count;
	
	::SendMessage( hwnd_, EM_SETSEL, (WPARAM)start, (LPARAM)end );	
}


void Win32Edit::scrollToLine( const uint32& lineIndex )
{
	::SendMessage( hwnd_, EM_LINESCROLL, 0, lineIndex );
}

void Win32Edit::scrollToSelection( const bool& _showEndSel/*=false*/ )
{
	if ( _showEndSel ) {
		// not implemented yet
	}
	::SendMessage( hwnd_, EM_SCROLLCARET, (WPARAM)0, (LPARAM)0 );
}

void Win32Edit::repaint( Rect* repaintRect )
{
	if ( NULL == repaintRect ){
		RECT bounds = {0,0,0,0};
		GetWindowRect( hwnd_, &bounds );
		RECT tmp = {0,0,abs(bounds.right-bounds.left), abs(bounds.bottom - bounds.top)};

		::InvalidateRect( hwnd_, &tmp, TRUE );
	}
	else {
		RECT rect = {0,0,0,0};
		rect.left = (long)repaintRect->left_;
		rect.top = (long)repaintRect->top_;
		rect.right = (long)repaintRect->right_;
		rect.bottom = (long)repaintRect->bottom_;
		::InvalidateRect( hwnd_, &rect, TRUE );
	}
}

void Win32Edit::setReadOnly( const bool& readonly )
{
	LRESULT options = SendMessage( hwnd_, EM_GETOPTIONS, 0, 0 ) ;
	bool xorIt = !readonly ;
	if( !readonly ) {
		xorIt = (options & ECO_READONLY) == ECO_READONLY ;
	}
	if( xorIt ) {
		options ^= ECO_READONLY ;
	} else {
		options |= ECO_READONLY ;
	}
	SendMessage( hwnd_, EM_SETOPTIONS, options, ECOOP_SET ) ;
}

uint32 Win32Edit::getTotalPrintablePageCount( PrintContext* context )
{
	printPageMap_.clear();

	uint32 result = 1;

	FORMATRANGE formatRange;
	memset(&formatRange,0,sizeof(formatRange));
	//print everything
	formatRange.chrg.cpMax = -1;
	formatRange.chrg.cpMin = 0;

	formatRange.hdc = (HDC)context->getPeer()->getContextID();
	formatRange.hdcTarget = formatRange.hdc;

	Rect printRect = context->getViewableBounds();
	double dpi = GraphicsToolkit::getDPI(context);

	printRect.left_ = (printRect.left_ / dpi) * 1400.0;
	printRect.top_ = (printRect.top_ / dpi) * 1400.0;
	printRect.bottom_ = (printRect.bottom_ / dpi) * 1400.0;
	printRect.right_ = (printRect.right_ / dpi) * 1400.0;

	formatRange.rcPage.left = printRect.left_;
	formatRange.rcPage.top = printRect.top_;
	formatRange.rcPage.right = printRect.right_;
	formatRange.rcPage.bottom = printRect.bottom_;

	formatRange.rc.left = printRect.left_;
	formatRange.rc.top = printRect.top_;
	formatRange.rc.right = printRect.right_;
	formatRange.rc.bottom = printRect.bottom_;

	HDC dc = GetDC( hwnd_ );
	double ctrlDPI = (double)GetDeviceCaps( dc, LOGPIXELSY);
	ReleaseDC( hwnd_, dc );

	DWORD margins = ::SendMessage( hwnd_, EM_GETMARGINS, 0, 0 );
	double lm = ((double)LOWORD(margins)/ctrlDPI) * 1400;
	double rm = ((double)HIWORD(margins)/ctrlDPI) * 1400;

	formatRange.rc.left += lm;
	formatRange.rc.right -= lm;
	formatRange.rc.top += 350; //add a 1/4"
	formatRange.rc.bottom -= 350; //add a 1/4"

	TextControl* tc = (TextControl*)this->getControl();
	String text = tc->getTextModel()->getText();
	uint32 textSize = text.size();

	SendMessage( hwnd_, EM_FORMATRANGE, 0, 0 );

	printPageMap_[result] = (uint32)-1;

	DWORD index = SendMessage( hwnd_, EM_FORMATRANGE, 0, (LPARAM)&formatRange );
	while ( (index <= textSize) && (formatRange.chrg.cpMin != index) ) {
		printPageMap_[result] = index;

		formatRange.chrg.cpMin = index;
		index = SendMessage( hwnd_, EM_FORMATRANGE, 0, (LPARAM)&formatRange );
		result ++;
	}

	SendMessage( hwnd_, EM_FORMATRANGE, 0, 0 );


	return result;
}

void Win32Edit::print( PrintContext* context, const int32& page )
{
	VCF_ASSERT( !printPageMap_.empty() );

	if ( printPageMap_.empty() ) {

		return;
	}

	std::map<uint32,uint32>::iterator found = printPageMap_.find( page );
	if ( found == printPageMap_.end() ) {
		//clear out of dodge! We are done printing
		printPageMap_.clear();
		return;
	}
	else {
		FORMATRANGE formatRange;
		memset(&formatRange,0,sizeof(formatRange));
		//print everything
		formatRange.chrg.cpMax = found->second;
		if ( 0 == (page-1) ) {
			formatRange.chrg.cpMin = 0;
		}
		else {
			formatRange.chrg.cpMin = printPageMap_[page-1];
		}


		formatRange.hdc = (HDC)context->getPeer()->getContextID();
		formatRange.hdcTarget = formatRange.hdc;

		Rect printRect = context->getViewableBounds();
		double dpi = GraphicsToolkit::getDPI(context);

		printRect.left_ = (printRect.left_ / dpi) * 1400.0;
		printRect.top_ = (printRect.top_ / dpi) * 1400.0;
		printRect.bottom_ = (printRect.bottom_ / dpi) * 1400.0;
		printRect.right_ = (printRect.right_ / dpi) * 1400.0;

		formatRange.rcPage.left = printRect.left_;
		formatRange.rcPage.top = printRect.top_;
		formatRange.rcPage.right = printRect.right_;
		formatRange.rcPage.bottom = printRect.bottom_;

		formatRange.rc.left = printRect.left_;
		formatRange.rc.top = printRect.top_;
		formatRange.rc.right = printRect.right_;
		formatRange.rc.bottom = printRect.bottom_;

		HDC dc = GetDC( hwnd_ );
		double ctrlDPI = (double)GetDeviceCaps( dc, LOGPIXELSY);
		ReleaseDC( hwnd_, dc );

		DWORD margins = ::SendMessage( hwnd_, EM_GETMARGINS, 0, 0 );
		double lm = ((double)LOWORD(margins)/ctrlDPI) * 1400;
		double rm = ((double)HIWORD(margins)/ctrlDPI) * 1400;

		formatRange.rc.left += lm;
		formatRange.rc.right -= lm;
		formatRange.rc.top += 350; //add a 1/4"
		formatRange.rc.bottom -= 350; //add a 1/4"



		SendMessage( hwnd_, EM_FORMATRANGE, TRUE, (LPARAM)&formatRange );
	}
}

void Win32Edit::finishPrinting()
{
	SendMessage( hwnd_, EM_FORMATRANGE, 0, 0 );
}

void Win32Edit::onControlModelChanged( Event* e )
{
	CallBack* tml = getCallback( "Win32TextModelHandler" );
	if ( NULL == tml ) {
		tml = new ClassProcedure1<TextEvent*,Win32Edit>( this, &Win32Edit::onTextModelTextChanged, "Win32TextModelHandler" );
	}



	TextModel* tm = textControl_->getTextModel();
	tm->addTextModelChangedHandler( (EventHandler*)tml );


	String text = tm->getText();


	setText( text );


}

void Win32Edit::cut()
{
	if ( !textControl_->getReadOnly() ) {
		SendMessage( hwnd_, WM_CUT, 0, 0 );
	}
}

void Win32Edit::copy()
{
	SendMessage( hwnd_, WM_COPY, 0, 0 );
}

void Win32Edit::paste()
{
	if ( !textControl_->getReadOnly() ) {
		SendMessage( hwnd_, WM_PASTE, 0, 0 );
	}
}

bool Win32Edit::canUndo()
{
	return SendMessage( hwnd_, EM_CANUNDO, 0, 0 ) ? true : false;
}

bool Win32Edit::canRedo()
{
	return SendMessage( hwnd_, EM_CANREDO, 0, 0 ) ? true : false;
}

void Win32Edit::undo()
{
	if ( !textControl_->getReadOnly() ) {
		SendMessage( hwnd_, EM_UNDO, 0, 0 );
	}
}

void Win32Edit::redo()
{
	//this one is necessary too, otherwise the model wouldn't be updated
	if ( !textControl_->getReadOnly() ) {
		SendMessage( hwnd_, EM_REDO, 0, 0 );
	}
}

void Win32Edit::setTextWrapping( const bool& val )
{
	if ( !val ) {
		SendMessage(hwnd_, EM_SETTARGETDEVICE, 0, 1);
	}
	else {
		SendMessage(hwnd_, EM_SETTARGETDEVICE, 0, 0);
	}
}


/**
$Id$
*/
