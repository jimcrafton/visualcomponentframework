////SharedLibraries.cpp

#include "FoundationKit.h"

using namespace VCF;
/**
* A simple program showing how to use the Library class to load a
*dynamic library at run time, retreive a function and invoke the function
*dynamically
*
*Make sure that you compile the SimpleDLL.cpp file - this can be done
*with the following:
	g++ -fPIC -shared -o libSimpleDLL.so SimpleDLL.cpp
*/

int main( int argc, char** argv )
{
	//lets be good and initialize the FoundationKit..
	FoundationKit::init( argc, argv );
	
	System::print("Begining test for DynamicLibraries\n");

	//create an instance of the Library on the stack.
	//This class can be created on the heap or the stack.	
	Library lib;

	//load the library up. This library name can also be passed in to the
	//constructor of the Library instance
	//if the library doesn't exist or can't be found Library::load() will
	//throw an exception
	try {
		lib.load( "SimpleDLL.so" );

		//make a typedef of our function prototype
		//you can see this in the SimpleDLL.h header
		typedef int (*GetInt)(int,double);
	
		GetInt func;
		//this will get the function address from the loaded library
		//if the library has not been loaded this method will throw
		//an exception
	 	func = (GetInt)lib.getFunction( "getAnInteger" );
	
		int i = -1;
		if ( func ) {
			//invoke the function
			i = func( 23, 245.455 );
		}
		//print out some info
		System::print( "The value of i: %d, from calling func @ %p\n", i, func );

		//unload the library. You can specify for the library to unload automatically
		//in the constructor of the Library if you want	
		lib.unload();
  }
	catch ( BasicException& e ) {
  	System::print( e.getMessage() + "\n" );
	}
	//clean up the FoundationKit by telling it to terminate		
	FoundationKit::terminate();
	return 0;
}



