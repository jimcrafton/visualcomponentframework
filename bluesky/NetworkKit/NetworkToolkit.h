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


	class NETWORKKIT_API NetworkToolkit {
	public:
		static void create();
		static void destroy();


		static SocketPeer* createSocketPeer();
		static IPAddressPeer* createIPAddressPeer();
		

	protected:

		NetworkToolkit(){};
		virtual ~NetworkToolkit(){};
			
		static NetworkToolkit* Instance;

		virtual SocketPeer* internal_createSocketPeer() = 0;
		virtual IPAddressPeer* internal_createIPAddressPeer() = 0;
	};

};



#endif //_VCF_NETWORKTOOLKIT_H__


