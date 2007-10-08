#ifndef _VCF_SOCKET_H__
#define _VCF_SOCKET_H__

//Socket.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_IPADDRESS_H__
	#include "vcf/NetworkKit/IPAddress.h"
#endif

namespace VCF {

	class Socket;
	class SocketPeer;
	class TCPSocket;



	/**
	\class SocketEvent Socket.h "vcf/NetworkKit/Socket.h"
	*/
	class NETWORKKIT_API SocketEvent : public Event {
	public:
		SocketEvent( Object* source, const unsigned long& eventType ) : 
		  Event(source,eventType),socket(NULL){

		}

		virtual Object* clone( bool deep=false ) {
			return new SocketEvent(*this);
		}

		Socket* socket;
	};


	typedef Delegate1<SocketEvent*> SocketEventDelegate; 



	typedef  std::vector<Socket*> SocketArray;

	/**
	\class Socket Socket.h "vcf/NetworkKit/Socket.h"
	*/
	class NETWORKKIT_API Socket : public Object {
	public:


		enum SocketType{
			/**
			Creates a standard stream based 
			socket peer used for TCP connections.
			*/
			stStream,

			/**
			Creates a stream based socket peer 
			used for TCP connections. This is different
			than the the stStream type in that it
			is specifically designed to support
			asynchronous IO. The implementation
			of this is platform dependant, assuming the 
			platform supports it at all. On Win32 systems
			this uses IO Completion ports under the hood
			to allow this to occur. This means that, at a 
			minimum, the application will have at 
			\em least one more thread running, and 
			possibly more than that depending on 
			the number of CPUs available.
			*/
			stStreamAsync,

			/**
			Creates a standard socket used for
			UDP connections.
			*/
			stDatagram,

			/**
			Creates a standard socket used for
			UDP connections. This is different
			than the the stDatagram type in that it
			is specifically designed to support
			asynchronous IO. The implementation
			of this is platform dependant, assuming the 
			platform supports it at all. On Win32 systems
			this uses IO Completion ports under the hood
			to allow this to occur. This means that, at a 
			minimum, the application will have at 
			\em least one more thread running, and 
			possibly more than that depending on 
			the number of CPUs available.
			*/
			stDatagramAsync
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
			ssListening	=	0x0020,
			ssOpen =		0x0100,
			ssClosed =		0x0000,
		};

		enum SocketEvents {			
			seClientConnected = 112491,
			seClientDisconnected,
			seReadyToRead,
			seReadyToWrite,
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
		Creates an unconnected socket of the 
		requested type.
		@param SocketType indicates the type of 
		socket to create. If the host operating 
		system doesn't support the requested type, 
		the underlying peer instance will be 
		NULL and an exception will be thrown
		by the constructor.

		@see SocketType
		*/
		Socket( const SocketType& socketType );
		

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


		//only applicable if the socket is 
		//listening.
		DELEGATE( SocketEventDelegate,ClientConnected );
		DELEGATE( SocketEventDelegate,ClientDisconnected );

		DELEGATE( EventDelegate,ReadyToRead );
		DELEGATE( EventDelegate,ReadyToWrite );


		/**
		Opens the socket for use and creates allocates any 
		neccessary OS resoruces for the socket (depending on 
		the peer implementation). If it was alread open, 
		then it is first closed and then opened. Once this 
		is called the socket's state will be set to 
		Socket::ssOpen.
		*/
		void open();

		/**
		Closes the socket and frees up any underlying OS resources
		that were allocated for the socket by the previous call
		to open().
		*/
		void close();

		/**
		Connects to a specified host and port. If the
		peer is unable to connect, then a SocketException 
		exception is thrown.
		
		@param String the host name to connect to. This may 
		a host name, like "google.com" or a valid IP address,
		such as "123.32.101.1".
		@param unsigned short port the port to connect to.
		*/
		void connect( const String& host, unsigned short port );

		/**
		This will start the socket listening on the 
		specified port. This can be called for either a 
		UDP or TCP socket, with the appropriate underlying
		calls to bind and/or listen made as neccessary.
		*/
		void listen( unsigned short port );

