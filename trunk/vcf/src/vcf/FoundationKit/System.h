#ifndef _VCF_SYSTEM_H__
#define _VCF_SYSTEM_H__
//System.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class SystemPeer;

class ErrorLog;

class BasicException;

class DateTime;

class Locale;


/**
*The System object represents basic lower level OS functions
*/
class FOUNDATIONKIT_API System : public Object {
public:
	static System* create();

	static void terminate();

	System();
	virtual ~System();

	static unsigned long getTickCount();

	static void sleep( const uint32& milliseconds );

	/**
	*sets the System's ErrorLog.
	*Note the Errolog is NOT owned by the System,
	*so it is the caller's responsibility to clean up the
	*memory. The suggested use is to create an ErrorLog
	*object on the stack in your main() function and
	*then pass it to the System after initialization of the
	*FoundationKit is done (i.e. after initFoundationKit() )
	*/
	static void setErrorLog( ErrorLog* errorLog );

	/**
	\par
	Prints out the text to stdout. Allows for formatted text, just like printf() does.
	Please see printf documentation for the various formatting flags.
	\par
	When using this to print out strings, there are some special rules to fullow
	due to the fact that the VCF uses all unicode strings internally. For
	example:
	\code
	String aName = "Bob Jones";
	System::print( "User Name: %s", aName.c_str() );
	\endcode
	On Win32 platforms the use of %s will work fine, but on others it may 
	not. To ensure that strings get printed out correctly, consider using the 
	%ls formatter, like so:
	\code
	String aName = "Bob Jones";
	System::print( "User Name: %ls", aName.c_str() );
	\endcode
	This will ensure that on all platforms the unicode string gets properly
	handled and output.
	*/
	static void print( String text, ... );

	/**
	@see System::print
	*/
	static void println( String text, ... );

	/**
	This will print the contents of the exception to stdout and the 
	error log if it exists.
	*/
	static void errorPrint( BasicException* exception );

	static bool doesFileExist( const String& fileName );

	/**
	This will return the value of the specified environment variable.
	For example, calling this on a Win32 system might return the following:
	\code
	String val = System::getEnvironmentVariable( "PATH" );	
	\endcode
	val would equal "C:\WINNT\system32;C:\WINNT;C:\WINNT\System32\Wbem;d:\Program Files\doxygen\bin;E:\dm\bin;E:\code\vcfdev\dev\vcf\bin;D:\Program Files\HTML Help Workshop;D:\cygwin\bin;D:\Program Files\Microsoft Visual Studio\Common\Tools\WinNT;D:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin;D:\Program Files\Microsoft Visual Studio\Common\Tools;D:\Program Files\Microsoft Visual Studio\VC98\bin;D:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\IDE".
	*/
	static String getEnvironmentVariable( const String& variableName );

	static String getCurrentWorkingDirectory();

	static void setCurrentWorkingDirectory( const String& currentDirectory );

	/**
	Sets the date instance to the current system time (UTC based).
	*/
	static void setDateToSystemTime( DateTime* date );

	/**
	Sets the date instance to the current <b>local</b> time. This may be different
	from the result of calling System::setDateToSystemTime().
	*/
	static void setDateToLocalTime( DateTime* date );

	/**
	This will convert a date in UTC to that of the system's local time zone,
	taking into account the system time zone, and DST if neccessary.
	*/
	static DateTime convertUTCTimeToLocalTime( const DateTime& date );	

	/**
	This will convert a date in the system's local time to UTC,
	taking into account the system time zone, and DST if neccessary.
	*/	
	static DateTime convertLocalTimeToUTCTime( const DateTime& date );

	/**
	Sets the current thread's locale. May not have an impact on some systems.
	*/
	static void setCurrentThreadLocale( Locale* locale );

	/**
	Returns the current thread's locale. This may be the same as the current user locale on 
	systems that do not allow per thread locale settings (such as Mac OSX).
	*/
	static Locale* getCurrentThreadLocale();

	/**
	Is the system Unicode enabled, i.e. does it support the use of Unicode string in API calls. 
	For example, if the VCF is running on a Win32 system on Windows 98 or Windows ME, this will 
	return false. On a Win32 system that is NT based (Windows NT 4.0, Windows 2000, or 
	Windows XP) this will return true. For Mac OSX this always returns true.
	*/
	static bool isUnicodeEnabled();
private:
	SystemPeer* systemPeer_;
	static System* systemInstance;

	ErrorLog* errorLogInstance_;

	Locale* locale_;
	bool unicodeEnabled_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.17.2.2  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.17.2.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.17  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.16  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.15.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.15.2.3  2004/03/21 00:39:22  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.15.2.2  2004/02/15 20:24:01  ddiego
*intial Locales implementation is now checked in. This adds several new classes, namely:
*The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
*The Locale class which provides locale support for the vcf
*The Win32LocalePeer which provides a basic Win32 implementation for locale support
*The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
*The TextCodec class which allows for custom text codec for encoding or decoding text.
*The MessageLoader class which is used to provide localized string translation
*The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
*Revision 1.15.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.15  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.2.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.14  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.13.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.13  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.1  2003/03/12 03:11:51  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.2  2003/01/05 03:25:11  cesarmello
*added method: System::println
*
*Revision 1.11.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.4.1  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.10  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.12.1  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SYSTEM_H__


