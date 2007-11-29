////TCPServer.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"
#include "vcf/FoundationKit/Dictionary.h"

using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	NetworkKit::init(  argc, argv );

	try {		
		TCPSocket server;
		server.listen( 34251 );
		
		server.getRemotePort();
		server.getLocalPort();

		Dictionary options;
		options[Socket::soBlocking] = false;
		server.setOptions( options );

		std::vector<Socket*> tmp;
		std::vector<Socket*> clients;
		while ( true ) {
			System::println( "waiting..." );
			tmp = clients;
			if ( tmp.empty() ) {
				server.selectFor( 5000, Socket::ssReadable );
			}
			else {
				server.getPeer()->select( 5000, &tmp, NULL, NULL );
			}
			
			TCPSocket* client = server.accept();
			if ( NULL != client ) {
				clients.push_back( client );

				IPAddress addr = client->getRemoteHostIPAddress();
				System::println( "Recv'd connect! From: " + addr.getHostAddress() +
								" port: " + (int)client->getRemotePort() );
			}


			std::vector<Socket*>::iterator it = tmp.begin();
			while ( it != tmp.end() ) {
				Socket* s = *it;
				TCPSocketInputStream sis( (TCPSocket&) *s );
				unsigned char buf[256];
				uint64 bytesRead = sis.read( &buf[0], sizeof(buf) );

				IPAddress addr = s->getRemoteHostIPAddress();

				if ( 0 == bytesRead ) {					
					
					System::println( "Lost connection from: " + addr.getHostAddress() +
								" port: " + (int)s->getRemotePort() );

					clients.erase( std::find(clients.begin(),clients.end(),s) );

					s->free();
				}
				else {
					buf[bytesRead] = 0;
					System::println( Format("Recv'd %d bytes {%s} from: %s port %d") 
										% bytesRead 
										% &buf[0]
										% addr.getHostAddress() 
										% s->getRemotePort() );	
				}

				++it;
			}

		}
	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}

	NetworkKit::terminate();
	FoundationKit::terminate();
	return 0;
}

