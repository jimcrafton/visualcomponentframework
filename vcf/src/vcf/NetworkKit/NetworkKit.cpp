//NetworkKit.cpp

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/NetworkToolkit.h"


using namespace VCF;



void NetworkKit::init( int argc, char** argv )
{
	NetworkToolkit::create();
}

void NetworkKit::terminate()
{
	NetworkToolkit::destroy();
}


NetworkException::NetworkException( const String & message ):
	BasicException( message ),errorCode_(0)
{
	errorCode_ = NetworkToolkit::getLastError();
}

NetworkException::NetworkException():
	BasicException( "Unknown Network Exception occurred." ),errorCode_(0)
{
	errorCode_ = NetworkToolkit::getLastError();
}
	
NetworkException::NetworkException( const String & message, int lineNumber ):
	BasicException(message, lineNumber),errorCode_(0)
{
	errorCode_ = NetworkToolkit::getLastError();
}