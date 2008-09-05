////StringPool.cpp

#include "vcf/FoundationKit/FoundationKit.h"


#ifdef _MSC_VER 
#include <comdef.h>
#endif


/*
#define WIN32_LEAN_AND_MEAN

#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <stdexcept>
#include <emmintrin.h>



*/
#include <fstream>
#include <iostream> // for cin/cout


//#include "C:\code\string_classes\fix_str\SOURCE\fix_str.h"



//typedef unsigned int uint32;
typedef wchar_t U16Char; //16 bit unicode character codepoint
//typedef wchar_t U16Char;
//typedef std::basic_string<U16Char> String;

using namespace VCF;



class HiResClock {
public:

	HiResClock(){
		QueryPerformanceFrequency( (LARGE_INTEGER*)&frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}



	void start() {		
		QueryPerformanceCounter( (LARGE_INTEGER*)&performanceCounter1_ );
	}

	void stop() {
		QueryPerformanceCounter( (LARGE_INTEGER*)&performanceCounter2_ );
	}

	void clear() {
		//QueryPerformanceFrequency( &frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return ((double)(performanceCounter2_ - performanceCounter1_))/((double)frequency_);
	}
protected:
	__int64 frequency_;
	__int64 performanceCounter1_;
	__int64 performanceCounter2_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};



inline size_t RoundUp(size_t cb, size_t units)
{
    return ((cb + units - 1) / units) * units;
}

//#define HAVE_MMX


class StringPool;

union MemHeader {
	struct {
		MemHeader* prev;			
		size_t  size;
	};
	U16Char alignment;
};

typedef void* StringDataHandle;



struct StringData {
	enum StateFlags {
		SubString = 0x00000001,
	};

	U16Char* strPtr;
	size_t length;
	size_t refcount;
	MemHeader* memHdr;
	StringPool* pool;	
	uint32 hashID;
	uint32 flags;
};	


class StringPool {
public:
	enum { 
		MIN_CBCHUNK = 32000,
        MAX_CHARALLOC = 1024*1024,
		NoEntry = (uint32)-1,
	};


	StringPool();
	~StringPool();	

	StringData* allocate(const U16Char* begin, const U16Char* end);

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
		::wmemcpy( (wchar_t*)dest, (wchar_t*)src, len );
#endif

		return dest;
	}


	

	static uint32 hash( const U16Char* str, size_t length )
    {
        uint32 result = 0;
#if 1
		result = 0;
		for (size_t i=0;i<length;i+=1 ) {        
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


	StringData* find( const U16Char* str, size_t length );

	static StringDataHandle addString( const U16Char* str, size_t length );

	static bool validString( StringDataHandle handle );
	static const U16Char* getString( StringDataHandle handle );
	static size_t getStringLength( StringDataHandle handle );

	static uint32 incStringRefcount( StringDataHandle handle );
	static uint32 decStringRefcount( StringDataHandle handle );
	static bool equals( StringDataHandle lhs, StringDataHandle rhs );
	static int compare( StringDataHandle lhs, StringDataHandle rhs );
	

	void compact( uint32 index=NoEntry );
	
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
		StringPool::currentStringPool = this;
	}

	bool compactsMemory() const {
		return compactMemory_;
	}

	void setCompactsMemory( bool val ) {
		compactMemory_ = val;
	}

	static StringPool* getCurrentPool() {
		return currentStringPool;
	}	

	static StringPool* getUsablePool();
private:

	unsigned char*  next_;   // first available byte
	unsigned char*  limit_;  // one past last available byte
	MemHeader* currentHdr_;   // current block
	size_t   granularity_;
	std::vector<size_t> freeEntries_;	
	size_t totalBytesAllocated_;
	uint32 threadID_;
	bool compactMemory_;


	typedef std::multimap<uint32,StringData*> StringMapT;

	typedef StringMapT::iterator StringMapIter;
	typedef StringMapT::const_iterator StringMapConstIter;
	typedef std::pair<StringMapIter,StringMapIter> StringMapRangeT;
	typedef std::pair<StringMapConstIter,StringMapConstIter> StringMapConstRangeT;
	typedef StringMapT::value_type StringMapPairT;

	StringMapT stringMap_;
	


	static StringPool* currentStringPool;


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

	static StringPoolTLSGuard poolTLSGuard;
};

StringPool* StringPool::currentStringPool = NULL;
DWORD StringPool::threadPoolTLSIndex = 0;

StringPool::StringPoolTLSGuard StringPool::poolTLSGuard;


StringPool* StringPool::getUsablePool()
{
	if ( NULL != StringPool::currentStringPool ) {
		return StringPool::currentStringPool;
	}

	if ( 0 == StringPool::threadPoolTLSIndex ) {
		StringPool::threadPoolTLSIndex = TlsAlloc();
		
		if ( TLS_OUT_OF_INDEXES == StringPool::threadPoolTLSIndex ) {
			static std::bad_alloc outOfTLS;
			throw(outOfTLS);
		}
	}

	StringPool* currentThreadPool = (StringPool*) TlsGetValue( StringPool::threadPoolTLSIndex );
	if ( NULL == currentThreadPool ) {
		currentThreadPool = new StringPool();
		StringPool::poolTLSGuard.threadPools.push_back( currentThreadPool );
		TlsSetValue( StringPool::threadPoolTLSIndex, currentThreadPool );
	}

	return currentThreadPool;
}




StringPool::StringPool():
	next_(NULL),
	limit_(NULL),
	currentHdr_(NULL),
	granularity_(0),
	totalBytesAllocated_(0),
	threadID_(0),
	compactMemory_(false)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	granularity_ = RoundUp(sizeof(MemHeader) + MIN_CBCHUNK,
								si.dwAllocationGranularity);

