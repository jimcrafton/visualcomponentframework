////NetworkKit.cpp


#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/StringTokenizer.h"




using namespace VCF;


class ReadThread : public Thread {
public:
	Socket* socket;
	ReadThread( Socket* s ) : socket(s){

	}


	AnsiString msgData;

	void doMsg() {
		
		System::println( "-------------------------------------------------------------------------------" );

		String msg = msgData;

		StringTokenizer tok( msg, " ");

		int elementCount = 0;

		char senderNick[256];
		char senderUser[256];
		char senderHost[256];

		memset(senderNick,0,sizeof(senderNick));
		memset(senderUser,0,sizeof(senderUser));
		memset(senderHost,0,sizeof(senderHost));


		std::vector<String> params;

		int offset = 0;

		while ( tok.hasMoreElements() ) {
			String s = tok.nextElement();
			

			if ( 0 == elementCount && s[0] == ':' ) {							
				
				
				if ( tok.hasMoreElements() ) {					
					sscanf( s.ansi_c_str() + 1, "%[^!]!%[^@]@%s", senderNick, senderUser, senderHost );
					
					offset += s.size() + 1;

					s = tok.nextElement();

					params.push_back( s );

					offset += s.size() + 1;
					elementCount ++;
					continue;
				}
				
			}
			else {
				int a = 0;
				int d = 0;
				if ( 0 == d ) {
					if ( s[0] == ':' ) {
						s.erase(0,1);
						d = 1;
					}
					

					a++;

					if ( 0 == d ) {
						params.push_back( s );						
					}
					else {						
						
						params.push_back( msgData.substr(offset,msgData.size()-offset) );
						break;
					}
				}				
			}
			
			offset += s.size() + 1;
			elementCount ++;
		}

		System::println( "Msg:<<" );

		System::println( Format( "\tnick:%s") % senderNick );
		System::println( Format( "\tuser:%s") % senderUser );
		System::println( Format( "\thost:%s") % senderHost );

		

		std::vector<String>::iterator it = params.begin();
		while ( it != params.end() ) {

			System::println( Format( "\tparam:%s") % *it );

			it++;
		}


		System::println( ">>" );

	}

	void parseMsg( const uchar* buf, size_t size ) {
		const uchar* start = buf;
		const uchar* tmp = buf;
		while ( ((tmp-buf) < size) ) {
			if ( (*tmp == '\r') || (*tmp == '\n') ) {

				msgData.append( (const char*)start, tmp-start );
				
				doMsg();


				msgData = "";

				if ( *tmp == '\r' ) {
					tmp ++;
				}

				if ( *tmp == '\n' ) {
					tmp ++;
				}

				start = tmp;
			}
			else {
				tmp++;
			}
		}

		if ( (tmp - start) > 1 ) {
			msgData.append( (const char*)start, tmp-start );
		}

	}

	virtual bool run() {

		SocketInputStream sis(*socket);

		uchar tmp[256];
		while ( canContinue() ) {
			socket->selectFor( Socket::SelectWaitForever, Socket::ssReadable );
			
			printf( "\nSelect completed\n" );

			do {			
				try {
					uint64 err = sis.read( tmp, sizeof(tmp) );
					
					printf( "\n>>Read off %d bytes!<<\n", (int)err );

					if ( err == 0 ) {
						System::println( "Disconnect!" );						
						break;
					}
					else {
						tmp[err] = 0;
						//parseMsg( tmp, err );
						printf( (const char*)&tmp[0] );
					}
				}
				catch ( BasicException& ) {
					System::println( "Socket error!" );
					break;
				}
			} while( socket->pending() && socket->isReadable() ) ;


			if ( socket->isClosed() || socket->hasError() ) {
				break;
			}
		}

		printf( "\nRead Thread completed\n" );
		return true;
	}
};




