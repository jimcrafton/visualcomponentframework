#ifndef _VCF_SOCKETEVENT_H__
#define _VCF_SOCKETEVENT_H__
//SocketEvent.h

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

class NETKIT_API SocketEvent : public VCF::Event {

public:
	SocketEvent( VCF::Object * source, Socket* sender,
		char* data=NULL, const int& dataSize=0 );

	virtual ~SocketEvent();

	char* getSocketData() {
		return data_;
	}

	int getDataSize() {
		return dataSize_;
	}

	Socket* getSender() {
		return sender_;
	}
protected:

	char* data_;
	int dataSize_;
	Socket* sender_;
};

}; //end of namespace VCFNet


#endif // _VCF_SOCKETEVENT_H__

/**
$Id$
*/
