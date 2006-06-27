//LinuxLocalePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/LinuxLocalePeer.h"
#include "vcf/FoundationKit/DateTime.h"
#include "vcf/FoundationKit/StringTokenizer.h"

#include <monetary.h>

using namespace VCF;

namespace
{
    class LocaleChanger
    {
    public:
        LocaleChanger(locale_t newLocale)
        {
            oldLocale_ = uselocale(newLocale);
        }

        ~LocaleChanger()
        {
            uselocale(oldLocale_);
        }
    private:
        locale_t oldLocale_;
    };
}

LinuxLocalePeer::LinuxLocalePeer() :
locale_(NULL)
{
    // use C locale by default
    locale_ = newlocale(LC_ALL_MASK, "C", NULL);
}

LinuxLocalePeer::~LinuxLocalePeer()
{
	if(locale_ != NULL && 
	   locale_ != LC_GLOBAL_LOCALE)
	{
		freelocale(locale_);
	}
}

void LinuxLocalePeer::setLocale( const UnicodeString& language,
                                 const UnicodeString& country,
                                 const UnicodeString& variant )
{
    if(locale_ != NULL &&
	   locale_ != LC_GLOBAL_LOCALE) {
        freelocale(locale_);
		locale_ = NULL;
    }
	if ( language.empty() && country.empty() ) {
        locale_ = newlocale(LC_ALL_MASK, "", NULL);
    }
	else {
        locale_ = newlocale(LC_ALL_MASK, (language+"_"+country+(variant.empty() ? "" : "."+variant)).ansi_c_str(), NULL);
    }
}

int LinuxLocalePeer::collate( const UnicodeString& s1, const UnicodeString& s2 )
{
	return wcscoll_l(s1.c_str(), s2.c_str(), locale_);
}

int LinuxLocalePeer::collateCaseInsensitive( const UnicodeString& s1,
                                             const UnicodeString& s2 )
{
	return collate(toLowerCase(s1), toLowerCase(s2));
}

UnicodeString LinuxLocalePeer::toString( const int& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'i", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toString( const unsigned int& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'u", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toString( const long& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'li", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toString( const unsigned long& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'lu", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toString( const double& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'f", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toString( const float& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    wchar_t buf[bufsize] = {0};
    swprintf(buf, sizeof(buf), L"%'f", val); 
    UnicodeString result = buf;
    return result;
}

UnicodeString LinuxLocalePeer::toStringFromCurrency( const double& val )
{
    LocaleChanger loc(locale_);
    const int bufsize = 100;
    char buf[bufsize] = {0};
    strfmon(buf, sizeof(buf), "%n", val); 
	UnicodeString result = buf;
	return result;
}

int LinuxLocalePeer::toInt( const UnicodeString& str )
{
    LocaleChanger loc(locale_);
	int result;
    swscanf(str.c_str(), L"%'i", &result);
	return result;
}

unsigned int LinuxLocalePeer::toUInt( const UnicodeString& str )
{
    LocaleChanger loc(locale_);
    unsigned int result;
    swscanf(str.c_str(), L"%'u", &result);
    return result;
}

double LinuxLocalePeer::toDouble( const UnicodeString& str )
{
    LocaleChanger loc(locale_);
	double result;
    swscanf(str.c_str(), L"%'f", &result);
	return result;
}

float LinuxLocalePeer::toFloat( const UnicodeString& str )
{
    LocaleChanger loc(locale_);
    float result;
    swscanf(str.c_str(), L"%'f", &result);
    return result;
}

double LinuxLocalePeer::toDoubleAsCurrency( const UnicodeString& str )
{
    LocaleChanger loc(locale_);
    float result;
    swscanf(str.c_str(), L"%'f", &result);
    return result;
}

UnicodeString LinuxLocalePeer::toLowerCase( const UnicodeString& s )
{
    LocaleChanger loc(locale_);
	UnicodeString result;
    for(size_t i=0; i<s.size(); ++i)
    {
        result += (UnicodeString::UniChar)towlower(s[i]);
    }
	return result;
}

UnicodeString LinuxLocalePeer::toUpperCase( const UnicodeString& s )
{
    LocaleChanger loc(locale_);
    UnicodeString result;
    for(size_t i=0; i<s.size(); ++i)
    {
        result += (UnicodeString::UniChar)towupper(s[i]);
    }
    return result;
}

UnicodeString LinuxLocalePeer::getNumberThousandsSeparator()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(THOUSEP);
	return result;
}

UnicodeString LinuxLocalePeer::getNumberDecimalPoint()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(DECIMAL_POINT);
	return result;
}

UnicodeString LinuxLocalePeer::getNumberGrouping()
{
    LocaleChanger loc(locale_);

	char *grouping = nl_langinfo(GROUPING);
	UnicodeString result;
    size_t i = 0;
    bool cont = grouping[i] != 0 && grouping[i] != CHAR_MAX;
    while(cont)
    {
        result += Format("%i") % grouping[i];
        ++i;
        cont = grouping[i] != 0 && grouping[i] != CHAR_MAX;
        if(cont)
        {
            result += ";";
        }
    }
	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyDecimalPoint()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(MON_DECIMAL_POINT);
	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyThousandsSeparator()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(MON_THOUSANDS_SEP);
	return result;
}

