#ifndef _VCF_BASICTABLEITEMEDITOR_H__
#define _VCF_BASICTABLEITEMEDITOR_H__
//BasicTableItemEditor.h

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



#ifndef _VCF_TABLEITEMEDITOR_H__
#	include "vcf/ApplicationKit/TableItemEditor.h"
#endif // _VCF_TABLEITEMEDITOR_H__

#ifndef _VCF_TABLECELLITEM_H__
#	include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__

#ifndef _VCF_TEXTCONTROL_H__
#	include "vcf/ApplicationKit/TextControl.h"
#endif // _VCF_TEXTCONTROL_H__



namespace VCF {

class TableCellItem;

class TextModelHandler;

class TextEvent;


#define BASICTABLEITEMEDITOR_CLASSID		"7E202381-F9EB-4585-9685-889FA9B07D47"

/**
BasicTableItemEditor represents a simple implementation of the TableItemEditor
interface.
@delegates:
	@del BasicTableItemEditor::CellItemChanged
	@del BasicTableItemEditor::CellItemValidateChange
*/
class APPLICATIONKIT_API BasicTableItemEditor : public TableItemEditor {
public:	
	BasicTableItemEditor( TableCellItem* editingItem );

	virtual ~BasicTableItemEditor();

	virtual TableCellItem* getItemToEdit(){
		return 	editingItem_;
	}

	virtual void updateItem();

	virtual Control* getEditingControl();
protected:
	TableCellItem* editingItem_;
	Control* editingControl_;

	void onEditorTextChanged( TextEvent* event );

	
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/26 20:59:28  ddiego
*some fixes to table control and to teh table item editor interface
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.16.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.16  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.15.2.3  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.15.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.15.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.15  2003/08/09 02:56:42  ddiego
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
*Revision 1.14.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.14  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.1  2003/03/12 03:09:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.12.14.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.12  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.2  2002/04/27 15:41:47  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.11.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.11  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_BASICTABLEITEMEDITOR_H__


