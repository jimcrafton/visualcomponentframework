#ifndef _VCF_SCINTILLAKIT_H__
#define _VCF_SCINTILLAKIT_H__
//ScintillaKit.h

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#ifdef WIN32


#pragma comment(lib,"imm32.lib")


/**
*Helps linking with the right library
*/


#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
# endif




#ifdef USE_SCINTILLAKIT_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "ScintillaKit"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "ScintillaKit"_LIB_CPLVERNUM".lib")
#	endif
#elif USE_SCINTILLAKIT_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "ScintillaKit_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "ScintillaKit_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // SCINTILLAKIT_LIB



// fast workaround so to be able to easily come back if we want
#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#   define _LIB_CPLVERNUM ""
#endif

	#ifdef SCINTILLAKIT_DLL
		#if defined(SCINTILLAKIT_EXPORTS) 
			#define SCINTILLAKIT_API __declspec(dllexport)
		#else
			#define SCINTILLAKIT_API __declspec(dllimport)
		#endif
	#else	
		#define SCINTILLAKIT_API
	#endif //SCINTILLAKIT_DLL
#else
	#define SCINTILLAKIT_API
#endif //WIN32



#define SCINTILLAKIT_CLASSID		"5836ad34-1065-4ffa-b6b1-2e3b62047309"




#define TD_LANG_CPP       "CPP"
#define TD_LANG_PYTHON    "Python"
#define TD_LANG_HTML      "HTML"
#define TD_LANG_XML       "XML"
#define TD_LANG_PERL      "Perl"
#define TD_LANG_SQL       "SQL"
#define TD_LANG_VB        "VB"
#define TD_LANG_LATEX     "Latex"
#define TD_LANG_LUA       "Lua"
#define TD_LANG_PASCAL    "Pascal"
#define TD_LANG_ADA       "ADA"
#define TD_LANG_LISP      "Lisp"
#define TD_LANG_RUBY      "Ruby"
#define TD_LANG_EIFFEL    "Eiffel"
#define TD_LANG_TCL       "TCL"
#define TD_LANG_ASP       "ASP"
#define TD_LANG_PHP       "PHP"
#define TD_LANG_FORTRAN   "Fortran"
#define TD_LANG_CSS       "CSS"




#ifndef _VCF_TEXTMODEL_H__
#include "vcf/ApplicationKit/TextModel.h"
#endif //_VCF_TEXTMODEL_H__

namespace VCF  {









	class SCINTILLAKIT_API ScintillaKit {
	public:
		static void init( int argc, char** argv );
		static void terminate();
	};








class SCINTILLAKIT_API FindInfo {
public:
	FindInfo() : atEnd_(false), position_(0),
				caseSensitive_(false), 
				matchWordOnly_(false),
				searchAllOpenDocs_(false)
				{
	}

	static ulong findString( const FindInfo& findInfo, const String& inText );

public:
	bool atEnd_;
	ulong position_;
	bool caseSensitive_;
	bool matchWordOnly_;
	bool searchAllOpenDocs_;
	String searchString_;
	std::vector<String> searchStrings_;
};


/**
*@class FindInfo
*
*
*/
class SCINTILLAKIT_API FindInFilesInfo : public FindInfo {
public:
	
	FindInFilesInfo():searchInSubDirectories_(true) {}

	bool searchInSubDirectories_;
	String fileTypes_;
	std::vector<String> fileTypesListing_;

	String startDirectory_;
	std::vector<String> startDirectories_;
};



/**
*@class FindInfo
*
*
*/
class SCINTILLAKIT_API ReplaceInfo : public FindInfo {
public:
	ReplaceInfo() {
		
	}
	
	String replaceString_;
	std::vector<String> replaceStrings_;
};


class SciTextModel;


/**
*@class FindInfo
*
*
*/
class SCINTILLAKIT_API FoundEntry {
public:
	FoundEntry() : position_(0), line_(0), column_(0),document_(NULL){

	}

	ulong position_;
	ulong line_;
	ulong column_;
	SciTextModel* document_;
	String fileName_;	
};

class ScintillaPeer;


#define SCITEXTMODEL_CLASSID		"e9157c98-e95d-4c07-ad7d-0ef8fc3aa1db"

/**
*@class TextDocument
*  The abstract class for text based documents.
*/
class SCINTILLAKIT_API SciTextModel : public TextModel {
public:

	SciTextModel();

	virtual String getText( const uint32& index, const uint32& count );
	virtual String getText();
	virtual uint32 getSize();




	
	bool find( FindInfo& findInfo );
	bool findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries );

	bool replace( ReplaceInfo& replaceInfo );
	bool replaceAll( ReplaceInfo& replaceInfo );
	

	void setSelectionRange( const long pos, const ulong length  );
	long getSelectionStart();
	uint32 getSelectionLength();

	/**
	returns a string that represents the selection starting 
	at the selection start and with a matching length as the 
	selection has. It is possible for this to return an empty
	string if the selection length is 0.
	@see getSelectionStart
	@see getSelectionLength
	*/
	String getSelection();

