////Conditions.cpp

#include "FoundationKit.h"

using namespace VCF;


static Mutex* theMutex = NULL;
static Condition* theCondition = NULL;
static producerDone = false;




class Reporter : public Runnable {
public:
	virtual bool run() {
		int count = 0;
		System::println( "Reporter %p starting...", this );

		while ( count < 10 && !producerDone ) {
			Lock l(*theMutex);
			
			theCondition->wait();

			System::println( "Reporter: Done waiting report %d, reporting from %p:\n\tNews Flash! Yada yada yada!", count + 1, this );
			count ++;
		}

		System::println( "Reporter done!" );

		return true;
	}

	virtual void stop() {
		System::println( "The Reporter has left the building!" );
	}
};


class Producer : public Runnable {
public:
	virtual bool run() {
		int count = 0;
		while ( count < 10 ) {
			Lock l(*theMutex);

			System::println("Producer chomping %d vitamins...\n\tchomp, chomp, chomp...", count );
			System::sleep( 300 );
			System::println( "Yawn...Burp!" );
			System::sleep( 100 );
			System::println( "...Fart!" );

			
			theCondition->broadcast();

			System::println( "Done chomping!" );


			count++;
		}

		System::println( "Producer done!" );
		producerDone = true;
		theCondition->broadcast();

		return true;
	}

	virtual void stop() {
		
	}
};



void example1() {
	theMutex = new Mutex();

	theCondition = new Condition( theMutex );


	Thread* th1 = new Thread( new Reporter() );
	th1->start();	

	Thread* th2 = new Thread( new Reporter() );
	th2->start();


	Thread* producer = new Thread( new Producer() );
	producer->start();
	
	producer->wait();
	
	
	//theCondition->broadcast();	

	System::sleep( 100 );


	theMutex->free();
	theCondition->free();
}




class bounded_buffer {
public:
    
    bounded_buffer(int n) : begin(0), end(0), buffered(0), circular_buf(n) { 
		buffer_not_full = new Condition( &monitor );
		buffer_not_empty = new Condition( &monitor );
	}

	~bounded_buffer() {
		buffer_not_full->free();
		buffer_not_empty->free();
	}

    void send (int m) {
        Lock lk(monitor);

        while (buffered == circular_buf.size()) {
            buffer_not_full->wait();
		}

        circular_buf[end] = m;

        end = (end+1) % circular_buf.size();

        buffered ++;

        buffer_not_empty->signal();
    }

    int receive() {
        Lock lk(monitor);
        while (buffered == 0) {
            buffer_not_empty->wait();
		}

        int i = circular_buf[begin];
        
		begin = (begin+1) % circular_buf.size();

        buffered --;

        buffer_not_full->signal();

        return i;
    }

private:
    int begin, end, buffered;

    std::vector<int> circular_buf;

    Condition* buffer_not_full;
	Condition* buffer_not_empty;

    Mutex monitor;
};



bounded_buffer* buffer;
int threadsDone = 2;

class Sender : public Thread {
public:
	
	virtual bool run() {
		int n = 0;
		while (n < 100) {
			buffer->send(n);
			System::println( "sent: %d", n );
			++n;
		}
		buffer->send(-1);

		threadsDone --;
		theCondition->signal();

		return true;
	}
};

class Receiver : public Thread {
public:
	
	virtual bool run() {
		int n;
		do {
			n = buffer->receive();
			System::println( "received: %d", n );
		} while (n != -1); // -1 indicates end of buffer

		threadsDone --;
		theCondition->signal();
		return true;
	}
};


void example2() 
{
	theMutex = new Mutex();
	theCondition = new Condition( theMutex );

	buffer = new bounded_buffer(10);
	Thread* send = new Sender();
	Thread* recv = new Receiver();

	send->start();
	recv->start();

	while ( threadsDone > 0 ) {
		theCondition->wait();
	}

	System::println( "example2 completed!" );
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();

	example2();


	FoundationKit::terminate();
	return 0;
}



