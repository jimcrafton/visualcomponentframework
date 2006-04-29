#ifndef _VCF_MENUITEMEVENT_H__
#define _VCF_MENUITEMEVENT_H__
//MenuItemEvent.h

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

#define MENU_ITEM_CONST						1400

#define MENU_ITEM_EVENT_CLICKED				CUSTOM_EVENT_TYPES + MENU_ITEM_CONST + 1
#define MENU_ITEM_EVENT_UPDATED				CUSTOM_EVENT_TYPES + MENU_ITEM_CONST + 2


/**
\class MenuItemEvent MenuItemEvent.h "vcf/ApplicationKit/MenuItemEvent.h"
*/
class APPLICATIONKIT_API MenuItemEvent : public Event {
public:
	MenuItemEvent( Object * source): Event( source ){}

	MenuItemEvent( Object* source, const unsigned long& eventType ):
		Event( source, eventType ){}

	virtual ~MenuItemEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new MenuItemEvent(*this);
	}

};



/**
*MenuItemEventHandler
*handles the following:
*onMenuItemClicked
*onMenuItemUpdate
*/
template <class SOURCE_TYPE>
class MenuItemEventHandler : public EventHandlerInstance<SOURCE_TYPE,MenuItemEvent> {
public:

	MenuItemEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,MenuItemEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,MenuItemEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~MenuItemEventHandler(){};
};

};


#endif // _VCF_MENUITEMEVENT_H__

/**
$Id$
*/
