#ifndef _VCF_DATAGRAMSOCKET_H__
#define _VCF_DATAGRAMSOCKET_H__
//DatagramSocket.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
* DatagramSocket is a thin wrapper around the socket using
* connectionless oriented protocol.
* -- by Ning Ke
*/


namespace VCFNet
{

class NETKIT_API DatagramSocketPeer
{
public:
	virtual ~DatagramSocketPeer() {};
	virtual int setRemoteHost(const VCF::String &, const int &) = 0;
	virtual int send(const char *, const int &) = 0;
	virtual int recv(char *, int &) = 0;
	virtual VCF::String getRemoteHostName() = 0;
	virtual int getRemoteHostPort() = 0;
};


class NETKIT_API DatagramSocket : public VCF::Object {
public:
	DatagramSocket();
	DatagramSocket(const int &);
	DatagramSocket(const VCF::String &, const int &);
	virtual ~DatagramSocket();
	// Sender must set remote address before it can send data.
	int setRemoteHost(const VCF::String &, const int &);
	int send(const char *, const int &);
	int recv(char *, int &);
	// returns the name and port of the local socket's address.
	VCF::String getLocalHostName() ;
	int getLocalHostPort() ;
	// return the name and port of the address the socket is connected to.
	VCF::String getRemoteHostName() ;
	int getRemoteHostPort() ;
	bool isInitialized(int &);
	bool isInitialized(VCF::String &);

protected:
	int port_;
	VCF::String host_;
	DatagramSocketPeer *peer_;
};
};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:45  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/10 19:09:55  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_DATAGRAMSOCKET_H__


