#ifndef _VCF_DEFAULTTEXTMODEL_H__
#define _VCF_DEFAULTTEXTMODEL_H__
//DefaultTextModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_ABSTRACTMODEL_H__
#	include "vcf/ApplicationKit/AbstractModel.h"
#endif // _VCF_ABSTRACTMODEL_H__


#ifndef _VCF_ABSTRACTTEXTMODEL_H__
#	include "vcf/ApplicationKit/AbstractTextModel.h"
#endif // _VCF_ABSTRACTTEXTMODEL_H__


namespace VCF{

#define DEFAULTTEXTMODEL_CLASSID		"8B2CDC32-3CAD-11d4-B553-00C04F0196DA"

class APPLICATIONKIT_API DefaultTextModel : public AbstractModel, public TextModel {
public:


    DefaultTextModel();

	virtual ~DefaultTextModel();

	/**
	@delegate TextModelChanged fired when the model's text data is changed
	@event TextModelEvent
	*/
	DELEGATE(TextModelChanged)

	virtual void addTextModelChangedHandler( EventHandler * handler ){
		TextModelChanged += handler;
	}

	virtual void removeTextModelChangedHandler( EventHandler * handler ) {
		TextModelChanged -= handler;
	}



    /**
     * clears out the model's data
     */
    virtual void empty();

	/**
	*sets the contents of the text model, completely changes what was previously
	*in the model
	*/
    virtual void setText( const String& text );

	/**
	*inserts text into the model at the given index
	*@param long the starting point to begin inserting the text. This number represents
	*a zero based index.
	*@param String the text to insert
	*/
    virtual void insertText( const unsigned long& index, const String& text );

	/**
	*replace text into the model in place of the selected text is any,
	*or at the current position otherwise
	*@param String the text to replace with
	*/
    virtual void replaceText( const unsigned long& index, const unsigned long& len, const String& text );

	/**
	*deletes text from the model, starting at index, and continuing for count characters,
	*or until the text data is empty.
	*@param long the starting point. The index is zero based.
	*@param long the number of characters to delete
	*/
    virtual void deleteText( const unsigned long& index, const unsigned long& count );

	/**
	*adds text to end of the current text data
	*/
    virtual void appendText( const String& text );

	/**
	*returns all of the TextModel's text in a string.
	*/
	virtual String getText();

	/**
	*returns the size of the TextModel
	*/
	virtual unsigned long getSize();

protected:
	String text_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/05 00:35:41  ddiego
*fixed the way the DefaulttextModel is implemented. Got rid of the need for teh AbsractTextModel class, we should delete it.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.11.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.10.2.1  2004/03/21 19:44:38  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.7  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:42:14  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.6.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTEXTMODEL_H__


