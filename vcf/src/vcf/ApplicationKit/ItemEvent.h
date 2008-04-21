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



/**
\class ItemEvent ItemEvent.h "vcf/ApplicationKit/ItemEvent.h"
*/
class APPLICATIONKIT_API ItemEvent : public Event
{
public:

		
	enum ItemEvents {
		Paint = CUSTOM_EVENT_TYPES + ITEM_CONST + 1,
		Changed,
		Selected,
		Added,
		Removed,
		TextChanged,
		Unselected,
		StateChangeRequested,
		StateChanged,
	};


	enum {
		InvalidIndex = (uint32)-1
	};

	ItemEvent( Object* source ):Event(source),
		paintContext(NULL),index(InvalidIndex),itemSelected(false){}

	ItemEvent( Object* source, const uint32& eventType ):Event(source,eventType),
		paintContext(NULL),index(InvalidIndex),itemSelected(false){}

	ItemEvent( Object* source, GraphicsContext* context ):Event(source),
		paintContext(context),index(InvalidIndex),itemSelected(false){}

	ItemEvent( const ItemEvent& rhs ):Event(rhs),paintContext(NULL),index(InvalidIndex),itemSelected(false) {
		*this = rhs;
	}

	virtual ~ItemEvent(){}


	ItemEvent& operator=( const ItemEvent& rhs ) {
		paintContext = rhs.paintContext;
		point = rhs.point;
		index = rhs.index;
		itemSelected = rhs.itemSelected;
		return *this;
	}


	virtual Object* clone( bool deep=false ) {
		return new ItemEvent(*this);
	}


		

	GraphicsContext* paintContext;
	Point point;
	uint32 index;
	bool itemSelected;
};


/**
*/
typedef Delegate1<ItemEvent*> ItemDelegate; 
typedef ItemDelegate::ProcedureType ItemHandler;


};


#endif // _VCF_ITEMEVENT_H__

/**
$Id$
*/
