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
Sample object that demonstrates overloading the toString method of the 
Object base class.
*/
class Foo : public Object {
public:
	virtual String toString() {
		return String("Foo here!\n\t") + Object::toString();
	}
};




/**
This example show how to work with strings
in the VCF and some of the extra utility functions in the StringUtils class.
Many thanks to Cesar Mello for doing the initial work on this
*/
int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

	try { 	
		
		// creating strings
		String s = "Now";
		String t = s + " is the time."; // concatenate strings with + operator

		/**
		use System::println() to send the String to stdout
		*/
		System::println(t);

		int len = t.size();  // number of characters: 16
		System::println(Format("Number of characters: %d") % len);

		String sub = t.substr(4); // returns char 4 to end: "is the time."
		System::println("substr(4): " + sub);

		sub = t.substr(4, 2); // returns chars 4 and 5
		System::println("substr(4, 2): " + sub);

		String toFind = "foo";
		int pos = t.find(toFind); // does not find the string (returns String::npos)

		if (pos == UnicodeString::npos)
		{
			System::println( Format("trying to find string \"foo\": not found. returns String::npos: %d") % pos);
		}

		System::println( toFind );

		toFind = "time";

		System::println( toFind );

		pos = t.find("time"); // finds the string "time" in position 11
		System::println( Format("string \"time\" found at position: %d in string {%s}") % pos % t );


		

		Foo f;
		System::println( String("f is: ") + f + "\n" + 99.5643231 + " bottles of " + &f + " on the wall!" );

		System::println( String("Is this ") + true + " or is this " + false + "?" );

		DateTime dt = DateTime::now();

		System::println( "The time is now: " + dt );

		void* ptr = &dt;

		System::println( String("The value of the void* pointer ptr is: ") + ptr );


		int i = 0;
		bool j = false;
		const double* k = NULL;
		float l = 0;
		Object o;
		
		System::println( "i is a " + typeid(i) + " type" );
		System::println( "j is a " + typeid(j) + " type" );
		System::println( "k is a " + typeid(k) + " type" );
		System::println( "l is a " + typeid(l) + " type" );
		System::println( "o is a " + typeid(o) + " type" );
		System::println( "f is a " + typeid(f) + " type" );
		System::println( "ptr is a " + typeid(ptr) + " type" );
		System::println( "dt is a " + typeid(dt) + " type" );

		long64 m = 0xffffffff;
		System::println( String("m: ") + m );

		m *= -0xfff;

		System::println( String("m: ") + m );


		VariantData v;
		v = 123;

		System::println( String("Variant (as int): ") + v );

		v = 441.2340995;
		System::println( String("Variant (as double): ") + v );

		v = &f;
		System::println( String("Variant (as object): ") + v );

		v = &dt;
		System::println( String("Variant (as object): ") + v );

		v = true;
		System::println( String("Variant (as boolean): ") + v );

		v = -199;
		System::println( String("Variant (as signed int): ") + v );

		v = 'A';
		System::println( String("Variant (as character): ") + v );

		v = "Hello World!";
		System::println( String("Variant (as string): ") + v );

		/**
		String utility functions
		*/

		/**
		format a string
		*/		
		String formattedString = Format( "hello %d, %0.2f World!!" ) % 1002 % 12.456330;
		System::println( formattedString );

		//error - too many arguments, expecting 2 argument, recv'd 3!
		try {
			formattedString = Format( "hello %d, %0.2f World!!" ) % 1002 % 0.0786 % 456;
			System::println( formattedString );
		}
		catch ( std::exception& e ) {
			System::print( Format("%s\n") % e.what() );
		}


		//error - too few arguments, expecting 2 argument, recv'd 1!
		try {
			formattedString = Format( "hello %d, %0.2f World!!" ) % 1002;
			System::println( formattedString );
		}
		catch ( std::exception& e ) {
			System::print( Format("%s\n") % e.what() );
		}

		//StringUtils::format is deprecated - don't use in new code
		formattedString = Format( "Number: %d, as hex: 0x%08X, a string: %s" ) % 12 % 12 % toFind;
		System::println( formattedString );


		//same thing with a Format
		formattedString = Format( "Number: %d, as hex: 0x%08X, a string: %s") % 12 % 12 % toFind;
		System::println( formattedString );

		/**
		code added with only purpose of fulling testing the Format functionality
		*/
		s = Format( "abc" );
		VCF_ASSERT(  "abc" == s );

		s = Format( "%%" );
		VCF_ASSERT(  "%" == s );

		s = Format( "%d" ) % 1;
		VCF_ASSERT(  "1" == s );

		s = Format( "%d%%" ) % 1;
		VCF_ASSERT(  "1%" == s );

		s = Format( "a %d%%" ) % 1;
		VCF_ASSERT(  "a 1%" == s );

		s = Format( "%% %d%%" ) % 1;
		VCF_ASSERT(  "% 1%" == s );

		s = Format( "a %% %% %d" ) % 1;
		VCF_ASSERT(  "a % % 1" == s );

		s = Format( "%da %% %% %d" ) % 1 % 2;
		VCF_ASSERT(  "1a % % 2" == s );

		s = Format( "%da %% %% %d%%" ) % 1 % 2;
		VCF_ASSERT(  "1a % % 2%" == s );

		s = Format( "%da %% %% %d%%%d" ) % 1 % 2 % 3;
		VCF_ASSERT( "1a % % 2%3" == s );

		s = Format( "%da %% %% %d%%%d%%" ) % 1 % 2 % 3;
		VCF_ASSERT( "1a % % 2%3%" == s );

		s = Format( "%da %% %% %d%%%%%d%%" ) % 1 % 2 % 3;
		VCF_ASSERT( "1a % % 2%%3%" == s );

		s = Format("Hola from %s") % String("me");
		VCF_ASSERT( "Hola from me" == s );

		s = Format("Hola from %s%%") % String("me");
		VCF_ASSERT( "Hola from me%" == s );

		s = Format( "a %d \r\n" ) % 1 ;
		VCF_ASSERT( "a 1 \r\n" == s );

		s = Format( "a %5d \r\n" ) % 1 ;
		VCF_ASSERT( "a     1 \r\n" == s );

		s = Format( "a	%d --> %d  is %d .. %d \r\n" ) % 1 % 2 % 3 % 4;
		VCF_ASSERT( "a	1 --> 2  is 3 .. 4 \r\n" == s );


		//error - too many arguments, expecting 2 argument, recv'd 3!
		try {
			s = Format( "%%d" ) % 1;
		}
		catch ( std::exception& e ) {
			System::print( Format("%s\n") % e.what() );
		}

		s = Format( "%d" ) %1;

		try {
			s = Format( "%d" );
		}
		catch ( std::exception& e ) {
			System::print( Format("%s\n") % e.what() );
		}

		try {
			s = Format( "%d %d" ) % 1;
		}
		catch ( std::exception& e ) {
			System::print( Format("%s\n") % e.what() );
		}





		
		/**
		getting a class name from type info
		*/

		String className = StringUtils::getClassNameFromTypeInfo( typeid(double) );

		System::println( Format("StringUtils::getClassNameFromTypeInfo() returned: %s") % className );

		className = StringUtils::getClassNameFromTypeInfo( typeid(StringUtils) );
		System::println( Format("StringUtils::getClassNameFromTypeInfo() returned: %s") % className );

		className = StringUtils::getClassNameFromTypeInfo( typeid(System) );
		System::println( Format("StringUtils::getClassNameFromTypeInfo() returned: %s") % className );



		/**
		transform a string to and from upper case and lowercase
		*/

		String xfrmedString = StringUtils::lowerCase( className );

		System::println( Format("lowercase: %s") % xfrmedString );

		xfrmedString = StringUtils::upperCase( className );

		System::println( Format("uppercase: %s") % xfrmedString );


		/**
		This will generate a new UUID and return it as a string
		*/
		String newUUID = StringUtils::newUUID();

		System::println( Format("new UUID: %s") % newUUID );


		/**
		converts various non string types to a string
		*/

		String val = StringUtils::toString( 12 );
		System::println( Format("value: %s") % val );

		val = StringUtils::toString( 1234.009459034 );
		System::println( Format("value: %s") % val );

		val = StringUtils::toString( 53433.000034f );
		System::println( Format("value: %s") % val );

		val = StringUtils::toString( true );
		System::println( Format("value: %s") % val );

		val = StringUtils::toString( false );
		System::println( Format("value: %s") % val );


		/**
		A trace statement useful for debugging. On Win32 systems this goes to the
		debugger for the current application
		*/

		StringUtils::trace( "Hello World" );

		/**
		Same as above, only with variable arguments
		*/
		StringUtils::trace( Format("Hello World %d times") % 10 );


		/**
		This demonstrates trimming text from a string
		*/
		String original = "####Some text#######";

		xfrmedString = StringUtils::trim( original, '#' );
		System::println( Format("original: %s \nxfrmedString after StringUtils::trim(): %s") % original % xfrmedString );


		xfrmedString = StringUtils::trimLeft( original, '#' );
		System::println( Format("original: %s \nxfrmedString after StringUtils::trimLeft(): %s") % original % xfrmedString );

		xfrmedString = StringUtils::trimRight( original, '#' );
		System::println( Format("original: %s \nxfrmedString after StringUtils::trimRight(): %s") % original % xfrmedString );


		/**
		The next examples uses the white space trimming functions
		*/

		original = "   12333873   ";

		xfrmedString = original;
		StringUtils::trimWhiteSpaces( xfrmedString );
		System::println( Format("original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpaces(): %s") % original % xfrmedString );

		xfrmedString = original;
		StringUtils::trimWhiteSpacesLeft( xfrmedString );
		System::println( Format("original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpacesLeft(): \"%s\"") % original % xfrmedString );


		xfrmedString = original;
		StringUtils::trimWhiteSpacesRight( xfrmedString );
		System::println( Format("original: \"%s\"\nxfrmedString after StringUtils::trimWhiteSpacesRight(): \"%s\"") % original % xfrmedString );


		System::println( "." );
		System::println( "all the tests and the example have completed successfully" );
	}
	catch ( std::exception& e ) {
		System::print( e.what() );
	}


	FoundationKit::terminate();

	return 0;
}




namespace VCF {




};


/**
$Id$
*/
