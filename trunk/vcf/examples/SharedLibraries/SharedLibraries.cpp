//SharedLibraries.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

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
		try {
			func = (GetInt)lib.getFunction( "getAnInteger" );
		}
		catch ( BasicException& e ) {
			System::print( e.getMessage() );
		}
		
		int i = -1;
		if ( func ) {
			//invoke the function
			i = func( 23, 245.455 );
		}
		//print out some info
		System::print( Format("The value of i: %d, from calling func @ %p\n") % i % func );
		
		//unload the library. You can specify for the library to unload automatically
		//in the constructor of the Library if you want
		lib.unload();
	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}
	//clean up the FoundationKit by telling it to terminate
	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:43  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.1  2005/04/17 15:11:47  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.4  2004/12/01 04:15:12  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.1  2004/09/15 04:41:23  ddiego
*made some minor changes to the SharedLibraries example, and the init and term code of the Library class.
*
*Revision 1.3  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


