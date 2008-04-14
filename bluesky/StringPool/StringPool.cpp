////StringPool.cpp

//#include "vcf/FoundationKit/FoundationKit.h"

#define WIN32_LEAN_AND_MEAN

#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <windows.h>



typedef unsigned int uint32;
//typedef unsigned short VCFChar;
typedef wchar_t VCFChar;
typedef std::basic_string<VCFChar> String;



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


class StringPool {
public:
	enum { 
		MIN_CBCHUNK = 32000,
        MAX_CHARALLOC = 1024*1024,
		NoEntry = (uint32)-1,
	};


	StringPool();
	~StringPool();

	VCFChar* allocate(const VCFChar* begin, const VCFChar* end);

	static uint32 hash( const VCFChar* str, size_t length )
    {
        uint32 result = (uint32)str;
#if 1
		result = 0;
		for (size_t i=0;i<length;i+=8 ) {        
            result = str[i] + (result << 6) + (result << 16) - result;			
		}
#endif
        return result;
    }


	uint32 find( const VCFChar* str, size_t length );

	uint32 addString( const VCFChar* str, size_t length );

	const VCFChar* getString( uint32 index );
	size_t getStringLength( uint32 index );

	uint32 incStringRefcount( uint32 index );
	uint32 decStringRefcount( uint32 index );
private:

	struct StrEntry {
		VCFChar* str;
		size_t length;
		size_t refcount;		
	};

	union MemHeader {
		struct {
			MemHeader* prev;
			size_t  size;
		};
		VCFChar alignment;
	};


	VCFChar*  next_;   // first available byte
	VCFChar*  limit_;  // one past last available byte
	MemHeader* currentHdr_;   // current block
	size_t   granularity_;
	std::vector<StrEntry> stringEntries_;

	typedef std::multimap<uint32,uint32> StringMapT;
	typedef StringMapT::iterator StringMapIter;
	typedef StringMapT::const_iterator StringMapConstIter;
	typedef std::pair<StringMapIter,StringMapIter> StringMapRangeT;
	typedef std::pair<StringMapConstIter,StringMapConstIter> StringMapConstRangeT;
	typedef StringMapT::value_type StringMapPairT;




	std::multimap<uint32,uint32> stringMap_;
	
};


StringPool::StringPool():
	next_(NULL),
	limit_(NULL),
	currentHdr_(NULL),
	granularity_(0)

{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	granularity_ = RoundUp(sizeof(MemHeader) + MIN_CBCHUNK,
								si.dwAllocationGranularity);
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

VCFChar* StringPool::allocate(const VCFChar* begin, const VCFChar* end)
{
	size_t length = end - begin + 1;
	VCFChar* tmpPtr = next_;
	if (next_ + length <= limit_) {
		next_ += length;
		memcpy(tmpPtr, begin, length*sizeof(VCFChar));
		return tmpPtr;
	}
	
	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (length <= MAX_CHARALLOC) {	
		allocSize = RoundUp(length * sizeof(VCFChar) + sizeof(MemHeader), granularity_);

		nextBytes = reinterpret_cast<unsigned char*>(
				VirtualAlloc(NULL, allocSize, MEM_COMMIT, PAGE_READWRITE) );
	}

	if (!nextBytes) {
		static std::bad_alloc outOfMemException;
		throw(outOfMemException);
	}

	
	limit_ = reinterpret_cast<VCFChar*>(nextBytes + allocSize);
	MemHeader* currentHdr = reinterpret_cast<MemHeader*>(nextBytes);
	currentHdr->prev = currentHdr_;
	currentHdr->size = allocSize;
	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<VCFChar*>(currentHdr + 1);
	
	return allocate(begin, end);
}


uint32 StringPool::find( const VCFChar* str, size_t length )
{
	uint32 result = NoEntry;

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
		uint32 idx = current->second;
		if ( idx < stringEntries_.size() ) {
			const StrEntry& entry = stringEntries_[idx];
			if ( entry.length == length ) {
				result = idx;
			}
		}
	}
	else {
		while ( current != found.second ) {
			uint32 idx = current->second;
			if ( idx < stringEntries_.size() ) {
				const StrEntry& entry = stringEntries_[idx];
				if ( entry.length == length ) {
					
					if ( 0 == ::wcscmp( entry.str, str/*, length * sizeof(VCFChar)*/ ) ) {
						result = idx;
						break;
					}
				}
			}
			
			++current ;
		}
	}
	

	return result;
}

