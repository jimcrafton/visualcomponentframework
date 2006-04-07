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
			new GenericEventHandler<Win32Edit>( this, &Win32Edit::onControlModelChanged, "Win32Edit::onControlModelChanged" );

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

	::SendMessage( hwnd_, EM_SETMARGINS, EC_RIGHTMARGIN, (long)rightMargin );

	editState_ &= ~esStyleChanging;
}

void Win32Edit::setLeftMargin( const double & leftMargin )
{
	editState_ |= esStyleChanging;

	::SendMessage( hwnd_, EM_SETMARGINS, EC_LEFTMARGIN, (long)leftMargin );

	editState_ &= ~esStyleChanging;
}

unsigned long Win32Edit::getLineCount()
{
	return ::SendMessage( hwnd_, EM_GETLINECOUNT, 0, 0 );
}

Rect Win32Edit::getContentBoundsForWidth(const double& width)
{
	return Win32TextPeer::getContentBoundsForWidth(width);
}

unsigned long Win32Edit::getCurrentLinePosition()
{
	DWORD pos = getSelectionStart();

	ulong32 result = ::SendMessage( hwnd_, EM_LINEFROMCHAR, pos, 0 );


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

void Win32Edit::getStyle( unsigned int start, unsigned int length, Dictionary& styles, Color& color )
{
	Win32TextPeer::getStyle( start, length, styles, color );
}


void Win32Edit::setDefaultStyle( Dictionary& styles )
{
	editState_ |= esStyleChanging;

	Win32TextPeer::setDefaultStyle( styles );

	editState_ &= ~esStyleChanging;
}



VCF::Point* Win32Edit::getPositionFromCharIndex( const unsigned long& index )
{
	DWORD pos = ::SendMessage( hwnd_, EM_POSFROMCHAR, index, 0 );
	posAtChar_.x_ = LOWORD(pos);
	posAtChar_.y_ = HIWORD(pos);
	return &posAtChar_;
}

unsigned long Win32Edit::getCharIndexFromPosition( VCF::Point* point )
{
	DWORD pos = 0;

	pos = MAKEWORD( (long)point->x_, (long)point->y_ );

	unsigned long result = ::SendMessage( hwnd_, EM_CHARFROMPOS, 0, pos );

	return result;
}

unsigned long Win32Edit::getCaretPosition()
{

	return getSelectionStart();
}

void Win32Edit::setCaretPosition( const unsigned long& caretPos )
{

}

//Ugly hack for bcb6 w. Stlport w. fixed ctype.h header
#if defined(__BORLANDC__) && defined(__SGI_STL_PORT) && ((__BORLANDC__ >= 0x0560) && (__BORLANDC__ < 0x0570))
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

			ulong32 start = 0;
			ulong32 end = 0;

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

			ulong32 start = 0;
			ulong32 end = 0;

			getSelectionMark( start, end );

			if ( (currentSelLength_ != (end - start)) || (currentSelStart_ != start) ) {
				//selection changed
				TextEvent event( textControl_, start, end - start );

				textControl_->SelectionChanged.fireEvent( &event );
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

				ulong32 virtKeyCode = Win32UIUtils::translateVKCode( wParam );

				switch ( virtKeyCode ) {
					case vkLeftArrow : 
					case vkRightArrow : 
					case vkPgUp : 
					case vkPgDown : 
					case vkHome : 
					case vkEnd : 
					case vkDownArrow :
					case vkUpArrow : {
						ulong32 start = 0;
						ulong32 end = 0;

						getSelectionMark( start, end );
						currentSelLength_ = end - start;
						currentSelStart_ = start;
					}
					break;
				}


				if ( (peerControl_->getComponentState() != Component::csDestroying) ) {

					KeyboardData keyData = Win32UIUtils::translateKeyData( hwnd_, lParam );
					unsigned long eventType = Control::KEYBOARD_DOWN;


					unsigned long keyMask = Win32UIUtils::translateKeyMask( keyData.keyMask );

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


							ulong32 start = 0;
							ulong32 end = 0;

							getSelectionMark( start, end );

							if ( event.hasShiftKey() && ((currentSelLength_ != (end - start)) || (currentSelStart_ != start)) ) {
								//selection changed
								TextEvent event( textControl_, start, end - start );

								textControl_->SelectionChanged.fireEvent( &event );
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
					ulong32 virtKeyCode = Win32UIUtils::translateVKCode( keyData.VKeyCode );

					unsigned long eventType = 0;
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
							if ( isgraph( keyData.character ) ) {

								virtKeyCode = Win32UIUtils::convertCharToVKCode( keyData.character );
							}
						}
						break;

						case WM_KEYUP: {
							eventType = Control::KEYBOARD_UP;
						}
						break;
					}

					unsigned long keyMask = Win32UIUtils::translateKeyMask( keyData.keyMask );

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

				textControl_->SelectionChanged.fireEvent( &event );
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



int Win32Edit::getCRCount( const unsigned long& begin, const unsigned long& end, const bool& limitCountsAreExact )
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

	unsigned long size = text.size();
	unsigned long b = VCF::minVal<>( begin, size );
	unsigned long e = VCF::minVal<>( end, size );

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

unsigned long Win32Edit::getSelectionStart()
{
	unsigned long start = 0;
	unsigned long end = -1;

	getSelectionMark( start, end );

	return ( start );
}

unsigned long Win32Edit::getSelectionCount()
{
	unsigned long start = 0;
	unsigned long end = 0;

	getSelectionMark( start, end );

	return ( end - start );
}

void Win32Edit::getSelectionMark( unsigned long & start, unsigned long & end )
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

}

void Win32Edit::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	unsigned long end = start + count;
	
	::SendMessage( hwnd_, EM_SETSEL, (WPARAM)start, (LPARAM)end );	
}


