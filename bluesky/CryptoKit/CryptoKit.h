#ifndef _VCF_CRYPTOKIT_H__
#define _VCF_CRYPTOKIT_H__

//CryptoKit.h

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif






/**
Handle the extension based on the compiler
*/
# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1500)
#     define _LIB_CPLVERNUM "vc90"
#   elif (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef VCF_BCC
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif




//auto link stuff
#if defined(VCF_MSC) || defined(VCF_BCC)
	#ifdef USE_CRYPTOKIT_DLL
		#define CRYPTOKIT_DLL
		// using dynamic link library
		#ifdef _DEBUG
			#pragma comment(lib, "CryptoKit_"_LIB_CPLVERNUM"_d.lib")
		#else
			#pragma comment(lib, "CryptoKit_"_LIB_CPLVERNUM".lib")
		#endif
	#elif defined USE_CRYPTOKIT_LIB
		// using statically linked library
		#ifdef _DEBUG
			#pragma comment(lib, "CryptoKit_"_LIB_CPLVERNUM"_sd.lib")
		#else
			#pragma comment(lib, "CryptoKit_"_LIB_CPLVERNUM"_s.lib")
		#endif
	#endif
#endif //VCF_MSC



//export crap
#ifdef CRYPTOKIT_DLL
	#if defined(CRYPTOKIT_EXPORTS)
		#define CRYPTOKIT_API __declspec(dllexport)
	#else
		#define CRYPTOKIT_API __declspec(dllimport)
	#endif
#else
	#define CRYPTOKIT_API
#endif //CRYPTOKIT_DLL