		/**
		Accepts a new connection and returns a new TCP socket
		instance. Assumes the listen() call has already occurred.
		If it has not then an exception is thrown by the underlying 
		peer implementation. This method will block until a socket
		connection has been detected unless the instance has been 
		set to non blocking. This is only valid when called by a 
		TCP socket.

		@return TCPSocket* a new instance of a TCPSocket. The caller
		of this method is responsible for the lifetime and clean up
		of this socket instance.

		@see soBlocking
		@see setOptions
		*/
		TCPSocket* accept();

		/**
		Sets the options for a socket. The options are stored as a 
		dictionary of items, with the keys being 1 or more values 
		represented by the Socket::soXXX const string variables. 
		The values are VariantData instances whose precise meaning
		depends on the key. For example, if you specify the 
		Socket::soBlocking key, then the value is bool, indicating 
		whether or not the socket should be set to blocking mode.
		
		@param Dictionary a dictionary of options with key/value
		pairs that specify various socket settings.

		@see Dictionary
		*/
		void setOptions( Dictionary& options );

		/**
		Returns a dictionary containing the current options for 
		the	socket.
		*/
		Dictionary getOptions();

		/**
		Returns the local ip address for this socket.
		*/
		IPAddress getLocalHostIPAddress();

		/**
		Returns the remote ip address that this socket is connected to.
		*/
		IPAddress getRemoteHostIPAddress();

		unsigned short getLocalPort();

		unsigned short getRemotePort();

		SocketPeer* getPeer() {
			return peer_;
		}	

		/**
		Returns the socket type. Can be one of the 
		SocketType enumeration values.

		@see SocketType
		*/
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

		bool isOpen() const {
			return (state_ & Socket::ssOpen) ? true : false;
		}

		bool isClosed() const {
			return (state_ == Socket::ssClosed) ? true : false;
		}

		/**
		Does a quick test to see if there is any readable or 
		writeable data available for the socket.
		@return bool returns true if the socket is marked for 
		writing or marked for reading. Otherwise returns false.
		*/
		bool pending() ;

		/**
		Do not call this method - for internal use 
		only.
		*/
		void internal_setErrorState( bool val ) {
			if ( val ) {
				state_ |= Socket::ssError;
			}
			else {
				state_ &= ~Socket::ssError;
			}
		}

		/**
		Do not call this method - for internal use 
		only.
		*/
		void internal_setReadable( bool val ) {
			if ( val ) {
				state_ |= Socket::ssReadable;
			}
			else {
				state_ &= ~Socket::ssReadable;
			}
		}

		/**
		Do not call this method - for internal use 
		only.
		*/
		void internal_setWriteable( bool val ) {
			if ( val ) {
				state_ |= Socket::ssWriteable;
			}
			else {
				state_ &= ~Socket::ssWriteable;
			}
		}

		/**
		Indicates whether the current operation would block.
		Assumes a non blocking socket. This is roughly equivalent
		to getting a an EWOULDBLOCK or WSAEWOULDBLOCK error number.

		@return bool True if the operation would block, otherwise
		false if it would not. 
		*/
		bool wouldOperationBlock();


		/**
		Perform a select, on this socket, for a specified timeout period,
		checking against some set of flags that will indicate whether or 
		not we should look for readable, writeable, or error states. 
		When this function returns, the socket's state may change 
		depending on the flags specified and the result of the 
		internal call to select. After returning you may call the 
		isReadable(), isWriteable(), or hasError() methods to determine
		the current state. For example:
		\code
		Socket s("foobar.com", 1234 );

		s.selectFor( 120, Socket::ssReadable );
		if ( s.isReadable() ) {
			//do something, such as reading data from the 
			//socket...
		}
		\endcode

		@param uint32 the maximum number of milliseconds to wait for. 
			@see Socket::SelectNoWait,
			@see Socket::SelectWaitForever
		@param uint flags these must be some combination of Socket::ssError, 
			Socket::ssReadable, or Socket::ssWriteable. If flags is 0, the 
			function will return immediately and do nothing.
		*/
		void selectFor( uint32 timeout, uint32 flags );
		
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
















	/**
	\class SocketPeer Socket.h "vcf/NetworkKit/Socket.h"
	An abstract class that represents a platform socket implementation.
	This needs to be implemented for each platform that the NetworkKit
	is portetd to. A typical implementation may use the BSD socket API 
	as a base implementation.
	*/
	class NETWORKKIT_API SocketPeer {
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
		virtual int create() = 0;

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
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int recvFrom( unsigned char* bytes, size_t bytesLength, IPEndPoint& fromAddr ) = 0;

