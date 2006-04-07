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

	virtual ulong32 getLanguageCode() = 0;
	virtual ulong32 getCountryCode() = 0;

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

	virtual bool isCharA( const long& charTypeMask, const VCFChar& c ) = 0;

	virtual UnicodeString translate( const UnicodeString& id ) = 0;

	/**
	returns a handler or otehr numeric identifier for hte locale. For Win32
	systems this will be the LCID value of the locale
	*/
	virtual OSHandleID getHandleID() = 0;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/23 05:15:39  ddiego
*fix to localize the locale language name.
*
*Revision 1.3.2.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.2.2.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 04:08:43  ddiego
*updates some missing locale impl files
*
*/


#endif // _VCF_LOCALEPEER_H__


