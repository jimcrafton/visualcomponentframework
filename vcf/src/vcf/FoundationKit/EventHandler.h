#ifndef _VCF_EVENTHANDLER_H__
#define _VCF_EVENTHANDLER_H__
//EventHandler.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Delegate;


/**
\class EventHandler EventHandler.h "vcf/FoundationKit/EventHandler.h"
EventHandler's form the back bone of the event
model in the VCF. The EventHandler base class
provides a clean way to invoke the class
specific member function pointers in the
derived EventHandlerInstance template class.

The EventHandler is an abstract class an cannot be created.
Instead you need to derive your own custom class from it
and implement the invoke() method. Typically you can 
just use one of the already provided class, either the 
StaticEventHandlerInstance for wrapping static (or "C" style functions),
or the various template derived classes that wrap a classes 
member function. 

*/
class FOUNDATIONKIT_API EventHandler : public VCF::Object {
public:
	typedef std::vector<EventHandler*> Vector;

	EventHandler(){};

	virtual ~EventHandler();

	/**
	
	Called during the events dispatch cycle.
	The implementation will end up calling the
	appropriate call back method.
	*/
	virtual void invoke( Event* e ) = 0;


	/**
	Returns the source that the event handler is attached to. Some 
	event handler implementations may not return a source for public
	use, or may not use one at all, so this method may return NULL. 
	An example of not using a source would be the StaticEventHandlerInstance
	which is used to wrap static functions.
	The default implementation returns a NULL object source.
	*/
	virtual Object* getSource() {
		return NULL;
	}


	/**
	
	Adds the EventHandler to it's source object.
	For this to work the source must be derived
	from ObjectWithEvents. By adding the event handler
	to the source, the handler's memory will be cleaned
	up by the source when the source is destroyed.
	
	The EventHandler may be retreived at any time
	by calling the getEventHandler() method on the
	source (once again, assuming the source is derived
	from ObjectWithEvents).
	@param Object the source to which the EventHandler
	will be added.
	@param String the name the EventHandler is referred to.
	This should be a reasonably unique name.
	*/
	void addHandlerToSource( Object* source, const String& handlerName );

	String getHandlerName();
protected:

	String getHandlerNameFromSource( Object* source );	
};


/**
\class EventHandlerInstance EventHandler.h "vcf/FoundationKit/EventHandler.h"
The EventHandlerInstance class is used to provide a
typesafe wrapper around a specific class's member function pointer.
In addition, when the instance is created, if the source passed in is
derived from VCF::ObjectWithEvents, then the handler will be
maintained in a list by the source, and destroyed when the source
is destroyed, freeing the creator of the handler from worrying about
memory leaks.
 
The SOURCE template parameter specified the source class that 
the event handler method is a member of. The EVENT template
parameter is the event class type. The event class type
\em must derive (directly or indirectly) from VCF::Event,
and it must be the same event type that is specified in the
event handler signature. The basic event handler
signature is:
\code
void someMethod( EVENT* event );
\endcode
For example
\code
class Foo : public Object {
public:
  void onSomeEvent( Event* e );
};

int main()
{
  Foo f;
  EventHandler* ev = new EventHandlerInstance<Foo,Event>(&f,&Foo::onSomeEvent);
  return 0;
}
\endcode

In the case above we simply created a new event handler
instance that wrap's the Foo::onSomeEvent() method. If we 
wanted to specify a different type:
\code
class Foo : public Object {
public:
  void onSomeEvent( MouseEvent* e );
};

int main()
{
  Foo f;
  EventHandler* ev = new EventHandlerInstance<Foo,MouseEvent>(&f,&Foo::onSomeEvent);
  return 0;
}
\endcode
We can do so by changing the method signature of onSomeEvent() from taking
a VCF::Event isntance to VCF::MouseEvent instance. The code above will have a
memory leak, since we are allocating a new EventHandler isntance
but not deleting it. If we would like to have the event handlers managed for
us, then one solution is use the ObjectWithEvents class, for example:
\code
class Foo : public ObjectWithEvents {
public:
  void onSomeEvent( MouseEvent* e );
};

int main()
{
  Foo f;
  EventHandler* ev = new EventHandlerInstance<Foo,MouseEvent>(&f,&Foo::onSomeEvent, "Foo::onSomeEvent");
  return 0;
}
\endcode
Now when the EventHandlerInstance instance is create it will be added to the 
Foo "source" instance and assigned a name of "Foo::onSomeEvent" (the name 
can be whatever you want, but be aware that if you come up with duplicate names
you'll see memory leaks). This event can then be retrieved at a later time via:
\code
EventHandler* ev = f.getEventHandler( "Foo::onSomeEvent" );
\endcode
When the Foo instance is destroyed it will automatically destroy all of it's 
event handlers in it's list.
@see Event
@see ObjectWithEvents
*/
template <class SOURCE, class EVENT>
class EventHandlerInstance : public EventHandler {
public:
	typedef void (SOURCE::*OnEventHandlerMethod)( EVENT* e );

