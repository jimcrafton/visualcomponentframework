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


		void open();

		void close();

		void connect( const String& host, unsigned short port );

		void listen( unsigned short port );

		Socket* accept();

		void setOptions( Dictionary& options );

		Dictionary getOptions();

		IPAddress getLocalHostIPAddress();

		IPAddress getRemoteHostIPAddress();

		unsigned short getLocalPort();

		unsigned short getRemotePort();

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

		bool isOpen() const {
			return (state_ & Socket::ssOpen) ? true : false;
		}

		bool isClosed() const {
			return (state_ == Socket::ssClosed) ? true : false;
		}

		bool pending() const;

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
		perform a select, on this socket, for a specified timeout period,
		checking against some set of flags that will indicate to check for 
		readable, writeable, or error states.
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
	An input stream class used for reading data from a socket. The
	class must be used in conjunction with a valid socket instance,
	you cannot create in instance otherwise. Not all of the InputStream
	class's methods can be implemented, for example, the seek method is 
	meaningless in this context, and calling it will result in 
	a NetworkException being thrown. The only method that makes sense 
	to call is the read() method.
	*/
	class NETWORKKIT_API SocketInputStream  : public InputStream {
	public:

		SocketInputStream( Socket& socket );

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
		Attempts to read sizeOfBytes from the socket associated 
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

	protected:
		uint64 totalBytesRecvd_;
		Socket* socket_;
	};



	class NETWORKKIT_API SocketOutputStream  : public OutputStream {
	public:

		SocketOutputStream( Socket& socket );

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

	protected:
		uint64 totalBytesWritten_;
		Socket* socket_;
	};








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
	};


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
	};
};



#endif //_VCF_SOCKET_H__