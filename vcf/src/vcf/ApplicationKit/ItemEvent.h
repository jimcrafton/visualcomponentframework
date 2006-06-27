#ifndef _VCF_ITEMEVENT_H__
#define _VCF_ITEMEVENT_H__
//ItemEvent.h

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

class GraphicsContext;

#define ITEM_CONST						300

#define ITEM_EVENT_PAINT				CUSTOM_EVENT_TYPES + ITEM_CONST + 1
#define ITEM_EVENT_CHANGED				CUSTOM_EVENT_TYPES + ITEM_CONST + 2
#define ITEM_EVENT_SELECTED				CUSTOM_EVENT_TYPES + ITEM_CONST + 3
#define ITEM_EVENT_ADDED				CUSTOM_EVENT_TYPES + ITEM_CONST + 4
#define ITEM_EVENT_DELETED				CUSTOM_EVENT_TYPES + ITEM_CONST + 5
#define ITEM_EVENT_TEXT_CHANGED			CUSTOM_EVENT_TYPES + ITEM_CONST + 6
#define ITEM_EVENT_UNSELECTED			CUSTOM_EVENT_TYPES + ITEM_CONST + 7


/**
\class ItemEvent ItemEvent.h "vcf/ApplicationKit/ItemEvent.h"
*/
class APPLICATIONKIT_API ItemEvent : public Event
{
public:
	ItemEvent( Object* source ):Event(source),
		paintContext_(NULL){}

	ItemEvent( Object* source, const uint32& eventType ):Event(source,eventType),
		paintContext_(NULL){}

	ItemEvent( Object* source, GraphicsContext* context ):Event(source),
		paintContext_(context){}

	ItemEvent( const ItemEvent& rhs ):Event(rhs),paintContext_(NULL) {
		*this = rhs;
	}

	virtual ~ItemEvent(){}


	ItemEvent& operator=( const ItemEvent& rhs ) {
		paintContext_ = rhs.paintContext_;
		point_ = rhs.point_;
		return *this;
	}


	virtual Object* clone( bool deep=false ) {
		return new ItemEvent(*this);
	}

	GraphicsContext* getContext() {
		return this->paintContext_;
	}


	/**
	*returns the point for this mouse event
	*/
	Point* getPoint() {
		return  &this->point_;
	}

	void setPoint( Point* point ){
		point_.x_ = point->x_;
		point_.y_ = point->y_;
	}

private:
	GraphicsContext* paintContext_;
	Point point_;
};



template <class SOURCE_TYPE>
class ItemEventHandler : public EventHandlerInstance<SOURCE_TYPE,ItemEvent> {
public:
	ItemEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ItemEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ItemEvent>( source, handlerMethod, handlerName ) {

	}

};


};


#endif // _VCF_ITEMEVENT_H__

/**
$Id$
*/
