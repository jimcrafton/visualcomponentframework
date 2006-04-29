#ifndef _VCF_ITEMEDITOREVENT_H__
#define _VCF_ITEMEDITOREVENT_H__
//ItemEditorEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define ITEMEDITOR_EVENT_CONST				3000

#define ITEMEDITOR_VALIDATION				CUSTOM_EVENT_TYPES + ITEMEDITOR_EVENT_CONST + 1
#define ITEMEDITOR_CHANGED					CUSTOM_EVENT_TYPES + ITEMEDITOR_EVENT_CONST + 2

class TableCellItem;


/**
\class ItemEditorEvent ItemItemEditorEvent.h "vcf/ApplicationKit/ItemEditorEvent.h"
*/
class ItemEditorEvent : public Event {
public:
	ItemEditorEvent( Object* source ) :
		Event( source ){
	}

	ItemEditorEvent( Object* source, void* dataToValidate ) :
		Event( source, ITEMEDITOR_VALIDATION ){
		setUserData( dataToValidate );
	}
	ItemEditorEvent( Object* source, const unsigned long& eventType  ) :
		Event( source, eventType ){
	}

	ItemEditorEvent( const ItemEditorEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~ItemEditorEvent(){

	}


	ItemEditorEvent& operator=( const ItemEditorEvent& rhs ) {
		Event::operator =( rhs );
		itemBeingEdited_ = rhs.itemBeingEdited_;
		return *this;
	}


	virtual Object* clone( bool deep=false ) {
		return new ItemEditorEvent(*this);
	}

	void fireInvalidStateException(){
		throw InvalidStateException(MAKE_ERROR_MSG_2(BAD_ITEMSTATE_EXCEPTION));
	}

	TableCellItem* getItemBeingEdited(){
		return itemBeingEdited_;
	}

	void setItemBeingEdited( TableCellItem* itemBeingEdited ){
		itemBeingEdited_ = itemBeingEdited;
	}

private:
	TableCellItem* itemBeingEdited_;
};




/**
*ItemEditorEventHandler
*handles:
*onChange
*onValidateChange
*/
template <class SOURCE_TYPE>
class ItemEditorEventHandler : public EventHandlerInstance<SOURCE_TYPE,ItemEditorEvent> {
public:
	ItemEditorEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ItemEditorEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ItemEditorEvent>( source, handlerMethod, handlerName ) {

	}

};

}; //end of namespace VCF


#endif // _VCF_ITEMEDITOREVENT_H__

/**
$Id$
*/
