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

#define USE_STRINGPOOL

#ifdef USE_STRINGPOOL
	#include <deque>

	#ifdef _MSC_VER 
		#include <comdef.h>
	#endif 
#endif



namespace VCF  {


typedef std::basic_string<char> AnsiString;


class TextCodec;






#ifdef USE_STRINGPOOL
	


typedef VCFChar U16Char;






inline size_t RoundUp(size_t cb, size_t units)
{
    return ((cb + units - 1) / units) * units;
}

//#define HAVE_MMX


class StringPool;
class FastString;


union MemHeader {
	struct {
		//MemHeader* prev;			
		size_t  size;
		unsigned char* next;
		unsigned char* limit;
		size_t refcount;
	};
	U16Char alignment; //here to align the struct
};


class StringData;

typedef void* (*UnmanagedAllocatorFunc)( size_t sizeBytesToAlloc );
typedef void (*UnmanagedDeallocatorFunc)( void* ptr, size_t sizeBytesToFree );


class StringExtraData;

class StringData {
private:

	enum StringStateBits {
		NotPoolManaged =	0x0001,
		SubString	=	0x0002,
	};

	StringData(){}


	friend class StringPool;
	friend class FastString;

	U16Char* strPtr;
	size_t length;
	size_t refcount;
	MemHeader* memHdr;
	StringPool* pool;	
	uint32 hashID;
	char* ansiStrPtr;
	StringExtraData* extra;
	uint32 bits;
};	




class StringRange {
public:
	StringRange():strPtr(NULL),length(0){}
	StringRange(const U16Char* s, size_t l): strPtr(s),length(l){}

	const U16Char* strPtr;
	size_t length;
};






class FOUNDATIONKIT_API StringPool {
public:
	enum { 
		MIN_CBCHUNK = 32000,
        MAX_CHARALLOC = 0xFFFFFFFF-1, //too low?? 1024*1024,
		NoEntry = (uint32)-1,
	};


	StringPool();
	~StringPool();	



	//utility functions 
	static bool freeMem( void* ptr, size_t ptrMemBytesToFree ) {
		#ifdef WIN32
			bool result = ::VirtualFree( ptr, ptrMemBytesToFree, MEM_RELEASE ) ? true : false;
			if ( !result ) {
				printf( "StringPool::freeMem failed. GetLastError(): %d\n", ::GetLastError() );
			}

			return result;
		#endif
	}

	static void* allocMem( size_t sizeBytesToAllocate ) {
		void* result = NULL;
		#ifdef WIN32
			result = ::VirtualAlloc(NULL, sizeBytesToAllocate, MEM_COMMIT, PAGE_READWRITE);
		#endif

		return result;

	}


	static size_t wstrlen( const U16Char *s1 ) {
		return ::wcslen( (const wchar_t*)s1 );
	}

	static const U16Char* wmemchr( const U16Char* buf, U16Char c, size_t count ) {
		return  (const U16Char*) ::wmemchr( (const wchar_t*)buf, c, count );
	}

	static int wmemcmp(const U16Char *s1, const U16Char *s2, size_t n) {
		int result = 0;

		#ifdef HAVE_MMX
		size_t numChars = (n / 4); //4 chars at a time
		size_t leftOver = (n % 4);

		__asm {
			emms
			mov         esi, s1            // input pointer
			mov         edi, s2              // output pointer
			mov         ecx, numChars
	do_loop:

			dec         ecx
			jnz         do_loop
			emms
		}
		#else
		result = ::wmemcmp( (const wchar_t*)s1, (const wchar_t*)s2, n );
		#endif
		return result;
	}

	static U16Char* wmemcpy( U16Char* dest, const U16Char* src, uint32 len ) {
		U16Char* result = dest;
#ifdef HAVE_MMX
		size_t numChars = (len / 4); //4 chars at a time
		size_t leftOver = (len % 4);

		__asm {
			emms
			mov         esi, src            // input pointer
			mov         edi, dest              // output pointer
			mov         ecx, numChars
	do_loop:
			movq        mm0, [esi]
			movq        [edi], mm0

			add         esi, 8
			add         edi, 8

			dec         ecx
			jnz         do_loop
			

			emms //reset to fpu
		}
		if ( leftOver > 0 ) {
			memcpy( dest + numChars*4, src + numChars*4, leftOver );
		}

#else
		result = ::wmemcpy( (wchar_t*)dest, (wchar_t*)src, len );
#endif

		return result;
	}


	

	static uint32 hash( const U16Char* str, size_t length )
    {
        uint32 result = 0;
		size_t len = length < 256 ? length : 256;
#if 1
		result = 0;
		for (size_t i=0;i<len;i+=1 ) {        
            result = str[i] + (result << 6) + (result << 16) - result;			
		}
#else
		//alternate hash algorithm
		unsigned char *bp = (unsigned char *)str; /* start of buffer */
		unsigned char *be = bp + length*sizeof(U16Char);    /* beyond end of buffer */

		uint32 hval = 0x811c9dc5;

		/* FNV-1 hash each octet in the buffer */
		while (bp < be) {
			/* multiply by the 32 bit FNV magic prime mod 2^32 */
			hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);

			/* xor the bottom with the current octet */
			hval ^= (uint32)*bp++;
		}
		/* return our new hash value */
      
		result = hval;
#endif

        return result;
    }






	//core public functions
	StringData* allocate(const U16Char* begin, const U16Char* end);
	StringData* allocate( size_t length );


	StringData* transformAnsiToUnicode( const char* str, size_t length, int encoding );

