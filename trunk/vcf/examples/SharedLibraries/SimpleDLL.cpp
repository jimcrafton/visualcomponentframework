//SimpleDLL.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include <stdio.h>
#include "SimpleDLL.h"
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

#ifdef __BORLANDC__
void vpl_init (void) {}

void vpl_terminate (void) {}
#endif

}


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/12/01 04:15:12  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.3  2004/10/16 16:18:03  kiklop74
*Updated SharedLibraries sample for compilation with BCB 5/6 with IDE projects
*
*Revision 1.3.2.2  2004/10/07 15:03:34  kiklop74
*Fixed building issues with bcb
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


