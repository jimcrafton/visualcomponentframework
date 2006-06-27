#ifndef _VCF_COLUMNITEMEVENT_H__
#define _VCF_COLUMNITEMEVENT_H__
//ColumnItemEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {


#define COLUMN_ITEM_CONST				1950

#define COLUMN_ITEM_WIDTH_CHANGED		CUSTOM_EVENT_TYPES + COLUMN_ITEM_CONST + 1
#define COLUMN_ITEM_CAPTION_CHANGED		CUSTOM_EVENT_TYPES + COLUMN_ITEM_CONST + 2



/**
\class ColumnItemEvent ColumnItemEvent.h "vcf/ApplicationKit/ColumnItemEvent.h"
*Class ColumnItemEvent documentation
*/
class ColumnItemEvent : public Event {
public:
	ColumnItemEvent( Object* source, const uint32& eventType ):
	  Event(source, eventType ){}


	virtual ~ColumnItemEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new ColumnItemEvent(*this);
	}

protected:

private:
};


}; //end of namespace VCF


#endif // _VCF_COLUMNITEMEVENT_H__

/**
$Id$
*/