		/**
		@return int Returns a 0 for success, otherwise 
		a negative number to indicate an error.
		*/
		virtual int sendTo( const unsigned char* bytes, size_t bytesLength, const IPEndPoint& toAddr ) = 0;

		/**
		Returns a handle for the OS specific socket resource. This 
		is typically a socket handle or descriptor, depending on the 
		OS and the underlying implementation.
		*/
		virtual OSHandleID getHandleID() = 0;

		/**
		Returns the IP address of the \em local host 
		as a string	formatted (for IPV4 at least) as 4 
		"octets", each separated by the "." character. 
		Each octet is a number string in the range from 
		0 to 255.
		*/
		virtual IPAddress getLocalHostIPAddress() = 0;

		/**
		Returns the IP address of the \em remote host 
		as a string	formatted (for IPV4 at least) as 4 
		"octets", each separated by the "." character. 
		Each octet is a number string in the range from 
		0 to 255.
		*/
		virtual IPAddress getRemoteHostIPAddress() = 0;

		/**
		Returns the local port number for this socket instance.
		*/
		virtual unsigned short getLocalPort() = 0;

		/**
		Returns the remote port number for this socket instance.
		*/
		virtual unsigned short getRemotePort() = 0;

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






	/**
	\class TCPSocket Socket.h "vcf/NetworkKit/Socket.h"
	A socket class that represents a TCP socket. Useful for 
	creating a TCP based client or server socket. A simple 
	example for a server might be something like this:
	\code
	TCPSocket server;
	server.listen( 1234 );

	while ( true ) {
		Socket* client = server.accept();

		{
			TCPSocketOutputStream sos( *client );
			unsigned char bytes[256];
			//put some data in the bytes variable...

			//write to the client socket
			sos.write( bytes, sizeof(bytes) );
		}

	}
	\endcode
	
	*/
	class NETWORKKIT_API TCPSocket : public Socket {
	public:
		/**
		Creates an unconnected socket 
		in stStream mode.
		*/
		TCPSocket();		

		/**
		Creates a bound and listening socket 
		in stStream mode.
		*/
		TCPSocket( unsigned short port );

		/**
		Creates a connected socket 
		in stStream mode. A connection is automatically
		made to the specified host and port.
		*/
		TCPSocket( const String& host, unsigned short port );

		virtual ~TCPSocket(){}

		friend class Socket;
	protected:
		/**
		Creates a socket from an existing peer
		intance. This is used primarily by the accept()
		method.
		*/
		TCPSocket( SocketPeer* peer ): Socket(peer){}
	};


	/**
	\class UDPSocket Socket.h "vcf/NetworkKit/Socket.h"
	*/
	class NETWORKKIT_API UDPSocket : public Socket {
	public:
		/**
		Creates an unconnected socket 
		in stDatagram mode.
		*/
		UDPSocket();		

		/**
		Creates a bound and listening socket 
		in stDatagram mode.
		*/
		UDPSocket( unsigned short port );

		/**
		Creates a connected socket 
		in stDatagram mode. A connection is automatically
		made to the specified host and port.
		*/
		UDPSocket( const String& host, unsigned short port );

		virtual ~UDPSocket(){}


		void connect();
	};









	/**
	\class TCPSocketInputStream Socket.h "vcf/NetworkKit/Socket.h"
	An input stream class used for reading data from a TCP socket. 
	The	class must be used in conjunction with a valid socket 
	instance, you cannot create in instance otherwise. Not all 
	of the InputStream class's methods can be implemented, for 
	example, the seek method is meaningless in this context, and 
	calling it will result in a RuntimeException being thrown. 
	The only method that makes sense to call is the read() method.

	\par
	An example of how to use the class might look like this:
	\code
	Socket* socket = \\get valid socket instance from somewhere...
	SocketInputStream sis(*socket);
	uchar tmp[256];
	uint64 err = sis.read( tmp, sizeof(tmp) );
	\endcode
	
	You might choose to use it in a loop, something like this:
	\code
	Socket* socket = \\get valid socket instance from somewhere...
	SocketInputStream sis(*socket);
	uchar tmp[256];
	while ( true ) {
		socket->selectFor( Socket::SelectWaitForever, Socket::ssReadable );

		do {			
			try {
				uint64 err = sis.read( tmp, sizeof(tmp) );

				if ( err == 0 ) {					
					break;
				}
				else {					
					//do something with the data stored in the 
					//tmp buffer...
				}
			}
			catch ( BasicException& ) {
				//exit the loop!
				break;
			}
		} while( socket->pending() && socket->isReadable() ) ;


		if ( socket->isClosed() || socket->hasError() ) {
			//exit the loop if we detect problems or the socket has
			//been closed...
			break;
		}
	}
	\endcode

	@see Socket::selectFor
	@see Socket::pending
	*/
	class NETWORKKIT_API TCPSocketInputStream  : public InputStream {
	public:

