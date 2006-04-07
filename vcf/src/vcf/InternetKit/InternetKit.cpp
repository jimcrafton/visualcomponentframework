//InternetKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/InternetKit/InternetKit.h"
#include "vcf/InternetKit/InternetToolkit.h"


using namespace VCF;

void InternetKit::init( int argc, char** argv )
{
	InternetToolkit::create();
}


void InternetKit::terminate()
{
	InternetToolkit::terminate();
}