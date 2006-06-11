#ifndef _VCF_OSXTEXTEDITPEER_H__
#define _VCF_OSXTEXTEDITPEER_H__
//OSXTextEditPeer.h
//
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/OSXTextPeer.h"



namespace VCF
{

class TextEvent;


class OSXTextEditPeer : public OSXControl, 
					public TextEditPeer, public OSXTextPeer {

public:

	enum EditState {
		esMultiLined =				0x0001,
		esStyleChanging =			0x0010,
		esPeerTextChanging =		0x0100,
		esModelTextChanging =		0x0200,
		esExternalTextChanging =	0x0400, /* means something like undo/redo/cut/paste */
		esKeyEvent =				0x1000
	};


	OSXTextEditPeer( TextControl* component, const bool& isMultiLineControl );

	virtual ~OSXTextEditPeer();

	virtual void create( Control* owningControl );
	
	virtual void setText( const VCF::String& text );

	virtual VCF::String getText();

	virtual void repaint( Rect* repaintRect=NULL );
	
	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );

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
	TextControl* textControl_;
	int editState_;
	VCF::Point ptAtCharPos_;
	
	bool stateAllowsModelChange();

	void onTextModelTextChanged( TextEvent* event );

	void onTextControlFontChanged( Event* event );
	
	void onControlModelChanged( Event* e );

	static uint32 convertCharToVKCode( VCFChar ch );	
};


}; // namespace VCF


#endif // _VCF_OSXTEXTEDITPEER_H__

/**
$Id$
*/
