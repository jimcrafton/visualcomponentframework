#ifndef _VCF_ABSTRACTTEXTMODEL_H__
#define _VCF_ABSTRACTTEXTMODEL_H__
//AbstractTextModel.h

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


namespace VCF
{

#define ABSTRACTTEXTMODEL_CLASSID	"8B2CDC33-3CAD-11d4-B553-00C04F0196DA"


/**
*An AbstractTextModel repersents a basic implementation of a
*TextModel. It is intended to serve as a starting point for
*concrete TextModel dereived classes and should never be
*instantiated directly. It handles some of the common chores
*such as setting up the event handling routines, and getting and
*setting text.
*@see TextModel
*@see DefaultTextModel
*@version 1.0
*@author Jim Crafton

@delegates
	@del AbstractTextModel::ModelEmptied
	@del AbstractTextModel::ModelValidate
	@del AbstractTextModel::TextModelChanged
*/
class APPLICATIONKIT_API AbstractTextModel : public TextModel
{
public:

	AbstractTextModel();

	virtual ~AbstractTextModel();



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
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.14.2.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.2  2004/03/21 19:44:38  marcelloptr
*improvements on TextModel and getCRCount
*
*Revision 1.13.2.1  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.13  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.2  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.12.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:09:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:41:45  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.9.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.9  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTTEXTMODEL_H__


