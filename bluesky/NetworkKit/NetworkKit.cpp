////NetworkKit.cpp

#include <winsock2.h>
#pragma comment( lib, "ws2_32" )

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"


namespace VCF {


	class NetworkKit {
	public:
		static void init( int argc, char** argv );

		static void terminate();
		
	};

};



namespace VCF {

	class SocketPeer;


	class Socket : public Object {
	public:
		enum SocketType{
			stStream,
			stDatagram
		};
		

		//socket options
		/**
		This key indicates whether or not the 
		socket is blocking or not. It's value 
		type is a bool.
		*/
		static const String soBlocking;

		/**
		Bool value
		*/
		static const String soBroadcast;

		/**
		Bool value
		*/
		static const String soDontLinger;

		/**
		Bool value
		*/
		static const String soDontRoute;

		/**
		Bool value
		*/
		static const String soKeepAlive;		

		/**
		int value
		*/
		static const String soRecvBuffer;

		/**
		Bool value
		*/
		static const String soReuseAddress;

		/**
		int value
		*/
		static const String soSendBuffer;
		
		/**
		\par
		A static utility function to verify that the 
		socket options have valid key-value pairings.
		The function iterates through the options
		until it finds the first invalid key-value 
		pairing.
		\par
		For example, if you used the key Socket::soBlocking
		with a int type, then the function would return a 
		false value.
		@return bool returns true if the options are valid,
		otherwise it returns false at the first key-value
		pair that is invalid.
		*/
		static bool validateOptions( Dictionary& options );

		/**
		Creates an unconnected socket 
		in stStream mode.
		*/
		Socket();

		/**
		Creates a bound and listening socket 
		in stStream mode.
		*/
		Socket( unsigned short port );

		/**
		Creates a connected socket 
		in stStream mode. A connection is made to 
		the specified host and port
		*/
		Socket( const String& host, unsigned short port );


		virtual ~Socket();

		void open();

		void close();

		void connect( const String& host, unsigned short port );

		void listen( unsigned short port );

		Socket* accept();

		void setOptions( Dictionary& options );

		Dictionary getOptions();

		String getHostName();

		String getHostIPAddress();

		unsigned short getPort();

		SocketPeer* getPeer() {
			return peer_;
		}	

		SocketType getSocketType() {
			return type_;
		}
	protected:
		/**
		Creates a socket from an existing peer
		intance. This is used primarily by the accept()
		method.
		*/
		Socket( SocketPeer* peer );


		SocketPeer* peer_;
		SocketType type_;
	};

};


const VCF::String VCF::Socket::soBlocking = "soBlocking"; 



namespace VCF {


	class SocketPeer {
	public:
		
		virtual ~SocketPeer(){};

		/**
		\par
		Creates a new OS specific socket handle. In the 
		simplest case, this would be implemented with the
		BSD socket() function.

		\par
		The caller specifies the socket type, which can
		be either a streaming type (i.e. a socket appropriate
		for TCP/IP streaming communication), or a datagram
		type (i.e. a socket appropriate
		for UPD communication )
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int create( Socket::SocketType type ) = 0;

		/**
		Closes the OS specific socket handle and releases any resources
		associated with it.
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int close() = 0;

		/**
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int connect( const String& host, const unsigned short port ) = 0;

		/**
		\par
		Note: bind is implicitly done here.
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int listen( unsigned short port ) = 0;

		/**
		Accepts a new connection and returns a new socket peer
		instance. Assumes the listen() call has already occurred.
		If it has not then an exception is thrown.
		*/
		virtual SocketPeer* accept() = 0;

		//IO
		/**
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int recv( unsigned char* bytes, size_t bytesLength ) = 0;

		/**
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int send( const unsigned char* bytes, size_t bytesLength ) = 0;

		/**
		Returns a handle for the OS specific socket resource. This 
		is typically a socket handle or descriptor, depending on the 
		OS and the underlying implementation.
		*/
		virtual OSHandleID getHandleID() = 0;

		/**
		Returns the host name that this instance represents.
		This is a potentially blocking call, and may take a while to 
		complete if the host name cannot be resolved by the underlying
		OS network stack.
		*/
		virtual String getHostName() = 0;

		/**
		Returns the IP address of the host as a string
		formatted (for IPV4 at least) as 4 "octets", 
		each separated by the "." character. Each
		octet is a number string in the range from 0 to 255.
		*/
		virtual String getHostIPAddress() = 0;

		/**
		Returns the port number for this socket instance.
		*/
		virtual unsigned short getPort() = 0;

		/**
		Sets the options for a socket. The options are stored as a 
		dictionary of items, with the keys being 1 or more values 
		represented by the Socket::soXXX const string variables.
		*/
		virtual void setOptions( Dictionary& options ) = 0;

		/**
		Returns a dictionary containing the options for the
		socket.
		*/
		virtual Dictionary getOptions() = 0;

		/**
		Indicates whether the current operation would block.
		Assumes a non blocking socket. This is roughly equivalent
		to getting a an EWOULDBLOCK or WSAEWOULDBLOCK error number.

		@return bool True if the operation would block, otherwise
		false if it would not. 
		*/
		virtual bool wouldOperationBlock() = 0;
	};

};

namespace VCF {


	class NetworkToolkit {
	public:
		static void create();
		static void destroy();


		static SocketPeer* createSocketPeer();

	protected:

		NetworkToolkit(){};
		virtual ~NetworkToolkit(){};
			
		static NetworkToolkit* Instance;

