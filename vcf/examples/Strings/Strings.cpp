#include "FoundationKit.h"

/**
*use the VCF namespace to make it more convenient 
*to refer to VCF classes
*/
using namespace VCF;


/**
This example show how to work with strings 
in the VCF and some of the extra utility functions in the StringUtils class.
Many thanks to Cesar Mello for doing the initial work on this
*/
int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

	// creating strings 
    String s = "Now";
    String t = s + " is the time."; // concatenate strings with + operator

	/**
	use System::println() to send the String to stdout
	*/
	System::println(t);

	int len = t.size();  // number of characters: 16
	System::println("Number of characters: %d", len);

    String sub = t.substr(4); // returns char 4 to end: "is the time."
	System::println("substr(4): " + sub);

    sub = t.substr(4, 2); // returns chars 4 and 5
	System::println("substr(4, 2): " + sub);

	String toFind = "foo";
    int pos = t.find(toFind); // does not find the string (returns String::npos)

    if (pos == String::npos)
    {
		System::println( "trying to find string \"foo\": not found. returns String::npos: %d", pos);
    }

	toFind = "time";
	pos = t.find(toFind); // finds the string "time" in position 11
	System::println("string \"time\" found at position: %d", pos);


	/**
	String utility functions
	*/

	/**
	format a string
	*/

	String formattedString = StringUtils::format( "Number: %d, as hex: 0x%08X, a string: %s", 12, 12, toFind.c_str() );
	System::println( formattedString );

	/**
	getting a class name from type info
	*/

	String className = StringUtils::getClassNameFromTypeInfo( typeid(int) );
	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %s", className.c_str() );

	className = StringUtils::getClassNameFromTypeInfo( typeid(StringUtils) );
	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %s", className.c_str() );

	className = StringUtils::getClassNameFromTypeInfo( typeid(System) );
	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %s", className.c_str() );


	
	/**
	transform a string to and from upper case and lowercase
	*/

	String xfrmedString = StringUtils::lowerCase( className );

	System::println( "lowercase: %s", xfrmedString.c_str() );

	xfrmedString = StringUtils::upperCase( className );

	System::println( "uppercase: %s", xfrmedString.c_str() );


	/**
	This will generate a new UUID and return it as a string
	*/
	String newUUID = StringUtils::newUUID();

	System::println( "new UUID: %s", newUUID.c_str() );


	/**
	converts various non string types to a string
	*/

	String val = StringUtils::toString( 12 );
	System::println( "value: %s", val.c_str() );

	val = StringUtils::toString( 1234.009459034 );
	System::println( "value: %s", val.c_str() );

	val = StringUtils::toString( 53433.000034f );
	System::println( "value: %s", val.c_str() );

	val = StringUtils::toString( true );
	System::println( "value: %s", val.c_str() );

	val = StringUtils::toString( false );
	System::println( "value: %s", val.c_str() );


	/**
	A trace statement useful for debugging. On Win32 systems this goes to the 
	debugger for the current application
	*/

	StringUtils::trace( "Hello World" );

	/**
	Same as above, only with variable arguments
	*/
	StringUtils::traceWithArgs( "Hello World %d times", 10 );
	

	/**
	This demonstrates trimming text from a string
	*/
	String original = "####Some text#######";

	xfrmedString = StringUtils::trim( original, '#' );
	System::println( "original: %s \nxfrmedString after StringUtils::trim(): %s", original.c_str(), xfrmedString.c_str() );


	xfrmedString = StringUtils::trimLeft( original, '#' );
	System::println( "original: %s \nxfrmedString after StringUtils::trimLeft(): %s", original.c_str(), xfrmedString.c_str() );

	xfrmedString = StringUtils::trimRight( original, '#' );
	System::println( "original: %s \nxfrmedString after StringUtils::trimRight(): %s", original.c_str(), xfrmedString.c_str() );


	/**
	The next examples uses the white space trimming functions
	*/

	original = "   12333873   ";

	xfrmedString = original;
	StringUtils::trimWhiteSpaces( xfrmedString );
	System::println( "original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpaces(): \"%s\"", original.c_str(), xfrmedString.c_str() );

	xfrmedString = original;
	StringUtils::trimWhiteSpacesLeft( xfrmedString );
	System::println( "original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpacesLeft(): \"%s\"", original.c_str(), xfrmedString.c_str() );


	xfrmedString = original;
	StringUtils::trimWhiteSpacesRight( xfrmedString );
	System::println( "original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpacesRight(): \"%s\"", original.c_str(), xfrmedString.c_str() );

	

	FoundationKit::terminate();

	return 0;
}



