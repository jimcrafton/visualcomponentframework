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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:48  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/12 03:13:29  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.2  2003/01/09 02:37:34  ddiego
*added the "&" operator for the method pointer to make GCC happy
*
*Revision 1.9.14.1  2003/01/08 00:20:02  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.8  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.7  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


