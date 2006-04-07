//OSXLocalePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/OSXLocalePeer.h"
#include "vcf/FoundationKit/DateTime.h"



using namespace VCF;



std::map<String,AppleLocalePair> OSXLocalePeer::localeMaping;


OSXLocalePeer::OSXLocalePeer():
    localeRef_(NULL),
	collateLocaleRef_(NULL),
	integerNumFormatterRef_(NULL),
	realNumFormatterRef_(NULL),
	currencyNumFormatterRef_(NULL)
{

    if ( OSXLocalePeer::localeMaping.empty() ) {
        OSXLocalePeer::localeMaping["en_US"] = AppleLocalePair(langEnglish,verUS);
        OSXLocalePeer::localeMaping["en_GB"] = AppleLocalePair(langEnglish,verBritain);
        OSXLocalePeer::localeMaping["en_UK"] = AppleLocalePair(langEnglish,verBritain);
        OSXLocalePeer::localeMaping["en_IE"] = AppleLocalePair(langEnglish,verIrelandEnglish);
        OSXLocalePeer::localeMaping["en_AU"] = AppleLocalePair(langEnglish,verAustralia);
        OSXLocalePeer::localeMaping["en_CA"] = AppleLocalePair(langEnglish,verEngCanada);
        OSXLocalePeer::localeMaping["en_ZA"] = AppleLocalePair(langEnglish,verAfrikaans);




        OSXLocalePeer::localeMaping["fr_FR"] = AppleLocalePair(langFrench,verFrance);
        OSXLocalePeer::localeMaping["fr_CH"] = AppleLocalePair(langFrench,verFrSwiss);
        OSXLocalePeer::localeMaping["fr_CA"] = AppleLocalePair(langFrench,verFrCanada);
        OSXLocalePeer::localeMaping["fr_BE"] = AppleLocalePair(langFrench,verFrBelgium);


        OSXLocalePeer::localeMaping["de_DE"] = AppleLocalePair(langGerman,verGermany);
        OSXLocalePeer::localeMaping["de_CH"] = AppleLocalePair(langGerman,verGrSwiss);
        OSXLocalePeer::localeMaping["de_AT"] = AppleLocalePair(langGerman,verAustria);


        OSXLocalePeer::localeMaping["it_IT"] = AppleLocalePair(langItalian,verItaly);
        OSXLocalePeer::localeMaping["it_CH"] = AppleLocalePair(langItalian,verItalianSwiss);


        OSXLocalePeer::localeMaping["nl_BE"] = AppleLocalePair(langDutch,verFlemish);
        OSXLocalePeer::localeMaping["nl_NL"] = AppleLocalePair(langDutch,verNetherlands);

        OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSwedish,verSweden);

        OSXLocalePeer::localeMaping["es_ES"] = AppleLocalePair(langSpanish,verSpain);
        OSXLocalePeer::localeMaping["ca_ES"] = AppleLocalePair(langSpanish,verCatalonia);
        OSXLocalePeer::localeMaping["es_MX"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_GT"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_CR"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_PA"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_DO"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_VE"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_CO"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_PE"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_AR"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_EC"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_CL"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_UY"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_PY"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_BO"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_SV"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_HN"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_NI"] = AppleLocalePair(langSpanish,verSpLatinAmerica);
        OSXLocalePeer::localeMaping["es_PR"] = AppleLocalePair(langSpanish,verSpLatinAmerica);


        OSXLocalePeer::localeMaping["da_DK"] = AppleLocalePair(langDanish,verDenmark);

        OSXLocalePeer::localeMaping["pt_PT"] = AppleLocalePair(langPortuguese,verPortugal);
        OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langPortuguese,verBrazil);

        OSXLocalePeer::localeMaping["no_NO"] = AppleLocalePair(langNorwegian,verNorway);
        OSXLocalePeer::localeMaping["nb_NO"] = AppleLocalePair(langNorwegian,verNorway);
        OSXLocalePeer::localeMaping["nn_NO"] = AppleLocalePair(langNorwegian,verNynorsk);

        OSXLocalePeer::localeMaping["he_IL"] = AppleLocalePair(langHebrew,verIsrael);
        OSXLocalePeer::localeMaping["iw_IL"] = AppleLocalePair(langHebrew,verIsrael);

        OSXLocalePeer::localeMaping["ja_JP"] = AppleLocalePair(langJapanese,verJapan);

        OSXLocalePeer::localeMaping["ar_SA"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_IQ"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_EG"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_LY"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_DZ"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_MA"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_TN"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_OM"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_YE"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_SY"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_JO"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_KW"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_AE"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_BH"] = AppleLocalePair(langArabic,verArabic);
        OSXLocalePeer::localeMaping["ar_QA"] = AppleLocalePair(langArabic,verArabic);

        OSXLocalePeer::localeMaping["fi_FI"] = AppleLocalePair(langFinnish,verFinland);

        OSXLocalePeer::localeMaping["el_GR"] = AppleLocalePair(langGreek,verGreece);
        OSXLocalePeer::localeMaping["is_IS"] = AppleLocalePair(langIcelandic,verIceland);
        OSXLocalePeer::localeMaping["mt_MT"] = AppleLocalePair(langMaltese,verMalta);
        OSXLocalePeer::localeMaping["tr_TR"] = AppleLocalePair(langTurkish,verTurkey);

        OSXLocalePeer::localeMaping["hr_HR"] = AppleLocalePair(langCroatian,verCroatia);
        OSXLocalePeer::localeMaping["sh_HR"] = AppleLocalePair(langCroatian,verCroatia);

        OSXLocalePeer::localeMaping["zh_TW"] = AppleLocalePair(langTradChinese,verTaiwan);

        OSXLocalePeer::localeMaping["ur_PK"] = AppleLocalePair(langUrdu,verPakistanUrdu);
        OSXLocalePeer::localeMaping["ur_IN"] = AppleLocalePair(langUrdu,verIndiaUrdu);

        OSXLocalePeer::localeMaping["hi_IN"] = AppleLocalePair(langHindi,verIndiaHindi);
        OSXLocalePeer::localeMaping["th_TH"] = AppleLocalePair(langThai,verThailand);
        OSXLocalePeer::localeMaping["ko_KR"] = AppleLocalePair(langKorean,verKorea);
        OSXLocalePeer::localeMaping["lt_LT"] = AppleLocalePair(langLithuanian,verLithuania);
        OSXLocalePeer::localeMaping["pl_PL"] = AppleLocalePair(langPolish,verPoland);
        OSXLocalePeer::localeMaping["hu_HU"] = AppleLocalePair(langHungarian,verHungary);
        OSXLocalePeer::localeMaping["et_EE"] = AppleLocalePair(langEstonian,verEstonia);
        OSXLocalePeer::localeMaping["lv_LV"] = AppleLocalePair(langLatvian,verLatvia);

        OSXLocalePeer::localeMaping["fo_FO"] = AppleLocalePair(langFaroese,verFaroeIsl);

        OSXLocalePeer::localeMaping["fa_IR"] = AppleLocalePair(langFarsi,verIran);

        //OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langPersian,verIran); ???

        OSXLocalePeer::localeMaping["ru_RU"] = AppleLocalePair(langRussian,verRussia);

        OSXLocalePeer::localeMaping["zh_CN"] = AppleLocalePair(langSimpChinese,verChina);

        //???OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langFlemish,kTextRegionDontCare);

        OSXLocalePeer::localeMaping["ga_IE"] = AppleLocalePair(langIrishGaelic,verIreland);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAlbanian,kTextRegionDontCare);

        OSXLocalePeer::localeMaping["ro_RO"] = AppleLocalePair(langRomanian,verRomania);
        OSXLocalePeer::localeMaping["cs_CZ"] = AppleLocalePair(langCzech,verCzech);
        OSXLocalePeer::localeMaping["sk_SK"] = AppleLocalePair(langSlovak,verSlovak);
        OSXLocalePeer::localeMaping["sl_SI"] = AppleLocalePair(langSlovenian,verSlovenian);

        OSXLocalePeer::localeMaping["sr_YU"] = AppleLocalePair(langSerbian,verSerbian);
        OSXLocalePeer::localeMaping["sh_YU"] = AppleLocalePair(langSerbian,verSerbian);

        OSXLocalePeer::localeMaping["mk_MK"] = AppleLocalePair(langMacedonian,verMacedonian);
        OSXLocalePeer::localeMaping["bg_BG"] = AppleLocalePair(langBulgarian,verBulgaria);
        OSXLocalePeer::localeMaping["uk_UA"] = AppleLocalePair(langUkrainian,verUkraine);
        OSXLocalePeer::localeMaping["be_BY"] = AppleLocalePair(langByelorussian,verByeloRussian);
        OSXLocalePeer::localeMaping["uz_UZ"] = AppleLocalePair(langUzbek,verUzbek);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKazakh,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAzerbaijani,kTextRegionDontCare);

        OSXLocalePeer::localeMaping["hy_AM"] = AppleLocalePair(langArmenian,verArmenian);
        OSXLocalePeer::localeMaping["ka_GE"] = AppleLocalePair(langGeorgian,verGeorgian);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMoldavian,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKirghiz,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTajiki,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTurkmen,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMongolian,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMongolianCyr,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langPashto,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKurdish,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKashmiri,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSindhi,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTibetan,kTextRegionDontCare);
        OSXLocalePeer::localeMaping["ne_NP"] = AppleLocalePair(langNepali,verNepal);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSanskrit,kTextRegionDontCare);
        OSXLocalePeer::localeMaping["mr_IN"] = AppleLocalePair(langMarathi,verMarathi);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langBengali,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAssamese,kTextRegionDontCare);
        OSXLocalePeer::localeMaping["gu_IN"] = AppleLocalePair(langGujarati,verGujarati);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langPunjabi,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langOriya,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMalayalam,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKannada,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTamil,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTelugu,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSinhalese,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langBurmese,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKhmer,kTextRegionDontCare);
        //OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langLao,kTextRegionDontCare);

        OSXLocalePeer::localeMaping["vi_VN"] = AppleLocalePair(langVietnamese,verVietnam);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langIndonesian,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTagalog,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMalayRoman,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMalayArabic,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAmharic,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTigrinya,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langOromo,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSomali,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSwahili,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langKinyarwanda,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langRuanda,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langRundi,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langNyanja,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langChewa,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langMalagasy,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langWelsh,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langBasque,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langCatalan,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langLatin,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langQuechua,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langGuarani,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAymara,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langTatar,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langUighur,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langDzongkha,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langJavaneseRom,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langSundaneseRom,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langGalician,kTextRegionDontCare);

        OSXLocalePeer::localeMaping["af_ZA"] = AppleLocalePair(langAfrikaans,verAfrikaans);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langBreton,kTextRegionDontCare);
        OSXLocalePeer::localeMaping["iu_CA"] = AppleLocalePair(langInuktitut,verNunavut);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langScottishGaelic,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langManxGaelic,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langIrishGaelicScript,kTextRegionDontCare);
        OSXLocalePeer::localeMaping["to_TO"] = AppleLocalePair(langTongan,verTonga);

        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langGreekPoly,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langGreenlandic,kTextRegionDontCare);
        //??OSXLocalePeer::localeMaping["pt_BR"] = AppleLocalePair(langAzerbaijanRoman,kTextRegionDontCare);
    }

}

