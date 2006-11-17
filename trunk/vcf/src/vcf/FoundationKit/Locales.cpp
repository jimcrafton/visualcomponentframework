//Locales.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/MessageLoader.h"



using namespace VCF;






Locale::Locale( const UnicodeString& languageCode, const UnicodeString& countryCode ):
	peer_(NULL)
{
	peer_ = SystemToolkit::createLocalePeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2( "No Locale peer found" ) );
	}

	peer_->setLocale( languageCode, countryCode, "" );
}

Locale::Locale( const Locale::LanguageCodes& languageCode, const Locale::CountryCodes& countryCode ):
	peer_(NULL)
{
	peer_ = SystemToolkit::createLocalePeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2( "No Locale peer found" ) );
	}

	peer_->setLocale( Locale::languageCodeToString(languageCode), Locale::countryCodeToString(countryCode), "" );
}

Locale::~Locale() 
{
	delete peer_;
	peer_ = NULL;
}

UnicodeString Locale::getName()
{
	return getLanguageCodeString() + "_" + getCountryCodeString();
}

Locale::LanguageCodes Locale::getLanguageCode()
{
	return (Locale::LanguageCodes)peer_->getLanguageCode();
}


Locale::CountryCodes Locale::getCountryCode()
{
	return (Locale::CountryCodes)peer_->getCountryCode();
}

