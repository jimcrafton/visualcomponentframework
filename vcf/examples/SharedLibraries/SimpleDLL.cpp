//SimpleDLL.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include <stdio.h>
#include "../examples/SharedLibraries/SimpleDLL.h"
#include <typeinfo>



void HelloWorld::hello()
{
	printf( "Hello from class: %s, instance @ %p\n", typeid(*this).name(), this );
}

extern "C" {

int getAnInteger( int val1, double d )
{
 	int result = (int) (val1 * 234 / d);
	return result;
}



}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:36  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


