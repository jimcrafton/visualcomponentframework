////CryptoKit.cpp

#include "vcf/FoundationKit/FoundationKit.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>


/**
For info on how to get the debug libraries to work for open ssl
http://codefromthe70s.org/sslimprov.asp
*/



namespace VCF {

namespace Crypto {

	class CryptoKit {
	public:
		static void init( int argc, char* argv[] );
		static void terminate();
	};


	class DigestToolkit {
	public:
		static void init( int argc, char* argv[] );
		static void terminate();
	};


	class MessageDigest {
	public:
		enum {
			MaxSize = EVP_MAX_MD_SIZE
		};
		
		enum {
			NotFinished = (size_t)-1
		};

		typedef std::vector<unsigned char> DigestResult;

		MessageDigest( const EVP_MD* digest ):finished_(false),resultSize_(0) {
			EVP_MD_CTX_init( &ctx_ );
			EVP_DigestInit( &ctx_, digest );
		}

		virtual ~MessageDigest() {
			EVP_MD_CTX_cleanup(&ctx_);
		}

		void update( const unsigned char* bytes, size_t sizeBytes ) {
			EVP_DigestUpdate( &ctx_, bytes, sizeBytes );
			finished_ = false;
		}

		DigestResult hash( const unsigned char* bytes, size_t sizeBytes ) {
			update( bytes, sizeBytes);			
			return finish();
		}

		DigestResult finish() {
			DigestResult result(MaxSize);
			EVP_DigestFinal( &ctx_, (unsigned char*)result.begin(), &resultSize_);
			result.resize(resultSize_);
			finished_ = true;
			return result;
		}

		size_t size() const {
			if ( !finished_ ) {
				return MessageDigest::NotFinished;
			}
			return resultSize_;
		}

	protected:
		bool finished_;
		EVP_MD_CTX ctx_;
		size_t resultSize_;
	};


	class MD2: public MessageDigest {
	public:
		MD2():MessageDigest( EVP_md2() ) {}
	};

	class MD5: public MessageDigest {
	public:
		MD5():MessageDigest( EVP_md5() ) {}
	};

	class DSS: public MessageDigest {
	public:
		DSS():MessageDigest( EVP_dss() ) {}
	};

	class DSS1: public MessageDigest {
	public:
		DSS1():MessageDigest( EVP_dss1() ) {}
	};

	class RipeMD160: public MessageDigest {
	public:
		RipeMD160():MessageDigest( EVP_ripemd160() ) {}
	};



	class SHA1: public MessageDigest {
	public:
		SHA1():MessageDigest( EVP_sha1() ) {}
	};

	class SHA: public MessageDigest {
	public:
		SHA():MessageDigest( EVP_sha() ) {}
	};


	class Base64Encoder {
	public:

		/**
		This adds a final 2 bytes because the logic of 
		EVP_EncodeFinal is that it adds a final '\n' character
		at the last index, increments the index, then sets 
		this value to '\0'. Adding 2 here guarantees that we
		end up with a valid size that is safe to use.
		*/
		inline static size_t safeSizeOf( size_t size ) {
			return ((size + 2) / 3) * 4 + 2;
		}

		/**
		This calculates the exact number of bytes used in encoding a 
		given number of bytes to base 64.
		*/
		inline static size_t sizeOf( size_t size ) {
			return ((size + 2) / 3) * 4;
		}

		
		Base64Encoder():encodedSize_(0) {
			EVP_EncodeInit( &ctx_ );
		}

		size_t size() const {
			return encodedSize_;
		}

		void encode( const unsigned char* inData, size_t inDataSize,
					unsigned char* outData, size_t outDataSize ) {
			int tmp = 0;
			
			if ( outDataSize < inDataSize ) {
				throw std::logic_error("output data size is less than input data size.");
			}

			EVP_EncodeUpdate( &ctx_, outData, &tmp, inData, inDataSize );
			encodedSize_ += tmp;
		}

		void finish( unsigned char* outData, size_t outDataSize ) {
			int tmp = 0;			
			
			EVP_EncodeFinal(&ctx_, outData, &tmp);

			encodedSize_ += tmp;
		}

		void init() {
			EVP_EncodeInit( &ctx_ );
		}

	protected:
		size_t encodedSize_;
		EVP_ENCODE_CTX ctx_;
	};

