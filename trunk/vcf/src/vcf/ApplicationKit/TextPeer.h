#ifndef _VCF_TEXTPEER_H__
#define _VCF_TEXTPEER_H__
//TextPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif





namespace Text {
	/**
	The "fs" prefix is for Font Style. The "ps" 
	prefix is for Paragraph Style. Note that some
	of these styles may or may not work on the 
	target platform.
	*/
	
	//font styles
	/**
	This key is associated with a string representing the font's name
	*/
	const VCF::String fsFontName = "fsFontName"; 
	
	/**
	This key is associated with a double that represents the font's 
	requested point size
	*/
	const VCF::String fsPointSize = "fsPointSize"; 
	
	/**
	This key is associated with a Color object that represents the font's 
	requested color. The value is expected to be a Color object. This 
	object should be allocated on the heap when assigned to the styles
	dictionary, and will be deleted when the styles dictionary is destroyed.
	*/
	const VCF::String fsColor = "fsColor"; 
	
	/**
	This key is associated with a bool that represents whether or not
	the font's bold is toggled on or off.
	*/
	const VCF::String fsBold = "fsBold"; 
	
	/**
	This key is associated with a bool that represents whether or not
	the font's italic is toggled on or off.
	*/
	const VCF::String fsItalic = "fsItalic"; 
	
	/**
	This key is associated with a bool that represents whether or not
	the font's strike out is toggled on or off.
	*/
	const VCF::String fsStrikeout = "fsStrikeout"; 
	
	/**
	This key is associated with an int that represents the
	font's underline state. It can be one of any of the values in
	the UnderlineTypes enum.
	*/
	const VCF::String fsUnderlined = "fsUnderlined";

	enum UnderlineTypes {
		utNone = -1,
		utSingle = 0, //the most common form to use
		utDouble,
		utDotted
	};	

	//paragraph styles
	
	/**
	This key is associated with an int that represents the
	paragraph's alignment. It can be one of any of the values in
	the ParagraphAlignment enum.	
	*/
	const VCF::String psAlignment = "psAlignment";	
	
	
	
	enum ParagraphAlignment {
		paLeft = 1,
		paCenter,
		paRight,
		paJustified
	};
};


namespace VCF  {

class Dictionary;
	

class PrintContext;

class GraphicsContext;	

class Rect;

/**
There are now two main interfaces for text - the rendering and storage of 
simple text, be it styled text, or plain text, and the editing of 
text. The TextPeer class handles the interface to the native platforms
display and storage facilities. This allows us to deal with text rendering
completely separate from the editing part, and allows us, for example, to 
create a rich text label quite easily. The TextEditPeer handles the 
extra facilities that comprise a native text edit control and inherits 
from the TextPeer interface.

Platform notes:
On Win32 this is being implemented by using the Text Object Model (TOM)
COM interfaces. On OSX we will use the Carbon Multilingual Text Engine (MLTE)
API to deal with this.
*/




/**
\class TextPeer TextPeer.h "vcf/ApplicationKit/TextPeer.h"
This is the basic text peer interface for storing and displaying text on the screen.
Printing and editing are left to the TextEditPeer interface. You can insert and remove
text with this class, as well as set the various styles of the text. You can use
this instance wherever you would like to draw basic styled text. 

*/
class APPLICATIONKIT_API TextPeer : public VCF::Interface {
public:

	/**
	Return the native text object handle. For Win32 systems this will be an
	IUnknown interface that may be queried for either ITextServices or 
	ITextDocument. For OSX this will be a TXNObject instance. 
	*/
	virtual OSHandleID getTextObjectHandle() = 0;
	
	//storage	
	virtual void insertText( unsigned int start, const String& text ) = 0;

	virtual void deleteText( unsigned int start, unsigned int length ) = 0;

	virtual unsigned int getTextLength() = 0;

	virtual String getText( unsigned int start, unsigned int length ) = 0;

	
	//display
	virtual void paint( GraphicsContext* context, const Rect& paintRect ) = 0;

	virtual void setRightMargin( const double & rightMargin ) = 0;

	virtual void setLeftMargin( const double & leftMargin ) = 0;	

	virtual void setTopMargin( const double & topMargin ) = 0;

	virtual void setBottomMargin( const double & bottomMargin ) = 0;	

	virtual double getLeftMargin() = 0;

	virtual double getRightMargin() = 0;

	virtual double getTopMargin() = 0;

	virtual double getBottomMargin() = 0;	

	virtual uint32 getLineCount() = 0;	
	
	virtual Rect getContentBoundsForWidth( const double& width ) = 0;
	