#include "vcf/FoundationKit/FoundationKit.h"







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

	
	/**
	\class RandomError "
	*/
	class RandomError : public BasicException {
	public:
		RandomError():
		  BasicException( "Exception with OpenSSL random number generator. Probably due to the PRNG not having been seeded with enough randomness" ){};
		  
		RandomError( const String & message ):
		  BasicException( message ){};
		  
		virtual ~RandomError() throw() {};
		  
	};


	class CipherInitException : public BasicException {
	public:
		CipherInitException():
		  BasicException( "Exception initializing a cryptographic object. Probably the key length needs to be set first." ){};
		  
		CipherInitException( const String & message ):
		  BasicException( message ){};
		  
		virtual ~CipherInitException() throw() {};
		  
	};


	class CryptoException  : public BasicException {
	public:
		CryptoException():
		  BasicException(""){
			openSSLErr_ = ERR_get_error();

			setMessage( getReason() );
		};
		
		CryptoException( unsigned long err ):BasicException(""), openSSLErr_(err) {
			setMessage( getReason() );
		}

		CryptoException( const String & message ):
		  BasicException(""){
			openSSLErr_ = ERR_get_error();
			setMessage( message + " \nOpen SSL error: " + getReason() );
		 };
		  
		virtual ~CryptoException() throw() {};
		
		String getReason() const {
			return String( ERR_reason_error_string( openSSLErr_ ) );
		}
	protected:
		unsigned long openSSLErr_;
		
	};



	class CryptoInputStream : public InputStream {
	public:

		CryptoInputStream( InputStream* inputStream ) : ioObject_(NULL),inputStream_(inputStream){

			VCF_ASSERT( NULL != inputStream_ );

			if ( NULL == inputStream_ ) {
				throw RuntimeException( "Cannot have a null input stream in a CryptoInputStream instance." );
			}


			ioObject_ = BIO_new( CryptoInputStream::getMethod() );

			ioObject_->ptr = this;
		}

		virtual ~CryptoInputStream() {
			BIO_free(ioObject_);
		}

		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			inputStream_->seek( offset, offsetFrom );
		}
		
		virtual uint64 getSize() {
			return inputStream_->getSize();
		}
		
		virtual uchar* getBuffer() {
			return inputStream_->getBuffer();
		}
		
		virtual uint64 getCurrentSeekPos() {
			return inputStream_->getCurrentSeekPos();
		}
		
		virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes ) {
			return inputStream_->read( bytesToRead, sizeOfBytes );
		}
		
		virtual bool isEOS() {
			return inputStream_->isEOS();
		}

		operator BIO* () {
			return ioObject_;
		}

		operator const BIO* () const {
			return ioObject_;
		}
	protected:
		

		//BIO_set_callback
		BIO* ioObject_;
		InputStream* inputStream_;


		
		static int readBIO(BIO *h, char *buf, int size)
		{
			CryptoInputStream* thisPtr = (CryptoInputStream*)h->ptr;

			if (NULL == thisPtr ) {
				return -1;
			}

			uint64 res = thisPtr->read( (uchar*)buf, (uint64)size );		

			return res;
		}
		
		static int getsBIO(BIO *h, char *str, int size)
		{
			CryptoInputStream* thisPtr = (CryptoInputStream*)h->ptr;

			if (NULL == thisPtr ) {
				return -1;
			}

			int totalRead = 0;
			//read in 256 byte chunks 
			int i=0;
			uint64 res = 0;
			AnsiString tmp;
			uchar buf[256];
			bool finished = false;
			int skip = 0;
			do {

				size_t read = (i * 256) + (size % 256);
				res = thisPtr->read( buf, (uint64)read );
				if ( res <= 0 ) {
					return 0;
				}
				totalRead += res;
				const uchar* P = buf;
				while ( (P-buf) < res ) {
					if ( *P == '\n' || *P == '\r' ) {
						finished = true;
						skip = 1;

						if ( (*P == '\r') && (((P-buf) + 1) < res) && (*(P+1) == '\n') ) {
							P++;
							skip = 2;
						}
						break;
					}
					P++;
				}
				
				tmp.append( (char*)buf, (P-buf) );
				if ( finished ) {					
					break;
				}
				

				i++;
			} while ( i < (size / 256) );


			uint64 pos = thisPtr->getCurrentSeekPos();
			thisPtr->seek( (pos - (totalRead - tmp.size())) + skip, stSeekFromStart );

			tmp += "\n";
			tmp.copy( str, tmp.size() );
			str[tmp.size()] = 0;		

			return tmp.size();
		}
		
		static long ctrlBIO(BIO *h, int cmd, long arg1, void *arg2)
		{
			printf( "ctrl( %p, %d, %d, %p )\n", h, cmd, arg1, arg2 );

			CryptoInputStream* thisPtr = (CryptoInputStream*)h->ptr;
			if (NULL == thisPtr ) {
				return 0;
			}

			switch (cmd) {
				case BIO_C_FILE_SEEK:  case BIO_CTRL_RESET: {
					thisPtr->seek( arg1, stSeekFromStart );
					return 1;
				}
				break;

				case BIO_C_FILE_TELL:  case BIO_CTRL_INFO: {
					return thisPtr->getCurrentSeekPos();
				}
				break;

				case BIO_CTRL_EOF: {
					return thisPtr->isEOS() ? 1 : 0;
				}
				break;

				case BIO_CTRL_GET_CLOSE: {
					return (long) h->shutdown;
				}
				break;

				case BIO_CTRL_SET_CLOSE: {
					h->shutdown=(int)arg1;
					return 1;
				}
				break;

				case BIO_CTRL_FLUSH: {
					//????????
				}
				break;

				case BIO_CTRL_WPENDING:
				case BIO_CTRL_PENDING:
				case BIO_CTRL_PUSH:
				case BIO_CTRL_POP: {
					return 0;
				}
				break;
			};
			return 1;
		}
		
		static int newBIO(BIO *h)
		{
			h->init=1;
			h->num=0;
			h->ptr=NULL;
			h->flags=BIO_FLAGS_UPLINK;
			
			return 1;
		}
		
		static int freeBIO(BIO *data)
		{
			if (data == NULL) return(0);
			if (data->shutdown) {
				
				data->ptr=NULL;
				data->flags=BIO_FLAGS_UPLINK;
				data->init=0;
			}
			
			return 1;
		}

		static BIO_METHOD* getMethod() 
		{
			static BIO_METHOD CryptoInputStreamMethod =
			{
				BIO_TYPE_SOURCE_SINK,
					"CryptoInputStream BIO",
					NULL,
					CryptoInputStream::readBIO,
					NULL,
					CryptoInputStream::getsBIO,
					CryptoInputStream::ctrlBIO,
					CryptoInputStream::newBIO,
					CryptoInputStream::freeBIO,
					NULL,
			};


			return &CryptoInputStreamMethod;
		}
	};




	

	class CryptoOutputStream : public OutputStream {
	public:

		CryptoOutputStream( OutputStream* outputStream ) : ioObject_(NULL),outputStream_(outputStream){
			VCF_ASSERT( NULL != outputStream_ );

			if ( NULL == outputStream_ ) {
				throw RuntimeException( "Cannot have a null output stream in a CryptoOutputStream instance." );
			}

			ioObject_ = BIO_new( CryptoOutputStream::getMethod() );

			ioObject_->ptr = this;
		}

		virtual ~CryptoOutputStream() {
			BIO_free(ioObject_);
		}

		virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
			outputStream_->seek( offset, offsetFrom );
		}
		
		virtual uint64 getSize() {
			return outputStream_->getSize();
		}
		
		virtual uchar* getBuffer() {
			return outputStream_->getBuffer();
		}
		
		virtual uint64 getCurrentSeekPos() {
			return outputStream_->getCurrentSeekPos();
		}
		
		virtual uint64 write( const unsigned char* bytesToWrite, uint64 sizeOfBytes ) {
			return outputStream_->write( bytesToWrite, sizeOfBytes );
		}
		
		operator BIO* () {
			return ioObject_;
		}

		operator const BIO* () const {
			return ioObject_;
		}
	protected:		
		BIO* ioObject_;
		OutputStream* outputStream_;


		
		static int writeBIO(BIO *h, const char *buf, int size)
		{
			CryptoOutputStream* thisPtr = (CryptoOutputStream*)h->ptr;

			if (NULL == thisPtr ) {
				return -1;
			}

			uint64 res = thisPtr->write( (const uchar*)buf, (uint64)size );		

			return res;
		}
		
		static int putsBIO(BIO *h, const char *str )
		{
			size_t strSz = strlen(str);
			
			return CryptoOutputStream::writeBIO( h, str, strSz );
		}
		
		static long ctrlBIO(BIO *h, int cmd, long arg1, void *arg2)
		{
			printf( "ctrl( %p, %d, %d, %p )\n", h, cmd, arg1, arg2 );
			CryptoOutputStream* thisPtr = (CryptoOutputStream*)h->ptr;
			if (NULL == thisPtr ) {
				return 0;
			}

			switch (cmd) {
				case BIO_C_FILE_SEEK:  case BIO_CTRL_RESET: {
					thisPtr->seek( arg1, stSeekFromStart );
					return 1;
				}
				break;

				case BIO_C_FILE_TELL:  case BIO_CTRL_INFO: {
					return thisPtr->getCurrentSeekPos();
				}
				break;

				case BIO_CTRL_GET_CLOSE: {
					return (long) h->shutdown;
				}
				break;

				case BIO_CTRL_SET_CLOSE: {
					h->shutdown=(int)arg1;
					return 1;
				}
				break;

				case BIO_CTRL_FLUSH: {
					//????????
				}
				break;

				case BIO_CTRL_EOF: 
				case BIO_CTRL_WPENDING:
				case BIO_CTRL_PENDING:
				case BIO_CTRL_PUSH:
				case BIO_CTRL_POP: {
					return 0;
				}
				break;
			};		

			return 1;
		}
		
		static int newBIO(BIO *h)
		{
			h->init=1;
			h->num=0;
			h->ptr=NULL;
			h->flags=BIO_FLAGS_UPLINK;
			
			return 1;
		}
		
		static int freeBIO(BIO *data)
		{
			if (data == NULL) return(0);
			if (data->shutdown) {
				
				data->ptr=NULL;
				data->flags=BIO_FLAGS_UPLINK;
				data->init=0;
			}
			
			return 1;
		}

		static BIO_METHOD* getMethod() 
		{
			static BIO_METHOD CryptoOutputStreamMethod =
			{
				BIO_TYPE_SOURCE_SINK,
					"CryptoOutputStream BIO",
					CryptoOutputStream::writeBIO,
					NULL,
					CryptoOutputStream::putsBIO,
					NULL,
					CryptoOutputStream::ctrlBIO,
					CryptoOutputStream::newBIO,
					CryptoOutputStream::freeBIO,
					NULL,
			};


			return &CryptoOutputStreamMethod;
		}
	};





	class BigInteger : public Object {
	public:
		BigInteger() {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );
		}

		BigInteger( const BigInteger& rhs ) {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );
			BN_copy(&num_, &rhs.num_ );
		}


		BigInteger( const int& rhs ) {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );			
			*this = rhs;
		}

		BigInteger( const unsigned int& rhs ) {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );			
			*this = rhs;
		}

		BigInteger( const long& rhs ) {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );			
			*this = rhs;
		}

		BigInteger( const unsigned long& rhs ) {
			memset( &num_, 0, sizeof(num_) );
			BN_init( &num_ );			
			*this = rhs;
		}


		virtual ~BigInteger() {
			BN_free( &num_ );
		}


		BigInteger& operator=( const BigInteger& rhs ) {
			
			BN_copy(&num_, &rhs.num_ );

			return *this;
		}

		BigInteger& swap( BigInteger& rhs ) {
			BN_swap(&num_, &rhs.num_ );
			return *this;
		}

		size_t getSize() const {
			return (size_t) BN_num_bytes( &num_ );
		}

		int getBits() const {
			return BN_num_bits( &num_ );
		}

		static int getBitsInULong( unsigned long val ) {
			return BN_num_bits_word( val );
		}


		bool isNegative() const {
			return BN_is_negative( &num_ ) ? true : false;
		}


		/**
		returns -1 if this < rhs, 0 if this == rhs, 1 if a > b
		*/
		int compare( const BigInteger& rhs ) const {
			return BN_cmp( &num_, &rhs.num_ );
		}

		/**
		returns -1 if abs(this) < (abs(rhs), 0 if abs(this) == (abs(rhs), 1 if abs(this) > (abs(rhs)
		*/
		int absCompare( const BigInteger& rhs ) const {
			return BN_ucmp( &num_, &rhs.num_ );
		}

		bool operator == ( const BigInteger& rhs ) const {
			return compare( rhs ) == 0;
		}

		bool operator != ( const BigInteger& rhs ) const {
			return compare( rhs ) != 0;
		}

		bool operator > ( const BigInteger& rhs ) const {
			return compare( rhs ) == 1;
		}

		bool operator >= ( const BigInteger& rhs ) const {
			return (compare( rhs ) < 0) ? false : true;
		}

		bool operator < ( const BigInteger& rhs ) const {
			return compare( rhs ) == -1;
		}

		bool operator <= ( const BigInteger& rhs ) const {
			return (compare( rhs ) > 0) ? false : true;
		}

		bool isZero() const {
			return BN_is_zero( &num_ ) ? true : false;
		}

		bool isOne() const {
			return BN_is_one( &num_ ) ? true : false;
		}

		bool isOdd() const {
			return BN_is_odd( &num_ ) ? true : false;
		}

		operator BIGNUM*() {
			return &num_;
		}

		operator const BIGNUM*() const {
			return &num_;
		}

		void setZero() {
			BN_zero( &num_ );
		}

		void setOne() {
			BN_one( &num_ );
		}

		//conversion routines...

		BigInteger& operator=( const int& rhs ) {			
			BN_set_word( &num_, abs(rhs) );			
			BN_set_negative( &num_, (rhs < 0) ? 1 : 0 );
			return *this;
		}

		BigInteger& operator=( const unsigned int& rhs ) {			
			BN_set_word( &num_, rhs );
			BN_set_negative( &num_, 0 );
			return *this;
		}

		BigInteger& operator=( const long& rhs ) {			
			BN_set_word( &num_, abs(rhs) );
			BN_set_negative( &num_, (rhs < 0) ? 1 : 0 );
			return *this;
		}

		BigInteger& operator=( const unsigned long& rhs ) {			
			BN_set_word( &num_, rhs );
			BN_set_negative( &num_, 0 );
			return *this;
		}

		operator unsigned int() const {
			return BN_get_word( &num_ );
		}

		operator int() const {
			if ( BN_is_negative(&num_) ) {
				return - BN_get_word( &num_ );
			}
			return BN_get_word( &num_ );
		}

		operator unsigned long() const {
			return BN_get_word( &num_ );
		}

		operator long() const {
			if ( BN_is_negative(&num_) ) {
				return - BN_get_word( &num_ );
			}
			return BN_get_word( &num_ );
		}

		//addition

		BigInteger& operator +=( const unsigned int& rhs ) {			
			BN_add_word( &num_, rhs );
			return *this;
		}

		BigInteger operator +( const unsigned int& rhs ) const {
			BigInteger result(*this);
			BN_add_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator +=( const int& rhs ) {			
			BN_add_word( &num_, rhs );
			return *this;
		}

		BigInteger operator +( const int& rhs ) const {
			BigInteger result(*this);
			BN_add_word( &result.num_, rhs );
			return result;
		}


		BigInteger& operator +=( const unsigned long& rhs ) {			
			BN_add_word( &num_, rhs );
			return *this;
		}

		BigInteger operator +( const unsigned long& rhs ) const {
			BigInteger result(*this);
			BN_add_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator +=( const long& rhs ) {			
			BN_add_word( &num_, rhs );
			return *this;
		}

		BigInteger operator +( const long& rhs ) const {
			BigInteger result(*this);
			BN_add_word( &result.num_, rhs );
			return result;
		}

		//subtraction

		BigInteger& operator -=( const unsigned int& rhs ) {			
			BN_sub_word( &num_, rhs );
			return *this;
		}

		BigInteger operator -( const unsigned int& rhs ) const {
			BigInteger result(*this);
			BN_sub_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator -=( const int& rhs ) {			
			BN_sub_word( &num_, rhs );
			return *this;
		}

		BigInteger operator -( const int& rhs ) const {
			BigInteger result(*this);
			BN_sub_word( &result.num_, rhs );
			return result;
		}


		BigInteger& operator -=( const unsigned long& rhs ) {			
			BN_sub_word( &num_, rhs );
			return *this;
		}

		BigInteger operator -( const unsigned long& rhs ) const {
			BigInteger result(*this);
			BN_sub_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator -=( const long& rhs ) {			
			BN_sub_word( &num_, rhs );
			return *this;
		}

		BigInteger operator -( const long& rhs ) const {
			BigInteger result(*this);
			BN_sub_word( &result.num_, rhs );
			return result;
		}


		//multiplication
		BigInteger& operator *=( const unsigned int& rhs ) {			
			BN_mul_word( &num_, rhs );
			return *this;
		}

		BigInteger operator *( const unsigned int& rhs ) const {
			BigInteger result(*this);
			BN_mul_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator *=( const int& rhs ) {			
			BN_mul_word( &num_, rhs );
			return *this;
		}

		BigInteger operator *( const int& rhs ) const {
			BigInteger result(*this);
			BN_mul_word( &result.num_, rhs );
			return result;
		}


		BigInteger& operator *=( const unsigned long& rhs ) {			
			BN_mul_word( &num_, rhs );
			return *this;
		}

		BigInteger operator *( const unsigned long& rhs ) const {
			BigInteger result(*this);
			BN_mul_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator *=( const long& rhs ) {			
			BN_mul_word( &num_, rhs );
			return *this;
		}

		BigInteger operator *( const long& rhs ) const {
			BigInteger result(*this);
			BN_mul_word( &result.num_, rhs );
			return result;
		}


		//division
		BigInteger& operator /=( const unsigned int& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator /( const unsigned int& rhs ) const {
			BigInteger result(*this);
			BN_div_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator /=( const int& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator /( const int& rhs ) const {
			BigInteger result(*this);
			BN_div_word( &result.num_, rhs );
			return result;
		}


		BigInteger& operator /=( const unsigned long& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator /( const unsigned long& rhs ) const {
			BigInteger result(*this);
			BN_div_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator /=( const long& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator /( const long& rhs ) const {
			BigInteger result(*this);
			BN_div_word( &result.num_, rhs );
			return result;
		}

		//mod
		BigInteger& operator %=( const unsigned int& rhs ) {			
			BN_mod_word( &num_, rhs );
			return *this;
		}

		BigInteger operator %( const unsigned int& rhs ) const {
			BigInteger result(*this);
			BN_mod_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator %=( const int& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator %( const int& rhs ) const {
			BigInteger result(*this);
			BN_mod_word( &result.num_, rhs );
			return result;
		}


		BigInteger& operator %=( const unsigned long& rhs ) {			
			BN_div_word( &num_, rhs );
			return *this;
		}

		BigInteger operator %( const unsigned long& rhs ) const {
			BigInteger result(*this);
			BN_mod_word( &result.num_, rhs );
			return result;
		}

		BigInteger& operator %=( const long& rhs ) {			
			BN_mod_word( &num_, rhs );
			return *this;
		}

		BigInteger operator %( const long& rhs ) const {
			BigInteger result(*this);
			BN_mod_word( &result.num_, rhs );
			return result;
		}


		//regular arithmetic

		BigInteger& operator +=( const BigInteger& rhs ) {
			BigInteger res;
			BN_add( &res.num_, &num_, &rhs.num_ );
			*this = res;
			return *this;
		}

		BigInteger operator +( const BigInteger& rhs ) const {
			BigInteger result(*this);
			result += rhs;
			return result;
		}


		BigInteger& operator -=( const BigInteger& rhs ) {
			BigInteger res;
			BN_sub( &res.num_, &num_, &rhs.num_ );
			*this = res;
			return *this;
		}

		BigInteger operator -( const BigInteger& rhs ) const {
			BigInteger result(*this);
			result -= rhs;
			return result;
		}

		BigInteger& operator *=( const BigInteger& rhs ) {
			BigInteger res;
			BN_CTX* ctx = BN_CTX_new();
			BN_CTX_init( ctx );

			BN_mul( &res.num_, &num_, &rhs.num_, ctx );

			BN_CTX_free( ctx );

			*this = res;
			return *this;
		}

		BigInteger operator *( const BigInteger& rhs ) const {
			BigInteger result(*this);
			result *= rhs;
			return result;
		}

		BigInteger& operator /=( const BigInteger& rhs ) {
			
			BN_CTX* ctx = BN_CTX_new();
			BN_CTX_init( ctx );

			BIGNUM* dv = BN_CTX_get(ctx);
			BIGNUM* rem = NULL;

			BN_div( dv, rem, &num_, &rhs.num_, ctx );

			BN_copy(&num_, dv );

			BN_CTX_free( ctx );			

			return *this;
		}

		BigInteger operator /( const BigInteger& rhs ) const {
			BigInteger result(*this);
			result /= rhs;
			return result;
		}


		BigInteger& operator %=( const BigInteger& rhs ) {
			
			BN_CTX* ctx = BN_CTX_new();
			BN_CTX_init( ctx );

			BIGNUM* dv = NULL;
			BIGNUM* rem = BN_CTX_get(ctx);

			BN_div( dv, rem, &num_, &rhs.num_, ctx );

			BN_copy(&num_, rem );

			BN_CTX_free( ctx );			

			return *this;
		}

		BigInteger operator %( const BigInteger& rhs ) const {
			BigInteger result(*this);
			result %= rhs;
			return result;
		}


		BigInteger& square() {
			BN_CTX* ctx = BN_CTX_new();
			BN_CTX_init( ctx );

			BIGNUM* res = BN_CTX_get(ctx);

			BN_sqr( res, &num_, ctx );

			BN_copy(&num_, res );

			BN_CTX_free( ctx );	
			return *this;
		}

		BigInteger pow( const BigInteger& rhs ) const {
			BigInteger result;

			BN_CTX* ctx = BN_CTX_new();
			BN_CTX_init( ctx );

			BN_exp( &result.num_, &num_, &rhs.num_, ctx );		

			BN_CTX_free( ctx );	
			return *this;
		}

		virtual String toString() {		
			char* res = BN_bn2dec( &num_ );

			String result(res);

			OPENSSL_free( res );

			return result;
		}
	protected:
		BIGNUM num_;
	};



	class Random {
	public:
		static void seed( void* dataPtr, size_t dataSize ) {
			RAND_seed(dataPtr,dataSize);
		}

		static void seed( int data ) {
			RAND_seed(&data,sizeof(data));
		}

		static void seed( double data ) {
			RAND_seed(&data,sizeof(data));
		}

		static bool seeded() {
			return RAND_status() ? true : false;
		}

		static add( void* dataPtr, size_t dataSize, double entropy ) {
			RAND_add( dataPtr, dataSize, entropy );
		}


		static void bytes( unsigned char* dataBuffer, size_t dataSize ) {
			if ( !RAND_bytes( dataBuffer, dataSize ) ) {
				throw RandomError();
			}
		}

		static void pseudoBytes( unsigned char* dataBuffer, size_t dataSize ) {
			if ( !RAND_pseudo_bytes( dataBuffer, dataSize ) ) {
				throw RandomError();
			}
		}

		static int newInt( bool pseudo=false ) {
			int result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static double newDouble( bool pseudo=false ) {
			double result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static bool newBool( bool pseudo=false ) {
			bool result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static char newChar( bool pseudo=false ) {
			char result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static short newShort( bool pseudo=false ) {
			short result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static float newFloat( bool pseudo=false ) {
			float result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static int64 newInt64( bool pseudo=false ) {
			int64 result = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&result, sizeof(result) );
			}
			else {
				Random::bytes( (unsigned char*)&result, sizeof(result) );
			}
			return result;
		}

		static DateTime newDate( bool pseudo=false ) {
			DateTime result;

			uint64 milliseconds = 0;
			if ( pseudo ) {
				Random::pseudoBytes( (unsigned char*)&milliseconds, sizeof(milliseconds) );
			}
			else {
				Random::bytes( (unsigned char*)&milliseconds, sizeof(milliseconds) );
			}

			result.setMilliseconds( milliseconds );

			return result;
		}

		static AnsiString newAnsiString( size_t length=256, bool pseudo=false ) {
			AnsiString result;
			char* tmp = new char[length];

			try {
				if ( pseudo ) {
					Random::pseudoBytes( (unsigned char*)tmp, length );
				}
				else {
					Random::bytes( (unsigned char*)tmp, length );
				}
			}
			catch ( RandomError& ) {
				delete [] tmp;
				throw ;
			}

			result.append( tmp, length );
			delete [] tmp;

			return result;
		}

		static String newString( size_t length=256, bool pseudo=false ) {
			String result;
			VCFChar* tmp = new VCFChar[length];

			try {
				if ( pseudo ) {
					Random::pseudoBytes( (unsigned char*)tmp, length );
				}
				else {
					Random::bytes( (unsigned char*)tmp, length );
				}
			}
			catch ( RandomError& ) {
				delete [] tmp;
				throw ;
			}

			result.append( tmp, length );
			delete [] tmp;

			return result;
		}
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

		MessageDigest( const EVP_MD* digest ):finished_(false),digest_(digest),resultSize_(0) {
			EVP_DigestInit( &ctx_, digest_ );
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
			
			EVP_DigestInit( &ctx_, digest_ );

			return result;
		}

		void hash( const unsigned char* bytes, size_t sizeBytes, unsigned char* outBuffer, size_t& outBufSize ) {
			update( bytes, sizeBytes );
			finish( outBuffer, outBufSize );
		}

		void finish( unsigned char* outBuffer, size_t& outBufSize ) {			
			EVP_DigestFinal( &ctx_, outBuffer, &outBufSize );			
			finished_ = true;		
			EVP_DigestInit( &ctx_, digest_ );
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
		const EVP_MD* digest_;
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

		const EVP_CIPHER* getEncryptionCipher() const {
			return encCipherImpl_;
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

		const EVP_CIPHER* getDecryptionCipher() const {
			return decCipherImpl_;
		}
	protected:
		EVP_CIPHER_CTX decryptionCtx_;
		size_t bytesDecrypted_;
		const EVP_CIPHER* decCipherImpl_;
	};


	class BlowfishECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishECB() : SymmetricEncryptionCipher(EVP_bf_ecb()), 
						SymmetricDecryptionCipher(EVP_bf_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishCBC() : SymmetricEncryptionCipher(EVP_bf_cbc()), 
						SymmetricDecryptionCipher(EVP_bf_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishCFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishCFB() : SymmetricEncryptionCipher(EVP_bf_cfb()), 
						SymmetricDecryptionCipher(EVP_bf_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class BlowfishOFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		BlowfishOFB() : SymmetricEncryptionCipher(EVP_bf_ofb()), 
						SymmetricDecryptionCipher(EVP_bf_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardECB() : SymmetricEncryptionCipher(EVP_des_ecb()), 
									SymmetricDecryptionCipher(EVP_des_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardCBC() : SymmetricEncryptionCipher(EVP_des_cbc()), 
										SymmetricDecryptionCipher(EVP_des_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardCFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardCFB() : SymmetricEncryptionCipher(EVP_des_cfb()), 
										SymmetricDecryptionCipher(EVP_des_cfb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardOFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardOFB() : SymmetricEncryptionCipher(EVP_des_ofb()), 
									SymmetricDecryptionCipher(EVP_des_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandard3CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandard3CBC() : SymmetricEncryptionCipher(EVP_des_ede3_cbc()), 
									SymmetricDecryptionCipher(EVP_des_ede3_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandardXCBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandardXCBC() : SymmetricEncryptionCipher(EVP_desx_cbc()), 
									SymmetricDecryptionCipher(EVP_desx_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandard3OFB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandard3OFB() : SymmetricEncryptionCipher(EVP_des_ede3_ofb()), 
									SymmetricDecryptionCipher(EVP_des_ede3_ofb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandard3CFB1 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandard3CFB1() : SymmetricEncryptionCipher(EVP_des_ede3_cfb1()), 
									SymmetricDecryptionCipher(EVP_des_ede3_cfb1()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandard3CFB8 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandard3CFB8() : SymmetricEncryptionCipher(EVP_des_ede3_cfb8()), 
									SymmetricDecryptionCipher(EVP_des_ede3_cfb8()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class DataEncryptionStandard3CFB64 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		DataEncryptionStandard3CFB64() : SymmetricEncryptionCipher(EVP_des_ede3_cfb64()), 
									SymmetricDecryptionCipher(EVP_des_ede3_cfb64()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	
	class AdvancedEncryptionStandard128ECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard128ECB() : SymmetricEncryptionCipher(EVP_aes_128_ecb()), 
									SymmetricDecryptionCipher(EVP_aes_128_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard192ECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard192ECB() : SymmetricEncryptionCipher(EVP_aes_192_ecb()), 
									SymmetricDecryptionCipher(EVP_aes_192_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard256ECB : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard256ECB() : SymmetricEncryptionCipher(EVP_aes_256_ecb()), 
									SymmetricDecryptionCipher(EVP_aes_256_ecb()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class AdvancedEncryptionStandard128CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard128CBC() : SymmetricEncryptionCipher(EVP_aes_128_cbc()), 
									SymmetricDecryptionCipher(EVP_aes_128_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard192CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard192CBC() : SymmetricEncryptionCipher(EVP_aes_192_cbc()), 
									SymmetricDecryptionCipher(EVP_aes_192_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard256CBC : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard256CBC() : SymmetricEncryptionCipher(EVP_aes_256_cbc()), 
									SymmetricDecryptionCipher(EVP_aes_256_cbc()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard128CFB1 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard128CFB1() : SymmetricEncryptionCipher(EVP_aes_128_cfb1()), 
									SymmetricDecryptionCipher(EVP_aes_128_cfb1()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard192CFB1 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard192CFB1() : SymmetricEncryptionCipher(EVP_aes_192_cfb1()), 
									SymmetricDecryptionCipher(EVP_aes_192_cfb1()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard256CFB1 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard256CFB1() : SymmetricEncryptionCipher(EVP_aes_256_cfb1()), 
									SymmetricDecryptionCipher(EVP_aes_256_cfb1()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class AdvancedEncryptionStandard128CFB8 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard128CFB8() : SymmetricEncryptionCipher(EVP_aes_128_cfb8()), 
									SymmetricDecryptionCipher(EVP_aes_128_cfb8()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard192CFB8 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard192CFB8() : SymmetricEncryptionCipher(EVP_aes_192_cfb8()), 
									SymmetricDecryptionCipher(EVP_aes_192_cfb8()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard256CFB8 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard256CFB8() : SymmetricEncryptionCipher(EVP_aes_256_cfb8()), 
									SymmetricDecryptionCipher(EVP_aes_256_cfb8()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};


	class AdvancedEncryptionStandard128CFB128 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard128CFB128() : SymmetricEncryptionCipher(EVP_aes_128_cfb128()), 
									SymmetricDecryptionCipher(EVP_aes_128_cfb128()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard192CFB128 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard192CFB128() : SymmetricEncryptionCipher(EVP_aes_192_cfb128()), 
									SymmetricDecryptionCipher(EVP_aes_192_cfb128()) {}
		
		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}
	};

	class AdvancedEncryptionStandard256CFB128 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:		
		AdvancedEncryptionStandard256CFB128() : SymmetricEncryptionCipher(EVP_aes_256_cfb128()), 
									SymmetricDecryptionCipher(EVP_aes_256_cfb128()) {}
		
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


	class RivestCipher4 : public  SymmetricEncryptionCipher, public  SymmetricDecryptionCipher {
	public:
		RivestCipher4() : 
		  SymmetricEncryptionCipher(EVP_rc4()), SymmetricDecryptionCipher(EVP_rc4()) {}

		void setKeyLength( size_t keyLength ) {
			EVP_CIPHER_CTX_set_key_length( &decryptionCtx_, keyLength );
			EVP_CIPHER_CTX_set_key_length( &encryptCtx_, keyLength );
		}

		void init( const unsigned char* key, size_t keyLength, 
				const unsigned char* iv, size_t ivLength ) {

			SymmetricEncryptionCipher::init( key, keyLength, iv, ivLength );
			SymmetricDecryptionCipher::init( key, keyLength, iv, ivLength );
		}

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






	typedef Delegate2<int,int> RSAKeyGenDelegate;
	typedef DelegateR<String> RSAPasswordDelegate;

	class RSAKeyPair;

	class RSAPrivateKey : public Persistable {
	public:

		RSAPasswordDelegate PasswordPrompt;

		RSAPrivateKey() : privateKey_(NULL),encryption_(NULL){}

		virtual ~RSAPrivateKey() {}


		virtual void saveToStream( OutputStream * stream ) {

			VCF_ASSERT( !passwd_.empty() );
			VCF_ASSERT( NULL != encryption_ );
			VCF_ASSERT( NULL != privateKey_ );

			if ( (NULL == encryption_) || (NULL == privateKey_) ) {
				throw InvalidPointerException( "Invalid RSAPrivateKey instance, encryption and/or rsa private key are NULL" );
			}

			CryptoOutputStream cos(stream);
			if ( !PEM_write_bio_RSAPrivateKey( cos, 
										privateKey_,
										encryption_->getEncryptionCipher(), 
										NULL,
										0,
										NULL,
										(void*)passwd_.ansi_c_str() ) ) {

				throw CryptoException(); //gets err code automatically
			}
		}

		virtual void loadFromStream( InputStream * stream ) {			
			
			CryptoInputStream cis(stream);

			typedef int (*PwdCB)(char*,int,int,void*);

			PwdCB cbPtr = NULL;
			void* cbArgPtr = NULL;
			privateKey_ = NULL;

			if ( !passwd_.empty() ) {
				cbPtr = RSAPrivateKey::knownPasswordCallback;
				cbArgPtr = (void*) passwd_.ansi_c_str();
			}
			else {
				cbPtr = RSAPrivateKey::passwordCallback;
				cbArgPtr = this;
			}

			if ( !PEM_read_bio_RSAPrivateKey( cis, 
										&privateKey_,
										cbPtr,
										cbArgPtr ) ) {

				throw CryptoException(); //gets err code automatically
			}
		}

		void setPassword( const String& passwd ) {
			passwd_ = passwd;
		}

		void setEncryptionCipher( const SymmetricEncryptionCipher* val ) {
			encryption_ = val;
		}

		friend class RSAKeyPair;
	protected:

		RSAPrivateKey( RSA* rsaKeyPair ): privateKey_(rsaKeyPair),encryption_(NULL) {

		}

		static int passwordCallback(char *buf, int size, int rwflag, void *u) {
			if ( NULL == u ) {
				return 0;
			}

			RSAPrivateKey* thisPtr = (RSAPrivateKey*)u;

			AnsiString pwd = thisPtr->PasswordPrompt();

			size_t sz = minVal<size_t>( size, pwd.size() );
			pwd.copy( buf, sz );
			return sz;
		}

		static int knownPasswordCallback(char *buf, int size, int rwflag, void *u) {
			if ( NULL == u ) {
				return 0;
			}

			AnsiString pwd = (char*)u;

			size_t sz = minVal<size_t>( size, pwd.size() );
			pwd.copy( buf, sz );
			return sz;
		}

		String passwd_;
		RSA* privateKey_;
		const SymmetricEncryptionCipher* encryption_;
	};

	class RSAKeyPair : public Object {
	public:

		RSAKeyGenDelegate RSAKeyGen; 

		enum {
			expRSA_F4 = RSA_F4,
			expRSA_3 = RSA_3
		};

		RSAKeyPair(): rsaKeyPair_(NULL){}

		~RSAKeyPair(){
			if ( NULL != rsaKeyPair_ ) {
				RSA_free( rsaKeyPair_ );
			}
		}

		bool generate( size_t bits, size_t exponent ) {

			if ( NULL != rsaKeyPair_ ) {
				RSA_free( rsaKeyPair_ );
			}

			rsaKeyPair_ = RSA_generate_key( bits, exponent, RSAKeyPair::keyPairCallback, this );



			return rsaKeyPair_ != NULL;
		}


		virtual String toString() {
			String result;

			TextOutputStream tos;
			CryptoOutputStream cos(&tos);

			RSA_print( cos, rsaKeyPair_, 0 );

			result += tos.getTextBuffer();

			return result;
		}

		RSAPrivateKey getPrivateKey() const {
			return RSAPrivateKey(rsaKeyPair_);
		}
		

		size_t getSize() const {
			return RSA_size( rsaKeyPair_ );
		}
	protected:
		RSA* rsaKeyPair_;

		static void keyPairCallback( int p, int n, void *arg ) {
			RSAKeyPair* thisPtr = (RSAKeyPair*)arg;
			thisPtr->RSAKeyGen( p, n );
		}
	};


	
};

};





#endif //_VCF_CRYPTOKIT_H__


