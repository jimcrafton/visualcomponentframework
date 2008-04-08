////StringPool.cpp

#include "vcf/FoundationKit/FoundationKit.h"

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



inline RoundUp(size_t cb, size_t units)
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
        uint32 result = 0;

		for (size_t i=0;i<length;i+=1 ) {
        //while ( length>0 ) {
            result = str[i] + (result << 6) + (result << 16) - result;
			//length --;
			//str++;
		}

        return result;
    }


	uint32 find( const VCFChar* str, size_t length );

	uint32 addString( const VCFChar* str, size_t length );

	const VCFChar* getString( uint32 index );
	size_t getStringLength( uint32 index );
private:

	struct StrEntry {
		VCFChar* str;
		size_t length;
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
		lstrcpynW(tmpPtr, begin, length);
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

	uint32 hash = StringPool::hash(str,length);

	StringMapRangeT found = stringMap_.equal_range( hash );
	while ( found.first != found.second ) {
		uint32 idx = found.first->second;
		if ( idx < stringEntries_.size() ) {
			const StrEntry& entry = stringEntries_[idx];
			if ( entry.length == length ) {
				if ( 0 == memcmp( entry.str, str, length * sizeof(VCFChar) ) ) {
					result = idx;
					break;
				}
			}
		}

		++found.first ;
	}
	

	return result;
}

uint32 StringPool::addString( const VCFChar* str, size_t length )
{
	uint32 result = NoEntry;

	result = find( str, length );

	if ( result == NoEntry ) {
		VCFChar* newStr = allocate( str, str+length );

		uint32 hash = StringPool::hash(str, length);

		StrEntry entry;
		entry.length = length;
		entry.str = newStr;

		stringEntries_.push_back( entry );
		result = stringEntries_.size()-1;

		stringMap_.insert(StringMapPairT(hash,result));
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

	FastString( const VCFChar* str ): index_(StringPool::NoEntry) {
		assign( str, wcslen(str) );
	}

	FastString( const VCFChar* str, size_t length ): index_(StringPool::NoEntry) {
		assign( str, length );
	}

	FastString(): index_(StringPool::NoEntry){}

	FastString( const FastString& f ):index_(f.index_) {

	}


	operator const VCFChar*() const {
		return stringPool.getString(index_);
	}

	FastString& operator=( const VCFChar* rhs ) {
		assign( rhs, wcslen(rhs) );
		return *this;
	}

	FastString& operator=( const FastString& rhs ) {
		index_ = rhs.index_;
		return *this;
	}

	void assign( const VCFChar* str, size_t length ) {
		index_ = stringPool.addString( str, length );
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
		index_ = 0;
	}

	bool empty() const {
		if ( index_ == StringPool::NoEntry ) {
			return true;
		}

		return size() == 0;
	}


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

	FoundationKit::init( argc, argv );
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

	FastString f;
	clock.start();
	f = L"Hola!";
	clock.stop();


	printf( "fs Length %u, took %0.8f seconds\n",f.length(),clock.duration() );

	

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




	FoundationKit::terminate();
	return 0;
}


