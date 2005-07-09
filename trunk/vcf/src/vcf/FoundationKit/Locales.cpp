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
	UnicodeString result ;

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
	return peer_->toString( val );
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

bool Locale::isCharA( const long& charTypeMask, const VCFChar& c )
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

	CommandLine cmdLine = FoundationKit::getCommandLine();

	FilePath app = cmdLine.getArgument(0);

	String resPath  = System::findResourceDirectory( this );

	UnicodeString resFile = resPath + app.getBaseName() + ".strings";

	if ( System::doesFileExist( resFile ) ) {
		MessageLoader* loader = MessageLoader::getMessageLoader( "text/strings" );

		loader->loadMessageFile( resFile );

		result = loader->getMessageFromID( id );
	}



	//MessageLoader::loadMessageFile



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
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/06/08 03:27:27  ddiego
*fix for popup menus
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.4  2004/07/22 04:18:59  ddiego
*fixed bug 995642 delete LoalePeer in Locale, and added some miscellaneous changes to the QTPlayer. Also fixing (not finished yet) a bug that
*prevents the TreePeer from being properly notified when the tree model's
*item is deleted.
*
*Revision 1.1.2.3  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.12  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.4.1  2004/02/15 20:24:02  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.11  2003/08/09 02:56:45  ddiego
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
*Revision 1.10.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.16.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.16.1  2003/03/12 03:13:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.8  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


