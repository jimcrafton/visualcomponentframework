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

int Win32SocketPeer::create( Socket::SocketType type )
{
	VCF_ASSERT( NULL == handle_ );

	int result = -1;

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

	handle_ = ::socket( AF_INET, sockType, 0 );

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

void Win32SocketPeer::select( uint32 timeout, SocketArray* readSockets, 
								SocketArray* writeSockets,
								SocketArray* errorSockets )
{
	fd_set* readers = NULL;
	fd_set* writers = NULL;
	fd_set* errors = NULL;

	//set up the read/write/error FD's
	fd_set readfd;
	FD_ZERO(&readfd);

	fd_set writefd;
	FD_ZERO(&writefd);
	
	fd_set exceptionfd;
	FD_ZERO(&exceptionfd);

	unsigned int maxSockHandle = 0;

	bool selectOnSelf = false;

	if ( (NULL == readSockets) && (NULL == writeSockets) && (NULL == writeSockets) ) {
		//select on self!
		selectOnSelf = true;
		socket_->internal_setReadable( false );
		socket_->internal_setWriteable( false );
		socket_->internal_setErrorState( false );

		unsigned int sockID = (unsigned int) getHandleID();
		FD_SET ( sockID, &readfd) ;
		FD_SET ( sockID, &writefd) ;
		FD_SET ( sockID, &exceptionfd) ;

		readers = &readfd;
		writers = &writefd;
		errors = &exceptionfd;
		if ( sockID > maxSockHandle ){
			maxSockHandle = sockID;	
		}
	}
	else {	
		if ( NULL != readSockets ) {
			SocketArray::iterator it = readSockets->begin();
			
			while ( it != readSockets->end() ){
				Socket* so = *it;
				VCF_ASSERT( so != NULL );
				
				unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
				
				FD_SET ( sockID, &readfd) ;
				if ( sockID > maxSockHandle ){
					maxSockHandle = sockID;	
				}
				it++;
			}
			
			readers = &readfd;
		}

		if ( NULL != writeSockets ) {
			SocketArray::iterator it = writeSockets->begin();
			
			while ( it != writeSockets->end() ){
				Socket* so = *it;
				VCF_ASSERT( so != NULL );
				
				unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
				
				FD_SET ( sockID, &writefd) ;
				if ( sockID > maxSockHandle ){
					maxSockHandle = sockID;	
				}
				it++;
			}
			
			writers = &writefd;
		}

		if ( NULL != errorSockets ) {
			SocketArray::iterator it = errorSockets->begin();
			
			while ( it != errorSockets->end() ){
				Socket* so = *it;
				VCF_ASSERT( so != NULL );
				
				unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
				
				FD_SET ( sockID, &exceptionfd) ;
				if ( sockID > maxSockHandle ){
					maxSockHandle = sockID;	
				}
				it++;
			}
			
			errors = &exceptionfd;
		}
	}

	//setup the select timeout struct...
	struct timeval timeoutTime;	
	//initialized to 0 values - this will return immediately
	timeoutTime.tv_sec = 0; 
	timeoutTime.tv_usec = 0;

	struct timeval* timeoutVal;
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

	//now all our FD's are set up, we can begin the select process...

	int err = ::select( maxSockHandle + 1, readers, writers, errors, timeoutVal );

	if ( err > 0 ) {
		if ( selectOnSelf ) {
			unsigned int sockID = (unsigned int) getHandleID();

			if ( FD_ISSET ( sockID, readers) ) {
				socket_->internal_setReadable( true );
			}
			
			if ( FD_ISSET ( sockID, writers) ) {
				socket_->internal_setWriteable( true );
			}

			if ( FD_ISSET ( sockID, errors) ) {
				socket_->internal_setErrorState( true );
			}
		}
		else {
			SocketArray tmpSockList;
			if ( NULL != readSockets ) {		
				tmpSockList.clear();
				
				SocketArray::iterator it = readSockets->begin();
				//check out the socket id's to see if they 
				//are flagged as readable, if they are copy the
				//socket to the temp list
				while ( it != readSockets->end() ){
					Socket* so = *it;
					unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
					if ( FD_ISSET ( sockID, readers) ) {						
						tmpSockList.push_back( so );
						so->internal_setReadable( true );
					}
					else {
						so->internal_setReadable( false );
					}
					it++;
				}
				
				//clear out the passed in array
				readSockets->clear();
				
				//re-assign the temp list to the passed in array
				*readSockets = tmpSockList;
			}

			if ( NULL != writeSockets ) {		
				tmpSockList.clear();
				
				SocketArray::iterator it = writeSockets->begin();
				//check out the socket id's to see if they 
				//are flagged as writeable, if they are copy the
				//socket to the temp list
				while ( it != writeSockets->end() ){
					Socket* so = *it;
					unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
					if ( FD_ISSET ( sockID, writers) ) {
						tmpSockList.push_back( so );
						so->internal_setWriteable( true );
					}
					else {
						so->internal_setReadable( false );
					}
					it++;
				}
				
				//clear out the passed in array
				writeSockets->clear();
				
				//re-assign the temp list to the passed in array
				*writeSockets = tmpSockList;
			}

			if ( NULL != errorSockets ) {		
				tmpSockList.clear();
				
				SocketArray::iterator it = errorSockets->begin();
				//check out the socket id's to see if they 
				//are flagged as writeable, if they are copy the
				//socket to the temp list
				while ( it != errorSockets->end() ){
					Socket* so = *it;
					unsigned int sockID = (unsigned int) so->getPeer()->getHandleID();
					if ( FD_ISSET ( sockID, errors) ) {
						tmpSockList.push_back( so );
						so->internal_setErrorState( true );
					}
					else {
						so->internal_setErrorState( false );
					}
					it++;
				}
				
				//clear out the passed in array
				errorSockets->clear();
				
				//re-assign the temp list to the passed in array
				*errorSockets = tmpSockList;
			}
		}
	}
	else {
		//error

		if ( NULL != readSockets ) {
			readSockets->clear();
		}
		
		if ( NULL != writeSockets ) {
			writeSockets->clear();
		}

		if ( NULL != errorSockets ) {
			errorSockets->clear();
		}
	}
}
