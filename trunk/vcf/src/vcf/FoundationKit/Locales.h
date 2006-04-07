#ifndef _VCF_LOCALES_H__
#define _VCF_LOCALES_H__
//Locales.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class LocalePeer;
class MessageLoader;


/**
\class Locale Locales.h "vcf/FoundationKit/Locales.h"
A locale instance represents the cultural data used to convert data to string
in manner appropriate to the language and country. Each locale is identified
by a language and a country code, where the language code is one of the possible
values as listed by
<a href="http://www.loc.gov/standards/iso639-2/langcodes.html">ISO-639-1</a>,
and the country code is one of the possible values as listed in
<a href="http://www.iso.org/iso/en/prods-services/iso3166ma/02iso-3166-code-lists/list-en1.html">
ISO-3166</a>. The complete locale is referred to as a combination of both these values,
for example, the french locale is referred to as "fr_FR", and the United States locale
is referred to as "en_US".

A locale offers a variety of methods to translate data into a string, based on the rules
of the locale. For example, monetary units are represented by the dollar symbol ("$")
in the "en_US" locale, but the United Kindom ("en_GB") are represented by the pound ("£").
Other functions include the ability to sort 2 strings based on the locale's sorting
rules (also referred to as "collation"), transforming numerical data (ints, longs,
doubles, etc) to a string. For example:
\code
Locale loc("en_US"); //United States
String numString = loc.toString( 123456 ); //numString = "123,456"

Locale loc("it_IT"); //Italy
String numString = loc.toString( 123456 ); //numString = "123.456"
\endcode
You can also convert currency data (as a double) to a string.

There are date and time functions for transforming a DateTime instance into a string
that is representative of the time in hours, minutes, and seconds, and into
a string that represents the date.

There are case transformation functions, to convert a string into all upper case
or into all lowercase.
*/
class FOUNDATIONKIT_API Locale : public Object {
public:

