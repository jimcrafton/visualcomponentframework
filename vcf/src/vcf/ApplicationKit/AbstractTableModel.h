#ifndef _VCF_ABSTRACTTABLEMODEL_H__
#define _VCF_ABSTRACTTABLEMODEL_H__
//AbstractTableModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABLEMODEL_H__
#	include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__


#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__


namespace VCF {

#define ABSTRACTTABLEMODEL_CLASSID		"BCA97CD4-6567-11d4-8EFF-00207811CFAB"



/**
*An AbstractTableModel repersents a basic implementation of a
*TableModel. It is intended to serve as a starting point for
*concrete TableModel dereived classes and should never be
*instantiated directly. It handles some of the common chores
*such as setting up the event handling routines.
*@see TableModel
*@see DefaultTableModel
*@version 1.0
*@author Jim Crafton

@delegates
	@del AbstractTableModel::ModelEmptied
	@del AbstractTableModel::ModelValidate
	@del AbstractTableModel::TableCellAdded
	@del AbstractTableModel::TableCellDeleted
	@del AbstractTableModel::TableRowAdded
	@del AbstractTableModel::TableRowDeleted
	@del AbstractTableModel::TableColumnAdded
	@del AbstractTableModel::TableColumnDeleted
*/
class APPLICATIONKIT_API AbstractTableModel : public TableModel{
public:

	AbstractTableModel();

	virtual ~AbstractTableModel();

	/**
	@delegate ModelEmptied fired when the model's empty() method is
	called.
	@event ModelEvent
	@see empty()
	*/
	DELEGATE(ModelEmptied)

	/**
	@delegate ModelValidate fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(ModelValidate)


    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -= handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied -= handler;
	}

	/**
	@delegate TableCellAdded
	@event TableModelEvent
	*/
	DELEGATE(TableCellAdded)

	/**
	@delegate TableCellDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableCellDeleted)

	/**
	@delegate TableRowAdded
	@event TableModelEvent
	*/
	DELEGATE(TableRowAdded)

	/**
	@delegate TableRowDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableRowDeleted)

	/**
	@delegate TableColumnAdded
	@event TableModelEvent
	*/
	DELEGATE(TableColumnAdded)

	/**
	@delegate TableColumnDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableColumnDeleted)

	virtual void addTableCellAddedHandler( EventHandler* handler ){
		TableCellAdded += handler;
	}

	virtual void removeTableCellAddedHandler( EventHandler* handler ){
		TableCellAdded -= handler;
	}

	virtual void addTableCellDeletedHandler( EventHandler* handler ) {
		TableCellDeleted += handler;
	}

	virtual void removeTableCellDeletedHandler( EventHandler* handler ) {
		TableCellDeleted -= handler;
	}

	virtual void addTableRowAddedHandler( EventHandler* handler ) {
		TableRowAdded += handler;
	}

	virtual void removeTableRowAddedHandler( EventHandler* handler ) {
		TableRowAdded -= handler;
	}

	virtual void addTableRowDeletedHandler( EventHandler* handler ) {
		TableRowDeleted += handler;
	}

	virtual void removeTableRowDeletedHandler( EventHandler* handler ) {
		TableRowDeleted -= handler;
	}

	virtual void addTableColumnAddedHandler( EventHandler* handler ) {
		TableColumnAdded += handler;
	}

	virtual void removeTableColumnAddedHandler( EventHandler* handler ) {
		TableColumnAdded -= handler;
	}

	virtual void addTableColumnDeletedHandler( EventHandler* handler ) {
		TableColumnDeleted += handler;
	}

	virtual void removeTableColumnDeletedHandler( EventHandler* handler ) {
		TableColumnDeleted -= handler;
	}

	virtual void addRow();

	virtual void insertRow( const uint32& afterRow );

	virtual void deleteRow( const uint32& row );

    virtual void addColumn();

	virtual void insertColumn( const uint32& afterColumn );

	virtual void deleteColumn( const uint32& column );

	virtual bool isCellEditable( const uint32& row, const uint32& column );

	virtual TableCellItem* getItem( const uint32& row, const uint32& column );

	virtual uint32 getRowCount();

	virtual uint32 getColumnCount();
};

}; //end of namespace VCF


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
*Revision 1.13.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.6.2  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.12.6.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.14.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.11.14.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.11  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.2  2002/04/27 15:41:45  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.10.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.10  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTTABLEMODEL_H__


