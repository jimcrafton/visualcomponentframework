//DefaultTableModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTableModel.h"
#include "vcf/ApplicationKit/DefaultTableCellItem.h"


using namespace VCF;

DefaultTableModel::DefaultTableModel():
	columnCount_(0),
	rowCount_(0),
	fixedRowsCount_(0),
	fixedColumnsCount_(0)
{
	
}

DefaultTableModel::~DefaultTableModel()
{
	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;
		delete row;
		row = NULL;
		rowIter ++;
	}
	tableData_.clear();
}


void DefaultTableModel::validate()
{

}

void DefaultTableModel::empty()
{
	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;		
		delete row;
		row = NULL;
		rowIter ++;
	}
	tableData_.clear();
	columnCount_ = 0;
	rowCount_ = 0;
	fixedColumnsCount_ = 0;
	fixedRowsCount_ = 0;
	
	TableModelEvent event( this, tmAllItemsDeleted );
	ModelChanged( &event );
}


bool DefaultTableModel::doInsertRow( const uint32& afterRow )
{
	if ( 0 == columnCount_ ){
		columnCount_++; //gotta have at least one column !
	}

	rowCount_ ++;
	TTableColumn* newRow = new TTableColumn();
	newRow->resize(columnCount_,VariantData::null());
	//for ( uint32 i=0;i<columnCount_;i++){		
		//TableCellItem* newItem = createCell( afterRow, i );
		//newItem->setModel( this );
		//newRow->push_back( newItem );
	//}

	tableData_.insert( tableData_.begin() + afterRow, newRow );	

	return true;
}

bool DefaultTableModel::doAddRows( const uint32& count )
{
	int start = rowCount_;

	rowCount_ += count;
	tableData_.resize( rowCount_, NULL );

	for ( int row=start;row<rowCount_;row++ ) {
		TTableColumn* newRow = new TTableColumn();
		tableData_[row] = newRow;

		newRow->resize( columnCount_, VariantData::null() );
	}
	return true;
}

bool DefaultTableModel::doRemoveRow( const uint32& row )
{
	TableModelEvent event( this, tmRowsDeleted, row, 1 );
	TableRowsDeleted( &event );

	std::vector<TTableColumn*>::iterator found = tableData_.begin() + row;
	if ( found != tableData_.end() ){
		TTableColumn* row = *found;

		tableData_.erase( found );
		delete row;
		row = NULL;
		if ( rowCount_ > 0 ){
			rowCount_ --;
		}
	}
	return true;
}


bool DefaultTableModel::doAddColumns( const uint32& count )
{
	int startCol = columnCount_;
	for ( int j=0;j<count;j++ ) {
		columnCount_ ++;

		int i = 0;
		std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
		while ( rowIter != tableData_.end() ){
			TTableColumn* row = *rowIter;
			row->push_back( VariantData::null() );
			rowIter++;
			i++;
		}
	}
	return true;
}

bool DefaultTableModel::doInsertColumn( const uint32& afterColumn )
{
	columnCount_ ++;
	if ( 0 == rowCount_ ){
		addRow();//gotta have at least one row !
	}
	else {
		int i = 0;
		std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
		while ( rowIter != tableData_.end() ){
			TTableColumn* row = *rowIter;
			//TableCellItem* newItem = createCell( i, afterColumn );
			//newItem->setModel( this );

			//if ( afterColumn < this->fixedColumnsCount_ ) {
			//	newItem->setFixed( true );
			//}

			row->insert( row->begin() + afterColumn, VariantData::null() );//newItem );
			rowIter++;
			i++;
		}
	}
	return true;
}

bool DefaultTableModel::doRemoveColumn( const uint32& column )
{
	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;
		std::vector<VariantData>::iterator found = row->begin() + column;
		if ( found != row->end() ){
			//TableCellItem* item = *found;
			row->erase( found );
			//delete item;
			//item = NULL;
		}
		rowIter++;
	}
	if ( columnCount_ > 0 ){
		columnCount_--;
	}

	return true;
}

bool DefaultTableModel::isCellEditable( const uint32& row, const uint32& column )
{
	bool result = true;

	if ( row <= fixedRowsCount_ && column <= fixedColumnsCount_ ) {
		result = false;
	}
	return result;
}

VariantData DefaultTableModel::getValue( const uint32& row, const uint32& column )
{
	VariantData result;

	TTableColumn* rows = tableData_[row];
	result = (*rows)[column];

	return result;
}


bool DefaultTableModel::doSetValue( const uint32& row, const uint32& column, const VariantData& value )
{
	TTableColumn* rows = tableData_[row];
	(*rows)[column] = value;

	return true;
}




bool DefaultTableModel::getRowValues( const uint32& row, std::vector<VariantData>& values )
{
	values.clear();

	values = *(tableData_[row]);

	return !values.empty();
}

bool DefaultTableModel::getColumnValues( const uint32& col, std::vector<VariantData>& values )
{
	values.clear();
	values.resize( rowCount_ );
	for (size_t row=0;row<rowCount_;row++ ) {
		TTableColumn* aRow = tableData_[row];
		values[row] = (*aRow)[col];
	}
	return !values.empty();
}

void DefaultTableModel::setFixedColumnsCount( const uint32& count )
{
	if ( count == fixedColumnsCount_ ) {
		return;
	}


	if ( columnCount_ < count ) {
		addColumns( count - columnCount_ );
	}
/*
	if ( count > fixedColumnsCount_ ) {
		for ( int i=0;i<rowCount_;i++ ) {
			for ( int j=fixedColumnsCount_;j<count;j++ ) {
				//getItem( i, j )->setFixed( true );
			}
		}
	}
	else {
		for ( int i=fixedRowsCount_;i<rowCount_;i++ ) {
			for ( int j=count;j<fixedColumnsCount_;j++ ) {
				//getItem( i, j )->setFixed( false );
			}
		}
	}
*/

	fixedColumnsCount_ = count ;
}

void DefaultTableModel::setFixedRowsCount( const uint32& count )
{
	if ( count == fixedRowsCount_ ) {
		return;
	}

	if ( rowCount_ < count ) {
		uint32 oldRowCount = rowCount_;
		addRows( count );
	}
/*
	if ( count > fixedRowsCount_ ) {
		for ( int i=fixedRowsCount_;i<count;i++ ) {
			for ( int j=0;j<columnCount_;j++ ) {
				//getItem( i, j )->setFixed( true );
			}
		}
	}
	else {
		for ( int i=count;i<fixedRowsCount_;i++ ) {
			for ( int j=fixedColumnsCount_;j<columnCount_;j++ ) {
				//getItem( i, j )->setFixed( false );
			}
		}
	}
*/
	fixedRowsCount_ = count ;
}


/**
$Id$
*/
