//InternetToolkit.cpp

#include "vcf/InternetKit/InternetKit.h"

#ifdef WIN32
#include "vcf/InternetKit/Win32InternetToolkit.h"
#endif


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



using namespace VCF;


InternetToolkit* InternetToolkit::inetKitInstance = NULL;

void InternetToolkit::create()
{
	InternetToolkit::inetKitInstance = NULL;

#ifdef WIN32
	InternetToolkit::inetKitInstance = new Win32InternetToolkit();
#endif
}

void InternetToolkit::terminate()
{
	delete InternetToolkit::inetKitInstance;
}