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


#include "vcf/NetworkKit/NetworkKitSelectLib.h"
#include "vcf/NetworkKit/SocketEvent.h"


namespace VCFNet
{

//common socket errors
#define VCFNET_STARTUP_FAILED		-1
#define VCFNET_CANT_OPEN_SOCKET		-2
#define VCFNET_HOSTNAME_ERROR		-3
#define VCFNET_CONNECT_ERROR		-4
#define VCFNET_CONNECT_SUCCESS		-5
#define VCFNET_BIND_FAILED			-6
#define VCFNET_SERVER_STARTED		-7
#define VCFNET_NOHOST				""
#define VCFNET_NOPORT				-1

#define VCFNET_INFINITEWAIT			-1
#define VCFNET_ASYNCHRONOUSWAIT		-2

enum SocketState{
	SOCKET_CLOSED_ERROR=0,
	SOCKET_READ_ERROR,
	SOCKET_WRITE_ERROR,
	SOCKET_OPEN_ERROR,
	SOCKET_NAME_ERROR,
	SOCKET_CREATE_ERROR,
	SOCKET_CONNECT_ERROR,
	SOCKET_WRITING,
	SOCKET_READING,
	SOCKET_CONNECTED,
	SOCKET_LISTENING,
	SOCKET_CANT_OPEN_SOCKET,
	SOCKET_HOSTNAME_ERROR,
	SOCKET_CLOSED,
	SOCKET_ALREADY_LISTENING_ERROR,
	SOCKET_BIND_FAILED
};

static VCF::String SocketStateNames[] ={"SOCKET_CLOSED_ERROR" ,
                            "SOCKET_READ_ERROR",
							"SOCKET_WRITE_ERROR",
							"SOCKET_OPEN_ERROR",
							"SOCKET_NAME_ERROR",
							"SOCKET_CREATE_ERROR",
							"SOCKET_CONNECT_ERROR",
							"SOCKET_WRITING",
							"SOCKET_READING",
							"SOCKET_CONNECTED",
							"SOCKET_LISTENING",
							"SOCKET_CANT_OPEN_SOCKET",
							"SOCKET_HOSTNAME_ERROR",
							"SOCKET_CLOSED",
							"SOCKET_ALREADY_LISTENING_ERROR",
							"SOCKET_BIND_FAILED" };

#define VCFNET_MAX_SOCKET_SIZE		512

class SocketPeer;

class SocketListeningLoop;

/**
*Socket Object represents a connected client to the listening socket.
*On Win32 the socketID_ represents a handle to a SOCKET structure
*this object is usually returns via a call to Socket::getClient()
*/
class NETKIT_API SocketObject {
public:
	SocketObject( const int& id=0 ) {
		socketID_ = id;
	}

	virtual ~SocketObject(){};

	int socketID_;
};

class NETKIT_API Socket : public VCF::Object
{
public:
	Socket( const int& port=0, const bool& startAsServer=false );

	Socket( const VCF::String& host, const int& port, const bool& startAsServer=false );

	Socket( const int& socketPeerID, const VCF::String& host, const int& port );

	virtual ~Socket();

	int getPort(){
		return port_;
	}

	void setPort( const int& port );

	VCF::String getHost(){
		return host_;
	}

	void setHost( const VCF::String& host );

	int send( const char* bytes, const int& size );

	SocketState startListening();

	SocketState stopListening();

	void init();

	SocketState getState(){
		return state_;
	}

	void setState( const SocketState& state )	{
		state_ = state;
	}

	virtual VCF::String toString();

	bool hasWaitingClients();

	Socket* getClient();

	/**
	*checks if there is any data for the socket
	*@param int waitAndBlock repesents the number of
	*milliseconds to wait and block for data. The default
	*value for this is VCFNET_ASYNCHRONOUSWAIT, which is
	*/
	void checkForPendingData( const int& waitAndBlock=VCFNET_ASYNCHRONOUSWAIT );

	bool isServer() {
		return isServer_;
	}

	void setAsServer( const bool& isServer ) {
		isServer_ = isServer;
	}

	DELEGATE(SocketDelegate,DataReceived)
	DELEGATE(SocketDelegate,ClientConnected)
	DELEGATE(SocketDelegate,ClientDisconnected)

	SocketPeer* getSocketPeer() {
		return socketPeer_;
	}

	// By Ning Ke: to set the listeningThread_ to an actual instance of
	// SocketListeningLoop. Application programmers can subclass
	// SocketListeningLoop to implement what happens when events
	// are fired.
	void setListeningLoop(SocketListeningLoop *);

protected:
	VCF::String host_;
	int port_;
protected:
	bool isServer_;
	SocketPeer* socketPeer_;
	SocketState state_;
	SocketListeningLoop* listeningThread_;
};

};


#endif // _VCF_SOCKET_H__

/**
$Id$
*/
