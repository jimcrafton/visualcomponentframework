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
class ResourceBundle;
class Format;

/**
\class System System.h "vcf/FoundationKit/System.h"
The System object represents basic lower level OS functions. 
The System instance is a singleton, and may not be created or 
deleted directly. Instead the FunctionKit::init() and FoundationKit::terminate()
take of this for you. You interact with it by calling the various 
static methods of the class, which in turn call the proper 
System peer implementation.
*/
class FOUNDATIONKIT_API System : public Object {
public:
	
	/**
	This enum is used to represent various 
	identifiers for common directories
	on the system. These each represent a 
	valid file path, or an empty string if
	there is no such equivalent for the
	platform. 
	@see getCommonDirectory()
	*/
	enum CommonDirectory {
		/**
		This is the home directory for the current user
		account that the framework is being executed
		from.
		*/
		cdUserHome = 0,

		/**
		This is the directory for storing application
		specific data for the current user
		account that the framework is being executed
		from.
		*/
		cdUserProgramData,

		/**
		This is the directory that represents the
		desktop for the current user
		account that the framework is being executed
		from.
		*/
		cdUserDesktop,

		/**
		This is the directory that represents
		where the user would store "favorites" (typically
		bookmarks, and the like) for the current user
		account that the framework is being executed
		from.
		*/
		cdUserFavorites,

		/**
		This is the directory that represents
		where the user would store their documents (by default)
		for the current user account that the framework 
		is being executed from.
		*/
		cdUserDocuments,

		/**
		This is the temp (or "scratch") directory for the current user
		account that the framework is being executed
		from.
		*/
		cdUserTemp,		

		/**
		This is the default, top level directory that the system
		stores programs/applications in. On Win32 this generally
		"C:\Program Files\". On Mac OSX this would generally be 
		"/Applications/".
		*/
		cdSystemPrograms,

		/**
		This is the system temp directory.
		*/
		cdSystemTemp,

		/**
		This is the system root directory.
		*/
		cdSystemRoot
	};

	/**
	This is for internal usage only - don't call
	*/
	static System* create();

	/*
	This is for internal usage only - don't call
	*/
	static void terminate();

	/**
	Locates the resource directory, if possible.
	Possible search patterns

	A): Dead simple

	\code
	<app>.app/
		<app>.exe
		Resources/
			button.png			<-----generic files - not localized
			<app>.strings		<----- optional
			en_US/
				button.png		<-----localized files - localized for US english
				<app>.strings	<-----localized strings data for en_US
			pl_PL/
				button.png		<-----localized files - localized for Poland polish
				<app>.strings	<-----localized strings data for pl_PL
			it_IT/
				button.png		<-----localized files - localized for Italy italian
				<app>.strings	<-----localized strings data for it_IT
	\endcode


	B): with contents - OSX compatible
	\code
	Bundle/
		/Contents
			<app>.exe
			Resources/
				button.png			<-----generic files - not localized
				<app>.strings		<----- optional
				en_US/
					button.png		<-----localized files - localized for US english
					<app>.strings	<-----localized strings data for en_US
				pl_PL/
					button.png		<-----localized files - localized for Poland polish
					<app>.strings	<-----localized strings data for pl_PL
				it_IT/
					button.png		<-----localized files - localized for Italy italian
					<app>.strings	<-----localized strings data for it_IT
	\endcode

	C): with contents and platform - OSX compatible		
	\code
	Bundle/
		/Contents
			/<OS-Name>
				<app>.exe
			Resources/
				button.png			<-----generic files - not localized
				<app>.strings		<----- optional
				en_US/
					button.png		<-----localized files - localized for US english
					<app>.strings	<-----localized strings data for en_US
				pl_PL/
					button.png		<-----localized files - localized for Poland polish
					<app>.strings	<-----localized strings data for pl_PL
				it_IT/
					button.png		<-----localized files - localized for Italy italian
					<app>.strings	<-----localized strings data for it_IT
					
	\endcode				

	D): with contents, platform, and compiler - OSX compatible		
	\code
	Bundle/
		/Contents
			/<OS-Name>
				/<compiler>
					<app>.exe
			Resources/
				button.png			<-----generic files - not localized
				<app>.strings		<----- optional
				en_US/
					button.png		<-----localized files - localized for US english
					<app>.strings	<-----localized strings data for en_US
				pl_PL/
					button.png		<-----localized files - localized for Poland polish
					<app>.strings	<-----localized strings data for pl_PL
				it_IT/
					button.png		<-----localized files - localized for Italy italian
					<app>.strings	<-----localized strings data for it_IT

	\endcode
	*/
	static String findResourceDirectory();

	static String findResourceDirectory( Locale* locale );

