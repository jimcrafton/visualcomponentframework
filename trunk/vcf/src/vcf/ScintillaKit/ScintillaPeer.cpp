//ScintillaPeer.cpp

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"


#include "Platform.h"

#include "Scintilla.h"
#include "SciLexer.h"


#include "PropSet.h"
#include "Accessor.h"
#include "WindowAccessor.h"




#include "vcf/ScintillaKit/ScintillaKit.h"
#include "vcf/ScintillaKit/ScintillaPeer.h"



#include "vcf/ApplicationKit/TextModel.h"
#include "vcf/ApplicationKit/Win32ToolKit.h"



#define CPP_KEYWORDS	"asm auto bool break case catch char class const const_cast continue \
default delete do double dynamic_cast else enum explicit export extern false float for \
friend goto if inline int long mutable namespace new operator private protected public \
register reinterpret_cast return short signed sizeof static static_cast struct switch \
template this throw true try typedef typeid typename union unsigned using \
void volatile wchar_t while"


#define CPP_WORD_CHARS	"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"



#define ELEMENTS(a)	(sizeof(a) / sizeof(a[0]))


using namespace VCF;

/*
bool IsAlphabetic(unsigned int ch)
{
	return ((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'));
}
*/

bool includes(const Win32ScintillaPeer::StyleAndWords &symbols, const String value)
{
	if (symbols.words.length() == 0) {
		return false;
	}
	else if ( IsAlphabetic(symbols.words[0]) ) {
		// Set of symbols separated by spaces
		size_t lenVal = value.length();

		const char *symbol = symbols.words.ansi_c_str();

		while (symbol) {
			const char *symbolEnd = strchr(symbol, ' ');

			size_t lenSymbol = strlen(symbol);

			if (symbolEnd) {
				lenSymbol = symbolEnd - symbol;
			}

			if (lenSymbol == lenVal) {

				if ( strncmp(symbol, value.ansi_c_str(), lenSymbol) == 0 ) {

					return true;
				}
			}
			symbol = symbolEnd;
			if (symbol)
				symbol++;
		}
	}
	else {
		// Set of individual characters. Only one character allowed for now
		char ch = symbols.words[0];
		return strchr(value.ansi_c_str(), ch) != 0;
	}
	return false;
}

/*
LRESULT Win32ScintillaPeerWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;
	Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hWnd );
	if ( NULL != win32Obj ) {
		//result = win32Obj->handleEventMessages( message, wParam, lParam );
		Win32ScintillaPeer* scintillaPeer = (Win32ScintillaPeer*)win32Obj;
		WNDPROC wndProc = scintillaPeer->getScintillaWndProc();
		result = CallWindowProc( wndProc, hWnd, message, wParam, lParam );
	}
	return result;
}
*/


std::map<HWND,Win32ScintillaPeer*> Win32ScintillaPeer::scintillaPeerMap;
namespace VCF {
class ScintillaHook {
public:
	void inc() {
		refs_ ++;
	}

	void dec() {
		if ( refs_ > 0 ) {
			refs_ --;
		}

		if ( refs_ <= 0 ) {
			delete this;
			ScintillaHook::hookInstance = NULL;
			return;
		}
	}

	static ScintillaHook* instance() {


		if ( NULL == ScintillaHook::hookInstance ) {
			ScintillaHook::hookInstance = new ScintillaHook();
		}

		return ScintillaHook::hookInstance;
	}
protected:
	static ScintillaHook* hookInstance;
	static LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );

	HHOOK hook_;
	int refs_;
private:

	ScintillaHook():refs_(0),hook_(NULL){
		hook_ = SetWindowsHookEx( WH_MOUSE, ScintillaHook::MouseProc, NULL, GetCurrentThreadId() );
	}

	~ScintillaHook(){
		UnhookWindowsHookEx( hook_ );
		StringUtils::trace( "ScintillaHook destroyed!\n" );
	}
};


};


ScintillaHook* ScintillaHook::hookInstance = NULL;

LRESULT CALLBACK ScintillaHook::MouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	ScintillaHook* hookInst = ScintillaHook::instance();

	if ( (WM_LBUTTONDOWN == wParam) || (WM_MBUTTONDOWN == wParam) || (WM_RBUTTONDOWN == wParam) ) {
		MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;

		std::map<HWND,Win32ScintillaPeer*>::iterator found =
			Win32ScintillaPeer::scintillaPeerMap.find( mh->hwnd );

		if ( found != Win32ScintillaPeer::scintillaPeerMap.end() ) {
			Win32ScintillaPeer* peer = found->second;

			int type = Control::MOUSE_DOWN;

			int btnMask = mbmLeftButton;
			if ( WM_MBUTTONDOWN == wParam ) {
				btnMask = mbmMiddleButton;
			}
			else if ( WM_RBUTTONDOWN == wParam ) {
				btnMask = mbmRightButton;
			}

			int keyMask = 0;
			short val = GetKeyState( VK_CONTROL );
			if ( (val >> 15) ) {
				keyMask |= kmCtrl;
			}

			val = GetKeyState( VK_SHIFT );
			if ( (val >> 15) ) {
				keyMask |= kmShift;
			}

			val = GetKeyState( VK_MENU );
			if ( (val >> 15) ) {
				keyMask |= kmAlt;
			}

			Point pt( mh->pt.x, mh->pt.y );

			Event* event = new MouseEvent ( peer->getPeerControl(), type,
											btnMask,
											keyMask, &pt );


			if ( (peer->getPeerControl()->getComponentState() != Component::csDestroying) ) {
				peer->getPeerControl()->handleEvent( event );
			}

			delete event;
		}
	}
	else if ( (WM_LBUTTONUP == wParam) || (WM_MBUTTONUP == wParam) || (WM_RBUTTONUP == wParam) ) {
		MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;

		std::map<HWND,Win32ScintillaPeer*>::iterator found =
			Win32ScintillaPeer::scintillaPeerMap.find( mh->hwnd );

		if ( found != Win32ScintillaPeer::scintillaPeerMap.end() ) {
			Win32ScintillaPeer* peer = found->second;

			int type = Control::MOUSE_UP;

			int btnMask = mbmLeftButton;
			if ( WM_MBUTTONUP == wParam ) {
				btnMask = mbmMiddleButton;
			}
			else if ( WM_RBUTTONUP == wParam ) {
				btnMask = mbmRightButton;
			}

			int keyMask = 0;
			short val = GetKeyState( VK_CONTROL );
			if ( (val >> 15) ) {
				keyMask |= kmCtrl;
			}

			val = GetKeyState( VK_SHIFT );
			if ( (val >> 15) ) {
				keyMask |= kmShift;
			}

			val = GetKeyState( VK_MENU );
			if ( (val >> 15) ) {
				keyMask |= kmAlt;
			}

			Point pt( mh->pt.x, mh->pt.y );

			Event* event = new MouseEvent ( peer->getPeerControl(), type,
											btnMask,
											keyMask, &pt );


			if ( (peer->getPeerControl()->getComponentState() != Component::csDestroying) ) {
				peer->getPeerControl()->handleEvent( event );
			}

			delete event;
		}
	}
	else if ( WM_MOUSEMOVE == wParam ) {
		MOUSEHOOKSTRUCT* mh = (MOUSEHOOKSTRUCT*)lParam;

		std::map<HWND,Win32ScintillaPeer*>::iterator found =
			Win32ScintillaPeer::scintillaPeerMap.find( mh->hwnd );

		if ( found != Win32ScintillaPeer::scintillaPeerMap.end() ) {
			Win32ScintillaPeer* peer = found->second;

			int type = Control::MOUSE_MOVE;

			int btnMask = 0;



			short val = GetKeyState( VK_LBUTTON );
			if ( (val >> 15) ) {
				btnMask |= mbmLeftButton;
			}

			val = GetKeyState( VK_MBUTTON );
			if ( (val >> 15) ) {
				btnMask |= mbmMiddleButton;
			}

			val = GetKeyState( VK_RBUTTON );
			if ( (val >> 15) ) {
				btnMask |= mbmRightButton;
			}

			int keyMask = 0;
			val = GetKeyState( VK_CONTROL );
			if ( (val >> 15) ) {
				keyMask |= kmCtrl;
			}

			val = GetKeyState( VK_SHIFT );
			if ( (val >> 15) ) {
				keyMask |= kmShift;
			}

			val = GetKeyState( VK_MENU );
			if ( (val >> 15) ) {
				keyMask |= kmAlt;
			}

			Point pt( mh->pt.x, mh->pt.y );

			Event* event = new MouseEvent ( peer->getPeerControl(), type,
											btnMask,
											keyMask, &pt );


			if ( (peer->getPeerControl()->getComponentState() != Component::csDestroying) ) {
				peer->getPeerControl()->handleEvent( event );
			}

			delete event;
		}
	}

	return CallNextHookEx( hookInst->hook_, nCode, wParam, lParam );
}


