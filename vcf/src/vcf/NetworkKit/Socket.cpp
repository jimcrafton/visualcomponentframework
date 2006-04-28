//Socket.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Socket.cpp:

#include "vcf/NetworkKit/NetworkKit.h"

using namespace VCFNet;
using namespace VCF;

Socket::Socket( const int& port, const bool& startAsServer )
{
	host_ = "localhost";
	port_ = port;
	isServer_ = startAsServer;
	init();
}

Socket::Socket( const String& host, const int& port, const bool& startAsServer )
{
	host_ = host;
	port_ = port;
	isServer_ = startAsServer;
	init();
}

Socket::Socket( const int& socketPeerID, const VCF::String& host, const int& port )
{
	host_ = host;
	port_ = port;
	isServer_ = false;
	socketPeer_ = NULL;
	listeningThread_ = NULL;

	NetToolkit* netKit = NetToolkit::getDefaultNetToolkit();
	socketPeer_ = netKit->createSocketPeer( this, socketPeerID, host_, port_ );
}

Socket::~Socket()
{
	if ( SOCKET_LISTENING == state_ ) {
		stopListening();
	}
	delete socketPeer_;
	socketPeer_ = NULL;
}

void Socket::init()
{
	state_ = SOCKET_CLOSED;
	socketPeer_ = NULL;
	listeningThread_ = NULL;
	NetToolkit* netKit = NetToolkit::getDefaultNetToolkit();
	socketPeer_ = netKit->createSocketPeer( this, host_, port_ );
}

void Socket::setPort( const int& port )
{
	port_ = port;
	socketPeer_->setPort( port_ );
}

void Socket::setHost( const String& host )
{
	host_ = host;
	socketPeer_->setHost( host );
}

int Socket::send( const char* bytes, const int& size )
{
	return socketPeer_->send( bytes, size );
}

SocketState Socket::startListening()
{
	state_ = socketPeer_->startListening();
	if ( SOCKET_LISTENING == state_ ) {
		// NK: Don't need this anymore
		//listeningThread_ = new SocketListeningLoop(this);
		if(listeningThread_ != NULL) {
			listeningThread_->start();
		}
	}
	return state_;
}

SocketState Socket::stopListening()
{
	if ( NULL != listeningThread_ ) {
		delete listeningThread_;
	}
	listeningThread_ = NULL;
	state_ = socketPeer_->stopListening();
	return state_;
}

String Socket::toString()
{
	return "Sockect State is \"" + SocketStateNames[(int)state_] + "\"";
}

bool Socket::hasWaitingClients()
{
	return socketPeer_->hasWaitingClients();
}

Socket* Socket::getClient()
{
	Socket* result = socketPeer_->getClient();
	return result;
}

void Socket::checkForPendingData( const int& waitAndBlock )
{
	socketPeer_->checkForPendingData( waitAndBlock );
}

// NK: see explantion in Socket.h
void Socket::setListeningLoop(SocketListeningLoop *sloop) {
	if(listeningThread_ == NULL) {
		listeningThread_ = sloop;
	}
}


/**
$Id$
*/