void OSXLocalePeer::setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant )
{
	if ( NULL != localeRef_ ) {
		CFRelease( localeRef_ );
		localeRef_ = NULL;
	}

	if ( NULL != integerNumFormatterRef_ ) {
		CFRelease( integerNumFormatterRef_ );
		integerNumFormatterRef_ = NULL;
	}
	
	if ( NULL != realNumFormatterRef_ ) {
		CFRelease( realNumFormatterRef_ );
		realNumFormatterRef_ = NULL;
	}
	
	if ( NULL != currencyNumFormatterRef_ ) {
		CFRelease( currencyNumFormatterRef_ );
		currencyNumFormatterRef_ = NULL;
	}



	String name = language + "_" + country;
	if ( language.empty() && country.empty() ) {
		localeRef_ = CFLocaleCopyCurrent();
		collateLocaleRef_ = NULL;
	}
	else {
        std::map<String,AppleLocalePair>::iterator found = OSXLocalePeer::localeMaping.find( name );
        if ( found != OSXLocalePeer::localeMaping.end() ) {
            AppleLocalePair& localePair = found->second;
            OSStatus err = LocaleRefFromLangOrRegionCode( localePair.first, localePair.second, &collateLocaleRef_ );
            if ( err != noErr ) {
                throw RuntimeException( MAKE_ERROR_MSG_2( "LocaleRefFromLangOrRegionCode failed!" ) );
            }
        }
		
		CFTextString localeName;
	
		localeName = name;
		
		localeRef_ = CFLocaleCreate( kCFAllocatorDefault, localeName );		
	}
	
	if ( NULL == localeRef_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "CFLocaleCreate failed for locale " + name ) );
	}
	
	
	integerNumFormatterRef_ = CFNumberFormatterCreate( kCFAllocatorDefault, localeRef_, kCFNumberFormatterDecimalStyle );
	
	if ( NULL == integerNumFormatterRef_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "CFNumberFormatterCreate failed for locale " + name ) );
	}
	
	
	realNumFormatterRef_ = CFNumberFormatterCreate( kCFAllocatorDefault, localeRef_, kCFNumberFormatterDecimalStyle );
	
	if ( NULL == realNumFormatterRef_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "CFNumberFormatterCreate failed for locale " + name ) );
	}
	
	currencyNumFormatterRef_ = CFNumberFormatterCreate( kCFAllocatorDefault, localeRef_, kCFNumberFormatterCurrencyStyle );
	
	if ( NULL == currencyNumFormatterRef_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "CFNumberFormatterCreate failed for locale " + name ) );
	}
	
	
}