	/**
	This sets the style for the text. Pass in a Dictionary with a set of values 
	for each style attribute.
	Example:
	
	TextPeer* textPeer = ....
	
	
	Dictionary styles;
	style [Text::fsFontName] = "Arial";
	style [Text::fsPointSize] = 15.0;	
	style [Text::fsBold] = true;
	
	textPeer->setStyle( 5, 10, styles ); 
	
	this changes the font at position 5, for a length of 10, 
	to be "arial", bold and a point size of 15.
	
	*/
	virtual void setStyle( unsigned int start, unsigned int length, Dictionary& styles ) = 0;		

	/**
	gets the current style of the text.
	@param unsigned int start the beginning of the location of which we are getting the style.
	@param unsigned int length the length of the location of which we are getting the style.
	@param Dictionary& styles the dictionary storing the values for each style attribute.
	*/
	virtual void getStyle( unsigned int start, unsigned int length, VCF::Dictionary& styles ) = 0;

	/**
	call this to set the defaults for the text peer.
	If this is not called, then the default font is that
	used for label controls and the defaul paragraph alignment
	is left aligned.
	*/
	virtual void setDefaultStyle( Dictionary& styles ) = 0;
};



/**
\class TextEditPeer TextPeer.h "vcf/ApplicationKit/TextPeer.h"
*A interface for supporting text controls
*This results in a native text control widget being
*created, with all painting responsibilities being
*controlled by the native widget. 
*/

class APPLICATIONKIT_API TextEditPeer : public TextPeer {
public:

	virtual Point* getPositionFromCharIndex( const uint32& index ) = 0;

	virtual uint32 getCharIndexFromPosition( Point* point ) = 0;

	/**
	*returns the current caret position with in the text control
	*this is specified by a zero based number representing the
	*insertion point with the text control's text (stored in the text
	*control's Model).
	*@return uint32 the index of the current insertion point in the Model's text
	*/
	virtual uint32 getCaretPosition() = 0;

	virtual void setCaretPosition( const uint32& caretPos ) = 0;

	virtual uint32 getCurrentLinePosition() = 0;

	/**
	*returns the zero based index that indicates where the current selection begins
	*may be the same index that getCaretPosition() returns
	*/
	virtual uint32 getSelectionStart() = 0;

	/**
	*returns the number of characters selected
	*@return uint32 the number of characters selected, a return value of 0
	*indicates that no characters are currently selected
	*/
	virtual uint32 getSelectionCount() = 0;

	/**
	*@param uint32 the starting point. The index is zero based.
	*@param uint32 the number of characters selected.
	*/
	virtual void setSelectionMark( const uint32& start, const uint32& count ) = 0;
	
	virtual void clearSelection() = 0;
	

	virtual void scrollToLine( const uint32& lineIndex ) = 0;

	virtual void scrollToSelection( const bool& showEndSel = false ) = 0;

	virtual void setReadOnly( const bool& readonly ) = 0;
	
	/**
	Cuts the selection and places it in the clipboard
	*/
	virtual void cut() = 0;

	/**
	Copies the selection and places it in the clipboard
	*/
	virtual void copy() = 0;

	/**
	Pastes the contents of the clipboard into the text control.
	*/
	virtual void paste() = 0;

	/**
	Returns a bool to indicate whether or not an undo operation can be
	performed. 
	@return bool true if an an undo operation can be performed. This 
	indicates that a call to undo() will succeed. Returns false to 
	indicate no undo is possible and any calls to undo() will
	be no-ops.
	*/
	virtual bool canUndo() = 0;

	/**
	Returns a bool to indicate whether or not a redo operation can be
	performed. 
	@return bool true if an a redo operation can be performed. This 
	indicates that a call to redo() will succeed. Returns false to 
	indicate no redo is possible and any calls to redo() will
	be no-ops.
	*/
	virtual bool canRedo() = 0;

	/**
	Undoes the last operation
	*/
	virtual void undo() = 0;

	/**
	Redoes the last operation
	*/
	virtual void redo() = 0;
	
	
	//printing
	virtual uint32 getTotalPrintablePageCount( PrintContext* context ) = 0;
	
	/**
	This attempts to print a single page and render in to the 
	printer context that's passed in.
	 
	Note that some platforms may not support this, as printing 
	support varies widely. It will work on Win32, and should work on
	Mac OS X as well.
	*/
	virtual void print( PrintContext* context, const int32& page ) = 0;

	virtual void finishPrinting() = 0;	

	virtual void setTextWrapping( const bool& val ) = 0; 	

	virtual bool getTextWrapping() = 0;
};

}; // namespace VCF


#endif // _VCF_TEXTPEER_H__

/**
$Id$
*/
