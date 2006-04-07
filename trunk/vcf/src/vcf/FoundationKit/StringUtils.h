#ifndef _VCF_STRINGUTILS_H__
#define _VCF_STRINGUTILS_H__
//StringUtils.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define MAX_TRACE_STRING		5000



// forward declaration needed for bcc32
class type_info;

namespace VCF {

class DateTime;
class VariantData;
class Format;

/**
\class StringUtils StringUtils.h "vcf/FoundationKit/StringUtils.h"
The StringUtils class is a collection of static
utility methods for operating on strings.
*/
class FOUNDATIONKIT_API StringUtils  {
public:

	/**
	outputs the text to the debugger output
	@param String the text to output
	*/
	static void trace( const VCF::String& text );

	/**
	Similar to trace() but allows variable arguments. Uses the
	same formatting rules as printf().
	@param String the text to trace out after formatting. See printf()
	for formatting rules.
	\deprecated 
	This is now a deprecated function and should not be used at all. Existing
	code should be changed to make use of the traceWithArgs( const Format& ) function 
	instead. It will be removed entirely in an upcoming release.
	*/
	//static void traceWithArgs( const VCF::String& text );

	static void traceWithArgs( const Format& formatter );

	/**
	formats a string. Uses the same formatting rules as
	sprintf().
	@param String the format text to use
	@return String the formatted string
	\deprecated 
	This is now a deprecated function and should not be used at all. Existing
	code should be changed to make use of the traceWithArgs( const Format& ) function 
	instead. It will be removed entirely in an upcoming release.
	*/
	//static VCF::String format( VCF::String formatText, ... );

	/**
	formats a string. Uses the same formatting rules as
	sprintf().
	@param Format the formatter to use
	@return String the formatted string
	@see Format
	*/
	static VCF::String format( const Format& formatter );

	/**
	trim all the occurrences of a specified character
	* at the beginning of the string
	 until it is met the first character from the left that is different
	@param String the text to trim
	@param char the character to trim
	@return String the trimmed string
	*/
	static VCF::String trimLeft( const VCF::String& text, const char& c );

	/**
	trim all the occurrences of a specified character
	at the end of the string
	until it is met the first character from the right that is different
	@param String the text to trim
	@param char the character to trim
	@return String the trimmed string
	*/
	static VCF::String trimRight( const VCF::String& text, const char& c );

	/**
	trim all the occurrences of a specified character
	at the beginning and the end of the string
	i.e. calls trimLeft + trimRight
	@param String the text to trim
	@param char the character to trim
	@return String the trimmed string
	*/
	static VCF::String trim( const VCF::String& text, const char& c );

	/**
	trim all the occurrences of any <space>, <tab>, <CR> and <LF>
	at the beginning of the string
	until it is met the first character from the left that is not a whitespace one
	@param String the text to trim
	*/
	static void trimWhiteSpacesLeft( VCF::String& text );

	/**
	trim all the occurrences of any <space>, <tab>, <CR> and <LF>
	at the end of the string
	until it is met the first character from the right that is not a whitespace one
	@param String the text to trim
	*/
	static void trimWhiteSpacesRight( VCF::String& text );

	/**
	trim all the occurrences of any <<space>, <tab>, <CR> and <LF>
	at the beginning and the end of the string
	i.e. calls trimWhiteSpacesLeft + trimWhiteSpacesRight
	@param String the text to trim
	*/
	static void trimWhiteSpaces( VCF::String& text );

	/**
	gets a copy of the string that is having erased all its characters on the left 
	of the count-th occurrence of the character ch.
	If the character is not found, the result string is equal to the original one.
	@param String the source string
	@param const VCFChar& ch, the char to be searched
	@param const bool& included, includes the found char in the erasing. By default is false.
	@param const int& count, number of occurrences of the character to search for.
	A negative value means a search from the end of the string. Default is +1.
	in the string. A count = 0 means no erasing on the string. It the count exceeds the
	number of occurrences in the string then search stops at the last one.
	@return String, the modified string.
	*/
	static String eraseLeftOfChar( const String& s, const VCFChar& ch, const bool& included=false, const int& count=1 );

