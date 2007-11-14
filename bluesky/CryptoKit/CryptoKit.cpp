////CryptoKit.cpp



#include "CryptoKit.h"







using namespace VCF;
using namespace VCF::Crypto;


void CryptoKit::init( int argc, char* argv[] )
{
	OpenSSL_add_all_digests();	
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_algorithms();
		
	ERR_load_crypto_strings();
}

void CryptoKit::terminate()
{

}



void DigestToolkit::init( int argc, char* argv[] )
{
	
}

void DigestToolkit::terminate()
{

}





