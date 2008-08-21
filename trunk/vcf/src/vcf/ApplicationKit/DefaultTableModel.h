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


/*
#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__
*/

/*
#ifndef _VCF_TABLECELLITEM_H__
#include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__
*/

#ifndef _VCF_TABLEMODEL_H__
#include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__


namespace VCF {

#define DEFAULTTABLEMODEL_CLASSID		"53EA0BA8-7068-11d4-8F12-00207811CFAB"

class TableCellItem;

/**
\class DefaultTableModel DefaultTableModel.h "vcf/ApplicationKit/DefaultTableModel.h"
*/
class APPLICATIONKIT_API DefaultTableModel : public TableModel {
public:
	DefaultTableModel();

	virtual ~DefaultTableModel();
	
   
    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual ValidationResult validate();

    /**
     * clears out the model's data
     */
    virtual void empty();
	
	virtual bool isCellEditable( const uint32& row, const uint32& column );

	virtual VariantData getValue( const uint32& row, const uint32& column );

	virtual uint32 getRowCount() {
		return rowCount_;
	}

	virtual uint32 getColumnCount() {
		return columnCount_;
	}

	virtual bool getRowValues( const uint32& row, std::vector<VariantData>& values );
	virtual bool getColumnValues( const uint32& col, std::vector<VariantData>& values );

	virtual void setFixedColumnsCount( const uint32& count );

	virtual void setFixedRowsCount( const uint32& count );

	virtual uint32 getFixedColumnsCount() {
		return fixedColumnsCount_;
	}

	virtual uint32 getFixedRowsCount() {
		return fixedRowsCount_;
	}
	
protected:	

	virtual bool doInsertRow( const uint32& afterRow );

	virtual bool doAddRows( const uint32& count );

	virtual bool doRemoveRow( const uint32& row );

	virtual bool doInsertColumn( const uint32& afterColumn );

	virtual bool doAddColumns( const uint32& count );

	virtual bool doRemoveColumn( const uint32& column );

	virtual bool doSetValue( const uint32& row, const uint32& column, const VariantData& value );


	/**
	*defines the a vector of TableCellItem's, or one row of data columnCount_ int32
	*/
	typedef std::vector<VariantData> TTableColumn;
private:
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
/*
	EnumeratorContainer<std::vector<TableCellItem*>,TableCellItem*> rowEnumContainer_;

	std::map<uint32,TableCellItem*> selectionMap_;
	EnumeratorMapContainer<std::map<uint32,TableCellItem*>,TableCellItem*> selectionContainer_;

	TableCellItem* focusedCell_;
	*/
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABLEMODEL_H__

/**
$Id$
*/
