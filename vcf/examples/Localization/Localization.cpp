//Localization.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

#include "vcf/FoundationKit/DateTime.h"
#include "vcf/FoundationKit/TextCodec.h"
#include "vcf/FoundationKit/LocalePeer.h"





/**
This is a simple wrapper around the Win32 QueryPerformanceCounter API
to allow hi resolution timing
*/
#ifdef VCF_WIN32
class HiResClock {
public:

	HiResClock(){
		QueryPerformanceFrequency( &frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}



	void start() {
		QueryPerformanceCounter( &performanceCounter1_ );
	}

	void stop() {
		QueryPerformanceCounter( &performanceCounter2_ );
	}

	void clear() {
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return (double)(performanceCounter2_.LowPart - performanceCounter1_.LowPart)/(double)frequency_.LowPart;
	}
protected:
	LARGE_INTEGER frequency_;
	LARGE_INTEGER performanceCounter1_;
	LARGE_INTEGER performanceCounter2_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};
#elif defined (VCF_OSX)
#include <Carbon/Carbon.h>

class HiResClock {
public:

	HiResClock():t1_(0),t2_(0){}

	void start() {
		t1_ = CFAbsoluteTimeGetCurrent();
	}

	void stop() {
		t2_ = CFAbsoluteTimeGetCurrent();
	}

	void clear() {
		t1_ = t2_ = 0;
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return t2_ - t1_;
	}

private:
	CFAbsoluteTime t1_;
	CFAbsoluteTime t2_;
	HiResClock( const HiResClock& rhs );
	HiResClock& operator=( const HiResClock& rhs );
};
#else
//do nothing for now on other platforms
class HiResClock {
public:

	HiResClock(){}

	void start() {
		
	}

	void stop() {
		
	}

	void clear() {
		
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return 0.0;
	}

private:
	HiResClock( const HiResClock& rhs );
	HiResClock& operator=( const HiResClock& rhs );
};
#endif










using namespace VCF;



/**
This class demonstrates how to write your own text codec
*/
class MyTextCodec : public VCF::TextCodec {
public:
	//values from Mike Lischke pascal Unicode functions
	//at http://www.delphi-unicode.net/
	//Thanks Mike !
	enum {
		Null				= 0,
		Tab					= 9,
		Space				= 32,
		LineFeed			= 10,
		VerticalTab			= 11,
		FormFeed			= 12,
		CarriageReturn		= 13,
		LineSeparator		= 0x2028,
		ParagraphSeparator	= 0x2029
	};

	//values from Mike Lischke pascal Unicode functions
	//at http://www.delphi-unicode.net/
	//Thanks Mike !
	enum ByteOrderMarks {
		BOM_LSB_FIRST = 0xFEFF,
		BOM_MSB_FIRST = 0xFFFE
	};

	enum UnicodeType {
		UTF7 = 0,
		UTF8,
		UTF16,
		UTF32
	};

	enum UnicodeLimits{
		ReplacementCharacter	= 0x0000FFFD,
		MaximumUCS2				= 0x0000FFFF,
		MaximumUTF16			= 0x0010FFFF,
		MaximumUCS4				= 0x7FFFFFFF
	};


	enum  {
		halfShift			= 10,
		halfBase			= 0x0010000,
		halfMask			= 0x3FF,
		SurrogateHighStart	= 0xD800,
		SurrogateHighEnd	= 0xDBFF,
		SurrogateLowStart	= 0xDC00,
		SurrogateLowEnd		= 0xDFFF
	};



	/**
	These are the 4 methods you have to implement
	*/

	virtual ulong32 convertToAnsiString( const UnicodeString& str, UnicodeString::AnsiChar* ansiStrBuffer,
										const ulong32& ansiStrBufferLength );

	virtual UnicodeString::AnsiChar convertToAnsiChar( const UnicodeString::UniChar& c );

	virtual UnicodeString convertToUnicodeString( const UnicodeString& str );

	virtual UnicodeString convertToUnicodeString( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength );

	/**
	You need to return a name, which needs to be unique, for your codec
	*/
	virtual String getName() {
		return "MyTextCodec";
	}

protected:
	static unsigned long offsetsFromUTF8[6];
	static unsigned char firstByteMark[7];
	static unsigned char bytesFromUTF8[256];
};


unsigned char MyTextCodec::firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
unsigned char MyTextCodec::bytesFromUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5 };

unsigned long MyTextCodec::offsetsFromUTF8[6] = {0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080};