		TCPSocketInputStream( TCPSocket& socket );

		/**
		Seeking is not permitted!
		*/
		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			//no-op
			throw NetworkException( "You cannot seek in a Socket Input stream" );
		}

		virtual uint64 getSize() {
			return totalBytesRecvd_;
		}

		/**
		Throws an exception - this is not permitted
		*/
		virtual char* getBuffer() {
			throw RuntimeException( "You cannot access the buffer pointer in a Socket Input stream" );
			return NULL;
		}

		
		/**
		Throws an exception - this is not permitted
		*/
		virtual uint64 getCurrentSeekPos() {
			throw RuntimeException( "You cannot access the seek position in a Socket Input stream" );
			return 0;	
		}

		virtual bool isEOS() {
			return false;
		}

		/**
		Attempts to read sizeOfBytes from the TCP socket 
		associated with this stream. The method will return 
		the number of bytes	read from the socket. The 
		return may be the following:
		\li A number greater than 0 but less than sizeOfBytes 
		that indicates the number of bytes successfully read 
		from the socket.
		\li 0 which may indicate a disconnect has happened and 
		no bytes were read. If the socket is marked as non-blocking 
		then the method will return 0 bytes, but the sockets 
		Socket::wouldOperationBlock() method will return true. 
		This indicates that the read operation will be completable
		in the future. If the socket is a blocking socket, then 
		this is probably a disconnect.
		\li If the socket's peer reports an error in reading  
		from the socket, then the method will throw a NetworkException.
		*/
		virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

	protected:
		uint64 totalBytesRecvd_;
		Socket* socket_;
	};



	/**
	\class TCPSocketOutputStream Socket.h "vcf/NetworkKit/Socket.h"
	An output stream class used for writing data to a TCP socket. 
	The	class must be used in conjunction with a valid socket 
	instance, you cannot create in instance otherwise. Not all 
	of the OutputStream class's methods can be implemented, for 
	example, the seek method is meaningless in this context, and 
	calling it will result in a RuntimeException being thrown. 
	The only method that makes sense to call is the write() method.
	*/
	class NETWORKKIT_API TCPSocketOutputStream  : public OutputStream {
	public:

		TCPSocketOutputStream( TCPSocket& socket );

		/**
		Seeking is not permitted!
		*/
		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			//no-op
			throw RuntimeException( "You cannot seek in a Socket Output stream" );
		}

		virtual uint64 getSize() {
			return totalBytesWritten_;
		}

		/**
		Returns NULL - this is not permitted
		*/
		virtual char* getBuffer() {
			throw RuntimeException( "You cannot access the buffer pointer in a Socket Output stream" );
			return NULL;
		}

		
		virtual uint64 getCurrentSeekPos() {
			throw RuntimeException( "You cannot access the seek position in a Socket Output stream" );
			return 0;	
		}

		/**
		Attempts to write sizeOfBytes to the TCP socket associated 
		with this stream. The method will return the number of bytes
		written to the socket. The return value may be the following:
		\li A number greater than 0 but less than sizeOfBytes that 
		indicates the number of bytes successfully written to
		the socket
		\li 0 which may indicate a disconnect has happened and 
		no bytes were written. If the socket is marked as non-blocking 
		then the method will return 0 bytes, but the sockets 
		Socket::wouldOperationBlock() method will return true. 
		If the socket is a blocking socket, then this is probably
		an error.
		\li If the socket's peer reports an error in writing to 
		the socket, then the method will throw a NetworkException.
		*/
		virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes );

