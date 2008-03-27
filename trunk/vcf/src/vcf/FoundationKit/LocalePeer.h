#ifndef _VCF_LOCALEPEER_H__
#define _VCF_LOCALEPEER_H__
//LocalePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {




enum CharacterType{
	ctSpace = 0x1,
	ctPrint = 0x2,
	ctCntrl = 0x04,
	ctUpper = 0x500,
	ctLower = 0x600,
	ctDigit = 0x10,
	ctPunct = 0x20,
	ctHexDigit = 0x40,
	ctAlpha = 0x08,
	ctAlphaNumeric = ctDigit | ctAlpha,
	ctGraph = ctAlphaNumeric | ctPunct
};

class DateTime;


/**
\class LocalePeer LocalePeer.h "vcf/FoundationKit/LocalePeer.h"
*/
class FOUNDATIONKIT_API LocalePeer {
public:
	virtual ~LocalePeer(){}

	/**
	Sets the locale specified by the langauge and country code.
	If language, country, and variant are empty, then the peer
	must use the current locale of the system.
	*/
	virtual void setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant ) = 0;

	virtual void setToCurrentThread() = 0;

	virtual uint32 getLanguageCode() = 0;
	virtual uint32 getCountryCode() = 0;

	virtual String getLanguage() = 0;

	virtual int collate( const UnicodeString& s1, const UnicodeString& s2 ) = 0;
	virtual int collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 ) = 0;

	virtual UnicodeString toString( const int& val ) = 0;
	virtual UnicodeString toString( const unsigned int& val ) = 0;
	virtual UnicodeString toString( const long& val ) = 0;
	virtual UnicodeString toString( const unsigned long& val ) = 0;
	virtual UnicodeString toString( const double& val ) = 0;
	virtual UnicodeString toString( const float& val ) = 0;

	virtual UnicodeString toStringFromDate( const DateTime& val, const UnicodeString& format ) = 0;
	virtual UnicodeString toStringFromTime( const DateTime& val, const UnicodeString& format ) = 0;

	virtual UnicodeString toStringFromCurrency( const double& val ) = 0;

	virtual int toInt( const UnicodeString& str ) = 0;
	virtual unsigned int toUInt( const UnicodeString& str ) = 0;
	virtual double toDouble( const UnicodeString& str ) = 0;
	virtual float toFloat( const UnicodeString& str ) = 0;
	virtual double toDoubleAsCurrency( const UnicodeString& str ) = 0;
	virtual DateTime toDateTime( const UnicodeString& str ) = 0;

	virtual UnicodeString toLowerCase( const UnicodeString& s ) = 0;
	virtual UnicodeString toUpperCase( const UnicodeString& s ) = 0;

	virtual UnicodeString getNumberThousandsSeparator() = 0;
	virtual UnicodeString getNumberDecimalPoint() = 0;
	virtual UnicodeString getNumberGrouping() = 0;
	virtual UnicodeString getCurrencyDecimalPoint() = 0;
	virtual UnicodeString getCurrencyThousandsSeparator() = 0;
	virtual UnicodeString getCurrencySymbol() = 0;
	virtual int getCurrencyFractionalDigits() = 0;
	virtual UnicodeString getCurrencyPositiveSign() = 0;
	virtual UnicodeString getCurrencyNegativeSign() = 0;

	virtual bool isCharA( const int32& charTypeMask, const VCFChar& c ) = 0;

	virtual UnicodeString translate( const UnicodeString& id ) = 0;

	/**
	returns a handler or otehr numeric identifier for hte locale. For Win32
	systems this will be the LCID value of the locale
	*/
	virtual OSHandleID getHandleID() = 0;
};

};


#endif // _VCF_LOCALEPEER_H__

/**
$Id$
*/