ulong32 MyTextCodec::convertToAnsiString( const UnicodeString& str, UnicodeString::AnsiChar* ansiStrBuffer,
									const ulong32& ansiStrBufferLength )
{
	long ch;
	short T = 0;
	short bytesToWrite = 0;
	long byteMask = 0;
	long byteMark = 0;

	long length =  str.size();
	if ( ansiStrBufferLength > 0 ) {
		length = minVal<long>( ansiStrBufferLength, length );
	}

	if ( 0 == length ){
		return 0;
	}


	const UnicodeString::UniChar* unicodeStr = str.c_str();

	long strLength = 0;

	T = 0;
	for ( int J=0;J<length;J++) {
		byteMask = 0xBF;
		byteMark = 0x80;

		ch = (long)unicodeStr[J];

		if ( ch < 0x80 ) {
			bytesToWrite = 1;
		}
		else if ( ch < 0x800 ) {
			bytesToWrite = 2;
		}
		else if ( ch < 0x10000 ) {
			bytesToWrite = 3;
		}
		else if ( ch < 0x200000 ) {
			bytesToWrite = 4;
		}
		else if ( ch < 0x4000000 ) {
			bytesToWrite = 5;
		}
		else if ( ch <= MaximumUCS4 ) {
			bytesToWrite = 6;
		}
		else {
			bytesToWrite = 2;
			ch = ReplacementCharacter;
		}

		for ( int L=bytesToWrite; L>2;L--) {
			if ( ansiStrBufferLength > 0 ) {
				ansiStrBuffer[T + L - 1] = (UnicodeString::AnsiChar)((ch | byteMark) & byteMask);
			}

			strLength ++;

			ch = ch >> 6;
		}
		strLength ++;

		if ( ansiStrBufferLength > 0 ) {
			ansiStrBuffer[T] = (UnicodeString::AnsiChar)(ch | MyTextCodec::firstByteMark[bytesToWrite]);
		}

		T += bytesToWrite;
	}

	if ( 0 == ansiStrBufferLength ) {
		strLength ++; //account for null terminator
	}
	else {
		ansiStrBuffer[strLength] = 0;
	}

	return strLength;
}

UnicodeString::AnsiChar MyTextCodec::convertToAnsiChar( const UnicodeString::UniChar& c )
{
	UnicodeString::AnsiChar result = 0;

	return result;
}

UnicodeString MyTextCodec::convertToUnicodeString( const UnicodeString& str )
{
	UnicodeString result(str);

	return result;
}

UnicodeString MyTextCodec::convertToUnicodeString( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength )
{
	UnicodeString result(str,stringLength);

	return result;
}






void testTime( const String& testName, const HiResClock& clock )
{
	printf( "Test \"%s\" took %.8f seconds\n", testName.ansi_c_str(), clock.duration() );
}







void testLocale( Locale& loc )
{
	System::println( "*******************************************************************************" );

	UnicodeString name = loc.getName();
	UnicodeString lc = loc.getLanguageCodeString();
	UnicodeString cc = loc.getCountryCodeString();
	UnicodeString lang = loc.getLanguageName();
	System::println( Format("Testing Locale %s. Lang code: %s, country code: %s, lang name: %s") %
			name % lc % cc % lang );

	System::println( "-------------------------------------------------------------------------------\n" );

	System::println( "loc.getCurrencyDecimalPoint(): " + loc.getCurrencyDecimalPoint() );
	System::println( "loc.getCurrencyFractionalDigits(): " + loc.getCurrencyFractionalDigits() );
	System::println( "loc.getCurrencyNegativeSign(): " + loc.getCurrencyNegativeSign() );
	System::println( "loc.getCurrencyPositiveSign(): " + loc.getCurrencyPositiveSign() );
	
	System::println( "loc.getCurrencySymbol(): " + loc.getCurrencySymbol() );
	System::println( "loc.getCurrencyThousandsSeparator(): " + loc.getCurrencyThousandsSeparator() );
	System::println( "loc.getNumberDecimalPoint(): " + loc.getNumberDecimalPoint() );
	System::println( "loc.getNumberGrouping(): " + loc.getNumberGrouping() );


	System::println( "loc.toStringFromCurrency(2343239685.4554): " + loc.toStringFromCurrency(2343239685.4554) );
		//loc.toStringFromCurrency(2343239685.4554) );

	System::println( "loc.toString(2340545.4554): " + loc.toString(2340545.4554) );
	System::println( "loc.toString(23993023): " + loc.toString(23993023) );


	UnicodeString s2 = "klsdfLKJDKLSJ Dlksjdflsdkf lKJP(RWIUWOR_(%$_09-09-";

	System::println( Format("%s\nafter lower case: \n%s") %	s2 % loc.toLowerCase( s2 ) );

	System::println( Format("%s\nafter UPPER case: \n%s") % s2 % loc.toUpperCase( s2 ) );


	UnicodeString s3 = loc.toString(23993023);
	System::println( Format("loc.toString(23993023) = %s\n after loc.toInt() = %d") % s3 % loc.toInt( s3 ) );

	s3 = loc.toString(23993023.000);
	System::println( Format("loc.toString(23993023.000) = %s\n after loc.toFloat() = %f") %	s3 % loc.toFloat( s3 ) );


	loc.isCharA( ctUpper, 'u' );

	DateTime now = DateTime::now();

	System::println( "loc.toStringFromDate(): " + loc.toStringFromDate(now,"") );
	System::println( "loc.toStringFromDate(\"dddd, MMM d yyyy\"): " + loc.toStringFromDate(now,"dddd, MMM d yyyy") );
	System::println( "loc.toStringFromTime(): " + loc.toStringFromTime(now,"") );

	System::println( "\n*******************************************************************************\n\n\n" );
	
}



















