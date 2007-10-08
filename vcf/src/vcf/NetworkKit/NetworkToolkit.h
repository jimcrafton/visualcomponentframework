#ifndef _VCF_NETWORKTOOLKIT_H__
#define _VCF_NETWORKTOOLKIT_H__

//NetworkToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

	class SocketPeer;
	class IPAddressPeer;


	/**
	\class NetworkToolkit NetworkToolkit.h "vcf/NetworkKit/NetworkToolkit.h"
	*/
	class NETWORKKIT_API NetworkToolkit {
	public:
		static void create();
		static void destroy();


		/**		
		Creates a new OS specific SocketPeer instance. 

		\par
		The caller specifies the socket type, which can
		be either a streaming type (i.e. a socket appropriate
		for TCP/IP streaming communication), or a datagram
		type (i.e. a socket appropriate
		for UPD communication )

		@param int socketType indicates the type of socket

		@return SocketPeer Returns a new SocketPeer instance 
		appropriate for the platform and the specified socket type.
		*/
		static SocketPeer* createSocketPeer( int socketType );
		static IPAddressPeer* createIPAddressPeer();
		

		static int getLastError();
	protected:

		NetworkToolkit(){};
		virtual ~NetworkToolkit(){};
			
		static NetworkToolkit* Instance;

		virtual SocketPeer* internal_createSocketPeer( int socketType ) = 0;
		virtual IPAddressPeer* internal_createIPAddressPeer() = 0;
		virtual int internal_getLastError() = 0;
	};

};



#endif //_VCF_NETWORKTOOLKIT_H__


