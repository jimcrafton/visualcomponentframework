#ifndef _VCF_VCFSTRING_H__
#define _VCF_VCFSTRING_H__
//VCFString.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{


typedef std::basic_string<char> AnsiString;


class TextCodec;


/**
\class UnicodeString VCFString.h "vcf/FoundationKit/VCFString.h"
The UnicodeString class represents a thin wrapper around the
std::basic_string class since std::basic_string cannot
be derived from (it has no virtual destructor). The
type of std::basic_string is a std::basic_string<wchar_t>
meaning that the string class maintains unicode data internally.

The main purpose of the String class is to provide a
drop in replacement for std::basic_string<wchar_t>, with an
interface that is 100% compatible. In addition we add a few
extra functions of our own:
	\li conversion operators for converting to a const char*
	or const wchar_t*
	\li conversion operators for std::basic_string<char> and
	std::basic_string<wchar_t>
	\li assignment operators for char* and wchar_t*
	\li assignment operators for std::basic_string<char> and
	std::basic_string<wchar_t>
	\li any of the various methods of basic_string that would
	ordinarily take a wchar_t* also have a matching method that
	takes a char*, with automatic conversion taking place from
	ansi to unicode.

These extra functions make it seamless to use with existing code that uses
either old C style strings and/or std::string/std::wstring instances.
For complete documentation of the std::basic_string, please see
<a href="http://www.sgi.com/tech/stl/basic_string.html">SGI's documentation</a>.

Another set of functions is used to encode or decode text using a
particular text codec isntance as specified by the TextCodec class.
These encoding/decoding methods are:
	\li decoding the current strings unicode data into some other
	form  of unicde data
	\li decoding the current string's data into an ansi string
	\li encoding the data from an ansi string and resetting the
	content of this string as a result
	\li encoding the data from another string intance into this string

In addition there are also a whole series of typedefs, again solely to make the
class compatible with the std::basic_string class.
*/
class FOUNDATIONKIT_API UnicodeString {
public:
		

	typedef char AnsiChar;

	//JC - see VCFChar.h for definiton of WideChar
	typedef VCF::WideChar UniChar;
#ifdef VCF_OSX
	typedef std::basic_string< WideChar, std::char_traits<WideChar> > StringData;
#else
	typedef std::basic_string<UniChar> StringData;
#endif
	typedef StringData::size_type size_type;


	enum {
		npos = (unsigned int)-1,
		UTF8BOMSize = sizeof(uchar) * 3,
		UTF16BOMSize = sizeof(ushort),
		UTF32BOMSize = sizeof(uint32),
		UTF8BOM = 0xEFBBBF,
		UTF16LittleEndianBOM = 0xFFFE,
		UTF16BigEndianBOM = 0xFEFF,
		UTF32LittleEndianBOM = 0xFFFE0000,
		UTF32BigEndianBOM = 0x0000FEFF
	};




	typedef StringData::traits_type traits_type;
	typedef StringData::allocator_type allocator_type;
	typedef UniChar char_type;
	typedef StringData::difference_type difference_type;
	typedef StringData::pointer pointer;
	typedef StringData::const_pointer const_pointer;
	typedef StringData::reference reference;
	typedef StringData::const_reference const_reference;
	typedef StringData::value_type value_type;
	typedef StringData::iterator iterator;
	typedef StringData::const_iterator const_iterator;
	typedef StringData::reverse_iterator reverse_iterator;
	typedef StringData::const_reverse_iterator const_reverse_iterator;


	~UnicodeString();

	UnicodeString():ansiDataBuffer_(NULL){}

	UnicodeString(const UnicodeString& rhs):ansiDataBuffer_(NULL) {
		*this = rhs;
	}

	UnicodeString(const StringData& rhs) : data_(rhs),ansiDataBuffer_(NULL) {

	}

	UnicodeString(const std::string& rhs);

	UnicodeString(const AnsiChar* string, size_type stringLength );
	UnicodeString(const UniChar* string, size_type stringLength );

	UnicodeString(const AnsiChar* string );
	UnicodeString(const UniChar* string );

	UnicodeString( size_type n, AnsiChar c );
	UnicodeString( size_type n, UniChar c );

