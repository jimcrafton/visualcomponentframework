#ifndef _VCF_LISTMODELEVENT_H__
#define _VCF_LISTMODELEVENT_H__
//ListModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class ListItem;

#define LIST_MODEL_CONST				900

#define LIST_MODEL_CONTENTS_DELETED		CUSTOM_EVENT_TYPES + LIST_MODEL_CONST + 1
#define LIST_MODEL_ITEM_CHANGED			CUSTOM_EVENT_TYPES + LIST_MODEL_CONST + 2
#define LIST_MODEL_ITEM_ADDED			CUSTOM_EVENT_TYPES + LIST_MODEL_CONST + 3
#define LIST_MODEL_ITEM_DELETED			CUSTOM_EVENT_TYPES + LIST_MODEL_CONST + 4


/**
\class ListModelEvent ListModelEvent.h "vcf/ApplicationKit/ListModelEvent.h"
*/
class APPLICATIONKIT_API ListModelEvent : public Event
{
public:
	ListModelEvent( Object* source ):Event(source),listItem_(NULL){}

	ListModelEvent( Object* source, const uint32& eventType ):Event(source,eventType),
		listItem_(NULL){}

	ListModelEvent( Object* source, ListItem* item ):Event(source),listItem_(item){}

	ListModelEvent( Object* source, const uint32& eventType, ListItem* item ):Event(source,eventType),
		listItem_(item){}

	ListModelEvent( const ListModelEvent& rhs ):Event(rhs),listItem_(NULL) {
		*this = rhs;
	}

	virtual ~ListModelEvent(){}


	ListModelEvent& operator=( const ListModelEvent& rhs ) {
		Event::operator =( rhs );
		listItem_ = rhs.listItem_;
		return *this;
	}

	ListItem* getListItem(){
		return this->listItem_;
	}

	void setListItem( ListItem* item ){
		this->listItem_ = item;
	}

	virtual Object* clone( bool deep=false ) {
		return new ListModelEvent(*this);
	}

private:
	ListItem* listItem_;
};






/**
*ListModelEventHandler
*handles the following:
*onListModelContentsChanged
*onItemAdded
*onItemDeleted
*/
template <class SOURCE_TYPE>
class ListModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,ListModelEvent> {
public:
	ListModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ListModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ListModelEvent>( source, handlerMethod, handlerName ) {

	}

};


};


#endif // _VCF_LISTMODELEVENT_H__

/**
$Id$
*/