	//adds a series of string pointers together to form one single string data instance
	//used by FastString::set
	StringData* concatenate( const std::vector<StringRange>& strArray );
	


	StringData* find( const U16Char* str, size_t length, const uint32& hash = 0 );

	void debug();

	static StringData* allocateUnmanagedString( const U16Char* str, size_t length );
	static StringData* allocateUnmanagedString( const char* str, size_t length, int encoding );

	static bool isSubString( StringData* handle );

	static StringData* addString( const U16Char* str, size_t length );
	static StringData* addString( const char* str, size_t length, int encoding );

	static uint32 incStringRefcount( StringData* handle );
	static uint32 decStringRefcount( StringData* handle );
	static bool equals( StringData* lhs, StringData* rhs );
	static int compare( StringData* lhs, StringData* rhs );
	
	static StringData* insert( StringData* src, StringData* dest, size_t insertPos );
	static StringData* insert( const U16Char* src, size_t srcLength, StringData* dest, size_t insertPos );
	static StringData* insert( U16Char ch, StringData* dest, size_t insertPos, size_t repeatCount );
	static StringData* erase( StringData* src, size_t startPos, size_t length );
	static StringData* subStr( StringData* src, size_t startPos, size_t length );

	static char* transformToAnsi( StringData* handle, int encoding );	
	
	size_t uniqueEntries() const {
		return stringMap_.size();
	}

	size_t totalBytesAllocated() {
		return totalBytesAllocated_;
	}


	uint32 getThreadID() const {
		return threadID_;
	}

	void makeCurrentPool() {
		StringPool::stringPoolStack->push_back(this);
	}

	static StringPool* popCurrentPool() {
		if ( NULL == StringPool::stringPoolStack ) {
			return NULL;
		}
		else if ( StringPool::stringPoolStack->empty() ) {
			return NULL;
		}

		StringPool* result = getCurrentPool();

		StringPool::stringPoolStack->pop_back();

		return result;
	}

	bool compactsMemory() const {
		return compactMemory_;
	}

	void setCompactsMemory( bool val ) {
		compactMemory_ = val;
	}

	bool onlyUsesMemoryPooling() const {
		return onlyUseMemPooling_;
	}

	void setOnlyUsesMemoryPooling( bool val );

	static unsigned int getNativeEncoding(int encoding);

	static StringPool* getCurrentPool() {

		if ( NULL == StringPool::stringPoolStack ) {
			return NULL;
		}

		if ( StringPool::stringPoolStack->empty() ) {
			return NULL;
		}

		return StringPool::stringPoolStack->back();
	}	

	static StringPool* getUsablePool();





	static void terminate();
private:

	UnmanagedAllocatorFunc stringAllocator_;
	UnmanagedDeallocatorFunc stringDeallocator_;

	static void* defStrAlloc( size_t sizeInBytes ) {
		return ::malloc( sizeInBytes );
	}

	static void defStrDealloc( void* ptr, size_t ) {
		::free(ptr);
	}

	bool onlyUseMemPooling_;

	unsigned char*  next_;   // first available byte
	unsigned char*  limit_;  // one past last available byte
	std::vector<MemHeader*> allocatedHdrs_;

	MemHeader* nextHdr( MemHeader* current );
	MemHeader* prevHdr( MemHeader* current );

	MemHeader* currentHdr_;   // current block
	size_t   granularity_;
	
	size_t totalBytesAllocated_;
	uint32 threadID_;
	bool compactMemory_;

	void initStringData( StringData* data, const U16Char* strPtr, size_t length );
	
	


	void freeStringData( StringData* handle );
	void freeMemHeader( MemHeader* memHdr );
	
	typedef std::multimap<uint32,StringData*> StringMapT;
	//typedef std::map<uint32,StringData*> StringMapT;

	typedef StringMapT::iterator StringMapIter;
	typedef StringMapT::const_iterator StringMapConstIter;
	typedef std::pair<StringMapIter,StringMapIter> StringMapRangeT;
	typedef std::pair<StringMapConstIter,StringMapConstIter> StringMapConstRangeT;
	typedef StringMapT::value_type StringMapPairT;

	StringMapT stringMap_;


	static std::deque<StringPool*>* stringPoolStack;


	static DWORD threadPoolTLSIndex;
	class StringPoolTLSGuard {
	public:
		StringPoolTLSGuard() {}

		~StringPoolTLSGuard() {

			std::vector<StringPool*>::iterator it = threadPools.begin();
			while ( it != threadPools.end() ) {
				StringPool* pool = *it;
				delete pool;
				++it;
			}

			if ( 0 != StringPool::threadPoolTLSIndex ) {
				TlsFree( StringPool::threadPoolTLSIndex );
			}
		}

		std::vector<StringPool*> threadPools;
	};

	friend class StringPoolTLSGuard;

	static StringPoolTLSGuard* poolTLSGuard;
};



class StringLiteral {
public:
	enum {
		InitialStorageSize = 256
	};
	StringLiteral():strPtr_(NULL){}
	StringLiteral( const StringLiteral& rhs ){}
	StringLiteral( const char* s ):strPtr_(NULL){
		size_t len = strlen(s);
		if ( len > storage.size() ) {
			storage.resize(len);
		}
		
		do {
			len --;
			storage[len] = s[len];
		}while ( len != 0 );

		strPtr_ = &storage[0];
	}
	StringLiteral( const U16Char* s ):strPtr_(s){}

	operator const U16Char* () const {
		return strPtr_;
	}
protected:
	static std::vector<U16Char> storage;
	const U16Char* strPtr_;
};