int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	/**
	register your custom codec
	*/
	VCF::TextCodec::registerCodec( new MyTextCodec() );

	/**
	This sections tests out a variety of locales
	*/

	{
		//test a locale identified by string codes for language and country
		Locale loc( "en", "US" );
		testLocale( loc );
	}

	{
		//test a locale by using the LanguageCodes and CountryCodes enums
		Locale loc( Locale::lcEnglish, Locale::ccUnitedKingdom );
		testLocale( loc );
	}

	{
		Locale loc( Locale::lcItalian, Locale::ccItaly );
		testLocale( loc );
	}


	{
		Locale loc( Locale::lcJapanese, Locale::ccJapan );
		testLocale( loc );
	}

	{
		Locale loc( Locale::lcPortuguese, Locale::ccBrazil );
		testLocale( loc );
	}

	{
		Locale loc( "de", "DE" );
		testLocale( loc );
	}

	{
		Locale loc( Locale::lcPolish, Locale::ccPoland );
		testLocale( loc );
	}


	{
		//these are some silly tests tha demonstrate using a VCF::UnicodeString class
		UnicodeString s;

		UnicodeString s1("alsdjkasdjklasd");

		const char* ptr = s1.ansi_c_str();
		printf( "ptr: %s\n", ptr );

		wprintf( L"ptr (as wchar_t): %s\n", UnicodeString(ptr).c_str() );


		/**
		This demonstrates using a TextCodec instance to transform a string
		from one form (ansi) to another (UTF16)
		*/
		UnicodeString s2;
		s2 = "Hello";
		
		char s2_ansi[256];
		size_t len = sizeof(s2_ansi);
		s2.decode_ansi( TextCodec::getCodec( "MyTextCodec" ), s2_ansi, len );

		printf( "s2_ansi: %s, len: %d\n", s2_ansi, len );
	}


	//test out transforming a country code enum to a 2 character string.
	UnicodeString cc = Locale::countryCodeToString( Locale::ccPanama );

	//test out transforming a language code enum to a 2 character string.
	cc = Locale::languageCodeToString( Locale::lcBengali );

	//test out transforming a string to a langauge code for a locale
	Locale::LanguageCodes lc = Locale::stringToLanguageCode( cc );
	Locale::CountryCodes ccs = Locale::stringToCountryCode( Locale::countryCodeToString( Locale::ccUnitedKingdom ) );


	/**
	Translation support !
	*/
	try {

		{
			Locale loc(Locale::lcFrench, Locale::ccFrance );

			printf( "loc[%s].translate( \"Hello\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "Hello" ).ansi_c_str() );
			printf( "loc[%s].translate( \"I understand\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "I understand" ).ansi_c_str() );
		}


		{
			Locale loc(Locale::lcItalian, Locale::ccItaly );

			printf( "loc[%s].translate( \"Hello\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "Hello" ).ansi_c_str() );
			printf( "loc[%s].translate( \"I understand\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "I understand" ).ansi_c_str() );
		}


		{
			Locale loc(Locale::lcPolish, Locale::ccPoland );

			printf( "loc[%s].translate( \"Hello\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "Hello" ).ansi_c_str() );
			printf( "loc[%s].translate( \"I understand\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "I understand" ).ansi_c_str() );
		}


		{
			Locale loc(Locale::lcSpanish, Locale::ccSpain );

			printf( "loc[%s].translate( \"Hello\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "Hello" ).ansi_c_str() );
			printf( "loc[%s].translate( \"I understand\" ) = %s\n", loc.getName().ansi_c_str(), loc.translate( "I understand" ).ansi_c_str() );
		}

	}
	catch ( std::exception& e ) {
		printf( "Exception: %s\n", e.what() );
	}



	HiResClock clock;

	int count = 1000;

	/**
	The following tests demonstrate the performance of the STL's string class
	vs. the performance of the VCF's new UnicodeString class (which is simply a class
	with an identical interface to std::basic_string<> and that wraps a basic_string<wchar_t>
	data member.
	*/
	//test 1
	{
		clock.start();
		UnicodeString s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( ( Format("Test 1 - UnicodeString assignment, %d times" ) % count ), clock );
	}

	//test 2
	{
		clock.start();

		for ( int i=0;i<count;i++ ) {
			UnicodeString s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( ( Format("Test 2 - new UnicodeString instance assignment, %d times" ) % count ), clock );
	}

	//test 3
	{
		clock.start();
		std::string s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( ( Format("Test 3 - std::string assignment, %d times" ) % count ), clock );
	}

	//test 4
	{
		clock.start();

		for ( int i=0;i<count;i++ ) {
			std::string s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( ( Format("Test 4 - new std::string instance assignment, %d times" ) % count ), clock );
	}


	count = 100000;
	//test 5
	{
		clock.start();
		UnicodeString s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 5 - UnicodeString assignment, %d times" ) % count ), clock );
	}

	//test 6
	{
		clock.start();

		for ( int i=0;i<count;i++ ) {
			UnicodeString s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 6 - new UnicodeString instance assignment, %d times" ) % count ), clock );
	}

	//test 7
	{
		clock.start();
		std::string s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 7 - std::string assignment, %d times" ) % count ), clock );
	}

	//test 8
	{
		clock.start();

		for ( int i=0;i<count;i++ ) {
			std::string s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 8 - new std::string instance assignment, %d times" ) % count ), clock );
	}




	//count = 10000000;
	count = 1;
	//test 9
	{
		clock.start();
		UnicodeString s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 9 - UnicodeString assignment, %d times" ) % count ), clock );
	}

	//test 10
	{
		clock.start();
		std::string s;
		for ( int i=0;i<count;i++ ) {
			s = "Some text: MySQL 3.23.54 running on mysql.sourceforge.net as vcf@sc8-pr-web3-b.sourceforge.net";
		}

		clock.stop();

		testTime( (Format("Test 10 - std::string assignment, %d times" ) % count ), clock );
	}

#define A_REALLY_LONG_STRING	"Developing globalized software is a continuous balancing act as software "\
	"developers and project managers inadvertently underestimate the level of effort and detail required "\
	"to create foreign-language software releases.Software developers must understand the ICU services to "\
	"design and deploy successful software releases. The services can save ICU users time in dealing with "\
	"the kinds of problems that typically arise during critical stages of the software life cycle.In "\
	"general, the standard process for creating globalized software includes 'internationalization,' "\
	"which covers generic coding and design issues, and 'localization,' which involves translating and "\
	"customizing a product for a specific market.Software developers must understand the intricacies of "\
	"internationalization since they write the actual underlying code. How well they use established "\
	"services to achieve mission objectives determines the overall success of the project. At a fundamental "\
	"level, code and feature design affect how a product is translated and customized. Therefore, software "\
	"developers need to understand key localization concepts.From a geographic perspective, a locale is a "\
	"place. From a software perspective, a locale is an ID used to select information associated with a a "\
	"language and/or a place. ICU locale information includes the name and identifier of the spoken language, "\
	"sorting and collating requirements, currency usage, numeric display preferences, and text direction "\
	"(left-to-right or right-to-left, horizontal or vertical).General locale-sensitive standards include "\
	"keyboard layouts, default paper and envelope sizes, common printers and monitor resolutions, character "\
	"sets or encoding ranges, and input methods."

	int length = UnicodeString(A_REALLY_LONG_STRING).size();
	count = 1000;
	//test 11
	{
		clock.start();
		UnicodeString s;
		for ( int i=0;i<count;i++ ) {
			s = A_REALLY_LONG_STRING;
		}

		clock.stop();

		testTime( (Format("Test 11 - UnicodeString assignment, %d times %d characters long" ) % count % length ), clock );
	}

	//test 12
	{
		clock.start();
		std::string s;
		for ( int i=0;i<count;i++ ) {
			s = A_REALLY_LONG_STRING;
		}

		clock.stop();

		testTime( (Format("Test 12 - std::string assignment, %d times %d characters long" ) % count % length ), clock );
	}

	
	System::println( "This example ran on " + System::getOSName() + " " + System::getOSVersion() + " built with compiler: " +
						System::getCompiler() );

	
	
	FoundationKit::terminate();
	return 0;
}


/**
$Id$
*/
