//Win32SocketPeer.cpp


#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/Win32SocketPeer.h"
#include "vcf/FoundationKit/Dictionary.h"

using namespace VCF;



Win32SocketPeer::Win32SocketPeer():
	handle_(NULL),
	socket_(NULL)
{
	memset( &sockAddr_, 0, sizeof(sockAddr_) );
}

Win32SocketPeer::Win32SocketPeer( SOCKET handle ):
	handle_(handle),
	socket_(NULL)
{
	VCF_ASSERT( NULL != handle_ );
	VCF_ASSERT( INVALID_SOCKET != handle_ );

	memset( &sockAddr_, 0, sizeof(sockAddr_) );

	int length = sizeof(sockAddr_);
	::getpeername( handle_, (sockaddr*)&sockAddr_, &length );
}

int Win32SocketPeer::create()
{
	VCF_ASSERT( NULL == handle_ );

	int result = -1;
/*
	int sockType = 0;
	switch ( type ) {
		case Socket::stStream : {
			sockType = SOCK_STREAM;
		}
		break;

		case Socket::stDatagram : {
			sockType = SOCK_DGRAM;
		}
		break;
	}
*/

	handle_ = ::socket( AF_INET, SOCK_STREAM, 0 );

	if ( INVALID_SOCKET == handle_ ) {
		handle_ = 0;
		result = -1;
	}
	else {
		BOOL val = TRUE;
		setsockopt( handle_, SOL_SOCKET, SO_DONTLINGER, (const char*)&val, sizeof(val) );
		result = 0;
	}

	return result;
}

int Win32SocketPeer::close()
{
	if ( NULL == handle_ ) {
		//do nothing, the handle doesn't need to be closed.
		return 0;
	}

	int result = -1;

	result = ::shutdown( handle_, SD_SEND | SD_RECEIVE );
	
	result = ::closesocket( handle_ );

	handle_ = NULL;

	return result;
}

int Win32SocketPeer::connect( const String& host, const unsigned short port )
{
	VCF_ASSERT( NULL != handle_ );

	int result = -1;


	switch ( socket_->getSocketType() ) {
		case Socket::stStream : {
			memset( &sockAddr_, 0, sizeof(sockAddr_) );
			sockAddr_.sin_family = AF_INET;
			struct hostent *hp = gethostbyname( host.ansi_c_str() );
			
			if ( NULL != hp ) {
				memcpy( &(sockAddr_.sin_addr.s_addr), hp->h_addr, hp->h_length );
				sockAddr_.sin_port = htons( port );
				
				result = ::connect( handle_, (sockaddr*)&sockAddr_ , sizeof(sockAddr_) );
				if ( -1 == result ) {
					int err =  WSAGetLastError();
					
					if ( WSAEWOULDBLOCK == err ) {
						result = 0;
					}
				}
			}
		}
		break;

		case Socket::stDatagram : {

		}
		break;
	}

	

	return result;
}

int Win32SocketPeer::listen( unsigned short port )
{
	VCF_ASSERT( NULL != handle_ );

	int result = -1;

	int val = 1;
	setsockopt( handle_, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val) );

	memset( &sockAddr_, 0, sizeof(sockAddr_) );


	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_addr.s_addr = INADDR_ANY;
	sockAddr_.sin_port = htons( port );

	result = ::bind( handle_, (sockaddr*)&sockAddr_, sizeof(sockAddr_) );

	if ( 0 == result ) {
		result = ::listen( handle_, SOMAXCONN );
	}

	return result;
}

SocketPeer* Win32SocketPeer::accept()
{
	Win32SocketPeer* result = NULL;

	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = sockAddr_.sin_port;

	int length = sizeof(addr);
	SOCKET acceptSocket = ::accept( handle_ , (sockaddr*)&addr, &length );

	if ( acceptSocket != INVALID_SOCKET ) {
		result = new Win32SocketPeer( acceptSocket );
	}


	return result;
}

int Win32SocketPeer::recv( unsigned char* bytes, size_t bytesLength )
{
	int result = -1;

	result = ::recv( handle_, (char*)bytes, bytesLength, 0 );

	if ( result < 0 ) {
		if ( !wouldOperationBlock() ) {
			socket_->internal_setErrorState( true );
		}
	}

	return result;
}