Win32ScintillaPeer::Win32ScintillaPeer( SciTextControl* editorControl ):
	AbstractWin32Component(editorControl),
	scintillaWndProc_(NULL),
	braceCount_(0),
	autoCCausedByOnlyOne_(false),
	indentMaintain_(true),
	autoIndent_(true),
	autoCompleteIgnoreCase_(false),
	callTipIgnoreCase_(false),
	indentOpening_(false),
	indentClosing_(false),
	bracesCheck_(true),
	bracesSloppy_(true),
	bracesStyle_(0),
	lexLanguage_(SCLEX_CPP),
	internalTextChange_(false),
	//updateFromModel_(false),
	statementLookback_(0),
	editorControl_(editorControl),
	scintillaFunc_(NULL),
	scintillaObject_(NULL),
	scintillaHwnd_(NULL)
{
	ScintillaHook::instance()->inc();
}

Win32ScintillaPeer::~Win32ScintillaPeer()
{
	ScintillaHook::instance()->dec();
}

void Win32ScintillaPeer::create( Control* owningControl )
{

	{
		String className = "Win32ScintillaPeer";
		if ( true != isRegistered() ){
			registerWin32Class( className, wndProc_  );
		}

		CreateParams params = createParams();

		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
		HWND parent = toolkit->getDummyParent();

		if ( System::isUnicodeEnabled() ) {
			hwnd_ = ::CreateWindowExW( params.second, className.c_str(),
									L"",	params.first,
									0, 0,
									1,
									1,
									parent,
									NULL, ::GetModuleHandleW(NULL), NULL );
		}
		else {
			hwnd_ = ::CreateWindowExA( params.second, className.ansi_c_str(),
									"",	params.first,
									0, 0,
									1,
									1,
									parent,
									NULL, ::GetModuleHandleA(NULL), NULL );
		}


		if ( NULL != hwnd_ ){
			Win32Object::registerWin32Object( this );
		}
		else {
			//throw exception
		}

		setCreated( true );
	}

	static bool firstCreate = true;
	if ( firstCreate ) {
		Scintilla_RegisterClasses( ::GetModuleHandleA(NULL) );
	}

	firstCreate = false;



	scintillaWndProc_ = NULL;


	scintillaHwnd_ = ::CreateWindowEx( WS_EX_CLIENTEDGE,
										"Scintilla",
										"",
										WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
										0,
										0,
										0,
										0,
										hwnd_,
										NULL,
										::GetModuleHandle(NULL),
										0 );//(HINSTANCE)textLib->getPeer()->getHandleID(), 0);

	if ( NULL != scintillaHwnd_ ) {

		Win32ScintillaPeer::scintillaPeerMap[scintillaHwnd_] = this;


		owningControl->ControlModelChanged +=
			new ClassProcedure1<Event*,Win32ScintillaPeer>( this, &Win32ScintillaPeer::onControlModelChanged, "Win32ScintillaPeer::onControlModelChanged" );



		//wndProc_ = (WNDPROC)Win32ScintillaPeerWndProc;
		//scintillaWndProc_ = (WNDPROC)::SetWindowLong( hwnd_, GWL_WNDPROC, (LONG)wndProc_ );
		//defaultWndProc_ = NULL;

		scintillaObject_ = (void*)SendMessage( scintillaHwnd_, SCI_GETDIRECTPOINTER,0,0 );
		scintillaFunc_ = (ScintillaFunc)SendMessage( scintillaHwnd_, SCI_GETDIRECTFUNCTION,0,0 );

		sendScintillaMessage(SCI_CLEARDOCUMENTSTYLE, 0, 0);
		//we'll handle the context menu
		sendScintillaMessage(SCI_USEPOPUP, 0, 0);

		/*
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.html"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.html.preprocessor"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.comment"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.at.else"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.flags"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("fold.preprocessor"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("styling.within.preprocessor"), (LPARAM)("1"));
		sendScintillaMessage(SCI_SETPROPERTY, (WPARAM)("asp.default.language"), (LPARAM)("1"));
		*/

		sendScintillaMessage(SCI_SETCARETFORE,0,0);
		sendScintillaMessage( SCI_SETCARETWIDTH, 1, 0 );
		sendScintillaMessage( SCI_SETCARETLINEVISIBLE, 0, 0 );

		sendScintillaMessage( SCI_CALLTIPSETBACK, RGB(0xff,0xff,0xff),0 );
		sendScintillaMessage( SCI_AUTOCSETIGNORECASE, 0, 0 );

		//sendScintillaMessage( SCI_SETWORDCHARS, 0, (LPARAM)CPP_WORD_CHARS );

		sendScintillaMessage( SCI_SETUSETABS, 1, 0 );
		sendScintillaMessage( SCI_SETTABINDENTS, 1, 0 );
		sendScintillaMessage( SCI_SETBACKSPACEUNINDENTS, 1, 0 );
		sendScintillaMessage( SCI_SETTABWIDTH, 4, 0 );
		sendScintillaMessage( SCI_SETINDENT, 4, 0 );

		sendScintillaMessage(SCI_SETFOLDFLAGS, 16,0);



		sendScintillaMessage( SCI_SETMODEVENTMASK, SC_MOD_CHANGEFOLD | SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT, 0 );

		//sendScintillaMessage( SCI_SETMARGINTYPEN, 2, SC_MARGIN_SYMBOL );
		//sendScintillaMessage( SCI_SETMARGINWIDTHN, 2, 14 );

		//sendScintillaMessage( SCI_SETMARGINMASKN, 2, SC_MASK_FOLDERS );
		//sendScintillaMessage( SCI_SETMARGINSENSITIVEN, 2, 1 );

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN, RGB(0, 0, 0));

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDER, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDER, RGB(0, 0, 0));

		/*
		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDERSUB, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, RGB(0, 0, 0));

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDERTAIL, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, RGB(0, 0, 0));

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND, RGB(0, 0, 0));

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID, RGB(0, 0, 0));

		sendScintillaMessage( SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
		sendScintillaMessage( SCI_MARKERSETFORE, SC_MARKNUM_FOLDERMIDTAIL, RGB(0xff, 0xff, 0xff));
		sendScintillaMessage( SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, RGB(0, 0, 0));
		*/

		DWORD backColor =  ::GetSysColor(COLOR_WINDOW);


		sendScintillaMessage( SCI_STYLESETVISIBLE, STYLE_BRACELIGHT, 1 );
		sendScintillaMessage( SCI_STYLESETVISIBLE, STYLE_BRACEBAD, 1 );
		sendScintillaMessage( SCI_SETINDENTATIONGUIDES, TRUE, 0 );

		//sendScintillaMessage( SCI_SETMARGINWIDTHN, 0, 30 );


		setEditorStyle( STYLE_BRACELIGHT, 0x00FF0000, backColor, 11, "Lucida Console", true );
		setEditorStyle( STYLE_BRACEBAD, 0x000000FF, backColor, 11, "Lucida Console", true, true );


		sendScintillaMessage( SCI_COLOURISE,0,-1);

		//use /n end of line style
		sendScintillaMessage( SCI_SETEOLMODE,SC_EOL_LF) ;

	}
}