	protected:
		uint64 totalBytesWritten_;
		Socket* socket_;
	};



	/**
	\class UDPSocketInputStream Socket.h "vcf/NetworkKit/Socket.h"
	An input stream class used for reading data from a UDP socket. The
	class must be used in conjunction with a valid socket instance,
	you cannot create in instance otherwise. Not all of the InputStream
	class's methods can be implemented, for example, the seek method is 
	meaningless in this context, and calling it will result in 
	a NetworkException being thrown. The only method that makes sense 
	to call is the read() method.	
	*/
	class NETWORKKIT_API UDPSocketInputStream  : public InputStream {
	public:

		UDPSocketInputStream( UDPSocket& socket, const IPEndPoint& readFrom );

		/**
		Seeking is not permitted!
		*/
		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			//no-op
			throw NetworkException( "You cannot seek in a Socket Input stream" );
		}

		virtual uint64 getSize() {
			return totalBytesRecvd_;
		}

		/**
		Returns NULL - this is not permitted
		*/
		virtual char* getBuffer() {
			throw NetworkException( "You cannot access the buffer pointer in a Socket Input stream" );
			return NULL;
		}

		
		virtual uint64 getCurrentSeekPos() {
			throw NetworkException( "You cannot access the seek position in a Socket Input stream" );
			return 0;	
		}

		virtual bool isEOS() {
			return false;
		}

		/**
		Attempts to read sizeOfBytes from the UDP socket associated 
		with this stream. The method will return the number of bytes
		read from the socket. The return may be the following:
		\li A number greater than 0 but less than sizeOfBytes that 
		indicates the number of bytes successfully read from
		the socket
		\li 0 which may indicate a disconnect has happened and 
		no bytes were read. If the socket is marked as non-blocking 
		then the method will return 0 bytes, but the sockets 
		Socket::wouldOperationBlock() method will return true. This 
		indicates that the read operation will be completable
		in the future.
		If the socket is a blocking socket, then this is probably
		a disconnect.
		\li If the socket's peer reports an error in reading  
		from the socket, then the method will throw a NetworkException.
		*/
		virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes );

		/**
		Reads from the specified end point.
		*/
		uint64 readFrom( unsigned char* bytesToRead, uint64 sizeOfBytes, IPEndPoint& from );
	protected:
		uint64 totalBytesRecvd_;
		Socket* socket_;
		IPEndPoint readFrom_;
	};



	/**
	\class UDPSocketOutputStream Socket.h "vcf/NetworkKit/Socket.h"
	*/
	class NETWORKKIT_API UDPSocketOutputStream  : public OutputStream {
	public:

		UDPSocketOutputStream( UDPSocket& socket, const IPEndPoint& sendTo );

		/**
		Seeking is not permitted!
		*/
		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			//no-op
			throw NetworkException( "You cannot seek in a Socket Output stream" );
		}

		virtual uint64 getSize() {
			return totalBytesWritten_;
		}

		/**
		Returns NULL - this is not permitted
		*/
		virtual char* getBuffer() {
			throw NetworkException( "You cannot access the buffer pointer in a Socket Output stream" );
			return NULL;
		}

		
		virtual uint64 getCurrentSeekPos() {
			throw NetworkException( "You cannot access the seek position in a Socket Output stream" );
			return 0;	
		}

		/**
		Attempts to write sizeOfBytes to the socket associated 
		with this stream. The method will return the number of bytes
		written to the socket. The return value may be the following:
		\li A number greater than 0 but less than sizeOfBytes that 
		indicates the number of bytes successfully written to
		the socket
		\li 0 which may indicate a disconnect has happened and 
		no bytes were written. If the socket is marked as non-blocking 
		then the method will return 0 bytes, but the sockets 
		Socket::wouldOperationBlock() method will return true. 
		If the socket is a blocking socket, then this is probably
		an error.
		\li If the socket's peer reports an error in writing to 
		the socket, then the method will throw a NetworkException.
		*/
		virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes );

		uint64 writeTo( const unsigned char* bytesToWrite, uint64 sizeOfBytes, const IPEndPoint& to );
	protected:
		uint64 totalBytesWritten_;
		Socket* socket_;
		IPEndPoint sendTo_;
	};
};



#endif //_VCF_SOCKET_H__