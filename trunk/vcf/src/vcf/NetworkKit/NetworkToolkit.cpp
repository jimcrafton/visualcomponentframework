//NetworkToolkit.cpp
#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkToolkit.h"

#ifdef WIN32
#include "vcf/NetworkKit/Win32NetworkToolkit.h"
#endif 



using namespace VCF;


NetworkToolkit* NetworkToolkit::Instance = NULL;


void NetworkToolkit::create()
{
	NetworkToolkit::Instance = NULL;

#ifdef WIN32
	NetworkToolkit::Instance = new Win32NetworkToolkit();
#endif


	VCF_ASSERT( NULL != NetworkToolkit::Instance );
}


void NetworkToolkit::destroy()
{
	delete NetworkToolkit::Instance;
	NetworkToolkit::Instance = NULL;
}

SocketPeer*	NetworkToolkit::createSocketPeer() 
{
	return NetworkToolkit::Instance->internal_createSocketPeer();
}

IPAddressPeer* NetworkToolkit::createIPAddressPeer()
{
	return NetworkToolkit::Instance->internal_createIPAddressPeer();
}

int NetworkToolkit::getLastError()
{
	if ( NULL == NetworkToolkit::Instance ) {
		return -1;
	}

	return NetworkToolkit::Instance->internal_getLastError();
}
