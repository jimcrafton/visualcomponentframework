//Processes.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

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

#if defined(VCF_WIN32)
	p1.createProcess( "XCOPY", "/?" );
#elif defined(VCF_POSIX)
	p1.createProcess( "ls", "--help" );
#endif

}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();


	FoundationKit::terminate();
	return 0;
}


/**
$Id$
*/