uint32 StringPool::addString( const VCFChar* str, size_t length )
{
	uint32 result = NoEntry;

	result = find( str, length );

	if ( result == NoEntry ) {
		VCFChar* newStr = allocate( str, str+length );

		uint32 hashID = hash(str, length);

		StrEntry entry;
		entry.length = length;
		entry.str = newStr;
		entry.refcount = 0;

		stringEntries_.push_back( entry );
		result = stringEntries_.size()-1;

		stringMap_.insert(StringMapPairT(hashID,result));
	}

	return result;
}

uint32 StringPool::incStringRefcount( uint32 index )
{
	uint32 result = NoEntry;
	if ( index < stringEntries_.size() ) {
		StrEntry& entry = stringEntries_[index];
		entry.refcount++;
		result = entry.refcount;
	}
	return result;
}

uint32 StringPool::decStringRefcount( uint32 index )
{
	uint32 result = NoEntry;
	if ( index < stringEntries_.size() ) {
		StrEntry& entry = stringEntries_[index];
		entry.refcount--;
		if ( 0 == entry.refcount ) {
			printf( "No more refs to str[\"%.8ls...\":%u]\n", entry.str, entry.length );
		}
		result = entry.refcount;
	}
	return result;
}

const VCFChar* StringPool::getString( uint32 index )
{
	if ( index < stringEntries_.size() && index != NoEntry ) {
		const StrEntry& entry = stringEntries_[index];
		return entry.str;
	}

	return NULL;
}

size_t StringPool::getStringLength( uint32 index )
{
	if ( index < stringEntries_.size() && index != NoEntry ) {
		const StrEntry& entry = stringEntries_[index];
		return entry.length;
	}

	return 0;
}

static StringPool stringPool;


class FastString {
public:

	typedef VCFChar* iterator;
    typedef const VCFChar* const_iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef VCFChar value_type;	
    typedef VCFChar *pointer;
    typedef const VCFChar *const_pointer;
	typedef VCFChar& reference;
    typedef const VCFChar& const_reference;

