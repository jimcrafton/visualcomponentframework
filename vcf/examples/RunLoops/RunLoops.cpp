////RunLoops.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadKit.h"
using namespace VCF;

#define InnerLoopEv 2003211

void Timer1( Event* e )
{
	printf( "Timer1 called!\n" );
	static int c = 0;
	c++;

	RunLoop* runLoop = ThreadManager::getCurrentRunLoop();

	if ( c >= 10 ) {		
		runLoop->stop();
	}

	if ( c == 4 ) {
		runLoop->postEvent( new Event(NULL,InnerLoopEv) );
		
	}
}


void Timer2( Event* e )
{
	printf( "Timer2 called!\n" );
	static int c = 0;
	c++;

	if ( c >= 10 ) {
		RunLoop* runLoop = ThreadManager::getCurrentRunLoop();
		runLoop->stop();
	}
}

void InnerLoop( Event* e )
{
	if ( e->getType() == InnerLoopEv ) {
		RunLoop* runLoop = ThreadManager::getCurrentRunLoop();

		int numSecondsToRun = 9;
		DateTime start = DateTime::now();
		DateTime dt = DateTime::now();
		dt.incrSecond( numSecondsToRun );
		runLoop->run( "mymode", dt );
		System::println( "Run loop finished!" );
		
		DateTimeSpan len = DateTime::now() - start;

		System::println( Format("Run loop lasted for %d seconds, we requested: %d seconds") % 
							len.getTotalSeconds() % 
							numSecondsToRun );

	}
}


void example1()
{
	RunLoop* runLoop = ThreadManager::getCurrentRunLoop();
	
	StaticEventHandlerInstance<Event> ev(Timer1);
	StaticEventHandlerInstance<Event> ev2(Timer2);
	StaticEventHandlerInstance<Event> ev3(InnerLoop);

	uint32 timerID = runLoop->addTimer( "", NULL, &ev, 1000 );
	uint32 timerID2 = runLoop->addTimer( "", NULL, &ev2, 3000 );

	runLoop->LoopEvents += &ev3;


	runLoop->run();

	//remember to clear out our timer's now that we are done!

	runLoop->removeTimer( timerID );
	runLoop->removeTimer( timerID2 );
	runLoop->LoopEvents -= &ev3;
};


class SimpleSource : public RunLoopSource {
public:	

	enum {
		SimpleSourceEvent = 'SMPL'
	};

	SimpleSource() : answer_(0) {

	}

	virtual void setRunLoop( RunLoop* rl ) {
		runLoop_ = rl;
	}

	virtual void perform() {
		answer_ += 3;

		Event* e = new Event( NULL, SimpleSourceEvent );
		e->setUserData( (void*)this );
		runLoop_->postEvent( e );
	}

	virtual void cancel() {
		System::println( Format("Cancelled SimpleSource") );
	}

	RunLoop* runLoop_;

	unsigned int answer_;
};

void SimpleSrcCB( Event* e ) 
{
	if ( e->getType() == SimpleSource::SimpleSourceEvent ) {
		SimpleSource* src = (SimpleSource*)e->getUserData();
		static int simSrcLoopCount = 0;
		simSrcLoopCount ++;

		if ( simSrcLoopCount >= 200 ) {
			RunLoop* runLoop = ThreadManager::getCurrentRunLoop();
			runLoop->stop();
		}
	}
}

void example2()
{
	System::println( "Starting example 2" );
	SimpleSource src;
	StaticEventHandlerInstance<Event> ev(SimpleSrcCB);

	RunLoop* runLoop = ThreadManager::getCurrentRunLoop();

	runLoop->LoopEvents += &ev;

	runLoop->addSource( &src );
	runLoop->run();

	System::println( Format("SimpleSource answer: %d\n") % src.answer_ );

	runLoop->removeSource( &src );

	runLoop->LoopEvents -= &ev;
}




class SimpleSrcRunner : public Runnable {
public:
	SimpleSource* src_;
	SimpleSrcRunner( SimpleSource* src ) : src_(src){}

	virtual bool run() {
		System::println( "Starting SimpleSrcThread" );
		
		StaticEventHandlerInstance<Event> ev(SimpleSrcCB);
		
		RunLoop* runLoop = ThreadManager::getCurrentRunLoop();
		
		runLoop->LoopEvents += &ev;
		
		runLoop->addSource( src_ );
		runLoop->run();
		
		
		
		runLoop->removeSource( src_ );
		
		runLoop->LoopEvents -= &ev;

		Thread::getMainThread()->getRunLoop()->stop();

		return true;
	}

	virtual void stop(){ }
};


void example3()
{
	System::println( "Starting example 3" );
	SimpleSource src;	

	RunLoop* runLoop = ThreadManager::getCurrentRunLoop();

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


