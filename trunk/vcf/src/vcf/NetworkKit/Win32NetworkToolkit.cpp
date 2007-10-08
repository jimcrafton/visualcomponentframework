//Win32NetworkToolkit.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkToolkit.h"
#include "vcf/NetworkKit/Socket.h"

#include "vcf/NetworkKit/Win32NetworkToolkit.h"
#include "vcf/NetworkKit/Win32SocketPeer.h"
#include "vcf/NetworkKit/Win32IPAddressPeer.h"



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

SocketPeer* Win32NetworkToolkit::internal_createSocketPeer( int socketType )
{
	SocketPeer* result = NULL;
	
	switch ( socketType ) {
		case Socket::stStream : {
			result = new Win32SocketPeer();
		}
		break;

		case Socket::stDatagram : {
			result = new Win32UDPSocketPeer();
		}
		break;
	}	

	return result;
}

IPAddressPeer* Win32NetworkToolkit::internal_createIPAddressPeer()
{
	return new Win32IPAddressPeer();
}

int Win32NetworkToolkit::internal_getLastError()
{
	int result = 0;


	int err = WSAGetLastError();

	switch (err) {
		case WSAEINPROGRESS :{ 
			result = neInProgress; 
		} break;
		case WSAEALREADY :{ 
			result = neAlreadyInprogress; 
		} break;
		case WSAENOTSOCK :{ 
			result = neNotSocket; 
		} break;
		case WSAEDESTADDRREQ :{ 
			result = neDestAddrRequested; 
		} break;
		case WSAEMSGSIZE    :{ 
			result = neMsgTooLong; 
		} break;
		case WSAEPROTOTYPE  :{ 
			result = neWrongProtocol; 
		} break;
		case WSAENOPROTOOPT :{ 
			result = neBadProtocolOpt; 
		} break;
		case WSAEPROTONOSUPPORT  :{ 
			result = neProtocolNotSupp; 
		} break;
		case WSAESOCKTNOSUPPORT  :{ 
			result = neSockTypeNotSupp; 
		} break;
		case WSAEOPNOTSUPP    :{ 
			result = neOperationNotSupp; 
		} break;   
		case WSAEPFNOSUPPORT  :{ 
			result = neProtoFamilyNotSupp; 
		} break;   
		case WSAEAFNOSUPPORT  :{ 
			result = neAddrFamilyNotSupp; 
		} break;   
		case WSAEADDRINUSE    :{ 
			result = neAddrInUse; 
		} break;   
		case WSAEADDRNOTAVAIL    :{ 
			result = neAddrNotAvailable; 
		} break;
		case WSAENETDOWN      :{ 
			result = neNetworkDown; 
		} break;   
		case WSAENETUNREACH   :{ 
			result = neNetworkUnreachable; 
		} break;   
		case WSAENETRESET     :{ 
			result = neNetworkReset; 
		} break;   
		case WSAECONNABORTED  :{ 
			result = neConnectionAborted; 
		} break;
		case WSAECONNRESET    :{ 
			result = neConnectionReset; 
		} break;
		case WSAENOBUFS       :{ 
			result = neNoBufferSpaceAvail; 
		} break;
		case WSAEISCONN       :{ 
			result = neSockAlreadyConnected; 
		} break;
		case WSAENOTCONN      :{ 
			result = neSockNotConnected; 
		} break;
		case WSAESHUTDOWN     :{ 
			result = neSockShutdown; 
		} break;
		case WSAETIMEDOUT     :{ 
			result = neConnectionTimedOut; 
		} break;
		case WSAECONNREFUSED  :{ 
			result = neConectionRefused; 
		} break;
		case WSAELOOP         :{ 
			result = neTooManySymLinks; 
		} break;
		case WSAENAMETOOLONG  :{ 
			result = neNameTooLong; 
		} break;
		case WSAEHOSTDOWN     :{ 
			result = neHostDown; 
		} break;
		case WSAEHOSTUNREACH  :{ 
			result = neHostUnreachable; 
		} break;
		case WSAEPROCLIM      :{ 
			result = neTooManyProcesses; 
		} break;		
	}


	return result;
}
