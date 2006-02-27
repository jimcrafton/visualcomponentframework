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

	class Socket;
	class SocketPeer;

	class InetAddrPeer;
	


	
	class InternetAddress : public Object {
	public:
		typedef std::vector<unsigned char>	RawBytes;

		InternetAddress();
		InternetAddress( const String& host );
		InternetAddress( const RawBytes& ipAddr );		
		InternetAddress( unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4 );		
		InternetAddress( unsigned char* bytes, size_t bytesLength );	
		virtual ~InternetAddress();

		RawBytes getAddressBytes();
		String getHostName();
		String getHostAddress();
	protected:
		InetAddrPeer* peer_;
	};

	typedef  std::vector<Socket*> SocketArray;

	class Socket : public Object {
	public:
		enum SocketType{
			stStream,
			stDatagram
		};

		enum {
			/**
			Select should check and then return immediately
			*/
			SelectNoWait = (uint32)0,

			/**
			Select will wait indefinitely, until one of the 
			sockets passed in is flagged with data.
			*/
			SelectWaitForever = (uint32)-1
		};
		
		enum SocketState{
			ssError	=		0x0001,
			ssReadable	=	0x0002,
			ssWriteable	=	0x0004,
			ssConnected =	0x0010,
			ssListening	=	0x0020
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

		bool isReadable() const {
			return (state_ & Socket::ssReadable) ? true : false;
		}

		bool hasError() const {
			return (state_ & Socket::ssError) ? true : false;
		}

		bool isWriteable() const {
			return (state_ & Socket::ssWriteable) ? true : false;
		}

		bool isConnected() const {
			return (state_ & Socket::ssConnected) ? true : false;
		}

		bool isListening() const {
			return (state_ & Socket::ssListening) ? true : false;
		}

		bool pending() const;

		void internal_setErrorState( bool val ) {
			if ( val ) {
				state_ |= Socket::ssError;
			}
			else {
				state_ &= ~Socket::ssError;
			}
		}

		void internal_setReadable( bool val ) {
			if ( val ) {
				state_ |= Socket::ssReadable;
			}
			else {
				state_ &= ~Socket::ssReadable;
			}
		}

		void internal_setWriteable( bool val ) {
			if ( val ) {
				state_ |= Socket::ssWriteable;
			}
			else {
				state_ &= ~Socket::ssWriteable;
			}
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

		int state_;
	};

};


const VCF::String VCF::Socket::soBlocking = "soBlocking"; 
const VCF::String VCF::Socket::soBroadcast = "soBroadcast";
const VCF::String VCF::Socket::soDontLinger = "soDontLinger";
const VCF::String VCF::Socket::soDontRoute = "soDontRoute";
const VCF::String VCF::Socket::soKeepAlive = "soKeepAlive";
const VCF::String VCF::Socket::soRecvBuffer = "soRecvBuffer";
const VCF::String VCF::Socket::soReuseAddress = "soReuseAddress";
const VCF::String VCF::Socket::soSendBuffer = "soSendBuffer";



namespace VCF {
	class InetAddrPeer {
	public:

		virtual void initWithHostName( const String& host ) = 0;
		virtual void initWithIPAddr( const InternetAddress::RawBytes& ipAddr ) = 0;
		virtual void initAsLocalHost() = 0;


		virtual InternetAddress::RawBytes getAddressBytes() = 0;
		virtual String getHostName() = 0;
		virtual String getHostAddress() = 0;
		virtual bool isIPV4() = 0;
		virtual bool isIPV6() = 0;
	};

};

namespace VCF {


	class SocketPeer {
	public:
		
		virtual ~SocketPeer(){};

		virtual void setPeerOwner( Socket* socket ) = 0;
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

		/**
		performs a select, using the various read, write, and/or error socket 
		lists. Will block for a maximum of timeout milliseconds. If the all
		the read, write, and error socket arrays are NULL, then the 
		select is performed only on the socket instance itself.
		@param uint32 the maximum number of milliseconds to wait for. 
			@see Socket::SelectNoWait,
			@see Socket::SelectWaitForever
		@param SocketArray a pointer to a vector of Socket instances to test
		whether or not they can be read from. This may vector
		may be null if the	caller is not interested in read notifications. 
		Note that the contents of the vector may change. You may pass in 10 
		sockets to test, and only get back 3 that are actually ready to be 
		read from.

		@param SocketArray a pointer to a vector of Socket instances to test
		whether or not they may be written to. This may vector
		may be null if the	caller is not interested in write notifications. 
		Note that the contents of the vector may change. You may pass in 10 
		sockets to test, and only get back 3 that are actually ready to be 
		written to.

		@param SocketArray a pointer to a vector of Socket instances to test
		whether or not they have errors. This may vector
		may be null if the	caller is not interested in write notifications. 
		Note that the contents of the vector may change. You may pass in 10 
		sockets to test, and only get back 3 that are actually in an error 
		state.
		*/
		virtual void select( uint32 timeout, SocketArray* readSockets, SocketArray* writeSockets,
						SocketArray* errorSockets ) = 0;
	};

};

namespace VCF {


	class NetworkToolkit {
	public:
		static void create();
		static void destroy();


		static SocketPeer* createSocketPeer();
		static InetAddrPeer* createInetAddrPeer();
		

	protected:

		NetworkToolkit(){};
		virtual ~NetworkToolkit(){};
			
		static NetworkToolkit* Instance;

		virtual SocketPeer* internal_createSocketPeer() = 0;
		virtual InetAddrPeer* internal_createInetAddrPeer() = 0;
	};

};







namespace VCF {


	class Win32NetworkToolkit : public NetworkToolkit {
	public:

		Win32NetworkToolkit();

	protected:		
		virtual ~Win32NetworkToolkit();

		virtual SocketPeer* internal_createSocketPeer();
		virtual InetAddrPeer* internal_createInetAddrPeer();
	};

};







namespace VCF {


	class Win32InetAddrPeer : public InetAddrPeer {
	public:
		Win32InetAddrPeer();
		virtual ~Win32InetAddrPeer();

		virtual void initWithHostName( const String& host );
		virtual void initWithIPAddr( const InternetAddress::RawBytes& ipAddr );
		virtual void initAsLocalHost();


		virtual InternetAddress::RawBytes getAddressBytes();
		virtual String getHostName();
		virtual String getHostAddress();
		virtual bool isIPV4();
		virtual bool isIPV6();

	protected:
		AnsiString ipAddress_;
		AnsiString host_;
		
	};

	class Win32SocketPeer : public SocketPeer {
	public:	

		Win32SocketPeer();

		Win32SocketPeer( SOCKET handle );

		virtual void setPeerOwner( Socket* socket ) {
			socket_ = socket;
		}

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

		virtual void select( uint32 timeout, SocketArray* readSockets, SocketArray* writeSockets,
						SocketArray* errorSockets );

	protected:
		SOCKET handle_;
		struct sockaddr_in sockAddr_;
		Socket* socket_;

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

InetAddrPeer* NetworkToolkit::createInetAddrPeer()
{
	return NetworkToolkit::Instance->internal_createInetAddrPeer();
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

InetAddrPeer* Win32NetworkToolkit::internal_createInetAddrPeer()
{
	return new Win32InetAddrPeer();
}


}


namespace VCF { 

Win32InetAddrPeer::Win32InetAddrPeer()
{
	
}

Win32InetAddrPeer::~Win32InetAddrPeer()
{

}

void Win32InetAddrPeer::initWithHostName( const String& host )
{
	host_ = host;
}

void Win32InetAddrPeer::initWithIPAddr( const InternetAddress::RawBytes& ipAddr )
{
	struct in_addr addr;
	memset( &addr,0,sizeof(addr) );
	addr.S_un.S_un_b.s_b1 = ipAddr[0];
	addr.S_un.S_un_b.s_b2 = ipAddr[1];
	addr.S_un.S_un_b.s_b3 = ipAddr[2];
	addr.S_un.S_un_b.s_b4 = ipAddr[3];

	ipAddress_ = inet_ntoa(addr);
}

void Win32InetAddrPeer::initAsLocalHost()
{
	host_ = "localhost";
}

InternetAddress::RawBytes Win32InetAddrPeer::getAddressBytes()
{
	InternetAddress::RawBytes result(4);

	struct in_addr addr;

	if ( ipAddress_.empty() ) {
		
		memset( &addr,0,sizeof(addr) );

		hostent* host = gethostbyname( host_.c_str() );
		if ( NULL != host ) {
			memcpy( &(addr.s_addr), host->h_addr, host->h_length );
		}
		ipAddress_ = inet_ntoa(addr);
	}
	else {
		addr.S_un.S_addr = inet_addr( ipAddress_.c_str() );
	}
	
	result[0] = addr.S_un.S_un_b.s_b1;
	result[1] = addr.S_un.S_un_b.s_b2;
	result[2] = addr.S_un.S_un_b.s_b3;
	result[3] = addr.S_un.S_un_b.s_b4;

	return result;
}

String Win32InetAddrPeer::getHostName()
{
	String result;

	
	struct in_addr addr;
	memset( &addr,0,sizeof(addr) );
	addr.S_un.S_addr = inet_addr( ipAddress_.c_str() );

	hostent* host = gethostbyaddr( (const char*)&addr.S_un, sizeof(addr.S_un), 0 );
	if ( NULL != host ) {
		host_ = host->h_name;
	}
	

	result = host_;
	

	return result;
}

String Win32InetAddrPeer::getHostAddress()
{
	String result;

	
	struct in_addr addr;
	memset( &addr,0,sizeof(addr) );
	
	hostent* host = gethostbyname( host_.c_str() );
	if ( NULL != host ) {
		memcpy( &(addr.s_addr), host->h_addr, host->h_length );
		
		if ( host->h_name != host_ ) {
			host_ = host->h_name;
		}
	}
	ipAddress_ = inet_ntoa(addr);
	
	
	result = ipAddress_;

	return result;
}

bool Win32InetAddrPeer::isIPV4()
{
	return true;
}

bool Win32InetAddrPeer::isIPV6()
{
	return false;
}

}





namespace VCF {

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


}







namespace VCF {

Socket::Socket():
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}
}

Socket::Socket( unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	open();

	listen( port );
}

Socket::Socket( const String& host, unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();
	
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	open();

	connect( host, port );
}

Socket::Socket( SocketPeer* peer ):
	peer_(peer),
	type_(Socket::stStream),
	state_(0)
{
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("NULL peer instance passed in to Socket constructor.") );
	}

	peer_->setPeerOwner( this );
}

