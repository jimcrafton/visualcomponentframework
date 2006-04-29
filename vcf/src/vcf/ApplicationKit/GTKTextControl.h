#ifndef _VCF_GTKTEXTCONTROL_H__
#define _VCF_GTKTEXTCONTROL_H__ 
//GTKTextControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_TEXTPEER_H__
#	include "vcf/ApplicationKit/TextPeer.h"
#endif // _VCF_TEXTPEER_H__


namespace VCF
{

class TextEvent;

/**
class GTKTextControl documentation
*/
class GTKTextControl : public AbstractGTKControl, public VCF::TextPeer
{
public:
	GTKTextControl( TextControl* component, const bool& isMultiLineControl );
	virtual ~GTKTextControl();

	virtual void create( Control* owningControl );

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

	virtual void setSelectionMark( const unsigned long& start,
	                               const unsigned long& count );

	virtual void setSelectionFont( Font* font );

	virtual void setParagraphAlignment( const TextAlignmentType& alignment );

	virtual void scrollToLine( const ulong32& lineIndex );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );

	virtual String getText();

	virtual void setText( const String& text );

	virtual void scrollToSelection( const bool& showEndSel = false );

	virtual void setReadOnly( const bool& readonly );

	virtual void setBorder( Border* border );

	virtual ulong32 getTotalPrintablePageCount( PrintContext* context );

	virtual void print( PrintContext* context, const long& page );

	virtual void finishPrinting();

protected:
	TextControl* textControl_;
	bool isMultiLineControl_;

	GtkEntry* singleLine_;
	GtkTextView* multiLine_;
	bool internalTextChange_;

	void onTextModelTextChanged( TextEvent* e );

};




};


#endif // _VCF_GTKTEXTCONTROL_H__

/**
$Id$
*/
