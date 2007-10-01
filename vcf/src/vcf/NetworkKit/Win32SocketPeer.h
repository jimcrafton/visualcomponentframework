
#ifndef _VCF_WIN32SOCKETPEER_H__
#define _VCF_WIN32SOCKETPEER_H__

//IPAddressPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF {


	class NETWORKKIT_API Win32SocketPeer : public SocketPeer {
	public:	

		Win32SocketPeer();

		Win32SocketPeer( SOCKET handle );

		virtual void setPeerOwner( Socket* socket ) {
			socket_ = socket;
		}

		virtual int create();

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



	class NETWORKKIT_API Win32UDPSocketPeer : public Win32SocketPeer {
	public:	

		Win32UDPSocketPeer();

		Win32UDPSocketPeer( SOCKET handle );

		virtual int create();

		virtual int connect( const String& host, const unsigned short port );

		virtual int listen( unsigned short port );

		virtual SocketPeer* accept();

		virtual int recv( unsigned char* bytes, size_t bytesLength );

		virtual int send( const unsigned char* bytes, size_t bytesLength );

	protected:
		struct sockaddr_in remoteAddr_;
	};
};

#endif //_VCF_WIN32SOCKETPEER_H__

