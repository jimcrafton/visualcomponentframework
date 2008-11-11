////StringPool.cpp

//#include "vcf/FoundationKit/FoundationKit.h"


#ifdef _MSC_VER 
#include <comdef.h>
#endif



#define WIN32_LEAN_AND_MEAN

#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <stdio.h>
#include <windows.h>
#include <stdexcept>
#include <emmintrin.h>
#include <algorithm>




#include <fstream>
#include <iostream> // for cin/cout


//#include "C:\code\string_classes\fix_str\SOURCE\fix_str.h"



typedef unsigned int uint32;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef wchar_t U16Char; //16 bit unicode character codepoint

typedef std::basic_string<U16Char> String;





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


class StringPool;
class FastString;


union MemHeader {
	struct {
		MemHeader* prev;			
		size_t  size;
		unsigned char* next;
		unsigned char* limit;
		size_t refcount;
	};
	U16Char alignment;
};


class StringData {
private:
	friend class StringPool;
	friend class FastString;

	U16Char* strPtr;
	size_t length;
	size_t refcount;
	MemHeader* memHdr;
	StringPool* pool;	
	uint32 hashID;
	char* ansiStrPtr;
};	


class StringPool {
public:
	enum { 
		MIN_CBCHUNK = 32000,
        MAX_CHARALLOC = 0xFFFFFFFF-1, //too low?? 1024*1024,
		NoEntry = (uint32)-1,
	};


	StringPool();
	~StringPool();	

	StringData* allocate(const U16Char* begin, const U16Char* end);
	StringData* allocate( size_t length );

	StringData* transformAnsiToUnicode( const char* str, size_t length, LanguageEncoding encoding );

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

	static StringData* addString( const U16Char* str, size_t length );
	static StringData* addString( const char* str, size_t length, LanguageEncoding encoding );

	static uint32 incStringRefcount( StringData* handle );
	static uint32 decStringRefcount( StringData* handle );
	static bool equals( StringData* lhs, StringData* rhs );
	static int compare( StringData* lhs, StringData* rhs );
	
