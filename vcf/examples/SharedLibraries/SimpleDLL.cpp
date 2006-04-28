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
$Id$
*/
