#ifndef _VCF_OBJECTWITHEVENTS_H__
#define _VCF_OBJECTWITHEVENTS_H__
//ObjectWithEvents.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define OBJECTWITHEVENTS_CLASSID		"eadd685c-e57b-49c5-b93d-00648641102a"


namespace VCF  {

class NotifyEvent;

/**
\class ObjectWithEvents ObjectWithEvents.h "vcf/FoundationKit/ObjectWithEvents.h"
ObjectWithEvents is an object that may
have 0 or more EventHandlers associated with it,
and will automatically clean up these EventHandlers
when it is destroyed. This simplifies handling
who has to clean up EventHandlers that have been
allocated on the heap (which they always will be).

Because the collection is a map, an event handler may be
retreived for future use - that is it may be reused by 
another delegate. For example:
\code
class Stuff : public ObjectWithEvents {
public:
	void onEvent( Event* e ) {
		
	}

};

int main() 
{
	FoundationKit::init();

	Stuff stuff;
	
	EventHandler* ev = 
		new GenericEventHandler<Stuff>(&stuff,&Stuff::onEvent,"Stuff::onEvent");
	
	FoundationKit::terminate();
	return 0;
}

\endcode

This adds the new event handler (ev) to the stuff instance. This event handler can
then be retreived at any time:

\code
void someFunction( Stuff* stuff ) 
{
	EventHandler* stuffHandler = stuff->getEventHandler( "Stuff::onEvent" );
	//use the stuffHandler somehow...
}
\endcode


Note that the ObjectWithEvents should not be created directly. Instead derive a 
new custom class using this as a base class.

@delegates	
	@del ObjectWithEvents::Notified
*/
class FOUNDATIONKIT_API ObjectWithEvents : public Object {
public:

	ObjectWithEvents();

	virtual ~ObjectWithEvents();

	/**
	This is a utility method for adding event handlers to an object.
	Adding a handler provides a convenient way to store the various events
	an object may wish to listen to. Handlers still need to have their method
	callbacks set, otherwise nothing will happen. When the object is destroyed
	all the event handlers in this list are also destroyed.
	*/
	void addEventHandler( const String& handlerName, CallBack* handler );

	/**
	Finds a CallBack for a given name. If the object has that
	handler then a pointer to the is returned otherwise null
	is returned.
	@see CallBack
	*/
	CallBack* getEventHandler( const String& handlerName );

	String getEventHandlerName( CallBack* handler );
	
	/**	
	@delegate Notifier events are used as a generic signal mechanism and can signify 
	anything that takes place to the ObjectWithEvents instance.
	@event NotifyEvent
	*/
	DELEGATE(NotifyDelegate,Notified)

protected:
	/**
	This map holds a list of CallBack that have been
	added to the object
	*/
	std::map<String,CallBack*> callbacks_;
};


}; //end of namespace VCF


#endif // _VCF_OBJECTWITHEVENTS_H__

/**
$Id$
*/
