//Win32SocketPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include <winsock2.h> //makes sure to link with Ws2_32.lib
#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkKitPrivate.h"

using namespace VCF;
using namespace VCFNet;

bool Win32SocketPeer::WinSockStarted = false;

struct MemStruct{
	int size;
	char* data;
};

Win32SocketPeer::Win32SocketPeer( Socket* socket, const String& host, const int& port )	{
	socket_ = socket;
	host_ = host;
	port_ = port;
	sock_ = 0;
	memset( &sin_, 0, sizeof(sin_) );
	if ( false == Win32SocketPeer::WinSockStarted ) {
		Win32SocketPeer::startup();
	}
}

Win32SocketPeer::Win32SocketPeer( Socket* socket, const int& socketPeerID, const VCF::String& host, const int& port )
{
	socket_ = socket;
	host_ = host;
	port_ = port;
	sock_ = socketPeerID;
	memset( &sin_, 0, sizeof(sin_) );
	if ( false == Win32SocketPeer::WinSockStarted ) {
		Win32SocketPeer::startup();
	}
}

Win32SocketPeer::~Win32SocketPeer(){

	std::vector<Socket*>::iterator it = connectedClients_.begin();
	while ( it != connectedClients_.end() ) {
		Socket* so = *it;
		printf( "deleting %x\n", so );
		delete so;
		it++;
	}

	if ( 0 != sock_ ) {
		closesocket(sock_);
		sock_ = 0;
	}
	connectedClients_.clear();
	disconnectedClients_.clear();
	socket_ = NULL;
}

SocketState Win32SocketPeer::stopListening(){
	SocketState result = SOCKET_CONNECT_ERROR;

	return result;
}

SocketState Win32SocketPeer::startListening(){

	if ( SOCKET_CLOSED != this->socket_->getState() ){
		return SOCKET_ALREADY_LISTENING_ERROR;
	}
	//printf("starting to listen for incoming sockets...\n");
	int length = 0;
	int msgsock = 0;

	/**
	*we want to create a socket in two different
	*ways depending on how the Socket::isServer_ is set
	*if true then bind and listen
	*otherwise connect ?
	*/

    //Create a socket if neccessary
	if ( sock_ <= 0  ) {
		sock_ = ::socket(AF_INET,SOCK_STREAM,0);
		if (sock_ < 0) {
			sock_ = 0;
			return SOCKET_CANT_OPEN_SOCKET;
		}
	}

	if ( true == this->socket_->isServer() )  {
		// Initialize the socket's address structure
		sin_.sin_family = AF_INET;
		sin_.sin_addr.s_addr = INADDR_ANY;
		sin_.sin_port = htons((short)port_);

		// Assign an address to this socket
		int bindErr =  bind( sock_, (sockaddr*)&sin_, sizeof(sin_) );
		if ( bindErr < 0)  {
			closesocket( sock_ );
			sock_ = 0;
			return SOCKET_BIND_FAILED;
		}

		//Prepare the socket queue for connection requests
		int listenErr = listen( sock_, 5 );

	}
	else {
		SocketState state = connectTo( this->host_, this->port_ );
		socket_->setState( state );
	}

	return SOCKET_LISTENING;
}

int Win32SocketPeer::send( const char* bytes, const int& size ){
	int result = 0;
	if ( SOCKET_CLOSED == this->socket_->getState() ){
		//connect
		SocketState state = connectTo( this->host_, this->port_ );
		socket_->setState( state );
	}
	result = ::send( sock_, bytes, size, 0 );
	if ( -1 == result ) {
		int i = WSAGetLastError();
	}
	return result;
}

void Win32SocketPeer::startup()	{
	if ( true == Win32SocketPeer::WinSockStarted ) {
		return;
	}

	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//throw exception
		WSACleanup();
		//throw SocketException( "Winsock dll load failed." );
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) 	{
		WSACleanup();
		//throw SocketException( "Winsock version 1.1 not found." );
	}

	Win32SocketPeer::WinSockStarted = true;
}

SocketState Win32SocketPeer::connectTo( const String& hostName, const int& port ){
	SocketState result = SOCKET_CONNECT_ERROR;

	host_ = hostName;
	const char* tmpHostName = hostName.ansi_c_str();
    struct hostent *hp;
	if ( 0 != sock_ ){ //attempt to close the previous connection
		closesocket( sock_ );
		sock_ = 0;
	}

    port_ = port;

	sock_ = socket (AF_INET, SOCK_STREAM, 0);
    if ( sock_ < 0 ) {
		return SOCKET_CANT_OPEN_SOCKET;
    }

    // Initialize the socket address to the server's address.
	memset( &sin_, 0, sizeof(sin_) );
    sin_.sin_family = AF_INET;

    hp = gethostbyname( tmpHostName );    //to get host address

	if (hp == NULL) {
		return SOCKET_CANT_OPEN_SOCKET;
    }

	memcpy( &(sin_.sin_addr.s_addr), hp->h_addr, hp->h_length );
    sin_.sin_port = htons((short)port_);

    // Connect to the server.
	int connectErr = connect(sock_, (sockaddr*)&sin_,sizeof(sin_));
    if ( connectErr < 0) {
		int i = WSAGetLastError();
		closesocket(sock_);
		return SOCKET_CONNECT_ERROR;
    }

	return SOCKET_CONNECTED;
}

