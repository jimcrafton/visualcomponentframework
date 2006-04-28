//SocketListeningLoop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/NetworkKit/NetworkKit.h"

using namespace VCF;
using namespace VCFNet;

SocketListeningLoop::SocketListeningLoop( Socket* socket )
{
	socket_ = socket;

	socketDataReceivedHandler_ =
		new SocketEventHandler<SocketListeningLoop>( this, &SocketListeningLoop::onDataReceived );

	socketClientConnectedHandler_ =
		new SocketEventHandler<SocketListeningLoop>( this, &SocketListeningLoop::onClientConnected );

	socketClientDisconnectedHandler_ =
		new SocketEventHandler<SocketListeningLoop>( this, &SocketListeningLoop::onClientDisconnected );


	if ( NULL != socket_ ) {
		socket_->DataReceived.addHandler( socketDataReceivedHandler_ );
		socket_->ClientConnected.addHandler( socketClientConnectedHandler_ );
		socket_->ClientDisconnected.addHandler( socketClientDisconnectedHandler_ );
	}
	socketIsServer_ = socket_->isServer();
	serverClientConnected_ = false;
}

SocketListeningLoop::~SocketListeningLoop()
{
	this->canContinue_ = false;
	if ( NULL != socket_ ) {
		socket_->DataReceived.removeHandler( socketDataReceivedHandler_ );
		socket_->ClientConnected.removeHandler( socketClientConnectedHandler_ );
		socket_->ClientDisconnected.removeHandler( socketClientDisconnectedHandler_ );
	}

	delete socketDataReceivedHandler_;
	socketDataReceivedHandler_ = NULL;

	delete socketClientConnectedHandler_;
	socketClientConnectedHandler_ = NULL;

	delete socketClientDisconnectedHandler_;
	socketClientDisconnectedHandler_ = NULL;
}

bool SocketListeningLoop::run()
{
	bool result = (NULL != this->socket_);
	if ( false == result ) {
		return false;
	}
	//printf( "running SocketListeningLoop::run for socket@%x\n",socket_ );
	//printf( "\twaiting a sec...\n" );

	if ( true == socketIsServer_ ) {
		//continue to listen for incoming data packets from already connected clients

		while ( (true == this->canContinue()) && (false == socket_->hasWaitingClients()) ) {
			//printf( "\tno clients yet...\n" );
			socket_->checkForPendingData();
			sleep( 10 );
		}

		if ( true == this->canContinue() ) {
			//somebody connected ! since we broke to the while loop - go get the client SocketObject
			Socket* clientSocket = socket_->getClient();
			if ( NULL != clientSocket ) {
				SocketEvent event( socket_, clientSocket );
				socket_->ClientConnected.fireEvent( &event );
			}
		}

		socket_->checkForPendingData();
	}
	else {
		//check for a connection
		bool connection = socket_->hasWaitingClients();
		if ( (true == connection) && ( false == serverClientConnected_) ) {
			//first time connection
			serverClientConnected_ = true;
			Socket* clientSocket = socket_->getClient();
			if ( NULL != clientSocket ) {
				SocketEvent event( socket_, clientSocket );
				socket_->ClientConnected.fireEvent( &event );
			}
		}

		if ( true == serverClientConnected_ ) {
			socket_->checkForPendingData();
		}
	}
	sleep( 10 );
	return result;
}

void SocketListeningLoop::onDataReceived( SocketEvent* event )
{
	//printf( "SocketListeningLoop::onDataReceived, event =%p\n", event );
}

void SocketListeningLoop::onClientConnected( SocketEvent* event )
{
	//printf( "SocketListeningLoop::onClientConnected, event =%p\n", event );
}

void SocketListeningLoop::onClientDisconnected( SocketEvent* event )
{
	printf( "SocketListeningLoop::onClientDisconnected, event =%p\n", event );
}


/**
$Id$
*/
