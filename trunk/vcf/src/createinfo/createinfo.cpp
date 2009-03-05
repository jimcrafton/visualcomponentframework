//createinfo.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/StringTokenizer.h"
#include "vcf/FoundationKit/Base64Codec.h"
#include "vcf/FoundationKit/PropertyListing.h"



using namespace VCF;


/**
createinfo is a little utility to create or update an INfo.xml file.
It provides a very simple command line interface that allows you send in 
the author, version and bundle name. It does everything else. If an
output dir is specified and the Info.plsit/xml file exists, then an update
is performed, otherwise a new file is created.
If no output directory is specified, then the program outputs to stdout.
*/

#define USAGE "Proper arguments to send to me are:\n"\
				"\t-version <version number>\n"\
				"\t-author <author name, in double quotes!>\n"\
				"\t[-out <output directory - if one is not specified, then output is to stdout>]\n"\
				"\t-name <bundle name for the info file>\n"\
				"\t-exe <executable name - NOT the path, just the name and extension."



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	CommandLine cmdLine = FoundationKit::getCommandLine();
	if ( !cmdLine.hasSwitch( "-author" ) ) {
		System::println( "Please supply an author value!" );
		System::println( USAGE );
		return 1;	
	}
	
	if ( !cmdLine.hasSwitch( "-version" ) ) {
		System::println( "Please supply an version number value!" );
		System::println( USAGE );
		return 1;	
	}

	if ( !cmdLine.hasSwitch( "-name" ) ) {
		System::println( "Please supply a bundle name!" );
		System::println( USAGE );
		return 1;	
	}

	if ( !cmdLine.hasSwitch( "-exe" ) ) {
		System::println( "Please supply an executable name!" );
		System::println( USAGE );
		return 1;	
	}

	String version = cmdLine.getArgument( "-version", 0 );
	String author = cmdLine.getArgument( "-author", 0 );
	
	String bundleName = cmdLine.getArgument( "-name", 0 );

	String exeName = cmdLine.getArgument( "-exe", 0 );

	String outDir;

	if ( cmdLine.hasSwitch( "-out" ) ) {
		FilePath fp = cmdLine.getArgument( "-out", 0 );
		
		if ( fp.isRelativePath() ) {
			//expand it completely using hte current working dir
			
			outDir = FilePath::makeDirectoryName( fp.expandRelativePathName( System::getCurrentWorkingDirectory() ) );
		}
	}

	DateTime date = DateTime::now();

	String crlf = "\n";

	String copyright = StringUtils::toString( date.getYear() ) + " " + author;

	String infoFileName = outDir + "Info.plist";
	String infoXML;

	PropertyListing plist;
	bool modified = false;

	//does the file already exist???
	if ( !outDir.empty() && File::exists( infoFileName ) ) {
		try {
			FileInputStream fs(infoFileName);
			XMLDictInputStream xis(&fs);
			xis >> &plist;


			VariantData v = plist.getByPath( "ProgramVersion" );

			if ( !plist.keyExists( "ProgramVersion" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["ProgramVersion"] = version;
				modified = true;
			}

			v = plist.getByPath( "Executable" );
			if ( !plist.keyExists( "Executable" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["Executable"] = exeName;
				modified = true;
			}

			v = plist.getByPath( "FileVersion" );
			if ( !plist.keyExists( "FileVersion" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["FileVersion"] = version;
				modified = true;
			}

			v = plist.getByPath( "ProductName" );
			if ( !plist.keyExists( "ProductName" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["ProductName"] = bundleName;
				modified = true;
			}

			v = plist.getByPath( "Copyright" );
			if ( !plist.keyExists( "Copyright" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["Copyright"] = copyright;
				modified = true;
			}

			v = plist.getByPath( "Author" );
			if ( !plist.keyExists( "Author" ) || ((v.isNull() || (v.isString() && v.toString().empty())) && !exeName.empty()) ) {
				plist["Author"] = author;
				modified = true;
			}
		}
		catch (BasicException& e) {
			System::println( "Invalid Info.xml file!\n Exception: " + e.getMessage() );
		}
		catch (...) {
			System::println( "Invalid Info.xml file!" );
			return 1;
		}
	}	
	else {
		modified = true;


		plist["ProgramVersion"] = version;
		plist["Executable"] = exeName;
		plist["FileVersion"] = version;
		plist["ProductName"] = bundleName;
		plist["Copyright"] = copyright;
		plist["Author"] = author;
		plist["Company"] = "Your company";
		
	}


	if ( !outDir.empty() && !infoFileName.empty() ) {

		//check if we need to create the directory!
		if ( !File::exists( outDir ) ) {
			//yep, go ahead and create it!

			try {
				Directory infoDir;
				infoDir.create( outDir, File::ofRead | File::ofWrite );
			}
			catch ( BasicException& e ) {
				System::println( "Error creating directory. Exception: " + e.getMessage() );
				return 1;
			}
		}


		
		if ( modified ) {
			try {
				FileOutputStream fs(infoFileName);
				XMLDictOutputStream xos(&fs);
				xos << &plist;
			}
			catch ( BasicException& e ) {
				System::println( "Error writing info dictionary. Exception: " + e.getMessage() );
				return 1;
			}
		}
	}
	else {
		System::println( plist.toString() );
	}	

	FoundationKit::terminate();
	return 0;
}



/**
$Id$
*/
