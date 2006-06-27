#ifndef _VCF_FOCUSEVENT_H__
#define _VCF_FOCUSEVENT_H__
//FocusEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
\class FocusEvent FocusEvent.h "vcf/ApplicationKit/FocusEvent.h"
* the event class for events specific of any change of focus.
*/
class APPLICATIONKIT_API FocusEvent : public Event {
public:
	FocusEvent( Object* source ): Event(source){}

	FocusEvent( Object* source, const uint32& eventType ): Event(source,eventType){}

	virtual ~FocusEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new FocusEvent(*this);
	}
};


/**
 The handler class for a FocusEvent.
 
 handles the following:
 
 	\li FocusGained
 	\li FocusLost
 
*/
template <class SOURCE_TYPE> class FocusEventHandler : public EventHandlerInstance<SOURCE_TYPE,FocusEvent> {
public:
	FocusEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,FocusEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,FocusEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~FocusEventHandler(){};
};

};


#endif // _VCF_FOCUSEVENT_H__

/**
$Id$
*/