/**
our immutable string class
*/
class FOUNDATIONKIT_API FastString {
public:


	enum LanguageEncoding { 
		leUnknown = -1,
		leDefault = 0,
		leIBM037 = 100,
		leIBM437,
		leIBM500,
		leArabic708,
		leArabic449,
		leArabicTransparent,
		leDOSArabic,
		leGreek,
		leBaltic,
		leLatin1,
		leLatin2,
		leCyrillic,
		leTurkish,
		leMultilingualLatin1,
		lePortuguese,
		leIcelandic,
		leHebrew,
		leFrenchCanadian,
		leArabic864,
		leNordic,
		leRussianCyrillic,
		leModernGreek,
		leEBCDICLatin2,
		leThai,
		leEBCDICGreekModern,
		leShiftJIS,
		leSimplifiedChinese,
		leKorean,
		leChineseTraditionalBig5,
		leEBCDICTurkish,
		leEBCDICLatin1,
		leEBCDICUSCanada,
		leEBCDICGermany,
		leEBCDICDenmarkNorway,
		leEBCDICFinlandSweden,
		leEBCDICItaly,
		leEBCDICLatinAmericaSpain,
		leEBCDICUnitedKingdom,
		leEBCDICFrance,
		leEBCDICInternational,
		leEBCDICIcelandic,
		leUTF16LittleEndianByteOrder,
		leUTF16BigEndianByteOrder,
		leANSICentralEuropean,
		leANSICyrillic,
		leANSILatin1,
		leANSIGreek,
		leANSITurkish,
		leANSIHebrew,
		leANSIArabic,
		leANSIBaltic,
		leANSIVietnamese,
		leJohabKorean,
		leMacRoman,
		leMacJapanese,
		leMacTraditionalChineseBig5,
		leMacKorean,
		leMacArabic,
		leMacHebrew,
		leMacGreek,
		leMacCyrillic,
		leMacSimplifiedChinese,
		leMacRomanian,
		leMacUkrainian,
		leMacThai,
		leMacLatin2,
		leMacIcelandic,
		leMacTurkish,
		leMacCroatian,
		leUTF32LittleEndianByteOrder,
		leUTF32BigEndianByteOrder,
		leCNSTaiwan,
		leTCATaiwan,
		leEtenTaiwan,
		leIBM5550Taiwan,
		leTeleTextTaiwan,
		leWangTaiwan,
		leIA5WesternEuropean,
		leIA5German,
		leIA5Swedish,
		leIA5Norwegian,
		leUSASCII,
		leT61,
		leISO6937,
		leIBM273Germany,
		leIBM277DenmarkNorway,
		leIBM278FinlandSweden,
		leIBM280Italy,
		leIBM284LatinAmericaSpain,
		leIBM285UnitedKingdom,
		leIBM290JapaneseKatakanaExt,
		leIBM297France,
		leIBM420Arabic,
		leIBM423Greek,
		leIBM424Hebrew,
		leIBMKoreanExtended,
		leIBMThai,
		leRussianKOI8R,
		leIBM871Icelandic,
		leIBM880CyrillicRussian,
		leIBM905Turkish,
		leIBM00924Latin1,
		leEUCJapaneseJIS,
		leSimplifiedChineseGB2312,
		leKoreanWansung,
		leEBCDICCyrillicSerbianBulgarian,
		leUkrainianKOI8U,
		leISO88591Latin1,
		leISO88592CentralEuropean,
		leISO88593Latin3,
		leISO88594Baltic,
		leISO88595Cyrillic,
		leISO88596Arabic,
		leISO88597Greek,
		leISO88598HebrewVisual,
		leISO88599Turkish,
		leISO885913Estonian,
		leISO885915Latin9,
		leEuropa3,
		leISO88598HebrewLogical,
		leISO2022JapaneseNoHalfwidthKatakana,
		leISO2022JapaneseWithHalfwidthKatakana,
		leISO2022JapaneseAllow1ByteKana,
		leISO2022Korean,
		leISO2022SimplifiedChinese,
		leISO2022TraditionalChinese,
		leEBCDICJapaneseExt,
		leEBCDICUSCanadaAndJapanese,
		leEBCDICKoreanExtAndKorean,
		leEBCDICSimplifiedChineseExtSimplifiedChinese,
		leEBCDICSimplifiedChinese,
		leEBCDICUSCanadaAndTraditionalChinese,
		leEBCDICJapaneseLatinExtAndJapanese,
		leEUCJapanese,
		leEUCSimplifiedChinese,
		leEUCKorean,
		leEUCTraditionalChinese,
		leHZGB2312SimplifiedChinese,
		leGB18030SimplifiedChinese,
		leISCIIDevanagari,
		leISCIIBengali,
		leISCIITamil,
		leISCIITelugu,
		leISCIIAssamese,
		leISCIIOriya,
		leISCIIKannada,
		leISCIIMalayalam,
		leISCIIGujarati,
		leISCIIPunjabi,
		leUTF7,
		leUTF8
	};

	typedef char AnsiChar;

	//JC - see VCFChar.h for definiton of WideChar
	typedef VCF::WideChar UniChar;

	#ifdef VCF_OSX
	typedef std::basic_string< WideChar, std::char_traits<WideChar> > STLString;
#else
	typedef std::basic_string<UniChar> STLString;
#endif
	typedef STLString::size_type size_type;

