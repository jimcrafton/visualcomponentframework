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
	Delegate1<Event*> Talking;

	/**
	This method fires fires off
	an event to the Talking delegate.
	The Talking delegate then notifies
	each event handler that is attached to
	it and invoke the handler method
	*/
	void talk() {
		Event e(this);

		Talking( &e );
	}
};



void StaticTalkingCallBack( Event* e ) {
	System::println( Format("StaticTalkingCallBack called by object: %s")
					% e->getSource()->toString() );
}

/**
we'll add a static function to our simple object's Talking delegate
*/
void example1() {

	System::println( "Example 1" );
	Simple simple;
	/**
	create the callback
	*/
	CallBack* callback = new Procedure1<Event*>( StaticTalkingCallBack );

	/**
	add the event handler to the Simple::Talking delegate
	*/
	simple.Talking.add( callback );


	simple.talk();

	/**
	When we created the event handler we did not specify a source to hold the event handler
	and perform automatic cleanup for us. Because of this we need to delete it ourselves
	*/

	callback->free();

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

	SimpleCallBackClass callbackInst;

	CallBack* callback = new ClassProcedure1<Event*,SimpleCallBackClass>( &callbackInst, &SimpleCallBackClass::onTalking );

	/**
	Add the handler to the Talking delegate. Note the
	use of the += operator to add the event handler. This
	is exactly equivalent to calling add(callback).
	*/
	simple.Talking += callback;


	simple.talk();

	/**
	When we created the event handler we did specify a source but since the
	source did not derive from VCF::ObjectWithEvents, no automatic cleanup
	is performed. So we must delete the handler ourselves
	*/

	callback->free();

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
class SimpleCallBackClass2 : public ObjectWithCallbacks {
public:
	SimpleCallBackClass2() {
		//lets add an event handler to our collection
		CallBack* callback =
			new ClassProcedure1<Event*,SimpleCallBackClass2>( this, &SimpleCallBackClass2::onTalking, "SimpleCallBackClass2::onTalking" );

		/**
		The handler will be automatically cleaned up for us, os we don't have to worry about it
		*/
	}
	/**
	All callback methods must take an event, and return void.
	They may be virtual methods.
	*/
	void onTalking( Event* e ) {
		System::println( Format("We got a talking event! Event source: %s")
						% e->getSource()->toString() );
	}
};

void example3()
{
	System::println( "Example 3" );

	Simple simple;

	SimpleCallBackClass callbackInst;

	/**
	Note that the SimpleCallBackClass2
	wil automatically
	*/
	SimpleCallBackClass2 callback2Inst;

	CallBack* callback = new ClassProcedure1<Event*,SimpleCallBackClass>( &callbackInst, &SimpleCallBackClass::onTalking );

	/**
	Add the handler to the Talking delegate.
	*/
	simple.Talking += callback;

	/**
	add callback2's event handler - we can access it by calling getEventHandler()
	*/
	simple.Talking += callback2Inst.getCallback( "SimpleCallBackClass2::onTalking" );


	/**
	Now when we call talk we'll fire off the event to *multiple* event handlers
	*/
	simple.talk();

	callback->free();

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
$Id$
*/
