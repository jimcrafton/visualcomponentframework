#ifndef _VCF_DEFAULTTABLEMODEL_H__
#define _VCF_DEFAULTTABLEMODEL_H__
//DefaultTableModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABLEMODEL_H__
#include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__


#ifndef _VCF_TABLECELLITEM_H__
#include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__

#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__


namespace VCF {

#define DEFAULTTABLEMODEL_CLASSID		"53EA0BA8-7068-11d4-8F12-00207811CFAB"

class TableCellItem;

/**
\class DefaultTableModel DefaultTableModel.h "vcf/ApplicationKit/DefaultTableModel.h"
*/
class APPLICATIONKIT_API DefaultTableModel : public AbstractModel, public TableModel {
public:
	DefaultTableModel();

	virtual ~DefaultTableModel();
	
   /* These functions override those in VCF::TableModel.  This is done
	* due to a complicated multiple inheritance rule that only the
	* pedantic CodeWarrior enforces. ACH 
	* The same thing happens with Borland compiler.
	*/
#if defined(VCF_CW) || defined(VCF_BCC)
	VCF::Delegate& getTableCellAdded(){ 
		return TableCellAdded; 
	} 
	
	VCF::Delegate& getTableCellDeleted(){ 
		return TableCellDeleted; 
	} 

	VCF::Delegate& getTableRowsAdded(){ 
		return TableRowsAdded; 
	}
	
	VCF::Delegate& getTableRowsDeleted(){ 
		return TableRowsDeleted; 
	} 

	VCF::Delegate& getTableColumnsAdded(){ 
		return TableColumnsAdded; 
	}
	
	VCF::Delegate& getTableColumnsDeleted(){ 
		return TableColumnsDeleted; 
	}
#endif	
    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate();

    /**
     * clears out the model's data
     */
    virtual void empty();

	virtual void addRow();

	virtual void insertRow( const uint32& afterRow );

	virtual void addRows( const uint32& count );

	virtual void deleteRow( const uint32& row );

    virtual void addColumn();

	virtual void insertColumn( const uint32& afterColumn );

	virtual void addColumns( const uint32& count );

	virtual void deleteColumn( const uint32& column );

	virtual bool isCellEditable( const uint32& row, const uint32& column );

	virtual TableCellItem* getItem( const uint32& row, const uint32& column );

	virtual uint32 getRowCount();

	virtual uint32 getColumnCount();

	virtual TableRowItemEnumerator* getRowItemEnumerator( const uint32& row );

	virtual TableCellItem* createCell( const uint32& row, const uint32& column );

	virtual TableCellItem* setSelectedCell( const bool& val, const uint32& row, const uint32& column );

	virtual void setSelectedRange( const bool& val, const uint32& startRow, const uint32& startColumn,
									const uint32& endRow, const uint32& endColumn );

	virtual void setFocusedCell( const uint32& row, const uint32& column );

	virtual TableCellItem* getFocusedCell() {
		return focusedCell_;
	}

	virtual void setFixedColumnsCount( const uint32& count );

	virtual void setFixedRowsCount( const uint32& count );

	virtual uint32 getFixedColumnsCount();

	virtual uint32 getFixedRowsCount();

	virtual void clearSelection();

	virtual Enumerator<TableCellItem*>* getSelectedCells();

	virtual CellID getCellIDForItem( TableCellItem* item );
protected:
	/**
	*defines the a vector of TableCellItem's, or one row of data columnCount_ long
	*/
	typedef std::vector<TableCellItem*> TTableColumn;
private:
	void init();
	uint32 rowCount_;
	uint32 columnCount_;

	uint32 fixedRowsCount_;
	uint32 fixedColumnsCount_;
	/*row/column data
	*access is by row column.
	*so tableData_[0] is row 0, and (*tableData_[0])[2] is the item in
	*row 0 at column 3
	*/
	std::vector<TTableColumn*> tableData_;

	EnumeratorContainer<std::vector<TableCellItem*>,TableCellItem*> rowEnumContainer_;

	std::map<ulong32,TableCellItem*> selectionMap_;
	EnumeratorMapContainer<std::map<ulong32,TableCellItem*>,TableCellItem*> selectionContainer_;

	TableCellItem* focusedCell_;
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABLEMODEL_H__

/**
$Id$
*/
