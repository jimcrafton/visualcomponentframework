#ifndef _VCF_TABLECONTROL_H__
#define _VCF_TABLECONTROL_H__
//TableControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
The TableControl is based (partially) on Chris Maunder's
excellent CGridCtrl. What follows is his license for the code:

Written by Chris Maunder <cmaunder@mail.com>
Copyright (c) 1998-2002. All Rights Reserved.

This code may be used in compiled form in any way you desire. This
file may be redistributed unmodified by any means PROVIDING it is
not sold for profit without the authors written consent, and
providing that this notice and the authors name and all copyright
notices remains intact.

An email letting me know how you are using it would be nice as well.

This file is provided "as is" with no expressed or implied warranty.
The author accepts no liability for any damage/loss of business that
this product may cause.

For use with CGridCtrl v2.20+
*/




#ifndef _VCF_TABLEMODEL_H__
#	include "vcf/ApplicationKit/TableModel.h"
#endif // _VCF_TABLEMODEL_H__

#ifndef _VCF_TABLECELLITEM_H__
#	include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__


#ifndef _VCF_TABLEMODELEVENT_H__
#	include "vcf/ApplicationKit/TableModelEvent.h"
#endif // _VCF_TABLEMODELEVENT_H__



namespace VCF {

#define DEFAULT_ROW_HEIGHT			20
#define DEFAULT_COLUMN_WIDTH		80
#define TABLECELL_HANDLER			"TableCellHandler"
#define TABLECONTROL_CLASSID		"AC704858-753B-46a7-815B-72C09C884164"

class TableControl;
class ItemEvent;
class TableItemEditor;


/**
\class TableCellClickEvent TableControl.h "vcf/ApplicationKit/TableControl.h"
*/
class APPLICATIONKIT_API TableCellClickEvent : public Event {
public:
	TableCellClickEvent( Object* source, const uint32& type, const CellID& cell ):
		Event(source,type), cell_(cell) {

	}

	CellID getCellID() {
		return cell_;
	}
	CellID cell_;
};

/**
\class CellRange TableControl.h "vcf/ApplicationKit/TableControl.h"
*/
class APPLICATIONKIT_API CellRange {
public:

	CellRange(int minRow = -1, int minCol = -1, int maxRow = -1, int maxCol = -1) {
		set(minRow, minCol, maxRow, maxCol);
	}


	void set(int minRow = -1, int minCol = -1, int maxRow = -1, int maxCol = -1) {
		minRow_ = minRow;
		minCol_ = minCol;
		maxRow_ = maxRow;
		maxCol_ = maxCol;
	}

	bool  isValid() const {
		return (minRow_ >= 0 && minCol_ >= 0 && maxRow_ >= 0 && maxCol_ >= 0 &&
						minRow_ <= maxRow_ && minCol_ <= maxCol_);
	}

	bool  inRange(int row, int col) const {
		return (row >= minRow_ && row <= maxRow_ && col >= minCol_ && col <= maxCol_);
	}



	bool  inRange(const CellID& cellID) const {
		return inRange(cellID.row, cellID.column);
	}

	int  count() {
		return (maxRow_ - minRow_ + 1) * (maxCol_ - minCol_ + 1);
	}

	CellID  getTopLeft() const {
		return CellID(minRow_, minCol_);
	}

	CellRange  intersect(const CellRange& rhs) const {
		return CellRange(maxVal<>(minRow_,rhs.minRow_), maxVal<>(minCol_,rhs.minCol_),
											minVal<>(maxRow_,rhs.maxRow_), minVal<>(maxCol_,rhs.maxCol_));
	}

	int getMinRow() const {
		return minRow_;
	}

	void setMinRow(int minRow) {
		minRow_ = minRow;
	}

	int getMinCol() const {
		return minCol_;
	}

	void setMinCol(int minCol) {
		minCol_ = minCol_;
	}

	int getMaxRow() const {
		return maxRow_;
	}