	static String findResourceDirectory( const String& fileName, Locale* locale );

	static String findResourceDirectoryForExecutable( const String& fileName );


	/**	
	Returns the name of the operating system that the VCF is currently running on.
	@return String the operating system name. Can be:
		\li "MacOS" for Mac OS
		\li	"Linux" for linux based systems
		\li "Solaris" for solaris systems
		\li	"Windows" for Win32 9.x based systems
		\li	"WindowsNT" for Win32 NT based systems
		\li	"WindowsCE" for WinCE based systems		

	*/
	static String getOSName();

	/**
	Returns the version of the operating system.
	*/
	static String getOSVersion();

	/**
	Returns the compiler that was used to build this version of the VCF. This is 
	a fixed, build setting that is platform and vendor dependant
	@return String the name of the compiler used to build the VCF. Can be:
		\li "VC6"			Microsoft Visual C++ 6
		\li "VC7"			Microsoft Visual C++ 7
		\li "VC71"			Microsoft Visual C++ 7.1
		\li "DMC"			Digital Mars
		\li	"GCC"			GCC C++ compiler
		\li "BCC4"			Borland C++ compiler BCB4
		\li "BCC5"			Borland C++ compiler BCB5
		\li "BCC6"			Borland C++ compiler BCB6

	*/
	static String getCompiler();

	/**
	Returns the computer's name, assuming this is supported 
	by the platform, otherwise an empty string.
	*/
	static String getComputerName();

	/**
	Returns the current user name that the framework is being 
	executed under.
	*/
	static String getUserName();

	/**
	Returns the current "tick" count. On Win32 systems this is analagous to the 
	GetTickCount() API. Should be millisecond resolution, but this is not by any means 
	guaranteed.
	*/
	static unsigned long getTickCount();

	/**
	Causes the calling thread/process to sleep for a specified number of milliseconds.
	*/
	static void sleep( const uint32& milliseconds );

	/**
	sets the System's ErrorLog.
	Note the Errolog is NOT owned by the System,
	so it is the caller's responsibility to clean up the
	memory. The suggested use is to create an ErrorLog
	object on the stack in your main() function and
	then pass it to the System after initialization of the
	FoundationKit is done (i.e. after initFoundationKit() )
	*/
	static void setErrorLog( ErrorLog* errorLog );

	/**
	
	Prints out the text to stdout. Allows for formatted text, just like printf() does.
	Please see printf documentation for the various formatting flags.
	
	When using this to print out strings, there are some special rules to fullow
	due to the fact that the VCF uses all unicode strings internally. For
	example:
	\code
	String aName = "Bob Jones";
	System::print( Format("User Name: %s") % aName.c_str() );
	\endcode
	On Win32 platforms the use of %s will work fine, but on others it may 
	not. To ensure that strings get printed out correctly, consider using the 
	%ls formatter, like so:
	\code
	String aName = "Bob Jones";
	System::print( Format("User Name: %ls") % aName.c_str() );
	\endcode
	or

	\code
	String aName = "Bob Jones";
	System::print( Format("User Name: %s") % aName );
	\endcode

	This will ensure that on all platforms the unicode string gets properly
	handled and output.
	@see Format
	*/
	static void print( const String& text );

	/**
	This function does what System::print() does, except that it adds a trailing
	cr/lf.
	@see System::print
	*/
	static void println( const String& text );

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
	val would equal "C:\WINNT\system32;C:\WINNT;C:\WINNT\System32\Wbem;...".
	*/
	static String getEnvironmentVariable( const String& variableName );

	/**
	Modifies (or creates) an enviroment variable for the current process. This modification
	is only good for the lifetime of the process.
	*/
	static void setEnvironmentVariable( const String& variableName, const String& newValue );

	/**
	Adds a directory to the current process's PATH environment variable. If no such environment
	variable exists, then it does nothing. Note that some systems may not even have 
	anything resembling a PATH.
	*/
	static void addPathDirectory( const String& directory );

	/**
	Returns the current working directory.
	*/
	static String getCurrentWorkingDirectory();

	/**
	Sets the current working directory
	*/
	static void setCurrentWorkingDirectory( const String& currentDirectory );

	/**
	This returns the name of a standard directory for the 
	OS. 
	@see CommonDirectory
	*/
	static String getCommonDirectory( CommonDirectory directory );

	/**
	This creates a temp file name. You can pass in a standard 
	directory type to indicate the directory to use in 
	creating the file name. For example to create 
	a temp file in the user's temp directory you might use:
	\code
	String tempFile = System::createTempFileName( System::cdUserTemp );
	\endcode
	*/
	static String createTempFileName( CommonDirectory directory );

