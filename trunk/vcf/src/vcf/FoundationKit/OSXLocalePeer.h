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
		return (OSHandleID)localeRef_;
	}
protected:

    static std::map<String,AppleLocalePair> localeMaping;
    LocaleRef localeRef_;
	UnicodeString crtLocaleStr_;
};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/08 20:52:47  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*Revision 1.1.2.1  2004/02/16 05:38:08  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:08:44  ddiego
*updates some missing locale impl files
*
*/


#endif // _VCF_OSXLOCALEPEER_H__


