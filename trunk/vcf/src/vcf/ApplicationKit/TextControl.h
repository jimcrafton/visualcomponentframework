#ifndef _VCF_TEXTCONTROL_H__
#define _VCF_TEXTCONTROL_H__
//TextControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__


#ifndef _VCF_TEXTEVENT_H__
#	include "vcf/ApplicationKit/TextEvent.h"
#endif // _VCF_TEXTEVENT_H__


namespace VCF {


class TextEditPeer;
class Dictionary;


#define TEXTCONTROL_CLASSID			"ED88C09E-26AB-11d4-B539-00C04F0196DA"
/**
\class TextControl TextControl.h "vcf/ApplicationKit/TextControl.h"
The base class for presenting text to the user. The text can be 
plain text, or styled text, i.e. text with multiple styles.

The TextControl is only for editing or presenting a single line of text.
For editing multiple lines of text, please see the MultilineTextControl.

All text controls contain a TextModel, that stores the actual text 
data.
@see MultilineTextControl
@see TextModel
*/
class APPLICATIONKIT_API TextControl : public Control {
public:

	DELEGATE(SelectionChanged);

	TextControl( const bool& multiLineControl=false );
	virtual ~TextControl();

	void init();

	virtual void paint( GraphicsContext * context );

	void setTextModel( TextModel * model );

	TextModel* getTextModel();

	unsigned long getCaretPosition() ;

	void setCaretPosition( const unsigned long& caretPos );

	void setRightMargin( const double & rightMargin );

	void setLeftMargin( const double & leftMargin );

	unsigned long getLineCount();

	unsigned long getCurrentLinePosition();

	double getLeftMargin();

	double getRightMargin();

	Point* getPositionFromCharIndex( const unsigned long& index );

	unsigned long getCharIndexFromPosition( Point* point );

	/**
	*returns the zero based index that indicates where the current selection begins.
	*It may be the same index that getCaretPosition() returns
	*/
	unsigned long getSelectionStart();

	/**
	gives the number of characters selected.
	@return unsigned long, the number of characters selected, a return value
	of 0 indicates that no characters are currently selected.
	*/
	unsigned long getSelectionCount();

	void setSelectionMark( const unsigned long& start, const unsigned long& count );

	void selectAll();

	void getStyle( unsigned int start, unsigned int length, Dictionary& styles, Color& color );

	void setStyle( unsigned int start, unsigned int length, Dictionary& styles );

	void setDefaultStyle( Dictionary& styles );

	String getSelectedText();

	void replaceSelectedText( const String& text );

	virtual bool keepsTabbingCharacters() {
		return keepTabbingCharacters_;
	}

	void setKeepTabbingCharacters( const bool& keepTabChars ) {
		keepTabbingCharacters_ = keepTabChars;
	}

	virtual bool keepReturnCharacter() {
		return keepReturnCharacter_;
	}

	void setKeepReturnCharacter( const bool& keepReturn ) {
		keepReturnCharacter_ = keepReturn;
	}

	virtual double getPreferredHeight();

	virtual void handleEvent( Event* event );

	bool getReadOnly() {
		return readOnly_;
	}

	void setReadOnly( const bool& val );

	virtual bool supportsMultiLinedText() {
		return false;
	}

	/**
	Call this function to disable the standard, built-in,
	accelerator's that make sure the platforms standard 
	shortcut's for cut, copy, paste, undo, and redo get
	handled by the underlying platform. You may choose
	to turn these off if your use of a text control
	provides more advanced cut/copy/paste/undo/redo support.
	If you're using the DocView arcichtecture you'll
	almost certainly want to turn them off.
	*/
	void disableStandardAccelerators();

	/**
	Call this function to enable the standard, built-in,
	accelerator's that make sure the platforms standard 
	shortcut's for cut, copy, paste, undo, and redo get
	handled by the underlying platform.
	By default these are enabled for every text control.
	*/
	void enableStandardAccelerators();

	/**
	Cuts the selection and places it in the clipboard.
	This uses the standard cut implementation provided by the
	underlying windowing platform. 
	*/
	void cut();

	/**
	Copies the selection and places it in the clipboard.
	This uses the standard copy implementation provided by the
	underlying windowing platform. 
	*/
	void copy();

