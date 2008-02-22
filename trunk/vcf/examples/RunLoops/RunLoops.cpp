////RunLoops.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadKit.h"
using namespace VCF;

#define InnerLoopEv 2003211

void Timer1( RunLoopTimer& timer )
{
	System::println( "Timer1 called!" );
	static DateTime t = DateTime::now();


	static int c = 0;
	c++;

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	if ( c >= 10 ) {		
		runLoop->stop();
	}

	if ( c == 4 ) {
//		runLoop->postEvent( new Event(NULL,InnerLoopEv) );
		
	}

	DateTimeSpan s = DateTime::now() - t;
	System::println( Format("Span: %d milliseconds") % s.getTotalMilliseconds() );
}


void Timer2( Event* e )
{
	System::println( "Timer2 called!" );
	static int c = 0;
	c++;

	if ( c >= 10 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->stop();
	}
}

void InnerLoop( Event* e )
{
	if ( e->getType() == InnerLoopEv ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

		int numSecondsToRun = 9;
		DateTime start = DateTime::now();
		DateTime dt = DateTime::now();
		dt.incrSecond( numSecondsToRun );
		runLoop->run();// "mymode", dt );
		System::println( "Run loop finished!" );
		
		DateTimeSpan len = DateTime::now() - start;

		System::println( Format("Run loop lasted for %d seconds, we requested: %d seconds") % 
							len.getTotalSeconds() % 
							numSecondsToRun );
	}
}


void example1()
{
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	
	RunLoopTimerPtr::Shared timer1( new RunLoopTimer( DateTimeSpan( 1000 ) ) );
	timer1->TimerFired += Timer1;

	runLoop->addTimer( timer1 );
	runLoop->run();

	//remember to clear out our timer's now that we are done!
	runLoop->removeTimer( timer1 );
};

void postEventHandler( Event* e )
{
	System::println( Format("postEventHandler called, event: %p, %s") % e % e->toString() );
	ThreadManager::getCurrentRunLoop()->stop();
}

void example2()
{
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->postEvent( new Procedure1<Event*>(postEventHandler), new Event(NULL), true );
	runLoop->run();

	System::println( "example 2 done." );	
}

class SimpleSource : public RunLoopSource {
public:	
	SimpleSource() : answer_(0) {
		signal();
	}

	virtual void perform() {
		answer_ += 3;

		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->stop();
	}

	virtual void cancel() {
		System::println( Format("Cancelled SimpleSource") );
	}

	unsigned int answer_;
};

void example3()
{
	System::println( "Starting example 2" );
	SmartPtr<SimpleSource>::Shared src(new SimpleSource());	

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	runLoop->addSource( src );
	runLoop->run();

	System::println( Format("SimpleSource answer: %d\n") % src->answer_ );

	runLoop->removeSource( src );
}




class SimpleSrcRunner : public Runnable {
public:
	SmartPtr<SimpleSource>::Shared src_;
	SimpleSrcRunner( SimpleSource* src ) : src_(src){}

	virtual bool run() {
		System::println( "Starting SimpleSrcThread" );
		
		
		//StaticEventHandlerInstance<Event> ev(SimpleSrcCB);
		
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		
		//runLoop->LoopEvents += &ev;
		
		runLoop->addSource( src_ );
		runLoop->run();
		
		
		
		runLoop->removeSource( src_ );
		
		//runLoop->LoopEvents -= &ev;

		Thread::getMainThread()->getRunLoop()->stop();

		return true;
	}

	virtual void stop(){ }
};


void example4()
{
	System::println( "Starting example 3" );
	SimpleSource src;	

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	Thread* th = new Thread( new SimpleSrcRunner(&src) );
	th->start();
	runLoop->run();

	System::println( Format("SimpleSource answer: %d\n") % src.answer_ );	
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();

	example2();

	example3();

	FoundationKit::terminate();
	return 0;
}