	threadID_ = ::GetCurrentThreadId();

}

StringPool::~StringPool()
{
	MemHeader* hdrPtr = currentHdr_;
	while (hdrPtr) {
		MemHeader hdr = *hdrPtr;
		VirtualFree(hdr.prev, hdr.size, MEM_RELEASE);
		hdrPtr = hdr.prev;
	}
}

StringData* StringPool::allocate(const U16Char* begin, const U16Char* end)
{
	size_t length = sizeof(StringData) + ((end - begin) * sizeof(U16Char)) + sizeof(U16Char);
	if ((next_ + length) <= limit_) {
		StringData* data = (StringData*)next_;
		data->length = (end - begin);
		data->memHdr = currentHdr_;
		data->pool = this;
		data->refcount = 0;
		data->strPtr = (U16Char*) (next_ + sizeof(StringData));
		data->hashID = 0;

		next_ += length;
		StringPool::wmemcpy( data->strPtr, begin, data->length );
		return data;
	}
	
	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (length <= MAX_CHARALLOC) {	
		allocSize = RoundUp(length + sizeof(MemHeader), granularity_);

		nextBytes = reinterpret_cast<unsigned char*>(
				VirtualAlloc(NULL, allocSize, MEM_COMMIT, PAGE_READWRITE) );
	}

	if (!nextBytes) {
		static std::bad_alloc outOfMemException;
		throw(outOfMemException);
	}

	totalBytesAllocated_ += allocSize;
	
	limit_ = reinterpret_cast<unsigned char*>(nextBytes + allocSize);
	MemHeader* currentHdr = reinterpret_cast<MemHeader*>(nextBytes);
	currentHdr->prev = currentHdr_;
	currentHdr->size = allocSize;
	

	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	
	return allocate(begin, end);
}

void StringPool::compact(uint32 index)
{
	/*
	if ( NoEntry == index ) {

	}
	else {
		std::vector<StrEntry>::iterator it = stringEntries_.begin() + index;
		if ( it != stringEntries_.end() ) {
			StrEntry& freeEntry = *it;
			freeEntries_.push_back( index );

			MemHeader* memHdr = freeEntry.memHdr;

			++it;
			while ( it != stringEntries_.end() ) {
				StrEntry& entry = *it;
				
				++it;
			}
		}
	}
	*/
}

StringData* StringPool::find( const U16Char* str, size_t length )
{
	StringData* result = NULL;//NoEntry;

	uint32 hashID = hash(str,length);

	StringMapRangeT found = stringMap_.equal_range( hashID );
	StringMapIter current = found.first;

	
	size_t rangeCount = 0;
	while ( current != found.second ) {
		rangeCount ++;
		++current;
	}

	current = found.first;
	if ( rangeCount == 1 ) {
		StringData* data = current->second;

		if ( data->length == length ) {
			result = data;
		}
		
	}
	else {
		while ( current != found.second ) {
			StringData* data = current->second;
			if ( data->length == length ) {
				if ( 0 == StringPool::wmemcmp( data->strPtr, str, length ) ) {
					result = data;
					break;
				}
			}
			
			++current ;
		}
	}
	
	return result;
}

StringDataHandle StringPool::addString( const U16Char* str, size_t length )
{
	StringData* result = NULL;

	StringPool* pool = StringPool::getUsablePool();
	if ( NULL == pool ) {
		return result;
	}

	result = pool->find( str, length );

	if ( result == NULL ) {
		StringData* newStr = pool->allocate( str, str+length );

		newStr->hashID = hash(newStr->strPtr, newStr->length);

		result = newStr;

		//////////////////////////////////////////////////////
		//PERFORMANCE WARNING!!
		//multimap::insert is *expensive. This is what changes
		//loading and parsing around 34,000 entries in a dictionary
		//from taking between 250ms to 137ms (with the insert) to
		//taking 45ms (without the insert). Ultimately the
		//multimap needs to go in favor of some other 
		//associative container.
		//////////////////////////////////////////////////////

		pool->stringMap_.insert(StringMapPairT(newStr->hashID,result));
	}

	return (StringDataHandle) result;
}

uint32 StringPool::incStringRefcount( StringDataHandle handle )
{
	if ( NULL != handle ) {
		StringData* data = (StringData*)handle;
		if ( !data->pool->compactsMemory() ) {
			return 0;
		}

		if ( data->pool->getThreadID() == ::GetCurrentThreadId() ) {
			data->refcount++;
		}
		else {
			//we need to lock it?
			data->refcount++;
		}
		return data->refcount;
	}

	return 0;
}

