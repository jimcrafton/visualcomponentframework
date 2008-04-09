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


InternetToolkit::~InternetToolkit()
{
	std::map<String,ProtocolHandler*>::iterator it = protocolHandlers_.begin();
	while ( it != protocolHandlers_.end() ) {
		delete it->second;
		++ it;
	}
}


void InternetToolkit::getDataFromURL( URL* url, OutputStream* stream )
{	
	ProtocolHandler* handler = InternetToolkit::getProtocolHandler( url->getScheme() );
	if ( NULL != handler )  {
		handler->getDataFromURL( url, stream );
	}
	else {
		InternetToolkit::inetKitInstance->internal_getDataFromURL( url, stream );
	}
}

void asyncGetDataFromURL(AsyncURL* url)
{
	try {
		InternetToolkit::getDataFromURL( url, url->getOutputStream() );
	}
	catch (BasicException& e) {
		StringUtils::trace( Format("Error with getDataFromURL(). Exception: %s\n") % e.getMessage() );
	}
	url->finished();

	if ( url->shouldAutoDelete() ) {
		delete url;
	}
}

void InternetToolkit::getDataFromURL( AsyncURL* url )
{
	ThreadedProcedure1<AsyncURL*>(url, asyncGetDataFromURL ).invoke();
}


void InternetToolkit::addProtocolHandler( ProtocolHandler* handler )
{
	InternetToolkit::inetKitInstance->protocolHandlers_[ handler->getProtocolName() ] = handler;
}

void InternetToolkit::removeProtocolHandler( ProtocolHandler* handler )
{
	std::map<String,ProtocolHandler*>::iterator found = 
		InternetToolkit::inetKitInstance->protocolHandlers_.find( handler->getProtocolName() );

	if ( found != InternetToolkit::inetKitInstance->protocolHandlers_.end() ) {
		InternetToolkit::inetKitInstance->protocolHandlers_.erase( found );
	}
}

ProtocolHandler* InternetToolkit::getProtocolHandler( const String& name )
{
	ProtocolHandler* result = NULL;

	std::map<String,ProtocolHandler*>::iterator found = 
		InternetToolkit::inetKitInstance->protocolHandlers_.find( name );

	if ( found != InternetToolkit::inetKitInstance->protocolHandlers_.end() ) {
		result = found->second;
	}

	return result;
}







/**
$Id$
*/