	/**
	This enumerates all the possible country codes. The value of
	each code is exactly that as specified in ISO-3166.
	*/
	enum CountryCodes {
		ccUndefined = 0,
		ccAfghanistan 	= 'AF',
		ccAlbania	= 'AL',
		ccAlgeria	= 'DZ',
		ccAmericanSamoa	= 'AS',
		ccAndorra	= 'AD',
		ccAngola	= 'AO',
		ccAnguilla	= 'AI',
		ccAntarctica	= 'AQ',
		ccAntiguaAndBarbuda	= 'AG',
		ccArgentina	= 'AR',
		ccArmenia	= 'AM',
		ccAruba	= 'AW',
		ccAustralia	= 'AU',
		ccAustria	= 'AT',
		ccAzerbaijan	= 'AZ',
		ccBahamas	= 'BS',
		ccBahrain	= 'BH',
		ccBangladesh	= 'BD',
		ccBarbados	= 'BB',
		ccBelarus	= 'BY',
		ccBelgium	= 'BE',
		ccBelize	= 'BZ',
		ccBenin	= 'BJ',
		ccBermuda	= 'BM',
		ccBhutan	= 'BT',
		ccBolivia	= 'BO',
		ccBosniaAndHerzegovina	= 'BA',
		ccBotswana	= 'BW',
		ccBouvetIsland	= 'BV',
		ccBrazil	= 'BR',
		ccBritishIndianOceanTerritory	= 'IO',
		ccBrunei	= 'BN',
		ccBulgaria	= 'BG',
		ccBurkinaFaso	= 'BF',
		ccBurundi	= 'BI',
		ccCambodia	= 'KH',
		ccCameroon	= 'CM',
		ccCanada	= 'CA',
		ccCapeVerde	= 'CV',
		ccCaymanIslands	= 'KY',
		ccCentralAfricanRepublic	= 'CF',
		ccChad	= 'TD',
		ccChile	= 'CL',
		ccChina	= 'CN',
		ccChristmasIsland	= 'CX',
		ccCocosIslands	= 'CC',
		ccColombia	= 'CO',
		ccComoros	= 'KM',
		ccCongo	= 'CG',
		ccDemocraticRepOfCongo = 'CD',
		ccCookIslands	= 'CK',
		ccCostaRica	= 'CR',
		ccCoteDIvoire	= 'CI',
		ccCroatia	= 'HR',
		ccCuba	= 'CU',
		ccCyprus	= 'CY',
		ccCzechRepublic	= 'CZ',
		ccDenmark	= 'DK',
		ccDjibouti	= 'DJ',
		ccDominica	= 'DM',
		ccDominicanRepublic	= 'DO',
		ccEcuador	= 'EC',
		ccEgypt	= 'EG',
		ccElSalvador	= 'SV',
		ccEquatorialGuinea	= 'GQ',
		ccEritrea	= 'ER',
		ccEstonia	= 'EE',
		ccEthiopia	= 'ET',
		ccFalklandIslands	= 'FK',
		ccFaroIslands	= 'FO',
		ccFiji	= 'FJ',
		ccFinland	= 'FI',
		ccFrance	= 'FR',
		ccFrenchGuiana	= 'GF',
		ccFrenchPolynesia	= 'PF',
		ccFrenchSouthernTerritories	= 'TF',
		ccGabon 	= 'GA',
		ccGambia	= 'GM',
		ccGeorgia	= 'GE',
		ccGermany	= 'DE',
		ccGhana	= 'GH',
		ccGibraltar	= 'GI',
		ccGreece	= 'GR',
		ccGreenland	= 'GL',
		ccGrenada	= 'GD',
		ccGuadeloupe	= 'GP',
		ccGuam	= 'GU',
		ccGuatemala	= 'GT',
		ccGuinea	= 'GN',
		ccGuineaBissau	= 'GW',
		ccGuyana	= 'GY',
		ccHaiti	= 'HT',
		ccHeardIslandAndMcdonaldIslands	= 'HM',
		ccVaticanCity	= 'VA',
		ccHonduras	= 'HN',
		ccHongKong	= 'HK',
		ccHungary	= 'HU',
		ccIceland	= 'IS',
		ccIndia	= 'IN',
		ccIndonesia	= 'ID',
		ccIran = 'IR',
		ccIraq	= 'IQ',
		ccIreland	= 'IE',
		ccIsrael	= 'IL',
		ccItaly	= 'IT',
		ccJamaica	= 'JM',
		ccJapan	= 'JP',
		ccJordan	= 'JO',
		ccKazakhstan	= 'KZ',
		ccKenya	= 'KE',
		ccKiribati	= 'KI',
		ccNorthKorea = 'KP',
		ccSouthKorea = 'KR',
		ccKuwait	= 'KW',
		ccKyrgyzstan	= 'KG',
		ccPeoplesRepublicOfLao 	= 'LA',
		ccLatvia	= 'LV',
		ccLebanon	= 'LB',
		ccLesotho	= 'LS',
		ccLiberia	= 'LR',
		ccLibyanArabJamahiriya	= 'LY',
		ccLiechtenstein	= 'LI',
		ccLithuania	= 'LT',
		ccLuxembourg	= 'LU',
		ccMacao	= 'MO',
		ccMacedonia = 'MK',
		ccMadagascar	= 'MG',
		ccMalawi	= 'MW',
		ccMalaysia	= 'MY',
		ccMaldives	= 'MV',
		ccMali	= 'ML',
		ccMalta	= 'MT',
		ccMarshallIslands	= 'MH',
		ccMartinique	= 'MQ',
		ccMauritania	= 'MR',
		ccMauritius	= 'MU',
		ccMayotte	= 'YT',
		ccMexico	= 'MX',
		ccMicronesia = 'FM',
		ccMoldova = 'MD',
		ccMonaco	= 'MC',
		ccMongolia	= 'MN',
		ccMontserrat	= 'MS',
		ccMorocco	= 'MA',
		ccMozambique	= 'MZ',
		ccMyanmar	= 'MM',
		ccNamibia	= 'NA',
		ccNauru	= 'NR',
		ccNepal	= 'NP',
		ccNetherlands	= 'NL',
		ccNetherlandsAntilles	= 'AN',
		ccNewCaledonia	= 'NC',
		ccNewZealand	= 'NZ',
		ccNicaragua	= 'NI',
		ccNiger	= 'NE',
		ccNigeria	= 'NG',
		ccNiue	= 'NU',
		ccNorfolkIsland	= 'NF',
		ccNorthernMarianaIslands	= 'MP',
		ccNorway	= 'NO',
		ccOman	= 'OM',
		ccPakistan	= 'PK',
		ccPalau	= 'PW',
		ccPalestinianTerritory = 'PS',
		ccPanama	= 'PA',
		ccPapuaNewGuinea	= 'PG',
		ccParaguay	= 'PY',
		ccPeru	= 'PE',
		ccPhilippines	= 'PH',
		ccPitcairn	= 'PN',
		ccPoland	= 'PL',
		ccPortugal	= 'PT',
		ccPuertoRico	= 'PR',
		ccQatar	= 'QA',
		ccReunion	= 'RE',
		ccRomania	= 'RO',
		ccRussianFederation	= 'RU',
		ccRwanda	= 'RW',
		ccSaintHelena 	= 'SH',
		ccSaintKitts	= 'KN',
		ccNevis	= 'KN',
		ccSaintLucia	= 'LC',
		ccSaintPierre	= 'PM',
		ccMiquelon	= 'PM',
		ccSaintVincent	= 'VC',
		ccTheGrenadines	= 'VC',
		ccSamoa	= 'WS',
		ccSanMarino	= 'SM',
		ccSaoTome	= 'ST',
		ccPrincipe	= 'ST',
		ccSaudiArabia	= 'SA',
		ccSenegal	= 'SN',
		ccSerbia	= 'CS',
		ccMontenegro	= 'CS',
		ccSeychelles	= 'SC',
		ccSierraLeone	= 'SL',
		ccSingapore	= 'SG',
		ccSlovakia	= 'SK',
		ccSlovenia	= 'SI',
		ccSolomonIslands	= 'SB',
		ccSomalia	= 'SO',
		ccSouthAfrica	= 'ZA',
		ccSouthGeorgia	= 'GS',
		ccSouthSandwichIslands	= 'GS',
		ccSpain	= 'ES',
		ccSriLanka	= 'LK',
		ccSudan	= 'SD',
		ccSuriname	= 'SR',
		ccSvalbard	= 'SJ',
		ccJanMayen	= 'SJ',
		ccSwaziland	= 'SZ',
		ccSweden	= 'SE',
		ccSwitzerland	= 'CH',
		ccSyrianArabRepublic	= 'SY',
		ccTaiwan = 'TW',
		ccTajikistan	= 'TJ',
		ccTanzania = 'TZ',
		ccThailand	= 'TH',
		ccTimorLeste	= 'TL',
		ccTogo	= 'TG',
		ccTokelau	= 'TK',
		ccTonga	= 'TO',
		ccTrinidad	= 'TT',
		ccTobago	= 'TT',
		ccTunisia	= 'TN',
		ccTurkey	= 'TR',
		ccTurkmenistan	= 'TM',
		ccTurksAndCaicosIslands	= 'TC',
		ccTuvalu	= 'TV',
		ccUganda	= 'UG',
		ccUkraine	= 'UA',
		ccUnitedArabEmirates	= 'AE',
		ccUnitedKingdom	= 'GB',
		ccUnitedStates	= 'US',
		ccUnitedStatesMinorOutlyingIslands	= 'UM',
		ccUruguay	= 'UY',
		ccUzbekistan	= 'UZ',
		ccVanuatu	= 'VU',
		ccVenezuela	= 'VE',
		ccVietNam	= 'VN',
		ccBritishVirginIslands = 'VG',
		ccUSVirginIslands = 'VI',
		ccWallisAndFutuna	= 'WF',
		ccWesternSahara	= 'EH',
		ccYemen	= 'YE',
		ccZaire = ccDemocraticRepOfCongo,
		ccZambia	= 'ZM',
		ccZimbabwe	= 'ZW'
	};


