//Win32DatagramSocketPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Implements DatagramSocket operations using the Win32 version of
// DGRAM socket. -- by Ning Ke

#include <winsock2.h>
#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkKitPrivate.h"


using namespace VCF;
using namespace VCFNet;

Win32DatagramSocketPeer::Win32DatagramSocketPeer(DatagramSocket *dgsock) {
	socket_ = dgsock;
	port_ = dgsock->getLocalHostPort();
	host_ = dgsock->getLocalHostName();
	sock_ = 0;
	startup();
}

Win32DatagramSocketPeer::Win32DatagramSocketPeer(DatagramSocket *dgsock, const int &port) {
	socket_ = dgsock;
	port_ = port;
	host_ = dgsock->getLocalHostName();
	sock_ = 0;
	startup();
}

Win32DatagramSocketPeer::Win32DatagramSocketPeer(DatagramSocket *dgsock, const String &host, const int &port) {
	socket_ = dgsock;
	host_ = host;
	port_ = port;
	sock_ = 0;
	startup();
}

Win32DatagramSocketPeer::~Win32DatagramSocketPeer() {
	if(sock_ != 0) {
		::closesocket(sock_);
	}
}

bool Win32DatagramSocketPeer::startup() {
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err = ::WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//throw exception
		::WSACleanup();
		//throw SocketException( "Winsock dll load failed." );
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) 	{
		::WSACleanup();
		//throw SocketException( "Winsock version 1.1 not found." );
	}

	// Create Datagram socket
	sock_ = ::socket(AF_INET, SOCK_DGRAM, 0);
    if ( sock_ < 0 ) {
		// throw exception
		return false;
    }

	// Bind the socket to port_ and host_ (if specified),
	// otherwise, bind to default local address and port.
	memset(&localHostAddr_, 0, sizeof(localHostAddr_));
    localHostAddr_.sin_family = AF_INET;
	if(!socket_->isInitialized(host_)) {
		localHostAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
		String tmpHost = host_;
		const char *nm = tmpHost.ansi_c_str();
		localHostAddr_.sin_addr.s_addr = htonl(::inet_addr(nm));
	}

	if(!socket_->isInitialized(port_)) {
		localHostAddr_.sin_port = htons(0);
	} else {
		localHostAddr_.sin_port = htons((short)port_);
	}

	if((::bind(sock_, (struct sockaddr *)&localHostAddr_, sizeof(localHostAddr_))) < 0) {
		return false;
	}

	return true;
}

// This sets the hisPort_, hisName_ and hisAddr_ to that of the
// address the socket is going to be connected to.
int Win32DatagramSocketPeer::setRemoteHost(const String &toHost, const int &toPort) {
	remoteHostPort_ = toPort;
	remoteHostName_ = toHost;

	memset( &remoteHostAddr_, 0, sizeof(remoteHostAddr_) );
	remoteHostAddr_.sin_family = AF_INET;

	struct hostent *hp;
	String tmphost = toHost;
	hp = ::gethostbyname(tmphost.ansi_c_str());	  //to get host address
	if (hp == NULL) {
		// throw exception
		return -1;
	}
	memcpy( &(remoteHostAddr_.sin_addr.s_addr), hp->h_addr, hp->h_length );
	remoteHostAddr_.sin_port = htons((short)remoteHostPort_);

	return 1;
}

int Win32DatagramSocketPeer::send(const char *buf, const int &size) {
	int res;

	res = ::sendto(sock_, buf, size, 0, (struct sockaddr*)&remoteHostAddr_, sizeof(remoteHostAddr_));
	return res;
}

// Receive from port_, after receiving, set remoteHostPort_, remoteHostAddr_ and
// remoteHostAddr_. (For future connect/send calls)
int Win32DatagramSocketPeer::recv(char *buf, int &size) {
	int res, len;
	struct sockaddr_in fromAddr;

	len = sizeof(fromAddr);
	res = ::recvfrom(sock_, buf, size, 0, (struct sockaddr*)&fromAddr, &len);
	// Now set remoteHostAddr_ to be fromAddr so as to allow user to get it.
	memset(&remoteHostAddr_, 0, sizeof(remoteHostAddr_));
	memcpy(&remoteHostAddr_, &fromAddr, sizeof(fromAddr));
	remoteHostPort_ = remoteHostAddr_.sin_port;
	remoteHostName_ = ::inet_ntoa(remoteHostAddr_.sin_addr);

	return res;
}

String Win32DatagramSocketPeer::getRemoteHostName() {
	return remoteHostName_;
}

int Win32DatagramSocketPeer::getRemoteHostPort() {
	return remoteHostPort_;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


