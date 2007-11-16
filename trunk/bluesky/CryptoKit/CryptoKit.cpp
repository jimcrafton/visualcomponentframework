////CryptoKit.cpp



#include "CryptoKit.h"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>





using namespace VCF;
using namespace VCF::Crypto;


void CryptoKit::init( int argc, char* argv[] )
{
	SSL_library_init();

	OpenSSL_add_all_digests();	
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_algorithms();

	SSL_load_error_strings();
	ERR_load_BIO_strings();
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





