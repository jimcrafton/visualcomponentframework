#ifndef _VCF_X11SIMPLETEXTCONTROL_H__
#define _VCF_X11SIMPLETEXTCONTROL_H__
//X11SimpleTextControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_X11CONTROL_H__
#	include "vcf/ApplicationKit/X11Control.h"
#endif // _VCF_X11CONTROL_H__

#ifndef _VCF_TEXTPEER_H__
#	include "vcf/ApplicationKit/TextPeer.h"
#endif // _VCF_TEXTPEER_H__

namespace VCF {


class TextEvent;

/**
X11SimpleTextControl
*/
class X11SimpleTextControl : public X11Control, public TextPeer {
public:

	X11SimpleTextControl( TextControl* component, const bool& isMultiLineControl );

	virtual ~X11SimpleTextControl();

	virtual void handleEvent( XEvent* x11Event );

	virtual String getText();

	virtual void setText( const String& text );

	virtual void handlePaintEvent();

	virtual void setRightMargin( const double & rightMargin );

	virtual void setLeftMargin( const double & leftMargin );

	virtual unsigned long getLineCount();

	virtual unsigned long getCurrentLinePosition();

	virtual double getLeftMargin();

	virtual double getRightMargin();

	virtual Point* getPositionFromCharIndex( const unsigned long& index );

	virtual unsigned long getCharIndexFromPosition( Point* point );

	/**
	*returns the current caret position with in the text control
	*this is specified by a zero based number representing the
	*insertion point with the text control's text (stored in the text
	*control's Model).
	*@return long the index of the current insertion point in the Model's text
	*/
	virtual unsigned long getCaretPosition();

	virtual void setCaretPosition( const unsigned long& caretPos );

	/**
	*returns the zero based index that indicates where the current selection begins
	*may be the same index that getCaretPosition() returns
	*/
	virtual unsigned long getSelectionStart();

	/**
	*returns the number of characters selected
	*@return unsigned long the number of characters selected, a return value of 0
	*indicates that no characters are currently selected
	*/
	virtual unsigned long getSelectionCount();

	virtual void setSelectionMark( const unsigned long& start, const unsigned long& count );

	virtual void setSelectionFont( Font* font );

	virtual void setParagraphAlignment( const TextAlignmentType& alignment );

	virtual void scrollToLine( const ulong32& lineIndex );

protected:
	void onTextModelTextChanged( TextEvent* event );

	String text_;
	ulong32 currentLinePos_;
	Point posAtChar_;
	ulong32 selectionStart_;
	ulong32 selectionEnd_;

	/**
	this is introduced in order to prevent getting into a stack overflow situation 
	due to infinite callback from the TextModel::setText() 
	Set this to false to prevent the control to change its content when the text model is changed,
	but remember to set it back to true when not necessary anymore.
	*/
	bool enabledSetTextOnControl_;

	double leftMargin_;
	double rightMargin_;
};


}; // end of namespace VCF


#endif // _VCF_X11SIMPLETEXTCONTROL_H__

/**
$Id$
*/
