#ifndef _VCF_ENUM_H__
#define _VCF_ENUM_H__
//Enum.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Enum.h:



namespace VCF
{

/**
*the Enum class is used to wrap C++ enum types,
*allowing the user to iterate forward and backward
*through the enum type. This works best with enums
*that have members whose value changes in intervals
*of 1.
*/
class FOUNDATIONKIT_API Enum : public Object{
public:
	Enum(){};

	virtual ~Enum(){};

	/**
	*moves to the next value.
	*When the end of the enum is reached
	*it cycles back to the begining
	*@return int the int value of the enum
	*/
	virtual int next() = 0;

	/**
	*Moves to the last value of the enum
	*@return int the int value of the enum
	*/
	virtual int end() = 0;

	/**
	*gets the current value of the enum
	*@return int the int value of the enum
	*/
	virtual int get() = 0;

	/**
	*Moves to the first value of the enum
	*@return int the int value of the enum
	*/
	virtual int begin() = 0;

	/**
	*Sets the current value of the enum
	*@return int the int value of the enum
	*/
	virtual void set( const int& intVal ) = 0;

	operator int (){
		return get();
	};

	/**
	*sets the enum val from a string. The default behaviour
	*is to assume the string represents an integer (i.e. "1" or "3")
	*if this is not the case then the enum wil be set to 0 value
	*/
	virtual void setFromString( const String& textVal ){
		set( StringUtils::fromStringAsInt( textVal ) );
	};
};





class FOUNDATIONKIT_API EnumValue {
public:
	Enum* getEnum() const {
		if ( NULL != enum_ ) {
			enum_->set( enumValue_ );
		}
		return enum_;
	}

	int getEnumVal() const {
		return 	enumValue_;
	}

	void set( const EnumValue& enumVal ) {
		enum_ = enumVal.enum_;
		if ( NULL != enum_ ) {
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

	void set( const String& stringVal ) {
		if ( NULL != enum_ ) {
			enum_->setFromString( stringVal );
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

	void set( Enum* enumVal ) {
		enum_ = enumVal;
		if ( NULL != enum_ ) {
			enumValue_ = enum_->get();
		}
		else {
			enumValue_ = 0;
		}
	}

protected:
	int enumValue_;
	Enum* enum_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/18 14:16:09  marcelloptr
*added some const specifiers
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:47  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 17:57:15  ddiego
*more merge changes - rtti code that was in the dev
*branch apparently didn't make it over to the stable branch.
*
*Revision 1.1.2.2  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.1.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.14  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.13  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.2.1  2003/03/12 03:11:49  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.14.1  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.11  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.10.4.2  2002/04/27 15:52:21  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.10.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.10  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ENUM_H__


