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
	requested color
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

	virtual unsigned long getLineCount() = 0;	
	
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
	@param Color& color the instance to which the color style attribute in the dictionary is pointing to.
	*/
	virtual void getStyle( unsigned int start, unsigned int length, VCF::Dictionary& styles, VCF::Color& color ) = 0;

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

	virtual Point* getPositionFromCharIndex( const unsigned long& index ) = 0;

	virtual unsigned long getCharIndexFromPosition( Point* point ) = 0;

	/**
	*returns the current caret position with in the text control
	*this is specified by a zero based number representing the
	*insertion point with the text control's text (stored in the text
	*control's Model).
	*@return long the index of the current insertion point in the Model's text
	*/
	virtual unsigned long getCaretPosition() = 0;

	virtual void setCaretPosition( const unsigned long& caretPos ) = 0;

	virtual unsigned long getCurrentLinePosition() = 0;

	/**
	*returns the zero based index that indicates where the current selection begins
	*may be the same index that getCaretPosition() returns
	*/
	virtual unsigned long getSelectionStart() = 0;

	/**
	*returns the number of characters selected
	*@return unsigned long the number of characters selected, a return value of 0
	*indicates that no characters are currently selected
	*/
	virtual unsigned long getSelectionCount() = 0;

	/**
	*@param long the starting point. The index is zero based.
	*@param long the number of characters selected.
	*/
	virtual void setSelectionMark( const unsigned long& start, const unsigned long& count ) = 0;
	
	virtual void clearSelection() = 0;
	

	virtual void scrollToLine( const ulong32& lineIndex ) = 0;

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
	virtual ulong32 getTotalPrintablePageCount( PrintContext* context ) = 0;
	
	/**
	This attempts to print a single page and render in to the 
	printer context that's passed in.
	 
	Note that some platforms may not support this, as printing 
	support varies widely. It will work on Win32, and should work on
	Mac OS X as well.
	*/
	virtual void print( PrintContext* context, const long& page ) = 0;

	virtual void finishPrinting() = 0;	

	virtual void setTextWrapping( const bool& val ) = 0; 
};

}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.3  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.4.2.2  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.4.2.1  2006/02/22 05:00:40  ddiego
*some minor text updates to support toggling word wrap.
*
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.6  2005/06/07 17:23:53  marcelloptr
*added missed getStyle() function. Fixed underline text that couldn't be removed once introduced.
*
*Revision 1.3.2.5  2005/05/30 22:22:29  ddiego
*fixed readonly mode in text edit and added better default font change support.
*
*Revision 1.3.2.4  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.3.2.3  2005/05/02 02:31:42  ddiego
*minor text updates.
*
*Revision 1.3.2.2  2005/04/25 00:11:57  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.3.2.1  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/11/19 05:54:28  ddiego
*added some fixes to the text peer for win32 for printing. added toolbars to text edit example anmd added printing
*
*Revision 1.2.2.1  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.6.6  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.6.5  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9.6.4  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.9.6.3  2003/08/23 02:01:28  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.9.6.2  2003/08/20 19:05:26  ddiego
*some minor changes to container logic
*
*Revision 1.9.6.1  2003/08/12 20:30:32  marcelloptr
*improvement: multiline editor - scrollToSelection
*
*Revision 1.9  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.20.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TEXTPEER_H__