	/**
	sets the selection text. The insertion point is the current 
	selection start position. Similar to calling insertText. The
	inserted text is the length of the selectionText param.
	@see insertText
	@see getSelectionStart
	*/
	void setSelection( const String& selectionText );

	/**
	returns the language identifier for this document. The id is used to
	determine what kind of lexer to user for the text editor for syntax highlighting
	@return String this may be an empty string (""), or it may contain
	the language id for the document, specifically ids like:
	<table>
		<tr>
			<td>ID tag</td> <td>ID String</td> <td>Language</td>
		</tr>
		<tr><td>TD_LANG_CPP</td> <td>"CPP"</td> <td>C/C++</td></tr>		
		<tr><td>TD_LANG_PYTHON</td> <td>"Python"</td> <td>Python</td></tr>
		<tr><td>TD_LANG_HTML</td> <td>"HTML"</td> <td></td>HTML</tr>
		<tr><td>TD_LANG_XML</td> <td>"XML"</td> <td></td>XML</tr>
		<tr><td>TD_LANG_PERL</td> <td>"Perl"</td> <td></td>Perl</tr>
		<tr><td>TD_LANG_SQL</td> <td>"SQL"</td> <td></td>SQL</tr>
		<tr><td>TD_LANG_VB</td> <td>"VB"</td> <td></td>VB</tr>
		<tr><td>TD_LANG_LATEX</td> <td>"Latex"</td> <td>Latex</td></tr>
		<tr><td>TD_LANG_LUA</td> <td>"Lua"</td> <td></td>Lua</tr>
		<tr><td>TD_LANG_PASCAL</td> <td>"Pascal"</td> <td>Pascal/ObjectPascal</td></tr>
		<tr><td>TD_LANG_ADA</td> <td>"ADA"</td> <td></td>Ada</tr>
		<tr><td>TD_LANG_LISP</td> <td>"Lisp"</td> <td></td>Lisp</tr>
		<tr><td>TD_LANG_RUBY</td> <td>"Ruby"</td> <td></td>Ruby</tr>
		<tr><td>TD_LANG_EIFFEL</td> <td>"Eiffel"</td> <td>Eiffel</td></tr>
		<tr><td>TD_LANG_TCL</td> <td>"TCL"</td> <td></td>tcl</tr>
		<tr><td>TD_LANG_ASP</td> <td>"ASP"</td> <td></td>ASP</tr>
		<tr><td>TD_LANG_PHP</td> <td>"PHP"</td> <td></td>PHP</tr>
		<tr><td>TD_LANG_FORTRAN</td> <td>"Fortran"</td>Fortan<td></td></tr>
		<tr><td>TD_LANG_CSS</td> <td>"CSS"</td> <td></td>CSS</tr>		
	</table>
	*/
	String getLexerID() {
		return lexerID_;
	}

	/**
	returns a list of keywords separated by spaces, tabs, "\n" or "\r" or 
	any combination of these.
	*/
	String getLanguageKeyWords() {
		return langKeywords_;
	}

	/**
	must be paired, i.e. {} or [], etc, open char, followed by closing char.
	A complete string might look like:
	"{}[]()", or perhaps "{}<>" for html style docs
	*/
	String getBraceCharacters() {
		return braceCharacters_;
	}

	/**
	returns the auto completion characters.
	The document implementer should return a set of 
	0 or more characters which, if typed into the document
	by the text editor, would trigger an autocompletion 
	list to appear.
	For example, a C++ document might return "." to indicate 
	that a "." should display the automatic completion list
	*/
	String getAutoCompletionCharacters() {
		return autoCompletionCharacters_;
	}

	/**
	returns the call tip characters.
	The document implementer should return a set of 
	0 or more characters which, if typed into the document
	by the text editor, would trigger the call tip tooltip
	window to appear.
	For example, a C++ document might return "(" to indicate 
	that a "(" should display the call tip.
	*/
	String getCallTipCharacters() {
		return callTipCharacters_;
	}

	/**
	return a list to be used in the auto completion popup
	window. The implementer should return a list of string
	using the " " character as the separator. 
	@param ulong the position within the text document
	that the auto completion is taking place. This can be used 
	by the document implementer to determine the appropriate 
	list of strings to return
	@return String a list of strings separated by a space (" ") 
	character. The list may be empty
	*/
	virtual String getAutoCompletionList( const uint& pos ){
		return String();
	}

	/**
	returns call tip text for display.
	The implementer can return text that the text editor will use
	to display in the call tip tooltip window that will popup.
	
	@param ulong within the text document
	that the call tip is taking place. This can be used 
	by the document implementer to determine the appropriate 
	text to return

	@return String the call text. May be empty.
	*/
	virtual String getCallTipText( const ulong& pos ) {
		return String();
	}


	void setScintillaPeer( ScintillaPeer* peer ) {
		sciPeer_ = peer;
	}
	protected:
		String lexerID_;
		String langKeywords_;
		String autoCompletionCharacters_;
		String callTipCharacters_;
		String braceCharacters_;
		ScintillaPeer* sciPeer_;

