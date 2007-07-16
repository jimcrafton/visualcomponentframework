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

	MenuItemEvent( Object* source, const uint32& eventType ):
		Event( source, eventType ){}

	virtual ~MenuItemEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new MenuItemEvent(*this);
	}

};



/**
*MenuItemEventHandler
*handles the following:
\li onMenuItemClicked
\li onMenuItemUpdate
*/
typedef Delegate1<MenuItemEvent*> MenuItemDelegate; 
typedef MenuItemDelegate::ProcedureType MenuItemHandler;
};


#endif // _VCF_MENUITEMEVENT_H__

/**
$Id$
*/