	/**
	This creates a temp file name. You can pass in directory 
	name to indicate the directory to use in 
	creating the file name. The directory is empty
	by default. For example to create 
	just a temp file name (no directory) you might use:
	\code
	String tempFile = System::createTempFileName();
	\endcode
	*/
	static String createTempFileName( const String& directory = "" );

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

	/**
	Returns the ResourceBundle for the calling process. 
	@return ResourceBundle* a pointer to the resource bundle. Do not delete this.
	*/
	static ResourceBundle* getResourceBundle();

	/**
	Retrieves the program information from a given file name
	@param String the fully qualified file name of the process to
	retrieve information from, or a directory that includes a Info.plist/Info.xml file in it
	identifying the process's ProgramInfo.
	@see ProgramInfo
	@see ResourceBundle::getProgramInfo()
	*/
	static ProgramInfo* getProgramInfoFromFileName( const String& fileName );


	/**
	Returns a new ProgramInfo instance from a given info.xml or info.plist.
	If the infoFileName points to an invalid file, or there is some other 
	problem reading the file, then the return value is NULL. The caller
	is responsible for deleting the ProgramInfo instance if a valid 
	instance is returned.
	*/
	static ProgramInfo* getProgramInfoFromInfoFile( const String& infoFileName );

	/**
	Returns a new ProgramInfo instance from a given info.xml or info.plist.
	If the infoFileName points to an invalid file, or there is some other 
	problem reading the file, then the return value is NULL. The caller
	is responsible for deleting the ProgramInfo instance if a valid 
	instance is returned.
	@param String the full path of the info.plist/info.xml file
	@param String the path of the initial value for the program file
	*/
	static ProgramInfo* getProgramInfoFromInfoFile( const String& infoFileName, const String& programFileName );

	/**
	Returns a string that is the package directory for the
	executable file name. If the file name is not a bundle, then an
	empty string is returned. For example, if passed in a file name such as 
	"c:\Program Files\MyApp\Contents\WindowsNT\MyApp.exe", the function
	would return "c:\Program Files\MyApp\" as the result. 
	*/
	static String getBundlePathFromExecutableName( const String& fileName );

	/**
	This attempts to return the complete path to the executable content in the
	bundle, as specified by the bundle program info. Attempts are made to 
	drill down into succesively deeper directories, first the immediate bundle 
	dir, then the Contents directory, then Contents/<OS-Name>, then 
	Contents/<OS-Name>/<compiler>
	*/
	static String getExecutableNameFromBundlePath( const String& fileName );


	static void internal_replaceResourceBundleInstance( ResourceBundle* newInstance );
protected:
	System();
	virtual ~System();

	SystemPeer* systemPeer_;
	static System* systemInstance;

	ErrorLog* errorLogInstance_;

	Locale* locale_;
	
	//this is set in the constructor for the System instance
	static bool unicodeEnabled;

	ResourceBundle* resBundle_;

	static String getInfoFileFromFileName( const String& fileName );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.9  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.8.2.5  2006/03/26 22:37:35  ddiego
*minor update to source docs.
*
*Revision 1.8.2.4  2006/03/12 22:01:41  ddiego
*doc updates.
*
*Revision 1.8.2.3  2006/02/19 06:50:31  ddiego
*minor updates.
*
*Revision 1.8.2.2  2005/09/07 04:19:55  ddiego
*filled in initial code for help support.
*
*Revision 1.8.2.1  2005/07/24 02:30:27  ddiego
*fixed bug in retreiving program info.
*
*Revision 1.8  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.7  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.6  2005/01/07 02:38:39  ddiego
*merged over devmain changes to system class bug.
*
*Revision 1.5  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because 
they're important resoource loading bug fixes. Also fixes a 
few other bugs as well.
*Revision 1.4.2.8  2005/06/08 13:46:26  marcelloptr
*very minor change
*
*Revision 1.4.2.7  2005/06/08 03:27:28  ddiego
*fix for popup menus
*
*Revision 1.4.2.6  2005/03/26 00:10:30  ddiego
*added some minor funs to system class
*
*Revision 1.4.2.5  2005/03/15 01:51:52  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.4.2.4  2005/03/14 05:44:51  ddiego
*added the Formatter class as part of the process of getting rid of the var arg methods in System and StringUtils.
*
*Revision 1.4.2.3  2005/01/07 01:15:23  ddiego
*fixed a foundation kit but that was cause a crash by releasing the system instance and then making use of a member variable for it. The member variable is now static, which is more appropriate.
*
*Revision 1.4.2.2  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.4.2.1  2004/12/19 04:05:01  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.4  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.3.2.3  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.3.2.2  2004/08/26 04:29:28  ddiego
*added support for getting the resource directory to the System class.
*
*Revision 1.3.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
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


