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



class APPLICATIONKIT_API TableCellClickEvent : public Event {
public:
	TableCellClickEvent( Object* source, const ulong32& type, const CellID& cell ):
		Event(source,type), cell_(cell) {

	}

	CellID getCellID() {
		return cell_;
	}
	CellID cell_;
};


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
Originally started as a basic table control, I quickly realized what an ordeal
this was going to turn into, and I began looking at Chris Maunder's excellent
CGridCtrl class. At this point, much of the original code that I wrote has
been completely dismantled, and in it's place I have ported over most of the
basic design/layout/algorithms from the CGridCtrl. The original CGridCtrl was
written for MFC, and has a number of very Win32-ish designs implicit in it.
These have been heavily changed to fit within the VCF way of doing things.
For example, the original TableControl made use of a TableModel with TableCellItem's
to represent an individual cell. This is still the case and in migrating over
to Chris's code, I had to make allowances for this, since his control doesn't
separate the model/data from the control itself (though he does use a CGridCell
class for the cell items). In addition most of the enumerations and all of the
function names have been changed, again to fit in with the VCF's coding standards.
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

	virtual void mouseDblClick(  MouseEvent* event );

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

	void resetColumnWidths();

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

	bool autoSizeColumn( int column, AutoSizeOption autoSizeStyle=asoDefault, bool resetScroll=true );

	bool autoSizeRow( int row, bool resetScroll=true);

	void editCell( const CellID& cell, const Point& pt );

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



};

};


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
*Revision 1.20.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.20  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.19.2.15  2004/03/22 22:55:47  ddiego
*minor table control change
*
*Revision 1.19.2.14  2004/03/19 21:25:41  ddiego
*just some minor noodlin
*
*Revision 1.19.2.13  2004/03/19 04:18:53  ddiego
*added more code to condition example, fixed some
*minor stuff in the table control
*
*Revision 1.19.2.12  2004/03/11 04:37:13  ddiego
*minor changes to table control.
*
*Revision 1.19.2.11  2004/03/10 04:27:31  ddiego
*blah
*
*Revision 1.19.2.10  2004/03/08 04:41:07  ddiego
*minor changes to DocumentManager - allow the use of
*Actions so that other UI elements can be added besides menu
*items (like Toolbar items)
*
*Revision 1.19.2.9  2004/03/03 05:02:53  ddiego
*Table editing is working again. The only major missing piece
*as compared to the CGridCtrl, is drag/drop support.
*
*Revision 1.19.2.8  2004/03/01 05:58:54  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.19.2.7  2004/02/26 05:10:38  ddiego
*more table control work
*
*Revision 1.19.2.6  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*Revision 1.19.2.5  2004/02/19 04:52:34  ddiego
*more progress made with TableControl
*
*Revision 1.19.2.4  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.19.2.3  2004/02/12 21:59:36  marcelloptr
*minor fixes related to TabModel
*
*Revision 1.19.2.2  2004/02/02 04:38:36  ddiego
*more table codin'
*
*Revision 1.19.2.1  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.19  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.18.2.3  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.18.2.2  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.18.2.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.18  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.17.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.17  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.1  2003/03/12 03:09:45  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.2.2  2002/12/27 23:04:32  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.15.2.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.15  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.14.4.1  2002/11/09 05:17:10  ddiego
*changes are for fixing bug [ 634798 ] Property pane not scrolling.
*ignore the inclusion of TreeListControl.cpp in this checkin.
*
*Revision 1.14  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.13.6.2  2002/09/10 04:07:48  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.13.6.1  2002/09/06 05:24:33  ddiego
*fixed bug in TableControl where it does not proeprly finished the ItemEditor
*correctly on loss of focus for the editor's control
*
*Revision 1.13  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.1  2002/04/27 15:42:56  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.12  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TABLECONTROL_H__