void Win32ScintillaPeer::setEditorStyle( const int& style, const ulong& foreColor,
										const ulong& backColor, const ulong& size,
										const String& fontFace, const bool& bold,
										const bool& italic )
{
	sendScintillaMessage( SCI_STYLESETFORE, style, foreColor);
	sendScintillaMessage( SCI_STYLESETBACK, style, backColor);
	if (size >= 1) {
		sendScintillaMessage( SCI_STYLESETSIZE, style, size);
	}
	if (false == fontFace.empty()) {
		AnsiString tmp = fontFace;
		sendScintillaMessage( SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(tmp.c_str()));
	}

	sendScintillaMessage( SCI_STYLESETBOLD, style, bold );

	sendScintillaMessage( SCI_STYLESETITALIC, style, italic );
}

bool Win32ScintillaPeer::findMatchingBracePosition( int &braceAtCaret, int &braceOpposite,
												   const bool& sloppy )
{
	bool isInside = false;

	int bracesStyleCheck = bracesStyle_;

	int caretPos = sendScintillaMessage( SCI_GETCURRENTPOS, 0, 0);

	braceAtCaret = -1;
	braceOpposite = -1;
	char charBefore = '\0';
	char styleBefore = '\0';

	PropSet props;
	WindowAccessor acc((WindowID)scintillaHwnd_, props);

	if (caretPos > 0) {
		charBefore = sendScintillaMessage( SCI_GETCHARAT,caretPos - 1, 0 );
		styleBefore = static_cast<char>(sendScintillaMessage( SCI_GETSTYLEAT, caretPos - 1, 0) & 31);
	}

	// Priority goes to character before caret

	SciTextModel* doc = editorControl_->getTextModel();

	String bracesStr = doc->getBraceCharacters();


	
	if (charBefore &&  (bracesStr.find( charBefore ) != String::npos ) &&
	        ((styleBefore == bracesStyleCheck) || (!bracesStyle_))) {
		braceAtCaret = caretPos - 1;
	}

	bool colonMode = false;

	if (lexLanguage_ == SCLEX_PYTHON && ':' == charBefore) {
		braceAtCaret = caretPos - 1;
		colonMode = true;
	}

	bool isAfter = true;

	if (sloppy && (braceAtCaret < 0)) {
		// No brace found so check other side
		char charAfter = acc[caretPos];
		char styleAfter = static_cast<char>(acc.StyleAt(caretPos) & 31);
		if (charAfter && (bracesStr.find( charAfter ) != String::npos ) && (styleAfter == bracesStyleCheck)) {
			braceAtCaret = caretPos;
			isAfter = false;
		}
		if (lexLanguage_ == SCLEX_PYTHON && ':' == charAfter) {
			braceAtCaret = caretPos;
			colonMode = true;
		}
	}
	if (braceAtCaret >= 0) {
		if (colonMode) {
			int lineStart = SendMessage(scintillaHwnd_, SCI_LINEFROMPOSITION, braceAtCaret, 0);
			int lineMaxSubord = SendMessage(scintillaHwnd_, SCI_GETLASTCHILD, lineStart, -1);
			braceOpposite = SendMessage(scintillaHwnd_, SCI_GETLINEENDPOSITION, lineMaxSubord, 0);
		}
		else {
			braceOpposite = SendMessage(scintillaHwnd_, SCI_BRACEMATCH, braceAtCaret, 0);
		}
		if (braceOpposite > braceAtCaret) {
			isInside = isAfter;
		}
		else {
			isInside = !isAfter;
		}
	}

	return isInside;
}

void Win32ScintillaPeer::braceMatch()
{
	int braceAtCaret = -1;
	int braceOpposite = -1;
	if ( false == bracesCheck_ ) {
		return;
	}

	findMatchingBracePosition( braceAtCaret, braceOpposite, bracesSloppy_ );


	if ((braceAtCaret != -1) && (braceOpposite == -1)) {

		SendMessage( scintillaHwnd_, SCI_BRACEBADLIGHT, braceAtCaret, 0 );

		sendScintillaMessage( SCI_SETHIGHLIGHTGUIDE, 0);
	}
	else {
		char chBrace = static_cast<char>( sendScintillaMessage( SCI_GETCHARAT, braceAtCaret, 0));

		SendMessage( scintillaHwnd_, SCI_BRACEHIGHLIGHT, braceAtCaret, braceOpposite);

		int columnAtCaret = SendMessage( scintillaHwnd_, SCI_GETCOLUMN, braceAtCaret, 0);

		if (chBrace == ':') {
			int lineStart = SendMessage(scintillaHwnd_, SCI_LINEFROMPOSITION, braceAtCaret, 0);
			int indentPos = SendMessage(scintillaHwnd_, SCI_GETLINEINDENTPOSITION, lineStart, 0);

			int indentPosNext = SendMessage(scintillaHwnd_, SCI_GETLINEINDENTPOSITION, lineStart + 1, 0);

			columnAtCaret = SendMessage(scintillaHwnd_, SCI_GETCOLUMN, indentPos, 0);

			int columnAtCaretNext = SendMessage(scintillaHwnd_, SCI_GETCOLUMN, indentPosNext, 0);

			int indentSize = SendMessage(scintillaHwnd_, SCI_GETINDENT, 0, 0);

			if (columnAtCaretNext - indentSize > 1) {
				columnAtCaret = columnAtCaretNext - indentSize;
			}
			//Platform::DebugPrintf(": %d %d %d\n", lineStart, indentPos, columnAtCaret);
		}

		int columnOpposite = SendMessage(scintillaHwnd_, SCI_GETCOLUMN, braceOpposite, 0);

		//if (props.GetInt("highlight.indentation.guides")) {
		SendMessage(scintillaHwnd_, SCI_SETHIGHLIGHTGUIDE, minVal<int>(columnAtCaret, columnOpposite), 0);
	}
}