void Win32Edit::scrollToLine( const ulong32& lineIndex )
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
	//SendMessage( hwnd_, EM_SETREADONLY, readonly ? TRUE : FALSE, 0 );
	if ( NULL != richEditCallback_ ) {
		SendMessage( hwnd_, EM_SETOLECALLBACK, 0, (LPARAM)0 );
		delete richEditCallback_;		
	}

	if ( readonly ) {
		richEditCallback_ = new Win32RichEditOleCallback();
		SendMessage( hwnd_, EM_SETOLECALLBACK, 0, (LPARAM)richEditCallback_ );
	}
}

ulong32 Win32Edit::getTotalPrintablePageCount( PrintContext* context )
{
	printPageMap_.clear();

	ulong32 result = 1;

	FORMATRANGE formatRange = {0};
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
	ulong32 textSize = text.size();

	SendMessage( hwnd_, EM_FORMATRANGE, 0, 0 );

	printPageMap_[result] = (ulong32)-1;

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

void Win32Edit::print( PrintContext* context, const long& page )
{
	VCF_ASSERT( !printPageMap_.empty() );

	if ( printPageMap_.empty() ) {

		return;
	}

	std::map<ulong32,ulong32>::iterator found = printPageMap_.find( page );
	if ( found == printPageMap_.end() ) {
		//clear out of dodge! We are done printing
		printPageMap_.clear();
		return;
	}
	else {
		FORMATRANGE formatRange = {0};
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
	EventHandler* tml = getEventHandler( "Win32TextModelHandler" );
	if ( NULL == tml ) {
		tml = new TextModelEventHandler<Win32Edit>( this, &Win32Edit::onTextModelTextChanged, "Win32TextModelHandler" );
	}



	TextModel* tm = textControl_->getTextModel();
	tm->addTextModelChangedHandler( tml );


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
	if ( val ) {
		SendMessage(hwnd_, EM_SETTARGETDEVICE, 0, 1);
	}
	else {
		SendMessage(hwnd_, EM_SETTARGETDEVICE, 0, 0);
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.7  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.13  2006/03/25 03:01:15  ddiego
*attempt to fix small glitch in win32 text edit for numpad handling.
*
*Revision 1.5.2.12  2006/03/25 02:25:41  ddiego
*attempt to fix small glitch in win32 text edit for numpad handling.
*
*Revision 1.5.2.11  2006/03/21 01:29:22  ddiego
*fixed table control double click bug.
*
*Revision 1.5.2.10  2006/03/19 18:21:17  ddiego
*diagnostic code commented out in win32edit - still have a selection bug not quite resolved.
*
*Revision 1.5.2.9  2006/03/16 03:23:11  ddiego
*fixes some font change notification issues in win32 peers.
*
*Revision 1.5.2.8  2006/03/15 04:18:21  ddiego
*fixed text control desktop refresh bug 1449840.
*
*Revision 1.5.2.7  2006/03/14 22:14:53  ddiego
*Win32ToolKit.cpp
*
*Revision 1.5.2.6  2006/02/22 05:00:40  ddiego
*some minor text updates to support toggling word wrap.
*
*Revision 1.5.2.5  2005/11/21 21:28:03  ddiego
*updated win32 code a bit due to osx changes.
*
*Revision 1.5.2.4  2005/10/22 17:04:19  ddiego
*added 2 more patches from kitovyj for mingw.
*
*Revision 1.5.2.3  2005/10/07 19:31:53  ddiego
*merged patch 1315995 and 1315991 into dev repos.
*
*Revision 1.5.2.2  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.5.2.1  2005/08/31 20:29:23  kiklop74
*Added fix for bcb6 rtl
*
*Revision 1.5  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.34  2005/06/26 01:53:03  marcelloptr
*improvements to the Color class. The default, when packing the components into a single integer, is now cpsARGB instead than cpsABGR.
*
*Revision 1.3.2.33  2005/06/09 06:13:08  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.3.2.32  2005/06/07 18:35:31  marcelloptr
*added missed getStyle() function. Fixed underline text that couldn't be removed once introduced.
*
*Revision 1.3.2.31  2005/05/30 22:31:29  ddiego
*fixed readonly mode in text edit and added better default font change support.
*
*Revision 1.3.2.30  2005/05/30 22:22:29  ddiego
*fixed readonly mode in text edit and added better default font change support.
*
*Revision 1.3.2.29  2005/05/24 21:03:12  ddiego
*fixed typo bug in get selection mark.
*
*Revision 1.3.2.28  2005/05/22 04:05:43  ddiego
*more text edit fixes.
*
*Revision 1.3.2.27  2005/05/19 22:14:51  marcelloptr
*Fixes around Win32Edit: selectAll and Redo operation. Deleting characters. Going to get read of getCRCount :)
*
*Revision 1.3.2.25  2005/05/19 02:19:11  ddiego
*more win32 edit fixes.
*
*Revision 1.3.2.24  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.3.2.23  2005/05/15 23:17:38  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.22  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3.2.21  2005/05/02 02:31:42  ddiego
*minor text updates.
*
*Revision 1.3.2.20  2005/04/30 11:52:36  marcelloptr
*added a comment for the enabledSetTextOnControl_ member variable
*
*Revision 1.3.2.17  2005/04/26 02:29:39  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.3.2.16  2005/04/25 00:11:58  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.3.2.15  2005/04/20 02:26:00  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.14  2005/04/16 17:22:55  marcelloptr
*temporary workaround for scrolling problem when inserting text (and selecting it)
*
*Revision 1.3.2.13  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.12  2005/03/28 18:25:23  marcelloptr
*just a comment
*
*Revision 1.3.2.10  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.3.2.9  2005/03/23 15:54:49  marcelloptr
*added a comment
*
*Revision 1.3.2.8  2005/03/23 03:31:23  ddiego
*fixed rich edit back color bug.
*
*Revision 1.3.2.7  2005/03/21 04:35:49  ddiego
*updates
*
*Revision 1.3.2.6  2005/03/15 01:51:50  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.5  2005/02/24 05:39:39  marcelloptr
*bugfix [1150773] - Win32Edit loses last n characters past the last 2048 written
*
*Revision 1.3.2.4  2005/02/17 04:06:35  ddiego
*fixed bug in handling wm_keydown event in win32edit
*
*Revision 1.3.2.3  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.2  2005/01/28 02:49:02  ddiego
*fixed bug 1111096 where the text control was properly handlind
*input from the numbpad keys.
*
*Revision 1.3.2.1  2004/12/22 03:32:19  marcelloptr
*we need to hide the selection when the focus is lost
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.6  2004/11/19 05:54:28  ddiego
*added some fixes to the text peer for win32 for printing. added toolbars to text edit example anmd added printing
*
*Revision 1.2.2.5  2004/11/18 06:45:44  ddiego
*updated toolbar btn bug, and added text edit sample.
*
*Revision 1.2.2.4  2004/10/03 23:14:37  ddiego
*fixed a text model bug that incorectly handled deleting chars.
*
*Revision 1.2.2.3  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.2  2004/09/06 21:30:20  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.12  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.11  2004/07/16 04:01:46  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.10  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.9  2004/07/15 04:27:14  ddiego
*more updates for edit nc client painting
*
*Revision 1.1.2.8  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.7  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.6  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.5  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/21 00:35:16  ddiego
*fixed a bug that pallindo found - was not passing
*in the right flag to the unicode version for calling SendMessage
*EM_STREAMIN
*
*Revision 1.1.2.3  2004/05/04 17:16:07  ddiego
*updated some win32 stuff for unicode compliance
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.41.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.41  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.38.2.7  2004/03/21 19:44:58  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.38.2.6  2004/03/21 00:39:23  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.38.2.5  2004/03/19 21:25:57  ddiego
*just some minor noodlin
*
*Revision 1.38.2.4  2004/03/17 03:22:57  ddiego
*fixed a glitch in setting focus
*
*Revision 1.38.2.3  2004/01/19 23:32:06  ddiego
**** empty log message ***
*
*Revision 1.38.2.2  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.38.2.1  2004/01/06 04:40:53  ddiego
*added first handler and setting the first handler to the delegate
*
*Revision 1.38  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.37.2.4  2003/12/02 22:11:30  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.37.2.3  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.37.2.2  2003/08/17 18:18:05  ddiego
*added some of Marcellos fixes, notably the one to fix CRLF problems in teh
*edit control
*
*Revision 1.37.2.1  2003/08/12 20:30:32  marcelloptr
*improvement: multiline editor - scrollToSelection
*
*Revision 1.37  2003/08/09 02:56:46  ddiego
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
*Revision 1.36.2.3  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.36.2.2  2003/06/13 03:05:32  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.36.2.1  2003/05/27 04:45:34  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.36  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.35.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.35.2.1  2003/03/12 03:12:33  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.35  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.34.2.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.34.2.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.34.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.34  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.33.4.1  2002/11/16 19:37:47  ddiego
*this fixes bug [ 635840 ] Some control eat text events in Design mode.
*All that needed doing was adding an overridden handleEvents() to the TextControl
*and doing some moving around of code in the Win32Edit code.
*
*Revision 1.33  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.32.6.1  2002/09/05 21:49:44  ddiego
*added support for kevboard events in deleting a component and
*setting a property value
*some miscellaneous fixes
*some merges in the xmake makefiles for FK and GK
*
*Revision 1.32  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.31  2002/03/22 04:30:08  ddiego
*bug fixes for weird resizing of win32 common controls (it figures) with the
*new code I put in yesterday. Put back the old code and it seems to work OK.
*Sigh...
*
*Revision 1.30.4.2  2002/04/27 15:52:30  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.30.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.30  2002/03/03 20:04:11  ddiego
*fixed [ 525186 ] Weird cursor in edit box. EM_STREAMIN seem to reset the cursor back to the beginning
*fix was to set cursor pos after the text was set. The cursor is now positioned AFTER the set text.
*
*Revision 1.29  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.28  2002/02/07 16:11:27  ddiego
*fixed TextModel assignment for keyboard events (forgot to uncomment it from yesterday -
*dohh! )
*Added default setting for MultiLineTextControl's keepReturnCharacter_ (set to
*false to keep the enter key)
*
*Revision 1.27  2002/02/07 04:38:55  ddiego
*fixes to Win32Edit, which include problems with setting text, and a bug that
*caused it to crash in Win 98. All textControls now default to the "EDIT"
*window class unles they are multiline, in which case an attempt is made to
*load the richedit control, and if that fails then the EDIT class is used
*Removed responding to WM_COMMAND messages
*in the default parent in the Win32Toolkit, also to fix the Win32Edit crash in 9.x
*
*Revision 1.26  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