Socket::~Socket()
{
	peer_->setPeerOwner( NULL );
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
	state_ = 0;
	if ( 0 != peer_->close() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Attempt to close peer failed.") );
	}
}

void Socket::connect( const String& host, unsigned short port )
{
	if ( 0 != peer_->connect( host, port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed connect.") );
	}

	state_ |= Socket::ssConnected;
}

void Socket::listen( unsigned short port )
{
	if ( 0 != peer_->listen( port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed listen.") );
	}

	state_ |= Socket::ssListening;
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

	Dictionary::Enumerator* enumerator = options.getEnumerator();

	static std::map<String,String> validOptionTypes;
	if ( validOptionTypes.empty() ) {
		validOptionTypes[Socket::soBlocking] = Socket::soBlocking;
		validOptionTypes[Socket::soBroadcast] = Socket::soBroadcast;
		validOptionTypes[Socket::soDontLinger] = Socket::soDontLinger;
		validOptionTypes[Socket::soDontRoute] = Socket::soDontRoute;
		validOptionTypes[Socket::soKeepAlive] = Socket::soKeepAlive;
		validOptionTypes[Socket::soRecvBuffer] = Socket::soRecvBuffer;
		validOptionTypes[Socket::soReuseAddress] = Socket::soReuseAddress;
		validOptionTypes[Socket::soSendBuffer] = Socket::soSendBuffer;
	}


	while ( enumerator->hasMoreElements() ) {
		Dictionary::pair element = enumerator->nextElement();
		if ( validOptionTypes.find( element.first ) == validOptionTypes.end() ) {
			result = false;
			break;	
		}
	}

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


bool Socket::pending() const
{
	peer_->select( Socket::SelectNoWait, NULL, NULL, NULL ); 

	return isReadable() || isWriteable();
}

}




namespace VCF {

InternetAddress::InternetAddress():
	peer_(NULL)
{
	peer_ = NetworkToolkit::createInetAddrPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	peer_->initAsLocalHost();
}

InternetAddress::InternetAddress( const String& host ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createInetAddrPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}
	peer_->initWithHostName(host);
}

InternetAddress::InternetAddress( const RawBytes& ipAddr ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createInetAddrPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}
	peer_->initWithIPAddr(ipAddr);
}

InternetAddress::InternetAddress( unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4 ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createInetAddrPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	RawBytes ipAddr(4);
	ipAddr[0] = b1;
	ipAddr[1] = b2;
	ipAddr[2] = b3;
	ipAddr[3] = b4;
	peer_->initWithIPAddr(ipAddr);
}

InternetAddress::InternetAddress( unsigned char* bytes, size_t bytesLength ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createInetAddrPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	if ( bytesLength < 4 ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid byte array, it's too short to represent an IP Address.") );
	}
	
	RawBytes ipAddr(4);
	ipAddr[0] = bytes[0];
	ipAddr[1] = bytes[1];
	ipAddr[2] = bytes[2];
	ipAddr[3] = bytes[3];
	peer_->initWithIPAddr(ipAddr);
}

InternetAddress::~InternetAddress()
{
	delete peer_;
}

InternetAddress::RawBytes InternetAddress::getAddressBytes()
{
	return peer_->getAddressBytes();
}

String InternetAddress::getHostName()
{
	return peer_->getHostName();
}

String InternetAddress::getHostAddress()
{
	return peer_->getHostAddress();
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


class ReadThread : public Thread {
public:
	virtual bool run() {
		return true;
	}
};


class ServerThread : public Thread {
public:
	virtual bool run() {

		Socket server;
		server.listen( 10032 );

		while ( canContinue() ) {
			Socket* client = server.accept();

			if ( NULL != client ) {
				AnsiString s = "Hello World!!!";
				client->getPeer()->send( (const unsigned char*) s.c_str(), s.size() );

				clients.push_back( client );
			}
		}

		return true;
	}
	SocketArray clients;
};



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	NetworkKit::init(  argc, argv );
	

	InternetAddress::RawBytes ip(4);
	ip[0] = 123;
	ip[1] = 168;
	ip[2] = 23;
	ip[3] = 103;

	InternetAddress addr(ip);

	InternetAddress addr2;

	InternetAddress addr3("www.google.com");

	InternetAddress::RawBytes ipBytes = addr.getAddressBytes();
	System::println( Format("%d.%d.%d.%d") % ipBytes[0] % ipBytes[1] % ipBytes[2] % ipBytes[3] ) ;

	System::println( Format("host address: %s") % addr.getHostAddress() );

	System::println( Format("host address: %s") % addr2.getHostAddress() );
	System::println( Format("host name: %s") % addr2.getHostName() );

	System::println( Format("host address: %s") % 	addr3.getHostAddress() );
	System::println( Format("host name: %s") % addr3.getHostName() );




	Socket server;
	Dictionary options;
	options[Socket::soBlocking] = false;
	server.setOptions( options );

	server.listen( 10032 );

	System::println( "Listening on port: " + StringUtils::toString(server.getPort()) );

	SocketArray clients;

	while (true ) {
		Socket* client = server.accept();
		if ( NULL != client ) {
			clients.push_back( client );
			client->setOptions( options );
			System::println( "Recv'd connect! From: " + client->getHostIPAddress() );
		}
		else {
			
			System::sleep( 100 );

			SocketArray readList = clients;	
			SocketArray writeList = clients;
			SocketArray errorList = clients;

			
			server.getPeer()->select( 100, &readList, &writeList, &errorList );

			uchar tmp[256];
			SocketArray::iterator it;
			for (it=readList.begin();it != readList.end(); it++ ) {
				Socket* s = *it;

				do {
					int err = s->getPeer()->recv( tmp, sizeof(tmp) );
					if ( err <= 0 ) {
						System::println( "Disconnect!" );
						
						clients.erase( std::find(clients.begin(),clients.end(),s) );
						break;
					}
					else {
						tmp[err] = 0;
						System::println( Format( "Recv'd %d bytes: %s\n") % err % tmp );
					}
				} while( s->pending() && s->isReadable() );

			}


		}

	}
	

	NetworkKit::terminate();

	FoundationKit::terminate();
	return 0;
}