	/**
	This enumerates all the possible language codes. The value of
	each code is exactly that as specified in ISO-639-1.
	*/
	enum LanguageCodes{
		lcUndefined = 0,
		lcAfar	= 'aa',
		lcAbkhazian	= 'ab',
		lcAfrikaans	= 'af',
		lcAkan	= 'ak',
		lcAlbanian	= 'sq',
		lcAmharic	= 'am',
		lcArabic	= 'ar',
		lcAragonese	= 'an',
		lcArmenian	= 'hy',
		lcAssamese	= 'as',
		lcAvaric	= 'av',
		lcAvestan	= 'ae',
		lcAymara	= 'ay',
		lcAzerbaijani	= 'az',
		lcBashkir	= 'ba',
		lcBambara	= 'bm',
		lcBasque	= 'eu',
		lcBelarusian	= 'be',
		lcBengali	= 'bn',
		lcBihari	= 'bh',
		lcBislama	= 'bi',
		lcTibetan	= 'bo',
		lcBosnian	= 'bs',
		lcBreton	= 'br',
		lcBulgarian	= 'bg',
		lcBurmese	= 'my',
		lcCatalan	= 'ca',
		lcValencian	= 'ca',
		lcCzech	= 'cs',
		lcChamorro	= 'ch',
		lcChechen	= 'ce',
		lcChinese	= 'zh',
		lcChurchSlavic	= 'cu',
		lcOldSlavonic	= 'cu',
		lcChurchSlavonic	= 'cu',
		lcOldBulgarian	= 'cu',
		lcOldChurchSlavonic	= 'cu',
		lcChuvash	= 'cv',
		lcCornish	= 'kw',
		lcCorsican	= 'co',
		lcCree	= 'cr',
		lcWelsh	= 'cy',
		lcDanish	= 'da',
		lcGerman	= 'de',
		lcDivehi	= 'dv',
		lcFlemish	= 'nl',
		lcDutch	= 'nl',
		lcDzongkha	= 'dz',
		lcGreek	= 'el',
		lcEnglish	= 'en',
		lcEsperanto	= 'eo',
		lcEstonian	= 'et',
		lcEwe	= 'ee',
		lcFaroese	= 'fo',
		lcPersian	= 'fa',
		lcFijian	= 'fj',
		lcFinnish	= 'fi',
		lcFrench	= 'fr',
		lcFrisian	= 'fy',
		lcFulah	= 'ff',
		lcGeorgian	= 'ka',
		lcGaelic	= 'gd',
		lcScottishGaelic	= 'gd',
		lcIrish	= 'ga',
		lcGallegan	= 'gl',
		lcManx	= 'gv',
		lcGuarani	= 'gn',
		lcGujarati	= 'gu',
		lcHaitian	= 'ht',
		lcHaitianCreole	= 'ht',
		lcHausa	= 'ha',
		lcHebrew	= 'he',
		lcHerero	= 'hz',
		lcHindi	= 'hi',
		lcHiriMotu	= 'ho',
		lcCroatian	= 'hr',
		lcHungarian	= 'hu',
		lcIgbo	= 'ig',
		lcIcelandic	= 'is',
		lcIdo	= 'io',
		lcSichuanYi	= 'ii',
		lcInuktitut	= 'iu',
		lcInterlingue	= 'ie',
		lcInterlingua	= 'ia',
		lcIndonesian	= 'id',
		lcInupiaq	= 'ik',
		lcItalian	= 'it',
		lcJavanese	= 'jv',
		lcJapanese	= 'ja',
		lcKalaallisut	= 'kl',
		lcGreenlandic	= 'kl',
		lcKannada	= 'kn',
		lcKashmiri	= 'ks',
		lcKanuri	= 'kr',
		lcKazakh	= 'kk',
		lcKhmer	= 'km',
		lcKikuyu	= 'ki',
		lcGikuyu	= 'ki',
		lcKinyarwanda	= 'rw',
		lcKirghiz	= 'ky',
		lcKomi	= 'kv',
		lcKongo	= 'kg',
		lcKorean	= 'ko',
		lcKuanyama	= 'kj',
		lcKwanyama	= 'kj',
		lcKurdish	= 'ku',
		lcLao	= 'lo',
		lcLatin	= 'la',
		lcLatvian	= 'lv',
		lcLimburgan	= 'li',
		lcLimburger	= 'li',
		lcLimburgish	= 'li',
		lcLingala	= 'ln',
		lcLithuanian	= 'lt',
		lcLuxembourgish	= 'lb',
		lcLetzeburgesch	= 'lb',
		lcLubaKatanga	= 'lu',
		lcGanda	= 'lg',
		lcMacedonian	= 'mk',
		lcMarshallese	= 'mh',
		lcMalayalam	= 'ml',
		lcMaori	= 'mi',
		lcMarathi	= 'mr',
		lcMalay	= 'ms',
		lcMalagasy	= 'mg',
		lcMaltese	= 'mt',
		lcMoldavian	= 'mo',
		lcMongolian	= 'mn',
		lcNauru	= 'na',
		lcNavajo	= 'nv',
		lcNavaho	= 'nv',
		lcSouthNdebele	= 'nr',
		lcNorthNdebele	= 'nd',
		lcNdonga	= 'ng',
		lcNepali	= 'ne',
		lcNorwegianNynorsk	= 'nn',
		lcNorwegianBokmal	= 'nb',
		lcNorwegian	= 'no',
		lcChichewa	= 'ny',
		lcChewa	= 'ny',
		lcNyanja	= 'ny',
		lcOccitan	= 'oc',
		lcProvencal	= 'oc',
		lcOjibwa	= 'oj',
		lcOriya	= 'or',
		lcOromo	= 'om',
		lcOssetian	= 'os',
		lcOssetic	= 'os',
		lcPunjabi	= 'pa',
		lcPali	= 'pi',
		lcPolish	= 'pl',
		lcPortuguese	= 'pt',
		lcPushto	= 'ps',
		lcQuechua	= 'qu',
		lcRaetoRomance	= 'rm',
		lcRomanian	= 'ro',
		lcRundi	= 'rn',
		lcRussian	= 'ru',
		lcSango	= 'sg',
		lcSanskrit	= 'sa',
		lcSerbian	= 'sr',
		lcSinhalese	= 'si',
		lcSlovak	= 'sk',
		lcSlovenian	= 'sl',
		lcNorthernSami	= 'se',
		lcSamoan	= 'sm',
		lcShona	= 'sn',
		lcSindhi	= 'sd',
		lcSomali	= 'so',
		lcSotho	= 'st',
		lcSpanish	= 'es',
		lcSardinian	= 'sc',
		lcSwati	= 'ss',
		lcSundanese	= 'su',
		lcSwahili	= 'sw',
		lcSwedish	= 'sv',
		lcTahitian	= 'ty',
		lcTamil	= 'ta',
		lcTatar	= 'tt',
		lcTelugu	= 'te',
		lcTajik	= 'tg',
		lcTagalog	= 'tl',
		lcThai	= 'th',
		lcTigrinya	= 'ti',
		lcTonga	= 'to',
		lcTswana	= 'tn',
		lcTsonga	= 'ts',
		lcTurkmen	= 'tk',
		lcTurkish	= 'tr',
		lcTwi	= 'tw',
		lcUighur	= 'ug',
		lcUkrainian	= 'uk',
		lcUrdu	= 'ur',
		lcUzbek	= 'uz',
		lcVenda	= 've',
		lcVietnamese	= 'vi',
		lcVolapuk	= 'vo',
		lcWalloon	= 'wa',
		lcWolof	= 'wo',
		lcXhosa	= 'xh',
		lcYiddish	= 'yi',
		lcYoruba	= 'yo',
		lcZhuang	= 'za',
		lcChuang	= 'za',
		lcZulu	= 'zu'

	};

