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


#include "vcf/ApplicationKit/TextPeer.h"

namespace VCF
{

class TextEvent;

class Win32Edit : public AbstractWin32Component, public VCF::TextPeer
{

public:
	Win32Edit( TextControl* component, const bool& isMultiLineControl );

	virtual ~Win32Edit();

	virtual void create( Control* owningControl );
    /**
     * sets the text for the widget
     */
    virtual void setText( const VCF::String& text );

    virtual void setRightMargin( const double & rightMargin );

	virtual void setLeftMargin( const double & leftMargin );

    virtual unsigned long getLineCount();

    virtual unsigned long getCurrentLinePosition();

	virtual void setCaretPosition( const unsigned long& caretPos );

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

	virtual void createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	void onTextModelTextChanged( TextEvent* event );

	virtual unsigned long getSelectionStart();

	virtual unsigned long getSelectionCount();

	virtual void setSelectionMark( const unsigned long& start, const unsigned long& count );

	virtual void setSelectionFont( Font* font );

	virtual void setParagraphAlignment( const TextAlignmentType& alignment );

	virtual void scrollToLine( const ulong32& lineIndex );

	virtual void scrollToSelection( const bool& _showEndSel = false );

	virtual void setReadOnly( const bool& readonly );

	virtual void repaint( Rect* repaintRect=NULL );

	virtual bool acceptsWMCommandMessages() {
		return true;
	}

	virtual void print( PrintContext* context, const long& page );

	virtual void finishPrinting();

	virtual ulong32 getTotalPrintablePageCount( PrintContext* context );
protected:
	//WNDPROC oldEditWndProc_;
	VCF::Point posAtChar_;
	HBRUSH backgroundBrush_;

	//unsigned long currentPos_; //JC - I commented this out - it wasn't being used
	int currentSelLength_;
	int currentSelStart_;

	TextControl* textControl_;
	bool isRichedit_;
	bool isMultiLined_;

	ulong32 numCharsRemainingToStreamIn_;
	void processTextEvent( VCFWin32::KeyboardData keyData, WPARAM wParam, LPARAM lParam );

	bool OKToResetControlText_;

	std::map<ulong32,ulong32> printPageMap_;

	/**
	this is a fix from Marcello to work around an apparent bug in Win32's handling of
	crlf's
	*/
	int getCRCount( const unsigned long& begin, const unsigned long& end, const bool& limitCountsAreExact );
	void getSelectionMark( unsigned long & start, unsigned long & count );

	void onControlModelChanged( Event* e );
	
	

	static DWORD CALLBACK EditStreamCallback( DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/11/19 05:54:28  ddiego
*added some fixes to the text peer for win32 for printing. added toolbars to text edit example anmd added printing
*
*Revision 1.2.2.3  2004/11/18 06:45:44  ddiego
*updated toolbar btn bug, and added text edit sample.
*
*Revision 1.2.2.2  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.20.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.20  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.19.2.1  2004/03/21 19:44:57  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.19  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.5  2003/12/02 22:11:30  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.18.2.4  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.18.2.3  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.18.2.2  2003/08/17 18:18:06  ddiego
*added some of Marcellos fixes, notably the one to fix CRLF problems in teh
*edit control
*
*Revision 1.18.2.1  2003/08/12 20:30:32  marcelloptr
*improvement: multiline editor - scrollToSelection
*
*Revision 1.18  2003/08/09 02:56:44  ddiego
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
*Revision 1.17.2.2  2003/06/13 03:04:31  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.17.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.17  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16.2.1  2003/03/12 03:11:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.14.1  2003/01/08 00:19:46  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.15  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/04/27 15:52:19  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.14  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32EDIT_H__