	#ifdef VCF_OSX
	UnicodeString(const wchar_t* string );
	#endif





	/**
	Decodes the unicode data in this string and places the data in the ansi string buffer
	passed in. When the function returns the strSize variable will be modified to reflect the
	number of bytes written to the ansi string buffer.
	@param TextCodec the code to use for decoding this string's data
	@param AnsiChar* str the ansi buffer to use to write the decoded data to
	@param size_type& strSize teh number of bytes in the str buffer. UIpon returning from this 
	function this will hold the number of bytes actually written to the str buffer. The
	null terminator will be written out
	@see ansi_c_str()
	*/
	void decode_ansi( TextCodec* codec, AnsiChar* str, size_type& strSize ) const ;

	/**
	Decodes the unicode data in the string and returns a new string with the
	decoded data as determined by the text codec.
	@param TextCodec the codec used to decode the string's data
	@return UnicodeString the new string that is created as a result of
	the decode process by the codec.
	*/
	UnicodeString decode( TextCodec* codec ) const ;

	/**
	This encodes the ansi string into unicode, according to the algorithms
	in the codec, and replaces the data in the string's data_ value.
	@param TextCodec* an instance of a TextCodec that represents the
	algorithm used in encoding the data stored in str.
	@param AnsiChar* the source ansi string buffer
	@param size_type the number of bytes to encode from the str buffer
	*/
	void encode( TextCodec* codec, const AnsiChar* str, size_type n );

	/**
	This encodes the data in the unicode string into another unicode string,
	according to the algorithms in the codec, and replaces the data in
	the string's data_ value.
	@param TextCodec* an instance of a TextCodec that represents the
	algorithm used in encoding the data stored in str.
	@param UnicodeString the source unicode string to encode from
	*/
	void encode( TextCodec* codec, const UnicodeString& str );

	/**
	Returns a const char* pointer. Equivalent to the c_str() method,
	only this translates the internal unicode data to an ansi string.
	
	Please note that the pointer returned from this function is only
	valid for the lifetime of the string that it was returned from.
	Calling this function requires that a new char buffer be allocated. As
	a result of this, the string instance that allocates this buffer
	manages the memory for it and when the string instance is destroyed,
	all allocated ansi string buffers that were allocated as a result of a
	call to this method are also destroyed. If a caller needs to maintain
	this char string beyond the lifetime of the string instance it was
	retreived from, they should copy it to a new buffer, or perhaps
	a std::string instance. An example of this might look like:
	\code

	std::string localString;
	const char* strPtr = NULL;
	{
		String s = "Hello World"; //new string instance. "Hello World" is stored as unicode

		strPtr = s.ansi_c_str();

		printf( "%s", strPtr ); //strPtr now points to an ansi string allocated by the s UnicodeString instance.

		localString = strPtr; //make a copy of strPtr and store in our std::string variable

	} //s falls out of scope, and is destroyed, reclaiming all allocated char* buffers due to ansi_c_str() calls

	printf( "%s", strPtr ); //oops! strPtr will point to garbage now!

	printf( "%s", localString.c_str() );  //however localString is OK because it is a copy from strPtr

	\endcode
	*/
	const AnsiChar* ansi_c_str() const;





	/**
	Returns a const char* pointer s a result of translating the
	unicode data to an ansi string. In Win32, the default
	behaviour is to convert this using the UTF8 code page.
	
	This pointer is "garbage collected" and is only valid for the lifetime of
	the string instance that it was retreived from. Once that
	instance is destroyed, the pointer is invalid. For example:
	\code
	const char* c_stringPtr = NULL;
	{
		String s = "Hello World";

		c_stringPtr = s; //c_stringPtr should equal "Hello World"
		printf( "c_stringPtr: %s", c_stringPtr );
	}

	//c_stringPtr is now invalid, since s has been destroyed
	printf( "c_stringPtr: %s", c_stringPtr ); //will print garbage

	\endcode
	@return const AnsiChar* the value of the string as ansi.
	@see ansi_c_str()
	*/
	/*
	operator const AnsiChar*() const {
		return ansi_c_str();
	}
	*/

