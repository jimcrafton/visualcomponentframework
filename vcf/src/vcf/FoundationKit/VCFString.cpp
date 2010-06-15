//VCFString.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top UnicodeString::level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/TextCodec.h"

#ifndef VCF_WIN32CE
#include <errno.h>
#endif


namespace VCF {




#ifdef USE_STRINGPOOL	

DWORD StringPool::threadPoolTLSIndex = 0;

StringPool::StringPoolTLSGuard* StringPool::poolTLSGuard = NULL;
std::deque<StringPool*>* StringPool::stringPoolStack = NULL;


void StringPool::debug()
{
	printf( ">>>>>>>>>StringPool::debug()<<<<<<<<<<<\n" );
	printf( "allocatedHdrs length: %u\n", allocatedHdrs_.size() );

	std::vector<MemHeader*>::iterator it =  allocatedHdrs_.begin();
	while ( it != allocatedHdrs_.end() ) {
		MemHeader* m = *it;
		
		printf( "MemHeader %p, refc: %u, size: %u\n", m, m->refcount, m->size );
		++it;
	}


	StringMapIter it2 = this->stringMap_.begin();
	size_t prevHash = 0;

	printf( "strings in map: %u\n", stringMap_.size() );
	while( it2 != stringMap_.end() ) {
		size_t h = it2->first;
		StringData* s = it2->second;

		if ( prevHash != h ) {
			printf( "Hash key: %u\n", h );
		}

		printf( "\tStr %p[%u, refc: %u, hdr: %p] : %.*S%s\n", 
				s, 
				s->length, 
				s->refcount, 
				s->memHdr, 
				(s->length > 20) ? 20 : s->length, 
				s->strPtr,
				(s->length > 20) ? "..." : "" );

		prevHash = h;

		++it2;
	}	
}


StringPool* StringPool::getUsablePool()
{
	if ( NULL == StringPool::stringPoolStack ) {
		StringPool::stringPoolStack = new std::deque<StringPool*>();
	}

	if ( !StringPool::stringPoolStack->empty() ) {
		return StringPool::stringPoolStack->back();
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

		if ( NULL == StringPool::poolTLSGuard ) {
			StringPool::poolTLSGuard = new StringPool::StringPoolTLSGuard();
		}

		StringPool::poolTLSGuard->threadPools.push_back( currentThreadPool );
		TlsSetValue( StringPool::threadPoolTLSIndex, currentThreadPool );
	}

	return currentThreadPool;
}



unsigned int StringPool::getNativeEncoding(int encoding)
{
	unsigned int result = -1;
#ifdef WIN32
	

	UnicodeString::LanguageEncoding tmp = (UnicodeString::LanguageEncoding)encoding;
	if ( encoding == UnicodeString::leDefault ) {
		tmp = UnicodeString::leUTF8 ;
		//Locale* locale = System::getCurrentThreadLocale();
		//if ( NULL != locale ) {
		//	tmp = locale->getEncoding();
		//}
	}


	
	switch (tmp) {				
		case UnicodeString::leIBM037: {result=037;}break;
		case UnicodeString::leIBM437: {result=437;}break;
		case UnicodeString::leIBM500: {result=500;}break;
		case UnicodeString::leArabic708: {result=708;}break;
		case UnicodeString::leArabic449: {result=709;}break;
		case UnicodeString::leArabicTransparent: {result=710;}break;
		case UnicodeString::leDOSArabic: {result=720;}break;
		case UnicodeString::leGreek: {result=737;}break;
		case UnicodeString::leBaltic: {result=775;}break;
		case UnicodeString::leLatin1: {result=850;}break;
		case UnicodeString::leLatin2: {result=852;}break;
		case UnicodeString::leCyrillic: {result=855;}break;
		case UnicodeString::leTurkish: {result=857;}break;
		case UnicodeString::leMultilingualLatin1: {result=858;}break;
		case UnicodeString::lePortuguese: {result=860;}break;
		case UnicodeString::leIcelandic: {result=861;}break;
		case UnicodeString::leHebrew: {result=862;}break;
		case UnicodeString::leFrenchCanadian: {result=863;}break;
		case UnicodeString::leArabic864: {result=864;}break;
		case UnicodeString::leNordic: {result=865;}break;
		case UnicodeString::leRussianCyrillic: {result=866;}break;
		case UnicodeString::leModernGreek: {result=869;}break;
		case UnicodeString::leEBCDICLatin2: {result=870;}break;
		case UnicodeString::leThai: {result=874;}break;
		case UnicodeString::leEBCDICGreekModern: {result=875;}break;
		case UnicodeString::leShiftJIS: {result=932;}break;
		case UnicodeString::leSimplifiedChinese: {result=936;}break;
		case UnicodeString::leKorean: {result=949;}break;
		case UnicodeString::leChineseTraditionalBig5: {result=950;}break;
		case UnicodeString::leEBCDICTurkish: {result=1026;}break;
		case UnicodeString::leEBCDICLatin1: {result=1047;}break;
		case UnicodeString::leEBCDICUSCanada: {result=1140;}break;
		case UnicodeString::leEBCDICGermany: {result=1141;}break;
		case UnicodeString::leEBCDICDenmarkNorway: {result=1142;}break;
		case UnicodeString::leEBCDICFinlandSweden: {result=1143;}break;
		case UnicodeString::leEBCDICItaly: {result=1144;}break;
		case UnicodeString::leEBCDICLatinAmericaSpain: {result=1145;}break;
		case UnicodeString::leEBCDICUnitedKingdom: {result=1146;}break;
		case UnicodeString::leEBCDICFrance: {result=1147;}break;
		case UnicodeString::leEBCDICInternational: {result=1148;}break;
		case UnicodeString::leEBCDICIcelandic: {result=1149;}break;
		case UnicodeString::leUTF16LittleEndianByteOrder: {result=1200;}break;
		case UnicodeString::leUTF16BigEndianByteOrder: {result=1201;}break;
		case UnicodeString::leANSICentralEuropean: {result=1250;}break;
		case UnicodeString::leANSICyrillic: {result=1251;}break;
		case UnicodeString::leANSILatin1: {result=1252;}break;
		case UnicodeString::leANSIGreek: {result=1253;}break;
		case UnicodeString::leANSITurkish: {result=1254;}break;
		case UnicodeString::leANSIHebrew: {result=1255;}break;
		case UnicodeString::leANSIArabic: {result=1256;}break;
		case UnicodeString::leANSIBaltic: {result=1257;}break;
		case UnicodeString::leANSIVietnamese: {result=1258;}break;
		case UnicodeString::leJohabKorean: {result=1361;}break;
		case UnicodeString::leMacRoman: {result=10000;}break;
		case UnicodeString::leMacJapanese: {result=10001;}break;
		case UnicodeString::leMacTraditionalChineseBig5: {result=10002;}break;
		case UnicodeString::leMacKorean: {result=10003;}break;
		case UnicodeString::leMacArabic: {result=10004;}break;
		case UnicodeString::leMacHebrew: {result=10005;}break;
		case UnicodeString::leMacGreek: {result=10006;}break;
		case UnicodeString::leMacCyrillic: {result=10007;}break;
		case UnicodeString::leMacSimplifiedChinese: {result=10008;}break;
		case UnicodeString::leMacRomanian: {result=10010;}break;
		case UnicodeString::leMacUkrainian: {result=10017;}break;
		case UnicodeString::leMacThai: {result=10021;}break;
		case UnicodeString::leMacLatin2: {result=10029;}break;
		case UnicodeString::leMacIcelandic: {result=10079;}break;
		case UnicodeString::leMacTurkish: {result=10081;}break;
		case UnicodeString::leMacCroatian: {result=10082;}break;
		case UnicodeString::leUTF32LittleEndianByteOrder: {result=12000;}break;
		case UnicodeString::leUTF32BigEndianByteOrder: {result=12001;}break;
		case UnicodeString::leCNSTaiwan: {result=20000;}break;
		case UnicodeString::leTCATaiwan: {result=20001;}break;
		case UnicodeString::leEtenTaiwan: {result=20002;}break;
		case UnicodeString::leIBM5550Taiwan: {result=20003;}break;
		case UnicodeString::leTeleTextTaiwan: {result=20004;}break;
		case UnicodeString::leWangTaiwan: {result=20005;}break;
		case UnicodeString::leIA5WesternEuropean: {result=20105;}break;
		case UnicodeString::leIA5German: {result=20106;}break;
		case UnicodeString::leIA5Swedish: {result=20107;}break;
		case UnicodeString::leIA5Norwegian: {result=20108;}break;
		case UnicodeString::leUSASCII: {result=20127;}break;
		case UnicodeString::leT61: {result=20261;}break;
		case UnicodeString::leISO6937: {result=20269;}break;
		case UnicodeString::leIBM273Germany: {result=20273;}break;
		case UnicodeString::leIBM277DenmarkNorway: {result=20277;}break;
		case UnicodeString::leIBM278FinlandSweden: {result=20278;}break;
		case UnicodeString::leIBM280Italy: {result=20280;}break;
		case UnicodeString::leIBM284LatinAmericaSpain: {result=20284;}break;
		case UnicodeString::leIBM285UnitedKingdom: {result=20285;}break;
		case UnicodeString::leIBM290JapaneseKatakanaExt: {result=20290;}break;
		case UnicodeString::leIBM297France: {result=20297;}break;
		case UnicodeString::leIBM420Arabic: {result=20420;}break;
		case UnicodeString::leIBM423Greek: {result=20423;}break;
		case UnicodeString::leIBM424Hebrew: {result=20424;}break;
		case UnicodeString::leIBMKoreanExtended: {result=20833;}break;
		case UnicodeString::leIBMThai: {result=20838;}break;
		case UnicodeString::leRussianKOI8R: {result=20866;}break;
		case UnicodeString::leIBM871Icelandic: {result=20871;}break;
		case UnicodeString::leIBM880CyrillicRussian: {result=20880;}break;
		case UnicodeString::leIBM905Turkish: {result=20905;}break;
		case UnicodeString::leIBM00924Latin1: {result=20924;}break;
		case UnicodeString::leEUCJapaneseJIS: {result=20932;}break;
		case UnicodeString::leSimplifiedChineseGB2312: {result=20936;}break;
		case UnicodeString::leKoreanWansung: {result=20949;}break;
		case UnicodeString::leEBCDICCyrillicSerbianBulgarian: {result=21025;}break;
		case UnicodeString::leUkrainianKOI8U: {result=21866;}break;
		case UnicodeString::leISO88591Latin1: {result=28591;}break;
		case UnicodeString::leISO88592CentralEuropean: {result=28592;}break;
		case UnicodeString::leISO88593Latin3: {result=28593;}break;
		case UnicodeString::leISO88594Baltic: {result=28594;}break;
		case UnicodeString::leISO88595Cyrillic: {result=28595;}break;
		case UnicodeString::leISO88596Arabic: {result=28596;}break;
		case UnicodeString::leISO88597Greek: {result=28597;}break;
		case UnicodeString::leISO88598HebrewVisual: {result=28598;}break;
		case UnicodeString::leISO88599Turkish: {result=28599;}break;
		case UnicodeString::leISO885913Estonian: {result=28603;}break;
		case UnicodeString::leISO885915Latin9: {result=28605;}break;
		case UnicodeString::leEuropa3: {result=29001;}break;
		case UnicodeString::leISO88598HebrewLogical: {result=38598;}break;
		case UnicodeString::leISO2022JapaneseNoHalfwidthKatakana: {result=50220;}break;
		case UnicodeString::leISO2022JapaneseWithHalfwidthKatakana: {result=50221;}break;
		case UnicodeString::leISO2022JapaneseAllow1ByteKana: {result=50222;}break;
		case UnicodeString::leISO2022Korean: {result=50225;}break;
		case UnicodeString::leISO2022SimplifiedChinese: {result=50227;}break;
		case UnicodeString::leISO2022TraditionalChinese: {result=50229;}break;
		case UnicodeString::leEBCDICJapaneseExt: {result=50930;}break;
		case UnicodeString::leEBCDICUSCanadaAndJapanese: {result=50931;}break;
		case UnicodeString::leEBCDICKoreanExtAndKorean: {result=50933;}break;
		case UnicodeString::leEBCDICSimplifiedChineseExtSimplifiedChinese: {result=50935;}break;
		case UnicodeString::leEBCDICSimplifiedChinese: {result=50936;}break;
		case UnicodeString::leEBCDICUSCanadaAndTraditionalChinese: {result=50937;}break;
		case UnicodeString::leEBCDICJapaneseLatinExtAndJapanese: {result=50939;}break;
		case UnicodeString::leEUCJapanese: {result=51932;}break;
		case UnicodeString::leEUCSimplifiedChinese: {result=51936;}break;
		case UnicodeString::leEUCKorean: {result=51949;}break;
		case UnicodeString::leEUCTraditionalChinese: {result=51950;}break;
		case UnicodeString::leHZGB2312SimplifiedChinese: {result=52936;}break;
		case UnicodeString::leGB18030SimplifiedChinese: {result=54936;}break;
		case UnicodeString::leISCIIDevanagari: {result=57002;}break;
		case UnicodeString::leISCIIBengali: {result=57003;}break;
		case UnicodeString::leISCIITamil: {result=57004;}break;
		case UnicodeString::leISCIITelugu: {result=57005;}break;
		case UnicodeString::leISCIIAssamese: {result=57006;}break;
		case UnicodeString::leISCIIOriya: {result=57007;}break;
		case UnicodeString::leISCIIKannada: {result=57008;}break;
		case UnicodeString::leISCIIMalayalam: {result=57009;}break;
		case UnicodeString::leISCIIGujarati: {result=57010;}break;
		case UnicodeString::leISCIIPunjabi: {result=57011;}break;
		case UnicodeString::leUTF7: {result=65000;}break;
		case UnicodeString::leUTF8: {result=65001;}break;
	}
	
#endif
	return result;
}

void StringPool::terminate()
{
	delete StringPool::poolTLSGuard;
	delete StringPool::stringPoolStack;
}


StringPool::StringPool():
	onlyUseMemPooling_(false),
	next_(NULL),
	limit_(NULL),
	currentHdr_(NULL),
	granularity_(0),
	totalBytesAllocated_(0),
	threadID_(0),
	compactMemory_(false),
	stringAllocator_(NULL),
	stringDeallocator_(NULL)
{
	
#ifdef WIN32

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	granularity_ = RoundUp(sizeof(MemHeader) + MIN_CBCHUNK,
								si.dwAllocationGranularity);

	threadID_ = ::GetCurrentThreadId();
#endif

}

StringPool::~StringPool()
{
	StringMapIter it2 = this->stringMap_.begin();
	
	while( it2 != stringMap_.end() ) {		
		StringData* s = it2->second;		

		s->pool = NULL;

		++it2;
	}	



	std::vector<MemHeader*>::iterator it = allocatedHdrs_.begin();
	while ( it != allocatedHdrs_.end() ) {
		MemHeader* hdr = *it;

		size_t sz = hdr->size;
		if ( StringPool::freeMem(hdr, hdr->size) ) {
			totalBytesAllocated_ -= sz;
		}

		++it;
	}

	allocatedHdrs_.clear();

	printf( "StringPool::~StringPool() totalBytesAllocated_: %u\n", totalBytesAllocated_ );
}


void StringPool::setOnlyUsesMemoryPooling( bool val )
{
	if ( val != onlyUseMemPooling_ ) {
		onlyUseMemPooling_ = val;
		if ( onlyUseMemPooling_ ) {
			stringMap_.clear();
		}
	}	
}

MemHeader* StringPool::nextHdr( MemHeader* current ) 
{
	MemHeader* result = NULL;

	if ( allocatedHdrs_.empty() ) {
		return NULL;
	}

	std::vector<MemHeader*>::iterator found = std::find( allocatedHdrs_.begin(), allocatedHdrs_.end(), current );
	if ( found != allocatedHdrs_.end() ) {
		++found;
		if ( found != allocatedHdrs_.end() ) {
			result = *found;
		}
	}

	return result;
}

MemHeader* StringPool::prevHdr( MemHeader* current )
{
	MemHeader* result = NULL;

	if ( allocatedHdrs_.empty() ) {
		return NULL;
	}

	std::vector<MemHeader*>::iterator found = std::find( allocatedHdrs_.begin(), allocatedHdrs_.end(), current );
	if ( found != allocatedHdrs_.end() && found != allocatedHdrs_.begin() ) {
		--found;		
		result = *found;
	}

	return result;
}

StringData* StringPool::allocateUnmanagedString( const U16Char* str, size_t length )
{
	StringData* result = NULL;

	return result;
}

StringData* StringPool::allocateUnmanagedString( const char* str, size_t length, int encoding )
{
	StringData* result = NULL;

	return result;
}

StringData* StringPool::allocate( size_t length )
{
	size_t bytesLength = sizeof(StringData) + (length * sizeof(U16Char)) + sizeof(U16Char);
	if ((next_ + bytesLength) <= limit_) {
		StringData* data = (StringData*)next_;

		initStringData( data, NULL, length );

		next_ += bytesLength;
		currentHdr_->next = next_;
		currentHdr_->refcount ++;
		return data;
	}
	
	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (bytesLength <= MAX_CHARALLOC) {	
		allocSize = RoundUp(bytesLength + sizeof(MemHeader), granularity_);

		nextBytes = reinterpret_cast<unsigned char*>( StringPool::allocMem(allocSize) );
	}

	if (!nextBytes) {
		static std::bad_alloc outOfMemException;
		throw(outOfMemException);
	}

	totalBytesAllocated_ += allocSize;
	
	limit_ = reinterpret_cast<unsigned char*>(nextBytes + allocSize);
	MemHeader* currentHdr = reinterpret_cast<MemHeader*>(nextBytes);
//	currentHdr->prev = currentHdr_;
	currentHdr->size = allocSize;
	currentHdr->refcount = 0;
	

	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	currentHdr_->next = next_;
	currentHdr_->limit = limit_;
	
	allocatedHdrs_.push_back( currentHdr_ );
	
	return allocate(length);
}

void StringPool::initStringData( StringData* data, const U16Char* strPtr, size_t length )
{
	data->length = length;
	data->memHdr = currentHdr_;
	data->pool = this;
	data->refcount = 0;
	data->strPtr = (U16Char*) (next_ + sizeof(StringData));
	data->hashID = 0;
	data->ansiStrPtr = 0;
	data->extra = NULL;
	data->bits = 0;

	if ( NULL != strPtr ) {
		StringPool::wmemcpy( data->strPtr, strPtr, data->length );
		data->strPtr[data->length] = 0;
		if ( !onlyUseMemPooling_ ) {
			data->hashID = StringPool::hash(data->strPtr, data->length);
		}
	}
}

StringData* StringPool::allocate(const U16Char* begin, const U16Char* end)
{
	size_t length = sizeof(StringData) + ((end - begin) * sizeof(U16Char)) + sizeof(U16Char);
	if ((next_ + length) <= limit_) {
		StringData* data = (StringData*)next_;
		
		initStringData( data, begin, (end - begin) );

		next_ += length;
		currentHdr_->next = next_;
		currentHdr_->refcount ++;
		return data;
	}
	
	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (length <= MAX_CHARALLOC) {	
		allocSize = RoundUp(length + sizeof(MemHeader), granularity_);
		nextBytes = reinterpret_cast<unsigned char*>( StringPool::allocMem( allocSize ) );
	}

	if (!nextBytes) {
		static std::bad_alloc outOfMemException;
		throw(outOfMemException);
	}

	totalBytesAllocated_ += allocSize;
	
	limit_ = reinterpret_cast<unsigned char*>(nextBytes + allocSize);
	MemHeader* currentHdr = reinterpret_cast<MemHeader*>(nextBytes);
//	currentHdr->prev = currentHdr_;
	currentHdr->size = allocSize;
	currentHdr->refcount = 0;
	

	currentHdr_ = currentHdr;
	next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	currentHdr_->next = next_;
	currentHdr_->limit = limit_;
	allocatedHdrs_.push_back( currentHdr_ );

	return allocate(begin, end);
}


StringData* StringPool::find( const U16Char* str, size_t length, const uint32& hashID )
{
	StringData* result = NULL;

	

	if ( stringMap_.empty() ) {
		return NULL;
	}


	if ( onlyUseMemPooling_ ) {
		return NULL;
	}

	uint32 realHashID = (0 == hashID) ? StringPool::hash(str,length) : hashID;

	StringMapRangeT found = stringMap_.equal_range( realHashID );
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


StringData* StringPool::transformAnsiToUnicode( const char* str, size_t length, int encoding )
{
	StringData* result = NULL;

	if ( length == 0 ) {
		return NULL;
	}


	unsigned int enc = StringPool::getNativeEncoding(encoding);

	int size = MultiByteToWideChar( enc, 0, str, length, NULL, 0 );

	if ( size <= 0 ) {
		//throw RuntimeException( L"size > 0 MultiByteToWideChar() failed in UnicodeString::transformAnsiToUnicode()" );
		return NULL;
	}

	StringData* newStr = allocate( (size_t)size );

	size = MultiByteToWideChar( enc, 0, str, length, newStr->strPtr, newStr->length );

	newStr->strPtr[size] = 0;

	result = find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {

		if ( !onlyUseMemPooling_ ) {
			newStr->hashID = hash(newStr->strPtr, newStr->length);
			stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		newStr->extra = new StringExtraData();
		newStr->extra->encoding = (UnicodeString::LanguageEncoding)encoding;


		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		printf( "reclaim the memory, found an existing instance for transformAnsiToUnicode()\n\tstr: %s\n",str );
		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		next_ -= bytesLength;
		totalBytesAllocated_ -= bytesLength;

		freeStringData( newStr );
	}

	return result;
}

StringData* StringPool::addString( const char* str, size_t length, int encoding )
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
		if ( !pool->onlyUseMemPooling_ ) {
			pool->stringMap_.insert(StringMapPairT(newStr->hashID,result));
		}		
	}

	return result;
}

char* StringPool::transformToAnsi( StringData* handle, int encoding )
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


void StringPool::freeMemHeader( MemHeader* memHdr )
{
	std::vector<MemHeader*>::iterator found = 
		std::find( allocatedHdrs_.begin(), 
					allocatedHdrs_.end(), memHdr );
	if ( found != allocatedHdrs_.end() ) {
		allocatedHdrs_.erase( found );
	}

	size_t bytesFreed = memHdr->size;
	if ( StringPool::freeMem(memHdr, 0 ) ) {
		totalBytesAllocated_ -= bytesFreed;
	}
	else {
		printf( "StringPool::freeMem failed. GetLastError(): %d\n", GetLastError() );
	}
}

void StringPool::freeStringData( StringData* data )
{
	if ( NULL != data->extra ) {

		//adjust child substring nodes
		if ( NULL != data->extra->nextSubstr ) {
			StringData* next = data->extra->nextSubstr;
			while ( next != NULL ) {
				if ( NULL != next->extra ) {
					StringData* nx = next->extra->nextSubstr;
					next->extra->substrParent = NULL;
					next->extra->nextSubstr = NULL;

					//re-hash the string data here to make it "independent"

					//if the string already exists, then just 


					next = nx;

					//if ( NULL != next ) {
					//	next->extra->nextSubstr = NULL;
					//}
				}
				else {
					next = NULL;
				}
			}
		}	

		delete data->extra;
		data->extra = NULL;
	}
	

	if ( data->memHdr->refcount > 0 ) {
		data->memHdr->refcount --;
	}
	else {
		if ( compactsMemory() ) {
			//printf( "Memhdr refcount is already at 0!!!\n" );
		}
	}


	if ( 0 == data->memHdr->refcount ) {
		if ( compactsMemory() ) {
			bool outstandingStrHandles = false;
			bool deleteMemHdr = true;

			if ( data->memHdr == currentHdr_ ) {
				if ( next_ == reinterpret_cast<unsigned char*>(currentHdr_ + sizeof(U16Char)) ) {
					//at begining , maybe we take out the whole thing

					MemHeader* prev = this->prevHdr( currentHdr_ );

					if ( NULL != prev ) {
						if ( prev->next < prev->limit ) {							
							currentHdr_ = prev;
							next_ = currentHdr_->next;
							limit_ = currentHdr_->limit;
							deleteMemHdr = true;
						}
					}
				}
				else {
					deleteMemHdr = false;
				}
			}				

			if ( !stringMap_.empty() ) {
				StringPool::StringMapIter it = stringMap_.begin();
				size_t count = 0;
				std::vector<StringPool::StringMapIter> removeEntries(stringMap_.size());
				while ( it != stringMap_.end() ) {
					StringData* strData = it->second;
					if ( strData->memHdr == data->memHdr ) {

						if ( strData->refcount > 0 ) {
							//printf( "String data %p[%u characters] {%.*S%s} still has ref count(%u) > 0\n", 
							//	strData, 
							//	strData->length, 
							//	(strData->length > 20) ? 20 : strData->length, 
							//	strData->strPtr,  
							//	(strData->length > 20) ? "..." : "",
							//	strData->refcount );


							outstandingStrHandles = true;
							deleteMemHdr = false;
						}
						else {
							removeEntries[count] = it;
							count++;
						}

						++it;						
					}
					else {
						++it;
					}
				}

				for (size_t ri=0;ri<count;ri++) {
					stringMap_.erase(removeEntries[ri]);
				}
			}

			if ( deleteMemHdr ) {
				freeMemHeader( data->memHdr );
			}
			else if ( !deleteMemHdr && !outstandingStrHandles ) {	
				//reset it back to the beginning
				next_ = reinterpret_cast<unsigned char*>(currentHdr_ + sizeof(U16Char));
				currentHdr_->next = next_;
				limit_ = currentHdr_->limit;
			}
		}
	}
}

uint32 StringPool::decStringRefcount( StringData* data )
{
	if ( NULL != data ) {
		StringPool* pool = data->pool;

		if ( NULL == pool ) {
			if ( data->refcount > 0 ) {
				data->refcount--;
			}
			if ( 0 == data->refcount ) {
				if ( data->bits & StringData::NotPoolManaged ) {
					
				}
				else {
					printf( "Orphaned StringData %p!\n", data );
				}
			}
		}
		else if ( pool->getThreadID() == ::GetCurrentThreadId() ) {
			if ( data->refcount > 0 ) {
				data->refcount--;
			}

			if ( 0 == data->refcount ) {
				pool->freeStringData( data );
				return 0;
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

	if ( NULL == rhs || NULL == lhs ) {
		return false;
	}

	if ( lhs->bits & StringData::NotPoolManaged ) {
		
	}	

	if ( lhs->length != rhs->length ) {
		return false;
	}

	if ( lhs->hashID != rhs->hashID && !(lhs->bits & StringData::SubString || rhs->bits & StringData::SubString) ) {
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

bool StringPool::isSubString( StringData* handle )
{
	if ( NULL == handle ) {
		return false;
	}

	if ( NULL == handle->extra ) {
		return false;
	}

	if ( NULL != handle->extra ) {
		return (NULL != handle->extra->substrParent);
	}

	return false;
}

int StringPool::compare( StringData* lhs, StringData* rhs )
{
	if ( lhs == rhs ) {
		return 0;
	}	

	if ( lhs->length == rhs->length && lhs->hashID == rhs->hashID ) {
		return 0;
	}

	size_t sz = lhs->length < rhs->length ? lhs->length : rhs->length;

	if ( (lhs->pool == rhs->pool) || (lhs->pool->getThreadID() == rhs->pool->getThreadID()) ) {
		return  ::wcscmp(  lhs->strPtr, rhs->strPtr );//StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, sz );
	}
	else {
		//different threads, different pools, do we need to lock here??
		return ::wcscmp(  lhs->strPtr, rhs->strPtr );//StringPool::wmemcmp( lhs->strPtr, rhs->strPtr, sz );
	}

	return 0;
}

StringData* StringPool::insert( const U16Char* src, size_t srcLength, StringData* dest, size_t insertPos )
{
	if ( insertPos > dest->length ) {
		return NULL;
	}


	StringData* result = NULL;

	StringPool* pool = dest->pool;

	size_t size = dest->length + srcLength;
	
	StringData* newStr = pool->allocate( size );

	if ( 0 == insertPos ) {
		StringPool::wmemcpy( newStr->strPtr, src, srcLength );
		StringPool::wmemcpy( &newStr->strPtr[srcLength], dest->strPtr, dest->length );		
	}
	else if ( dest->length -1 == insertPos ) {
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, dest->length );
		StringPool::wmemcpy( &newStr->strPtr[dest->length], src, srcLength );
	}
	else {		
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, insertPos );
		StringPool::wmemcpy( &newStr->strPtr[insertPos], src, srcLength );	
		StringPool::wmemcpy( &newStr->strPtr[insertPos+srcLength], &dest->strPtr[insertPos], dest->length - insertPos );	
	}

	result = pool->find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {
		if ( !pool->onlyUseMemPooling_ ) {
			newStr->hashID = StringPool::hash(newStr->strPtr, newStr->length);

			pool->stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		pool->next_ -= bytesLength;
		pool->totalBytesAllocated_ -= bytesLength;

		pool->freeStringData( newStr );
	}
	

	return result;
}	

StringData* StringPool::insert( StringData* src, StringData* dest, size_t insertPos )
{	
	StringData* result = NULL;

	StringPool* pool = NULL;

	if ( NULL == src ) {
		return result;
	}

	if ( NULL != dest ) {
		if ( insertPos > dest->length ) {
			return result;
		}


		if ( (src->pool == dest->pool) || (src->pool->getThreadID() == dest->pool->getThreadID()) ) {
			pool = dest->pool;
		}
		else {
			pool = StringPool::getUsablePool();
		}
	}
	else {

		if ( insertPos > 0 ) {
			return NULL;
		}

		pool = StringPool::getUsablePool();
	}


	

	

	size_t size = src->length;
	if ( NULL != dest ) {
		size += dest->length;
	}
	
	StringData* newStr = pool->allocate( size );

	if ( 0 == insertPos ) {
		StringPool::wmemcpy( newStr->strPtr, src->strPtr, src->length );
		if ( NULL != dest ) {
			StringPool::wmemcpy( &newStr->strPtr[src->length], dest->strPtr, dest->length );		
		}
	}
	else if ( dest->length -1 == insertPos ) {
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, dest->length );
		StringPool::wmemcpy( &newStr->strPtr[dest->length], src->strPtr, src->length );
	}
	else {		
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, insertPos );
		StringPool::wmemcpy( &newStr->strPtr[insertPos], src->strPtr, src->length );	
		StringPool::wmemcpy( &newStr->strPtr[insertPos+src->length], &dest->strPtr[insertPos], dest->length - insertPos );	
	}

	newStr->strPtr[newStr->length] = 0;

	result = pool->find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {
		if ( !pool->onlyUseMemPooling_ ) {
			newStr->hashID = StringPool::hash(newStr->strPtr, newStr->length);

			pool->stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		pool->next_ -= bytesLength;
		pool->totalBytesAllocated_ -= bytesLength;

		pool->freeStringData( newStr );
	}
	

	return result;
}

StringData* StringPool::insert( U16Char ch, StringData* dest, size_t insertPos, size_t repeatCount )
{
	if ( NULL == dest ) {
		return NULL;
	}

	if ( insertPos > dest->length ) {
		return NULL;
	}


	if ( 0 == repeatCount ) {
		return NULL;
	}

	StringData* result = NULL;

	StringPool* pool = dest->pool;	

	size_t size = dest->length + repeatCount;
	
	StringData* newStr = pool->allocate( size );

	if ( 0 == insertPos ) {
		for (size_t i=0;i<repeatCount;i++ ) {
			newStr->strPtr[i] = ch;
		}
		StringPool::wmemcpy( &newStr->strPtr[repeatCount], dest->strPtr, dest->length );		
	}
	else if ( dest->length -1 == insertPos ) {
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, dest->length );		
		for (size_t i=0;i<repeatCount;i++ ) {
			newStr->strPtr[dest->length + i] = ch;
		}
	}
	else {		
		StringPool::wmemcpy( newStr->strPtr, dest->strPtr, insertPos );
		for (size_t i=0;i<repeatCount;i++ ) {
			newStr->strPtr[insertPos + i] = ch;
		}		
		StringPool::wmemcpy( &newStr->strPtr[insertPos+repeatCount], &dest->strPtr[insertPos], dest->length - insertPos );	
	}

	result = pool->find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {
		if ( !pool->onlyUseMemPooling_ ) {
			newStr->hashID = StringPool::hash(newStr->strPtr, newStr->length);

			pool->stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		pool->next_ -= bytesLength;
		pool->totalBytesAllocated_ -= bytesLength;

		pool->freeStringData( newStr );
	}
	

	return result;
}

StringData* StringPool::erase( StringData* src, size_t startPos, size_t length )
{
	StringData* result = NULL;

	if ( startPos > src->length ) {
		return NULL;
	}

	if ( (startPos+length) > src->length ) {
		return NULL;
	}

	if ( 0 == startPos && length >= src->length ) {
		StringPool::decStringRefcount(src);
		return NULL;
	}

	StringPool* pool = src->pool;	

	size_t size = length > src->length ? (src->length - startPos) : src->length - length;
	
	StringData* newStr = pool->allocate( size );
	
	if ( 0 == startPos ) {
		StringPool::wmemcpy( newStr->strPtr, &src->strPtr[length], newStr->length );		
	}
	else {		
		StringPool::wmemcpy( newStr->strPtr, src->strPtr, startPos );
		StringPool::wmemcpy( &newStr->strPtr[startPos], &src->strPtr[startPos + length], src->length - (startPos + length) );	
	}

	result = pool->find( newStr->strPtr, newStr->length );

	if ( NULL == result ) {
		if ( !pool->onlyUseMemPooling_ ) {
			newStr->hashID = StringPool::hash(newStr->strPtr, newStr->length);

			pool->stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		pool->next_ -= bytesLength;
		pool->totalBytesAllocated_ -= bytesLength;

		pool->freeStringData( newStr );
	}

	return result;
}

StringData* StringPool::subStr( StringData* src, size_t startPos, size_t length )
{
	StringData* result = NULL;
	StringPool* pool = src->pool;

	if ( startPos > src->length || (startPos + length) > src->length ) {
		return NULL;
	}


	if ( NULL != src->extra ) {
		if ( NULL != src->extra->nextSubstr ) {
			StringData* next = src->extra->nextSubstr;
			while ( next != NULL ) {

				if ( NULL != next->extra ) {
					if ( next->length == length && next->extra->subStrStart == startPos ) {
						return next;
					}

					next = next->extra->nextSubstr;
				}
				else {
					next = NULL;
				}
			}
		}
	}

	size_t bytesLength = sizeof(StringData);// + (length * sizeof(U16Char)) + sizeof(U16Char);
	if ((pool->next_ + bytesLength) <= pool->limit_) {
		StringData* data = (StringData*)pool->next_;

		pool->initStringData( data, NULL , length );

		data->strPtr = src->strPtr + startPos;

		data->extra = new StringExtraData();
		data->extra->subStrStart = startPos;
		data->extra->subStrEnd = startPos+length;
		data->extra->substrParent = src;
		data->bits |= StringData::SubString;

		if ( NULL == src->extra ) {
			src->extra = new StringExtraData();
		}
		src->extra->nextSubstr = data;


		pool->next_ += bytesLength;
		pool->currentHdr_->next = pool->next_;
		pool->currentHdr_->refcount ++;
		return data;
	}



	unsigned char* nextBytes = NULL;
	size_t allocSize = 0;

	if (bytesLength <= MAX_CHARALLOC) {	
		allocSize = RoundUp(bytesLength + sizeof(MemHeader), pool->granularity_);
		nextBytes = reinterpret_cast<unsigned char*>( StringPool::allocMem(allocSize) );
	}

	if (!nextBytes) {
		static std::bad_alloc outOfMemException;
		throw(outOfMemException);
	}

	pool->totalBytesAllocated_ += allocSize;
	
	pool->limit_ = reinterpret_cast<unsigned char*>(nextBytes + allocSize);
	MemHeader* currentHdr = reinterpret_cast<MemHeader*>(nextBytes);
//	currentHdr->prev = currentHdr_;
	currentHdr->size = allocSize;
	currentHdr->refcount = 0;
	

	pool->currentHdr_ = currentHdr;
	pool->next_ = reinterpret_cast<unsigned char*>(currentHdr + sizeof(U16Char));
	pool->currentHdr_->next = pool->next_;
	pool->currentHdr_->limit = pool->limit_;
	
	pool->allocatedHdrs_.push_back( pool->currentHdr_ );

	return subStr( src, startPos, length );
}


StringData* StringPool::concatenate( const std::vector<StringRange>& strArray )
{
	StringData* result = NULL;


	size_t size = 0;
	for (size_t i=0;i<strArray.size();i++ ) {
		size += strArray[i].length;
	}	
	
	StringData* newStr = allocate( size );

	U16Char* tmp = newStr->strPtr;
	for (size_t j=0;j<strArray.size();j++ ) {
		StringPool::wmemcpy( tmp, strArray[j].strPtr, strArray[j].length );		
		tmp += strArray[j].length;
	}

	result = find( newStr->strPtr, newStr->length );


	if ( NULL == result ) {
		if ( !onlyUseMemPooling_ ) {
			newStr->hashID = StringPool::hash(newStr->strPtr, newStr->length);

			stringMap_.insert(StringMapPairT(newStr->hashID,newStr));		
		}

		result = newStr;
	}
	else {
		size_t bytesLength = sizeof(StringData) + (newStr->length * sizeof(U16Char)) + sizeof(U16Char);

		//reclaim the memory, we don't need it after all, since we found an existing
		//match
		next_ -= bytesLength;
		totalBytesAllocated_ -= bytesLength;
		freeStringData( newStr );
	}


	return result;
}


std::vector<U16Char> StringLiteral::storage(StringLiteral::InitialStorageSize);


UnicodeString UnicodeString::set( size_t pos, const U16Char& ch ) const
{
	std::vector<StringRange> strings(3);	
	strings[0].strPtr = c_str();
	strings[0].length = pos;
	strings[1].strPtr = &ch;
	strings[1].length = 1;
	strings[2].strPtr = strings[0].strPtr + strings[0].length + strings[1].length;
	strings[2].length = size() - strings[0].length + strings[1].length;


	return UnicodeString( StringPool::getCurrentPool()->concatenate(strings) );
}


uint64 UnicodeString::sizeOf() const
{

	uint64 result  = sizeof(UnicodeString);

	result +=  size() * sizeof(VCFChar);

	return result;
}

void UnicodeString::decode_ansi( TextCodec* codec, AnsiChar* str, size_type& strSize, LanguageEncoding encoding ) const 
{
	VCF_ASSERT ( str != NULL );

	uint32 size = codec->convertToAnsiString( *this, str, strSize, encoding );

	if ( size < strSize ) {
		str[size] = 0;
	}

	strSize = size;
}

UnicodeString UnicodeString::decode( TextCodec* codec, LanguageEncoding encoding ) const 
{
	return codec->convertToUnicodeString( *this, encoding );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString::AnsiChar* str, size_type n, LanguageEncoding encoding )
{
	VCF_ASSERT ( str != NULL );
	*this = codec->convertToUnicodeString( str, n, encoding );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString& str, LanguageEncoding encoding )
{
	*this = codec->convertToUnicodeString( str, encoding );
}



void UnicodeString::transformAnsiToUnicode( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, 
										UnicodeString& newStr, 
										UnicodeString::LanguageEncoding encoding )
{

	newStr.assign( StringPool::getCurrentPool()->transformAnsiToUnicode( str, stringLength, encoding ) );
}


UnicodeString::AnsiChar* UnicodeString::transformUnicodeToAnsi( const UnicodeString& str, UnicodeString::LanguageEncoding encoding )
{
	
	return StringPool::getCurrentPool()->transformToAnsi( str.data_, encoding )	;
}


UnicodeString::UniChar UnicodeString::transformAnsiCharToUnicodeChar( UnicodeString::AnsiChar c, LanguageEncoding encoding )
{
	UnicodeString::UniChar result = 0;

	unsigned int sysEncoding = StringPool::getNativeEncoding( encoding ) ;

#ifdef VCF_WIN
	UINT codePage = CP_ACP;

	if ( sysEncoding != (unsigned int)-1 ) {
		codePage = sysEncoding;
	}

	int err = MultiByteToWideChar( codePage, 0, &c, 1, (LPWSTR)&result, 1 );

	if ( !(err > 0) ) {
		throw RuntimeException( L"size > 0 MultiByteToWideChar() failed" );
	}

#elif defined(VCF_OSX)
	char str[2] = {c,0};
	CFStringRef cfStr =
			CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );

	int size = CFStringGetLength( cfStr );
	if ( !(size > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
	}

	UniChar unicodeText[2];
	CFRange range = {0,2};
	CFStringGetCharacters(cfStr,range,unicodeText);
	result = unicodeText[0];
	CFRelease( cfStr );

#elif defined(VCF_POSIX)
	UnicodeString::UniChar tmp[2] = {0,0};
	mbstowcs( tmp, &c, 1 );
	result = tmp[0];
#endif

	return result;
}

UnicodeString::AnsiChar UnicodeString::transformUnicodeCharToAnsiChar( UnicodeString::UniChar c, LanguageEncoding encoding )
{
	AnsiChar result = 0;

	unsigned int sysEncoding = StringPool::getNativeEncoding( encoding ) ;

#ifdef VCF_WIN

	UINT codePage = CP_ACP;

	if ( sysEncoding != (unsigned int)-1 ) {
		codePage = sysEncoding;
	}

	if (  0 == ::WideCharToMultiByte( codePage, 0, (LPCWSTR)&c, 1,
									&result, 1, NULL, NULL ) ) {
		result = 0;
		throw RuntimeException( L"WideCharToMultiByte() failed" );
	}


#elif defined(VCF_OSX)
	String str;
	str +=c;


	CFTextString tmp;
	tmp = str;
	CFRange r = {0,tmp.length()};
	CFIndex size2 = 0;
	CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );

	if ( !(size2 > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
	}

	size2 = minVal<CFIndex>( 1, size2 );


	if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false,
									(UInt8*)&result, size2, &size2 ) ) {
		//CFStringGetBytes failed
		throw RuntimeException( L"CFStringGetBytes failed" );
		result = 0;
	}

#elif defined(VCF_POSIX)
	int size = wctomb(NULL, c);


	if ( size < 0 ) {
		throw RuntimeException( L"size < 0 wctomb() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wctomb( tmp, c ) < 0 ) {
		throw RuntimeException( L"wctomb() failed" );
		result = 0;
	}
	else {
		result = tmp[0];
	}

	delete [] tmp;

#endif
	return result;
}

int UnicodeString::adjustForBOMMarker( UnicodeString::AnsiChar*& stringPtr, uint32& len )
{
	int result = 0;

	uint32 bom = 0;
	if ( len > UnicodeString::UTF16BOMSize ) {
		bom  = ((stringPtr[0] << 8) | stringPtr[1]) & 0x0000FFFF;
		if ( UnicodeString::UTF16LittleEndianBOM == bom ) {
			stringPtr += UnicodeString::UTF16BOMSize; //skip over the BOM
			len -= UnicodeString::UTF16BOMSize;
			result = UnicodeString::UTF16LittleEndianBOM;
		}
		else {
			if ( UnicodeString::UTF16BigEndianBOM == bom ) {
				result = UnicodeString::UTF16BigEndianBOM;
				StringUtils::trace( "Unable to translate UTF16BigEndianBOM string\n" );
			}
			else {
				if ( len > UnicodeString::UTF8BOMSize ) {
					bom = 0;
					bom  = ((stringPtr[0] << 16) | (stringPtr[1] << 8) | stringPtr[0]) & 0x00FFFFFF;
					if ( UnicodeString::UTF8BOM == bom ) {
						result = UnicodeString::UTF8BOM;
						stringPtr += UnicodeString::UTF8BOMSize; //skip over the BOM
						len -= UnicodeString::UTF8BOMSize;
					}
					else {
						if ( len > UnicodeString::UTF8BOMSize ) {
							bom = 0;
							bom  = (stringPtr[0] << 24) | (stringPtr[1] << 16) | (stringPtr[2] << 8) | stringPtr[3];

							if ( (UnicodeString::UTF32LittleEndianBOM == bom) ||
									(UnicodeString::UTF32BigEndianBOM == bom) ) {
								StringUtils::trace( "Unable to translate UTF32 BOM string\n" );

								if ( UnicodeString::UTF32LittleEndianBOM == bom ) {
									result = UnicodeString::UTF32LittleEndianBOM;
								}
								else if ( UnicodeString::UTF32BigEndianBOM == bom ) {
									result = UnicodeString::UTF32BigEndianBOM;
								}
							}
						}
					}
				}
			}
		}
	}

	return result;
}




#endif //USE_STRINGPOOL





























/**
This is the original UnicodeString string implementation, that does NOT use a string pool, but is 
just a thin layer over the std::basic_string<> class.
*/
#ifndef USE_STRINGPOOL	





int UnicodeString::adjustForBOMMarker( UnicodeString::AnsiChar*& stringPtr, uint32& len )
{
	//for now only handle UTF16 Little endian - bail on anything else!
	int result = 0;

	uint32 bom = 0;
	if ( len > UnicodeString::UTF16BOMSize ) {
		bom  = ((stringPtr[0] << 8) | stringPtr[1]) & 0x0000FFFF;
		if ( UnicodeString::UTF16LittleEndianBOM == bom ) {
			stringPtr += UnicodeString::UTF16BOMSize; //skip over the BOM
			len -= UnicodeString::UTF16BOMSize;
			result = UnicodeString::UTF16LittleEndianBOM;
		}
		else {
			if ( UnicodeString::UTF16BigEndianBOM == bom ) {
				result = UnicodeString::UTF16BigEndianBOM;
				StringUtils::trace( "Unable to translate UTF16BigEndianBOM string\n" );
			}
			else {
				if ( len > UnicodeString::UTF8BOMSize ) {
					bom = 0;
					bom  = ((stringPtr[0] << 16) | (stringPtr[1] << 8) | stringPtr[0]) & 0x00FFFFFF;
					if ( UnicodeString::UTF8BOM == bom ) {
						result = UnicodeString::UTF8BOM;
						stringPtr += UnicodeString::UTF8BOMSize; //skip over the BOM
						len -= UnicodeString::UTF8BOMSize;
					}
					else {
						if ( len > UnicodeString::UTF8BOMSize ) {
							bom = 0;
							bom  = (stringPtr[0] << 24) | (stringPtr[1] << 16) | (stringPtr[2] << 8) | stringPtr[3];

							if ( (UnicodeString::UTF32LittleEndianBOM == bom) ||
									(UnicodeString::UTF32BigEndianBOM == bom) ) {
								StringUtils::trace( "Unable to translate UTF32 BOM string\n" );

								if ( UnicodeString::UTF32LittleEndianBOM == bom ) {
									result = UnicodeString::UTF32LittleEndianBOM;
								}
								else if ( UnicodeString::UTF32BigEndianBOM == bom ) {
									result = UnicodeString::UTF32BigEndianBOM;
								}
							}
						}
					}
				}
			}
		}
	}

	return result;
}

UnicodeString::UnicodeString(const std::string& rhs, LanguageEncoding encoding):
	ansiDataBuffer_(NULL)
{
	UnicodeString::transformAnsiToUnicode( rhs.c_str(), rhs.size(), data_, encoding );
}

UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string, LanguageEncoding encoding ):
	ansiDataBuffer_(NULL)
{
	if ( string != NULL ) {
		UnicodeString::transformAnsiToUnicode( string, strlen(string), data_, encoding );
	}
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string ):
	data_(string),
	ansiDataBuffer_(NULL)
{

}


UnicodeString::UnicodeString(const UnicodeString::AnsiChar* string, UnicodeString::size_type stringLength, LanguageEncoding encoding ):
	ansiDataBuffer_(NULL)
{
	UnicodeString::transformAnsiToUnicode( string, stringLength, data_, encoding );
}

UnicodeString::UnicodeString(const UnicodeString::UniChar* string, UnicodeString::size_type stringLength ):
	data_(string,stringLength),
	ansiDataBuffer_(NULL)
{
}

UnicodeString::UnicodeString( size_type n, UnicodeString::AnsiChar c, LanguageEncoding encoding ):
	data_( n, UnicodeString::transformAnsiCharToUnicodeChar(c,encoding) ),
	ansiDataBuffer_(NULL)
{

}

UnicodeString::UnicodeString( size_type n, UnicodeString::UniChar c ):
	data_(n, c),
	ansiDataBuffer_(NULL)
{

}


#ifdef VCF_OSX
UnicodeString::UnicodeString(const wchar_t* string ):
	ansiDataBuffer_(NULL)
{
	//!!!!!!!!!!!!!!!!!!MAJOR HACK ALERT!!!!!!!!!!!!!!!
	//Because *&^$%'n Apple doesn't provide wcslen we have to do this here - completely
	//*&^#$%% LAME!!!!!! :(
	int strLength = 0;
	const wchar_t* P = string;
	while ( *P != 0 ) {
		strLength ++;
		P++;

		if ( strLength >= 10000 ) { //arbitrarily stop after 10,000 characters? Lame as HELLL
			break;
		}
	}

	if ( *P == 0 ) {
		strLength ++;
	}


	int size = strLength;

	if ( !(size > 0) ) {
		throw RuntimeException( "size < 0 wcstombs() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wcstombs( tmp, string, strLength ) > 0 ) {
		tmp[size] = 0;
		UnicodeString::transformAnsiToUnicode( tmp, size, data_ );
	}

	delete [] tmp;
	tmp = NULL;
}
#endif


UnicodeString::~UnicodeString()
{
	if ( NULL != ansiDataBuffer_ ) {
		delete [] ansiDataBuffer_;
		ansiDataBuffer_ = NULL;
	}
}

unsigned int UnicodeStringGetEncoding(UnicodeString::LanguageEncoding encoding)
{
	unsigned int result = -1;
#ifdef VCF_WIN


	UnicodeString::LanguageEncoding tmp = encoding;
	if ( encoding == UnicodeString::leDefault ) {

		Locale* locale = System::getCurrentThreadLocale();
		if ( NULL != locale ) {
			tmp = locale->getEncoding();
		}
	}



	switch (tmp) {
		case UnicodeString::leIBM037: {result=037;}break;
		case UnicodeString::leIBM437: {result=437;}break;
		case UnicodeString::leIBM500: {result=500;}break;
		case UnicodeString::leArabic708: {result=708;}break;
		case UnicodeString::leArabic449: {result=709;}break;
		case UnicodeString::leArabicTransparent: {result=710;}break;
		case UnicodeString::leDOSArabic: {result=720;}break;
		case UnicodeString::leGreek: {result=737;}break;
		case UnicodeString::leBaltic: {result=775;}break;
		case UnicodeString::leLatin1: {result=850;}break;
		case UnicodeString::leLatin2: {result=852;}break;
		case UnicodeString::leCyrillic: {result=855;}break;
		case UnicodeString::leTurkish: {result=857;}break;
		case UnicodeString::leMultilingualLatin1: {result=858;}break;
		case UnicodeString::lePortuguese: {result=860;}break;
		case UnicodeString::leIcelandic: {result=861;}break;
		case UnicodeString::leHebrew: {result=862;}break;
		case UnicodeString::leFrenchCanadian: {result=863;}break;
		case UnicodeString::leArabic864: {result=864;}break;
		case UnicodeString::leNordic: {result=865;}break;
		case UnicodeString::leRussianCyrillic: {result=866;}break;
		case UnicodeString::leModernGreek: {result=869;}break;
		case UnicodeString::leEBCDICLatin2: {result=870;}break;
		case UnicodeString::leThai: {result=874;}break;
		case UnicodeString::leEBCDICGreekModern: {result=875;}break;
		case UnicodeString::leShiftJIS: {result=932;}break;
		case UnicodeString::leSimplifiedChinese: {result=936;}break;
		case UnicodeString::leKorean: {result=949;}break;
		case UnicodeString::leChineseTraditionalBig5: {result=950;}break;
		case UnicodeString::leEBCDICTurkish: {result=1026;}break;
		case UnicodeString::leEBCDICLatin1: {result=1047;}break;
		case UnicodeString::leEBCDICUSCanada: {result=1140;}break;
		case UnicodeString::leEBCDICGermany: {result=1141;}break;
		case UnicodeString::leEBCDICDenmarkNorway: {result=1142;}break;
		case UnicodeString::leEBCDICFinlandSweden: {result=1143;}break;
		case UnicodeString::leEBCDICItaly: {result=1144;}break;
		case UnicodeString::leEBCDICLatinAmericaSpain: {result=1145;}break;
		case UnicodeString::leEBCDICUnitedKingdom: {result=1146;}break;
		case UnicodeString::leEBCDICFrance: {result=1147;}break;
		case UnicodeString::leEBCDICInternational: {result=1148;}break;
		case UnicodeString::leEBCDICIcelandic: {result=1149;}break;
		case UnicodeString::leUTF16LittleEndianByteOrder: {result=1200;}break;
		case UnicodeString::leUTF16BigEndianByteOrder: {result=1201;}break;
		case UnicodeString::leANSICentralEuropean: {result=1250;}break;
		case UnicodeString::leANSICyrillic: {result=1251;}break;
		case UnicodeString::leANSILatin1: {result=1252;}break;
		case UnicodeString::leANSIGreek: {result=1253;}break;
		case UnicodeString::leANSITurkish: {result=1254;}break;
		case UnicodeString::leANSIHebrew: {result=1255;}break;
		case UnicodeString::leANSIArabic: {result=1256;}break;
		case UnicodeString::leANSIBaltic: {result=1257;}break;
		case UnicodeString::leANSIVietnamese: {result=1258;}break;
		case UnicodeString::leJohabKorean: {result=1361;}break;
		case UnicodeString::leMacRoman: {result=10000;}break;
		case UnicodeString::leMacJapanese: {result=10001;}break;
		case UnicodeString::leMacTraditionalChineseBig5: {result=10002;}break;
		case UnicodeString::leMacKorean: {result=10003;}break;
		case UnicodeString::leMacArabic: {result=10004;}break;
		case UnicodeString::leMacHebrew: {result=10005;}break;
		case UnicodeString::leMacGreek: {result=10006;}break;
		case UnicodeString::leMacCyrillic: {result=10007;}break;
		case UnicodeString::leMacSimplifiedChinese: {result=10008;}break;
		case UnicodeString::leMacRomanian: {result=10010;}break;
		case UnicodeString::leMacUkrainian: {result=10017;}break;
		case UnicodeString::leMacThai: {result=10021;}break;
		case UnicodeString::leMacLatin2: {result=10029;}break;
		case UnicodeString::leMacIcelandic: {result=10079;}break;
		case UnicodeString::leMacTurkish: {result=10081;}break;
		case UnicodeString::leMacCroatian: {result=10082;}break;
		case UnicodeString::leUTF32LittleEndianByteOrder: {result=12000;}break;
		case UnicodeString::leUTF32BigEndianByteOrder: {result=12001;}break;
		case UnicodeString::leCNSTaiwan: {result=20000;}break;
		case UnicodeString::leTCATaiwan: {result=20001;}break;
		case UnicodeString::leEtenTaiwan: {result=20002;}break;
		case UnicodeString::leIBM5550Taiwan: {result=20003;}break;
		case UnicodeString::leTeleTextTaiwan: {result=20004;}break;
		case UnicodeString::leWangTaiwan: {result=20005;}break;
		case UnicodeString::leIA5WesternEuropean: {result=20105;}break;
		case UnicodeString::leIA5German: {result=20106;}break;
		case UnicodeString::leIA5Swedish: {result=20107;}break;
		case UnicodeString::leIA5Norwegian: {result=20108;}break;
		case UnicodeString::leUSASCII: {result=20127;}break;
		case UnicodeString::leT61: {result=20261;}break;
		case UnicodeString::leISO6937: {result=20269;}break;
		case UnicodeString::leIBM273Germany: {result=20273;}break;
		case UnicodeString::leIBM277DenmarkNorway: {result=20277;}break;
		case UnicodeString::leIBM278FinlandSweden: {result=20278;}break;
		case UnicodeString::leIBM280Italy: {result=20280;}break;
		case UnicodeString::leIBM284LatinAmericaSpain: {result=20284;}break;
		case UnicodeString::leIBM285UnitedKingdom: {result=20285;}break;
		case UnicodeString::leIBM290JapaneseKatakanaExt: {result=20290;}break;
		case UnicodeString::leIBM297France: {result=20297;}break;
		case UnicodeString::leIBM420Arabic: {result=20420;}break;
		case UnicodeString::leIBM423Greek: {result=20423;}break;
		case UnicodeString::leIBM424Hebrew: {result=20424;}break;
		case UnicodeString::leIBMKoreanExtended: {result=20833;}break;
		case UnicodeString::leIBMThai: {result=20838;}break;
		case UnicodeString::leRussianKOI8R: {result=20866;}break;
		case UnicodeString::leIBM871Icelandic: {result=20871;}break;
		case UnicodeString::leIBM880CyrillicRussian: {result=20880;}break;
		case UnicodeString::leIBM905Turkish: {result=20905;}break;
		case UnicodeString::leIBM00924Latin1: {result=20924;}break;
		case UnicodeString::leEUCJapaneseJIS: {result=20932;}break;
		case UnicodeString::leSimplifiedChineseGB2312: {result=20936;}break;
		case UnicodeString::leKoreanWansung: {result=20949;}break;
		case UnicodeString::leEBCDICCyrillicSerbianBulgarian: {result=21025;}break;
		case UnicodeString::leUkrainianKOI8U: {result=21866;}break;
		case UnicodeString::leISO88591Latin1: {result=28591;}break;
		case UnicodeString::leISO88592CentralEuropean: {result=28592;}break;
		case UnicodeString::leISO88593Latin3: {result=28593;}break;
		case UnicodeString::leISO88594Baltic: {result=28594;}break;
		case UnicodeString::leISO88595Cyrillic: {result=28595;}break;
		case UnicodeString::leISO88596Arabic: {result=28596;}break;
		case UnicodeString::leISO88597Greek: {result=28597;}break;
		case UnicodeString::leISO88598HebrewVisual: {result=28598;}break;
		case UnicodeString::leISO88599Turkish: {result=28599;}break;
		case UnicodeString::leISO885913Estonian: {result=28603;}break;
		case UnicodeString::leISO885915Latin9: {result=28605;}break;
		case UnicodeString::leEuropa3: {result=29001;}break;
		case UnicodeString::leISO88598HebrewLogical: {result=38598;}break;
		case UnicodeString::leISO2022JapaneseNoHalfwidthKatakana: {result=50220;}break;
		case UnicodeString::leISO2022JapaneseWithHalfwidthKatakana: {result=50221;}break;
		case UnicodeString::leISO2022JapaneseAllow1ByteKana: {result=50222;}break;
		case UnicodeString::leISO2022Korean: {result=50225;}break;
		case UnicodeString::leISO2022SimplifiedChinese: {result=50227;}break;
		case UnicodeString::leISO2022TraditionalChinese: {result=50229;}break;
		case UnicodeString::leEBCDICJapaneseExt: {result=50930;}break;
		case UnicodeString::leEBCDICUSCanadaAndJapanese: {result=50931;}break;
		case UnicodeString::leEBCDICKoreanExtAndKorean: {result=50933;}break;
		case UnicodeString::leEBCDICSimplifiedChineseExtSimplifiedChinese: {result=50935;}break;
		case UnicodeString::leEBCDICSimplifiedChinese: {result=50936;}break;
		case UnicodeString::leEBCDICUSCanadaAndTraditionalChinese: {result=50937;}break;
		case UnicodeString::leEBCDICJapaneseLatinExtAndJapanese: {result=50939;}break;
		case UnicodeString::leEUCJapanese: {result=51932;}break;
		case UnicodeString::leEUCSimplifiedChinese: {result=51936;}break;
		case UnicodeString::leEUCKorean: {result=51949;}break;
		case UnicodeString::leEUCTraditionalChinese: {result=51950;}break;
		case UnicodeString::leHZGB2312SimplifiedChinese: {result=52936;}break;
		case UnicodeString::leGB18030SimplifiedChinese: {result=54936;}break;
		case UnicodeString::leISCIIDevanagari: {result=57002;}break;
		case UnicodeString::leISCIIBengali: {result=57003;}break;
		case UnicodeString::leISCIITamil: {result=57004;}break;
		case UnicodeString::leISCIITelugu: {result=57005;}break;
		case UnicodeString::leISCIIAssamese: {result=57006;}break;
		case UnicodeString::leISCIIOriya: {result=57007;}break;
		case UnicodeString::leISCIIKannada: {result=57008;}break;
		case UnicodeString::leISCIIMalayalam: {result=57009;}break;
		case UnicodeString::leISCIIGujarati: {result=57010;}break;
		case UnicodeString::leISCIIPunjabi: {result=57011;}break;
		case UnicodeString::leUTF7: {result=65000;}break;
		case UnicodeString::leUTF8: {result=65001;}break;
		case UnicodeString::leDefault: {}break;
		case UnicodeString::leUnknown: {}break;
	}

#endif
	return result;
}

void UnicodeString::transformAnsiToUnicode( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, UnicodeString::StringData& newStr, LanguageEncoding encoding )
{
	if ( stringLength == 0 ) {
		newStr = newStr.erase(0,newStr.size());
	}
	else {

		unsigned int sysEncoding = UnicodeStringGetEncoding(encoding);

	#ifdef VCF_WIN

		/***
		What code page do we want to use here???? CP_ACP may not be the
		most appropriate one to use. First UnicodeString::let's try and examine the
		current locale
		*/

		UINT codePage = CP_ACP;

		if ( sysEncoding != (unsigned int)-1 ) {
			codePage = sysEncoding;
		}

		int size = MultiByteToWideChar( codePage, 0, str, stringLength, NULL, 0 );

		if ( !(size > 0) ) {
			throw RuntimeException( L"size > 0 MultiByteToWideChar() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* tmp = new UniChar[size];


		int err = MultiByteToWideChar( codePage, 0, str, stringLength, (LPWSTR)tmp, size );
		if ( 0 == err ) {
			err = GetLastError();
		}

		newStr.assign( tmp, size );

		delete [] tmp;

	#elif defined(VCF_OSX)
		CFStringRef cfStr =
		CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );

		int size = CFStringGetLength( cfStr );
		if ( !(size > 0) ) {
			throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* unicodeText = new UniChar[size+1];
		CFRange range = {0,size};
		CFStringGetCharacters(cfStr,range,unicodeText);
		unicodeText[size] = 0;
		newStr.assign( unicodeText, size );
		delete [] unicodeText;
		CFRelease( cfStr );

	#elif defined(VCF_POSIX)
		int size = mbstowcs (NULL, str, 0 );
		if ( size < 0) {
			throw RuntimeException( L"size < 0 mbstowcs() failed in UnicodeString::transformAnsiToUnicode()" );
		}

		UniChar* tmp = new UniChar[size+1];

		int err = mbstowcs( tmp, str, size );
		if ( err > 0 ) {
			newStr.assign( tmp, size );
		}

		delete [] tmp;

	#endif
	}
}

UnicodeString::UniChar UnicodeString::transformAnsiCharToUnicodeChar( UnicodeString::AnsiChar c, LanguageEncoding encoding )
{
	UnicodeString::UniChar result = 0;

	unsigned int sysEncoding = UnicodeStringGetEncoding(encoding);

#ifdef VCF_WIN
	UINT codePage = CP_ACP;

	if ( sysEncoding != (unsigned int)-1 ) {
		codePage = sysEncoding;
	}

	int err = MultiByteToWideChar( codePage, 0, &c, 1, (LPWSTR)&result, 1 );

	if ( !(err > 0) ) {
		throw RuntimeException( L"size > 0 MultiByteToWideChar() failed" );
	}

#elif defined(VCF_OSX)
	char str[2] = {c,0};
	CFStringRef cfStr =
			CFStringCreateWithCString( NULL, str, CFStringGetSystemEncoding() );

	int size = CFStringGetLength( cfStr );
	if ( !(size > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringCreateWithCString() failed in UnicodeString::transformAnsiToUnicode()" );
	}

	UniChar unicodeText[2];
	CFRange range = {0,2};
	CFStringGetCharacters(cfStr,range,unicodeText);
	result = unicodeText[0];
	CFRelease( cfStr );

#elif defined(VCF_POSIX)
	UnicodeString::UniChar tmp[2] = {0,0};
	mbstowcs( tmp, &c, 1 );
	result = tmp[0];
#endif

	return result;
}

UnicodeString::AnsiChar UnicodeString::transformUnicodeCharToAnsiChar( UnicodeString::UniChar c, LanguageEncoding encoding )
{
	AnsiChar result;

	unsigned int sysEncoding = UnicodeStringGetEncoding(encoding);

#ifdef VCF_WIN

	UINT codePage = CP_ACP;

	if ( sysEncoding != (unsigned int)-1 ) {
		codePage = sysEncoding;
	}

	if (  0 == ::WideCharToMultiByte( codePage, 0, (LPCWSTR)&c, 1,
									&result, 1, NULL, NULL ) ) {
		result = 0;
		throw RuntimeException( L"WideCharToMultiByte() failed" );
	}


#elif defined(VCF_OSX)
	String str;
	str +=c;


	CFTextString tmp;
	tmp = str;
	CFRange r = {0,tmp.length()};
	CFIndex size2 = 0;
	CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );

	if ( !(size2 > 0) ) {
		throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
	}

	size2 = minVal<CFIndex>( 1, size2 );


	if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false,
									(UInt8*)&result, size2, &size2 ) ) {
		//CFStringGetBytes failed
		throw RuntimeException( L"CFStringGetBytes failed" );
		result = 0;
	}

#elif defined(VCF_POSIX)
	int size = wctomb(NULL, c);


	if ( size < 0 ) {
		throw RuntimeException( L"size < 0 wctomb() failed" );
	}

	UnicodeString::AnsiChar* tmp = new UnicodeString::AnsiChar[size+1];

	if ( wctomb( tmp, c ) < 0 ) {
		throw RuntimeException( L"wctomb() failed" );
		result = 0;
	}
	else {
		result = tmp[0];
	}

	delete [] tmp;

#endif
	return result;
}

UnicodeString::AnsiChar* UnicodeString::transformUnicodeToAnsi( const UnicodeString& str, LanguageEncoding encoding )
{
	UnicodeString::AnsiChar* result= NULL;
	int size = 0;


	unsigned int sysEncoding = UnicodeStringGetEncoding(encoding);

#ifdef VCF_WIN
	UINT codePage = CP_ACP;

	if ( sysEncoding != (unsigned int)-1 ) {
		codePage = sysEncoding;
	}

    int strLength = str.data_.size();
	if ( str.empty() ) {
		strLength = 1;
	}

	size = ::WideCharToMultiByte( codePage, 0, (LPCWSTR)str.data_.c_str(), strLength,
							NULL, 0, NULL, NULL );

	if ( !(size > 0) ) {
		throw RuntimeException( L"size > 0 WideCharToMultiByte() failed" );
	}

	result = new UnicodeString::AnsiChar[size+1];

	if (  0 == ::WideCharToMultiByte( codePage, 0, (LPCWSTR)str.data_.c_str(), strLength,
									result, size, NULL, NULL ) ) {
		//WideCharToMultiByte failed
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}

#elif defined(VCF_OSX)
	if ( str.length() > 0 ) {
		CFTextString tmp;
		tmp = str;
		CFRange r = {0,tmp.length()};
		CFIndex size2 = 0;
		CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false, NULL, 0, &size2 );

		if ( !(size2 > 0) ) {
			throw RuntimeException( L"size <= 0 CFStringGetBytes() failed" );
		}

		result = new UnicodeString::AnsiChar[size2+1];

		if (  0 == ::CFStringGetBytes( tmp, r, CFStringGetSystemEncoding(), '?', false,
										(UInt8*)result, size2, &size2 ) ) {
			//CFStringGetBytes failed
			delete [] result;
			result = NULL;
		}
		else {
			result[size2] = 0;
		}
	}

#elif defined(VCF_POSIX)
	size = wcstombs( NULL, str.data_.c_str(), 0 );

	if ( size < 0 ) {
        // It is not possible to convert the string at once.
        mbstate_t mbs;
        memset(&mbs, 0, sizeof(mbs));
        char mbstr[64];
        size_t mbslen;
        const wchar_t *wcsPtr = str.data_.c_str();
        std::string strRes;
        while(wcsPtr != NULL) {
            memset(mbstr, 0, sizeof(mbstr));
            mbslen = wcsrtombs(mbstr, &wcsPtr, sizeof(mbstr)-1, &mbs);
            if(mbslen == (size_t)-1) {
                if(errno == EILSEQ) {
                    // Conversion failed. Convert to ? instead.
                    strRes += mbstr;
                    strRes += "?";
                    wcsPtr++;
                }
            }
            else
            {
                strRes += mbstr;
            }
        }
        result = new UnicodeString::AnsiChar[strRes.length()+1];
        memset(result, 0, strRes.length()+1);
        strncpy(result, strRes.c_str(), strRes.length());
        return result;
	}

	result = new UnicodeString::AnsiChar[size+1];

	if ( wcstombs( result, str.data_.c_str(), size ) < 0 ) {
		delete [] result;
		result = NULL;
	}
	else {
		result[size] = 0;
	}

#endif

	return result;
}

void UnicodeString::decode_ansi( TextCodec* codec, UnicodeString::AnsiChar* str, UnicodeString::size_type& strSize, LanguageEncoding encoding ) const
{
	VCF_ASSERT ( str != NULL );

	uint32 size = codec->convertToAnsiString( *this, str, strSize, encoding );

	if ( size < strSize ) {
		str[size] = 0;
	}

	strSize = size;
}

UnicodeString UnicodeString::decode( TextCodec* codec, LanguageEncoding encoding ) const
{
	return codec->convertToUnicodeString( *this, encoding );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString::AnsiChar* str, UnicodeString::size_type n, LanguageEncoding encoding )
{
	VCF_ASSERT ( str != NULL );
	*this = codec->convertToUnicodeString( str, n, encoding );
	modified();
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString& str, LanguageEncoding encoding )
{
	*this = codec->convertToUnicodeString( str, encoding );
	modified();
}


bool UnicodeString::operator ==( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ == tmp.data_;
}

bool UnicodeString::operator !=( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ != tmp.data_;
}

bool UnicodeString::operator >( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ > tmp.data_;
}

bool UnicodeString::operator >=( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ >= tmp.data_;
}

bool UnicodeString::operator <( const UnicodeString::AnsiChar* rhs ) const
{
	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ < tmp.data_;
}

bool UnicodeString::operator <=( const UnicodeString::AnsiChar* rhs ) const
{

	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
	}
	return data_ <= tmp.data_;
}


UnicodeString& UnicodeString::operator=(const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );

	if ( s != NULL ) {
		UnicodeString::transformAnsiToUnicode( s, strlen(s), data_ );
		modified();
	}

	return *this;
}

UnicodeString& UnicodeString::operator=(UnicodeString::AnsiChar c)
{
	data_ = UnicodeString::transformAnsiCharToUnicodeChar( c  );
	modified();
	return *this;
}

const UnicodeString::AnsiChar* UnicodeString::ansi_c_str(LanguageEncoding encoding) const
{
	if ( NULL == ansiDataBuffer_  ) {
		ansiDataBuffer_ = UnicodeString::transformUnicodeToAnsi( *this, encoding );
	}

	return ansiDataBuffer_;
}

UnicodeString& UnicodeString::operator+=(UnicodeString::AnsiChar c)
{
	data_ += UnicodeString::transformAnsiCharToUnicodeChar( c  );
	modified();
	return *this;
}

UnicodeString& UnicodeString::operator+=(const AnsiChar* rhs )
{


	UnicodeString tmp;
	if ( rhs != NULL ) {
		UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );
		data_ += tmp.data_;
		modified();
	}

