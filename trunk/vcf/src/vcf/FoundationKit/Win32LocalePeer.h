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

	virtual ulong32 getLanguageCode();
	virtual ulong32 getCountryCode();

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

	virtual bool isCharA( const long& charTypeMask, const VCFChar& c );

	virtual UnicodeString translate( const UnicodeString& id );

	virtual OSHandleID getHandleID() {
		return (OSHandleID)lcid_;
	}
protected:
	UnicodeString changeToGenericNumberString( const UnicodeString& str );
	void initNumberFormatForIntW( NUMBERFMTW& fmt );
	void initNumberFormatForIntA( NUMBERFMTA& fmt );
	void initNumberFormatForFloatW( NUMBERFMTW& fmt );
	void initNumberFormatForFloatA( NUMBERFMTA& fmt );
	LCID lcid_;
	UnicodeString crtLocaleStr_;

	static std::map<String,int> langIDs;
	static std::map<String,int> countryIDs;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:24  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.2  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 04:08:44  ddiego
*updates some missing locale impl files
*
*/


#endif // _VCF_WIN32LOCALEPEER_H__


