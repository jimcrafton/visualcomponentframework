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
	VCF::EventHandler* socketDataReceivedHandler_;
	VCF::EventHandler* socketClientConnectedHandler_;
	VCF::EventHandler* socketClientDisconnectedHandler_;
};

}; //end of namespace VCFNet


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
*Revision 1.10.8.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:11:47  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/22 17:32:31  zzack
*changed to new include style
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SOCKETLISTENINGLOOP_H__


