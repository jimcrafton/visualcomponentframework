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


namespace VCF{

/** @interface */

/**
*A interface for supporting text controls
*This results in a native text control widget being
*created, with all painting responsibilities being
*controlled by the native widget. This means that
*some advanced graphics features and Font capabilities
*may not appear in the control. FOr example, setting
*the Font's setShear() method will have no effect
*on the widget's rendering of it's text.
*@version 1.0
*author Jim Crafton
*/
class APPLICATIONKIT_API TextPeer : public VCF::Interface {
public:
	virtual void setRightMargin( const double & rightMargin ) = 0;

	virtual void setLeftMargin( const double & leftMargin ) = 0;

	virtual unsigned long getLineCount() = 0;

	virtual unsigned long getCurrentLinePosition() = 0;

	virtual double getLeftMargin() = 0;

	virtual double getRightMargin() = 0;

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

	virtual void setSelectionFont( Font* font ) = 0;

	virtual void setParagraphAlignment( const TextAlignmentType& alignment ) = 0;

	virtual void scrollToLine( const ulong32& lineIndex ) = 0;

	virtual void scrollToSelection( const bool& showEndSel = false ) = 0;

	virtual void setReadOnly( const bool& readonly ) = 0;
};

};


/**
*CVS Log info
*$Log$
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


