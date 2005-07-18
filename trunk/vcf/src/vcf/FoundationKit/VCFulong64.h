#ifndef _VCF_VCFULONG64_H__
#define _VCF_VCFULONG64_H__
//VCFulong64.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
This is wrapper class that provides support for an unsigned 64 bit integer.
This ensures that we have a real C++ 64 bit type, as opposed to some weird typedef magic.
For platforms that support a 64bit int we just wrap that. If a platform doesn't support
this, then we would have to add some specialized routines to deal with this. This class
is intended to bu used exactly like you would a long or an int, and support the various
constructors, copy constructors, operator overloads, etc to facilitate this. For example:
\code
ulong64 num = 123;
int num2 = num;
num -= 12;
num += 1234444;
num = num / 234;

ulong64 num3(12);
ulong64 num4(num);

if ( num3 == num4 ) { //do something }
\endcode
In addition you can get the high and low 32 bit component via the hi() and lo() methods,
as in this example:
\code
ulong64 num = 0x1234abcd5678cdef;
unsigned long lo = num.lo(); //lo == 0x5678cdef
unsigned long hi = num.hi(); //hi == 0x1234abcd
\endcode
*/

class FOUNDATIONKIT_API ulong64 {
public:

#	if defined(_MSC_VER) || defined(__BORLANDC__)
		typedef unsigned __int64 u64_t;
		typedef __int64 int64_t;
#	else
		typedef unsigned long long u64_t;
		typedef long long int64_t;
#	endif



	ulong64() :data_(0){

	}

	ulong64(u64_t val) :data_(val){

	}

	ulong64(int64_t val) :data_(val){

	}

	ulong64( unsigned long val ) :data_(val){

	}

	ulong64( unsigned int val ) :data_(val){

	}

	ulong64( unsigned short val ) :data_(val){

	}

	ulong64( unsigned char val ) :data_(val){

	}

	ulong64( long val ) :data_((unsigned long)val){

	}

	ulong64( int val ) :data_((unsigned long)val){

	}

	ulong64( short val ) :data_((unsigned long)val){

	}

	ulong64( char val ) :data_((unsigned long)val){

	}

	ulong64( const ulong64& rhs ) :data_(rhs.data_){

	}

	ulong64( ulong32 valLow, ulong32 valHigh ){
		u64_t tmp = valHigh;
		tmp = tmp << 32;
		data_ = tmp | (valLow & 0xffffffff);
	}


	ulong64& operator=( const ulong64& rhs ) {
		data_ = rhs.data_;

		return *this;
	}

	ulong64& operator=( const u64_t& rhs ) {
		data_ = rhs;
		return *this;
	}

	ulong64& operator=( const int64_t& rhs ) {
		data_ = rhs;
		return *this;
	}


	ulong64& operator=( const long& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const int& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const short& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const char& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const unsigned long& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const unsigned int& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const unsigned short& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const unsigned char& rhs ) {
		data_ = rhs;

		return *this;
	}

	ulong64& operator=( const double& rhs ) {
		data_ = (long)rhs;

		return *this;
	}

	ulong64& operator=( const float& rhs ) {
		data_ = (long)rhs;
		return *this;
	}




	ulong64& operator++() {
		data_ ++;
		return *this;
	}

	ulong64& operator--() {
		data_ --;
		return *this;
	}

	ulong64 operator+( const ulong64& rhs ) const {
		ulong64 result(*this);

		result.data_ += rhs.data_;

		return result;
	}


	ulong64 operator+( const unsigned long& rhs ) const{
		ulong64 result(*this);

		result.data_ += rhs;

		return result;
	}

	ulong64 operator+( const long& rhs ) const {
		ulong64 result(*this);

		result.data_ += rhs;

		return result;
	}

	ulong64 operator+( const int& rhs ) const{
		ulong64 result(*this);

		result.data_ += rhs;

		return result;
	}

	ulong64& operator+=( const unsigned long& rhs ) {

		data_ += rhs;

		return *this;
	}

	ulong64& operator+=( const ulong64& rhs ) {

		data_ += rhs.data_;

		return *this;
	}


	ulong64 operator*( const ulong64& rhs ) const {
		ulong64 result(*this);

		result.data_ *= rhs.data_;

		return result;
	}

	ulong64 operator*( const unsigned long& rhs ) const{
		ulong64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	ulong64 operator*( const long& rhs ) const{
		ulong64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	ulong64 operator*( const int& rhs ) const{
		ulong64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	ulong64& operator*=( const unsigned long& rhs ) {

		data_ *= rhs;

		return *this;
	}

	ulong64& operator*=( const ulong64& rhs ) {

		data_ *= rhs.data_;

		return *this;
	}


	ulong64 operator/( const ulong64& rhs ) const{
		ulong64 result(*this);

		result.data_ /= rhs.data_;

		return result;
	}

	ulong64 operator/( const unsigned long& rhs ) const{
		ulong64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	ulong64 operator/( const long& rhs ) const {
		ulong64 result(*this);

		result.data_ /= rhs;

		return result;
	}


	ulong64 operator/( int rhs ) const {
		ulong64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	ulong64 operator/( const char& rhs ) const{
		ulong64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	ulong64& operator/=( const unsigned long& rhs ) {

		data_ /= rhs;

		return *this;
	}

	ulong64& operator/=( const ulong64& rhs ) {

		data_ /= rhs.data_;

		return *this;
	}


	ulong64 operator%( const ulong64& rhs ) const{
		ulong64 result(*this);

		result.data_ %= rhs.data_;

		return result;
	}

	ulong64 operator%( const unsigned long& rhs ) const{
		ulong64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	ulong64 operator%( const long& rhs ) const {
		ulong64 result(*this);

		result.data_ %= rhs;

		return result;
	}


	ulong64 operator%( int rhs ) const {
		ulong64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	ulong64 operator%( const char& rhs ) const{
		ulong64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	ulong64& operator%=( const unsigned long& rhs ) {

		data_ %= rhs;

		return *this;
	}

	ulong64& operator%=( const ulong64& rhs ) {

		data_ %= rhs.data_;

		return *this;
	}


	ulong64 operator-( const ulong64& rhs ) const{
		ulong64 result(*this);

		result.data_ -= rhs.data_;

		return result;
	}

	ulong64 operator-( const unsigned long& rhs ) const{
		ulong64 result(*this);

		result.data_ -= rhs;

		return result;
	}

	ulong64 operator-( const long& rhs ) const{
		ulong64 result(*this);

		result.data_ -= rhs;

		return result;
	}

	ulong64& operator-=( const ulong64& rhs ) {

		data_ -= rhs.data_;

		return *this;
	}

	ulong64& operator-=( const unsigned long& rhs ) {

		data_ -= rhs;

		return *this;
	}

	//comparison

	bool operator> (const ulong64& rhs ) const{
		return data_ > rhs.data_;
	}

	bool operator< (const ulong64& rhs ) const{
		return data_ < rhs.data_;
	}

	bool operator>= (const ulong64& rhs ) const{
		return data_ >= rhs.data_;
	}

	bool operator<= (const ulong64& rhs ) const{
		return data_ <= rhs.data_;
	}

	bool operator!= (const ulong64& rhs ) const{
		return data_ != rhs.data_;
	}

	bool operator== (const ulong64& rhs ) const{
		return data_ == rhs.data_;
	}

	//converstion routines

	operator char() const {
		return (char)data_;
	}

	operator unsigned char() const {
		return (unsigned char)data_;
	}

	operator short() const {
		return (short)data_;
	}

	operator unsigned short() const {
		return (unsigned short)data_;
	}

	operator long() const {
		return (long)data_;
	}

	operator unsigned long() const {
		return (unsigned long)data_;
	}

	operator int() const {
		return (int)data_;
	}

	operator unsigned int() const {
		return (unsigned int)data_;
	}

	operator double() const {
		return (double)(int64_t)data_;//(signed __int64)data_;
	}

	operator int64_t() const {
		return (int64_t)data_;//(signed __int64)data_;
	}

	operator u64_t() const {
		return (u64_t)data_;
	}



	/**
	This returns the top 32 bits of the number
	*/
	unsigned long hi() const {
		unsigned long result = 0;
		result = data_ >> 32;
		return result;
	}

	/**
	This returns the low 32 bits of the number
	*/
	unsigned long lo() const {
		unsigned long result = 0;
		result = data_ & 0xffffffff;
		return result;
	}

	/**
	This sets the top 32 bits of the number
	*/
	void hi( unsigned long val ) {
		u64_t tmp = val;
		tmp = tmp << 32;
		data_ = tmp | (data_ & 0xffffffff);
	}

	/**
	This sets the low 32 bits of the number
	*/
	void lo( unsigned long val ) {
		/**
		kind of hacky but GCC won't let me do this
		data_ = val | (data_ & 0xffffffff00000000);
		since it complains about a constant value being too big.
		Cie la vie! :)
		*/

		u64_t tmp = data_ >> 32;
		data_ = (tmp << 32) | val;
	}

	u64_t data_;
};








class FOUNDATIONKIT_API long64 {
public:

#	if defined(_MSC_VER) || defined(__BORLANDC__)
		typedef __int64 int64_t;
#	else
		typedef long long int64_t;
#	endif



	long64() :data_(0){

	}
	

	long64(int64_t val) :data_(val){

	}

	long64( unsigned long val ) :data_(val){

	}

	long64( unsigned int val ) :data_(val){

	}

	long64( unsigned short val ) :data_(val){

	}

	long64( unsigned char val ) :data_(val){

	}

	long64( long val ) :data_((unsigned long)val){

	}

	long64( int val ) :data_((unsigned long)val){

	}

	long64( short val ) :data_((unsigned long)val){

	}

	long64( char val ) :data_((unsigned long)val){

	}

	long64( const long64& rhs ) :data_(rhs.data_){

	}

	long64( ulong32 valLow, ulong32 valHigh ){
		int64_t tmp = valHigh;
		tmp = tmp << 32;
		data_ = tmp | (valLow & 0xffffffff);
	}


	long64& operator=( const long64& rhs ) {
		data_ = rhs.data_;

		return *this;
	}
	

	long64& operator=( const int64_t& rhs ) {
		data_ = rhs;
		return *this;
	}


	long64& operator=( const long& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const int& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const short& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const char& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const unsigned long& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const unsigned int& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const unsigned short& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const unsigned char& rhs ) {
		data_ = rhs;

		return *this;
	}

	long64& operator=( const double& rhs ) {
		data_ = (long)rhs;

		return *this;
	}

	long64& operator=( const float& rhs ) {
		data_ = (long)rhs;
		return *this;
	}




	long64& operator++() {
		data_ ++;
		return *this;
	}

	long64& operator--() {
		data_ --;
		return *this;
	}

	long64 operator+( const long64& rhs ) const {
		long64 result(*this);

		result.data_ += rhs.data_;

		return result;
	}


	long64 operator+( const unsigned long& rhs ) const{
		long64 result(*this);

		result.data_ += rhs;

		return result;
	}

	long64 operator+( const long& rhs ) const {
		long64 result(*this);

		result.data_ += rhs;

		return result;
	}

	long64 operator+( const int& rhs ) const{
		long64 result(*this);

		result.data_ += rhs;

		return result;
	}

	long64& operator+=( const unsigned long& rhs ) {

		data_ += rhs;

		return *this;
	}

	long64& operator+=( const long64& rhs ) {

		data_ += rhs.data_;

		return *this;
	}


	long64 operator*( const long64& rhs ) const {
		long64 result(*this);

		result.data_ *= rhs.data_;

		return result;
	}

	long64 operator*( const unsigned long& rhs ) const{
		long64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	long64 operator*( const long& rhs ) const{
		long64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	long64 operator*( const int& rhs ) const{
		long64 result(*this);

		result.data_ *= rhs;

		return result;
	}

	long64& operator*=( const int& rhs ) {

		data_ *= rhs;

		return *this;
	}

	long64& operator*=( const unsigned long& rhs ) {

		data_ *= rhs;

		return *this;
	}

	long64& operator*=( const long64& rhs ) {

		data_ *= rhs.data_;

		return *this;
	}


	long64 operator/( const long64& rhs ) const{
		long64 result(*this);

		result.data_ /= rhs.data_;

		return result;
	}

	long64 operator/( const unsigned long& rhs ) const{
		long64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	long64 operator/( const long& rhs ) const {
		long64 result(*this);

		result.data_ /= rhs;

		return result;
	}


	long64 operator/( int rhs ) const {
		long64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	long64 operator/( const char& rhs ) const{
		long64 result(*this);

		result.data_ /= rhs;

		return result;
	}

	long64& operator/=( const unsigned long& rhs ) {

		data_ /= rhs;

		return *this;
	}

	long64& operator/=( const long64& rhs ) {

		data_ /= rhs.data_;

		return *this;
	}


	long64 operator%( const long64& rhs ) const{
		long64 result(*this);

		result.data_ %= rhs.data_;

		return result;
	}

	long64 operator%( const unsigned long& rhs ) const{
		long64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	long64 operator%( const long& rhs ) const {
		long64 result(*this);

		result.data_ %= rhs;

		return result;
	}


	long64 operator%( int rhs ) const {
		long64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	long64 operator%( const char& rhs ) const{
		long64 result(*this);

		result.data_ %= rhs;

		return result;
	}

	long64& operator%=( const unsigned long& rhs ) {

		data_ %= rhs;

		return *this;
	}

	long64& operator%=( const long64& rhs ) {

		data_ %= rhs.data_;

		return *this;
	}


	long64 operator-( const long64& rhs ) const{
		long64 result(*this);

		result.data_ -= rhs.data_;

		return result;
	}

	long64 operator-( const unsigned long& rhs ) const{
		long64 result(*this);

		result.data_ -= rhs;

		return result;
	}

	long64 operator-( const long& rhs ) const{
		long64 result(*this);

		result.data_ -= rhs;

		return result;
	}

	long64& operator-=( const long64& rhs ) {

		data_ -= rhs.data_;

		return *this;
	}

	long64& operator-=( const unsigned long& rhs ) {

		data_ -= rhs;

		return *this;
	}

	//comparison

	bool operator> (const long64& rhs ) const{
		return data_ > rhs.data_;
	}

	bool operator< (const long64& rhs ) const{
		return data_ < rhs.data_;
	}

	bool operator>= (const long64& rhs ) const{
		return data_ >= rhs.data_;
	}

	bool operator<= (const long64& rhs ) const{
		return data_ <= rhs.data_;
	}

	bool operator!= (const long64& rhs ) const{
		return data_ != rhs.data_;
	}

	bool operator== (const long64& rhs ) const{
		return data_ == rhs.data_;
	}

	//converstion routines

	operator char() const {
		return (char)data_;
	}

	operator unsigned char() const {
		return (unsigned char)data_;
	}

	operator short() const {
		return (short)data_;
	}

	operator unsigned short() const {
		return (unsigned short)data_;
	}

	operator long() const {
		return (long)data_;
	}

	operator unsigned long() const {
		return (unsigned long)data_;
	}

	operator int() const {
		return (int)data_;
	}

	operator unsigned int() const {
		return (unsigned int)data_;
	}

	operator double() const {
		return (double)(int64_t)data_;//(signed __int64)data_;
	}

	operator int64_t() const {
		return (int64_t)data_;//(signed __int64)data_;
	}
	


	/**
	This returns the top 32 bits of the number
	*/
	unsigned long hi() const {
		unsigned long result = 0;
		result = data_ >> 32;
		return result;
	}

	/**
	This returns the low 32 bits of the number
	*/
	unsigned long lo() const {
		unsigned long result = 0;
		result = data_ & 0xffffffff;
		return result;
	}

	/**
	This sets the top 32 bits of the number
	*/
	void hi( unsigned long val ) {
		int64_t tmp = val;
		tmp = tmp << 32;
		data_ = tmp | (data_ & 0xffffffff);
	}

	/**
	This sets the low 32 bits of the number
	*/
	void lo( unsigned long val ) {
		/**
		kind of hacky but GCC won't let me do this
		data_ = val | (data_ & 0xffffffff00000000);
		since it complains about a constant value being too big.
		Cie la vie! :)
		*/

		int64_t tmp = data_ >> 32;
		data_ = (tmp << 32) | val;
	}

	int64_t data_;
};


};// end of namespace


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.4  2005/07/09 23:15:06  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/23 21:12:35  marcelloptr
*added *=, /= and %= operators to lon64 and ulong64 classes
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/31 12:22:52  kiklop74
*Minor tweak in long64 class needed to properly define type for bcc
*
*Revision 1.1.2.7  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.6  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.5  2004/07/05 01:01:55  marcelloptr
*added ulong64 ctor, operators and toString conversion
*
*Revision 1.1.2.4  2004/06/16 15:40:47  marcelloptr
*just some comments
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_VCFULONG64_H__


