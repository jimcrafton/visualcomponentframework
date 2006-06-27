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
	focusedCell_(NULL)
{
	init();
}

DefaultTableModel::~DefaultTableModel()
{
	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;
		std::vector<TableCellItem*>::iterator it = row->begin();
		while ( it != row->end() ){
			TableCellItem* item = *it;
			delete item;
			item = NULL;
			it++;
		}
		row->clear();
		delete row;
		row = NULL;
		rowIter ++;
	}
	tableData_.clear();
}

void DefaultTableModel::init()
{
	columnCount_ = 0;
	rowCount_ = 0;
	fixedRowsCount_ = 0;
	fixedColumnsCount_ = 0;

	selectionContainer_.initContainer( selectionMap_ );
}


Enumerator<TableCellItem*>* DefaultTableModel::getSelectedCells()
{
	return selectionContainer_.getEnumerator();
}

void DefaultTableModel::validate()
{

}

void DefaultTableModel::empty()
{
	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;
		std::vector<TableCellItem*>::iterator it = row->begin();
		while ( it != row->end() ){
			TableCellItem* item = *it;
			delete item;
			item = NULL;
			it++;
		}
		row->clear();
		delete row;
		row = NULL;
		rowIter ++;
	}
	tableData_.clear();
	columnCount_ = 0;
	rowCount_ = 0;
	fixedColumnsCount_ = 0;
	fixedRowsCount_ = 0;

	focusedCell_ = NULL;

	selectionMap_.clear();

	AbstractModel::empty();
}

void DefaultTableModel::addRow()
{
	addRows( 1 );
}

void DefaultTableModel::insertRow( const uint32& afterRow )
{
	if ( 0 == columnCount_ ){
		columnCount_++; //gotta have at least one column !
	}

	rowCount_ ++;
	TTableColumn* newRow = new TTableColumn();
	for ( uint32 i=0;i<columnCount_;i++){
		TableCellItem* newItem = createCell( afterRow, i );
		newItem->setModel( this );
		newRow->push_back( newItem );
	}

	tableData_.insert( tableData_.begin() + afterRow, newRow );
	TableModelEvent event( this, ROWS_ADDED, afterRow, 1 );
	TableRowsAdded.fireEvent( &event );
}

void DefaultTableModel::addRows( const uint32& count )
{
	int start = rowCount_;


	rowCount_ += count;
	tableData_.resize( rowCount_, NULL );

	for ( int row=start;row<rowCount_;row++ ) {
		TTableColumn* newRow = new TTableColumn();
		tableData_[row] = newRow;

		newRow->resize( columnCount_, NULL );

		for ( uint32 i=0;i<columnCount_;i++){
			TableCellItem* newItem = createCell( row, i );

			newItem->setModel( this );

			if ( i < fixedColumnsCount_ ) {
				newItem->setFixed( true );
			}

			(*newRow)[i] = newItem;
		}
	}

	TableModelEvent event( this, ROWS_ADDED, start, count );
	TableRowsAdded.fireEvent( &event );

	/*
	bool notifyFirstColumnAdded = false;
	if ( 0 == columnCount_ ){
		columnCount_++; //gotta have at least one column !
		notifyFirstColumnAdded = true;
	}

	for ( int j=0;j<count;j++ ) {

		rowCount_ ++;
		TTableColumn* newRow = new TTableColumn();
		for ( uint32 i=0;i<columnCount_;i++){
			TableCellItem* newItem = createCell( rowCount_-1, i );
			newItem->setColumn( i );
			newItem->setRow( rowCount_ -1 );
			newRow->push_back( newItem );
		}

		tableData_.push_back( newRow );
	}


	if ( notifyFirstColumnAdded ) {
		TableModelEvent columnEvent( this, COLUMN_ADDED, NO_ROW_CHANGED, columnCount_-1 );

		TableColumnAdded.fireEvent( &columnEvent );
	}


	*/
}

