////jstest.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/JavaScriptKit/JavaScriptKit.h"

using namespace VCF;




#define TestScript1  \
	"var harry = new HarryTheBear();"\
	"harry.boo();"



#define TestScript2  \
	"var harvey = new HarveyTheBug();"\
	"harvey.feelingGassy = true;"\
	"harvey.scram(); println(\"sdfsdf\");"


#define TestScript3  \
	"sdjklfhsdkfhksdf"


#define TestScript4  \
	"PrintMe.print( \"Hello there!\" );"

#define TestScript5  \
	"function onRunning(e) "\
	"{"\
	"  PrintMe.print(\"js event handler onRunning() called!\");"\
	"}"\
	"function onStateChanged(e) "\
	"{"\
	"  PrintMe.print(\"js event handler onStateChanged() called!\");"\
	"}"\
	"var hermes = new HermesTheFleet();"\
	"hermes.StateChanged = onStateChanged;"\
	"hermes.RunningLaps = onRunning;"\
	"hermes.numLaps = 10;"\
	"hermes.running = true;"




class HarryTheBear : public Object {
public:
	HarryTheBear(){}

	void boo() {
		System::println( "Harry says: Boo!!!" );
	}
};




class HarveyTheBug : public Object {
public:
	HarveyTheBug():feelingGassy_(false){}

	void scram() {
		System::println( Format("Harvey says: Get outta here, %s!!!") % (feelingGassy_ ? "I'm feeling gassy" : "I hate the world") );
	}

	bool feelingGassy() {
		return feelingGassy_;
	}

	void setFeelingGassy( const bool& val ) {
		feelingGassy_ = val;
	}
protected:
	bool feelingGassy_;
};


class PrintMe : public Object  {
public:
	void print( const String& s ) {
		System::println( s );
	}
};


class HermesTheFleet : public Object {
public:

	DELEGATE(EventDelegate,StateChanged);
	DELEGATE(EventDelegate,RunningLaps);


	HermesTheFleet():running_(false),numLaps_(1){}

	bool running() {
		return running_;
	}

	void setRunning( const bool& val ) {
		running_ = val;

		Event e(this,0);
		StateChanged(&e);

		if ( running() ) {
			for (int i=0;i<numLaps();i++ ) {
				Event e2(this,0);
				RunningLaps(&e2);
				System::sleep(100);
			}
		}
	}

	int numLaps() {
		return numLaps_;
	}

	void setNumLaps( const int& val ) {
		numLaps_ = val;

		Event e(this,0);
		StateChanged(&e);
	}
protected:
	bool running_;
	int numLaps_;
};

// This RTTI information will glue us to the JS engine.
_class_rtti_( HarryTheBear, "VCF::Object", "9083a1ec-73ac-4d89-b899-f0716e8f3c68" )
    _procedure_( boo )
_class_rtti_end_

_class_rtti_( HarveyTheBug, "VCF::Object", "f574705a-c9c4-4b81-b916-61e71d4531c2" )
    _procedure_( scram )
	_property_(bool,"feelingGassy",feelingGassy,setFeelingGassy,"" )
_class_rtti_end_

_class_rtti_( PrintMe, "VCF::Object", "21614fe1-de12-407e-abcc-049ff386178e" )
    _procedure1_( print, const String&, "s" )	
_class_rtti_end_

_class_rtti_( HermesTheFleet, "VCF::Object", "66440e9c-f172-4186-b829-07d19758608e" )
	_property_(bool,"running",running,setRunning,"" )
	_property_(int,"numLaps",numLaps,setNumLaps,"" )
	_event_("VCF::GenericEventHandler",VCF::Event,StateChanged)
	_event_("VCF::GenericEventHandler",VCF::Event,RunningLaps)
_class_rtti_end_



void OnError( Event* e )
{
	JavaScriptEvent* jse = (JavaScriptEvent*) e;
	System::println( "JS Error: " + jse->message );
}

void OnScriptExec( Event* e )
{
	JavaScriptEvent* jse = (JavaScriptEvent*) e;
	System::println( "Script exec: " + jse->message );
}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	JavaScriptKit::init( argc, argv );

	REGISTER_CLASSINFO_EXTERNAL( HarryTheBear ); 
	REGISTER_CLASSINFO_EXTERNAL( HarveyTheBug ); 
	REGISTER_CLASSINFO_EXTERNAL( PrintMe ); 
	REGISTER_CLASSINFO_EXTERNAL( HermesTheFleet ); 

	PrintMe printMeInstance;

	try {
        // Initialize the JS engine.
        JavaScriptEngine::initialize();

        // Add an event handler.
        EventHandler* errHandler = new EventHandler( &OnError );
		EventHandler* scriptHandler = new EventHandler( &OnScriptExec );

        JavaScriptEngine::engine().ErrorOccurred += errHandler;
		JavaScriptEngine::engine().ScriptExecuting += scriptHandler;


		//make the js engine aware of all the known VCF Class's in the ClassRegistry at
		//this point in time.
		JavaScriptEngine::engine().updateFromClassRegistry();
        
		JavaScriptEngine::engine().defineGlobalObject( &printMeInstance );

		String script = TestScript1;
		JavaScriptEngine::engine().executeScript( script );

		script = TestScript2;
		JavaScriptEngine::engine().executeScript( script );

		
		//test an error!
		script = TestScript3;
		JavaScriptEngine::engine().executeScript( script );

		script = TestScript4;
		JavaScriptEngine::engine().executeScript( script );
		

		script = TestScript5;
		JavaScriptEngine::engine().executeScript( script );


		JavaScriptEngine::engine().executeScriptFromFile( "test1.js" );


		JavaScriptEngine::engine().ErrorOccurred -= errHandler;
		JavaScriptEngine::engine().ScriptExecuting -= scriptHandler;
        		
        // Terminate the JS engine.
        JavaScriptEngine::terminate();  

		

		delete errHandler;
		delete scriptHandler;

    }
    catch ( BasicException& e ) {
        System::print( Format( "error running script: %s\n" ) % e.getMessage() );
    }


	JavaScriptKit::terminate();

	FoundationKit::terminate();
	return 0;
}