	/**
	gets a copy of the string that is having erased all its characters on the right 
	of the count-th occurrence of the character ch.
	If the character is not found, the result string is equal to the original one.
	@param String the source string
	@param const VCFChar& ch, the char to be searched
	@param const bool& included, includes the found char in the erasing. By default is false.
	@param const int& count, number of occurrences of the character to search for.
	A negative value means a search from the end of the string. Default is +1.
	in the string. A count = 0 means no erasing on the string. It the count exceeds the
	number of occurrences in the string then search stops at the last one.
	@return String, the modified string.
	*/
	static String eraseRightOfChar( const String& s, const VCFChar& ch, const bool& included=false, const int& count=1 );

	/**
	converts the string to lower case
	@param String the text to convert
	@return String the converted string
	*/
	static VCF::String lowerCase( const VCF::String& text );

	/**
	converts the string to upper case
	@param String the text to convert
	@return String the converted string
	*/
	static VCF::String upperCase( const VCF::String& text );

	/**
	Performs a case insensitive string compare between str1 and
	str2. This may not be locale safe, but it will try and use
	the lower level OS facilities for case insensitive string
	comparison if they exist. Otherwise it will simply convert 
	both strings to uppercase and compare the results.
	@return int returns 0 if the strings are equivalent, returns
	greater than 0 if str1 is greater than str2, and returns less
	than 0 if str1 is less than str2.
 	*/
	static int noCaseCompare( const VCF::String& str1, const VCF::String& str2 );

	/**
	converts the value to a string
	@param uchar the hexadecimal value to convert
	@return String the string representation of the hexadecimal value
	*/
	static VCF::String toStringFromHexNumber( const uchar& value );

	/**
	converts the value to a string
	@param int the value to convert
	@return String the string representation of the int value
	*/
	static VCF::String toString( const int& value );

	/**
	converts the value to a string
	@param uint32 the value to convert
	@return String the string representation of the unsigned int value
	*/
	static VCF::String toString( const VCF::uint32& value );

	/**
	converts the value to a string
	@param long the value to convert
	@return String the string representation of the long value
	*/
	static VCF::String toString( const long& value );

	/**
	converts the value to a string
	@param ulong32 the value to convert
	@return String the string representation of the unsigned long value
	*/
	static VCF::String toString( const VCF::ulong32& value );

	/**
	converts the value to a string
	@param VCF::long64 the value to convert
	@return String the string representation of the VCF::long64 value
	*/
	static VCF::String toString( const VCF::long64& value );

	/**
	converts the value to a string
	@param VCF::ulong64 the value to convert
	@return String the string representation of the VCF::ulong64 value
	*/
	static VCF::String toString( const VCF::ulong64& value );

	/**
	converts the value to a string
	@param float the value to convert
	@return String the string representation of the float value
	*/
	static VCF::String toString( const float& value );

	/**
	converts the value to a string
	@param double the value to convert
	@return String the string representation of the double value
	*/
	static VCF::String toString( const double& value );

	/**
	converts the value to a string
	@param char int the value to convert
	@return String the string representation of the char value
	*/
	static VCF::String toString( const char& value );

	/**
	converts the value to a string
	@param char bool the value to convert
	@return String the string representation of the bool value
	*(either "true" or "false")
	*/
	static VCF::String toString( const bool& value );


	/**
	Converts a VariantData instance to a string.
	@param VariantData the variant to convert
	@return String the string returned from calling VariantData::toString
	*/
	static VCF::String toString( const VariantData& value );

	/**
	converts the value to an hexadecimal number
	@param String the value to convert
	@return int the hexadecimal representation of the String value
	*/
	static int fromStringAsHexNumber( const VCF::String& value );

	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static int fromStringAsInt( const VCF::String& value );

	/**
	converts the value to an unsigned integer
	@param String the value to convert
	@return uint32 the unsigned integer representation of the String value
	*/
	static VCF::uint32 fromStringAsUInt( const VCF::String& value );

	/**
	converts the value to a long
	@param String the value to convert
	@return long the long integer representation of the String value
	*/
	static long fromStringAsLong( const VCF::String& value );

	/**
	converts the value to an unsigned long
	@param String the value to convert
	@return ulong32 the unsigned long integer representation of the String value
	*/
	static VCF::ulong32 fromStringAsULong( const VCF::String& value );