void DefaultTableModel::deleteRow( const uint32& row )
{
	TableModelEvent event( this, ROWS_DELETED, row, 1 );
	TableRowsDeleted.fireEvent( &event );

	std::vector<TTableColumn*>::iterator found = tableData_.begin() + row;
	if ( found != tableData_.end() ){
		TTableColumn* row = *found;
		std::vector<TableCellItem*>::iterator it = row->begin();
		while ( it != row->end() ){
			TableCellItem* item = *it;
			delete item;
			item = NULL;
			it++;
		}
		tableData_.erase( found );
		delete row;
		row = NULL;
		if ( rowCount_ > 0 ){
			rowCount_ --;
		}
	}
}

void DefaultTableModel::addColumn()
{
	addColumns( 1 );
}

void DefaultTableModel::addColumns( const uint32& count )
{


	int startCol = columnCount_;
	for ( int j=0;j<count;j++ ) {
		columnCount_ ++;

		int i = 0;
		std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
		while ( rowIter != tableData_.end() ){
			TTableColumn* row = *rowIter;
			TableCellItem* newItem = createCell( i, columnCount_-1 );

			newItem->setModel( this );

			if ( columnCount_-1 < this->fixedColumnsCount_ ) {
				newItem->setFixed( true );
			}

			row->push_back( newItem );
			rowIter++;
			i++;
		}

	}
	TableModelEvent event( this, COLUMNS_ADDED, NO_ROW_CHANGED, 0, startCol, count );
	TableColumnsAdded.fireEvent( &event );
}

void DefaultTableModel::insertColumn( const uint32& afterColumn )
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
			TableCellItem* newItem = createCell( i, afterColumn );
			newItem->setModel( this );

			if ( afterColumn < this->fixedColumnsCount_ ) {
				newItem->setFixed( true );
			}

			row->insert( row->begin() + afterColumn, newItem );
			rowIter++;
			i++;
		}
	}

	TableModelEvent event( this, COLUMNS_ADDED, NO_ROW_CHANGED, 0, afterColumn, 1 );
	TableColumnsAdded.fireEvent( &event );
}

void DefaultTableModel::deleteColumn( const uint32& column )
{

	TableModelEvent event( this, COLUMNS_DELETED, NO_ROW_CHANGED, 0, column, 1 );
	TableColumnsDeleted.fireEvent( &event );

	std::vector<TTableColumn*>::iterator rowIter = tableData_.begin();
	while ( rowIter != tableData_.end() ){
		TTableColumn* row = *rowIter;
		std::vector<TableCellItem*>::iterator found = row->begin() + column;
		if ( found != row->end() ){
			TableCellItem* item = *found;
			row->erase( found );
			delete item;
			item = NULL;
		}
		rowIter++;
	}
	if ( columnCount_ > 0 ){
		columnCount_--;
	}
}

bool DefaultTableModel::isCellEditable( const uint32& row, const uint32& column )
{
	bool result = false;
	TableCellItem* item = getItem( row, column );
	if ( NULL != item ){
		result = item->isEditable();
	}
	return result;
}

TableCellItem* DefaultTableModel::getItem( const uint32& row, const uint32& column )
{
	TableCellItem* result = NULL;
	TTableColumn* rows = tableData_[row];
	result = (*rows)[column];
	return result;
}

uint32 DefaultTableModel::getRowCount()
{
	return rowCount_;
}

uint32 DefaultTableModel::getColumnCount()
{
	return columnCount_;
}

TableRowItemEnumerator* DefaultTableModel::getRowItemEnumerator( const uint32& row )
{
	TableRowItemEnumerator* result = NULL;
	rowEnumContainer_.initContainer( *(tableData_[row]) );

	result = rowEnumContainer_.getEnumerator();

	return result;
}

TableCellItem* DefaultTableModel::createCell( const uint32& row, const uint32& column )
{
	TableCellItem* result = new DefaultTableCellItem();
	result->setModel( this );
	return result;
}

TableCellItem* DefaultTableModel::setSelectedCell( const bool& val, const uint32& row, const uint32& column )
{
	VCF_ASSERT( (row<rowCount_) && (column<columnCount_) );

	TableCellItem* selectedCell = getItem( row, column );

	selectedCell->setSelected( val );

	uint32 key = (row << 16) | column;

	if ( true == val ) {
		selectionMap_[key] = selectedCell;
	}
	else {
		std::map<uint32,TableCellItem*>::iterator found = selectionMap_.find( key );
		if ( found != selectionMap_.end() ) {
			selectionMap_.erase( found );
		}
	}

	TableModelEvent event( this, CELL_CHANGED, row, 1, column, 1 );
	TableCellsSelected.fireEvent( &event );

	return selectedCell;
}



