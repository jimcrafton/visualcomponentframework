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
	for ( ulong32 i=0;i<columnCount_;i++){
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

		for ( ulong32 i=0;i<columnCount_;i++){
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
		for ( ulong32 i=0;i<columnCount_;i++){
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

	ulong32 key = (row << 16) | column;

	if ( true == val ) {
		selectionMap_[key] = selectedCell;
	}
	else {
		std::map<ulong32,TableCellItem*>::iterator found = selectionMap_.find( key );
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

			ulong32 key = (i << 16) | j;

			if ( true == val ) {
				selectionMap_[key] = selectedCell;
			}
			else {
				std::map<ulong32,TableCellItem*>::iterator found = selectionMap_.find( key );
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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.10  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.12.2.9  2004/03/16 03:40:46  ddiego
*minor
*
*Revision 1.12.2.8  2004/03/10 04:27:45  ddiego
*blah
*
*Revision 1.12.2.7  2004/03/01 05:59:19  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.12.2.6  2004/02/19 04:52:35  ddiego
*more progress made with TableControl
*
*Revision 1.12.2.5  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.12.2.4  2004/02/02 04:38:45  ddiego
*more table codin'
*
*Revision 1.12.2.3  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.12.2.2  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.12.2.1  2004/01/29 22:26:47  ddiego
*table fixes, this still needs some more work
*
*Revision 1.12  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.1  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.11  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:13:08  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.9.14.1  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:46  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.8  2002/03/01 01:02:53  ddiego
*fixes bug [ 524006 ] TreeListControl crash
*makes some changes to model classes to utilize event types better
*
*Revision 1.7  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


