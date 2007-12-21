#ifndef _VCF_TABLEMODEL_H__
#define _VCF_TABLEMODEL_H__
//TableModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#ifndef _VCF_TABLEMODELEVENT_H__
#include "vcf/ApplicationKit/TableModelEvent.h"
#endif





namespace VCF{

//class TableCellItem;


typedef Enumerator<TableCellItem*> TableRowItemEnumerator;



/**
\class CellID TableModel.h "vcf/ApplicationKit/TableModel.h"
*/
class APPLICATIONKIT_API CellID {
public:
	CellID():row(-1), column(-1){}

	CellID( int r, int c ):row(r), column(c){}

	bool isValid() const {
		return ((row>=0) && (column>=0)) ? true : false;
	}
	operator bool () const {
		return isValid();
	}

	bool operator==( const CellID& rhs ) const {
		return (row == rhs.row) && (column == rhs.column);
	}

	bool operator!=( const CellID& rhs ) const {
		return (row != rhs.row) || (column != rhs.column);
	}

public:
	int row;
	int column;
};





#define TABLEMODEL_EVENT_CONST						2000
#define COLUMNS_DELETED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 1
#define COLUMNS_ADDED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 2
#define ROWS_DELETED						CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 3
#define ROWS_ADDED						CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 4
#define CELL_CHANGED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 5
#define ALL_COLUMNS_CHANGED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 6
#define ALL_ROWS_CHANGED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 7
#define ALL_ITEMS_DELETED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 8

#define NO_ROW_CHANGED					-1
#define NO_COLUMN_CHANGED				-1

/**
\class TableModelEvent TableModel.h "vcf/ApplicationKit/TableModel.h"
*/
class APPLICATIONKIT_API TableModelEvent : public Event {
public:

	TableModelEvent( Object* source, const uint32& eventType,
		             const int& startRow =-1, const int& rowCount=0,
					 const int& startColumn =-1, const int& columnCount =0):
		Event(source,eventType),
		startRow_(startRow),
		numberOfRowsAffected_(rowCount),
		startColumn_(startColumn),
		numberOfColumnsAffected_(columnCount){

	}

	TableModelEvent( const TableModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}
	virtual ~TableModelEvent(){};


	TableModelEvent& operator=( const TableModelEvent& rhs ) {
		Event::operator =( rhs );
		startRow_ = rhs.startRow_;
		numberOfRowsAffected_ = rhs.numberOfRowsAffected_;

		startColumn_ = rhs.startColumn_;
		numberOfColumnsAffected_ = rhs.numberOfColumnsAffected_;

		return *this;
	}


	/**
	*get the row that changed. a return of -1 means no rows
	*changed for this event
	*/
	int getStartRowThatChanged() {
		return startRow_;
	}

	int getNumberOfRowsAffected() {
		return numberOfRowsAffected_;
	}

	int getStartColumnThatChanged() {
		return startColumn_;
	}

	int getNumberOfColumnsAffected() {
		return numberOfColumnsAffected_;
	}



	virtual Object* clone( bool deep=false ) {
		return new TableModelEvent(*this);
	}
private:
	int startRow_;
	int numberOfRowsAffected_;
	int startColumn_;
	int numberOfColumnsAffected_;
};




/**
*TableModelEventHandler
*handles the following:
\li onChange
*/
typedef Delegate1<TableModelEvent*> TableModelDelegate; 
typedef TableModelDelegate::ProcedureType TableModelHandler;




/**
\class TableModel TableModel.h "vcf/ApplicationKit/TableModel.h"
@delegates	
	@del TableModel::TableCellAdded
	@del TableModel::TableCellDeleted	
	@del TableModel::TableRowsAdded
	@del TableModel::TableRowsDeleted
	@del TableModel::TableColumnsAdded
	@del TableModel::TableColumnsDeleted

*/

class APPLICATIONKIT_API TableModel : public Model  {
public:

	virtual ~TableModel(){};

	/**
	@delegate TableCellAdded
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableCellAdded);

	/**
	@delegate TableCellDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableCellDeleted);


	/**
	@delegate TableRowAdded
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableRowsAdded);

	/**
	@delegate TableRowDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableRowsDeleted);

	/**
	@delegate TableColumnAdded
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableColumnsAdded);

	/**
	@delegate TableColumnDeleted
	@event TableModelEvent
	*/
	DELEGATE(TableModelDelegate,TableColumnsDeleted);
	
    
    virtual void addRow() = 0;

	virtual void insertRow( const uint32& afterRow ) = 0;

	virtual void addRows( const uint32& count ) = 0;

	virtual void deleteRow( const uint32& row ) = 0;

    virtual void addColumn() = 0;

	virtual void insertColumn( const uint32& afterColumn ) = 0;

	virtual void addColumns( const uint32& count ) = 0;

	virtual void deleteColumn( const uint32& column ) = 0;

	virtual bool isCellEditable( const uint32& row, const uint32& column ) = 0;

	virtual VariantData getValue( const uint32& row, const uint32& column ) = 0;
	virtual String getValueAsString( const uint32& row, const uint32& column ) = 0;

	virtual uint32 getRowCount() = 0;

	virtual uint32 getColumnCount() = 0;

	virtual bool getRowValues( const uint32& row, std::vector<VariantData>& values ) = 0;
	virtual bool getColumnValues( const uint32& col, std::vector<VariantData>& values ) = 0;

	/**
	*this is overriden to provide TableModels derivations
	*control over what kind of item get created
	*at any cell in the table.
	*@param uint32 - the row being created
	*/
	//virtual TableCellItem* createCell( const uint32& row, const uint32& column ) = 0;

	//virtual TableCellItem* setSelectedCell( const bool& val, const uint32& row, const uint32& column ) = 0;

	//virtual void setFocusedCell( const uint32& row, const uint32& column ) = 0;

	//virtual TableCellItem* getFocusedCell() = 0;


	//virtual void setSelectedRange( const bool& val, const uint32& startRow, const uint32& startColumn,
	//								const uint32& endRow, const uint32& endColumn ) = 0;

	virtual void setFixedColumnsCount( const uint32& count ) = 0;

	virtual void setFixedRowsCount( const uint32& count ) = 0;

	virtual uint32 getFixedColumnsCount() = 0;

	virtual uint32 getFixedRowsCount() = 0;

	//virtual void clearSelection() = 0;

	//virtual Enumerator<TableCellItem*>* getSelectedCells() = 0;

	//virtual CellID getCellIDForItem( TableCellItem* item ) = 0;


};

};


#endif // _VCF_TABLEMODEL_H__

/**
$Id$
*/