	enum BOMMarkers {		
		UTF8BOMSize = sizeof(uchar) * 3,
		UTF16BOMSize = sizeof(ushort),
		UTF32BOMSize = sizeof(uint32),
		UTF8BOM = 0xEFBBBF,
		UTF16LittleEndianBOM = 0xFFFE,
		UTF16BigEndianBOM = 0xFEFF,
		UTF32LittleEndianBOM = 0xFFFE0000,
		UTF32BigEndianBOM = 0x0000FEFF
	};

	typedef STLString::traits_type traits_type;
	typedef STLString::allocator_type allocator_type;


	typedef UniChar char_type;

	//Note that this is const only for iterator
	//access
    typedef const U16Char* const_iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef U16Char value_type;
    typedef const U16Char *const_pointer;
    typedef const U16Char& const_reference;

	#if (_MSC_VER <= 1200) && !defined(__GNUC__)
	//	typedef std::reverse_iterator<iterator, value_type,
	//				reference, pointer, difference_type> reverse_iterator;

		typedef std::reverse_iterator<const_iterator, value_type,
					const_reference, const_pointer, difference_type>
					const_reverse_iterator;
	#else
//		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	#endif
		

	enum {
		npos = (size_type) -1
	};



	//basic_string compat
	FastString( size_t count, const U16Char& ch ): data_(NULL)  {
		FastString::STLString tmp(count, ch );
		assign( tmp.c_str(), tmp.size() );
	}

	FastString( const U16Char& ch ): data_(NULL)  {
		assign( &ch, 1 );
	}

	FastString( const U16Char* str ): data_(NULL)  {
		assign( str, StringPool::wstrlen(str) );
	}

	FastString( const U16Char* str, size_t length ): data_(NULL) {
		assign( str, length );
	}

	
	FastString( const char* str ): data_(NULL)  {
		assign( str, strlen(str) );
	}

	FastString( const char* str, size_t length, LanguageEncoding encoding=leDefault ): data_(NULL) {
		assign( str, length, encoding );
	}

	FastString( const unsigned char* str, size_t length, LanguageEncoding encoding=leDefault ): data_(NULL) {
		assign( (const char*)str, length, encoding );
	}

	FastString( const AnsiString& str, LanguageEncoding encoding=leDefault ): data_(NULL) {
		assign( str.c_str(), str.size(), encoding );
	}

	FastString( const STLString& str ): data_(NULL) {
		assign( str.c_str(), str.size() );
	}

	FastString(): data_(NULL){}

	FastString( const FastString& f ):data_(f.data_) {
		StringPool::incStringRefcount(data_);
	}


	~FastString() {
		StringPool::decStringRefcount(data_);
	}

	FastString& operator=( const U16Char* rhs ) {
		assign( rhs, StringPool::wstrlen(rhs) );
		return *this;
	}

	FastString& operator=( const char* rhs ) {
		assign( rhs, strlen(rhs) );
		return *this;
	}

	FastString& operator=( const FastString& rhs ) {
		if ( data_ != rhs.data_ ) {
			StringPool::decStringRefcount(data_);

			data_ = rhs.data_;

			StringPool::incStringRefcount(data_);
		}
		return *this;
	}

	void assign( const U16Char* str, size_t length ) {
		StringPool::decStringRefcount(data_);

		data_ = StringPool::addString( str, length );
		
		StringPool::incStringRefcount(data_);
	}

	void assign( const char* str, size_t length, LanguageEncoding encoding=leDefault ) {
		StringPool::decStringRefcount(data_);

		data_ = StringPool::addString( str, length, encoding );
		
		StringPool::incStringRefcount(data_);
	}

	const U16Char* c_str() const {
		if ( NULL == data_ ) {
			return L"";
		}

		return data_->strPtr;
	}

	const char* ansi_c_str(LanguageEncoding encoding=leDefault) const {
		if ( NULL == data_ ) {
			return NULL;
		}

		if ( NULL == data_->ansiStrPtr ) {
			StringPool::transformToAnsi( data_, encoding );
		}

		return data_->ansiStrPtr;
	}


	size_t length() const {
		if ( NULL == data_ ) {
			return 0;
		}
		return data_->length;
	}

	size_t size() const {
		if ( NULL == data_ ) {
			return 0;
		}
		return data_->length;
	}

	size_t size_in_bytes() const {
		if ( NULL == data_ ) {
			return 0;
		}
		return data_->length * sizeof(U16Char);
	}

	LanguageEncoding encoding() const;


	bool operator == ( const FastString& rhs ) const {
		return StringPool::equals(data_, rhs.data_ );
	}

	bool operator == ( const U16Char* rhs ) const {
		return operator ==( FastString(rhs) );
	}

	bool operator == ( const char* rhs ) const {
		return operator ==(FastString(rhs));
	}


	inline 
	bool operator !=( const FastString& rhs ) const {
		return !StringPool::equals(data_, rhs.data_ );
	}

	inline 
	bool operator <( const FastString& rhs ) const 	{
		return (StringPool::compare( data_, rhs.data_ ) < 0) ? true : false;
	}

	inline 
	bool operator <=( const FastString& rhs ) const 	{
		return (StringPool::compare( data_, rhs.data_ ) <= 0) ? true : false;
	}

	inline 
	bool operator >( const FastString& rhs ) const {
		return (StringPool::compare( data_, rhs.data_ ) > 0) ? true : false;
	}

	inline 
	bool operator >=( const FastString& rhs ) const {
		return (StringPool::compare( data_, rhs.data_ ) >= 0) ? true : false;
	}

	void clear() {
		StringPool::decStringRefcount(data_);
		data_ = NULL;
	}

	bool empty() const {
		if ( NULL == data_ ) {
			return true;
		}

		return size() == 0;
	}

