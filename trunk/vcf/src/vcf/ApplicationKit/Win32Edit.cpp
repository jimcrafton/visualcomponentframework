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
#include <richedit.h>


using namespace VCFWin32;
using namespace VCF;

static bool Win32RicheditLibraryLoaded = false;

Win32Edit::Win32Edit( TextControl* component, const bool& isMultiLineControl ):
	AbstractWin32Component( component ),	
	textControl_(component),
	numCharsRemainingToStreamIn_(0),
	isRichedit_(false),
	OKToResetControlText_(true),
	backgroundBrush_(NULL),
	isMultiLined_(isMultiLineControl),
	currentSelLength_(0),
	currentSelStart_(-1)
{

}

Win32Edit::~Win32Edit()
{
	if ( NULL != backgroundBrush_ ) {
		DeleteObject( backgroundBrush_ );
	}
}

void Win32Edit::create( Control* owningControl )
{

	if ( NULL == textControl_ ){
		//throw exception !!!!!!
	}
	createParams();

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = "EDIT";
	AnsiString richeditLibrary = "";

	OSVERSIONINFO osInfo;
	memset( &osInfo, 0, sizeof(OSVERSIONINFO) );
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if ( true == isMultiLined_ ) {
		if ( GetVersionEx( &osInfo ) ) {
			if ( osInfo.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
				richeditLibrary = "RICHED20.Dll";
				if ( System::isUnicodeEnabled() ) {
					className = RICHEDIT_CLASSW;
				}
				else {
					className = RICHEDIT_CLASSA;
				}
			}
			else if ( osInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) { //Windows 9.x
				richeditLibrary = "RICHED32.DLL";
				className = "RichEdit";
			}
		}


		try {
			if ( false == Win32RicheditLibraryLoaded ) {
				if  ( NULL != LoadLibraryA( richeditLibrary.c_str() ) ) {
					Win32RicheditLibraryLoaded = true;
					isRichedit_ = true;
				}
				else {
					String errMsg =
						StringUtils::format( "Failed to load \"%s\", a required DLL when using richedit controls. \n"\
						"Please make sure this DLL is located in your Windows system, or application directory.",
						richeditLibrary.c_str() );

					throw RuntimeException( errMsg );
				}
			}
		}
		catch (...) {
			//we couldn't load the richedit libraries so lets downgrade to the default edit control
			className = "EDIT";
			isRichedit_ = false;
		}
	}

	
	styleMask_ &= ~WS_VISIBLE;
	DWORD style = styleMask_ | ES_AUTOHSCROLL | ES_SAVESEL | ES_NOHIDESEL;
	if ( true == isMultiLined_ ) {
		style |= ES_MULTILINE | WS_HSCROLL | WS_VSCROLL;// | ES_WANTRETURN;
	}

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( exStyleMask_,
		                             className.c_str(),
									 NULL,
									 style,
		                             0,
									 0,
									 1,
									 CW_USEDEFAULT,
									 parent,
									 NULL,
									 ::GetModuleHandleW(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( exStyleMask_,
		                             className.ansi_c_str(),
									 NULL,
									 style,
		                             0,
									 0,
									 1,
									 CW_USEDEFAULT,
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}




	if ( NULL != hwnd_ ){

		Win32Object::registerWin32Object( this );
		
		subclassWindow();
		
		setFont( textControl_->getFont() );

		textControl_->ControlModelChanged +=
			new GenericEventHandler<Win32Edit>( this, &Win32Edit::onControlModelChanged, "Win32Edit::onControlModelChanged" );

	}
	else {
		//throw exception
		throw RuntimeException( "Runtime Exception: " + Win32Utils::getErrorString( ::GetLastError() ) );
	}

	setCreated( true );
}

void Win32Edit::setRightMargin( const double & rightMargin )
{
	::SendMessage( hwnd_, EM_SETMARGINS, EC_RIGHTMARGIN, (long)rightMargin );
}

void Win32Edit::setLeftMargin( const double & leftMargin )
{
	::SendMessage( hwnd_, EM_SETMARGINS, EC_LEFTMARGIN, (long)leftMargin );
}

unsigned long Win32Edit::getLineCount()
{
	return ::SendMessage( hwnd_, EM_GETLINECOUNT, 0, 0 );
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

void Win32Edit::createParams()
{
	exStyleMask_ = 0;
	styleMask_ = SIMPLE_VIEW;
	styleMask_ &= ~WS_BORDER;
}

void Win32Edit::processTextEvent( VCFWin32::KeyboardData keyData, WPARAM wParam, LPARAM lParam )
{
	VCF::TextModel* model = textControl_->getTextModel();
	if ( NULL != model ){
		//this is the braindead way - needs to be reworked in the future

		VCF::String newText;

		if ( System::isUnicodeEnabled() ) {
			int length = ::GetWindowTextLengthW( hwnd_ );

			VCFChar* text = new VCFChar[length+1];
			memset( text, 0, (length+1)*sizeof(VCFChar));
			::GetWindowTextW( hwnd_, text, length+1 );

			newText = text;

			delete[] text;
		}
		else {
			int length = ::GetWindowTextLengthA( hwnd_ );

			char* text = new char[length+1];
			memset( text, 0, length+1);
			::GetWindowTextA( hwnd_, text, length+1 );

			newText = text;

			delete[] text;
		}




		OKToResetControlText_ = false;

		model->setText( newText );

		OKToResetControlText_ = true;



		/**
		*for the future we need to be able to insertText and deleteText from the
		*model according to the characters pressed. At first glance this is that
		*big of a deal: determine if we have a selection, delete the selected
		*text, and then insert the appropriate character. The problem comes in
		*determing what causes a delete and what to insert. Normally the only things
		*that should cause an delete/insert are the set of characters [a..z,A..Z,0..9],
		*back space, space, and delete. This is a valid assumption assuming en/US language
		*but for other languages this totally falls down...
		*/

		/*
		//figure out if anything is selected
		int selStart = 0;
		int selEnd = 0;
		::SendMessage( hwnd_, EM_GETSEL, (WPARAM)&selStart, (LPARAM)&selEnd );
		int delta = abs( selStart - selEnd );
		if ( 0 != delta ){
			//text is being deleted

			if ( (keyData.VKeyCode != VK_BACK) || (keyData.VKeyCode == VK_BACK) ){

			}
		}


		unsigned long index = peerControl_->getCaretPosition();
		VCF::String text;
		char ch[2] = {0};
		ch[0] = (VCF::VCFChar)keyData.character;
		text += ch;
		model->insertText( index, text );
		*/
	}
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

		case WM_RBUTTONUP : case WM_LBUTTONUP : {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

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
			
			ulong32 virtKeyCode = Win32Utils::translateVKCode( wParam );

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

				KeyboardData keyData = Win32Utils::translateKeyData( hwnd_, lParam );
				unsigned long eventType = Control::KEYBOARD_DOWN;
				

				unsigned long keyMask = Win32Utils::translateKeyMask( keyData.keyMask );

				virtKeyCode = Win32Utils::translateVKCode( keyData.VKeyCode );

				VCF::KeyboardEvent event( peerControl_, eventType, keyData.repeatCount,
					keyMask, (VCF::VCFChar)keyData.character, (VirtualKeyCode)virtKeyCode );

				OKToResetControlText_ = false;
				
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
				

				OKToResetControlText_ = true;

				//wndProcResult = 1;
				result = true;
			}

			if ( !(peerControl_->getComponentState() & Component::csDesigning) ) {
				wndProcResult = defaultWndProcedure(  message, wParam, lParam );
				result = true;
			}


		}
		break;

		case WM_CHAR:  case WM_KEYUP:{

			
			if ( !(peerControl_->getComponentState() & Component::csDesigning) ) {
				wndProcResult = defaultWndProcedure(  message, wParam, lParam );
				result = true;
			}

			if ( (peerControl_->getComponentState() != Component::csDestroying) ) {

				KeyboardData keyData = Win32Utils::translateKeyData( hwnd_, lParam );
				unsigned long eventType = 0;
				switch ( message ){
					case WM_CHAR: {
						eventType = Control::KEYBOARD_PRESSED;
					}
					break;
					
					case WM_KEYUP: {
						eventType = Control::KEYBOARD_UP;
					}
					break;
				}

				unsigned long keyMask = Win32Utils::translateKeyMask( keyData.keyMask );
				ulong32 virtKeyCode = Win32Utils::translateVKCode( keyData.VKeyCode );
				VCF::KeyboardEvent event( peerControl_, eventType, keyData.repeatCount,
					keyMask, (VCF::VCFChar)keyData.character, (VirtualKeyCode)virtKeyCode );

				OKToResetControlText_ = false;
				
				peerControl_->handleEvent( &event );

				OKToResetControlText_ = true;
				
				result = true;
			}

		}
		break;
		
		case WM_COMMAND:{
			
			WPARAM fakeWParam = LOWORD(wParam);

			
			wndProcResult = 0;
			result = true;

			switch ( HIWORD(wParam) ) {
				case EN_UPDATE:{
					
					// 

					OKToResetControlText_ = false;

					VCF::TextModel* model = textControl_->getTextModel();
					if ( NULL != model ) {
						
					}

					OKToResetControlText_ = true;
				}
				break; 

				default : {

				}
				break;
			}

		}
		break;

		

		case WM_PASTE : {
			wndProcResult = 0;
			result = false;

			OKToResetControlText_ = false;		

			if ( !(peerControl_->getComponentState() & Component::csDesigning) ) {
				wndProcResult = defaultWndProcedure(  message, wParam, lParam );
				result = true;
			}

			VCF::TextModel* model = textControl_->getTextModel();
			if ( NULL != model ) {
				String text = getText();
				if ( text != model->getText() ) {
					model->setText( text );
				}
			}

			OKToResetControlText_ = true;
			
		}
		break;

		case WM_ERASEBKGND :{
			wndProcResult = 1;
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

			COLORREF backColor = RGB(color->getRed() * 255.0,
									color->getGreen() * 255.0,
									color->getBlue() * 255.0 );

			backgroundBrush_ = CreateSolidBrush( backColor );
			SetBkColor( hdcEdit, backColor );

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
		

		default: {				
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;		
	}
	
	return result;
}

void Win32Edit::onTextModelTextChanged( TextEvent* event )
{
	if ( NULL != event ){
		if ( true == OKToResetControlText_ ){

			String text = textControl_->getTextModel()->getText();

			setText( text );		

		}
	}
}

DWORD CALLBACK Win32Edit::EditStreamCallback( DWORD dwCookie, // application-defined value
												LPBYTE pbBuff,  // pointer to a buffer
												LONG cb,        // number of bytes to read or write
												LONG *pcb       // pointer to number of bytes transferred
												)
{

	Win32Edit* thisPtr = (Win32Edit*)dwCookie;
	*pcb = 0;
	TextControl* tc = (TextControl*)thisPtr->getControl();
	String text = tc->getTextModel()->getText();
	if ( (text.size()-1) > thisPtr->numCharsRemainingToStreamIn_ ) {

		memset( pbBuff, 0, cb );

		if ( System::isUnicodeEnabled() ) {
			*pcb = text.copy( (VCFChar*)pbBuff, cb / sizeof(VCFChar), thisPtr->numCharsRemainingToStreamIn_ ) * sizeof(VCFChar);
		}
		else{
			AnsiString tmp = text;

			*pcb = tmp.copy( (char*)pbBuff, cb, thisPtr->numCharsRemainingToStreamIn_ );
		}


		thisPtr->numCharsRemainingToStreamIn_ += *pcb;
	}

	return 0;//(*pcb>0 ? NOERROR : E_FAIL);
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
	DWORD start = getSelectionStart();
	DWORD count = getSelectionCount();

	if ( isRichedit_ ) {
		EDITSTREAM editStream;
		memset( &editStream, 0, sizeof(EDITSTREAM) );
		editStream.dwCookie = (DWORD)this;
		editStream.pfnCallback = Win32Edit::EditStreamCallback;
		numCharsRemainingToStreamIn_ = 0;//text.size();

		int streamedIn = 0;
		if ( System::isUnicodeEnabled() ) {
			streamedIn = ::SendMessage( hwnd_, EM_STREAMIN, SF_TEXT | SF_UNICODE, (LPARAM)&editStream );
		}
		else{
			streamedIn = ::SendMessage( hwnd_, EM_STREAMIN, SF_TEXT, (LPARAM)&editStream );
		}
		int err = UpdateWindow( hwnd_ );
	}
	else {
		int err = 0;
		if ( System::isUnicodeEnabled() ) {		

			err = ::SetWindowTextW( hwnd_, text.c_str() );
		}
		else {
			err = ::SetWindowTextA( hwnd_, text.ansi_c_str() );
		}

		if ( !err ) {
			err = GetLastError();
			StringUtils::traceWithArgs( "error is %d\n", err );
		}
	}

	setSelectionMark( start, count );
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
	/**
	Bug fix from Marcello, EM_GETSEL doesn't handle
	CRLF's right
	*/

	// Note: we tested well that to use CHARRANGE chrg with a isRichedit_ control doesn't make any difference
	::SendMessage( hwnd_, EM_GETSEL, (WPARAM)&start, (LPARAM)&end );

	TextControl* tc = (TextControl*)this->getControl();
	String text = tc->getTextModel()->getText();
	unsigned long size = text.size();
	if ( size < start ) {
		start = size;
	}
	if ( size < end ) {
		end = size;
	}

	unsigned long count = end - start;
	unsigned long CRCount = getCRCount( 0, start, false );
	unsigned long realSelectionStart = start + CRCount;
	unsigned long CRCountSpan = 0;
	if ( end != -1 ) {
		// we need to see if the selection has some '\r' in it
		CRCountSpan = getCRCount( realSelectionStart, realSelectionStart + count, false );
	}
	start = realSelectionStart;
	end = realSelectionStart + count + CRCountSpan;

	if ( size < start ) {
		start = size;
	}
	if ( size < end ) {
		end = size;
	}
}

void Win32Edit::setSelectionMark( const unsigned long& start, const unsigned long& count )
{
	/**
	Bug fix from Marcello, EM_SETSEL doesn't like temporary vars as it's
	message parameters
	*/

	unsigned long end = start + count;

	int CRCount = getCRCount( 0, start, true );
	int CRCountSpan = getCRCount( start, end, true );	//fix 2004/01/14 was false before which gives error that seem almost random


	unsigned long adjustedStart = start - CRCount;
	unsigned long adjustedCount = count - CRCountSpan;
	end = adjustedStart + adjustedCount;

	// Remark:  to use EM_EXSETSEL with CHARRANGE doesn't work with a isRichedit_ control:
	//          both if we are using (adjustedStart, adjustedCount) or not. Anybody surprised ?
	::SendMessage( hwnd_, EM_SETSEL, (WPARAM)adjustedStart, (LPARAM)end );
}

void Win32Edit::setSelectionFont( Font* font )
{
	CHARFORMAT charFormat;
	memset( &charFormat, 0, sizeof(CHARFORMAT) );
	charFormat.cbSize = sizeof(CHARFORMAT);
	charFormat.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE | CFM_STRIKEOUT | CFM_UNDERLINE ;
	charFormat.yHeight = (long)(font->getPointSize() * 20.0);
	charFormat.crTextColor = RGB( font->getColor()->getRed() * 255.0,
									font->getColor()->getGreen() * 255.0,
									font->getColor()->getBlue() * 255.0 );

	font->getName().copy( charFormat.szFaceName, 31 );

	if ( true == font->getBold() ) {
		charFormat.dwEffects |= CFE_BOLD;
	}

	if ( true == font->getItalic() ) {
		charFormat.dwEffects |= CFE_ITALIC;
	}

	if ( true == font->getStrikeOut() ) {
		charFormat.dwEffects |= CFE_STRIKEOUT;
	}

	if ( true == font->getUnderlined() ) {
		charFormat.dwEffects |= CFE_UNDERLINE;
	}

	::SendMessage( hwnd_, EM_SETCHARFORMAT, (WPARAM)SCF_WORD | SCF_SELECTION, (LPARAM)&charFormat );
}

void Win32Edit::setParagraphAlignment( const TextAlignmentType& alignment )
{
	PARAFORMAT paragraphFormat;
	memset( &paragraphFormat, 0, sizeof(PARAFORMAT) );
	paragraphFormat.cbSize = sizeof(PARAFORMAT);
	paragraphFormat.dwMask = PFM_ALIGNMENT;
	switch( alignment ) {
		case taTextLeft : {
			paragraphFormat.wAlignment = PFA_LEFT;
		}
		break;

		case taTextCenter : {
			paragraphFormat.wAlignment = PFA_CENTER;
		}
		break;

		case taTextRight : {
			paragraphFormat.wAlignment = PFA_RIGHT;
		}
		break;
	}
	::SendMessage( hwnd_, EM_SETPARAFORMAT, 0, (LPARAM)&paragraphFormat );
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
	SendMessage( hwnd_, EM_SETREADONLY, readonly ? TRUE : FALSE, 0 );
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

	//OKToResetControlText_ = false;

	setText( text );

	//OKToResetControlText_ = true;
}

/**
*CVS Log info
*$Log$
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


