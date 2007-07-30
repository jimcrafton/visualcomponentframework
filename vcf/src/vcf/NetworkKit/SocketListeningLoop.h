#ifndef _VCF_SOCKETLISTENINGLOOP_H__
#define _VCF_SOCKETLISTENINGLOOP_H__
//SocketListeningLoop.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFNet {

class Socket;

class SocketAdapter;

class SocketEvent;

class NETKIT_API SocketListeningLoop : public VCF::Thread {

public:
	SocketListeningLoop( Socket* socket );

	virtual ~SocketListeningLoop();

	virtual bool run();

	virtual void onDataReceived( SocketEvent* event );

	virtual void onClientConnected( SocketEvent* event );

	virtual void onClientDisconnected( SocketEvent* event );
private:
	Socket* socket_;
	bool socketIsServer_;
	bool serverClientConnected_;
	VCF::CallBack* socketDataReceivedHandler_;
	VCF::CallBack* socketClientConnectedHandler_;
	VCF::CallBack* socketClientDisconnectedHandler_;
};

}; //end of namespace VCFNet


#endif // _VCF_SOCKETLISTENINGLOOP_H__

/**
$Id$
*/
