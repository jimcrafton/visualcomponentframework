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

class APPLICATIONKIT_API TableItemEditor : public Object{
public:

	TableItemEditor(){};

	virtual ~TableItemEditor(){};

	virtual bool isCellEditable() = 0;

	virtual void addCellItemChangedHandler( EventHandler* handler ) = 0;

	virtual void removeCellItemChangedHandler( EventHandler* handler ) = 0;

	virtual void addCellItemValidateChangeHandler( EventHandler* handler ) = 0;

	virtual void removeCellItemValidateChangeHandler( EventHandler* handler ) = 0;

	/**
	*this is called to initialize the table item editor with some value
	*from the TableCellItem, typically the caption.
	*/
	virtual void setItemToEdit( TableCellItem* itemToEdit ) = 0;

	virtual TableCellItem* getItemToEdit() = 0;

	/**
	*updates the item passed in during the setItemToEdit() call, to
	*change to whatever new value has been set in the editor.
	*prior to the data transfer, all ItemEditorListeners should have their
	*ItemEditorListener::onValidateChange() method called. Implementers of
	*ItemEditorListener::onValidateChange() should throw an exception if
	*invalid data is detected. This can done by simply calling the
	*ItemEditrEvent's fireInvalidStateException() method.
	*the data is presumed to be stored in the Event's setUserData/getUserData
	*calls.
	*/
	virtual void updateItem() = 0;

	virtual Control* getEditingControl() = 0;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
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