	/**
	@param SOURCE the source instance. This is the instance that the 
	event handler method will be invoked on.
	@param OnEventHandlerMethod the mehthod pointer that this event handler
	will call when the invoke() method is triggered.
	@param String the name of the event handler. This is optional. If no
	name is specified (the default), then the event handler will \em not
	be added to the source instance. If the a name is specified and the 
	source instance derives from ObjectWithEvents, then the event handler
	instance will be added to the source with the name passed in destroyed 
	when the source is destroyed. Note that any text may be used for the name, 
	but if an event handler already exists on the source with that same name,
	then a memory leak will occur. If instead the same handler will be added 
	twice with two different names we may have a memory access exception, 
	as the framework will try to delete twice the same object.
	*/
	EventHandlerInstance( SOURCE* source, OnEventHandlerMethod handlerMethod, const String& handlerName="" ) {
		source_ = source;
		handlerMethod_ = handlerMethod;

		addHandlerToSource( source, handlerName );
	}

	virtual ~EventHandlerInstance(){

	}

	virtual void invoke( Event* e ) {
		if ( (NULL != source_) && (NULL != handlerMethod_) ) {
			(source_->*handlerMethod_)( dynamic_cast<EVENT*>(e) );
		}
	}

	virtual Object* getSource() {
		return source_;
	}
protected:
	SOURCE* source_;
	OnEventHandlerMethod handlerMethod_;
};

/**
\class StaticEventHandlerInstance EventHandler.h "vcf/FoundationKit/EventHandler.h"
StaticEventHandlerInstance's are used to provide a
typesafe wrapper around a specific class's <b>static</a> function pointers,
as opposed to method pointers (which take the implicit this pointer).
In addition, when they are created, if the source passed in is
derived from VCF::ObjectWithEvents /em and the handler name is specified,
then the handler will be maintained in a list by the source, and destroyed 
when the source is destroyed, freeing the creator of the handler from 
worrying about memory leaks.
*/
template <class EVENT>
class StaticEventHandlerInstance : public EventHandler {
public:
	typedef void (*OnStaticEventHandlerMethod)( EVENT* e );

	StaticEventHandlerInstance( OnStaticEventHandlerMethod handlerMethod,
								Object* source=NULL,
								const String& handlerName="" ) {
		handlerMethod_ = handlerMethod;
		if( NULL != source ) {
			addHandlerToSource( source, handlerName );
		}
	}

	virtual ~StaticEventHandlerInstance(){

	}

	virtual void invoke( Event* e ) {
		if ( NULL != handlerMethod_ ) {
			(*handlerMethod_)( dynamic_cast<EVENT*>(e) );
		}
	}

protected:
	OnStaticEventHandlerMethod handlerMethod_;
};


/**
\class GenericEventHandler EventHandler.h "vcf/FoundationKit/EventHandler.h"
The GenericEventHandler class is provided as a convenience class for use when dealing with a generic
Event object.
*/
template <class SOURCE_TYPE>
class GenericEventHandler : public EventHandlerInstance<SOURCE_TYPE,Event> {
public:
	GenericEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,Event>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,Event>( source, handlerMethod, handlerName ) {

	}

	virtual ~GenericEventHandler(){};
};

}; //end of namespace VCF


#endif // _VCF_EVENTHANDLER_H__

/**
$Id$
*/
