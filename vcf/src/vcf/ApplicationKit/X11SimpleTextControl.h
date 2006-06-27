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

	virtual uint32 getLineCount();

	virtual uint32 getCurrentLinePosition();

	virtual double getLeftMargin();

	virtual double getRightMargin();

	virtual Point* getPositionFromCharIndex( const uint32& index );

	virtual uint32 getCharIndexFromPosition( Point* point );

	/**
	*returns the current caret position with in the text control
	*this is specified by a zero based number representing the
	*insertion point with the text control's text (stored in the text
	*control's Model).
	*@return uint32 the index of the current insertion point in the Model's text
	*/
	virtual uint32 getCaretPosition();

	virtual void setCaretPosition( const uint32& caretPos );

	/**
	*returns the zero based index that indicates where the current selection begins
	*may be the same index that getCaretPosition() returns
	*/
	virtual uint32 getSelectionStart();

	/**
	*returns the number of characters selected
	*@return uint32 the number of characters selected, a return value of 0
	*indicates that no characters are currently selected
	*/
	virtual uint32 getSelectionCount();

	virtual void setSelectionMark( const uint32& start, const uint32& count );

	virtual void setSelectionFont( Font* font );

	virtual void setParagraphAlignment( const TextAlignmentType& alignment );

	virtual void scrollToLine( const uint32& lineIndex );

protected:
	void onTextModelTextChanged( TextEvent* event );

	String text_;
	uint32 currentLinePos_;
	Point posAtChar_;
	uint32 selectionStart_;
	uint32 selectionEnd_;

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
