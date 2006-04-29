#ifndef _VCF_TIMEREVENT_H__
#define _VCF_TIMEREVENT_H__
//TimerEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

#define TIMER_EVENT_ACTIVATED				CUSTOM_EVENT_TYPES + 5000
#define TIMER_EVENT_DEACTIVATED				CUSTOM_EVENT_TYPES + 5001
#define TIMER_EVENT_PULSE					CUSTOM_EVENT_TYPES + 5002



/**
\class TimerEvent TimerEvent.h "vcf/ApplicationKit/TimerEvent.h"
*Class TimerEvent documentation
*/
class APPLICATIONKIT_API TimerEvent : public VCF::Event {
public:
	TimerEvent( Object* source, const unsigned long& eventType ): Event(source,eventType){}

	virtual ~TimerEvent(){}

	virtual Object* clone( bool deep=false ) {
		return new TimerEvent(*this);
	}
protected:

private:
};


template <class SOURCE_TYPE>
class TimerEventHandler : public EventHandlerInstance<SOURCE_TYPE,TimerEvent> {
public:
	TimerEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TimerEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TimerEvent>( source, handlerMethod, handlerName ) {

	}

};

}; //end of namespace VCF


#endif // _VCF_TIMEREVENT_H__

/**
$Id$
*/