UnicodeString LinuxLocalePeer::getCurrencySymbol()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(CURRENCY_SYMBOL);
	return result;
}

int LinuxLocalePeer::getCurrencyFractionalDigits()
{
    LocaleChanger loc(locale_);
	int result = *nl_langinfo(FRAC_DIGITS);
	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyPositiveSign()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(POSITIVE_SIGN);
	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyNegativeSign()
{
    LocaleChanger loc(locale_);
	UnicodeString result = nl_langinfo(NEGATIVE_SIGN);
	return result;
}

bool LinuxLocalePeer::isCharA( const int32& charTypeMask, const VCFChar& c )
{
    LocaleChanger loc(locale_);
    int32 mask = 0;
	if ( charTypeMask & ctSpace ) {
		if ( ::isspace( c ) ) {
			mask |= ctSpace;
		}
	}

	if ( charTypeMask & ctPrint ) {
		if ( ::isprint( c ) ) {
			mask |= ctPrint;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( ::isprint( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( ::iscntrl( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctUpper ) {
		if ( ::isupper( c ) ) {
			mask |= ctUpper;
		}
	}

	if ( charTypeMask & ctLower ) {
		if ( ::islower( c ) ) {
			mask |= ctLower;
		}
	}

	if ( charTypeMask & ctDigit ) {
		if ( ::isdigit( c ) ) {
			mask |= ctDigit;
		}
	}

	if ( charTypeMask & ctPunct ) {
		if ( ::ispunct( c ) ) {
			mask |= ctPunct;
		}
	}

	if ( charTypeMask & ctHexDigit ) {
		if ( ::isxdigit( c ) ) {
			mask |= ctHexDigit;
		}
	}

	if ( charTypeMask & ctAlpha ) {
		if ( ::isalpha( c ) ) {
			mask |= ctAlpha;
		}
	}

	if ( charTypeMask & ctAlphaNumeric ) {
		if ( ::isalnum( c ) ) {
			mask |= ctAlphaNumeric;
		}
	}

	if ( charTypeMask & ctGraph ) {
		if ( ::isgraph( c ) ) {
			mask |= ctGraph;
		}
	}

	return ( 0 == mask ) ? false : true;
}

UnicodeString LinuxLocalePeer::translate( const UnicodeString& id )
{
    LocaleChanger loc(locale_);
	return "";
}

UnicodeString LinuxLocalePeer::toStringFromDate( const DateTime& val, const UnicodeString& format )
{
    LocaleChanger loc(locale_);
    UnicodeString tmpFormat = format;
    if(tmpFormat.empty())
    {
        tmpFormat = "%x";
    }
	UnicodeString result;
    time_t time = val.getCTime();
    struct tm* ltime = localtime(&time);
    wchar_t buf[100];
    wcsftime(buf, sizeof(buf), tmpFormat.c_str(), ltime);
    result = buf;
	return result;
}

UnicodeString LinuxLocalePeer::toStringFromTime( const DateTime& val, const UnicodeString& format )
{
    LocaleChanger loc(locale_);
    UnicodeString tmpFormat = format;
    if(tmpFormat.empty())
    {
        tmpFormat = "%X";
    }
    UnicodeString result;
    time_t time = val.getCTime();
    struct tm* ltime = localtime(&time);
    wchar_t buf[100];
    wcsftime(buf, sizeof(buf), tmpFormat.c_str(), ltime);
    result = buf;
    return result;
}

namespace 
{
    const char* GetLocaleName(locale_t loc)
    {
        // 0 element is good as any.
        return loc->__names[0];
    }

    UnicodeString GetCountryOrLanguage(const char* origlocaleName, int lORc)
    {
        UnicodeString result;
        // this might not be necessary
        char* tmpLocaleName = strdup(origlocaleName);
        char* language = strtok(tmpLocaleName, "_");
        if(language != NULL)
        {
            char* country = strtok(NULL, "_");
            if(country != NULL)
            {
                if(lORc == 0)
                {
                    result = language;    
                }
                else if(lORc == 1)
                {
                    result = country;
                }
            }
        }
        free(tmpLocaleName);
        return result;
    }

    inline
    UnicodeString GetCountryName(locale_t loc)
    {
        return GetCountryOrLanguage(GetLocaleName(loc), 1);
    }

    inline
    UnicodeString GetLanguageName(locale_t loc)
    {
        return GetCountryOrLanguage(GetLocaleName(loc), 0);
    }
}

uint32 LinuxLocalePeer::getLanguageCode()
{
    return Locale::stringToLanguageCode(GetLanguageName(locale_));
}

uint32 LinuxLocalePeer::getCountryCode()
{
    return Locale::stringToCountryCode(GetCountryName(locale_));
}

String LinuxLocalePeer::getLanguage()
{
	//JC - I added this, it's blank for now - 
	//the Locale class will simply return an english
	//version of the name. Ideally we'd like to see the 
	//localized version of the language name here
	String result;
	return result;
}


/**
$Id$
*/