	void setMaxRow(int maxRow) {
		maxRow_ = maxRow;
	}

	int getMaxCol() const {
		return maxCol_;
	}

	void setMaxCol(int maxCol) {
		maxCol_ = maxCol;
	}

	int getRowSpan() const {
		return maxRow_ - minRow_ + 1;
	}

	int getColSpan() const {
		return maxCol_ - minCol_ + 1;
	}

	CellRange& operator=(const CellRange& rhs) {
		if (this != &rhs) {
			set(rhs.minRow_, rhs.minCol_, rhs.maxRow_, rhs.maxCol_);
		}

		return *this;
	}

	bool operator==(const CellRange& rhs) const	{
		return ((minRow_ == rhs.minRow_) && (minCol_ == rhs.minCol_) &&
						(maxRow_ == rhs.maxRow_) && (maxCol_ == rhs.maxCol_));
	}

	bool operator!=(const CellRange& rhs) const {
		return !operator==(rhs);
	}

protected:
	int minRow_;
	int minCol_;
	int maxRow_;
	int maxCol_;
};




/**
\class TableControl TableControl.h "vcf/ApplicationKit/TableControl.h"
This class if for presenting data in a tabular format. You can 
adjust the number of rows and columns, as well as various formatting 
features. You can also have custom editors for editing individual
cells.

Originally started as a basic table control, I quickly realized what an ordeal
this was going to turn into, and I began looking at Chris Maunder's excellent
CGridCtrl class. At this point, much of the original code that I wrote has
been completely dismantled, and in it's place I have ported over most of the
basic design/layout/algorithms from the CGridCtrl. 

The original CGridCtrl was written for MFC, and has a number of very 
Win32-ish designs implicit in it. These have been heavily changed to fit 
within the VCF way of doing things. For example, the original TableControl 
made use of a TableModel with TableCellItem's to represent an individual cell. 
This is still the case and in migrating over to Chris's code, I had to make 
allowances for this, since his control doesn't separate the model/data from the 
control itself (though he does use a CGridCell class for the cell items). In 
addition most of the enumerations and all of the function names have been 
changed, again to fit in with the VCF's coding standards.
*/
class APPLICATIONKIT_API TableControl : public CustomControl, public DelegatedContainer<TableControl> {
public:
	enum {
		TableCellClickedEvent = CUSTOM_EVENT_TYPES + 32131,
		FixedRowClickedEvent,
		FixedColumnClickedEvent,
		SelectingEvent,
		TableSelectionChangingEvent,
		TableSelectionChangedEvent
	};

	enum DrawGridLines {
		dglNone = 0,
		dglDrawVerticalLines = 1,
		dglDrawHorizontalLines = 2,
		dglDrawBoth = 3
	};

	enum AutoSizeOption{
		asoDefault = 0,
		asoHeader = 1,
		asoData = 2,
		asoBoth
	};

	TableControl( TableModel* model=NULL );
	virtual ~TableControl();

	virtual void paint( GraphicsContext * context );

	void init();

	uint32 getDefaultRowHeight();

	void setDefaultRowHeight( const uint32& defaultRowHeight );

	uint32 getDefaultColumnWidth();

	void setDefaultColumnWidth( const uint32& defaultColumnWidth );

	void setColumnWidth( const uint32& column, const uint32& width );

	void setRowHeight( const uint32& row, const uint32& height );

	double getRowHeight( uint32 row );

	double getColumnWidth( uint32 col );

	TableModel* getTableModel();

	void setTableModel( TableModel* model );

	void setColumnCount( const uint32& colCount );

	void setRowCount( const uint32& rowCount );


	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	//virtual void mouseDblClick(  MouseEvent* event );
	virtual void mouseClick(  MouseEvent* event );

	//virtual void setBounds( Rect* rect, const bool& anchorDeltasNeedUpdating=true ) throw( InvalidPeer );

	void setAutoResizeColumns( const bool& autoResizeColumns );

	bool getAutoResizeColumns(){
		return autoResizeColumns_;
	}