	static char* transformToAnsi( StringData* handle, LanguageEncoding encoding );	
	
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
		StringPool::stringPoolStack.push_back(this);
	}

	static StringPool* popCurrentPool() {
		if ( StringPool::stringPoolStack.empty() ) {
			return NULL;
		}

		StringPool* result = getCurrentPool();

		StringPool::stringPoolStack.pop_back();

		return result;
	}

	bool compactsMemory() const {
		return compactMemory_;
	}

	void setCompactsMemory( bool val ) {
		compactMemory_ = val;
	}

	static unsigned int getNativeEncoding(LanguageEncoding encoding);

	static StringPool* getCurrentPool() {
		if ( StringPool::stringPoolStack.empty() ) {
			return NULL;
		}

		return StringPool::stringPoolStack.back();
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


	static std::deque<StringPool*> stringPoolStack;


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

DWORD StringPool::threadPoolTLSIndex = 0;

StringPool::StringPoolTLSGuard StringPool::poolTLSGuard;
std::deque<StringPool*> StringPool::stringPoolStack;



StringPool* StringPool::getUsablePool()
{
	if ( !StringPool::stringPoolStack.empty() ) {
		return StringPool::stringPoolStack.back();
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



unsigned int StringPool::getNativeEncoding(LanguageEncoding encoding)
{
	unsigned int result = -1;
#ifdef WIN32
	

	LanguageEncoding tmp = encoding;
	if ( encoding == leDefault ) {
		tmp = leUTF8 ;
		//Locale* locale = System::getCurrentThreadLocale();
		//if ( NULL != locale ) {
		//	tmp = locale->getEncoding();
		//}
	}


	
	switch (tmp) {				
		case leIBM037: {result=037;}break;
		case leIBM437: {result=437;}break;
		case leIBM500: {result=500;}break;
		case leArabic708: {result=708;}break;
		case leArabic449: {result=709;}break;
		case leArabicTransparent: {result=710;}break;
		case leDOSArabic: {result=720;}break;
		case leGreek: {result=737;}break;
		case leBaltic: {result=775;}break;
		case leLatin1: {result=850;}break;
		case leLatin2: {result=852;}break;
		case leCyrillic: {result=855;}break;
		case leTurkish: {result=857;}break;
		case leMultilingualLatin1: {result=858;}break;
		case lePortuguese: {result=860;}break;
		case leIcelandic: {result=861;}break;
		case leHebrew: {result=862;}break;
		case leFrenchCanadian: {result=863;}break;
		case leArabic864: {result=864;}break;
		case leNordic: {result=865;}break;
		case leRussianCyrillic: {result=866;}break;
		case leModernGreek: {result=869;}break;
		case leEBCDICLatin2: {result=870;}break;
		case leThai: {result=874;}break;
		case leEBCDICGreekModern: {result=875;}break;
		case leShiftJIS: {result=932;}break;
		case leSimplifiedChinese: {result=936;}break;
		case leKorean: {result=949;}break;
		case leChineseTraditionalBig5: {result=950;}break;
		case leEBCDICTurkish: {result=1026;}break;
		case leEBCDICLatin1: {result=1047;}break;
		case leEBCDICUSCanada: {result=1140;}break;
		case leEBCDICGermany: {result=1141;}break;
		case leEBCDICDenmarkNorway: {result=1142;}break;
		case leEBCDICFinlandSweden: {result=1143;}break;
		case leEBCDICItaly: {result=1144;}break;
		case leEBCDICLatinAmericaSpain: {result=1145;}break;
		case leEBCDICUnitedKingdom: {result=1146;}break;
		case leEBCDICFrance: {result=1147;}break;
		case leEBCDICInternational: {result=1148;}break;
		case leEBCDICIcelandic: {result=1149;}break;
		case leUTF16LittleEndianByteOrder: {result=1200;}break;
		case leUTF16BigEndianByteOrder: {result=1201;}break;
		case leANSICentralEuropean: {result=1250;}break;
		case leANSICyrillic: {result=1251;}break;
		case leANSILatin1: {result=1252;}break;
		case leANSIGreek: {result=1253;}break;
		case leANSITurkish: {result=1254;}break;
		case leANSIHebrew: {result=1255;}break;
		case leANSIArabic: {result=1256;}break;
		case leANSIBaltic: {result=1257;}break;
		case leANSIVietnamese: {result=1258;}break;
		case leJohabKorean: {result=1361;}break;
		case leMacRoman: {result=10000;}break;
		case leMacJapanese: {result=10001;}break;
		case leMacTraditionalChineseBig5: {result=10002;}break;
		case leMacKorean: {result=10003;}break;
		case leMacArabic: {result=10004;}break;
		case leMacHebrew: {result=10005;}break;
		case leMacGreek: {result=10006;}break;
		case leMacCyrillic: {result=10007;}break;
		case leMacSimplifiedChinese: {result=10008;}break;
		case leMacRomanian: {result=10010;}break;
		case leMacUkrainian: {result=10017;}break;
		case leMacThai: {result=10021;}break;
		case leMacLatin2: {result=10029;}break;
		case leMacIcelandic: {result=10079;}break;
		case leMacTurkish: {result=10081;}break;
		case leMacCroatian: {result=10082;}break;
		case leUTF32LittleEndianByteOrder: {result=12000;}break;
		case leUTF32BigEndianByteOrder: {result=12001;}break;
		case leCNSTaiwan: {result=20000;}break;
		case leTCATaiwan: {result=20001;}break;
		case leEtenTaiwan: {result=20002;}break;
		case leIBM5550Taiwan: {result=20003;}break;
		case leTeleTextTaiwan: {result=20004;}break;
		case leWangTaiwan: {result=20005;}break;
		case leIA5WesternEuropean: {result=20105;}break;
		case leIA5German: {result=20106;}break;
		case leIA5Swedish: {result=20107;}break;
		case leIA5Norwegian: {result=20108;}break;
		case leUSASCII: {result=20127;}break;
		case leT61: {result=20261;}break;
		case leISO6937: {result=20269;}break;
		case leIBM273Germany: {result=20273;}break;
		case leIBM277DenmarkNorway: {result=20277;}break;
		case leIBM278FinlandSweden: {result=20278;}break;
		case leIBM280Italy: {result=20280;}break;
		case leIBM284LatinAmericaSpain: {result=20284;}break;
		case leIBM285UnitedKingdom: {result=20285;}break;
		case leIBM290JapaneseKatakanaExt: {result=20290;}break;
		case leIBM297France: {result=20297;}break;
		case leIBM420Arabic: {result=20420;}break;
		case leIBM423Greek: {result=20423;}break;
		case leIBM424Hebrew: {result=20424;}break;
		case leIBMKoreanExtended: {result=20833;}break;
		case leIBMThai: {result=20838;}break;
		case leRussianKOI8R: {result=20866;}break;
		case leIBM871Icelandic: {result=20871;}break;
		case leIBM880CyrillicRussian: {result=20880;}break;
		case leIBM905Turkish: {result=20905;}break;
		case leIBM00924Latin1: {result=20924;}break;
		case leEUCJapaneseJIS: {result=20932;}break;
		case leSimplifiedChineseGB2312: {result=20936;}break;
		case leKoreanWansung: {result=20949;}break;
		case leEBCDICCyrillicSerbianBulgarian: {result=21025;}break;
		case leUkrainianKOI8U: {result=21866;}break;
		case leISO88591Latin1: {result=28591;}break;
		case leISO88592CentralEuropean: {result=28592;}break;
		case leISO88593Latin3: {result=28593;}break;
		case leISO88594Baltic: {result=28594;}break;
		case leISO88595Cyrillic: {result=28595;}break;
		case leISO88596Arabic: {result=28596;}break;
		case leISO88597Greek: {result=28597;}break;
		case leISO88598HebrewVisual: {result=28598;}break;
		case leISO88599Turkish: {result=28599;}break;
		case leISO885913Estonian: {result=28603;}break;
		case leISO885915Latin9: {result=28605;}break;
		case leEuropa3: {result=29001;}break;
		case leISO88598HebrewLogical: {result=38598;}break;
		case leISO2022JapaneseNoHalfwidthKatakana: {result=50220;}break;
		case leISO2022JapaneseWithHalfwidthKatakana: {result=50221;}break;
		case leISO2022JapaneseAllow1ByteKana: {result=50222;}break;
		case leISO2022Korean: {result=50225;}break;
		case leISO2022SimplifiedChinese: {result=50227;}break;
		case leISO2022TraditionalChinese: {result=50229;}break;
		case leEBCDICJapaneseExt: {result=50930;}break;
		case leEBCDICUSCanadaAndJapanese: {result=50931;}break;
		case leEBCDICKoreanExtAndKorean: {result=50933;}break;
		case leEBCDICSimplifiedChineseExtSimplifiedChinese: {result=50935;}break;
		case leEBCDICSimplifiedChinese: {result=50936;}break;
		case leEBCDICUSCanadaAndTraditionalChinese: {result=50937;}break;
		case leEBCDICJapaneseLatinExtAndJapanese: {result=50939;}break;
		case leEUCJapanese: {result=51932;}break;
		case leEUCSimplifiedChinese: {result=51936;}break;
		case leEUCKorean: {result=51949;}break;
		case leEUCTraditionalChinese: {result=51950;}break;
		case leHZGB2312SimplifiedChinese: {result=52936;}break;
		case leGB18030SimplifiedChinese: {result=54936;}break;
		case leISCIIDevanagari: {result=57002;}break;
		case leISCIIBengali: {result=57003;}break;
		case leISCIITamil: {result=57004;}break;
		case leISCIITelugu: {result=57005;}break;
		case leISCIIAssamese: {result=57006;}break;
		case leISCIIOriya: {result=57007;}break;
		case leISCIIKannada: {result=57008;}break;
		case leISCIIMalayalam: {result=57009;}break;
		case leISCIIGujarati: {result=57010;}break;
		case leISCIIPunjabi: {result=57011;}break;
		case leUTF7: {result=65000;}break;
		case leUTF8: {result=65001;}break;
	}
	
#endif
	return result;
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

StringData* StringPool::allocate( size_t length )
{
	size_t bytesLength = sizeof(StringData) + (length * sizeof(U16Char)) + sizeof(U16Char);
	if ((next_ + bytesLength) <= limit_) {
		StringData* data = (StringData*)next_;
		data->length = length;
		data->memHdr = currentHdr_;
		data->pool = this;
		data->refcount = 0;
		data->strPtr = (U16Char*) (next_ + sizeof(StringData));
		data->hashID = 0;
		data->ansiStrPtr = 0;

		next_ += bytesLength;
		currentHdr_->next = next_;
		currentHdr_->refcount ++;

		return data;
	}
	
	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (bytesLength <= MAX_CHARALLOC) {	
		allocSize = RoundUp(bytesLength + sizeof(MemHeader), granularity_);

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
	currentHdr->refcount = 0;
	

	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	currentHdr_->next = next_;
	currentHdr_->limit = limit_;
	
	return allocate(length);
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
		data->ansiStrPtr = 0;

		next_ += length;
		currentHdr_->next = next_;
		currentHdr_->refcount ++;

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
	currentHdr->refcount = 0;
	

	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	currentHdr_->next = next_;
	currentHdr_->limit = limit_;


	return allocate(begin, end);
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

StringData* StringPool::transformAnsiToUnicode( const char* str, size_t length, LanguageEncoding encoding )
{
	StringData* result = NULL;

	unsigned int enc = StringPool::getNativeEncoding(encoding);

	int size = MultiByteToWideChar( enc, 0, str, length, NULL, 0 );

	if ( size <= 0 ) {
		//throw RuntimeException( L"size > 0 MultiByteToWideChar() failed in UnicodeString::transformAnsiToUnicode()" );
		return NULL;
	}

	StringData* newStr = allocate( (size_t)size );

	size = MultiByteToWideChar( enc, 0, str, length, newStr->strPtr, newStr->length );

	result = find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {
		newStr->hashID = hash(newStr->strPtr, newStr->length);
		stringMap_.insert(StringMapPairT(newStr->hashID,newStr));
		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		next_ -= bytesLength;
		totalBytesAllocated_ -= bytesLength;


	//	currentHdr_ = currentHdr;
	//next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));


		if ( next_ == reinterpret_cast<unsigned char*>(currentHdr_ + sizeof(U16Char)) ) {
			//at begining , maybe we take out the whole thing
			if ( NULL != currentHdr_->prev ) {
				if ( currentHdr_->prev->next < currentHdr_->prev->limit ) {
					MemHeader* tmp = currentHdr_;
					currentHdr_ = currentHdr_->prev;
					next_ = currentHdr_->next;
					limit_ = currentHdr_->limit;

					VirtualFree(tmp, 0, MEM_RELEASE);
				}
			}
		}
	}

	return result;
}

StringData* StringPool::addString( const char* str, size_t length, LanguageEncoding encoding )
{
	StringData* result = NULL;
	StringPool* pool = StringPool::getUsablePool();
	if ( NULL == pool ) {
		return NULL;
	}

	result = pool->transformAnsiToUnicode( str, length, encoding );	

	return result;
}

StringData* StringPool::addString( const U16Char* str, size_t length )
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
		//multimap::insert is *expensive*. This is what changes
		//loading and parsing around 34,000 entries in a dictionary
		//from taking between 250ms to 137ms (with the insert) to
		//taking 45ms (without the insert). Ultimately the
		//multimap needs to go in favor of some other 
		//associative container.
		//////////////////////////////////////////////////////

		pool->stringMap_.insert(StringMapPairT(newStr->hashID,result));
	}

	return result;
}

char* StringPool::transformToAnsi( StringData* handle, LanguageEncoding encoding )
{
	char* result = NULL;

	StringData* data = (StringData*)handle;

	if ( NULL != data ) {
		int len = data->length;
		if ( data->length == 0 ) {
			len = 1;
		}

		unsigned int enc = StringPool::getNativeEncoding(encoding);

		int size = ::WideCharToMultiByte( enc, 0, data->strPtr, len,
											NULL, 0, NULL, NULL );

		if ( size <= 0 ) {
			return NULL;
		}

		result = new char[size+1];

		if (  0 == ::WideCharToMultiByte( enc, 0, data->strPtr, len,
											result, size, NULL, NULL ) ) {
				//WideCharToMultiByte failed
				delete [] result;
				result = NULL;
		}
		else {
			result[size] = 0;
			data->ansiStrPtr = result;
		}
	}

	return result;
}

uint32 StringPool::incStringRefcount( StringData* data )
{
	if ( NULL != data ) {
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

uint32 StringPool::decStringRefcount( StringData* data )
{
	if ( NULL != data ) {
		StringPool* pool = data->pool;
		if ( pool->getThreadID() == ::GetCurrentThreadId() ) {
			if ( data->refcount > 0 ) {
				data->refcount--;

				if ( 0 == data->refcount ) {
					if ( data->memHdr->refcount > 0 ) {
						data->memHdr->refcount --;
					}
					else {
						if ( pool->compactsMemory() ) {
							printf( "Memhdr refcount is already at 0!!!\n" );
						}
					}
					if ( 0 == data->memHdr->refcount ) {
						if ( pool->compactsMemory() ) {
							if ( data->memHdr != pool->currentHdr_ ) {
								//MemHeader* tmp = data->memHdr;
								//currentHdr_ = currentHdr_->prev;
								//next_ = currentHdr_->next;
								//limit_ = currentHdr_->limit;

								StringPool::StringMapIter it = pool->stringMap_.begin();
								size_t count = 0;
								while ( it != pool->stringMap_.end() ) {
									if ( it->second->memHdr == data->memHdr ) {

										if ( it->second->refcount != 0 ) {
											printf( "String data %p {%ls} still has ref count(%u) > 0\n", it->second, it->second->strPtr,  it->second->refcount );
											return 0;
										}

										StringPool::StringMapIter tmp = it;
										++it;
										pool->stringMap_.erase(tmp);
										count++;
									}
									else {
										++it;
									}
								}
								printf( "yanked %u strings\n", count );
								size_t bytesFreed = data->memHdr->size;
								void* ptr = data->memHdr;
								if ( VirtualFree(data->memHdr, 0, MEM_RELEASE) ) {
									pool->totalBytesAllocated_ -= bytesFreed;
									printf( "Freed %u bytes of data %p\n", bytesFreed, ptr );
								}
								else {
									printf( "VirtualFree failed. GetLastError(): %d\n", GetLastError() );
								}

								return 0;

							}
						}
					}

					return 0;
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
}

bool StringPool::equals( StringData* lhs, StringData* rhs )
{
	if ( lhs == rhs ) {
		return true;
	}

	if ( lhs->length != rhs->length ) {
		return false;
	}

	if ( (lhs->pool == rhs->pool) || (lhs->pool->getThreadID() == rhs->pool->getThreadID()) ) {
		return 0 == StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, lhs->length );
	}
	else {
		//different threads, different pools, do we need to lock here??
		return 0 == StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, lhs->length );
	}

	return false;
}

int StringPool::compare( StringData* lhs, StringData* rhs )
{
	if ( lhs == rhs ) {
		return 0;
	}

	if ( (lhs->pool == rhs->pool) || (lhs->pool->getThreadID() == rhs->pool->getThreadID()) ) {
		return StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, lhs->length );
	}
	else {
		//different threads, different pools, do we need to lock here??
		return StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, lhs->length );
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

	FastString( const U16Char* str, size_t length ): data_(NULL) {
		assign( str, length );
	}

	FastString( const char* str, size_t length, LanguageEncoding encoding=leDefault ): data_(NULL) {
		assign( str, length, encoding );
	}

	FastString( const unsigned char* str, size_t length, LanguageEncoding encoding=leDefault ): data_(NULL) {
		assign( (const char*)str, length, encoding );
	}

	FastString(): data_(NULL){}

	FastString( const FastString& f ):data_(f.data_) {
		StringPool::incStringRefcount(data_);
	}


	~FastString() {
		StringPool::decStringRefcount(data_);
	}

	operator const U16Char*() const {
		return data_->strPtr;
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


	bool operator == ( const FastString& rhs ) const {
		return StringPool::equals(data_, rhs.data_ );
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

	int compare( const FastString& rhs ) const {
		return StringPool::compare( data_, rhs.data_ );
	}

	FastString substr( size_type pos, size_type length ) const {
		return FastString( data_->strPtr + pos, length );
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

    const_reference at(size_type pos) const {
		if ( pos >= length() ) {
			throw std::out_of_range("array index is too large");
		}
		return data_->strPtr[ pos ];
	}

    const_reference operator[](size_type pos) const {
		return data_->strPtr[ pos ];
	}

	void swap( FastString& str ) {
		if ( str.data_ != data_ ) {			
			StringData* tmp = data_;
			data_ = str.data_;
			str.data_ = tmp;
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

	size_type find( const U16Char* searchStr, size_type pos, size_type len) const {
		size_type strLen = length();

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



	//utility

protected:
	StringData* data_;
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

	/*
	std::locale old = std::locale::global(std::locale(".950"));

	std::wifstream src;
	src.imbue(std::locale(".950"));
	src.open("cedict.b5");
	src.seekg( 0, std::ios_base::end );
	size_t sz = src.tellg();
	src.seekg( 0, std::ios_base::beg );
	
	unsigned short* data = new unsigned short[ sz ];

	src.read( data, sz );

	wstring chStr( data, sz );//, UnicodeString::leChineseTraditionalBig5);

	delete [] data;


	const unsigned short* P = chStr.c_str();
	const unsigned short* start = P;
	const unsigned short* line = start;
	wstring s;
	while ( P-start < sz ) {
		if ( *P == L'\r' || *P == L'\n' ) {
			if ( *P == L'\r' && *(P+1) == L'\n' ) {
				P++;
			}

			if (P-line > 0 && line[0] != L'#') {
				s.assign(line,P-line);

				ChDictionaryEntry de;
				if (de.Parse(s)) {
					v.push_back(de);
				}
			}


			P++;
			line = P;
		}
		P++;
	}
*/

/*
	//StringTokenizer tok(chStr,"\r\n");

	while ( tok.hasMoreElements() ) {
		String s = tok.nextElement();
		if (s.length() > 0 && s[0] != L'#') {
			ChDictionaryEntry de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}
	}
*/
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
	/*
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
	*/
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
	FILE* f = fopen("cedict.b5","rb");
	fseek(f,0,SEEK_END);
	size_t sz = ftell(f);
	fseek(f,0,SEEK_SET);
	
	unsigned char* data = new unsigned char[ sz ];

	fread(data,sz,1,f);
	fclose(f);

	FastString chStr(data,sz,leChineseTraditionalBig5);

	delete [] data;


	const U16Char*  P = (const U16Char*)chStr.c_str();
	const U16Char*  start = P;
	const U16Char*  line = P;

	sz = chStr.length();
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
	printf( "====part3()====================================================================\n" );

	FastString fs;
	_bstr_t b = "asdasdasd";

	fs = b;

	BSTR b2 = fs.toBSTR();

	_variant_t v = fs;

	VARIANT v2 = fs;

	printf( "====End of part3()=============================================================\n" );
}


int main( int argc, char** argv )
{

//	FoundationKit::init( argc, argv );

	
	StringPool stringPool;
	stringPool.makeCurrentPool();
	stringPool.setCompactsMemory(true);


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
		
		StringData* idx = sp.addString(s,4);
		
		
		StringData* idx2 = sp.addString(s,4);
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

	printf( "fs Length %u, (f = BIGSTR) took %0.8f seconds\n",f.length(),clock.duration() );

	clock.start();
	f = BIGSTR2;
	clock.stop();

	printf( "fs Length %u, (f = BIGSTR2) took %0.8f seconds %0.8f ms\n",f.length(),clock.duration(),clock.duration()*1000.0 );


	
	clock.start();
	f = BIGSTR2;
	clock.stop();

	printf( "fs Length %u, (f = BIGSTR2) took %0.8f seconds\n",f.length(),clock.duration() );


	FastString f2;
	clock.start();
	f2 = f;
	clock.stop();

	printf( "fs Length %u, (f2 = f) took %0.8f seconds\n",f2.length(),clock.duration() );

	printf( "===============================================================================\n" );
	printf( "===============================================================================\n" );





	String s;
	clock.start();
	s = L"Hola!";
	clock.stop();


	printf( "basic_string<> s Length %u, took %0.8f seconds\n", s.length(),clock.duration() );

	

	clock.start();
	s = BIGSTR;
	clock.stop();

	printf( "basic_string<> s Length %u, (s = BIGSTR) took %0.8f seconds\n", s.length(),clock.duration() );

	clock.start();
	s = BIGSTR2;
	clock.stop();

	printf( "basic_string<> s Length %u, (s = BIGSTR2) took %0.8f seconds\n", s.length(),clock.duration() );



	clock.start();
	s = BIGSTR2;
	clock.stop();

	printf( "basic_string<> s Length %u, (s = BIGSTR2) took %0.8f seconds\n", s.length(),clock.duration() );


	String s2;

	clock.start();
	s2 = s;
	clock.stop();

	printf( "basic_string<>  s2 Length %u, (s2 = s) took %0.8f seconds\n",s2.length(),clock.duration() );



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





	part2();


	part3();

	printf( "num entries in string pool: %u\n", StringPool::getUsablePool()->uniqueEntries() );
	printf( "total bytes in string pool: %u\n", StringPool::getUsablePool()->totalBytesAllocated() );

	Sleep(10000000);

//	FoundationKit::terminate();

	return 0;
}


