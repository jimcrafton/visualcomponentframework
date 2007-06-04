////ThreadMeth.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadPool.h"
#include "vcf/FoundationKit/ThreadedFunctions.h"


#include "Delegates.h"

using namespace VCF;




ThreadPool* delegate::delegateThreadPool = NULL;


inline String operator+ ( const char* lhs, const BasicException& rhs )
{
	return String(lhs) + rhs.getMessage();
}


void doit( int i ) {
	printf( "Hello from doit! i: %d\n", i );
	::Sleep( 3000 );
}




void doit2( Thread* th, int i ) {
	printf( "Hello from doit2! i: %d, th: %p, tid: 0x%04x \n", i, th, th->getThreadID() );

}

class Snarfy {
public:
//	virtual ~Snarfy(){}

	void thisBlows( int g ) {
		printf( "Hello from thisBlows! i: %d, this ptr: %p\n", g, this );
	}
};


class Swanky {
public:
	void doit( double& d, const String& s ) {
		printf( "Hello from Swanky::doit! d: %0.3f, s: %s, this ptr: %p\n", 
					d, s.ansi_c_str(), this );
	}


	void doit2( Thread* th, double& d, const String& s ) {
		printf( "Hello from Swanky::doit! d: %0.3f, s: %s, this ptr: %p\n", 
					d, s.ansi_c_str(), this );

		for (int i=0;i<10;i++) {
			th->sleep(1000);
		}
	}

	void doit3() {
		printf( "Hello from Swanky::doit3! this ptr: %p\n", this );
	}
};



void abc(int,double,char)
{

}

void abc2(int, const String&,double,char,bool,Object*)
{

}

void abc3(){

}


int abc4()
{
	return 100;
}

class FooBar {
public:	
	int duh()
	{
		return 100;
	}
};

bool duhDoIt( const String& str, double d )
{
	bool result = true;
	printf( "duhDoIt() %s, %0.5f, returning %d\n", str.ansi_c_str(), d, result );
	return result;
}


class Blooper : public Object {
public:

	bool stuffIt( const String& str, double d )
	{
		bool result = false;
		printf( "Blooper::stuffIt() %s, %0.5f, returning %d\n", str.ansi_c_str(), d, result );
		return result;
	}

};


class RunThis : public Runnable {
public:
	RunThis(){
		printf( "Creating RunThis %p\n", this );
	}

	virtual ~RunThis() {
		printf( "Deleting RunThis %p\n", this );
	}

	virtual bool run() {

		Thread* th = ThreadManager::getCurrentThread();

		printf( "RunThis %p on thread %p id 0x%04x\n", this, th, th->getThreadID() );
		th->sleep(3000);
		return true;
	}

	virtual void stop(){}
};


void HopAlong(int,char,double,String)
{
	printf( "HopAlong\n");
}

void HopAlongA(int,char,double,String,bool)
{
	printf( "HopAlongA\n");
}

String whatAmI(int)
{
	printf( "whatAmI\n");
	return "Gooofy!";
}



String whatAmI2(int,bool)
{
	printf( "whatAmI2\n");
	return "Gooofy!";
}


double whatAmI24(int,bool,String*)
{
	printf( "whatAmI24\n");
	return 9.0010;
}


double whatAmIb(int,bool,int*,char**, String,Object*)
{
	printf( "whatAmIb\n");
	return 9.0010;
}


void doneWithInvokes( AsyncResult* result ) 
{
	printf( "doneWithInvokes called! AsyncResult is completed? : %s\n", result->isCompleted() ? "Yes" : "No" );
}



class Obj1 : public ObjectWithCallbacks {
public:


	void doIt(int i) {
		System::println( "Obj1 returns " + StringUtils::toString(i) );
	}
};


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	Snarfy sn;
	String s;
	Swanky sk;
	
/*
	Thread* th = ThreadedProcedure1<int>(10,doit).invoke();
	
	th->wait();

	th = ThreadedProcedure1<int>(231,doit2).invoke();

	th->wait();
	
	
	

	th = ThreadedProcedure1<int,Snarfy>(&sn,38112,&Snarfy::thisBlows).invoke();
	th->wait();



	s = "hello";
	

	double d = 0.0332;
	
	th = ThreadedProcedure2<double&,const String&,Swanky>(&sk,d,s,&Swanky::doit2).invoke();
	th->wait();


	printf( "Bye!\n");


	ThreadedProcedure3<int,double,char>(10,200.0,'a',abc).invoke();

	ThreadedProcedure4<int,char,double,String>(10,'a',200.0,"poop",HopAlong).invoke();

	ThreadedProcedure5<int,char,double,String,bool>(10,'a',200.0,"poop",true,HopAlongA).invoke();

	
	ThreadedProcedure6<int, const String&,double,char,bool,Object*>(10,s,200.0,'a',true,th,abc2).invoke();
	
	ThreadedProcedure<Swanky>(&sk, &Swanky::doit3).invoke();

	ThreadedProcedure<>(abc3).invoke();



	
	ThreadedProcedure<> g(abc3);
	g.invoke();


	FooBar fb;
	ThreadedFunction<int,FooBar>(&fb, &FooBar::duh).invoke();



	ThreadedFunction<int> h(abc4);
	h.invoke();
	



	th = ThreadedFunction1<String,int>(56,whatAmI).invoke();
	th->wait();

	th = ThreadedFunction2<String,int,bool>(102,true,whatAmI2).invoke();
	th->wait();

	th = ThreadedFunction3<double,int,bool,String*>(102,true,NULL,whatAmI24).invoke();
	th->wait();

	th = ThreadedFunction6<double,int,bool,int*,char**, String,Object*>(102,true,NULL,argv,"",NULL,whatAmIb).invoke();
	th->wait();

*/


	Delagate1<int> d2;
	d2 += doit;


	
	d2 += new ClassProcedure1<int,Snarfy>(&sn,&Snarfy::thisBlows,"Snarfy::thisBlows");


	{
		Obj1 obj;
		d2 += new ClassProcedure1<int,Obj1>(&obj,&Obj1::doIt,"Obj1::doIt");

		d2( 100 );
	}
	




	AsyncCallback acb(doneWithInvokes) ;
	AsyncResult* ar = d2.beginInvoke( 10, &acb );

	ar->wait();

	ar->free();


	s = d2.at( 0 ).getReturnType().name();


	Delagate2R<bool,const String&,double> d3;

	d3 += duhDoIt;


	Blooper bl;

	d3 += new ClassFunction2<bool,const String&,double,Blooper>(&bl,&Blooper::stuffIt);

	s = d3.at( 1 ).getReturnType().name();
	CallBack::TypeArray types = d3.at( 1 ).getArgumentTypes();

	uint32 ac = types.size();
	s = types[0]->name();
	s = types[1]->name();

	bool result = d3.invoke("Hola", 120.456);
	printf( "d2 result: %d\n", result );
	for ( int i=0;i<d3.results.size();i++ ) {
		printf( "d2 results[%d]: %d\n", i, (int)d3.results[i] );
	}
	




	
	



	String h("hola!");
	d3.setRunCallbacksAsynchronously(true);

	ar = d3.beginInvoke( h, 120.456, NULL );

	ar->wait();

	bool b = d3.endInvoke( ar );

	ar->free();


	//test adding bogus callback type
	try {
		d3 += new ClassProcedure1<int,Snarfy>(&sn,&Snarfy::thisBlows,"Snarfy::thisBlows");
	}
	catch ( BasicException& e ) {
		System::println( "Error: " + e );
	}


	delegate::terminateThreadPool();


	FoundationKit::terminate();
	return 0;
}