void Win32ScintillaPeer::insertText( unsigned int start, const String& text )
{
	AnsiString tmp = text;

	if ( ((unsigned int)-1) == start ) {
		SendMessage( scintillaHwnd_, SCI_SETTEXT, 0, (LPARAM)tmp.c_str() );
	}
	else {
		SendMessage( scintillaHwnd_, SCI_INSERTTEXT, start, (LPARAM)tmp.c_str() );
	}
}

void Win32ScintillaPeer::removeText( unsigned int start, unsigned int length )
{
	SendMessage( scintillaHwnd_, SCI_SETTARGETSTART, start, 0 );
	SendMessage( scintillaHwnd_, SCI_REPLACETARGET, length, 0 );
}

unsigned int Win32ScintillaPeer::getTextLength()
{
	return SendMessage( scintillaHwnd_, SCI_GETTEXTLENGTH, 0, 0 );
}

String Win32ScintillaPeer::getText( unsigned int start, unsigned int length )
{
	String result;

	if ( ((unsigned int)-1) == length ) {
		int textLen = SendMessage( scintillaHwnd_, SCI_GETTEXTLENGTH, 0, 0 );
		if ( textLen > 0 ) {
			char* tmpText = new char[textLen+1];
			memset( tmpText, 0, textLen+1 );
			SendMessage( scintillaHwnd_, SCI_GETTEXT, textLen+1, (LPARAM)tmpText );
			
			result = tmpText;
			delete tmpText;
			tmpText = NULL;
		}
	}
	else {
		TextRange rng;
		rng.chrg.cpMin = start;
		rng.chrg.cpMax = start + length;
		char* tmp = new char[ length+1 ];
		memset( tmp, 0, length+1 );

		rng.lpstrText = tmp;

		SendMessage( scintillaHwnd_, SCI_GETTEXTRANGE, 0, (LPARAM)&rng );

		result = tmp;

		delete  [] tmp;
	}
	
	

	return result;
}



bool Win32ScintillaPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndResult = 0;
	switch ( message ) {


		case WM_DESTROY:{
			std::map<HWND,Win32ScintillaPeer*>::iterator found =
				Win32ScintillaPeer::scintillaPeerMap.find( scintillaHwnd_ );

			if ( found != Win32ScintillaPeer::scintillaPeerMap.end() ) {
				Win32ScintillaPeer::scintillaPeerMap.erase( found );
			}

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );
		}
		break;

		case WM_NOTIFY:{
			NMHDR* notificationHdr = (LPNMHDR)lParam;

			result = handleEventMessages( notificationHdr->code, wParam, lParam, wndResult );
		}
		break;

		case WM_SIZE : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );

			DWORD w = LOWORD(lParam);
			DWORD h = HIWORD(lParam);
			MoveWindow( scintillaHwnd_, 0, 0, w, h, TRUE );
		}
		break;

		case WM_COMMAND : {
			WORD hi = HIWORD(wParam);
			Event* event = NULL;
			if ( SCEN_SETFOCUS == hi ) {
				event = new FocusEvent ( peerControl_, Control::FOCUS_GAINED );
			}
			else if ( SCEN_KILLFOCUS == hi ) {
				event = new FocusEvent ( peerControl_, Control::FOCUS_LOST );
			}
			else {
				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );
			}

			if ( NULL != event ) {
				if ( NULL != event && (peerControl_->getComponentState() != Component::csDestroying) ) {
					peerControl_->handleEvent( event );
				}
				delete event;
			}
		}
		break;


		case WM_SETFOCUS : {
			//result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );
			SendMessage( scintillaHwnd_, WM_SETFOCUS, (WPARAM)hwnd_, 0 );
		}
		break;


		case WM_CHAR : {			
			SendMessage( scintillaHwnd_, WM_SETFOCUS, (WPARAM)hwnd_, 0 );
			editorControl_->startTypingTimer();
		}
		break;

		

		case WM_KILLFOCUS : {
			//result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );
		}
		break;

		case SCN_CHARADDED: {
			SCNotification* notification = (SCNotification*)lParam;
			char ch = notification->ch;
/*
			if  (ch  ==  '\r'  ||  ch  ==  '\n')  {
				char  linebuf[1000];
				int  curLine  =  sendScintillaMessage( SCI_LINEFROMPOSITION,
														sendScintillaMessage(SCI_GETCURRENTPOS) );

				int  lineLength  =  sendScintillaMessage(SCI_LINELENGTH,  curLine);

				if  (curLine  >  0  &&  lineLength  <=  2)  {
					int  prevLineLength  =  sendScintillaMessage(SCI_LINELENGTH,  curLine  -  1);
					if  (prevLineLength  <  sizeof(linebuf))  {
						WORD  buflen  =  sizeof(linebuf);
						memcpy(linebuf,  &buflen,  sizeof(buflen));
						sendScintillaMessage(EM_GETLINE,  curLine  -  1,
											reinterpret_cast<LPARAM>(static_cast<char  *>(linebuf)));

						linebuf[prevLineLength]  =  '\0';

						for  (int  pos  =  0;  linebuf[pos];  pos++)  {
							if  (linebuf[pos]  !=  ' '  &&  linebuf[pos]  !=  '\t')
								linebuf[pos]  =  '\0';
						}
						sendScintillaMessage(EM_REPLACESEL,  0,  reinterpret_cast<LPARAM>(static_cast<char  *>(linebuf)));
					}
				}
			}
			else {
			*/
				int selStart = sendScintillaMessage(SCI_GETSELECTIONSTART,0,0);
				int selEnd = sendScintillaMessage(SCI_GETSELECTIONEND,0,0);

				if ((selEnd == selStart) && (selStart > 0)) {
					int style = sendScintillaMessage(SCI_GETSTYLEAT, selStart - 1, 0);
					
					if (style != 1) {
						if (sendScintillaMessage(SCI_CALLTIPACTIVE)) {
							if (ch == ')') {
								braceCount_--;
								if (braceCount_ < 1)
									sendScintillaMessage(SCI_CALLTIPCANCEL);
							}
							else if (ch == '(') {
								braceCount_++;
							}
							else {
								//ContinueCallTip();
							}
						}
						else if (sendScintillaMessage(SCI_AUTOCACTIVE)) {
							if (ch == '(') {
								braceCount_++;
								startCallTip( selStart );
							}
							else if (ch == ')') {
								braceCount_--;
							}
							else if ( String::npos != calltipWordCharacters_.find(ch) ) {
								startCallTip( selStart );
							}
							else if ( String::npos != autoCompleteStartCharacters_.find(ch) ) {
								sendScintillaMessage(SCI_AUTOCCANCEL);
								startAutoComplete( selStart );
							}
							/*
							else if (!wordCharacters.contains(ch)) {
							sendScintillaMessage(SCI_AUTOCCANCEL);
							}
							else if (autoCCausedByOnlyOne) {
							StartAutoCompleteWord(true);
							}
							*/
						}
						/*
						else if (HandleXml(ch)) {
							// Handled in the routine
						}
						*/
						else {
							if (ch == '(') {
								braceCount_ = 1;
								//StartCallTip();
							} else {
								autoCCausedByOnlyOne_ = false;

								if ( indentMaintain_ ) {
									maintainIndentation( ch );
								}
								else {
									automaticIndentation( ch );
								}

								if ( String::npos != autoCompleteStartCharacters_.find( ch ) ) {
									startAutoComplete( selStart );
								}
								else if ( String::npos != calltipWordCharacters_.find(ch) ) {
									startCallTip( selStart );
								}
								/*
								else if (props.GetInt("autocompleteword.automatic") && wordCharacters.contains(ch)) {
									//StartAutoCompleteWord(true);
									autoCCausedByOnlyOne = sendScintillaMessage(SCI_AUTOCACTIVE);
								}
								*/

							}
						}
					}
				}
			//}

		}
		break;

		case SCN_UPDATEUI: {
			braceMatch();

			bool insertMode = sendScintillaMessage( SCI_GETOVERTYPE ) ? false : true;
			if ( (insertMode && (editorControl_->getEntryMode() == SciTextControl::temOverwrite)) ||
				(!insertMode && (editorControl_->getEntryMode() == SciTextControl::temInsert)) ) {

				editorControl_->setEntryMode( insertMode ? SciTextControl::temInsert : SciTextControl::temOverwrite );
			}

			if ( NULL != editorControl_->getViewModel() ) {
/*
					internalTextChange_ = true;
					SciTextModel* doc = editorControl_->getTextModel();
					long start = getSelectionStart();
					long count = getSelectionCount();
					if ( (start != doc->getSelectionStart()) ||
						(count != doc->getSelectionLength()) ) {

						doc->setSelectionRange( start, count );
					}
					internalTextChange_ = false;
					*/
			}
		}
		break;

		case SCEN_SETFOCUS : {
			StringUtils::trace( "SCEN_SETFOCUS\n" );
		}
		break;

		case SCEN_KILLFOCUS : {
			StringUtils::trace( "SCEN_KILLFOCUS\n" );
		}
		break;



		case SCN_MODIFIED: {

			SCNotification* notification = (SCNotification*)lParam;
			if (0 != (notification->modificationType & SC_MOD_CHANGEFOLD)) {
				foldChanged(notification->line,
							notification->foldLevelNow, notification->foldLevelPrev);
			}
			else if ( (notification->modificationType & SC_MOD_DELETETEXT) ||
						(notification->modificationType & SC_MOD_INSERTTEXT) ) {
				//if ( !updateFromModel_ ) {

					

					internalTextChange_ = true;


					if ( notification->modificationType & SC_MOD_DELETETEXT ) {
						//editorControl_->getTextModel()->removeText( notification->position, notification->length );
					}
					else if ( notification->modificationType & SC_MOD_INSERTTEXT ) {
						//String text;
						//text.append( notification->text, notification->length );
						//editorControl_->getTextModel()->insertText( notification->position, text );
					}

					internalTextChange_ = false;
				//}
			}
		}
		break;

		default : {
			//CallWindowProc( scintillaWndProc_, hwnd_, message, wParam, lParam );
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndResult );
		}
		break;
	}
	return result;
}