	return *this;
}

/*
UnicodeString UnicodeString::operator+( const AnsiChar& rhs )
{
	UnicodeString result;
	result = data_ + UnicodeString::transformAnsiCharToUnicodeChar( c  );
	return result;
}

UnicodeString UnicodeString::operator+( const AnsiChar* rhs )
{
	UnicodeString result;
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( rhs, strlen(rhs), tmp.data_ );

	result = data_ + tmp;
	return result;
}
*/

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.append( tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::append(const UnicodeString::AnsiChar *s)
{
	if ( s != NULL ) {
		UnicodeString tmp;
		UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
		data_.append( tmp.data_ );
		modified();
	}

	return *this;
}

UnicodeString& UnicodeString::append( size_type n, UnicodeString::AnsiChar c)
{
	data_.append( n, UnicodeString::transformAnsiCharToUnicodeChar( c  ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	data_.assign( tmp.data_ );
	modified();
	return *this;
}

UnicodeString& UnicodeString::assign(const UnicodeString::AnsiChar *s)
{
	UnicodeString tmp;
	if ( s != NULL ) {
		UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	}
	data_.assign( tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::assign( size_type n, UnicodeString::AnsiChar c)
{
	data_.assign( n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	UnicodeString tmp;
	if ( s != NULL ) {
		UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );
	}
	data_.insert( p0, tmp.data_ );
	modified();
	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, const UnicodeString::AnsiChar *s)
{

	UnicodeString tmp;
	if ( s != NULL ) {
		UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );
	}
	data_.insert( p0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::insert(UnicodeString::size_type p0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( p0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString::iterator UnicodeString::insert(UnicodeString::iterator it, UnicodeString::AnsiChar c)
{
	data_.insert( it, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return begin();
}

void UnicodeString::insert(UnicodeString::iterator it, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.insert( it, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( p0, n0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::size_type p0, UnicodeString::size_type n0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.replace( p0, n0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s, UnicodeString::size_type n)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, const UnicodeString::AnsiChar *s)
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	data_.replace( first0, last0, tmp.data_ );
	modified();

	return *this;
}

UnicodeString& UnicodeString::replace(UnicodeString::iterator first0, UnicodeString::iterator last0, UnicodeString::size_type n, UnicodeString::AnsiChar c)
{
	data_.replace( first0, last0, n, UnicodeString::transformAnsiCharToUnicodeChar( c ) );
	modified();

	return *this;
}

UnicodeString::size_type UnicodeString::copy(UnicodeString::AnsiChar *s, UnicodeString::size_type n, UnicodeString::size_type pos) const
{
	VCF_ASSERT ( s != NULL );
/*
JC this is commented out to make the copy code simpler here.
We translate to a AnsiString, adn then call the copy() method on that
and return the result
	UnicodeString::AnsiChar* copyStr = UnicodeString::transformUnicodeToAnsi( *this );

	UnicodeString::size_type result = minVal<UnicodeString::size_type>( strlen(copyStr+pos), n );

	memcpy( s, copyStr+pos, result );


	delete [] copyStr;

	return result;
*/

	AnsiString copyStr = *this;


	return copyStr.copy( s, n, pos );

}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.rfind( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::rfind(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.rfind( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_first_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_first_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_first_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos, UnicodeString::size_type n) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, n, tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(const UnicodeString::AnsiChar *s, UnicodeString::size_type pos ) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.find_last_not_of( tmp.data_, pos ) ;
}

UnicodeString::size_type UnicodeString::find_last_not_of(UnicodeString::AnsiChar c, UnicodeString::size_type pos ) const
{
	return data_.find_last_not_of( UnicodeString::transformAnsiCharToUnicodeChar( c ), pos ) ;
}

int UnicodeString::compare(const UnicodeString::AnsiChar *s) const
{
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s, strlen(s), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}

int UnicodeString::compare(UnicodeString::size_type p0, UnicodeString::size_type n0, const UnicodeString::AnsiChar *s, UnicodeString::size_type pos) const
{
	VCF_ASSERT ( s != NULL );
	UnicodeString tmp;
	UnicodeString::transformAnsiToUnicode( s+pos, strlen(s+pos), tmp.data_ );

	return data_.compare( p0, n0, tmp.data_ ) ;
}

uint64 UnicodeString::sizeOf() const
{
	uint64 result  = sizeof(UnicodeString);

	result +=  data_.capacity() * sizeof(VCFChar);

	return result;
}

#endif //#ifdef FOOBAR

};


/**
$Id$
*/
