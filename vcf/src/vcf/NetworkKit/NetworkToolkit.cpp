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

SocketPeer*	NetworkToolkit::createSocketPeer( int socketType ) 
{
	return NetworkToolkit::Instance->internal_createSocketPeer(socketType);
}

IPAddressPeer* NetworkToolkit::createIPAddressPeer()
{
	return NetworkToolkit::Instance->internal_createIPAddressPeer();
}

String NetworkToolkit::getErrorString( int errCode )
{
	String result;
	static std::map<int,String> errorCodeMap;
	if ( errorCodeMap.empty() ) {
		errorCodeMap[neInProgress] = "In Progress";
		errorCodeMap[neAlreadyInprogress] = "Already In Progress";
		errorCodeMap[neNotSocket] = "Not a socket";
		errorCodeMap[neDestAddrRequested] = "Dest Address Requested";
		errorCodeMap[neMsgTooLong] = "Message Too Long";
		errorCodeMap[neWrongProtocol] = "Wrontg Protocol";
		errorCodeMap[neBadProtocolOpt] = "Bad Protocol Options";
		errorCodeMap[neProtocolNotSupp] = "Protocol Not supported";
		errorCodeMap[neSockTypeNotSupp] = "Socket Type Not supported";
		errorCodeMap[neOperationNotSupp] = "Operation Not supported";
		errorCodeMap[neProtoFamilyNotSupp] = "Proto family Not supported";
		errorCodeMap[neAddrFamilyNotSupp] = "Address family Not supported";
		errorCodeMap[neAddrInUse] = "Address in use";
		errorCodeMap[neAddrNotAvailable] = "Address not available";
		errorCodeMap[neNetworkDown] = "Network down";
		errorCodeMap[neNetworkUnreachable] = "Network unreachable";
		errorCodeMap[neNetworkReset] = "Network reset";
		errorCodeMap[neConnectionAborted] = "Connection aborted";
		errorCodeMap[neConnectionReset] = "Connection reset";
		errorCodeMap[neNoBufferSpaceAvail] = "No buffer Space available";
		errorCodeMap[neSockAlreadyConnected] = "Socket already connected";
		errorCodeMap[neSockNotConnected] = "Socket not connected";
		errorCodeMap[neSockShutdown] = "Socket shutdown";
		errorCodeMap[neConnectionTimedOut] = "Connection timed out";
		errorCodeMap[neConectionRefused] = "Connection refused";
		errorCodeMap[neTooManySymLinks] = "Too many sym links";
		errorCodeMap[neNameTooLong] = "Name too long";
		errorCodeMap[neHostDown] = "Host is down";
		errorCodeMap[neHostUnreachable] = "Host unreachable";
		errorCodeMap[neTooManyProcesses] = "Too many processes";
	}

	result = errorCodeMap[errCode];

	return result;
}

int NetworkToolkit::getLastError()
{
	if ( NULL == NetworkToolkit::Instance ) {
		return -1;
	}

	return NetworkToolkit::Instance->internal_getLastError();
}