void Win32ScintillaPeer::foldChanged(int line, int levelNow, int levelPrev)
{
	//Platform::DebugPrintf("Fold %d %x->%x\n", line, levelPrev, levelNow);
	if (levelNow & SC_FOLDLEVELHEADERFLAG) {
		if (!(levelPrev & SC_FOLDLEVELHEADERFLAG)) {
			sendScintillaMessage( SCI_SETFOLDEXPANDED, line, 1);
		}
	}

	else if (levelPrev & SC_FOLDLEVELHEADERFLAG) {
		//Platform::DebugPrintf("Fold removed %d-%d\n", line, sendScintillaMessage(SCI_GETLASTCHILD, line));
		if (!sendScintillaMessage(SCI_GETFOLDEXPANDED, line)) {
			// Removing the fold from one that has been contracted so should expand
			// otherwise lines are left invisible with no way to make them visible
			expand(line, true, false, 0, levelPrev);
		}
	}
}

void Win32ScintillaPeer::expand(int &line, bool doExpand, bool force, int visLevels, int level)
{
	int lineMaxSubord = sendScintillaMessage(SCI_GETLASTCHILD, line, level & SC_FOLDLEVELNUMBERMASK);
	line++;
	while (line <= lineMaxSubord) {
		if (force) {
			if (visLevels > 0)
				sendScintillaMessage(SCI_SHOWLINES, line, line);
			else
				sendScintillaMessage(SCI_HIDELINES, line, line);
		} else {
			if (doExpand)
				sendScintillaMessage(SCI_SHOWLINES, line, line);
		}
		int levelLine = level;
		if (levelLine == -1)
			levelLine = sendScintillaMessage(SCI_GETFOLDLEVEL, line);
		if (levelLine & SC_FOLDLEVELHEADERFLAG) {
			if (force) {
				if (visLevels > 1)
					sendScintillaMessage(SCI_SETFOLDEXPANDED, line, 1);
				else
					sendScintillaMessage(SCI_SETFOLDEXPANDED, line, 0);
				expand(line, doExpand, force, visLevels - 1);
			} else {
				if (doExpand) {
					if (!sendScintillaMessage(SCI_GETFOLDEXPANDED, line))
						sendScintillaMessage(SCI_SETFOLDEXPANDED, line, 1);
					expand(line, true, force, visLevels - 1);
				} else {
					expand(line, false, force, visLevels - 1);
				}
			}
		} else {
			line++;
		}
	}
}

String Win32ScintillaPeer::getText()
{
	String result = "";

	int textLen = SendMessage( scintillaHwnd_, SCI_GETTEXTLENGTH, 0, 0 );
	if ( textLen > 0 ) {
		char* tmpText = new char[textLen+1];
		memset( tmpText, 0, textLen+1 );
		SendMessage( scintillaHwnd_, SCI_GETTEXT, textLen+1, (LPARAM)tmpText );

		result = tmpText;
		delete tmpText;
		tmpText = NULL;
	}

	return result;
}

void Win32ScintillaPeer::setText( const String& text )
{
	AnsiString tmp = text;
	SendMessage( scintillaHwnd_, SCI_SETTEXT, 0, (LPARAM)tmp.c_str() );
}

