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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:39  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.6.1  2006/03/19 00:03:40  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3  2004/08/07 02:47:33  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.4  2004/04/29 03:40:55  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


