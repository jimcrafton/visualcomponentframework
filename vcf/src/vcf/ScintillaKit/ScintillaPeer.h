#ifndef _VCFB_SCINTILLAPEER_H__
#define _VCFB_SCINTILLAPEER_H__
//ScintillaPeer.h

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/TextPeer.h"





namespace VCF {

class SciTextControl;
class ScintillaHook;

typedef int (*ScintillaFunc)(void*,int,int,int);

/**
*Class Win32ScintillaPeer documentation
*/
class Win32ScintillaPeer : public AbstractWin32Component, public ScintillaPeer {
public:
	enum IndentationStatus {
		isNone,		// no effect on indentation
		isBlockStart,	// indentation block begin such as "{" or VB "function"
		isBlockEnd,	// indentation end indicator such as "}" or VB "end"
		isKeyWordStart	// Keywords that cause indentation
	};

	struct StyleAndWords {
		int styleNumber;
		String words;
		bool isEmpty() {
			return words.size() == 0;
		}

		bool isSingleChar() {
			return words.size() == 1;
		}
	};

	Win32ScintillaPeer( SciTextControl* editorControl );

	virtual ~Win32ScintillaPeer();

	virtual void create( Control* owningControl );

	virtual void setLeftMargin( const double & leftMargin );
	virtual void setRightMargin( const double & rightMargin );

	virtual double getLeftMargin();
	virtual double getRightMargin();

	//storage
	virtual void insertText( unsigned int start, const String& text );

	virtual void removeText( unsigned int start, unsigned int length );

	virtual unsigned int getTextLength();

	virtual String getText( unsigned int start, unsigned int length );
	
	virtual uint32 getLineCount();

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setFocused();

	virtual bool isFocused();

	virtual void setControl( Control* component );

	WNDPROC getScintillaWndProc() {
		return scintillaWndProc_;
	}

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndResult, WNDPROC defaultWndProc=NULL );

	virtual uint32 getCurrentLinePosition();

	virtual Point getPositionFromCharIndex( const uint32& index );

	virtual uint32 getCharIndexFromPosition( const Point& point );

	virtual uint32 getCaretPosition();

	virtual void setCaretPosition( const uint32& caretPos );

	void onTextModelTextChanged( ModelEvent* event );

	virtual uint32 getSelectionStart();

	virtual uint32 getSelectionCount();

	virtual void setSelectionMark( const uint32& start, const uint32& count );

	virtual void clearSelection();

	virtual void scroll( int column, int line );

	virtual void scrollToLine( const uint32& lineIndex ){};

	virtual void scrollToSelection( const bool& showEndSel = false );

	virtual void setEditorStyle( const int& style, const ulong& foreColor, const ulong& backColor,
							const ulong& size, const String& fontFace,
							const bool& bold=false, const bool& italic=false );

	int sendScintillaMessage( int code, int wParam=0, int lParam=0 );


	void setAutoCompletionCharacters( const String& autoCompletionChars );

	virtual void setVisible( const bool& val );

	ulong getLineFromPosition( ulong pos );

	ulong getColumnFromPosition( ulong pos );

	ulong getFirstVisibleLine();

	ulong getLinesOnScreen();

	virtual void setReadOnly( const bool& readonly );

	virtual void print( PrintContext* context, const int32& page );

	virtual uint32 getTotalPrintablePageCount( PrintContext* context );

	virtual void finishPrinting();

	void setAutoIndent( bool val ) {
		autoIndent_ = val;
	}


	virtual void cut();

	virtual void copy();

	virtual void paste();

	virtual bool canUndo();

	virtual bool canRedo();

	virtual void undo();

	virtual void redo();

	virtual void setTextWrapping( const bool& val );

	virtual bool getTextWrapping();

	
	virtual bool getIndentMaintain() {
		return indentMaintain_;
	}

	virtual void setIndentMaintain( bool val ) {
		indentMaintain_ = val;
	}
	
	virtual uint32 getTabWidth();
	virtual void setTabWidth( const uint32& val );
	
	virtual uint32 getIndent();
	virtual void setIndent( const uint32& val );
	
	virtual bool areIndentGuidesVisible();
	virtual void setIndentGuidesVisible( const bool& val );
	
	virtual bool isWhiteSpaceVisible();
	virtual void setWhiteSpaceVisible( const bool& val );
	
	virtual bool isEOLVisible();
	virtual void setEOLVisible( const bool& val );
protected:

	friend class ScintillaHook;

	WNDPROC scintillaWndProc_;
	int braceCount_;
	bool autoCCausedByOnlyOne_;
	bool indentMaintain_;
	bool autoIndent_;
	bool autoCompleteIgnoreCase_;
	bool callTipIgnoreCase_;
	bool indentOpening_;
	bool indentClosing_;
	bool bracesCheck_;
	bool bracesSloppy_;
	int bracesStyle_;
	int lexLanguage_;
	bool internalTextChange_;
	//bool updateFromModel_;

	String calltipWordCharacters_;
	String calltipEndDefinition_;
	String autoCompleteStartCharacters_;
	String wordCharacters_;

	int statementLookback_;

	StyleAndWords statementIndent_;

	StyleAndWords statementEnd_;

	StyleAndWords blockStart_;

	StyleAndWords blockEnd_;

	SciTextControl* editorControl_;
	ScintillaFunc scintillaFunc_;
	void* scintillaObject_;
	HWND scintillaHwnd_;

	static std::map<HWND,Win32ScintillaPeer*> scintillaPeerMap;

	void braceMatch();

	int getLineLength(int line);

	void maintainIndentation( char ch );

	bool findMatchingBracePosition( int &braceAtCaret, int &braceOpposite, const bool& sloppy );

	void automaticIndentation( char ch );

	int getIndentOfBlock(int line);

	IndentationStatus getIndentState(int line);

	unsigned int getLinePartsInStyle(int line, int style1, int style2, String sv[], int len);

	void setLineIndentation(int line, int indent);

	bool rangeIsAllWhitespace(int start, int end);

	int getLineIndentation(int line);

	void foldChanged(int line, int levelNow, int levelPrev);

	void expand(int &line, bool doExpand, bool force, int visLevels=0, int level=-1 );

	void startAutoComplete( ulong pos );

	void startCallTip( ulong pos );

	void onControlModelChanged( Event* );
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.19  2006/02/26 21:11:36  ddiego
*added vc80 files and fixed some minor glitches
*in code that vc8 picked up. This should also fixe the
*problems that vc71 was encountering as well.
*
*Revision 1.18  2005/07/22 03:10:52  ddiego
*minor update for vcf changes.
*
*Revision 1.17  2005/06/09 15:46:35  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.16  2005/06/02 18:14:13  marcelloptr
*added few scrolling functions
*
*Revision 1.14  2005/05/18 17:29:00  marcelloptr
*forgotten to update insertText signature
*
*Revision 1.13  2005/05/16 04:13:43  ddiego
*vcfb updates because of vcf changes.
*
*Revision 1.12  2005/04/28 23:42:36  ddiego
*fixes for latest vcf updates
*
*Revision 1.11  2005/03/27 05:27:25  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.10  2005/02/16 05:14:42  ddiego
*fixes a number of issues, and revamps the property editor completely and makes sure it now uses the updated property editor interface.
*
*Revision 1.9  2004/12/08 04:14:18  ddiego
*added new project to auto copy the object repos from the src dir
*
*Revision 1.8  2004/10/22 01:37:15  marcelloptr
*reformatting source files in a standard way
*
*/


#endif // _VCFB_SCINTILLAPEER_H__


