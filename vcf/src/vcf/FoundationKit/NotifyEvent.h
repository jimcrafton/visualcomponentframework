#ifndef _VCF_NOTIFYEVENT_H__
#define _VCF_NOTIFYEVENT_H__
//NotifyEvent.h

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
\class NotifyEvent NotifyEvent.h "vcf/FoundationKit/NotifyEvent.h"
A generic event meant only to indicate some sort of "signal" has 
happened on the event's source instance. The actual semantics of this
is entirely up to the class deriving from ObjectWithEvents.
@see ObjectWithEvents.
*/
class NotifyEvent : public Event{

public:
	NotifyEvent( Object * source):
		Event(source)
	{};

	NotifyEvent( Object* source, const uint32& eventType ):
		Event(source,eventType)
	{};

	virtual ~NotifyEvent(){};

	virtual Object* clone( bool deep=false ) {
		return new NotifyEvent(*this);
	}
};


typedef Delegate1<NotifyEvent*> NotifyDelegate;
typedef NotifyDelegate::ProcedureType NotifyHandler;

}; //end of namespace VCF


#endif // _VCF_NOTIFYEVENT_H__

/**
$Id$
*/