	/**
	Returns a const UniChar* pointer - equivalent to
	calling c_str().
	@return const UniChar* a const pointer to the string data
	@see c_str()
	*/
	/*
	operator const UniChar*() const {
		return c_str();
	}
	*/


	/**
	This is a convenience function to get at the string's
	underlying data as a const std::basic_string. Since
	it's a const reference, you can't modify anything on the
	basic_string reference returned.

	\code
	std::basic_string<UniChar> stlString;
	String myString = "Hello World";

	stlString = myString; //this makes a copy

	const std::basic_string<UniChar>& constRefString = myString; //this is a const reference - immutable
	\endcode
	@returns std::basic_string<UniChar>& a const reference to the string's
	underlying std::basic_string member variable.
	*/
	operator const StringData& () const {
		return data_;
	}

	/**
	This is a convenience function to get at the string's
	underlying data as a const std::basic_string. Since
	it's a reference, you can modify the basic_string reference returned.

	@returns std::basic_string<UniChar>& a reference to the string's
	underlying std::basic_string member variable.
	*/
	operator StringData& () {
		modified();
		return data_;
	}


	/**
	This is a convenience function that converts the string's data from
	unicode to ansi, and returns a std::basic_string<AnsiChar> (also
	known as std::string).

	@returns AnsiString a converted string
	*/
	operator AnsiString () const {	// was std::basic_string<AnsiChar> not a reference
		return AnsiString( ansi_c_str() );	// was std::basic_string<AnsiChar>
	}

	UnicodeString& operator=(const UnicodeString& rhs) {
		data_ = rhs.data_;
		modified();
		return *this;
	}

	UnicodeString& operator=(const AnsiString& s) {
		UnicodeString::transformAnsiToUnicode( s.c_str(), s.size(), data_ );
		modified();
		return *this;
	}

	UnicodeString& operator=(const AnsiChar *s);

	UnicodeString& operator=(const UniChar *s) {
		data_ = s;
		modified();
		return *this;
	}

	UnicodeString& operator=(AnsiChar c);

	UnicodeString& operator=(UniChar c) {
		data_ = c;
		modified();
		return *this;
	}


