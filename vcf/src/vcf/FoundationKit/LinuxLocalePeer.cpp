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



using namespace VCF;



LinuxLocalePeer::LinuxLocalePeer()
{

}

void LinuxLocalePeer::setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant )
{
	if ( language.empty() && country.empty() ) {

	}
	else {

	}
}

int LinuxLocalePeer::collate( const UnicodeString& s1, const UnicodeString& s2 )
{
	return 0;
}


int LinuxLocalePeer::collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 )
{
	return 0;
}


UnicodeString LinuxLocalePeer::toString( const int& val )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toString( const unsigned int& val )
{
	UnicodeString result;
	return result;
}

UnicodeString LinuxLocalePeer::toString( const long& val )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toString( const unsigned long& val )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toString( const double& val )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toString( const float& val )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toStringFromCurrency( const double& val )
{
	UnicodeString result;

	return result;
}




int LinuxLocalePeer::toInt( const UnicodeString& str )
{
	int result;
	return result;
}

unsigned int LinuxLocalePeer::toUInt( const UnicodeString& str )
{
	unsigned int result;

	return result;
}

double LinuxLocalePeer::toDouble( const UnicodeString& str )
{
	double result;


	return result;
}

float LinuxLocalePeer::toFloat( const UnicodeString& str )
{
	float result;


	return result;
}

double LinuxLocalePeer::toDoubleAsCurrency( const UnicodeString& str )
{
	double result;


	return result;
}



UnicodeString LinuxLocalePeer::toLowerCase( const UnicodeString& s )
{
	UnicodeString result;


	return result;
}

UnicodeString LinuxLocalePeer::toUpperCase( const UnicodeString& s )
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getNumberThousandsSeparator()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getNumberDecimalPoint()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getNumberGrouping()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyDecimalPoint()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyThousandsSeparator()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getCurrencySymbol()
{
	UnicodeString result;

	return result;
}

int LinuxLocalePeer::getCurrencyFractionalDigits()
{
	int result = 0;

	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyPositiveSign()
{
	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::getCurrencyNegativeSign()
{
	UnicodeString result;

	return result;
}

bool LinuxLocalePeer::isCharA( const long& charTypeMask, const VCFChar& c )
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

UnicodeString LinuxLocalePeer::translate( const UnicodeString& id )
{
	return "";
}

UnicodeString LinuxLocalePeer::toStringFromDate( const DateTime& val, const UnicodeString& format )
{

	UnicodeString result;

	return result;
}

UnicodeString LinuxLocalePeer::toStringFromTime( const DateTime& val, const UnicodeString& format )
{
	UnicodeString result;

	return result;
}

ulong32 LinuxLocalePeer::getLanguageCode()
{
	return 0;

}



ulong32 LinuxLocalePeer::getCountryCode()
{

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.2  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 05:38:10  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:08:44  ddiego
*updates some missing locale impl files
*
*/


