#ifndef _VCF_LINUXLOCALEPEER_H__
#define _VCF_LINUXLOCALEPEER_H__ 
//LinuxLocalePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxLocalePeer : public LocalePeer
{
public:
	LinuxLocalePeer();


	virtual void setLocale( const UnicodeString& language,
	                        const UnicodeString& country,
	                        const UnicodeString& variant );

	virtual ulong32 getLanguageCode();
	virtual ulong32 getCountryCode();

	virtual int collate( const UnicodeString& s1, const UnicodeString& s2 );
	virtual int collateCaseInsensitive( const UnicodeString& s1,
	                                    const UnicodeString& s2 );

	virtual UnicodeString toString( const int& val );
	virtual UnicodeString toString( const unsigned int& val );
	virtual UnicodeString toString( const long& val );
	virtual UnicodeString toString( const unsigned long& val );
	virtual UnicodeString toString( const double& val );
	virtual UnicodeString toString( const float& val );

	virtual UnicodeString toStringFromDate( const DateTime& val,
	                                        const UnicodeString& format );

	virtual UnicodeString toStringFromTime( const DateTime& val,
	                                        const UnicodeString& format );


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
		return (OSHandleID)0;
	}
protected:
	UnicodeString crtLocaleStr_;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:03  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2.4.1  2005/04/17 16:11:31  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/16 05:38:08  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.1.2.1  2004/02/16 04:08:44  ddiego
*updates some missing locale impl files
*
*/


#endif // _VCF_LINUXLOCALEPEER_H__


