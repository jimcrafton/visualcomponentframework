//SimpleDLL.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include <cstdio>
#include <cwchar>
#include <typeinfo>
#include "SimpleDLL.h"



void HelloWorld::hello()
{
	wprintf( L"Hello from class: %s, instance @ %p\n", typeid(*this).name(), this );
}

extern "C" {

int getAnInteger( int val1, double d )
{
 	int result = (int) (val1 * 234 / d);
	return result;
}




SIMPLEDLL_API void _vpl_init ( void* handle ) 
{
	wprintf( L"Lib initialized! Handle: %p\n", handle );
}

SIMPLEDLL_API void _vpl_terminate ( void* handle ) 
{
	wprintf( L"Lib terminated! Handle: %p\n", handle );
}



}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.3  2006/03/19 00:03:40  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.5.2.2  2005/09/03 17:13:23  ddiego
*added a new argument to _vpl_init and _vpl_terminate functions.
*
*Revision 1.5.2.1  2005/07/23 21:45:41  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.4.2.2  2005/04/17 17:19:10  iamfraggle
*Small fixes
*
*Revision 1.4.2.1  2005/04/17 15:11:47  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
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


