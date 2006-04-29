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


#endif // _VCF_ABSTRACTTABLEMODEL_H__

/**
$Id$
*/