	/**
	Construct a new locale instance from a language code string, and a
	country code string.
	*/
	Locale( const UnicodeString& languageCode, const UnicodeString& countryCode );

	Locale( const LanguageCodes& languageCode, const CountryCodes& countryCode );

	virtual ~Locale();

	LanguageCodes getLanguageCode();

	CountryCodes getCountryCode();

	/**
	Returns the locale's ISO-639-1 language code. The language codes can be seen here:
	http://www.loc.gov/standards/iso639-2/langcodes.html.
	Each code is 2 characters long, and are always lower case.
	*/
	UnicodeString getLanguageCodeString() {
		return Locale::languageCodeToString(getLanguageCode());
	}

	/**
	Returns the english full language name as specified by ISO-639-2. For example,
	the language code "zh" has a language name value of "Chinese".
	*/
	UnicodeString getLanguageName();

	/**
	Get the ISO-3166 country code. This can be see here:
	http://www.iso.org/iso/en/prods-services/iso3166ma/02iso-3166-code-lists/list-en1.html
	Each code is 2 characters long, and are always upper case.
	*/
	UnicodeString getCountryCodeString() {
		return Locale::countryCodeToString(getCountryCode());
	}

	/**
	returns a string that is a combination of the language code, an
	"_", and the country code.
	*/
	UnicodeString getName();