void Win32ScintillaPeer::onControlModelChanged( Event* )
{
	SciTextModel* tm = editorControl_->getTextModel();

	if ( NULL != tm ) {

		//set up the lexer here

		String keywords = tm->getLanguageKeyWords();

		if ( tm->getLexerID() == TD_LANG_CPP ) {
			lexLanguage_ = SCLEX_CPP;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_CPP, 0 );
			if ( keywords.empty() ) {
				keywords = CPP_KEYWORDS;
			}
		}
		else if ( tm->getLexerID() == TD_LANG_PYTHON ) {
			lexLanguage_ = SCLEX_PYTHON;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_PYTHON, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_HTML ) {
			lexLanguage_ = SCLEX_HTML;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_HTML, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_XML ) {
			lexLanguage_ = SCLEX_XML;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_XML, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_PERL ) {
			lexLanguage_ = SCLEX_PERL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_PERL, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_SQL ) {
			lexLanguage_ = SCLEX_SQL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_SQL, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_VB ) {
			lexLanguage_ = SCLEX_VB;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_VB, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_LATEX ) {
			lexLanguage_ = SCLEX_LATEX;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_LATEX, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_LUA ) {
			lexLanguage_ = SCLEX_LUA;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_LUA, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_PASCAL ) {
			lexLanguage_ = SCLEX_PASCAL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_PASCAL, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_ADA ) {
			lexLanguage_ = SCLEX_ADA;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_ADA, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_LISP ) {
			lexLanguage_ = SCLEX_LISP;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_LISP, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_RUBY ) {
			lexLanguage_ = SCLEX_RUBY;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_RUBY, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_EIFFEL ) {
			lexLanguage_ = SCLEX_EIFFEL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_EIFFEL, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_TCL ) {
			lexLanguage_ = SCLEX_TCL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_TCL, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_ASP ) {
			lexLanguage_ = SCLEX_ASP;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_ASP, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_PHP ) {
			lexLanguage_ = SCLEX_PHP;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_PHP, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_FORTRAN ) {
			lexLanguage_ = SCLEX_FORTRAN;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_FORTRAN, 0 );
		}
		else if ( tm->getLexerID() == TD_LANG_CSS ) {
			lexLanguage_ = SCLEX_CSS;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_CSS, 0 );
		}
		else {
			lexLanguage_ = SCLEX_NULL;
			sendScintillaMessage( SCI_SETLEXER, SCLEX_NULL, 0 );
		}

		if ( !keywords.empty() ) {
			sendScintillaMessage( SCI_SETKEYWORDS, 0, (LPARAM)keywords.ansi_c_str() );
		}

		setAutoCompletionCharacters( tm->getAutoCompletionCharacters() );

		calltipWordCharacters_ = tm->getCallTipCharacters();

		setSelectionMark( tm->getSelectionStart(), tm->getSelectionLength() );

		AnsiString text = tm->getText();

		sendScintillaMessage( SCI_SETTEXT, 0, (LPARAM)text.c_str() );
	}
}

void Win32ScintillaPeer::setControl( Control* component )
{
	AbstractWin32Component::setControl( component );
	editorControl_ = (SciTextControl*)component;
}

void Win32ScintillaPeer::setRightMargin( const double & rightMargin )
{
	sendScintillaMessage( SCI_SETMARGINRIGHT, 0, rightMargin );
}

void Win32ScintillaPeer::setLeftMargin( const double & leftMargin )
{
	sendScintillaMessage( SCI_SETMARGINLEFT, 0, leftMargin );
}

uint32 Win32ScintillaPeer::getLineCount()
{
	return sendScintillaMessage( SCI_GETLINECOUNT );
}

uint32 Win32ScintillaPeer::getCurrentLinePosition()
{
	return sendScintillaMessage( SCI_LINEFROMPOSITION, sendScintillaMessage( SCI_GETCURRENTPOS ) );
}

void Win32ScintillaPeer::scroll( int column, int line )
{
	sendScintillaMessage( SCI_LINESCROLL, column, line );
}


double Win32ScintillaPeer::getLeftMargin()
{
	return sendScintillaMessage(SCI_GETMARGINLEFT);
}

double Win32ScintillaPeer::getRightMargin()
{
	return sendScintillaMessage(SCI_GETMARGINRIGHT);
}

VCF::Point Win32ScintillaPeer::getPositionFromCharIndex( const uint32& index )
{
	VCF::Point result;
	result.x_ = sendScintillaMessage( SCI_POINTXFROMPOSITION, 0, index );
	result.y_ = sendScintillaMessage( SCI_POINTYFROMPOSITION, 0, index );

	return result;
}

uint32 Win32ScintillaPeer::getCharIndexFromPosition( const VCF::Point& point )
{
	return (uint32)sendScintillaMessage( SCI_POSITIONFROMPOINT, (int)point.x_, (int)point.y_ );
}

uint32 Win32ScintillaPeer::getCaretPosition()
{
	return getSelectionStart();
}

/*
void Win32ScintillaPeer::onTextModelTextChanged( ModelEvent* event )
{
	
	if ( false == internalTextChange_ ) {
		SciTextModel* tm = (SciTextModel*)event->getSource();

		switch ( event->getType() ) {
			case SciTextModel::tmTextInserted : {
				TextEvent* te = (TextEvent*)event;

				updateFromModel_ = true;
				unsigned long firstVisibleLine = sendScintillaMessage(SCI_GETFIRSTVISIBLELINE);
				unsigned long visibleLineCount = sendScintillaMessage(SCI_LINESONSCREEN);
				StringUtils::trace( Format( "fvl:%d, lc: %d\n" ) % firstVisibleLine % visibleLineCount	);

				AnsiString tmp = te->changeText;

				sendScintillaMessage( SCI_INSERTTEXT, te->changeStart, (LPARAM)tmp.c_str() );

				updateFromModel_ = false;
			}
			break;

			case SciTextModel::tmTextRemoved : {
				TextEvent* te = (TextEvent*)event;
				AnsiString tmp = te->changeText;

				updateFromModel_ = true;
				unsigned long firstVisibleLine = sendScintillaMessage(SCI_GETFIRSTVISIBLELINE);
				unsigned long visibleLineCount = sendScintillaMessage(SCI_LINESONSCREEN);
				StringUtils::trace( Format( "fvl:%d, lc: %d\n" ) % firstVisibleLine % visibleLineCount	);

				sendScintillaMessage( SCI_SETTARGETSTART, te->changeStart, 0 );
				sendScintillaMessage( SCI_SETTARGETEND, te->changeStart + tmp.size(), 0 );
				sendScintillaMessage( SCI_REPLACETARGET, 0, (LPARAM)tmp.c_str() );

				updateFromModel_ = false;
			}
			break;

			case Document::deSaved : {
				//do nothing!
			}
			break;

			case SciTextModel::tmTextSelectionChanged : {
				updateFromModel_ = true;

				setSelectionMark( tm->getSelectionStart(), tm->getSelectionLength() );

				if ( !peerControl_->isFocused() ) {
					StringUtils::trace( "SciTextModel::teTextSelectionChanged, peerControl_->setFocused()\n" );
					peerControl_->setFocused();
				}

				updateFromModel_ = false;
			}
			break;

			default : {
				AnsiString text = tm->getText();
				updateFromModel_ = true;
				sendScintillaMessage( SCI_SETTEXT, 0, (LPARAM)text.c_str() );
				updateFromModel_ = false;
			}
			break;
		}
	}
}
*/