	/**
	converts the value to a 64 bit signed integer 
	@param String the value to convert
	@return long64 the 64 bit signed integer representation of the String value
	*/
	static VCF::long64 fromStringAsLong64( const VCF::String& value );

	/**
	converts the value to a 64 bit unsigned integer 
	@param String the value to convert
	@return ulong64 the 64 bit unsigned integer representation of the String value
	*/
	static VCF::ulong64 fromStringAsULong64( const VCF::String& value );




	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static float fromStringAsFloat( const VCF::String& value );

	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static double fromStringAsDouble( const VCF::String& value );

	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static char fromStringAsChar( const VCF::String& value );

	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static short fromStringAsShort( const VCF::String& value );

	/**
	converts the value to an int
	@param String the value to convert
	@return int the integer representation of the String value
	*/
	static bool fromStringAsBool( const VCF::String& value );


	/**
	generates a new UUID and returns the string representation
	@return String the new UUID as a string value
	*/
	static VCF::String newUUID();

	/**
	gets the class name from a type_info struct.
	@param type_info the value returned from the
	expression :
	\code
		typeid(AClass)
	\endcode
	@return String the name of the class the typeInfo references
	*/
	static VCF::String getClassNameFromTypeInfo( const std::type_info& typeInfo );

	/**
	Converts a typeinfo to a string. GCC does such a piss poor job of this
	that we have to write our own coverter, since the data returned by
	the GCC implemented type_info::name() is useless.
	*/
	static VCF::String toString( const std::type_info& typeInfo );
	
	/**
	Formats a string from date time object using the various argument/formatting
	tags in the formatting string. For example, a date that equals "Jan 2, 2005",
	and a formatting string of "%a %B %#d, %Y" will return string that equals
	"Sunday January 2, 2005". A listing of the possible format codes follows:
	<table>
		<tr>
			<td>Format code</td> <td>Meaning</td>
		</tr>
		<tr>
			<td>%%</td>
		<td>outputs just a "%" character</td>
		</tr>
		<tr>
			<td>%a</td>
		<td>Abbreviated weekday name</td>
		</tr>
		<tr>
			<td>%A</td>
		<td>Full weekday name</td>
		</tr>
		<tr>
			<td>%b</td>
		<td>Abbreviated month name</td>
		</tr>
		<tr>
			<td>%B</td>
		<td>Full month name</td>
		</tr>
		<tr>
			<td>%c</td>
		<td>Date and time representation appropriate for locale</td>
		</tr>
		<tr>
			<td>%d </td>
		<td>Day of month as decimal number (01 – 31)</td>
		</tr>
		<tr>
			<td>%D</td>
		<td>Day of the year as decimal number</td>
		</tr>
		<tr>
			<td>%H</td>
		<td>Hour in 24-hour format (00 – 23)</td>
		</tr>
		<tr>
			<td>%I</td>
		<td>Hour in 12-hour format (01 – 12)</td>
		</tr>
		<tr>
			<td>%j </td>
		<td>Day of year as decimal number (001 – 366)</td>
		</tr>
		<tr>
			<td>%m</td>
		<td>Month as decimal number (01 – 12) </td>
		</tr>
		<tr>
			<td>%M</td>
		<td>Minute as decimal number (00 – 59) </td>
		</tr>
		<tr>
			<td>%p</td>
		<td>Current locale's A.M./P.M. indicator for 12-hour clock</td>
		</tr>
		<tr>
			<td>%S</td>
		<td>Second as decimal number (00 – 59) </td>
		</tr>
		<tr>
			<td>%U</td>
		<td>Week of year as decimal number, with Sunday as first day of week (00 – 53) </td>
		</tr>
		<tr>
			<td>%w</td>
		<td>Weekday as decimal number (0 – 6; Sunday is 0) </td>
		</tr>
		<tr>
			<td>%W</td>
		<td>Week of year as decimal number, with Monday as first day of week (00 – 53) </td>
		</tr>
		<tr>
			<td>%x</td>
		<td>Date representation for current locale</td>
		</tr>
		<tr>
			<td>%X</td>
		<td>Time representation for current locale </td>
		</tr>
		<tr>
			<td>%y</td>
		<td>Year without century, as decimal number (00 – 99)</td>
		</tr>
		<tr>
			<td>%Y</td>
		<td>Year with century, as decimal number</td>
		</tr>
		<tr>
			<td>%s</td>
		<td>millisecond part</td>
		</tr>
	</table>
	@param Date the date to use
	@param String a string with formatting codes in it.
	@return String the newly formatted string
	*/
	static VCF::String format( const DateTime& date, const String& formatting );

