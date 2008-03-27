//VCFString.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/TextCodec.h"

#include <errno.h>

using namespace VCF;



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

UnicodeString::UnicodeString( size_type n, UnicodeString::AnsiChar c ):
	data_( n, UnicodeString::transformAnsiCharToUnicodeChar(c) ),
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
	}
	
#endif
	return result;
}

void UnicodeString::transformAnsiToUnicode( const UnicodeString::AnsiChar* str, UnicodeString::size_type stringLength, UnicodeString::StringData& newStr, LanguageEncoding encoding )
{
	if ( stringLength == 0 ) {
		newStr.erase(0,newStr.size());
	}
	else {

		unsigned int sysEncoding = UnicodeStringGetEncoding(encoding);

	#ifdef VCF_WIN

		/***
		What code page do we want to use here???? CP_ACP may not be the 
		most appropriate one to use. First let's try and examine the 
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

#ifdef VCF_WIN
	int err = MultiByteToWideChar( CP_ACP, 0, &c, 1, (LPWSTR)&result, 1 );

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

#ifdef VCF_WIN
	
	if (  0 == ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)&c, 1,
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


#ifdef VCF_WIN
    int strLength = str.data_.size();
	if ( str.empty() ) {
		strLength = 1;
	}

	size = ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
							NULL, 0, NULL, NULL );

	if ( !(size > 0) ) {
		throw RuntimeException( L"size > 0 WideCharToMultiByte() failed" );
	}

	result = new UnicodeString::AnsiChar[size+1];

	if (  0 == ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)str.data_.c_str(), strLength,
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

void UnicodeString::decode_ansi( TextCodec* codec, UnicodeString::AnsiChar* str, UnicodeString::size_type& strSize ) const 
{
	VCF_ASSERT ( str != NULL );

	uint32 size = codec->convertToAnsiString( *this, str, strSize );	
	
	if ( size < strSize ) {
		str[size] = 0;
	}
	
	strSize = size;
}

UnicodeString UnicodeString::decode( TextCodec* codec ) const
{
	return codec->convertToUnicodeString( *this );
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString::AnsiChar* str, UnicodeString::size_type n )
{
	VCF_ASSERT ( str != NULL );
	*this = codec->convertToUnicodeString( str, n );
	modified();
}

void UnicodeString::encode( TextCodec* codec, const UnicodeString& str )
{
	*this = codec->convertToUnicodeString( str );
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

const UnicodeString::AnsiChar* UnicodeString::ansi_c_str() const
{	
	if ( NULL == ansiDataBuffer_  ) {
		ansiDataBuffer_ = UnicodeString::transformUnicodeToAnsi( *this );
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


/**
$Id$
*/