OSXLocalePeer::~OSXLocalePeer()
{
	if ( NULL != localeRef_ ) {
		CFRelease( localeRef_ );
		localeRef_ = NULL;
	}

	if ( NULL != integerNumFormatterRef_ ) {
		CFRelease( integerNumFormatterRef_ );
		integerNumFormatterRef_ = NULL;
	}
	
	if ( NULL != realNumFormatterRef_ ) {
		CFRelease( realNumFormatterRef_ );
		realNumFormatterRef_ = NULL;
	}
	
	if ( NULL != currencyNumFormatterRef_ ) {
		CFRelease( currencyNumFormatterRef_ );
		currencyNumFormatterRef_ = NULL;
	}
}

int OSXLocalePeer::collate( const UnicodeString& s1, const UnicodeString& s2 )
{
    
	int result = 0;
	
    CollatorRef collatorRef = 0;
    OSStatus err = UCCreateCollator( collateLocaleRef_, 0, 0, &collatorRef );
    if ( err == noErr ) {
        Boolean matched = FALSE;
        SInt32 order = 0;
        UCCompareText( collatorRef, s1.c_str(), s1.length(),
                        s2.c_str(), s2.length(),
                        &matched,
                        &order );

        if ( order < 0 ) {
            result = -1;
        }
        else if ( order == 0 ) {
            result = 0;
        }
        else if ( order > 0 ) {
            result = 1;
        }

        UCDisposeCollator( &collatorRef );
    }
	
	return result;
}


