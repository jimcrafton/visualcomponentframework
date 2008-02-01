////TCPClient.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"
#include "vcf/FoundationKit/Dictionary.h"

using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	NetworkKit::init(  argc, argv );

	try {		
		TCPSocket client;
		client.connect( "localhost", 34251 );

		DateTime date = DateTime::now();
		AnsiString theTime = StringUtils::format( date, "%Y-%m-%d %H:%M:%S" );

		IPAddress addr = client.getRemoteHostIPAddress();

		System::println( Format("sending {%s} to %s on port %d") %
								theTime.c_str() %
								addr.getHostAddress() %
								client.getRemotePort() );

		TCPSocketOutputStream sos( client );
		sos.write( (const unsigned char*)theTime.c_str(), theTime.size() );

	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}

	NetworkKit::terminate();
	FoundationKit::terminate();
	return 0;
}

