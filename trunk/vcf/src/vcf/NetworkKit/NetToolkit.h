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
*Revision 1.9.8.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.10.1  2003/03/23 03:23:52  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.12.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_NETTOOLKIT_H__


