//SimpleDLL.cpp
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



}


