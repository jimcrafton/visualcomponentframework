#ifndef _VCF_TABLEITEMEDITOR_H__
#define _VCF_TABLEITEMEDITOR_H__
//TableItemEditor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;

class ItemEditorListener;

class TableCellItem;

#define TABLEITEMEDITOR_CLASSID		"53EA0BA4-7068-11d4-8F12-00207811CFAB"

/**
\par
The TableItemEditor class is used to provide editing capabilities
for individual cell items in a TableControl. When the TableControl
detects that an event has occurred to start an edit, it calls the 
respective TableCellItem's createItemEditor() method. This will 
create a new instance of a TableItemEditor, as appropriate
for that cell. A simple implementation of this interface can
be found in the BasicTableItemEditor class. 
\par
The editor allows you to retrieve the item that is currently being edited.
It also allows access to the control that is used to edit the item. This
control is managed by the underlying TableControl, all you need to do is create
the control instance once. One approach might be to create the control in
your custom class's constructor. Another approach, which the BasicTableItemEditor
takes, is to set a member variable to NULL in the constructor, and then
in the implementation of getEditingControl, check the member variable, if it's
NULL, then create the control at that point and set the member variable, and then
return the member variable.
@see TableCellItem::createItemEditor
@see BasicTableItemEditor
*/
class APPLICATIONKIT_API TableItemEditor : public ObjectWithEvents {
public:

	TableItemEditor(){};

	virtual ~TableItemEditor(){};

	/**
	@delegate CellItemChanged
	@event ItemEditorEvent
	*/
	DELEGATE(CellItemChanged);

	/**
	@delegate CellItemValidateChange
	@event ItemEditorEvent
	@eventtype ITEMEDITOR_CHANGED
	*/
	DELEGATE(CellItemValidateChange);
	

	/**
	Returns an instance to the item current associated 
	with this editor.
	*/
	virtual TableCellItem* getItemToEdit() = 0;

	/**
	Updates the item to change to whatever new value has been 
	set in the editor. 
	*/
	virtual void updateItem() = 0;

    /**
	Returns a control instance that belongs to this editor. This control
	instance is managed by the table control, and it has the same life time
	as the editor that created it.
	*/
	virtual Control* getEditingControl() = 0;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/26 20:59:29  ddiego
*some fixes to table control and to teh table item editor interface
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.6.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.6.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.20.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TABLEITEMEDITOR_H__


