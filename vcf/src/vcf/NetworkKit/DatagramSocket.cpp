//DatagramSocket.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Provides constructors and relegate "real" implementation to
// DatagramSocketPeer.
// -- Ning Ke

#ifdef WIN32 //this is a hack - this will be removed when we redo sockets
			 //and add this to teh toolkit
	#include <winsock2.h>
#endif

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkKitPrivate.h"

using namespace VCF;
using namespace VCFNet;

// Used to initialize (UDP) client socket.
DatagramSocket::DatagramSocket() {
	port_ = 0;
	host_ = "";
	peer_ = NULL;
#ifdef WIN32
	peer_ = new Win32DatagramSocketPeer(this);
#endif
}

// Used to initialize (UDP)Server socket.
DatagramSocket::DatagramSocket(const int &port) {
	port_ = port;
	host_ = "";
	peer_ = NULL;
#ifdef WIN32
	peer_ = new Win32DatagramSocketPeer(this, port);
#endif
}

// For (UDP)server socket
DatagramSocket::DatagramSocket(const String &host, const int &port) {
	host_ = host;
	port_ = port;
	peer_ = NULL;
#ifdef WIN32
	peer_ = new Win32DatagramSocketPeer(this, host, port);
#endif
}

DatagramSocket::~DatagramSocket() {
	delete peer_;
	peer_ = NULL;
}

int DatagramSocket::setRemoteHost(const String &remoteHostName, const int &remoteHostPort) {
	return peer_->setRemoteHost(remoteHostName, remoteHostPort);
}

String DatagramSocket::getLocalHostName() {
	return host_;

}

int DatagramSocket::getLocalHostPort() {
	return port_;
}


String DatagramSocket::getRemoteHostName() {
	return peer_->getRemoteHostName();
}

int DatagramSocket::getRemoteHostPort() {
	return peer_->getRemoteHostPort();
}

bool DatagramSocket::isInitialized(String &hostName) {
	if(hostName == "") {
		return false;
	} else {
		return true;
	}
}

bool DatagramSocket::isInitialized(int &portNum) {
	if(portNum == 0) {
		return false;
	} else {
		return true;
	}
}

int DatagramSocket::send(const char *buf, const int &size) {
	return peer_->send(buf, size);
}

int DatagramSocket::recv(char *buf, int &size) {
	return peer_->recv(buf, size);
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