	bool valid() const {
		if ( NULL == data_ ) {
			return false;
		}
		return data_->refcount > 0;
	}

	bool isSubstr() const {
		return StringPool::isSubString(data_);
	}

	int compare( const FastString& rhs ) const {
		return StringPool::compare( data_, rhs.data_ );
	}

	FastString substr( size_type pos, size_type length ) const {
		return FastString( StringPool::subStr( data_, pos, length ) );
		//return FastString( data_->strPtr + pos, length );
	}
	
    const_iterator begin() const {
		if ( NULL == data_ ) {
			return NULL;
		}
		return data_->strPtr;
	}

    const_iterator end() const {
		if ( NULL == data_ ) {
			return NULL;
		}

		return data_->strPtr + data_->length;
	}
    
    const_reverse_iterator rbegin() const {
		return const_reverse_iterator( end() );
	}

    const_reverse_iterator rend() const {
		return const_reverse_iterator( begin() );
	}

    const U16Char& at(size_t pos) const {
		if ( pos >= length() ) {
			throw std::out_of_range("array index is too large");
		}
		return data_->strPtr[ pos ];
	}

    const U16Char& operator[](size_t pos) const {
		return data_->strPtr[ pos ];
	}

	void swap( FastString& str ) {
		if ( str.data_ != data_ ) {			
			StringData* tmp = data_;
			data_ = str.data_;
			str.data_ = tmp;
		}
	}


	size_type find_first_not_of(const FastString& str, size_type pos = 0) const {
		return find_first_not_of( str.c_str(), pos, str.size() );
	}

	size_type find_first_not_of(const U16Char* strPtr, size_type pos, size_type length ) const {
		size_t sz = size();
		if (length < sz) {
			const U16Char *const currentPtr = c_str() + sz;
			for (const U16Char* P = c_str() + pos; P < currentPtr; ++P) {
				if (FastString::traits_type::find(strPtr, length, *P) == 0) {
					return (P - c_str());
				}
			}
		}

		return (FastString::npos);		
	}

	size_type find_first_of(const FastString& str, size_type pos = 0) const {
		return find_first_of( str.c_str(), pos, str.size() );
	}
	
	size_type find_first_of(const U16Char* strPtr, size_type pos, size_type length ) const {
		
		if (0 < length && pos < size()) {
			const U16Char *const currentPtr = c_str() + size();
			for (const U16Char* P = c_str() + pos; P < currentPtr; ++P)
				if (FastString::traits_type::find(strPtr, length, *P) != 0)
					return (P - c_str());	// found a match
		}

		return (FastString::npos);
	}

	size_type find_last_of(const FastString& str, size_type pos = npos) const {
		return find_last_of( str.c_str(), pos, str.size() );
	}

	size_type find_last_of(const U16Char* strPtr, size_type pos, size_type length ) const {
		if (0 < length && 0 < size() ) {
			for (const U16Char* P = c_str() 
				+ (pos < size() ? pos : size() - 1); ; --P) {

				if (FastString::traits_type::find(strPtr, length, *P) != 0) {
					return (P - c_str());	// found a match
				}
				else if (P == c_str()) {
					break;	// at beginning, no more chance for match
				}
			}
		}
		
		return (FastString::npos);
	}

	size_type find(const FastString& str, size_type pos = 0) const {
		return find( str.c_str(), pos, str.size() ); 
	}

	size_type find(const U16Char* strPtr, size_type pos = 0) const {
		return find( strPtr, pos, StringPool::wstrlen(strPtr) ); 
	}

	size_type find( U16Char ch, size_type pos = 0) const {
		return find( (const U16Char*)&ch, pos, 1); 
	}

	size_type find( const U16Char* searchStr, size_type pos, size_type len) const {
		size_type strLen = length();

		if ( 0 == strLen) {
			return FastString::npos;
		}

		if (len == 0 && pos <= strLen) {
			return (pos);
		}

		size_type searchLength = strLen - pos;
		const U16Char* sourceStr = data_->strPtr;

		if ( pos < strLen && (len <= searchLength) ) {
			const U16Char *currentStr1, *currentStr2;
			
			for (searchLength -= len - 1, currentStr2 = sourceStr + pos;
					(currentStr1 = StringPool::wmemchr(currentStr2, *searchStr, searchLength )) != 0;
					searchLength -= currentStr1 - currentStr2 + 1, currentStr2 = currentStr1 + 1) {

				if (StringPool::wmemcmp(currentStr1, searchStr, len) == 0) {
					return (currentStr1 - sourceStr); 
				}
			}
		}
		return FastString::npos; 
	}



	size_type rfind(U16Char c, size_type pos = npos) const {
		return rfind( &c, pos, 1 );
	}

	size_type rfind(const U16Char* strPtr, size_type pos = npos) const {
		return rfind( strPtr, pos, StringPool::wstrlen(strPtr) );
	}

	size_type rfind(const FastString& str, size_type pos = npos) const {
		return rfind( str.c_str(), pos, str.length() );
	}

	size_type rfind( const U16Char *strPtr, size_type pos, size_type len) const {
		size_type strLen = length();
		
		if ( 0 == strLen) {
			return FastString::npos;
		}

		if (len == 0) {
			return (pos < strLen ? pos : strLen);
		}

		if (len <= strLen) {
			const U16Char* ptr = data_->strPtr;

			for (const U16Char* currentStr1 = ptr + + (pos < strLen - len ? pos : strLen - len); ; --currentStr1)
				if ( (*currentStr1 == *strPtr) && StringPool::wmemcmp(currentStr1, strPtr, len) == 0)
					return (currentStr1 - ptr);
				else if (currentStr1 == ptr)
					break;
		}
		return FastString::npos;
	}

