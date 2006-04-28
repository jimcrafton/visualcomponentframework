#ifndef _VCF_NETTOOLKIT_H__
#define _VCF_NETTOOLKIT_H__
//NetToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/NetworkKit/NetworkKitSelectLib.h"


namespace VCFNet
{

class Socket;

class SocketPeer;

class NETKIT_API NetToolkit : public VCF::Object
{
public:
	NetToolkit();
	virtual ~NetToolkit();

	static NetToolkit* getDefaultNetToolkit();

	VCF::String getLocalMachineName();

	VCF::uint32 getLocalIPAddress();

	virtual SocketPeer* createSocketPeer( Socket* socket, const VCF::String& host, const int& port );

	virtual SocketPeer* createSocketPeer( Socket* socket, const int& socketPeerID, const VCF::String& host, const int& port );
protected:
	static NetToolkit netToolkitInstance;
};


};


#endif // _VCF_NETTOOLKIT_H__

/**
$Id$
*/