		virtual SocketPeer* internal_createSocketPeer() = 0;
	};

};







namespace VCF {


	class Win32NetworkToolkit : public NetworkToolkit {
	public:

		Win32NetworkToolkit();

	protected:		
		virtual ~Win32NetworkToolkit();

		virtual SocketPeer* internal_createSocketPeer();
	};

};







namespace VCF {


	class Win32SocketPeer : public SocketPeer {
	public:	

		Win32SocketPeer();

		Win32SocketPeer( SOCKET handle );

		virtual int create( Socket::SocketType type );

		virtual int close();

		virtual int connect( const String& host, const unsigned short port );

		virtual int listen( unsigned short port );

		virtual SocketPeer* accept();

		virtual int recv( unsigned char* bytes, size_t bytesLength );

		virtual int send( const unsigned char* bytes, size_t bytesLength );

		virtual OSHandleID getHandleID();

		virtual String getHostName();

		virtual String getHostIPAddress();

		virtual unsigned short getPort();

		virtual void setOptions( Dictionary& options );

		virtual Dictionary getOptions();

		virtual bool wouldOperationBlock();

	protected:
		SOCKET handle_;
		struct sockaddr_in sockAddr_;

	};

};





namespace VCF {

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
}

SocketPeer*	NetworkToolkit::createSocketPeer() 
{
	return NetworkToolkit::Instance->internal_createSocketPeer();
}



};







namespace VCF {

Win32NetworkToolkit::Win32NetworkToolkit()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData; 
	int startedOk = WSAStartup(wVersionRequested, &wsaData); 
	if (startedOk != 0) {		
		//throw exception
		WSACleanup();
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 || 
		HIBYTE( wsaData.wVersion ) != 1 ) 	{ 
		WSACleanup();
		startedOk = -1;
	}
	
	if (0 != startedOk) {
		throw RuntimeException( MAKE_ERROR_MSG_2("WSAStartup failed to initialize!") );
	}
}

Win32NetworkToolkit::~Win32NetworkToolkit()
{
	WSACleanup();
}

SocketPeer* Win32NetworkToolkit::internal_createSocketPeer()
{
	SocketPeer* result = new Win32SocketPeer();

	return result;
}


}




namespace VCF {

Win32SocketPeer::Win32SocketPeer():
	handle_(NULL)		
{
	memset( &sockAddr_, 0, sizeof(sockAddr_) );
}

Win32SocketPeer::Win32SocketPeer( SOCKET handle ):
	handle_(handle)
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

	return result;
}

int Win32SocketPeer::send( const unsigned char* bytes, size_t bytesLength )
{
	int result = -1;

	result = ::send( handle_, (const char*)bytes, bytesLength, 0 );

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
	
}

Dictionary Win32SocketPeer::getOptions()
{
	Dictionary result;

	return result;
}

bool Win32SocketPeer::wouldOperationBlock()
{
	return WSAGetLastError() == WSAEWOULDBLOCK ? true : false;
}

}







namespace VCF {

Socket::Socket():
	peer_(NULL),
	type_(Socket::stStream)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}
}

Socket::Socket( unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	
	open();

	listen( port );
}

Socket::Socket( const String& host, unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream)
{
	peer_ = NetworkToolkit::createSocketPeer();
	
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	open();

	connect( host, port );
}

Socket::Socket( SocketPeer* peer ):
	peer_(peer),
	type_(Socket::stStream)
{
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("NULL peer instance passed in to Socket constructor.") );
	}
}

Socket::~Socket()
{
	delete peer_;
}

void Socket::open()
{
	close();
	
	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}
}

void Socket::close()
{
	if ( 0 != peer_->close() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Attempt to close peer failed.") );
	}
}

void Socket::connect( const String& host, unsigned short port )
{
	if ( 0 != peer_->connect( host, port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed connect.") );
	}
}

void Socket::listen( unsigned short port )
{
	if ( 0 != peer_->listen( port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed listen.") );
	}
}

Socket* Socket::accept()
{
	Socket* result = NULL;

	SocketPeer* newSockPeer = peer_->accept();
	if ( NULL != newSockPeer ) {
		result = new Socket( newSockPeer );
	}

	return result;
}

bool Socket::validateOptions( Dictionary& options )
{
	bool result = true;

	return result;
}


void Socket::setOptions( Dictionary& options )
{
	if ( Socket::validateOptions( options ) ) {
		peer_->setOptions( options );
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid option (or options) passed to socket - no options set.") );
	}
}

Dictionary Socket::getOptions()
{
	return peer_->getOptions();
}

String Socket::getHostName()
{
	return peer_->getHostName();
}

String Socket::getHostIPAddress()
{
	return peer_->getHostIPAddress();
}

unsigned short Socket::getPort()
{
	return peer_->getPort();
}

}




namespace VCF {


void NetworkKit::init( int argc, char** argv )
{
	NetworkToolkit::create();
}

void NetworkKit::terminate()
{
	NetworkToolkit::destroy();
}


};



using namespace VCF;




int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	NetworkKit::init(  argc, argv );
	



	Socket sock;

	
	sock.connect( "www.microsoft.com", 23 );

	String s = sock.getHostIPAddress();
	String s2 = sock.getHostName();
	int p = sock.getPort();

	sock.close();

	sock.open();

	sock.listen( 10032 );

	s = sock.getHostIPAddress();
	s2 = sock.getHostName();
	p = sock.getPort();



	NetworkKit::terminate();

	FoundationKit::terminate();
	return 0;
}


