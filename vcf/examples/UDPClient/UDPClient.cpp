////UDPClient.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"

using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	NetworkKit::init(  argc, argv );

	try {		
		UDPSocket s;
		s.connect();
		
		IPEndPoint to("localhost",34251);
		int i = 0;
		s.getPeer()->sendTo( (const unsigned char*)&i, sizeof(i), to );

		s.selectFor( Socket::SelectWaitForever, Socket::ssReadable );
		IPEndPoint from;
		unsigned char buf[256];
		int recvd = s.getPeer()->recvFrom( buf, sizeof(buf), from );

		String timeStr;
		timeStr.assign( (const char*)buf, recvd );

		System::println( Format("Recv'd the time of %s from %s") % timeStr % from.getHostAddress() );

	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}

	NetworkKit::terminate();
	FoundationKit::terminate();
	return 0;
}


