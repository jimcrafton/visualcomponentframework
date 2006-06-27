#ifndef _VCF_TABLEMODELEVENT_H__
#define _VCF_TABLEMODELEVENT_H__
//TableModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

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
\class TableModelEvent TableModelEvent.h "vcf/ApplicationKit/TableModelEvent.h"
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
*onChange
*/
template <class SOURCE_TYPE>
class TableModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,TableModelEvent> {
public:
	TableModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TableModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TableModelEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~TableModelEventHandler(){};
};

}; //end of namespace VCF


#endif // _VCF_TABLEMODELEVENT_H__

/**
$Id$
*/