	class Base64Decoder {
	public:
		Base64Decoder():decodedSize_(0) {
			EVP_DecodeInit(&ctx_);
		}

		size_t size() const {
			return decodedSize_;
		}

		void decode( const unsigned char* inData, size_t inDataSize,
					unsigned char* outData, size_t outDataSize ) {

			int tmp = 0;
			
			EVP_DecodeUpdate( &ctx_, outData, &tmp, 
						inData, inDataSize );


			decodedSize_ += tmp;

		}

		void finish( unsigned char* outData, size_t outDataSize ) {
			int tmp = 0;			
			
			EVP_DecodeFinal(&ctx_, outData, &tmp);

			decodedSize_ += tmp;
		}

		inline static size_t sizeOf( size_t size ) {
			return ((size/4)*3) - 2;
		}
	protected:
		size_t decodedSize_;
		EVP_ENCODE_CTX ctx_;
	};


	class SymmetricEncryptionCipher {
	public:
		enum {
			MaxEncryptKeyLength = EVP_MAX_KEY_LENGTH,
			MaxEncryptIVecLength = EVP_MAX_IV_LENGTH,
		};

		SymmetricEncryptionCipher( const EVP_CIPHER* cipherImpl ):encCipherImpl_(cipherImpl),bytesEncrypted_(0) {
			EVP_CIPHER_CTX_init(&encryptCtx_);
		}

		virtual ~SymmetricEncryptionCipher() {
			EVP_CIPHER_CTX_cleanup(&encryptCtx_);
		}

		size_t getEncryptKeyLength() const {
			return EVP_CIPHER_key_length(encCipherImpl_);
		}

		size_t getEncryptIVecLength() const {
			return EVP_CIPHER_iv_length(encCipherImpl_);
		}

		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			EVP_EncryptInit( &encryptCtx_, encCipherImpl_, key, iv );
		}

		void encrypt( const unsigned char* data, size_t dataLength, 
						unsigned char* encryptedData, size_t encryptedDataLength ) {


			int tmp = 0;
			if ( encryptedDataLength < dataLength ) {
				throw std::logic_error("output data size is less than input data size.");
			}
			
			int err = EVP_EncryptUpdate( &encryptCtx_, encryptedData, &tmp, data, dataLength );
			bytesEncrypted_ += tmp;
		}

		void finishEncryption( unsigned char* encryptedData, size_t encryptedDataLength ) {
			int tmp = 0;
			EVP_EncryptFinal(&encryptCtx_, encryptedData, &tmp);
			bytesEncrypted_ += tmp;
		}

		size_t getBytesEncrypted() const {
			return bytesEncrypted_;
		}
	protected:
		EVP_CIPHER_CTX encryptCtx_;
		size_t bytesEncrypted_;
		const EVP_CIPHER* encCipherImpl_;
	};

	class SymmetricDecryptionCipher {
	public:
		enum {
			MaxDecryptKeyLength = EVP_MAX_KEY_LENGTH,
			MaxDecryptIVecLength = EVP_MAX_IV_LENGTH,
		};

		SymmetricDecryptionCipher( const EVP_CIPHER* cipherImpl ):decCipherImpl_(cipherImpl),bytesDecrypted_(0) {
			EVP_CIPHER_CTX_init(&decryptionCtx_);
		}

		virtual ~SymmetricDecryptionCipher() {
			EVP_CIPHER_CTX_cleanup(&decryptionCtx_);
		}

		size_t getDecryptKeyLength() const {
			return EVP_CIPHER_key_length(decCipherImpl_);
		}

		size_t getDecryptIVecLength() const {
			return EVP_CIPHER_iv_length(decCipherImpl_);
		}

		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			EVP_DecryptInit( &decryptionCtx_, decCipherImpl_, key, iv );
		}

		void decrypt( const unsigned char* encryptedData, size_t encryptedDataLength, 
						unsigned char* decryptedData, size_t decryptedDataLength ) {


			int tmp = 0;
			
			
			int err = EVP_DecryptUpdate( &decryptionCtx_, decryptedData, &tmp, encryptedData, encryptedDataLength );
			bytesDecrypted_ += tmp;
		}

		void finishDecryption( unsigned char* decryptedData, size_t decryptedDataLength ) {
			int tmp = 0;
			EVP_DecryptFinal(&decryptionCtx_, decryptedData, &tmp);
			bytesDecrypted_ += tmp;
		}