int OSXLocalePeer::collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 )
{
	int result = 0;
    CollatorRef collatorRef = 0;
    OSStatus err = UCCreateCollator( collateLocaleRef_, 0, kUCCollateCaseInsensitiveMask, &collatorRef );
    if ( err == noErr ) {
        Boolean matched = FALSE;
        SInt32 order = 0;
        UCCompareText( collatorRef, s1.c_str(), s1.length(),
                        s2.c_str(), s2.length(),
                        &matched,
                        &order );

        if ( order < 0 ) {
            result = -1;
        }
        else if ( order == 0 ) {
            result = 0;
        }
        else if ( order > 0 ) {
            result = 1;
        }

        UCDisposeCollator( &collatorRef );
    }
	return result;
}


UnicodeString OSXLocalePeer::toString( const int& val )
{
	CFTextString result;
	result = CFNumberFormatterCreateStringWithValue( NULL, integerNumFormatterRef_, kCFNumberIntType, &val );
	return result;
}

UnicodeString OSXLocalePeer::toString( const unsigned int& val )
{
	CFTextString result;
	double tmp = val;
	result = CFNumberFormatterCreateStringWithValue( NULL, integerNumFormatterRef_, kCFNumberDoubleType, &tmp );
	return result;
}

UnicodeString OSXLocalePeer::toString( const long& val )
{
	CFTextString result;
	result = CFNumberFormatterCreateStringWithValue( NULL, integerNumFormatterRef_, kCFNumberLongType, &val );
	return result;
}

