////UDPServer.cpp
#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"

using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	NetworkKit::init(  argc, argv );

	try {		
		UDPSocket s;
		s.listen( 34251 );
		
		while ( true ) {
			s.selectFor( Socket::SelectWaitForever, Socket::ssReadable );

			IPEndPoint from;
			unsigned char buf[256];
			s.getPeer()->recvFrom( buf, sizeof(buf), from );

			DateTime date = DateTime::now();
			AnsiString theTime = StringUtils::format( date, "%Y-%m-%d %H:%M:%S" );

			s.getPeer()->sendTo( (unsigned char*)theTime.c_str(), theTime.size(), from );
		}
	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}

	NetworkKit::terminate();
	FoundationKit::terminate();
	return 0;
}

