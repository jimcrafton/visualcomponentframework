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




namespace VCF{

//class TableCellItem;


typedef Enumerator<TableCellItem*> TableRowItemEnumerator;



/**
\class CellID TableModel.h "vcf/ApplicationKit/TableModel.h"
*/
class APPLICATIONKIT_API CellID {
public:

	enum {
		Invalid = (uint32)-1
	};

	CellID():row(CellID::Invalid), column(CellID::Invalid){}

	CellID( uint32 r, uint32 c ):row(r), column(c){}

	bool isValid() const {
		return ((row!=CellID::Invalid) && (column!=CellID::Invalid)) ? true : false;
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

	uint32 row;
	uint32 column;
};




enum TableModelEvents {
	TABLEMODEL_EVENT_CONST = CUSTOM_EVENT_TYPES + 2000,
	tmColumnsDeleted,
	tmColumnsAdded,
	tmRowsDeleted,
	tmRowsAdded,
	tmCellChanged,
	tmAllColumnsChanged,
	tmAllRowsChanged,
	tmAllItemsDeleted,
};

#define NO_ROW_CHANGED					-1
#define NO_COLUMN_CHANGED				-1

/**
\class TableModelEvent TableModel.h "vcf/ApplicationKit/TableModel.h"
*/
class APPLICATIONKIT_API TableModelEvent : public ModelEvent {
public:

	TableModelEvent( Object* source, const uint32& eventType,
		             const int& startRowVal =-1, const int& rowCountVal=0,
					 const int& startColumnVal =-1, const int& columnCountVal =0):
		ModelEvent(source,eventType),
		startRow(startRowVal),
		numberOfRowsAffected(rowCountVal),
		startColumn(startColumnVal),
		numberOfColumnsAffected(columnCountVal){

	}

	TableModelEvent( const TableModelEvent& rhs ):ModelEvent(rhs) {
		*this = rhs;
	}
	virtual ~TableModelEvent(){};


	TableModelEvent& operator=( const TableModelEvent& rhs ) {
		ModelEvent::operator =( rhs );
		startRow = rhs.startRow;
		numberOfRowsAffected = rhs.numberOfRowsAffected;

		startColumn = rhs.startColumn;
		numberOfColumnsAffected = rhs.numberOfColumnsAffected;

		return *this;
	}


	



	virtual Object* clone( bool deep=false ) {
		return new TableModelEvent(*this);
	}

	int startRow;
	int numberOfRowsAffected;
	int startColumn;
	int numberOfColumnsAffected;
};




/**
*TableModelEventHandler
*handles the following:
\li onChange
*/
typedef Delegate1<TableModelEvent*> TableModelDelegate; 
typedef TableModelDelegate::ProcedureType TableModelHandler;


#define TABLEMODEL_CLASSID		"3f215738-a52d-459a-a82b-0a3e7d174714"

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
	
    virtual bool isEmpty() { 
		return getRowCount() > 0 || getColumnCount() > 0;
	}

    virtual void addRow() {
		addRows( 1 );
	}

	void insertRow( const uint32& afterRow ) {
		if ( doInsertRow( afterRow ) ) { 
			TableModelEvent event( this, tmRowsAdded, afterRow, 1 );
			TableRowsAdded( &event );
		}
	}

	void addRows( const uint32& count ) {
		uint32 start = getRowCount();

		if ( doAddRows( count ) ) {

			TableModelEvent event( this, tmRowsAdded, start, count );
			TableRowsAdded( &event );
		}
	}

	void removeRow( const uint32& row ) {
		TableModelEvent event( this, tmRowsDeleted, row, 1 );
		TableRowsDeleted( &event );

		doRemoveRow( row );
	}

    virtual void addColumn() {
		addColumns( 1 );
	}

	void insertColumn( const uint32& afterColumn ) {
		if ( doInsertColumn( afterColumn ) ) {
			TableModelEvent event( this, tmColumnsAdded, NO_ROW_CHANGED, 0, afterColumn, 1 );
			TableColumnsAdded( &event );
		}
	}

	void addColumns( const uint32& count ) {
		uint32 startCol = getColumnCount();
		if ( doAddColumns( count ) ) {
			TableModelEvent event( this, tmColumnsAdded, NO_ROW_CHANGED, 0, startCol, count );
			TableColumnsAdded( &event );
		}
	}

	void removeColumn( const uint32& column ) {
		TableModelEvent event( this, tmColumnsDeleted, NO_ROW_CHANGED, 0, column, 1 );
		TableColumnsDeleted( &event );

		doRemoveColumn( column );
	}

	virtual bool isCellEditable( const uint32& row, const uint32& column ) = 0;

	virtual VariantData getValue( const uint32& row, const uint32& column ) = 0;

	virtual String getValueAsString( const uint32& row, const uint32& column ) {
		return getValue(row,column).toString();
	}

	void setValue( const uint32& row, const uint32& column, const VariantData& value ) {
		if ( doSetValue( row, column, value ) ) {
			TableModelEvent event( this, tmCellChanged );	
			
			event.startRow = row;
			event.startColumn = column;
			event.numberOfColumnsAffected = 1;
			event.numberOfRowsAffected = 1;
			
			ModelChanged( &event );
		}
	}
	
	virtual void setValueAsString( const uint32& row, const uint32& column, const String& value ) {
		VariantData v;
		v.setFromString(value);
		setValue(row,column,v);
	}

	virtual uint32 getRowCount() = 0;

	virtual uint32 getColumnCount() = 0;

	virtual bool getRowValues( const uint32& row, std::vector<VariantData>& values ) = 0;
	virtual bool getColumnValues( const uint32& col, std::vector<VariantData>& values ) = 0;

	virtual void setFixedColumnsCount( const uint32& count ) = 0;

	virtual void setFixedRowsCount( const uint32& count ) = 0;

	virtual uint32 getFixedColumnsCount() = 0;

	virtual uint32 getFixedRowsCount() = 0;

protected:
	virtual bool doInsertRow( const uint32& afterRow ) {
		return false;
	}

	virtual bool doAddRows( const uint32& count ) {
		return false;
	}

	virtual bool doRemoveRow( const uint32& row ) {
		return false;
	}

	virtual bool doInsertColumn( const uint32& afterColumn ) {
		return false;
	}

	virtual bool doAddColumns( const uint32& count ) {
		return false;
	}

	virtual bool doRemoveColumn( const uint32& column ) {
		return false;
	}

	virtual bool doSetValue( const uint32& row, const uint32& column, const VariantData& value ) {
		return false;
	}
};

};


#endif // _VCF_TABLEMODEL_H__

/**
$Id$
*/
