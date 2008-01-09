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

	int row;
	int column;
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

	virtual void setValue( const uint32& row, const uint32& column, const VariantData& value ) = 0;
	virtual void setValueAsString( const uint32& row, const uint32& column, const String& value ) = 0;

	virtual uint32 getRowCount() = 0;

	virtual uint32 getColumnCount() = 0;

	virtual bool getRowValues( const uint32& row, std::vector<VariantData>& values ) = 0;
	virtual bool getColumnValues( const uint32& col, std::vector<VariantData>& values ) = 0;

	virtual void setFixedColumnsCount( const uint32& count ) = 0;

	virtual void setFixedRowsCount( const uint32& count ) = 0;

	virtual uint32 getFixedColumnsCount() = 0;

	virtual uint32 getFixedRowsCount() = 0;

};

};


#endif // _VCF_TABLEMODEL_H__

/**
$Id$
*/