int Win32SocketPeer::send( const unsigned char* bytes, size_t bytesLength )
{
	int result = -1;

	result = ::send( handle_, (const char*)bytes, bytesLength, 0 );

	if ( result < 0 ) {
		if ( !wouldOperationBlock() ) {
			socket_->internal_setErrorState( true );
		}
	}

	return result;
}

OSHandleID Win32SocketPeer::getHandleID()
{
	return (OSHandleID) handle_;
}

String Win32SocketPeer::getHostName()
{
	String result;

	struct hostent *hp = gethostbyaddr( (const char*)&sockAddr_.sin_addr.S_un, sizeof(sockAddr_.sin_addr.S_un), 0 );
	if ( NULL != hp ) {
		result = hp->h_name;
	}
	else {
		int err = WSAGetLastError();
		printf( "err: %d\n", err );
	}


	return result;
}

String Win32SocketPeer::getHostIPAddress()
{
	String result = Format("%d.%d.%d.%d") % 
		sockAddr_.sin_addr.S_un.S_un_b.s_b1 %
		sockAddr_.sin_addr.S_un.S_un_b.s_b2 %
		sockAddr_.sin_addr.S_un.S_un_b.s_b3 %
		sockAddr_.sin_addr.S_un.S_un_b.s_b4;

	return result;
}

unsigned short Win32SocketPeer::getPort()
{
	unsigned short result = ntohs( sockAddr_.sin_port );
	return result;
}

void Win32SocketPeer::setOptions( Dictionary& options )
{	
	Dictionary::Enumerator* enumerator = options.getEnumerator();	

	while ( enumerator->hasMoreElements() ) {
		Dictionary::pair element = enumerator->nextElement();
		if ( element.first == Socket::soBlocking ) {
			bool blocking = element.second;
			unsigned long val = blocking ? 0 : 1;

			::ioctlsocket( handle_, FIONBIO, &val );
		}
		else if ( element.first == Socket::soBroadcast ) {
			bool blocking = element.second;
			BOOL val = blocking ? TRUE : FALSE;
			::setsockopt( handle_, SOL_SOCKET, SO_BROADCAST, (const char*)&val, sizeof(val) );
		}
		else if ( element.first == Socket::soDontLinger ) {
			bool dontLinger = element.second;
			BOOL val = dontLinger ? TRUE : FALSE;
			::setsockopt( handle_, SOL_SOCKET, SO_DONTLINGER, (const char*)&val, sizeof(val) );			
		}
		else if ( element.first == Socket::soDontRoute ) {
			bool dontRoute = element.second;
			BOOL val = dontRoute ? TRUE : FALSE;
			::setsockopt( handle_, SOL_SOCKET, SO_DONTROUTE, (const char*)&val, sizeof(val) );
		}
		else if ( element.first == Socket::soKeepAlive ) {
			bool keepAlive = element.second;
			BOOL val = keepAlive ? TRUE : FALSE;
			::setsockopt( handle_, SOL_SOCKET, SO_KEEPALIVE, (const char*)&val, sizeof(val) );
		}
		else if ( element.first == Socket::soRecvBuffer ) {
			int recvBuffer = element.second;
			::setsockopt( handle_, SOL_SOCKET, SO_RCVBUF, (const char*)&recvBuffer, sizeof(recvBuffer) );
		}
		else if ( element.first == Socket::soReuseAddress ) {
			bool reuseAddr = element.second;
			BOOL val = reuseAddr ? TRUE : FALSE;
			::setsockopt( handle_, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val) );
		}
		else if ( element.first == Socket::soSendBuffer ) {
			int sendBuffer = element.second;
			::setsockopt( handle_, SOL_SOCKET, SO_SNDBUF, (const char*)&sendBuffer, sizeof(sendBuffer) );
		}
	}
}

