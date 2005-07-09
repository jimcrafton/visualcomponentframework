//ThreadBasics.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadManager.h"

using namespace VCF;


/**
This will demonstrate the usage of some simple threads.
We'll cover the following :

Creating a thread that deletes itself, and runs over a fixed
series of operations - see example1()

Creating a thread that delete's itself, but is stopped before
it finishes what it's doing - see example2()

Creating a thread that is does not automatically delete
itself  - see example3()

Derive a new class from Runnable and use a Thread to
run it - see example4().

*/


/**
global variable to tell when the thread's done
*/
bool test1Done = false;
bool example1Done = false;
bool example2Done = false;
bool example3Done = false;

/**
This will create a simple thread that loops
10,000 times, incrementing a counter
and then printing out the counter value
to stdout.
Notice the usage of checking the
Thread::canContinue() method. It is critical
that any kind of looping or repetitive functionality
use this test to determine if the thread should continue.
If Thread::canContinue() should return false, a correct
implementation of a run() method must return as soon as
possible.
Since we do not provide any constructor for our
SimpleThread thread class we use the default
constructors for Thread.
*/
class SimpleThread : public Thread {
public:

	/**
	this is our method execution.
	We override the run() method from
	Thread.
	*/
	virtual bool run() {
		test1Done = false;
		int i = 0;
		while ( i < 10000 ) {
			if ( (i % 100) == 0 ) {
				System::println( Format("printing i: %d") % i );
			}
			i++;
		}
		
		test1Done = true;

		Thread* th = ThreadManager::getCurrentThread();

		System::println( Format("ThreadManager::getCurrentThread(): %p, this: %p") % th % this );

		return true;
	}

protected:
	/**
	destroy will get called just prior to the instance's destructor.
	destroy is useful to overide and put clean up code in because it is
	still valid to make calls to virtual methods here. Due to the nature
	of C++, virtual method calls made in an object's destructor may not
	perform	as expected.
	*/
	virtual void destroy() {
		System::println( Format("Bye, bye from %p") % this );
	}
};



/**
This example create the thread,
and starts it. The thread will delete
itself, so all we have to do is wait for
the test1Done variable to become true.
Note that 2 loops are running - the process's
main loop (in this code the "while ( !test1Done ) {"
loop), and the loop for the SimpleThread's run()
method.

Note that once we create and start the thread, we do
not reference the pointer any more. Since the thread
can complete it task at any point, and once completed
it will self delete, we have to be careful when we
reference the pointer.
Threads that auto deleted are appropriate to use where
the thread object can operate on it's own and doesn't
need to be intereacted with by anyone else.
*/
void example1()
{
	example1Done = false;

	System::println( "\nexample1 starting" );
	/**
	Create the thread - notice it created on the heap
	*/
	Thread* thread = new SimpleThread();
	/**
	start the thread - if you don't call this your thread
	won't run!. Alternately, in this case, we could
	have placed the call to start() in the SimpleThread
	class's constructor.
	*/
	thread->start();

	/**
	Now loop around, sleeping for 1 second
	(1000 milliseconds), and print to stdout.
	*/
	while ( !test1Done ) {

		System::println( "The main thread is now going to sleep for 1 millisec...\n" );
		System::sleep( 1 );

	}

	/**
	example 1 is now finished!
	*/
	System::println( "example1 done" );
	example1Done = true;
}


/**
This thread will delete itself.
Note the use of the canContinue() check.
*/
class SimpleThread2 : public Thread {
public:

	/**
	this is our method execution.
	We override the run() method from
	Thread.
	*/
	virtual bool run() {

		int i = 0;
		while ( i < 10000 ) {

			System::println( Format("printing i: %d") % i );

			i++;
			/**
			Note the detection that we have been interrupted (canContinue() returning false)
			and how we gracefully leave the loop and end the thread
			*/
			if ( !canContinue() ) {
				if ( i < 10000 ) {
					System::println( "Thread interrupted before i reached 10000" );
				}
				break;
			}
		}

		return true;
	}

protected:
	virtual void destroy() {
		System::println( Format("Bye, bye from %p") % this );
	}
};

