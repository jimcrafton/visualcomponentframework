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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:59  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/04/30 11:52:36  marcelloptr
*added a comment for the enabledSetTextOnControl_ member variable
*
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.2.10.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/09 05:38:54  ddiego
*added a VERY simple editable text control. It is dog slow though, but
*better than nothing.
*
*Auto generated header for class X11SimpleTextControl
*/


#endif // _VCF_X11SIMPLETEXTCONTROL_H__