UnicodeString OSXLocalePeer::toString( const unsigned long& val )
{
	CFTextString result;
	double tmp = val;
	result = CFNumberFormatterCreateStringWithValue( NULL, integerNumFormatterRef_, kCFNumberDoubleType, &tmp );
	return result;
}

UnicodeString OSXLocalePeer::toString( const double& val )
{
	CFTextString result;
	result = CFNumberFormatterCreateStringWithValue( NULL, realNumFormatterRef_, kCFNumberDoubleType, &val );
	return result;
}

UnicodeString OSXLocalePeer::toString( const float& val )
{
	CFTextString result;
	result = CFNumberFormatterCreateStringWithValue( NULL, realNumFormatterRef_, kCFNumberFloatType, &val );
	return result;
}

UnicodeString OSXLocalePeer::toStringFromCurrency( const double& val )
{
	CFTextString result;
	result = CFNumberFormatterCreateStringWithValue( NULL, currencyNumFormatterRef_, kCFNumberDoubleType, &val );
	return result;
}




int OSXLocalePeer::toInt( const UnicodeString& str )
{
	int result = 0;
	CFTextString tmp(str);
	
	CFRefObject<CFNumberRef> num = 
		CFNumberFormatterCreateNumberFromString( kCFAllocatorDefault, 
													integerNumFormatterRef_, 
													tmp, 
													NULL, 
													kCFNumberFormatterParseIntegersOnly );
	if ( NULL != num ) {
		if ( !CFNumberGetValue( num, kCFNumberIntType, &result ) ) {
			result = StringUtils::fromStringAsInt( str );
		}
	}
	return result;
}

unsigned int OSXLocalePeer::toUInt( const UnicodeString& str )
{
	unsigned int result = 0;

	CFTextString tmp(str);
	
	CFRefObject<CFNumberRef> num = 
		CFNumberFormatterCreateNumberFromString( kCFAllocatorDefault, 
													integerNumFormatterRef_, 
													tmp, 
													NULL, 
													kCFNumberFormatterParseIntegersOnly );
	if ( NULL != num ) {
		double val = 0;
		if ( CFNumberGetValue( num, kCFNumberDoubleType, &val ) ) {
			result = (unsigned int)val;
		}
		else {
			result = StringUtils::fromStringAsUInt( str );
		}
	}
	
	return result;
}

double OSXLocalePeer::toDouble( const UnicodeString& str )
{
	double result = 0;
	CFTextString tmp(str);
	
	CFRefObject<CFNumberRef> num = 
		CFNumberFormatterCreateNumberFromString( kCFAllocatorDefault, 
													realNumFormatterRef_, 
													tmp, 
													NULL, 
													kCFNumberFormatterParseIntegersOnly );
	if ( NULL != num ) {
		if ( !CFNumberGetValue( num, kCFNumberDoubleType, &result ) ) {
			result = StringUtils::fromStringAsDouble( str );
		}
	}
	
	return result;
}

