#ifndef _VCF_WIN32EDIT_H__
#define _VCF_WIN32EDIT_H__
//Win32Edit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/Win32TextPeer.h"



namespace VCF
{

class TextEvent;
class Win32RichEditOleCallback;


class Win32Edit : public AbstractWin32Component, 
					public VCF::TextEditPeer, public Win32TextPeer {

public:

	enum EditState {
		esMultiLined =				0x0001,
		esStyleChanging =			0x0010,
		esPeerTextChanging =		0x0100,
		esModelTextChanging =		0x0200,
		esExternalTextChanging =	0x0400, /* means something like undo/redo/cut/paste */		
		esKeyEvent =				0x1000
	};


	Win32Edit( TextControl* component, const bool& isMultiLineControl );

	virtual ~Win32Edit();

	virtual void create( Control* owningControl );
	/**
	* sets the text for the widget
	*/
	virtual void setText( const VCF::String& text );

	virtual VCF::String getText();

	virtual CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void repaint( Rect* repaintRect=NULL );

	virtual bool acceptsWMCommandMessages() {
		return true;
	}


	//TextPeer interface

	virtual OSHandleID getTextObjectHandle();

	//storage
	virtual void insertText( unsigned int start, const String& text );

	virtual void deleteText( unsigned int start, unsigned int length );

	virtual unsigned int getTextLength();

	virtual String getText( unsigned int start, unsigned int length );


	//display
	virtual void paint( GraphicsContext* context, const Rect& paintRect );

	virtual void setRightMargin( const double & rightMargin );

	virtual void setLeftMargin( const double & leftMargin );

	virtual void setTopMargin( const double & topMargin );

	virtual void setBottomMargin( const double & bottomMargin );

	virtual double getLeftMargin();

	virtual double getRightMargin();

	virtual double getTopMargin();

	virtual double getBottomMargin();

	virtual unsigned long getLineCount();

	virtual Rect getContentBoundsForWidth(const double& width);

	virtual void setStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void getStyle( unsigned int start, unsigned int length, Dictionary& styles );

	virtual void setDefaultStyle( Dictionary& styles );






	virtual Point* getPositionFromCharIndex( const unsigned long& index );

	virtual unsigned long getCharIndexFromPosition( Point* point );

	virtual unsigned long getCaretPosition();

	virtual void setCaretPosition( const unsigned long& caretPos );

	virtual unsigned long getCurrentLinePosition();



	virtual unsigned long getSelectionStart();

	virtual unsigned long getSelectionCount();

	virtual void setSelectionMark( const unsigned long& start, const unsigned long& count );

	virtual void clearSelection();

	virtual void scrollToLine( const ulong32& lineIndex );

	virtual void scrollToSelection( const bool& _showEndSel = false );

	virtual void setReadOnly( const bool& readonly );



	virtual void print( PrintContext* context, const long& page );

	virtual void finishPrinting();

	virtual ulong32 getTotalPrintablePageCount( PrintContext* context );

	virtual void cut();

	virtual void copy();

	virtual void paste();

	virtual bool canUndo();

	virtual bool canRedo();

	virtual void undo();

	virtual void redo();

	virtual void setTextWrapping( const bool& val ); 
protected:
	VCF::Point posAtChar_;
	HBRUSH backgroundBrush_;
	int currentSelLength_;
	int currentSelStart_;
	TextControl* textControl_;
	int editState_;
	std::map<ulong32,ulong32> printPageMap_;
	Win32RichEditOleCallback* richEditCallback_;//only needed in readonly mode

	bool stateAllowsModelChange();

	void onTextModelTextChanged( TextEvent* event );

	/**
	this is a fix from Marcello to work around an apparent bug in Win32's handling of
	crlf's
	*/
	int getCRCount( const unsigned long& begin, const unsigned long& end, const bool& limitCountsAreExact );
	void getSelectionMark( unsigned long & start, unsigned long & end );

	void onControlModelChanged( Event* e );

	//static DWORD CALLBACK EditStreamCallback( DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb );
};


}; // namespace VCF


#endif // _VCF_WIN32EDIT_H__

/**
$Id$
*/