UnicodeString Locale::getLanguageName()
{
	UnicodeString result = peer_->getLanguage();

	if ( result.empty() ) {	

		switch ( getLanguageCode() ) {
			case Locale::lcAfar  : {
				result="Afar";
			}
			break;

			case Locale::lcAbkhazian  : {
				result="Abkhazian";
			}
			break;

			case Locale::lcAfrikaans  : {
				result="Afrikaans";
			}
			break;

			case Locale::lcAkan  : {
				result="Akan";
			}
			break;

			case Locale::lcAlbanian  : {
				result="Albanian";
			}
			break;

			case Locale::lcAmharic  : {
				result="Amharic";
			}
			break;

			case Locale::lcArabic  : {
				result="Arabic";
			}
			break;

			case Locale::lcAragonese  : {
				result="Aragonese";
			}
			break;

			case Locale::lcArmenian  : {
				result="Armenian";
			}
			break;

			case Locale::lcAssamese  : {
				result="Assamese";
			}
			break;

			case Locale::lcAvaric  : {
				result="Avaric";
			}
			break;

			case Locale::lcAvestan  : {
				result="Avestan";
			}
			break;

			case Locale::lcAymara  : {
				result="Aymara";
			}
			break;

			case Locale::lcAzerbaijani  : {
				result="Azerbaijani";
			}
			break;

			case Locale::lcBashkir  : {
				result="Bashkir";
			}
			break;

			case Locale::lcBambara  : {
				result="Bambara";
			}
			break;

			case Locale::lcBasque  : {
				result="Basque";
			}
			break;

			case Locale::lcBelarusian  : {
				result="Belarusian";
			}
			break;

			case Locale::lcBengali  : {
				result="Bengali";
			}
			break;

			case Locale::lcBihari  : {
				result="Bihari";
			}
			break;

			case Locale::lcBislama  : {
				result="Bislama";
			}
			break;

			case Locale::lcTibetan  : {
				result="Tibetan";
			}
			break;

			case Locale::lcBosnian  : {
				result="Bosnian";
			}
			break;

			case Locale::lcBreton  : {
				result="Breton";
			}
			break;

			case Locale::lcBulgarian  : {
				result="Bulgarian";
			}
			break;

			case Locale::lcBurmese  : {
				result="Burmese";
			}
			break;

			case Locale::lcCatalan  : {
				result="Catalan";
			}
			break;

			case Locale::lcCzech  : {
				result="Czech";
			}
			break;

			case Locale::lcChamorro  : {
				result="Chamorro";
			}
			break;

			case Locale::lcChechen  : {
				result="Chechen";
			}
			break;

			case Locale::lcChinese  : {
				result="Chinese";
			}
			break;

			case Locale::lcChurchSlavic  : {
				result="ChurchSlavic";
			}
			break;






			case Locale::lcChuvash  : {
				result="Chuvash";
			}
			break;

			case Locale::lcCornish  : {
				result="Cornish";
			}
			break;

			case Locale::lcCorsican  : {
				result="Corsican";
			}
			break;

			case Locale::lcCree  : {
				result="Cree";
			}
			break;

			case Locale::lcWelsh  : {
				result="Welsh";
			}
			break;

			case Locale::lcDanish  : {
				result="Danish";
			}
			break;

			case Locale::lcGerman  : {
				result="German";
			}
			break;

			case Locale::lcDivehi  : {
				result="Divehi";
			}
			break;

			case Locale::lcFlemish  : {
				result="Flemish";
			}
			break;


			case Locale::lcDzongkha  : {
				result="Dzongkha";
			}
			break;

			case Locale::lcGreek  : {
				result="Greek";
			}
			break;

			case Locale::lcEnglish  : {
				result="English";
			}
			break;

			case Locale::lcEsperanto  : {
				result="Esperanto";
			}
			break;

			case Locale::lcEstonian  : {
				result="Estonian";
			}
			break;

			case Locale::lcEwe  : {
				result="Ewe";
			}
			break;

			case Locale::lcFaroese  : {
				result="Faroese";
			}
			break;

			case Locale::lcPersian  : {
				result="Persian";
			}
			break;

			case Locale::lcFijian  : {
				result="Fijian";
			}
			break;

			case Locale::lcFinnish  : {
				result="Finnish";
			}
			break;

			case Locale::lcFrench  : {
				result="French";
			}
			break;

			case Locale::lcFrisian  : {
				result="Frisian";
			}
			break;

			case Locale::lcFulah  : {
				result="Fulah";
			}
			break;

			case Locale::lcGeorgian  : {
				result="Georgian";
			}
			break;

			case Locale::lcGaelic  : {
				result="Gaelic";
			}
			break;


			case Locale::lcIrish  : {
				result="Irish";
			}
			break;

			case Locale::lcGallegan  : {
				result="Gallegan";
			}
			break;

			case Locale::lcManx  : {
				result="Manx";
			}
			break;

			case Locale::lcGuarani  : {
				result="Guarani";
			}
			break;

			case Locale::lcGujarati  : {
				result="Gujarati";
			}
			break;

			case Locale::lcHaitian  : {
				result="Haitian";
			}
			break;


			case Locale::lcHausa  : {
				result="Hausa";
			}
			break;

			case Locale::lcHebrew  : {
				result="Hebrew";
			}
			break;

			case Locale::lcHerero  : {
				result="Herero";
			}
			break;

			case Locale::lcHindi  : {
				result="Hindi";
			}
			break;

			case Locale::lcHiriMotu  : {
				result="HiriMotu";
			}
			break;

			case Locale::lcCroatian  : {
				result="Croatian";
			}
			break;

			case Locale::lcHungarian  : {
				result="Hungarian";
			}
			break;

			case Locale::lcIgbo  : {
				result="Igbo";
			}
			break;

			case Locale::lcIcelandic  : {
				result="Icelandic";
			}
			break;

			case Locale::lcIdo  : {
				result="Ido";
			}
			break;

			case Locale::lcSichuanYi  : {
				result="SichuanYi";
			}
			break;

			case Locale::lcInuktitut  : {
				result="Inuktitut";
			}
			break;

			case Locale::lcInterlingue  : {
				result="Interlingue";
			}
			break;

			case Locale::lcInterlingua  : {
				result="Interlingua";
			}
			break;

			case Locale::lcIndonesian  : {
				result="Indonesian";
			}
			break;

			case Locale::lcInupiaq  : {
				result="Inupiaq";
			}
			break;

			case Locale::lcItalian  : {
				result="Italian";
			}
			break;

			case Locale::lcJavanese  : {
				result="Javanese";
			}
			break;

			case Locale::lcJapanese  : {
				result="Japanese";
			}
			break;

			case Locale::lcKalaallisut  : {
				result="Kalaallisut";
			}
			break;


			case Locale::lcKannada  : {
				result="Kannada";
			}
			break;

			case Locale::lcKashmiri  : {
				result="Kashmiri";
			}
			break;

			case Locale::lcKanuri  : {
				result="Kanuri";
			}
			break;

			case Locale::lcKazakh  : {
				result="Kazakh";
			}
			break;

			case Locale::lcKhmer  : {
				result="Khmer";
			}
			break;

			case Locale::lcKikuyu  : {
				result="Kikuyu";
			}
			break;



			case Locale::lcKinyarwanda  : {
				result="Kinyarwanda";
			}
			break;

			case Locale::lcKirghiz  : {
				result="Kirghiz";
			}
			break;

			case Locale::lcKomi  : {
				result="Komi";
			}
			break;

			case Locale::lcKongo  : {
				result="Kongo";
			}
			break;

			case Locale::lcKorean  : {
				result="Korean";
			}
			break;

			case Locale::lcKuanyama  : {
				result="Kuanyama";
			}
			break;

			case Locale::lcKurdish  : {
				result="Kurdish";
			}
			break;

			case Locale::lcLao  : {
				result="Lao";
			}
			break;

			case Locale::lcLatin  : {
				result="Latin";
			}
			break;

			case Locale::lcLatvian  : {
				result="Latvian";
			}
			break;

			case Locale::lcLimburgan  : {
				result="Limburgan";
			}
			break;




			case Locale::lcLingala  : {
				result="Lingala";
			}
			break;

			case Locale::lcLithuanian  : {
				result="Lithuanian";
			}
			break;

			case Locale::lcLuxembourgish  : {
				result="Luxembourgish";
			}
			break;



			case Locale::lcLubaKatanga  : {
				result="LubaKatanga";
			}
			break;

			case Locale::lcGanda  : {
				result="Ganda";
			}
			break;

			case Locale::lcMacedonian  : {
				result="Macedonian";
			}
			break;

			case Locale::lcMarshallese  : {
				result="Marshallese";
			}
			break;

			case Locale::lcMalayalam  : {
				result="Malayalam";
			}
			break;

			case Locale::lcMaori  : {
				result="Maori";
			}
			break;

			case Locale::lcMarathi  : {
				result="Marathi";
			}
			break;

			case Locale::lcMalay  : {
				result="Malay";
			}
			break;

			case Locale::lcMalagasy  : {
				result="Malagasy";
			}
			break;

			case Locale::lcMaltese  : {
				result="Maltese";
			}
			break;

			case Locale::lcMoldavian  : {
				result="Moldavian";
			}
			break;

			case Locale::lcMongolian  : {
				result="Mongolian";
			}
			break;

			case Locale::lcNauru  : {
				result="Nauru";
			}
			break;

			case Locale::lcNavajo  : {
				result="Navajo";
			}
			break;


			case Locale::lcSouthNdebele  : {
				result="SouthNdebele";
			}
			break;

			case Locale::lcNorthNdebele  : {
				result="NorthNdebele";
			}
			break;

			case Locale::lcNdonga  : {
				result="Ndonga";
			}
			break;

			case Locale::lcNepali  : {
				result="Nepali";
			}
			break;

			case Locale::lcNorwegianNynorsk  : {
				result="NorwegianNynorsk";
			}
			break;

			case Locale::lcNorwegianBokmal  : {
				result="NorwegianBokmal";
			}
			break;

			case Locale::lcNorwegian  : {
				result="Norwegian";
			}
			break;

			case Locale::lcChichewa  : {
				result="Chichewa";
			}
			break;



			case Locale::lcOccitan  : {
				result="Occitan";
			}
			break;


			case Locale::lcOjibwa  : {
				result="Ojibwa";
			}
			break;

			case Locale::lcOriya  : {
				result="Oriya";
			}
			break;

			case Locale::lcOromo  : {
				result="Oromo";
			}
			break;

			case Locale::lcOssetian  : {
				result="Ossetian";
			}
			break;


			case Locale::lcPunjabi  : {
				result="Punjabi";
			}
			break;

			case Locale::lcPali  : {
				result="Pali";
			}
			break;

			case Locale::lcPolish  : {
				result="Polish";
			}
			break;

			case Locale::lcPortuguese  : {
				result="Portuguese";
			}
			break;

			case Locale::lcPushto  : {
				result="Pushto";
			}
			break;

			case Locale::lcQuechua  : {
				result="Quechua";
			}
			break;

			case Locale::lcRaetoRomance  : {
				result="RaetoRomance";
			}
			break;

			case Locale::lcRomanian  : {
				result="Romanian";
			}
			break;

			case Locale::lcRundi  : {
				result="Rundi";
			}
			break;

			case Locale::lcRussian  : {
				result="Russian";
			}
			break;

			case Locale::lcSango  : {
				result="Sango";
			}
			break;

			case Locale::lcSanskrit  : {
				result="Sanskrit";
			}
			break;

			case Locale::lcSerbian  : {
				result="Serbian";
			}
			break;

			case Locale::lcSinhalese  : {
				result="Sinhalese";
			}
			break;

			case Locale::lcSlovak  : {
				result="Slovak";
			}
			break;

			case Locale::lcSlovenian  : {
				result="Slovenian";
			}
			break;

			case Locale::lcNorthernSami  : {
				result="NorthernSami";
			}
			break;

			case Locale::lcSamoan  : {
				result="Samoan";
			}
			break;

			case Locale::lcShona  : {
				result="Shona";
			}
			break;

			case Locale::lcSindhi  : {
				result="Sindhi";
			}
			break;

			case Locale::lcSomali  : {
				result="Somali";
			}
			break;

			case Locale::lcSotho  : {
				result="Sotho";
			}
			break;

			case Locale::lcSpanish  : {
				result="Spanish";
			}
			break;

			case Locale::lcSardinian  : {
				result="Sardinian";
			}
			break;

			case Locale::lcSwati  : {
				result="Swati";
			}
			break;

			case Locale::lcSundanese  : {
				result="Sundanese";
			}
			break;

			case Locale::lcSwahili  : {
				result="Swahili";
			}
			break;

			case Locale::lcSwedish  : {
				result="Swedish";
			}
			break;

			case Locale::lcTahitian  : {
				result="Tahitian";
			}
			break;

			case Locale::lcTamil  : {
				result="Tamil";
			}
			break;

			case Locale::lcTatar  : {
				result="Tatar";
			}
			break;

			case Locale::lcTelugu  : {
				result="Telugu";
			}
			break;

			case Locale::lcTajik  : {
				result="Tajik";
			}
			break;

			case Locale::lcTagalog  : {
				result="Tagalog";
			}
			break;

			case Locale::lcThai  : {
				result="Thai";
			}
			break;

			case Locale::lcTigrinya  : {
				result="Tigrinya";
			}
			break;

			case Locale::lcTonga  : {
				result="Tonga";
			}
			break;

			case Locale::lcTswana  : {
				result="Tswana";
			}
			break;

			case Locale::lcTsonga  : {
				result="Tsonga";
			}
			break;

			case Locale::lcTurkmen  : {
				result="Turkmen";
			}
			break;

			case Locale::lcTurkish  : {
				result="Turkish";
			}
			break;

			case Locale::lcTwi  : {
				result="Twi";
			}
			break;

			case Locale::lcUighur  : {
				result="Uighur";
			}
			break;

			case Locale::lcUkrainian  : {
				result="Ukrainian";
			}
			break;

			case Locale::lcUrdu  : {
				result="Urdu";
			}
			break;

			case Locale::lcUzbek  : {
				result="Uzbek";
			}
			break;

			case Locale::lcVenda  : {
				result="Venda";
			}
			break;

			case Locale::lcVietnamese  : {
				result="Vietnamese";
			}
			break;

			case Locale::lcVolapuk  : {
				result="Volapuk";
			}
			break;

			case Locale::lcWalloon  : {
				result="Walloon";
			}
			break;

			case Locale::lcWolof  : {
				result="Wolof";
			}
			break;

			case Locale::lcXhosa  : {
				result="Xhosa";
			}
			break;

			case Locale::lcYiddish  : {
				result="Yiddish";
			}
			break;

			case Locale::lcYoruba  : {
				result="Yoruba";
			}
			break;

			case Locale::lcZhuang  : {
				result="Zhuang";
			}
			break;

			case Locale::lcZulu  : {
				result="Zulu";
			}
			break;
		}
	}

	return result;
}

