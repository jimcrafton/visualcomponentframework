////Processes.cpp

#include "FoundationKit.h"

/**
A brief example demonstrating how the Process class works
*/
using namespace VCF;



/**
This will demonstrate how to create a process
*/
void example1()
{
	//create a process object
	Process p1;

	//create a process

	p1.createProcess( "XCOPY", "/?" );	
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();
	

	FoundationKit::terminate();
	return 0;
}