void Win32SocketPeer::setPort( const int& port )
{
	this->port_ = port;
	this->socket_->setState( SOCKET_CLOSED );
	if ( 0 != sock_ ){ //attempt to close the previous connection
		closesocket( sock_ );
		sock_ = 0;
	}
}

int Win32SocketPeer::getPort()
{
	return port_;
}

void Win32SocketPeer::setHost( const String& host )
{
	host_ = host;
	this->socket_->setState( SOCKET_CLOSED );
	if ( 0 != sock_ ){ //attempt to close the previous connection
		closesocket( sock_ );
		sock_ = 0;
	}
}

String Win32SocketPeer::getHost()
{
	return host_;
}

bool Win32SocketPeer::hasWaitingClients()
{
	bool result = false;

	struct timeval timeout ;
	fd_set fd ;

	FD_ZERO(&fd);

	FD_SET ( sock_, &fd) ;
	timeout.tv_sec = 0 ;
	timeout.tv_usec = 0 ;

	int selectResult = SOCKET_ERROR;
	if ( this->socket_->isServer() ) {
		selectResult = select( sock_ + 1, &fd, NULL, NULL, &timeout );
	}
	else {
		selectResult = select( sock_ + 1, NULL, &fd, NULL, &timeout );
	}
	if ( SOCKET_ERROR == selectResult ){
		//throw exception
	}

	result = ( selectResult > 0 );

	if ( result )  {
		int i = 8;
		i++;
	}


	return result;
}

Socket* Win32SocketPeer::getClient()
{
	Socket* result = NULL;
	if ( true == this->socket_->isServer() ) {
		int length = 0;
		int msgsock = 0;
		//Initialize the socket's address structure

		sin_.sin_family = AF_INET;
		sin_.sin_addr.s_addr = INADDR_ANY;
		sin_.sin_port = htons((short)port_);

		//StringUtils::trace("Listening for connect requests on port " + StringUtils::toString(port_) + "\n" );
		//printf( "Listening for connect requests on port %d\n", port_ );
		//Prepare the socket queue for connection requests

		length = sizeof(sin_);
		msgsock = accept( sock_, (sockaddr*)&sin_, &length );

		if (msgsock != SOCKET_ERROR) {
			result = new Socket( msgsock, host_, port_ );
			this->connectedClients_.push_back( result );
		}
		else {
			//StringUtils::trace("Accept() failed on sock_ = " + StringUtils::toString((int)sock_) + "\n" );
			//printf("Accept() failed on sock_ = %d\n", sock_ );
		}

		//StringUtils::trace("Connection from host " + host_ + " port: " + StringUtils::toString(port_) + "\n" );
		//printf("Connection from host %s port: %d\n", host_.c_str(), port_ );
	}

	else {
		if ( true == connectedClients_.empty() ) {
			result = new Socket(sock_, host_, port_ );
			this->connectedClients_.push_back( result );
		}
	}
	return result;
}

