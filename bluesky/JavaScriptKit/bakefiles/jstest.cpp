
#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"

#include "JavaScriptKit.h"


using namespace VCF;

// This class will be used as a JS global object.
class ClassWithMethods : public Object {
public:
    // This RTTI information will glue us to the JS engine.
    _class_rtti_( ClassWithMethods, "VCF::Object", "9083a1ec-73ac-4d89-b899-f0716e8f3c68" )
        _procedure1_( print, const String&, "s" )
    _class_rtti_end_

    // We call this method from our JS example file.
    void print( const String& str ) {
        System::println( str );
    }

    // Just print all the JS events.
    void onEvent( Event* e ) {
        JavaScriptEvent* jse = (JavaScriptEvent*) e;

        System::println( jse->message );
    }
};

int main( int argc, char** argv )
{
    FoundationKit::init( argc, argv );

    // Register the class information.
    REGISTER_CLASSINFO( ClassWithMethods ); 

    // Our demo class.
    ClassWithMethods* clazz = new ClassWithMethods();

    try {
        // Initialize the JS engine.
        JavaScriptEngine::initialize();
        JavaScriptEngine* js = &JavaScriptEngine::engine();

        // Add an event handler.
        EventHandler* handler = new GenericEventHandler<ClassWithMethods>( clazz, &ClassWithMethods::onEvent );
        js->ErrorOccurred += handler;
        js->ScriptExecuting += handler;

        
        // Update the JS engine from the VCF class registry.
        js->updateFromClassRegistry();
        js->defineGlobalObject( clazz );


        // Execute a script.
        js->executeScriptFromFile( "jstest.js" );


        // Remove the handler.
        js->ScriptExecuting -= handler;
        js->ErrorOccurred -= handler;
        delete handler;
        handler = NULL;


        // Terminate the JS engine.
        JavaScriptEngine::terminate();  
    }
    catch ( BasicException& e ) {
        System::print( Format( "error running script: %s\n" ) % e.getMessage() );
    }

    clazz->free();

    FoundationKit::terminate();
    return 0;
}