void Win32ScintillaPeer::setCaretPosition( const uint32& caretPos )
{
	sendScintillaMessage(SCI_SETSELECTIONSTART,caretPos,0);
	sendScintillaMessage(SCI_SETSELECTIONEND,caretPos,0);
	sendScintillaMessage(SCI_GOTOPOS,caretPos,0);
}

void Win32ScintillaPeer::clearSelection()
{

}

uint32 Win32ScintillaPeer::getSelectionStart()
{
	uint32 result = sendScintillaMessage(SCI_GETSELECTIONSTART,0,0);
	return result;
}

uint32 Win32ScintillaPeer::getSelectionCount()
{
	uint32 result = 0;

	int selStart = sendScintillaMessage(SCI_GETSELECTIONSTART,0,0);

	int selEnd = sendScintillaMessage(SCI_GETSELECTIONEND,0,0);

	result = (uint32) abs( selEnd - selStart );

	return result;
}

void Win32ScintillaPeer::setSelectionMark( const uint32& start, const uint32& count )
{

	sendScintillaMessage(SCI_SETSELECTIONSTART,start,0);

	sendScintillaMessage(SCI_SETSELECTIONEND,start+count,0);

	sendScintillaMessage( SCI_SCROLLCARET );
}

int Win32ScintillaPeer::sendScintillaMessage( int code, int wParam, int lParam )
{
	return scintillaFunc_( scintillaObject_, code, wParam, lParam );
}

int Win32ScintillaPeer::getLineLength(int line)
{
	return sendScintillaMessage(SCI_GETLINEENDPOSITION, line) - sendScintillaMessage(SCI_POSITIONFROMLINE, line);
}

void Win32ScintillaPeer::maintainIndentation( char ch )
{
	if ( (ch != '\n') && (ch != '\r') ) {
		return;
	}


	int eolMode = sendScintillaMessage(SCI_GETEOLMODE);

	int curLine = sendScintillaMessage(SCI_LINEFROMPOSITION,
	                  sendScintillaMessage(SCI_GETCURRENTPOS));

	int lastLine = curLine - 1;
	int indentAmount = 0;

	if (((eolMode == SC_EOL_CRLF || eolMode == SC_EOL_LF) && ch == '\n') ||
	        (eolMode == SC_EOL_CR && ch == '\r')) {
		if ( true == autoIndent_ ) {

			while (lastLine >= 0 && getLineLength(lastLine) == 0) {
				lastLine--;
			}

		}
		if ( lastLine >= 0 ) {
			indentAmount = getLineIndentation(lastLine);
		}

		if ( indentAmount > 0 ) {
			setLineIndentation(curLine, indentAmount);
		}
	}
}

bool Win32ScintillaPeer::rangeIsAllWhitespace(int start, int end)
{
	PropSet props;
	WindowAccessor acc( (WindowID)scintillaHwnd_, props );


	for (int i = start;i < end;i++) {
		if ((acc[i] != ' ') && (acc[i] != '\t'))
			return false;
	}
	return true;
}

void Win32ScintillaPeer::automaticIndentation( char ch ) {

	CharacterRange crange;

	crange.cpMin = sendScintillaMessage(SCI_GETSELECTIONSTART,0,0);
	crange.cpMax = sendScintillaMessage(SCI_GETSELECTIONEND,0,0);


	int selStart = crange.cpMin;

	int  curLine  =  sendScintillaMessage( SCI_LINEFROMPOSITION,
														sendScintillaMessage(SCI_GETCURRENTPOS) );

	int thisLineStart = sendScintillaMessage(SCI_POSITIONFROMLINE, curLine);
	int indentSize = sendScintillaMessage(SCI_GETINDENT);
	int indentBlock = getIndentOfBlock(curLine - 1);

	if ( blockEnd_.isSingleChar() && ch == blockEnd_.words[0]) {	// Dedent maybe

		if (!indentClosing_) {

			if ( rangeIsAllWhitespace( thisLineStart, selStart - 1) ) {
				setLineIndentation(curLine, indentBlock - indentSize);
			}
		}
	}
	else if (!blockEnd_.isSingleChar() && (ch == ' ')) {	// Dedent maybe

		if (!indentClosing_ && (getIndentState(curLine) == isBlockEnd)) {

		}
	}
	else if (ch == blockStart_.words[0]) {	// Dedent maybe if first on line and previous line was starting keyword
		if (!indentOpening_ && (getIndentState(curLine - 1) == isKeyWordStart)) {

			if ( rangeIsAllWhitespace(thisLineStart, selStart - 1) ) {
				setLineIndentation(curLine, indentBlock - indentSize);
			}
		}
	}
	else if ((ch == '\r' || ch == '\n') && (selStart == thisLineStart)) {
		if (!indentClosing_ && !blockEnd_.isSingleChar()) {	// Dedent previous line maybe
			String controlWords[1];
			if (getLinePartsInStyle(curLine - 1, blockEnd_.styleNumber,
			                        -1, controlWords, ELEMENTS(controlWords))) {

				if ( includes( blockEnd_, controlWords[0] ) ) {
					// Check if first keyword on line is an ender
					setLineIndentation(curLine - 1, getIndentOfBlock(curLine - 2) - indentSize);
					// Recalculate as may have changed previous line
					indentBlock = getIndentOfBlock(curLine - 1);
				}
			}
		}
		setLineIndentation(curLine, indentBlock);
	}
}

void Win32ScintillaPeer::setLineIndentation(int line, int indent)
{
	CharacterRange crange;
	crange.cpMin = sendScintillaMessage(SCI_GETSELECTIONSTART);
	crange.cpMax = sendScintillaMessage(SCI_GETSELECTIONEND);

	int posBefore = sendScintillaMessage(SCI_GETLINEINDENTPOSITION, line, 0);

	sendScintillaMessage(SCI_SETLINEINDENTATION, line, indent);

	int posAfter = sendScintillaMessage(SCI_GETLINEINDENTPOSITION, line);

	int posDifference = posAfter - posBefore;
	if (posAfter > posBefore) {
		// Move selection on
		if (crange.cpMin >= posBefore) {
			crange.cpMin += posDifference;
		}
		if (crange.cpMax >= posBefore) {
			crange.cpMax += posDifference;
		}
	} else if (posAfter < posBefore) {
		// Move selection back
		if (crange.cpMin >= posAfter) {
			if (crange.cpMin >= posBefore)
				crange.cpMin += posDifference;
			else
				crange.cpMin = posAfter;
		}
		if (crange.cpMax >= posAfter) {
			if (crange.cpMax >= posBefore)
				crange.cpMax += posDifference;
			else
				crange.cpMax = posAfter;
		}
	}

	sendScintillaMessage(SCI_SETSEL, crange.cpMin, crange.cpMax);
}

