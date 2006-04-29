#ifndef _VCF_HELPEVENT_H__
#define _VCF_HELPEVENT_H__
//HelpEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

#define HELP_EVENT_TYPE		CUSTOM_EVENT_TYPES + 900


/**
\class HelpEvent HelpEvent.h "vcf/ApplicationKit/HelpEvent.h"
*/
class APPLICATIONKIT_API HelpEvent : public Event {
public:
	HelpEvent( Object* source ): Event(source,HELP_EVENT_TYPE){}

	virtual ~HelpEvent() {}

	virtual Object* clone( bool deep=false ) {
		return new HelpEvent(*this);
	}

	String helpSection;
	String helpBook;
	String helpDirectory;

};


/**
\class HelpEventHandler HelpEvent.h "vcf/ApplicationKit/HelpEvent.h"
*class HelpEventHandler documentation
*/
template <class SOURCE_TYPE> class HelpEventHandler : public EventHandlerInstance<SOURCE_TYPE,HelpEvent> {
public:


	HelpEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,HelpEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,HelpEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~HelpEventHandler(){};
};



}; //end of namespace VCF


#endif // _VCF_HELPEVENT_H__

/**
$Id$
*/
