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
*Revision 1.11  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.8.1  2003/01/08 00:20:02  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/09/12 03:26:07  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.8  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