	//os specific string type conversion
#ifdef WIN32	
	//win32

#ifdef _MSC_VER 
	operator _bstr_t () const {
		return _bstr_t( c_str() );
	}

	FastString& operator=( const _bstr_t& rhs ) {
		assign( (const wchar_t*)rhs, rhs.length() );
		return *this;
	}

	operator _variant_t () const {
		
		return _variant_t( _bstr_t(c_str()) );
	}

	FastString& operator=( const _variant_t& rhs ) {
		_bstr_t b = rhs;
		assign( (const wchar_t*)b, b.length() );
		return *this;
	}	
#endif


	BSTR toBSTR() const {
		return SysAllocString(c_str());
	}

	FastString& assignBSTR( const BSTR& rhs ) {
		assign( (const U16Char*)rhs, SysStringLen(rhs) );
		return *this;
	}


	operator VARIANT() const {
		VARIANT result;
		VariantInit( &result );
		result.bstrVal = SysAllocString(c_str());
		result.vt = VT_BSTR;

		return result;
	}

	FastString& operator=( const VARIANT& rhs ) {
		if ( rhs.vt == VT_BSTR ) {
			assign( (const U16Char*)rhs.bstrVal, SysStringLen(rhs.bstrVal) );
		}
		return *this;
	}
#endif

	//stl conversion support
	operator std::wstring() const {
		return std::wstring(c_str());
	}

	FastString& operator=( const std::wstring& rhs ) {
		assign( rhs.c_str(), rhs.length() );
		return *this;
	}


	//stl conversion support
	operator std::string() const {
		return std::string(ansi_c_str());
	}

	FastString& operator=( const std::string& rhs ) {
		assign( rhs.c_str(), rhs.length() );
		return *this;
	}


	

	//utility

	FastString replace_if( const U16Char& chToFind, const U16Char& chToReplace ) const {
		STLString tmp = *this;
		std::replace_if( tmp.begin(), tmp.end(),
					std::bind2nd(std::equal_to<U16Char>(),chToFind) , chToReplace );

		return FastString(tmp.c_str(),tmp.size());
	}


	FastString replace( size_type pos, size_type length, const FastString& replaceStr ) const {
		return replace( pos, length, replaceStr.c_str(), replaceStr.size() );
	}

	FastString replace( size_type pos, size_type length, const U16Char* replaceStrPtr, size_type strLength ) const {
		FastString::STLString tmp = *this;
		tmp.replace( pos, length, replaceStrPtr, strLength );

		return FastString(tmp);
	}


	FastString insert( size_type pos, const FastString& str ) const {
		return FastString( StringPool::insert(  str.data_, data_, pos ) );
	}

	FastString insert( size_type pos, const value_type* str ) const {
		return FastString( StringPool::insert(  str, StringPool::wstrlen((const wchar_t*)str), data_, pos ) );
	}

	FastString insert( size_type pos, const value_type* str, size_type strLength ) const {
		return FastString( StringPool::insert(  str, strLength, data_, pos ) );
	}

	FastString insert( size_type pos, size_type count,  value_type ch ) const {
		return FastString( StringPool::insert(  ch, data_, pos, count ) );
	}

	FastString insert( size_type pos, value_type ch ) const {
		return FastString( StringPool::insert(  ch, data_, pos, 1 ) );
	}

	FastString insert( size_type pos, const AnsiChar* str ) const {
		return insert( pos, str, strlen(str) );
	}

	FastString insert( size_type pos, const AnsiChar* str, size_type strLength ) const {
		
		return insert( pos, FastString(str,strLength) );
	}

	FastString append( value_type ch ) const {
		value_type tmp[2] = {ch,0};
		return append( FastString( tmp, 1 ) );
	}

	FastString append( const char* strPtr,  size_type length ) const {
		return append( FastString( strPtr, length ) );
	}

	FastString append( const value_type* strPtr,  size_type length ) const {
		return append( FastString( strPtr, length ) );
	}

	//here for STL compat
	FastString append( size_type count, value_type ch ) const {
		if ( NULL == data_ ) {
			return FastString( ch );
		}

		return StringPool::insert(  ch, data_, length(), count );
	}


	FastString append( const FastString& str ) const {
		return insert( length(), str );
	}

	FastString prepend( const FastString& str ) const {
		return insert( 0, str );
	}


	FastString erase( size_type pos = 0, size_type count = npos ) const {
		return FastString( StringPool::erase( data_, pos, count ) );
	}

	FastString erase( const_iterator first, const_iterator last ) const {
		return FastString( StringPool::erase( data_, first - begin(), last - first ) );
	}

	FastString erase( const_iterator it ) const {
		return FastString( StringPool::erase( data_, it - begin(), 1 ) );
	}

	size_type copy( value_type* strPtr,  size_type length, size_type offset = 0 ) const {		
		StringPool::wmemcpy( strPtr, c_str() + offset, length );
		return length - offset;
	}

	size_type copy( char* strPtr,  size_type length, size_type offset = 0 ) const {		
		AnsiString s = *this;
		return s.copy( strPtr, length );
	}

	friend
	FastString operator+ (const FastString& lhs, const FastString& rhs );

	FastString& operator+= ( const FastString& rhs ) {
		*this = insert( length(), rhs );
		return *this;
	}

	FastString& operator+= ( const value_type* rhs ) {
		*this = insert( length(), FastString(rhs) );
		return *this;
	}

