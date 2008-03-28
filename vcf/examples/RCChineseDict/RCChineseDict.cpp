////RCChineseDict.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/StringTokenizer.h"

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



struct DictionaryEntry {
	bool Parse(const String& line);
	String trad;
	String simp;
	String pinyin;
	String english;
};

bool DictionaryEntry::Parse(const String& line)
{
    size_t start = 0;
    size_t end = line.find(L' ', start);

    if (end == String::npos) return false;

    trad.assign(line, start, end);

    start = line.find(L'[', end);

    if (start == String::npos) return false;

    end = line.find(L']', ++start);

    if (end == String::npos) return false;

    pinyin.assign(line, start, end - start);
    start = line.find(L'/', end);
    if (start == String::npos) return false;

    start++;
    end = line.rfind(L'/');
    if (end == String::npos) return false;

    if (end <= start) return false;
    english.assign(line, start, end-start);

    return true;
}

class LangDictionary
{
public:
	LangDictionary();
	int Length() { 
		return v.size(); 
	}

	const DictionaryEntry& Item(int i) { 
		return v[i]; 
	}

private:
	std::vector<DictionaryEntry> v;
};


LangDictionary::LangDictionary()
{
	FileInputStream fs("cedict.b5");
	
	unsigned char* data = new unsigned char[ fs.getSize() ];

	fs.read( data, fs.getSize() );

	String chStr((const char*)data,fs.getSize(),UnicodeString::leChineseTraditionalBig5);

	delete [] data;


	StringTokenizer tok(chStr,"\r\n");
	/*
	std::vector<String> lines;
	tok.getElements(lines);
	std::vector<String>::iterator it = lines.begin();
	while ( it != lines.end() ) {
		const String& s = *it;
		if (s.length() > 0 && s[0] != L'#') {
			DictionaryEntry de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}
		++it;
	}
	*/
	while ( tok.hasMoreElements() ) {
		String s = tok.nextElement();
		if (s.length() > 0 && s[0] != L'#') {
			DictionaryEntry de;
			if (de.Parse(s)) {
				v.push_back(de);
			}
		}
	}	
}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	HiResClock clock;
	clock.start();
	LangDictionary dict;
	clock.stop();

	System::println( Format("Took %0.8f seconds or %0.4f milliseconds") % clock.duration() % (clock.duration()*1000.0) );


	

	FoundationKit::terminate();
	return 0;
}


