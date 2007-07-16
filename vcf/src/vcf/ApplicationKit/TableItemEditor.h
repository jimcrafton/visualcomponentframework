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
\class TableItemEditor TableItemEditor.h "vcf/ApplicationKit/TableItemEditor.h"
The TableItemEditor class is used to provide editing capabilities
for individual cell items in a TableControl. When the TableControl
detects that an event has occurred to start an edit, it calls the 
respective TableCellItem's createItemEditor() method. This will 
create a new instance of a TableItemEditor, as appropriate
for that cell. A simple implementation of this interface can
be found in the BasicTableItemEditor class. 

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
	DELEGATE(ItemEditorDelegate,CellItemChanged);

	/**
	@delegate CellItemValidateChange
	@event ItemEditorEvent
	@eventtype ITEMEDITOR_CHANGED
	*/
	DELEGATE(ItemEditorDelegate,CellItemValidateChange);
	

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


#endif // _VCF_TABLEITEMEDITOR_H__

/**
$Id$
*/