		size_t getBytesDecrypted() const {
			return bytesDecrypted_;
		}
	protected:
		EVP_CIPHER_CTX decryptionCtx_;
		size_t bytesDecrypted_;
		const EVP_CIPHER* decCipherImpl_;
	};


	class BlowfishECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishECB() : SymmetricEncryptionCipher(EVP_bf_ecb()), SymmetricDecryptionCipher(EVP_bf_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishCBC() : SymmetricEncryptionCipher(EVP_bf_cbc()), SymmetricDecryptionCipher(EVP_bf_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishCFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishCFB() : SymmetricEncryptionCipher(EVP_bf_cfb()), SymmetricDecryptionCipher(EVP_bf_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishOFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishOFB() : SymmetricEncryptionCipher(EVP_bf_ofb()), SymmetricDecryptionCipher(EVP_bf_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardECB() : SymmetricEncryptionCipher(EVP_des_ecb()), SymmetricDecryptionCipher(EVP_des_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardCBC() : SymmetricEncryptionCipher(EVP_des_cbc()), SymmetricDecryptionCipher(EVP_des_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardCFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardCFB() : SymmetricEncryptionCipher(EVP_des_cfb()), SymmetricDecryptionCipher(EVP_des_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardOFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardOFB() : SymmetricEncryptionCipher(EVP_des_ofb()), SymmetricDecryptionCipher(EVP_des_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class RivestCipher2 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher2() : SymmetricEncryptionCipher(EVP_rc2_ecb()), SymmetricDecryptionCipher(EVP_rc2_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class RivestCipher2CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher2CBC() : SymmetricEncryptionCipher(EVP_rc2_cbc()), SymmetricDecryptionCipher(EVP_rc2_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class RivestCipher2_40CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher2_40CBC() : SymmetricEncryptionCipher(EVP_rc2_40_cbc()), SymmetricDecryptionCipher(EVP_rc2_40_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class RivestCipher2CFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher2CFB() : SymmetricEncryptionCipher(EVP_rc2_cfb()), SymmetricDecryptionCipher(EVP_rc2_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class RivestCipher2OFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher2OFB() : SymmetricEncryptionCipher(EVP_rc2_ofb()), SymmetricDecryptionCipher(EVP_rc2_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class Cast5ECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		Cast5ECB() : SymmetricEncryptionCipher(EVP_cast5_ecb()), SymmetricDecryptionCipher(EVP_cast5_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class Cast5CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		Cast5CBC() : SymmetricEncryptionCipher(EVP_cast5_cbc()), SymmetricDecryptionCipher(EVP_cast5_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class Cast5CFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		Cast5CFB() : SymmetricEncryptionCipher(EVP_cast5_cfb()), SymmetricDecryptionCipher(EVP_cast5_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};
	
		
	class Cast5OFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		Cast5OFB() : SymmetricEncryptionCipher(EVP_cast5_ofb()), SymmetricDecryptionCipher(EVP_cast5_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};
	

	class IdeaECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		IdeaECB() : SymmetricEncryptionCipher(EVP_idea_ecb()), SymmetricDecryptionCipher(EVP_idea_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class IdeaCFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		IdeaCFB() : SymmetricEncryptionCipher(EVP_idea_cfb()), SymmetricDecryptionCipher(EVP_idea_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class IdeaOFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		IdeaOFB() : SymmetricEncryptionCipher(EVP_idea_ofb()), SymmetricDecryptionCipher(EVP_idea_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class IdeaCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		IdeaCBC() : SymmetricEncryptionCipher(EVP_idea_cbc()), SymmetricDecryptionCipher(EVP_idea_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};




	class RSABase {
	public:

		RSABase() : rsa_(NULL){
			rsa_ = RSA_new();
		}

		~RSABase(){ 
			RSA_free( rsa_ );
		}

		size_t modulusSize() const {
			RSA_size( rsa_ );
		}
	protected:

		RSA* rsa_;
	};



	class Key {
	public:

		enum KeyTypes{
			TypeNone = EVP_PKEY_NONE,
			TypeRSA = EVP_PKEY_RSA,
			TypeRSA2 =  EVP_PKEY_RSA2,
			TypeDSA = EVP_PKEY_DSA,
			TypeDSA1 = EVP_PKEY_DSA1,
			TypeDSA2 = EVP_PKEY_DSA2,
			TypeDSA3 = EVP_PKEY_DSA3,
			TypeDSA4 = EVP_PKEY_DSA4,
			TypeDH = EVP_PKEY_DH,
			TypeEC = EVP_PKEY_EC
		};

		Key(): key_(NULL){
			key_ = EVP_PKEY_new();
		}

		~Key() {
			EVP_PKEY_free( key_ );
			key_ = NULL;
		}

		int size() const {
			return EVP_PKEY_size( key_ );
		}

		int bits() const {
			return EVP_PKEY_bits( key_ );
		}

		void assignKey( int type, char* key ) {
			int err = EVP_PKEY_assign( key_, type, key );	
		}

		void copy( const Key& from ) {
			int err = EVP_PKEY_copy_parameters( key_, from.key_ );
		}

		void copy( EVP_PKEY* from ) {
			int err = EVP_PKEY_copy_parameters( key_, from );
		}

		bool missingParameters() const {
			return (EVP_PKEY_missing_parameters(key_) == 1) ? true : false;
		}

		void saveParameters( int mode ) {
			int err = EVP_PKEY_save_parameters( key_, mode );
		}

		bool compare( const Key& rhs ) const {
			return (EVP_PKEY_cmp_parameters( key_, rhs.key_ ) == 1) ? true : false;
		}

		bool compare( EVP_PKEY* rhs ) const {
			return (EVP_PKEY_cmp_parameters( key_, rhs ) == 1) ? true : false;
		}


		EVP_PKEY* in() const {
			return key_;
		}

	protected:
		EVP_PKEY* key_;
	};
};

};

using namespace VCF;
using namespace VCF::Crypto;


void CryptoKit::init( int argc, char* argv[] )
{
	OpenSSL_add_all_digests();
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







static void callback(int p, int n, void *arg)
{
	char c='B';
	
	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
}

int add_ext(X509 *cert, int nid, char *value)
{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;
	/* This sets the 'context' of the extensions. */
	/* No configuration database */
	X509V3_set_ctx_nodb(&ctx);
	/* Issuer and subject certs: both the target since it is self signed,
	* no request and no CRL
	*/
	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;
	
	X509_add_ext(cert,ex,-1);
	X509_EXTENSION_free(ex);
	return 1;
}

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
	{
		if ((pk=EVP_PKEY_new()) == NULL)
		{
			abort(); 
			return(0);
		}
	}
	else
		pk= *pkeyp;
	
	if ((x509p == NULL) || (*x509p == NULL))
	{
		if ((x=X509_new()) == NULL)
			goto err;
	}
	else
		x= *x509p;
	
	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
	{
		abort();
		goto err;
	}
	rsa=NULL;
	
	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),0);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);
	
	name=X509_get_subject_name(x);
	
	/* This function creates and adds the entry, working out the
	* correct string type and performing checks on its length.
	* Normally we'd check the return value for errors...
	*/
	X509_NAME_add_entry_by_txt(name,"C",
		MBSTRING_ASC, (const unsigned char*)"UK", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
		MBSTRING_ASC, (const unsigned char*)"OpenSSL Group", -1, -1, 0);
	
		/* Its self signed so set the issuer name to be the same as the
		* subject.
	*/
	X509_set_issuer_name(x,name);
	
	/* Add various extensions: standard extensions */
	add_ext(x, NID_basic_constraints, "critical,CA:TRUE");
	add_ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");
	
	add_ext(x, NID_subject_key_identifier, "hash");
	
	/* Some Netscape specific extensions */
	add_ext(x, NID_netscape_cert_type, "sslCA");
	
	add_ext(x, NID_netscape_comment, "example comment extension");
	
	
#ifdef CUSTOM_EXT
	/* Maybe even add our own extension based on existing */
	{
		int nid;
		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
		X509V3_EXT_add_alias(nid, NID_netscape_comment);
		add_ext(x, nid, "example comment alias");
	}
#endif
	
	if (!X509_sign(x,pk,EVP_md5()))
		goto err;
	
	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
}



using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	CryptoKit::init( argc, argv );

	char mess1[] = "Test Message";
	char mess2[] = "Hello World\n";
	

	

		
	ERR_load_crypto_strings();

	MD2 md2;
	MD5 md5;
	VCF::Crypto::SHA1 sha1;
	VCF::Crypto::SHA sha;
	DSS dss;
	DSS1 dss1;
	RipeMD160 rp160;


	MessageDigest::DigestResult res = md5.hash( (const unsigned char*)mess1, strlen(mess1) );

	int i = 0;

	printf("md5 Digest is (%d bytes): ", md5.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");


	res = sha1.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("sha1 Digest is (%d bytes): ", sha1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = sha.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("sha Digest is (%d bytes): ", sha1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = md2.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("md2 Digest is (%d bytes): ", md2.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = dss.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("dss Digest is (%d bytes): ", dss.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");


	res = dss1.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("dss1 Digest is (%d bytes): ", dss1.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");

	res = rp160.hash( (const unsigned char*)mess1, strlen(mess1) );

	printf("rp160 Digest is (%d bytes): ", rp160.size() );
	for(i = 0; i < res.size(); i++) printf("%X", res[i]);
	printf("\n");



	int seed = 209348203;
	RAND_seed(&seed,sizeof(seed));

	unsigned int randNum = 0;

	printf( "initial random num: %u\n", randNum );

	for (int ii=0;ii<10;ii++ ) {
		RAND_bytes( (unsigned char*)&randNum,sizeof(randNum));
		printf( "random num: %u\n", randNum );
	}

	char fn[256];
	memset( fn,0,sizeof(fn) );
	RAND_file_name(fn,255);
	printf( "random file name: %s\n", fn );




	const char* msg = "Hello world, how are you?";
	char* result = NULL;

	int msgLen = strlen(msg);
	int resultLen = Base64Encoder::safeSizeOf(msgLen);

	result = new char[resultLen+1];
	int ol = 0;
	int tmp = 0;


	Base64Encoder encoder;

	encoder.encode( (const unsigned char*)msg, msgLen, (unsigned char*)result, resultLen+1 );

	encoder.finish( (unsigned char*)result, resultLen+1 );
	
	ol += encoder.size();

	//result[ol-1] = 0;

	printf( "predicted size from %d bytes to b64: %d. Actual: %d\n",
		msgLen, Base64Encoder::sizeOf(msgLen), ol );

	printf( "Base64 encoded \"%s\" into \n\t%s\n",
			msg, result );


	Base64Decoder decoder;

	char* decodeResult = new char[resultLen+1];

	memset(decodeResult,0,resultLen+1);

	
	decoder.decode( (const unsigned char*)result, ol, (unsigned char*)decodeResult, resultLen+1	);

	decoder.finish( (unsigned char*)decodeResult, resultLen+1 );

	
	printf( "predicted size from %d bytes to normal : %d. Actual: %d\n",
			ol, Base64Decoder::sizeOf(ol), decoder.size() );

	printf( "Base64 decoded \"%s\" into \n\t\"%s\"\n",
			result, decodeResult );

	delete [] result;
	delete [] decodeResult;




	unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned char iv[] = {1,2,3,4,5,6,7,8};

	printf( "Key: " );
	for (int x=0;x<sizeof(key);x++ ) {
		printf( "%X", key[x] );
	}
	printf( "\n" );

	printf( "ivec: " );
	for (int y=0;y<sizeof(iv);y++ ) {
		printf( "%X", iv[y] );
	}
	printf( "\n" );

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit(&ctx, EVP_bf_cbc(), key, iv);

	unsigned char outbuf[1024];
	int outlen = 0;
	int tmplen = 0;
	memset(outbuf,0,sizeof(outbuf) );
	const char* text = "Hello - some text to be encrypted.";

	int err = EVP_EncryptUpdate( &ctx, outbuf, &outlen, (const unsigned char*)text, strlen(text) );
	err = EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
	outlen += tmplen;

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for (int j=0;j<outlen;j++ ) {
		printf( "%X", outbuf[j] );
	}
	printf( "\n %d bytes\n", outlen );	

	EVP_CIPHER_CTX_cleanup(&ctx);


	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit(&ctx, EVP_bf_cbc(), key, iv);

	unsigned char outbuf2[1024];
	int outlen2 = 0;
	tmplen = 0;
	memset(outbuf2,0,sizeof(outbuf2) );

	err = EVP_DecryptUpdate( &ctx, outbuf2, &outlen2, outbuf, outlen );
	err = EVP_DecryptFinal(&ctx, outbuf2 + outlen2, &tmplen);
	outlen2 += tmplen;


	printf( "Decrypted \n" );
	for (int jj=0;jj<outlen;jj++ ) {
		printf( "%X", outbuf[jj] );
	}

	outbuf2[outlen2] = 0;
	printf( "\n (%d bytes)\n into:\n \"%s\" (%d bytes)\n", outlen, (const char*)outbuf2, outlen2 );



	BlowfishCBC bfCbc;

	memset(outbuf, 0, sizeof(outbuf));
	bfCbc.init( key, sizeof(key), iv, sizeof(iv) );
	bfCbc.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	bfCbc.finishEncryption( outbuf+bfCbc.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for (int d=0;d<bfCbc.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", bfCbc.getBytesEncrypted() );


	DataEncryptionStandardECB des1;

	memset(outbuf, 0, sizeof(outbuf));
	des1.init( key, sizeof(key), iv, sizeof(iv) );
	des1.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	des1.finishEncryption( outbuf+des1.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for ( d=0;d<des1.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", des1.getBytesEncrypted() );

	Cast5OFB cast1;

	memset(outbuf, 0, sizeof(outbuf));
	cast1.init( key, sizeof(key), iv, sizeof(iv) );
	cast1.encrypt( (const unsigned char*)text, strlen(text), outbuf, sizeof(outbuf) );
	cast1.finishEncryption( outbuf+cast1.getBytesEncrypted(), sizeof(outbuf) );

	printf( "Encrypted using Cast5OFB algo \"%s\" (%d bytes) into:\n", text, strlen(text) );
	for ( d=0;d<cast1.getBytesEncrypted();d++ ) {
		printf( "%X", outbuf[d] );
	}
	printf( "\n %d bytes\n", cast1.getBytesEncrypted() );




	Key pubKey;
	Key privKey;


	printf( "Key size: %u, bits: %d\n", pubKey.size(), pubKey.bits() );
	

	RSA* rsaKeyPair = RSA_generate_key( 512, RSA_F4, NULL, NULL );

	RSA_print_fp(stdout,rsaKeyPair,0);

	int szOfRSA = RSA_size( rsaKeyPair );

	X509 *x509=NULL;
	EVP_PKEY *pkey=NULL;
	
	mkcert(&x509,&pkey,512,0,365);
	
	RSA_print_fp(stdout,pkey->pkey.rsa,0);
	X509_print_fp(stdout,x509);
	
	PEM_write_PrivateKey(stdout,pkey,NULL,NULL,0,NULL, NULL);
	PEM_write_X509(stdout,x509);
	
	X509_free(x509);



	FILE* fp = fopen( "test-pub.pem", "wb" );

	PEM_write_RSAPublicKey(fp,rsaKeyPair);

	fclose(fp);


#define PASSWORD	"test"

	fp = fopen( "test-priv.pem", "wb" );
	PEM_write_RSAPrivateKey( fp, rsaKeyPair, NULL, (unsigned char*)PASSWORD, strlen(PASSWORD), NULL, NULL );
	fclose(fp);


	fp = fopen( "test-priv.pem", "rb" );
	RSA* rsa2 = NULL;
	PEM_read_RSAPrivateKey(  fp, &rsa2, NULL, NULL );
	fclose(fp);

	const char* data = "Holy Crap!";


	unsigned char rsaData[1024];
	memset(rsaData, 0, sizeof(rsaData) );

	err = RSA_public_encrypt( strlen(data), (const unsigned char*)data, rsaData, rsaKeyPair, RSA_PKCS1_PADDING );


	//err = RSA_padding_add_PKCS1_type_1( rsaData, sizeof(rsaData), (const unsigned char*)data, strlen(data) );


	unsigned char rsaDecryptedData[1024];
	memset(rsaDecryptedData, 0, sizeof(rsaDecryptedData) );

	err = RSA_private_decrypt( szOfRSA, rsaData, rsaDecryptedData, rsaKeyPair, RSA_PKCS1_PADDING );

	ERR_print_errors_fp( stdout );


	CryptoKit::terminate();
	FoundationKit::terminate();
	return 0;
}


