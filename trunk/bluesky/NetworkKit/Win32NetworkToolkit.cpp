//Win32NetworkToolkit.cpp

#include "NetworkKit.h"
#include "NetworkToolkit.h"
#include "Socket.h"

#include "Win32NetworkToolkit.h"
#include "Win32SocketPeer.h"
#include "Win32IPAddressPeer.h"



using namespace VCF;



Win32NetworkToolkit::Win32NetworkToolkit()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData; 
	int startedOk = WSAStartup(wVersionRequested, &wsaData); 
	if (startedOk != 0) {		
		//throw exception
		WSACleanup();
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 || 
		HIBYTE( wsaData.wVersion ) != 1 ) 	{ 
		WSACleanup();
		startedOk = -1;
	}
	
	if (0 != startedOk) {
		throw NetworkException( MAKE_ERROR_MSG_2("WSAStartup failed to initialize!") );
	}
}

Win32NetworkToolkit::~Win32NetworkToolkit()
{
	WSACleanup();
}

SocketPeer* Win32NetworkToolkit::internal_createSocketPeer()
{
	SocketPeer* result = new Win32SocketPeer();

	return result;
}

IPAddressPeer* Win32NetworkToolkit::internal_createIPAddressPeer()
{
	return new Win32IPAddressPeer();
}

