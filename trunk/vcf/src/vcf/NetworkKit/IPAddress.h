
#ifndef _VCF_IPADDRESS_H__
#define _VCF_IPADDRESS_H__

//IPAddress.h

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

		IPAddress( const IPAddress& ipAddress );

		virtual ~IPAddress();

		RawBytes getAddressBytes() const ;
		String getHostName() const ;
		String getHostAddress() const;

		static std::vector<IPAddress> getDNSHostAddresses( const String& host );
	protected:
		IPAddressPeer* peer_;
	};


	class NETWORKKIT_API IPEndPoint : public IPAddress {
	public:
		IPEndPoint(): IPAddress(),port_(0) {}

		IPEndPoint( const String& host ): IPAddress(host),port_(0){}
		IPEndPoint( const RawBytes& ipAddr ): IPAddress(ipAddr),port_(0){}

		IPEndPoint( const String& host, unsigned short port ): IPAddress(host),port_(port){}
		IPEndPoint( const RawBytes& ipAddr, unsigned short port ): IPAddress(ipAddr),port_(port){}

		IPEndPoint( const IPAddress& ipAddress ): IPAddress(ipAddress),port_(0){}

		IPEndPoint& operator= (const IPEndPoint& rhs );

		unsigned short getPort() const {
			return port_;
		}

	protected:
		unsigned short port_;
	};

};

#endif //_VCF_IPADDRESS_H__