unsigned int Win32ScintillaPeer::getLinePartsInStyle(int line, int style1, int style2, String sv[], int len)
{
	for (int i = 0; i < len; i++)
		sv[i] = "";

	PropSet props;
	WindowAccessor acc( (WindowID)scintillaHwnd_, props );

	String s;
	int part = 0;

	int thisLineStart = sendScintillaMessage(SCI_POSITIONFROMLINE, line);

	int nextLineStart = sendScintillaMessage(SCI_POSITIONFROMLINE, line + 1);

	for (int pos = thisLineStart; pos < nextLineStart; pos++) {
		if ((acc.StyleAt(pos) == style1) || (acc.StyleAt(pos) == style2)) {
			char c[2];
			c[0] = acc[pos];
			c[1] = '\0';
			s += c;
		}
		else if (s.length() > 0) {
			if (part < len) {
				sv[part++] = s;
			}
			s = "";
		}
	}
	if ((s.size() > 0) && (part < len)) {
		sv[part++] = s;
	}
	return part;
}

Win32ScintillaPeer::IndentationStatus Win32ScintillaPeer::getIndentState(int line)
{
	// C like language indentation defined by braces and keywords
	IndentationStatus indentState = isNone;
	String controlWords[20];
	unsigned int parts = getLinePartsInStyle(line, statementIndent_.styleNumber,
	                     -1, controlWords, ELEMENTS(controlWords));


	for (unsigned int i = 0; i < parts; i++) {
		if (includes(statementIndent_, controlWords[i]))
			indentState = isKeyWordStart;
	}

	// Braces override keywords
	String controlStrings[20];
	parts = getLinePartsInStyle(line, blockEnd_.styleNumber,
	                            -1, controlStrings, ELEMENTS(controlStrings));


	for (unsigned int j = 0; j < parts; j++) {
		if ( includes(blockEnd_, controlStrings[j]) ) {
			indentState = isBlockEnd;
		}

		if ( includes(blockStart_, controlStrings[j]) ) {
			indentState = isBlockStart;
		}
	}

	return indentState;
}

int Win32ScintillaPeer::getIndentOfBlock(int line)
{
	if (line < 0)
		return 0;
	int indentSize = sendScintillaMessage(SCI_GETINDENT);

	int indentBlock = sendScintillaMessage(SCI_GETLINEINDENTATION, line);

	int backLine = line;
	IndentationStatus indentState = isNone;
	if (statementIndent_.isEmpty() && blockStart_.isEmpty() && blockEnd_.isEmpty())
		indentState = isBlockStart;	// Don't bother searching backwards

	int lineLimit = line - statementLookback_;
	if (lineLimit < 0)
		lineLimit = 0;
	while ((backLine >= lineLimit) && (indentState == 0)) {

		indentState = getIndentState(backLine);

		if (indentState != 0) {

			indentBlock = sendScintillaMessage(SCI_GETLINEINDENTATION, backLine);

			if (indentState == isBlockStart) {
				if (!indentOpening_)
					indentBlock += indentSize;
			}
			if (indentState == isBlockEnd) {
				if (indentClosing_)
					indentBlock -= indentSize;
				if (indentBlock < 0)
					indentBlock = 0;
			}
			if ((indentState == isKeyWordStart) && (backLine == line))
				indentBlock += indentSize;
		}
		backLine--;
	}
	return indentBlock;
}

int Win32ScintillaPeer::getLineIndentation(int line)
{
	return sendScintillaMessage(SCI_GETLINEINDENTATION, line);
}

bool Win32ScintillaPeer::isFocused()
{
	bool result = false;

	HWND focusedHandle = ::GetFocus();
	if ( (focusedHandle == hwnd_) || (focusedHandle == scintillaHwnd_) ) {
		result = true;
	}
	return result;
}

void Win32ScintillaPeer::setFocused()
{
	//AbstractWin32Component::setFocused();
	::SetFocus( scintillaHwnd_ );
}


void Win32ScintillaPeer::scrollToSelection( const bool& showEndSel )
{
	sendScintillaMessage( SCI_SCROLLCARET );
}

void Win32ScintillaPeer::setAutoCompletionCharacters( const String& autoCompletionChars )
{
	autoCompleteStartCharacters_ = autoCompletionChars;
}

void Win32ScintillaPeer::startAutoComplete( ulong pos )
{
	SciTextModel* tm = editorControl_->getTextModel();

	if ( NULL != tm ) {
		AnsiString list = tm->getAutoCompletionList( pos );
		if ( !list.empty() ) {
			sendScintillaMessage( SCI_AUTOCSHOW, 0, (LPARAM)list.c_str() );
		}
	}
}

void Win32ScintillaPeer::startCallTip( ulong pos )
{
	SciTextModel* tm = editorControl_->getTextModel();

	if ( NULL != tm ) {
		AnsiString text = tm->getCallTipText( pos );
		if ( !text.empty() ) {
			sendScintillaMessage( SCI_CALLTIPSHOW, pos, (LPARAM)text.c_str() );
		}
	}
}

void Win32ScintillaPeer::setVisible( const bool& val )
{
	AbstractWin32Component::setVisible( val );

	::ShowWindow( scintillaHwnd_, val ? SW_SHOW : SW_HIDE );
}

ulong Win32ScintillaPeer::getLineFromPosition( ulong pos )
{
	return sendScintillaMessage( SCI_LINEFROMPOSITION, pos );
}


ulong Win32ScintillaPeer::getColumnFromPosition( ulong pos )
{
	return sendScintillaMessage( SCI_GETCOLUMN, pos );
}

ulong Win32ScintillaPeer::getFirstVisibleLine()
{
	return sendScintillaMessage( SCI_GETFIRSTVISIBLELINE );
}

ulong Win32ScintillaPeer::getLinesOnScreen()
{
	return sendScintillaMessage( SCI_LINESONSCREEN );
}

void Win32ScintillaPeer::setReadOnly( const bool& readonly )
{
	sendScintillaMessage( SCI_SETREADONLY, readonly, 0 );
}

void Win32ScintillaPeer::print( PrintContext* context, const int32& page )
{

}

uint32 Win32ScintillaPeer::getTotalPrintablePageCount( PrintContext* context )
{
	return 0;
}

void Win32ScintillaPeer::finishPrinting()
{

}

void Win32ScintillaPeer::cut()
{
	sendScintillaMessage( SCI_CUT, 0, 0 );
}

void Win32ScintillaPeer::copy()
{
	sendScintillaMessage( SCI_COPY, 0, 0 );
}

void Win32ScintillaPeer::paste()
{
	sendScintillaMessage( SCI_PASTE, 0, 0 );
}

bool Win32ScintillaPeer::canUndo()
{
	return sendScintillaMessage( SCI_CANUNDO, 0, 0 ) ? true : false;
}

bool Win32ScintillaPeer::canRedo()
{
	return false;
}

void Win32ScintillaPeer::undo()
{
	sendScintillaMessage( SCI_UNDO, 0, 0 );
}

void Win32ScintillaPeer::redo()
{

}

void Win32ScintillaPeer::setTextWrapping( const bool& val )
{
	sendScintillaMessage( SCI_SETWRAPMODE, val ? SC_WRAP_WORD : SC_WRAP_NONE, 0 );	
}

bool Win32ScintillaPeer::getTextWrapping()
{
	return sendScintillaMessage( SCI_GETWRAPMODE, 0, 0 ) ? true : false;
}