uint32 StringPool::decStringRefcount( StringDataHandle handle )
{
	if ( NULL != handle ) {
		
		StringData* data = (StringData*)handle;
		if ( !data->pool->compactsMemory() ) {
			return 0;
		}

		if ( data->pool->getThreadID() == ::GetCurrentThreadId() ) {
			if ( data->refcount > 0 ) {
				data->refcount--;

				if ( 0 == data->refcount ) {

				}
			}
		}
		else {
			//we need to lock it?
			data->refcount--;
		}
		return data->refcount;
	}

	return 0;
	/*
	uint32 result = NoEntry;
	if ( index < stringEntries_.size() ) {
		StrEntry& entry = stringEntries_[index];
		entry.refcount--;
		if ( 0 == entry.refcount ) {			
			//printf( "No more refs to str[\"%.8ls...\":%u]\n", entry.str, entry.length );
		}
		result = entry.refcount;
	}
	return result;
	*/
}

const U16Char* StringPool::getString( StringDataHandle handle )
{
	if ( NULL == handle ) {
		return NULL;
	}

	return ((StringData*)handle)->strPtr;
}

size_t StringPool::getStringLength( StringDataHandle handle )
{
	if ( NULL == handle ) {
		return 0;
	}
	return ((StringData*)handle)->length;
}

bool StringPool::validString( StringDataHandle handle )
{
	if ( NULL != handle ) {
		return ((StringData*)handle)->refcount > 0;
	}

	return false;
}

bool StringPool::equals( StringDataHandle lhs, StringDataHandle rhs )
{
	StringData* lhsData = (StringData*)lhs;
	StringData* rhsData = (StringData*)rhs;

	if ( lhsData == rhsData ) {
		return true;
	}

	if ( lhsData->length != rhsData->length ) {
		return false;
	}

	if ( (lhsData->pool == rhsData->pool) || (lhsData->pool->getThreadID() == rhsData->pool->getThreadID()) ) {
		return 0 == StringPool::wmemcmp( lhsData->strPtr, rhsData->strPtr, lhsData->length );
	}
	else {
		//different threads, different pools, do we need to lock here??
		return 0 == StringPool::wmemcmp( lhsData->strPtr, rhsData->strPtr, lhsData->length );
	}

	return false;
}

int StringPool::compare( StringDataHandle lhs, StringDataHandle rhs )
{
	StringData* lhsData = (StringData*)lhs;
	StringData* rhsData = (StringData*)rhs;
	
	if ( lhsData == rhsData ) {
		return 0;
	}

	if ( (lhsData->pool == rhsData->pool) || (lhsData->pool->getThreadID() == rhsData->pool->getThreadID()) ) {
		return StringPool::wmemcmp( lhsData->strPtr, rhsData->strPtr, lhsData->length );
	}
	else {
		//different threads, different pools, do we need to lock here??
		return StringPool::wmemcmp( lhsData->strPtr, rhsData->strPtr, lhsData->length );
	}

	return 0;
}

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

std::vector<U16Char> StringLiteral::storage(StringLiteral::InitialStorageSize);


class FastString {
public:

	typedef U16Char* iterator;
    typedef const U16Char* const_iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef U16Char value_type;	
    typedef U16Char *pointer;
    typedef const U16Char *const_pointer;
	typedef U16Char& reference;
    typedef const U16Char& const_reference;

	#if (_MSC_VER <= 1200) && !defined(__GNUC__)
	typedef std::reverse_iterator<iterator, value_type,
				reference, pointer, difference_type> reverse_iterator;

	typedef std::reverse_iterator<const_iterator, value_type,
				const_reference, const_pointer, difference_type>
				const_reverse_iterator;
	#else
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	#endif
		

	enum {
		npos = (size_type) -1
	};





	//FastString( const U16Char* str ): index_(StringPool::NoEntry) {
	//	assign( str, wcslen(str) );
	//}

	FastString( const U16Char* str, size_t length ): dataHandle_(NULL) {
		assign( str, length );
	}

	FastString(): dataHandle_(NULL){}

	FastString( const FastString& f ):dataHandle_(f.dataHandle_) {
		StringPool::incStringRefcount(dataHandle_);
	}


	~FastString() {
		StringPool::decStringRefcount(dataHandle_);
	}

	operator const U16Char*() const {
		return StringPool::getString(dataHandle_);
	}

	FastString& operator=( const U16Char* rhs ) {
		assign( rhs, StringPool::wstrlen(rhs) );
		return *this;
	}

	FastString& operator=( const FastString& rhs ) {
		StringPool::decStringRefcount(dataHandle_);

		dataHandle_ = rhs.dataHandle_;
		
		StringPool::incStringRefcount(dataHandle_);
		return *this;
	}

	void assign( const U16Char* str, size_t length ) {
		StringPool::decStringRefcount(dataHandle_);

		dataHandle_ = StringPool::addString( str, length );
		
		StringPool::incStringRefcount(dataHandle_);
	}

	const U16Char* c_str() const {
		return StringPool::getString(dataHandle_);
	}

	size_t length() const {
		return StringPool::getStringLength(dataHandle_);
	}

	size_t size() const {
		return StringPool::getStringLength(dataHandle_);
	}


	bool operator == ( const FastString& rhs ) const {
		return StringPool::equals(dataHandle_, rhs.dataHandle_ );
	}

	void clear() {
		StringPool::decStringRefcount(dataHandle_);
		dataHandle_ = NULL;
	}