int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	NetworkKit::init(  argc, argv );	

	try {

		IPAddress::RawBytes ip(4);
		ip[0] = 127;
		ip[1] = 0;
		ip[2] = 0;
		ip[3] = 1;

		IPAddress addr(ip);

		IPAddress addr2;

		IPAddress addr3("www.google.com");

		IPAddress::RawBytes ipBytes = addr.getAddressBytes();
		System::println( Format("%d.%d.%d.%d") % ipBytes[0] % ipBytes[1] % ipBytes[2] % ipBytes[3] ) ;

		System::println( Format("host address: %s") % addr.getHostAddress() );

		System::println( Format("host address: %s") % addr2.getHostAddress() );
		System::println( Format("host name: %s") % addr2.getHostName() );


		System::println( Format("host address: %s") % addr3.getHostAddress() );
		System::println( Format("host name: %s") % addr3.getHostName() );


		std::vector<IPAddress> addrs = IPAddress::getDNSHostAddresses( "google.com" );
		for (int ipIdx=0;ipIdx<addrs.size();ipIdx++ ) {
			System::println( Format("Host addr #%d %s") % (ipIdx+1) % addrs[ipIdx].getHostAddress() );
		}



		//System::println( Format("host address: %s") % 	addr3.getHostAddress() );
		//System::println( Format("host name: %s") % addr3.getHostName() );


		Socket ircServer;
		unsigned short ircPort = 5030;
		String ircHost = "172.24.82.202"; //"irc.freenode.net";

		ircServer.connect( ircHost, ircPort );

		ReadThread* th = new ReadThread(&ircServer);
		th->start();
		/*
		AnsiString msg;
		msg = (String)(Format( "USER %s %s %s :%s" ) % "ddiego" % "b" % "c" % "Odysseus");
		msg += " \r\n";

		SocketOutputStream sos(ircServer);
		sos.write( (const uchar*)msg.c_str(), msg.size() );

		msg = (String)(Format( "NICK %s" ) % "Unknown[1]");
		msg += " \r\n";
		sos.write( (const uchar*)msg.c_str(), msg.size() );
*/


		//rt->quit();



	//b_server_printf( server, "NICK %s", server->nickname );

		while ( true ) {
			Sleep(1000);
		}


/*
		Socket server;
		Dictionary options;
		options[Socket::soBlocking] = false;
		server.setOptions( options );

		server.listen( 10032 );

		System::println( "Listening on port: " + StringUtils::toString(server.getPort()) );

		SocketArray clients;

		while (true ) {
			Socket* client = server.accept();
			if ( NULL != client ) {
				clients.push_back( client );
				client->setOptions( options );
				System::println( "Recv'd connect! From: " + client->getHostIPAddress() +
								" port: " + (int)client->getPort() );
			}
			else {
				
				SocketArray readList = clients;	
				SocketArray writeList = clients;
				SocketArray errorList = clients;

				
				server.getPeer()->select( 100, &readList, &writeList, &errorList );

				uchar tmp[256];
				SocketArray::iterator it;
				for (it=readList.begin();it != readList.end(); it++ ) {
					Socket* s = *it;

					SocketInputStream sis(*s);

					do {

						try {
							ulong32 err = sis.read( tmp, sizeof(tmp) );
							
							if ( err == 0 ) {
								System::println( "Disconnect!" );
								
								clients.erase( std::find(clients.begin(),clients.end(),s) );
								break;
							}
							else {
								tmp[err] = 0;
								System::println( Format( "Recv'd %d bytes: %s\n") % err % tmp );
							}
						}
						catch ( BasicException& ) {
							System::println( "Socket error! Manually disconnecting!" );
								
							clients.erase( std::find(clients.begin(),clients.end(),s) );
							break;
						}
					} while( s->pending() && s->isReadable() );
				}
			}
		}
		*/

	}
	catch ( BasicException& e ) {
		System::println( e.getMessage() );
	}

	NetworkKit::terminate();

	FoundationKit::terminate();
	return 0;
}





