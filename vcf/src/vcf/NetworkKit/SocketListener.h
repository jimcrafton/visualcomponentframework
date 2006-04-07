#ifndef _VCF_SOCKETLISTENER_H__
#define _VCF_SOCKETLISTENER_H__
//SocketListener.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFNet {

class SocketEvent;

/**
*SocketEventHandler
*handles:
*onDataReceived
*onClientConnected
*onClientDisconnected
*/

template <class SOURCE_TYPE> class SocketEventHandler : public VCF::EventHandlerInstance<SOURCE_TYPE,SocketEvent> {
public:

	SocketEventHandler( SOURCE_TYPE* source,
		_typename_ VCF::EventHandlerInstance<SOURCE_TYPE,SocketEvent>::OnEventHandlerMethod handlerMethod,
		const VCF::String& handlerName="") :
			VCF::EventHandlerInstance<SOURCE_TYPE,SocketEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~SocketEventHandler(){};

};



}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:46  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/12/28 02:50:41  dougtinkham
*_typename_ added in template for MinGW to build
*
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:48  ddiego
*migration towards new directory structure
*
*Revision 1.6.10.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SOCKETLISTENER_H__


