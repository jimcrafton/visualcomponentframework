#ifndef _VCF_SOCKETPEER_H__
#define _VCF_SOCKETPEER_H__
//SocketPeer.h

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

class Socket;

class NETKIT_API SocketPeer {
public:
	virtual ~SocketPeer(){};

	virtual SocketState startListening() = 0;

	virtual int send( const char* bytes, const int& size ) = 0;

	virtual SocketState stopListening() = 0;

	virtual void setPort( const int& port ) = 0;

	virtual int getPort() = 0;

	virtual void setHost( const VCF::String& host ) = 0;

	virtual VCF::String getHost() = 0;

	virtual bool hasWaitingClients() = 0;

	virtual Socket* getClient() = 0;

	virtual void checkForPendingData( const int& waitAndBlock ) = 0;

	virtual int getSocketPeerID() = 0;
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
*Revision 1.7.10.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SOCKETPEER_H__


