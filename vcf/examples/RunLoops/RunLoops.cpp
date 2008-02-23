////RunLoops.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadKit.h"
using namespace VCF;


class example{
public:
	example(const String& a):s(a){
		System::println( s + " starting." );
	}

	~example(){
		System::println( s + " finished." );
	}
private:
	String s;
};


void InnerLoop()
{
	System::println( "InnerLoop() called!" );

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	int numSecondsToRun = 9;
	DateTime start = DateTime::now();
	DateTime dt = DateTime::now();
	dt.incrSecond( numSecondsToRun );
	runLoop->run( dt );
	System::println( "InnerLoop() Run loop finished!" );
	
	DateTimeSpan len = DateTime::now() - start;

	System::println( Format("InnerLoop() Run loop lasted for %d seconds, we requested: %d seconds") % 
						len.getTotalSeconds() % 
						numSecondsToRun );

}



void InnerLoop2()
{
	System::println( "InnerLoop2() called!" );

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	int numSecondsToRun = 9;
	DateTime start = DateTime::now();
	DateTime dt = DateTime::now();
	dt.incrSecond( numSecondsToRun );
	runLoop->run( dt, "mymode" );
	System::println( "InnerLoop2() Run loop finished!" );
	
	DateTimeSpan len = DateTime::now() - start;

	System::println( Format("InnerLoop2() Run loop lasted for %d seconds, we requested: %d seconds") % 
						len.getTotalSeconds() % 
						numSecondsToRun );

}


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

	

	DateTimeSpan s = DateTime::now() - t;
	System::println( Format("Span: %d milliseconds") % s.getTotalMilliseconds() );
}


void Timer2( RunLoopTimer& timer )
{
	System::println( "Timer2 called!" );
	static int c = 0;
	c++;

	if ( c == 4 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->postEvent( new Procedure(InnerLoop), true );		
	}

	if ( c >= 10 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		System::println( "Timer2 is requesting run loop to stop!" );
		runLoop->stop();
	}
}


void Timer3( RunLoopTimer& timer )
{
	System::println( "Timer3 called!" );
	static int c = 0;
	c++;

	if ( c == 4 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->postEvent( new Procedure(InnerLoop2), true );		
	}

	if ( c >= 10 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		System::println( "Timer3 is requesting run loop to stop!" );
		runLoop->stop();
	}
}


void Timer4( RunLoopTimer& timer )
{
	System::println( "Timer4 called!" );
	static int c = 0;
	c++;

	if ( c == 4 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->postEvent( new Procedure(InnerLoop2), true );		
	}

	if ( c >= 10 ) {
		RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
		System::println( "Timer4 is requesting run loop to stop!" );
		runLoop->stop();
	}
}



void example1()
{	
	example e("example1()");

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
	example e("example2()");
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->postEvent( new Procedure1<Event*>(postEventHandler), new Event(NULL), true );
	runLoop->run();	
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
	example e("example3()");
	SmartPtr<SimpleSource>::Shared src(new SimpleSource());	

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();

	runLoop->addSource( src );
	runLoop->run();

	System::println( Format("SimpleSource answer: %d\n") % src->answer_ );

	runLoop->removeSource( src );
}



void example4() 
{
	example e("example4()");

	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	DateTime t = DateTime::now();
	runLoop->run( DateTimeSpan(1000) );

	DateTimeSpan s = DateTime::now() - t;
	System::println( Format("example4 finished in %d milliseconds") % s.getTotalMilliseconds() );
}


void example5()
{
	example e("example5()");
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->clearAllTimers();
	runLoop->clearAllSources();
	
	RunLoopTimerPtr::Shared timer( new RunLoopTimer( DateTimeSpan( 500 ) ) );
	timer->TimerFired += Timer2;

	runLoop->addTimer( timer );
	runLoop->run();

	//remember to clear out our timer's now that we are done!
	runLoop->removeTimer( timer );
};


void example6()
{
	example e("example6()");
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->clearAllTimers();
	runLoop->clearAllSources();
	
	RunLoopTimerPtr::Shared timer( new RunLoopTimer( DateTimeSpan( 500 ) ) );
	timer->TimerFired += Timer3;

	runLoop->addTimer( timer );
	runLoop->run();

	//remember to clear out our timer's now that we are done!
	runLoop->removeTimer( timer );
};

void example7()
{
	example e("example7()");
	RunLoopPtr::Shared runLoop = ThreadManager::getCurrentRunLoop();
	runLoop->clearAllTimers();
	runLoop->clearAllSources();
	
	RunLoopTimerPtr::Shared timer( new RunLoopTimer( DateTimeSpan( 500 ) ) );
	timer->TimerFired += Timer4;

	runLoop->addTimer( timer, RunLoop::SharedMode );
	runLoop->run();

	//remember to clear out our timer's now that we are done!
	runLoop->removeTimer( timer, RunLoop::SharedMode );
};



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();

	example2();

	example3();

	example4();

	example5();

	example6();

	example7();

	FoundationKit::terminate();
	return 0;
}