	bool empty() const {
		if ( NULL == dataHandle_ ) {
			return true;
		}

		return size() == 0;
	}

	bool valid() const {
		return StringPool::validString(dataHandle_);
	}

	int compare( const FastString& rhs ) const {
		return StringPool::compare( dataHandle_, rhs.dataHandle_ );
	}

	FastString substr( size_type pos, size_type length ) const {
		return FastString( StringPool::getString(dataHandle_) + pos, length );
	}
	
    const_iterator begin() const {
		return StringPool::getString(dataHandle_);
	}

    const_iterator end() const {
		return StringPool::getString(dataHandle_) + StringPool::getStringLength(dataHandle_);
	}
    
    const_reverse_iterator rbegin() const {
		return const_reverse_iterator( end() );
	}

    const_reverse_iterator rend() const {
		return const_reverse_iterator( begin() );
	}

    const_reference at(size_type pos) const {
		if ( pos >= StringPool::getStringLength(dataHandle_) ) {
			throw std::out_of_range("array index is too large");
		}
		return StringPool::getString(dataHandle_)[ pos ];
	}

    const_reference operator[](size_type pos) const {
		return StringPool::getString(dataHandle_)[ pos ];
	}

	void swap( FastString& str ) {
		if ( str.dataHandle_ != dataHandle_ ) {			
			StringDataHandle tmp = dataHandle_;
			dataHandle_ = str.dataHandle_;
			str.dataHandle_ = tmp;
		}
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

	size_type find( const U16Char* searchStr, size_type pos, size_type length) const {
		size_type len = StringPool::getStringLength(dataHandle_);

		if (length == 0 && pos <= len) {
			return (pos);
		}

		size_type searchLength = len - pos;
		const U16Char* sourceStr = StringPool::getString(dataHandle_);

		if ( pos < len && (length <= searchLength) ) {
			const U16Char *currentStr1, *currentStr2;
			
			for (searchLength -= length - 1, currentStr2 = sourceStr + pos;
					(currentStr1 = StringPool::wmemchr(currentStr2, *searchStr, searchLength )) != 0;
					searchLength -= currentStr1 - currentStr2 + 1, currentStr2 = currentStr1 + 1) {

					if (StringPool::wmemcmp(currentStr1, searchStr, length) == 0) {
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

	size_type rfind( const U16Char *strPtr, size_type pos, size_type length) const {
		size_type len = StringPool::getStringLength(dataHandle_);
		if (length == 0) {
			return (pos < len ? pos : len);
		}

		if (length <= len) {
			const U16Char* ptr = StringPool::getString(dataHandle_);

			for (const U16Char* currentStr1 = ptr + + (pos < len - length ? pos : len - length); ; --currentStr1)
				if ( (*currentStr1 == *strPtr) && StringPool::wmemcmp(currentStr1, strPtr, length) == 0)
					return (currentStr1 - ptr);
				else if (currentStr1 == ptr)
					break;
		}
		return FastString::npos;
	}




	//os specific string type conversion
	//win32

#ifdef _MSC_VER 
	operator _bstr_t () const {
		return _bstr_t( c_str() );
	}

	FastString& operator=( const _bstr_t& rhs ) {
		assign( rhs, rhs.length() );
		return *this;
	}

	operator _variant_t () const {
		
		return _variant_t( _bstr_t(c_str()) );
	}

	FastString& operator=( const _variant_t& rhs ) {
		_bstr_t b = rhs;
		assign( b, b.length() );
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

/*
	operator BSTR() const {
		return SysAllocString(c_str());
	}

	FastString& operator=( const BSTR& rhs ) {
		assign( (const U16Char*)rhs, SysStringLen(rhs) );
		return *this;
	}
*/

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

	//stl conversion support
	operator std::wstring() const {
		return std::wstring(c_str());
	}

	FastString& operator=( const std::wstring& rhs ) {
		assign( rhs.c_str(), rhs.length() );
		return *this;
	}
protected:
	StringDataHandle dataHandle_;
};


#define BIGSTR	L"sf;lkasjd f;klasjdf; kalsjdf; akljdsf; kaljsdf;k ajd;sfkl ja;sdfklja;weroitupqeriogn.fvkxcpbv78xc9v8b"

#define BIGSTR2 L"The seven-day mission was highlighted by the mating of the"\
				L" U.S.-built Node 1 station element to the Functional Cargo Block"\
				L"(FGB in Russian) already in orbit, and two spacewalks to connect "\
				L"power and data transmission cables between the Node and the FGB. "\
				L"The FGB, built by Boeing and the Russian Space Agency, launched "\
				L"on a Russian Proton rocket from the Baikonur Cosmodrome in Kazakhstan "\
				L"in November 1998."\
				L"Node 1, also called the Unity Module was the first Space Station hardware"\
				L"delivered by the Space Shuttle. It has two Pressurized Mating Adapters "\
				L"(PMA), one attached to either end. One PMA is permanently mated to the "\
				L"FGB and the other used for orbiter dockings and crew access to the station"\
				L". Node 1 also contains an International Standard Payload Rack used to support"\
				L"on-orbit activities which was activated after the fifth Shuttle/Station assembly"\
				L"flight."\
				L"To begin the assembly sequence, the crew conducted a series of rendezvous "\
				L"maneuvers similar to those conducted on other Shuttle missions to reach the "\
				L"orbiting FGB. On the way, Currie used the Shuttle's robot arm to place Node "\
				L"1 atop the Orbiter Docking System. Cabana completed the rendezvous by flying "\
				L"Endeavour to within 35 feet (10 m) of the FGB, allowing Currie to capture the "\
				L"FGB with the robot arm and place it on the Node's Pressurized Mating Adapter."\
				L"Once the two elements were docked, Ross and Newman conducted two scheduled "\
				L"spacewalks to connect power and data cables between the Node, PMAs and the "\
				L"FGB. The day following the spacewalks, Endeavour undocked from the two components"\
				L", completing the first Space Station assembly mission."\
				L"The ISS after STS-88 construction."\
				L"The ISS after STS-88 construction."\
				L"Illustration of the International Space Station after STS-88"\
				L"Illustration of the International Space Station after STS-88"\
				L"Other payloads on the STS-88 mission included the IMAX Cargo Bay Camera "\
				L"(ICBC), the Argentinean Scientific Applications Satellite-S (SAC-A), the "\
				L"MightySat 1 Hitchhiker payload, the Space Experiment Module (SEM-07) and "\
				L"Getaway Special G-093 sponsored by the University of Michigan."\
				L"Endeavour's astronauts toured the new International Space Statio on "\
				L"Dec. 11, entering the Unity and Zarya modules for the first time and establishing "\
				L"an S-band communications system that enables U.S. flight controllers to monitor "\
				L"the outpost's systems."\
				L"Reflecting the international cooperation involved in building the largest space "\
				L"complex in history, Commander Robert Cabana and Russian Cosmonaut Sergei Krikalev "\
				L"opened the hatch to the U.S.-built Unity connecting module and floated into the "\
				L"new station together."\
				L"The rest of the crew followed and began turning on lights and unstowing gear in "\
				L"the roomy hub to which other modules will be connected in the future. Each "\
				L"passageway within Unity was marked by a sign leading the way into tunnels to "\
				L"which new modules will be connected."\
				L"About an hour later, Robert Cabana and Sergei Krikalyov opened the hatch to the "\
				L"Russian-built Zarya control module, which will be the nerve center for the station "\
				L"in its embryonic stage. Joined by Pilot Frederick Sturckow and Mission Specialists "\
				L"Jerry Ross, James Newman and Nancy Currie, Cabana and Krikalev hailed the historic"\
				L"entrance into the International Space Station and said the hatch opening signified "\
				L"the start of a new era in space exploration."\
				L"Ross and Newman went right to work in Unity, completing the assembly of an early "\
				L"S-band communications system that allows flight controllers in Houston to send "\
				L"commands to Unity's systems and to keep tabs on the health of the station with a "\
				L"more extensive communications capability than exists through Russian ground stations"\
				L". The astronauts also conducted a successful test of the videoconferencing "\
				L"capability of the early communications system, which was used by the first crew "\
				L"to permanently occupy the station in January 2000 (Expedition 1). Newman downlinked"\
				L"greetings to controllers in the station flight control room in Houston and to "\
				L"astronaut Bill Shepherd, who will command the first crew and live aboard the "\
				L"station with Krikalev and Cosmonaut Yuri Gidzenko."










#define BIGSTR2_ANSI "The seven-day mission was highlighted by the mating of the"\
				" U.S.-built Node 1 station element to the Functional Cargo Block"\
				"(FGB in Russian) already in orbit, and two spacewalks to connect "\
				"power and data transmission cables between the Node and the FGB. "\
				"The FGB, built by Boeing and the Russian Space Agency, launched "\
				"on a Russian Proton rocket from the Baikonur Cosmodrome in Kazakhstan "\
				"in November 1998."\
				"Node 1, also called the Unity Module was the first Space Station hardware"\
				"delivered by the Space Shuttle. It has two Pressurized Mating Adapters "\
				"(PMA), one attached to either end. One PMA is permanently mated to the "\
				"FGB and the other used for orbiter dockings and crew access to the station"\
				". Node 1 also contains an International Standard Payload Rack used to support"\
				"on-orbit activities which was activated after the fifth Shuttle/Station assembly"\
				"flight."\
				"To begin the assembly sequence, the crew conducted a series of rendezvous "\
				"maneuvers similar to those conducted on other Shuttle missions to reach the "\
				"orbiting FGB. On the way, Currie used the Shuttle's robot arm to place Node "\
				"1 atop the Orbiter Docking System. Cabana completed the rendezvous by flying "\
				"Endeavour to within 35 feet (10 m) of the FGB, allowing Currie to capture the "\
				"FGB with the robot arm and place it on the Node's Pressurized Mating Adapter."\
				"Once the two elements were docked, Ross and Newman conducted two scheduled "\
				"spacewalks to connect power and data cables between the Node, PMAs and the "\
				"FGB. The day following the spacewalks, Endeavour undocked from the two components"\
				", completing the first Space Station assembly mission."\
				"The ISS after STS-88 construction."\
				"The ISS after STS-88 construction."\
				"Illustration of the International Space Station after STS-88"\
				"Illustration of the International Space Station after STS-88"\
				"Other payloads on the STS-88 mission included the IMAX Cargo Bay Camera "\
				"(ICBC), the Argentinean Scientific Applications Satellite-S (SAC-A), the "\
				"MightySat 1 Hitchhiker payload, the Space Experiment Module (SEM-07) and "\
				"Getaway Special G-093 sponsored by the University of Michigan."\
				"Endeavour's astronauts toured the new International Space Statio on "\
				"Dec. 11, entering the Unity and Zarya modules for the first time and establishing "\
				"an S-band communications system that enables U.S. flight controllers to monitor "\
				"the outpost's systems."\
				"Reflecting the international cooperation involved in building the largest space "\
				"complex in history, Commander Robert Cabana and Russian Cosmonaut Sergei Krikalev "\
				"opened the hatch to the U.S.-built Unity connecting module and floated into the "\
				"new station together."\
				"The rest of the crew followed and began turning on lights and unstowing gear in "\
				"the roomy hub to which other modules will be connected in the future. Each "\
				"passageway within Unity was marked by a sign leading the way into tunnels to "\
				"which new modules will be connected."\
				"About an hour later, Robert Cabana and Sergei Krikalyov opened the hatch to the "\
				"Russian-built Zarya control module, which will be the nerve center for the station "\
				"in its embryonic stage. Joined by Pilot Frederick Sturckow and Mission Specialists "\
				"Jerry Ross, James Newman and Nancy Currie, Cabana and Krikalev hailed the historic"\
				"entrance into the International Space Station and said the hatch opening signified "\
				"the start of a new era in space exploration."\
				"Ross and Newman went right to work in Unity, completing the assembly of an early "\
				"S-band communications system that allows flight controllers in Houston to send "\
				"commands to Unity's systems and to keep tabs on the health of the station with a "\
				"more extensive communications capability than exists through Russian ground stations"\
				". The astronauts also conducted a successful test of the videoconferencing "\
				"capability of the early communications system, which was used by the first crew "\
				"to permanently occupy the station in January 2000 (Expedition 1). Newman downlinked"\
				"greetings to controllers in the station flight control room in Houston and to "\
				"astronaut Bill Shepherd, who will command the first crew and live aboard the "\
				"station with Krikalev and Cosmonaut Yuri Gidzenko."








using std::string;
using std::wstring;
using std::vector;

struct ChDictionaryEntry
{
	bool Parse(const wstring& line);
	wstring trad;
	wstring simp;
	wstring pinyin;
	wstring english;
};

bool ChDictionaryEntry::Parse(const wstring& line)
{
    wstring::size_type start = 0;
    wstring::size_type end = line.find(L' ', start);
    if (end == wstring::npos) return false;
    trad.assign(line, start, end);
    start = line.find(L'[', end);
    if (start == wstring::npos) return false;
    end = line.find(L']', ++start);
    if (end == wstring::npos) return false;
    pinyin.assign(line, start, end - start);
    start = line.find(L'/', end);
    if (start == wstring::npos) return false;
    start++;
    end = line.rfind(L'/');
    if (end == wstring::npos) return false;
    if (end <= start) return false;
    english.assign(line, start, end-start);
    return true;
}

class ChDictionary
{
public:
	ChDictionary();
	int Length() { return v.size(); }
	const ChDictionaryEntry& Item(int i) { return v[i]; }
private:
	vector<ChDictionaryEntry> v;
};

ChDictionary::ChDictionary()
{
	/*std::locale old = std::locale::global(std::locale(".950"));

	std::wifstream src;
	src.imbue(std::locale(".950"));
	src.open("cedict.b5");
	wstring s;
	int i = 0;
	while (std::getline(src, s)) {
		if (s.length() > 0 && s[0] != L'#') {
			ChDictionaryEntry de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}

		i++;
	}*/

	FileInputStream fs("cedict.b5");
	
	unsigned char* data = new unsigned char[ fs.getSize() ];

	fs.read( data, fs.getSize() );

	String chStr((const char*)data,fs.getSize(),UnicodeString::leChineseTraditionalBig5);

	delete [] data;


	StringTokenizer tok(chStr,"\r\n");

	while ( tok.hasMoreElements() ) {
		String s = tok.nextElement();
		if (s.length() > 0 && s[0] != L'#') {
			ChDictionaryEntry de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}
	}

}






struct ChDictionaryEntry2
{
	bool Parse(const wstring& line);
	FastString trad;
	FastString simp;
	FastString pinyin;
	FastString english;
};

bool ChDictionaryEntry2::Parse(const wstring& line)
{
    wstring::size_type start = 0;
    wstring::size_type end = line.find(L' ', start);
    if (end == wstring::npos) return false;

	const U16Char* begin = (const U16Char*)line.c_str();

    trad.assign(begin + start, end - start);
    start = line.find(L'[', end);
    if (start == wstring::npos) return false;
    end = line.find(L']', ++start);
    if (end == wstring::npos) return false;
    pinyin.assign(begin + start, end - start);
    start = line.find(L'/', end);
    if (start == wstring::npos) return false;
    start++;
    end = line.rfind(L'/');
    if (end == wstring::npos) return false;
    if (end <= start) return false;
    english.assign(begin + start, end - start);
    return true;
}

class ChDictionary2
{
public:
	ChDictionary2();
	int Length() { return v.size(); }
	const ChDictionaryEntry2& Item(int i) { return v[i]; }
private:
	vector<ChDictionaryEntry2> v;
};

ChDictionary2::ChDictionary2()
{
	FileInputStream fs("cedict.b5");
	
	unsigned char* data = new unsigned char[ fs.getSize() ];

	fs.read( data, fs.getSize() );

	String chStr((const char*)data,fs.getSize(),UnicodeString::leChineseTraditionalBig5);

	delete [] data;


	StringTokenizer tok(chStr,"\r\n");

	while ( tok.hasMoreElements() ) {
		String s = tok.nextElement();
		if (s.length() > 0 && s[0] != L'#') {
			ChDictionaryEntry2 de;
			if (de.Parse(s)) {
				v.push_back(de);
				//printf( "eng: %ls\n", de.english.c_str() );
			}
		}
	}	
}







struct ChDictionaryEntry3
{
	bool Parse(const FastString& line);
	FastString trad;
	FastString simp;
	FastString pinyin;
	FastString english;
};

bool ChDictionaryEntry3::Parse(const FastString& line)
{
    FastString::size_type start = 0;
    FastString::size_type end = line.find(L' ', start);
    if (end == FastString::npos) return false;

	const U16Char* begin = line.c_str();

    trad.assign(begin + start, end - start);
    start = line.find(L'[', end);
    if (start == wstring::npos) return false;
    end = line.find(L']', ++start);
    if (end == wstring::npos) return false;
    pinyin.assign(begin + start, end - start);
    start = line.find(L'/', end);
    if (start == wstring::npos) return false;
    start++;
    end = line.rfind(L'/');
    if (end == wstring::npos) return false;
    if (end <= start) return false;
    english.assign(begin + start, end - start);
    return true;
}

class ChDictionary3
{
public:
	ChDictionary3();
	void doit();
	int Length() { return v.size(); }
	const ChDictionaryEntry3& Item(int i) { return v[i]; }
private:
	vector<ChDictionaryEntry3> v;
};

ChDictionary3::ChDictionary3()
{
	
}


void ChDictionary3::doit()
{
	FileInputStream fs("cedict.b5");
	
	unsigned char* data = new unsigned char[ fs.getSize() ];

	fs.read( data, fs.getSize() );

	String chStr((const char*)data,fs.getSize(),UnicodeString::leChineseTraditionalBig5);

	delete [] data;


	const U16Char*  P = (const U16Char*)chStr.c_str();
	const U16Char*  start = P;
	const U16Char*  line = P;

	size_t sz = chStr.length();
	while ( P-start < sz ) {
		if ( *P == '\r' || *P == '\n' ) {
			if ( *P == '\r' && *(P+1) == '\n' ) {
				P++;
			}
			P++;

			if ((P-line) > 0 && *line != L'#') {
				ChDictionaryEntry3 de;
				FastString s(line,(P-line));
				if (de.Parse(s)) {
					v.push_back(de);					
				}
			}


			line = P;
		}
		P++;
	}
/*
	while ( tok.hasMoreElements() ) {
		String s = tok.nextElement();
		if (s.length() > 0 && s[0] != L'#') {
			ChDictionaryEntry3 de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}
	}	*/
}

void part2()
{
	printf( "part2.....\n" );
	printf( "num entries in string pool: %u\n", StringPool::getUsablePool()->uniqueEntries() );
	printf( "total bytes in string pool: %u\n", StringPool::getUsablePool()->totalBytesAllocated() );
	HiResClock clock;

	clock.start();
	
	{
		ChDictionary dict;
		clock.stop();

		std::cout << dict.Length() << std::endl;		
		printf( "basic_string (ChDictionary) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
	}


	{
		clock.start();
		ChDictionary dict;
		clock.stop();

		std::cout << dict.Length() << std::endl;		
		printf( "basic_string (ChDictionary) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
	}


	
	
	{
		clock.start();
		ChDictionary2 dict2;
		clock.stop();

		std::cout << dict2.Length() << std::endl;		
		printf( "FastString (ChDictionary2) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
	}

	{
		clock.start();
		ChDictionary2 dict2;
		clock.stop();

		std::cout << dict2.Length() << std::endl;		
		printf( "FastString (ChDictionary2) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
	}

	{
		clock.start();
		ChDictionary2 dict2;
		clock.stop();

		std::cout << dict2.Length() << std::endl;		
		printf( "FastString (ChDictionary2) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
	}




	{
		ChDictionary3 dict3;
		clock.start();
		dict3.doit();
		clock.stop();

		std::cout << dict3.Length() << std::endl;		
		printf( "FastString (ChDictionary3) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
		printf( "num entries in string pool: %u\n", StringPool::getUsablePool()->uniqueEntries() );
	}

	{
		ChDictionary3 dict3;
		clock.start();
		dict3.doit();
		clock.stop();

		std::cout << dict3.Length() << std::endl;		
		printf( "FastString (ChDictionary3) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );
		printf( "num entries in string pool: %u\n", StringPool::getUsablePool()->uniqueEntries() );
	}

	{
		ChDictionary3 dict3;
		clock.start();
		dict3.doit();
		clock.stop();

		std::cout << dict3.Length() << std::endl;		
		printf( "FastString (ChDictionary3) impl took %0.8f seconds or %0.4f milliseconds\n", clock.duration() , (clock.duration()*1000.0) );

		printf( "num entries in string pool: %u\n", StringPool::getUsablePool()->uniqueEntries() );
		printf( "total bytes in string pool: %u\n", StringPool::getUsablePool()->totalBytesAllocated() );

		int idx = 22;
		printf( "item[%d].english: %ls\n", idx, dict3.Item(idx).english.c_str() );
		printf( "item[%d].pinyin: %ls\n", idx, dict3.Item(idx).pinyin.c_str() );
		printf( "item[%d].trad: %ls\n", idx, dict3.Item(idx).trad.c_str() );
	}

	
}



void part3()
{
	FastString fs;
	_bstr_t b = "asdasdasd";

	fs = b;

	BSTR b2 = fs.toBSTR();

	_variant_t v = fs;

	VARIANT v2 = fs;
}


int main( int argc, char** argv )
{

	FoundationKit::init( argc, argv );

	
	StringPool stringPool;
	stringPool.makeCurrentPool();


	HiResClock clock;

	U16Char t1[5000];

	size_t BIGSTR2_len = wcslen(BIGSTR2);
	clock.start();
	StringPool::wmemcpy( t1, BIGSTR2, BIGSTR2_len );
	clock.stop();

	printf( "StringPool::wmemcpy %u bytes took %0.8f seconds\n", BIGSTR2_len, clock.duration() );
	

	clock.start();
	::wmemcpy( t1, BIGSTR2, BIGSTR2_len );
	clock.stop();

	printf( "::wmemcpy took %0.8f seconds\n", clock.duration() );

	{
		const U16Char* s = L"Hola";
		
		StringPool sp;
		sp.allocate( s, s+4);
		
		std::vector<FastString> v;
		v.resize(10);
		
		FastString f = v[2];
		FastString f2 = f;
		f = v[0];
		
		StringDataHandle idx = sp.addString(s,4);
		
		
		StringDataHandle idx2 = sp.addString(s,4);
	}

	
	{
	FastString f;
	clock.start();
	f = L"Hola!";
	clock.stop();
	printf( "fs Length %u, took %0.8f seconds\n",f.length(),clock.duration() );
	}


	

	
	FastString f;

	clock.start();
	f = BIGSTR;
	clock.stop();

	printf( "fs Length %u, took %0.8f seconds\n",f.length(),clock.duration() );

	clock.start();
	f = BIGSTR2;
	clock.stop();

	printf( "fs Length %u, took %0.8f seconds\n",f.length(),clock.duration() );


	
	clock.start();
	f = BIGSTR2;
	clock.stop();

	printf( "fs Length %u, took %0.8f seconds\n",f.length(),clock.duration() );


	FastString f2;
	clock.start();
	f2 = f;
	clock.stop();

	printf( "fs Length %u, took %0.8f seconds\n",f2.length(),clock.duration() );

	printf( "===============================================================================\n" );
	printf( "===============================================================================\n" );





	String s;
	clock.start();
	s = L"Hola!";
	clock.stop();


	printf( "s Length %u, took %0.8f seconds\n", s.length(),clock.duration() );

	

	clock.start();
	s = BIGSTR;
	clock.stop();

	printf( "s Length %u, took %0.8f seconds\n", s.length(),clock.duration() );

	clock.start();
	s = BIGSTR2;
	clock.stop();

	printf( "s Length %u, took %0.8f seconds\n", s.length(),clock.duration() );



	clock.start();
	s = BIGSTR2;
	clock.stop();

	printf( "s Length %u, took %0.8f seconds\n", s.length(),clock.duration() );


	String s2;

	clock.start();
	s2 = s;
	clock.stop();

	printf( "s Length %u, took %0.8f seconds\n",s2.length(),clock.duration() );



	s2.find(L"hello");
	


	FastString f3;
	f3 = L"Hello Sam I am because I like green Eggs and Ham!";
	size_t pos = f3.find( L"Sam" );


	pos = f3.rfind( L"Sam" );


	FastString f4;
	f4 = StringLiteral("Hello World");

	const char* str = BIGSTR2_ANSI;
	size_t stringLength = strlen(str);

	HiResClock clock2;

	clock.start();
	clock2.start();
	size_t size = MultiByteToWideChar( CP_UTF8, 0, str, stringLength, NULL, 0 );
	U16Char* tmp = new U16Char[size];

	int err = MultiByteToWideChar( CP_UTF8, 0, str, stringLength, (LPWSTR)tmp, size );

	clock2.stop();

	FastString f5;
	f5 = tmp;


	delete [] tmp;
	

	printf( "f5 from ansi Length %u, MultiByteToWideChar took %0.8f seconds, total took %0.8f seconds\n",f5.length(),clock2.duration(), clock.duration() );



	clock.start();
	clock2.start();

	FastString f6;
	StringLiteral sl("Hello World");
	clock2.stop();
	f6 = sl;

	f6 = f6.substr( 5, 5 );

	clock.stop();

	printf( "f6 from ansi Length %u, StringLiteral took %0.8f seconds, total took %0.8f seconds\n",f5.length(),clock2.duration(), clock.duration() );





	//part2();


	part3();

	//Sleep(10000000);

	FoundationKit::terminate();

	return 0;
}