	/**
	Collates, or compares, taking case into consideration, two strings.
	Returns either -1, 0, 1, indicating
	s1 is less than, equal to, or greater than s2.
	@param UnicodeString the first string
	@param the second string
	@return The values are either -1, 0, or 1, as follows:
		\li returns -1 if s1 < s2
		\li returns 0 if s1 == s2
		\li returns 1 if s1 > s2
	*/
	int collate( const UnicodeString& s1, const UnicodeString& s2 );

	/**
	Collates, or compares, two strings, ignoring their case. Returns either -1, 0, 1, indicating
	s1 is less than, equal to, or greater than s2.
	@param UnicodeString the first string
	@param the second string
	@return The values are either -1, 0, or 1, as follows:
		\li returns -1 if s1 < s2
		\li returns 0 if s1 == s2
		\li returns 1 if s1 > s2
	*/
	int collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 );

	/**
	converts the integer val into a UnicodeString.
	For example:
	\code
	Locale loc("it", "IT" );

	UnicodeString numStr = loc.toString( 12345678 );
	//numStr will equal "12.345.678" since italy uses the "." as a decimal separator.
	\endcode
	@param int the value to convert
	@return UnicodeString the value as a string, taking into consideration any formatting
	rules of the locale.
	@see getNumberDecimalPoint()
	*/
	UnicodeString toString( const int& val );
	UnicodeString toString( const unsigned int& val );
	UnicodeString toString( const long& val );
	UnicodeString toString( const unsigned long& val );
	UnicodeString toString( const double& val );
	UnicodeString toString( const float& val );

	/**
	Converts a double currency value into a string.

	*/
	UnicodeString toStringFromCurrency( const double& val );

	/**
	converts a date/time instance into a string representing the date portion of
	the DateTime instance.
	
	For example:
	\code
	Locale loc("it", "IT" );

	DateTime aDate(11,12,1969);

	UnicodeString datStr = loc.toStringFromDate( aDate );
	\endcode
	
	You can also format the string that is output by using the following codes. Note that
	the case of the codes <strong>must</strong> be preserved, i.e. "dd", not "DD".
	<table>
	  <tr>
	    <td>Value</td><td>Meaning</td>
	  </tr>
	  <tr>
	    <td>d</td><td>The day of the month (1-31) with no leading zero.</td>
	  </tr>
	  <tr>
	    <td>dd</td><td>The day of the month (01-31) <b>with</b> leading zero.</td>
	  </tr>
	  <tr>
	    <td>ddd</td><td>The day of the week as an abbreviated string ("Mon", "Tue", etc).</td>
	  </tr>
	  <tr>
	    <td>dddd</td><td>The day of the week as a string, fully spelled out ("Monday", "Tuesday", etc).</td>
	  </tr>
	  <tr>
	    <td>M</td><td>The month as a number (1-12) with no leading zero.</td>
	  </tr>
	  <tr>
	    <td>MM</td><td>The month as a number (01-12) <string>with</strong> leading zero.</td>
	  </tr>
	  <tr>
	    <td>MMM</td><td>The month as an abbreviated string ("Jul", "Aug", etc).</td>
	  </tr>
	  <tr>
	    <td>MMMM</td><td>The month as string, fully spelled out ("July", "August", etc).</td>
	  </tr>
	  <tr>
	    <td>y</td><td>The last 2 digits of the year with no leading zero if the value is less than 10.</td>
	  </tr>
	  <tr>
	    <td>yy</td><td>The last 2 digits of the year with a leading zero.</td>
	  </tr>
	  <tr>
	    <td>yyyy</td><td>The year with all 4 (or more) digits.</td>
	  </tr>
	</table>
	An example of this:
	\code
	Locale loc("en", "US" );

	DateTime aDate(12,11,1969);

	UnicodeString datStr = loc.toStringFromDate( aDate, "dddd, MMM d yyyy" );
	//datStr will equal "Saturday, Nov 12 1969"
	\endcode
	@return UnicodeString the new string instance of a date
	*/
	UnicodeString toStringFromDate( const DateTime& val, const UnicodeString& format="" );

	/**
	converts a date/time instance into a string representing the time portion of
	the DateTime instance.
	
	For example:
	\code
	Locale loc("it", "IT" );

	DateTime aDate(11,12,1969,14,34,45);

	UnicodeString datStr = loc.toStringFromTime( aDate );
	//datStr = "14.34.45"
	\endcode
	
	You can also format the string that is output by using the following codes. Note that
	the case of the codes <strong>must</strong> be preserved, i.e. "dd", not "DD".
	<table>
	  <tr>
	    <td>Value</td><td>Meaning</td>
	  </tr>
	  <tr>
	    <td>h</td><td>The hour as a number (0-12) with no leading zero, and a 12 hour clock.</td>
	  </tr>
	  <tr>
	    <td>hh</td><td>The hour as a number (00-12) <b>with</b> leading zero, and a 12 hour clock.</td>
	  </tr>
	  <tr>
	    <td>H</td><td>The hour as a number (0-23) with no leading zero, and a 24 hour clock</td>
	  </tr>
	  <tr>
	    <td>HH</td><td>The hour as a number (00-23) <b>with</b> leading zero, and a 24 hour clock.</td>
	  </tr>
	  <tr>
	    <td>m</td><td>The minute as a number (0-59) with no leading zero.</td>
	  </tr>
	  <tr>
	    <td>mm</td><td>The minute as a number (00-59) <b>with</b> leading zero.</td>
	  </tr>
	  <tr>
	    <td>s</td><td>The second as a number (0-59) with no leading zero.</td>
	  </tr>
	  <tr>
	    <td>ss</td><td>The second as a number (00-59) <b>with</b> leading zero.</td>
	  </tr>

	</table>
	An example of this:
	\code
	Locale loc("en", "US" );

	DateTime aDate(11,12,1969,14,34,45);

	UnicodeString timeStr = loc.toStringFromDate( aDate, "h:mm:ss" );
	//timeStr will equal "2:34:45"
	\endcode
	@return UnicodeString the new string instance of a date
	*/
	UnicodeString toStringFromTime( const DateTime& val, const UnicodeString& format="" );

	/**
	Converts a string to a integer.
	*/
	int toInt( const UnicodeString& str );
	unsigned int toUInt( const UnicodeString& str );
	double toDouble( const UnicodeString& str );
	float toFloat( const UnicodeString& str );
	double toDoubleAsCurrency( const UnicodeString& str );

	/**
	Transforms all alpha numeric characters in a string to lower case.
	\code
	Locale loc("en","US");
	UnicodeString lowerCaseStr = loc.toLowerCase("ABC Defg 123 HIJKLM");
	//lowerCaseStr equals "abc defg 123 hijklm"
	\endcode
	@return UnicodeString the new string with all lower case characters
	*/
	UnicodeString toLowerCase( const UnicodeString& s );

	/**
	Transforms all alpha numeric characters in a string to upper case.
	\code
	Locale loc("en","US");
	UnicodeString lowerCaseStr = loc.toUpperCase("ABC Defg 123 HIJKLM");
	//lowerCaseStr equals "ABC DEFG 123 HIJKLM"
	\endcode

	@return UnicodeString the new string with all upper case characters
	*/
	UnicodeString toUpperCase( const UnicodeString& s );

	UnicodeString getNumberThousandsSeparator();
	UnicodeString getNumberDecimalPoint();
	UnicodeString getNumberGrouping();
	UnicodeString getCurrencyDecimalPoint();
	UnicodeString getCurrencyThousandsSeparator();
	UnicodeString getCurrencySymbol();
	int getCurrencyFractionalDigits();
	UnicodeString getCurrencyPositiveSign();
	UnicodeString getCurrencyNegativeSign();

	bool isCharA( const long& charTypeMask, const VCFChar& c );

	UnicodeString translate( const UnicodeString& id );

	LocalePeer* getPeer() {
		return peer_;
	}

	static UnicodeString languageCodeToString( LanguageCodes code );
	static UnicodeString countryCodeToString( CountryCodes code );

	static LanguageCodes stringToLanguageCode( const UnicodeString& code );
	static CountryCodes stringToCountryCode( const UnicodeString& code );
protected:
	LocalePeer* peer_;


};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/23 00:56:09  ddiego
*added a fix to algo for determing resource directory name.
*
*Revision 1.2.6.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/22 04:18:59  ddiego
*fixed bug 995642 delete LoalePeer in Locale, and added some miscellaneous changes to the QTPlayer. Also fixing (not finished yet) a bug that
*prevents the TreePeer from being properly notified when the tree model's
*item is deleted.
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.12.2.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.2.2  2004/02/16 05:34:04  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.11.2.1  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.11  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.10  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.9.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.9  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.22.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.22.1  2003/03/12 03:09:36  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LOCALES_H__