	FastString& operator+= ( const AnsiChar* rhs ) {
		*this = insert( length(), FastString(rhs) );
		return *this;
	}


	
	FastString set( size_t pos, const U16Char& ch ) const;


	uint64 sizeOf() const;

	void decode_ansi( TextCodec* codec, AnsiChar* str, size_type& strSize, LanguageEncoding encoding=leDefault ) const ;
	FastString decode( TextCodec* codec, LanguageEncoding encoding=leDefault ) const ;
	void encode( TextCodec* codec, const AnsiChar* str, size_type n, LanguageEncoding encoding=leDefault );
	void encode( TextCodec* codec, const FastString& str, LanguageEncoding encoding=leDefault );



	static void transformAnsiToUnicode( const AnsiChar* str, size_type stringLength, FastString& newStr, LanguageEncoding encoding=leDefault );

	static AnsiChar* transformUnicodeToAnsi( const FastString& str, LanguageEncoding encoding=leDefault );

	static UniChar transformAnsiCharToUnicodeChar( AnsiChar c, LanguageEncoding encoding=leDefault );
	static AnsiChar transformUnicodeCharToAnsiChar( UniChar c, LanguageEncoding encoding=leDefault );

	static int adjustForBOMMarker( AnsiChar*& stringPtr, uint32& len );

protected:

	FastString( StringData* data ):data_(NULL) {
		assign(data);
	}

	void assign( StringData* data ) {
		StringPool::decStringRefcount(data_);

		data_ = data;
		
		StringPool::incStringRefcount(data_);
	}


	FastString& operator=( StringData* data ) {
		assign( data );
		return *this;
	}

	StringData* data_;
};



inline FastString operator+ (const FastString& lhs, const FastString& rhs )
{		
	return lhs.insert( lhs.length(), rhs );
}





class StringExtraData {
public:
	StringExtraData():encoding(FastString::leDefault),
						subStrStart(StringExtraData::SubStrNPos),
						subStrEnd(StringExtraData::SubStrNPos),
						substrParent(NULL),
						nextSubstr(NULL) {}
	enum {
		SubStrNPos = (size_t)-1,
	};

	FastString::LanguageEncoding encoding;
	size_t subStrStart; 
	size_t subStrEnd;
	StringData* substrParent;
	StringData* nextSubstr;
};


inline FastString::LanguageEncoding FastString::encoding() const 
{
	if ( NULL == data_ ) {
		return leUnknown;
	}

	if ( NULL != data_->extra ) {
		return data_->extra->encoding;
	}
	return leDefault;
}	


typedef FastString UnicodeString;





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
	UnicodeString result(lhs) ;

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
	UnicodeString result(UnicodeString::transformAnsiCharToUnicodeChar( lhs ));
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
	UnicodeString result(lhs, strlen(lhs));

	result += rhs;
	return result;
}


inline UnicodeString operator +( const UnicodeString& lhs, const UnicodeString::AnsiChar* rhs )
{
	UnicodeString result(lhs);
	UnicodeString tmp(rhs, strlen(rhs));
	result += tmp;
	return result;
}



#endif



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

#ifndef USE_STRINGPOOL


class FOUNDATIONKIT_API UnicodeString {
public:
		

