
#ifndef _VCF_IPADDRESS_H__
#define _VCF_IPADDRESS_H__

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


	class IPAddressPeer;

	
	
	class NETWORKKIT_API IPAddress : public Object {
	public:
		typedef std::vector<unsigned char>	RawBytes;

		IPAddress();
		IPAddress( const String& host );
		IPAddress( const RawBytes& ipAddr );		
		IPAddress( unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4 );		
		IPAddress( unsigned char* bytes, size_t bytesLength );	
		virtual ~IPAddress();

		RawBytes getAddressBytes();
		String getHostName();
		String getHostAddress();
	protected:
		IPAddressPeer* peer_;
	};



};

#endif //_VCF_IPADDRESS_H__

