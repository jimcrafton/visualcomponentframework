//NetworkToolkit.cpp
#include "NetworkKit.h"
#include "NetworkToolkit.h"

#ifdef WIN32
#include "Win32NetworkToolkit.h"
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
}

SocketPeer*	NetworkToolkit::createSocketPeer() 
{
	return NetworkToolkit::Instance->internal_createSocketPeer();
}

IPAddressPeer* NetworkToolkit::createIPAddressPeer()
{
	return NetworkToolkit::Instance->internal_createIPAddressPeer();
}
