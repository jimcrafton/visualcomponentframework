//EventBasics.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;



/**
This demonstration will explain how to use and create classes
that support events within the VCF
*/



/**
This class will fire an event when it's
talk method is called
*/
class Simple : public Object {
public:

	/**
	We define our delegate here.
	The delegate is what you hook
	up event handlers to.
	*/
	Delegate Talking;

	/**
	This method fires fires off
	an event to the Talking delegate.
	The Talking delegate then notifies
	each event handler that is attached to
	it and invoke the handler method
	*/
	void talk() {
		Event e(this);

		Talking.fireEvent( &e );
	}
};



void StaticTalkingCallBack( Event* e ) {
	System::println( "StaticTalkingCallBack called by object: %s", e->getSource()->toString().c_str() );
}

/**
we'll add a static function to our simple object's Talking delegate
*/
void example1() {

	System::println( "Example 1" );
	Simple simple;
	/**
	create the event handler
	*/
	EventHandler* handler = new StaticEventHandlerInstance<Event>( StaticTalkingCallBack );

	/**
	add the event handler to the Simple::Talking delegate
	*/
	simple.Talking.addHandler( handler );


	simple.talk();

	/**
	When we created the event handler we did not specify a source to hold the event handler
	and performa automatic cleanup for us. Because of this we need to delete it ourselves
	*/

	delete handler;

	System::println( "Finished with Example 1" );
}


/**
The next example will make a class that has a member function as a callback
Currently, we must make the class derive either directly or indirectly
from the VCF::Object base class.
*/
class SimpleCallBackClass : public Object {
public:
	/**
	All callback methods must take an event, and return void.
	They may be virtual methods.
	*/
	void onTalking( Event* e ) {
		System::println( "We got a talking event!" );
	}
};

void example2() {
	System::println( "Example 2" );

	Simple simple;

	SimpleCallBackClass callback;

	EventHandler* handler = new GenericEventHandler<SimpleCallBackClass>( &callback, &SimpleCallBackClass::onTalking );

	/**
	Add the handler to the Talking delegate. Note the
	use of the += operator to add the event handler. This
	is exactly equivalent to calling addHandler(handler).
	*/
	simple.Talking += handler;


	simple.talk();

	/**
	When we created the event handler we did specify a source but since the
	source did not derive from VCF::ObjectWithEvents, no automatic cleanup
	is performed. So we must delete the handler ourselves
	*/

	delete handler;

	System::println( "Finished with Example 2" );
}


/**
The next example will make a class that has a member function as a callback
Note that now we are making the class derive from VCF::ObjectWithEvents.
This will allow the class to maintain a collection of eventhandlers,
and when the instance is destroyed, the event handlers will also be destroyed.
The event handlers can also be named, and you can then refer to any of the event
handlers in the collection by name.
*/
class SimpleCallBackClass2 : public ObjectWithEvents {
public:
	SimpleCallBackClass2() {
		//lets add an event handler to our collection
		EventHandler* handler =
			new GenericEventHandler<SimpleCallBackClass2>( this, &SimpleCallBackClass2::onTalking, "SimpleCallBackClass2::onTalking" );

		/**
		The handler will be automatically cleaned up for us, os we don't have to worry about it
		*/
	}
	/**
	All callback methods must take an event, and return void.
	They may be virtual methods.
	*/
	void onTalking( Event* e ) {
		System::println( "We got a talking event! Event source: %s", e->getSource()->toString().c_str() );
	}
};

void example3()
{
	System::println( "Example 3" );

	Simple simple;

	SimpleCallBackClass callback;

	/**
	Note that the SimpleCallBackClass2
	wil automatically
	*/
	SimpleCallBackClass2 callback2;

	EventHandler* handler = new GenericEventHandler<SimpleCallBackClass>( &callback, &SimpleCallBackClass::onTalking );

	/**
	Add the handler to the Talking delegate.
	*/
	simple.Talking += handler;

	/**
	add callback2's event handler - we can access it by calling getEventHandler()
	*/
	simple.Talking += callback2.getEventHandler( "SimpleCallBackClass2::onTalking" );


	/**
	Now when we call talk we'll fire off the event to *multiple* event handlers
	*/
	simple.talk();

	delete handler;

	System::println( "Finished with Example 3" );
}



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();

	example2();

	example3();

	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:01  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.4  2004/04/29 03:40:53  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


