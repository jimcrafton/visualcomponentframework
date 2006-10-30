//NetworkKit.cpp

#include "NetworkKit.h"
#include "NetworkToolkit.h"


using namespace VCF;



void NetworkKit::init( int argc, char** argv )
{
	NetworkToolkit::create();
}

void NetworkKit::terminate()
{
	NetworkToolkit::destroy();
}