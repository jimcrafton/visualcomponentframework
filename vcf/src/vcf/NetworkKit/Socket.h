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
#include "vcf/NetworkKit/SocketListener.h"
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

	DELEGATE(DataReceived)
	DELEGATE(ClientConnected)
	DELEGATE(ClientDisconnected)

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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:48  ddiego
*migration towards new directory structure
*
*Revision 1.13.8.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.2.1  2003/03/12 03:11:47  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.10.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.10  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SOCKET_H__