Dictionary Win32SocketPeer::getOptions()
{
	Dictionary result;

	BOOL boolVal = 0;
	int valSize = sizeof(boolVal);

	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_BROADCAST, (char*)&boolVal, &valSize ) ) {
		result[Socket::soBroadcast] = boolVal ? true : false;
	}

	boolVal = 0;
	valSize = sizeof(boolVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_DONTLINGER, (char*)&boolVal, &valSize ) ) {
		result[Socket::soDontLinger] = boolVal ? true : false;
	}

	boolVal = 0;
	valSize = sizeof(boolVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_DONTROUTE, (char*)&boolVal, &valSize ) ) {
		result[Socket::soDontRoute] = boolVal ? true : false;
	}

	boolVal = 0;
	valSize = sizeof(boolVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_KEEPALIVE, (char*)&boolVal, &valSize ) ) {
		result[Socket::soKeepAlive] = boolVal ? true : false;
	}

	int intVal = 0;
	valSize = sizeof(intVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_RCVBUF, (char*)&intVal, &valSize ) ) {
		result[Socket::soRecvBuffer] = intVal;
	}

	boolVal = 0;
	valSize = sizeof(boolVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_REUSEADDR, (char*)&boolVal, &valSize ) ) {
		result[Socket::soReuseAddress] = boolVal ? true : false;
	}


	intVal = 0;
	valSize = sizeof(intVal);
	if( SOCKET_ERROR != getsockopt( handle_, SOL_SOCKET, SO_SNDBUF, (char*)&intVal, &valSize ) ) {
		result[Socket::soSendBuffer] = intVal;
	}

	return result;
}

bool Win32SocketPeer::wouldOperationBlock()
{
	return WSAGetLastError() == WSAEWOULDBLOCK ? true : false;
}




void selectLoopOnce( std::vector<Socket*>* inReadSockets,
										std::vector<Socket*>* inWriteSockets,
										std::vector<Socket*>* inErrorSockets,
										struct timeval* timeoutVal,
										std::vector<Socket*>* outReadSockets,
										std::vector<Socket*>* outWriteSockets,
										std::vector<Socket*>* outErrorSockets)

{
	fd_set* reader = NULL;
	fd_set* writer = NULL;
	fd_set* errors = NULL;

	fd_set readfd;
	FD_ZERO(&readfd);

	fd_set writefd;
	FD_ZERO(&writefd);
	
	fd_set exceptionfd;
	FD_ZERO(&exceptionfd);

	unsigned int maxSock = 0;

	if ( NULL != inReadSockets ) {
		VCF_ASSERT( inReadSockets->size() <= FD_SETSIZE );

		std::vector<Socket*>::iterator it = inReadSockets->begin();

		while ( it != inReadSockets->end() ){
			Socket* so = *it;
			VCF_ASSERT( so != NULL );

			unsigned int sockID = (unsigned int)so->getPeer()->getHandleID();
			FD_SET ( sockID, &readfd) ;		
			if ( sockID > maxSock ){
				maxSock = sockID;	
			}
			it++;
		}

		reader = &readfd;
	}

	if ( NULL != inWriteSockets ) {
		VCF_ASSERT( inWriteSockets->size() <= FD_SETSIZE );

		std::vector<Socket*>::iterator it = inWriteSockets->begin();

		while ( it != inWriteSockets->end() ){
			Socket* so = *it;
			unsigned int sockID = (unsigned int)so->getPeer()->getHandleID();
			FD_SET ( sockID, &writefd) ;		
			if ( sockID > maxSock ){
				maxSock = sockID;	
			}
			it++;
		}

		writer = &writefd;
	}

	if ( NULL != inErrorSockets ) {
		VCF_ASSERT( inErrorSockets->size() <= FD_SETSIZE );

		std::vector<Socket*>::iterator it = inErrorSockets->begin();

		while ( it != inErrorSockets->end() ){
			Socket* so = *it;
			unsigned int sockID = (unsigned int)so->getPeer()->getHandleID();
			FD_SET ( sockID, &exceptionfd) ;		
			if ( sockID > maxSock ){
				maxSock = sockID;	
			}
			it++;
		}

		errors = &exceptionfd;
	}


	int result = ::select( maxSock + 1, reader, writer, errors, timeoutVal);

	if ( result > 0 ) {
		if ( (NULL != inReadSockets) && (NULL != outReadSockets) ) {			
			std::vector<Socket*>::iterator it = inReadSockets->begin();			
			while ( it != inReadSockets->end() ){
				Socket* so = *it;
				int sockID = (int)so->getPeer()->getHandleID();
				if ( FD_ISSET ( sockID, reader) ) {
					outReadSockets->push_back( so );
					so->internal_setReadable( true );
				}
				else {
					so->internal_setReadable( false );
				}
				it++;
			}
		}
		
		if ( (NULL != inWriteSockets) && (NULL != outWriteSockets) ) {
			std::vector<Socket*>::iterator it = inWriteSockets->begin();			
			while ( it != inWriteSockets->end() ){
				Socket* so = *it;
				int sockID = (int)so->getPeer()->getHandleID();
				if ( FD_ISSET ( sockID, writer) ) {
					outWriteSockets->push_back( so );
					so->internal_setWriteable( true );
				}
				else {
					so->internal_setWriteable( false );
				}
				it++;
			}
		}
		
		if ( (NULL != inErrorSockets) && (NULL != outErrorSockets) ) {
			std::vector<Socket*>::iterator it = inErrorSockets->begin();			
			while ( it != inErrorSockets->end() ){
				Socket* so = *it;
				int sockID = (int)so->getPeer()->getHandleID();
				if ( FD_ISSET ( sockID, writer) ) {
					outErrorSockets->push_back( so );
					so->internal_setErrorState( true );
				}
				else {
					so->internal_setErrorState( false );
				}				
					

				it++;
			}
		}
	}
}