	//typedef std::reverse_iterator<iterator, value_type,
      //  reference, pointer, difference_type> reverse_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	//typedef std::reverse_iterator<const_iterator, value_type,
      //  const_reference, const_pointer, difference_type>
        //    const_reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	enum {
		npos = (size_type) -1
	};





	//FastString( const VCFChar* str ): index_(StringPool::NoEntry) {
	//	assign( str, wcslen(str) );
	//}

	FastString( const VCFChar* str, size_t length ): index_(StringPool::NoEntry) {
		assign( str, length );
	}

	FastString(): index_(StringPool::NoEntry){}

	FastString( const FastString& f ):index_(f.index_) {
		stringPool.incStringRefcount(index_);
	}


	~FastString() {
		stringPool.decStringRefcount(index_);
	}

	operator const VCFChar*() const {
		return stringPool.getString(index_);
	}

	FastString& operator=( const VCFChar* rhs ) {
		assign( rhs, wcslen(rhs) );
		return *this;
	}

	FastString& operator=( const FastString& rhs ) {
		stringPool.decStringRefcount(index_);

		index_ = rhs.index_;
		
		stringPool.incStringRefcount(index_);
		return *this;
	}

	void assign( const VCFChar* str, size_t length ) {
		stringPool.decStringRefcount(index_);

		index_ = stringPool.addString( str, length );
		
		stringPool.incStringRefcount(index_);
	}

	const VCFChar* c_str() const {
		return stringPool.getString(index_);
	}

	size_t length() const {
		return stringPool.getStringLength(index_);
	}

	size_t size() const {
		return stringPool.getStringLength(index_);
	}


	bool operator == ( const FastString& rhs ) const {
		return rhs.index_ == index_;
	}

	void clear() {
		stringPool.decStringRefcount(index_);
		index_ = 0;
	}

	bool empty() const {
		if ( index_ == StringPool::NoEntry ) {
			return true;
		}

		return size() == 0;
	}



	
    const_iterator begin() const {
		return stringPool.getString(index_);
	}

    const_iterator end() const {
		return stringPool.getString(index_) + stringPool.getStringLength(index_);
	}
    
    const_reverse_iterator rbegin() const {
		return const_reverse_iterator( end() );
	}

    const_reverse_iterator rend() const {
		return const_reverse_iterator( begin() );
	}

    const_reference at(size_type pos) const {
		if ( pos >= stringPool.getStringLength(index_) ) {
			throw std::out_of_range("array index is too large");
		}
		return stringPool.getString(index_)[ pos ];
	}

    const_reference operator[](size_type pos) const {
		return stringPool.getString(index_)[ pos ];
	}

	void swap( FastString& str ) {
		if ( str.index_ != index_ ) {			
			size_t tmp = index_;
			index_ = str.index_;
			str.index_ = tmp;
		}
	}

	size_type find(const FastString& str, size_type pos = 0) const {
		return find( str.c_str(), pos, str.size() ); 
	}

	size_type find(const VCFChar* strPtr, size_type pos = 0) const {
		return find( strPtr, pos, wcslen(strPtr) ); 
	}

	size_type find( VCFChar ch, size_type pos = 0) const {
		return find( (const VCFChar*)&ch, pos, 1); 
	}

	size_type find( const VCFChar* searchStr, size_type pos, size_type length) const {
		size_type len = stringPool.getStringLength(index_);

		if (length == 0 && pos <= len) {
			return (pos);
		}

		size_type searchLength = len - pos;
		const VCFChar* sourceStr = stringPool.getString(index_);

		if ( pos < len && (length <= searchLength) ) {
			const VCFChar *currentStr1, *currentStr2;
			
			for (searchLength -= length - 1, currentStr2 = sourceStr + pos;
					(currentStr1 = wmemchr(currentStr2, *searchStr, searchLength )) != 0;
					searchLength -= currentStr1 - currentStr2 + 1, currentStr2 = currentStr1 + 1) {

					if (wmemcmp(currentStr1, searchStr, length) == 0) {
						return (currentStr1 - sourceStr); 
					}
			}
		}
		return FastString::npos; 
	}



	size_type rfind(VCFChar c, size_type pos = npos) const {
		return rfind( &c, pos, 1 );
	}

	size_type rfind(const VCFChar* strPtr, size_type pos = npos) const {
		return rfind( strPtr, pos, wcslen(strPtr) );
	}

	size_type rfind(const FastString& str, size_type pos = npos) const {
		return rfind( str.c_str(), pos, str.length() );
	}

	size_type rfind( const VCFChar *strPtr, size_type pos, size_type length) const {
		size_type len = stringPool.getStringLength(index_);
		if (length == 0) {
			return (pos < len ? pos : len);
		}

		if (length <= len) {
			const VCFChar* ptr = stringPool.getString(index_);

			for (const VCFChar* currentStr1 = ptr + + (pos < len - length ? pos : len - length); ; --currentStr1)
				if ( (*currentStr1 == *strPtr) && wmemcmp(currentStr1, strPtr, length) == 0)
					return (currentStr1 - ptr);
				else if (currentStr1 == ptr)
					break;
		}
		return (npos); }
protected:
	size_t index_;
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


int main( int argc, char** argv ){


	{
		const VCFChar* s = L"Hola";
		
		StringPool sp;
		sp.allocate( s, s+4);
		
		std::vector<FastString> v;
		v.resize(10);
		
		FastString f = v[2];
		FastString f2 = f;
		f = v[0];
		
		uint32 idx = sp.addString(s,4);
		
		
		uint32 idx2 = sp.addString(s,4);
	}

	HiResClock clock;
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

	return 0;
}