int Locale::collate( const UnicodeString& s1, const UnicodeString& s2 )
{
	return peer_->collate( s1, s2 );
}

int Locale::collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 )
{
	return peer_->collateCaseInsensitive( s1, s2 );
}

UnicodeString Locale::toString( const int& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toString( const unsigned int& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toString( const long& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toString( const unsigned long& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toString( const double& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toString( const float& val )
{
	return peer_->toString( val );
}

UnicodeString Locale::toStringFromCurrency( const double& val )
{
	return peer_->toStringFromCurrency( val );
}

UnicodeString Locale::toStringFromDate( const DateTime& val, const UnicodeString& format )
{
	return peer_->toStringFromDate( val, format );
}

UnicodeString Locale::toStringFromTime( const DateTime& val, const UnicodeString& format )
{
	return peer_->toStringFromTime( val, format );
}

int Locale::toInt( const UnicodeString& str )
{
	return peer_->toInt( str );
}

unsigned int Locale::toUInt( const UnicodeString& str )
{
	return peer_->toUInt( str );
}

double Locale::toDouble( const UnicodeString& str )
{
	return peer_->toDouble( str );
}

float Locale::toFloat( const UnicodeString& str )
{
	return peer_->toFloat( str );
}

double Locale::toDoubleAsCurrency( const UnicodeString& str )
{
	return peer_->toDoubleAsCurrency( str );
}

DateTime Locale::toDateTime( const UnicodeString& str )
{
	return peer_->toDateTime( str );
}

UnicodeString Locale::toLowerCase( const UnicodeString& s )
{
	return peer_->toLowerCase( s );
}

UnicodeString Locale::toUpperCase( const UnicodeString& s )
{
	return peer_->toUpperCase( s );
}

UnicodeString Locale::getNumberThousandsSeparator()
{
	return peer_->getNumberThousandsSeparator();
}

UnicodeString Locale::getNumberDecimalPoint()
{
	return peer_->getNumberDecimalPoint();
}

UnicodeString Locale::getNumberGrouping()
{
	return peer_->getNumberGrouping();
}

UnicodeString Locale::getCurrencyDecimalPoint()
{
	return peer_->getCurrencyDecimalPoint();
}

UnicodeString Locale::getCurrencyThousandsSeparator()
{
	return peer_->getCurrencyThousandsSeparator();
}

UnicodeString Locale::getCurrencySymbol()
{
	return peer_->getCurrencySymbol();
}

int Locale::getCurrencyFractionalDigits()
{
	return peer_->getCurrencyFractionalDigits();
}

UnicodeString Locale::getCurrencyPositiveSign()
{
	return peer_->getCurrencyPositiveSign();
}

UnicodeString Locale::getCurrencyNegativeSign()
{
	return peer_->getCurrencyNegativeSign();
}

bool Locale::isCharA( const int32& charTypeMask, const VCFChar& c )
{
	return peer_->isCharA( charTypeMask, c );
}

UnicodeString Locale::translate( const UnicodeString& id )
{



	/**
	Steps:
	1. Get app directory
	2. Look for "Resources" directory. If not found then fail
	3. look for sub directory with same name as locale, i.e.
	we should be able to locate (if we are a english American
	locale) <app dir>/Resources/en_US/
	4. based on the extension of the file name, attempt to get a
	MessageLoader instance.
	If we have a MessageLoader then
		a. Load a text file named <app name>.strings bay calling MessageLoader::loadMessageFile()
		b. call getMessageFromID on the MessageLoader instance

	If we *don't* have a MessageLoader then:
		c. peer_->translate( id )

	The default .strings format:
	Each entry has the following form:

	  entry: " id-string " = " translated-string " ;
		a. whitespace outside of the quotes is ignored.
		b. a comment is for one line, and is preceded by a # character

		example:

		#this is my spanish strings file
		"Hello" = "Hola";
	*/

	UnicodeString result;

	const CommandLine& cmdLine = FoundationKit::getCommandLine();

	FilePath app = cmdLine.getArgument(0);

	String resPath  = System::findResourceDirectory( this );

	UnicodeString resFile = resPath + app.getBaseName() + ".strings";

	if ( System::doesFileExist( resFile ) ) {
		MessageLoader* loader = MessageLoader::getMessageLoader( "text/strings" );

		loader->loadMessageFile( resFile );

		result = loader->getMessageFromID( id );
	}

	return result.empty() ? id : result;
}

UnicodeString Locale::languageCodeToString( LanguageCodes code )
{
	UnicodeString result;

	result.append( 1, (char)((code & 0xFF00) >> 8) );
	result.append( 1, (char)(code & 0xFF) );

	return result;
}

UnicodeString Locale::countryCodeToString( CountryCodes code )
{
	UnicodeString result;

	result.append( 1, (char)((code & 0xFF00) >> 8) );
	result.append( 1, (char)(code & 0xFF) );

	return result;
}


Locale::LanguageCodes Locale::stringToLanguageCode( const UnicodeString& code )
{
	LanguageCodes result;

	result = (LanguageCodes) ((code.at(0) << 8) | code.at(1));

	return result;
}

Locale::CountryCodes Locale::stringToCountryCode( const UnicodeString& code )
{
	CountryCodes result;

	result = (CountryCodes) ((code.at(0) << 8) | code.at(1));

	return result;
}


/**
$Id$
*/
