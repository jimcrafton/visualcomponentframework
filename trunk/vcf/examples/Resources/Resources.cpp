////Resources.cpp

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


/**
This simple program will demonstrate how to load up resources.
We will use bundle based resources for this test, and .rc based 
resources for the Win32 version.
*/

#define IDS_STRING1	"1"

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );


	//retrieves the System's resource bundle for this application
	ResourceBundle* resBundle = System::getResourceBundle();

	//retreive a string resource
	String val = resBundle->getString( IDS_STRING1 );

	System::println( "IDS_STRING1: " + val );
	
	val = resBundle->getString( "HELLO_STR" );

	System::println( "HELLO_STR: " + val );

	val = resBundle->getString( "goodbye_str" );

	System::println( "goodbye_str: " + val );


	/**
	This retreives a resource in the form of a raw data buffer.
	The caller is responsible for freeing the resources
	instance if one is returned
	*/

	Resource* res = resBundle->getResource( "MyData.dat" );
	if ( NULL == res ) {
		System::println( "Failed to find resource!" );
	}
	else {
		System::println( "Found resource " + res->getName() + 
							" size in bytes: " + StringUtils::toString(res->getDataSize()) +
							" buffer: " + Format( "%p") % res->getData() );

		res->free();
	}

	/**
	This will extract a resource from the exe
	*/
	res = resBundle->getResource( "logo.png" );
	if ( NULL == res ) {
		System::println( "Failed to find resource!" );
	}
	else {
		System::println( "Found resource " + res->getName() + 
							" size in bytes: " + StringUtils::toString(res->getDataSize()) +
							" buffer: " + Format( "%p" ) % res->getData() );

		res->free();
	}


	/**
	Get program information about the program from either the 
	Win32 RT_VERSION res type, or, if the file exists, the Info.xml (or Info.plist)
	meta-data files.
	The caller is responsible for releasing the ProgramInfo instance
	*/
	ProgramInfo* info = resBundle->getProgramInfo();
	if ( NULL == info ) {
		System::println( "Sorry, no program information was found." );
	}
	else {
		System::println( "Program information:" );

		System::println( info->getProgramName() );
		System::println( info->getProgramVersion() );
		System::println( info->getAuthor() );
		System::println( info->getCompany() );
		System::println( info->getDescription() );		


		info->free();
	}

	FoundationKit::terminate();
	return 0;
}


