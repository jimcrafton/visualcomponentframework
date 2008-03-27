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
class FOUNDATIONKIT_API System {
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

	/**
	Finds the resource for the specific locale. The generic findResourceDirectory()
	assumes the locale that is currently set for the thread. The starting point
	is the programs executable path.
	*/
	static String findResourceDirectory( Locale* locale );


	/**
	This will find the resource directory using fileName as the starting point and
	the specified locale.
	*/
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
	static uint32 getTickCount();

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

	static void setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz );
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

	static System* getInstance();
};

};


#endif // _VCF_SYSTEM_H__

/**
$Id$
*/
