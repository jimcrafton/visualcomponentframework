//InternetToolkit.cpp

#include "vcf/InternetKit/InternetKit.h"

#ifdef VCF_WIN
#include "vcf/InternetKit/Win32InternetToolkit.h"
#endif

#include "vcf/FoundationKit/ThreadPool.h"


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

#ifdef VCF_WIN
	InternetToolkit::inetKitInstance = new Win32InternetToolkit();
#endif
}

void InternetToolkit::terminate()
{
	
	delete InternetToolkit::inetKitInstance;
}


void InternetToolkit::getDataFromURL( URL* url, OutputStream* stream )
{
	InternetToolkit::inetKitInstance->internal_getDataFromURL( url, stream );
}

void asyncGetDataFromURL(AsyncURL* url)
{
	InternetToolkit::getDataFromURL( url, url->getOutputStream() );
	url->finished();
}

void InternetToolkit::getDataFromURL( AsyncURL* url )
{
	ThreadedProcedure1<AsyncURL*>(url, asyncGetDataFromURL ).invoke();
}
/**
$Id$
*/