/**
This will demostrate the usage of
calling stop to interupt the threads work.
The thread is still set up to auto delete,
so we have to be a bit careful here.
*/
void example2()
{
	example2Done = false;
	System::println( "\nexample2 starting" );
	Thread* thread = new SimpleThread2();
	thread->start();


	System::println( "The main thread is now going to sleep for 100 millisec...\n" );
	System::sleep( 100 );

	//hopefully the thread has not finished at this point
	System::println( "The main thread is now going to stop the child thread...\n" );
	thread->stop();


	System::println( "example2 done" );
	example2Done = true;
}



/**
This is our simple thread class
that does not automatically delete itself
*/
class SimpleThread3 : public Thread {
public:
	/**
	We have to declare a constructor
	here. Note that we pass in "false"
	to the Thread constructor. This is
	to indicate that we are not to be
	automatically deleted. By default
	a Thread is automatically deleted.
	*/
	SimpleThread3() : Thread(false), counter_(0) {

	}

	/**
	our run method simply increments our counter
	till it hits 100 or the thread can no longer
	continue.
	*/
	virtual bool run() {

		counter_ = 0;

		while ( (counter_ < 100) && canContinue() ) {
			System::println( Format("counter_: %d") % counter_ );
			counter_++;
		}

		return true;
	}

	/**
	our done method simply allows a caller to determine if the
	thread is finished with it's task.
	*/
	bool done() {
		return counter_ >= 100;
	}
	int counter_;

protected:
	virtual void destroy() {
		System::println( Format("Bye, bye from %p") % this );
	}

};


/**
This wil demonstrate a thread that does
not automatically delete itself.
Instead the creator of the thread is
responsible for it's clean up.
*/
void example3()
{
	example3Done = false;
	System::println( "\nexample3 starting" );
	SimpleThread3* thread = new SimpleThread3();
	thread->start();

	while ( !thread->done() ) {
		System::println( "The main thread is now going to sleep for a sec...\n" );
		System::sleep( 1000 );
	}

	System::println( Format("Thread process id: 0x%08x, thread id: 0x%08x")
						% thread->getOwningProcessID()
						% thread->getThreadID() );

	System::println( Format("Thread: %s") % thread->toString().c_str() );
	thread->free();


	System::println( "example3 done" );
	example3Done = true;
}


/**
A little class to wrap a function
*/
class ExampleTest {
public:
	typedef void (*exampleFunc)();

	ExampleTest( exampleFunc func ): done_(false),func_(func) {

	}

	void callFunc() {
		func_();
		done_ = true;
	}

	bool done() {
		return done_;
	}
	bool done_;
	exampleFunc func_;
};

/**
We create a runnable class here.
A class is runnable if it implements the
VCF::Runnable interface, and overrides the run()
method. In our example we will simply call the
function pointer store in our ExampleTest
class
*/
class RunnableExample : public ExampleTest, public Runnable {
public:
	RunnableExample( exampleFunc func ): ExampleTest(func) {

	}

	virtual ~RunnableExample() {
		System::println( Format("RunnableExample destroyed!: %p") % this );
	}

	virtual void stop() {
		/* we don't have any cleanup to perform in this example */
	}

	virtual bool run() {
		callFunc();
		return true;
	}
};

/**
This demonstrates the use a thread and a separate Runnable
object.
Each runnable object is attached to a thread. Each runnable object
is connected to a function pointer for each of the
previous examples. Once instantiated, each thread is immediately started
thus demonstrating how the Runnable interface works, and 3 simultaneous
threads running together
*/
void example4()
{
	System::println( "\nexample4 starting.\nThis will run all the previous examples in separated simultaneous threads." );



	Thread* thread1 = new Thread( new RunnableExample(example1) );
	Thread* thread2 = new Thread( new RunnableExample(example2) );
	Thread* thread3 = new Thread( new RunnableExample(example3) );

	example1Done = false;
	example2Done = false;
	example3Done = false;

	thread1->start();
	thread2->start();
	thread3->start();


	while ( (!example1Done) || (!example2Done) || (!example3Done) ) {

		System::sleep( 1000 );
		System::println( "Waiting for examples..." );

	}

	System::println( "example4 done" );
}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );


	example1();

	example2();

	example3();

	example4();

	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:46  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.4.2  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3.4.1  2005/04/17 15:12:05  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.3  2004/08/07 02:47:40  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.5  2004/07/05 00:14:14  marcelloptr
*minor improvements on the messages displayed by this example
*
*Revision 1.2.4.4  2004/04/29 03:40:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