	/**
	@delegate TableCellClicked
	@event TableCellClicked
	*/
	DELEGATE(TableCellClicked)

	/**
	@delegate TableCellDblClicked
	@event TableCellDblClicked
	*/
	DELEGATE(TableCellDblClicked)

	/**
	@delegate TableCellDown
	@event TableCellDown
	*/
	DELEGATE(TableCellDown)

	/**
	@delegate TableCellFinishedEditing
	@event TableCellFinishedEditing
	*/
	DELEGATE(TableCellFinishedEditing)

	/**
	@delegate FixedRowClicked
	@event TableCellClicked
	*/
	DELEGATE(FixedRowClicked)

	/**
	@delegate FixedRowClicked
	@event TableCellClicked
	*/
	DELEGATE(FixedColumnClicked)

	/**
	@delegate TableSelecting
	@event TableSelecting
	*/
	DELEGATE(TableSelecting)

	/**
	@delegate TableSelectionChanging
	@event TableSelecting
	*/
	DELEGATE(TableSelectionChanging)

	/**
	@delegate TableSelectionChanged
	@event TableSelecting
	*/
	DELEGATE(TableSelectionChanged)

	virtual void handleEvent( Event* e );

	DrawGridLines getDrawGridLinesStyle() {
		return drawGridLinesStyle_;
	}

	void setDrawGridLinesStyle( DrawGridLines val );

	/**
	We'll always return false, so that we can control when to start the drag-drop
	operation
	*/
	virtual bool canBeginDragDrop( Point* point ) {
		return false;
	}




	bool getAllowColumnResizing() {
		return allowColumnResizing_;
	}

	void setAllowColumnResizing( bool val ) {
		allowColumnResizing_ = val;
	}



	bool getAllowRowResizing() {
		return allowRowResizing_;
	}

	void setAllowRowResizing( bool val ) {
		allowRowResizing_ = val;
	}

	bool getListMode() {
		return listMode_;
	}

	void setListMode( bool val ) {
		listMode_ = val;
	}

	bool getAllowColumnHide() {
		return allowColumnHide_;
	}

	void setAllowColumnHide( bool val ) {
		allowColumnHide_ = val;
	}

	bool getAllowRowHide() {
		return allowRowHide_;
	}

	void setAllowRowHide( bool val ) {
		allowRowHide_ = val;
	}

	bool getEnableSelection() {
		return enableSelection_;
	}

	void setEnableSelection( bool val ) {
		enableSelection_ = val;
	}

	bool getAllowSingleColumnSelection() {
		return allowSingleColumnSelection_;
	}

	void setAllowSingleColumnSelection( bool val ) {
		allowSingleColumnSelection_ = val;
	}

	bool getAllowSingleRowSelection() {
		return allowSingleRowSelection_;
	}

	void setAllowSingleRowSelection( bool val ) {
		allowSingleRowSelection_ = val;
	}

	bool getAllowFixedColumnSelection() {
		return allowFixedColumnSelection_;
	}

	void setAllowFixedColumnSelection( bool val ) {
		allowFixedColumnSelection_ = val;
	}

	bool getAllowFixedRowSelection() {
		return allowFixedRowSelection_;
	}

	void setAllowFixedRowSelection( bool val ) {
		allowFixedRowSelection_ = val;
	}

	virtual void keyDown( KeyboardEvent* e );

	void resizeColumnWidths();
	void resizeRowHeights();
	void resizeColumnRowDimensions();

	/**
	* autosize the specified column's width to its text
	*/
	bool autoSizeColumn( int column, AutoSizeOption autoSizeStyle=asoDefault, bool resetScroll=true );

	/**
	* autosize the specified row's heigth to its text
	*/
	bool autoSizeRow( int row, bool resetScroll=true);

	Color* getDefaultTableCellColor();

	void setDefaultTableCellColor( Color* color );

	Font* getDefaultTableCellFont();

	void setDefaultTableCellFont( Font* font );
protected:

	enum MouseState{
		msNone = 0,
		msPrepareForEdit,
		msPrepareForDrag,
		msPrepareToSelect,
		msPrepareColResize,
		msColResizing,
		msPrepareRowResize,
		msRowResizing,
		msSelectAll,
		msSelectColumn,
		msSelectRow,
		msSelectCells
	};



	Rect getBoundsForCell( const CellID& cell );

	Rect getBoundsForItem( TableCellItem* item );



	double getFixedColumnWidth();
	double getFixedRowHeight();

	void onTableModelChanged( TableModelEvent* event );
	void onTableCellItemSelected( ItemEvent* event );
	void onTableModelEmptied( ModelEvent* e );
	void onEditingControlKeyPressed( KeyboardEvent* event );

	void finishEditing();
	void cancelEditing();

	void onFocusLost( FocusEvent* e );

	void onFinishEditing( Event* e );

	CellID getCellIDFromPoint( const Point& pt, bool allowFixedCellCheck=true );

	TableCellItem* getItem( const CellID& cell );

	CellID setFocusedCell( const CellID& cell );

	bool columnResizeAreaHitTest( const Point& pt );
	bool rowResizeAreaHitTest( const Point& pt );

	/**
	returns false if the cell is not visible,
	otherwise pt will be set to the top left coordinates
	of the item represented by the row/col of cell
	*/
	bool getCellOrigin( const CellID& cell, Point& pt );

	CellID getTopLeftNonFixedCell( const bool& recalc=false );

	CellRange getVisibleNonFixedCellRange( Rect* rect=NULL, bool forceRecalculation=false );


	Point getClickedPoint( const CellID& cell, const Point& pt );

	void clearSelectionRange();

	void doSelection( const CellID& cell );

	void selectAllCells();

	void selectColumns( CellID currentCell, bool forceRedraw=false, bool selectCells=true );

	void selectRows( CellID currentCell, bool forceRedraw=false, bool selectCells=true );

	void selectCells( CellID currentCell, bool forceRedraw=false, bool selectCells=true );

	void fixedRowClicked( CellID cell );

	void fixedColumnClicked( CellID cell );

	void recalcScrollBars();

	void onVerticalScrolling( Event* e );
	void onHorizontalScrolling( Event* e );

	double getTotalRowHeight();
	double getTotalColumnWidth();

	void editCell( const CellID& cell, const Point& pt );

	Rect getEditCellRect( const CellID& editCellID );

protected:

	TableCellItem* selectedCellItem_;
	Control* currentEditingControl_;

	TableItemEditor* currentItemEditor_;

	bool autoResizeColumns_;
	bool allowColumnResizing_;
	bool allowRowResizing_;
	bool hiddenColumnUnhide_;
	bool hiddenRowUnhide_;
	bool listMode_;
	bool allowColumnHide_;
	bool allowRowHide_;
	bool enableSelection_;
	bool allowSingleColumnSelection_;
	bool allowSingleRowSelection_;
	bool allowFixedColumnSelection_;
	bool allowFixedRowSelection_;
	bool allowLiveResizing_;

	int resizeCaptureRange_;

	Point resizeDragPt_;
	Point lastMousePoint_;
	Point leftClickPoint_;

	CellID clickCell_;
	CellID selectionStartCell_;
	CellID currentCell_;

	CellID topLeftCell_;

	uint32 dragColumnWidth_;

	double totalRowHeight_;


	MouseState mouseState_;

	DrawGridLines drawGridLinesStyle_;

	AutoSizeOption autoSizeStyle_;

	uint32 defaultColumnWidth_;
	uint32 defaultRowHeight_;

	std::vector<uint32> columnWidths_;
	std::vector<uint32> rowHeights_;

	std::map<CellID,TableCellItem*> previouslySelectedCellMap_;

	Color* defaultCellColor_;
	Font* defaultCellFont_;


};


}; // namespace VCF



#endif // _VCF_TABLECONTROL_H__

/**
$Id$
*/
