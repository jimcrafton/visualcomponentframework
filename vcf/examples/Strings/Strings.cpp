//Strings.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

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

    if (pos == UnicodeString::npos)
    {
		System::println( "trying to find string \"foo\": not found. returns String::npos: %d", pos);
    }

    System::println( toFind );

	toFind = "time";

    System::println( toFind );

	pos = t.find("time"); // finds the string "time" in position 11
	System::println("string \"time\" found at position: %d in string {%ls}", pos, t.c_str() );


	/**
	String utility functions
	*/

	/**
	format a string
	*/

	String formattedString = StringUtils::format( "Number: %d, as hex: 0x%08X, a string: %ls", 12, 12, toFind.c_str() );
	System::println( formattedString );

	/**
	getting a class name from type info
	*/

	String className = StringUtils::getClassNameFromTypeInfo( typeid(double) );

	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %ls", className.c_str() );

	className = StringUtils::getClassNameFromTypeInfo( typeid(StringUtils) );
	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %ls", className.c_str() );

	className = StringUtils::getClassNameFromTypeInfo( typeid(System) );
	System::println( "StringUtils::getClassNameFromTypeInfo() returned: %ls", className.c_str() );



	/**
	transform a string to and from upper case and lowercase
	*/

	String xfrmedString = StringUtils::lowerCase( className );

	System::println( "lowercase: %ls", xfrmedString.c_str() );

	xfrmedString = StringUtils::upperCase( className );

	System::println( "uppercase: %ls", xfrmedString.c_str() );


	/**
	This will generate a new UUID and return it as a string
	*/
	String newUUID = StringUtils::newUUID();

	System::println( "new UUID: %ls", newUUID.c_str() );


	/**
	converts various non string types to a string
	*/

	String val = StringUtils::toString( 12 );
	System::println( "value: %ls", val.c_str() );

	val = StringUtils::toString( 1234.009459034 );
	System::println( "value: %ls", val.c_str() );

	val = StringUtils::toString( 53433.000034f );
	System::println( "value: %ls", val.c_str() );

	val = StringUtils::toString( true );
	System::println( "value: %ls", val.c_str() );

	val = StringUtils::toString( false );
	System::println( "value: %ls", val.c_str() );


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
	System::println( "original: %ls \nxfrmedString after StringUtils::trim(): %ls", original.c_str(), xfrmedString.c_str() );


	xfrmedString = StringUtils::trimLeft( original, '#' );
	System::println( "original: %ls \nxfrmedString after StringUtils::trimLeft(): %ls", original.c_str(), xfrmedString.c_str() );

	xfrmedString = StringUtils::trimRight( original, '#' );
	System::println( "original: %ls \nxfrmedString after StringUtils::trimRight(): %ls", original.c_str(), xfrmedString.c_str() );


	/**
	The next examples uses the white space trimming functions
	*/

	original = "   12333873   ";

	xfrmedString = original;
	StringUtils::trimWhiteSpaces( xfrmedString );
	System::println( "original: \"%ls\"\nxfrmedString after StringUtils::trimWhiteSpaces(): %ls", original.c_str(), xfrmedString.c_str() );

	xfrmedString = original;
	StringUtils::trimWhiteSpacesLeft( xfrmedString );
	System::println( "original: \"%ls\"\nxfrmedString after StringUtils::trimWhiteSpacesLeft(): \"%ls\"", original.c_str(), xfrmedString.c_str() );


	xfrmedString = original;
	StringUtils::trimWhiteSpacesRight( xfrmedString );
	System::println( "original: \"%ls\"\nxfrmedString after StringUtils::trimWhiteSpacesRight(): \"%ls\"", original.c_str(), xfrmedString.c_str() );



	FoundationKit::terminate();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:38  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.9  2004/06/06 07:05:27  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.2.4.7  2004/05/31 13:20:56  ddiego
*more osx updates
*
*Revision 1.2.4.6  2004/05/03 03:44:52  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.2.4.5  2004/04/29 03:40:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


