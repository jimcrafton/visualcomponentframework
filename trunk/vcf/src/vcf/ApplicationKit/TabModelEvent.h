#ifndef _VCF_TABMODELEVENT_H__
#define _VCF_TABMODELEVENT_H__
//TabModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define TABMODELEVENT_CONST						232

#define TAB_MODEL_EVENT_ITEM_ADDED				CUSTOM_EVENT_TYPES + TABMODELEVENT_CONST + 1
#define TAB_MODEL_EVENT_ITEM_REMOVED			CUSTOM_EVENT_TYPES + TABMODELEVENT_CONST + 2
#define TAB_MODEL_EVENT_ITEM_SELECTED			CUSTOM_EVENT_TYPES + TABMODELEVENT_CONST + 3

class TabPage;


/**
\class TabModelEvent TabModelEvent.h "vcf/ApplicationKit/TabModelEvent.h"
* the event class for events specific of tabbed pages
* It containes the pointer to the specific tab page 
* associated to this event.
*@see 
*/
class APPLICATIONKIT_API TabModelEvent : public Event{
public:
	TabModelEvent( Object * source, TabPage* page ): Event(source), page_(page) {}

	TabModelEvent( Object* source, const uint32& eventType, TabPage* page )
		: Event(source,eventType), page_(page) {}

	TabModelEvent( const TabModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~TabModelEvent(){}


	TabModelEvent& operator= ( const TabModelEvent& rhs ) {
		Event::operator =( rhs );

		page_ = rhs.page_;

		return *this;
	}

	TabPage* getTabPage(){
		return page_;
	}

	virtual Object* clone( bool deep=false ) {
		return new TabModelEvent(*this);
	}
private:
	/**
	* the tab page to be associated to the event.
	*/
	TabPage* page_;

};





/**
The handler class for a TabModelEvent.
 
handles the following:

	\li onTabPageAdded
	\li onTabPageRemoved
	\li onTabPageSelected
*/
template <class SOURCE_TYPE>
class TabModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,TabModelEvent> {
public:
	TabModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TabModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TabModelEvent>( source, handlerMethod, handlerName ) {

	}


};


}; // namespace VCF


#endif // _VCF_TABMODELEVENT_H__

/**
$Id$
*/