	/**
	Pastes the contents of the clipboard into the text control.
	This uses the standard paste implementation provided by the
	underlying windowing platform. 
	*/
	void paste();

	/**
	Returns a bool to indicate whether or not an undo operation can be
	performed. 
	@return bool true if an an undo operation can be performed. This 
	indicates that a call to undo() will succeed. Returns false to 
	indicate no undo is possible and any calls to undo() will
	be no-ops.
	*/
	bool canUndo();

	/**
	Returns a bool to indicate whether or not a redo operation can be
	performed. 
	@return bool true if an a redo operation can be performed. This 
	indicates that a call to redo() will succeed. Returns false to 
	indicate no redo is possible and any calls to redo() will
	be no-ops.
	*/
	bool canRedo();

	/**
	Undoes the last operation.
	This uses the standard undo implementation provided by the
	underlying windowing platform. 
	*/
	void undo();

	/**
	Redoes the last operation.
	This uses the standard redo implementation provided by the
	underlying windowing platform. 
	*/
	void redo();

	/**
	This toggles word wrapping. If you turn off word wrapping
	the scroll bars will show up autmatically (if they are needed).
	If you turn on word wrapping the scroll bars will disapear.
	*/
	void setTextWrapping( const bool& val );
protected:
	/**
	handlers of some standard accelerator events.
	*/
	void undoAccelerator( Event* e );
	void redoAccelerator( Event* e );
	void cutAccelerator( Event* e );
	void copyAccelerator( Event* e );
	void pasteAccelerator( Event* e );
	void selectAllAccelerator( Event* e );

	/**
	handler called when the control is getting the focus.
	By default it is added only to a single line control,
	so we can select all the text whenever we get the focus.
	*/
	virtual void gotFocus( FocusEvent* event );

protected:
	TextEditPeer * textPeer_;
	TextModel* model_;
	bool keepTabbingCharacters_;
	bool keepReturnCharacter_;
	bool readOnly_;

};

}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.4  2006/03/21 00:57:35  ddiego
*fixed bug in table control - problem was really with casting a
*model to a table model, and having the pointer value not be right. Needed
*to use dynamic_cast() to fix it. Curiously this problem was not flagegd in
*debug at all.
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
*Revision 1.4  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.11  2005/06/09 03:40:38  marcelloptr
*removed a forgotten comment
*
*Revision 1.3.2.10  2005/06/09 02:25:50  ddiego
*updated osx build
*
*Revision 1.3.2.9  2005/06/07 17:23:53  marcelloptr
*added missed getStyle() function. Fixed underline text that couldn't be removed once introduced.
*
*Revision 1.3.2.8  2005/05/20 03:04:05  ddiego
*minor mods to set focused control.
*
*Revision 1.3.2.7  2005/05/19 22:07:45  marcelloptr
*Fixes around Win32Edit: selectAll and Redo operation. Deleting characters. Going to get read of getCRCount :)
*
*Revision 1.3.2.6  2005/05/16 16:02:00  marcelloptr
*minor change on doc
*
*Revision 1.3.2.5  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.4  2005/04/25 00:11:57  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.3.2.3  2005/03/28 18:07:37  marcelloptr
*minor fixes or comments
*
*Revision 1.3.2.1  2005/03/27 05:25:13  ddiego
*added more fixes to accelerator handling.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/03 22:47:33  ddiego
*fixed a text model bug that incorectly handled deleting chars.
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
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
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
*Revision 1.19.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.19  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.18.2.1  2004/03/21 19:44:38  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.18  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.17.2.5  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.17.2.4  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.17.2.3  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.17.2.2  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.17.2.1  2003/08/23 02:01:23  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.17  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.16.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.16  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.1  2003/03/12 03:09:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.2.3  2002/12/27 23:04:32  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.14.2.2  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.14.2.1  2002/12/25 22:06:20  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.14  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.13.8.1  2002/11/16 19:37:47  ddiego
*this fixes bug [ 635840 ] Some control eat text events in Design mode.
*All that needed doing was adding an overridden handleEvents() to the TextControl
*and doing some moving around of code in the Win32Edit code.
*
*Revision 1.13  2002/06/24 04:24:49  ddiego
*mods to VCFBuilder
*
*Revision 1.12  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.1  2002/04/27 15:42:57  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.11  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TEXTCONTROL_H__


