//NetToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifdef WIN32 //this is a hack - this will be removed when we redo sockets
			 //and add this to teh toolkit
	#include <winsock2.h>
#endif
#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkKitPrivate.h"

using namespace VCF;
using namespace VCFNet;


NetToolkit NetToolkit::netToolkitInstance;

NetToolkit::NetToolkit()
{

}

NetToolkit::~NetToolkit()
{

}

NetToolkit* NetToolkit::getDefaultNetToolkit()
{
	return &NetToolkit::netToolkitInstance;
}

SocketPeer* NetToolkit::createSocketPeer( Socket* socket, const VCF::String& host, const int& port )
{
#ifdef WIN32
	return new Win32SocketPeer( socket, host, port );
#else
	return NULL;
#endif
}

VCF::String NetToolkit::getLocalMachineName()
{
	VCF::String result = "";
#ifdef WIN32
	result = Win32SocketPeer::getLocalMachineName();
#endif

	return result;
}

SocketPeer* NetToolkit::createSocketPeer( Socket* socket, const int& socketPeerID, const VCF::String& host, const int& port )
{
#ifdef WIN32
	return new Win32SocketPeer( socket, socketPeerID, host, port );
#else
	return NULL;
#endif
}

VCF::uint32 NetToolkit::getLocalIPAddress()
{
	return 0;
}


/**
$Id$
*/
