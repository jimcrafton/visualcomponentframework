#ifndef _VCF_OSXLOCALEPEER_H__
#define _VCF_OSXLOCALEPEER_H__
//OSXLocalePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

typedef std::pair<int,int> AppleLocalePair;


class OSXLocalePeer : public LocalePeer {
public:
	OSXLocalePeer();

	virtual ~OSXLocalePeer();

	virtual void setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant );

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
		return (OSHandleID)localeRef_;
	}
protected:

    static std::map<String,AppleLocalePair> localeMaping;
	CFLocaleRef localeRef_;	
	LocaleRef collateLocaleRef_;
	CFNumberFormatterRef integerNumFormatterRef_;
	CFNumberFormatterRef realNumFormatterRef_;
	CFNumberFormatterRef currencyNumFormatterRef_;
	UnicodeString crtLocaleStr_;
	

};




};


#endif // _VCF_OSXLOCALEPEER_H__

/**
$Id$
*/
