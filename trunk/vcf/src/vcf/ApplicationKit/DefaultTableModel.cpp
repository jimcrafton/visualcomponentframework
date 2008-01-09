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
	init();
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

void DefaultTableModel::init()
{
	//selectionContainer_.initContainer( selectionMap_ );
}

/*
Enumerator<TableCellItem*>* DefaultTableModel::getSelectedCells()
{
	return selectionContainer_.getEnumerator();
}
*/

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
	newRow->resize(columnCount_,VariantData::null());
	//for ( uint32 i=0;i<columnCount_;i++){		
		//TableCellItem* newItem = createCell( afterRow, i );
		//newItem->setModel( this );
		//newRow->push_back( newItem );
	//}

	tableData_.insert( tableData_.begin() + afterRow, newRow );
	TableModelEvent event( this, tmRowsAdded, afterRow, 1 );
	TableRowsAdded( &event );
}

void DefaultTableModel::addRows( const uint32& count )
{
	int start = rowCount_;


	rowCount_ += count;
	tableData_.resize( rowCount_, NULL );

	for ( int row=start;row<rowCount_;row++ ) {
		TTableColumn* newRow = new TTableColumn();
		tableData_[row] = newRow;

		newRow->resize( columnCount_, VariantData::null() );
/*
		for ( uint32 i=0;i<columnCount_;i++){
			TableCellItem* newItem = createCell( row, i );

			newItem->setModel( this );

			if ( i < fixedColumnsCount_ ) {
				newItem->setFixed( true );
			}

			(*newRow)[i] = newItem;
		}
		*/
	}

	TableModelEvent event( this, tmRowsAdded, start, count );
	TableRowsAdded( &event );

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

		TableColumnAdded( &columnEvent );
	}


	*/
}

void DefaultTableModel::deleteRow( const uint32& row )
{
	TableModelEvent event( this, tmRowsDeleted, row, 1 );
	TableRowsDeleted( &event );

	std::vector<TTableColumn*>::iterator found = tableData_.begin() + row;
	if ( found != tableData_.end() ){
		TTableColumn* row = *found;
		
		/*std::vector<TableCellItem*>::iterator it = row->begin();
		while ( it != row->end() ){
			TableCellItem* item = *it;
			delete item;
			item = NULL;
			it++;
		}
		*/
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
			//TableCellItem* newItem = createCell( i, columnCount_-1 );

			//newItem->setModel( this );

			//if ( columnCount_-1 < this->fixedColumnsCount_ ) {
			//	newItem->setFixed( true );
			//}

			row->push_back( VariantData::null() );
			rowIter++;
			i++;
		}

	}
	TableModelEvent event( this, tmColumnsAdded, NO_ROW_CHANGED, 0, startCol, count );
	TableColumnsAdded( &event );
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

	TableModelEvent event( this, tmColumnsAdded, NO_ROW_CHANGED, 0, afterColumn, 1 );
	TableColumnsAdded( &event );
}

void DefaultTableModel::deleteColumn( const uint32& column )
{

	TableModelEvent event( this, tmColumnsDeleted, NO_ROW_CHANGED, 0, column, 1 );
	TableColumnsDeleted( &event );

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
}

bool DefaultTableModel::isCellEditable( const uint32& row, const uint32& column )
{
	bool result = true;
	/*
	TableCellItem* item = getItem( row, column );
	if ( NULL != item ){
		result = item->isEditable();
	}
	*/

	if ( row <= fixedRowsCount_ && column <= fixedColumnsCount_ ) {
		result = false;
	}
	return result;
}
/*
TableCellItem* DefaultTableModel::getItem( const uint32& row, const uint32& column )
{
	TableCellItem* result = NULL;
	TTableColumn* rows = tableData_[row];
	result = (*rows)[column];
	return result;
}
*/

VariantData DefaultTableModel::getValue( const uint32& row, const uint32& column )
{
	VariantData result;

	TTableColumn* rows = tableData_[row];
	result = (*rows)[column];

	return result;
}

String DefaultTableModel::getValueAsString( const uint32& row, const uint32& column )
{
	String result;

	TTableColumn* rows = tableData_[row];
	const VariantData& v = (*rows)[column];
	result = v.toString();

	return result;
}

void DefaultTableModel::setValue( const uint32& row, const uint32& column, const VariantData& value )
{
	TTableColumn* rows = tableData_[row];
	(*rows)[column] = value;

	TableModelEvent itemEvent( this, tmCellChanged );
	
	itemEvent.startRow = row;
	itemEvent.startColumn = column;
	itemEvent.numberOfColumnsAffected = 1;
	itemEvent.numberOfRowsAffected = 1;
	
	ModelChanged( &itemEvent );
}

void DefaultTableModel::setValueAsString( const uint32& row, const uint32& column, const String& value )
{
	TTableColumn* rows = tableData_[row];
	VariantData v = (*rows)[column];

	v.setFromString( value );
	setValue( row, column, v );
}

uint32 DefaultTableModel::getRowCount()
{
	return rowCount_;
}

uint32 DefaultTableModel::getColumnCount()
{
	return columnCount_;
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
/*

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
	TableCellsSelected( &event );

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
	TableCellsSelected( &event );
	//TableCellsSelected
}
*/

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
/*
void DefaultTableModel::clearSelection()
{
	for ( int i=0;i<rowCount_;i++ ) {
		for ( int j=0;j<columnCount_;j++ ) {
			getItem( i, j )->setSelected( false );
		}
	}

	selectionMap_.clear();


	TableModelEvent event( this, CELL_CHANGED );
	TableCellsSelected( &event );
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
*/

/**
$Id$
*/