	/**
	Code page values for the locale:
	*/
	enum LanguageEncoding { 
		leUnknown = -1,
		leDefault = 0,
		leIBM037 = 100,
		leIBM437,
		leIBM500,
		leArabic708,
		leArabic449,
		leArabicTransparent,
		leDOSArabic,
		leGreek,
		leBaltic,
		leLatin1,
		leLatin2,
		leCyrillic,
		leTurkish,
		leMultilingualLatin1,
		lePortuguese,
		leIcelandic,
		leHebrew,
		leFrenchCanadian,
		leArabic864,
		leNordic,
		leRussianCyrillic,
		leModernGreek,
		leEBCDICLatin2,
		leThai,
		leEBCDICGreekModern,
		leShiftJIS,
		leSimplifiedChinese,
		leKorean,
		leChineseTraditionalBig5,
		leEBCDICTurkish,
		leEBCDICLatin1,
		leEBCDICUSCanada,
		leEBCDICGermany,
		leEBCDICDenmarkNorway,
		leEBCDICFinlandSweden,
		leEBCDICItaly,
		leEBCDICLatinAmericaSpain,
		leEBCDICUnitedKingdom,
		leEBCDICFrance,
		leEBCDICInternational,
		leEBCDICIcelandic,
		leUTF16LittleEndianByteOrder,
		leUTF16BigEndianByteOrder,
		leANSICentralEuropean,
		leANSICyrillic,
		leANSILatin1,
		leANSIGreek,
		leANSITurkish,
		leANSIHebrew,
		leANSIArabic,
		leANSIBaltic,
		leANSIVietnamese,
		leJohabKorean,
		leMacRoman,
		leMacJapanese,
		leMacTraditionalChineseBig5,
		leMacKorean,
		leMacArabic,
		leMacHebrew,
		leMacGreek,
		leMacCyrillic,
		leMacSimplifiedChinese,
		leMacRomanian,
		leMacUkrainian,
		leMacThai,
		leMacLatin2,
		leMacIcelandic,
		leMacTurkish,
		leMacCroatian,
		leUTF32LittleEndianByteOrder,
		leUTF32BigEndianByteOrder,
		leCNSTaiwan,
		leTCATaiwan,
		leEtenTaiwan,
		leIBM5550Taiwan,
		leTeleTextTaiwan,
		leWangTaiwan,
		leIA5WesternEuropean,
		leIA5German,
		leIA5Swedish,
		leIA5Norwegian,
		leUSASCII,
		leT61,
		leISO6937,
		leIBM273Germany,
		leIBM277DenmarkNorway,
		leIBM278FinlandSweden,
		leIBM280Italy,
		leIBM284LatinAmericaSpain,
		leIBM285UnitedKingdom,
		leIBM290JapaneseKatakanaExt,
		leIBM297France,
		leIBM420Arabic,
		leIBM423Greek,
		leIBM424Hebrew,
		leIBMKoreanExtended,
		leIBMThai,
		leRussianKOI8R,
		leIBM871Icelandic,
		leIBM880CyrillicRussian,
		leIBM905Turkish,
		leIBM00924Latin1,
		leEUCJapaneseJIS,
		leSimplifiedChineseGB2312,
		leKoreanWansung,
		leEBCDICCyrillicSerbianBulgarian,
		leUkrainianKOI8U,
		leISO88591Latin1,
		leISO88592CentralEuropean,
		leISO88593Latin3,
		leISO88594Baltic,
		leISO88595Cyrillic,
		leISO88596Arabic,
		leISO88597Greek,
		leISO88598HebrewVisual,
		leISO88599Turkish,
		leISO885913Estonian,
		leISO885915Latin9,
		leEuropa3,
		leISO88598HebrewLogical,
		leISO2022JapaneseNoHalfwidthKatakana,
		leISO2022JapaneseWithHalfwidthKatakana,
		leISO2022JapaneseAllow1ByteKana,
		leISO2022Korean,
		leISO2022SimplifiedChinese,
		leISO2022TraditionalChinese,
		leEBCDICJapaneseExt,
		leEBCDICUSCanadaAndJapanese,
		leEBCDICKoreanExtAndKorean,
		leEBCDICSimplifiedChineseExtSimplifiedChinese,
		leEBCDICSimplifiedChinese,
		leEBCDICUSCanadaAndTraditionalChinese,
		leEBCDICJapaneseLatinExtAndJapanese,
		leEUCJapanese,
		leEUCSimplifiedChinese,
		leEUCKorean,
		leEUCTraditionalChinese,
		leHZGB2312SimplifiedChinese,
		leGB18030SimplifiedChinese,
		leISCIIDevanagari,
		leISCIIBengali,
		leISCIITamil,
		leISCIITelugu,
		leISCIIAssamese,
		leISCIIOriya,
		leISCIIKannada,
		leISCIIMalayalam,
		leISCIIGujarati,
		leISCIIPunjabi,
		leUTF7,
		leUTF8
	};

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

	UnicodeString(const std::string& rhs, LanguageEncoding encoding=leDefault);

	UnicodeString(const AnsiChar* string, size_type stringLength, LanguageEncoding encoding=leDefault );	

	UnicodeString(const UniChar* string, size_type stringLength );

	UnicodeString(const AnsiChar* string, LanguageEncoding encoding=leDefault );
	UnicodeString(const UniChar* string );

	UnicodeString( size_type n, AnsiChar c, LanguageEncoding encoding=leDefault );
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
	void decode_ansi( TextCodec* codec, AnsiChar* str, size_type& strSize, LanguageEncoding encoding=leDefault ) const ;

	/**
	Decodes the unicode data in the string and returns a new string with the
	decoded data as determined by the text codec.
	@param TextCodec the codec used to decode the string's data
	@return UnicodeString the new string that is created as a result of
	the decode process by the codec.
	*/
	UnicodeString decode( TextCodec* codec, LanguageEncoding encoding=leDefault ) const ;

	/**
	This encodes the ansi string into unicode, according to the algorithms
	in the codec, and replaces the data in the string's data_ value.
	@param TextCodec* an instance of a TextCodec that represents the
	algorithm used in encoding the data stored in str.
	@param AnsiChar* the source ansi string buffer
	@param size_type the number of bytes to encode from the str buffer
	*/
	void encode( TextCodec* codec, const AnsiChar* str, size_type n, LanguageEncoding encoding=leDefault );

	/**
	This encodes the data in the unicode string into another unicode string,
	according to the algorithms in the codec, and replaces the data in
	the string's data_ value.
	@param TextCodec* an instance of a TextCodec that represents the
	algorithm used in encoding the data stored in str.
	@param UnicodeString the source unicode string to encode from
	*/
	void encode( TextCodec* codec, const UnicodeString& str, LanguageEncoding encoding=leDefault );

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
	const AnsiChar* ansi_c_str(LanguageEncoding encoding=leDefault) const;





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

	UnicodeString replace_if( const UniChar& chToFind, const UniChar& chToReplace ) const {
		UnicodeString tmp(*this);
		std::replace_if( tmp.data_.begin(), tmp.data_.end(),
					std::bind2nd(std::equal_to<UniChar>(),chToFind) , chToReplace );

		return tmp;
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

	uint64 sizeOf() const;

	static void transformAnsiToUnicode( const AnsiChar* str, size_type stringLength, StringData& newStr, LanguageEncoding encoding=leDefault );

	static AnsiChar* transformUnicodeToAnsi( const UnicodeString& str, LanguageEncoding encoding=leDefault );

	static UniChar transformAnsiCharToUnicodeChar( AnsiChar c, LanguageEncoding encoding=leDefault );
	static AnsiChar transformUnicodeCharToAnsiChar( UniChar c, LanguageEncoding encoding=leDefault );

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


#endif



//typedef std::basic_string<VCFChar> String;

typedef UnicodeString String;

};


#endif // _VCF_VCFSTRING_H__

/**
$Id$
*/