	friend bool operator ==( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator ==( const StringData& rhs ) const {
		return data_ == rhs;
	}

	bool operator ==( const UniChar* rhs ) const {
		return data_ == rhs;
	}

	friend bool operator !=( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator !=( const StringData& rhs ) const {
		return data_ != rhs;
	}

	bool operator !=( const UniChar* rhs ) const {
		return data_ != rhs;
	}

	friend bool operator <( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator <( const StringData& rhs ) const {
		return data_ < rhs;
	}
	
	bool operator <( const UniChar* rhs ) const {
		return data_ < rhs;
	}

	friend bool operator <=( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator <=( const StringData& rhs ) const {
		return data_ <= rhs;
	}

	bool operator <=( const UniChar* rhs ) const {
		return data_ <= rhs;
	}

	friend bool operator >( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator >( const StringData& rhs ) const {
		return data_ > rhs;
	}

	bool operator >( const UniChar* rhs ) const {
		return data_ > rhs;
	}

	friend bool operator >=( const UnicodeString& lhs, const UnicodeString& rhs );

	bool operator >=( const StringData& rhs ) const {
		return data_ >= rhs;
	}

	bool operator >=( const UniChar* rhs ) const {
		return data_ >= rhs;
	}

	bool operator ==( const AnsiChar* rhs ) const;
	bool operator !=( const AnsiChar* rhs ) const;
	bool operator >( const AnsiChar* rhs ) const;
	bool operator >=( const AnsiChar* rhs ) const;
	bool operator <( const AnsiChar* rhs ) const;
	bool operator <=( const AnsiChar* rhs ) const;

	iterator begin() {
		modified();
		return data_.begin();
	}

	const_iterator begin() const {
		return data_.begin();
	}

	iterator end() {
		return data_.end();
	}

	const_iterator end() const {
		return data_.end();
	}

	reverse_iterator rbegin(){
		modified();
		return data_.rbegin();
	}

	const_reverse_iterator rbegin() const{
		return data_.rbegin();
	}

	reverse_iterator rend(){
		return data_.rend();
	}

	const_reverse_iterator rend() const {
		return data_.rend();
	}

	const_reference at(size_type pos) const {
		return data_.at(pos);
	}

	reference at(size_type pos) {
		modified();
		return data_.at(pos);
	}

	const_reference operator[](size_type pos) const {
		return data_[pos];
	}

	reference operator[](size_type pos) {
		modified();
		return data_[pos];
	}



	const UniChar* c_str() const {
		return data_.c_str();
	}

	const UniChar* data() const {
		return data_.data();
	}

	size_type length() const {
		return data_.length();
	}

	/**
	Returns the number of characters in the string. This is <b>not</b> the same
	as the number of bytes that make up the string.
	@see size_in_bytes()
	*/
	size_type size() const {
		return data_.size();
	}

	/**
	The number of bytes that make up this string. This is current the size of the
	string times the size of a single character (which is 16 bits, or 2 bytes).
	*/
	size_type size_in_bytes() const {
		return data_.size() * sizeof(VCFChar);
	}

	size_type max_size() const {
		return data_.max_size();
	}

	void resize(size_type n, UniChar c = UniChar()) {
		data_.resize( n, c );
	}

	size_type capacity() const {
		return data_.capacity();
	}

	void reserve(size_type n = 0) {
		modified();
		data_.reserve( n );
	}

	bool empty() const {
		return data_.empty();
	}

	UnicodeString& operator+=(const UnicodeString& rhs) {
		data_ += rhs.data_;
		modified();
		return *this;
	}

	UnicodeString& operator+=(const UniChar *s) {
		data_ += s;
		modified();
		return *this;
	}

	UnicodeString& operator+=(UniChar c) {
		data_ += c;
		modified();
		return *this;
	}

	UnicodeString& operator+=(AnsiChar c);

	UnicodeString& operator+=(const AnsiChar* rhs );

	UnicodeString& append(const UnicodeString& str) {
		data_.append( str.data_ );
		modified();
		return *this;
	}

	UnicodeString& append(const UnicodeString& str, size_type pos, size_type n) {
		data_.append( str.data_, pos, n );
		modified();
		return *this;
	}

	UnicodeString& append(const UniChar *s, size_type n) {
		data_.append( s, n );
		modified();
		return *this;
	}

	UnicodeString& append(const AnsiChar *s, size_type n);

	UnicodeString& append(const UniChar *s){
		data_.append( s );
		modified();
		return *this;
	}

	UnicodeString& append(const AnsiChar *s);

	UnicodeString& append( size_type n, UniChar c){
		data_.append( n, c );
		modified();
		return *this;
	}

	UnicodeString& append( size_type n, AnsiChar c);

	UnicodeString& append(const_iterator first, const_iterator last){
		data_.append( first, last );
		modified();
		return *this;
	}

	UnicodeString& assign(const UnicodeString& str){
		data_.assign( str.data_ );
		modified();
		return *this;
	}

	UnicodeString& assign(const UnicodeString& str, size_type pos, size_type n) {
		data_.assign( str.data_, pos, n );
		modified();
		return *this;
	}

	UnicodeString& assign(const UniChar *s, size_type n) {
		data_.assign( s, n );
		modified();
		return *this;
	}

	UnicodeString& assign(const UniChar *s) {
		data_.assign( s );
		modified();
		return *this;
	}

	UnicodeString& assign( size_type n, UniChar c)  {
		data_.assign( n, c );
		modified();
		return *this;
	}

	UnicodeString& assign(const AnsiChar *s, size_type n);

	UnicodeString& assign(const AnsiChar *s);

	UnicodeString& assign( size_type n, AnsiChar c);

	UnicodeString& assign(const_iterator first, const_iterator last) {
		data_.assign( first, last );
		modified();
		return *this;
	}

	UnicodeString& insert(size_type p0, const UnicodeString& str) {
		data_.insert( p0, str.data_ );
		modified();
		return *this;
	}

	UnicodeString& insert(size_type p0, const UnicodeString& str, size_type pos, size_type n) {
		data_.insert( p0, str.data_, pos, n );
		modified();
		return *this;
	}

	UnicodeString& insert(size_type p0, const AnsiChar *s, size_type n);

	UnicodeString& insert(size_type p0, const UniChar *s, size_type n) {
		data_.insert( p0, s, n );
		modified();
		return *this;
	}

	UnicodeString& insert(size_type p0, const AnsiChar *s);

	UnicodeString& insert(size_type p0, const UniChar *s) {
		data_.insert( p0, s );
		modified();
		return *this;
	}

	UnicodeString& insert(size_type p0, size_type n, AnsiChar c);

	UnicodeString& insert(size_type p0, size_type n, UniChar c) {
		data_.insert( p0, n, c );
		modified();
		return *this;
	}

	iterator insert(iterator it, AnsiChar c) ;

	iterator insert(iterator it, UniChar c) {
		modified();
		return data_.insert( it, c );
	}

	void insert(iterator it, size_type n, AnsiChar c) ;

	void insert(iterator it, size_type n, UniChar c)  {
		data_.insert( it, n, c );
		modified();
	}

	void insert(iterator it, const_iterator first, const_iterator last){
		data_.insert( it, first, last );
		modified();
	}

	UnicodeString& erase(size_type p0 = 0, size_type n = npos) {
		data_.erase( p0, n );
		modified();
		return *this;
	}

	iterator erase(iterator it) {
		modified();
		return data_.erase( it );
	}

	iterator erase(iterator first, iterator last) {
		modified();
		return data_.erase( first, last );
	}

	UnicodeString& replace(size_type p0, size_type n0, const UnicodeString& str) {
		data_.replace( p0, n0, str.data_ );
		modified();
		return *this;
	}

	UnicodeString& replace(size_type p0, size_type n0, const UnicodeString& str, size_type pos, size_type n) {
		data_.replace( p0, n0, str.data_, pos, n );
		modified();
		return *this;
	}

	UnicodeString& replace(size_type p0, size_type n0, const AnsiChar *s, size_type n);

	UnicodeString& replace(size_type p0, size_type n0, const UniChar *s, size_type n) {
		data_.replace( p0, n0, s, n );
		modified();
		return *this;
	}

	UnicodeString& replace(size_type p0, size_type n0, const AnsiChar *s);

	UnicodeString& replace(size_type p0, size_type n0, const UniChar *s) {
		data_.replace( p0, n0, s );
		modified();
		return *this;
	}

	UnicodeString& replace(size_type p0, size_type n0, size_type n, AnsiChar c);

	UnicodeString& replace(size_type p0, size_type n0, size_type n, UniChar c) {
		data_.replace( p0, n0, n, c );
		modified();
		return *this;
	}

	UnicodeString& replace(iterator first0, iterator last0, const UnicodeString& str) {
		data_.replace( first0, last0, str.data_ );
		modified();
		return *this;
	}

	UnicodeString& replace(iterator first0, iterator last0, const AnsiChar *s, size_type n);

	UnicodeString& replace(iterator first0, iterator last0, const UniChar *s, size_type n)  {
		data_.replace( first0, last0, s, n );
		modified();
		return *this;
	}

	UnicodeString& replace(iterator first0, iterator last0, const AnsiChar *s);

	UnicodeString& replace(iterator first0, iterator last0, const UniChar *s) {
		data_.replace( first0, last0, s );
		modified();
		return *this;
	}

	UnicodeString& replace(iterator first0, iterator last0, size_type n, AnsiChar c);

	UnicodeString& replace(iterator first0, iterator last0, size_type n, UniChar c) {
		data_.replace( first0, last0, n, c );
		modified();
		return *this;
	}

	UnicodeString& replace(iterator first0, iterator last0, const_iterator first, const_iterator last) {
		data_.replace( first0, last0, first, last );
		modified();
		return *this;
	}

	size_type copy(AnsiChar *s, size_type n, size_type pos = 0) const;

	size_type copy(UniChar *s, size_type n, size_type pos = 0) const {
		return data_.copy( s, n, pos );
	}

	void swap(UnicodeString& str) {
		data_.swap( str.data_ );
		modified();
		str.modified();
	}

	size_type find(const UnicodeString& str, size_type pos = 0) const {
		return data_.find( str.data_, pos );
	}

	size_type find(const AnsiChar *s, size_type pos, size_type n) const;

	size_type find(const UniChar *s, size_type pos, size_type n) const {
		return data_.find( s, pos, n );
	}


	size_type find(const AnsiChar *s, size_type pos = 0) const;

	size_type find(const UniChar *s, size_type pos = 0) const {
		return data_.find( s, pos );
	}

	size_type find(AnsiChar c, size_type pos = 0) const;

	size_type find(UniChar c, size_type pos = 0) const {
		return data_.find( c, pos );
	}

	size_type rfind(const UnicodeString& str, size_type pos = npos) const {
		return data_.rfind( str.data_, pos );
	}

	size_type rfind(const AnsiChar *s, size_type pos, size_type n = npos) const;

	size_type rfind(const UniChar *s, size_type pos, size_type n = npos) const {
		return data_.rfind( s, pos, n );
	}

	size_type rfind(const AnsiChar *s, size_type pos = npos) const;

	size_type rfind(const UniChar *s, size_type pos = npos) const {
		return data_.rfind( s, pos );
	}

	size_type rfind(AnsiChar c, size_type pos = npos) const;

	size_type rfind(UniChar c, size_type pos = npos) const {
		return data_.rfind( c, pos );
	}

	size_type find_first_of(const UnicodeString& str, size_type pos = 0) const {
		return data_.find_first_of( str.data_, pos );
	}

	size_type find_first_of(const AnsiChar *s, size_type pos, size_type n) const ;

	size_type find_first_of(const UniChar *s, size_type pos, size_type n) const  {
		return data_.find_first_of( s, pos, n );
	}

	size_type find_first_of(const AnsiChar *s, size_type pos = 0) const;

	size_type find_first_of(const UniChar *s, size_type pos = 0) const {
		return data_.find_first_of( s, pos );
	}

	size_type find_first_of(AnsiChar c, size_type pos = 0) const ;

	size_type find_first_of(UniChar c, size_type pos = 0) const {
		return data_.find_first_of( c, pos );
	}

	size_type find_last_of(const UnicodeString& str, size_type pos = npos) const {
		return data_.find_last_of( str.data_, pos );
	}

	size_type find_last_of(const AnsiChar *s, size_type pos, size_type n = npos) const;

	size_type find_last_of(const UniChar *s, size_type pos, size_type n = npos) const {
		return data_.find_last_of( s, pos, n );
	}

	size_type find_last_of(const AnsiChar *s, size_type pos = npos) const;

	size_type find_last_of(const UniChar *s, size_type pos = npos) const {
		return data_.find_last_of( s, pos );
	}

	size_type find_last_of(AnsiChar c, size_type pos = npos) const;

	size_type find_last_of(UniChar c, size_type pos = npos) const  {
		return data_.find_last_of( c, pos );
	}

	size_type find_first_not_of(const UnicodeString& str, size_type pos = 0) const {
		return data_.find_first_not_of( str.data_, pos );
	}

	size_type find_first_not_of(const AnsiChar *s, size_type pos, size_type n) const;

	size_type find_first_not_of(const UniChar *s, size_type pos, size_type n) const  {
		return data_.find_first_not_of( s, pos, n );
	}

	size_type find_first_not_of(const AnsiChar *s, size_type pos = 0) const;

	size_type find_first_not_of(const UniChar *s, size_type pos = 0) const {
		return data_.find_first_not_of( s, pos );
	}

	size_type find_first_not_of(AnsiChar c, size_type pos = 0) const;

	size_type find_first_not_of(UniChar c, size_type pos = 0) const  {
		return data_.find_first_not_of( c, pos );
	}

	size_type find_last_not_of(const UnicodeString& str, size_type pos = npos) const  {
		return data_.find_last_not_of( str.data_, pos );
	}

	size_type find_last_not_of(const AnsiChar *s, size_type pos, size_type n) const;

	size_type find_last_not_of(const UniChar *s, size_type pos, size_type n) const {
		return data_.find_last_not_of( s, pos, n );
	}

	size_type find_last_not_of(const AnsiChar *s, size_type pos = npos) const;

	size_type find_last_not_of(const UniChar *s, size_type pos = npos) const {
		return data_.find_last_not_of( s, pos );
	}

	size_type find_last_not_of(AnsiChar c, size_type pos = npos) const;

	size_type find_last_not_of(UniChar c, size_type pos = npos) const {
		return data_.find_last_not_of( c, pos );
	}

	UnicodeString substr(size_type pos = 0, size_type n = npos) const  {
		return data_.substr( pos, n );
	}

	int compare(const UnicodeString& str) const {
		return data_.compare( str.data_ );
	}

	int compare(size_type p0, size_type n0, const UnicodeString& str){
		return data_.compare( p0, n0, str.data_ );
	}

	int compare(size_type p0, size_type n0, const UnicodeString& str, size_type pos, size_type n) {
		return data_.compare( p0, n0, str.data_, pos, n );
	}


	int compare(const AnsiChar *s) const;

	int compare(const UniChar *s) const {
		return data_.compare( s );
	}

	int compare(size_type p0, size_type n0, const AnsiChar *s) const;

	int compare(size_type p0, size_type n0, const UniChar *s) const {
		return data_.compare( p0, n0, s );
	}

	int compare(size_type p0, size_type n0, const AnsiChar *s, size_type pos) const;

	int compare(size_type p0, size_type n0, const UniChar *s, size_type pos) const {
		return data_.compare( p0, n0, s, pos );
	}

	static void transformAnsiToUnicode( const AnsiChar* str, size_type stringLength, StringData& newStr );

	static AnsiChar* transformUnicodeToAnsi( const UnicodeString& str );

	static UniChar transformAnsiCharToUnicodeChar( AnsiChar c );
	static AnsiChar transformUnicodeCharToAnsiChar( UniChar c );

	static int adjustForBOMMarker( AnsiChar*& stringPtr, uint32& len );
protected:
	StringData data_;
	mutable AnsiChar* ansiDataBuffer_;

	void modified() {
		if ( NULL != ansiDataBuffer_ ) {
			delete [] ansiDataBuffer_;
			ansiDataBuffer_ = NULL;
		}
	}
	
};




inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString& rhs )
{
	UnicodeString result (lhs);

	result += rhs;

	return result;

}

inline UnicodeString operator +( const UnicodeString::UniChar* lhs, const UnicodeString& rhs )
{
	UnicodeString result(lhs) ;

	result += rhs;

	return result;
}


inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString::UniChar* rhs )
{
	UnicodeString result(lhs) ;

	result += rhs;

	return result;
}


inline UnicodeString operator +( const UnicodeString::UniChar& lhs, const UnicodeString& rhs )
{
	UnicodeString result(1,lhs) ;

	result += rhs;

	return result;
}


inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString::UniChar& rhs )
{
	UnicodeString result(lhs) ;

	result += rhs;

	return result;
}


inline UnicodeString operator +( const UnicodeString::AnsiChar& lhs, const UnicodeString& rhs )
{
	UnicodeString result(1,UnicodeString::transformAnsiCharToUnicodeChar( lhs ));
	result += rhs;
	return result;
}


inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString::AnsiChar& rhs )
{
	UnicodeString result(lhs);
	result += UnicodeString::transformAnsiCharToUnicodeChar( rhs  );
	return result;
}


inline UnicodeString operator +( const UnicodeString::AnsiChar* lhs, const UnicodeString& rhs )
{
	UnicodeString result;
	UnicodeString::transformAnsiToUnicode( lhs, strlen(lhs), result );

	result += rhs;
	return result;
}


inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString::AnsiChar* rhs )
{
	UnicodeString result(lhs);
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp );

	result += tmp;
	return result;
}

inline bool operator ==( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ == rhs.data_;
}

inline bool operator !=( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ != rhs.data_;
}

inline bool operator <( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ < rhs.data_;
}

inline bool operator <=( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ <= rhs.data_;
}

inline bool operator >( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ > rhs.data_;
}

inline bool operator >=( const UnicodeString& lhs, const UnicodeString& rhs )
{
	return lhs.data_ >= rhs.data_;
}



//typedef std::basic_string<VCFChar> String;

typedef UnicodeString String;

};


#endif // _VCF_VCFSTRING_H__

/**
$Id$
*/
