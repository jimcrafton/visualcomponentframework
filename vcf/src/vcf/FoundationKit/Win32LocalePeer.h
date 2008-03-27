#ifndef _VCF_WIN32LOCALEPEER_H__
#define _VCF_WIN32LOCALEPEER_H__
//Win32LocalePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class Win32LocalePeer : public LocalePeer {
public:
	Win32LocalePeer();


	virtual void setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant );

	virtual void setToCurrentThread();

	virtual uint32 getLanguageCode();
	virtual uint32 getCountryCode();

	virtual String getLanguage();

	virtual int collate( const UnicodeString& s1, const UnicodeString& s2 );
	virtual int collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 );

	virtual UnicodeString toString( const int& val );
	virtual UnicodeString toString( const unsigned int& val );
	virtual UnicodeString toString( const long& val );
	virtual UnicodeString toString( const unsigned long& val );
	virtual UnicodeString toString( const double& val );
	virtual UnicodeString toString( const float& val );

	virtual UnicodeString toStringFromDate( const DateTime& val, const UnicodeString& format );
	virtual UnicodeString toStringFromTime( const DateTime& val, const UnicodeString& format );


	virtual UnicodeString toStringFromCurrency( const double& val );

	virtual int toInt( const UnicodeString& str );
	virtual unsigned int toUInt( const UnicodeString& str );
	virtual double toDouble( const UnicodeString& str );
	virtual float toFloat( const UnicodeString& str );
	virtual double toDoubleAsCurrency( const UnicodeString& str );
	virtual DateTime toDateTime( const UnicodeString& str );

	virtual UnicodeString toLowerCase( const UnicodeString& s );
	virtual UnicodeString toUpperCase( const UnicodeString& s );

	virtual UnicodeString getNumberThousandsSeparator();
	virtual UnicodeString getNumberDecimalPoint();
	virtual UnicodeString getNumberGrouping();
	virtual UnicodeString getCurrencyDecimalPoint();
	virtual UnicodeString getCurrencyThousandsSeparator();
	virtual UnicodeString getCurrencySymbol();
	virtual int getCurrencyFractionalDigits();
	virtual UnicodeString getCurrencyPositiveSign();
	virtual UnicodeString getCurrencyNegativeSign();

	virtual bool isCharA( const int32& charTypeMask, const VCFChar& c );

	virtual UnicodeString translate( const UnicodeString& id );

	virtual OSHandleID getHandleID() {
		return (OSHandleID)UIntToPtr( (uintptr)lcid_ );
	}
protected:
	UnicodeString changeToGenericNumberString( const UnicodeString& str );
	void initNumberFormatForIntW( NUMBERFMTW& fmt );
	void initNumberFormatForIntA( NUMBERFMTA& fmt );
	void initNumberFormatForFloatW( NUMBERFMTW& fmt );
	void initNumberFormatForFloatA( NUMBERFMTA& fmt );
	LCID lcid_;
	AnsiString crtLocaleStr_;

	static std::map<AnsiString,int> langIDs;
	static std::map<AnsiString,int> countryIDs;
};




};


#endif // _VCF_WIN32LOCALEPEER_H__

/**
$Id$
*/