void Win32SocketPeer::select( uint32 timeout, SocketArray* readSockets, 
								SocketArray* writeSockets,
								SocketArray* errorSockets )
{
	//Doesn't make any sense to have ALL three null
	VCF_ASSERT( (NULL != readSockets) || (NULL != writeSockets) || (NULL != errorSockets) );

	//setup the select timeout struct...
	struct timeval* timeoutVal;
	struct timeval timeoutTime;	
	//initialized to 0 values - this will return immediately
	timeoutTime.tv_sec = 0; 
	timeoutTime.tv_usec = 0;

	if ( Socket::SelectWaitForever == timeout ) {
		timeoutVal = NULL;
	}
	else if ( Socket::SelectNoWait == timeout ) {
		timeoutVal = &timeoutTime;
	}
	else {
		timeoutTime.tv_sec = timeout / 1000; //timeout is in milliseconds
		timeoutTime.tv_usec = (timeout % 1000) * 1000;
		timeoutVal = &timeoutTime;
	}



	std::vector<Socket*>* inReadSockets = NULL;
	std::vector<Socket*>* inWriteSockets = NULL;
	std::vector<Socket*>* inErrorSockets = NULL;


	std::vector<Socket*> tmpReadSockets;
	std::vector<Socket*> tmpWriteSockets;
	std::vector<Socket*> tmpErrorSockets;

	std::vector<Socket*> tmpOutReadSockets;
	std::vector<Socket*> tmpOutWriteSockets;
	std::vector<Socket*> tmpOutErrorSockets;

	std::vector<Socket*>::iterator readIt;
	std::vector<Socket*>::iterator writeIt;
	std::vector<Socket*>::iterator errorIt;

	bool selectDone = false;

	if ( readSockets ) {
		readIt = readSockets->begin();	
	}
	
	if ( writeSockets ) {
		writeIt = writeSockets->begin();	
	}

	if ( errorSockets ) {
		errorIt = errorSockets->begin();	
	}
	

	while ( !selectDone ) {

		//load up the various socket arrays

		int count = 0;
		tmpReadSockets.clear();
		tmpWriteSockets.clear();
		tmpErrorSockets.clear();

		inReadSockets = NULL;
		inWriteSockets = NULL;
		inErrorSockets = NULL;

		if ( readSockets ) {
			count = 0;
			while ( readIt != readSockets->end() && count < FD_SETSIZE ) {
				tmpReadSockets.push_back( *readIt );
				++ readIt;
				count ++;
			}

			inReadSockets = tmpReadSockets.empty() ? NULL : &tmpReadSockets;
		}

		if ( writeSockets ) {
			count = 0;
			while ( writeIt != writeSockets->end() && count < FD_SETSIZE ) {
				tmpWriteSockets.push_back( *writeIt );
				++ writeIt;
				count ++;
			}

			inWriteSockets = tmpWriteSockets.empty() ? NULL : &tmpWriteSockets;
		}

		if ( errorSockets ) {
			count = 0;
			while ( errorIt != errorSockets->end() && count < FD_SETSIZE ) {
				tmpErrorSockets.push_back( *errorIt );
				++ errorIt;
				count ++;
			}

			inErrorSockets = tmpErrorSockets.empty() ? NULL : &tmpErrorSockets;
		}

		
		if ( inReadSockets || inWriteSockets || inErrorSockets ) {
			selectLoopOnce( inReadSockets, 
									inWriteSockets, 
									inErrorSockets,
									timeoutVal,
									(inReadSockets != NULL) ? &tmpOutReadSockets : NULL,
									(inWriteSockets != NULL) ? &tmpOutWriteSockets : NULL,
									(inErrorSockets != NULL) ? &tmpOutErrorSockets : NULL );
		}
		else {
			selectDone = true;
		}		
	}


	if ( readSockets ) {
		*readSockets = tmpOutReadSockets;
	}

	if ( writeSockets ) {
		*writeSockets = tmpOutWriteSockets;
	}

	if ( errorSockets ) {
		*errorSockets = tmpOutErrorSockets;
	}
}




