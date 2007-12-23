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



class TextEvent;


#define BASICTABLEITEMEDITOR_CLASSID		"7E202381-F9EB-4585-9685-889FA9B07D47"

/**
\class BasicTableItemEditor BasicTableItemEditor.h "vcf/ApplicationKit/BasicTableItemEditor.h"
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


#endif // _VCF_BASICTABLEITEMEDITOR_H__

/**
$Id$
*/