float OSXLocalePeer::toFloat( const UnicodeString& str )
{
	float result = 0;

	CFTextString tmp(str);
	
	CFRefObject<CFNumberRef> num = 
		CFNumberFormatterCreateNumberFromString( kCFAllocatorDefault, 
													realNumFormatterRef_, 
													tmp, 
													NULL, 
													kCFNumberFormatterParseIntegersOnly );
	if ( NULL != num ) {
		if ( !CFNumberGetValue( num, kCFNumberFloatType, &result ) ) {
			result = StringUtils::fromStringAsFloat( str );
		}
	}

	return result;
}

double OSXLocalePeer::toDoubleAsCurrency( const UnicodeString& str )
{
	double result = StringUtils::fromStringAsDouble( str );


	return result;
}



UnicodeString OSXLocalePeer::toLowerCase( const UnicodeString& s )
{
	CFTextString result(s);
	CFStringLowercase( result, localeRef_ );
	CFStringRef tmp = CFStringCreateCopy(NULL,result);
	result = tmp;
	CFRelease(tmp);
	
	return result;
}

UnicodeString OSXLocalePeer::toUpperCase( const UnicodeString& s )
{

	CFTextString result(s);
	CFStringUppercase( result, localeRef_ );
	CFStringRef tmp = CFStringCreateCopy(NULL,result);
	result = tmp;
	CFRelease(tmp);

	return result;
}

UnicodeString OSXLocalePeer::getNumberThousandsSeparator()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterGroupingSeparator );

	return prop;
}

UnicodeString OSXLocalePeer::getNumberDecimalPoint()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterDecimalSeparator );

	return prop;
}

UnicodeString OSXLocalePeer::getNumberGrouping()
{
	UnicodeString result;
	CFRefObject<CFNumberRef> prop;
	prop = (CFNumberRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterGroupingSize );
	if ( prop ) {
		int val=0;
		if ( CFNumberGetValue( prop, kCFNumberIntType, &val ) ) {
			char tmp[256];
			sprintf(tmp,"%d", val );
			result = tmp;
		}
	}
	return result;
}

UnicodeString OSXLocalePeer::getCurrencyDecimalPoint()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterCurrencyDecimalSeparator );

	return prop;
}

UnicodeString OSXLocalePeer::getCurrencyThousandsSeparator()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterGroupingSeparator );

	return prop;
}

UnicodeString OSXLocalePeer::getCurrencySymbol()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterCurrencySymbol );

	return prop;
}

int OSXLocalePeer::getCurrencyFractionalDigits()
{
	int result = 0;
	CFRefObject<CFNumberRef> prop;
	prop = (CFNumberRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterMinFractionDigits );
	if ( NULL != prop ) {
		CFNumberGetValue( prop, kCFNumberIntType, &result );
	}
	
	return result;
}

UnicodeString OSXLocalePeer::getCurrencyPositiveSign()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterPlusSign );

	return prop;
}

UnicodeString OSXLocalePeer::getCurrencyNegativeSign()
{
	CFTextString prop;
	prop = (CFStringRef) CFNumberFormatterCopyProperty( currencyNumFormatterRef_, kCFNumberFormatterMinusSign );

	return prop;
}

