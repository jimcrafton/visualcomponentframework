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


#endif // _VCF_SOCKETLISTENER_H__

/**
$Id$
*/
