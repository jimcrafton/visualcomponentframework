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
*Revision 1.9.14.1  2003/01/08 00:20:02  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.8.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.8  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.7  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