Win32UDPSocketPeer::Win32UDPSocketPeer():
	Win32SocketPeer()
{

}

Win32UDPSocketPeer::Win32UDPSocketPeer( SOCKET handle ):
	Win32SocketPeer(handle)
{

}

int Win32UDPSocketPeer::create()
{
	VCF_ASSERT( NULL == handle_ );

	int result = -1;

	handle_ = ::socket( AF_INET, SOCK_DGRAM, 0 );

	if ( INVALID_SOCKET == handle_ ) {
		handle_ = 0;
		result = -1;
	}
	else {
		BOOL val = TRUE;
		setsockopt( handle_, SOL_SOCKET, SO_DONTLINGER, (const char*)&val, sizeof(val) );
		result = 0;




		memset(&sockAddr_, 0, sizeof(sockAddr_));
    	sockAddr_.sin_family = AF_INET;    	
    	sockAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
		sockAddr_.sin_port = htons(0);
		result = ::bind( handle_, (struct sockaddr *)&sockAddr_, sizeof(sockAddr_) );
	}

	return result;
}


int Win32UDPSocketPeer::connect( const String& host, const unsigned short port )
{
	int result = -1;

	memset( &remoteAddr_, 0, sizeof(remoteAddr_) );
	remoteAddr_.sin_family = AF_INET;
	struct hostent *hp = ::gethostbyname(host.ansi_c_str());

	if ( NULL != hp ) {
		memcpy( &(remoteAddr_.sin_addr.s_addr), hp->h_addr, hp->h_length );
		remoteAddr_.sin_port = htons((short)port);
	}

	return result;
}

int Win32UDPSocketPeer::listen( unsigned short port )
{
	throw RuntimeException( "listen() not allowed for UDP socket" );
	return -1;
}

SocketPeer* Win32UDPSocketPeer::accept()
{
	return Win32SocketPeer::accept();
}

int Win32UDPSocketPeer::recv( unsigned char* bytes, size_t bytesLength )
{
	int result = -1;

	struct sockaddr_in fromAddr;
	int fromLength = sizeof(fromAddr);
	result = ::recvfrom( handle_, (char*) bytes, bytesLength, 0, (struct sockaddr*)&fromAddr, &fromLength );

	if ( result < 0 ) {
		if ( !wouldOperationBlock() ) {
			socket_->internal_setErrorState( true );
		}
	}

	memset(&remoteAddr_, 0, sizeof(remoteAddr_));
	memcpy(&remoteAddr_, &fromAddr, sizeof(fromAddr));


	return result;
}

int Win32UDPSocketPeer::send( const unsigned char* bytes, size_t bytesLength )
{
	int result = -1;

	result = ::sendto( handle_, (const char*)bytes, bytesLength, 0, (struct sockaddr*)&remoteAddr_, sizeof(remoteAddr_));

	if ( result < 0 ) {
		if ( !wouldOperationBlock() ) {
			socket_->internal_setErrorState( true );
		}
	}

	return result;
}