void DefaultTableModel::setSelectedRange( const bool& val, const uint32& startRow, const uint32& startColumn,
									const uint32& endRow, const uint32& endColumn )
{
	this->clearSelection();

	for (int i=startRow;i<=endRow;i++ ) {
		for (int j=startColumn;j<=endColumn;j++ ) {
			TableCellItem* selectedCell = getItem( i, j );

			selectedCell->setSelected( val );

			uint32 key = (i << 16) | j;

			if ( true == val ) {
				selectionMap_[key] = selectedCell;
			}
			else {
				std::map<uint32,TableCellItem*>::iterator found = selectionMap_.find( key );
				if ( found != selectionMap_.end() ) {
					selectionMap_.erase( found );
				}
			}
		}
	}

	TableModelEvent event( this, CELL_CHANGED, startRow, endRow-startRow, startColumn, endColumn-startColumn );
	TableCellsSelected.fireEvent( &event );
	//TableCellsSelected
}

void DefaultTableModel::setFixedColumnsCount( const uint32& count )
{
	if ( count == fixedColumnsCount_ ) {
		return;
	}


	if ( columnCount_ < count ) {
		addColumns( count - columnCount_ );
	}

	if ( count > fixedColumnsCount_ ) {
		for ( int i=0;i<rowCount_;i++ ) {
			for ( int j=fixedColumnsCount_;j<count;j++ ) {
				getItem( i, j )->setFixed( true );
			}
		}
	}
	else {
		for ( int i=fixedRowsCount_;i<rowCount_;i++ ) {
			for ( int j=count;j<fixedColumnsCount_;j++ ) {
				getItem( i, j )->setFixed( false );
			}
		}
	}

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
		//addRows( count - oldRowCount );
		//addColumns( count - oldRowCount );
	}

	if ( count > fixedRowsCount_ ) {
		for ( int i=fixedRowsCount_;i<count;i++ ) {
			for ( int j=0;j<columnCount_;j++ ) {
				getItem( i, j )->setFixed( true );
			}
		}
	}
	else {
		for ( int i=count;i<fixedRowsCount_;i++ ) {
			for ( int j=fixedColumnsCount_;j<columnCount_;j++ ) {
				getItem( i, j )->setFixed( false );
			}
		}
	}

	fixedRowsCount_ = count ;
}

uint32 DefaultTableModel::getFixedColumnsCount()
{
	return fixedColumnsCount_;
}

uint32 DefaultTableModel::getFixedRowsCount()
{
	return fixedRowsCount_;
}

void DefaultTableModel::clearSelection()
{
	for ( int i=0;i<rowCount_;i++ ) {
		for ( int j=0;j<columnCount_;j++ ) {
			getItem( i, j )->setSelected( false );
		}
	}

	selectionMap_.clear();


	TableModelEvent event( this, CELL_CHANGED );
	TableCellsSelected.fireEvent( &event );
}

CellID DefaultTableModel::getCellIDForItem( TableCellItem* item )
{
	CellID result;

	std::vector<TTableColumn*>::iterator rowIt = tableData_.begin();
	while ( rowIt != tableData_.end() ) {
		TTableColumn* columns = *rowIt;

		TTableColumn::iterator found = std::find( columns->begin(), columns->end(), item );
		if ( found != columns->end() ) {

			result.column = found - columns->begin();

			result.row = rowIt - tableData_.begin();

			break;
		}

		rowIt ++;
	}

	return result;
}

void DefaultTableModel::setFocusedCell( const uint32& row, const uint32& column )
{
	if ( NULL != focusedCell_ ) {
		focusedCell_->setFocused( false );
	}

	CellID cell = CellID(row,column);

	if ( cell.isValid() ) {
		focusedCell_ = getItem( row, column );

		if ( NULL != focusedCell_ ) {
			focusedCell_->setFocused( true );
		}
	}
	else {
		focusedCell_ = NULL;
	}
}


/**
$Id$
*/
