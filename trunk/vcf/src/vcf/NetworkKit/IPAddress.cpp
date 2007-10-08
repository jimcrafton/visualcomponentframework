//IPAddress.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/IPAddress.h"
#include "vcf/NetworkKit/IPAddressPeer.h"
#include "vcf/NetworkKit/NetworkToolkit.h"



using namespace VCF;


IPAddress::IPAddress():
	peer_(NULL)
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	peer_->initAsLocalHost();
}

IPAddress::IPAddress( const String& host ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}
	peer_->initWithHostName(host);
}

IPAddress::IPAddress( const RawBytes& ipAddr ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}
	peer_->initWithIPAddr(ipAddr);
}

IPAddress::IPAddress( unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4 ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	RawBytes ipAddr(4);
	ipAddr[0] = b1;
	ipAddr[1] = b2;
	ipAddr[2] = b3;
	ipAddr[3] = b4;
	peer_->initWithIPAddr(ipAddr);
}

IPAddress::IPAddress( unsigned char* bytes, size_t bytesLength ):
	peer_(NULL)
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	if ( bytesLength < 4 ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid byte array, it's too short to represent an IP Address.") );
	}
	
	RawBytes ipAddr(4);
	ipAddr[0] = bytes[0];
	ipAddr[1] = bytes[1];
	ipAddr[2] = bytes[2];
	ipAddr[3] = bytes[3];
	peer_->initWithIPAddr(ipAddr);
}

IPAddress::IPAddress( const IPAddress& ipAddress )
{
	peer_ = NetworkToolkit::createIPAddressPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create Inet Address peer.") );
	}

	peer_->initWithIPAddrPeer( ipAddress.peer_ );
}

IPAddress::~IPAddress()
{
	delete peer_;
}

IPAddress::RawBytes IPAddress::getAddressBytes() const
{
	return peer_->getAddressBytes();
}

String IPAddress::getHostName() const
{
	return peer_->getHostName();
}

String IPAddress::getHostAddress() const
{
	return peer_->getHostAddress();
}


std::vector<IPAddress> IPAddress::getDNSHostAddresses( const String& host )
{
	std::vector<IPAddress> result;

	IPAddressPeer* peer = NetworkToolkit::createIPAddressPeer();

	result = peer->getDNSHostAddresses( host );

	delete peer;

	return result;
}



IPEndPoint& IPEndPoint::operator= (const IPEndPoint& rhs )
{
	peer_->initWithIPAddrPeer( rhs.peer_ );
	port_ = rhs.port_;
	return *this;
}