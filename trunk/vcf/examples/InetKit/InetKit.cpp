////InetKit.cpp

#include "vcf/FoundationKit/FoundationKit.h"

#if !defined(VCF_DISABLE_PRAGMA_LINKING)
#   define USE_INTERNETKIT_DLL
#endif

#include "vcf/InternetKit/InternetKit.h"


using namespace VCF;


void onURLAuthenticateEvent( Event* e ) 
{
	URLAuthenticationEvent* urlEvent = (URLAuthenticationEvent*)e;

	urlEvent->setUserName( "sdfj;sdfkjs;dfklj" );
	urlEvent->setPassword( "skjfhskdjfhskdjfhk" );
	
}

void onURLEvent( Event* e ) 
{
	URLEvent* urlEvent = (URLEvent*)e;

	static uint32 totalBytes = 0;

	totalBytes += urlEvent->getBytesReceived();

	System::println( String("Bytes recv'd: ") + urlEvent->getBytesReceived() );

	System::println( "Total bytes recv'd: " + System::getCurrentThreadLocale()->toString( totalBytes ) );
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	InternetKit::init(argc, argv); 
	
	StaticEventHandlerInstance<Event> ev(onURLEvent);
	StaticEventHandlerInstance<Event> ev2(onURLAuthenticateEvent);



	URL url ("http://www.your-password-protected-site.com/your/precious/content.html");

	url.DataReceived += &ev;
	url.AuthenticationRequested += &ev2;

	try {
		url.downloadToFile( "test.html" ); 
	}
	catch ( URLException& e ) {
		System::println( e.getMessage() );
	}




	URL url2 ("http://www.cwi.nl:80/%7Eguido/Python.html");

	url2 = "foo:bar@www.cwi.nl:88/%7Eguido/Python.html";

	url2 = "foo@www.cwi.nl:88/%7Eguido/Python.html";

	url2 = "cwi.nl:88/%7Eguido/Python.html";

	url2 = "foo:b@ar@www.cwi.nl:88/%7Eguido/Python.html";

	url2.validate();

	URL file ("file:///f:/code/vcfdev/dev/vcf/examples/InetKit/test.html");

	std::vector<String> parts = file.getParts();

	StringUtils::trace( Format("scheme: %s\nuser: %s\npwd: %s\nhost: %s\nport: %s\nurl path: %s\n") %
									parts[URL::upScheme] %
									parts[URL::upUser] % 
									parts[URL::upPassword] % 
									parts[URL::upHost] % 
									parts[URL::upPort] % 
									parts[URL::upUrlPath] );

	InternetKit::terminate();

	FoundationKit::terminate();
	return 0;
}


