#ifndef _VCF_WIN32SOCKETPEER_H__
#define _VCF_WIN32SOCKETPEER_H__
//Win32SocketPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFNet
{

class SocketObject;

class Socket;

#define MAX_PENDING_CONNECTS SOMAXCONN

class Win32SocketPeer : public SocketPeer {
public:
	Win32SocketPeer( Socket* socket, const VCF::String& host, const int& port );

	Win32SocketPeer( Socket* socket, const int& socketPeerID, const VCF::String& host, const int& port );

	virtual ~Win32SocketPeer();

	virtual SocketState startListening();

	virtual int send( const char* bytes, const int& size );


	virtual SocketState stopListening();

	virtual void setPort( const int& port );

	virtual int getPort();

	virtual void setHost( const VCF::String& host );

	virtual VCF::String getHost();

	static void startup();

	SocketState connectTo( const VCF::String& hostName, const int& port );

	virtual bool hasWaitingClients();

	virtual Socket* getClient();

	virtual void checkForPendingData( const int& waitAndBlock );

	virtual int getSocketPeerID();

	static VCF::String getLocalMachineName();
protected:
	void readDataFromClient( Socket* client, fd_set* readfd );
private:
	struct sockaddr_in sin_;
	std::vector<Socket*> connectedClients_;
	std::vector<Socket*> disconnectedClients_;
	Socket* socket_;
	VCF::String host_;
	int port_;
	SOCKET  sock_;
	static bool WinSockStarted;
};


};


#endif // _VCF_WIN32SOCKETPEER_H__

/**
$Id$
*/
