#ifndef _VCF_WIN32IPADDRESSPEER_H__
#define _VCF_WIN32IPADDRESSPEER_H__

//Win32IPAddressPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "IPAddress.h"
#include "IPAddressPeer.h"

namespace VCF {

	class NETWORKKIT_API Win32IPAddressPeer : public IPAddressPeer {
	public:
		Win32IPAddressPeer();
		virtual ~Win32IPAddressPeer();

		virtual void initWithHostName( const String& host );
		virtual void initWithIPAddr( const IPAddress::RawBytes& ipAddr );
		virtual void initWithIPAddrPeer( IPAddressPeer* peer );
		virtual void initAsLocalHost();


		virtual IPAddress::RawBytes getAddressBytes();
		virtual String getHostName();
		virtual String getHostAddress();
		virtual bool isIPV4();
		virtual bool isIPV6();

		virtual  std::vector<IPAddress> getDNSHostAddresses( const String& host );
	protected:
		AnsiString ipAddress_;
		AnsiString host_;
		
	};

};


#endif //_VCF_WIN32IPADDRESSPEER_H__

