#ifndef _VCF_WIN32SYSTEMPEER_H__
#define _VCF_WIN32SYSTEMPEER_H__
//Win32SystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32SystemPeer.h: interface for the Win32SystemPeer class.





namespace VCF {
class Win32ResourceBundle;

class Win32SystemPeer : public SystemPeer {
public:
	Win32SystemPeer();
	virtual ~Win32SystemPeer();

	virtual unsigned long getTickCount();

	virtual void sleep( const uint32& milliseconds );

	virtual bool doesFileExist( const String& fileName );

	virtual String getEnvironmentVariable( const String& variableName );

	virtual String getCurrentWorkingDirectory();

	virtual void setEnvironmentVariable( const String& variableName, const String& newValue );

	virtual void addPathDirectory( const String& directory );

	virtual void setCurrentWorkingDirectory( const String& currentDirectory );

	virtual void setDateToSystemTime( DateTime* date );

	virtual void setDateToLocalTime( DateTime* date );

	virtual void setCurrentThreadLocale( Locale* locale );

	virtual bool isUnicodeEnabled();

	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date );	

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date );
	
	virtual String getOSName();

	virtual String getOSVersion();

	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName );
protected:
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:24  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2.2.3  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.2  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.15.2.2  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.15  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.3  2004/03/21 00:39:22  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.2.2  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.13.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.13  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.1  2002/12/27 23:04:42  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.4.1  2002/09/18 21:50:56  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.9  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.6.1  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.8  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32SYSTEMPEER_H__