void Win32SocketPeer::readDataFromClient( Socket* client, fd_set* readfd )
{
	if ( NULL == client ) {
		return;
	}

	int clientSock = client->getSocketPeer()->getSocketPeerID();
	if (FD_ISSET (clientSock, readfd)) {
		//StringUtils::trace( StringUtils::toString(*it) +  " sent data...\n" );
		//printf( "%d sent data...\n", client->socketID_ );
		// this guy sent something

		char buf[VCFNET_MAX_SOCKET_SIZE];
		char* totalDataBuf = NULL;
		int totalSize = VCFNET_MAX_SOCKET_SIZE;
		std::vector<MemStruct*> dataList;
		memset( buf, 0 , VCFNET_MAX_SOCKET_SIZE );

		//read first chunk of data
		int recvResult = recv( clientSock, buf, VCFNET_MAX_SOCKET_SIZE, 0 );

		switch ( recvResult ) {
			case 0 : {
				//printf( "client closed connection - fire event\n" );
				//client closed connection - fire event
				SocketEvent event( socket_, client );
				this->socket_->ClientDisconnected.fireEvent( &event );
				disconnectedClients_.push_back( client );
			}
			break;

			case SOCKET_ERROR : {
				//socket error throw exception ????
				if ( false == this->socket_->isServer() ) {
					//possible problem - perhaps the server
					int err = WSAGetLastError();
					switch ( err ) {
						case WSAECONNRESET : {
							SocketEvent event( socket_, client );
							this->socket_->ClientDisconnected.fireEvent( &event );
							disconnectedClients_.push_back( client );
						}
						break;
					}
				}
			}
			break;

			default : {
				// NK: First add data received so far into dataList.
				MemStruct* memStruct = new MemStruct;
				memStruct->data = new char[recvResult];
				memset( memStruct->data, 0, recvResult );
				memStruct->size = recvResult;
				memcpy(memStruct->data, buf, recvResult );
				dataList.push_back( memStruct );
				totalSize = recvResult;

				//check to see if more data is still out there
				u_long res = 0;
				ioctlsocket( clientSock, FIONREAD, &res );
				char* tmp = NULL;
				if ( res > 0 ){
					while ( res > 0 ){ //continue to pull data
						MemStruct* memStruct = new MemStruct;
						memStruct->data = new char[res];
						memset( memStruct->data, 0, res );
						memStruct->size = res;
						recvResult = recv( clientSock, memStruct->data, res, 0 );
						if ( recvResult != SOCKET_ERROR ){
							dataList.push_back( memStruct );
							totalSize += res;
							ioctlsocket( clientSock, FIONREAD, &res );
						}
						else {
							res = 0;
						}
					}
				}

				if ( ! dataList.empty() ){
					totalDataBuf = new char[totalSize];
					memset( totalDataBuf, 0, totalSize );
					char* tmpBuf = totalDataBuf;
					int insertData = 0;
					std::vector<MemStruct*>::iterator dataIt = dataList.begin();
					while ( dataIt != dataList.end() ){
						MemStruct* memStruct = (*dataIt);
						tmp = memStruct->data;
						memcpy( tmpBuf, tmp, memStruct->size );
						tmpBuf += memStruct->size;
						delete [] memStruct->data;
						memStruct->data = NULL;
						delete memStruct;
						memStruct = NULL;
						dataIt++;
					}
				}
				else {
					totalDataBuf = buf;
				}

				//finished reading - fire event
				SocketEvent event( socket_, client, totalDataBuf, totalSize );
				this->socket_->DataReceived.fireEvent( &event );
			}
			break;
		}
	}
}

void Win32SocketPeer::checkForPendingData( const int& waitAndBlock )
{
	//printf(  "Starting checkForPendingData()...\n" );

	if ( !connectedClients_.empty() ){
		//StringUtils::trace( "checkForPendingData() has clients - looping...\n" );
		//printf( "checkForPendingData() has clients - looping...\n" );
		std::vector<Socket*>::iterator it = connectedClients_.begin();

		fd_set readfd;
		FD_ZERO(&readfd);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;

		int maxSock = 0;
		while ( it != connectedClients_.end() ){
			Socket* so = *it;
			int sockID = so->getSocketPeer()->getSocketPeerID();
			FD_SET ( sockID, &readfd) ;
			if ( sockID > maxSock ){
				maxSock = sockID;
			}
			it++;
		}
		//printf( "maxSock = %d\n", maxSock );
		struct timeval* timeoutVal = NULL;
		if ( (VCFNET_ASYNCHRONOUSWAIT == waitAndBlock) ) {
			timeoutVal = &timeout;
		}
		else if ( waitAndBlock > 0 ) {
			timeout.tv_sec = waitAndBlock / 1000; //waitAndBlock is in milliseconds
			timeoutVal = &timeout;
		}
		int i = select( maxSock + 1, &readfd, NULL, NULL, timeoutVal);

		//printf( "select( %d, ... ), returned %d\n", maxSock + 1, i );

		if ( (SOCKET_ERROR != i) && ( i > 0 ) ){ //no errors, and 1 or more sockets have data
			it = connectedClients_.begin();

			while ( it != connectedClients_.end() ){
				readDataFromClient( *it, &readfd );
				//printf( "readDataFromClient( so->socketID_=%d)\n", (*it)->socketID_ );
				it++;
			}

			it = this->disconnectedClients_.begin();
			while ( it != disconnectedClients_.end() ) {
				Socket* so = *it;
				std::vector<Socket*>::iterator found = std::find( connectedClients_.begin(), connectedClients_.end(), so );

				if ( found != connectedClients_.end() ) {
					connectedClients_.erase( found );
					delete so;
					so = NULL;
				}
				it++;
			}
			disconnectedClients_.clear();
		}
		else {
			//printf( "select() failed - returned %d\n\terror was : %s", i, getWSAErrorString( WSAGetLastError() ) );
		}
	}
	//printf(  "finished checkForPendingData()...\n" );
}

VCF::String Win32SocketPeer::getLocalMachineName()
{
	Win32SocketPeer::startup();
	VCF::String result = "";
	struct hostent *hp;
	hp = gethostbyname( "localhost" );
	if ( NULL != hp ) {
		result = hp->h_name;
	}

	return result;
}

int Win32SocketPeer::getSocketPeerID()
{
	return this->sock_;
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
*Revision 1.1.2.1  2004/04/28 03:45:49  ddiego
*migration towards new directory structure
*
*Revision 1.15.8.1  2004/04/26 16:43:34  ddiego
*checked in some minor fixes to some of the other
*libraries due to switch over to unicode
*
*Revision 1.15  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.1  2003/03/12 03:12:42  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.1  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.13  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.1  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.12  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.11  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


