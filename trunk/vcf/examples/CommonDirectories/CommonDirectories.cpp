////CommonDirectories.cpp

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


/**
This is a trivial program to show how to retreive
common directories.
*/
int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	String dir;

	System::println( Format("Get information for User: %ls on computer: %ls\n") 
						% System::getUserName().c_str() 
						% System::getComputerName().c_str() );

	dir = System::getCommonDirectory( System::cdUserHome );	
	System::println( Format("System::cdUserHome: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdUserProgramData );	
	System::println( Format("System::cdUserProgramData: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdUserDesktop );	
	System::println( Format("System::cdUserDesktop: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdUserFavorites );	
	System::println( Format("System::cdUserFavorites: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdUserDocuments );	
	System::println( Format("System::cdUserDocuments: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdUserTemp );	
	System::println( Format("System::cdUserTemp: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdSystemPrograms );	
	System::println( Format("System::cdSystemPrograms: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdSystemTemp );	
	System::println( Format("System::cdSystemTemp: %ls\n") % dir.c_str() );

	dir = System::getCommonDirectory( System::cdSystemRoot );	
	System::println( Format("System::cdSystemRoot: %ls\n") % dir.c_str() );


	FoundationKit::terminate();
	return 0;
}