	/**
	This functions is used to change, if neccessary, a format string
	to one accceptable for the native platforms string formatting routines.
	Its existance is due to the fact that OSX's Core Foundation
	string formatting routines do <b>not</b> understand how to deal
	with unicode buffers without the use of the "%S" format directive.
	Naturally, no other system uses the "%S" directive, hence the
	neccessity of this function, which will search for the presence of
	the "%ls" directive (which on both Win32 and linux based systems
	accepts a unicode/wchar_t buffer) and replace it with the %S directive.
	To be smart the search/replace will only occur if called on OSX.
	*/
	static VCF::String convertFormatString( const String& formattedString );

	/**
	Translate a VirtualKey code into a human readable string.
	This can be used to display an accelerator key into a string to
	be displayed in a MenuItem when an accelerator is associated to it.
	*/
	static VCF::String translateVKCodeToString( VirtualKeyCode code );
protected:
	static String weekdays[];
	static String abbrevWeekdays[];
	static String months[];
	static String abbrevMonths[];
};



















/**
The following functions provide support for appending and translating various 
primitive types to string values. This makes it more convenient to write strings
that also have integers, objects, or other types as part of the string message.
The goal is to slowly get away from using the variable argument sprintf() style
functions such as StringUtils::traceWithArgs(), or System::println().
For example, you might have written the following code:
\code
System::println( Format("Name %s, number %d") % str % 1223 );
\endcode
With the operators below you can now rewrite this like so:
\code
System::println( "Name " + str + " number " + 1223 );
\endcode

*/

	
String operator+ ( const String& lhs, const int& val );

String& operator+= ( String& lhs, const int& val );

String operator+ ( const String& lhs, const unsigned int& val );

String& operator+= ( String& lhs, const unsigned int& val );

String operator+ ( const String& lhs, const long& val );

String& operator+= ( String& lhs, const long& val );

String operator+ ( const String& lhs, const unsigned long& val );

String& operator+= ( String& lhs, const unsigned long& val );

String operator+ ( const String& lhs, const short& val );

String& operator+= ( String& lhs, const short& val );

String operator+ ( const String& lhs, const double& val );

String& operator+= ( String& lhs, const double& val );


String operator+ ( const String& lhs, const float& val );

String& operator+= ( String& lhs, const float& val );

String operator+ ( const String& lhs, const bool& val );

String& operator+= ( String& lhs, const bool& val );

String operator+ ( const String& lhs, const ulong64& val );

String& operator+= ( String& lhs, const ulong64& val );

String operator+ ( const String& lhs, const long64& val );

String& operator+= ( String& lhs, const long64& val );

/*
void pointers!
*/
String operator+ ( const String& lhs, void* val );

String& operator+= ( String& lhs, void* val );

/**
Objects!
*/
String operator+ ( const String& lhs, Object& val );

String& operator+= ( String& lhs, Object& val );

String operator+ ( const String& lhs, Object* val );

String& operator+= ( String& lhs, Object* val );


/**
type info!
*/
String operator+ ( const String& lhs, const std::type_info& typeInfo );

String& operator+= ( String& lhs, const std::type_info& typeInfo );



/**
Variant data
*/
String operator+ ( const String& lhs, const VariantData& rhs );

String& operator+= ( String& lhs, const VariantData& rhs );




};//end of namespace VCF






