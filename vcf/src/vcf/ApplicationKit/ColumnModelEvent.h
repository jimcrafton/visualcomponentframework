#ifndef _VCF_COLUMNMODELEVENT_H__
#define _VCF_COLUMNMODELEVENT_H__
//ColumnModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ColumnItem;

#define COLUMN_MODEL_CONST				1900

#define COLUMN_MODEL_CONTENTS_DELETED		CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 1
#define COLUMN_MODEL_ITEM_CHANGED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 2
#define COLUMN_MODEL_ITEM_ADDED				CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 3
#define COLUMN_MODEL_ITEM_DELETED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 4


/**
\class ColumnModelEvent ColumnModelEvent.h "vcf/ApplicationKit/ColumnModelEvent.h"
*Class ColumnModelEvent documentation
*/
class ColumnModelEvent : public Event {
public:

	
	ColumnModelEvent( Object* source ):
	  Event( source ), columnItem_(NULL){ }

	ColumnModelEvent( Object* source, const unsigned long& eventType ):
	  Event( source, eventType ), columnItem_(NULL){}

	ColumnModelEvent( Object* source, ColumnItem* item ):
		Event( source ), columnItem_(item){}


	ColumnModelEvent( Object* source, const unsigned long& eventType, ColumnItem* item ):
		Event( source, eventType ), columnItem_(item){}


	virtual ~ColumnModelEvent(){}
	
	ColumnItem* getColumnItem() {
		return columnItem_;
	}
	
	void setColumnItem( ColumnItem* item ) {
		columnItem_ = item;
	}

	ColumnModelEvent( const ColumnModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}


	ColumnModelEvent& operator=( const ColumnModelEvent& rhs ) {
		Event::operator =( rhs );
		columnItem_ = rhs.columnItem_;

		return *this;
	}
	
	virtual Object* clone( bool deep=false ) {
		return new ColumnModelEvent(*this);
	}
protected:
	ColumnItem* columnItem_;
};

/**
\class ColumnModelEventHandler ColumnModelEvent.h "vcf/ApplicationKit/ColumnModelEvent.h"
*/
template <class SOURCE_TYPE> class ColumnModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent> {
public:
	ColumnModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~ColumnModelEventHandler(){};
};

}; //end of namespace VCF


#endif // _VCF_COLUMNMODELEVENT_H__

/**
$Id$
*/
