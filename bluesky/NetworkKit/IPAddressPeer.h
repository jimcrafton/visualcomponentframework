#ifndef _VCF_IPADDRESSPEER_H__
#define _VCF_IPADDRESSPEER_H__

//IPAddressPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


	class NETWORKKIT_API IPAddressPeer {
	public:

		virtual ~IPAddressPeer(){}

		virtual void initWithHostName( const String& host ) = 0;
		virtual void initWithIPAddr( const IPAddress::RawBytes& ipAddr ) = 0;
		virtual void initAsLocalHost() = 0;


		virtual IPAddress::RawBytes getAddressBytes() = 0;
		virtual String getHostName() = 0;
		virtual String getHostAddress() = 0;
		virtual bool isIPV4() = 0;
		virtual bool isIPV6() = 0;
	};

};


#endif //_VCF_IPADDRESSPEER_H__
