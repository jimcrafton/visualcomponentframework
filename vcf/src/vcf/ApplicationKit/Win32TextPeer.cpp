//Win32TextPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32TextPeer.h"
#include "vcf/FoundationKit/Dictionary.h"

#include <Richedit.h>
#include <imm.h>
#include "thirdparty/win32/Microsoft/TOM.h"
#include <Richole.h>


#define DEFINE_GUIDXXX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID CDECL name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUIDXXX(IID_ITextDocument,0x8CC497C0,0xA1DF,0x11CE,0x80,0x98,
                0x00,0xAA,0x00,0x47,0xBE,0x5D);



const IID IID_ITextServices = { // 8d33f740-cf58-11ce-a89d-00aa006cadc5
    0x8d33f740,
    0xcf58,
    0x11ce,
    {0xa8, 0x9d, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
  };

const IID IID_ITextHost = { // c5bdd8d0-d26e-11ce-a89e-00aa006cadc5
    0xc5bdd8d0,
    0xd26e,
    0x11ce,
    {0xa8, 0x9e, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5}
  };


#include "thirdparty/win32/Microsoft/textserv.h"


static PCreateTextServices CreateTextServicesFunc;


using namespace VCF;







class TextHost : public ITextHost {
public:

	HWND hwnd_;
	PARAFORMAT paraFmt_;
	CHARFORMATW charFmt_;
	bool wrapLines_;
	bool multiLines_;

	TextHost(bool wrapLines, bool multiLines ) {
		wrapLines_ = wrapLines;
		multiLines_ = multiLines ;
		memset(&paraFmt_,0,sizeof(paraFmt_)) ;
		paraFmt_.cbSize = sizeof(paraFmt_);
		paraFmt_.dwMask = PFM_ALL;
		paraFmt_.wAlignment = PFA_LEFT;

		Font font;


		memset(&charFmt_,0,sizeof(charFmt_)) ;
		charFmt_.cbSize = sizeof(charFmt_);

		charFmt_.yHeight = font.getPointSize();


		charFmt_.yOffset = 0;
		charFmt_.crTextColor = font.getColor()->getColorRef32();


		charFmt_.dwEffects = CFM_EFFECTS | CFE_AUTOBACKCOLOR;
		charFmt_.dwEffects &= ~(CFE_PROTECTED | CFE_LINK | CFE_AUTOCOLOR);

		charFmt_.dwEffects &= ~CFE_BOLD;
		charFmt_.dwEffects &= ~CFE_ITALIC;
		charFmt_.dwEffects &= ~CFE_UNDERLINE;
		charFmt_.dwEffects &= ~CFE_STRIKEOUT;

		if ( font.getBold() ) {
			charFmt_.dwEffects |= CFE_BOLD;
		}

		if ( font.getItalic() ) {
			charFmt_.dwEffects |= CFE_ITALIC;
		}

		if ( font.getStrikeOut() ) {
			charFmt_.dwEffects |= CFE_STRIKEOUT;
		}

		if ( font.getUnderlined() ) {
			charFmt_.dwEffects |= CFE_UNDERLINE;
		}


		charFmt_.dwMask = CFM_ALL | CFM_BACKCOLOR | CFM_STYLE;
		charFmt_.bCharSet = DEFAULT_CHARSET;

		charFmt_.bPitchAndFamily = FF_DONTCARE;

		String fntName = font.getName();
		fntName.copy( charFmt_.szFaceName, fntName.size() );
	}

	STDMETHODIMP QueryInterface( REFIID iid, void ** ppvObject ) {
		String uuidStr;

		if ( iid == IID_ITextHost ) {
			*ppvObject = (void*) (ITextHost*)this;
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

	//@cmember Get the DC for the host
	HDC TxGetDC() {
		return GetDC( hwnd_ );
	}

	//@cmember Release the DC gotten from the host
	INT TxReleaseDC(HDC hdc) {
		return ReleaseDC( hwnd_, hdc );
	}

	//@cmember Show the scroll bar
	BOOL TxShowScrollBar(INT fnBar, BOOL fShow) {
		return FALSE;
	}

	//@cmember Enable the scroll bar
	BOOL TxEnableScrollBar (INT fuSBFlags, INT fuArrowflags) {
		return FALSE;
	}

	//@cmember Set the scroll range
	BOOL TxSetScrollRange(
							INT fnBar,
							LONG nMinPos,
							INT nMaxPos,
							BOOL fRedraw) {
		return FALSE;
	}

	//@cmember Set the scroll position
	BOOL TxSetScrollPos (INT fnBar, INT nPos, BOOL fRedraw) {
		return FALSE;
	}

	//@cmember InvalidateRect
	void TxInvalidateRect(LPCRECT prc, BOOL fMode) {
		InvalidateRect( hwnd_, prc, fMode );
	}

	//@cmember Send a WM_PAINT to the window
	void TxViewChange(BOOL fUpdate) {

	}

	//@cmember Create the caret
	BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight) {
		StringUtils::trace( "TxCreateCaret\n" );
		return ::CreateCaret( hwnd_, hbmp, xWidth, yHeight );
		//return FALSE;
	}

	//@cmember Show the caret
	BOOL TxShowCaret(BOOL fShow) {
		StringUtils::trace( "TxShowCaret\n" );
		if ( fShow ) {
			::ShowCaret( hwnd_ );
		}
		else {
			::HideCaret( hwnd_ );
		}
		return FALSE;
	}

	//@cmember Set the caret position
	BOOL TxSetCaretPos(INT x, INT y) {
		StringUtils::trace( "TxSetCaretPos\n" );
		return ::SetCaretPos( x, y );
		//return FALSE;
	}

	//@cmember Create a timer with the specified timeout
	BOOL TxSetTimer(UINT idTimer, UINT uTimeout) {
		StringUtils::trace( "TxSetTimer\n" );
		return SetTimer( hwnd_, idTimer, uTimeout, NULL );
	}

	//@cmember Destroy a timer
	void TxKillTimer(UINT idTimer) {
		StringUtils::trace( "KillTimer\n" );
		KillTimer( hwnd_, idTimer );
	}

	//@cmember Scroll the content of the specified window's client area
	void TxScrollWindowEx (
							INT dx,
							INT dy,
							LPCRECT lprcScroll,
							LPCRECT lprcClip,
							HRGN hrgnUpdate,
							LPRECT lprcUpdate,
							UINT fuScroll) {

	}

	//@cmember Get mouse capture
	void TxSetCapture(BOOL fCapture) {
		StringUtils::trace( "TxSetCapture\n" );
		if ( fCapture ) {
			SetCapture( hwnd_ );
		}
		else {
			ReleaseCapture();
		}
	}

	//@cmember Set the focus to the text window
	void TxSetFocus() {
		StringUtils::trace( "TxSetFocus\n" );
		SetFocus( hwnd_ );
	}

	//@cmember Establish a new cursor shape
	void TxSetCursor(HCURSOR hcur, BOOL fText) {
		StringUtils::trace( "TxSetCursor\n" );
		SetCursor( hcur );
	}

	//@cmember Converts screen coordinates of a specified point to the client coordinates
	BOOL TxScreenToClient (LPPOINT lppt) {
		return ScreenToClient( hwnd_, lppt );
	}

	//@cmember Converts the client coordinates of a specified point to screen coordinates
	BOOL TxClientToScreen (LPPOINT lppt) {
		return ClientToScreen( hwnd_, lppt );
	}

	//@cmember Request host to activate text services
	HRESULT TxActivate( LONG * plOldState ) {
		return S_OK;
	}

	//@cmember Request host to deactivate text services
   	HRESULT TxDeactivate( LONG lNewState ){
		return S_OK;
	}

	//@cmember Retrieves the coordinates of a window's client area
	HRESULT TxGetClientRect(LPRECT prc){
		GetClientRect( hwnd_, prc );
		return S_OK;
	}

	//@cmember Get the view rectangle relative to the inset
	HRESULT TxGetViewInset(LPRECT prc){
		prc->left = 0;
		prc->right = 0;
		prc->top = 100;
		prc->bottom = 55;
		return S_OK;
	}

	//@cmember Get the default character format for the text
	HRESULT TxGetCharFormat(const CHARFORMATW **ppCF ){

		*ppCF = &charFmt_;

		return S_OK;
	}

	//@cmember Get the default paragraph format for the text
	HRESULT TxGetParaFormat(const PARAFORMAT **ppPF){
		*ppPF = &paraFmt_;

		return S_OK;
	}

	//@cmember Get the background color for the window
	COLORREF TxGetSysColor(int nIndex){
		return GetSysColor( nIndex );
	}

	//@cmember Get the background (either opaque or transparent)
	HRESULT TxGetBackStyle(TXTBACKSTYLE *pstyle) {
		*pstyle = TXTBACK_TRANSPARENT;
		return S_OK;
	}

	//@cmember Get the maximum length for the text
	HRESULT TxGetMaxLength(DWORD *plength){
		*plength = INFINITE;
		return S_OK;
	}

	//@cmember Get the bits representing requested scroll bars for the window
	HRESULT TxGetScrollBars(DWORD *pdwScrollBar){
		pdwScrollBar = 0;
		return S_OK;
	}

	//@cmember Get the character to display for password input
	HRESULT TxGetPasswordChar(TCHAR *pch){
		return S_FALSE;
	}

	//@cmember Get the accelerator character
	HRESULT TxGetAcceleratorPos(LONG *pcp){
		*pcp = -1;
		return S_OK;
	}

	//@cmember Get the native size
    HRESULT TxGetExtent(LPSIZEL lpExtent){
		return E_NOTIMPL;
	}

	//@cmember Notify host that default character format has changed
	HRESULT OnTxCharFormatChange (const CHARFORMATW * pcf){
		memcpy(&charFmt_, pcf, pcf->cbSize);
		return S_OK;
	}

	//@cmember Notify host that default paragraph format has changed
	HRESULT OnTxParaFormatChange (const PARAFORMAT * ppf){
		memcpy(&paraFmt_, ppf, ppf->cbSize);
		return S_OK;
	}

	//@cmember Bulk access to bit properties
	HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits){

		DWORD bits = *pdwBits;


		bits = TXTBIT_RICHTEXT | TXTBIT_USECURRENTBKG;

		if ( wrapLines_ ) {
			bits |= TXTBIT_WORDWRAP;
		}

		if ( multiLines_ ) {
			bits |= TXTBIT_MULTILINE;
		}

		*pdwBits = bits;
		return S_OK;
	}

	//@cmember Notify host of events
	HRESULT TxNotify(DWORD iNotify, void *pv){
		return S_OK;
	}

	// Far East Methods for getting the Input Context
//#ifdef WIN95_IME
	virtual HIMC TxImmGetContext(){
		return NULL;
	}

	void TxImmReleaseContext( HIMC himc ) {

	}
//#endif

	//@cmember Returns HIMETRIC size of the control bar.
	HRESULT TxGetSelectionBarWidth (LONG *lSelBarWidth) {
		*lSelBarWidth = 0;
		return S_OK;
	}

};












Win32TextPeer::Win32TextPeer( const bool& autoWordWrap, const bool& multiLined ):
	host_(NULL),
	textSvcs_(NULL),
	textDocument_(NULL)
{
	static bool initializedWin32TextPeer = false;

	if ( !initializedWin32TextPeer ) {
		//load up the Riched20.dll

		HINSTANCE riched20 = LoadLibraryA( "Riched20.dll" );

		if ( NULL == riched20 ) {
			throw RuntimeException( "Riched20.dll not found on this system! Can't create Text Peer implementation!" );
		}

		CreateTextServicesFunc = (PCreateTextServices) GetProcAddress( riched20, "CreateTextServices" );

		if ( NULL == CreateTextServicesFunc ) {
			throw RuntimeException( "Riched20.dll found but apparently it does not export the CreateTextServices function. Can't create Text Peer implementation!" );
		}
	}

	initializedWin32TextPeer = true;


	host_ = new TextHost(autoWordWrap,multiLined);

	IUnknown* unk = NULL;
	CreateTextServicesFunc( NULL, host_, &unk );

	unk->QueryInterface( IID_ITextServices, (void**)&textSvcs_ );

	if ( NULL == textSvcs_ ) {
		throw RuntimeException( "Unable to get ITextServices interface! Can't create Text Peer implementation!" );
	}

	textSvcs_->AddRef();

	unk->QueryInterface( IID_ITextDocument, (void**)&textDocument_ );

	if ( NULL == textDocument_ ) {
		throw RuntimeException( "Unable to get ITextDocument interface! Can't create Text Peer implementation!" );
	}

	textDocument_->AddRef();

	unk->Release();
}

Win32TextPeer::Win32TextPeer():
	host_(NULL),
	textSvcs_(NULL),
	textDocument_(NULL)
{


}

Win32TextPeer::~Win32TextPeer()
{
	if ( NULL != textSvcs_ ) {
		textSvcs_->Release();
	}

	if ( NULL != textDocument_ ) {
		textDocument_->Release();
	}

	delete host_;
}


void Win32TextPeer::initFromRichEdit( HWND hwnd )
{
	//extract the TOM interfaces!
	IUnknown* unk = NULL;
	::SendMessage( hwnd, EM_GETOLEINTERFACE, 0, (LPARAM)&unk );

	if ( NULL == unk ) {
		throw RuntimeException( "Unable to retrieve IUnknown interface from edit control." );
	}

	unk->QueryInterface( IID_ITextDocument, (void**)&textDocument_ );

	if ( NULL == textDocument_ ) {
		throw RuntimeException( "Unable to get ITextDocument interface! Can't create Text Peer implementation!" );
	}

	textDocument_->AddRef();

	unk->QueryInterface( IID_ITextServices, (void**)&textSvcs_ );

	if ( NULL == textSvcs_ ) {
		throw RuntimeException( "Unable to get ITextServices interface! Can't create Text Peer implementation!" );
	}

	textSvcs_->AddRef();

	unk->Release();
}

void Win32TextPeer::initHostDefaultStyle( Font* font )
{
	String name = font->getName();
	name.copy( host_->charFmt_.szFaceName, name.size() );

	Color* color = font->getColor();
	host_->charFmt_.crTextColor = color->getColorRef32();


	host_->charFmt_.yHeight = font->getPointSize();

	if ( font->getBold() ) {
		host_->charFmt_.dwEffects |= CFE_BOLD;
	}
	else {
		host_->charFmt_.dwEffects &= ~CFE_BOLD;
	}


	if ( font->getUnderlined() ) {
		host_->charFmt_.dwEffects |= CFE_ITALIC;
	}
	else {
		host_->charFmt_.dwEffects &= ~CFE_ITALIC;
	}

	if ( font->getStrikeOut() ) {
		host_->charFmt_.dwEffects |= CFE_STRIKEOUT;
	}
	else {
		host_->charFmt_.dwEffects &= ~CFE_STRIKEOUT;
	}

	if ( font->getUnderlined() ) {
		host_->charFmt_.dwEffects &= ~CFE_UNDERLINE;
	}
	else {
		host_->charFmt_.dwEffects |= CFE_UNDERLINE;
	}

}

OSHandleID Win32TextPeer::getTextObjectHandle()
{
	OSHandleID result ;

	IUnknown* unk = (IUnknown*)textDocument_;

	result = (OSHandleID) unk;

	return result;
}

//storage
void Win32TextPeer::insertText( unsigned int start, const String& text )
{
	ITextRange* range;
	textDocument_->Range( start, start, &range );
	if ( NULL != range ) {
		BSTR str = SysAllocStringLen( text.c_str(), text.length() );

		HRESULT hr = range->SetText( str );

		SysFreeString( str );

		range->Release();
	}
}

void Win32TextPeer::deleteText( unsigned int start, unsigned int length )
{
	ITextRange* range;
	textDocument_->Range( start, start+length, &range );
	if ( NULL != range ) {

		HRESULT hr = range->Delete( tomCharacter, 0, NULL );

		range->Release();
	}
}

unsigned int Win32TextPeer::getTextLength()
{
	unsigned int result = 0;
	ITextRange* range;
	textDocument_->Range( 0, 0, &range );
	if ( NULL != range ) {
		long len = 0;
		range->GetStoryLength( &len );

		result = len;

		range->Release();
	}

	return result;
}

String Win32TextPeer::getText( unsigned int start, unsigned int length )
{
	String result;
	ITextRange* range;
	textDocument_->Range( start, start+length, &range );
	if ( NULL != range ) {
		BSTR str = SysAllocString( NULL );
		range->GetText( &str );

		result.assign( str, SysStringLen(str) );

		SysFreeString( str );

		range->Release();
	}
	return result;
}

void Win32TextPeer::paint( GraphicsContext* context, const Rect& paintRect )
{
	HDC dc = (HDC)context->getPeer()->getContextID();

	RECTL rect;
	rect.left = paintRect.left_ + margins_.left_;
	rect.top = paintRect.top_ + margins_.top_;
	rect.right = paintRect.right_ - margins_.right_;
	rect.bottom = paintRect.bottom_ - margins_.bottom_;

	textSvcs_->TxDraw(
						DVASPECT_CONTENT,  		// Draw Aspect
						0,						// Lindex
						NULL,					// Info for drawing optimization
						NULL,					// target device information
						dc,				// Draw device HDC
						0,			 	   	// Target device HDC
						(RECTL*) &rect,			// Bounding client rectangle
						NULL,					// Clipping rectangle for metafiles
						NULL,			// Update rectangle
						NULL, 	   				// Call back function
						NULL,					// Call back parameter
						TXTVIEW_INACTIVE);		// What view of the object could be TXTVIEW_ACTIVE

}

void Win32TextPeer::setRightMargin( const double & rightMargin )
{
	margins_.right_ = rightMargin;
}

void Win32TextPeer::setLeftMargin( const double & leftMargin )
{
	margins_.left_ = leftMargin;
}

void Win32TextPeer::setTopMargin( const double & topMargin )
{
	margins_.top_ = topMargin;
}

void Win32TextPeer::setBottomMargin( const double & bottomMargin )
{
	margins_.bottom_ = bottomMargin;
}

double Win32TextPeer::getLeftMargin()
{
	return margins_.left_;
}

double Win32TextPeer::getRightMargin()
{
	return margins_.right_;
}

double Win32TextPeer::getTopMargin()
{
	return margins_.top_;
}

double Win32TextPeer::getBottomMargin()
{
	return margins_.bottom_;
}

unsigned long Win32TextPeer::getLineCount()
{
	unsigned long result = 0;
	ITextRange* range = NULL;
	textDocument_->Range( 0, 0, &range );
	if ( NULL != range ) {
		long len = 0;
		range->GetStoryLength( &len );
		range->SetEnd ( len );
		HRESULT hr = range->MoveStart( tomLine, 1, NULL );
		while ( S_OK == hr ) {
			result ++;
			hr = range->MoveStart( tomLine, 1, NULL );
		}

		range->Release();
	}

	return result;
}

Rect Win32TextPeer::getContentBoundsForWidth(const double& width)
{
	Rect result;
	long w;
	long h;
	w = width;
	h = 1;
	SIZEL sz;
	sz.cx = w;
	sz.cy = h;

	HDC dc = GetDC( GetDesktopWindow() );
	HRESULT hr = textSvcs_->TxGetNaturalSize( DVASPECT_CONTENT, dc, NULL, NULL,
								TXTNS_FITTOCONTENT, &sz, &w, &h );

	ReleaseDC( GetDesktopWindow(), dc );

	result.bottom_ = result.top_ + h;
	result.right_ = result.left_ + w;


	return result;
}

void Win32TextPeer::getStyle( unsigned int start, unsigned int length, Dictionary& styles, Color& color )
{
	String result;
	ITextRange* range = NULL;
	textDocument_->Range( start, start+length, &range );
	if ( NULL != range ) {
		ITextFont* font = NULL;
		ITextPara* para = NULL;
		range->GetFont( &font );
		range->GetPara( &para );

		if ( (NULL != font) && (NULL != para) ) {
			BSTR str = SysAllocString( NULL );
			styles[ Text::fsFontName ] = font->GetName( &str );
			SysFreeString( str );

			long val;

			font->GetForeColor( &val );
			color.setColorRef32( val );
			styles[ Text::fsColor ] = (Object*)&color; // color cannot be a temporary

			float size = 0;
			font->GetSize( &size );
			styles[ Text::fsPointSize ] = (double)size;

			font->GetBold( &val );
			styles[ Text::fsBold ] = ( tomTrue == val ) ? true : false;

			font->GetItalic( &val );
			styles[ Text::fsItalic ] = ( tomTrue == val ) ? true : false;

			font->GetStrikeThrough( &val );
			styles[ Text::fsStrikeout ] = ( tomTrue == val ) ? true : false;

			Text::UnderlineTypes underline = Text::utNone;
			font->GetUnderline( &val );
			switch ( (int)val ) {
				case tomNone : {
					underline = Text::utNone;
				}
				break;

				case tomSingle : {
					underline = Text::utSingle;
				}
				break;

				case tomDouble : {
					underline = Text::utDouble;
				}
				break;

				case tomDotted : {
					underline = Text::utDotted;
				}
				break;
			}
			styles[ Text::fsUnderlined ] = underline;


			font->Release();
		}

		if ( NULL != para ) {
			Text::ParagraphAlignment alignment = Text::paLeft;
			long val = 0;
			para->GetAlignment( &val );

			switch ( (int)val ) {
				case tomAlignLeft : {
					alignment = Text::paLeft;
				}
				break;

				case tomAlignCenter : {
					alignment = Text::paCenter;
				}
				break;

				case tomAlignRight : {
					alignment = Text::paRight;
				}
				break;

				case tomAlignJustify : {
					alignment = Text::paJustified;
				}
				break;
			}
			styles[ Text::psAlignment ] = alignment;


			para->Release();
		}

		range->Release();
	}
}

void Win32TextPeer::setStyle( unsigned int start, unsigned int length, Dictionary& styles )
{
	String result;
	ITextRange* range = NULL;
	textDocument_->Range( start, start+length, &range );
	if ( NULL != range ) {
		ITextFont* font = NULL;
		ITextPara* para = NULL;
		range->GetFont( &font );
		range->GetPara( &para );

		Dictionary::Enumerator* items = styles.getEnumerator();

		if ( (NULL != font) && (NULL != para) ) {
			while ( items->hasMoreElements() ) {
				Dictionary::pair style = items->nextElement();

				if ( style.first == Text::fsFontName ) {
					String s = style.second;
					BSTR name = SysAllocStringLen( s.c_str(), s.length() );
					font->SetName( name );
					SysFreeString( name );
				}
				else if ( style.first == Text::fsColor ) {
					Color* color = (Color*)(Object*)style.second;
					VCF_ASSERT( NULL != color );

					font->SetForeColor( color->getColorRef32() );

				}
				else if ( style.first == Text::fsPointSize ) {

					double val = style.second;
					font->SetSize( val );
				}
				else if ( style.first == Text::fsBold ) {
					long val = ((bool)style.second) ? tomTrue : tomFalse;
					font->SetBold( val );
				}
				else if ( style.first == Text::fsItalic ) {
					long val = ((bool)style.second) ? tomTrue : tomFalse;
					font->SetItalic( val );
				}
				else if ( style.first == Text::fsStrikeout ) {
					long val = ((bool)style.second) ? tomTrue : tomFalse;
					font->SetStrikeThrough( val );
				}
				else if ( style.first == Text::fsUnderlined ) {
					long val = tomNone;
					switch ( (int)style.second ) {
						case Text::utNone : {
							val = tomNone;
						}
						break;

						case Text::utSingle : {
							val = tomSingle;
						}
						break;

						case Text::utDouble : {
							val = tomDouble;
						}
						break;

						case Text::utDotted : {
							val = tomDotted;
						}
						break;
					}
					font->SetUnderline( val );
				}
				else if ( style.first == Text::psAlignment ) {
					int alignment = style.second;

					long val = 0;

					switch ( alignment ) {
						case Text::paLeft : {
							val = tomAlignLeft;
						}
						break;

						case Text::paCenter : {
							val = tomAlignCenter;
						}
						break;

						case Text::paRight : {
							val = tomAlignRight;
						}
						break;

						case Text::paJustified : {
							val = tomAlignJustify;
						}
						break;
					}
					para->SetAlignment( val );
				}
			}

			para->Release();
			font->Release();
		}

		range->Release();
	}
}

void Win32TextPeer::setDefaultStyle( Dictionary&  styles )
{
	if ( NULL == host_ ) {
		return;
	}


	Dictionary::Enumerator* items = styles.getEnumerator();

	while ( items->hasMoreElements() ) {
		Dictionary::pair style = items->nextElement();

		if ( style.first == Text::fsFontName ) {
			String s = style.second;
			s.copy( host_->charFmt_.szFaceName, s.size() );
		}
		else if ( style.first == Text::fsColor ) {
			Color* color = (Color*)(Object*)style.second;
			VCF_ASSERT( NULL != color );

			host_->charFmt_.crTextColor = color->getColorRef32();
		}
		else if ( style.first == Text::fsPointSize ) {
			double val = style.second;
			host_->charFmt_.yHeight = val;
		}
		else if ( style.first == Text::fsBold ) {
			if ( (bool)style.second ) {
				host_->charFmt_.dwEffects |= CFE_BOLD;
			}
			else {
				host_->charFmt_.dwEffects &= ~CFE_BOLD;
			}
		}
		else if ( style.first == Text::fsItalic ) {
			if ( (bool)style.second ) {
				host_->charFmt_.dwEffects |= CFE_ITALIC;
			}
			else {
				host_->charFmt_.dwEffects &= ~CFE_ITALIC;
			}
		}
		else if ( style.first == Text::fsStrikeout ) {
			if ( (bool)style.second ) {
				host_->charFmt_.dwEffects |= CFE_STRIKEOUT;
			}
			else {
				host_->charFmt_.dwEffects &= ~CFE_STRIKEOUT;
			}
		}
		else if ( style.first == Text::fsUnderlined ) {
			int underline = style.second;
			if ( Text::utNone == underline ) {
				host_->charFmt_.dwEffects &= ~CFE_UNDERLINE;
			}
			else {
				host_->charFmt_.dwEffects |= CFE_UNDERLINE;
			}
		}
		else if ( style.first == Text::psAlignment ) {
			int alignment = style.second;

			switch ( alignment ) {
				case Text::paLeft : {
					host_->paraFmt_.wAlignment = PFA_LEFT;
				}
				break;

				case Text::paCenter : {
					host_->paraFmt_.wAlignment = PFA_CENTER;
				}
				break;

				case Text::paRight : {
					host_->paraFmt_.wAlignment = PFA_RIGHT;
				}
				break;

				case Text::paJustified : {
					//not supported!
					//host_->paraFmt_.wAlignment = PFA_RIGHT;
				}
				break;
			}
		}
	}

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.12  2005/07/05 03:34:35  marcelloptr
*minor bug fixed
*
*Revision 1.1.2.11  2005/06/26 01:31:20  marcelloptr
*improvements to the Color class. The default, when packing the components into a single integer, is now cpsARGB instead than cpsABGR.
*
*Revision 1.1.2.10  2005/06/25 19:50:49  marcelloptr
*forgotten MP mark
*
*Revision 1.1.2.9  2005/06/09 07:18:25  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.1.2.6  2005/06/07 17:31:29  marcelloptr
*added missed getStyle() function. Fixed underline text that couldn't be removed once introduced.
*
*/