namespace VCF {
/**
Implementation of string operators
*/



inline String operator+ ( const String& lhs, const int& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const int& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const unsigned int& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const unsigned int& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const long& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const long& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const unsigned long& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const unsigned long& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const short& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const short& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const double& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const double& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const float& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const float& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const bool& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const bool& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const ulong64& val )
{
	return lhs + StringUtils::toString(val);
}

inline String& operator+= ( String& lhs, const ulong64& val )
{
	return lhs += StringUtils::toString(val);
}

inline String operator+ ( const String& lhs, const long64& val )
{
	return lhs + StringUtils::toString(val); 
}

inline String& operator+= ( String& lhs, const long64& val )
{
	return lhs += StringUtils::toString(val);
}

/*
void pointers!
*/
inline String operator+ ( const String& lhs, void* val )
{
	char tmp[256];
	sprintf( tmp, "%p", val );
	
	return lhs + tmp;
}

inline String& operator+= ( String& lhs, void* val )
{
	char tmp[256];
	sprintf( tmp, "%p", val );

	return lhs += tmp;
}

/**
Objects!
*/

inline String operator+ ( const String& lhs, Object& val )
{
	return lhs + val.toString();
}

inline String& operator+= ( String& lhs, Object& val )
{
	return lhs += val.toString();
}

inline String operator+ ( const String& lhs, Object* val )
{
	return lhs + ((val != NULL) ? val->toString() : String("null"));
}

inline String& operator+= ( String& lhs, Object* val )
{
	return lhs += ((val != NULL) ? val->toString() : String("null"));
}


/**
type info!
*/
inline String operator+ ( const String& lhs, const std::type_info& typeInfo )
{
	return lhs + StringUtils::getClassNameFromTypeInfo( typeInfo );
}

inline String& operator+= ( String& lhs, const std::type_info& typeInfo )
{
	return lhs += StringUtils::getClassNameFromTypeInfo( typeInfo );
}

/**
Variant data
*/

inline String operator+ ( const String& lhs, const VariantData& rhs )
{
	return lhs + StringUtils::toString(rhs);
}

inline String& operator+= ( String& lhs, const VariantData& rhs )
{
	return lhs += StringUtils::toString(rhs);
}


};
/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.5  2006/03/12 22:01:41  ddiego
*doc updates.
*
*Revision 1.5.2.4  2006/01/22 17:19:38  ddiego
*fixed some bugs in type_info handling for gcc.
*
*Revision 1.5.2.3  2006/01/22 05:50:09  ddiego
*added case insensitive string compare to string utils class.
*
*Revision 1.5.2.2  2005/08/01 17:11:46  marcelloptr
*minor fixes or additions
*
*Revision 1.5.2.1  2005/07/24 02:30:26  ddiego
*fixed bug in retreiving program info.
*
*Revision 1.5  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.4  2005/07/09 23:15:05  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.7  2005/04/11 17:07:13  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3.2.6  2005/03/15 01:51:52  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.5  2005/03/14 18:56:47  marcelloptr
*comments and added an error message to avoid an infinite loop
*
*Revision 1.3.2.4  2005/03/14 05:44:51  ddiego
*added the Formatter class as part of the process of getting rid of the var arg methods in System and StringUtils.
*
*Revision 1.3.2.3  2005/03/14 04:17:25  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.2.2  2005/02/20 23:10:15  kiklop74
*Fixed minor issue wioth ? operator. Borland compiler requires exactly same return types.
*
*Revision 1.3.2.1  2005/02/16 05:09:33  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/23 12:20:00  marcelloptr
*bugfix [1048400] menus are now merged regardless of their shortcut key
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/07/26 00:47:38  marcelloptr
*added conversions String <-> long64
*
*Revision 1.1.2.8  2004/07/21 02:06:53  marcelloptr
*BugFix 985136 cast to (int) and ulong64 and other conversion issues
*The fromStringAs... functions now throw an exception in case of some errors
*
*Revision 1.1.2.7  2004/07/05 01:01:55  marcelloptr
*added ulong64 ctor, operators and toString conversion
*
*Revision 1.1.2.6  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.14.2.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.13.2.2  2004/01/17 18:47:30  ddiego
*added a new example for DateTime calss and some other minor fixes to it
*
*Revision 1.13.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.13  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.4  2003/11/10 01:57:43  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.12.4.3  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.12.4.2  2003/08/20 22:55:20  ddiego
*got rid of some older methods for StringUtils, should be using the FilePath
*class instead
*
*Revision 1.12.4.1  2003/08/11 19:58:53  marcelloptr
*improvement: StringUtils::trimWhiteSpaces functions added
*
*Revision 1.12  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2002/12/28 21:51:19  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.10  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.9.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_STRINGUTILS_H__