		virtual void doSetText( const String& text );
		virtual void doInsertText( const uint32& index, const String& text );
		virtual void doReplaceText( const uint32& index, const uint32& count, const String& text );
		virtual void doRemoveText( const uint32& index, const uint32& count );

};


class ScintillaPeer {
public:
	virtual ~ScintillaPeer(){}

	//use -1 for start to set the text for the whole thing
	virtual void insertText( unsigned int start, const String& text ) = 0;

	virtual void removeText( unsigned int start, unsigned int length ) = 0;

	virtual unsigned int getTextLength() = 0;

	virtual String getText( unsigned int start, unsigned int length ) = 0;

	virtual uint32 getLineCount() = 0;

	virtual uint32 getCurrentLinePosition() = 0;

	virtual Point getPositionFromCharIndex( const uint32& index ) = 0;
	virtual uint32 getCharIndexFromPosition( const Point& point ) = 0;

	virtual uint32 getSelectionStart() = 0;
	virtual uint32 getSelectionCount() = 0;
	virtual void setSelectionMark( const uint32& start, const uint32& count ) = 0;

	virtual uint32 getCaretPosition() = 0;
	virtual void setCaretPosition( const uint32& caretPos ) = 0;

	virtual void setLeftMargin( const double & leftMargin ) = 0;
	virtual void setRightMargin( const double & rightMargin ) = 0;

	virtual double getLeftMargin() = 0;
	virtual double getRightMargin() = 0;

	virtual void setEditorStyle( const int& style, const ulong& foreColor, const ulong& backColor,
							const ulong& size, const String& fontFace,
							const bool& bold=false, const bool& italic=false ) = 0;

	virtual void setReadOnly( const bool& readonly ) = 0;

	virtual void print( PrintContext* context, const int32& page ) = 0;

	virtual uint32 getTotalPrintablePageCount( PrintContext* context ) = 0;

	virtual void finishPrinting() = 0;

	virtual void cut() = 0;
	virtual void copy() = 0;
	virtual void paste() = 0;

	virtual bool canUndo() = 0;
	virtual bool canRedo() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;

	virtual void setTextWrapping( const bool& val ) = 0;
	virtual bool getTextWrapping() = 0;
};


/**
* the control for advanced editing of any type of text.
* It has the framework for real time processing
* of text typed by the user.
*@see DocBookEditor
*@see VCFBuilder::ContentProcessingThread
*/
class SCINTILLAKIT_API SciTextControl : public Control { 
public:
	/**
	*
	*
	*/
	enum TextEditorEvent{
		teTextEntryModeChanged = 0x100601
	};

	enum TextEntryMode{
		temOverwrite = 0,
		temInsert
	};

	SciTextControl();

	virtual ~SciTextControl();

public:
	virtual bool isLightWeight() {
		return false;
	}

	virtual void paint( GraphicsContext * context );

	void setCaretPosition( const unsigned long& caretPos );

	void setEditorStyle( const int& style, const ulong& foreColor, 
							const ulong& backColor, const ulong& size, 
							const String& fontFace, const bool& bold=false, 
							const bool& italic=false );

	
	ulong getLineFromPosition( ulong pos );

	ulong getColumnFromPosition( ulong pos );

	void gotoLineNumber( ulong linNumber );

	TextEntryMode getEntryMode() {
		return entryMode_;
	}

	void setEntryMode( TextEntryMode val );

	virtual void handleEvent( Event* e );

	virtual void modelChanged( Model* oldModel, Model* newModel );

	SciTextModel* getTextModel();
	/**
	* restarts the timer.
	* It is called from the peer when he receives the message
	* that the text has been modified.
	*/
	void startTypingTimer();

	/**
	* disables the timer.
	* It is called at each timer pulse.
	*/
	void stopTypingTimer();

protected:
	/**
	* called by the timer.
	* First it disable the timer.
	* It then takes all the latest job done by the user
	* while typing, stored in contentQueue_, and
	* move it to a vector of ContentLocation(s)
	* that is then processed by the application through
	* a thread that is awakened in order to do the job.
	*@see DocBookDocument::createContentForEdit()
	*@see VCFBuilder::ContentProcessingThread
	*@see VCFBuilderApp::processContentRangeOnDocument()
	*/
	void onTypingTimeout( Event* e );

	/**
	* 
	*
	*/
	void onDocumentChanged( ModelEvent* e );

protected:

	//TextDocument* model_;

	/**
	* the queue of the latest job done by the user
	* stored in ContentLocation(s) blocks.
	*/
	//std::deque<ContentLocation*> contentQueue_;

	/**
	*
	*
	*/
	TextEntryMode entryMode_;

	/**
	* the timer pulsing every second an event
	* caught by onTypingTimeout()
	* @see SciTextControl::onTypingTimeout()
	*/
	TimerComponent* typingTimer_;
};





/*

extern "C" {

SCINTILLAKIT_API void _vpl_init();

};

*/


}; //end of namespace VCFBuilder




#endif // _VCF_SCINTILLAKIT_H__