bool OSXLocalePeer::isCharA( const long& charTypeMask, const VCFChar& c )
{
	long mask = 0;

	UnicodeString oldLocaleStr = setlocale( LC_CTYPE, NULL );

	setlocale( LC_CTYPE, crtLocaleStr_.ansi_c_str() );

	if ( charTypeMask & ctSpace ) {
		if ( isspace( c ) ) {
			mask |= ctSpace;
		}
	}

	if ( charTypeMask & ctPrint ) {
		if ( isprint( c ) ) {
			mask |= ctPrint;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( isprint( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( iscntrl( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctUpper ) {
		if ( isupper( c ) ) {
			mask |= ctUpper;
		}
	}

	if ( charTypeMask & ctLower ) {
		if ( islower( c ) ) {
			mask |= ctLower;
		}
	}

	if ( charTypeMask & ctDigit ) {
		if ( isdigit( c ) ) {
			mask |= ctDigit;
		}
	}

	if ( charTypeMask & ctPunct ) {
		if ( ispunct( c ) ) {
			mask |= ctPunct;
		}
	}

	if ( charTypeMask & ctHexDigit ) {
		if ( isxdigit( c ) ) {
			mask |= ctHexDigit;
		}
	}

	if ( charTypeMask & ctAlpha ) {
		if ( isalpha( c ) ) {
			mask |= ctAlpha;
		}
	}

	if ( charTypeMask & ctAlphaNumeric ) {
		if ( isalnum( c ) ) {
			mask |= ctAlphaNumeric;
		}
	}

	if ( charTypeMask & ctGraph ) {
		if ( isgraph( c ) ) {
			mask |= ctGraph;
		}
	}

	setlocale( LC_CTYPE, oldLocaleStr.ansi_c_str() );

	return (0 == mask) ? false : true;
}

UnicodeString OSXLocalePeer::translate( const UnicodeString& id )
{
	return "";
}

UnicodeString OSXLocalePeer::toStringFromDate( const DateTime& val, const UnicodeString& format )
{

	CFTextString result;

	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
	unsigned long millisecond;	
	val.get( &year, &month, &day, &hour, &minute, &second, &millisecond );

	CFGregorianDate cfDate;
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = ((double)second) + ( 1000.0/(double)millisecond );
	
	CFAbsoluteTime timeVal = CFGregorianDateGetAbsoluteTime( cfDate, NULL );
	CFRefObject<CFDateRef> dt = CFDateCreate(NULL, timeVal);
	CFDateFormatterRef dtFmt = CFDateFormatterCreate(NULL, 
													localeRef_, 
													kCFDateFormatterLongStyle, 
													kCFDateFormatterNoStyle);
													
	result = CFDateFormatterCreateStringWithDate(NULL, dtFmt, dt);
	
	return result;
}

UnicodeString OSXLocalePeer::toStringFromTime( const DateTime& val, const UnicodeString& format )
{
	CFTextString result;

	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
	unsigned long millisecond;	
	val.get( &year, &month, &day, &hour, &minute, &second, &millisecond );
	
	CFGregorianDate cfDate;
	cfDate.year = year;
	cfDate.month = month;
	cfDate.day = day;
	cfDate.hour = hour;
	cfDate.minute = minute;
	cfDate.second = ((double)second) + ( 1000.0/(double)millisecond );
	
	CFAbsoluteTime timeVal = CFGregorianDateGetAbsoluteTime( cfDate, NULL );
	CFRefObject<CFDateRef> dt = CFDateCreate(NULL, timeVal);
	CFDateFormatterRef dtFmt = CFDateFormatterCreate(NULL, 
													localeRef_, 
													kCFDateFormatterNoStyle, 
													kCFDateFormatterShortStyle);
													
	result = CFDateFormatterCreateStringWithDate(NULL, dtFmt, dt);
	
	return result;
}

ulong32 OSXLocalePeer::getLanguageCode()
{
	CFTextString tmp(CFLocaleGetIdentifier(localeRef_));
	
	UnicodeString id = tmp;
	
	VCF_ASSERT( id.size() >= 2 );

	return Locale::stringToLanguageCode( id.substr(0,2) );
}


ulong32 OSXLocalePeer::getCountryCode()
{
	CFTextString tmp(CFLocaleGetIdentifier(localeRef_));
	
	UnicodeString id = tmp;
	
	VCF_ASSERT( id.size() >= 2 );
	
	size_t pos = id.find("_");
	
	VCF_ASSERT( pos != UnicodeString::npos );
	

	return Locale::stringToCountryCode( id.substr(pos+1,id.size()-(pos+1)) );
}

String OSXLocalePeer::getLanguage()
{
	String result;
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2006/03/23 05:23:14  ddiego
*added missing stub for OSX to locale peer.
*
*Revision 1.3.2.2  2005/11/27 23:55:45  ddiego
*more osx updates.
*
*Revision 1.3.2.1  2005/11/13 16:02:46  ddiego
*more sox updates.
*
*Revision 1.3  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/23 01:26:56  ddiego
*build updates
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.7  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*Revision 1.1.2.1  2004/02/16 05:38:10  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:08:44  ddiego
*updates some missing locale impl files
*
*/


